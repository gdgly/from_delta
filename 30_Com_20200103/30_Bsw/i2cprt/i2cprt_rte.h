/*******************************************************************************
 * \file    i2cprt_rte.h
 * \brief   RTE interface for i2cprt.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-23 15:34:14 +0800 (Thu, 23 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 14 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef I2CPRT_RTE_H
#define I2CPRT_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

#include "global.h"
#include "rte.h"
#include "pmbus_cfg.h"
/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/

/***********************************************
 * Input
 **********************************************/

/****  flag ******/
#define RTE_Read_B_R_CMD_WAIT_FLG          (RTE_I2C_CMD_WAIT_FLG)
#define RTE_Read_B_R_PEC_ERR_FLG           (RTE_I2C_PEC_ERR_FLG)
#define RTE_Read_B_R_PEC_CHANGE_FLG        (RTE_I2C_PEC_CHANGE_FLG)
#define RTE_Read_B_R_CMD_DETECTED          (RTE_I2C_CMD_DETECTED)
#define RTE_Read_B_R_I2C_ADDRESS0          (RTE_B_DIO_I2C_ADDRESS0)
#define RTE_Read_B_R_I2C_ADDRESS1          (RTE_B_DIO_I2C_ADDRESS1)
#define RTE_Read_B_R_I2C_ADDRESS2          (RTE_B_DIO_I2C_ADDRESS2)
#define RTE_Read_B_R_PEC_Enable            (RTE_bPEC_Enable)

/****  Variables ******/
#define Rte_Read_R_u8PMBusCmd(var)         ((**var) = RTE_u8PmbusCommand)
#define Rte_Read_R_u8PecErrCmd(var)        ((**var) = RTE_u8I2cPECErrCmd)
#define Rte_Read_R_u8I2cPEC(var)           ((**var) = RTE_u8I2cPEC)
#define Rte_Read_R_u8I2cTxLen(var)         ((**var) = RTE_u8I2cTxLen)
#define Rte_Read_R_u8I2cRxCnt(var)         ((**var) = RTE_u8I2cRxCnt)
#define Rte_Read_R_u8I2cExpRxCnt(var)      ((**var) = RTE_u8I2cExpRxCnt)

/***********************************************
 * Output
 **********************************************/

/****  flag ******/
#define RTE_Write_B_P_CMD_WAIT_FLG              (RTE_I2C_CMD_WAIT_FLG)
#define RTE_Write_B_P_PEC_ERR_FLG               (RTE_I2C_PEC_ERR_FLG)
#define RTE_Write_B_P_PEC_CHANGE_FLG            (RTE_I2C_PEC_CHANGE_FLG)
#define RTE_Write_B_P_CMD_DETECTED              (RTE_I2C_CMD_DETECTED)
#define RTE_Write_B_P_PMBUS_PEC_FAULT           (PMBUS_tStatus.u8StatusCmlP0.Bits.PEC_FAULT) 
 
/****  Variables ******/
#define Rte_Write_P_u8PecErrCmd                 (RTE_u8I2cPECErrCmd)
#define Rte_Write_P_u8I2cPEC                    (RTE_u8I2cPEC)
#define Rte_Write_P_u8I2cTxLen                  (RTE_u8I2cTxLen)
#define Rte_Write_P_u8I2cRxCnt                  (RTE_u8I2cRxCnt)
#define Rte_Write_P_u8I2cExpTxCnt               (RTE_u8I2cExpTxCnt)
#define Rte_Write_P_u8I2cExpRxCnt               (RTE_u8I2cExpRxCnt)


/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/



/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
SINLINE uint8 I2CPRT_RTE_Read_B_R_I2C_ADDRESS0(void)
{
	return RTE_Read_B_R_I2C_ADDRESS0;
}

SINLINE uint8 I2CPRT_RTE_Read_B_R_I2C_ADDRESS1(void)
{
	return RTE_Read_B_R_I2C_ADDRESS1;
}

SINLINE uint8 I2CPRT_RTE_Read_B_R_I2C_ADDRESS2(void)
{
	return RTE_Read_B_R_I2C_ADDRESS2;
}

SINLINE uint8 I2CPRT_RTE_Read_B_R_CMD_WAIT_FLG(void)
{
	return RTE_Read_B_R_CMD_WAIT_FLG;
}

SINLINE uint8 I2CPRT_RTE_Read_B_R_PEC_ERR_FLG(void)
{
	return RTE_Read_B_R_PEC_ERR_FLG;
}

SINLINE uint8 I2CPRT_RTE_Read_B_R_PEC_CHANGE_FLG(void)
{
	return RTE_Read_B_R_PEC_CHANGE_FLG;
}

SINLINE uint8 I2CPRT_RTE_Read_B_R_CMD_DETECTED(void)
{
	return RTE_Read_B_R_CMD_DETECTED;
}

SINLINE uint8 I2CPRT_RTE_Read_B_R_PEC_Enable(void)
{
	return RTE_Read_B_R_PEC_Enable;
}


SINLINE void I2CPRT_Rte_Read_R_u8PMBusCmd(uint8 *var)
{
	Rte_Read_R_u8PMBusCmd(&var);
}

SINLINE void I2CPRT_Rte_Read_R_u8PecErrCmd(uint8 *var)
{
	Rte_Read_R_u8PecErrCmd(&var);
}

SINLINE void I2CPRT_Rte_Read_R_u8I2cPEC(uint8 *var)
{
	Rte_Read_R_u8I2cPEC(&var);
}

SINLINE void I2CPRT_Rte_Read_R_u8I2cTxLen(uint8 *var)
{
	Rte_Read_R_u8I2cTxLen(&var);
}

SINLINE void I2CPRT_Rte_Read_R_u8I2cRxCnt(uint8 *var)
{
	Rte_Read_R_u8I2cRxCnt(&var);
}

SINLINE void I2CPRT_Rte_Read_R_u8I2cExpRxCnt(uint8 *var)
{
	Rte_Read_R_u8I2cExpRxCnt(&var);
}

SINLINE uint8 I2CPRT_Rte_Read_R_u8TxBuf(uint8 u8Index)
{
	return RTE_au8I2cTxBuf[u8Index];
}



/* Write */
SINLINE void I2CPRT_RTE_Write_B_P_CMD_WAIT_FLG(uint8 u8Status)
{
	RTE_Write_B_P_CMD_WAIT_FLG = u8Status;
}

SINLINE void I2CPRT_RTE_Write_B_P_PEC_ERR_FLG(uint8 u8Status)
{
	RTE_Write_B_P_PEC_ERR_FLG = u8Status;
}

SINLINE void I2CPRT_RTE_Write_B_P_PEC_CHANGE_FLG(uint8 u8Status)
{
	RTE_Write_B_P_PEC_CHANGE_FLG = u8Status;
}

SINLINE void I2CPRT_RTE_Write_B_P_CMD_DETECTED(uint8 u8Status)
{
	RTE_Write_B_P_CMD_DETECTED = u8Status;
}

SINLINE void I2CPRT_RTE_Write_B_P_PMBUS_PEC_FAULT(uint8 u8Status)
{
	RTE_Write_B_P_PMBUS_PEC_FAULT = u8Status;
}

SINLINE void I2CPRT_Rte_Write_P_u8PecErrCmd(uint8 u8Data)
{
	Rte_Write_P_u8PecErrCmd = u8Data;
}

SINLINE void I2CPRT_Rte_Write_P_u8I2cPEC(uint8 u8Data)
{
	Rte_Write_P_u8I2cPEC = u8Data;
}

SINLINE void I2CPRT_Rte_Write_P_u8I2cTxLen(uint8 u8Data)
{
	Rte_Write_P_u8I2cTxLen = u8Data;
}

SINLINE void I2CPRT_Rte_Write_P_u8I2cRxCnt(uint8 u8Data)
{
	Rte_Write_P_u8I2cRxCnt = u8Data;
}

SINLINE void I2CPRT_Rte_Write_P_u8I2cExpTxCnt(uint8 u8Data)
{
	Rte_Write_P_u8I2cExpTxCnt = u8Data;
}

SINLINE void I2CPRT_Rte_Write_P_u8I2cExpRxCnt(uint8 u8Data)
{
	Rte_Write_P_u8I2cExpRxCnt = u8Data;
}

SINLINE void I2CPRT_Rte_Write_P_u8TxBuf(uint8 u8Data,uint8 u8Index)
{
	RTE_au8I2cTxBuf[u8Index] = u8Data;
}




#ifdef __cplusplus
  }
#endif
#endif  /* I2CPRT_RTE_H */

  
/*
 * End of file
 */
