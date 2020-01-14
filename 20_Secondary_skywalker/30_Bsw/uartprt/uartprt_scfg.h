/** *****************************************************************************
 * \file    uartprt_scfg.h
 * \brief   Server request service file for uartprt.c
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

#ifndef UARTPRT_SCFG_H
#define UARTPRT_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_PORT_MODULE            0
#define MG_UART_MODULE            1
#define MG_CRC_MODULE             1

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"

#if MG_PORT_MODULE
#include "port_api.h"
#endif
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

/* PORT module section */
inline uint8 UARTPRT_scfg_u8ReadGpioPortUartAddr(void)
{
  #if MG_PORT_MODULE
  return PORT_u8ReadGpioPinUartAddr();
  #else
  return RESET;
  #endif
}

/* UART module section */
__attribute__((section ("ccram")))
inline uint8 UARTPRT_scfg_u8UartReadRxIsrFlg(void)
{
  #if MG_UART_MODULE
  return UART_u8UartReadRxIsrFlg();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint8 UARTPRT_scfg_u8UartReadTxEmptyFlg(void)
{
  #if MG_UART_MODULE
  return UART_u8UartReadTxEmptyFlg();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint8 UARTPRT_scfg_u8UartReadRxReg(void)
{
  #if MG_UART_MODULE
  return UART_u8UartReadRxReg();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline void UARTPRT_scfg_vUartWriteTxReg(uint8 u8TxData)
{
  #if MG_UART_MODULE
  UART_vUartWriteTxReg(u8TxData);
  #endif
}

__attribute__((section ("ccram")))
inline uint16 UARTPRT_scfg_u16UartReadBaudrate(void)
{
  #if MG_UART_MODULE
  return UART_u16UartReadBaudrate();
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
