/** *****************************************************************************
 * \file    tempctrl_conf.h
 * \brief   Configurations file for tempctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-07-08 11:37:14 +0800 (Mon, 08 Jul 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 196 $
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
/* COM OUTLET */
#define MG_U16_NTC_COM_OUTLET_OTP_SETPOINT       ((sint16)70)
#define MG_U16_NTC_COM_OUTLET_OTP_RESETPOINT     ((sint16)55)
#define MG_U16_NTC_COM_OUTLET_OTW_SETPOINT       ((sint16)65)
#define MG_U16_NTC_COM_OUTLET_OTW_RESETPOINT     ((sint16)55)
 
/* COM INLET */
#define MG_U16_NTC_COM_INLET_OTP_SETPOINT       ((sint16)70)
#define MG_U16_NTC_COM_INLET_OTP_RESETPOINT     ((sint16)55)
#define MG_U16_NTC_COM_INLET_OTW_SETPOINT       ((sint16)RTE_AMB_OT_WARN_LIMIT)
#define MG_U16_NTC_COM_INLET_OTW_RESETPOINT     ((sint16)55)    

/* PRI1 PFC */
#define MG_U16_NTC_PRI_PFC_OTP_SETPOINT         ((sint16)125)
#define MG_U16_NTC_PRI_PFC_OTP_RESETPOINT       ((sint16)105)
#define MG_U16_NTC_PRI_PFC_OTW_SETPOINT         ((sint16)120)
#define MG_U16_NTC_PRI_PFC_OTW_RESETPOINT       ((sint16)105)

/* SEC1 SR */
#define MG_U16_NTC_SEC_SR_OTP_SETPOINT          ((sint16)125)
#define MG_U16_NTC_SEC_SR_OTP_RESETPOINT        ((sint16)105)
#define MG_U16_NTC_SEC_SR_OTW_SETPOINT          ((sint16)120)
#define MG_U16_NTC_SEC_SR_OTW_RESETPOINT        ((sint16)105)

/* SEC1 Oring */
#define MG_U16_NTC_SEC_ORING_OTP_SETPOINT       ((sint16)125)
#define MG_U16_NTC_SEC_ORING_OTP_RESETPOINT     ((sint16)105)
#define MG_U16_NTC_SEC_ORING_OTW_SETPOINT       ((sint16)120)
#define MG_U16_NTC_SEC_ORING_OTW_RESETPOINT     ((sint16)105)

#define MG_U16_NTC_OTP_DLY                      ((uint16)50U)  /* N*7*10ms */
#define MG_U16_NTC_OTW_DLY                      ((uint16)50U)  /* N*7*10ms */

#define MG_U16Q10_NTC_ADC_0C                    ((uint16)947U)
#define MG_U16Q10_NTC_ADC_MINUS_10C             ((uint16)974U)

#define MG_CONF_TEMP_COMP_LINE_MAX              (4u)

#define MG_CONF_DIFF_BY_FAN_FAIL                (15)

static const sint32 MG_S32_TEMP_COMP_K[4][MG_CONF_TEMP_COMP_LINE_MAX]=
{
  {-109,-164,-164,-218},
  {-109,-164,0,109},
  {1420,655,164,983},
  {109,-328,-328,-546}
};
static const sint32 MG_S32_TEMP_COMP_B[4][MG_CONF_TEMP_COMP_LINE_MAX]=
{
  {-262144,-196608,-196608,-43690},
  {-393216,-65536,-393216,-699051},
  {393216,1310720,2293760,0},
  {-1572864,-1048576,-1048576,-436907}
};
static const uint32 MG_U32_TEMP_COMP_THD[MG_CONF_TEMP_COMP_LINE_MAX]=
{
  1200,2000,2800,65535
};
#ifdef __cplusplus
  }
#endif
#endif  /* RTC_CONF_H */


/*
 * End of file
 */
