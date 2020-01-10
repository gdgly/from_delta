/** *****************************************************************************
 * \file    i2cprt_scb.h
 * \brief   Service function call back file for i2cprt.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-10 18:40:44 +0800 (Fri, 10 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 12 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef I2CPRT_SCB_H
#define I2CPRT_SCB_H
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
/********************************************************************************
 * \brief         Init I2C module.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_vInit(void);

/********************************************************************************
 * \brief         De-Init I2C module.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_vDeInit(void);

/********************************************************************************
 * \brief         if the slave address is not fixed check 
 *                the address every 10ms in schm.c.
 * \param[in]     u8DlyEn   Delay is for anti-shake
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_vUpdateI2cAddress( uint8 u8DlyEn );
	
/********************************************************************************
 * \brief         Detect Stop bit and check wait flag to handle received frame 
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_vProcessReceiveData( void );

#ifdef __cplusplus
  }
#endif
#endif  /* UART_SCB_H */

  
/*
 * End of file
 */
