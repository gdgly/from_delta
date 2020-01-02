/** *****************************************************************************
 * \file    uart.c
 * \brief   UART communication driver
 *
 * \section AUTHOR
 *    1. Fred Ji
 *    2. Dominik Beinlich
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

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>

/* Module header */
#define UART_EXPORT_H
  #include "uart_api.h"
  #include "uart_scb.h"
  #include "uart_cfg.h"
  #include "uart_scfg.h"
  #include "uart_conf.h"

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void (*mg_Uart1RxIsrCallback)(uint8 u8Data);
static void (*mg_Uart2RxIsrCallback)(uint8 u8Data);
  
/*******************************************************************************
 * Global functions (public to other modules)
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
void UART_vInit(void)
{
  /* Initialize UART */
  USART_InitTypeDef     USART_InitStructure;
	uint8 u8Loop;
	
	for(u8Loop=0;u8Loop<(uint8)UART_CFG_E_INDEX_COUNT;u8Loop++)
	{
		/* Enable USART clock */
    UART_CFG_UART_SETUP[u8Loop].PeriphClockCmd(UART_CFG_UART_SETUP[u8Loop].u32Perip, ENABLE);

		/* USARTx configuration
		 * USARTx configured as follow:
		 *       - BaudRate = 4800 baud
		 *       - Word Length = 8 Bits
		 *       - One Stop Bit
		 *       - No parity
		 *       - Hardware flow control disabled (RTS and CTS signals)
		 *       - Receive and transmit enabled
		 */
		USART_InitStructure.USART_BaudRate = UART_CFG_UART_SETUP[u8Loop].u32BaudRate;
		USART_InitStructure.USART_WordLength = UART_CFG_UART_SETUP[u8Loop].u32WordLength;
		USART_InitStructure.USART_StopBits = UART_CFG_UART_SETUP[u8Loop].u32StopBits;
		USART_InitStructure.USART_Parity = UART_CFG_UART_SETUP[u8Loop].u32Parity;
		USART_InitStructure.USART_HardwareFlowControl = UART_CFG_UART_SETUP[u8Loop].u32HardwareFlowControl;
		USART_InitStructure.USART_Mode = UART_CFG_UART_SETUP[u8Loop].u32Mode;

		/* USART configuration */
		USART_Init(UART_CFG_UART_SETUP[u8Loop].UARTx, &USART_InitStructure);
		/* Enable USART */
		USART_Cmd(UART_CFG_UART_SETUP[u8Loop].UARTx, ENABLE);

									 
		if(UART_CFG_UART_SETUP[u8Loop].eITNewState == ENABLE )
		{
			if(UART_CFG_UART_SETUP[u8Loop].UARTx == USART1)
			{
				mg_Uart1RxIsrCallback = UART_CFG_UART_SETUP[u8Loop].Receive;
			}
			else if(UART_CFG_UART_SETUP[u8Loop].UARTx == USART2)
			{
				mg_Uart2RxIsrCallback = UART_CFG_UART_SETUP[u8Loop].Receive;
			}
			/* Temporary typedefs */
			NVIC_InitTypeDef      NVIC_InitStructure;
			
		  /* Enable the USART1 Interrupt */
			USART_ITConfig(UART_CFG_UART_SETUP[u8Loop].UARTx, 
										 UART_CFG_UART_SETUP[u8Loop].u32UsartIT, 
										 ENABLE);
			
			/* Configure NVIC to enable USART interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = UART_CFG_UART_SETUP[u8Loop].u8NvicIRQChannel;
			NVIC_InitStructure.NVIC_IRQChannelPriority = UART_CFG_UART_SETUP[u8Loop].u8NvicIRQChannelPrio;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			
		}
		else
		{
			/* do nothing */
		}
  }
}

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
void UART_vDeInit(void)
{

}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != FALSE)
  {
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		(*mg_Uart1RxIsrCallback)(0);
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != FALSE)
  {
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		(*mg_Uart2RxIsrCallback)(1u);
	}
}

uint8 UART_u8UartReadRxReg(uint8 u8UartIndex)
{
	return UART_CFG_UART_SETUP[u8UartIndex].UARTx->RDR;
}
void UART_vUartWriteTxReg(uint8 u8UartIndex,uint8 u8TxData)
{
	UART_CFG_UART_SETUP[u8UartIndex].UARTx->TDR = u8TxData;
}

uint8 UART_u8UartReadTxEmptyFlg(uint8 u8UartIndex)
{
	return (UART_CFG_UART_SETUP[u8UartIndex].UARTx->ISR & USART_ISR_TC);
}

uint8 UART_u8UartReadRxIsrFlg(uint8 u8UartIndex)
{
	return (UART_CFG_UART_SETUP[u8UartIndex].UARTx->ISR & USART_ISR_TC);
}

uint16 UART_u16UartReadBaudrate(uint8 u8UartIndex)
{
	return (uint16)UART_CFG_UART_SETUP[u8UartIndex].u32BaudRate;
}

/*******************************************************************************
 * Local functions (privat for module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initialize the UART for use to build the serial
 *                communication link between primary and secondary MCU
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */


/*
 * End of file
 */
