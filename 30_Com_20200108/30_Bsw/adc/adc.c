/*******************************************************************************
 * \file    adc.c
 * \brief   MCU ADC configurations
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2018-09-13 20:02:04 +0800 (Thu, 13 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 30 $
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
#define ADC_EXPORT_H
	#include "adc_api.h"
  #include "adc_scb.h"
  #include "adc_cfg.h"
  #include "adc_scfg.h"
  #include "adc_conf.h"
	#include "rte.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

#define MG_U32_ADC1_DR_ADDRESS                (0x40012440u)

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/


/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static uint16 mg_u16AdcResultRaw[ADC_CFG_E_INDEX_COUNT]={0};

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

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
void ADC_vInit(void)
{
	uint8 u8Loop;
  ADC_InitTypeDef     ADC_InitStructure;
  DMA_InitTypeDef     DMA_InitStructure;
  ADC_DeInit(ADC1);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

  /* Config DMA Use for ADC End of EOC Copy data to Array  */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32)MG_U32_ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32)&mg_u16AdcResultRaw[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = (uint8)ADC_CFG_E_INDEX_COUNT;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Channel1, ENABLE);
  /* ADC DMA request in circular mode */
  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 

  for(u8Loop = 0u; u8Loop < (uint8)ADC_CFG_E_INDEX_COUNT; u8Loop++)
	{
    ADC_ChannelConfig(ADC1, 
		                  ADC_CFG_ADC_SETUP[u8Loop].u32AdcControlChannel, 
		                  ADC_CFG_ADC_SETUP[u8Loop].u32AdcSampleTime); 
	}

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);     
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);

  /* Enable ADC_DMA */
  ADC_DMACmd(ADC1, ENABLE);   
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
void ADC_vDeInit(void)
{

}

/** ****************************************************************************
 * \brief Read the specified value 
 *
 * \param[in] eAdcIndex     Index of the specified adc channel
 * \param[out] pu16AdcVal   Raw value of the adc
 *
 * \return -
 *
 **************************************************************************** */
void ADC_vReadRaw(ADC_CFG_E_INDEX eAdcIndex,uint16 *pu16AdcVal)
{
  *pu16AdcVal = mg_u16AdcResultRaw[eAdcIndex];
}/* ADC_vReadRaw */

/*
 * End of file
 */
