/*******************************************************************************
 * \file    port.c
 * \brief   MCU port configurations
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2019-07-19 09:17:10 +0800 (Fri, 19 Jul 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 200 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>

/* Module header */
#define PORT_EXPORT_H
  #include "port_api.h"
  #include "port_scb.h"
  #include "port_cfg.h"
  #include "port_scfg.h"
  #include "port_conf.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize and configure MCU ports
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void PORT_vInit(void)
{
  /* Temporary typedefs */
  GPIO_InitTypeDef GPIO_InitStruct;
	uint8 u8Loop;

	for(u8Loop=0u;u8Loop<(uint8)PORT_CFG_E_INDEX_COUNT;u8Loop++)
	{
		/* Enable GPIO peripheral clock */
		RCC_AHBPeriphClockCmd(PORT_CFG_PORT_SETUP[u8Loop].u32Perip, ENABLE);
		
		GPIO_InitStruct.GPIO_Pin   = PORT_CFG_PORT_SETUP[u8Loop].u16Pin;
		GPIO_InitStruct.GPIO_Mode  = PORT_CFG_PORT_SETUP[u8Loop].Mode_Type;
		GPIO_InitStruct.GPIO_Speed = PORT_CFG_PORT_SETUP[u8Loop].GPIO_Speed;
		GPIO_InitStruct.GPIO_OType = PORT_CFG_PORT_SETUP[u8Loop].GPIO_OType;
		GPIO_InitStruct.GPIO_PuPd  = PORT_CFG_PORT_SETUP[u8Loop].GPIO_PuPd;;

		if(PORT_CFG_PORT_SETUP[u8Loop].Mode_Type == GPIO_Mode_AF)
		{
			GPIO_PinAFConfig(PORT_CFG_PORT_SETUP[u8Loop].GPIOx,
											 PORT_CFG_PORT_SETUP[u8Loop].u16PinSource,
											 PORT_CFG_PORT_SETUP[u8Loop].u8GpioAF);
		}
		/**************Digtal output port init status**********************/
		else if(PORT_CFG_PORT_SETUP[u8Loop].Mode_Type == GPIO_Mode_OUT)
		{
			if(PORT_CFG_PORT_SETUP[u8Loop].u8OutState == TRUE)
			{
				PORT_CFG_PORT_SETUP[u8Loop].GPIOx->BSRR = PORT_CFG_PORT_SETUP[u8Loop].u16Pin;
			}
			else
			{
				PORT_CFG_PORT_SETUP[u8Loop].GPIOx->BRR = PORT_CFG_PORT_SETUP[u8Loop].u16Pin;
			}
		}
		else
		{
			/* do nothing */
		}
    
    GPIO_Init(PORT_CFG_PORT_SETUP[u8Loop].GPIOx, &GPIO_InitStruct);

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
void PORT_vDeInit(void)
{
	uint8 u8Loop;
	
	for(u8Loop=0u;u8Loop<(uint8)PORT_CFG_E_INDEX_COUNT;u8Loop++)
	{
		/**************Digtal output port init status**********************/
    if(PORT_CFG_PORT_SETUP[u8Loop].Mode_Type == GPIO_Mode_OUT)
		{
			if(PORT_CFG_PORT_SETUP[u8Loop].u8OutState == TRUE)
			{
				PORT_CFG_PORT_SETUP[u8Loop].GPIOx->BSRR = PORT_CFG_PORT_SETUP[u8Loop].u16Pin;
			}
			else
			{
				PORT_CFG_PORT_SETUP[u8Loop].GPIOx->BRR = PORT_CFG_PORT_SETUP[u8Loop].u16Pin;
			}
		}
	}
}/* PORT_vDeInit */

/** *****************************************************************************
 * \brief         Set or reset GPIO pin
 *
 * \param[in]     Set or Reset
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void PORT_vSetGpioPin(PORT_CFG_E_INDEX ePortIndex,uint8 u8Status)
{
	/**************Digtal output port init status**********************/
	if(u8Status == TRUE)
	{
		PORT_CFG_PORT_SETUP[ePortIndex].GPIOx->BSRR = PORT_CFG_PORT_SETUP[ePortIndex].u16Pin;
	}
	else
	{
		PORT_CFG_PORT_SETUP[ePortIndex].GPIOx->BRR = PORT_CFG_PORT_SETUP[ePortIndex].u16Pin;
	}
}

/** *****************************************************************************
 * \brief         Set or reset GPIO pin
 *
 * \param[in]     Set or Reset
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void PORT_vSetGpioPinToggle(PORT_CFG_E_INDEX ePortIndex)
{
	/**************Digtal output port init status**********************/
  PORT_CFG_PORT_SETUP[ePortIndex].GPIOx->ODR ^= PORT_CFG_PORT_SETUP[ePortIndex].u16Pin;
}

/** *****************************************************************************
 * \brief         Read GPIO pin
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    Pin status
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 PORT_u8ReadGpioPin(PORT_CFG_E_INDEX ePortIndex)
{
  uint8 u8Bitstatus = 0x00;

  if ((PORT_CFG_PORT_SETUP[ePortIndex].GPIOx->IDR & PORT_CFG_PORT_SETUP[ePortIndex].u16Pin) != (uint32_t)Bit_RESET)
  {
    u8Bitstatus = (uint8)Bit_SET;
  }
  else
  {
    u8Bitstatus = (uint8)Bit_RESET;
  }
  return u8Bitstatus;
}

/** *****************************************************************************
 * \brief         Set the GPIO mode
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void PORT_vSetGpioMode(PORT_CFG_E_INDEX ePortIndex, PORT_CFG_E_GPIO_MODE eGpioMode)
{
 static uint8 u8Mode;
  switch(eGpioMode)
  {
    case PORT_CFG_E_GPIO_MODE_OUT:
    {
      u8Mode = GPIO_Mode_OUT;
      break;
    }
    case PORT_CFG_E_GPIO_MODE_IN:
    {
      u8Mode = GPIO_Mode_IN;
      break;
    }
    case PORT_CFG_E_GPIO_MODE_AF:
    {
      u8Mode = GPIO_Mode_AF;
      break;
    }
    case PORT_CFG_E_GPIO_MODE_AN:
    {
      u8Mode = GPIO_Mode_AN;
      break;
    }
    default:
    {
      u8Mode = GPIO_Mode_IN;
      break;
    }
  }
  
  /* Mode configuration */
  PORT_CFG_PORT_SETUP[ePortIndex].GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (PORT_CFG_PORT_SETUP[ePortIndex].u16PinSource * 2));
  PORT_CFG_PORT_SETUP[ePortIndex].GPIOx->MODER |= (((uint32_t)u8Mode) << (PORT_CFG_PORT_SETUP[ePortIndex].u16PinSource * 2));
}
/*
 * End of file
 */
