/** *****************************************************************************
 * \file    i2cprt_scfg.h
 * \brief   Server request service file for i2cprt.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-07-19 09:17:10 +0800 (Fri, 19 Jul 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 200 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef I2CPRT_SCFG_H
#define I2CPRT_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>
#include "global.h"
#include "i2c_api.h"		
#include "i2c_cfg.h"
#include "crc_api.h"
#include "pmbus_api.h"
		
#define MG_I2C_TX_DATA_REG         I2C1->TXDR                   /* TX register */
#define MG_I2C_RX_DATA_REG         I2C1->RXDR                   /* RX register */
		
SINLINE uint8 I2CPRT_SCFG_u8ReadData(void)
{
	return (I2C1->RXDR);
}

SINLINE void I2CPRT_SCFG_u8WriteData(uint8 u8Data)
{
	I2C1->TXDR = u8Data;
}
		
SINLINE void I2CPRT_SCFG_vClearTimeoutCnt(void)
{
	I2C_vClearTimeoutCnt(I2C_CFG_E_INDEX_PMBUS);
}
		
SINLINE ITStatus I2CPRT_SCFG_eGetRxNEFlg(void)
{
	return I2C_GetITStatus(I2C1,I2C_IT_RXNE);
}

SINLINE ITStatus I2CPRT_SCFG_eGetTxISFlg(void)
{
	return I2C_GetITStatus(I2C1,I2C_IT_TXIS);
}

SINLINE ITStatus I2CPRT_SCFG_eGetRxOVRFlg(void)
{
	return I2C_GetITStatus(I2C1, I2C_IT_OVR); /* RX register overrun error */
}

SINLINE void I2CPRT_SCFG_vClearRxOVRFlg(void)
{
	 I2C_ClearITPendingBit(I2C1, I2C_IT_OVR); /* RX register clear overrun error */
}

SINLINE ITStatus I2CPRT_SCFG_eGetRxARLOFlg(void)
{
	return I2C_GetITStatus(I2C1, I2C_IT_ARLO); /* Arbitration lost error */
}

SINLINE void I2CPRT_SCFG_vClearRxARLOFlg(void)
{
	 I2C_ClearITPendingBit(I2C1, I2C_IT_ARLO); /* Clear Arbitration lost error */
}

SINLINE ITStatus I2CPRT_SCFG_eGetRxBERRFlg(void)
{
	return I2C_GetITStatus(I2C1, I2C_IT_BERR); /* Bus error */
}

SINLINE void I2CPRT_SCFG_vClearRxBERRFlg(void)
{
	 I2C_ClearITPendingBit(I2C1, I2C_IT_BERR); /* Clear Bus error */
}

SINLINE ITStatus I2CPRT_SCFG_eGetNACKFlg(void)
{
	return I2C_GetITStatus(I2C1, I2C_IT_NACKF); /* NACK error */
}

SINLINE void I2CPRT_SCFG_vClearNACKFlg(void)
{
	 I2C_ClearITPendingBit(I2C1, I2C_IT_NACKF); /* Clear NACK error */
}

SINLINE uint16 I2CPRT_SCFG_u16TransferDirection(void)
{
	 return I2C_GetTransferDirection(I2C1); /* I2C read operation */
}

SINLINE ITStatus I2CPRT_SCFG_eGetRxADDRFlg(void)
{
	return I2C_GetITStatus(I2C1, I2C_IT_ADDR); /* I2C received address byte  */
}

SINLINE void I2CPRT_SCFG_vClearRxADDRFlg(void)
{
	I2C_ClearITPendingBit(I2C1, I2C_IT_ADDR); /* I2C received address byte */
}

SINLINE void I2CPRT_SCFG_vDisableOAR1(void)
{
	I2C1->OAR1 &= ~I2C_OAR1_OA1EN; /* I2C disable own address */
}

SINLINE void I2CPRT_SCFG_vEnableOAR1(void)
{
	I2C1->OAR1 |= I2C_OAR1_OA1EN;  /* I2C enable own address */
}

SINLINE void I2CPRT_SCFG_vSetOAR1(uint32 u32Address)
{
	I2C1->OAR1 &= 0xFFFFFF00;  /* I2C enable own address */
	I2C1->OAR1 |= u32Address;  /* I2C change own addr */
}

SINLINE ITStatus I2CPRT_SCFG_eGetRxSTOPFlg(void)
{
	return I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF); /* I2C received stop flag  */
}

SINLINE void I2CPRT_SCFG_vClearRxSTOPFlg(void)
{
	I2C_ClearFlag(I2C1, I2C_FLAG_STOPF); /* clear I2C received stop flag */
}

SINLINE void I2CPRT_SCFG_vClearTxEFlg(void)
{
	I2C1->ISR |= I2C_FLAG_TXE; /* clear I2C tranfer empty flag */
}

SINLINE uint8 I2CPRT_SCFG_u8GetCrc8(uint8 u8InCrc, uint8 u8InData)
{
	return CRC_u8GetCrc8(u8InCrc,u8InData);
}

SINLINE void I2CPRT_SCFG_vCmdCheck(void)
{
  PMBUS_vCmdCheck();
}

SINLINE void I2CPRT_SCFG_vDisableInt(void)
{
	I2C_vDisableNvicInt((uint8)I2C_CFG_E_INDEX_PMBUS);
}

SINLINE void I2CPRT_SCFG_vEnableInt(void)
{
	I2C_vEnableNvicInt((uint8)I2C_CFG_E_INDEX_PMBUS);
}

SINLINE void I2CPRT_SCFG_vPMBusSendData(void)
{
	PMBUS_vSendData();
}

SINLINE void I2CPRT_SCFG_vPMBusHandleData(void)
{
	vPMBus_HandleData();
}

#ifdef __cplusplus
  }
#endif
#endif  /* I2C_SCFG_H */

  
/*
 * End of file
 */
