/** *****************************************************************************
 * \file    ledctrl_scfg.h
 * \brief   Server request service file for ledctrl.c
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

#ifndef LEDCTRL_SCFG_H
#define LEDCTRL_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "port_cfg.h"
#include "port_api.h"
#include "fanctrl_api.h"
		
		
SINLINE void LEDCTRL_SCFG_vSetInOKOn(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_C14_LED_AC_OK,TRUE);
}

SINLINE void LEDCTRL_SCFG_vSetInOKOff(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_C14_LED_AC_OK,FALSE);
}

SINLINE void LEDCTRL_SCFG_vSetInOKToggle(void)
{
  PORT_vSetGpioPinToggle(PORT_CFG_E_C14_LED_AC_OK);
}

SINLINE void LEDCTRL_SCFG_vSetOutOKOn(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_C13_LED_DC_OK,TRUE);
}

SINLINE void LEDCTRL_SCFG_vSetOutOKOff(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_C13_LED_DC_OK,FALSE);
}

SINLINE void LEDCTRL_SCFG_vSetOutOKToggle(void)
{
  PORT_vSetGpioPinToggle(PORT_CFG_E_C13_LED_DC_OK);
}

SINLINE void LEDCTRL_SCFG_vSetFailAmberOn(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_C15_LED_FAULT,TRUE);
}

SINLINE void LEDCTRL_SCFG_vSetFailAmberOff(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_C15_LED_FAULT,FALSE);
}

SINLINE void LEDCTRL_SCFG_vSetFailAmberToggle(void)
{
  PORT_vSetGpioPinToggle(PORT_CFG_E_C15_LED_FAULT);
}

SINLINE uint8 LEDCTRL_SCFG_u8ReadFanBitFail(void)
{
 return (FANCTRL_u8ReadFanBitFail(0) || FANCTRL_u8ReadFanBitFail(1));
}




#ifdef __cplusplus
  }
#endif
#endif  /* LEDCTRL_SCFG_H */

  
/*
 * End of file
 */
