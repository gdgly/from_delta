/** *****************************************************************************
 * \file    uart_api.h
 * \brief   Service function request file for uart.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date$
 *  $Author$
 *  $Revision$
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

#include "StdPeriphDriver.h"
#include "global.h"
#include "uart_conf.h"

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
 * \brief         UART NVIC configuration
 *
 * \param[in]     UartId: can be 1 to 3. PrePriority: can be 1 to 7. SubPriority: can be 1 to 7
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void UART_vUartNvicCfg(uint8 u8UartId, uint8 u8PrePriority, uint8 u8SubPriority);

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
__attribute__((section ("ccram")))
extern inline uint8 UART_u8UartReadRxReg(void)
{
  return MG_RX_DATA_REG;
}

__attribute__((section ("ccram")))
extern inline void UART_vUartWriteTxReg(uint8 u8TxData)
{
  MG_TX_DATA_REG = u8TxData;
}

__attribute__((section ("ccram")))
extern inline uint8 UART_u8UartReadTxEmptyFlg(void)
{
  return MG_TX_CMPLT_FLG_RD;
}

__attribute__((section ("ccram")))
extern inline uint8 UART_u8UartReadRxIsrFlg(void)
{
  return MG_RX_DATA_RDY_FLG_RD;
}

__attribute__((section ("ccram")))
extern inline uint16 UART_u16UartReadBaudrate(void)
{
  return MG_BAUDRATE;
}


#ifdef __cplusplus
  }
#endif
#endif  /* UART_API_H */

  
/*
 * End of file
 */
