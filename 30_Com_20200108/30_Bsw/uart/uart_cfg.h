/** *****************************************************************************
 * \file    uart_cfg.h
 * \brief   Server call back service file for uart.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-03-01 14:35:06 +0800 (Fri, 01 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 145 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef UART_CFG_H
#define UART_CFG_H
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
#include "uart_conf.h"
#include "uartprt_scb.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/
		
#define MG_USART1_RX_ISR_SUB_PRIO       1
#define MG_USART2_RX_ISR_SUB_PRIO       1
		
 #ifdef UART_EXPORT_H

/* The structure defining the setup of each timer PWM output */
typedef struct
{
  /* Peripheral (Tivaware sysctl.h values required, e.g. SYSCTL_PERIPH_TIMER0) */
  uint32 u32Perip;
  
  /* Enables or disables the High Speed APB (APB2) peripheral clock */
  void (* PeriphClockCmd)(uint32_t RCC_Periph, FunctionalState NewState);

  /* Timer base (Tivaware hw_memmap.h values required, e.g. TIMER0_BASE)*/
  USART_TypeDef *UARTx;

	/* This member configures the USART communication baud rate. */
  uint32 u32BaudRate; 

	/* Specifies the number of data bits transmitted or received in a frame. */
  uint32 u32WordLength;          

  /* Specifies the number of stop bits transmitted. */
  uint32 u32StopBits;            

	/* Specifies the parity mode. */
  uint32 u32Parity;             
 
	/* Specifies wether the Receive or Transmit mode is enabled or disabled. */
  uint32 u32Mode;               

  /* Specifies wether the hardware flow control mode is enabled or disabled.  */
  uint32 u32HardwareFlowControl; 
	
	/* specifies the USART interrupt sources to be enabled or disabled. */
	uint32 u32UsartIT;
	
	/* new state of the specified USARTx interrupts*/
	FunctionalState eITNewState;
	
	/* Specifies the IRQ channel to be enabled or disabled. */
  uint8 u8NvicIRQChannel; 
	
  /* Specifies the priority level for the IRQ channel specified in NVIC_IRQChannel. */
  uint8_t u8NvicIRQChannelPrio;  
	
  /* Rx ISR call back */
	void (* Receive)(uint8_t);  
	
}tPwmSetup;

static const tPwmSetup UART_CFG_UART_SETUP[] =
{
/* UART1 initialised*/
{
 .u32Perip               = RCC_APB2Periph_USART1,
 .PeriphClockCmd         = RCC_APB2PeriphClockCmd,
 .UARTx                  = USART1,
 .u32BaudRate            = MG_BAUDRATE,
 .u32WordLength          = USART_WordLength_8b,
 .u32StopBits            = USART_StopBits_1,
 .u32Parity              = USART_Parity_No,
 .u32Mode                = USART_Mode_Rx | USART_Mode_Tx,
 .u32HardwareFlowControl = USART_HardwareFlowControl_None,
 .u32UsartIT             = USART_IT_RXNE,
 .eITNewState            = ENABLE,
 .u8NvicIRQChannel       = USART1_IRQn,
 .u8NvicIRQChannelPrio   = MG_USART1_RX_ISR_SUB_PRIO,
 .Receive                = UARTPRT_vUsartIrqHandler
},

/* UART2 initialised*/
{
 .u32Perip               = RCC_APB1Periph_USART2,
 .PeriphClockCmd         = RCC_APB1PeriphClockCmd,
 .UARTx                  = USART2,
 .u32BaudRate            = MG_BAUDRATE,
 .u32WordLength          = USART_WordLength_8b,
 .u32StopBits            = USART_StopBits_1,
 .u32Parity              = USART_Parity_No,
 .u32Mode                = USART_Mode_Rx | USART_Mode_Tx,
 .u32HardwareFlowControl = USART_HardwareFlowControl_None,
 .u32UsartIT             = USART_IT_RXNE,
 .eITNewState            = ENABLE,
 .u8NvicIRQChannel       = USART2_IRQn,
 .u8NvicIRQChannelPrio   = MG_USART2_RX_ISR_SUB_PRIO,
 .Receive                = UARTPRT_vUsartIrqHandler
},
}; /* */
#endif

typedef enum UART_CFG_E_INDEX_
{
  UART_CFG_E_INDEX_COM1 = 0,
  UART_CFG_E_INDEX_COM2,
  UART_CFG_E_INDEX_COUNT
} UART_CFG_E_INDEX;

#ifdef __cplusplus
  }
#endif
#endif  /* UART_CFG_H */

  
/*
 * End of file
 */
