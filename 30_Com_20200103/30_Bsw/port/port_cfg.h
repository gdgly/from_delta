/** *****************************************************************************
 * \file    port_cfg.h
 * \brief   Server call back service file for port.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-02-19 14:24:47 +0800 (Tue, 19 Feb 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 142 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PORT_CFG_H
#define PORT_CFG_H
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

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/
#ifdef PORT_EXPORT_H

/* The structure defining the setup of each GPIO input */
typedef struct
{
  /* Peripheral (StdPeriphDriver.h values required, e.g. RCC_AHBPeriph_GPIOA) */
  uint32 u32Perip;

  /* Port (StdPeriphDriver.h values required, e.g. GPIOA) */
  GPIO_TypeDef* GPIOx;

  /* Pin (StdPeriphDriver.h values required, e.g. GPIO_Pin_0) */
  uint16 u16Pin;

  /* Configuration_Mode (StdPeriphDriver.h e.g. GPIO_Mode_AF )*/
  GPIOMode_TypeDef Mode_Type;

	/* Speed for the selected pins (StdPeriphDriver.h e.g. GPIO_Speed_50MHz )*/
  GPIOSpeed_TypeDef GPIO_Speed;
	
	/* Output type for the selected pins (StdPeriphDriver.h e.g. GPIO_OType_PP )*/
  GPIOOType_TypeDef GPIO_OType; 

	/* Pull-up/Pull down for the selected pins (StdPeriphDriver.h e.g. GPIO_PuPd_UP )*/
  GPIOPuPd_TypeDef GPIO_PuPd; 
	
	/* Specifies the pin for the Alternate function. (StdPeriphDriver.h e.g. GPIO_PinSource2 ) */
	uint16_t u16PinSource; 
	
  /* Selects the pin to used as Alternate function (StdPeriphDriver.h e.g. GPIO_AF_1 ) */	
	uint8_t u8GpioAF;
	
	/* Initialised pin state - FALSE for low, TRUE for high */
	uint8 u8OutState;

} tPortSetup;

/* Define the GPIO pins to be initialised */
static const tPortSetup PORT_CFG_PORT_SETUP[] =
{
/* Port A */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_0, .Mode_Type=GPIO_Mode_AN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource0, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* Inlet NTC */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_1, .Mode_Type=GPIO_Mode_AN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource1, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* Internal voltage of 12VSB */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_2, .Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource2, .u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* TX of UART2 */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_3, .Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource3, .u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* RX of UART2 */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_4, .Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource4, .u8GpioAF=GPIO_AF_4, .u8OutState=FALSE}, /* Adjust the VSB voltage */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_5, .Mode_Type=GPIO_Mode_AN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource5, .u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* voltage of VSB */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_6, .Mode_Type=GPIO_Mode_AN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource6, .u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* current of VSB */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_7, .Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource7, .u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* VSB OVP test signal */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_8, .Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource8, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* uCC_Fan_Speed2 */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_9, .Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource9, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* uCC_Fan_Speed1 */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_10,.Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource10,.u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* PSON/L signal to PSU*/
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_11,.Mode_Type=GPIO_Mode_OUT,.GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource11,.u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* Power OK signal to system */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_12,.Mode_Type=GPIO_Mode_OUT,.GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource12,.u8GpioAF=GPIO_AF_0, .u8OutState=FALSE},  /* SMBAlert signal */
{.u32Perip=RCC_AHBPeriph_GPIOA, .GPIOx=GPIOA, .u16Pin=GPIO_Pin_15,.Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource15,.u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* PSKILL signal */

/* Port B */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_0, .Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource0, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* Fault flag of 54V */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_1, .Mode_Type=GPIO_Mode_OUT,.GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource1, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* Disable VSB SR signal */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_2, .Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_OD ,  .GPIO_PuPd=GPIO_PuPd_NOPULL, .u16PinSource=GPIO_PinSource2, .u8GpioAF=GPIO_AF_0, .u8OutState=TRUE},  /* Turn on or off VSB*/
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_3, .Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource3, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* I2c Address pin2 */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_4, .Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource4, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* I2c Address pin1 */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_5, .Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource5, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* I2c Address pin0 */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_6, .Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource6, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* TX of UART1*/
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_7, .Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource7, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* RX of UART1 */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_8, .Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_OD ,  .GPIO_PuPd=GPIO_PuPd_NOPULL, .u16PinSource=GPIO_PinSource8, .u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* SCL */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_9, .Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_OD ,  .GPIO_PuPd=GPIO_PuPd_NOPULL, .u16PinSource=GPIO_PinSource9, .u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* SDA */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_10,.Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_OD ,  .GPIO_PuPd=GPIO_PuPd_NOPULL, .u16PinSource=GPIO_PinSource10,.u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* SCL*/
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_11,.Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_OD ,  .GPIO_PuPd=GPIO_PuPd_NOPULL, .u16PinSource=GPIO_PinSource11,.u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* SDA */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_12,.Mode_Type=GPIO_Mode_OUT,.GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource12,.u8GpioAF=GPIO_AF_0, .u8OutState=TRUE},  /* Internal  synchronize with second side */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_13,.Mode_Type=GPIO_Mode_IN, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource13,.u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* Output VIN OK signal to system */
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_14,.Mode_Type=GPIO_Mode_OUT,.GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource14,.u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* AC OK signal from PFC*/
{.u32Perip=RCC_AHBPeriph_GPIOB, .GPIOx=GPIOB, .u16Pin=GPIO_Pin_15,.Mode_Type=GPIO_Mode_AF, .GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP,     .u16PinSource=GPIO_PinSource15,.u8GpioAF=GPIO_AF_1, .u8OutState=FALSE}, /* FAN control signal */
/* Port C */
{.u32Perip=RCC_AHBPeriph_GPIOC, .GPIOx=GPIOC, .u16Pin=GPIO_Pin_13,.Mode_Type=GPIO_Mode_OUT,.GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource13, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* LED show DC OK*/
{.u32Perip=RCC_AHBPeriph_GPIOC, .GPIOx=GPIOC, .u16Pin=GPIO_Pin_14,.Mode_Type=GPIO_Mode_OUT,.GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource14, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* LED show AC OK */
{.u32Perip=RCC_AHBPeriph_GPIOC, .GPIOx=GPIOC, .u16Pin=GPIO_Pin_15,.Mode_Type=GPIO_Mode_OUT,.GPIO_Speed=GPIO_Speed_50MHz, .GPIO_OType=GPIO_OType_PP ,  .GPIO_PuPd=GPIO_PuPd_UP, .u16PinSource=GPIO_PinSource15, .u8GpioAF=GPIO_AF_0, .u8OutState=FALSE}, /* LED show PSU fault */
};

#endif

/* Suggestion received to turn this into #defines, but the type checking is preferred */
typedef enum PORT_CFG_E_INDEX_
{
  /* Port A */
  PORT_CFG_E_A0_NTC_INLET = 0,
  PORT_CFG_E_A1_VSB_INT,
  PORT_CFG_E_A2_UART_TX2,
  PORT_CFG_E_A3_UART_RX2,
  PORT_CFG_E_A4_VSB_ADJ,
  PORT_CFG_E_A5_VSB_EXT,
  PORT_CFG_E_A6_VSB_I,
  PORT_CFG_E_A7_VSB_OVP_TEST,
  PORT_CFG_E_A8_FAN2_SPEED,
  PORT_CFG_E_A9_FAN1_SPEED,
  PORT_CFG_E_A10_PSON_L,
  PORT_CFG_E_A11_PW_OK,
  PORT_CFG_E_A12_SMBALERT_L,
  PORT_CFG_E_A15_PSKILL,
  /* Port B */
  PORT_CFG_E_B0_54V_FAULT,
  PORT_CFG_E_B1_DISABLE_VSB_SR,
  PORT_CFG_E_B2_VSB_OFF,
  PORT_CFG_E_B3_VIN_LINE,//PORT_CFG_E_B3_I2C_PA2,
  PORT_CFG_E_B4_I2C_PA1,
  PORT_CFG_E_B5_I2C_PA0,
  PORT_CFG_E_B6_UART_TX1,
  PORT_CFG_E_B7_UART_RX1,
  PORT_CFG_E_B8_SCL_COM,
  PORT_CFG_E_B9_SDA_COM,
  PORT_CFG_E_B10_SCL_EE,
  PORT_CFG_E_B11_SDA_EE,
  PORT_CFG_E_B12_SYNC_INTERNAL,
  PORT_CFG_E_B13_VIN_OK_IN,
  PORT_CFG_E_B14_ACOK_OUT,
  PORT_CFG_E_B15_FAN_DRIVER,
  /* Port C */
  PORT_CFG_E_C13_LED_DC_OK,
  PORT_CFG_E_C14_LED_AC_OK,
  PORT_CFG_E_C15_LED_FAULT,
  PORT_CFG_E_INDEX_COUNT /* Must be last row!*/
} PORT_CFG_E_INDEX;

typedef enum PORT_CFG_E_GPIO_MODE_
{
  PORT_CFG_E_GPIO_MODE_OUT = 0,
  PORT_CFG_E_GPIO_MODE_IN,
  PORT_CFG_E_GPIO_MODE_AF,
  PORT_CFG_E_GPIO_MODE_AN
}PORT_CFG_E_GPIO_MODE;

#ifdef __cplusplus
  }
#endif
#endif  /* PORT_CFG_H */

  
/*
 * End of file
 */
