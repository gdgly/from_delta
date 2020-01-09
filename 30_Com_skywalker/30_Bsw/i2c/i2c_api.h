/** *****************************************************************************
 * \file    i2c_api.h
 * \brief   Service function request file for uart.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-07 18:22:40 +0800 (Tue, 07 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 11 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef I2C_API_H
#define I2C_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void I2C_vInit(void);

/** *****************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void I2C_vDeInit(void);

/********************************************************************************
 * \brief         I2C timeout handler. called in schm.c every 100us.
 *                check if I2C bus hung up (SCL or SDA low for 35ms)
 *                if yes:
 *                release the bus of the I2C interface by reseting module
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2C_vI2cTimeOutHandler(void);

void I2C_vClearTimeoutCnt(uint8 u8Index);
void I2C_vDisableNvicInt(uint8 u8Index);
void I2C_vEnableNvicInt(uint8 u8Index);

#ifdef __cplusplus
  }
#endif
#endif  /* UART_API_H */

  
/*
 * End of file
 */
