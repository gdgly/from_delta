/** *****************************************************************************
 * \file    uart_conf.h
 * \brief   Configurations file for uart.c
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

#ifndef UART_CONF_H
#define UART_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/***********************************************
 * Baud rate
 **********************************************/
#define MG_BAUDRATE                 ((uint16)38400U)   /* Set baudrate */

/***********************************************
 * UART peripheral register relative definition
 **********************************************/
#define MG_RX_DATA_REG              USART2->RDR                    /* Rx register */
#define MG_TX_DATA_REG              USART2->TDR                    /* Tx register */
#define MG_TX_CMPLT_FLG_RD          (USART2->ISR & USART_ISR_TC)   /* Tx shift register empty */
#define MG_RX_DATA_RDY_FLG_RD       ((USART2->ISR & USART_ISR_RXNE) == USART_ISR_RXNE) /* Rx interrupt flag */

#define MG_UART1        1
#define MG_UART2        2
#define MG_UART3        3


#ifdef __cplusplus
  }
#endif
#endif  /* UART_CONF_H */


/*
 * End of file
 */
