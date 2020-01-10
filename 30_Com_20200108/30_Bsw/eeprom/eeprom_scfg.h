/** *****************************************************************************
 * \file    eeprom_scfg.h
 * \brief   Server request service file for eeprom.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef EEPROM_SCFG_H
#define EEPROM_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>
#include "global.h"
		
		
SINLINE void EEPROM_SCFG_vSetAutoEndMode(void)
{
	I2C2->CR2 |= I2C_CR2_AUTOEND;
}

SINLINE void EEPROM_SCFG_vSetSoftwareEndMode(void)
{
	I2C2->CR2 &= ~I2C_CR2_AUTOEND;
}

SINLINE void EEPROM_SCFG_vSetReloadMode(void)
{
	I2C2->CR2 |= I2C_CR2_RELOAD;
}

SINLINE void EEPROM_SCFG_vSetNoReloadMode(void)
{
	I2C2->CR2 &= ~I2C_CR2_RELOAD;
}

SINLINE void EEPROM_SCFG_vGenerateStart(void)
{
	I2C2->CR2 |= I2C_CR2_START;
}

SINLINE void EEPROM_SCFG_vGenerateStop(void)
{
	I2C2->CR2 |= I2C_CR2_STOP; 
}

SINLINE void EEPROM_SCFG_vSetMasterWr(void)
{
	I2C2->CR2 &= ~I2C_CR2_RD_WRN; 
}

SINLINE void EEPROM_SCFG_vSetMasterRd(void)
{
	I2C2->CR2 |= I2C_CR2_RD_WRN;
}

SINLINE uint8 EEPROM_SCFG_u8IsBusBusy(void)
{
	return ((I2C2->CR2&I2C_ISR_BUSY)==I2C_ISR_BUSY);
}





SINLINE ITStatus EEPROM_SCFG_eGetRxNEFlg(void)
{
	return I2C_GetITStatus(I2C2,I2C_IT_RXNE);
}

SINLINE ITStatus EEPROM_SCFG_eGetTxISFlg(void)
{
	return I2C_GetITStatus(I2C2, I2C_IT_TXIS);
}

SINLINE void EEPROM_SCFG_vSendData(uint8 u8Data)
{
	I2C_SendData(I2C2,u8Data);
}

SINLINE ITStatus EEPROM_SCFG_eGetTCFlg(void)
{
	return I2C_GetITStatus(I2C2, I2C_IT_TC); 
}

SINLINE void EEPROM_SCFG_vClearTCFlg(void)
{
	 I2C_ClearITPendingBit(I2C2, I2C_IT_TC);
}

SINLINE void EEPROM_SCFG_vNumberOfBytesConfig(uint8 u8NumberBytes)
{
	I2C_NumberOfBytesConfig(I2C2, u8NumberBytes);
}

SINLINE uint8 EEPROM_SCFG_u8ReceiveData(void)
{
	return I2C_ReceiveData(I2C2);
}


#ifdef __cplusplus
  }
#endif
#endif  /* EEPROM_SCFG_H */

  
/*
 * End of file
 */
