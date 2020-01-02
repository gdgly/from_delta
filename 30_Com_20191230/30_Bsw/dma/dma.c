/** *****************************************************************************
 * \file    dma.c
 * \brief   MCU DMA configurations
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <stdio.h>
#include <StdPeriphDriver.h>
#include "global.h"
#include "rte.h"

/* Module header */
#define DMA_EXPORT_H
  #include "dma.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
 
/* Hardware address of ADC result register */
#define MG_U32_ADC1_2_DATA_REG_ADDR   0x5000030C

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

/** *****************************************************************************
 * \brief         Allows direct memory access and data 
 *                transfer (buffer sampled ADC values)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void DMA_vDmaInit(void)
{
#if 0  
  /* Temporary typedefs */
  DMA_InitTypeDef     DMA_InitCfg;

  /* Enable DMA clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Set the peripheral address (ADC) */
  DMA_InitCfg.DMA_PeripheralBaseAddr = MG_U32_ADC1_2_DATA_REG_ADDR;
  /* Set the memory address, where the values are stored */
  DMA_InitCfg.DMA_MemoryBaseAddr = (uint32)&RTE_uAdcBuffer.Val32[0];
  /* Set the peripheral (ADC) as source */
  DMA_InitCfg.DMA_DIR = DMA_DIR_PeripheralSRC;
  /* Number of data to transfer */
  DMA_InitCfg.DMA_BufferSize = 4;    /* This value * 2 is the number of max. sampled channels */
  /* Don't count up the peripheral address (fixed to data register of ADC) */
  DMA_InitCfg.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  /* Count up memory address to store sampled ADC values in buffer */
  DMA_InitCfg.DMA_MemoryInc = DMA_MemoryInc_Enable;
  /* Data type definitions */
  DMA_InitCfg.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitCfg.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  /* Circular DMA mode for continous sampling */
  DMA_InitCfg.DMA_Mode = DMA_Mode_Circular;
  /* High priority */
  DMA_InitCfg.DMA_Priority = DMA_Priority_High;
  /* No memory to memory pipelining */
  DMA_InitCfg.DMA_M2M = DMA_M2M_Disable;
  /* Use initialized structure as DMA structure */
  DMA_Init(DMA1_Channel1, &DMA_InitCfg);

  /* Enable DMA1 Channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

  /* Interrupt when transfer complete and half transfer complete */
  DMA_ITConfig(DMA1_Channel1, DMA_IT_HT, ENABLE);
#endif
}

/*
 * End of file
 */
