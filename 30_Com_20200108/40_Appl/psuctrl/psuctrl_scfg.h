/** *****************************************************************************
 * \file    psuctrl_scfg.h
 * \brief   Server request service file for psuctrl.c
 *
 * \section AUTHOR
 *    1. jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-11-06 15:17:49 +0800 (Tue, 06 Nov 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 104 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PSUCTRL_SCFG_H
#define PSUCTRL_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "pwm_api.h"
#include "pwm_cfg.h"	
#include "port_api.h"
#include "port_cfg.h"		
#include "global.h"
#include "monctrl_api.h"
#include "psuctrl_rte.h"
#include "pmbus_api.h"
		
SINLINE void PSUCTRL_SCFG_vVsbTrimDuty(uint16 u16Duty)
{
	PWM_vPwmDutyUpdate(PWM_CFG_E_INDEX_PWM_Vsb_Adj,u16Duty);
}

SINLINE void PSUCTRL_SCFG_vVsbOvpDuty(uint16 u16Duty)
{
	PWM_vPwmDutyUpdate(PWM_CFG_E_INDEX_PWM_Vsb_Adj,u16Duty);
}

SINLINE void PSUCTRL_SCFG_vSetVsbOvpPwmOut(uint8 u8State)
{
  if(FALSE == u8State)
  {
	  PORT_vSetGpioMode(PORT_CFG_E_A4_VSB_ADJ,PORT_CFG_E_GPIO_MODE_OUT);
    PORT_vSetGpioPin(PORT_CFG_E_A4_VSB_ADJ,TRUE);
  }
  else
  {
	  PORT_vSetGpioMode(PORT_CFG_E_A4_VSB_ADJ,PORT_CFG_E_GPIO_MODE_AF);
  }
}

SINLINE void PSUCTRL_SCFG_vSyncIntSetOn(uint8 u8Status)
{
	PORT_vSetGpioPin(PORT_CFG_E_B12_SYNC_INTERNAL,u8Status);
	PSUCTRL_Rte_Write_B_P_SYNC_INTERNAL_ON(u8Status);
}

SINLINE void PSUCTRL_SCFG_vVsbSetOn(uint8 u8Status)
{
  if(u8Status == TRUE)
  {
    PORT_vSetGpioPin(PORT_CFG_E_B2_VSB_OFF,FALSE);
    PORT_vSetGpioMode(PORT_CFG_E_B2_VSB_OFF,PORT_CFG_E_GPIO_MODE_OUT);
  }
  else
  {
    PORT_vSetGpioMode(PORT_CFG_E_B2_VSB_OFF,PORT_CFG_E_GPIO_MODE_IN);
  }
	PSUCTRL_Rte_Write_B_P_VSB_ON(u8Status);
}

SINLINE void PSUCTRL_SCFG_vClearAllFault(void)
{
	PMBUS_vClearAllFault();
}

SINLINE void PSUCTRL_SCFG_vClearPowerOffFault(void)
{
	PMBUS_vClearPowerOffFault();
}


#ifdef __cplusplus
  }
#endif
#endif  /* PSUCTRL_SCFG_H */

  
/*
 * End of file
 */
