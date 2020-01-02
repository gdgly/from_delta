/** *****************************************************************************
 * \file    i2cprt_cfg.h
 * \brief   Server call back service file for i2cprt.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
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

#ifndef I2CPRT_CFG_H
#define I2CPRT_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "i2c_cfg.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/
		
#define I2CPRT_CFG_BASE_SLA_ADR        I2C_CFG_I2C1_BASE_SLA_ADR	
		
#define I2CPRT_CFG_I2C_DEFAULT_VAL        0xffu
		
#define I2CPRT_CFG_vI2cIsr             I2C1_IRQHandler

typedef enum I2CPRT_CFG_E_I2C_STATE_
{
  I2CPRT_CFG_E_I2C_IDLE = 0,       
  I2CPRT_CFG_E_I2C_READ,           
  I2CPRT_CFG_E_I2C_WRITE,     
  I2CPRT_CFG_E_I2C_BLOCK_WRITE,       
} I2CPRT_CFG_E_I2C_STATE;


#define I2CPRT_CFG_au8I2cRxBuf       RTE_au8I2cRxBuf
#define I2CPRT_CFG_au8I2cTxBuf       RTE_au8I2cTxBuf
#ifdef __cplusplus
  }
#endif
#endif  /* I2CPRT_CFG_H */

  
/*
 * End of file
 */
