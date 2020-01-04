/** *****************************************************************************
 * \file    mem_scfg.h
 * \brief   Server request service file for mem.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-09-13 20:02:04 +0800 (Thu, 13 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 30 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef MEM_SCFG_H
#define MEM_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/


#include "eeprom_api.h"
#include "crc_api.h"
#include "pwm_api.h"
#include "pwm_cfg.h"	
#include "flash_api.h"
		
		
SINLINE void MEM_SCFG_vReadMem(uint8* pu8Buffer, uint16 u16ReadAddr, uint16 u16NumByteToRead)
{
	(void)EEPROM_u32ReadBuffer(pu8Buffer, u16ReadAddr,u16NumByteToRead);
}

SINLINE void MEM_SCFG_vWriteMem(uint16 u16ReadAddr, const uint8* pu8Buffer,  uint16 u16NumByteToWrite)
{
	(void)EEPROM_u32WriteBuffer(pu8Buffer, u16ReadAddr,u16NumByteToWrite);
}

SINLINE uint8 MEM_SCFG_u8GetCrc8(uint8 u8InCrc, uint8 u8InData)
{
	return CRC_u8GetCrc8(u8InCrc,u8InData);
}
		
SINLINE void MEM_SCFG_vVsbTrimDuty(uint16 u16Duty)
{
	PWM_vPwmDutyUpdate(PWM_CFG_E_INDEX_PWM_Vsb_Trim,u16Duty);
}

SINLINE uint8 MEM_SCFG_u8IsEepromStandbyState()
{
  return TRUE;//(uint8)(EEPROM_u32WaitEepromStandbyState() == 0?1u:0U);
}

SINLINE uint32 MEM_SCFG_u32ReadBootloaderFwVer()
{
  return FLASH_u32BootloaderFwVer();
}


#ifdef __cplusplus
  }
#endif
#endif  /* MEM_SCFG_H */

  
/*
 * End of file
 */
