/** *****************************************************************************
 * \file    port_conf.h
 * \brief   Configurations file for port.c
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

#ifndef PORT_CONF_H
#define PORT_CONF_H
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

/*******************************************************************************
 * General purpose section
 ******************************************************************************/
#define PORT_A      1
#define PORT_B      2
#define PORT_C      3
#define PORT_D      4

#define PIN_0       0
#define PIN_1       1
#define PIN_2       2
#define PIN_3       3
#define PIN_4       4
#define PIN_5       5
#define PIN_6       6
#define PIN_7       7
#define PIN_8       8
#define PIN_9       9
#define PIN_10      10
#define PIN_11      11
#define PIN_12      12
#define PIN_13      13
#define PIN_14      14
#define PIN_15      15

#define MG_HRTIMER_PWM                GPIO_AF_13
#define MG_TIMER1_CH1_PWM             GPIO_AF_4
#define MG_TIMER2_CH1_PWM             GPIO_AF_1
#define MG_TIMER3_CH1_PWM             GPIO_AF_2
#define MG_EXTI                       GPIO_AF_13
#define MG_UART                       GPIO_AF_7
#define MG_SWDIO_SWCLK                GPIO_AF_0
#define MG_I2C                        GPIO_AF_4
#define MG_SPI                        GPIO_AF_5

/*******************************************************************************
 * PORT configuration section
 ******************************************************************************/
#define MG_PORT_BULK_OK               PORT_B
#define MG_PIN_BULK_OK                PIN_13

#define MG_PORT_PWM_ON                PORT_B
#define MG_PIN_PWM_ON                 PIN_5

#define MG_PORT_ACS_ON                PORT_A
#define MG_PIN_ACS_ON                 PIN_12

#define MG_PORT_OVP_CLR               PORT_B
#define MG_PIN_OVP_CLR                PIN_8

#define MG_PORT_OVP                   PORT_B
#define MG_PIN_OVP                    PIN_9

#define MG_PORT_LLC_HALT              PORT_B
#define MG_PIN_LLC_HALT               PIN_15

#define MG_PORT_LLC_FAULT             PORT_B
#define MG_PIN_LLC_FAULT              PIN_12

//#define MG_PORT_LLC_SWITCH_EN         PORT_C
//#define MG_PIN_LLC_SWITCH_EN          PIN_14

//#define MG_PORT_UART_ADDR             PORT_B
//#define MG_PIN_UART_ADDR              PIN_10

#define MG_PORT_ORING_EN              PORT_C
#define MG_PIN_ORING_EN               PIN_14

#define MG_PORT_DEBUG                 PORT_B
#define MG_PIN_DEBUG                  PIN_14

#if DEBUG_MODE
#if (MG_PORT_DEBUG == PORT_A)
#define MG_PORT_DEBUG_PIN_SET         GPIOA->BSRR = (1 << MG_PIN_DEBUG)       /* Set debug pin high */
#define MG_PORT_DEBUG_PIN_RESET       GPIOA->BRR = (1 << MG_PIN_DEBUG)        /* Set debug pin low */
#define MG_PORT_DEBUG_PIN_TOGGLE      GPIO_Toggle(GPIOA, (1 << MG_PIN_DEBUG)) /* Toggle debug pin */
#endif
#if (MG_PORT_DEBUG == PORT_B)
#define MG_PORT_DEBUG_PIN_SET         GPIOB->BSRR = (1 << MG_PIN_DEBUG)       /* Set debug pin high */
#define MG_PORT_DEBUG_PIN_RESET       GPIOB->BRR = (1 << MG_PIN_DEBUG)        /* Set debug pin low */
#define MG_PORT_DEBUG_PIN_TOGGLE      GPIO_Toggle(GPIOB, (1 << MG_PIN_DEBUG)) /* Toggle debug pin */
#endif
#if (MG_PORT_DEBUG == PORT_C)
#define MG_PORT_DEBUG_PIN_SET         GPIOC->BSRR = (1 << MG_PIN_DEBUG)       /* Set debug pin high */
#define MG_PORT_DEBUG_PIN_RESET       GPIOC->BRR = (1 << MG_PIN_DEBUG)        /* Set debug pin low */
#define MG_PORT_DEBUG_PIN_TOGGLE      GPIO_Toggle(GPIOC, (1 << MG_PIN_DEBUG)) /* Toggle debug pin */
#endif
#if (MG_PORT_DEBUG == PORT_D)
#define MG_PORT_DEBUG_PIN_SET         GPIOD->BSRR = (1 << MG_PIN_DEBUG)       /* Set debug pin high */
#define MG_PORT_DEBUG_PIN_RESET       GPIOD->BRR = (1 << MG_PIN_DEBUG)        /* Set debug pin low */
#define MG_PORT_DEBUG_PIN_TOGGLE      GPIO_Toggle(GPIOD, (1 << MG_PIN_DEBUG)) /* Toggle debug pin */
#endif
#endif


#ifdef __cplusplus
  }
#endif
#endif  /* PORT_CONF_H */


/*
 * End of file
 */
