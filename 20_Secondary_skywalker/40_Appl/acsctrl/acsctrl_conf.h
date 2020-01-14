/** *****************************************************************************
 * \file    acsctrl_conf.h
 * \brief   Configuration file for acsctrl.c
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

#ifndef ACSCTRL_CONF_H
#define ACSCTRL_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

#define MG_ACTIVE_CURRENT_SHARE_ENABLE      1     /* 1 = Active current share; 0 = No active current share */
#define MG_SYNC_START_ENABLED               0     /* 1 = Syncronized start-up enabled; NOTE: requires active current share bus to be connected */
#define MG_POSITONAL_INCREMENTAL_PI         1     /* 1 = Positional PI, 0 =  Incremental PI */

#define MG_200US_TO_1MS_FACT               5U     /* 1ms / 200uS = 5 */

/***********************************************
 * Sync Control Status
 **********************************************/
#define MG_B_LLC_SYNC_START_SEQUENCE   ACSCTRL_mg_uSyncStatus.Bits.f0  /* 1 = syncronized start-up sequence enabled */
#define MG_B_LLC_SYNC_START_UP         ACSCTRL_mg_uSyncStatus.Bits.f1  /* 1 = ready for syncronized start-up */
#define MG_B_LLC_SYNC_START_READY      ACSCTRL_mg_uSyncStatus.Bits.f2  /* 1 = syncronized start-up ready */

/***********************************************
 * Measurements 
 **********************************************/
#define  MG_F32_K1_IOUT_FLT               0.5F     /* (100%) old value */
#define  MG_F32_K2_IOUT_FLT               0.5F     /* (100%) new value */

/***********************************************
 * Current share bus (Vref adjustment)
 **********************************************/
#define MG_F32_ACS_BUS_CTRL_KP         0.0100F    /* KP parameter */
#define MG_F32_ACS_BUS_CTRL_KI         0.0005F    /* KI parameter */

/* Limitations */
#define MG_F32_MAX_ACS_BUS_ERROR        10.0F     /* (A) */
#define MG_F32_MAX_ACS_VREF_ADJUST       0.5F     /* (V) */
#define MG_F32_MIN_ACS_VREF_ADJUST       0.0F     /* (V) */

#define MG_F32_MAX_CURR_OUT_COMPEN       5.0F     /* (A) */

#define MG_F32_ACS_LOCAL_TO_BUS_OFFSET  -1.0F     /* (A) Positive: increase Ibus voltage; Negative: reduce Ibus voltage; NOTE: Ibus voltage has to be equal or lower than Ilocal */

/***********************************************
 * Syncronized start up
 **********************************************/
#define MG_F32_ACS_BUS_SYNC_PULSE_DET   30.0F     /* (A) Current equivalent pulse detection treshold */
#define MG_F32_ACS_BUS_SYNC_PULSE       60.0F     /* (A) Current equivalent pulse */
#define MG_F32_VOUT_SYNC_START_UP       40.0F     /* (V) If output voltage higher -> bypass pulse generation and power up directly */

#define MG_U16_PULSE_DET_DLY      (uint16)(2U * MG_200US_TO_1MS_FACT)     /* (ms) (200us * 5 = 1ms) */
#define MG_U16_PULSE_LENGTH       (uint16)(4U * MG_200US_TO_1MS_FACT)     /* (ms) (200us * 5 = 1ms) */
#define MG_U16_START_UP_DLY       (uint16)(800U * MG_200US_TO_1MS_FACT)   /* (ms) (200us * 5 = 1ms) */

/*******************************************************************************
 * Scaling section
 ******************************************************************************/

#define MG_U16Q15_K1_IOUT_FLT               (uint16)U32Q15(MG_F32_K1_IOUT_FLT)
#define MG_U16Q15_K2_IOUT_FLT               (uint16)U32Q15(MG_F32_K2_IOUT_FLT)

#define MG_S16_10mA_MAX_ACS_BUS_ERROR       (sint16)(MG_F32_MAX_ACS_BUS_ERROR * F32_10_MILLI)
#define MG_S16_10mA_MIN_ACS_BUS_ERROR       (sint16)(-MG_F32_MAX_ACS_BUS_ERROR * F32_10_MILLI)

#define MG_S16_10mV_MAX_ACS_VREF_ADJUST     (sint16)(MG_F32_MAX_ACS_VREF_ADJUST * F32_10_MILLI)
#define MG_S16_10mV_MIN_ACS_VREF_ADJUST     (sint16)(MG_F32_MIN_ACS_VREF_ADJUST * F32_10_MILLI)
#define MG_S16_10mA_MAX_CURR_OUT_COMPEN     (sint16)(MG_F32_MAX_CURR_OUT_COMPEN * F32_10_MILLI)
#define MG_S16_10mA_MIN_CURR_OUT_COMPEN     (sint16)(-MG_F32_MAX_CURR_OUT_COMPEN * F32_10_MILLI)

#define MG_S16_10mA_ACS_LOCAL_TO_BUS_OFFSET (sint16)(MG_F32_ACS_LOCAL_TO_BUS_OFFSET * F32_10_MILLI)

#define MG_S32Q15_ACS_BUS_CTRL_KP           ((sint32)S32Q15(MG_F32_ACS_BUS_CTRL_KP))
#define MG_S32Q15_ACS_BUS_CTRL_KI           ((sint32)S32Q15(MG_F32_ACS_BUS_CTRL_KI))
#define MG_S32Q15_ACS_BUS_CTRL_B0           ((sint32)S32Q15(MG_F32_ACS_BUS_CTRL_KP + (MG_F32_ACS_BUS_CTRL_KI / 2)))
#define MG_S32Q15_ACS_BUS_CTRL_B1           ((sint32)S32Q15(-MG_F32_ACS_BUS_CTRL_KP + (MG_F32_ACS_BUS_CTRL_KI / 2)))

#define MG_U16_10mA_ACS_BUS_SYNC_PULSE_DET  (uint16)(MG_F32_ACS_BUS_SYNC_PULSE_DET * F32_10_MILLI)
#define MG_U16_10mA_ACS_BUS_SYNC_PULSE      (uint16)(MG_F32_ACS_BUS_SYNC_PULSE * F32_10_MILLI)
#define MG_U16_10mV_VOUT_SYNC_START_UP      (uint16)(MG_F32_VOUT_SYNC_START_UP * F32_10_MILLI)
#define MG_U16_PULSE_LENGTH_TM              (uint16)(SAT_L((MG_U16_PULSE_LENGTH - MG_U16_PULSE_DET_DLY), 0))


#ifdef __cplusplus
  }
#endif
#endif  /* ACSCTRL_CONF_H */

  
/*
 * End of file
 */
