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



SINLINE void LEDCTRL_SCFG_vSetInGREOn(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_A9_LED_GRE, TRUE);
}

SINLINE void LEDCTRL_SCFG_vSetInGREOff(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_A9_LED_GRE, FALSE);
}

SINLINE void LEDCTRL_SCFG_vSetInGREToggle(void)
{
	PORT_vSetGpioPinToggle(PORT_CFG_E_A9_LED_GRE);
}

SINLINE void LEDCTRL_SCFG_vSetInREDOn(void)
{
	PORT_vSetGpioPin(PORT_CFG_E_A10_LED_RED, TRUE);
}

SINLINE void LEDCTRL_SCFG_vSetInREDOff(void)
{
  PORT_vSetGpioPin(PORT_CFG_E_A10_LED_RED, FALSE);
}

SINLINE void LEDCTRL_SCFG_vSetInREDToggle(void)
{
	PORT_vSetGpioPinToggle(PORT_CFG_E_A10_LED_RED);
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
