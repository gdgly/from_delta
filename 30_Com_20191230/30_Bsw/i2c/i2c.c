/*******************************************************************************
 * \file    i2c.c
 * \brief   Init I2C
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-03-01 14:35:06 +0800 (Fri, 01 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 145 $
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
#define I2C_EXPORT_H
  #include "i2c_api.h"
  #include "i2c_scb.h"
  #include "i2c_cfg.h"
  #include "i2c_scfg.h"
  #include "i2c_rte.h"
  #include "i2c_conf.h"

/*******************************************************************************
 * Global data
 ******************************************************************************/

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/


/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
uint8 mg_u8I2cResetFlag[I2C_CFG_E_INDEX_COUNT];
uint16 mg_u16SclLowCnt[I2C_CFG_E_INDEX_COUNT];
uint16 mg_u16SdaLowCnt[I2C_CFG_E_INDEX_COUNT];
/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
static void mg_vI2cReset(uint8 u8I2cIndex);

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/


/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/********************************************************************************
 * \brief         Init I2C module.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2C_vDeInit(void)
{
	
}

/********************************************************************************
 * \brief         Init I2C module.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2C_vInit(void)
{

	uint8 u8Loop;
  
  for(u8Loop=0;u8Loop<(uint8)I2C_CFG_E_INDEX_COUNT;u8Loop++)
  {

		mg_vI2cReset(u8Loop);
		
		if(I2C_CFG_I2C_SETUP[u8Loop].eITNewState == ENABLE)
		{
		  /* Temporary typedefs */
			NVIC_InitTypeDef      NVIC_InitStructure;
			
			/*Enable I2C interrupt flag*/
			I2C_ITConfig(I2C_CFG_I2C_SETUP[u8Loop].I2Cx, 
									 I2C_CFG_I2C_SETUP[u8Loop].u32IT, 
									 ENABLE);
			/* Configure NVIC to enable USART interrupt */
			NVIC_InitStructure.NVIC_IRQChannel         = I2C_CFG_I2C_SETUP[u8Loop].u8NvicIRQChannel;
			NVIC_InitStructure.NVIC_IRQChannelPriority = I2C_CFG_I2C_SETUP[u8Loop].u8NvicIRQChannelPrio;
			NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
		}
  }
} /* I2C_vInit() */


/********************************************************************************
 * \brief         I2C timeout handler. called in schm.c every 100us.
 *                check if I2C bus hung up (SCL or SDA low for 35ms)
 *                if yes:
 *                release the bus of the I2C interface by reseting module
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2C_vI2cTimeOutHandler(void)
{
  uint8 u8Loop;
  MONCTRL_RTE_Write_B_P_I2C_RESET_FLG(FALSE);
	
  for(u8Loop=0;u8Loop<(uint8)I2C_CFG_E_INDEX_COUNT;u8Loop++)
  {
		if(TRUE == I2C_CFG_I2C_SETUP[u8Loop].u32IsTimeOutCheck)
		{
			/* SCL status check */
			if (0 == GPIO_ReadInputDataBit(I2C_CFG_I2C_SETUP[u8Loop].sScl.GPIOx,I2C_CFG_I2C_SETUP[u8Loop].sScl.u16Pin))
			{
				if (mg_u16SclLowCnt[u8Loop] < I2C_CFG_I2C_SETUP[u8Loop].sScl.u16Timeout)
				{
					mg_u16SclLowCnt[u8Loop]++;
				}
				else
				{
					mg_u16SclLowCnt[u8Loop] = 0;
					mg_u8I2cResetFlag[u8Loop] = TRUE;
				}
			}
			else
			{
				mg_u16SclLowCnt[u8Loop] = 0;
			}

			/* SDA status check */
			if (0 == GPIO_ReadInputDataBit(I2C_CFG_I2C_SETUP[u8Loop].sSda.GPIOx,I2C_CFG_I2C_SETUP[u8Loop].sSda.u16Pin))
			{
				if (mg_u16SdaLowCnt[u8Loop] < I2C_CFG_I2C_SETUP[u8Loop].sSda.u16Timeout)
				{
					mg_u16SdaLowCnt[u8Loop]++;
				}
				else
				{
					mg_u16SdaLowCnt[u8Loop] = 0;
					mg_u8I2cResetFlag[u8Loop] = TRUE;
				}
			}
			else
			{
				mg_u16SdaLowCnt[u8Loop] = 0;
			}

			/* Reset I2C module to release lines */
			if (TRUE == mg_u8I2cResetFlag[u8Loop])
			{
				I2C_SoftwareResetCmd(I2C_CFG_I2C_SETUP[u8Loop].I2Cx);
				mg_vI2cReset(u8Loop);
        mg_u8I2cResetFlag[u8Loop] = FALSE;
			}
	  }
  }

} /* I2C_vI2cTimeOutHandler */

void I2C_vClearTimeoutCnt(uint8 u8Index)
{
	mg_u16SclLowCnt[u8Index] = 0;
  mg_u16SdaLowCnt[u8Index] = 0;
}

void I2C_vDisableNvicInt(uint8 u8Index)
{
	/* Temporary typedefs */
  NVIC_InitTypeDef      NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel         = I2C_CFG_I2C_SETUP[u8Index].u8NvicIRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPriority = I2C_CFG_I2C_SETUP[u8Index].u8NvicIRQChannelPrio;
	NVIC_InitStructure.NVIC_IRQChannelCmd      = DISABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void I2C_vEnableNvicInt(uint8 u8Index)
{
	/* Temporary typedefs */
  NVIC_InitTypeDef      NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel         = I2C_CFG_I2C_SETUP[u8Index].u8NvicIRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPriority = I2C_CFG_I2C_SETUP[u8Index].u8NvicIRQChannelPrio;
	NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/********************************************************************************
 * \brief         reset I2C module when error occurs.
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vI2cReset(uint8 u8I2cIndex)
{
	I2C_InitTypeDef  I2C_InitStructure;
	
	/*Enable I2C1 clock*/
	I2C_CFG_I2C_SETUP[u8I2cIndex].PeriphClockCmd(I2C_CFG_I2C_SETUP[u8I2cIndex].u32Perip, ENABLE); 

	I2C_StretchClockCmd(I2C_CFG_I2C_SETUP[u8I2cIndex].I2Cx,ENABLE);
	/*Config I2C_initStructure*/
	I2C_InitStructure.I2C_Timing = I2C_CFG_I2C_SETUP[u8I2cIndex].u32Timing;
	I2C_InitStructure.I2C_AnalogFilter = I2C_CFG_I2C_SETUP[u8I2cIndex].u32AnalogFilter;
	I2C_InitStructure.I2C_DigitalFilter = I2C_CFG_I2C_SETUP[u8I2cIndex].u32DigitalFilter;
	I2C_InitStructure.I2C_Mode = I2C_CFG_I2C_SETUP[u8I2cIndex].u32Mode;
	I2C_InitStructure.I2C_OwnAddress1 = I2C_CFG_I2C_SETUP[u8I2cIndex].u32OwnAddress1;
	I2C_InitStructure.I2C_Ack = I2C_CFG_I2C_SETUP[u8I2cIndex].u32Ack;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_CFG_I2C_SETUP[u8I2cIndex].u32AcknowledgedAddress;
	/*Init I2C interface*/
	I2C_Init(I2C_CFG_I2C_SETUP[u8I2cIndex].I2Cx, &I2C_InitStructure);
	
	/*Enable I2C interface*/
	I2C_Cmd(I2C_CFG_I2C_SETUP[u8I2cIndex].I2Cx, ENABLE);
}

/* End of file */
