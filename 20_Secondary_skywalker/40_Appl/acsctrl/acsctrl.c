/** *****************************************************************************
 * \file    acsctrl.c
 * \brief   Active current share control control
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
#define ACSCTRL_EXPORT_H
  #include "acsctrl_api.h"
  #include "acsctrl_scb.h"
  #include "acsctrl_cfg.h"
  #include "acsctrl_scfg.h"
  #include "acsctrl_rte.h"
  #include "acsctrl_conf.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
#if MG_ACTIVE_CURRENT_SHARE_ENABLE
static uint16 ACSCTRL_mg_u1610mACurrOutRaw = 0U;
static uint16 ACSCTRL_mg_u1610mACurrOutFlt = 0U;
static uint16 ACSCTRL_mg_u1610mACurrOut = 0U;
static sint16 ACSCTRL_mg_s1610mACurrOutCompen = 0;
static uint16 ACSCTRL_mg_u1610mAAcsBus = 0U;
static uint16 ACSCTRL_mg_u1610mAAcsLocal = 0U;

static volatile sint32 ACSCTRL_mg_s3210mAAcsBusU0;
static volatile sint32 ACSCTRL_mg_s3210mAAcsBusU1;
static volatile sint32 ACSCTRL_mg_s3210mAAcsBusE0;
static volatile sint32 ACSCTRL_mg_s3210mAAcsBusE1;
static volatile sint32 ACSCTRL_mg_s32q1510mAAcsBusE0Tmp;
static volatile sint32 ACSCTRL_mg_s32q1510mAAcsBusE1 = 0U;

static uint16 LLCCTRL_mg_u16q12CalibIshareGain;
static sint16 LLCCTRL_mg_s16q12CalibIshareOfs;
#endif

static GLOBAL_U_U8BIT ACSCTRL_mg_uSyncStatus;

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
void ACSCTRL_vInit(void)
{
  #if MG_ACTIVE_CURRENT_SHARE_ENABLE
  ACSCTRL_scfg_vSetAcsBus(0U);
  /* Get inital calibration data */
  ACSCTRL_Read_R_q12_CalibIshareGain_rte(&LLCCTRL_mg_u16q12CalibIshareGain);
  ACSCTRL_Read_R_s16_10mA_CalibIshareOfs_rte(&LLCCTRL_mg_s16q12CalibIshareOfs);
  #endif
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
void ACSCTRL_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         Active current share control function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))  /* Load ISR into CCRAM for max processing speed */
void ACSCTRL_vAcsCtrl(void)
{
  #if MG_ACTIVE_CURRENT_SHARE_ENABLE
  /*******************************************************************************
   * Active current share processing
   * Processing time: 2.6us
   *******************************************************************************/
  /*******************************************************************************
   * Local bus measurement processing
   *******************************************************************************/
  /* Get internal output voltage */
  ACSCTRL_mg_u1610mAAcsLocal = ACSCTRL_scfg_u16AdcSampleAcsLocal();

  /*******************************************************************************
   * Share bus measurement processing
   *******************************************************************************/
  /* Get external output voltage */
  ACSCTRL_mg_u1610mAAcsBus = ACSCTRL_scfg_u16AdcSampleAcsBus();

  /*******************************************************************************
   * Current measurement processing
   *******************************************************************************/
  /* Get output current */
  ACSCTRL_mg_u1610mACurrOutRaw = ACSCTRL_scfg_u16AdcSampleCurrOut();
  /* Use a digital filter for output current averaging */
  ACSCTRL_mg_u1610mACurrOutFlt = (((uint32)MG_U16Q15_K1_IOUT_FLT * ACSCTRL_mg_u1610mACurrOutFlt
                                 + (uint32)MG_U16Q15_K2_IOUT_FLT * ACSCTRL_mg_u1610mACurrOutRaw) >> 15);
  /* Calibrate measured output current */
  ACSCTRL_mg_u1610mACurrOut = ((((sint32)ACSCTRL_mg_u1610mACurrOutFlt * LLCCTRL_mg_u16q12CalibIshareGain) >> 12) + LLCCTRL_mg_s16q12CalibIshareOfs);

  /*******************************************************************************
   * Set active current share bus voltage
   *******************************************************************************/
  if (FALSE == MG_B_LLC_SYNC_START_SEQUENCE)
  {
    /* Set the active current share bus voltage (feed forward) */
    ACSCTRL_scfg_vSetAcsBus(SAT_L(((sint16)ACSCTRL_mg_u1610mACurrOut + ACSCTRL_mg_s1610mACurrOutCompen), 0));
  }

  /*******************************************************************************
   * Current share bus loop (Vref adjustment)
   *******************************************************************************/
  if ((TRUE == Rte_Read_R_B_LLC_EN) && (FALSE == Rte_Read_R_B_SOFT_START))
  {
    /* Get current share error */
    ACSCTRL_mg_s3210mAAcsBusE0 = ((sint32)ACSCTRL_mg_u1610mAAcsBus - ACSCTRL_mg_u1610mAAcsLocal) + MG_S16_10mA_ACS_LOCAL_TO_BUS_OFFSET;
    /* Limit the error */
    ACSCTRL_mg_s3210mAAcsBusE0 = LIMIT(ACSCTRL_mg_s3210mAAcsBusE0, MG_S16_10mA_MIN_ACS_BUS_ERROR, MG_S16_10mA_MAX_ACS_BUS_ERROR);

    #if MG_POSITONAL_INCREMENTAL_PI  /* Positional PI */
    /* Parallel PI controller */
    ACSCTRL_mg_s3210mAAcsBusU0 = (((MG_S32Q15_ACS_BUS_CTRL_KP * ACSCTRL_mg_s3210mAAcsBusE0) + ACSCTRL_mg_s32q1510mAAcsBusE1) >> 15);
    /* New integral part calculation */
    ACSCTRL_mg_s32q1510mAAcsBusE0Tmp = (MG_S32Q15_ACS_BUS_CTRL_KI * ACSCTRL_mg_s3210mAAcsBusE0);

    /* Anti wind up */
    /* If PI output higher than upper limit */
    if (MG_S16_10mV_MAX_ACS_VREF_ADJUST < ACSCTRL_mg_s3210mAAcsBusU0)
    {
      /* Anti wind-up with integral adjustment (back tracking) */
      ACSCTRL_mg_s32q1510mAAcsBusE0Tmp = (((sint32)MG_S16_10mV_MAX_ACS_VREF_ADJUST - ACSCTRL_mg_s3210mAAcsBusU0) << 15);
      /* then set PI output to upper limit */
      ACSCTRL_mg_s3210mAAcsBusU0 = MG_S16_10mV_MAX_ACS_VREF_ADJUST;
    }
    /* If PI output below lower limit */
    if (MG_S16_10mV_MIN_ACS_VREF_ADJUST > ACSCTRL_mg_s3210mAAcsBusU0)
    {
      /* Anti wind-up with integral adjustment (back tracking) */
      ACSCTRL_mg_s32q1510mAAcsBusE0Tmp = (((sint32)MG_S16_10mV_MIN_ACS_VREF_ADJUST - ACSCTRL_mg_s3210mAAcsBusU0) << 15);
      /* then set PI output to lower limit */
      ACSCTRL_mg_s3210mAAcsBusU0 = MG_S16_10mV_MIN_ACS_VREF_ADJUST;
    }
    /* Error summation for I-part and limitation */
    ACSCTRL_mg_s32q1510mAAcsBusE1 = ACSCTRL_mg_s32q1510mAAcsBusE1 + ACSCTRL_mg_s32q1510mAAcsBusE0Tmp;
    #else  /* Incremental PI */
    /* PI controller */
    ACSCTRL_mg_s3210mAAcsBusU0 = ACSCTRL_mg_s3210mAAcsBusU1 
                                 +(((MG_S32Q15_ACS_BUS_CTRL_B0 * ACSCTRL_mg_s3210mAAcsBusE0)
                                 +  (MG_S32Q15_ACS_BUS_CTRL_B1 * ACSCTRL_mg_s3210mAAcsBusE1)) >> 15);
    /* If PI output limit */
    ACSCTRL_mg_s3210mAAcsBusU0 = LIMIT(ACSCTRL_mg_s3210mAAcsBusU0, MG_S16_10mV_MIN_ACS_VREF_ADJUST, MG_S16_10mV_MAX_ACS_VREF_ADJUST);
    /* Store variables */
    ACSCTRL_mg_s3210mAAcsBusU1 = ACSCTRL_mg_s3210mAAcsBusU0;
    ACSCTRL_mg_s3210mAAcsBusE1 = ACSCTRL_mg_s3210mAAcsBusE0;
    #endif
    /* Write data to RTE */
    ACSCTRL_Write_P_10mV_MainVoltAdjCurrShare_rte(ACSCTRL_mg_s3210mAAcsBusU0);
  }
  else
  {
    /* Reset active current share loop */
    ACSCTRL_mg_s32q1510mAAcsBusE1 = 0U;
    ACSCTRL_mg_s3210mAAcsBusU0 = MG_S16_10mV_MIN_ACS_VREF_ADJUST;
  }
  #endif
}

/** *****************************************************************************
 * \brief         Syncronized power-up sequence
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void ACSCTRL_vSyncCtrl(void)
{
  #if MG_SYNC_START_ENABLED
  static uint8 u8PulseDetCtr = 0U;
  static uint16 u16PulseDly = 0U;
  static uint16 u16PulseCtr = 0U;
  static uint16 u1610mVVoltOutExt = 0U;

  if (FALSE == Rte_Read_R_B_LLC_EN)
  {
    /* Read data from RTE */
    ACSCTRL_Read_R_10mV_VoltOutExt_rte(&u1610mVVoltOutExt);

    /*******************************************************************************
     * Syncronized start-up detection
     *******************************************************************************/
    /* If voltage detected on active current share bus, then begin start-up sequence */
    if ((MG_U16_10mA_ACS_BUS_SYNC_PULSE_DET < ACSCTRL_mg_u1610mAAcsBus) || (MG_U16_10mV_VOUT_SYNC_START_UP < u1610mVVoltOutExt))
    {
      /* If pulse detected, start power-up */
      if (MG_U16_PULSE_DET_DLY < u8PulseDetCtr)
      {
        /* Set power-up flag */
        MG_B_LLC_SYNC_START_UP = TRUE;
      }
      else
      {
        /* Count-up detection counter */
        u8PulseDetCtr++;
      }
    }
    else
    {
      /* Reset power-up flag */
      MG_B_LLC_SYNC_START_UP = FALSE;

      /* Decrease pulse detection counter */
      if (0U < u8PulseDetCtr)
      {
        u8PulseDetCtr--;
      }
    }

    /*******************************************************************************
     * Process synced start-up delay
     *******************************************************************************/
    if (TRUE == Rte_Read_R_B_LLC_STANDBY)
    {
      /* Wait for some time to make sure all untis are ready */
      if (MG_U16_START_UP_DLY < u16PulseDly)
      {
        /* Set sync start up ready flag */
        MG_B_LLC_SYNC_START_READY = TRUE;
      }
      else
      {
        /* Increase pulse delay counter */
        u16PulseDly++;
      }
    }
    else
    {
      /* Reset sync start up ready flag */
      MG_B_LLC_SYNC_START_READY = FALSE;
      /* Reset counter */
      u16PulseDly = 0;
    }

    /*******************************************************************************
     * Syncronized start-up pulse generation
     *******************************************************************************/
    if ((TRUE == MG_B_LLC_SYNC_START_READY) && (MG_U16_10mV_VOUT_SYNC_START_UP > u1610mVVoltOutExt))
    {
      /* Enable sync start sequence */
      MG_B_LLC_SYNC_START_SEQUENCE = TRUE;
      /* Generate a pulse on active current share bus */
      ACSCTRL_scfg_vSetAcsBus(MG_U16_10mA_ACS_BUS_SYNC_PULSE);
    }
    else
    {
      u16PulseCtr = 0U;
      /* Disable sync start sequence and free current share bus */
      MG_B_LLC_SYNC_START_SEQUENCE = FALSE;
    }
  }
  else
  {
    /* If the pulse not reached the desired length and the start-up sequence active, continue pulse */
    if ((MG_U16_PULSE_LENGTH_TM > u16PulseCtr) && (TRUE == MG_B_LLC_SYNC_START_SEQUENCE))
    {
      u16PulseCtr++;
    }
    /* Else disable pulse */
    else
    {
      /* Disable sync start sequence and free current share bus */
      MG_B_LLC_SYNC_START_SEQUENCE = FALSE;
      u16PulseCtr = 0U;
    }
    u8PulseDetCtr = 0U;
    u16PulseDly = 0U;
    /* Reset sync start up ready flag */
    MG_B_LLC_SYNC_START_READY = FALSE;
  }
  #else
  /* Disable sync start sequence and free current share bus */
  MG_B_LLC_SYNC_START_SEQUENCE = FALSE;
  /* Set sync start up ready flag */
  MG_B_LLC_SYNC_START_UP = TRUE;
  #endif
  /* Get calibration data from RTE */
  ACSCTRL_Read_R_q12_CalibIshareGain_rte(&LLCCTRL_mg_u16q12CalibIshareGain);
  ACSCTRL_Read_R_s16_10mA_CalibIshareOfs_rte(&LLCCTRL_mg_s16q12CalibIshareOfs);
  if(ACSCTRL_mg_u1610mAAcsLocal < ACSCTRL_mg_u1610mACurrOut)
  {
    ACSCTRL_mg_s1610mACurrOutCompen++;
  }
  else if(ACSCTRL_mg_u1610mAAcsLocal > ACSCTRL_mg_u1610mACurrOut)
  {
    ACSCTRL_mg_s1610mACurrOutCompen--;
  }
  ACSCTRL_mg_s1610mACurrOutCompen = LIMIT(ACSCTRL_mg_s1610mACurrOutCompen, MG_S16_10mA_MIN_CURR_OUT_COMPEN, MG_S16_10mA_MAX_CURR_OUT_COMPEN);
  /* Write RTE variables */
  ACSCTRL_Write_P_B_LLC_SYNC_START_UP_rte(MG_B_LLC_SYNC_START_UP);
}


/*
 * End of file
 */

