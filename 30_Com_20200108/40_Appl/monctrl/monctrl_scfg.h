/** *****************************************************************************
 * \file    monctrl_scfg.h
 * \brief   Server request service file for monctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-09-09 17:59:22 +0800 (Mon, 09 Sep 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 229 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef MONCATL_SCFG_H
#define MONCATL_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"
#include "psuctrl_api.h"		
#include "pmbus_api.h"	
#include "buffer_cfg.h"
#include "buffer_api.h"		
#include "adc_api.h"
#include "rte.h"
#include "pwm_api.h"
#include "pwm_cfg.h"
#include "port_cfg.h"   
#include "port_api.h"  
#include "pmbus_scb.h"    

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

SINLINE void MONCTRL_SCFG_vClearAllFault(void)
{
	PMBUS_vClearAllFault();
}
SINLINE uint16 MONCTRL_SCFG_u16GetVsbIntVoltAvg(void)
{
	return BUFFER_u16GetMean1ms(BUFFER_CFG_E_IntVsb);
}

SINLINE uint16 MONCTRL_SCFG_u16GetIsb(void)
{
  uint16 u16Data;
  ADC_vReadRaw(ADC_CFG_E_INDEX_PA6_AIN6_IVsb, &u16Data);
  u16Data= (uint16)(((uint32)u16Data * RTE_U16_1mA_I_VSB_SCALE_FACT)>>12);
  u16Data = (uint16)(((uint32)u16Data * RTE_CALI_sData.sIoutVsb[CALI_I_VSB_LINE_NUM -1u].s16Amp + 4096) >> 13);
	return u16Data;
}

SINLINE uint16 MONCTRL_SCFG_u16GetVsbExtVolt10mVAvg(void)
{
	return BUFFER_u16GetMean1ms(BUFFER_CFG_E_ExtVsb);
}

SINLINE void MONCTRL_SCFG_vVsbOvpDuty(uint16 u16Duty)
{
	PWM_vPwmDutyUpdate(PWM_CFG_E_INDEX_PWM_Vsb_Adj,u16Duty);
}


SINLINE void MONCTRL_SCFG_vSetVsbOvpPwmOut(uint8 u8State)
{
#if 0 /* nokia has no Vsb ovp test pin */
  if(FALSE == u8State)
  {
	  PORT_vSetGpioMode(PORT_CFG_E_A4_VSB_ADJ,PORT_CFG_E_GPIO_MODE_OUT);
    PORT_vSetGpioPin(PORT_CFG_E_A4_VSB_ADJ,TRUE);
  }
  else
  {
	  PORT_vSetGpioMode(PORT_CFG_E_A4_VSB_ADJ,PORT_CFG_E_GPIO_MODE_AF);
  }
#endif
}


inline void MONCTRL_cfg_vBlackBoxVinSaveData2Buff(void)
{
  PMBUS_vSaveBlackBoxVinData2Buff();
}

#ifdef __cplusplus
  }
#endif
#endif  /* MONCATL_SCFG_H */

  
/*
 * End of file
 */
