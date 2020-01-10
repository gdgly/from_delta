/** *****************************************************************************
 * \file    cali_scfg.h
 * \brief   Server request service file for cali.c
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

#ifndef CALI_SCFG_H
#define CALI_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "eeprom_api.h"
#include "crc_api.h"
#include "buffer_cfg.h"
#include "buffer_api.h"
#include "adc_api.h"
#include "rte.h"

SINLINE void CALI_SCFG_vReadMem(uint8* pu8Buffer, uint16 u16ReadAddr, uint16 u16NumByteToRead)
{
	(void)EEPROM_u32ReadBuffer(pu8Buffer, u16ReadAddr,u16NumByteToRead);
}

SINLINE void CALI_SCFG_vWriteMem(uint16 u16ReadAddr, const uint8* pu8Buffer,  uint16 u16NumByteToWrite)
{
	(void)EEPROM_u32WriteBuffer(pu8Buffer, u16ReadAddr,u16NumByteToWrite);
}

SINLINE uint8 CALI_SCFG_u8IsEepromStandbyState()
{
  return (uint8)(EEPROM_u32WaitEepromStandbyState() == 0?1u:0U);
}

SINLINE uint8 CALI_SCFG_u8GetCrc8(uint8 u8InCrc, uint8 u8InData)
{
	return CRC_u8GetCrc8(u8InCrc,u8InData);
}

SINLINE uint16 CALI_SCFG_u16GetVsbIntVoltAvg(void)
{
	return BUFFER_u16GetMean1ms(BUFFER_CFG_E_IntVsb);
}

SINLINE uint16 CALI_SCFG_u16GetVsbCurrAvg(void)
{
	return BUFFER_u16GetMean1ms(BUFFER_CFG_E_Isb);
}
SINLINE void CALI_SCFG_vGetVsbIntVolt(uint16 *pData)
{
	ADC_vReadRaw(ADC_CFG_E_INDEX_PA5_AIN5_IntVsb, pData);
	*pData = (uint16)(((uint32)*pData * RTE_U16_10mV_V_VSB_INT_SCALE_FACT)>>12);
}

SINLINE void CALI_SCFG_vGetVsbCurr(uint16 *pData)
{
	ADC_vReadRaw(ADC_CFG_E_INDEX_PA6_AIN6_IVsb, pData);
	*pData = (uint16)(((uint32)*pData * RTE_U16_1mA_I_VSB_SCALE_FACT)>>12);
}


#ifdef __cplusplus
  }
#endif
#endif  /* CALI_SCFG_H */

  
/*
 * End of file
 */
