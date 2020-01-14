/** *****************************************************************************
 * \file    tempctrl.h
 * \brief   Configuration file for tempctrl.c
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

#ifndef TEMPCTRL_CONF_H
#define TEMPCTRL_CONF_H
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

/***************************************
 * NTC number
 **************************************/
#define MG_NTC_NBR                            2       /* Primary total NTC number */

#define MG_NTC_OTP_MONITORING                 0       /* 1 = OTP monitoring is enabled; 0 = Only NTC resistor averaging used */

#define MG_100MS_TO_1S_FACT                   10U     /* 1s / 100mS = 10 */

/***********************************************
 * Over temperature detection setting
 **********************************************/
/* NTC1 OTP */
#define MG_U16_1Ohm_NTC_1_OT_SETPOINT      ((uint16)600U)     /* (Ohm) */
#define MG_U16_1Ohm_NTC_1_OT_RESETPOINT    ((uint16)800U)     /* (Ohm) */
#define MG_F32_1s_NTC_1_OTP_DLY                      1.0F     /* (s) */
/* NTC1 OTW */
#define MG_U16_1Ohm_NTC_1_OTW_SETPOINT     ((uint16)650U)     /* (Ohm) */
#define MG_U16_1Ohm_NTC_1_OTW_RESETPOINT   ((uint16)800U)     /* (Ohm) */
#define MG_F32_1s_NTC_1_OTW_DLY                      0.2F     /* (s) */

/* NTC2 OTP */
#define MG_U16_1Ohm_NTC_2_OT_SETPOINT       ((uint16)600U)    /* (Ohm) */
#define MG_U16_1Ohm_NTC_2_OT_RESETPOINT     ((uint16)800U)    /* (Ohm) */
#define MG_F32_1s_NTC_2_OTP_DLY                      1.0F     /* (s) */
/* NTC2 OTW */
#define MG_U16_1Ohm_NTC_2_OTW_SETPOINT      ((uint16)650U)    /* (Ohm) */
#define MG_U16_1Ohm_NTC_2_OTW_RESETPOINT    ((uint16)800U)    /* (Ohm) */
#define MG_F32_1s_NTC_2_OTW_DLY                      0.2F     /* (s) */

/* NTC3 OTP */
#define MG_U16_1Ohm_NTC_3_OT_SETPOINT       ((uint16)600U)    /* (Ohm) */
#define MG_U16_1Ohm_NTC_3_OT_RESETPOINT     ((uint16)800U)    /* (Ohm) */
#define MG_F32_1s_NTC_3_OTP_DLY                      1.0F     /* (s) */
/* NTC3 OTW */
#define MG_U16_1Ohm_NTC_3_OTW_SETPOINT      ((uint16)650U)    /* (Ohm) */
#define MG_U16_1Ohm_NTC_3_OTW_RESETPOINT    ((uint16)800U)    /* (Ohm) */
#define MG_F32_1s_NTC_3_OTW_DLY                      0.2F     /* (s) */

/* NTC4 OTP */
#define MG_U16_1Ohm_NTC_4_OT_SETPOINT       ((uint16)600U)    /* (Ohm) */
#define MG_U16_1Ohm_NTC_4_OT_RESETPOINT     ((uint16)800U)    /* (Ohm) */
#define MG_F32_1s_NTC_4_OTP_DLY                      1.0F     /* (s) */
/* NTC4 OTW */
#define MG_U16_1Ohm_NTC_4_OTW_SETPOINT      ((uint16)650U)    /* (Ohm) */
#define MG_U16_1Ohm_NTC_4_OTW_RESETPOINT    ((uint16)800U)    /* (Ohm) */
#define MG_F32_1s_NTC_4_OTW_DLY                      0.2F     /* (s) */

#define MG_B_NTC_1_OT                   TEMPCTRL_mg_uTempStatus.Bits.f0   /* 1 = NTC 1 OT */
#define MG_B_NTC_1_OTW                  TEMPCTRL_mg_uTempStatus.Bits.f1   /* 1 = NTC 1 OT warning */
#define MG_B_NTC_2_OT                   TEMPCTRL_mg_uTempStatus.Bits.f2   /* 1 = NTC 2 OT */
#define MG_B_NTC_2_OTW                  TEMPCTRL_mg_uTempStatus.Bits.f3   /* 1 = NTC 2 OT warning */
#define MG_B_NTC_3_OT                   TEMPCTRL_mg_uTempStatus.Bits.f4   /* 1 = NTC 3 OT */
#define MG_B_NTC_3_OTW                  TEMPCTRL_mg_uTempStatus.Bits.f5   /* 1 = NTC 3 OT warning */
#define MG_B_NTC_4_OT                   TEMPCTRL_mg_uTempStatus.Bits.f6   /* 1 = NTC 4 OT */
#define MG_B_NTC_4_OTW                  TEMPCTRL_mg_uTempStatus.Bits.f7   /* 1 = NTC 4 OT warning */

/***********************************************
 * Measurement settings
 **********************************************/ 
#define MG_U8_AVG_CTR                   ((uint8)32U)      /* 32 times averaging */

/*******************************************************************************
 * Scaling section
 ******************************************************************************/

#define MG_U16_100ms_NTC_1_OTP_DLY          (uint16)(MG_F32_1s_NTC_1_OTP_DLY * MG_100MS_TO_1S_FACT)     /* s * 10 (100ms * 10 = 1s) */
#define MG_U16_100ms_NTC_1_OTW_DLY          (uint16)(MG_F32_1s_NTC_1_OTW_DLY * MG_100MS_TO_1S_FACT)     /* s * 10 (100ms * 10 = 1s) */
#define MG_U16_100ms_NTC_2_OTP_DLY          (uint16)(MG_F32_1s_NTC_2_OTP_DLY * MG_100MS_TO_1S_FACT)     /* s * 10 (100ms * 10 = 1s) */
#define MG_U16_100ms_NTC_2_OTW_DLY          (uint16)(MG_F32_1s_NTC_2_OTW_DLY * MG_100MS_TO_1S_FACT)     /* s * 10 (100ms * 10 = 1s) */
#define MG_U16_100ms_NTC_3_OTP_DLY          (uint16)(MG_F32_1s_NTC_3_OTP_DLY * MG_100MS_TO_1S_FACT)     /* s * 10 (100ms * 10 = 1s) */
#define MG_U16_100ms_NTC_3_OTW_DLY          (uint16)(MG_F32_1s_NTC_3_OTW_DLY * MG_100MS_TO_1S_FACT)     /* s * 10 (100ms * 10 = 1s) */
#define MG_U16_100ms_NTC_4_OTP_DLY          (uint16)(MG_F32_1s_NTC_4_OTP_DLY * MG_100MS_TO_1S_FACT)     /* s * 10 (100ms * 10 = 1s) */
#define MG_U16_100ms_NTC_4_OTW_DLY          (uint16)(MG_F32_1s_NTC_4_OTW_DLY * MG_100MS_TO_1S_FACT)     /* s * 10 (100ms * 10 = 1s) */


#ifdef __cplusplus
  }
#endif
#endif  /* TEMPCTRL_CONF_H */

  
/*
 * End of file
 */
