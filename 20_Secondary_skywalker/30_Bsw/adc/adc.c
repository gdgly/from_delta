/** *****************************************************************************
 * \file    adc.c
 * \brief   MCU ADC configurations
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

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "debug_llc.h"

/* Module header */
#define ADC_EXPORT_H
  #include "adc_api.h"
  #include "adc_scb.h"
  #include "adc_cfg.h"
  #include "adc_scfg.h"
  #include "adc_conf.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
static void mg_vAdcHwInit(void);
static void mg_vDmaHwInit(void);
static void mg_vDelay(uint16);
  
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
  /* Init the ADC's */
  mg_vAdcHwInit();
  /* Init the DMA for the ADC data transfer */
  mg_vDmaHwInit();
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

/** *****************************************************************************
 * \brief         Initialize the ADC scaling factors
 *
 * \param[in]     Reference scaling factor
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void ADC_vVoltOutExtScale(uint16 u16ScaleFact)
{
  /* Calculate scaling factor */
  mg_u32q12AdcScaleFactVoltOutExt = (((uint32)u16ScaleFact << 12) / MG_ADC_RESOLUTION);
}

void ADC_vVoltOutIntScale(uint16 u16ScaleFact)
{
  /* Calculate scaling factor */
  mg_u32q12AdcScaleFactVoltOutInt = (((uint32)u16ScaleFact << 12) / MG_ADC_RESOLUTION);
}

void ADC_vCurrOutScale(uint16 u16ScaleFact)
{
  /* Calculate scaling factor */
  mg_u32q12AdcScaleFactCurrOut = (((uint32)u16ScaleFact << 12) / MG_ADC_RESOLUTION);
}

void ADC_vVoltRef3V3Scale(uint16 u16ScaleFact)
{
  /* Calculate scaling factor */
  mg_u32q12AdcScaleFactVoltRef3V3 = (((uint32)u16ScaleFact << 12) / MG_ADC_RESOLUTION);
}

void ADC_vAdcResNtcScale(uint16 u16ScaleFact)
{
  /* Calculate scaling factor */
  mg_u321OhmAdcScaleFactResNtc = u16ScaleFact;
}

void ADC_vAcsBusScale(uint16 u16ScaleFact)
{
  /* Calculate scaling factor */
  mg_u32q12AdcScaleFactAcsBus = (((uint32)u16ScaleFact << 12) / MG_ADC_RESOLUTION);
}

void ADC_vAcsLocalScale(uint16 u16ScaleFact)
{
  /* Calculate scaling factor */
  mg_u32q12AdcScaleFactAcsLocal = (((uint32)u16ScaleFact << 12) / MG_ADC_RESOLUTION);
}

/** *****************************************************************************
 * \brief         ADC DMA NVIC configuration
 *
 * \param[in]     DmaChId: can be 1 to 7. PrePriority: can be 1 to 7. SubPriority: can be 1 to 7
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void ADC_vAdcDmaNvicCfg(uint8 u8DmaChId, uint8 u8PrePriority, uint8 u8SubPriority)
{
  static uint8 u8IrqCh = 0;
  
  /* DMA Channel 1 */
  if (u8DmaChId == MG_DMA1CH1)
  {
    u8IrqCh = DMA1_Channel1_IRQn;
  }
  /* DMA Channel 2 */
  if (u8DmaChId == MG_DMA1CH2)
  {
    u8IrqCh = DMA1_Channel2_IRQn;
  }
  /* DMA Channel 3 */
  if (u8DmaChId == MG_DMA1CH3)
  {
    u8IrqCh = DMA1_Channel3_IRQn;
  }
  /* DMA Channel 4 */
  if (u8DmaChId == MG_DMA1CH4)
  {
    u8IrqCh = DMA1_Channel4_IRQn;
  }
  /* DMA Channel 5 */
  if (u8DmaChId == MG_DMA1CH5)
  {
    u8IrqCh = DMA1_Channel5_IRQn;
  }
  /* DMA Channel 6 */
  if (u8DmaChId == MG_DMA1CH6)
  {
    u8IrqCh = DMA1_Channel6_IRQn;
  }
  /* DMA Channel 7 */
  if (u8DmaChId == MG_DMA1CH7)
  {
    u8IrqCh = DMA1_Channel7_IRQn;
  }
  
  /* Temporary typedefs */
  NVIC_InitTypeDef      NVIC_InitCfg;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  /* Configure NVIC to enable DMA channel interrupt */
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
 * \brief         Initialize the ADC module
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vAdcHwInit(void)
{
  /* Temporary typedefs */
  ADC_CommonInitTypeDef         ADC_CommonInitCfg;
  ADC_InitTypeDef               ADC_InitCfg;

  /* Configure the ADC PLL clocks */
  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);
  /* Enable ADC clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);

  /* Calibration procedure */
  ADC_VoltageRegulatorCmd(ADC1, ENABLE);
  ADC_VoltageRegulatorCmd(ADC2, ENABLE);

  /************************************************************
   * Function call: Delay(delay_in_uS)
   * Description: Insert a delay in uS
   ************************************************************/
  mg_vDelay(20);  /* 10uS is the worse case time for ADC voltage regulator power-up */
                  /* However wait 20uS at this point be ensure proper operation */

  /* Calibrate the ADC's */
  ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1) != RESET);

  ADC_SelectCalibrationMode(ADC2, ADC_CalibrationMode_Single);
  ADC_StartCalibration(ADC2);
  while(ADC_GetCalibrationStatus(ADC2) != RESET);

  /***********************************************
   * ADC1 & ADC2 (Master configuration only -> applied also for Slave)
   **********************************************/
  /* Set ADC into regular simultaneous mode to sample two channels at the same time */
  ADC_CommonInitCfg.ADC_Mode = ADC_Mode_RegSimul;
  /* Set ADC clock to asynch mode */
  ADC_CommonInitCfg.ADC_Clock = ADC_Clock_AsynClkMode;
  /* DMA for converted value pipelining */
  ADC_CommonInitCfg.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
  ADC_CommonInitCfg.ADC_DMAMode = ADC_DMAMode_Circular;
  /* No sampling delay for ADC 2 */
  ADC_CommonInitCfg.ADC_TwoSamplingDelay = 0U;
  /* Use initialized structure as ADC structure */
  ADC_CommonInit(ADC1, &ADC_CommonInitCfg);

  /***********************************************
   * ADC1
   **********************************************/
  /* Discontinous sample mode */
  ADC_InitCfg.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;
  /* 12-bit ADC resolution */
  ADC_InitCfg.ADC_Resolution = ADC_Resolution_12b;
  /* External trigger events: Ext7 = HRTIM_ADCTRG1 event, Ext14 = TIM15_TRGO event  */
  ADC_InitCfg.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_14;
  ADC_InitCfg.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;
  /* Right aligned data */
  ADC_InitCfg.ADC_DataAlign = ADC_DataAlign_Right;
  /* Overwrite stored ADC value if new conversion is complete */
  ADC_InitCfg.ADC_OverrunMode = ADC_OverrunMode_Enable;
  /* Auto injection mode off */
  ADC_InitCfg.ADC_AutoInjMode = ADC_AutoInjec_Disable;
  /* Number of channels to convert per sequence */
  ADC_InitCfg.ADC_NbrOfRegChannel = MG_NUM_OF_ADC_CHANNEL;
  /* Use initialized structure as ADC structure */
  ADC_Init(ADC1, &ADC_InitCfg);

  /*
   * Buffered input: 1.5cycles; Non-buffered input: 2.5cycles; Slow channel inputs: 4.5cycles (MINIMUM REQUIREMENTS)
   * NOTE: Sampling channel-pair requires same sampling time
   */
  /* Sequence 1 (ISR): */
  /* ADC1 regular channel 1 (PA0) configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, MG_ADC_1_SAMPLE_V_OUT_EXT, ADC_SampleTime_4Cycles5);
  /* ADC1 regular channel 2 (PA1) configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, MG_ADC_1_SAMPLE_V_OUT_INT, ADC_SampleTime_4Cycles5);
  /* ADC1 regular channel 3 (PA2) configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, MG_ADC_1_SAMPLE_I_OUT, ADC_SampleTime_4Cycles5);
  /* ADC1 regular channel 4 (PA3) configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, MG_ADC_1_SAMPLE_ACS_BUS, ADC_SampleTime_4Cycles5);
  /* ADC1 regular channel 12 (PB1) configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, MG_ADC_1_SAMPLE_ACS_LOCAL, ADC_SampleTime_4Cycles5);
  /* ADC1 regular channel 11 (PB0) configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, MG_ADC_1_SAMPLE_2V5REF, ADC_SampleTime_4Cycles5);

  /***********************************************
   * ADC2
   **********************************************/
  /* Discontinous sample mode */
  ADC_InitCfg.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;
  /* 12-bit ADC resolution */
  ADC_InitCfg.ADC_Resolution = ADC_Resolution_12b;
  /* External trigger events: Ext8 = HRTIM_ADCTRG3 event */
  ADC_InitCfg.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_14;
  ADC_InitCfg.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
  /* Right aligned data */
  ADC_InitCfg.ADC_DataAlign = ADC_DataAlign_Right;
  /* Overwrite stored ADC value if new conversion is complete */
  ADC_InitCfg.ADC_OverrunMode = ADC_OverrunMode_Enable;
  /* Auto injection mode off */
  ADC_InitCfg.ADC_AutoInjMode = ADC_AutoInjec_Disable;
  /* Number of channels to convert per sequence */
  ADC_InitCfg.ADC_NbrOfRegChannel = MG_NUM_OF_ADC_CHANNEL;
  /* Use initialized structure as ADC structure */
  ADC_Init(ADC2, &ADC_InitCfg);

  /*
   * Buffered input: 1.5cycles; Non-buffered input: 2.5cycles; Slow channel inputs: 4.5cycles (MINIMUM REQUIREMENTS)
   * NOTE: Sampling channel-pair requires same sampling time
   * Regular sampling time = 12.5cycles conversion time + sampling time
   */
  /* Sequence 1 (ISR): */
  /* ADC2 regular channel 3 (PA6) configuration */
  ADC_RegularChannelConfig(ADC2, ADC_Channel_3, MG_ADC_2_SAMPLE_NTC_ORING, ADC_SampleTime_4Cycles5);
  /* ADC2 regular channel 12 (PB2) configuration */
  ADC_RegularChannelConfig(ADC2, ADC_Channel_12, MG_ADC_2_SAMPLE_NTC_SR, ADC_SampleTime_4Cycles5);
  /* ADC2 regular channel 12 (PB2) configuration */
  ADC_RegularChannelConfig(ADC2, ADC_Channel_12, MG_ADC_2_SAMPLE_DUMMY_1, ADC_SampleTime_4Cycles5);
  /* ADC2 regular channel 12 (PB2) configuration */
  ADC_RegularChannelConfig(ADC2, ADC_Channel_12, MG_ADC_2_SAMPLE_DUMMY_2, ADC_SampleTime_4Cycles5);
  /* ADC2 regular channel 12 (PB2) configuration */
  ADC_RegularChannelConfig(ADC2, ADC_Channel_12, MG_ADC_2_SAMPLE_DUMMY_3, ADC_SampleTime_4Cycles5);
  /* ADC2 regular channel 12 (PB2) configuration */
  ADC_RegularChannelConfig(ADC2, ADC_Channel_12, MG_ADC_2_SAMPLE_DUMMY_4, ADC_SampleTime_4Cycles5);

  /***********************************************
   * Start of ADC's
   **********************************************/
  /* Start DMA pipelining */
  ADC_DMACmd(ADC1, ENABLE); /* Due to regular simultaneous mode the converted data of ADC1 and ADC2 */
                            /* are available at the same time -> one DMA triggered by the Master ADC */

  /* Enable ADC's */
  ADC_Cmd(ADC1, ENABLE);
  ADC_Cmd(ADC2, ENABLE);

  /* Start regular conversions (triggered by PWM's) */
  ADC_StartConversion(ADC1);
}

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
static void mg_vDmaHwInit(void)
{
  /* Temporary typedefs */
  DMA_InitTypeDef     DMA_InitCfg;

  /* Enable DMA clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /***********************************************
   * Configure DMA channel for ADC transfer
   **********************************************/
  /* Set the peripheral address (ADC) */
  DMA_InitCfg.DMA_PeripheralBaseAddr = MG_U32_ADC1_2_DATA_REG_ADDR_CDR;
  /* Set the memory address, where the values are stored */
  DMA_InitCfg.DMA_MemoryBaseAddr = (uint32_t)&mg_u16q12Adc12Buffer;
  /* Set the peripheral (period) as source */
  DMA_InitCfg.DMA_DIR = DMA_DIR_PeripheralSRC;
  /* Number of data to transfer */
  DMA_InitCfg.DMA_BufferSize = MG_NUM_OF_ADC_CHANNEL;    /* This value * 2 is the number of max. sampled channels */
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

  /* Enable DMA interrupt upon complete transfer of ADC conversion result */
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
}

/** *****************************************************************************
 * \brief         Insert a delay for the ADC power up. 
 *                This delay has to be larger than 10uS
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vDelay(uint16 AdcPwrUpDelay)
{
  uint16 DelayCtr = 0U;
  
  /* Adjust the delay iterations to achieve uS
   * Calibrated for 72MHz (1 / 0.125uS = 8)
   * Note: when used 64MHz clock, the delay is 1.1uS instead of 1uS */
  AdcPwrUpDelay = AdcPwrUpDelay << 3;
  /*
   * One while conditioning takes ~5 cycles
   * One adding operation takes ~4 cycles
   * -> 9 cycles per iteration = 135ns @ 64MHz; 125ns @ 72MHz
   */
  while (AdcPwrUpDelay > DelayCtr)
  {
    DelayCtr++;
  }
}


/*
 * End of file
 */
