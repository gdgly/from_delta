/** *****************************************************************************
 * \file    llcctrl.c
 * \brief   LLC control loop and related routines
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date$
 *  $Author$
 *  $Revision$
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#define DEBUG_VAR
#include "global.h"
#include "debug_llc.h"

/* Module header */
#define LLCCTRL_EXPORT_H
  #include "llcctrl_api.h"
  #include "llcctrl_scb.h"
  #include "llcctrl_cfg.h"
  #include "llcctrl_scfg.h"
  #include "llcctrl_rte.h"
  #include "llcctrl_conf.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/***********************************************
 * Voltage control loop
 **********************************************/
typedef struct
{
  sint32 s32q24VoltB0;
  sint32 s32q24VoltB1;
  sint32 s32q24VoltB2;
  sint32 s32q24VoltB3;
  sint32 s32q24VoltA1;
  sint32 s32q24VoltA2;
  sint32 s32q24VoltA3;

  uint32 u321nsVoltU0;
  uint32 u32q41nsVoltU0;
  uint32 u32q41nsVoltU1;
  uint32 u32q41nsVoltU2;
  uint32 u32q41nsVoltU3;
  sint32 s3210mVVoltE0;
  sint32 s3210mVVoltE1;
  sint32 s3210mVVoltE2;
  sint32 s3210mVVoltE3;
  sint32 s3210mVVoltErr;
  sint32 sS1610mVMaxVoltErr;
  sint32 sS1610mErrAvg;

/***********************************************
 * PWM control mode
 **********************************************/
#if MG_PWM_CTRL_MODE
  sint32 s32q16PwmModeU0;
  sint32 s32q16PwmModeU1;
  sint32 s3210mVPwmModeE0;
  sint32 s3210mVPwmModeE0Tmp;
  sint32 s3210mVPwmModeE1;
#else
  sint16 s16BmCtr;
  sint16 s1610mVBmAdj;
#endif
/***********************************************
 * Switchinng frequency
 **********************************************/
  uint32 u321nsLlcPeriod;
  uint32 u321nsLlcPeriodMin;

} MG_S_3P3Z_CTRL;

typedef struct
{
  sint32 s32q15IirB0;
  sint32 s32q15IirB1;
  sint32 s32q15IirB2;
  sint32 s32q30IirA1;
  sint32 s32q30IirA2;
} MG_S_IIR_FILT;

/***********************************************
 * LoopStatus
 **********************************************/
static GLOBAL_U_U8BIT LLCCTRL_mg_uCtrlStatus;

/***********************************************
 * Measurements
 **********************************************/
static uint16 LLCCTRL_mg_u1610mVVoltOutExtRaw = 0U;
static uint16 LLCCTRL_mg_u1610mVVoltOutExt = 0U;
static uint16 LLCCTRL_mg_u1610mVVoltOutIntRaw = 0U;
static uint16 LLCCTRL_mg_u1610mVVoltOutInt = 0U;
static uint16 LLCCTRL_mg_u1610mVVoltOut = 0U;
static uint16 LLCCTRL_mg_u1610mACurrOutRaw = 0U;
static uint16 LLCCTRL_mg_u1610mACurrOutFlt = 0U;
static uint16 LLCCTRL_mg_u1610mACurrOut = 0U;
static uint32 LLCCTRL_mg_u32q15_Kext_Vout = 32767U;
static uint32 LLCCTRL_mg_u32q15_Kint_Vout = 0U;
#if MG_CALIBRATE_VREF_IOUT
  static uint16 LLCCTRL_mg_u16q12VoltRefCaliFact = 4095U;
#endif
static uint16 LLCCTRL_mg_u16q12CalibVoltOutGain;
static uint16 LLCCTRL_mg_u16q12CalibCurrOutGain;

/***********************************************
 * Voltage control loop
 **********************************************/
static MG_S_3P3Z_CTRL LLCCTRL_mg_sLoop;

/***********************************************
 * Duty cycle and dead time
 **********************************************/
static volatile uint16 LLCCTRL_mg_u16q16LlcDutyCycle;
static volatile uint16 LLCCTRL_mg_u161nsLlcDeadTime;
static volatile sint16 LLCCTRL_mg_s161nsLlcDeadTime1;
static volatile sint16 LLCCTRL_mg_s161nsSrOnDeadTime;
static volatile sint32 LLCCTRL_mg_s321nsSrOnDeadTime1;
static volatile sint32 LLCCTRL_mg_s321nsSrOnDeadTime2;
static volatile sint16 LLCCTRL_mg_s161nsSrOffDeadTime;
static volatile sint32 LLCCTRL_mg_s321nsSrOffDeadTime1;
static volatile sint32 LLCCTRL_mg_s321nsSrOffDeadTime2;

/***********************************************
 * Main output voltage
 **********************************************/
static sint16 LLCCTRL_mg_s1610mVMainVoltRef;
static sint16 LLCCTRL_mg_s1610mVMainVoltRefDroop;
static sint16 LLCCTRL_mg_s1610mVMainVoltAdjCurrLimit;
static uint32 LLCCTRL_mg_u32q810mVMainVoltRefSoftStart;
static sint16 LLCCTRL_mg_s16q810mVSoftStartFact;
static sint16 LLCCTRL_mg_s1610mVMainVoltAdjCurrShare;

/***********************************************
 * Current limit mode
 **********************************************/
#if MG_CURR_LIMIT_MODE
static uint16 LLCCTRL_mg_u1610mACurrLimit;
static uint16 LLCCTRL_mg_u1610mACurrLimitReg;
static uint16 LLCCTRL_mg_u1610mACurrLimitSs;
static volatile sint32 LLCCTRL_mg_s3210mVCurrLimitU0;
static volatile sint32 LLCCTRL_mg_s3210mVCurrLimitU1;
static volatile sint32 LLCCTRL_mg_s3210mACurrLimitE0;
static volatile sint32 LLCCTRL_mg_s3210mACurrLimitE0Tmp;
static volatile sint32 LLCCTRL_mg_s3210mACurrLimitE1;
#endif

/***********************************************
 * IIR ripple filter
 **********************************************/
#if MG_IIR_RIPPLE_FLT
static MG_S_IIR_FILT LLCCTRL_mg_IirFlt;
static volatile sint32 LLCCTRL_mg_s32q1510mVIirU0 = 0U;
static volatile sint32 LLCCTRL_mg_s32q1510mVIirU1 = 0U;
static volatile sint32 LLCCTRL_mg_s32q1510mVIirU2 = 0U;
static volatile sint32 LLCCTRL_mg_s3210mVIirE0 = 0U;
static volatile sint32 LLCCTRL_mg_s3210mVIirE1 = 0U;
static volatile sint32 LLCCTRL_mg_s3210mVIirE2 = 0U;
static volatile sint32 LLCCTRL_mg_s32q8IirGain = MG_S32Q8_IIR_FLT_GAIN;
#endif
static volatile sint16 LLCCTRL_mg_s1610mVIirFlt = 0U;

/***********************************************
 * Debugging
 **********************************************/
#define LLCCTRL_DEBUG   0
#if LLCCTRL_DEBUG
sint16 LLCCTRL_mg_s16debug_var1 = 0U;
sint16 LLCCTRL_mg_s16debug_var2 = 0U;
sint32 LLCCTRL_mg_s32debug_var3 = 0U;
sint32 LLCCTRL_mg_s32debug_var4 = 0U;
#endif

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vInit(void)
{
  /* Turn off PWM A output */
  LLCCTRL_scfg_vHrTimerAPwmOff();
  /* Turn off PWM C output */
  LLCCTRL_scfg_vHrTimerBPwmOff();
  /* Init control status */
  LLCCTRL_mg_uCtrlStatus.ALL = 0U;
  /* Set voltage refernce to zero */
  LLCCTRL_mg_s1610mVMainVoltRef = 0U;

  /* Init LLC control status */
  MG_B_LLC_SOFT_START = TRUE;
  MG_B_LLC_CURR_LIMIT_MODE = FALSE;
  MG_B_LLC_CT_OCP = FALSE;
  LLCCTRL_scfg_vHrTimerAClearDlyProtFlg();

  /* Get inital calibration data */
  LLCCTRL_Read_R_q12_CalibVoltOutGain_rte(&LLCCTRL_mg_u16q12CalibVoltOutGain);
  LLCCTRL_Read_R_q12_CalibCurrOutGain_rte(&LLCCTRL_mg_u16q12CalibCurrOutGain);

  /* Init base period */
  LLCCTRL_mg_sLoop.u321nsLlcPeriodMin = MG_U32_nS_LLC_PERIOD_MIN;
  LLCCTRL_mg_sLoop.u321nsLlcPeriod = LLCCTRL_mg_sLoop.u321nsLlcPeriodMin;
  /* Initialize the compensator */
  LLCCTRL_mg_sLoop.u321nsVoltU0 = LLCCTRL_mg_sLoop.u321nsLlcPeriod;
  LLCCTRL_mg_sLoop.u32q41nsVoltU0 = (LLCCTRL_mg_sLoop.u321nsLlcPeriod << 4);
  LLCCTRL_mg_sLoop.u32q41nsVoltU1 = LLCCTRL_mg_sLoop.u32q41nsVoltU0;
  LLCCTRL_mg_sLoop.u32q41nsVoltU2 = LLCCTRL_mg_sLoop.u32q41nsVoltU1;
  LLCCTRL_mg_sLoop.u32q41nsVoltU3 = LLCCTRL_mg_sLoop.u32q41nsVoltU2;
  LLCCTRL_mg_sLoop.s3210mVVoltE0 = 0U;
  LLCCTRL_mg_sLoop.s3210mVVoltE1 = 0U;
  LLCCTRL_mg_sLoop.s3210mVVoltE2 = 0U;
  LLCCTRL_mg_sLoop.s3210mVVoltE3 = 0U;
  LLCCTRL_mg_sLoop.sS1610mVMaxVoltErr = MG_S16_10mV_MAX_V_ERR;
#if MG_PWM_CTRL_MODE
  LLCCTRL_mg_sLoop.s3210mVPwmModeE1 = 0U;
#endif
  /* Set duty cycle to zero */
  LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MIN_DUTY_CYCLE;
  /* Set minimum dead times */
  LLCCTRL_mg_u161nsLlcDeadTime = MG_S16_nS_PWM_LLC_DT_MAX;
  LLCCTRL_mg_s161nsSrOnDeadTime = MG_S16_nS_PWM_SR_ON_DT_MAX;
  LLCCTRL_mg_s161nsSrOffDeadTime = MG_S16_nS_PWM_SR_OFF_DT_MAX;

  /*******************************************************************************
   * Set PWM outputs (LLC & SR)
   * Processing time: 2.2us
   *******************************************************************************/
  LLCCTRL_scfg_vHrTimerSetPwm(LLCCTRL_mg_sLoop.u321nsLlcPeriod, LLCCTRL_mg_u16q16LlcDutyCycle, LLCCTRL_mg_u161nsLlcDeadTime, LLCCTRL_mg_s161nsSrOnDeadTime, LLCCTRL_mg_s161nsSrOffDeadTime);

  /* Set CT over current protection reference */
  LLCCTRL_scfg_vSetCompRef(MG_U16_10mA_LLC_CURR_CT_OCP);
}

/** *****************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief           DMA1 Channel1 Interrupt service routine
 *                  Processing of LLC control loop
 * Repetition:      Base repetition: 100kHz (10.00uS);
 *                  Currently used: ~?.??uS (??%)
 *
 * ADC conversion time: - 4 ADC's = 0.531uS @ 64MHz OR 0.472uS @ 72MHz (4 channels with 2.5cycles)
 *                      - 6 ADC's = 0.796uS @ 64MHz OR 0.708uS @ 72MHz (6 channels with 2.5cycles)
 *
 * ADC sampling:  External output voltage; Internal output voltage; Output current;
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
 /*
  * NOTE: Put the ccram attribute directly in front of the function (DMA1_Channel1_IRQHandler)
  * Add in memory map dissambly file:
  *       RW_IRAM2 0x10000000 0x00001000
  *       {
  *         *.o (RESET_RAM, +First) ;in case of vector table relocated in CCRAM
  *         .ANY (ccram)
  *       }
  */
__attribute__((section ("ccram")))  /* Load ISR into CCRAM for max processing speed */
void LLCCTRL_vLlcCtrlIsr(void)
{
  /*******************************************************************************
   * Measurement processing
   * Processing time: 0.955us (incl. calibration)
   *******************************************************************************/
  /*******************************************************************************
   * External voltage measurement processing
   *******************************************************************************/
  /* Get external output voltage */
  LLCCTRL_mg_u1610mVVoltOutExtRaw = LLCCTRL_scfg_u16AdcSampleVoltOutExt();
  /* Calibrate measured external output voltage */
  LLCCTRL_mg_u1610mVVoltOutExt = (((sint32)LLCCTRL_mg_u1610mVVoltOutExtRaw * LLCCTRL_mg_u16q12CalibVoltOutGain) >> 12);

  /*******************************************************************************
   * Internal voltage measurement processing
   *******************************************************************************/
  /* Get internal output voltage */
  LLCCTRL_mg_u1610mVVoltOutIntRaw = LLCCTRL_scfg_u16AdcSampleVoltOutInt();
  /* Calibrate measured external output voltage */
  LLCCTRL_mg_u1610mVVoltOutInt = (((sint32)LLCCTRL_mg_u1610mVVoltOutIntRaw * LLCCTRL_mg_u16q12CalibVoltOutGain) >> 12);

  /*******************************************************************************
   * Merge external and internal voltage
   *******************************************************************************/
  /* Determine the combination filter weights */
  #if MG_VEXT_FBK_LOOP
  LLCCTRL_mg_u32q15_Kint_Vout = LIMIT(((sint32)LLCCTRL_mg_u1610mVVoltOutExt - LLCCTRL_mg_u1610mVVoltOutInt), (sint16)0U, MG_S16_10mV_MAX_VOUT_DIFF);
  LLCCTRL_mg_u32q15_Kint_Vout = LLCCTRL_mg_u32q15_Kint_Vout * MG_U16Q15_VOUT_TRANS_FACT;
  LLCCTRL_mg_u32q15_Kext_Vout = LIMIT((S32Q15(1.0F) - (sint32)LLCCTRL_mg_u32q15_Kint_Vout), (sint16)0U, S32Q15(1.0F));
  /* Calculate combination filter */
  LLCCTRL_mg_u1610mVVoltOut = ((LLCCTRL_mg_u32q15_Kext_Vout * LLCCTRL_mg_u1610mVVoltOutExt
                              + LLCCTRL_mg_u32q15_Kint_Vout * LLCCTRL_mg_u1610mVVoltOutInt) >> 15);
  #else
  LLCCTRL_mg_u1610mVVoltOut = LLCCTRL_mg_u1610mVVoltOutInt;
  #endif

  /*******************************************************************************
   * Current measurement processing
   *******************************************************************************/
  /* Get output current */
  LLCCTRL_mg_u1610mACurrOutRaw = LLCCTRL_scfg_u16AdcSampleCurrOut();
  #if MG_CALIBRATE_VREF_IOUT
    LLCCTRL_mg_u1610mACurrOutRaw = (((uint32)LLCCTRL_mg_u16q12VoltRefCaliFact * LLCCTRL_mg_u1610mACurrOutRaw) >> 12);
  #endif
  /* Use a digital filter for output current averaging */
  LLCCTRL_mg_u1610mACurrOutFlt = (((uint32)MG_U16Q15_K1_IOUT_FLT * LLCCTRL_mg_u1610mACurrOutFlt
                                 + (uint32)MG_U16Q15_K2_IOUT_FLT * LLCCTRL_mg_u1610mACurrOutRaw) >> 15);
  /* Calibrate measured output current */
  LLCCTRL_mg_u1610mACurrOut = (((sint32)LLCCTRL_mg_u1610mACurrOutFlt * LLCCTRL_mg_u16q12CalibCurrOutGain) >> 12);
  if(MG_U16_10mA_LLC_CURR_LIMIT_ERR < LLCCTRL_mg_u1610mACurrOutRaw)
  {
    LLCCTRL_mg_sLoop.sS1610mVMaxVoltErr = MG_S16_10mV_MAX_V_ERR_HC;
  }
  else
  {
    LLCCTRL_mg_sLoop.sS1610mVMaxVoltErr = MG_S16_10mV_MAX_V_ERR;
  }

  #if (DEBUG_SECTION_FIXED_FREQ_DRV_ON)
  Rte_Read_R_B_LLC_EN = TRUE;
  MG_B_LLC_SOFT_START = TRUE;
  #endif

  if (Rte_Read_R_B_LLC_EN)
  {
    #if (!DEBUG_SECTION_PWM_DRV_OFF)
    /* If LLC enabled and no CT OCP occured -> turn on LLC */
    if (!LLCCTRL_scfg_u8HrTimerAReadDlyProtFlg())
    {
      /* Turn on PWM A output */
      LLCCTRL_scfg_vHrTimerAPwmOn();
      #if (!DEBUG_SECTION_SR_DRV_OFF)
      /* Turn on PWM C output */
      LLCCTRL_scfg_vHrTimerBPwmOn();
      #else
      /* Turn off PWM C output */
      LLCCTRL_scfg_vHrTimerBPwmOff();
      #endif
    }
    #else
    /* Turn off PWM A output */
    LLCCTRL_scfg_vHrTimerAPwmOff();
    /* Turn off PWM C output */
    LLCCTRL_scfg_vHrTimerBPwmOff();
    #endif

    /*******************************************************************************
     * Droop control
     * Processing time: 0.15us
     * VoltRefTemp = VoltZeroLoad - (DroopFactor * Iout) + ActiveCurrentShareDroop
     * DroopFactor = (VoltZeroLoad - VoltMaxLoad) / (IoutMax)
     * DroopFactorOVL = (VoltMaxLoad - VoltOverLoad) / (IoutOverLoad - IoutMax)
     *******************************************************************************/
    /* Calculate droop */
    LLCCTRL_mg_s1610mVMainVoltRefDroop = (MG_U16_10mV_LLC_VOLT_OUT_ZERO_LOAD - ((MG_U32Q15_DROOP_FACT * LLCCTRL_mg_u1610mACurrOut) >> 15));
    #if MG_OVER_LAOD_DROOP
    /* Calculate over load droop */
    LLCCTRL_mg_s1610mVMainVoltRefDroop = (LLCCTRL_mg_s1610mVMainVoltRefDroop - ((MG_U32Q15_DROOP_FACT_OVL * SAT_L(((sint32)LLCCTRL_mg_u1610mACurrOut - MG_U16_10mA_LLC_CURR_OUT_MAX_LOAD), 0)) >> 15));
    #endif
    /* Limit the temporary reference voltage */
    LLCCTRL_mg_s1610mVMainVoltRefDroop = SAT_H(LLCCTRL_mg_s1610mVMainVoltRefDroop, MG_U16_10mV_LLC_VOLT_OUT_ZERO_LOAD);

    /* Get data from RTE */
    LLCCTRL_Read_R_10mV_MainVoltAdjCurrShare_rte(&LLCCTRL_mg_s1610mVMainVoltAdjCurrShare);
    /* Add active current share droop */
    LLCCTRL_mg_s1610mVMainVoltRefDroop = LLCCTRL_mg_s1610mVMainVoltRefDroop + LLCCTRL_mg_s1610mVMainVoltAdjCurrShare;

    /*******************************************************************************
     * Loop coefficients and voltage reference determination
     * Processing time: 0.8us
     *******************************************************************************/
    /* Soft start mode */
    if (MG_B_LLC_SOFT_START)
    {
      #if MG_CURR_LIMIT_MODE
      /* Apply soft start current limit */
      LLCCTRL_mg_u1610mACurrLimit = LLCCTRL_mg_u1610mACurrLimitSs;
      #endif

      /* Apply soft start mode parameter set */
      LLCCTRL_mg_sLoop.s32q24VoltB0 = MG_S32Q24_VOLT_SS_B0;
      LLCCTRL_mg_sLoop.s32q24VoltB1 = MG_S32Q24_VOLT_SS_B1;
      LLCCTRL_mg_sLoop.s32q24VoltB2 = MG_S32Q24_VOLT_SS_B2;
      LLCCTRL_mg_sLoop.s32q24VoltB3 = MG_S32Q24_VOLT_SS_B3;
      LLCCTRL_mg_sLoop.s32q24VoltA1 = MG_S32Q24_VOLT_SS_A1;
      LLCCTRL_mg_sLoop.s32q24VoltA2 = MG_S32Q24_VOLT_SS_A2;
      LLCCTRL_mg_sLoop.s32q24VoltA3 = MG_S32Q24_VOLT_SS_A3;

      /* Check if soft start reference > droop reference */
      if ((LLCCTRL_mg_u32q810mVMainVoltRefSoftStart >> 8) >= LLCCTRL_mg_s1610mVMainVoltRefDroop)
      {
        /* Disable soft start */
        MG_B_LLC_SOFT_START = FALSE;
        /* Set voltage reference */
        LLCCTRL_mg_s1610mVMainVoltRef = LLCCTRL_mg_s1610mVMainVoltRefDroop;
      }
      else
      {
        /* Calculate the ramp slope according to the load */
        LLCCTRL_mg_s16q810mVSoftStartFact = ((sint16)MG_U16Q8_10mV_SS_ZERO_LOAD_FACT - ((MG_U32Q23_10mV_SS_LOAD_FACT * LLCCTRL_mg_u1610mACurrOut) >> 15));
        LLCCTRL_mg_s16q810mVSoftStartFact = SAT_L(LLCCTRL_mg_s16q810mVSoftStartFact, MG_U16Q8_10mV_SS_MAX_LOAD_FACT);
        /* Linear ramp-up voltage refernce */
        LLCCTRL_mg_u32q810mVMainVoltRefSoftStart = LLCCTRL_mg_u32q810mVMainVoltRefSoftStart + LLCCTRL_mg_s16q810mVSoftStartFact;
        /* Set voltage reference */
        LLCCTRL_mg_s1610mVMainVoltRef = LLCCTRL_mg_u32q810mVMainVoltRefSoftStart >> 8;
      }
    }
    /* Regular operation mode */
    else
    {
      /* Apply regular operation 0 parameter set */
      LLCCTRL_mg_sLoop.s32q24VoltB0 = MG_S32Q24_VOLT_RO_0_B0;
      LLCCTRL_mg_sLoop.s32q24VoltB1 = MG_S32Q24_VOLT_RO_0_B1;
      LLCCTRL_mg_sLoop.s32q24VoltB2 = MG_S32Q24_VOLT_RO_0_B2;
      LLCCTRL_mg_sLoop.s32q24VoltB3 = MG_S32Q24_VOLT_RO_0_B3;
      LLCCTRL_mg_sLoop.s32q24VoltA1 = MG_S32Q24_VOLT_RO_0_A1;
      LLCCTRL_mg_sLoop.s32q24VoltA2 = MG_S32Q24_VOLT_RO_0_A2;
      LLCCTRL_mg_sLoop.s32q24VoltA3 = MG_S32Q24_VOLT_RO_0_A3;

      #if MG_CURR_LIMIT_MODE
      /* Apply regular operation current limit */
      LLCCTRL_mg_u1610mACurrLimit = LLCCTRL_mg_u1610mACurrLimitReg;
      #endif
      /* Set voltage reference */
      LLCCTRL_mg_s1610mVMainVoltRef = LLCCTRL_mg_s1610mVMainVoltRefDroop;

      #if DEBUG_SECTION_OVP_TEST
      /* In case of OVP test, choose over voltage reference */
      if (Rte_Read_R_B_LLC_OVP_TEST)
      {
        LLCCTRL_mg_s1610mVMainVoltRef = MG_U16_10mV_LLC_VOUT_OVP_TEST_VREF;
      }
      #endif
    }

    #if MG_CURR_LIMIT_MODE
    /*******************************************************************************
     * Constant current limit mode
     * Processing time: 0.74us, may
     *******************************************************************************/
    /* Get current limitation error */
    LLCCTRL_mg_s3210mACurrLimitE0 = (sint32)LLCCTRL_mg_u1610mACurrLimit - LLCCTRL_mg_u1610mACurrOut;

		#if MG_POSITONAL_INCREMENTAL_PI  /* Positional PI */
    /* Parallel PI controller */
    LLCCTRL_mg_s3210mVCurrLimitU0 = ((MG_S32Q15_CURR_LIMIT_KP * LLCCTRL_mg_s3210mACurrLimitE0) >> 15) + LLCCTRL_mg_s3210mACurrLimitE1;
    /* New integral part calculation */
    LLCCTRL_mg_s3210mACurrLimitE0Tmp = ((MG_S32Q15_CURR_LIMIT_KI * LLCCTRL_mg_s3210mACurrLimitE0) >> 15);

    /* Anti wind up */
    /* If PI output higher than upper limit */
    if (MG_S16_10mV_CC_VOUT_ADJ_MAX < LLCCTRL_mg_s3210mVCurrLimitU0)
    {
      /* Anti wind-up with integral clamping */
      LLCCTRL_mg_s3210mACurrLimitE0Tmp = 0U;
      /* Then set PI output to upper limit */
      LLCCTRL_mg_s3210mVCurrLimitU0 = MG_S16_10mV_CC_VOUT_ADJ_MAX;
    }
    /* If PI output below lower limit */
    if ((-(sint32)LLCCTRL_mg_s1610mVMainVoltRef) > LLCCTRL_mg_s3210mVCurrLimitU0)
    {
      /* Anti wind-up with integral clamping */
      LLCCTRL_mg_s3210mACurrLimitE0Tmp = 0U;
      /* Then set PI output to lower limit */
      LLCCTRL_mg_s3210mVCurrLimitU0 = (-(sint32)LLCCTRL_mg_s1610mVMainVoltRef);
    }

    /* Err summation for I-part and limitation */
    LLCCTRL_mg_s3210mACurrLimitE1 = LLCCTRL_mg_s3210mACurrLimitE1 + LLCCTRL_mg_s3210mACurrLimitE0Tmp;

    /* Get current mode voltage reference */
    LLCCTRL_mg_s1610mVMainVoltAdjCurrLimit = LLCCTRL_mg_s3210mVCurrLimitU0;
    #else  /* Incremental PI */
    /* Parallel PI controller */
    LLCCTRL_mg_s3210mVCurrLimitU0 = LLCCTRL_mg_s3210mVCurrLimitU1
                                    + (((MG_S32Q15_CURR_LIMIT_B0 * LLCCTRL_mg_s3210mACurrLimitE0)
                                    +   (MG_S32Q15_CURR_LIMIT_B1 * LLCCTRL_mg_s3210mACurrLimitE1)) >> 15);
    /* Anti wind up */
    LLCCTRL_mg_s3210mVCurrLimitU0 = LIMIT(LLCCTRL_mg_s3210mVCurrLimitU0, (-(sint32)LLCCTRL_mg_s1610mVMainVoltRef), MG_S16_10mV_CC_VOUT_ADJ_MAX);
    /* Store variables */
    LLCCTRL_mg_s3210mVCurrLimitU1 = LLCCTRL_mg_s3210mVCurrLimitU0;
    LLCCTRL_mg_s3210mACurrLimitE1 = LLCCTRL_mg_s3210mACurrLimitE0;
    /* Get current mode voltage reference */
    LLCCTRL_mg_s1610mVMainVoltAdjCurrLimit = LLCCTRL_mg_s3210mVCurrLimitU0;
    #endif
    /* Write status to RTE */
    #if 1
    if (MG_S16_10mV_CC_VOUT_ADJ_MAX > LLCCTRL_mg_s1610mVMainVoltAdjCurrLimit)
    {
      /* Constatn current mode active */
      MG_B_LLC_CURR_LIMIT_MODE = TRUE;
    }
    else
    {
      /* Constant current mode inactive */
      MG_B_LLC_CURR_LIMIT_MODE = FALSE;
    }
    #else
    MG_B_LLC_CURR_LIMIT_MODE = ((MG_S16_10mV_CC_VOUT_ADJ_MAX) > (LLCCTRL_mg_s1610mVMainVoltAdjCurrLimit) ? (TRUE) : (FALSE));
    #endif

    #else
    /* Current limit mode adjustment always zero */
    LLCCTRL_mg_s1610mVMainVoltAdjCurrLimit = 0U;
    #endif

    /*******************************************************************************
     * Main output voltage error determination
     * Processing time: 0.23us
     *******************************************************************************/
    LLCCTRL_mg_s1610mVMainVoltRef = SAT_L(LLCCTRL_mg_s1610mVMainVoltRef + LLCCTRL_mg_s1610mVMainVoltAdjCurrLimit, (sint16)0);
    /* Calculate voltage control error */
    LLCCTRL_mg_sLoop.s3210mVVoltErr = (sint32)LLCCTRL_mg_s1610mVMainVoltRef - LLCCTRL_mg_u1610mVVoltOut;
    /* Limit the error signal */
    LLCCTRL_mg_sLoop.s3210mVVoltE0 = LIMIT((LLCCTRL_mg_sLoop.s3210mVVoltErr + LLCCTRL_mg_s1610mVIirFlt), MG_S16_10mV_MIN_V_ERR, LLCCTRL_mg_sLoop.sS1610mVMaxVoltErr);

    /*******************************************************************************
     * Main output voltage loop
     * Processing time: 0.76us
     *******************************************************************************/
    /* Voltage loop calculation */
    /* (((Q24 * Q0) + ((Q24 * Q0))) >> 24) -> Q0 */
    LLCCTRL_mg_sLoop.u32q41nsVoltU0 = ( ((((sint64)LLCCTRL_mg_sLoop.s32q24VoltB0 * LLCCTRL_mg_sLoop.s3210mVVoltE0)
                               + ((sint64)LLCCTRL_mg_sLoop.s32q24VoltB1 * LLCCTRL_mg_sLoop.s3210mVVoltE1)
                               + ((sint64)LLCCTRL_mg_sLoop.s32q24VoltB2 * LLCCTRL_mg_sLoop.s3210mVVoltE2)
                               + ((sint64)LLCCTRL_mg_sLoop.s32q24VoltB3 * LLCCTRL_mg_sLoop.s3210mVVoltE3)) >> 20)
                               + ((((sint64)LLCCTRL_mg_sLoop.s32q24VoltA1 * LLCCTRL_mg_sLoop.u32q41nsVoltU1)
                               + ((sint64)LLCCTRL_mg_sLoop.s32q24VoltA2 * LLCCTRL_mg_sLoop.u32q41nsVoltU2)
                               + ((sint64)LLCCTRL_mg_sLoop.s32q24VoltA3 * LLCCTRL_mg_sLoop.u32q41nsVoltU3)) >> 24) );

    /* Limit voltage loop output */
    LLCCTRL_mg_sLoop.u32q41nsVoltU0 = LIMIT((LLCCTRL_mg_sLoop.u32q41nsVoltU0), (LLCCTRL_mg_sLoop.u321nsLlcPeriodMin << 4), MG_U32Q4_nS_LLC_PERIOD_MAX);
    LLCCTRL_mg_sLoop.u321nsVoltU0 = (LLCCTRL_mg_sLoop.u32q41nsVoltU0 >> 4);

    /*******************************************************************************
     * Set period, deadtime and duty cycle
     * Processing time: 0.12us
     *******************************************************************************/
    /* Check if over voltage */
    if ((Rte_Read_R_B_LLC_OVP)) //(MG_U16_10mV_LLC_VOLT_OUT_OVP < LLCCTRL_mg_u1610mVVoltOut)
    {
      /* Set frequency to max and turn off PWM */
      /* Set control variables */
      LLCCTRL_mg_sLoop.u321nsVoltU0   = MG_U32_nS_LLC_PERIOD_CT_PEAK_OVP;
      LLCCTRL_mg_sLoop.u32q41nsVoltU0 = MG_U32Q4_nS_LLC_PERIOD_CT_PEAK_OVP;
      LLCCTRL_mg_sLoop.u32q41nsVoltU1 = LLCCTRL_mg_sLoop.u32q41nsVoltU0;
      LLCCTRL_mg_sLoop.u32q41nsVoltU2 = LLCCTRL_mg_sLoop.u32q41nsVoltU1;
      LLCCTRL_mg_sLoop.u32q41nsVoltU3 = LLCCTRL_mg_sLoop.u32q41nsVoltU2;
      LLCCTRL_mg_sLoop.s3210mVVoltE0 = 0U;
      LLCCTRL_mg_sLoop.s3210mVVoltE1 = 0U;
      LLCCTRL_mg_sLoop.s3210mVVoltE2 = 0U;
      LLCCTRL_mg_sLoop.s3210mVVoltE3 = 0U;

      /* Set new period value */
      LLCCTRL_mg_sLoop.u321nsLlcPeriod = LLCCTRL_mg_sLoop.u321nsVoltU0;
      /* Set zero duty cycle */
      LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MIN_DUTY_CYCLE;
    }
    /* Check if main transformer over current occured (delayed protection) */
    else if (LLCCTRL_scfg_u8HrTimerAReadDlyProtFlg())
    {
      /* Set OCP CT flag */
      MG_B_LLC_CT_OCP = TRUE;
      /* Set frequency to max and turn off SR */
      /* Set control variables */
      LLCCTRL_mg_sLoop.u321nsVoltU0 = MG_U32_nS_LLC_PERIOD_CT_PEAK_OVP;
      LLCCTRL_mg_sLoop.u32q41nsVoltU0 = MG_U32Q4_nS_LLC_PERIOD_CT_PEAK_OVP;
      LLCCTRL_mg_sLoop.u32q41nsVoltU1 = LLCCTRL_mg_sLoop.u32q41nsVoltU0;
      LLCCTRL_mg_sLoop.u32q41nsVoltU2 = LLCCTRL_mg_sLoop.u32q41nsVoltU1;
      LLCCTRL_mg_sLoop.u32q41nsVoltU3 = LLCCTRL_mg_sLoop.u32q41nsVoltU2;
      LLCCTRL_mg_sLoop.s3210mVVoltE0 = 0U;
      LLCCTRL_mg_sLoop.s3210mVVoltE1 = 0U;
      LLCCTRL_mg_sLoop.s3210mVVoltE2 = 0U;
      LLCCTRL_mg_sLoop.s3210mVVoltE3 = 0U;

      /* Hold soft start reference on actual output voltage */
      LLCCTRL_mg_u32q810mVMainVoltRefSoftStart = ((uint32)LLCCTRL_mg_u1610mVVoltOut << 8);

      /* Set new period value */
      LLCCTRL_mg_sLoop.u321nsLlcPeriod = LLCCTRL_mg_sLoop.u321nsVoltU0;
      /* Set max duty cycle */
      LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MAX_DUTY_CYCLE;
    }
    /* Else regular operation */
    else
    {
      #if MG_PWM_CTRL_MODE
      /*******************************************************************************
       * PWM control mode
       * Processing time: 0.98us
       *******************************************************************************/
      /* If low load condition use PWM control */
      if ((LLCCTRL_mg_sLoop.u321nsLlcPeriodMin >= LLCCTRL_mg_sLoop.u321nsVoltU0) || MG_B_LLC_PWM_MODE)
      {
        /* Get PWM control error */
        LLCCTRL_mg_sLoop.s3210mVPwmModeE0 = LLCCTRL_mg_sLoop.s3210mVVoltErr;
        /* Limit the PWM mode voltage error */
        LLCCTRL_mg_sLoop.s3210mVPwmModeE0 = LIMIT(LLCCTRL_mg_sLoop.s3210mVPwmModeE0, MG_S16_10mV_MIN_PWM_ERR, MG_S16_10mV_MAX_PWM_ERR);
        #if MG_POSITONAL_INCREMENTAL_PI  /* Positional PI */
        /* Parallel PI controller */
        LLCCTRL_mg_sLoop.s32q16PwmModeU0 = ((MG_S32Q8_PWM_CTRL_KP * LLCCTRL_mg_sLoop.s3210mVPwmModeE0) >> 8) + LLCCTRL_mg_sLoop.s3210mVPwmModeE1;
        /* New integral part calculation */
        LLCCTRL_mg_sLoop.s3210mVPwmModeE0Tmp = ((MG_S32Q8_PWM_CTRL_KI * LLCCTRL_mg_sLoop.s3210mVPwmModeE0) >> 8);

        /* Anti wind up */
        /* If PI output higher than upper limit */
        if (MG_U16Q16_MAX_DUTY_CYCLE < LLCCTRL_mg_sLoop.s32q16PwmModeU0)
        {
          /* Anti wind-up with integral adjustment (back tracking) */
          LLCCTRL_mg_sLoop.s3210mVPwmModeE0Tmp = ((sint32)MG_U16Q16_MAX_DUTY_CYCLE - LLCCTRL_mg_sLoop.s32q16PwmModeU0);
          /* then set PI output to upper limit */
          LLCCTRL_mg_sLoop.s32q16PwmModeU0 = MG_U16Q16_MAX_DUTY_CYCLE;
        }
        /* If PI output below lower limit */
        if (MG_U16Q16_MIN_DUTY_CYCLE > LLCCTRL_mg_sLoop.s32q16PwmModeU0)
        {
          /* Anti wind-up with integral adjustment (back tracking) */
          LLCCTRL_mg_sLoop.s3210mVPwmModeE0Tmp = ((sint32)MG_U16Q16_MIN_DUTY_CYCLE - LLCCTRL_mg_sLoop.s32q16PwmModeU0);
          /* then set PI output to lower limit */
          LLCCTRL_mg_sLoop.s32q16PwmModeU0 = MG_U16Q16_MIN_DUTY_CYCLE;
        }

        /* Err summation for I-part and limitation */
        LLCCTRL_mg_sLoop.s3210mVPwmModeE1 = LLCCTRL_mg_sLoop.s3210mVPwmModeE1 + LLCCTRL_mg_sLoop.s3210mVPwmModeE0Tmp;
        #else  /* Incremental PI */
        /* PI controller */
        LLCCTRL_mg_sLoop.s32q16PwmModeU0 = LLCCTRL_mg_sLoop.s32q16PwmModeU0
                                           + (((MG_S32Q8_PWM_CTRL_B0 * LLCCTRL_mg_sLoop.s3210mVPwmModeE0)
                                           +   (MG_S32Q8_PWM_CTRL_B1 * LLCCTRL_mg_sLoop.s3210mVPwmModeE1)) >> 8);
        /* If PI output limit */
        LLCCTRL_mg_sLoop.s32q16PwmModeU0 = LIMIT(LLCCTRL_mg_sLoop.s32q16PwmModeU0, MG_U16Q16_MIN_DUTY_CYCLE, MG_U16Q16_MAX_DUTY_CYCLE);
        /* Store variables */
        LLCCTRL_mg_sLoop.s32q16PwmModeU1 = LLCCTRL_mg_sLoop.s32q16PwmModeU0;
        LLCCTRL_mg_sLoop.s3210mVPwmModeE1 = LLCCTRL_mg_sLoop.s3210mVPwmModeE0;
        #endif
        /* If duty cycle is 50% go to frequency control mode */
        if (MG_U16Q16_MAX_DUTY_CYCLE <= LLCCTRL_mg_sLoop.s32q16PwmModeU0)
        {
          /* Reset PWM mode flag and variables */
          MG_B_LLC_PWM_MODE = FALSE;
          LLCCTRL_mg_sLoop.s32q16PwmModeU0 = MG_U16Q16_MAX_DUTY_CYCLE;
        }
        else
        {
          /* Set PWM mode flag */
          MG_B_LLC_PWM_MODE = TRUE;
          /* Set voltage loop variables accordingly to PWM mode */
          LLCCTRL_mg_sLoop.u321nsVoltU0 = LLCCTRL_mg_sLoop.u321nsLlcPeriodMin;
          LLCCTRL_mg_sLoop.u32q41nsVoltU0 = (LLCCTRL_mg_sLoop.u321nsLlcPeriodMin << 4);
          LLCCTRL_mg_sLoop.u32q41nsVoltU1 = LLCCTRL_mg_sLoop.u32q41nsVoltU0;
          LLCCTRL_mg_sLoop.u32q41nsVoltU2 = LLCCTRL_mg_sLoop.u32q41nsVoltU1;
          LLCCTRL_mg_sLoop.u32q41nsVoltU3 = LLCCTRL_mg_sLoop.u32q41nsVoltU2;
          LLCCTRL_mg_sLoop.s3210mVVoltE0 = 0U;
          LLCCTRL_mg_sLoop.s3210mVVoltE1 = 0U;
          LLCCTRL_mg_sLoop.s3210mVVoltE2 = 0U;
          LLCCTRL_mg_sLoop.s3210mVVoltE3 = 0U;
          /* Set the LLC duty cycle to controller output */
          LLCCTRL_mg_u16q16LlcDutyCycle = (uint16)LLCCTRL_mg_sLoop.s32q16PwmModeU0;
        }
      }

      /* Choose duty cycle accordingly to mode */
      if (FALSE == MG_B_LLC_PWM_MODE)
      {
        /* Set the LLC duty cycle */
        LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MAX_DUTY_CYCLE;
      }

      /* Set new period value */
      LLCCTRL_mg_sLoop.u321nsLlcPeriod = LLCCTRL_mg_sLoop.u321nsVoltU0;

      /* Calculate new minimum period for next cycle */
      LLCCTRL_mg_sLoop.u321nsLlcPeriodMin = MG_U32_nS_LLC_PERIOD_PWM_SS + ((MG_U32Q10_nS_PWM_FREQ_FACT * LLCCTRL_mg_s1610mVMainVoltRef) >> 10);
      LLCCTRL_mg_sLoop.u321nsLlcPeriodMin = LIMIT(LLCCTRL_mg_sLoop.u321nsLlcPeriodMin, MG_U32_nS_LLC_PERIOD_PWM_SS, MG_U32_nS_LLC_PERIOD_PWM);
      #else

      /*******************************************************************************
       * Frequency burst mode
       * Processing time: 0.50us
       *******************************************************************************/
      if (MG_B_LLC_SOFT_START)
      {
        /* Burst mode turn on */
        if (MG_U32_nS_LLC_PERIOD_FBURST_IN > LLCCTRL_mg_sLoop.u321nsVoltU0)
        {
          /* Set burst mode enabled flag */
          MG_B_LLC_BM = TRUE;
        }
        /* Burst mode turn off */
        else
        {
          /* Set burst mode disabled flag */
          MG_B_LLC_BM = FALSE;
        }

        /* If burst mode flag is set -> burst mode */
        if (MG_B_LLC_BM)
        {
          /* PWM on */
          if (MG_U32_nS_LLC_PERIOD_FBURST < LLCCTRL_mg_sLoop.u321nsVoltU0)
          {
            /* Set max duty cycle */
            LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MAX_DUTY_CYCLE;
          }
          /* PWM off */
          else
          {
            /* Set zero duty cycle */
            LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MIN_DUTY_CYCLE;
          }
        }
        /* Else normal condition */
        else
        {
          /* Set max duty cycle */
          LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MAX_DUTY_CYCLE;
        }
      }
      else
      {
        /*******************************************************************************
         * Voltage burst mode
         * Processing time: 0.80us
         *******************************************************************************/
        /* Burst mode turn on */
        if (((MG_U32_nS_LLC_PERIOD_BURST_IN > LLCCTRL_mg_sLoop.u321nsVoltU0) && (MG_U16_10mV_CURR_BM_ON > LLCCTRL_mg_u1610mACurrOut)))
        {
          /* Set burst mode enabled flag */
          MG_B_LLC_BM = TRUE;
        }
        /* Burst mode turn off */
        else if ((MG_U16_10mV_CURR_BM_OFF < LLCCTRL_mg_u1610mACurrOut) || (MG_B_LLC_BM_TIMEOUT))
        {
          /* Set burst mode disabled flag */
          MG_B_LLC_BM = FALSE;
        }

        /* Adjust the burst mode turn on point */
        if (MG_S16_10mV_VOLT_BM_ERR_OFFSET > LLCCTRL_mg_sLoop.s3210mVVoltErr)
        {
          /* Increase error turn on point -> output voltage drops */
          LLCCTRL_mg_sLoop.s1610mVBmAdj++;
          LLCCTRL_mg_sLoop.s1610mVBmAdj = SAT_H(LLCCTRL_mg_sLoop.s1610mVBmAdj, MG_S16_10mV_VOLT_BM_ADJ_MIN);
        }
        else
        {
          /* Reduce error turn on point -> output voltage increase */
          LLCCTRL_mg_sLoop.s1610mVBmAdj--;
          LLCCTRL_mg_sLoop.s1610mVBmAdj = SAT_L(LLCCTRL_mg_sLoop.s1610mVBmAdj, MG_S16_10mV_VOLT_BM_ADJ_MAX);
        }

        /* If burst mode flag is set -> burst mode */
        if (MG_B_LLC_BM)
        {
          /* PWM on */
          if (LLCCTRL_mg_sLoop.s1610mVBmAdj < LLCCTRL_mg_sLoop.s3210mVVoltErr)
          {
            /* Set max duty cycle */
            LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MAX_DUTY_CYCLE;

            /* Increase burst mode time out counter depending on error (large error cause quick time out) */
            if ((MG_S16_10mV_BM_TIMEOUT_VOLT_ERR_3 + LLCCTRL_mg_sLoop.s1610mVBmAdj) < LLCCTRL_mg_sLoop.s3210mVVoltErr)
            {
              LLCCTRL_mg_sLoop.s16BmCtr = LLCCTRL_mg_sLoop.s16BmCtr + MG_U16_BM_TIMEOUT_SET_3;
            }
            /* Increase burst mode time out counter depending on error */
            else if ((MG_S16_10mV_BM_TIMEOUT_VOLT_ERR_2 + LLCCTRL_mg_sLoop.s1610mVBmAdj) < LLCCTRL_mg_sLoop.s3210mVVoltErr)
            {
              LLCCTRL_mg_sLoop.s16BmCtr = LLCCTRL_mg_sLoop.s16BmCtr + MG_U16_BM_TIMEOUT_SET_2;
            }
            /* Increase burst mode time out counter depending on error */
            else if ((MG_S16_10mV_BM_TIMEOUT_VOLT_ERR_1 + LLCCTRL_mg_sLoop.s1610mVBmAdj) < LLCCTRL_mg_sLoop.s3210mVVoltErr)
            {
              LLCCTRL_mg_sLoop.s16BmCtr = LLCCTRL_mg_sLoop.s16BmCtr + MG_U16_BM_TIMEOUT_SET_1;
            }
          }
          /* PWM off */
          else
          {
            /* Set zero duty cycle */
            LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MIN_DUTY_CYCLE;

            /* Decrease burst mode time out counter */
            LLCCTRL_mg_sLoop.s16BmCtr = LLCCTRL_mg_sLoop.s16BmCtr - MG_U16_BM_TIMEOUT_RESET;
            LLCCTRL_mg_sLoop.s16BmCtr = SAT_L(LLCCTRL_mg_sLoop.s16BmCtr, (sint16)0);
          }

          /* Judge if burst mode time out has occured */
          if (MG_U16_BM_TIMEOUT_VAL < LLCCTRL_mg_sLoop.s16BmCtr)
          {
            /* Set burst mode time out flag and reset counter */
            MG_B_LLC_BM_TIMEOUT = TRUE;
            LLCCTRL_mg_sLoop.s16BmCtr = 0U;
          }
          else
          {
            /* Reset time out flag */
            MG_B_LLC_BM_TIMEOUT = FALSE;
          }

          /* Set burst mode variables */
          LLCCTRL_mg_sLoop.u321nsVoltU0 = MG_U32_nS_LLC_PERIOD_BURST;
          LLCCTRL_mg_sLoop.u32q41nsVoltU0 = (MG_U32_nS_LLC_PERIOD_BURST << 4);
          LLCCTRL_mg_sLoop.u32q41nsVoltU1 = LLCCTRL_mg_sLoop.u32q41nsVoltU0;
          LLCCTRL_mg_sLoop.u32q41nsVoltU2 = LLCCTRL_mg_sLoop.u32q41nsVoltU1;
          LLCCTRL_mg_sLoop.u32q41nsVoltU3 = LLCCTRL_mg_sLoop.u32q41nsVoltU2;
          LLCCTRL_mg_sLoop.s3210mVVoltE0 = 0U;
          LLCCTRL_mg_sLoop.s3210mVVoltE1 = 0U;
          LLCCTRL_mg_sLoop.s3210mVVoltE2 = 0U;
          LLCCTRL_mg_sLoop.s3210mVVoltE3 = 0U;
        }
        /* Else normal condition */
        else
        {
          /* Set max duty cycle */
          LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MAX_DUTY_CYCLE;
        }
      }

      /* Set new period value */
      LLCCTRL_mg_sLoop.u321nsLlcPeriod = LLCCTRL_mg_sLoop.u321nsVoltU0;
      #endif
    }

    /* Store control loop variables */
    LLCCTRL_mg_sLoop.u32q41nsVoltU3 = LLCCTRL_mg_sLoop.u32q41nsVoltU2;
    LLCCTRL_mg_sLoop.u32q41nsVoltU2 = LLCCTRL_mg_sLoop.u32q41nsVoltU1;
    LLCCTRL_mg_sLoop.u32q41nsVoltU1 = LLCCTRL_mg_sLoop.u32q41nsVoltU0;
    LLCCTRL_mg_sLoop.s3210mVVoltE3 = LLCCTRL_mg_sLoop.s3210mVVoltE2;
    LLCCTRL_mg_sLoop.s3210mVVoltE2 = LLCCTRL_mg_sLoop.s3210mVVoltE1;
    LLCCTRL_mg_sLoop.s3210mVVoltE1 = LLCCTRL_mg_sLoop.s3210mVVoltE0;

    #if DEBUG_SECTION_FIXED_FREQ_MODE
    LLCCTRL_mg_u321nsLlcPeriod = DEBUG_SECTION_FIXED_PERIOD;
    LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MAX_DUTY_CYCLE;
    #endif
  }
  else
  /*******************************************************************************
   * LLC off mode
   * Processing time: 0.44us
   *******************************************************************************/
  {
    /* Turn off PWM A output */
    LLCCTRL_scfg_vHrTimerAPwmOff();
    /* Turn off PWM C output */
    LLCCTRL_scfg_vHrTimerBPwmOff();

    /* Reset variables */
    LLCCTRL_mg_s1610mVMainVoltRef = 0U;
    LLCCTRL_mg_u32q810mVMainVoltRefSoftStart = ((uint32)LLCCTRL_mg_u1610mVVoltOut << 8);
    LLCCTRL_mg_s1610mVMainVoltAdjCurrLimit = 0U;
    LLCCTRL_mg_u1610mACurrOut = 0U;

    /* Set/reset flags */
    MG_B_LLC_CURR_LIMIT_MODE = FALSE;
    MG_B_LLC_SOFT_START = TRUE;
    MG_B_LLC_CT_OCP = FALSE;
    LLCCTRL_scfg_vHrTimerAClearDlyProtFlg();
    /* Reset CT OCP on RTE */
    MG_B_LLC_CT_OCP_TO_MON = FALSE;
    #if (!MG_PWM_CTRL_MODE)
    MG_B_LLC_BM = TRUE;
    #else
    MG_B_LLC_PWM_MODE = TRUE;
    #endif

    /* Reset control variables */
    LLCCTRL_mg_sLoop.u321nsVoltU0 = LLCCTRL_mg_sLoop.u321nsLlcPeriodMin;
    LLCCTRL_mg_sLoop.u32q41nsVoltU0 = (LLCCTRL_mg_sLoop.u321nsLlcPeriodMin << 4);
    LLCCTRL_mg_sLoop.u32q41nsVoltU1 = LLCCTRL_mg_sLoop.u32q41nsVoltU0;
    LLCCTRL_mg_sLoop.u32q41nsVoltU2 = LLCCTRL_mg_sLoop.u32q41nsVoltU1;
    LLCCTRL_mg_sLoop.u32q41nsVoltU3 = LLCCTRL_mg_sLoop.u32q41nsVoltU2;
    LLCCTRL_mg_sLoop.s3210mVVoltE0 = 0U;
    LLCCTRL_mg_sLoop.s3210mVVoltE1 = 0U;
    LLCCTRL_mg_sLoop.s3210mVVoltE2 = 0U;
    LLCCTRL_mg_sLoop.s3210mVVoltE3 = 0U;
    #if MG_CURR_LIMIT_MODE
    LLCCTRL_mg_s3210mVCurrLimitU0 = 0U;
    LLCCTRL_mg_s3210mACurrLimitE1 = 0U;
    #endif
    #if MG_PWM_CTRL_MODE
    LLCCTRL_mg_sLoop.s3210mVPwmModeE1 = 0U;
    LLCCTRL_mg_sLoop.s32q16PwmModeU0 = MG_U16Q16_MIN_DUTY_CYCLE;
    #endif

    /* Reset PWM */
    LLCCTRL_mg_sLoop.u321nsLlcPeriod = LLCCTRL_mg_sLoop.u321nsLlcPeriodMin;
    LLCCTRL_mg_u16q16LlcDutyCycle = MG_U16Q16_MIN_DUTY_CYCLE;
    LLCCTRL_mg_u161nsLlcDeadTime = MG_S16_nS_PWM_LLC_DT_MAX;
    LLCCTRL_mg_s161nsSrOnDeadTime = MG_S16_nS_PWM_SR_ON_DT_MAX;
    LLCCTRL_mg_s161nsSrOffDeadTime = MG_S16_nS_PWM_SR_OFF_DT_MAX;
  }

  /*******************************************************************************
   * LLC and SR dead time control
   *******************************************************************************/
  /* Linear LLC dead time */
  LLCCTRL_mg_s161nsLlcDeadTime1 = ((((sint32)MG_U32_nS_PWM_LLC_DT_PERIOD_1 - (sint32)LLCCTRL_mg_sLoop.u321nsLlcPeriod) * MG_S32Q12_LLC_DT_FACT_1) >> 12);
  LLCCTRL_mg_s161nsLlcDeadTime1 = LIMIT(LLCCTRL_mg_s161nsLlcDeadTime1, MG_S16_nS_LLC_DT_MIN_1, MG_S16_nS_LLC_DT_MAX_1);
  LLCCTRL_mg_u161nsLlcDeadTime = (MG_S16_nS_PWM_LLC_DEAD_TIME_1 + LLCCTRL_mg_s161nsLlcDeadTime1);

  /* Linear SR turn on dead time */
  LLCCTRL_mg_s321nsSrOnDeadTime1 = ((((sint32)MG_U32_nS_PWM_SR_ON_DT_PERIOD_1 - (sint32)LLCCTRL_mg_sLoop.u321nsLlcPeriod) * MG_S32Q12_SR_ON_DT_FACT_1) >> 12);
  LLCCTRL_mg_s321nsSrOnDeadTime1 = LIMIT(LLCCTRL_mg_s321nsSrOnDeadTime1, MG_S16_nS_SR_ON_DT_MIN_1, MG_S16_nS_SR_ON_DT_MAX_1);
  LLCCTRL_mg_s321nsSrOnDeadTime2 = ((((sint32)MG_U32_nS_PWM_SR_ON_DT_PERIOD_2 - (sint32)LLCCTRL_mg_sLoop.u321nsLlcPeriod) * MG_S32Q12_SR_ON_DT_FACT_2) >> 12);
  LLCCTRL_mg_s321nsSrOnDeadTime2 = LIMIT(LLCCTRL_mg_s321nsSrOnDeadTime2, MG_S16_nS_SR_ON_DT_MIN_2, MG_S16_nS_SR_ON_DT_MAX_2);
  LLCCTRL_mg_s161nsSrOnDeadTime = (MG_S16_nS_PWM_SR_ON_DEAD_TIME_1 + LLCCTRL_mg_s321nsSrOnDeadTime1 + LLCCTRL_mg_s321nsSrOnDeadTime2);

  /* Linear SR turn off dead time */
  LLCCTRL_mg_s321nsSrOffDeadTime1 = ((((sint32)MG_U32_nS_PWM_SR_OFF_DT_PERIOD_1 - (sint32)LLCCTRL_mg_sLoop.u321nsLlcPeriod) * MG_S32Q12_SR_OFF_DT_FACT_1) >> 12);
  LLCCTRL_mg_s321nsSrOffDeadTime1 = LIMIT(LLCCTRL_mg_s321nsSrOffDeadTime1, MG_S16_nS_SR_OFF_DT_MIN_1, MG_S16_nS_SR_OFF_DT_MAX_1);
  LLCCTRL_mg_s321nsSrOffDeadTime2 = ((((sint32)MG_U32_nS_PWM_SR_OFF_DT_PERIOD_2 - (sint32)LLCCTRL_mg_sLoop.u321nsLlcPeriod) * MG_S32Q12_SR_OFF_DT_FACT_2) >> 12);
  LLCCTRL_mg_s321nsSrOffDeadTime2 = LIMIT(LLCCTRL_mg_s321nsSrOffDeadTime2, MG_S16_nS_SR_OFF_DT_MIN_2, MG_S16_nS_SR_OFF_DT_MAX_2);
  LLCCTRL_mg_s161nsSrOffDeadTime = (MG_S16_nS_PWM_SR_OFF_DEAD_TIME_1 + LLCCTRL_mg_s321nsSrOffDeadTime1 + LLCCTRL_mg_s321nsSrOffDeadTime2);

  /*******************************************************************************
   * Set PWM outputs (LLC & SR)
   * Processing time: 2.0us
   *******************************************************************************/
  LLCCTRL_scfg_vHrTimerSetPwm(LLCCTRL_mg_sLoop.u321nsLlcPeriod, LLCCTRL_mg_u16q16LlcDutyCycle, LLCCTRL_mg_u161nsLlcDeadTime, LLCCTRL_mg_s161nsSrOnDeadTime, LLCCTRL_mg_s161nsSrOffDeadTime);

  /* In case of previous CT over current event, new applied PWM values and no active over current -> release PWM */
  if (MG_B_LLC_CT_OCP && (!LLCCTRL_scfg_u8CompOutputStatus()))
  {
    /* If no CT OC latch, turn on PWM outputs again and reset flags */
    #if ((FALSE == DEBUG_SECTION_OCP_LATCH) && (FALSE == MG_OCP_LATCH))
      /* Reset delayed protection ISR flag */
      LLCCTRL_scfg_vHrTimerAClearDlyProtFlg();
      /* Reset flag */
      MG_B_LLC_CT_OCP = FALSE;
      #if (!DEBUG_SECTION_PWM_DRV_OFF)
        /* Turn on PWM A output */
        LLCCTRL_scfg_vHrTimerAPwmOn();
        #if (!DEBUG_SECTION_SR_DRV_OFF)
          /* Turn on PWM C output */
          LLCCTRL_scfg_vHrTimerBPwmOn();
        #endif
      #endif
    #else
      /* Report the CT OCP to RTE */
      MG_B_LLC_CT_OCP_TO_MON = TRUE;
    #endif
  }
} /* END ISR */

/** *****************************************************************************
 * \brief         Update the status of LLC control loop
 *                Repetition time: 200uS
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))  /* Load ISR into CCRAM for max processing speed */
void LLCCTRL_vStatusUpdate(void)
{
  /* Write RTE variables */
  LLCCTRL_Write_P_B_LLC_OCP_CT_rte(MG_B_LLC_CT_OCP_TO_MON);
  LLCCTRL_Write_P_B_LLC_SOFT_START_rte(MG_B_LLC_SOFT_START);
  LLCCTRL_Write_P_B_LLC_CURR_LIMIT_EN_rte(MG_B_LLC_CURR_LIMIT_MODE);
}

/** *****************************************************************************
 * \brief         Adjust parameters accordingly to low or high line
 *                Repetition time: 200uS
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vLlHlAdjust(void)
{
  /* Get calibration data from RTE */
  #if MG_CALIBRATE_VREF_IOUT
  LLCCTRL_Read_R_q12_VoltRefCaliFact_rte(&LLCCTRL_mg_u16q12VoltRefCaliFact);
  #endif
  LLCCTRL_Read_R_q12_CalibVoltOutGain_rte(&LLCCTRL_mg_u16q12CalibVoltOutGain);
  LLCCTRL_Read_R_q12_CalibCurrOutGain_rte(&LLCCTRL_mg_u16q12CalibCurrOutGain);

  /* If PSU in low line operation */
  if (!Rte_Read_R_B_VIN_LINE)
  {
    #if MG_CURR_LIMIT_MODE
    /*******************************************************************************
     * Set current limit mode parameters
     *******************************************************************************/
    /* If soft start active */
    LLCCTRL_mg_u1610mACurrLimitSs = MG_U16_10mA_CC_IOUT_SS_LL;
    LLCCTRL_mg_u1610mACurrLimitReg = MG_U16_10mA_CC_IOUT_LL;
    #endif
  }
  /* Else PSU in high line operation */
  else
  {
    #if MG_CURR_LIMIT_MODE
    /*******************************************************************************
     * Set current limit mode parameters
     *******************************************************************************/
    LLCCTRL_mg_u1610mACurrLimitSs = MG_U16_10mA_CC_IOUT_SS_HL;
    LLCCTRL_mg_u1610mACurrLimitReg = MG_U16_10mA_CC_IOUT_HL;
    #endif
  }
}

/** *****************************************************************************
 * \brief         Process output double line ripple IIR-Gain filter coeffcients
 *                Notch frequency 95.0 - 125.0Hz
 *                Notch filter bandwidth 15Hz
 *                Repetition time: has to be 200us/5kHz
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vIirRippleFlt(void)
{
  static uint16 u16100mHzVoltInFreq;
  static uint16 LLCCTRL_mg_u16ErrCnt = 0;
  static sint32 LLCCTRL_mg_s32ErrSum = 0;

  LLCCTRL_mg_s32ErrSum = LLCCTRL_mg_s32ErrSum + LLCCTRL_mg_sLoop.s3210mVVoltErr;
  LLCCTRL_mg_u16ErrCnt++;
  if (LLCCTRL_mg_u16ErrCnt >= 4096)
  {
    LLCCTRL_mg_sLoop.sS1610mErrAvg = (LLCCTRL_mg_s32ErrSum >> 12);
    RTE_u16DebugData1 = LLCCTRL_mg_sLoop.sS1610mErrAvg;
    LLCCTRL_mg_s32ErrSum = 0;
    LLCCTRL_mg_u16ErrCnt = 0;
  }
  /* Get RTE data */
  LLCCTRL_Read_R_100mHz_VoltInFreq_rte(&u16100mHzVoltInFreq);

  #if MG_IIR_RIPPLE_FLT
  if (400U >= u16100mHzVoltInFreq) /* < 80Hz */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.0F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.0F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 0.0F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.0F);
  }
  else if (490U >= u16100mHzVoltInFreq) /* 95Hz */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.005295056836108720F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.005295056836108720F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 1.975250469494065580F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.989409886327782484F);
  }
  else if (510U >= u16100mHzVoltInFreq) /*(98Hz,102Hz) */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.005310303638607782F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.005310303638607782F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 1.973692542012342570F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.989379392722784412F);
  }
  else if (530U >= u16100mHzVoltInFreq) /* (102Hz,106Hz) */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.005324766833247133F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.005324766833247133F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 1.972140424986102540F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.989350466333505762F);
  }
  else if (550U >= u16100mHzVoltInFreq) /* (106Hz,110Hz) */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.005339209041465511F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.005339209041465511F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 1.970518129141805460F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.989321581917068982F);
  }
  else if (570U >= u16100mHzVoltInFreq) /* (110Hz,114Hz) */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.005355146753642061F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.005355146753642061F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 1.968643489466320060F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.989289706492715859F);
  }
  else if (590U >= u16100mHzVoltInFreq) /* (114Hz,118Hz) */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.005370301077859338F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.005370301077859338F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 1.966778559982777840F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.989259397844281296F);
  }
  else if (640U >= u16100mHzVoltInFreq) /* 125Hz */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.005385431242382720F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.005385431242382720F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 1.964836090273921920F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.989229137515234558F);
  }
  else /* >128Hz */
  {
    LLCCTRL_mg_IirFlt.s32q15IirB0 = S32Q15( 0.0F);
    LLCCTRL_mg_IirFlt.s32q15IirB2 = S32Q15(-0.0F);
    LLCCTRL_mg_IirFlt.s32q30IirA1 = S32Q30( 0.0F);
    LLCCTRL_mg_IirFlt.s32q30IirA2 = S32Q30(-0.0F);
  }

  /*******************************************************************************
   * IIR gain filter processing
   *******************************************************************************/
  /* Dynamic and fault impact limitation */
  LLCCTRL_mg_s3210mVIirE0 = LIMIT(LLCCTRL_mg_sLoop.s3210mVVoltErr, -MG_S16_10mV_IIR_IN_LIMIT, MG_S16_10mV_IIR_IN_LIMIT);
  /* Get the IIR-Gain filters amplified (gain) error signal */
  LLCCTRL_mg_s3210mVIirE0 = (LLCCTRL_mg_s3210mVIirE0 * LLCCTRL_mg_s32q8IirGain) >> 8;

  /* 90-120Hz IIR ripple cancellation filter */
  LLCCTRL_mg_s32q1510mVIirU0 = (   ((sint32)LLCCTRL_mg_IirFlt.s32q15IirB0 * LLCCTRL_mg_s3210mVIirE0)
                               +   ((sint32)LLCCTRL_mg_IirFlt.s32q15IirB2 * LLCCTRL_mg_s3210mVIirE2)
                               + ((((sint64)LLCCTRL_mg_IirFlt.s32q30IirA1 * LLCCTRL_mg_s32q1510mVIirU1)
                               +   ((sint64)LLCCTRL_mg_IirFlt.s32q30IirA2 * LLCCTRL_mg_s32q1510mVIirU2)) >> 30) );

  /* Store variables */
  LLCCTRL_mg_s3210mVIirE2 = LLCCTRL_mg_s3210mVIirE1;
  LLCCTRL_mg_s3210mVIirE1 = LLCCTRL_mg_s3210mVIirE0;
  LLCCTRL_mg_s32q1510mVIirU2 = LLCCTRL_mg_s32q1510mVIirU1;
  LLCCTRL_mg_s32q1510mVIirU1 = LLCCTRL_mg_s32q1510mVIirU0;

  if(FALSE == MG_B_LLC_SOFT_START)
  {
    /* Filter gain limitation */
    LLCCTRL_mg_s1610mVIirFlt = LIMIT((LLCCTRL_mg_s32q1510mVIirU0 >> 15), -MG_S16_10mV_IIR_OUT_LIMIT, MG_S16_10mV_IIR_OUT_LIMIT);
  }
  else
  {
    LLCCTRL_mg_s1610mVIirFlt = 0;
  }
  #else
  LLCCTRL_mg_s1610mVIirFlt = 0;
  #endif
}


/*
 * End of file
 */

