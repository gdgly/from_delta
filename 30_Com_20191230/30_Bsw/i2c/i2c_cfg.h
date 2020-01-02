/** *****************************************************************************
 * \file    i2c_cfg.h
 * \brief   Server call back service file for i2c.c
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

#ifndef I2C_CFG_H
#define I2C_CFG_H
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
#define I2C_CFG_I2C1_BASE_SLA_ADR          0x80u		
#define I2C_CFG_I2C2_BASE_SLA_ADR          0x00u		


		
 #ifdef I2C_EXPORT_H
 
#define MG_I2C_CFG_I2C1_SDA_LOW_TIME_OUT    ((uint16)350U) 
#define MG_I2C_CFG_I2C1_SCL_LOW_TIME_OUT    ((uint16)350U)
 
#define MG_I2C1_RX_ISR_SUB_PRIO       0u
#define MG_I2C2_RX_ISR_SUB_PRIO       1u

/* The structure defining the setup of each timer PWM output */
typedef struct
{
	struct
	{
		/* Port (StdPeriphDriver.h values required, e.g. GPIOA) */
		GPIO_TypeDef* GPIOx;

		/* Pin (StdPeriphDriver.h values required, e.g. GPIO_Pin_0) */
		uint16 u16Pin;
		
		/* timeout value */
		uint16 u16Timeout;
	}sScl;
	struct
	{
		/* Port (StdPeriphDriver.h values required, e.g. GPIOA) */
		GPIO_TypeDef* GPIOx;

		/* Pin (StdPeriphDriver.h values required, e.g. GPIO_Pin_0) */
		uint16 u16Pin;
		
		/* timeout value */
		uint16 u16Timeout;
	}sSda;
  /* Peripheral (Tivaware sysctl.h values required, e.g. SYSCTL_PERIPH_TIMER0) */
  uint32 u32Perip;
  
  /* Enables or disables the High Speed APB (APB2) peripheral clock */
  void (* PeriphClockCmd)(uint32_t RCC_Periph, FunctionalState NewState);

  /* Timer base (Tivaware hw_memmap.h values required, e.g. TIMER0_BASE)*/
  I2C_TypeDef *I2Cx;

	/* Specifies the I2C_TIMINGR_register value. */
  uint32 u32Timing; 

	/* Enables or disables analog noise filter. */
  uint32 u32AnalogFilter;          

  /* Configures the digital noise filter. This parameter can be a number between 0x00 and 0x0F*/
  uint32 u32DigitalFilter;            

	/* Specifies the I2C mode. */
  uint32 u32Mode;             
 
	/* Specifies the device own address 1. */
  uint32 u32OwnAddress1;               

  /* Enables or disables the acknowledgement. */
  uint32 u32Ack; 
	
	/* Specifies if 7-bit or 10-bit address is acknowledged. */
	uint32 u32AcknowledgedAddress;
	
	/* Enable or disable I2c Time out check */
	uint32 u32IsTimeOutCheck;
	
	/* new state of the specified I2Cx interrupts*/
	FunctionalState eITNewState;
  
  /* specifies the I2C interrupts sources to be enabled or disabled. */
  uint32 u32IT;
	
	/* Specifies the IRQ channel to be enabled or disabled. */
  uint8 u8NvicIRQChannel; 
	
  /* Specifies the priority level for the IRQ channel specified in NVIC_IRQChannel. */
  uint8_t u8NvicIRQChannelPrio;  
	
//  /* ISR call back */
//	void (*IsrCallback)(void);  
	
}tPwmSetup;

static const tPwmSetup I2C_CFG_I2C_SETUP[] =
{
/* I2C1 initialised for PMBUS */
{
 .sScl.GPIOx             = GPIOB,
 .sScl.u16Pin            = GPIO_Pin_8,
 .sScl.u16Timeout        = MG_I2C_CFG_I2C1_SCL_LOW_TIME_OUT,
 .sSda.GPIOx             = GPIOB,
 .sSda.u16Pin            = GPIO_Pin_9,
 .sSda.u16Timeout        = MG_I2C_CFG_I2C1_SDA_LOW_TIME_OUT,
 .u32Perip               = RCC_APB1Periph_I2C1,
 .PeriphClockCmd         = RCC_APB1PeriphClockCmd,
 .I2Cx                   = I2C1,
 .u32Timing              = 0x10800000u,
 .u32AnalogFilter        = I2C_AnalogFilter_Enable,
 .u32DigitalFilter       = 0x00u,
 .u32Mode                = I2C_Mode_I2C,
 .u32OwnAddress1         = I2C_CFG_I2C1_BASE_SLA_ADR,
 .u32Ack                 = I2C_Ack_Enable,
 .u32AcknowledgedAddress = I2C_AcknowledgedAddress_7bit,
 .u32IsTimeOutCheck      = TRUE,
 .eITNewState            = ENABLE,
 .u32IT                  = I2C_IT_RXI | I2C_IT_ADDRI | I2C_IT_TXI |  I2C_IT_ERRI | I2C_IT_NACKI,
 .u8NvicIRQChannel       = I2C1_IRQn,
 .u8NvicIRQChannelPrio   = MG_I2C1_RX_ISR_SUB_PRIO
},

/* I2C2 initialised for EEPROM*/
{
 .sScl.GPIOx             = GPIOB,
 .sScl.u16Pin            = GPIO_Pin_10,
 .sScl.u16Timeout        = 0,
 .sSda.GPIOx             = GPIOB,
 .sSda.u16Pin            = GPIO_Pin_11,
 .sSda.u16Timeout        = 0,
 .u32Perip               = RCC_APB1Periph_I2C2,
 .PeriphClockCmd         = RCC_APB1PeriphClockCmd,
 .I2Cx                   = I2C2,
 .u32Timing              = 0x30E3323Du,
 .u32AnalogFilter        = I2C_AnalogFilter_Enable,
 .u32DigitalFilter       = 0x00u,
 .u32Mode                = I2C_Mode_I2C,
 .u32OwnAddress1         = 0x00,
 .u32Ack                 = I2C_Ack_Enable,
 .u32AcknowledgedAddress = I2C_AcknowledgedAddress_7bit,
 .u32IsTimeOutCheck      = FALSE,
 .eITNewState            = DISABLE,
 .u32IT                  = I2C_IT_TCI | I2C_IT_TXI | I2C_IT_RXI,
 .u8NvicIRQChannel       = I2C2_IRQn,
 .u8NvicIRQChannelPrio   = MG_I2C2_RX_ISR_SUB_PRIO
},
}; /* */
#endif

typedef enum I2C_CFG_E_INDEX_
{
  I2C_CFG_E_INDEX_PMBUS = 0,
  I2C_CFG_E_INDEX_EEP,
  I2C_CFG_E_INDEX_COUNT
} I2C_CFG_E_INDEX;

#ifdef __cplusplus
  }
#endif
#endif  /* I2C_CFG_H */

  
/*
 * End of file
 */
