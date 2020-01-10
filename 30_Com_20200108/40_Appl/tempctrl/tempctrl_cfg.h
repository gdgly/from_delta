/** *****************************************************************************
 * \file    tempctrl_cfg.h
 * \brief   Server call back service file for tempctr.c
 *
 * \section AUTHOR
 *    1. Jeff.Zhou
 *
 * \section SVN
 *  $Date: 2019-10-31 15:53:09 +0800 (Thu, 31 Oct 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 237 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef TEMPCTRL_CFG_H
#define TEMPCTRL_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/
 #ifdef TEMPCTRL_EXPORT_H
 #include "tempctrl_rte.h"
 #include "tempctrl_scfg.h"
 #include "tempctrl_conf.h"
    
/* The structure defining the setup of tempareture control  */
typedef struct
{
  /* OTP set point */
  sint16 s16OTPSetPoint;
  
  /* OTP reset point */
  sint16 s16OTPResetPoint;
  
  /* OTW set point */
  sint16 s16OTWSetPoint;
  
  /* OTW reset point */
  sint16 s16OTWResetPoint;
  
  /* OTP delay time */
  uint16 u16OTPDlyTime;
  
  /* OTW delay time */
  uint16 u16OTWDlyTime;
  
  /* Diff by Fan fail */
  sint16 s16DiffByFanFail;
	
  /* Read NTC Adc value */
	uint16 (*u16ReadAdcValue)(void);  
	
}tTempCtrlConf;

static const tTempCtrlConf TEMPCTRL_CFG_CONF[] =
{
/* Inlet NTC */
{
  .s16OTPSetPoint   = MG_U16_NTC_COM_INLET_OTP_SETPOINT,
  .s16OTPResetPoint = MG_U16_NTC_COM_INLET_OTP_RESETPOINT,
  .s16OTWSetPoint   = MG_U16_NTC_COM_INLET_OTW_SETPOINT,
  .s16OTWResetPoint = MG_U16_NTC_COM_INLET_OTW_RESETPOINT,
  .u16OTPDlyTime    = MG_U16_NTC_OTP_DLY,
  .u16OTWDlyTime    = MG_U16_NTC_OTW_DLY,
  .s16DiffByFanFail = 0,
  .u16ReadAdcValue  = TEMPCTRL_SCFG_u16ReadInletNtc
},
/* Outlet NTC */
{
	.s16OTPSetPoint   = MG_U16_NTC_COM_OUTLET_OTP_SETPOINT,
  .s16OTPResetPoint = MG_U16_NTC_COM_OUTLET_OTP_RESETPOINT,
  .s16OTWSetPoint   = MG_U16_NTC_COM_OUTLET_OTW_SETPOINT,
  .s16OTWResetPoint = MG_U16_NTC_COM_OUTLET_OTW_RESETPOINT,
  .u16OTPDlyTime    = MG_U16_NTC_OTP_DLY,
  .u16OTWDlyTime    = MG_U16_NTC_OTW_DLY,
  .s16DiffByFanFail = 0,
  .u16ReadAdcValue  = TEMPCTRL_SCFG_u16ReadOutletNtc
},
/* PFC NTC */
{
  .s16OTPSetPoint   = MG_U16_NTC_PRI_PFC_OTP_SETPOINT,
  .s16OTPResetPoint = MG_U16_NTC_PRI_PFC_OTP_RESETPOINT,
  .s16OTWSetPoint   = MG_U16_NTC_PRI_PFC_OTW_SETPOINT,
  .s16OTWResetPoint = MG_U16_NTC_PRI_PFC_OTW_RESETPOINT,
  .u16OTPDlyTime    = MG_U16_NTC_OTP_DLY,
  .u16OTWDlyTime    = MG_U16_NTC_OTW_DLY,
  .s16DiffByFanFail = MG_CONF_DIFF_BY_FAN_FAIL,
  .u16ReadAdcValue  = TEMPCTRL_Rte_Read_R_u161mVPfcNtc
},
/* LLC NTC */
{
  .s16OTPSetPoint   = MG_U16_NTC_PRI_LLC_OTP_SETPOINT,
  .s16OTPResetPoint = MG_U16_NTC_PRI_LLC_OTP_RESETPOINT,
  .s16OTWSetPoint   = MG_U16_NTC_PRI_LLC_OTW_SETPOINT,
  .s16OTWResetPoint = MG_U16_NTC_PRI_LLC_OTW_RESETPOINT,
  .u16OTPDlyTime    = MG_U16_NTC_OTP_DLY,
  .u16OTWDlyTime    = MG_U16_NTC_OTW_DLY,
  .s16DiffByFanFail = MG_CONF_DIFF_BY_FAN_FAIL,
  .u16ReadAdcValue  = TEMPCTRL_Rte_Read_R_u161mVLlcNtc
},
/* RECDIODE NTC */
{
  .s16OTPSetPoint   = MG_U16_NTC_SEC_RECDIO_OTP_SETPOINT,
  .s16OTPResetPoint = MG_U16_NTC_SEC_RECDIO_OTP_RESETPOINT,
  .s16OTWSetPoint   = MG_U16_NTC_SEC_RECDIO_OTW_SETPOINT,
  .s16OTWResetPoint = MG_U16_NTC_SEC_RECDIO_OTW_RESETPOINT,
  .u16OTPDlyTime    = MG_U16_NTC_OTP_DLY,
  .u16OTWDlyTime    = MG_U16_NTC_OTW_DLY,
  .s16DiffByFanFail = MG_CONF_DIFF_BY_FAN_FAIL,
  .u16ReadAdcValue  = TEMPCTRL_Rte_Read_R_u161mVSrNtc
},

}; /* */
#endif

typedef enum TEMPCTRL_CFG_E_CONF_INDEX_
{
  TEMPCTRL_CFG_E_INDEX_INLET = 0,
	TEMPCTRL_CFG_E_INDEX_OUTLET,
  TEMPCTRL_CFG_E_INDEX_PFC,
  TEMPCTRL_CFG_E_INDEX_LLC,
  TEMPCTRL_CFG_E_INDEX_RECDIO,
  TEMPCTRL_CFG_E_INDEX_COUNT
} TEMPCTRL_CFG_E_CONF_INDEX;

#ifdef __cplusplus
  }
#endif
#endif  /* TEMPCTRL_CFG_H */

  
/*
 * End of file
 */
