/** *****************************************************************************
 * \file    uart.c
 * \brief   UART communication driver
 *
 * \section AUTHOR
 *    1. Fred Ji
 *    2. Dominik Beinlich
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

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "debug_llc.h"

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

static void mg_vUartHwInit(void);
  
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
  mg_vUartHwInit();
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
void UART_vUartNvicCfg(uint8 u8UartId, uint8 u8PrePriority, uint8 u8SubPriority)
{
  static uint8 u8IrqCh = 0;
  
  /* UART1 */
  if (u8UartId == MG_UART1)
  {
    u8IrqCh = USART1_IRQn;
  }
  /* UART2 */
  if (u8UartId == MG_UART2)
  {
    u8IrqCh = USART2_IRQn;
  }
  /* UART3 */
  if (u8UartId == MG_UART3)
  {
    u8IrqCh = USART3_IRQn;
  }
  
  /* Temporary typedefs */
  NVIC_InitTypeDef      NVIC_InitCfg;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  /* Configure NVIC to enable USART interrupt */
  NVIC_InitCfg.NVIC_IRQChannel = u8IrqCh;
  NVIC_InitCfg.NVIC_IRQChannelPreemptionPriority = u8PrePriority;
  NVIC_InitCfg.NVIC_IRQChannelSubPriority = u8SubPriority;
  NVIC_InitCfg.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitCfg);
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
static void mg_vUartHwInit(void)
{
  /* Initialize UART */
  USART_InitTypeDef     USART_InitStructure;

  /* Enable USART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  /* USARTx configuration
   * USARTx configured as follow:
   *       - BaudRate = 4800 baud
   *       - Word Length = 8 Bits
   *       - One Stop Bit
   *       - No parity
   *       - Hardware flow control disabled (RTS and CTS signals)
   *       - Receive and transmit enabled
   */
  USART_InitStructure.USART_BaudRate = MG_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* USART configuration */
  USART_Init(USART2, &USART_InitStructure);
  /* Enable USART */
  USART_Cmd(USART2, ENABLE);
  /* Enable the USART1 Interrupt */
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

/*
 * End of file
 */
