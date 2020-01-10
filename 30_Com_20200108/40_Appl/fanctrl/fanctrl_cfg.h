/** *****************************************************************************
 * \file    fanctrl_cfg.h
 * \brief   Server call back service file for fanctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-11-09 11:10:05 +0800 (Fri, 09 Nov 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 115 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef FANCATL_CFG_H
#define FANCATL_CFG_H
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
#include "fanctrl_conf.h"
/*******************************************************************************
 * Module interface
 ******************************************************************************/
/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/
 #ifdef FANCTRL_EXPORT_H
 #include "fanctrl_scfg.h"
 
/* The structure defining the setup of fan control  */
typedef struct
{	
  /* Read Fan speed I/O status  */
	uint8 (*u8ReadPinIoStatus)(void);  
	void  (*vSetFanCtrlPwmDuty)(uint16 u16Duty);
}tFanCtrlConf;

static const tFanCtrlConf FANCTRL_CFG_CONF[] =
{
/* Fan 1 */
{
  .u8ReadPinIoStatus   = FANCTRL_SCFG_u8RdFan1Status,
  .vSetFanCtrlPwmDuty  = FANCTRL_SCFG_vSetFan1Duty,
},
/* Fan 2*/
{
  .u8ReadPinIoStatus   = FANCTRL_SCFG_u8RdFan2Status,
  .vSetFanCtrlPwmDuty  = FANCTRL_SCFG_vSetFan2Duty
},
}; /* */
#endif

typedef enum FANCTRL_CFG_E_CONF_INDEX_
{
  FANCTRL_CFG_E_INDEX_FAN1 = 0,
  FANCTRL_CFG_E_INDEX_FAN2,
  FANCTRL_CFG_E_INDEX_COUNT
} FANCTRL_CFG_E_CONF_INDEX;

#ifdef __cplusplus
  }
#endif
#endif  /* FANCATL_CFG_H */

  
/*
 * End of file
 */
