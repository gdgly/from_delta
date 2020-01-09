/** *****************************************************************************
 * \file    timectrl_scfg.h
 * \brief   Server request service file for timectrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-15 18:06:30 +0800 (Wed, 15 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 13 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef TIMECATL_SCFG_H
#define TIMECATL_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "eeprom_api.h"
#include "crc_api.h"
#include "mem_conf.h"

SINLINE void TIMECATL_SCFG_vReadMem(uint8* pu8Buffer)
{
	(void)EEPROM_u32ReadBuffer(pu8Buffer,EEP_USED_MINUTES_LB, 5);
}

SINLINE void TIMECATL_SCFG_vReadMem_1(uint8* pu8Buffer)
{
	(void)EEPROM_u32ReadBuffer(pu8Buffer,EEP_USED_MINUTES_1_LB, 5);
}

SINLINE void TIMECATL_SCFG_vWriteMem(uint16 u16ReadAddr, const uint8* pu8Buffer,  uint16 u16NumByteToWrite)
{
	(void)EEPROM_u32WriteBuffer(pu8Buffer, u16ReadAddr,u16NumByteToWrite);
}

SINLINE uint8 TIMECATL_SCFG_u8GetCrc8(uint8 u8InCrc, uint8 u8InData)
{
	return CRC_u8GetCrc8(u8InCrc,u8InData);
}

SINLINE uint8 TIMECTRL_SCFG_u8IsEepromStandbyState()
{
  return TRUE;//(uint8)(EEPROM_u32WaitEepromStandbyState() == 0?1u:0U);
}



#ifdef __cplusplus
  }
#endif
#endif  /* TIMECATL_SCFG_H */

  
/*
 * End of file
 */
