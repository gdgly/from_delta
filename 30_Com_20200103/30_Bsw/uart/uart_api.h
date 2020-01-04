/** *****************************************************************************
 * \file    uart_api.h
 * \brief   Service function request file for uart.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-03 17:54:42 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 9 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef UART_API_H
#define UART_API_H
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
void UART_vInit(void);

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
void UART_vDeInit(void);

/** *****************************************************************************
 * \brief         Read UART ISR flags
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 UART_u8UartReadRxReg(uint8 u8UartIndex);

void UART_vUartWriteTxReg(uint8 u8UartIndex,uint8 u8TxData);

uint8 UART_u8UartReadTxEmptyFlg(uint8 u8UartIndex);

uint8 UART_u8UartReadRxIsrFlg(uint8 u8UartIndex);

uint16 UART_u16UartReadBaudrate(uint8 u8UartIndex);


#ifdef __cplusplus
  }
#endif
#endif  /* UART_API_H */

  
/*
 * End of file
 */
