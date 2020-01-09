/** *****************************************************************************
 * \file    tempctrl_scfg.h
 * \brief   Server request service file for tempctrl.c
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

#ifndef TEMPCTRL_SCFG_H
#define TEMPCTRL_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "adc_api.h"
#include "buffer_cfg.h"
#include "buffer_api.h"
#include "fanctrl_api.h"

static uint16 mg_u16Ret;

SINLINE uint16 TEMPCTRL_SCFG_u16ReadInletNtc(void)
{
	ADC_vReadRaw(ADC_CFG_E_INDEX_PA0_AIN0_INTC, &mg_u16Ret);
  
  return mg_u16Ret;
}

SINLINE uint16 TEMPCTRL_SCFG_u16ReadPoutV1Avg(void)
{
  return BUFFER_u16GetMean10ms(BUFFER_CFG_E_P1);
}

SINLINE uint8 TEMPCTRL_SCFG_u8ReadFanBitFail(void)
{
 return (FANCTRL_u8ReadFanBitFail(0) || FANCTRL_u8ReadFanBitFail(1));
}

#ifdef __cplusplus
  }
#endif
#endif  /* TEMPCTRL_SCFG_H */

  
/*
 * End of file
 */
