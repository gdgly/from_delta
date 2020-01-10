/** *****************************************************************************
 * \file    fanctrl_scfg.h
 * \brief   Server request service file for fanctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-05-08 09:09:27 +0800 (Wed, 08 May 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 179 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef FANCTRL_SCFG_H
#define FANCTRL_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "port_cfg.h"
#include "port_api.h"
#include "pwm_cfg.h"
#include "pwm_api.h"
#include "tempctrl_cfg.h"
#include "tempctrl_api.h"
#include "buffer_cfg.h"
#include "buffer_api.h"
    
SINLINE uint8 FANCTRL_SCFG_u8RdFan1Status(void)
{
	return 0;
}

SINLINE uint8 FANCTRL_SCFG_u8RdFan2Status(void)
{
	return 0;
}

SINLINE uint8 FANCTRL_SCFG_u8RdFan3Status(void)
{
	return 0;  /* Todo if need */
}

SINLINE uint8 FANCTRL_SCFG_u8RdFan4Status(void)
{
	return 0; /* Todo if need */
}

SINLINE void FANCTRL_SCFG_vSetFan1Duty(uint16 u16Duty)
{
	;
}
SINLINE void FANCTRL_SCFG_vSetFan2Duty(uint16 u16Duty)
{
	;
}

SINLINE void FANCTRL_SCFG_vReadAmbTemp(sint32 *var)
{
  *var = TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_INLET);
}

SINLINE sint16 FANCTRL_SCFG_s16ReadAmbTemp(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_INLET);
}

SINLINE sint16 FANCTRL_SCFG_s16ReadOutTemp(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_OUTLET);
}

SINLINE sint16 FANCTRL_SCFG_s16ReadPriPfc(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_PFC);
}

SINLINE sint16 FANCTRL_SCFG_s16ReadPriLlc(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_LLC);
}

SINLINE sint16 FANCTRL_SCFG_s16ReadSecRecdiode(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_RECDIO);
}

SINLINE uint16 FANCTRL_SCFG_u16ReadPoutV1Avg(void)
{
  return BUFFER_u16GetMean10ms(BUFFER_CFG_E_P1);
}


#ifdef __cplusplus
  }
#endif
#endif  /* FANCTRL_SCFG_H */



  
/*
 * End of file
 */
