/** *****************************************************************************
 * \file    hwio.c
 * \brief   Hardware input/output interface
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

#include "global.h"
#include "debug_llc.h"

/* Module header */
#define HWIO_EXPORT_H
  #include "hwio_api.h"
  #include "hwio_scb.h"
  #include "hwio_cfg.h"
  #include "hwio_scfg.h"
  #include "hwio_rte.h"
  #include "hwio_conf.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static uint16 HWIO_mg_u161mVVoltRefCaliFact = 0U;

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
void HWIO_vInit(void)
{
  /* Init ADC scaling */
  HWIO_scfg_vAdcVoltOutExtScale(MG_U16_10mV_VOUT_EXT_SCALE_FACT);
  HWIO_scfg_vAdcVoltOutIntScale(MG_U16_10mV_VOUT_INT_SCALE_FACT);
  HWIO_scfg_vAdcCurrOutScale(MG_U16_10mA_I_OUT_SCALE_FACT);
  HWIO_scfg_vAdcAcsBusScale(MG_U16_10mA_I_OUT_SCALE_FACT);
  HWIO_scfg_vAdcAcsLocalScale(MG_U16_10mA_I_OUT_SCALE_FACT);
  HWIO_scfg_vAdcVoltRef3V3Scale(MG_U16_1mV_VREF_SCALE_FACT);
  HWIO_scfg_vAdcResNtcScale(MG_U16_1Ohm_NTC_PULL_UP_RES);
  /* Init COMP scaling */
  HWIO_scfg_vCompCurrCtOcScale(MG_U32_10mA_I_CT_COMP_SCALE_FACT);
  /* Init DAC scaling */
  HWIO_scfg_vDacAcsScale(MG_U16_10mA_I_OUT_SCALE_FACT);
  /* Init PWM */
  HWIO_scfg_vTimerSetPeriod(MG_TIM1, MG_TIMER_1_PERIOD_US);
  HWIO_scfg_vTimer1Ch1DutyCycle(MG_Q16_TIMER_1_DUTY_CYCLE);
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
void HWIO_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         Get converted ADC units
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vReadAdcUnits(void)
{
  /*************************************************************
   * Get external output voltage
   ************************************************************/
  static uint16 u1610mVVoltOutExt;
  /* Get converted phase A current */
  u1610mVVoltOutExt = HWIO_scfg_u16AdcSampleVoltOutExt();
  /* Hand over the data to RTE */
  HWIO_Write_P_10mV_VoltOutExt_rte(u1610mVVoltOutExt);

  /*************************************************************
   * Get internal output voltage
   ************************************************************/
  static uint16 u1610mVVoltOutInt;
  /* Get converted phase B current */
  u1610mVVoltOutInt = HWIO_scfg_u16AdcSampleVoltOutInt();
  /* Hand over the data to RTE */
  HWIO_Write_P_10mV_VoltOutInt_rte(u1610mVVoltOutInt);

  /*************************************************************
   * Get output current
   ************************************************************/
  static uint16 u1610mACurrOutRaw;
  static uint16 u1610mACurrOutFlt;
  static uint16 u1610mACurrOutCali;
  static sint16 s16CalibCurrOutAmp = 0;
  static sint16 s16CalibCurrOutOfs = 0;
  /*******************************************************************************
   * Get the calibration data from COM
   *******************************************************************************/
  /* Get the output current amp calibration value */
  HWIO_Read_R_s16CalibCurrOutAmp_rte(&s16CalibCurrOutAmp);
  /* Get the output current offset calibration value */
  HWIO_Read_R_s16CalibCurrOutOfs_rte(&s16CalibCurrOutOfs);
  /* Get converted input current */
  u1610mACurrOutRaw = HWIO_scfg_u16AdcSampleCurrOut();
  /* Use a digital filter for output current averaging */
  u1610mACurrOutFlt = (((uint32)MG_U16Q15_K1_I_OUT_FLT * u1610mACurrOutFlt 
                      + (uint32)MG_U16Q15_K2_I_OUT_FLT * u1610mACurrOutRaw) >> 15);
  /* Hand over the data to RTE */
  HWIO_Write_P_10mA_CurrOut_rte(u1610mACurrOutFlt);
  /* Get the calibration value of output current */
  u1610mACurrOutCali = ((((((u1610mACurrOutFlt * s16CalibCurrOutAmp + 4096) >> 13) + s16CalibCurrOutOfs) * (uint16)F32_10_MILLI) >> 7));
  /* Hand over the data to RTE */
  HWIO_Write_P_10mA_CurrOutCali_rte(u1610mACurrOutCali);

  /*************************************************************
   * Get active current share bus current
   ************************************************************/
  static uint16 u1610mAAcsBus;
  /* Get converted input current */
  u1610mAAcsBus = HWIO_scfg_u16AdcSampleAcsBus();
  /* Hand over the data to RTE */
  HWIO_Write_P_10mA_AcsBus_rte(u1610mAAcsBus);

  /*************************************************************
   * Get active current share local current
   ************************************************************/
  static uint16 u1610mAAcsLocal;
  /* Get converted input current */
  u1610mAAcsLocal = HWIO_scfg_u16AdcSampleAcsLocal();
  /* Hand over the data to RTE */
  HWIO_Write_P_10mA_AcsLocal_rte(u1610mAAcsLocal);

  /*************************************************************
   * Get 3.3V reference voltage
   ************************************************************/
  static uint16 u161mVVoltRef3V3;
  static uint16 u161mVVoltRef3V3Flt;
  /* Get converted reference voltage */
  u161mVVoltRef3V3 = HWIO_scfg_u16VoltRef3V3();
  /* Digital LP filter */
  u161mVVoltRef3V3Flt = (((uint32)MG_U16Q15_K1_REF_FLT * u161mVVoltRef3V3Flt
                        + (uint32)MG_U16Q15_K2_REF_FLT * u161mVVoltRef3V3) >> 15);
  /* Max and min value limitation */
  u161mVVoltRef3V3Flt = LIMIT(u161mVVoltRef3V3Flt, MG_U16_1mV_VREF_EXT_LIMIT_LOW, MG_U16_1mV_VREF_EXT_LIMIT_HIGH);
  /* Calculate the calibration factor in Q12 format*/
  HWIO_mg_u161mVVoltRefCaliFact = (((uint32)MG_U16_1mV_VREF_EXTERNAL << 12) / u161mVVoltRef3V3Flt);
  /* Hand over the data to RTE */
  HWIO_Write_P_1mV_VoltRef3V3_rte(u161mVVoltRef3V3Flt);
  HWIO_Write_P_q12_VoltRefCaliFact_rte(HWIO_mg_u161mVVoltRefCaliFact);

  /*************************************************************
   * Get ORING NTC voltage and resistance
   ************************************************************/
  static uint16 u161OhmNtcOring;
  static uint16 u161mVNtcOring;
  /* Get booster NTC voltage */
  u161OhmNtcOring = HWIO_scfg_u16NtcOringSample();
  u161mVNtcOring  = HWIO_scfg_u16NtcOringSamplemV();
  /* Hand over the data to RTE */
  HWIO_Write_P_1Ohm_ResNtcOring_rte(u161OhmNtcOring);
  HWIO_Write_P_1mV_VoltNtcOring_rte(u161mVNtcOring);

  /*************************************************************
   * Get SR NTC voltage and resistance
   ************************************************************/
  static uint16 u161OhmNtcSr;
  static uint16 u161mVNtcSr;
  /* Get booster NTC voltage */
  u161OhmNtcSr = HWIO_scfg_u16NtcSrSample();
  u161mVNtcSr =  HWIO_scfg_u16NtcSrSamplemV();
  /* Hand over the data to RTE */
  HWIO_Write_P_1Ohm_ResNtcSr_rte(u161OhmNtcSr);
  HWIO_Write_P_1mV_VoltNtcSr_rte(u161mVNtcSr);
}

/** *****************************************************************************
 * \brief         Enable PWM's
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vEnablePwm(void)
{
  #if (!DEBUG_SECTION_PWM_DRV_OFF)
  /* PWM A */
  if (Rte_Read_R_B_PWM_A_ON)
  {
    #if (!DEBUG_SECTION_PWM_A_DRV_OFF)
    /* Enable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_A, TRUE);
    #endif
  }
  else
  {
    /* Disable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_A, FALSE);
  }

  /* PWM B */
  if (Rte_Read_R_B_PWM_B_ON)
  {
    #if (!DEBUG_SECTION_PWM_B_DRV_OFF)
    /* Enable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_B, TRUE);
    #endif
  }
  else
  {
    /* Disable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_B, FALSE);
  }
  
  /* PWM C */
  if (Rte_Read_R_B_PWM_C_ON)
  {
    #if (!DEBUG_SECTION_PWM_C_DRV_OFF)
    /* Enable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_C, TRUE);
    #endif
  }
  else
  {
    /* Disable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_C, FALSE);
  }

  /* PWM D */
  if (Rte_Read_R_B_PWM_D_ON)
  {
    #if (!DEBUG_SECTION_PWM_D_DRV_OFF)
    /* Enable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_D, TRUE);
    #endif
  }
  else
  {
    /* Disable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_D, FALSE);
  }
  
  /* PWM E */
  if (Rte_Read_R_B_PWM_E_ON)
  {
    #if (!DEBUG_SECTION_PWM_E_DRV_OFF)
    /* Enable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_E, TRUE);
    #endif
  }
  else
  {
    /* Disable PWM */
    HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_E, FALSE);
  }
  #else
  /* Disable PWM */
  HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_A, FALSE);
  HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_B, FALSE);
  HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_C, FALSE);
  HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_D, FALSE);
  HWIO_scfg_vHrTimerDrvEnable(MG_HRTIM_E, FALSE);
  #endif
}

/** *****************************************************************************
 * \brief         Set GPIO ports
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vSetGpioPort(void)
{
  #if (!DEBUG_SECTION_PIN_DRV_OFF)
  /* PWM ON */
  if (Rte_Read_R_B_PORT_PWM_ON)
  {
    /* Reset GPIO port (active low) */
    HWIO_scfg_vSetGpioPortPwmOn(FALSE);
  }
  else
  {
    #if DEBUG_SECTION_PIN_DRV_ON
    /* Reset GPIO port (active low) */
    HWIO_scfg_vSetGpioPortPwmOn(FALSE);
    #else
    /* Set GPIO port (active low) */
    HWIO_scfg_vSetGpioPortPwmOn(TRUE);
    #endif
  }
  #else
  /* Set GPIO port (active low) */
  HWIO_scfg_vSetGpioPortPwmOn(TRUE);
  #endif
  
  /* ISHARE ON */
  if (Rte_Read_R_B_PORT_ISHARE_ON)
  {
    /* Set GPIO port (active low) */
    HWIO_scfg_vSetGpioPortIshareOn(FALSE);
  }
  else
  {
    /* Reset GPIO port (active low) */
    HWIO_scfg_vSetGpioPortIshareOn(TRUE);
  }

  /* ORING EN */
  if (Rte_Read_R_B_PORT_ORING_EN)
  {
    /* Set GPIO port (active high) */
    HWIO_scfg_vSetGpioPortOringEn(TRUE);
  }
  else
  {
    /* Reset GPIO port (active high) */
    HWIO_scfg_vSetGpioPortOringEn(FALSE);
  }

  /* ORING EN */
  if (Rte_Read_R_B_PORT_LLC_FAULT)
  {
    /* Set GPIO port (active high) */
    HWIO_scfg_vSetGpioPortLlcFault(TRUE);
  }
  else
  {
    /* Reset GPIO port (active high) */
    HWIO_scfg_vSetGpioPortLlcFault(FALSE);
  }

  #if MG_OVP_CLEAR_BY_MOSFET
  /* OVP CLR */
  if (Rte_Read_R_B_PORT_OVP_CLR)
  {
    /* Set GPIO port (active high) */
    HWIO_scfg_vSetGpioPortOvpClr(TRUE);
  }
  else
  {
    /* Set GPIO port (active high) */
    HWIO_scfg_vSetGpioPortOvpClr(FALSE);
  }
  #else
  /* OVP CLR */
  if (Rte_Read_R_B_PORT_OVP_CLR)
  {
    /* Set the GPIO pin to output */
    HWIO_scfg_vOutputGpioPinOvpClr();
    /* Set GPIO port (active low) */
    HWIO_scfg_vSetGpioPortOvpClr(FALSE);
  }
  else
  {
    /* Set the GPIO pin to input */
    HWIO_scfg_vInputGpioPinOvpClr();
  }
  #endif
}

/** *****************************************************************************
 * \brief         Read GPIO ports
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vReadGpioPort(void)
{
  /* BULK OK */
  if (HWIO_scfg_u8ReadGpioPortBulkOk())
  {
    HWIO_Write_P_B_PORT_BULK_OK_rte(TRUE); /* Active high */
    Rte_Write_P_B_Port_LLC_FAULT = FALSE;
  }
  else
  {
    HWIO_Write_P_B_PORT_BULK_OK_rte(FALSE);
    Rte_Write_P_B_Port_LLC_FAULT = TRUE;
  }

  /* OVP */
  if (HWIO_scfg_u8ReadGpioPortOvp())
  {
    HWIO_Write_P_B_PORT_OVP_rte(TRUE); /* Active high */
  }
  else
  {
    HWIO_Write_P_B_PORT_OVP_rte(FALSE);
  }

  /* SWITCH EN */
  //if (HWIO_scfg_u8ReadGpioPortLlcSwitchEn())
  //{
  //  HWIO_Write_P_B_PORT_LLC_SWITCH_EN_rte(TRUE); /* Active high */
  //}
  //else
  //{
  //  HWIO_Write_P_B_PORT_LLC_SWITCH_EN_rte(FALSE);
  //}

  /* LLC EN */
  if (HWIO_scfg_u8ReadGpioPortLlcHalt())
  {
    HWIO_Write_P_B_PORT_LLC_HALT_rte(TRUE); /* Active high */
  }
  else
  {
    HWIO_Write_P_B_PORT_LLC_HALT_rte(FALSE);
  }
}

/** *****************************************************************************
 * \brief         Read boot loader existing flag from flash and write it to RTE
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vCheckBootLoaderExistFlg(void)
{
  uint8 u8FlgReturn;
  /* Check if flag is existing/correct */
  u8FlgReturn = HWIO_scfg_u8FlashReadBlExistFlg();
  /* Set RTE status */
  HWIO_Write_P_B_BL_EXIST_rte(u8FlgReturn);
}

/** *****************************************************************************
 * \brief         Read boot loader firmware version from flash and write it to RTE
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vReadBootLoaderFwVersion(void)
{
  GLOBAL_DWORD_VAL u32FwReturn;
  /* Check if flag is existing/correct */
  u32FwReturn.u32Val = HWIO_scfg_u32FlashReadBlFwVer();
  /* Set RTE status */
  HWIO_Rte_Write_P_BlFwVerMajor(u32FwReturn.Bytes.LB);
  HWIO_Rte_Write_P_BlFwVerMinor(u32FwReturn.Bytes.HB);
  HWIO_Rte_Write_P_BlFwVerDebug(u32FwReturn.Bytes.UB);
}


/*
 * End of file
 */
