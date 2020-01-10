/** *****************************************************************************
 * \file    uartprt_scfg.h
 * \brief   Server request service file for uartprt.c
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

#ifndef UARTPRT_SCFG_H
#define UARTPRT_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_UART_MODULE            1
#define MG_CRC_MODULE             1

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"

#if MG_UART_MODULE
#include "uart_api.h"
#endif
#if MG_CRC_MODULE
#include "crc_api.h"
#endif

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Module interface
 ******************************************************************************/

/* UART module section */
__attribute__((section ("ccram")))
inline uint8 UARTPRT_scfg_u8UartReadRxIsrFlg(uint8 u8UartIndex)
{
  #if MG_UART_MODULE
  return UART_u8UartReadRxIsrFlg(u8UartIndex);
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint8 UARTPRT_scfg_u8UartReadTxEmptyFlg(uint8 u8UartIndex)
{
  #if MG_UART_MODULE
  return UART_u8UartReadTxEmptyFlg(u8UartIndex);
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint8 UARTPRT_scfg_u8UartReadRxReg(uint8 u8UartIndex)
{
  #if MG_UART_MODULE
  return UART_u8UartReadRxReg(u8UartIndex);
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline void UARTPRT_scfg_vUartWriteTxReg(uint8 u8UartIndex,uint8 u8TxData)
{
  #if MG_UART_MODULE
  UART_vUartWriteTxReg(u8UartIndex,u8TxData);
  #endif
}

__attribute__((section ("ccram")))
inline uint16 UARTPRT_scfg_u16UartReadBaudrate(uint8 u8UartIndex)
{
  #if MG_UART_MODULE
  return UART_u16UartReadBaudrate(u8UartIndex);
  #else
  return 0;
  #endif
}

/* CRC module section */
inline uint16 UARTPRT_scfg_u16GetCrc16(uint16 u16InCrc, uint8 u8InData)
{
  #if MG_CRC_MODULE
  return CRC_u16GetCrc16(u16InCrc, u8InData);
  #else
  return 0;
  #endif
}

inline uint8 UARTPRT_scfg_u8GetCrc8(uint8 u8InCrc, uint8 u8InData)
{
  #if MG_CRC_MODULE
  return CRC_u8GetCrc8(u8InCrc, u8InData);
  #else
  return 0;
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* UARTPRT_SCFG_H */

  
/*
 * End of file
 */
