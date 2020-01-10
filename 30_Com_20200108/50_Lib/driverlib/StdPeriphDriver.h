/**
  ******************************************************************************
  * @file    stm32f0xx_adc.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the ADC firmware 
  *          library
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_ADC_H
#define __STM32F0XX_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"              //Fred.Ji 2016Feb18
#include "RegBitDefs.h"										// common header file	 
/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  ADC Init structure definition
  */
  
typedef struct
{
  uint32_t ADC_Resolution;                  /*!< Selects the resolution of the conversion.
                                                 This parameter can be a value of @ref ADC_Resolution */

  FunctionalState ADC_ContinuousConvMode;   /*!< Specifies whether the conversion is performed in
                                                 Continuous or Single mode.
                                                 This parameter can be set to ENABLE or DISABLE. */

  uint32_t ADC_ExternalTrigConvEdge;        /*!< Selects the external trigger Edge and enables the
                                                 trigger of a regular group. This parameter can be a value
                                                 of @ref ADC_external_trigger_edge_conversion */

  uint32_t ADC_ExternalTrigConv;            /*!< Defines the external trigger used to start the analog
                                                 to digital conversion of regular channels. This parameter
                                                 can be a value of @ref ADC_external_trigger_sources_for_channels_conversion */

  uint32_t ADC_DataAlign;                   /*!< Specifies whether the ADC data alignment is left or right.
                                                 This parameter can be a value of @ref ADC_data_align */

  uint32_t  ADC_ScanDirection;              /*!< Specifies in which direction the channels will be scanned
                                                 in the sequence. 
                                                 This parameter can be a value of @ref ADC_Scan_Direction */
}ADC_InitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */ 
#define IS_ADC_ALL_PERIPH(PERIPH)                  ((PERIPH) == ADC1)

/** @defgroup ADC_JitterOff
  * @{
  */ 
/* These defines are obsolete and maintained for legacy purpose only. They are replaced  by the ADC_ClockMode */  
#define ADC_JitterOff_PCLKDiv2                    ADC_CFGR2_JITOFFDIV2
#define ADC_JitterOff_PCLKDiv4                    ADC_CFGR2_JITOFFDIV4

#define IS_ADC_JITTEROFF(JITTEROFF) (((JITTEROFF) & 0x3FFFFFFF) == (uint32_t)RESET)

/**
  * @}
  */
  
/** @defgroup ADC_ClockMode
  * @{
  */ 
#define ADC_ClockMode_AsynClk                  ((uint32_t)0x00000000)   /*!< ADC Asynchronous clock mode */
#define ADC_ClockMode_SynClkDiv2               ADC_CFGR2_CKMODE_0   /*!<  Synchronous clock mode divided by 2 */
#define ADC_ClockMode_SynClkDiv4               ADC_CFGR2_CKMODE_1   /*!<  Synchronous clock mode divided by 4 */
#define IS_ADC_CLOCKMODE(CLOCK) (((CLOCK) == ADC_ClockMode_AsynClk) ||\
				                        ((CLOCK) == ADC_ClockMode_SynClkDiv2) ||\
				                        ((CLOCK) == ADC_ClockMode_SynClkDiv4))

/**
  * @}
  */ 

/** @defgroup ADC_Resolution
  * @{
  */ 
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)
#define ADC_Resolution_10b                         ADC_CFGR1_RES_0
#define ADC_Resolution_8b                          ADC_CFGR1_RES_1
#define ADC_Resolution_6b                          ADC_CFGR1_RES

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) || \
                                       ((RESOLUTION) == ADC_Resolution_10b) || \
                                       ((RESOLUTION) == ADC_Resolution_8b) || \
                                       ((RESOLUTION) == ADC_Resolution_6b))

/**
  * @}
  */ 

/** @defgroup ADC_external_trigger_edge_conversion 
  * @{
  */ 
#define ADC_ExternalTrigConvEdge_None              ((uint32_t)0x00000000)
#define ADC_ExternalTrigConvEdge_Rising            ADC_CFGR1_EXTEN_0
#define ADC_ExternalTrigConvEdge_Falling           ADC_CFGR1_EXTEN_1
#define ADC_ExternalTrigConvEdge_RisingFalling     ADC_CFGR1_EXTEN

#define IS_ADC_EXT_TRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigConvEdge_None) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Rising) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Falling) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_RisingFalling))
/**
  * @}
  */ 

/** @defgroup ADC_external_trigger_sources_for_channels_conversion
  * @{
  */ 

/* TIM1 */
#define ADC_ExternalTrigConv_T1_TRGO               ((uint32_t)0x00000000)
#define ADC_ExternalTrigConv_T1_CC4                ADC_CFGR1_EXTSEL_0

/* TIM2 */
#define ADC_ExternalTrigConv_T2_TRGO               ADC_CFGR1_EXTSEL_1

/* TIM3 */
#define ADC_ExternalTrigConv_T3_TRGO               ((uint32_t)(ADC_CFGR1_EXTSEL_0 | ADC_CFGR1_EXTSEL_1))

/* TIM15 */
#define ADC_ExternalTrigConv_T15_TRGO              ADC_CFGR1_EXTSEL_2

#define IS_ADC_EXTERNAL_TRIG_CONV(CONV) (((CONV) == ADC_ExternalTrigConv_T1_TRGO) || \
                                         ((CONV) == ADC_ExternalTrigConv_T1_CC4)   || \
                                         ((CONV) == ADC_ExternalTrigConv_T2_TRGO)  || \
                                         ((CONV) == ADC_ExternalTrigConv_T3_TRGO)  || \
                                         ((CONV) == ADC_ExternalTrigConv_T15_TRGO)) 
/**
  * @}
  */ 

/** @defgroup ADC_data_align 
  * @{
  */ 
  
#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                         ADC_CFGR1_ALIGN

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */

/** @defgroup ADC_Scan_Direction 
  * @{
  */ 
  
#define ADC_ScanDirection_Upward                   ((uint32_t)0x00000000)
#define ADC_ScanDirection_Backward                 ADC_CFGR1_SCANDIR

#define IS_ADC_SCAN_DIRECTION(DIRECTION) (((DIRECTION) == ADC_ScanDirection_Upward) || \
                                          ((DIRECTION) == ADC_ScanDirection_Backward))
/**
  * @}
  */ 

/** @defgroup ADC_DMA_Mode 
  * @{
  */ 
  
#define ADC_DMAMode_OneShot                        ((uint32_t)0x00000000)
#define ADC_DMAMode_Circular                       ADC_CFGR1_DMACFG

#define IS_ADC_DMA_MODE(MODE) (((MODE) == ADC_DMAMode_OneShot) || \
                               ((MODE) == ADC_DMAMode_Circular))
/**
  * @}
  */ 
    
/** @defgroup ADC_analog_watchdog_selection 
  * @{
  */ 
  
#define ADC_AnalogWatchdog_Channel_0                 ((uint32_t)0x00000000)
#define ADC_AnalogWatchdog_Channel_1                 ((uint32_t)0x04000000)
#define ADC_AnalogWatchdog_Channel_2                 ((uint32_t)0x08000000)
#define ADC_AnalogWatchdog_Channel_3                 ((uint32_t)0x0C000000)
#define ADC_AnalogWatchdog_Channel_4                 ((uint32_t)0x10000000)
#define ADC_AnalogWatchdog_Channel_5                 ((uint32_t)0x14000000)
#define ADC_AnalogWatchdog_Channel_6                 ((uint32_t)0x18000000)
#define ADC_AnalogWatchdog_Channel_7                 ((uint32_t)0x1C000000)
#define ADC_AnalogWatchdog_Channel_8                 ((uint32_t)0x20000000)
#define ADC_AnalogWatchdog_Channel_9                 ((uint32_t)0x24000000)
#define ADC_AnalogWatchdog_Channel_10                ((uint32_t)0x28000000) /*!< Not available for STM32F031 devices */
#define ADC_AnalogWatchdog_Channel_11                ((uint32_t)0x2C000000) /*!< Not available for STM32F031 devices */
#define ADC_AnalogWatchdog_Channel_12                ((uint32_t)0x30000000) /*!< Not available for STM32F031 devices */
#define ADC_AnalogWatchdog_Channel_13                ((uint32_t)0x34000000) /*!< Not available for STM32F031 devices */
#define ADC_AnalogWatchdog_Channel_14                ((uint32_t)0x38000000) /*!< Not available for STM32F031 devices */
#define ADC_AnalogWatchdog_Channel_15                ((uint32_t)0x3C000000) /*!< Not available for STM32F031 devices */
#define ADC_AnalogWatchdog_Channel_16                ((uint32_t)0x40000000)
#define ADC_AnalogWatchdog_Channel_17                ((uint32_t)0x44000000)
#define ADC_AnalogWatchdog_Channel_18                ((uint32_t)0x48000000)


#define IS_ADC_ANALOG_WATCHDOG_CHANNEL(CHANNEL) (((CHANNEL) == ADC_AnalogWatchdog_Channel_0)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_1)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_2)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_3)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_4)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_5)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_6)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_7)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_8)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_9)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_10) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_11) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_12) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_13) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_14) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_15) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_16) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_17) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_18))
/**
  * @}
  */ 
  
/** @defgroup ADC_sampling_times 
  * @{
  */ 

#define ADC_SampleTime_1_5Cycles                     ((uint32_t)0x00000000)
#define ADC_SampleTime_7_5Cycles                     ((uint32_t)0x00000001)
#define ADC_SampleTime_13_5Cycles                    ((uint32_t)0x00000002)
#define ADC_SampleTime_28_5Cycles                    ((uint32_t)0x00000003)
#define ADC_SampleTime_41_5Cycles                    ((uint32_t)0x00000004)
#define ADC_SampleTime_55_5Cycles                    ((uint32_t)0x00000005)
#define ADC_SampleTime_71_5Cycles                    ((uint32_t)0x00000006)
#define ADC_SampleTime_239_5Cycles                   ((uint32_t)0x00000007)

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SampleTime_1_5Cycles)   || \
                                  ((TIME) == ADC_SampleTime_7_5Cycles)   || \
                                  ((TIME) == ADC_SampleTime_13_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_28_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_41_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_55_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_71_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_239_5Cycles))
/**
  * @}
  */ 

/** @defgroup ADC_thresholds 
  * @{
  */ 
  
#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)

/**
  * @}
  */ 

/** @defgroup ADC_channels 
  * @{
  */ 
  
#define ADC_Channel_0                              ADC_CHSELR_CHSEL0
#define ADC_Channel_1                              ADC_CHSELR_CHSEL1
#define ADC_Channel_2                              ADC_CHSELR_CHSEL2
#define ADC_Channel_3                              ADC_CHSELR_CHSEL3
#define ADC_Channel_4                              ADC_CHSELR_CHSEL4
#define ADC_Channel_5                              ADC_CHSELR_CHSEL5
#define ADC_Channel_6                              ADC_CHSELR_CHSEL6
#define ADC_Channel_7                              ADC_CHSELR_CHSEL7
#define ADC_Channel_8                              ADC_CHSELR_CHSEL8
#define ADC_Channel_9                              ADC_CHSELR_CHSEL9
#define ADC_Channel_10                             ADC_CHSELR_CHSEL10 /*!< Not available for STM32F031 devices */
#define ADC_Channel_11                             ADC_CHSELR_CHSEL11 /*!< Not available for STM32F031 devices */
#define ADC_Channel_12                             ADC_CHSELR_CHSEL12 /*!< Not available for STM32F031 devices */
#define ADC_Channel_13                             ADC_CHSELR_CHSEL13 /*!< Not available for STM32F031 devices */
#define ADC_Channel_14                             ADC_CHSELR_CHSEL14 /*!< Not available for STM32F031 devices */
#define ADC_Channel_15                             ADC_CHSELR_CHSEL15 /*!< Not available for STM32F031 devices */
#define ADC_Channel_16                             ADC_CHSELR_CHSEL16
#define ADC_Channel_17                             ADC_CHSELR_CHSEL17
#define ADC_Channel_18                             ADC_CHSELR_CHSEL18 /*!< Not available for STM32F030 devices */

#define ADC_Channel_TempSensor                     ((uint32_t)ADC_Channel_16)
#define ADC_Channel_Vrefint                        ((uint32_t)ADC_Channel_17)
#define ADC_Channel_Vbat                           ((uint32_t)ADC_Channel_18) /*!< Not available for STM32F030 devices */

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) != (uint32_t)RESET) && (((CHANNEL) & 0xFFF80000) == (uint32_t)RESET))

/**
  * @}
  */ 
  
/** @defgroup ADC_interrupts_definition 
  * @{
  */ 
  
#define ADC_IT_ADRDY                               ADC_IER_ADRDYIE
#define ADC_IT_EOSMP                               ADC_IER_EOSMPIE
#define ADC_IT_EOC                                 ADC_IER_EOCIE
#define ADC_IT_EOSEQ                               ADC_IER_EOSEQIE
#define ADC_IT_OVR                                 ADC_IER_OVRIE
#define ADC_IT_AWD                                 ADC_IER_AWDIE
 
#define IS_ADC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFF60) == (uint32_t)RESET))

#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_ADRDY) || ((IT) == ADC_IT_EOSMP) || \
                           ((IT) == ADC_IT_EOC)   || ((IT) == ADC_IT_EOSEQ) || \
                           ((IT) == ADC_IT_OVR)   || ((IT) == ADC_IT_AWD))

#define IS_ADC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFF60) == (uint32_t)RESET))

/**
  * @}
  */ 

/** @defgroup ADC_flags_definition 
  * @{
  */ 
  
#define ADC_FLAG_ADRDY                             ADC_ISR_ADRDY
#define ADC_FLAG_EOSMP                             ADC_ISR_EOSMP
#define ADC_FLAG_EOC                               ADC_ISR_EOC
#define ADC_FLAG_EOSEQ                             ADC_ISR_EOSEQ
#define ADC_FLAG_OVR                               ADC_ISR_OVR
#define ADC_FLAG_AWD                               ADC_ISR_AWD

#define ADC_FLAG_ADEN                              ((uint32_t)0x01000001)
#define ADC_FLAG_ADDIS                             ((uint32_t)0x01000002)
#define ADC_FLAG_ADSTART                           ((uint32_t)0x01000004)
#define ADC_FLAG_ADSTP                             ((uint32_t)0x01000010)
#define ADC_FLAG_ADCAL                             ((uint32_t)0x81000000) 

#define IS_ADC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFFFF60) == (uint32_t)RESET))

#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_ADRDY)   || ((FLAG) == ADC_FLAG_EOSMP) || \
                               ((FLAG) == ADC_FLAG_EOC)     || ((FLAG) == ADC_FLAG_EOSEQ) || \
                               ((FLAG) == ADC_FLAG_AWD)     || ((FLAG) == ADC_FLAG_OVR)   || \
                               ((FLAG) == ADC_FLAG_ADEN)    || ((FLAG) == ADC_FLAG_ADDIS) || \
                               ((FLAG) == ADC_FLAG_ADSTART) || ((FLAG) == ADC_FLAG_ADSTP) || \
                               ((FLAG) == ADC_FLAG_ADCAL))
/**
  * @}
  */
  
/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/*  Function used to set the ADC configuration to the default reset state *****/
void ADC_DeInit(ADC_TypeDef* ADCx);

/* Initialization and Configuration functions *********************************/ 
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_ClockModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_ClockMode);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
/* This Function is obsolete and maintained for legacy purpose only.
   ADC_ClockModeConfig() function should be used instead */
void ADC_JitterCmd(ADC_TypeDef* ADCx, uint32_t ADC_JitterOff, FunctionalState NewState);

/* Power saving functions *****************************************************/
void ADC_AutoPowerOffCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_WaitModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

/* Analog Watchdog configuration functions ************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog_Channel);
void ADC_AnalogWatchdogSingleChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

/* Temperature Sensor , Vrefint and Vbat management function ******************/
void ADC_TempSensorCmd(FunctionalState NewState);
void ADC_VrefintCmd(FunctionalState NewState);
void ADC_VbatCmd(FunctionalState NewState); /*!< Not applicable for STM32F030 devices */

/* Channels Configuration functions *******************************************/
void ADC_ChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, uint32_t ADC_SampleTime);
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_OverrunModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint32_t ADC_GetCalibrationFactor(ADC_TypeDef* ADCx);
void ADC_StopOfConversion(ADC_TypeDef* ADCx);
void ADC_StartOfConversion(ADC_TypeDef* ADCx);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);

/* Regular Channels DMA Configuration functions *******************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMARequestModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMARequestMode);

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_ADC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_can.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the CAN firmware 
  *          library, applicable only for STM32F072 devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_CAN_H
#define __STM32F0xx_CAN_H

#ifdef __cplusplus
 extern "C" {
#endif


/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup CAN
  * @{
  */

/* Exported types ------------------------------------------------------------*/

#define IS_CAN_ALL_PERIPH(PERIPH) (((PERIPH) == CAN))

/** 
  * @brief  CAN init structure definition
  */
typedef struct
{
  uint16_t CAN_Prescaler;   /*!< Specifies the length of a time quantum. 
                                 It ranges from 1 to 1024. */
  
  uint8_t CAN_Mode;         /*!< Specifies the CAN operating mode.
                                 This parameter can be a value of @ref CAN_operating_mode */

  uint8_t CAN_SJW;          /*!< Specifies the maximum number of time quanta 
                                 the CAN hardware is allowed to lengthen or 
                                 shorten a bit to perform resynchronization.
                                 This parameter can be a value of @ref CAN_synchronisation_jump_width */

  uint8_t CAN_BS1;          /*!< Specifies the number of time quanta in Bit 
                                 Segment 1. This parameter can be a value of 
                                 @ref CAN_time_quantum_in_bit_segment_1 */

  uint8_t CAN_BS2;          /*!< Specifies the number of time quanta in Bit Segment 2.
                                 This parameter can be a value of @ref CAN_time_quantum_in_bit_segment_2 */
  
  FunctionalState CAN_TTCM; /*!< Enable or disable the time triggered communication mode.
                                This parameter can be set either to ENABLE or DISABLE. */
  
  FunctionalState CAN_ABOM;  /*!< Enable or disable the automatic bus-off management.
                                  This parameter can be set either to ENABLE or DISABLE. */

  FunctionalState CAN_AWUM;  /*!< Enable or disable the automatic wake-up mode. 
                                  This parameter can be set either to ENABLE or DISABLE. */

  FunctionalState CAN_NART;  /*!< Enable or disable the non-automatic retransmission mode.
                                  This parameter can be set either to ENABLE or DISABLE. */

  FunctionalState CAN_RFLM;  /*!< Enable or disable the Receive FIFO Locked mode.
                                  This parameter can be set either to ENABLE or DISABLE. */

  FunctionalState CAN_TXFP;  /*!< Enable or disable the transmit FIFO priority.
                                  This parameter can be set either to ENABLE or DISABLE. */
} CAN_InitTypeDef;

/** 
  * @brief  CAN filter init structure definition
  */
typedef struct
{
  uint16_t CAN_FilterIdHigh;         /*!< Specifies the filter identification number (MSBs for a 32-bit
                                              configuration, first one for a 16-bit configuration).
                                              This parameter can be a value between 0x0000 and 0xFFFF */

  uint16_t CAN_FilterIdLow;          /*!< Specifies the filter identification number (LSBs for a 32-bit
                                              configuration, second one for a 16-bit configuration).
                                              This parameter can be a value between 0x0000 and 0xFFFF */

  uint16_t CAN_FilterMaskIdHigh;     /*!< Specifies the filter mask number or identification number,
                                              according to the mode (MSBs for a 32-bit configuration,
                                              first one for a 16-bit configuration).
                                              This parameter can be a value between 0x0000 and 0xFFFF */

  uint16_t CAN_FilterMaskIdLow;      /*!< Specifies the filter mask number or identification number,
                                              according to the mode (LSBs for a 32-bit configuration,
                                              second one for a 16-bit configuration).
                                              This parameter can be a value between 0x0000 and 0xFFFF */

  uint16_t CAN_FilterFIFOAssignment; /*!< Specifies the FIFO (0 or 1) which will be assigned to the filter.
                                              This parameter can be a value of @ref CAN_filter_FIFO */
  
  uint8_t CAN_FilterNumber;          /*!< Specifies the filter which will be initialized. It ranges from 0 to 13. */

  uint8_t CAN_FilterMode;            /*!< Specifies the filter mode to be initialized.
                                              This parameter can be a value of @ref CAN_filter_mode */

  uint8_t CAN_FilterScale;           /*!< Specifies the filter scale.
                                              This parameter can be a value of @ref CAN_filter_scale */

  FunctionalState CAN_FilterActivation; /*!< Enable or disable the filter.
                                              This parameter can be set either to ENABLE or DISABLE. */
} CAN_FilterInitTypeDef;

/** 
  * @brief  CAN Tx message structure definition  
  */
typedef struct
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be transmitted. This parameter can be a value 
                        of @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the message that will 
                        be transmitted. This parameter can be a value of 
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be 
                        transmitted. This parameter can be a value between 
                        0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be transmitted. It ranges from 0 
                        to 0xFF. */
} CanTxMsg;

/** 
  * @brief  CAN Rx message structure definition  
  */
typedef struct
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be received. This parameter can be a value of 
                        @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the received message.
                        This parameter can be a value of 
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
                        This parameter can be a value between 0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to 
                        0xFF. */

  uint8_t FMI;     /*!< Specifies the index of the filter the message stored in 
                        the mailbox passes through. This parameter can be a 
                        value between 0 to 0xFF */
} CanRxMsg;

/* Exported constants --------------------------------------------------------*/

/** @defgroup CAN_Exported_Constants
  * @{
  */

/** @defgroup CAN_InitStatus 
  * @{
  */

#define CAN_InitStatus_Failed              ((uint8_t)0x00) /*!< CAN initialization failed */
#define CAN_InitStatus_Success             ((uint8_t)0x01) /*!< CAN initialization OK */


/* Legacy defines */
#define CANINITFAILED    CAN_InitStatus_Failed
#define CANINITOK        CAN_InitStatus_Success
/**
  * @}
  */

/** @defgroup CAN_operating_mode 
  * @{
  */

#define CAN_Mode_Normal             ((uint8_t)0x00)  /*!< normal mode */
#define CAN_Mode_LoopBack           ((uint8_t)0x01)  /*!< loopback mode */
#define CAN_Mode_Silent             ((uint8_t)0x02)  /*!< silent mode */
#define CAN_Mode_Silent_LoopBack    ((uint8_t)0x03)  /*!< loopback combined with silent mode */

#define IS_CAN_MODE(MODE) (((MODE) == CAN_Mode_Normal) || \
                           ((MODE) == CAN_Mode_LoopBack)|| \
                           ((MODE) == CAN_Mode_Silent) || \
                           ((MODE) == CAN_Mode_Silent_LoopBack))
/**
  * @}
  */


 /**
  * @defgroup CAN_operating_mode 
  * @{
  */  
#define CAN_OperatingMode_Initialization  ((uint8_t)0x00) /*!< Initialization mode */
#define CAN_OperatingMode_Normal          ((uint8_t)0x01) /*!< Normal mode */
#define CAN_OperatingMode_Sleep           ((uint8_t)0x02) /*!< sleep mode */


#define IS_CAN_OPERATING_MODE(MODE) (((MODE) == CAN_OperatingMode_Initialization) ||\
                                    ((MODE) == CAN_OperatingMode_Normal)|| \
																		((MODE) == CAN_OperatingMode_Sleep))
/**
  * @}
  */
  
/**
  * @defgroup CAN_operating_mode_status
  * @{
  */  

#define CAN_ModeStatus_Failed    ((uint8_t)0x00)                /*!< CAN entering the specific mode failed */
#define CAN_ModeStatus_Success   ((uint8_t)!CAN_ModeStatus_Failed)   /*!< CAN entering the specific mode Succeed */
/**
  * @}
  */

/** @defgroup CAN_synchronisation_jump_width 
  * @{
  */
#define CAN_SJW_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */
#define CAN_SJW_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */
#define CAN_SJW_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */
#define CAN_SJW_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */

#define IS_CAN_SJW(SJW) (((SJW) == CAN_SJW_1tq) || ((SJW) == CAN_SJW_2tq)|| \
                         ((SJW) == CAN_SJW_3tq) || ((SJW) == CAN_SJW_4tq))
/**
  * @}
  */

/** @defgroup CAN_time_quantum_in_bit_segment_1 
  * @{
  */
#define CAN_BS1_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */
#define CAN_BS1_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */
#define CAN_BS1_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */
#define CAN_BS1_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */
#define CAN_BS1_5tq                 ((uint8_t)0x04)  /*!< 5 time quantum */
#define CAN_BS1_6tq                 ((uint8_t)0x05)  /*!< 6 time quantum */
#define CAN_BS1_7tq                 ((uint8_t)0x06)  /*!< 7 time quantum */
#define CAN_BS1_8tq                 ((uint8_t)0x07)  /*!< 8 time quantum */
#define CAN_BS1_9tq                 ((uint8_t)0x08)  /*!< 9 time quantum */
#define CAN_BS1_10tq                ((uint8_t)0x09)  /*!< 10 time quantum */
#define CAN_BS1_11tq                ((uint8_t)0x0A)  /*!< 11 time quantum */
#define CAN_BS1_12tq                ((uint8_t)0x0B)  /*!< 12 time quantum */
#define CAN_BS1_13tq                ((uint8_t)0x0C)  /*!< 13 time quantum */
#define CAN_BS1_14tq                ((uint8_t)0x0D)  /*!< 14 time quantum */
#define CAN_BS1_15tq                ((uint8_t)0x0E)  /*!< 15 time quantum */
#define CAN_BS1_16tq                ((uint8_t)0x0F)  /*!< 16 time quantum */

#define IS_CAN_BS1(BS1) ((BS1) <= CAN_BS1_16tq)
/**
  * @}
  */

/** @defgroup CAN_time_quantum_in_bit_segment_2 
  * @{
  */
#define CAN_BS2_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */
#define CAN_BS2_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */
#define CAN_BS2_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */
#define CAN_BS2_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */
#define CAN_BS2_5tq                 ((uint8_t)0x04)  /*!< 5 time quantum */
#define CAN_BS2_6tq                 ((uint8_t)0x05)  /*!< 6 time quantum */
#define CAN_BS2_7tq                 ((uint8_t)0x06)  /*!< 7 time quantum */
#define CAN_BS2_8tq                 ((uint8_t)0x07)  /*!< 8 time quantum */

#define IS_CAN_BS2(BS2) ((BS2) <= CAN_BS2_8tq)
/**
  * @}
  */

/** @defgroup CAN_clock_prescaler 
  * @{
  */
#define IS_CAN_PRESCALER(PRESCALER) (((PRESCALER) >= 1) && ((PRESCALER) <= 1024))
/**
  * @}
  */

/** @defgroup CAN_filter_number 
  * @{
  */
#define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 27)
/**
  * @}
  */

/** @defgroup CAN_filter_mode 
  * @{
  */
#define CAN_FilterMode_IdMask       ((uint8_t)0x00)  /*!< identifier/mask mode */
#define CAN_FilterMode_IdList       ((uint8_t)0x01)  /*!< identifier list mode */

#define IS_CAN_FILTER_MODE(MODE) (((MODE) == CAN_FilterMode_IdMask) || \
                                  ((MODE) == CAN_FilterMode_IdList))
/**
  * @}
  */

/** @defgroup CAN_filter_scale 
  * @{
  */
#define CAN_FilterScale_16bit       ((uint8_t)0x00) /*!< Two 16-bit filters */
#define CAN_FilterScale_32bit       ((uint8_t)0x01) /*!< One 32-bit filter */

#define IS_CAN_FILTER_SCALE(SCALE) (((SCALE) == CAN_FilterScale_16bit) || \
                                    ((SCALE) == CAN_FilterScale_32bit))
/**
  * @}
  */

/** @defgroup CAN_filter_FIFO
  * @{
  */
#define CAN_Filter_FIFO0             ((uint8_t)0x00)  /*!< Filter FIFO 0 assignment for filter x */
#define CAN_Filter_FIFO1             ((uint8_t)0x01)  /*!< Filter FIFO 1 assignment for filter x */
#define IS_CAN_FILTER_FIFO(FIFO) (((FIFO) == CAN_FilterFIFO0) || \
                                  ((FIFO) == CAN_FilterFIFO1))

/* Legacy defines */
#define CAN_FilterFIFO0  CAN_Filter_FIFO0
#define CAN_FilterFIFO1  CAN_Filter_FIFO1
/**
  * @}
  */

/** @defgroup CAN_Start_bank_filter_for_slave_CAN 
  * @{
  */
#define IS_CAN_BANKNUMBER(BANKNUMBER) (((BANKNUMBER) >= 1) && ((BANKNUMBER) <= 27))
/**
  * @}
  */

/** @defgroup CAN_Tx 
  * @{
  */
#define IS_CAN_TRANSMITMAILBOX(TRANSMITMAILBOX) ((TRANSMITMAILBOX) <= ((uint8_t)0x02))
#define IS_CAN_STDID(STDID)   ((STDID) <= ((uint32_t)0x7FF))
#define IS_CAN_EXTID(EXTID)   ((EXTID) <= ((uint32_t)0x1FFFFFFF))
#define IS_CAN_DLC(DLC)       ((DLC) <= ((uint8_t)0x08))
/**
  * @}
  */

/** @defgroup CAN_identifier_type 
  * @{
  */
#define CAN_Id_Standard             ((uint32_t)0x00000000)  /*!< Standard Id */
#define CAN_Id_Extended             ((uint32_t)0x00000004)  /*!< Extended Id */
#define IS_CAN_IDTYPE(IDTYPE) (((IDTYPE) == CAN_Id_Standard) || \
                               ((IDTYPE) == CAN_Id_Extended))

/* Legacy defines */
#define CAN_ID_STD      CAN_Id_Standard           
#define CAN_ID_EXT      CAN_Id_Extended
/**
  * @}
  */

/** @defgroup CAN_remote_transmission_request 
  * @{
  */
#define CAN_RTR_Data                ((uint32_t)0x00000000)  /*!< Data frame */
#define CAN_RTR_Remote              ((uint32_t)0x00000002)  /*!< Remote frame */
#define IS_CAN_RTR(RTR) (((RTR) == CAN_RTR_Data) || ((RTR) == CAN_RTR_Remote))

/* Legacy defines */
#define CAN_RTR_DATA     CAN_RTR_Data         
#define CAN_RTR_REMOTE   CAN_RTR_Remote
/**
  * @}
  */

/** @defgroup CAN_transmit_constants 
  * @{
  */
#define CAN_TxStatus_Failed         ((uint8_t)0x00)/*!< CAN transmission failed */
#define CAN_TxStatus_Ok             ((uint8_t)0x01) /*!< CAN transmission succeeded */
#define CAN_TxStatus_Pending        ((uint8_t)0x02) /*!< CAN transmission pending */
#define CAN_TxStatus_NoMailBox      ((uint8_t)0x04) /*!< CAN cell did not provide 
                                                         an empty mailbox */
/* Legacy defines */	
#define CANTXFAILED                  CAN_TxStatus_Failed
#define CANTXOK                      CAN_TxStatus_Ok
#define CANTXPENDING                 CAN_TxStatus_Pending
#define CAN_NO_MB                    CAN_TxStatus_NoMailBox
/**
  * @}
  */

/** @defgroup CAN_receive_FIFO_number_constants 
  * @{
  */
#define CAN_FIFO0                 ((uint8_t)0x00) /*!< CAN FIFO 0 used to receive */
#define CAN_FIFO1                 ((uint8_t)0x01) /*!< CAN FIFO 1 used to receive */

#define IS_CAN_FIFO(FIFO) (((FIFO) == CAN_FIFO0) || ((FIFO) == CAN_FIFO1))
/**
  * @}
  */

/** @defgroup CAN_sleep_constants 
  * @{
  */
#define CAN_Sleep_Failed     ((uint8_t)0x00) /*!< CAN did not enter the sleep mode */
#define CAN_Sleep_Ok         ((uint8_t)0x01) /*!< CAN entered the sleep mode */

/* Legacy defines */	
#define CANSLEEPFAILED   CAN_Sleep_Failed
#define CANSLEEPOK       CAN_Sleep_Ok
/**
  * @}
  */

/** @defgroup CAN_wake_up_constants 
  * @{
  */
#define CAN_WakeUp_Failed        ((uint8_t)0x00) /*!< CAN did not leave the sleep mode */
#define CAN_WakeUp_Ok            ((uint8_t)0x01) /*!< CAN leaved the sleep mode */

/* Legacy defines */
#define CANWAKEUPFAILED   CAN_WakeUp_Failed        
#define CANWAKEUPOK       CAN_WakeUp_Ok        
/**
  * @}
  */

/**
  * @defgroup CAN_Error_Code_constants
  * @{
  */                                                         
#define CAN_ErrorCode_NoErr           ((uint8_t)0x00) /*!< No Error */ 
#define	CAN_ErrorCode_StuffErr        ((uint8_t)0x10) /*!< Stuff Error */ 
#define	CAN_ErrorCode_FormErr         ((uint8_t)0x20) /*!< Form Error */ 
#define	CAN_ErrorCode_ACKErr          ((uint8_t)0x30) /*!< Acknowledgment Error */ 
#define	CAN_ErrorCode_BitRecessiveErr ((uint8_t)0x40) /*!< Bit Recessive Error */ 
#define	CAN_ErrorCode_BitDominantErr  ((uint8_t)0x50) /*!< Bit Dominant Error */ 
#define	CAN_ErrorCode_CRCErr          ((uint8_t)0x60) /*!< CRC Error  */ 
#define	CAN_ErrorCode_SoftwareSetErr  ((uint8_t)0x70) /*!< Software Set Error */ 
/**
  * @}
  */

/** @defgroup CAN_flags 
  * @{
  */
/* If the flag is 0x3XXXXXXX, it means that it can be used with CAN_GetFlagStatus()
   and CAN_ClearFlag() functions. */
/* If the flag is 0x1XXXXXXX, it means that it can only be used with 
   CAN_GetFlagStatus() function.  */

/* Transmit Flags */
#define CAN_FLAG_RQCP0             ((uint32_t)0x38000001) /*!< Request MailBox0 Flag */
#define CAN_FLAG_RQCP1             ((uint32_t)0x38000100) /*!< Request MailBox1 Flag */
#define CAN_FLAG_RQCP2             ((uint32_t)0x38010000) /*!< Request MailBox2 Flag */

/* Receive Flags */
#define CAN_FLAG_FMP0              ((uint32_t)0x12000003) /*!< FIFO 0 Message Pending Flag */
#define CAN_FLAG_FF0               ((uint32_t)0x32000008) /*!< FIFO 0 Full Flag            */
#define CAN_FLAG_FOV0              ((uint32_t)0x32000010) /*!< FIFO 0 Overrun Flag         */
#define CAN_FLAG_FMP1              ((uint32_t)0x14000003) /*!< FIFO 1 Message Pending Flag */
#define CAN_FLAG_FF1               ((uint32_t)0x34000008) /*!< FIFO 1 Full Flag            */
#define CAN_FLAG_FOV1              ((uint32_t)0x34000010) /*!< FIFO 1 Overrun Flag         */

/* Operating Mode Flags */
#define CAN_FLAG_WKU               ((uint32_t)0x31000008) /*!< Wake up Flag */
#define CAN_FLAG_SLAK              ((uint32_t)0x31000012) /*!< Sleep acknowledge Flag */
/* @note When SLAK interrupt is disabled (SLKIE=0), no polling on SLAKI is possible. 
         In this case the SLAK bit can be polled.*/

/* Error Flags */
#define CAN_FLAG_EWG               ((uint32_t)0x10F00001) /*!< Error Warning Flag   */
#define CAN_FLAG_EPV               ((uint32_t)0x10F00002) /*!< Error Passive Flag   */
#define CAN_FLAG_BOF               ((uint32_t)0x10F00004) /*!< Bus-Off Flag         */
#define CAN_FLAG_LEC               ((uint32_t)0x30F00070) /*!< Last error code Flag */

#define IS_CAN_GET_FLAG(FLAG) (((FLAG) == CAN_FLAG_LEC)  || ((FLAG) == CAN_FLAG_BOF)   || \
                               ((FLAG) == CAN_FLAG_EPV)  || ((FLAG) == CAN_FLAG_EWG)   || \
                               ((FLAG) == CAN_FLAG_WKU)  || ((FLAG) == CAN_FLAG_FOV0)  || \
                               ((FLAG) == CAN_FLAG_FF0)  || ((FLAG) == CAN_FLAG_FMP0)  || \
                               ((FLAG) == CAN_FLAG_FOV1) || ((FLAG) == CAN_FLAG_FF1)   || \
                               ((FLAG) == CAN_FLAG_FMP1) || ((FLAG) == CAN_FLAG_RQCP2) || \
                               ((FLAG) == CAN_FLAG_RQCP1)|| ((FLAG) == CAN_FLAG_RQCP0) || \
                               ((FLAG) == CAN_FLAG_SLAK ))

#define IS_CAN_CLEAR_FLAG(FLAG)(((FLAG) == CAN_FLAG_LEC) || ((FLAG) == CAN_FLAG_RQCP2) || \
                                ((FLAG) == CAN_FLAG_RQCP1)  || ((FLAG) == CAN_FLAG_RQCP0) || \
                                ((FLAG) == CAN_FLAG_FF0)  || ((FLAG) == CAN_FLAG_FOV0) ||\
                                ((FLAG) == CAN_FLAG_FF1) || ((FLAG) == CAN_FLAG_FOV1) || \
                                ((FLAG) == CAN_FLAG_WKU) || ((FLAG) == CAN_FLAG_SLAK))
/**
  * @}
  */

  
/** @defgroup CAN_interrupts 
  * @{
  */ 
#define CAN_IT_TME                  ((uint32_t)0x00000001) /*!< Transmit mailbox empty Interrupt*/

/* Receive Interrupts */
#define CAN_IT_FMP0                 ((uint32_t)0x00000002) /*!< FIFO 0 message pending Interrupt*/
#define CAN_IT_FF0                  ((uint32_t)0x00000004) /*!< FIFO 0 full Interrupt*/
#define CAN_IT_FOV0                 ((uint32_t)0x00000008) /*!< FIFO 0 overrun Interrupt*/
#define CAN_IT_FMP1                 ((uint32_t)0x00000010) /*!< FIFO 1 message pending Interrupt*/
#define CAN_IT_FF1                  ((uint32_t)0x00000020) /*!< FIFO 1 full Interrupt*/
#define CAN_IT_FOV1                 ((uint32_t)0x00000040) /*!< FIFO 1 overrun Interrupt*/

/* Operating Mode Interrupts */
#define CAN_IT_WKU                  ((uint32_t)0x00010000) /*!< Wake-up Interrupt*/
#define CAN_IT_SLK                  ((uint32_t)0x00020000) /*!< Sleep acknowledge Interrupt*/

/* Error Interrupts */
#define CAN_IT_EWG                  ((uint32_t)0x00000100) /*!< Error warning Interrupt*/
#define CAN_IT_EPV                  ((uint32_t)0x00000200) /*!< Error passive Interrupt*/
#define CAN_IT_BOF                  ((uint32_t)0x00000400) /*!< Bus-off Interrupt*/
#define CAN_IT_LEC                  ((uint32_t)0x00000800) /*!< Last error code Interrupt*/
#define CAN_IT_ERR                  ((uint32_t)0x00008000) /*!< Error Interrupt*/

/* Flags named as Interrupts : kept only for FW compatibility */
#define CAN_IT_RQCP0   CAN_IT_TME
#define CAN_IT_RQCP1   CAN_IT_TME
#define CAN_IT_RQCP2   CAN_IT_TME


#define IS_CAN_IT(IT)        (((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FMP0)  ||\
                             ((IT) == CAN_IT_FF0)  || ((IT) == CAN_IT_FOV0)  ||\
                             ((IT) == CAN_IT_FMP1) || ((IT) == CAN_IT_FF1)   ||\
                             ((IT) == CAN_IT_FOV1) || ((IT) == CAN_IT_EWG)   ||\
                             ((IT) == CAN_IT_EPV)  || ((IT) == CAN_IT_BOF)   ||\
                             ((IT) == CAN_IT_LEC)  || ((IT) == CAN_IT_ERR)   ||\
                             ((IT) == CAN_IT_WKU)  || ((IT) == CAN_IT_SLK))

#define IS_CAN_CLEAR_IT(IT) (((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FF0)    ||\
                             ((IT) == CAN_IT_FOV0)|| ((IT) == CAN_IT_FF1)    ||\
                             ((IT) == CAN_IT_FOV1)|| ((IT) == CAN_IT_EWG)    ||\
                             ((IT) == CAN_IT_EPV) || ((IT) == CAN_IT_BOF)    ||\
                             ((IT) == CAN_IT_LEC) || ((IT) == CAN_IT_ERR)    ||\
                             ((IT) == CAN_IT_WKU) || ((IT) == CAN_IT_SLK))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/  

/*  Function used to set the CAN configuration to the default reset state *****/ 
void CAN_DeInit(CAN_TypeDef* CANx);

/* Initialization and Configuration functions *********************************/ 
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct);
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct);
void CAN_SlaveStartBank(uint8_t CAN_BankNumber); 
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState);
void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState);

/* CAN Frames Transmission functions ******************************************/
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage);
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox);
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox);

/* CAN Frames Reception functions *********************************************/
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage);
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber);
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber);

/* Operation modes functions **************************************************/
uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode);
uint8_t CAN_Sleep(CAN_TypeDef* CANx);
uint8_t CAN_WakeUp(CAN_TypeDef* CANx);

/* CAN Bus Error management functions *****************************************/
uint8_t CAN_GetLastErrorCode(CAN_TypeDef* CANx);
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef* CANx);
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx);

/* Interrupts and flags management functions **********************************/
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState);
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT);
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_CAN_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_cec.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the CEC firmware 
  *          library, applicable only for STM32F051, STM32F042 and STM32F072 devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_CEC_H
#define __STM32F0XX_CEC_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup CEC
  * @{
  */
/* Exported types ------------------------------------------------------------*/
  
/** 
  * @brief CEC Init structure definition 
  */
typedef struct
{
  uint32_t CEC_SignalFreeTime;     /*!< Specifies the CEC Signal Free Time configuration.
                                   This parameter can be a value of @ref CEC_Signal_Free_Time */
  uint32_t CEC_RxTolerance;        /*!< Specifies the CEC Reception Tolerance.
                                   This parameter can be a value of @ref CEC_RxTolerance */
  uint32_t CEC_StopReception;      /*!< Specifies the CEC Stop Reception.
                                   This parameter can be a value of @ref CEC_Stop_Reception */
  uint32_t CEC_BitRisingError;     /*!< Specifies the CEC Bit Rising Error generation.
                                   This parameter can be a value of @ref CEC_Bit_Rising_Error_Generation */
  uint32_t CEC_LongBitPeriodError; /*!< Specifies the CEC Long Bit Error generation.
                                   This parameter can be a value of @ref CEC_Long_Bit_Error_Generation */
  uint32_t CEC_BRDNoGen;           /*!< Specifies the CEC Broadcast Error generation.
                                   This parameter can be a value of @ref CEC_BDR_No_Gen */
  uint32_t CEC_SFTOption;          /*!< Specifies the CEC Signal Free Time option.
                                   This parameter can be a value of @ref CEC_SFT_Option */

}CEC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup CEC_Exported_Constants
  * @{
  */

/** @defgroup CEC_Signal_Free_Time
  * @{
  */
#define CEC_SignalFreeTime_Standard     ((uint32_t)0x00000000) /*!< CEC Signal Free Time Standard         */
#define CEC_SignalFreeTime_1T           ((uint32_t)0x00000001) /*!< CEC  1.5 nominal data bit periods     */
#define CEC_SignalFreeTime_2T           ((uint32_t)0x00000002) /*!< CEC  2.5 nominal data bit periods     */
#define CEC_SignalFreeTime_3T           ((uint32_t)0x00000003) /*!< CEC  3.5 nominal data bit periods     */
#define CEC_SignalFreeTime_4T           ((uint32_t)0x00000004) /*!< CEC  4.5 nominal data bit periods     */
#define CEC_SignalFreeTime_5T           ((uint32_t)0x00000005) /*!< CEC  5.5 nominal data bit periods     */
#define CEC_SignalFreeTime_6T           ((uint32_t)0x00000006) /*!< CEC  6.5 nominal data bit periods     */
#define CEC_SignalFreeTime_7T           ((uint32_t)0x00000007) /*!< CEC  7.5 nominal data bit periods     */

#define IS_CEC_SIGNAL_FREE_TIME(TIME) (((TIME) == CEC_SignalFreeTime_Standard) || \
                                       ((TIME) == CEC_SignalFreeTime_1T)|| \
                                       ((TIME) == CEC_SignalFreeTime_2T)|| \
                                       ((TIME) == CEC_SignalFreeTime_3T)|| \
                                       ((TIME) == CEC_SignalFreeTime_4T)|| \
                                       ((TIME) == CEC_SignalFreeTime_5T)|| \
                                       ((TIME) == CEC_SignalFreeTime_6T)|| \
                                       ((TIME) == CEC_SignalFreeTime_7T))
/**
  * @}
  */

/** @defgroup CEC_RxTolerance
  * @{
  */
#define CEC_RxTolerance_Standard        ((uint32_t)0x00000000) /*!< Standard Tolerance Margin            */
#define CEC_RxTolerance_Extended        CEC_CFGR_RXTOL         /*!< Extended Tolerance Margin            */

#define IS_CEC_RX_TOLERANCE(TOLERANCE) (((TOLERANCE) == CEC_RxTolerance_Standard) || \
                                        ((TOLERANCE) == CEC_RxTolerance_Extended))
/**
  * @}
  */

/** @defgroup CEC_Stop_Reception
  * @{
  */
#define CEC_StopReception_Off           ((uint32_t)0x00000000) /*!< No RX Stop on bit Rising Error (BRE) */
#define CEC_StopReception_On            CEC_CFGR_BRESTP        /*!< RX Stop on bit Rising Error (BRE)    */

#define IS_CEC_STOP_RECEPTION(RECEPTION) (((RECEPTION) == CEC_StopReception_On) || \
                                          ((RECEPTION) == CEC_StopReception_Off))
/**
  * @}
  */

/** @defgroup CEC_Bit_Rising_Error_Generation
  * @{
  */
#define CEC_BitRisingError_Off          ((uint32_t)0x00000000) /*!< Bit Rising Error generation turned Off */
#define CEC_BitRisingError_On           CEC_CFGR_BREGEN        /*!< Bit Rising Error generation turned On  */

#define IS_CEC_BIT_RISING_ERROR(ERROR) (((ERROR) == CEC_BitRisingError_Off) || \
                                        ((ERROR) == CEC_BitRisingError_On))
/**
  * @}
  */

/** @defgroup CEC_Long_Bit_Error_Generation
  * @{
  */
#define CEC_LongBitPeriodError_Off      ((uint32_t)0x00000000)  /*!< Long Bit Period Error generation turned Off */
#define CEC_LongBitPeriodError_On       CEC_CFGR_LREGEN         /*!< Long Bit Period Error generation turned On  */

#define IS_CEC_LONG_BIT_PERIOD_ERROR(ERROR) (((ERROR) == CEC_LongBitPeriodError_Off) || \
                                             ((ERROR) == CEC_LongBitPeriodError_On))
/**
  * @}
  */

/** @defgroup CEC_BDR_No_Gen
  * @{
  */

#define CEC_BRDNoGen_Off      ((uint32_t)0x00000000)  /*!< Broadcast Bit Rising Error generation turned Off */
#define CEC_BRDNoGen_On       CEC_CFGR_BRDNOGEN       /*!< Broadcast Bit Rising Error generation turned On  */

#define IS_CEC_BDR_NO_GEN_ERROR(ERROR) (((ERROR) == CEC_BRDNoGen_Off) || \
                                        ((ERROR) == CEC_BRDNoGen_On))
/**
  * @}
  */

/** @defgroup CEC_SFT_Option
  * @{
  */
#define CEC_SFTOption_Off              ((uint32_t)0x00000000)  /*!< SFT option turned Off                   */
#define CEC_SFTOption_On               CEC_CFGR_SFTOPT         /*!< SFT option turned On                    */

#define IS_CEC_SFT_OPTION(OPTION) (((OPTION) == CEC_SFTOption_Off) || \
                                  ((OPTION) == CEC_SFTOption_On))
/**
  * @}
  */

/** @defgroup CEC_Own_Address
  * @{
  */
#define IS_CEC_ADDRESS(ADDRESS)         ((ADDRESS) < 0x10)

/**
  * @}
  */

/** @defgroup CEC_Interrupt_Configuration_definition
  * @{
  */
#define CEC_IT_TXACKE                   CEC_IER_TXACKEIE
#define CEC_IT_TXERR                    CEC_IER_TXERRIE
#define CEC_IT_TXUDR                    CEC_IER_TXUDRIE
#define CEC_IT_TXEND                    CEC_IER_TXENDIE
#define CEC_IT_TXBR                     CEC_IER_TXBRIE
#define CEC_IT_ARBLST                   CEC_IER_ARBLSTIE
#define CEC_IT_RXACKE                   CEC_IER_RXACKEIE
#define CEC_IT_LBPE                     CEC_IER_LBPEIE
#define CEC_IT_SBPE                     CEC_IER_SBPEIE
#define CEC_IT_BRE                      CEC_IER_BREIEIE
#define CEC_IT_RXOVR                    CEC_IER_RXOVRIE
#define CEC_IT_RXEND                    CEC_IER_RXENDIE
#define CEC_IT_RXBR                     CEC_IER_RXBRIE

#define IS_CEC_IT(IT) ((((IT) & (uint32_t)0xFFFFE000) == 0x00) && ((IT) != 0x00))

#define IS_CEC_GET_IT(IT) (((IT) == CEC_IT_TXACKE) || \
                           ((IT) == CEC_IT_TXERR)|| \
                           ((IT) == CEC_IT_TXUDR)|| \
                           ((IT) == CEC_IT_TXEND)|| \
                           ((IT) == CEC_IT_TXBR)|| \
                           ((IT) == CEC_IT_ARBLST)|| \
                           ((IT) == CEC_IT_RXACKE)|| \
                           ((IT) == CEC_IT_LBPE)|| \
                           ((IT) == CEC_IT_SBPE)|| \
                           ((IT) == CEC_IT_BRE)|| \
                           ((IT) == CEC_IT_RXOVR)|| \
                           ((IT) == CEC_IT_RXEND)|| \
                           ((IT) == CEC_IT_RXBR))
/**
  * @}
  */

/** @defgroup CEC_ISR_register_flags_definition
  * @{
  */
#define CEC_FLAG_TXACKE                 CEC_ISR_TXACKE
#define CEC_FLAG_TXERR                  CEC_ISR_TXERR
#define CEC_FLAG_TXUDR                  CEC_ISR_TXUDR
#define CEC_FLAG_TXEND                  CEC_ISR_TXEND
#define CEC_FLAG_TXBR                   CEC_ISR_TXBR
#define CEC_FLAG_ARBLST                 CEC_ISR_ARBLST
#define CEC_FLAG_RXACKE                 CEC_ISR_RXACKE
#define CEC_FLAG_LBPE                   CEC_ISR_LBPE
#define CEC_FLAG_SBPE                   CEC_ISR_SBPE
#define CEC_FLAG_BRE                    CEC_ISR_BRE
#define CEC_FLAG_RXOVR                  CEC_ISR_RXOVR
#define CEC_FLAG_RXEND                  CEC_ISR_RXEND
#define CEC_FLAG_RXBR                   CEC_ISR_RXBR

#define IS_CEC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFE000) == 0x00) && ((FLAG) != 0x00))

#define IS_CEC_GET_FLAG(FLAG) (((FLAG) == CEC_FLAG_TXACKE) || \
                               ((FLAG) == CEC_FLAG_TXERR)|| \
                               ((FLAG) == CEC_FLAG_TXUDR)|| \
                               ((FLAG) == CEC_FLAG_TXEND)|| \
                               ((FLAG) == CEC_FLAG_TXBR)|| \
                               ((FLAG) == CEC_FLAG_ARBLST)|| \
                               ((FLAG) == CEC_FLAG_RXACKE)|| \
                               ((FLAG) == CEC_FLAG_LBPE)|| \
                               ((FLAG) == CEC_FLAG_SBPE)|| \
                               ((FLAG) == CEC_FLAG_BRE)|| \
                               ((FLAG) == CEC_FLAG_RXOVR)|| \
                               ((FLAG) == CEC_FLAG_RXEND)|| \
                               ((FLAG) == CEC_FLAG_RXBR))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the CEC configuration to the default reset state *****/
void CEC_DeInit(void);

/* CEC_Initialization and Configuration functions *****************************/
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct);
void CEC_StructInit(CEC_InitTypeDef* CEC_InitStruct);
void CEC_Cmd(FunctionalState NewState);
void CEC_ListenModeCmd(FunctionalState NewState);
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress);
void CEC_OwnAddressClear(void);

/* CEC_Data transfers functions ***********************************************/
void CEC_SendData(uint8_t Data);
uint8_t CEC_ReceiveData(void);
void CEC_StartOfMessage(void);
void CEC_EndOfMessage(void);

/* CEC_Interrupts and flags management functions ******************************/
void CEC_ITConfig(uint16_t CEC_IT, FunctionalState NewState);
FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG);
void CEC_ClearFlag(uint32_t CEC_FLAG);
ITStatus CEC_GetITStatus(uint16_t CEC_IT);
void CEC_ClearITPendingBit(uint16_t CEC_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_CEC_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_comp.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the COMP firmware 
  *          library, applicable only for STM32F051 and STM32F072 devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_COMP_H
#define __STM32F0XX_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  COMP Init structure definition  
  */
  
typedef struct
{

  uint32_t COMP_InvertingInput;     /*!< Selects the inverting input of the comparator.
                                          This parameter can be a value of @ref COMP_InvertingInput */

  uint32_t COMP_Output;             /*!< Selects the output redirection of the comparator.
                                          This parameter can be a value of @ref COMP_Output */

  uint32_t COMP_OutputPol;           /*!< Selects the output polarity of the comparator.
                                          This parameter can be a value of @ref COMP_OutputPolarity */

  uint32_t COMP_Hysteresis;         /*!< Selects the hysteresis voltage of the comparator.
                                          This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t COMP_Mode;               /*!< Selects the operating mode of the comparator
                                         and allows to adjust the speed/consumption.
                                          This parameter can be a value of @ref COMP_Mode */

}COMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
   
/** @defgroup COMP_Exported_Constants
  * @{
  */ 

/** @defgroup COMP_Selection
  * @{
  */

#define COMP_Selection_COMP1                    ((uint32_t)0x00000000) /*!< COMP1 Selection */
#define COMP_Selection_COMP2                    ((uint32_t)0x00000010) /*!< COMP2 Selection */

#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP_Selection_COMP1) || \
                                    ((PERIPH) == COMP_Selection_COMP2))
 
/**
  * @}
  */ 

/** @defgroup COMP_InvertingInput
  * @{
  */

#define COMP_InvertingInput_1_4VREFINT          ((uint32_t)0x00000000) /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_1_2VREFINT          COMP_CSR_COMP1INSEL_0  /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_3_4VREFINT          COMP_CSR_COMP1INSEL_1  /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_VREFINT             ((uint32_t)0x00000030) /*!< VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_DAC1                COMP_CSR_COMP1INSEL_2  /*!< DAC1_OUT (PA4) connected to comparator inverting input */
#define COMP_InvertingInput_DAC2                ((uint32_t)0x00000050) /*!< DAC2_OUT (PA5) connected to comparator inverting input, applicable only for STM32F072 devices */
#define COMP_InvertingInput_IO                  ((uint32_t)0x00000060) /*!< I/O (PA0 for COMP1 and PA2 for COMP2) connected to comparator inverting input */

#define IS_COMP_INVERTING_INPUT(INPUT) (((INPUT) == COMP_InvertingInput_1_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_1_2VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_3_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_VREFINT)    || \
                                        ((INPUT) == COMP_InvertingInput_DAC1)       || \
                                        ((INPUT) == COMP_InvertingInput_DAC2)       || \
                                        ((INPUT) == COMP_InvertingInput_1_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_IO))
/**
  * @}
  */ 
  
/** @defgroup COMP_Output
  * @{
  */

#define COMP_Output_None                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
#define COMP_Output_TIM1BKIN              COMP_CSR_COMP1OUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_Output_TIM1IC1               COMP_CSR_COMP1OUTSEL_1   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_Output_TIM1OCREFCLR          ((uint32_t)0x00000300)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_Output_TIM2IC4               COMP_CSR_COMP1OUTSEL_2   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_Output_TIM2OCREFCLR          ((uint32_t)0x00000500)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM3IC1               ((uint32_t)0x00000600)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_Output_TIM3OCREFCLR          COMP_CSR_COMP1OUTSEL     /*!< COMP output connected to TIM3 OCREF Clear */


#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_Output_None)         || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN)     || \
                                ((OUTPUT) == COMP_Output_TIM1IC1)      || \
                                ((OUTPUT) == COMP_Output_TIM1OCREFCLR) || \
                                ((OUTPUT) == COMP_Output_TIM2IC4)      || \
                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR) || \
                                ((OUTPUT) == COMP_Output_TIM3IC1)      || \
                                ((OUTPUT) == COMP_Output_TIM3OCREFCLR))
/**
  * @}
  */ 

/** @defgroup COMP_OutputPolarity
  * @{
  */
#define COMP_OutputPol_NonInverted          ((uint32_t)0x00000000)  /*!< COMP output on GPIO isn't inverted */
#define COMP_OutputPol_Inverted             COMP_CSR_COMP1POL       /*!< COMP output on GPIO is inverted */

#define IS_COMP_OUTPUT_POL(POL) (((POL) == COMP_OutputPol_NonInverted)  || \
                                 ((POL) == COMP_OutputPol_Inverted))

/**
  * @}
  */ 

/** @defgroup COMP_Hysteresis
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the hysteresis level */
#define COMP_Hysteresis_No                         0x00000000           /*!< No hysteresis */
#define COMP_Hysteresis_Low                        COMP_CSR_COMP1HYST_0 /*!< Hysteresis level low */
#define COMP_Hysteresis_Medium                     COMP_CSR_COMP1HYST_1 /*!< Hysteresis level medium */
#define COMP_Hysteresis_High                       COMP_CSR_COMP1HYST   /*!< Hysteresis level high */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_Hysteresis_No) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Low) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Medium) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_High))
/**
  * @}
  */

/** @defgroup COMP_Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_Mode_HighSpeed                     0x00000000            /*!< High Speed */
#define COMP_Mode_MediumSpeed                   COMP_CSR_COMP1MODE_0  /*!< Medium Speed */
#define COMP_Mode_LowPower                      COMP_CSR_COMP1MODE_1 /*!< Low power mode */
#define COMP_Mode_UltraLowPower                 COMP_CSR_COMP1MODE   /*!< Ultra-low power mode */

#define IS_COMP_MODE(MODE)    (((MODE) == COMP_Mode_UltraLowPower) || \
                               ((MODE) == COMP_Mode_LowPower)      || \
                               ((MODE) == COMP_Mode_MediumSpeed)   || \
                               ((MODE) == COMP_Mode_HighSpeed))
/**
  * @}
  */

/** @defgroup COMP_OutputLevel
  * @{
  */ 
/* When output polarity is not inverted, comparator output is high when
   the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OutputLevel_High                   COMP_CSR_COMP1OUT
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputLevel_Low                    ((uint32_t)0x00000000)

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_DeInit(void);

/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct);
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct);
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
void COMP_SwitchCmd(FunctionalState NewState);
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection);

/* Window mode control function ***********************************************/
void COMP_WindowCmd(FunctionalState NewState);

/* COMP configuration locking function ****************************************/
void COMP_LockConfig(uint32_t COMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_COMP_H */

/**
  * @}
  */ 

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_crc.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the CRC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_CRC_H
#define __STM32F0XX_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup CRC_ReverseInputData
  * @{
  */
#define CRC_ReverseInputData_No             ((uint32_t)0x00000000) /*!< No reverse operation of Input Data */
#define CRC_ReverseInputData_8bits          CRC_CR_REV_IN_0        /*!< Reverse operation of Input Data on 8 bits */
#define CRC_ReverseInputData_16bits         CRC_CR_REV_IN_1        /*!< Reverse operation of Input Data on 16 bits */
#define CRC_ReverseInputData_32bits         CRC_CR_REV_IN          /*!< Reverse operation of Input Data on 32 bits */

#define IS_CRC_REVERSE_INPUT_DATA(DATA) (((DATA) == CRC_ReverseInputData_No)     || \
                                         ((DATA) == CRC_ReverseInputData_8bits)  || \
                                         ((DATA) == CRC_ReverseInputData_16bits) || \
                                         ((DATA) == CRC_ReverseInputData_32bits))

/**
  * @}
  */

/** @defgroup CRC_PolynomialSize
  * @brief    Only applicable for STM32F042 and STM32F072 devices 
  * @{
  */
#define CRC_PolSize_7                       CRC_CR_POLSIZE        /*!< 7-bit polynomial for CRC calculation */
#define CRC_PolSize_8                       CRC_CR_POLSIZE_1      /*!< 8-bit polynomial for CRC calculation */
#define CRC_PolSize_16                      CRC_CR_POLSIZE_0      /*!< 16-bit polynomial for CRC calculation */
#define CRC_PolSize_32                      ((uint32_t)0x00000000)/*!< 32-bit polynomial for CRC calculation */

#define IS_CRC_POL_SIZE(SIZE) (((SIZE) == CRC_PolSize_7)  || \
                               ((SIZE) == CRC_PolSize_8)  || \
                               ((SIZE) == CRC_PolSize_16) || \
                               ((SIZE) == CRC_PolSize_32))

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Configuration of the CRC computation unit **********************************/
void CRC_DeInit(void);
void CRC_ResetDR(void);
void CRC_PolynomialSizeSelect(uint32_t CRC_PolSize); /*!< Only applicable for STM32F042 and STM32F072 devices */ 
void CRC_ReverseInputDataSelect(uint32_t CRC_ReverseInputData);
void CRC_ReverseOutputDataCmd(FunctionalState NewState);
void CRC_SetInitRegister(uint32_t CRC_InitValue); 
void CRC_SetPolynomial(uint32_t CRC_Pol); /*!< Only applicable for STM32F042 and STM32F072 devices */

/* CRC computation ************************************************************/
uint32_t CRC_CalcCRC(uint32_t CRC_Data);
uint32_t CRC_CalcCRC16bits(uint16_t CRC_Data); /*!< Only applicable for STM32F042 and STM32F072 devices */
uint32_t CRC_CalcCRC8bits(uint8_t CRC_Data); /*!< Only applicable for STM32F042 and STM32F072 devices */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);

/* Independent register (IDR) access (write/read) *****************************/
void CRC_SetIDRegister(uint8_t CRC_IDValue);
uint8_t CRC_GetIDRegister(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_CRC_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_crs.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the CRS firmware 
  *          library, applicable only for STM32F042 and STM32F072 devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_CRS_H
#define __STM32F0XX_CRS_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup CRS_Interrupt_Sources
  * @{
  */
#define CRS_IT_SYNCOK             CRS_ISR_SYNCOKF    /*!< SYNC event OK */
#define CRS_IT_SYNCWARN           CRS_ISR_SYNCWARNF  /*!< SYNC warning */
#define CRS_IT_ERR                CRS_ISR_ERRF       /*!< error */
#define CRS_IT_ESYNC              CRS_ISR_ESYNCF     /*!< Expected SYNC */
#define CRS_IT_TRIMOVF            CRS_ISR_TRIMOVF    /*!< Trimming overflow or underflow */
#define CRS_IT_SYNCERR            CRS_ISR_SYNCERR    /*!< SYNC error */
#define CRS_IT_SYNCMISS           CRS_ISR_SYNCMISS    /*!< SYNC missed*/

#define IS_CRS_IT(IT) (((IT) == CRS_IT_SYNCOK) || ((IT) == CRS_IT_SYNCWARN) || \
                       ((IT) == CRS_IT_ERR)  || ((IT) == CRS_IT_ESYNC))
                       
#define IS_CRS_GET_IT(IT) (((IT) == CRS_IT_SYNCOK) || ((IT) == CRS_IT_SYNCWARN) || \
                           ((IT) == CRS_IT_ERR) || ((IT) == CRS_IT_ESYNC) || \
                           ((IT) == CRS_IT_TRIMOVF) || ((IT) == CRS_IT_SYNCERR) || \
                           ((IT) == CRS_IT_SYNCMISS))

#define IS_CRS_CLEAR_IT(IT) ((IT) != 0x00)                                         

/**
  * @}
  */

/** @defgroup CRS_Flags
  * @{
  */
#define CRS_FLAG_SYNCOK             CRS_ISR_SYNCOKF    /*!< SYNC event OK */
#define CRS_FLAG_SYNCWARN           CRS_ISR_SYNCWARNF  /*!< SYNC warning */
#define CRS_FLAG_ERR                CRS_ISR_ERRF       /*!< error */
#define CRS_FLAG_ESYNC              CRS_ISR_ESYNCF     /*!< Expected SYNC */
#define CRS_FLAG_TRIMOVF            CRS_ISR_TRIMOVF    /*!< Trimming overflow or underflow */
#define CRS_FLAG_SYNCERR            CRS_ISR_SYNCERR    /*!< SYNC error */
#define CRS_FLAG_SYNCMISS           CRS_ISR_SYNCMISS    /*!< SYNC missed*/

#define IS_CRS_FLAG(FLAG) (((FLAG) == CRS_FLAG_SYNCOK) || ((FLAG) == CRS_FLAG_SYNCWARN) || \
                           ((FLAG) == CRS_FLAG_ERR) || ((FLAG) == CRS_FLAG_ESYNC) || \
                           ((FLAG) == CRS_FLAG_TRIMOVF) || ((FLAG) == CRS_FLAG_SYNCERR) || \
                           ((FLAG) == CRS_FLAG_SYNCMISS))

/**
  * @}
  */
  
/** @defgroup CRS_Synchro_Source
  * @{
  */
#define CRS_SYNCSource_GPIO       ((uint32_t)0x00)        /*!< Synchro Signal soucre GPIO */
#define CRS_SYNCSource_LSE        CRS_CFGR_SYNCSRC_0      /*!< Synchro Signal source LSE */
#define CRS_SYNCSource_USB        CRS_CFGR_SYNCSRC_1      /*!< Synchro Signal source USB SOF */

#define IS_CRS_SYNC_SOURCE(SOURCE) (((SOURCE) == CRS_SYNCSource_GPIO) || \
                                    ((SOURCE) == CRS_SYNCSource_LSE) ||\
                                    ((SOURCE) == CRS_SYNCSource_USB))
/**
  * @}
  */

/** @defgroup CRS_SynchroDivider
  * @{
  */
#define CRS_SYNC_Div1        ((uint32_t)0x00)                          /*!< Synchro Signal not divided */
#define CRS_SYNC_Div2        CRS_CFGR_SYNCDIV_0                        /*!< Synchro Signal divided by 2 */
#define CRS_SYNC_Div4        CRS_CFGR_SYNCDIV_1                        /*!< Synchro Signal divided by 4 */
#define CRS_SYNC_Div8        (CRS_CFGR_SYNCDIV_1 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 8 */
#define CRS_SYNC_Div16       CRS_CFGR_SYNCDIV_2                        /*!< Synchro Signal divided by 16 */
#define CRS_SYNC_Div32       (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 32 */
#define CRS_SYNC_Div64       (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_1) /*!< Synchro Signal divided by 64 */
#define CRS_SYNC_Div128      CRS_CFGR_SYNCDIV                          /*!< Synchro Signal divided by 128 */

#define IS_CRS_SYNC_DIV(DIV) (((DIV) == CRS_SYNC_Div1) || ((DIV) == CRS_SYNC_Div2)   ||\
                              ((DIV) == CRS_SYNC_Div4) || ((DIV) == CRS_SYNC_Div8)   || \
                              ((DIV) == CRS_SYNC_Div16) || ((DIV) == CRS_SYNC_Div32) || \
                              ((DIV) == CRS_SYNC_Div64) || ((DIV) == CRS_SYNC_Div128))
/**
  * @}
  */

/** @defgroup CRS_SynchroPolarity
  * @{
  */
#define CRS_SYNCPolarity_Rising       ((uint32_t)0x00)      /*!< Synchro Active on rising edge */
#define CRS_SYNCPolarity_Falling      CRS_CFGR_SYNCPOL      /*!< Synchro Active on falling edge */

#define IS_CRS_SYNC_POLARITY(POLARITY) (((POLARITY) == CRS_SYNCPolarity_Rising) || \
                                    ((POLARITY) == CRS_SYNCPolarity_Falling))
/**
  * @}
  */


    
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Configuration of the CRS **********************************/
void CRS_DeInit(void);
void CRS_AdjustHSI48CalibrationValue(uint8_t CRS_HSI48CalibrationValue);
void CRS_FrequencyErrorCounterCmd(FunctionalState NewState);
void CRS_AutomaticCalibrationCmd(FunctionalState NewState); 
void CRS_SoftwareSynchronizationGenerate(void);
void CRS_FrequencyErrorCounterReload(uint32_t CRS_ReloadValue);
void CRS_FrequencyErrorLimitConfig(uint8_t CRS_ErrorLimitValue);
void CRS_SynchronizationPrescalerConfig(uint32_t CRS_Prescaler);
void CRS_SynchronizationSourceConfig(uint32_t CRS_Source);
void CRS_SynchronizationPolarityConfig(uint32_t CRS_Polarity);
uint32_t CRS_GetReloadValue(void);
uint32_t CRS_GetHSI48CalibrationValue(void);
uint32_t CRS_GetFrequencyErrorValue(void);
uint32_t CRS_GetFrequencyErrorDirection(void);

/* Interrupts and flags management functions **********************************/
void CRS_ITConfig(uint32_t CRS_IT, FunctionalState NewState);
FlagStatus CRS_GetFlagStatus(uint32_t CRS_FLAG);
void CRS_ClearFlag(uint32_t CRS_FLAG);
ITStatus CRS_GetITStatus(uint32_t CRS_IT);
void CRS_ClearITPendingBit(uint32_t CRS_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_CRS_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_dac.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the DAC firmware 
  *          library, applicable only for STM32F051 and STM32F072 devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_DAC_H
#define __STM32F0XX_DAC_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup DAC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  DAC Init structure definition
  */
  
typedef struct
{
  uint32_t DAC_Trigger;                      /*!< Specifies the external trigger for the selected DAC channel.
                                                  This parameter can be a value of @ref DAC_trigger_selection */

  uint32_t DAC_WaveGeneration;               /*!< Specifies whether DAC channel noise waves or triangle waves
                                                  are generated, or whether no wave is generated.
                                                  This parameter can be a value of @ref DAC_wave_generation
                                                  This parameter is only applicable for STM32F072 devices */

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; /*!< Specifies the LFSR mask for noise wave generation or
                                                  the maximum amplitude triangle generation for the DAC channel. 
                                                  This parameter can be a value of @ref DAC_lfsrunmask_triangleamplitude 
                                                  This parameter is only applicable for STM32F072 devices */

  uint32_t DAC_OutputBuffer;                 /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                                  This parameter can be a value of @ref DAC_output_buffer */
}DAC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DAC_Exported_Constants
  * @{
  */

/** @defgroup DAC_Trigger 
  * @{
  */
  
#define DAC_Trigger_None                   ((uint32_t)0x00000000) /*!< Conversion is automatic once the DAC1_DHRxxxx register 
                                                                       has been loaded, and not by external trigger */
#define DAC_Trigger_T6_TRGO                ((uint32_t)0x00000004) /*!< TIM6 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T3_TRGO                ((uint32_t)0x0000000C) /*!< TIM3 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T7_TRGO                ((uint32_t)0x00000014) /*!< TIM7 TRGO selected as external conversion trigger for DAC channel1, 
                                                                       applicable only for STM32F072 devices */
#define DAC_Trigger_T15_TRGO               ((uint32_t)0x0000001C) /*!< TIM15 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T2_TRGO                ((uint32_t)0x00000024) /*!< TIM2 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_Ext_IT9                ((uint32_t)0x00000034) /*!< EXTI Line9 event selected as external conversion trigger for DAC channels */
#define DAC_Trigger_Software               ((uint32_t)0x0000003C) /*!< Conversion started by software trigger for DAC channels */

#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_None)     || \
                                 ((TRIGGER) == DAC_Trigger_T6_TRGO)  || \
                                 ((TRIGGER) == DAC_Trigger_T7_TRGO)  || \
                                 ((TRIGGER) == DAC_Trigger_T3_TRGO)  || \
                                 ((TRIGGER) == DAC_Trigger_T15_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T2_TRGO)  || \
                                 ((TRIGGER) == DAC_Trigger_Ext_IT9)  || \
                                 ((TRIGGER) == DAC_Trigger_Software))
                                 
/**
  * @}
  */

/** @defgroup DAC_wave_generation 
  * @brief    This parameters are only applicable for STM32F072 devices.
  * @{
  */

#define DAC_WaveGeneration_None            ((uint32_t)0x00000000)
#define DAC_WaveGeneration_Noise           ((uint32_t)0x00000040)
#define DAC_WaveGeneration_Triangle        ((uint32_t)0x00000080)
#define IS_DAC_GENERATE_WAVE(WAVE) (((WAVE) == DAC_WaveGeneration_None)  || \
                                    ((WAVE) == DAC_WaveGeneration_Noise) || \
                                    ((WAVE) == DAC_WaveGeneration_Triangle))
/**
  * @}
  */

/** @defgroup DAC_lfsrunmask_triangleamplitude   
  * @brief    These parameters are only applicable for STM32F072 devices.
  * @{
  */

#define DAC_LFSRUnmask_Bit0                ((uint32_t)0x00000000) /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUnmask_Bits1_0             ((uint32_t)0x00000100) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits2_0             ((uint32_t)0x00000200) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits3_0             ((uint32_t)0x00000300) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits4_0             ((uint32_t)0x00000400) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits5_0             ((uint32_t)0x00000500) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits6_0             ((uint32_t)0x00000600) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits7_0             ((uint32_t)0x00000700) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits8_0             ((uint32_t)0x00000800) /*!< Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits9_0             ((uint32_t)0x00000900) /*!< Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits10_0            ((uint32_t)0x00000A00) /*!< Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits11_0            ((uint32_t)0x00000B00) /*!< Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_TriangleAmplitude_1            ((uint32_t)0x00000000) /*!< Select max triangle amplitude of 1 */
#define DAC_TriangleAmplitude_3            ((uint32_t)0x00000100) /*!< Select max triangle amplitude of 3 */
#define DAC_TriangleAmplitude_7            ((uint32_t)0x00000200) /*!< Select max triangle amplitude of 7 */
#define DAC_TriangleAmplitude_15           ((uint32_t)0x00000300) /*!< Select max triangle amplitude of 15 */
#define DAC_TriangleAmplitude_31           ((uint32_t)0x00000400) /*!< Select max triangle amplitude of 31 */
#define DAC_TriangleAmplitude_63           ((uint32_t)0x00000500) /*!< Select max triangle amplitude of 63 */
#define DAC_TriangleAmplitude_127          ((uint32_t)0x00000600) /*!< Select max triangle amplitude of 127 */
#define DAC_TriangleAmplitude_255          ((uint32_t)0x00000700) /*!< Select max triangle amplitude of 255 */
#define DAC_TriangleAmplitude_511          ((uint32_t)0x00000800) /*!< Select max triangle amplitude of 511 */
#define DAC_TriangleAmplitude_1023         ((uint32_t)0x00000900) /*!< Select max triangle amplitude of 1023 */
#define DAC_TriangleAmplitude_2047         ((uint32_t)0x00000A00) /*!< Select max triangle amplitude of 2047 */
#define DAC_TriangleAmplitude_4095         ((uint32_t)0x00000B00) /*!< Select max triangle amplitude of 4095 */

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) (((VALUE) == DAC_LFSRUnmask_Bit0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits1_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits2_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits3_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits4_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits5_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits6_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits7_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits8_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits9_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits10_0) || \
                                                      ((VALUE) == DAC_LFSRUnmask_Bits11_0) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_1) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_3) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_7) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_15) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_31) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_63) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_127) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_255) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_511) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_1023) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_2047) || \
                                                      ((VALUE) == DAC_TriangleAmplitude_4095))
/**
  * @}
  */                                      

/** @defgroup DAC_OutputBuffer 
  * @{
  */

#define DAC_OutputBuffer_Enable            ((uint32_t)0x00000000)
#define DAC_OutputBuffer_Disable           DAC_CR_BOFF1
#define IS_DAC_OUTPUT_BUFFER_STATE(STATE) (((STATE) == DAC_OutputBuffer_Enable) || \
                                           ((STATE) == DAC_OutputBuffer_Disable))
/**
  * @}
  */
  
/** @defgroup DAC_Channel_selection 
  * @{
  */

#define DAC_Channel_1                      ((uint32_t)0x00000000)
#define DAC_Channel_2                      ((uint32_t)0x00000010) /*!< Only applicable for STM32F072 devices */
#define IS_DAC_CHANNEL(CHANNEL) (((CHANNEL) == DAC_Channel_1) || \
                                 ((CHANNEL) == DAC_Channel_2))

/**
  * @}
  */

/** @defgroup DAC_data_alignment
  * @{
  */

#define DAC_Align_12b_R                    ((uint32_t)0x00000000)
#define DAC_Align_12b_L                    ((uint32_t)0x00000004)
#define DAC_Align_8b_R                     ((uint32_t)0x00000008)
#define IS_DAC_ALIGN(ALIGN) (((ALIGN) == DAC_Align_12b_R) || \
                             ((ALIGN) == DAC_Align_12b_L) || \
                             ((ALIGN) == DAC_Align_8b_R))
/**
  * @}
  */

/** @defgroup DAC_wave_generation 
  * @brief    These parameters are only applicable for STM32F072 devices.
  * @{
  */

#define DAC_Wave_Noise                     ((uint32_t)0x00000040)
#define DAC_Wave_Triangle                  ((uint32_t)0x00000080)
#define IS_DAC_WAVE(WAVE) (((WAVE) == DAC_Wave_Noise) || \
                           ((WAVE) == DAC_Wave_Triangle))
/**
  * @}
  */
  
/** @defgroup DAC_data 
  * @{
  */

#define IS_DAC_DATA(DATA) ((DATA) <= 0xFFF0) 

/**
  * @}
  */

/** @defgroup DAC_interrupts_definition 
  * @{
  */ 
  
#define DAC_IT_DMAUDR                      DAC_SR_DMAUDR1
#define IS_DAC_IT(IT) (((IT) == DAC_IT_DMAUDR)) 

/**
  * @}
  */ 


/** @defgroup DAC_flags_definition 
  * @{
  */ 
  
#define DAC_FLAG_DMAUDR                    DAC_SR_DMAUDR1
  
#define IS_DAC_FLAG(FLAG) (((FLAG) == DAC_FLAG_DMAUDR))

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the DAC configuration to the default reset state *****/
void DAC_DeInit(void);

/*  DAC channels configuration: trigger, output buffer, data format functions */
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState); /*!< Only applicable for STM32F072 devices */
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState); /*!< Only applicable for STM32F072 devices */ 
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data); /*!< Only applicable for STM32F072 devices */
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1); /*!< Only applicable for STM32F072 devices */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);

/* DMA management functions ***************************************************/
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void DAC_ITConfig(uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState);
FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG);
void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG);
ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT);
void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_DAC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_dbgmcu.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the DBGMCU firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_DBGMCU_H
#define __STM32F0XX_DBGMCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup DBGMCU
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/


/** @defgroup DBGMCU_Exported_Constants
  * @{
  */

#define DBGMCU_STOP                  DBGMCU_CR_DBG_STOP
#define DBGMCU_STANDBY               DBGMCU_CR_DBG_STANDBY
#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFF9) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM2_STOP             DBGMCU_APB1_FZ_DBG_TIM2_STOP /*!< Not applicable for STM32F030 devices */
#define DBGMCU_TIM3_STOP             DBGMCU_APB1_FZ_DBG_TIM3_STOP
#define DBGMCU_TIM6_STOP             DBGMCU_APB1_FZ_DBG_TIM6_STOP
#define DBGMCU_TIM7_STOP             DBGMCU_APB1_FZ_DBG_TIM7_STOP /*!< Only applicable for STM32F072 devices */ 
#define DBGMCU_TIM14_STOP            DBGMCU_APB1_FZ_DBG_TIM14_STOP
#define DBGMCU_RTC_STOP              DBGMCU_APB1_FZ_DBG_RTC_STOP
#define DBGMCU_WWDG_STOP             DBGMCU_APB1_FZ_DBG_WWDG_STOP
#define DBGMCU_IWDG_STOP             DBGMCU_APB1_FZ_DBG_IWDG_STOP
#define DBGMCU_I2C1_SMBUS_TIMEOUT    DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT
#define DBGMCU_CAN1_STOP             DBGMCU_APB1_FZ_DBG_CAN1_STOP /*!< Only applicable for STM32F042 and STM32F072 devices */
#define IS_DBGMCU_APB1PERIPH(PERIPH) ((((PERIPH) & 0xFDDFE2CC) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM1_STOP             DBGMCU_APB2_FZ_DBG_TIM1_STOP
#define DBGMCU_TIM15_STOP            DBGMCU_APB2_FZ_DBG_TIM15_STOP
#define DBGMCU_TIM16_STOP            DBGMCU_APB2_FZ_DBG_TIM16_STOP
#define DBGMCU_TIM17_STOP            DBGMCU_APB2_FZ_DBG_TIM17_STOP
#define IS_DBGMCU_APB2PERIPH(PERIPH) ((((PERIPH) & 0xFFF8F7FF) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/* Device and Revision ID management functions ********************************/ 
uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);

/* Peripherals Configuration functions ****************************************/ 
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_DBGMCU_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_dma.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the DMA firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_DMA_H
#define __STM32F0XX_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  DMA Init structures definition
  */
typedef struct
{
  uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx.              */

  uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx.                  */

  uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction     */

  uint32_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel. 
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction     */

  uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */

  uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode     */

  uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_peripheral_data_size        */

  uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_memory_data_size            */

  uint32_t DMA_Mode;               /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_circular_normal_mode
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */

  uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level              */

  uint32_t DMA_M2M;                /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                        This parameter can be a value of @ref DMA_memory_to_memory            */
}DMA_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants
  * @{
  */

#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || \
                                   ((PERIPH) == DMA1_Channel2) || \
                                   ((PERIPH) == DMA1_Channel3) || \
                                   ((PERIPH) == DMA1_Channel4) || \
                                   ((PERIPH) == DMA1_Channel5) || \
                                   ((PERIPH) == DMA1_Channel6) || \
                                   ((PERIPH) == DMA1_Channel7) || \
                                   ((PERIPH) == DMA2_Channel1) || \
                                   ((PERIPH) == DMA2_Channel2) || \
                                   ((PERIPH) == DMA2_Channel3) || \
                                   ((PERIPH) == DMA2_Channel4) || \
                                   ((PERIPH) == DMA2_Channel5))

/** @defgroup DMA_data_transfer_direction 
  * @{
  */

#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)
#define DMA_DIR_PeripheralDST              DMA_CCR_DIR

#define IS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralSRC) || \
                         ((DIR) == DMA_DIR_PeripheralDST))
/**
  * @}
  */

/** @defgroup DMA_peripheral_incremented_mode 
  * @{
  */

#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)
#define DMA_PeripheralInc_Enable           DMA_CCR_PINC

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Disable) || \
                                            ((STATE) == DMA_PeripheralInc_Enable))
/**
  * @}
  */

/** @defgroup DMA_memory_incremented_mode 
  * @{
  */

#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)
#define DMA_MemoryInc_Enable               DMA_CCR_MINC

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Disable) || \
                                        ((STATE) == DMA_MemoryInc_Enable))
/**
  * @}
  */

/** @defgroup DMA_peripheral_data_size 
  * @{
  */

#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord    DMA_CCR_PSIZE_0
#define DMA_PeripheralDataSize_Word        DMA_CCR_PSIZE_1

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) || \
                                           ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
                                           ((SIZE) == DMA_PeripheralDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_memory_data_size 
  * @{
  */

#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord        DMA_CCR_MSIZE_0
#define DMA_MemoryDataSize_Word            DMA_CCR_MSIZE_1

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) || \
                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                       ((SIZE) == DMA_MemoryDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_circular_normal_mode 
  * @{
  */

#define DMA_Mode_Normal                    ((uint32_t)0x00000000)
#define DMA_Mode_Circular                  DMA_CCR_CIRC

#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Normal) || ((MODE) == DMA_Mode_Circular))
/**
  * @}
  */

/** @defgroup DMA_priority_level 
  * @{
  */

#define DMA_Priority_VeryHigh              DMA_CCR_PL
#define DMA_Priority_High                  DMA_CCR_PL_1
#define DMA_Priority_Medium                DMA_CCR_PL_0
#define DMA_Priority_Low                   ((uint32_t)0x00000000)

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
                                   ((PRIORITY) == DMA_Priority_High) || \
                                   ((PRIORITY) == DMA_Priority_Medium) || \
                                   ((PRIORITY) == DMA_Priority_Low))
/**
  * @}
  */

/** @defgroup DMA_memory_to_memory 
  * @{
  */

#define DMA_M2M_Disable                    ((uint32_t)0x00000000)
#define DMA_M2M_Enable                     DMA_CCR_MEM2MEM

#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Disable) || ((STATE) == DMA_M2M_Enable))

/**
  * @}
  */

/** @defgroup DMA_Remap_Config 
  * @{
  */ 
#define DMAx_CHANNEL1_RMP                                     0x00000000
#define DMAx_CHANNEL2_RMP                                     0x10000000
#define DMAx_CHANNEL3_RMP                                     0x20000000
#define DMAx_CHANNEL4_RMP                                     0x30000000
#define DMAx_CHANNEL5_RMP                                     0x40000000
#define DMAx_CHANNEL6_RMP                                     0x50000000
#define DMAx_CHANNEL7_RMP                                     0x60000000


#define IS_DMA_ALL_LIST(LIST) (((LIST) == DMA1) || \
                               ((LIST) == DMA2))

/****************** DMA1 remap bit field definition********************/
/* DMA1 - Channel 1 */
#define DMA1_CH1_DEFAULT      (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH1_ADC          (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_ADC)       /*!< Remap ADC on DMA1 Channel 1*/   
#define DMA1_CH1_TIM17_CH1    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 1 */
#define DMA1_CH1_TIM17_UP     (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 1 */ 
#define DMA1_CH1_USART1_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART2_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART3_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART4_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART5_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART6_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART7_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 1 */ 
#define DMA1_CH1_USART8_RX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR1_CH1_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 1 */ 
/* DMA1 - Channel 2 */
#define DMA1_CH2_DEFAULT      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH2_ADC          (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_ADC)       /*!< Remap ADC on DMA1 channel 2 */  
#define DMA1_CH2_I2C1_TX      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_I2C1_TX)   /*!< Remap I2C1 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_SPI1_RX      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_SPI_1RX)   /*!< Remap SPI1 Rx on DMA1 channel 2 */ 
#define DMA1_CH2_TIM1_CH1     (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_TIM1_CH1)  /*!< Remap TIM1 channel 1 on DMA1 channel 2 */
#define DMA1_CH2_TIM17_CH1    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 2 */
#define DMA1_CH2_TIM17_UP     (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 2 */ 
#define DMA1_CH2_USART1_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART2_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART3_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART4_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART5_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART6_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART7_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 2 */ 
#define DMA1_CH2_USART8_TX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR1_CH2_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 2 */ 
/* DMA1 - Channel 3 */
#define DMA1_CH3_DEFAULT      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMAx */   
#define DMA1_CH3_TIM6_UP      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM6_UP)   /*!< Remap TIM6 up on DMA1 channel 3 */ 
#define DMA1_CH3_DAC_CH1      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_DAC_CH1)   /*!< Remap DAC Channel 1on DMA1 channel 3 */ 
#define DMA1_CH3_I2C1_RX      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_I2C1_RX)   /*!< Remap I2C1 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_SPI1_TX      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_SPI1_TX)   /*!< Remap SPI1 Tx on DMA1 channel 3 */ 
#define DMA1_CH3_TIM1_CH2     (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM1_CH2)  /*!< Remap TIM1 channel 2 on DMA1 channel 3 */
#define DMA1_CH3_TIM2_CH2     (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM2_CH2)  /*!< Remap TIM2 channel 2 on DMA1 channel 3 */
#define DMA1_CH3_TIM16_CH1    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 3 */
#define DMA1_CH3_TIM16_UP     (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 3 */ 
#define DMA1_CH3_USART1_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART2_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART3_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART4_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART5_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART6_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART7_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 3 */ 
#define DMA1_CH3_USART8_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR1_CH3_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 3 */ 
/* DMA1 - Channel 4 */
#define DMA1_CH4_DEFAULT      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH4_TIM7_UP      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM7_UP)   /*!< Remap TIM7 up on DMA1 channel 4 */ 
#define DMA1_CH4_DAC_CH2      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_DAC_CH2)   /*!< Remap DAC Channel 2 on DMA1 channel 4 */
#define DMA1_CH4_I2C2_TX      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_I2C2_TX)   /*!< Remap I2C2 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_SPI2_RX      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_SPI2_RX)   /*!< Remap SPI2 Rx on DMA1 channel 4 */ 
#define DMA1_CH4_TIM2_CH4     (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM2_CH4)  /*!< Remap TIM2 channel 4 on DMA1 channel 4 */
#define DMA1_CH4_TIM3_CH1     (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM3_CH1)  /*!< Remap TIM3 channel 1 on DMA1 channel 4 */
#define DMA1_CH4_TIM3_TRIG    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM3_TRIG) /*!< Remap TIM3 Trig on DMA1 channel 4 */ 
#define DMA1_CH4_TIM16_CH1    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 4 */
#define DMA1_CH4_TIM16_UP     (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 4 */ 
#define DMA1_CH4_USART1_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART2_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART3_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART4_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART5_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART6_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART7_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 4 */ 
#define DMA1_CH4_USART8_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR1_CH4_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 4 */ 
/* DMA1 - Channel 5 */
#define DMA1_CH5_DEFAULT      (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH5_I2C2_RX      (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_I2C2_RX)   /*!< Remap I2C2 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_SPI2_TX      (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_SPI2_TX)   /*!< Remap SPI1 Tx on DMA1 channel 5 */ 
#define DMA1_CH5_TIM1_CH3     (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_TIM1_CH3)  /*!< Remap TIM1 channel 3 on DMA1 channel 5 */
#define DMA1_CH5_USART1_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART2_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART3_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART4_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART5_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART6_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART7_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 5 */ 
#define DMA1_CH5_USART8_RX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR1_CH5_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 5 */ 
/* DMA1 - Channel 6 */
#define DMA1_CH6_DEFAULT      (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH6_I2C1_TX      (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_I2C1_TX)   /*!< Remap I2C1 Tx on DMA1 channel 6 */ 
#define DMA1_CH6_SPI2_RX      (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_SPI2_RX)   /*!< Remap SPI2 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_TIM1_CH1     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM1_CH1)  /*!< Remap TIM1 channel 1 on DMA1 channel 6 */
#define DMA1_CH6_TIM1_CH2     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM1_CH2)  /*!< Remap TIM1 channel 2 on DMA1 channel 6 */
#define DMA1_CH6_TIM1_CH3     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM1_CH3)  /*!< Remap TIM1 channel 3 on DMA1 channel 6 */
#define DMA1_CH6_TIM3_CH1     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM3_CH1)  /*!< Remap TIM3 channel 1 on DMA1 channel 6 */
#define DMA1_CH6_TIM3_TRIG    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM3_TRIG) /*!< Remap TIM3 Trig on DMA1 channel 6 */ 
#define DMA1_CH6_TIM16_CH1    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 6 */
#define DMA1_CH6_TIM16_UP     (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 6 */ 
#define DMA1_CH6_USART1_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART2_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART3_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART4_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART5_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART6_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART7_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 6 */ 
#define DMA1_CH6_USART8_RX    (uint32_t) (DMAx_CHANNEL6_RMP | DMA_RMPCR1_CH6_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 6 */ 
/* DMA1 - Channel 7 */
#define DMA1_CH7_DEFAULT      (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_DEFAULT)       /*!< Default remap position for DMA1 */   
#define DMA1_CH7_I2C1_RX      (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_I2C1_RX)   /*!< Remap I2C1 Rx on DMA1 channel 7 */ 
#define DMA1_CH7_SPI2_TX      (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_SPI2_TX)   /*!< Remap SPI2 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_TIM2_CH2     (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_TIM2_CH2)  /*!< Remap TIM2 channel 2 on DMA1 channel 7 */
#define DMA1_CH7_TIM2_CH4     (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_TIM2_CH4)  /*!< Remap TIM2 channel 4 on DMA1 channel 7 */
#define DMA1_CH7_TIM17_CH1    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 7 */
#define DMA1_CH7_TIM17_UP     (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 7 */ 
#define DMA1_CH7_USART1_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART2_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART3_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART4_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART5_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART6_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART7_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 7 */ 
#define DMA1_CH7_USART8_TX    (uint32_t) (DMAx_CHANNEL7_RMP | DMA_RMPCR1_CH7_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 7 */

#define IS_DMA1_REMAP(REMAP)  ((REMAP == DMA1_CH1_DEFAULT)   ||\
                                    (REMAP == DMA1_CH1_ADC)       ||\
                                    (REMAP == DMA1_CH1_TIM17_CH1) ||\
                                    (REMAP == DMA1_CH1_TIM17_UP)  ||\
                                    (REMAP == DMA1_CH1_USART1_RX) ||\
                                    (REMAP == DMA1_CH1_USART2_RX) ||\
                                    (REMAP == DMA1_CH1_USART3_RX) ||\
                                    (REMAP == DMA1_CH1_USART4_RX) ||\
                                    (REMAP == DMA1_CH1_USART5_RX) ||\
                                    (REMAP == DMA1_CH1_USART6_RX) ||\
                                    (REMAP == DMA1_CH1_USART7_RX) ||\
                                    (REMAP == DMA1_CH1_USART8_RX) ||\
                                    (REMAP == DMA1_CH2_DEFAULT)   ||\
                                    (REMAP == DMA1_CH2_ADC)       ||\
                                    (REMAP == DMA1_CH2_I2C1_TX)   ||\
                                    (REMAP == DMA1_CH2_SPI1_RX)   ||\
                                    (REMAP == DMA1_CH2_TIM1_CH1)  ||\
                                    (REMAP == DMA1_CH2_I2C1_TX)   ||\
                                    (REMAP == DMA1_CH2_TIM17_CH1) ||\
                                    (REMAP == DMA1_CH2_TIM17_UP)  ||\
                                    (REMAP == DMA1_CH2_USART1_TX) ||\
                                    (REMAP == DMA1_CH2_USART2_TX) ||\
                                    (REMAP == DMA1_CH2_USART3_TX) ||\
                                    (REMAP == DMA1_CH2_USART4_TX) ||\
                                    (REMAP == DMA1_CH2_USART5_TX) ||\
                                    (REMAP == DMA1_CH2_USART6_TX) ||\
                                    (REMAP == DMA1_CH2_USART7_TX) ||\
                                    (REMAP == DMA1_CH2_USART8_TX) ||\
                                    (REMAP == DMA1_CH3_DEFAULT)   ||\
                                    (REMAP == DMA1_CH3_TIM6_UP)   ||\
                                    (REMAP == DMA1_CH3_DAC_CH1)   ||\
                                    (REMAP == DMA1_CH3_I2C1_RX)   ||\
                                    (REMAP == DMA1_CH3_SPI1_TX)   ||\
                                    (REMAP == DMA1_CH3_TIM1_CH2)  ||\
                                    (REMAP == DMA1_CH3_TIM2_CH2)  ||\
                                    (REMAP == DMA1_CH3_TIM16_CH1) ||\
                                    (REMAP == DMA1_CH3_TIM16_UP)  ||\
                                    (REMAP == DMA1_CH3_USART1_RX) ||\
                                    (REMAP == DMA1_CH3_USART2_RX) ||\
                                    (REMAP == DMA1_CH3_USART3_RX) ||\
                                    (REMAP == DMA1_CH3_USART4_RX) ||\
                                    (REMAP == DMA1_CH3_USART5_RX) ||\
                                    (REMAP == DMA1_CH3_USART6_RX) ||\
                                    (REMAP == DMA1_CH3_USART7_RX) ||\
                                    (REMAP == DMA1_CH3_USART8_RX) ||\
                                    (REMAP == DMA1_CH4_DEFAULT)   ||\
                                    (REMAP == DMA1_CH4_TIM7_UP)   ||\
                                    (REMAP == DMA1_CH4_DAC_CH2)   ||\
                                    (REMAP == DMA1_CH4_I2C2_TX)   ||\
                                    (REMAP == DMA1_CH4_SPI2_RX)   ||\
                                    (REMAP == DMA1_CH4_TIM2_CH4)  ||\
                                    (REMAP == DMA1_CH4_TIM3_CH1)  ||\
                                    (REMAP == DMA1_CH4_TIM3_TRIG) ||\
                                    (REMAP == DMA1_CH4_TIM16_CH1) ||\
                                    (REMAP == DMA1_CH4_TIM16_UP)  ||\
                                    (REMAP == DMA1_CH4_USART1_TX) ||\
                                    (REMAP == DMA1_CH4_USART2_TX) ||\
                                    (REMAP == DMA1_CH4_USART3_TX) ||\
                                    (REMAP == DMA1_CH4_USART4_TX) ||\
                                    (REMAP == DMA1_CH4_USART5_TX) ||\
                                    (REMAP == DMA1_CH4_USART6_TX) ||\
                                    (REMAP == DMA1_CH4_USART7_TX) ||\
                                    (REMAP == DMA1_CH4_USART8_TX) ||\
                                    (REMAP == DMA1_CH5_DEFAULT)   ||\
                                    (REMAP == DMA1_CH5_I2C2_RX)   ||\
                                    (REMAP == DMA1_CH5_SPI2_TX)   ||\
                                    (REMAP == DMA1_CH5_TIM1_CH3)  ||\
                                    (REMAP == DMA1_CH5_USART1_RX) ||\
                                    (REMAP == DMA1_CH5_USART2_RX) ||\
                                    (REMAP == DMA1_CH5_USART3_RX) ||\
                                    (REMAP == DMA1_CH5_USART4_RX) ||\
                                    (REMAP == DMA1_CH5_USART5_RX) ||\
                                    (REMAP == DMA1_CH5_USART6_RX) ||\
                                    (REMAP == DMA1_CH5_USART7_RX) ||\
                                    (REMAP == DMA1_CH5_USART8_RX) ||\
                                    (REMAP == DMA1_CH6_DEFAULT)   ||\
                                    (REMAP == DMA1_CH6_I2C1_TX)   ||\
                                    (REMAP == DMA1_CH6_SPI2_RX)   ||\
                                    (REMAP == DMA1_CH6_TIM1_CH1)  ||\
                                    (REMAP == DMA1_CH6_TIM1_CH2)  ||\
                                    (REMAP == DMA1_CH6_TIM1_CH3)  ||\
                                    (REMAP == DMA1_CH6_TIM3_CH1)  ||\
                                    (REMAP == DMA1_CH6_TIM3_TRIG) ||\
                                    (REMAP == DMA1_CH6_TIM16_CH1) ||\
                                    (REMAP == DMA1_CH6_TIM16_UP)  ||\
                                    (REMAP == DMA1_CH6_USART1_RX) ||\
                                    (REMAP == DMA1_CH6_USART2_RX) ||\
                                    (REMAP == DMA1_CH6_USART3_RX) ||\
                                    (REMAP == DMA1_CH6_USART4_RX) ||\
                                    (REMAP == DMA1_CH6_USART5_RX) ||\
                                    (REMAP == DMA1_CH6_USART6_RX) ||\
                                    (REMAP == DMA1_CH6_USART7_RX) ||\
                                    (REMAP == DMA1_CH6_USART8_RX) ||\
                                    (REMAP == DMA1_CH7_DEFAULT)   ||\
                                    (REMAP == DMA1_CH7_I2C1_RX)   ||\
                                    (REMAP == DMA1_CH7_SPI2_TX)   ||\
                                    (REMAP == DMA1_CH7_TIM2_CH2)  ||\
                                    (REMAP == DMA1_CH7_TIM2_CH4)  ||\
                                    (REMAP == DMA1_CH7_TIM17_CH1) ||\
                                    (REMAP == DMA1_CH7_TIM17_UP)  ||\
                                    (REMAP == DMA1_CH7_USART1_TX) ||\
                                    (REMAP == DMA1_CH7_USART2_TX) ||\
                                    (REMAP == DMA1_CH7_USART3_TX) ||\
                                    (REMAP == DMA1_CH7_USART4_TX) ||\
                                    (REMAP == DMA1_CH7_USART5_TX) ||\
                                    (REMAP == DMA1_CH7_USART6_TX) ||\
                                    (REMAP == DMA1_CH7_USART7_TX) ||\
                                    (REMAP == DMA1_CH7_USART8_TX))

/****************** DMA2 remap bit field definition********************/
/* DMA2 - Channel 1 */
#define DMA2_CH1_DEFAULT      (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH1_I2C2_TX      (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_I2C2_TX)   /*!< Remap I2C2 TX on DMA2 channel 1 */ 
#define DMA2_CH1_USART1_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART2_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART3_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART4_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART5_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART6_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART7_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 1 */ 
#define DMA2_CH1_USART8_TX    (uint32_t) (DMAx_CHANNEL1_RMP | DMA_RMPCR2_CH1_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 1 */ 
/* DMA2 - Channel 2 */
#define DMA2_CH2_DEFAULT      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH2_I2C2_RX      (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_I2C2_RX)   /*!< Remap I2C2 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART1_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART1_RX) /*!< Remap USART1 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART2_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART2_RX) /*!< Remap USART2 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART3_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART3_RX) /*!< Remap USART3 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART4_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART4_RX) /*!< Remap USART4 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART5_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART5_RX) /*!< Remap USART5 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART6_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART6_RX) /*!< Remap USART6 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART7_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART7_RX) /*!< Remap USART7 Rx on DMA2 channel 2 */ 
#define DMA2_CH2_USART8_RX    (uint32_t) (DMAx_CHANNEL2_RMP | DMA_RMPCR2_CH2_USART8_RX) /*!< Remap USART8 Rx on DMA2 channel 2 */ 
/* DMA2 - Channel 3 */
#define DMA2_CH3_DEFAULT      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH3_TIM6_UP      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_TIM6_UP)   /*!< Remap TIM6 up on DMA2 channel 3 */ 
#define DMA2_CH3_DAC_CH1      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_DAC_CH1)   /*!< Remap DAC channel 1 on DMA2 channel 3 */
#define DMA2_CH3_SPI1_RX      (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_SPI1_RX)   /*!< Remap SPI1 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART1_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART1_RX) /*!< Remap USART1 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART2_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART2_RX) /*!< Remap USART2 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART3_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART3_RX) /*!< Remap USART3 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART4_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART4_RX) /*!< Remap USART4 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART5_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART5_RX) /*!< Remap USART5 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART6_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART6_RX) /*!< Remap USART6 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART7_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART7_RX) /*!< Remap USART7 Rx on DMA2 channel 3 */ 
#define DMA2_CH3_USART8_RX    (uint32_t) (DMAx_CHANNEL3_RMP | DMA_RMPCR2_CH3_USART8_RX) /*!< Remap USART8 Rx on DMA2 channel 3 */ 
/* DMA2 - Channel 4 */
#define DMA2_CH4_DEFAULT      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH4_TIM7_UP      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_TIM7_UP)   /*!< Remap TIM7 up on DMA2 channel 4 */ 
#define DMA2_CH4_DAC_CH2      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_DAC_CH2)   /*!< Remap DAC channel 2 on DMA2 channel 4 */
#define DMA2_CH4_SPI1_TX      (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_SPI1_TX)   /*!< Remap SPI1 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART1_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART2_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART3_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART4_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART5_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART6_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART7_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 4 */ 
#define DMA2_CH4_USART8_TX    (uint32_t) (DMAx_CHANNEL4_RMP | DMA_RMPCR2_CH4_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 4 */ 
/* DMA2 - Channel 5 */
#define DMA2_CH5_DEFAULT      (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_DEFAULT)       /*!< Default remap position for DMA2 */   
#define DMA2_CH5_ADC          (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_ADC)       /*!< Remap ADC on DMA2 channel 5 */  
#define DMA2_CH5_USART1_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART2_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART3_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART4_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART5_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART6_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART7_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 5 */ 
#define DMA2_CH5_USART8_TX    (uint32_t) (DMAx_CHANNEL5_RMP | DMA_RMPCR2_CH5_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 5 */ 

#define IS_DMA2_REMAP(REMAP)  ((REMAP == DMA2_CH1_DEFAULT)   ||\
                                    (REMAP == DMA2_CH1_I2C2_TX)   ||\
                                    (REMAP == DMA2_CH1_USART1_TX) ||\
                                    (REMAP == DMA2_CH1_USART2_TX) ||\
                                    (REMAP == DMA2_CH1_USART3_TX) ||\
                                    (REMAP == DMA2_CH1_USART4_TX) ||\
                                    (REMAP == DMA2_CH1_USART5_TX) ||\
                                    (REMAP == DMA2_CH1_USART6_TX) ||\
                                    (REMAP == DMA2_CH1_USART7_TX) ||\
                                    (REMAP == DMA2_CH1_USART8_TX) ||\
                                    (REMAP == DMA2_CH2_DEFAULT)   ||\
                                    (REMAP == DMA2_CH2_I2C2_RX)   ||\
                                    (REMAP == DMA2_CH2_USART1_RX) ||\
                                    (REMAP == DMA2_CH2_USART2_RX) ||\
                                    (REMAP == DMA2_CH2_USART3_RX) ||\
                                    (REMAP == DMA2_CH2_USART4_RX) ||\
                                    (REMAP == DMA2_CH2_USART5_RX) ||\
                                    (REMAP == DMA2_CH2_USART6_RX) ||\
                                    (REMAP == DMA2_CH2_USART7_RX) ||\
                                    (REMAP == DMA2_CH2_USART8_RX) ||\
                                    (REMAP == DMA2_CH3_DEFAULT)   ||\
                                    (REMAP == DMA2_CH3_TIM6_UP)   ||\
                                    (REMAP == DMA2_CH3_DAC_CH1)   ||\
                                    (REMAP == DMA2_CH3_SPI1_RX)   ||\
                                    (REMAP == DMA2_CH3_USART1_RX) ||\
                                    (REMAP == DMA2_CH3_USART2_RX) ||\
                                    (REMAP == DMA2_CH3_USART3_RX) ||\
                                    (REMAP == DMA2_CH3_USART4_RX) ||\
                                    (REMAP == DMA2_CH3_USART5_RX) ||\
                                    (REMAP == DMA2_CH3_USART6_RX) ||\
                                    (REMAP == DMA2_CH3_USART7_RX) ||\
                                    (REMAP == DMA2_CH3_USART8_RX) ||\
                                    (REMAP == DMA2_CH4_DEFAULT)   ||\
                                    (REMAP == DMA2_CH4_TIM7_UP)   ||\
                                    (REMAP == DMA2_CH4_DAC_CH2)   ||\
                                    (REMAP == DMA2_CH4_SPI1_TX)   ||\
                                    (REMAP == DMA2_CH4_USART1_TX) ||\
                                    (REMAP == DMA2_CH4_USART2_TX) ||\
                                    (REMAP == DMA2_CH4_USART3_TX) ||\
                                    (REMAP == DMA2_CH4_USART4_TX) ||\
                                    (REMAP == DMA2_CH4_USART5_TX) ||\
                                    (REMAP == DMA2_CH4_USART6_TX) ||\
                                    (REMAP == DMA2_CH4_USART7_TX) ||\
                                    (REMAP == DMA2_CH4_USART8_TX) ||\
                                    (REMAP == DMA2_CH5_DEFAULT)   ||\
                                    (REMAP == DMA2_CH5_ADC)       ||\
                                    (REMAP == DMA2_CH5_USART1_TX) ||\
                                    (REMAP == DMA2_CH5_USART2_TX) ||\
                                    (REMAP == DMA2_CH5_USART3_TX) ||\
                                    (REMAP == DMA2_CH5_USART4_TX) ||\
                                    (REMAP == DMA2_CH5_USART5_TX) ||\
                                    (REMAP == DMA2_CH5_USART6_TX) ||\
                                    (REMAP == DMA2_CH5_USART7_TX) ||\
                                    (REMAP == DMA2_CH5_USART8_TX ))

/**
  * @}
  */
  
/** @defgroup DMA_interrupts_definition
  * @{
  */

#define DMA_IT_TC                          DMA_CCR_TCIE
#define DMA_IT_HT                          DMA_CCR_HTIE
#define DMA_IT_TE                          DMA_CCR_TEIE

#define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00))

#define DMA1_IT_GL1                        DMA_ISR_GIF1
#define DMA1_IT_TC1                        DMA_ISR_TCIF1
#define DMA1_IT_HT1                        DMA_ISR_HTIF1
#define DMA1_IT_TE1                        DMA_ISR_TEIF1
#define DMA1_IT_GL2                        DMA_ISR_GIF2
#define DMA1_IT_TC2                        DMA_ISR_TCIF2
#define DMA1_IT_HT2                        DMA_ISR_HTIF2
#define DMA1_IT_TE2                        DMA_ISR_TEIF2
#define DMA1_IT_GL3                        DMA_ISR_GIF3
#define DMA1_IT_TC3                        DMA_ISR_TCIF3
#define DMA1_IT_HT3                        DMA_ISR_HTIF3
#define DMA1_IT_TE3                        DMA_ISR_TEIF3
#define DMA1_IT_GL4                        DMA_ISR_GIF4
#define DMA1_IT_TC4                        DMA_ISR_TCIF4
#define DMA1_IT_HT4                        DMA_ISR_HTIF4
#define DMA1_IT_TE4                        DMA_ISR_TEIF4
#define DMA1_IT_GL5                        DMA_ISR_GIF5
#define DMA1_IT_TC5                        DMA_ISR_TCIF5
#define DMA1_IT_HT5                        DMA_ISR_HTIF5
#define DMA1_IT_TE5                        DMA_ISR_TEIF5
#define DMA1_IT_GL6                        DMA_ISR_GIF6   /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_IT_TC6                        DMA_ISR_TCIF6  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_IT_HT6                        DMA_ISR_HTIF6  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_IT_TE6                        DMA_ISR_TEIF6  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_IT_GL7                        DMA_ISR_GIF7   /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_IT_TC7                        DMA_ISR_TCIF7  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_IT_HT7                        DMA_ISR_HTIF7  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_IT_TE7                        DMA_ISR_TEIF7  /*!< Only applicable for STM32F072 and STM32F091 devices */

#define DMA2_IT_GL1                        ((uint32_t)0x10000001)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TC1                        ((uint32_t)0x10000002)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_HT1                        ((uint32_t)0x10000004)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TE1                        ((uint32_t)0x10000008)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_GL2                        ((uint32_t)0x10000010)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TC2                        ((uint32_t)0x10000020)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_HT2                        ((uint32_t)0x10000040)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TE2                        ((uint32_t)0x10000080)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_GL3                        ((uint32_t)0x10000100)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TC3                        ((uint32_t)0x10000200)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_HT3                        ((uint32_t)0x10000400)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TE3                        ((uint32_t)0x10000800)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_GL4                        ((uint32_t)0x10001000)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TC4                        ((uint32_t)0x10002000)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_HT4                        ((uint32_t)0x10004000)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TE4                        ((uint32_t)0x10008000)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_GL5                        ((uint32_t)0x10010000)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TC5                        ((uint32_t)0x10020000)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_HT5                        ((uint32_t)0x10040000)  /*!< Only applicable for STM32F091 devices */
#define DMA2_IT_TE5                        ((uint32_t)0x10080000)  /*!< Only applicable for STM32F091 devices */

#define IS_DMA_CLEAR_IT(IT) (((((IT) & 0xF0000000) == 0x00) || (((IT) & 0xEFF00000) == 0x00)) && ((IT) != 0x00))

#define IS_DMA_GET_IT(IT) (((IT) == DMA1_IT_GL1) || ((IT) == DMA1_IT_TC1) || \
                           ((IT) == DMA1_IT_HT1) || ((IT) == DMA1_IT_TE1) || \
                           ((IT) == DMA1_IT_GL2) || ((IT) == DMA1_IT_TC2) || \
                           ((IT) == DMA1_IT_HT2) || ((IT) == DMA1_IT_TE2) || \
                           ((IT) == DMA1_IT_GL3) || ((IT) == DMA1_IT_TC3) || \
                           ((IT) == DMA1_IT_HT3) || ((IT) == DMA1_IT_TE3) || \
                           ((IT) == DMA1_IT_GL4) || ((IT) == DMA1_IT_TC4) || \
                           ((IT) == DMA1_IT_HT4) || ((IT) == DMA1_IT_TE4) || \
                           ((IT) == DMA1_IT_GL5) || ((IT) == DMA1_IT_TC5) || \
                           ((IT) == DMA1_IT_HT5) || ((IT) == DMA1_IT_TE5) || \
                           ((IT) == DMA1_IT_GL6) || ((IT) == DMA1_IT_TC6) || \
                           ((IT) == DMA1_IT_HT6) || ((IT) == DMA1_IT_TE6) || \
                           ((IT) == DMA1_IT_GL7) || ((IT) == DMA1_IT_TC7) || \
                           ((IT) == DMA1_IT_HT7) || ((IT) == DMA1_IT_TE7) || \
                           ((IT) == DMA2_IT_GL1) || ((IT) == DMA2_IT_TC1) || \
                           ((IT) == DMA2_IT_HT1) || ((IT) == DMA2_IT_TE1) || \
                           ((IT) == DMA2_IT_GL2) || ((IT) == DMA2_IT_TC2) || \
                           ((IT) == DMA2_IT_HT2) || ((IT) == DMA2_IT_TE2) || \
                           ((IT) == DMA2_IT_GL3) || ((IT) == DMA2_IT_TC3) || \
                           ((IT) == DMA2_IT_HT3) || ((IT) == DMA2_IT_TE3) || \
                           ((IT) == DMA2_IT_GL4) || ((IT) == DMA2_IT_TC4) || \
                           ((IT) == DMA2_IT_HT4) || ((IT) == DMA2_IT_TE4) || \
                           ((IT) == DMA2_IT_GL5) || ((IT) == DMA2_IT_TC5) || \
                           ((IT) == DMA2_IT_HT5) || ((IT) == DMA2_IT_TE5))

/**
  * @}
  */

/** @defgroup DMA_flags_definition 
  * @{
  */
#define DMA1_FLAG_GL1                      DMA_ISR_GIF1
#define DMA1_FLAG_TC1                      DMA_ISR_TCIF1
#define DMA1_FLAG_HT1                      DMA_ISR_HTIF1
#define DMA1_FLAG_TE1                      DMA_ISR_TEIF1
#define DMA1_FLAG_GL2                      DMA_ISR_GIF2
#define DMA1_FLAG_TC2                      DMA_ISR_TCIF2
#define DMA1_FLAG_HT2                      DMA_ISR_HTIF2
#define DMA1_FLAG_TE2                      DMA_ISR_TEIF2
#define DMA1_FLAG_GL3                      DMA_ISR_GIF3
#define DMA1_FLAG_TC3                      DMA_ISR_TCIF3
#define DMA1_FLAG_HT3                      DMA_ISR_HTIF3
#define DMA1_FLAG_TE3                      DMA_ISR_TEIF3
#define DMA1_FLAG_GL4                      DMA_ISR_GIF4
#define DMA1_FLAG_TC4                      DMA_ISR_TCIF4
#define DMA1_FLAG_HT4                      DMA_ISR_HTIF4
#define DMA1_FLAG_TE4                      DMA_ISR_TEIF4
#define DMA1_FLAG_GL5                      DMA_ISR_GIF5
#define DMA1_FLAG_TC5                      DMA_ISR_TCIF5
#define DMA1_FLAG_HT5                      DMA_ISR_HTIF5
#define DMA1_FLAG_TE5                      DMA_ISR_TEIF5
#define DMA1_FLAG_GL6                      DMA_ISR_GIF6   /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_FLAG_TC6                      DMA_ISR_TCIF6  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_FLAG_HT6                      DMA_ISR_HTIF6  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_FLAG_TE6                      DMA_ISR_TEIF6  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_FLAG_GL7                      DMA_ISR_GIF7   /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_FLAG_TC7                      DMA_ISR_TCIF7  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_FLAG_HT7                      DMA_ISR_HTIF7  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_FLAG_TE7                      DMA_ISR_TEIF7  /*!< Only applicable for STM32F072 and STM32F091 devices */

#define DMA2_FLAG_GL1                      ((uint32_t)0x10000001)
#define DMA2_FLAG_TC1                      ((uint32_t)0x10000002)
#define DMA2_FLAG_HT1                      ((uint32_t)0x10000004)
#define DMA2_FLAG_TE1                      ((uint32_t)0x10000008)
#define DMA2_FLAG_GL2                      ((uint32_t)0x10000010)
#define DMA2_FLAG_TC2                      ((uint32_t)0x10000020)
#define DMA2_FLAG_HT2                      ((uint32_t)0x10000040)
#define DMA2_FLAG_TE2                      ((uint32_t)0x10000080)
#define DMA2_FLAG_GL3                      ((uint32_t)0x10000100)
#define DMA2_FLAG_TC3                      ((uint32_t)0x10000200)
#define DMA2_FLAG_HT3                      ((uint32_t)0x10000400)
#define DMA2_FLAG_TE3                      ((uint32_t)0x10000800)
#define DMA2_FLAG_GL4                      ((uint32_t)0x10001000)
#define DMA2_FLAG_TC4                      ((uint32_t)0x10002000)
#define DMA2_FLAG_HT4                      ((uint32_t)0x10004000)
#define DMA2_FLAG_TE4                      ((uint32_t)0x10008000)
#define DMA2_FLAG_GL5                      ((uint32_t)0x10010000)
#define DMA2_FLAG_TC5                      ((uint32_t)0x10020000)
#define DMA2_FLAG_HT5                      ((uint32_t)0x10040000)
#define DMA2_FLAG_TE5                      ((uint32_t)0x10080000)

#define IS_DMA_CLEAR_FLAG(FLAG) (((((FLAG) & 0xF0000000) == 0x00) || (((FLAG) & 0xEFF00000) == 0x00)) && ((FLAG) != 0x00))

#define IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA1_FLAG_GL1) || ((FLAG) == DMA1_FLAG_TC1) || \
                               ((FLAG) == DMA1_FLAG_HT1) || ((FLAG) == DMA1_FLAG_TE1) || \
                               ((FLAG) == DMA1_FLAG_GL2) || ((FLAG) == DMA1_FLAG_TC2) || \
                               ((FLAG) == DMA1_FLAG_HT2) || ((FLAG) == DMA1_FLAG_TE2) || \
                               ((FLAG) == DMA1_FLAG_GL3) || ((FLAG) == DMA1_FLAG_TC3) || \
                               ((FLAG) == DMA1_FLAG_HT3) || ((FLAG) == DMA1_FLAG_TE3) || \
                               ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC4) || \
                               ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE4) || \
                               ((FLAG) == DMA1_FLAG_GL5) || ((FLAG) == DMA1_FLAG_TC5) || \
                               ((FLAG) == DMA1_FLAG_HT5) || ((FLAG) == DMA1_FLAG_TE5) || \
                               ((FLAG) == DMA1_FLAG_GL6) || ((FLAG) == DMA1_FLAG_TC6) || \
                               ((FLAG) == DMA1_FLAG_HT6) || ((FLAG) == DMA1_FLAG_TE6) || \
                               ((FLAG) == DMA1_FLAG_GL7) || ((FLAG) == DMA1_FLAG_TC7) || \
                               ((FLAG) == DMA1_FLAG_HT7) || ((FLAG) == DMA1_FLAG_TE7) || \
                               ((FLAG) == DMA2_FLAG_GL1) || ((FLAG) == DMA2_FLAG_TC1) || \
                               ((FLAG) == DMA2_FLAG_HT1) || ((FLAG) == DMA2_FLAG_TE1) || \
                               ((FLAG) == DMA2_FLAG_GL2) || ((FLAG) == DMA2_FLAG_TC2) || \
                               ((FLAG) == DMA2_FLAG_HT2) || ((FLAG) == DMA2_FLAG_TE2) || \
                               ((FLAG) == DMA2_FLAG_GL3) || ((FLAG) == DMA2_FLAG_TC3) || \
                               ((FLAG) == DMA2_FLAG_HT3) || ((FLAG) == DMA2_FLAG_TE3) || \
                               ((FLAG) == DMA2_FLAG_GL4) || ((FLAG) == DMA2_FLAG_TC4) || \
                               ((FLAG) == DMA2_FLAG_HT4) || ((FLAG) == DMA2_FLAG_TE4) || \
                               ((FLAG) == DMA2_FLAG_GL5) || ((FLAG) == DMA2_FLAG_TC5) || \
                               ((FLAG) == DMA2_FLAG_HT5) || ((FLAG) == DMA2_FLAG_TE5))
/**
  * @}
  */

/** @defgroup DMA_Buffer_Size 
  * @{
  */

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the DMA configuration to the default reset state ******/
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);

/* Initialization and Configuration functions *********************************/
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
void DMA_RemapConfig(DMA_TypeDef* DMAy, uint32_t DMAx_CHy_RemapRequest);

/* Data Counter functions******************************************************/ 
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);

/* Interrupts and flags management functions **********************************/
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
void DMA_ClearFlag(uint32_t DMAy_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_DMA_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_exti.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the EXTI 
  *          firmware library
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_EXTI_H
#define __STM32F0XX_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  EXTI mode enumeration  
  */

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

/** 
  * @brief  EXTI Trigger enumeration  
  */

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
/**
  * @brief  EXTI Init Structure definition
  */

typedef struct
{
  uint32_t EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.
                                         This parameter can be any combination of @ref EXTI_Lines */

  EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI lines.
                                         This parameter can be set either to ENABLE or DISABLE */
}EXTI_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup EXTI_Exported_Constants
  * @{
  */
/** @defgroup EXTI_Lines 
  * @{
  */

#define EXTI_Line0       ((uint32_t)0x00000001)  /*!< External interrupt line 0  */
#define EXTI_Line1       ((uint32_t)0x00000002)  /*!< External interrupt line 1  */
#define EXTI_Line2       ((uint32_t)0x00000004)  /*!< External interrupt line 2  */
#define EXTI_Line3       ((uint32_t)0x00000008)  /*!< External interrupt line 3  */
#define EXTI_Line4       ((uint32_t)0x00000010)  /*!< External interrupt line 4  */
#define EXTI_Line5       ((uint32_t)0x00000020)  /*!< External interrupt line 5  */
#define EXTI_Line6       ((uint32_t)0x00000040)  /*!< External interrupt line 6  */
#define EXTI_Line7       ((uint32_t)0x00000080)  /*!< External interrupt line 7  */
#define EXTI_Line8       ((uint32_t)0x00000100)  /*!< External interrupt line 8  */
#define EXTI_Line9       ((uint32_t)0x00000200)  /*!< External interrupt line 9  */
#define EXTI_Line10      ((uint32_t)0x00000400)  /*!< External interrupt line 10 */
#define EXTI_Line11      ((uint32_t)0x00000800)  /*!< External interrupt line 11 */
#define EXTI_Line12      ((uint32_t)0x00001000)  /*!< External interrupt line 12 */
#define EXTI_Line13      ((uint32_t)0x00002000)  /*!< External interrupt line 13 */
#define EXTI_Line14      ((uint32_t)0x00004000)  /*!< External interrupt line 14 */
#define EXTI_Line15      ((uint32_t)0x00008000)  /*!< External interrupt line 15 */
#define EXTI_Line16      ((uint32_t)0x00010000)  /*!< External interrupt line 16 
                                                      Connected to the PVD Output, 
                                                      not applicable for STM32F030 devices */
#define EXTI_Line17      ((uint32_t)0x00020000)  /*!< Internal interrupt line 17 
                                                      Connected to the RTC Alarm 
                                                      event */
#define EXTI_Line18      ((uint32_t)0x00040000)  /*!< Internal interrupt line 18 
                                                      Connected to the USB
                                                      event, only applicable for 
                                                      STM32F072 devices */
#define EXTI_Line19      ((uint32_t)0x00080000)  /*!< Internal interrupt line 19
                                                      Connected to the RTC Tamper
                                                      and Time Stamp events */
#define EXTI_Line20      ((uint32_t)0x00100000)   /*!< Internal interrupt line 20
                                                      Connected to the RTC wakeup
                                                      event, only applicable for 
                                                      STM32F072 devices  */ 
#define EXTI_Line21      ((uint32_t)0x00200000)  /*!< Internal interrupt line 21
                                                      Connected to the Comparator 1
                                                      event, only applicable for STM32F051
                                                      ans STM32F072 devices */
#define EXTI_Line22      ((uint32_t)0x00400000)  /*!< Internal interrupt line 22
                                                      Connected to the Comparator 2
                                                      event, only applicable for STM32F051
                                                      and STM32F072 devices */
#define EXTI_Line23      ((uint32_t)0x00800000)  /*!< Internal interrupt line 23
                                                      Connected to the I2C1 wakeup
                                                      event, not applicable for STM32F030 devices */
#define EXTI_Line25      ((uint32_t)0x02000000)  /*!< Internal interrupt line 25
                                                      Connected to the USART1 wakeup
                                                      event, not applicable for STM32F030 devices */
#define EXTI_Line26      ((uint32_t)0x04000000)  /*!< Internal interrupt line 26
                                                      Connected to the USART2 wakeup
                                                      event, applicable only for 
                                                      STM32F072 devices */
#define EXTI_Line27      ((uint32_t)0x08000000)  /*!< Internal interrupt line 27
                                                      Connected to the CEC wakeup
                                                      event, applicable only for STM32F051
                                                      and STM32F072 devices */
#define EXTI_Line31      ((uint32_t)0x80000000)  /*!< Internal interrupt line 31
                                                      Connected to the VDD USB monitor
                                                      event, applicable only for 
                                                      STM32F072 devices */
#define IS_EXTI_LINE(LINE) ((((LINE) & (uint32_t)0x71000000) == 0x00) && ((LINE) != (uint16_t)0x00))

#define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) || \
                                ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) || \
                                ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) || \
                                ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) || \
                                ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) || \
                                ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                                ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                                ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                                ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                                ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19) || \
                                ((LINE) == EXTI_Line20) || ((LINE) == EXTI_Line21) || \
                                ((LINE) == EXTI_Line22) || ((LINE) == EXTI_Line23) || \
                                ((LINE) == EXTI_Line25) || ((LINE) == EXTI_Line26) || \
                                ((LINE) == EXTI_Line27) || ((LINE) == EXTI_Line31))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Function used to set the EXTI configuration to the default reset state *****/
void EXTI_DeInit(void);

/* Initialization and Configuration functions *********************************/
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);

/* Interrupts and flags management functions **********************************/
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_EXTI_H */
/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_flash.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the FLASH 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_FLASH_H
#define __STM32F0XX_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  FLASH Status
  */ 
typedef enum
{
  FLASH_BUSY = 1,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;

/* Exported constants --------------------------------------------------------*/
  
/** @defgroup FLASH_Exported_Constants
  * @{
  */ 
  
/** @defgroup FLASH_Latency 
  * @{
  */ 
#define FLASH_Latency_0                ((uint32_t)0x00000000)  /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                FLASH_ACR_LATENCY       /*!< FLASH One Latency cycle */

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1))
/**
  * @}
  */ 

/** @defgroup FLASH_Interrupts 
  * @{
  */
   
#define FLASH_IT_EOP                   FLASH_CR_EOPIE  /*!< End of programming interrupt source */
#define FLASH_IT_ERR                   FLASH_CR_ERRIE  /*!< Error interrupt source */
#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFFFEBFF) == 0x00000000) && (((IT) != 0x00000000)))
/**
  * @}
  */ 

/** @defgroup FLASH_Address 
  * @{
  */
#if defined(STM32F042) || defined(STM32F031) || defined(STM32F070x6)      /*32K devices */
 #define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x08007FFF))
#elif defined(STM32F030) || defined(STM32F051)                            /*64K devices */
 #define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0800FFFF))
#elif defined(STM32F072) || defined(STM32F070xB)                          /*128K devices */
 #define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0801FFFF))
#else /* STM32F091 || STM32F030 || STM32F030xC  */                        /*256K Flash devices */
 #define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0800FFFF))
#endif /* STM32F042 || STM32F031 || STM32F070x6 */
/**
  * @}
  */

/** @defgroup FLASH_OB_DATA_ADDRESS 
  * @{
  */  
#define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) == 0x1FFFF804) || ((ADDRESS) == 0x1FFFF806)) 

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_Write_Protection 
  * @{
  */
  
#if !defined (STM32F072) && !defined (STM32F070xB) && !defined (STM32F091) && !defined (STM32F030) && !defined (STM32F030xC)  /* 32K and 64K Flash devices */  
#define OB_WRP_Pages0to3               ((uint32_t)0x00000001) /* Write protection of page 0 to 3 */
#define OB_WRP_Pages4to7               ((uint32_t)0x00000002) /* Write protection of page 4 to 7 */
#define OB_WRP_Pages8to11              ((uint32_t)0x00000004) /* Write protection of page 8 to 11 */
#define OB_WRP_Pages12to15             ((uint32_t)0x00000008) /* Write protection of page 12 to 15 */
#define OB_WRP_Pages16to19             ((uint32_t)0x00000010) /* Write protection of page 16 to 19 */
#define OB_WRP_Pages20to23             ((uint32_t)0x00000020) /* Write protection of page 20 to 23 */
#define OB_WRP_Pages24to27             ((uint32_t)0x00000040) /* Write protection of page 24 to 27 */
#define OB_WRP_Pages28to31             ((uint32_t)0x00000080) /* Write protection of page 28 to 31 */
#define OB_WRP_Pages32to35             ((uint32_t)0x00000100) /* Write protection of page 32 to 35 */
#define OB_WRP_Pages36to39             ((uint32_t)0x00000200) /* Write protection of page 36 to 39 */
#define OB_WRP_Pages40to43             ((uint32_t)0x00000400) /* Write protection of page 40 to 43 */
#define OB_WRP_Pages44to47             ((uint32_t)0x00000800) /* Write protection of page 44 to 47 */
#define OB_WRP_Pages48to51             ((uint32_t)0x00001000) /* Write protection of page 48 to 51 */
#define OB_WRP_Pages52to55             ((uint32_t)0x00002000) /* Write protection of page 52 to 55 */
#define OB_WRP_Pages56to59             ((uint32_t)0x00004000) /* Write protection of page 56 to 59 */
#define OB_WRP_Pages60to63             ((uint32_t)0x00008000) /* Write protection of page 60 to 63 */

#define OB_WRP_AllPages                ((uint32_t)0x0000FFFF) /*!< Write protection of all Sectors */

#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))

#else  /* 128K and 256K Flash devices */

#define OB_WRP_Pages0to1               ((uint32_t)0x00000001) /* Write protection of page 0 to 1 */
#define OB_WRP_Pages2to3               ((uint32_t)0x00000002) /* Write protection of page 2 to 3 */
#define OB_WRP_Pages4to5               ((uint32_t)0x00000004) /* Write protection of page 4 to 5 */
#define OB_WRP_Pages6to7               ((uint32_t)0x00000008) /* Write protection of page 6 to 7 */
#define OB_WRP_Pages8to9               ((uint32_t)0x00000010) /* Write protection of page 8 to 9 */
#define OB_WRP_Pages10to11             ((uint32_t)0x00000020) /* Write protection of page 10 to 11 */
#define OB_WRP_Pages12to13             ((uint32_t)0x00000040) /* Write protection of page 12 to 13 */
#define OB_WRP_Pages14to15             ((uint32_t)0x00000080) /* Write protection of page 14 to 15 */
#define OB_WRP_Pages16to17             ((uint32_t)0x00000100) /* Write protection of page 16 to 17 */
#define OB_WRP_Pages18to19             ((uint32_t)0x00000200) /* Write protection of page 18 to 19 */
#define OB_WRP_Pages20to21             ((uint32_t)0x00000400) /* Write protection of page 20 to 21 */
#define OB_WRP_Pages22to23             ((uint32_t)0x00000800) /* Write protection of page 22 to 23 */
#define OB_WRP_Pages24to25             ((uint32_t)0x00001000) /* Write protection of page 24 to 25 */
#define OB_WRP_Pages26to27             ((uint32_t)0x00002000) /* Write protection of page 26 to 27 */
#define OB_WRP_Pages28to29             ((uint32_t)0x00004000) /* Write protection of page 28 to 29 */
#define OB_WRP_Pages30to31             ((uint32_t)0x00008000) /* Write protection of page 30 to 31 */
#define OB_WRP_Pages32to33             ((uint32_t)0x00010000) /* Write protection of page 32 to 33 */
#define OB_WRP_Pages34to35             ((uint32_t)0x00020000) /* Write protection of page 34 to 35 */
#define OB_WRP_Pages36to37             ((uint32_t)0x00040000) /* Write protection of page 36 to 37 */
#define OB_WRP_Pages38to39             ((uint32_t)0x00080000) /* Write protection of page 38 to 39 */
#define OB_WRP_Pages40to41             ((uint32_t)0x00100000) /* Write protection of page 40 to 41 */
#define OB_WRP_Pages42to43             ((uint32_t)0x00200000) /* Write protection of page 42 to 43 */
#define OB_WRP_Pages44to45             ((uint32_t)0x00400000) /* Write protection of page 44 to 45 */
#define OB_WRP_Pages46to47             ((uint32_t)0x00800000) /* Write protection of page 46 to 47 */
#define OB_WRP_Pages48to49             ((uint32_t)0x01000000) /* Write protection of page 48 to 49 */
#define OB_WRP_Pages50to51             ((uint32_t)0x02000000) /* Write protection of page 50 to 51 */
#define OB_WRP_Pages52to53             ((uint32_t)0x04000000) /* Write protection of page 52 to 53 */
#define OB_WRP_Pages54to55             ((uint32_t)0x08000000) /* Write protection of page 54 to 55 */
#define OB_WRP_Pages56to57             ((uint32_t)0x10000000) /* Write protection of page 56 to 57 */
#define OB_WRP_Pages58to59             ((uint32_t)0x20000000) /* Write protection of page 58 to 59 */
#define OB_WRP_Pages60to61             ((uint32_t)0x40000000) /* Write protection of page 60 to 61 */

#if defined(STM32F091) || defined(STM32F030xC)  /* 256K Flash devices */
#define OB_WRP_Pages62to127            ((uint32_t)0x80000000) /* Write protection of page 62 to 127 */
#else    /* 128K Flash devices */
#define OB_WRP_Pages62to63             ((uint32_t)0x80000000) /* Write protection of page 62 to 63 */
#endif /* STM32F091 || STM32F030xC */
#define OB_WRP_AllPages                ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Sectors */
#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))

#endif /* STM32F072 || STM32F070xB || STM32F091 || STM32F030 || STM32F030xC */
/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_Read_Protection 
  * @{
  */ 

/** 
  * @brief  FLASH_Read Protection Level  
  */ 
#define OB_RDP_Level_0   ((uint8_t)0xAA)
#define OB_RDP_Level_1   ((uint8_t)0xBB)
/*#define OB_RDP_Level_2   ((uint8_t)0xCC)*/ /* Warning: When enabling read protection level 2 
                                                it's no more possible to go back to level 1 or 0 */

#define IS_OB_RDP(LEVEL) (((LEVEL) == OB_RDP_Level_0)||\
                          ((LEVEL) == OB_RDP_Level_1))/*||\
                          ((LEVEL) == OB_RDP_Level_2))*/
/**
  * @}
  */ 

/** @defgroup FLASH_Option_Bytes_IWatchdog 
  * @{
  */

#define OB_IWDG_SW                     ((uint8_t)0x01)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware IWDG selected */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_nRST_STOP 
  * @{
  */

#define OB_STOP_NoRST                  ((uint8_t)0x02) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_nRST_STDBY 
  * @{
  */

#define OB_STDBY_NoRST                 ((uint8_t)0x04) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT1
  * @{
  */

#define OB_BOOT1_RESET                 ((uint8_t)0x00) /*!< BOOT1 Reset */
#define OB_BOOT1_SET                   ((uint8_t)0x10) /*!< BOOT1 Set */
#define IS_OB_BOOT1(BOOT1) (((BOOT1) == OB_BOOT1_RESET) || ((BOOT1) == OB_BOOT1_SET))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT0
  * @{
  */

#define OB_BOOT0_RESET                 ((uint8_t)0x00) /*!< BOOT0 Reset */
#define OB_BOOT0_SET                   ((uint8_t)0x08) /*!< BOOT0 Set */
#define IS_OB_BOOT0(BOOT0) (((BOOT0) == OB_BOOT0_RESET) || ((BOOT0) == OB_BOOT0_SET))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_BOOT0SW
  * @{
  */

#define OB_BOOT0_SW                   ((uint8_t)0x00) /*!< BOOT0 pin disabled */  
#define OB_BOOT0_HW                   ((uint8_t)0x80) /*!< BOOT0 pin bonded with GPIO */
#define IS_OB_BOOT0SW(BOOT0) (((BOOT0) == OB_BOOT0_SW) || ((BOOT0) == OB_BOOT0_HW))

/**
  * @}
  */
  
/** @defgroup FLASH_Option_Bytes_VDDA_Analog_Monitoring
  * @{
  */

#define OB_VDDA_ANALOG_ON              ((uint8_t)0x20) /*!< Analog monitoring on VDDA Power source ON */
#define OB_VDDA_ANALOG_OFF             ((uint8_t)0x00) /*!< Analog monitoring on VDDA Power source OFF */

#define IS_OB_VDDA_ANALOG(ANALOG) (((ANALOG) == OB_VDDA_ANALOG_ON) || ((ANALOG) == OB_VDDA_ANALOG_OFF))

/**
  * @}
  */    

/** @defgroup FLASH_Option_Bytes_SRAM_Parity_Enable 
  * @{
  */

#define OB_SRAM_PARITY_SET              ((uint8_t)0x00) /*!< SRAM parity enable Set */
#define OB_SRAM_PARITY_RESET            ((uint8_t)0x40) /*!< SRAM parity enable reset */

#define IS_OB_SRAM_PARITY(PARITY) (((PARITY) == OB_SRAM_PARITY_SET) || ((PARITY) == OB_SRAM_PARITY_RESET))

/**
  * @}
  */ 
  
/** @defgroup FLASH_Flags 
  * @{
  */ 

#define FLASH_FLAG_BSY                 FLASH_SR_BSY     /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR               FLASH_SR_PGERR   /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR              FLASH_SR_WRPERR  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP                 FLASH_SR_EOP     /*!< FLASH End of Programming flag */
 
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFCB) == 0x00000000) && ((FLAG) != 0x00000000))

#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_PGERR) || \
                                  ((FLAG) == FLASH_FLAG_WRPERR) || ((FLAG) == FLASH_FLAG_EOP))
/**
  * @}
  */ 

/** @defgroup FLASH_Timeout_definition 
  * @{
  */ 
#define FLASH_ER_PRG_TIMEOUT         ((uint32_t)0x000B0000)

/**
  * @}
  */ 

/** @defgroup FLASH_Legacy 
  * @{
  */
#define FLASH_WRProt_Pages0to3	       OB_WRP_Pages0to3
#define FLASH_WRProt_Pages4to7	       OB_WRP_Pages4to7
#define FLASH_WRProt_Pages8to11	       OB_WRP_Pages8to11
#define FLASH_WRProt_Pages12to15	   OB_WRP_Pages12to15
#define FLASH_WRProt_Pages16to19	   OB_WRP_Pages16to19
#define FLASH_WRProt_Pages20to23	   OB_WRP_Pages20to23
#define FLASH_WRProt_Pages24to27	   OB_WRP_Pages24to27
#define FLASH_WRProt_Pages28to31	   OB_WRP_Pages28to31
#define FLASH_WRProt_Pages32to35	   OB_WRP_Pages32to35
#define FLASH_WRProt_Pages36to39	   OB_WRP_Pages36to39
#define FLASH_WRProt_Pages40to43	   OB_WRP_Pages40to21
#define FLASH_WRProt_Pages44to47	   OB_WRP_Pages44to23
#define FLASH_WRProt_Pages48to51	   OB_WRP_Pages48to51
#define FLASH_WRProt_Pages52to55	   OB_WRP_Pages52to55
#define FLASH_WRProt_Pages56to59	   OB_WRP_Pages56to59
#define FLASH_WRProt_Pages60to63	   OB_WRP_Pages60to63


#define FLASH_WRProt_AllPages          OB_WRP_AllPages
/**
  * @}
  */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
  
/** 
  * @brief  FLASH memory functions that can be executed from FLASH.  
  */  
/* FLASH Interface configuration functions ************************************/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_PrefetchBufferCmd(FunctionalState NewState);
FlagStatus FLASH_GetPrefetchBufferStatus(void);

/* FLASH Memory Programming functions *****************************************/
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

/* FLASH Option Bytes Programming functions *****************************************/
void FLASH_OB_Unlock(void);
void FLASH_OB_Lock(void);
void FLASH_OB_Launch(void);
FLASH_Status FLASH_OB_Erase(void);
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP);
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP);
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1);
FLASH_Status FLASH_OB_BOOT0Config(uint8_t OB_BOOT0);
FLASH_Status FLASH_OB_BOOT0SWConfig(uint8_t OB_BOOT0SW);
FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG);
FLASH_Status FLASH_OB_SRAMParityConfig(uint8_t OB_SRAM_Parity);
FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER);
FLASH_Status FLASH_OB_ProgramData(uint32_t Address, uint8_t Data);
uint8_t FLASH_OB_GetUser(void);
uint32_t FLASH_OB_GetWRP(void);
FlagStatus FLASH_OB_GetRDP(void);

/* FLASH Interrupts and flags management functions **********************************/
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

/** @defgroup FLASH_Legacy 
  * @{
  */
#define FLASH_EraseOptionBytes               FLASH_OB_Erase
#define FLASH_EnableWriteProtection	         FLASH_OB_EnableWRP
#define FLASH_UserOptionByteConfig	         FLASH_OB_UserConfig
#define FLASH_ProgramOptionByteData          FLASH_OB_ProgramData
#define FLASH_GetUserOptionByte	             FLASH_OB_GetUser
#define FLASH_GetWriteProtectionOptionByte   FLASH_OB_GetWRP

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_FLASH_H */

/**
  * @}
  */

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_gpio.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the GPIO 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_GPIO_H
#define __STM32F0XX_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */
/* Exported types ------------------------------------------------------------*/

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE) || \
                                    ((PERIPH) == GPIOF))

#define IS_GPIO_LIST_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                     ((PERIPH) == GPIOB))

/** @defgroup Configuration_Mode_enumeration 
  * @{
  */
typedef enum
{
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode              */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode             */
  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog In/Out Mode      */
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN)|| ((MODE) == GPIO_Mode_OUT) || \
                            ((MODE) == GPIO_Mode_AF)|| ((MODE) == GPIO_Mode_AN))
/**
  * @}
  */

/** @defgroup Output_type_enumeration
  * @{
  */
typedef enum
{
  GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;

#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))

/**
  * @}
  */

/** @defgroup Output_Maximum_frequency_enumeration 
  * @{
  */
typedef enum
{
  GPIO_Speed_Level_1  = 0x00, /*!< I/O output speed: Low 2 MHz */
  GPIO_Speed_Level_2  = 0x01, /*!< I/O output speed: Medium 10 MHz */
  GPIO_Speed_Level_3  = 0x03  /*!< I/O output speed: High 50 MHz */
}GPIOSpeed_TypeDef;

#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_Level_1) || ((SPEED) == GPIO_Speed_Level_2) || \
                              ((SPEED) == GPIO_Speed_Level_3))
/**
  * @}
  */

/** @defgroup Configuration_Pull-Up_Pull-Down_enumeration 
  * @{
  */
typedef enum
{
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
}GPIOPuPd_TypeDef;

#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN))
/**
  * @}
  */

/** @defgroup Bit_SET_and_Bit_RESET_enumeration
  * @{
  */
typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET
}BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))
/**
  * @}
  */

/**
  * @brief  GPIO Init structure definition  
  */
typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */
                                       
  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef   */

  GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef  */

  GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef  */

  GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef   */
}GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
  * @{
  */

/** @defgroup GPIO_pins_define 
  * @{
  */
#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected    */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected    */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected    */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected    */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected    */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected    */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected    */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected    */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected    */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected    */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected   */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected   */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected   */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected   */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected   */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected   */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins selected */

#define IS_GPIO_PIN(PIN) ((PIN) != (uint16_t)0x00)

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))

/**
  * @}
  */

/** @defgroup GPIO_Pin_sources 
  * @{
  */
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))
/**
  * @}
  */

/** @defgroup GPIO_Alternate_function_selection_define 
  * @{
  */

/** 
  * @brief  AF 0 selection
  */
#define GPIO_AF_0            ((uint8_t)0x00) /* WKUP, EVENTOUT, TIM15, SPI1, TIM17,
                                                MCO, SWDAT, SWCLK, TIM14, BOOT,
                                                USART1, CEC, IR_OUT, SPI2, TS, TIM3,
                                                USART4, CAN, TIM3, USART2, USART3, 
                                                CRS, TIM16, TIM1 */
/** 
  * @brief  AF 1 selection
  */
#define GPIO_AF_1            ((uint8_t)0x01) /* USART2, CEC, TIM3, USART1, IR,
                                                EVENTOUT, I2C1, I2C2, TIM15, SPI2,
                                                USART3, TS, SPI1 */
/** 
  * @brief  AF 2 selection
  */
#define GPIO_AF_2            ((uint8_t)0x02) /* TIM2, TIM1, EVENTOUT, TIM16, TIM17,
                                                USB */
/** 
  * @brief  AF 3 selection
  */
#define GPIO_AF_3            ((uint8_t)0x03) /* TS, I2C1, TIM15, EVENTOUT */

/** 
  * @brief  AF 4 selection
  */
#define GPIO_AF_4            ((uint8_t)0x04) /* TIM14, USART4, USART3, CRS, CAN,
                                                I2C1 */

/** 
  * @brief  AF 5 selection
  */
#define GPIO_AF_5            ((uint8_t)0x05) /* TIM16, TIM17, TIM15, SPI2, I2C2, 
                                                MCO, I2C1, USB */

/** 
  * @brief  AF 6 selection
  */
#define GPIO_AF_6            ((uint8_t)0x06) /* EVENTOUT */
/** 
  * @brief  AF 7 selection
  */
#define GPIO_AF_7            ((uint8_t)0x07) /* COMP1 OUT and COMP2 OUT */

#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_0) || ((AF) == GPIO_AF_1) || \
                          ((AF) == GPIO_AF_2) || ((AF) == GPIO_AF_3) || \
                          ((AF) == GPIO_AF_4) || ((AF) == GPIO_AF_5) || \
                          ((AF) == GPIO_AF_6) || ((AF) == GPIO_AF_7))

/**
  * @}
  */

/** @defgroup GPIO_Speed_Legacy 
  * @{
  */

#define GPIO_Speed_2MHz  GPIO_Speed_Level_1   /*!< I/O output speed: Low 2 MHz  */
#define GPIO_Speed_10MHz GPIO_Speed_Level_2   /*!< I/O output speed: Medium 10 MHz */
#define GPIO_Speed_50MHz GPIO_Speed_Level_3   /*!< I/O output speed: High 50 MHz */
  
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Function used to set the GPIO configuration to the default reset state *****/
void GPIO_DeInit(GPIO_TypeDef* GPIOx);

/* Initialization and Configuration functions *********************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Read and Write functions **********************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);

/* GPIO Alternate functions configuration functions ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_GPIO_H */
/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_i2c.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the I2C firmware
  *          library
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_I2C_H
#define __STM32F0XX_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  I2C Init structure definition
  */

typedef struct
{
  uint32_t I2C_Timing;              /*!< Specifies the I2C_TIMINGR_register value.
                                         This parameter must be set by referring to I2C_Timing_Config_Tool*/

  uint32_t I2C_AnalogFilter;        /*!< Enables or disables analog noise filter.
                                         This parameter can be a value of @ref I2C_Analog_Filter*/

  uint32_t I2C_DigitalFilter;       /*!< Configures the digital noise filter.
                                         This parameter can be a number between 0x00 and 0x0F*/

  uint32_t I2C_Mode;                /*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode*/

  uint32_t I2C_OwnAddress1;         /*!< Specifies the device own address 1.
                                         This parameter can be a 7-bit or 10-bit address*/

  uint32_t I2C_Ack;                 /*!< Enables or disables the acknowledgement.
                                         This parameter can be a value of @ref I2C_acknowledgement*/

  uint32_t I2C_AcknowledgedAddress; /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                         This parameter can be a value of @ref I2C_acknowledged_address*/
}I2C_InitTypeDef;

/* Exported constants --------------------------------------------------------*/


/** @defgroup I2C_Exported_Constants
  * @{
  */

#define IS_I2C_ALL_PERIPH(PERIPH)       (((PERIPH) == I2C1) || \
                                         ((PERIPH) == I2C2))
                                         
#define IS_I2C_1_PERIPH(PERIPH)         ((PERIPH) == I2C1) 

/** @defgroup I2C_Analog_Filter 
  * @{
  */

#define I2C_AnalogFilter_Enable         ((uint32_t)0x00000000)
#define I2C_AnalogFilter_Disable        I2C_CR1_ANFOFF

#define IS_I2C_ANALOG_FILTER(FILTER)    (((FILTER) == I2C_AnalogFilter_Enable) || \
                                         ((FILTER) == I2C_AnalogFilter_Disable))
/**
  * @}
  */

/** @defgroup I2C_Digital_Filter
  * @{
  */

#define IS_I2C_DIGITAL_FILTER(FILTER)   ((FILTER) <= 0x0000000F)
/**
  * @}
  */

/** @defgroup I2C_mode 
  * @{
  */

#define I2C_Mode_I2C                    ((uint32_t)0x00000000)
#define I2C_Mode_SMBusDevice            I2C_CR1_SMBDEN
#define I2C_Mode_SMBusHost              I2C_CR1_SMBHEN

#define IS_I2C_MODE(MODE)               (((MODE) == I2C_Mode_I2C) || \
                                         ((MODE) == I2C_Mode_SMBusDevice) || \
                                         ((MODE) == I2C_Mode_SMBusHost))
/**
  * @}
  */

/** @defgroup I2C_acknowledgement
  * @{
  */

#define I2C_Ack_Enable                  ((uint32_t)0x00000000)
#define I2C_Ack_Disable                 I2C_CR2_NACK

#define IS_I2C_ACK(ACK)                 (((ACK) == I2C_Ack_Enable) || \
                                         ((ACK) == I2C_Ack_Disable))
/**
  * @}
  */

/** @defgroup I2C_acknowledged_address
  * @{
  */

#define I2C_AcknowledgedAddress_7bit    ((uint32_t)0x00000000)
#define I2C_AcknowledgedAddress_10bit   I2C_OAR1_OA1MODE

#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS) (((ADDRESS) == I2C_AcknowledgedAddress_7bit) || \
                                             ((ADDRESS) == I2C_AcknowledgedAddress_10bit))
/**
  * @}
  */ 

/** @defgroup I2C_own_address1
  * @{
  */

#define IS_I2C_OWN_ADDRESS1(ADDRESS1)   ((ADDRESS1) <= (uint32_t)0x000003FF)
/**
  * @}
  */

/** @defgroup I2C_transfer_direction 
  * @{
  */

#define I2C_Direction_Transmitter       ((uint16_t)0x0000)
#define I2C_Direction_Receiver          ((uint16_t)0x0400)

#define IS_I2C_DIRECTION(DIRECTION)     (((DIRECTION) == I2C_Direction_Transmitter) || \
                                         ((DIRECTION) == I2C_Direction_Receiver))
/**
  * @}
  */

/** @defgroup I2C_DMA_transfer_requests 
  * @{
  */

#define I2C_DMAReq_Tx                   I2C_CR1_TXDMAEN
#define I2C_DMAReq_Rx                   I2C_CR1_RXDMAEN

#define IS_I2C_DMA_REQ(REQ)             ((((REQ) & (uint32_t)0xFFFF3FFF) == 0x00) && ((REQ) != 0x00))
/**
  * @}
  */

/** @defgroup I2C_slave_address
  * @{
  */

#define IS_I2C_SLAVE_ADDRESS(ADDRESS)   ((ADDRESS) <= (uint16_t)0x03FF)
/**
  * @}
  */


/** @defgroup I2C_own_address2
  * @{
  */

#define IS_I2C_OWN_ADDRESS2(ADDRESS2)   ((ADDRESS2) <= (uint16_t)0x00FF)

/**
  * @}
  */

/** @defgroup I2C_own_address2_mask
  * @{
  */

#define I2C_OA2_NoMask                  ((uint8_t)0x00)
#define I2C_OA2_Mask01                  ((uint8_t)0x01)                 
#define I2C_OA2_Mask02                  ((uint8_t)0x02)
#define I2C_OA2_Mask03                  ((uint8_t)0x03)
#define I2C_OA2_Mask04                  ((uint8_t)0x04)
#define I2C_OA2_Mask05                  ((uint8_t)0x05)
#define I2C_OA2_Mask06                  ((uint8_t)0x06)
#define I2C_OA2_Mask07                  ((uint8_t)0x07)

#define IS_I2C_OWN_ADDRESS2_MASK(MASK)  (((MASK) == I2C_OA2_NoMask) || \
                                         ((MASK) == I2C_OA2_Mask01) || \
                                         ((MASK) == I2C_OA2_Mask02) || \
                                         ((MASK) == I2C_OA2_Mask03) || \
                                         ((MASK) == I2C_OA2_Mask04) || \
                                         ((MASK) == I2C_OA2_Mask05) || \
                                         ((MASK) == I2C_OA2_Mask06) || \
                                         ((MASK) == I2C_OA2_Mask07))  

/**
  * @}
  */

/** @defgroup I2C_timeout
  * @{
  */

#define IS_I2C_TIMEOUT(TIMEOUT)   ((TIMEOUT) <= (uint16_t)0x0FFF)

/**
  * @}
  */

/** @defgroup I2C_registers 
  * @{
  */

#define I2C_Register_CR1                ((uint8_t)0x00)
#define I2C_Register_CR2                ((uint8_t)0x04)
#define I2C_Register_OAR1               ((uint8_t)0x08)
#define I2C_Register_OAR2               ((uint8_t)0x0C)
#define I2C_Register_TIMINGR            ((uint8_t)0x10)
#define I2C_Register_TIMEOUTR           ((uint8_t)0x14)
#define I2C_Register_ISR                ((uint8_t)0x18)
#define I2C_Register_ICR                ((uint8_t)0x1C)
#define I2C_Register_PECR               ((uint8_t)0x20)
#define I2C_Register_RXDR               ((uint8_t)0x24)
#define I2C_Register_TXDR               ((uint8_t)0x28)

#define IS_I2C_REGISTER(REGISTER)       (((REGISTER) == I2C_Register_CR1) || \
                                         ((REGISTER) == I2C_Register_CR2) || \
                                         ((REGISTER) == I2C_Register_OAR1) || \
                                         ((REGISTER) == I2C_Register_OAR2) || \
                                         ((REGISTER) == I2C_Register_TIMINGR) || \
                                         ((REGISTER) == I2C_Register_TIMEOUTR) || \
                                         ((REGISTER) == I2C_Register_ISR) || \
                                         ((REGISTER) == I2C_Register_ICR) || \
                                         ((REGISTER) == I2C_Register_PECR) || \
                                         ((REGISTER) == I2C_Register_RXDR) || \
                                         ((REGISTER) == I2C_Register_TXDR))
/**
  * @}
  */

/** @defgroup I2C_interrupts_definition 
  * @{
  */

#define I2C_IT_ERRI                     I2C_CR1_ERRIE
#define I2C_IT_TCI                      I2C_CR1_TCIE
#define I2C_IT_STOPI                    I2C_CR1_STOPIE
#define I2C_IT_NACKI                    I2C_CR1_NACKIE
#define I2C_IT_ADDRI                    I2C_CR1_ADDRIE
#define I2C_IT_RXI                      I2C_CR1_RXIE
#define I2C_IT_TXI                      I2C_CR1_TXIE

#define IS_I2C_CONFIG_IT(IT)            ((((IT) & (uint32_t)0xFFFFFF01) == 0x00) && ((IT) != 0x00))

/**
  * @}
  */

/** @defgroup I2C_flags_definition 
  * @{
  */

#define  I2C_FLAG_TXE                   I2C_ISR_TXE
#define  I2C_FLAG_TXIS                  I2C_ISR_TXIS
#define  I2C_FLAG_RXNE                  I2C_ISR_RXNE
#define  I2C_FLAG_ADDR                  I2C_ISR_ADDR
#define  I2C_FLAG_NACKF                 I2C_ISR_NACKF
#define  I2C_FLAG_STOPF                 I2C_ISR_STOPF
#define  I2C_FLAG_TC                    I2C_ISR_TC
#define  I2C_FLAG_TCR                   I2C_ISR_TCR
#define  I2C_FLAG_BERR                  I2C_ISR_BERR
#define  I2C_FLAG_ARLO                  I2C_ISR_ARLO
#define  I2C_FLAG_OVR                   I2C_ISR_OVR
#define  I2C_FLAG_PECERR                I2C_ISR_PECERR
#define  I2C_FLAG_TIMEOUT               I2C_ISR_TIMEOUT
#define  I2C_FLAG_ALERT                 I2C_ISR_ALERT
#define  I2C_FLAG_BUSY                  I2C_ISR_BUSY

#define IS_I2C_CLEAR_FLAG(FLAG)         ((((FLAG) & (uint32_t)0xFFFF4000) == 0x00) && ((FLAG) != 0x00))

#define IS_I2C_GET_FLAG(FLAG)           (((FLAG) == I2C_FLAG_TXE) || ((FLAG) == I2C_FLAG_TXIS) || \
                                         ((FLAG) == I2C_FLAG_RXNE) || ((FLAG) == I2C_FLAG_ADDR) || \
                                         ((FLAG) == I2C_FLAG_NACKF) || ((FLAG) == I2C_FLAG_STOPF) || \
                                         ((FLAG) == I2C_FLAG_TC) || ((FLAG) == I2C_FLAG_TCR) || \
                                         ((FLAG) == I2C_FLAG_BERR) || ((FLAG) == I2C_FLAG_ARLO) || \
                                         ((FLAG) == I2C_FLAG_OVR) || ((FLAG) == I2C_FLAG_PECERR) || \
                                         ((FLAG) == I2C_FLAG_TIMEOUT) || ((FLAG) == I2C_FLAG_ALERT) || \
                                         ((FLAG) == I2C_FLAG_BUSY))

/**
  * @}
  */


/** @defgroup I2C_interrupts_definition 
  * @{
  */

#define  I2C_IT_TXIS                    I2C_ISR_TXIS
#define  I2C_IT_RXNE                    I2C_ISR_RXNE
#define  I2C_IT_ADDR                    I2C_ISR_ADDR
#define  I2C_IT_NACKF                   I2C_ISR_NACKF
#define  I2C_IT_STOPF                   I2C_ISR_STOPF
#define  I2C_IT_TC                      I2C_ISR_TC
#define  I2C_IT_TCR                     I2C_ISR_TCR
#define  I2C_IT_BERR                    I2C_ISR_BERR
#define  I2C_IT_ARLO                    I2C_ISR_ARLO
#define  I2C_IT_OVR                     I2C_ISR_OVR
#define  I2C_IT_PECERR                  I2C_ISR_PECERR
#define  I2C_IT_TIMEOUT                 I2C_ISR_TIMEOUT
#define  I2C_IT_ALERT                   I2C_ISR_ALERT

#define IS_I2C_CLEAR_IT(IT)             ((((IT) & (uint32_t)0xFFFFC001) == 0x00) && ((IT) != 0x00))
                               
#define IS_I2C_GET_IT(IT)               (((IT) == I2C_IT_TXIS) || ((IT) == I2C_IT_RXNE) || \
                                         ((IT) == I2C_IT_ADDR) || ((IT) == I2C_IT_NACKF) || \
                                         ((IT) == I2C_IT_STOPF) || ((IT) == I2C_IT_TC) || \
                                         ((IT) == I2C_IT_TCR) || ((IT) == I2C_IT_BERR) || \
                                         ((IT) == I2C_IT_ARLO) || ((IT) == I2C_IT_OVR) || \
                                         ((IT) == I2C_IT_PECERR) || ((IT) == I2C_IT_TIMEOUT) || \
                                         ((IT) == I2C_IT_ALERT))
                               

/**
  * @}
  */

/** @defgroup I2C_ReloadEndMode_definition 
  * @{
  */

#define  I2C_Reload_Mode                I2C_CR2_RELOAD
#define  I2C_AutoEnd_Mode               I2C_CR2_AUTOEND
#define  I2C_SoftEnd_Mode               ((uint32_t)0x00000000)

                              
#define IS_RELOAD_END_MODE(MODE)        (((MODE) == I2C_Reload_Mode) || \
                                         ((MODE) == I2C_AutoEnd_Mode) || \
                                         ((MODE) == I2C_SoftEnd_Mode))
                               

/**
  * @}
  */

/** @defgroup I2C_StartStopMode_definition 
  * @{
  */

#define  I2C_No_StartStop                 ((uint32_t)0x00000000)
#define  I2C_Generate_Stop                I2C_CR2_STOP
#define  I2C_Generate_Start_Read          (uint32_t)(I2C_CR2_START | I2C_CR2_RD_WRN)
#define  I2C_Generate_Start_Write         I2C_CR2_START

                              
#define IS_START_STOP_MODE(MODE)        (((MODE) == I2C_Generate_Stop) || \
                                         ((MODE) == I2C_Generate_Start_Read) || \
                                         ((MODE) == I2C_Generate_Start_Write) || \
                                         ((MODE) == I2C_No_StartStop))
                               

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


/* Initialization and Configuration functions *********************************/
void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx);
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint32_t I2C_IT, FunctionalState NewState);
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StopModeCmd(I2C_TypeDef* I2Cx, FunctionalState NewState); /*!< not applicable for STM32F030 devices */
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SlaveByteControlCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SlaveAddressConfig(I2C_TypeDef* I2Cx, uint16_t Address);
void I2C_10BitAddressingModeCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);

/* Communications handling functions ******************************************/
void I2C_AutoEndCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ReloadCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_NumberOfBytesConfig(I2C_TypeDef* I2Cx, uint8_t Number_Bytes);
void I2C_MasterRequestConfig(I2C_TypeDef* I2Cx, uint16_t I2C_Direction);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_10BitAddressHeaderCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint8_t I2C_GetAddressMatched(I2C_TypeDef* I2Cx);
uint16_t I2C_GetTransferDirection(I2C_TypeDef* I2Cx);
void I2C_TransferHandling(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Number_Bytes, uint32_t ReloadEndMode, uint32_t StartStopMode);

/*  SMBUS management functions ************************************************/
void I2C_SMBusAlertCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ExtendedClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_IdleClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_TimeoutAConfig(I2C_TypeDef* I2Cx, uint16_t Timeout);
void I2C_TimeoutBConfig(I2C_TypeDef* I2Cx, uint16_t Timeout);
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_PECRequestCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx);

/* I2C registers management functions *****************************************/
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);

/* Data transfers management functions ****************************************/
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);

/* DMA transfers management functions *****************************************/
void I2C_DMACmd(I2C_TypeDef* I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);


#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_I2C_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_iwdg.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_IWDG_H
#define __STM32F0XX_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/** @defgroup IWDG_WriteAccess
  * @{
  */

#define IWDG_WriteAccess_Enable     ((uint16_t)0x5555)
#define IWDG_WriteAccess_Disable    ((uint16_t)0x0000)
#define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable) || \
                                      ((ACCESS) == IWDG_WriteAccess_Disable))
/**
  * @}
  */

/** @defgroup IWDG_prescaler 
  * @{
  */

#define IWDG_Prescaler_4            ((uint8_t)0x00)
#define IWDG_Prescaler_8            ((uint8_t)0x01)
#define IWDG_Prescaler_16           ((uint8_t)0x02)
#define IWDG_Prescaler_32           ((uint8_t)0x03)
#define IWDG_Prescaler_64           ((uint8_t)0x04)
#define IWDG_Prescaler_128          ((uint8_t)0x05)
#define IWDG_Prescaler_256          ((uint8_t)0x06)
#define IS_IWDG_PRESCALER(PRESCALER) (((PRESCALER) == IWDG_Prescaler_4)  || \
                                      ((PRESCALER) == IWDG_Prescaler_8)  || \
                                      ((PRESCALER) == IWDG_Prescaler_16) || \
                                      ((PRESCALER) == IWDG_Prescaler_32) || \
                                      ((PRESCALER) == IWDG_Prescaler_64) || \
                                      ((PRESCALER) == IWDG_Prescaler_128)|| \
                                      ((PRESCALER) == IWDG_Prescaler_256))
/**
  * @}
  */

/** @defgroup IWDG_Flag 
  * @{
  */

#define IWDG_FLAG_PVU               IWDG_SR_PVU
#define IWDG_FLAG_RVU               IWDG_SR_RVU
#define IWDG_FLAG_WVU               IWDG_SR_WVU
#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU)  || \
                            ((FLAG) == IWDG_FLAG_WVU))

#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)

#define IS_IWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0xFFF)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Prescaler and Counter configuration functions ******************************/
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_SetWindowValue(uint16_t WindowValue);

/* IWDG activation function ***************************************************/
void IWDG_Enable(void);

/* Flag management function ***************************************************/
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_IWDG_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_misc.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the miscellaneous
  *          firmware library functions (add-on to CMSIS functions).
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_MISC_H
#define __STM32F0XX_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup MISC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  NVIC Init Structure definition  
  */

typedef struct
{
  uint8_t NVIC_IRQChannel;             /*!< Specifies the IRQ channel to be enabled or disabled.
                                            This parameter can be a value of @ref IRQn_Type 
                                            (For the complete STM32 Devices IRQ Channels list, 
                                            please refer to stm32f0xx.h file) */

  uint8_t NVIC_IRQChannelPriority;     /*!< Specifies the priority level for the IRQ channel specified
                                            in NVIC_IRQChannel. This parameter can be a value
                                            between 0 and 3.  */

  FunctionalState NVIC_IRQChannelCmd;  /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                            will be enabled or disabled. 
                                            This parameter can be set either to ENABLE or DISABLE */   
} NVIC_InitTypeDef;

/**  
  *
@verbatim   

@endverbatim
*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup MISC_Exported_Constants
  * @{
  */

/** @defgroup MISC_System_Low_Power 
  * @{
  */

#define NVIC_LP_SEVONPEND            ((uint8_t)0x10)
#define NVIC_LP_SLEEPDEEP            ((uint8_t)0x04)
#define NVIC_LP_SLEEPONEXIT          ((uint8_t)0x02)
#define IS_NVIC_LP(LP) (((LP) == NVIC_LP_SEVONPEND) || \
                        ((LP) == NVIC_LP_SLEEPDEEP) || \
                        ((LP) == NVIC_LP_SLEEPONEXIT))
/**
  * @}
  */

/** @defgroup MISC_Preemption_Priority_Group 
  * @{
  */
#define IS_NVIC_PRIORITY(PRIORITY)  ((PRIORITY) < 0x04)

/**
  * @}
  */

/** @defgroup MISC_SysTick_clock_source 
  * @{
  */

#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \
                                       ((SOURCE) == SysTick_CLKSource_HCLK_Div8))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_MISC_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_pwr.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the PWR firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_PWR_H
#define __STM32F0XX_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants
  * @{
  */ 

/** @defgroup PWR_PVD_detection_level 
  * @brief    This parameters are only applicable for STM32F051 and STM32F072 devices
  * @{
  */ 

#define PWR_PVDLevel_0                  PWR_CR_PLS_LEV0
#define PWR_PVDLevel_1                  PWR_CR_PLS_LEV1
#define PWR_PVDLevel_2                  PWR_CR_PLS_LEV2
#define PWR_PVDLevel_3                  PWR_CR_PLS_LEV3
#define PWR_PVDLevel_4                  PWR_CR_PLS_LEV4
#define PWR_PVDLevel_5                  PWR_CR_PLS_LEV5
#define PWR_PVDLevel_6                  PWR_CR_PLS_LEV6
#define PWR_PVDLevel_7                  PWR_CR_PLS_LEV7 

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1)|| \
                                 ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3)|| \
                                 ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5)|| \
                                 ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7))
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Pins 
  * @{
  */

#define PWR_WakeUpPin_1                 PWR_CSR_EWUP1
#define PWR_WakeUpPin_2                 PWR_CSR_EWUP2
#define PWR_WakeUpPin_3                 PWR_CSR_EWUP3 /*!< only applicable for STM32F072 devices */
#define PWR_WakeUpPin_4                 PWR_CSR_EWUP4 /*!< only applicable for STM32F072 devices */
#define PWR_WakeUpPin_5                 PWR_CSR_EWUP5 /*!< only applicable for STM32F072 devices */
#define PWR_WakeUpPin_6                 PWR_CSR_EWUP6 /*!< only applicable for STM32F072 devices */
#define PWR_WakeUpPin_7                 PWR_CSR_EWUP7 /*!< only applicable for STM32F072 devices */
#define PWR_WakeUpPin_8                 PWR_CSR_EWUP8 /*!< only applicable for STM32F072 devices */
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WakeUpPin_1) || ((PIN) == PWR_WakeUpPin_2) || \
                                ((PIN) == PWR_WakeUpPin_3) || ((PIN) == PWR_WakeUpPin_4) || \
                                ((PIN) == PWR_WakeUpPin_5) || ((PIN) == PWR_WakeUpPin_6) || \
                                ((PIN) == PWR_WakeUpPin_7) || ((PIN) == PWR_WakeUpPin_8))
/**
  * @}
  */

 
/** @defgroup PWR_Regulator_state_is_Sleep_STOP_mode 
  * @{
  */

#define PWR_Regulator_ON                ((uint32_t)0x00000000)
#define PWR_Regulator_LowPower          PWR_CR_LPSDSR
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_Regulator_ON) || \
                                     ((REGULATOR) == PWR_Regulator_LowPower))
/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry 
  * @{
  */

#define PWR_SLEEPEntry_WFI              ((uint8_t)0x01)
#define PWR_SLEEPEntry_WFE              ((uint8_t)0x02)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPEntry_WFI) || ((ENTRY) == PWR_SLEEPEntry_WFE))
 
/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry 
  * @{
  */

#define PWR_STOPEntry_WFI               ((uint8_t)0x01)
#define PWR_STOPEntry_WFE               ((uint8_t)0x02)
#define PWR_STOPEntry_SLEEPONEXIT       ((uint8_t)0x03)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE) ||\
                                  ((ENTRY) == PWR_STOPEntry_SLEEPONEXIT))
 
/**
  * @}
  */

/** @defgroup PWR_Flag 
  * @{
  */

#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO /*!< Not applicable for STM32F030 devices */
#define PWR_FLAG_VREFINTRDY             PWR_CSR_VREFINTRDYF 

#define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_VREFINTRDY))

#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the PWR configuration to the default reset state ******/
void PWR_DeInit(void);

/* Backup Domain Access function **********************************************/
void PWR_BackupAccessCmd(FunctionalState NewState);

/* PVD configuration functions ************************************************/
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel); /*!< only applicable for STM32F051 and STM32F072 devices */
void PWR_PVDCmd(FunctionalState NewState); /*!< only applicable for STM32F051 and STM32F072 devices */

/* WakeUp pins configuration functions ****************************************/
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState);

/* Low Power modes configuration functions ************************************/
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);

/* Flags management functions *************************************************/
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_PWR_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_rcc.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the RCC 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_RCC_H
#define __STM32F0XX_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

typedef struct
{
  uint32_t SYSCLK_Frequency;
  uint32_t HCLK_Frequency;
  uint32_t PCLK_Frequency;
  uint32_t ADCCLK_Frequency;
  uint32_t CECCLK_Frequency;
  uint32_t I2C1CLK_Frequency;
  uint32_t USART1CLK_Frequency;
  uint32_t USART2CLK_Frequency; /*!< Only applicable for STM32F072 and STM32F091 devices */
  uint32_t USART3CLK_Frequency; /*!< Only applicable for STM32F091 devices */
  uint32_t USBCLK_Frequency;    /*!< Only applicable for STM32F072 devices */
}RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup RCC_HSE_configuration 
  * @{
  */

#define RCC_HSE_OFF                      ((uint8_t)0x00)
#define RCC_HSE_ON                       ((uint8_t)0x01)
#define RCC_HSE_Bypass                   ((uint8_t)0x05)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/**
  * @}
  */ 
 
/** @defgroup RCC_PLL_Clock_Source 
  * @{
  */

#define RCC_PLLSource_HSI_Div2           RCC_CFGR_PLLSRC_HSI_Div2
#define RCC_PLLSource_PREDIV1            RCC_CFGR_PLLSRC_HSE_PREDIV /* Old HSEPREDIV1 bit definition, maintained for legacy purpose */
#define RCC_PLLSource_HSE                RCC_CFGR_PLLSRC_HSE_PREDIV /*!< Only applicable for STM32F072 devices */
#define RCC_PLLSource_HSI48              RCC_CFGR_PLLSRC_HSI48_PREDIV /*!< Only applicable for STM32F072 devices */
#define RCC_PLLSource_HSI                RCC_CFGR_PLLSRC_HSI_PREDIV /*!< Only applicable for STM32F072 devices */

#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_HSI48)    || \
                                   ((SOURCE) == RCC_PLLSource_HSI)      || \
                                   ((SOURCE) == RCC_PLLSource_HSE)      || \
                                   ((SOURCE) == RCC_PLLSource_PREDIV1))
/**
  * @}
  */ 

/** @defgroup RCC_PLL_Multiplication_Factor 
  * @{
  */

#define RCC_PLLMul_2                    RCC_CFGR_PLLMULL2
#define RCC_PLLMul_3                    RCC_CFGR_PLLMULL3
#define RCC_PLLMul_4                    RCC_CFGR_PLLMULL4
#define RCC_PLLMul_5                    RCC_CFGR_PLLMULL5
#define RCC_PLLMul_6                    RCC_CFGR_PLLMULL6
#define RCC_PLLMul_7                    RCC_CFGR_PLLMULL7
#define RCC_PLLMul_8                    RCC_CFGR_PLLMULL8
#define RCC_PLLMul_9                    RCC_CFGR_PLLMULL9
#define RCC_PLLMul_10                   RCC_CFGR_PLLMULL10
#define RCC_PLLMul_11                   RCC_CFGR_PLLMULL11
#define RCC_PLLMul_12                   RCC_CFGR_PLLMULL12
#define RCC_PLLMul_13                   RCC_CFGR_PLLMULL13
#define RCC_PLLMul_14                   RCC_CFGR_PLLMULL14
#define RCC_PLLMul_15                   RCC_CFGR_PLLMULL15
#define RCC_PLLMul_16                   RCC_CFGR_PLLMULL16
#define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_2) || ((MUL) == RCC_PLLMul_3)   || \
                             ((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5)   || \
                             ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7)   || \
                             ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9)   || \
                             ((MUL) == RCC_PLLMul_10) || ((MUL) == RCC_PLLMul_11) || \
                             ((MUL) == RCC_PLLMul_12) || ((MUL) == RCC_PLLMul_13) || \
                             ((MUL) == RCC_PLLMul_14) || ((MUL) == RCC_PLLMul_15) || \
                             ((MUL) == RCC_PLLMul_16))
/**
  * @}
  */

/** @defgroup RCC_PREDIV1_division_factor
  * @{
  */
#define  RCC_PREDIV1_Div1               RCC_CFGR2_PREDIV1_DIV1
#define  RCC_PREDIV1_Div2               RCC_CFGR2_PREDIV1_DIV2
#define  RCC_PREDIV1_Div3               RCC_CFGR2_PREDIV1_DIV3
#define  RCC_PREDIV1_Div4               RCC_CFGR2_PREDIV1_DIV4
#define  RCC_PREDIV1_Div5               RCC_CFGR2_PREDIV1_DIV5
#define  RCC_PREDIV1_Div6               RCC_CFGR2_PREDIV1_DIV6
#define  RCC_PREDIV1_Div7               RCC_CFGR2_PREDIV1_DIV7
#define  RCC_PREDIV1_Div8               RCC_CFGR2_PREDIV1_DIV8
#define  RCC_PREDIV1_Div9               RCC_CFGR2_PREDIV1_DIV9
#define  RCC_PREDIV1_Div10              RCC_CFGR2_PREDIV1_DIV10
#define  RCC_PREDIV1_Div11              RCC_CFGR2_PREDIV1_DIV11
#define  RCC_PREDIV1_Div12              RCC_CFGR2_PREDIV1_DIV12
#define  RCC_PREDIV1_Div13              RCC_CFGR2_PREDIV1_DIV13
#define  RCC_PREDIV1_Div14              RCC_CFGR2_PREDIV1_DIV14
#define  RCC_PREDIV1_Div15              RCC_CFGR2_PREDIV1_DIV15
#define  RCC_PREDIV1_Div16              RCC_CFGR2_PREDIV1_DIV16

#define IS_RCC_PREDIV1(PREDIV1) (((PREDIV1) == RCC_PREDIV1_Div1) || ((PREDIV1) == RCC_PREDIV1_Div2) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div3) || ((PREDIV1) == RCC_PREDIV1_Div4) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div5) || ((PREDIV1) == RCC_PREDIV1_Div6) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div7) || ((PREDIV1) == RCC_PREDIV1_Div8) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div9) || ((PREDIV1) == RCC_PREDIV1_Div10) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div11) || ((PREDIV1) == RCC_PREDIV1_Div12) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div13) || ((PREDIV1) == RCC_PREDIV1_Div14) || \
                                 ((PREDIV1) == RCC_PREDIV1_Div15) || ((PREDIV1) == RCC_PREDIV1_Div16))
/**
  * @}
  */
 
/** @defgroup RCC_System_Clock_Source 
  * @{
  */

#define RCC_SYSCLKSource_HSI             RCC_CFGR_SW_HSI
#define RCC_SYSCLKSource_HSE             RCC_CFGR_SW_HSE
#define RCC_SYSCLKSource_PLLCLK          RCC_CFGR_SW_PLL
#define RCC_SYSCLKSource_HSI48           RCC_CFGR_SW_HSI48 /*!< Only applicable for STM32F072 devices */

#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI)   || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE)   || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSI48) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK))
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source
  * @{
  */

#define RCC_SYSCLK_Div1                  RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_Div2                  RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_Div4                  RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_Div8                  RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_Div16                 RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_Div64                 RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_Div128                RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_Div256                RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_Div512                RCC_CFGR_HPRE_DIV512
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))
/**
  * @}
  */ 

/** @defgroup RCC_APB_Clock_Source
  * @{
  */

#define RCC_HCLK_Div1                    RCC_CFGR_PPRE_DIV1
#define RCC_HCLK_Div2                    RCC_CFGR_PPRE_DIV2
#define RCC_HCLK_Div4                    RCC_CFGR_PPRE_DIV4
#define RCC_HCLK_Div8                    RCC_CFGR_PPRE_DIV8
#define RCC_HCLK_Div16                   RCC_CFGR_PPRE_DIV16
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))
/**
  * @}
  */
  
/** @defgroup RCC_ADC_clock_source 
  * @{
  */
/* These defines are obsolete and kept for legacy purpose only.
Proper ADC clock selection is done within ADC driver by mean of the ADC_ClockModeConfig() function */
#define RCC_ADCCLK_HSI14                 ((uint32_t)0x00000000)
#define RCC_ADCCLK_PCLK_Div2             ((uint32_t)0x01000000)
#define RCC_ADCCLK_PCLK_Div4             ((uint32_t)0x01004000)

#define IS_RCC_ADCCLK(ADCCLK) (((ADCCLK) == RCC_ADCCLK_HSI14) || ((ADCCLK) == RCC_ADCCLK_PCLK_Div2) || \
                               ((ADCCLK) == RCC_ADCCLK_PCLK_Div4))

/**
  * @}
  */

/** @defgroup RCC_CEC_clock_source 
  * @{
  */

#define RCC_CECCLK_HSI_Div244            ((uint32_t)0x00000000)
#define RCC_CECCLK_LSE                   RCC_CFGR3_CECSW

#define IS_RCC_CECCLK(CECCLK) (((CECCLK) == RCC_CECCLK_HSI_Div244) || ((CECCLK) == RCC_CECCLK_LSE))

/**
  * @}
  */

/** @defgroup RCC_I2C_clock_source 
  * @{
  */

#define RCC_I2C1CLK_HSI                   ((uint32_t)0x00000000)
#define RCC_I2C1CLK_SYSCLK                RCC_CFGR3_I2C1SW

#define IS_RCC_I2CCLK(I2CCLK) (((I2CCLK) == RCC_I2C1CLK_HSI) || ((I2CCLK) == RCC_I2C1CLK_SYSCLK))

/**
  * @}
  */

/** @defgroup RCC_USB_clock_source
  * @brief    Applicable only for STM32F072 devices
  * @{
  */

#define RCC_USBCLK_HSI48                 ((uint32_t)0x00000000)
#define RCC_USBCLK_PLLCLK                RCC_CFGR3_USBSW

#define IS_RCC_USBCLK(USBCLK) (((USBCLK) == RCC_USBCLK_HSI48) || ((USBCLK) == RCC_USBCLK_PLLCLK))

/**
  * @}
  */

/** @defgroup RCC_USART_clock_source 
  * @{
  */

#define RCC_USART1CLK_PCLK                  ((uint32_t)0x10000000)
#define RCC_USART1CLK_SYSCLK                ((uint32_t)0x10000001)
#define RCC_USART1CLK_LSE                   ((uint32_t)0x10000002)
#define RCC_USART1CLK_HSI                   ((uint32_t)0x10000003)

#define RCC_USART2CLK_PCLK                  ((uint32_t)0x20000000) /*!< Only applicable for STM32F072 and STM32F091 devices */
#define RCC_USART2CLK_SYSCLK                ((uint32_t)0x20010000) /*!< Only applicable for STM32F072 and STM32F091 devices */
#define RCC_USART2CLK_LSE                   ((uint32_t)0x20020000) /*!< Only applicable for STM32F072 and STM32F091 devices */
#define RCC_USART2CLK_HSI                   ((uint32_t)0x20030000) /*!< Only applicable for STM32F072 and STM32F091 devices */

#define RCC_USART3CLK_PCLK                  ((uint32_t)0x30000000) /*!< Only applicable for STM32F091 devices */
#define RCC_USART3CLK_SYSCLK                ((uint32_t)0x30040000) /*!< Only applicable for STM32F091 devices */
#define RCC_USART3CLK_LSE                   ((uint32_t)0x30080000) /*!< Only applicable for STM32F091 devices */
#define RCC_USART3CLK_HSI                   ((uint32_t)0x300C0000) /*!< Only applicable for STM32F091 devices */


#define IS_RCC_USARTCLK(USARTCLK) (((USARTCLK) == RCC_USART1CLK_PCLK)   || \
                                   ((USARTCLK) == RCC_USART1CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART1CLK_LSE)    || \
                                   ((USARTCLK) == RCC_USART1CLK_HSI)    || \
                                   ((USARTCLK) == RCC_USART2CLK_PCLK)   || \
                                   ((USARTCLK) == RCC_USART2CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART2CLK_LSE)    || \
                                   ((USARTCLK) == RCC_USART2CLK_HSI)|| \
                                   ((USARTCLK) == RCC_USART3CLK_PCLK)   || \
                                   ((USARTCLK) == RCC_USART3CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART3CLK_LSE)    || \
                                   ((USARTCLK) == RCC_USART3CLK_HSI))

/**
  * @}
  */
         
/** @defgroup RCC_Interrupt_Source 
  * @{
  */

#define RCC_IT_LSIRDY                    ((uint8_t)0x01)
#define RCC_IT_LSERDY                    ((uint8_t)0x02)
#define RCC_IT_HSIRDY                    ((uint8_t)0x04)
#define RCC_IT_HSERDY                    ((uint8_t)0x08)
#define RCC_IT_PLLRDY                    ((uint8_t)0x10)
#define RCC_IT_HSI14RDY                  ((uint8_t)0x20)
#define RCC_IT_HSI48RDY                  ((uint8_t)0x40) /*!< Only applicable for STM32F072 devices */
#define RCC_IT_CSS                       ((uint8_t)0x80)

#define IS_RCC_IT(IT) ((((IT) & (uint8_t)0x80) == 0x00) && ((IT) != 0x00))

#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_HSI14RDY) || \
                           ((IT) == RCC_IT_CSS)    || ((IT) == RCC_IT_HSI48RDY))

#define IS_RCC_CLEAR_IT(IT) ((IT) != 0x00)

/**
  * @}
  */
  
/** @defgroup RCC_LSE_Configuration 
  * @{
  */

#define RCC_LSE_OFF                      ((uint32_t)0x00000000)
#define RCC_LSE_ON                       RCC_BDCR_LSEON
#define RCC_LSE_Bypass                   ((uint32_t)(RCC_BDCR_LSEON | RCC_BDCR_LSEBYP))
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source
  * @{
  */

#define RCC_RTCCLKSource_LSE             RCC_BDCR_RTCSEL_LSE
#define RCC_RTCCLKSource_LSI             RCC_BDCR_RTCSEL_LSI
#define RCC_RTCCLKSource_HSE_Div32       RCC_BDCR_RTCSEL_HSE

#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div32))
/**
  * @}
  */

/** @defgroup RCC_LSE_Drive_Configuration 
  * @{
  */

#define RCC_LSEDrive_Low                 ((uint32_t)0x00000000)
#define RCC_LSEDrive_MediumLow           RCC_BDCR_LSEDRV_0
#define RCC_LSEDrive_MediumHigh          RCC_BDCR_LSEDRV_1
#define RCC_LSEDrive_High                RCC_BDCR_LSEDRV
#define IS_RCC_LSE_DRIVE(DRIVE) (((DRIVE) == RCC_LSEDrive_Low) || ((DRIVE) == RCC_LSEDrive_MediumLow) || \
                                 ((DRIVE) == RCC_LSEDrive_MediumHigh) || ((DRIVE) == RCC_LSEDrive_High))
/**
  * @}
  */
  
/** @defgroup RCC_AHB_Peripherals 
  * @{
  */

#define RCC_AHBPeriph_GPIOA               RCC_AHBENR_GPIOAEN
#define RCC_AHBPeriph_GPIOB               RCC_AHBENR_GPIOBEN
#define RCC_AHBPeriph_GPIOC               RCC_AHBENR_GPIOCEN
#define RCC_AHBPeriph_GPIOD               RCC_AHBENR_GPIODEN
#define RCC_AHBPeriph_GPIOE               RCC_AHBENR_GPIOEEN /*!< Only applicable for STM32F072 and STM32F091 devices */
#define RCC_AHBPeriph_GPIOF               RCC_AHBENR_GPIOFEN
#define RCC_AHBPeriph_TS                  RCC_AHBENR_TSEN
#define RCC_AHBPeriph_CRC                 RCC_AHBENR_CRCEN
#define RCC_AHBPeriph_FLITF               RCC_AHBENR_FLITFEN
#define RCC_AHBPeriph_SRAM                RCC_AHBENR_SRAMEN
#define RCC_AHBPeriph_DMA1                RCC_AHBENR_DMA1EN
#define RCC_AHBPeriph_DMA2                RCC_AHBENR_DMA2EN

#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFE81FFA8) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB_RST_PERIPH(PERIPH) ((((PERIPH) & 0xFE81FFA8) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripherals 
  * @{
  */

#define RCC_APB2Periph_SYSCFG            RCC_APB2ENR_SYSCFGEN
#define RCC_APB2Periph_USART6            RCC_APB2ENR_USART6EN
#define RCC_APB2Periph_USART7            RCC_APB2ENR_USART7EN
#define RCC_APB2Periph_USART8            RCC_APB2ENR_USART8EN
#define RCC_APB2Periph_ADC1              RCC_APB2ENR_ADC1EN
#define RCC_APB2Periph_TIM1              RCC_APB2ENR_TIM1EN
#define RCC_APB2Periph_SPI1              RCC_APB2ENR_SPI1EN
#define RCC_APB2Periph_USART1            RCC_APB2ENR_USART1EN
#define RCC_APB2Periph_TIM15             RCC_APB2ENR_TIM15EN
#define RCC_APB2Periph_TIM16             RCC_APB2ENR_TIM16EN
#define RCC_APB2Periph_TIM17             RCC_APB2ENR_TIM17EN
#define RCC_APB2Periph_DBGMCU            RCC_APB2ENR_DBGMCUEN

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFB8A51E) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */ 

/** @defgroup RCC_APB1_Peripherals 
  * @{
  */

#define RCC_APB1Periph_TIM2              RCC_APB1ENR_TIM2EN    /*!< Only applicable for STM32F051, STM32F072 and STM32F091 devices */
#define RCC_APB1Periph_TIM3              RCC_APB1ENR_TIM3EN
#define RCC_APB1Periph_TIM6              RCC_APB1ENR_TIM6EN
#define RCC_APB1Periph_TIM7              RCC_APB1ENR_TIM7EN    /*!< Only applicable for STM32F072 devices */
#define RCC_APB1Periph_TIM14             RCC_APB1ENR_TIM14EN
#define RCC_APB1Periph_WWDG              RCC_APB1ENR_WWDGEN
#define RCC_APB1Periph_SPI2              RCC_APB1ENR_SPI2EN
#define RCC_APB1Periph_USART2            RCC_APB1ENR_USART2EN
#define RCC_APB1Periph_USART3            RCC_APB1ENR_USART3EN  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define RCC_APB1Periph_USART4            RCC_APB1ENR_USART4EN  /*!< Only applicable for STM32F072 and STM32F091 devices */
#define RCC_APB1Periph_USART5            RCC_APB1ENR_USART5EN  /*!< Only applicable for STM32F091 devices */
#define RCC_APB1Periph_I2C1              RCC_APB1ENR_I2C1EN
#define RCC_APB1Periph_I2C2              RCC_APB1ENR_I2C2EN
#define RCC_APB1Periph_USB               RCC_APB1ENR_USBEN     /*!< Only applicable for STM32F072 and STM32F042 devices */
#define RCC_APB1Periph_CAN               RCC_APB1ENR_CANEN     /*!< Only applicable for STM32F072, STM32F042 and STM32F091 devices */
#define RCC_APB1Periph_CRS               RCC_APB1ENR_CRSEN     /*!< Only applicable for STM32F072, STM32F042 and STM32F091 devices */
#define RCC_APB1Periph_PWR               RCC_APB1ENR_PWREN
#define RCC_APB1Periph_DAC               RCC_APB1ENR_DACEN     /*!< Only applicable for STM32F051, STM32F072 and STM32F091 devices */
#define RCC_APB1Periph_CEC               RCC_APB1ENR_CECEN     /*!< Only applicable for STM32F051, STM32F042, STM32F072 and STM32F091 devices */

#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0x8581B6CC) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Source
  * @{
  */

#define RCC_MCOSource_NoClock            ((uint8_t)0x00)
#define RCC_MCOSource_HSI14              ((uint8_t)0x01)
#define RCC_MCOSource_LSI                ((uint8_t)0x02)
#define RCC_MCOSource_LSE                ((uint8_t)0x03)
#define RCC_MCOSource_SYSCLK             ((uint8_t)0x04)
#define RCC_MCOSource_HSI                ((uint8_t)0x05)
#define RCC_MCOSource_HSE                ((uint8_t)0x06)
#define RCC_MCOSource_PLLCLK_Div2        ((uint8_t)0x07)
#define RCC_MCOSource_HSI48              ((uint8_t)0x08)  /*!< Only applicable for STM32F072 devices */
#define RCC_MCOSource_PLLCLK             ((uint8_t)0x87)

#define IS_RCC_MCO_SOURCE(SOURCE) (((SOURCE) == RCC_MCOSource_NoClock) || ((SOURCE) == RCC_MCOSource_HSI14)      || \
                                   ((SOURCE) == RCC_MCOSource_SYSCLK)  || ((SOURCE) == RCC_MCOSource_HSI)        || \
                                   ((SOURCE) == RCC_MCOSource_HSE)     || ((SOURCE) == RCC_MCOSource_PLLCLK_Div2)|| \
                                   ((SOURCE) == RCC_MCOSource_LSI)     || ((SOURCE) == RCC_MCOSource_HSI48)      || \
                                   ((SOURCE) == RCC_MCOSource_PLLCLK)  || ((SOURCE) == RCC_MCOSource_LSE))
/**
  * @}
  */ 

/** @defgroup RCC_MCOPrescaler
  * @{
  */
#if !defined (STM32F051)
#define RCC_MCOPrescaler_1            RCC_CFGR_MCO_PRE_1
#define RCC_MCOPrescaler_2            RCC_CFGR_MCO_PRE_2
#define RCC_MCOPrescaler_4            RCC_CFGR_MCO_PRE_4
#define RCC_MCOPrescaler_8            RCC_CFGR_MCO_PRE_8
#define RCC_MCOPrescaler_16           RCC_CFGR_MCO_PRE_16
#define RCC_MCOPrescaler_32           RCC_CFGR_MCO_PRE_32
#define RCC_MCOPrescaler_64           RCC_CFGR_MCO_PRE_64
#define RCC_MCOPrescaler_128          RCC_CFGR_MCO_PRE_128

#define IS_RCC_MCO_PRESCALER(PRESCALER) (((PRESCALER) == RCC_MCOPrescaler_1)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_2)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_4)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_8)  || \
                                         ((PRESCALER) == RCC_MCOPrescaler_16) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_32) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_64) || \
                                         ((PRESCALER) == RCC_MCOPrescaler_128))
#endif /* STM32F051 */                                         
/**
  * @}
  */ 

/** @defgroup RCC_Flag 
  * @{
  */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x01)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x11)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x19)
#define RCC_FLAG_LSERDY                  ((uint8_t)0x21)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x41)
#define RCC_FLAG_V18PWRRSTF              ((uint8_t)0x57)
#define RCC_FLAG_OBLRST                  ((uint8_t)0x59)
#define RCC_FLAG_PINRST                  ((uint8_t)0x5A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x5B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x5C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x5D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x5E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x5F)
#define RCC_FLAG_HSI14RDY                ((uint8_t)0x61)
#define RCC_FLAG_HSI48RDY                ((uint8_t)0x71) /*!< Only applicable for STM32F072 devices */ 

#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY)  || ((FLAG) == RCC_FLAG_HSERDY)  || \
                           ((FLAG) == RCC_FLAG_PLLRDY)  || ((FLAG) == RCC_FLAG_LSERDY)  || \
                           ((FLAG) == RCC_FLAG_LSIRDY)  || ((FLAG) == RCC_FLAG_OBLRST)  || \
                           ((FLAG) == RCC_FLAG_PINRST)  || ((FLAG) == RCC_FLAG_PORRST)  || \
                           ((FLAG) == RCC_FLAG_SFTRST)  || ((FLAG) == RCC_FLAG_IWDGRST) || \
                           ((FLAG) == RCC_FLAG_WWDGRST) || ((FLAG) == RCC_FLAG_LPWRRST) || \
                           ((FLAG) == RCC_FLAG_HSI14RDY)|| ((FLAG) == RCC_FLAG_HSI48RDY)|| \
                           ((FLAG) == RCC_FLAG_V18PWRRSTF))

#define IS_RCC_HSI_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)
#define IS_RCC_HSI14_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the RCC clock configuration to the default reset state */
void RCC_DeInit(void);

/* Internal/external clocks, PLL, CSS and MCO configuration functions *********/
void RCC_HSEConfig(uint8_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_AdjustHSI14CalibrationValue(uint8_t HSI14CalibrationValue);
void RCC_HSI14Cmd(FunctionalState NewState);
void RCC_HSI14ADCRequestCmd(FunctionalState NewState);
void RCC_LSEConfig(uint32_t RCC_LSE);
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive);
void RCC_LSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_HSI48Cmd(FunctionalState NewState); /*!< Only applicable for STM32F072 devices */
uint32_t RCC_GetHSI48CalibrationValue(void); /*!< Only applicable for STM32F072 devices */
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Div);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
#ifdef STM32F051
void RCC_MCOConfig(uint8_t RCC_MCOSource);
#else
void RCC_MCOConfig(uint8_t RCC_MCOSource,uint32_t RCC_MCOPrescaler);
#endif /* STM32F051 */

/* System, AHB and APB busses clocks configuration functions ******************/
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLKConfig(uint32_t RCC_HCLK);
void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK); /* This function is obsolete.
                                               For proper ADC clock selection, refer to
                                               ADC_ClockModeConfig() in the ADC driver */
void RCC_CECCLKConfig(uint32_t RCC_CECCLK);
void RCC_I2CCLKConfig(uint32_t RCC_I2CCLK);
void RCC_USARTCLKConfig(uint32_t RCC_USARTCLK);
void RCC_USBCLKConfig(uint32_t RCC_USBCLK); /*!< Only applicable for STM32F042 and STM32F072 devices */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

/* Peripheral clocks configuration functions **********************************/
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);

void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_RCC_H */

/**
  * @}
  */

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_rtc.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the RTC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_RTC_H
#define __STM32F0XX_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  RTC Init structures definition  
  */ 
typedef struct
{
  uint32_t RTC_HourFormat;   /*!< Specifies the RTC Hour Format.
                             This parameter can be a value of @ref RTC_Hour_Formats */
  
  uint32_t RTC_AsynchPrediv; /*!< Specifies the RTC Asynchronous Predivider value.
                             This parameter must be set to a value lower than 0x7F */
  
  uint32_t RTC_SynchPrediv;  /*!< Specifies the RTC Synchronous Predivider value.
                             This parameter must be set to a value lower than 0x1FFF */
}RTC_InitTypeDef;

/** 
  * @brief  RTC Time structure definition  
  */
typedef struct
{
  uint8_t RTC_Hours;    /*!< Specifies the RTC Time Hour.
                        This parameter must be set to a value in the 0-12 range
                        if the RTC_HourFormat_12 is selected or 0-23 range if
                        the RTC_HourFormat_24 is selected. */

  uint8_t RTC_Minutes;  /*!< Specifies the RTC Time Minutes.
                        This parameter must be set to a value in the 0-59 range. */
  
  uint8_t RTC_Seconds;  /*!< Specifies the RTC Time Seconds.
                        This parameter must be set to a value in the 0-59 range. */

  uint8_t RTC_H12;      /*!< Specifies the RTC AM/PM Time.
                        This parameter can be a value of @ref RTC_AM_PM_Definitions */
}RTC_TimeTypeDef; 

/** 
  * @brief  RTC Date structure definition  
  */
typedef struct
{
  uint8_t RTC_WeekDay; /*!< Specifies the RTC Date WeekDay.
                        This parameter can be a value of @ref RTC_WeekDay_Definitions */
  
  uint8_t RTC_Month;   /*!< Specifies the RTC Date Month.
                        This parameter can be a value of @ref RTC_Month_Date_Definitions */

  uint8_t RTC_Date;     /*!< Specifies the RTC Date.
                        This parameter must be set to a value in the 1-31 range. */
  
  uint8_t RTC_Year;     /*!< Specifies the RTC Date Year.
                        This parameter must be set to a value in the 0-99 range. */
}RTC_DateTypeDef;

/** 
  * @brief  RTC Alarm structure definition  
  */
typedef struct
{
  RTC_TimeTypeDef RTC_AlarmTime;     /*!< Specifies the RTC Alarm Time members. */

  uint32_t RTC_AlarmMask;            /*!< Specifies the RTC Alarm Masks.
                                     This parameter can be a value of @ref RTC_AlarmMask_Definitions */

  uint32_t RTC_AlarmDateWeekDaySel;  /*!< Specifies the RTC Alarm is on Date or WeekDay.
                                     This parameter can be a value of @ref RTC_AlarmDateWeekDay_Definitions */
  
  uint8_t RTC_AlarmDateWeekDay;      /*!< Specifies the RTC Alarm Date/WeekDay.
                                     This parameter must be set to a value in the 1-31 range 
                                     if the Alarm Date is selected.
                                     This parameter can be a value of @ref RTC_WeekDay_Definitions 
                                     if the Alarm WeekDay is selected. */
}RTC_AlarmTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Exported_Constants
  * @{
  */ 


/** @defgroup RTC_Hour_Formats 
  * @{
  */ 
#define RTC_HourFormat_24              ((uint32_t)0x00000000)
#define RTC_HourFormat_12              ((uint32_t)0x00000040)
#define IS_RTC_HOUR_FORMAT(FORMAT)     (((FORMAT) == RTC_HourFormat_12) || \
                                        ((FORMAT) == RTC_HourFormat_24))
/**
  * @}
  */ 

/** @defgroup RTC_Asynchronous_Predivider 
  * @{
  */ 
#define IS_RTC_ASYNCH_PREDIV(PREDIV)   ((PREDIV) <= 0x7F)
 
/**
  * @}
  */ 


/** @defgroup RTC_Synchronous_Predivider 
  * @{
  */ 
#define IS_RTC_SYNCH_PREDIV(PREDIV)    ((PREDIV) <= 0x7FFF)

/**
  * @}
  */ 

/** @defgroup RTC_Time_Definitions 
  * @{
  */ 
#define IS_RTC_HOUR12(HOUR)            (((HOUR) > 0) && ((HOUR) <= 12))
#define IS_RTC_HOUR24(HOUR)            ((HOUR) <= 23)
#define IS_RTC_MINUTES(MINUTES)        ((MINUTES) <= 59)
#define IS_RTC_SECONDS(SECONDS)        ((SECONDS) <= 59)

/**
  * @}
  */ 

/** @defgroup RTC_AM_PM_Definitions 
  * @{
  */ 
#define RTC_H12_AM                     ((uint8_t)0x00)
#define RTC_H12_PM                     ((uint8_t)0x40)
#define IS_RTC_H12(PM) (((PM) == RTC_H12_AM) || ((PM) == RTC_H12_PM))

/**
  * @}
  */ 

/** @defgroup RTC_Year_Date_Definitions 
  * @{
  */ 
#define IS_RTC_YEAR(YEAR)              ((YEAR) <= 99)

/**
  * @}
  */ 

/** @defgroup RTC_Month_Date_Definitions 
  * @{
  */ 
#define RTC_Month_January              ((uint8_t)0x01)
#define RTC_Month_February             ((uint8_t)0x02)
#define RTC_Month_March                ((uint8_t)0x03)
#define RTC_Month_April                ((uint8_t)0x04)
#define RTC_Month_May                  ((uint8_t)0x05)
#define RTC_Month_June                 ((uint8_t)0x06)
#define RTC_Month_July                 ((uint8_t)0x07)
#define RTC_Month_August               ((uint8_t)0x08)
#define RTC_Month_September            ((uint8_t)0x09)
#define RTC_Month_October              ((uint8_t)0x10)
#define RTC_Month_November             ((uint8_t)0x11)
#define RTC_Month_December             ((uint8_t)0x12)
#define IS_RTC_MONTH(MONTH)            (((MONTH) >= 1) && ((MONTH) <= 12))
#define IS_RTC_DATE(DATE)              (((DATE) >= 1) && ((DATE) <= 31))

/**
  * @}
  */ 

/** @defgroup RTC_WeekDay_Definitions 
  * @{
  */ 
  
#define	RTC_Weekday_Monday             ((uint8_t)0x01)
#define	RTC_Weekday_Tuesday            ((uint8_t)0x02)
#define	RTC_Weekday_Wednesday          ((uint8_t)0x03)
#define	RTC_Weekday_Thursday           ((uint8_t)0x04)
#define	RTC_Weekday_Friday             ((uint8_t)0x05)
#define	RTC_Weekday_Saturday           ((uint8_t)0x6)
#define	RTC_Weekday_Sunday             ((uint8_t)0x07)
#define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday) || \
                                 ((WEEKDAY) == RTC_Weekday_Tuesday) || \
                                 ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                 ((WEEKDAY) == RTC_Weekday_Thursday) || \
                                 ((WEEKDAY) == RTC_Weekday_Friday) || \
                                 ((WEEKDAY) == RTC_Weekday_Saturday) || \
                                 ((WEEKDAY) == RTC_Weekday_Sunday))
/**
  * @}
  */ 


/** @defgroup RTC_Alarm_Definitions 
  * @{
  */ 
#define IS_RTC_ALARM_DATE_WEEKDAY_DATE(DATE) (((DATE) > 0) && ((DATE) <= 31))
#define IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday) || \
                                                    ((WEEKDAY) == RTC_Weekday_Tuesday) || \
                                                    ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                                    ((WEEKDAY) == RTC_Weekday_Thursday) || \
                                                    ((WEEKDAY) == RTC_Weekday_Friday) || \
                                                    ((WEEKDAY) == RTC_Weekday_Saturday) || \
                                                    ((WEEKDAY) == RTC_Weekday_Sunday))

/**
  * @}
  */ 


/** @defgroup RTC_AlarmDateWeekDay_Definitions 
  * @{
  */ 
#define RTC_AlarmDateWeekDaySel_Date      ((uint32_t)0x00000000)  
#define RTC_AlarmDateWeekDaySel_WeekDay   ((uint32_t)0x40000000)  

#define IS_RTC_ALARM_DATE_WEEKDAY_SEL(SEL) (((SEL) == RTC_AlarmDateWeekDaySel_Date) || \
                                            ((SEL) == RTC_AlarmDateWeekDaySel_WeekDay))

/**
  * @}
  */ 


/** @defgroup RTC_AlarmMask_Definitions 
  * @{
  */ 
#define RTC_AlarmMask_None                ((uint32_t)0x00000000)
#define RTC_AlarmMask_DateWeekDay         ((uint32_t)0x80000000)  
#define RTC_AlarmMask_Hours               ((uint32_t)0x00800000)
#define RTC_AlarmMask_Minutes             ((uint32_t)0x00008000)
#define RTC_AlarmMask_Seconds             ((uint32_t)0x00000080)
#define RTC_AlarmMask_All                 ((uint32_t)0x80808080)
#define IS_RTC_ALARM_MASK(MASK)  (((MASK) & 0x7F7F7F7F) == (uint32_t)RESET)

/**
  * @}
  */ 

/** @defgroup RTC_Alarms_Definitions 
  * @{
  */ 
#define RTC_Alarm_A                       ((uint32_t)0x00000100)
#define IS_RTC_ALARM(ALARM)      ((ALARM) == RTC_Alarm_A)
#define IS_RTC_CMD_ALARM(ALARM)  (((ALARM) & (RTC_Alarm_A)) != (uint32_t)RESET)

/**
  * @}
  */ 

/** @defgroup RTC_Alarm_Sub_Seconds_Masks Definitions.
  * @{
  */ 
#define RTC_AlarmSubSecondMask_All         ((uint8_t)0x00) /*!< All Alarm SS fields are masked. 
                                                                There is no comparison on sub seconds 
                                                                for Alarm */
#define RTC_AlarmSubSecondMask_SS14_1      ((uint8_t)0x01) /*!< SS[14:1] are don't care in Alarm 
                                                                comparison. Only SS[0] is compared. */
#define RTC_AlarmSubSecondMask_SS14_2      ((uint8_t)0x02) /*!< SS[14:2] are don't care in Alarm 
                                                                comparison. Only SS[1:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_3      ((uint8_t)0x03) /*!< SS[14:3] are don't care in Alarm 
                                                                comparison. Only SS[2:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_4      ((uint8_t)0x04) /*!< SS[14:4] are don't care in Alarm 
                                                                comparison. Only SS[3:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_5      ((uint8_t)0x05) /*!< SS[14:5] are don't care in Alarm 
                                                                comparison. Only SS[4:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_6      ((uint8_t)0x06) /*!< SS[14:6] are don't care in Alarm 
                                                                comparison. Only SS[5:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_7      ((uint8_t)0x07) /*!< SS[14:7] are don't care in Alarm 
                                                                comparison. Only SS[6:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_8      ((uint8_t)0x08) /*!< SS[14:8] are don't care in Alarm 
                                                                comparison. Only SS[7:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_9      ((uint8_t)0x09) /*!< SS[14:9] are don't care in Alarm 
                                                                comparison. Only SS[8:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_10     ((uint8_t)0x0A) /*!< SS[14:10] are don't care in Alarm 
                                                                comparison. Only SS[9:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_11     ((uint8_t)0x0B) /*!< SS[14:11] are don't care in Alarm 
                                                                comparison. Only SS[10:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_12     ((uint8_t)0x0C) /*!< SS[14:12] are don't care in Alarm 
                                                                comparison.Only SS[11:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_13     ((uint8_t)0x0D) /*!< SS[14:13] are don't care in Alarm 
                                                                comparison. Only SS[12:0] are compared */
#define RTC_AlarmSubSecondMask_SS14        ((uint8_t)0x0E) /*!< SS[14] is don't care in Alarm 
                                                                comparison.Only SS[13:0] are compared */
#define RTC_AlarmSubSecondMask_None        ((uint8_t)0x0F) /*!< SS[14:0] are compared and must match 
                                                                to activate alarm. */
#define IS_RTC_ALARM_SUB_SECOND_MASK(MASK)   (((MASK) == RTC_AlarmSubSecondMask_All) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_1) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_2) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_3) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_4) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_5) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_6) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_7) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_8) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_9) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_10) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_11) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_12) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_13) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_SS14) || \
                                              ((MASK) == RTC_AlarmSubSecondMask_None))
/**
  * @}
  */ 

/** @defgroup RTC_Alarm_Sub_Seconds_Value
  * @{
  */ 
  
#define IS_RTC_ALARM_SUB_SECOND_VALUE(VALUE) ((VALUE) <= 0x00007FFF)

/**
  * @}
  */ 

/** @defgroup RTC_Wakeup_Timer_Definitions 
  * @brief    These parameters are only available for STM32F072 devices
  * @{
  */
#define RTC_WakeUpClock_RTCCLK_Div16        ((uint32_t)0x00000000)
#define RTC_WakeUpClock_RTCCLK_Div8         ((uint32_t)0x00000001)
#define RTC_WakeUpClock_RTCCLK_Div4         ((uint32_t)0x00000002)
#define RTC_WakeUpClock_RTCCLK_Div2         ((uint32_t)0x00000003)
#define RTC_WakeUpClock_CK_SPRE_16bits      ((uint32_t)0x00000004)
#define RTC_WakeUpClock_CK_SPRE_17bits      ((uint32_t)0x00000006)
#define IS_RTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == RTC_WakeUpClock_RTCCLK_Div16) || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div8) || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div4) || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div2) || \
                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_16bits) || \
                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_17bits))
#define IS_RTC_WAKEUP_COUNTER(COUNTER)  ((COUNTER) <= 0xFFFF)
/**
  * @}
  */ 

/** @defgroup RTC_Time_Stamp_Edges_definitions 
  * @{
  */ 
#define RTC_TimeStampEdge_Rising          ((uint32_t)0x00000000)
#define RTC_TimeStampEdge_Falling         ((uint32_t)0x00000008)
#define IS_RTC_TIMESTAMP_EDGE(EDGE) (((EDGE) == RTC_TimeStampEdge_Rising) || \
                                     ((EDGE) == RTC_TimeStampEdge_Falling))
/**
  * @}
  */ 

/** @defgroup RTC_Output_selection_Definitions 
  * @{
  */ 
#define RTC_Output_Disable             ((uint32_t)0x00000000)
#define RTC_Output_AlarmA              ((uint32_t)0x00200000)
#define RTC_Output_WakeUp              ((uint32_t)0x00600000) /*!< available only for STM32F072 devices */
 
#define IS_RTC_OUTPUT(OUTPUT) (((OUTPUT) == RTC_Output_Disable) || \
                               ((OUTPUT) == RTC_Output_AlarmA)  || \
                               ((OUTPUT) == RTC_Output_WakeUp))

/**
  * @}
  */ 

/** @defgroup RTC_Output_Polarity_Definitions 
  * @{
  */ 
#define RTC_OutputPolarity_High           ((uint32_t)0x00000000)
#define RTC_OutputPolarity_Low            ((uint32_t)0x00100000)
#define IS_RTC_OUTPUT_POL(POL) (((POL) == RTC_OutputPolarity_High) || \
                                ((POL) == RTC_OutputPolarity_Low))
/**
  * @}
  */ 


/** @defgroup RTC_Calib_Output_selection_Definitions 
  * @{
  */ 
#define RTC_CalibOutput_512Hz            ((uint32_t)0x00000000) 
#define RTC_CalibOutput_1Hz              ((uint32_t)0x00080000)
#define IS_RTC_CALIB_OUTPUT(OUTPUT)  (((OUTPUT) == RTC_CalibOutput_512Hz) || \
                                      ((OUTPUT) == RTC_CalibOutput_1Hz))
/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_period_Definitions 
  * @{
  */ 
#define RTC_SmoothCalibPeriod_32sec   ((uint32_t)0x00000000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation
                                                             period is 32s,  else 2exp20 RTCCLK seconds */
#define RTC_SmoothCalibPeriod_16sec   ((uint32_t)0x00002000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation 
                                                             period is 16s, else 2exp19 RTCCLK seconds */
#define RTC_SmoothCalibPeriod_8sec    ((uint32_t)0x00004000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation 
                                                             period is 8s, else 2exp18 RTCCLK seconds */
#define  IS_RTC_SMOOTH_CALIB_PERIOD(PERIOD) (((PERIOD) == RTC_SmoothCalibPeriod_32sec) || \
                                             ((PERIOD) == RTC_SmoothCalibPeriod_16sec) || \
                                             ((PERIOD) == RTC_SmoothCalibPeriod_8sec))
                                          
/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_Plus_pulses_Definitions 
  * @{
  */ 
#define RTC_SmoothCalibPlusPulses_Set    ((uint32_t)0x00008000) /*!<  The number of RTCCLK pulses added  
                                                                during a X -second window = Y - CALM[8:0]. 
                                                                 with Y = 512, 256, 128 when X = 32, 16, 8 */
#define RTC_SmoothCalibPlusPulses_Reset  ((uint32_t)0x00000000) /*!<  The number of RTCCLK pulses subbstited
                                                                 during a 32-second window =   CALM[8:0]. */
#define  IS_RTC_SMOOTH_CALIB_PLUS(PLUS) (((PLUS) == RTC_SmoothCalibPlusPulses_Set) || \
                                         ((PLUS) == RTC_SmoothCalibPlusPulses_Reset))

/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_Minus_pulses_Definitions 
  * @{
  */ 
#define  IS_RTC_SMOOTH_CALIB_MINUS(VALUE) ((VALUE) <= 0x000001FF)

/**
  * @}
  */ 

/** @defgroup RTC_DayLightSaving_Definitions 
  * @{
  */ 
#define RTC_DayLightSaving_SUB1H   ((uint32_t)0x00020000)
#define RTC_DayLightSaving_ADD1H   ((uint32_t)0x00010000)
#define IS_RTC_DAYLIGHT_SAVING(SAVING) (((SAVING) == RTC_DayLightSaving_SUB1H) || \
                                        ((SAVING) == RTC_DayLightSaving_ADD1H))

#define RTC_StoreOperation_Reset        ((uint32_t)0x00000000)
#define RTC_StoreOperation_Set          ((uint32_t)0x00040000)
#define IS_RTC_STORE_OPERATION(OPERATION) (((OPERATION) == RTC_StoreOperation_Reset) || \
                                           ((OPERATION) == RTC_StoreOperation_Set))
/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Trigger_Definitions 
  * @{
  */ 
#define RTC_TamperTrigger_RisingEdge            ((uint32_t)0x00000000)
#define RTC_TamperTrigger_FallingEdge           ((uint32_t)0x00000001)
#define RTC_TamperTrigger_LowLevel              ((uint32_t)0x00000000)
#define RTC_TamperTrigger_HighLevel             ((uint32_t)0x00000001)
#define IS_RTC_TAMPER_TRIGGER(TRIGGER) (((TRIGGER) == RTC_TamperTrigger_RisingEdge) || \
                                        ((TRIGGER) == RTC_TamperTrigger_FallingEdge) || \
                                        ((TRIGGER) == RTC_TamperTrigger_LowLevel) || \
                                        ((TRIGGER) == RTC_TamperTrigger_HighLevel)) 

/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Filter_Definitions 
  * @{
  */ 
#define RTC_TamperFilter_Disable   ((uint32_t)0x00000000) /*!< Tamper filter is disabled */

#define RTC_TamperFilter_2Sample   ((uint32_t)0x00000800) /*!< Tamper is activated after 2 
                                                          consecutive samples at the active level */
#define RTC_TamperFilter_4Sample   ((uint32_t)0x00001000) /*!< Tamper is activated after 4 
                                                          consecutive samples at the active level */
#define RTC_TamperFilter_8Sample   ((uint32_t)0x00001800) /*!< Tamper is activated after 8 
                                                          consecutive samples at the active leve. */
#define IS_RTC_TAMPER_FILTER(FILTER) (((FILTER) == RTC_TamperFilter_Disable) || \
                                      ((FILTER) == RTC_TamperFilter_2Sample) || \
                                      ((FILTER) == RTC_TamperFilter_4Sample) || \
                                      ((FILTER) == RTC_TamperFilter_8Sample))
/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Sampling_Frequencies_Definitions 
  * @{
  */ 
#define RTC_TamperSamplingFreq_RTCCLK_Div32768 ((uint32_t)0x00000000) /*!< Each of the tamper inputs are sampled
                                                                      with a frequency =  RTCCLK / 32768 */
#define RTC_TamperSamplingFreq_RTCCLK_Div16384 ((uint32_t)0x00000100) /*!< Each of the tamper inputs are sampled
                                                                      with a frequency =  RTCCLK / 16384 */
#define RTC_TamperSamplingFreq_RTCCLK_Div8192  ((uint32_t)0x00000200) /*!< Each of the tamper inputs are sampled
                                                                      with a frequency =  RTCCLK / 8192  */
#define RTC_TamperSamplingFreq_RTCCLK_Div4096  ((uint32_t)0x00000300) /*!< Each of the tamper inputs are sampled
                                                                      with a frequency =  RTCCLK / 4096  */
#define RTC_TamperSamplingFreq_RTCCLK_Div2048  ((uint32_t)0x00000400) /*!< Each of the tamper inputs are sampled
                                                                      with a frequency =  RTCCLK / 2048  */
#define RTC_TamperSamplingFreq_RTCCLK_Div1024  ((uint32_t)0x00000500) /*!< Each of the tamper inputs are sampled
                                                                      with a frequency =  RTCCLK / 1024  */
#define RTC_TamperSamplingFreq_RTCCLK_Div512   ((uint32_t)0x00000600) /*!< Each of the tamper inputs are sampled
                                                                      with a frequency =  RTCCLK / 512   */
#define RTC_TamperSamplingFreq_RTCCLK_Div256   ((uint32_t)0x00000700) /*!< Each of the tamper inputs are sampled
                                                                      with a frequency =  RTCCLK / 256   */
#define IS_RTC_TAMPER_SAMPLING_FREQ(FREQ) (((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div32768) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div16384) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div8192) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div4096) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div2048) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div1024) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div512) || \
                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div256))
                                           
/**
  * @}
  */

  /** @defgroup RTC_Tamper_Pin_Precharge_Duration_Definitions 
  * @{
  */ 
#define RTC_TamperPrechargeDuration_1RTCCLK ((uint32_t)0x00000000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 1 RTCCLK cycle */
#define RTC_TamperPrechargeDuration_2RTCCLK ((uint32_t)0x00002000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 2 RTCCLK cycles */
#define RTC_TamperPrechargeDuration_4RTCCLK ((uint32_t)0x00004000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 4 RTCCLK cycles */
#define RTC_TamperPrechargeDuration_8RTCCLK ((uint32_t)0x00006000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 8 RTCCLK cycles */

#define IS_RTC_TAMPER_PRECHARGE_DURATION(DURATION) (((DURATION) == RTC_TamperPrechargeDuration_1RTCCLK) || \
                                                    ((DURATION) == RTC_TamperPrechargeDuration_2RTCCLK) || \
                                                    ((DURATION) == RTC_TamperPrechargeDuration_4RTCCLK) || \
                                                    ((DURATION) == RTC_TamperPrechargeDuration_8RTCCLK))
/**
  * @}
  */

/** @defgroup RTC_Tamper_Pins_Definitions 
  * @{
  */ 
#define RTC_Tamper_1            RTC_TAFCR_TAMP1E /*!< Tamper detection enable for 
                                                 input tamper 1 */
#define RTC_Tamper_2            RTC_TAFCR_TAMP2E /*!< Tamper detection enable for 
                                                 input tamper 2 */
#define RTC_Tamper_3            RTC_TAFCR_TAMP3E /*!< Tamper detection enable for 
                                                 input tamper 3, available only 
                                                 for STM32F072 devices */
#define IS_RTC_TAMPER(TAMPER) ((((TAMPER) & (uint32_t)0xFFFFFFD6) == 0x00) && ((TAMPER) != (uint32_t)RESET))

/**
  * @}
  */

/** @defgroup RTC_Output_Type_ALARM_OUT 
  * @{
  */ 
#define RTC_OutputType_OpenDrain           ((uint32_t)0x00000000)
#define RTC_OutputType_PushPull            ((uint32_t)0x00040000)
#define IS_RTC_OUTPUT_TYPE(TYPE) (((TYPE) == RTC_OutputType_OpenDrain) || \
                                  ((TYPE) == RTC_OutputType_PushPull))

/**
  * @}
  */ 

/** @defgroup RTC_Add_1_Second_Parameter_Definitions
  * @{
  */ 
#define RTC_ShiftAdd1S_Reset      ((uint32_t)0x00000000)
#define RTC_ShiftAdd1S_Set        ((uint32_t)0x80000000)
#define IS_RTC_SHIFT_ADD1S(SEL) (((SEL) == RTC_ShiftAdd1S_Reset) || \
                                 ((SEL) == RTC_ShiftAdd1S_Set))
/**
  * @}
  */ 

/** @defgroup RTC_Substract_Fraction_Of_Second_Value
  * @{
  */ 
#define IS_RTC_SHIFT_SUBFS(FS) ((FS) <= 0x00007FFF)

/**
  * @}
  */ 

/** @defgroup RTC_Backup_Registers_Definitions 
  * @{
  */

#define RTC_BKP_DR0                       ((uint32_t)0x00000000)
#define RTC_BKP_DR1                       ((uint32_t)0x00000001)
#define RTC_BKP_DR2                       ((uint32_t)0x00000002)
#define RTC_BKP_DR3                       ((uint32_t)0x00000003)
#define RTC_BKP_DR4                       ((uint32_t)0x00000004)
#define IS_RTC_BKP(BKP)                   (((BKP) == RTC_BKP_DR0) || \
                                           ((BKP) == RTC_BKP_DR1) || \
                                           ((BKP) == RTC_BKP_DR2) || \
                                           ((BKP) == RTC_BKP_DR3) || \
                                           ((BKP) == RTC_BKP_DR4)) 
/**
  * @}
  */ 

/** @defgroup RTC_Input_parameter_format_definitions 
  * @{
  */ 
#define RTC_Format_BIN                    ((uint32_t)0x000000000)
#define RTC_Format_BCD                    ((uint32_t)0x000000001)
#define IS_RTC_FORMAT(FORMAT) (((FORMAT) == RTC_Format_BIN) || ((FORMAT) == RTC_Format_BCD))

/**
  * @}
  */ 

/** @defgroup RTC_Flags_Definitions 
  * @{
  */ 
#define RTC_FLAG_RECALPF                  RTC_ISR_RECALPF
#define RTC_FLAG_TAMP3F                   RTC_ISR_TAMP3F /*!< Only available for STM32F072 devices */
#define RTC_FLAG_TAMP2F                   RTC_ISR_TAMP2F
#define RTC_FLAG_TAMP1F                   RTC_ISR_TAMP1F
#define RTC_FLAG_TSOVF                    RTC_ISR_TSOVF
#define RTC_FLAG_TSF                      RTC_ISR_TSF
#define RTC_FLAG_WUTF                     RTC_ISR_WUTF /*!< Only available for STM32F072 devices */
#define RTC_FLAG_ALRAF                    RTC_ISR_ALRAF
#define RTC_FLAG_INITF                    RTC_ISR_INITF
#define RTC_FLAG_RSF                      RTC_ISR_RSF
#define RTC_FLAG_INITS                    RTC_ISR_INITS
#define RTC_FLAG_SHPF                     RTC_ISR_SHPF
#define RTC_FLAG_WUTWF                    RTC_ISR_WUTWF /*!< Only available for STM32F072 devices */
#define RTC_FLAG_ALRAWF                   RTC_ISR_ALRAWF 

#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_TSOVF)  || ((FLAG) == RTC_FLAG_TSF)     || \
                               ((FLAG) == RTC_FLAG_WUTF)   || ((FLAG) == RTC_FLAG_ALRAWF)  || \
                               ((FLAG) == RTC_FLAG_ALRAF)  || ((FLAG) == RTC_FLAG_INITF)   || \
                               ((FLAG) == RTC_FLAG_RSF)    || ((FLAG) == RTC_FLAG_WUTWF)   || \
                               ((FLAG) == RTC_FLAG_TAMP1F) || ((FLAG) == RTC_FLAG_TAMP2F)  || \
                               ((FLAG) == RTC_FLAG_TAMP3F) || ((FLAG) == RTC_FLAG_RECALPF) || \
                               ((FLAG) == RTC_FLAG_SHPF))
#define IS_RTC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFF02DF) == (uint32_t)RESET))

/**
  * @}
  */ 

/** @defgroup RTC_Interrupts_Definitions 
  * @{
  */ 
#define RTC_IT_TS                         ((uint32_t)0x00008000)
#define RTC_IT_WUT                        ((uint32_t)0x00004000) /* Available only for STM32F072 devices */
#define RTC_IT_ALRA                       ((uint32_t)0x00001000)
#define RTC_IT_TAMP                       ((uint32_t)0x00000004) /* Used only to Enable the Tamper Interrupt */
#define RTC_IT_TAMP1                      ((uint32_t)0x00020000)
#define RTC_IT_TAMP2                      ((uint32_t)0x00040000)
#define RTC_IT_TAMP3                      ((uint32_t)0x00080000) /* Available only for STM32F072 devices */

#define IS_RTC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFF2FFB) == (uint32_t)RESET))
#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_TS)    || ((IT) == RTC_IT_ALRA)  || \
                           ((IT) == RTC_IT_TAMP1) || ((IT) == RTC_IT_WUT)   || \
                           ((IT) == RTC_IT_TAMP2) || ((IT) == RTC_IT_TAMP3))                           

#define IS_RTC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFF12FFF) == (uint32_t)RESET))

/**
  * @}
  */ 

/**
  * @}
  */ 


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/*  Function used to set the RTC configuration to the default reset state *****/
ErrorStatus RTC_DeInit(void);


/* Initialization and Configuration functions *********************************/
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct);
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct);
void RTC_WriteProtectionCmd(FunctionalState NewState);
ErrorStatus RTC_EnterInitMode(void);
void RTC_ExitInitMode(void);
ErrorStatus RTC_WaitForSynchro(void);
ErrorStatus RTC_RefClockCmd(FunctionalState NewState);
void RTC_BypassShadowCmd(FunctionalState NewState);

/* Time and Date configuration functions **************************************/
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);
uint32_t RTC_GetSubSecond(void);
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct);
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct);
void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct);

/* Alarms (Alarm A) configuration functions  **********************************/
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct);
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState);
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint8_t RTC_AlarmSubSecondMask);
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm);

/* WakeUp Timer configuration functions ***************************************/ 
void RTC_WakeUpClockConfig(uint32_t RTC_WakeUpClock); /*!< available only for STM32F072 devices */ 
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter); /*!< available only for STM32F072 devices */ 
uint32_t RTC_GetWakeUpCounter(void); /*!< available only for STM32F072 devices */ 
ErrorStatus RTC_WakeUpCmd(FunctionalState NewState); /*!< available only for STM32F072 devices */ 

/* Daylight Saving configuration functions ************************************/
void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation);
uint32_t RTC_GetStoreOperation(void);

/* Output pin Configuration function ******************************************/
void RTC_OutputConfig(uint32_t RTC_Output, uint32_t RTC_OutputPolarity);

/* Digital Calibration configuration functions ********************************/
void RTC_CalibOutputCmd(FunctionalState NewState);
void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput);
ErrorStatus RTC_SmoothCalibConfig(uint32_t RTC_SmoothCalibPeriod, 
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue);

/* TimeStamp configuration functions ******************************************/
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState);
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct, RTC_DateTypeDef* RTC_StampDateStruct);
uint32_t RTC_GetTimeStampSubSecond(void);

/* Tampers configuration functions ********************************************/
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger);
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState);
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter);
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq);
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration);
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState);
void RTC_TamperPullUpCmd(FunctionalState NewState);

/* Backup Data Registers configuration functions ******************************/
void RTC_WriteBackupRegister(uint32_t RTC_BKP_DR, uint32_t Data);
uint32_t RTC_ReadBackupRegister(uint32_t RTC_BKP_DR);

/* Output Type Config configuration functions *********************************/
void RTC_OutputTypeConfig(uint32_t RTC_OutputType);
 
/* RTC_Shift_control_synchonisation_functions *********************************/
ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS);

/* Interrupts and flags management functions **********************************/
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState);
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG);
void RTC_ClearFlag(uint32_t RTC_FLAG);
ITStatus RTC_GetITStatus(uint32_t RTC_IT);
void RTC_ClearITPendingBit(uint32_t RTC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_RTC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_spi.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the SPI 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_SPI_H
#define __STM32F0XX_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  SPI Init structure definition  
  */

typedef struct
{
  uint16_t SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

  uint16_t SPI_Mode;                /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of @ref SPI_mode */
  
  uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */
 
  uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint16_t SPI_CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */
}SPI_InitTypeDef;


/** 
  * @brief  I2S Init structure definition
  * @note   These parameters are not available for STM32F030 devices.    
  */

typedef struct
{
  uint16_t I2S_Mode;         /*!< Specifies the I2S operating mode.
                                  This parameter can be a value of @ref SPI_I2S_Mode */

  uint16_t I2S_Standard;     /*!< Specifies the standard used for the I2S communication.
                                  This parameter can be a value of @ref SPI_I2S_Standard */

  uint16_t I2S_DataFormat;   /*!< Specifies the data format for the I2S communication.
                                  This parameter can be a value of @ref SPI_I2S_Data_Format */

  uint16_t I2S_MCLKOutput;   /*!< Specifies whether the I2S MCLK output is enabled or not.
                                  This parameter can be a value of @ref SPI_I2S_MCLK_Output */

  uint32_t I2S_AudioFreq;    /*!< Specifies the frequency selected for the I2S communication.
                                  This parameter can be a value of @ref SPI_I2S_Audio_Frequency */

  uint16_t I2S_CPOL;         /*!< Specifies the idle state of the I2S clock.
                                  This parameter can be a value of @ref SPI_I2S_Clock_Polarity */
}I2S_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2))
                                   
#define IS_SPI_1_PERIPH(PERIPH) (((PERIPH) == SPI1))

/** @defgroup SPI_data_direction 
  * @{
  */
  
#define SPI_Direction_2Lines_FullDuplex ((uint16_t)0x0000)
#define SPI_Direction_2Lines_RxOnly     ((uint16_t)0x0400)
#define SPI_Direction_1Line_Rx          ((uint16_t)0x8000)
#define SPI_Direction_1Line_Tx          ((uint16_t)0xC000)
#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                     ((MODE) == SPI_Direction_2Lines_RxOnly) || \
                                     ((MODE) == SPI_Direction_1Line_Rx) || \
                                     ((MODE) == SPI_Direction_1Line_Tx))
/**
  * @}
  */

/** @defgroup SPI_mode 
  * @{
  */

#define SPI_Mode_Master                 ((uint16_t)0x0104)
#define SPI_Mode_Slave                  ((uint16_t)0x0000)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))
/**
  * @}
  */

/** @defgroup SPI_data_size
  * @{
  */

#define SPI_DataSize_4b                 ((uint16_t)0x0300)
#define SPI_DataSize_5b                 ((uint16_t)0x0400)
#define SPI_DataSize_6b                 ((uint16_t)0x0500)
#define SPI_DataSize_7b                 ((uint16_t)0x0600)
#define SPI_DataSize_8b                 ((uint16_t)0x0700)
#define SPI_DataSize_9b                 ((uint16_t)0x0800)
#define SPI_DataSize_10b                ((uint16_t)0x0900)
#define SPI_DataSize_11b                ((uint16_t)0x0A00)
#define SPI_DataSize_12b                ((uint16_t)0x0B00)
#define SPI_DataSize_13b                ((uint16_t)0x0C00)
#define SPI_DataSize_14b                ((uint16_t)0x0D00)
#define SPI_DataSize_15b                ((uint16_t)0x0E00)
#define SPI_DataSize_16b                ((uint16_t)0x0F00)
#define IS_SPI_DATA_SIZE(SIZE) (((SIZE) == SPI_DataSize_4b) || \
                                 ((SIZE) == SPI_DataSize_5b) || \
                                 ((SIZE) == SPI_DataSize_6b) || \
                                 ((SIZE) == SPI_DataSize_7b) || \
                                 ((SIZE) == SPI_DataSize_8b) || \
                                 ((SIZE) == SPI_DataSize_9b) || \
                                 ((SIZE) == SPI_DataSize_10b) || \
                                 ((SIZE) == SPI_DataSize_11b) || \
                                 ((SIZE) == SPI_DataSize_12b) || \
                                 ((SIZE) == SPI_DataSize_13b) || \
                                 ((SIZE) == SPI_DataSize_14b) || \
                                 ((SIZE) == SPI_DataSize_15b) || \
                                 ((SIZE) == SPI_DataSize_16b))
/**
  * @}
  */

/** @defgroup SPI_CRC_length
  * @{
  */

#define SPI_CRCLength_8b                ((uint16_t)0x0000)
#define SPI_CRCLength_16b               SPI_CR1_CRCL
#define IS_SPI_CRC_LENGTH(LENGTH) (((LENGTH) == SPI_CRCLength_8b) || \
                                   ((LENGTH) == SPI_CRCLength_16b))
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity 
  * @{
  */

#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   SPI_CR1_CPOL
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase 
  * @{
  */

#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  SPI_CR1_CPHA
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management 
  * @{
  */

#define SPI_NSS_Soft                    SPI_CR1_SSM
#define SPI_NSS_Hard                    ((uint16_t)0x0000)
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))
/**
  * @}
  */

/** @defgroup SPI_BaudRate_Prescaler 
  * @{
  */

#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030)
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_256))
/**
  * @}
  */

/** @defgroup SPI_MSB_LSB_transmission 
  * @{
  */

#define SPI_FirstBit_MSB                ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                SPI_CR1_LSBFIRST
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))
/**
  * @}
  */
  
/** @defgroup SPI_I2S_Mode 
  * @{
  */

#define I2S_Mode_SlaveTx                ((uint16_t)0x0000)
#define I2S_Mode_SlaveRx                ((uint16_t)0x0100)
#define I2S_Mode_MasterTx               ((uint16_t)0x0200)
#define I2S_Mode_MasterRx               ((uint16_t)0x0300)
#define IS_I2S_MODE(MODE) (((MODE) == I2S_Mode_SlaveTx) || \
                           ((MODE) == I2S_Mode_SlaveRx) || \
                           ((MODE) == I2S_Mode_MasterTx)|| \
                           ((MODE) == I2S_Mode_MasterRx))
/**
  * @}
  */

/** @defgroup SPI_I2S_Standard 
  * @{
  */

#define I2S_Standard_Phillips           ((uint16_t)0x0000)
#define I2S_Standard_MSB                ((uint16_t)0x0010)
#define I2S_Standard_LSB                ((uint16_t)0x0020)
#define I2S_Standard_PCMShort           ((uint16_t)0x0030)
#define I2S_Standard_PCMLong            ((uint16_t)0x00B0)
#define IS_I2S_STANDARD(STANDARD) (((STANDARD) == I2S_Standard_Phillips) || \
                                   ((STANDARD) == I2S_Standard_MSB) || \
                                   ((STANDARD) == I2S_Standard_LSB) || \
                                   ((STANDARD) == I2S_Standard_PCMShort) || \
                                   ((STANDARD) == I2S_Standard_PCMLong))
/**
  * @}
  */

/** @defgroup SPI_I2S_Data_Format 
  * @{
  */

#define I2S_DataFormat_16b              ((uint16_t)0x0000)
#define I2S_DataFormat_16bextended      ((uint16_t)0x0001)
#define I2S_DataFormat_24b              ((uint16_t)0x0003)
#define I2S_DataFormat_32b              ((uint16_t)0x0005)
#define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == I2S_DataFormat_16b) || \
                                    ((FORMAT) == I2S_DataFormat_16bextended) || \
                                    ((FORMAT) == I2S_DataFormat_24b) || \
                                    ((FORMAT) == I2S_DataFormat_32b))
/**
  * @}
  */

/** @defgroup SPI_I2S_MCLK_Output 
  * @{
  */

#define I2S_MCLKOutput_Enable           SPI_I2SPR_MCKOE
#define I2S_MCLKOutput_Disable          ((uint16_t)0x0000)
#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOutput_Enable) || \
                                    ((OUTPUT) == I2S_MCLKOutput_Disable))
/**
  * @}
  */

/** @defgroup SPI_I2S_Audio_Frequency 
  * @{
  */

#define I2S_AudioFreq_192k               ((uint32_t)192000)
#define I2S_AudioFreq_96k                ((uint32_t)96000)
#define I2S_AudioFreq_48k                ((uint32_t)48000)
#define I2S_AudioFreq_44k                ((uint32_t)44100)
#define I2S_AudioFreq_32k                ((uint32_t)32000)
#define I2S_AudioFreq_22k                ((uint32_t)22050)
#define I2S_AudioFreq_16k                ((uint32_t)16000)
#define I2S_AudioFreq_11k                ((uint32_t)11025)
#define I2S_AudioFreq_8k                 ((uint32_t)8000)
#define I2S_AudioFreq_Default            ((uint32_t)2)

#define IS_I2S_AUDIO_FREQ(FREQ) ((((FREQ) >= I2S_AudioFreq_8k) && \
                                 ((FREQ) <= I2S_AudioFreq_192k)) || \
                                 ((FREQ) == I2S_AudioFreq_Default))
/**
  * @}
  */

/** @defgroup SPI_I2S_Clock_Polarity 
  * @{
  */

#define I2S_CPOL_Low                    ((uint16_t)0x0000)
#define I2S_CPOL_High                   SPI_I2SCFGR_CKPOL
#define IS_I2S_CPOL(CPOL) (((CPOL) == I2S_CPOL_Low) || \
                           ((CPOL) == I2S_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_FIFO_reception_threshold 
  * @{
  */

#define SPI_RxFIFOThreshold_HF          ((uint16_t)0x0000)
#define SPI_RxFIFOThreshold_QF          SPI_CR2_FRXTH
#define IS_SPI_RX_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == SPI_RxFIFOThreshold_HF) || \
                                             ((THRESHOLD) == SPI_RxFIFOThreshold_QF))
/**
  * @}
  */

/** @defgroup SPI_I2S_DMA_transfer_requests 
  * @{
  */

#define SPI_I2S_DMAReq_Tx               SPI_CR2_TXDMAEN
#define SPI_I2S_DMAReq_Rx               SPI_CR2_RXDMAEN
#define IS_SPI_I2S_DMA_REQ(REQ) ((((REQ) & (uint16_t)0xFFFC) == 0x00) && ((REQ) != 0x00))
/**
  * @}
  */

/** @defgroup SPI_last_DMA_transfers
  * @{
  */

#define SPI_LastDMATransfer_TxEvenRxEven   ((uint16_t)0x0000)
#define SPI_LastDMATransfer_TxOddRxEven    ((uint16_t)0x4000)
#define SPI_LastDMATransfer_TxEvenRxOdd    ((uint16_t)0x2000)
#define SPI_LastDMATransfer_TxOddRxOdd     ((uint16_t)0x6000)
#define IS_SPI_LAST_DMA_TRANSFER(TRANSFER) (((TRANSFER) == SPI_LastDMATransfer_TxEvenRxEven) || \
                                            ((TRANSFER) == SPI_LastDMATransfer_TxOddRxEven) || \
                                            ((TRANSFER) == SPI_LastDMATransfer_TxEvenRxOdd) || \
                                            ((TRANSFER) == SPI_LastDMATransfer_TxOddRxOdd))
/**
  * @}
  */
/** @defgroup SPI_NSS_internal_software_management 
  * @{
  */

#define SPI_NSSInternalSoft_Set         SPI_CR1_SSI
#define SPI_NSSInternalSoft_Reset       ((uint16_t)0xFEFF)
#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))
/**
  * @}
  */

/** @defgroup SPI_CRC_Transmit_Receive 
  * @{
  */

#define SPI_CRC_Tx                      ((uint8_t)0x00)
#define SPI_CRC_Rx                      ((uint8_t)0x01)
#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))
/**
  * @}
  */

/** @defgroup SPI_direction_transmit_receive 
  * @{
  */

#define SPI_Direction_Rx                ((uint16_t)0xBFFF)
#define SPI_Direction_Tx                ((uint16_t)0x4000)
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
                                     ((DIRECTION) == SPI_Direction_Tx))
/**
  * @}
  */

/** @defgroup SPI_I2S_interrupts_definition 
  * @{
  */

#define SPI_I2S_IT_TXE                  ((uint8_t)0x71)
#define SPI_I2S_IT_RXNE                 ((uint8_t)0x60)
#define SPI_I2S_IT_ERR                  ((uint8_t)0x50)

#define IS_SPI_I2S_CONFIG_IT(IT) (((IT) == SPI_I2S_IT_TXE) || \
                                  ((IT) == SPI_I2S_IT_RXNE) || \
                                  ((IT) == SPI_I2S_IT_ERR))

#define I2S_IT_UDR                      ((uint8_t)0x53)
#define SPI_IT_MODF                     ((uint8_t)0x55)
#define SPI_I2S_IT_OVR                  ((uint8_t)0x56)
#define SPI_I2S_IT_FRE                  ((uint8_t)0x58)

#define IS_SPI_I2S_GET_IT(IT) (((IT) == SPI_I2S_IT_RXNE) || ((IT) == SPI_I2S_IT_TXE) || \
                               ((IT) == SPI_I2S_IT_OVR) || ((IT) == SPI_IT_MODF) || \
                               ((IT) == SPI_I2S_IT_FRE)|| ((IT) == I2S_IT_UDR))
/**
  * @}
  */


/** @defgroup SPI_transmission_fifo_status_level 
  * @{
  */ 

#define SPI_TransmissionFIFOStatus_Empty           ((uint16_t)0x0000)
#define SPI_TransmissionFIFOStatus_1QuarterFull    ((uint16_t)0x0800) 
#define SPI_TransmissionFIFOStatus_HalfFull        ((uint16_t)0x1000) 
#define SPI_TransmissionFIFOStatus_Full            ((uint16_t)0x1800)

/**
  * @}
  */ 

/** @defgroup SPI_reception_fifo_status_level 
  * @{
  */ 
#define SPI_ReceptionFIFOStatus_Empty           ((uint16_t)0x0000)
#define SPI_ReceptionFIFOStatus_1QuarterFull    ((uint16_t)0x0200) 
#define SPI_ReceptionFIFOStatus_HalfFull        ((uint16_t)0x0400) 
#define SPI_ReceptionFIFOStatus_Full            ((uint16_t)0x0600)

/**
  * @}
  */ 


/** @defgroup SPI_I2S_flags_definition 
  * @{
  */

#define SPI_I2S_FLAG_RXNE               SPI_SR_RXNE
#define SPI_I2S_FLAG_TXE                SPI_SR_TXE
#define I2S_FLAG_CHSIDE                 SPI_SR_CHSIDE
#define I2S_FLAG_UDR                    SPI_SR_UDR
#define SPI_FLAG_CRCERR                 SPI_SR_CRCERR
#define SPI_FLAG_MODF                   SPI_SR_MODF
#define SPI_I2S_FLAG_OVR                SPI_SR_OVR
#define SPI_I2S_FLAG_BSY                SPI_SR_BSY
#define SPI_I2S_FLAG_FRE                SPI_SR_FRE



#define IS_SPI_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
#define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE)|| \
                                   ((FLAG) == SPI_I2S_FLAG_FRE)|| ((FLAG) == I2S_FLAG_CHSIDE)|| \
                                   ((FLAG) == I2S_FLAG_UDR))
/**
  * @}
  */

/** @defgroup SPI_CRC_polynomial 
  * @{
  */

#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct); /*!< Not applicable for STM32F030 devices */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct); /*!< Not applicable for STM32F030 devices */
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_NSSPulseModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState); /*!< Not applicable for STM32F030 devices */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_RxFIFOThresholdConfig(SPI_TypeDef* SPIx, uint16_t SPI_RxFIFOThreshold);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);

/* Data transfers functions ***************************************************/
void SPI_SendData8(SPI_TypeDef* SPIx, uint8_t Data);
void SPI_I2S_SendData16(SPI_TypeDef* SPIx, uint16_t Data);
uint8_t SPI_ReceiveData8(SPI_TypeDef* SPIx);
uint16_t SPI_I2S_ReceiveData16(SPI_TypeDef* SPIx);

/* Hardware CRC Calculation functions *****************************************/
void SPI_CRCLengthConfig(SPI_TypeDef* SPIx, uint16_t SPI_CRCLength);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);

/* DMA transfers management functions *****************************************/
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_LastDMATransferCmd(SPI_TypeDef* SPIx, uint16_t SPI_LastDMATransfer);

/* Interrupts and flags management functions **********************************/
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
uint16_t SPI_GetTransmissionFIFOStatus(SPI_TypeDef* SPIx);
uint16_t SPI_GetReceptionFIFOStatus(SPI_TypeDef* SPIx);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_SPI_H */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_syscfg.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the SYSCFG firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/*!< Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_SYSCFG_H
#define __STM32F0XX_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSCFG
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup SYSCFG_Exported_Constants
  * @{
  */ 
  
/** @defgroup SYSCFG_EXTI_Port_Sources 
  * @{
  */ 
#define EXTI_PortSourceGPIOA       ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB       ((uint8_t)0x01)
#define EXTI_PortSourceGPIOC       ((uint8_t)0x02)
#define EXTI_PortSourceGPIOD       ((uint8_t)0x03) /*!< not available for STM32F031 devices */
#define EXTI_PortSourceGPIOE       ((uint8_t)0x04) /*!< only available for STM32F072 devices */
#define EXTI_PortSourceGPIOF       ((uint8_t)0x05)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOF)) 
/**
  * @}
  */

/** @defgroup SYSCFG_EXTI_Pin_sources 
  * @{
  */ 
#define EXTI_PinSource0            ((uint8_t)0x00)
#define EXTI_PinSource1            ((uint8_t)0x01)
#define EXTI_PinSource2            ((uint8_t)0x02)
#define EXTI_PinSource3            ((uint8_t)0x03)
#define EXTI_PinSource4            ((uint8_t)0x04)
#define EXTI_PinSource5            ((uint8_t)0x05)
#define EXTI_PinSource6            ((uint8_t)0x06)
#define EXTI_PinSource7            ((uint8_t)0x07)
#define EXTI_PinSource8            ((uint8_t)0x08)
#define EXTI_PinSource9            ((uint8_t)0x09)
#define EXTI_PinSource10           ((uint8_t)0x0A)
#define EXTI_PinSource11           ((uint8_t)0x0B)
#define EXTI_PinSource12           ((uint8_t)0x0C)
#define EXTI_PinSource13           ((uint8_t)0x0D)
#define EXTI_PinSource14           ((uint8_t)0x0E)
#define EXTI_PinSource15           ((uint8_t)0x0F)

#define IS_EXTI_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == EXTI_PinSource0) || \
                                       ((PINSOURCE) == EXTI_PinSource1) || \
                                       ((PINSOURCE) == EXTI_PinSource2) || \
                                       ((PINSOURCE) == EXTI_PinSource3) || \
                                       ((PINSOURCE) == EXTI_PinSource4) || \
                                       ((PINSOURCE) == EXTI_PinSource5) || \
                                       ((PINSOURCE) == EXTI_PinSource6) || \
                                       ((PINSOURCE) == EXTI_PinSource7) || \
                                       ((PINSOURCE) == EXTI_PinSource8) || \
                                       ((PINSOURCE) == EXTI_PinSource9) || \
                                       ((PINSOURCE) == EXTI_PinSource10) || \
                                       ((PINSOURCE) == EXTI_PinSource11) || \
                                       ((PINSOURCE) == EXTI_PinSource12) || \
                                       ((PINSOURCE) == EXTI_PinSource13) || \
                                       ((PINSOURCE) == EXTI_PinSource14) || \
                                       ((PINSOURCE) == EXTI_PinSource15))
/**
  * @}
  */

/** @defgroup SYSCFG_Memory_Remap_Config 
  * @{
  */ 
#define SYSCFG_MemoryRemap_Flash                ((uint8_t)0x00)
#define SYSCFG_MemoryRemap_SystemMemory         ((uint8_t)0x01)
#define SYSCFG_MemoryRemap_SRAM                 ((uint8_t)0x03)


#define IS_SYSCFG_MEMORY_REMAP(REMAP) (((REMAP) == SYSCFG_MemoryRemap_Flash) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SystemMemory) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SRAM))

/**
  * @}
  */

/** @defgroup SYSCFG_DMA_Remap_Config 
  * @{
  */ 
#define SYSCFG_DMARemap_TIM3        SYSCFG_CFGR1_TIM3_DMA_RMP      /* Remap TIM3 DMA requests from channel4 to channel6, 
                                                                      available only for STM32F072 devices */
#define SYSCFG_DMARemap_TIM2        SYSCFG_CFGR1_TIM2_DMA_RMP      /* Remap TIM2 DMA requests from channel3/4 to channel7, 
                                                                      available only for STM32F072 devices */ 
#define SYSCFG_DMARemap_TIM1        SYSCFG_CFGR1_TIM1_DMA_RMP      /* Remap TIM1 DMA requests from channel2/3/4 to channel6, 
                                                                      available only for STM32F072 devices */
#define SYSCFG_DMARemap_I2C1        SYSCFG_CFGR1_I2C1_DMA_RMP      /* Remap I2C1 DMA requests from channel3/2 to channel7/6, 
                                                                      available only for STM32F072 devices */
#define SYSCFG_DMARemap_USART3      SYSCFG_CFGR1_USART3_DMA_RMP    /* Remap USART3 DMA requests from channel6/7 to channel3/2, 
                                                                      available only for STM32F072 devices */
#define SYSCFG_DMARemap_USART2      SYSCFG_CFGR1_USART2_DMA_RMP    /* Remap USART2 DMA requests from channel4/5 to channel6/7, 
                                                                      available only for STM32F072 devices */
#define SYSCFG_DMARemap_SPI2        SYSCFG_CFGR1_SPI2_DMA_RMP      /* Remap SPI2 DMA requests from channel4/5 to channel6/7, 
                                                                      available only for STM32F072 devices */
#define SYSCFG_DMARemap_TIM17_2     SYSCFG_CFGR1_TIM17_DMA_RMP2    /* Remap TIM17 DMA requests from channel1/2 to channel7, 
                                                                      available only for STM32F072 devices */
#define SYSCFG_DMARemap_TIM16_2     SYSCFG_CFGR1_TIM16_DMA_RMP2    /* Remap TIM16 DMA requests from channel3/4 to channel6, 
                                                                      available only for STM32F072 devices */
#define SYSCFG_DMARemap_TIM17       SYSCFG_CFGR1_TIM17_DMA_RMP    /* Remap TIM17 DMA requests from channel1 to channel2 */
#define SYSCFG_DMARemap_TIM16       SYSCFG_CFGR1_TIM16_DMA_RMP    /* Remap TIM16 DMA requests from channel3 to channel4 */
#define SYSCFG_DMARemap_USART1Rx    SYSCFG_CFGR1_USART1RX_DMA_RMP /* Remap USART1 Rx DMA requests from channel3 to channel5 */
#define SYSCFG_DMARemap_USART1Tx    SYSCFG_CFGR1_USART1TX_DMA_RMP /* Remap USART1 Tx DMA requests from channel2 to channel4 */
#define SYSCFG_DMARemap_ADC1        SYSCFG_CFGR1_ADC_DMA_RMP      /* Remap ADC1 DMA requests from channel1 to channel2 */
  
#define IS_SYSCFG_DMA_REMAP(REMAP) (((REMAP) == SYSCFG_DMARemap_TIM17) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM16) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1Rx) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1Tx) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM3_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM2_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM1_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_I2C1_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_USART3_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_USART2_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_SPI2_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM17_DMA_RMP2) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM16_DMA_RMP2) || \
                                    ((REMAP) == SYSCFG_DMARemap_ADC1))

/**
  * @}
  */

/** @defgroup SYSCFG_I2C_FastModePlus_Config 
  * @{
  */ 
#define SYSCFG_I2CFastModePlus_PB6       SYSCFG_CFGR1_I2C_FMP_PB6 /* Enable Fast Mode Plus on PB6 */
#define SYSCFG_I2CFastModePlus_PB7       SYSCFG_CFGR1_I2C_FMP_PB7 /* Enable Fast Mode Plus on PB7 */
#define SYSCFG_I2CFastModePlus_PB8       SYSCFG_CFGR1_I2C_FMP_PB8 /* Enable Fast Mode Plus on PB8 */
#define SYSCFG_I2CFastModePlus_PB9       SYSCFG_CFGR1_I2C_FMP_PB9 /* Enable Fast Mode Plus on PB9 */
#define SYSCFG_I2CFastModePlus_I2C1      SYSCFG_CFGR1_I2C_FMP_I2C1 /* Enable Fast Mode Plus on PB10, PB11, PF6 and PF7(only for STM32F0031 and STM32F030 devices) */
#define SYSCFG_I2CFastModePlus_I2C2      SYSCFG_CFGR1_I2C_FMP_I2C2 /* Enable Fast Mode Plus on I2C2 pins, available only for STM32F072 devices */
#define SYSCFG_I2CFastModePlus_PA9       SYSCFG_CFGR1_I2C_FMP_PA9 /* Enable Fast Mode Plus on PA9 (only for STM32F031 and STM32F030 devices) */
#define SYSCFG_I2CFastModePlus_PA10      SYSCFG_CFGR1_I2C_FMP_PA10/* Enable Fast Mode Plus on PA10(only for STM32F031 and STM32F030 devices) */

#define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C2) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA10))


/**
  * @}
  */

/** @defgroup SYSCFG_Lock_Config 
  * @{
  */ 
#define SYSCFG_Break_PVD                     SYSCFG_CFGR2_PVD_LOCK       /*!< Connects the PVD event to the Break Input of TIM1, not available for STM32F030 devices */
#define SYSCFG_Break_SRAMParity              SYSCFG_CFGR2_SRAM_PARITY_LOCK  /*!< Connects the SRAM_PARITY error signal to the Break Input of TIM1 */
#define SYSCFG_Break_Lockup                  SYSCFG_CFGR2_LOCKUP_LOCK       /*!< Connects Lockup output of CortexM0 to the break input of TIM1 */

#define IS_SYSCFG_LOCK_CONFIG(CONFIG) (((CONFIG) == SYSCFG_Break_PVD)        || \
                                       ((CONFIG) == SYSCFG_Break_SRAMParity) || \
                                       ((CONFIG) == SYSCFG_Break_Lockup))

/**
  * @}
  */

/** @defgroup SYSCFG_flags_definition 
  * @{
  */

#define SYSCFG_FLAG_PE               SYSCFG_CFGR2_SRAM_PE

#define IS_SYSCFG_FLAG(FLAG) (((FLAG) == SYSCFG_FLAG_PE))

/**
  * @}
  */

/** @defgroup SYSCFG_ISR_WRAPPER
  * @{
  */
#define SYSCFG_ITLINE0                           ((uint32_t) 0x00000000)
#define SYSCFG_ITLINE1                           ((uint32_t) 0x00000001)
#define SYSCFG_ITLINE2                           ((uint32_t) 0x00000002)
#define SYSCFG_ITLINE3                           ((uint32_t) 0x00000003)
#define SYSCFG_ITLINE4                           ((uint32_t) 0x00000004)
#define SYSCFG_ITLINE5                           ((uint32_t) 0x00000005)
#define SYSCFG_ITLINE6                           ((uint32_t) 0x00000006)
#define SYSCFG_ITLINE7                           ((uint32_t) 0x00000007)
#define SYSCFG_ITLINE8                           ((uint32_t) 0x00000008)
#define SYSCFG_ITLINE9                           ((uint32_t) 0x00000009)
#define SYSCFG_ITLINE10                          ((uint32_t) 0x0000000A)
#define SYSCFG_ITLINE11                          ((uint32_t) 0x0000000B)
#define SYSCFG_ITLINE12                          ((uint32_t) 0x0000000C)
#define SYSCFG_ITLINE13                          ((uint32_t) 0x0000000D)
#define SYSCFG_ITLINE14                          ((uint32_t) 0x0000000E)
#define SYSCFG_ITLINE15                          ((uint32_t) 0x0000000F)
#define SYSCFG_ITLINE16                          ((uint32_t) 0x00000010)
#define SYSCFG_ITLINE17                          ((uint32_t) 0x00000011)
#define SYSCFG_ITLINE18                          ((uint32_t) 0x00000012)
#define SYSCFG_ITLINE19                          ((uint32_t) 0x00000013)
#define SYSCFG_ITLINE20                          ((uint32_t) 0x00000014)
#define SYSCFG_ITLINE21                          ((uint32_t) 0x00000015)
#define SYSCFG_ITLINE22                          ((uint32_t) 0x00000016)
#define SYSCFG_ITLINE23                          ((uint32_t) 0x00000017)
#define SYSCFG_ITLINE24                          ((uint32_t) 0x00000018)
#define SYSCFG_ITLINE25                          ((uint32_t) 0x00000019)
#define SYSCFG_ITLINE26                          ((uint32_t) 0x0000001A)
#define SYSCFG_ITLINE27                          ((uint32_t) 0x0000001B)
#define SYSCFG_ITLINE28                          ((uint32_t) 0x0000001C)
#define SYSCFG_ITLINE29                          ((uint32_t) 0x0000001D)
#define SYSCFG_ITLINE30                          ((uint32_t) 0x0000001E)
#define SYSCFG_ITLINE31                          ((uint32_t) 0x0000001F)

#define ITLINE_EWDG           ((uint32_t) ((SYSCFG_ITLINE0 << 0x18) | SYSCFG_ITLINE0_SR_EWDG)) /* EWDG Interrupt */
#define ITLINE_PVDOUT         ((uint32_t) ((SYSCFG_ITLINE1 << 0x18) | SYSCFG_ITLINE1_SR_PVDOUT)) /* Power voltage detection Interrupt */
#define ITLINE_VDDIO2         ((uint32_t) ((SYSCFG_ITLINE1 << 0x18) | SYSCFG_ITLINE1_SR_VDDIO2)) /* VDDIO2 Interrupt */
#define ITLINE_RTC_WAKEUP     ((uint32_t) ((SYSCFG_ITLINE2 << 0x18) | SYSCFG_ITLINE2_SR_RTC_WAKEUP)) /* RTC WAKEUP -> exti[20] Interrupt */
#define ITLINE_RTC_TSTAMP     ((uint32_t) ((SYSCFG_ITLINE2 << 0x18) | SYSCFG_ITLINE2_SR_RTC_TSTAMP)) /* RTC Time Stamp -> exti[19] interrupt */
#define ITLINE_RTC_ALRA       ((uint32_t) ((SYSCFG_ITLINE2 << 0x18) | SYSCFG_ITLINE2_SR_RTC_ALRA)) /* RTC Alarm -> exti[17] interrupt */
#define ITLINE_FLASH_ITF      ((uint32_t) ((SYSCFG_ITLINE3 << 0x18) | SYSCFG_ITLINE3_SR_FLASH_ITF)) /* Flash ITF Interrupt */
#define ITLINE_CRS            ((uint32_t) ((SYSCFG_ITLINE4 << 0x18) | SYSCFG_ITLINE4_SR_CRS)) /* CRS Interrupt */
#define ITLINE_CLK_CTRL       ((uint32_t) ((SYSCFG_ITLINE4 << 0x18) | SYSCFG_ITLINE4_SR_CLK_CTRL)) /* CLK Control Interrupt */
#define ITLINE_EXTI0          ((uint32_t) ((SYSCFG_ITLINE5 << 0x18) | SYSCFG_ITLINE5_SR_EXTI0)) /* External Interrupt 0 */
#define ITLINE_EXTI1          ((uint32_t) ((SYSCFG_ITLINE5 << 0x18) | SYSCFG_ITLINE5_SR_EXTI1)) /* External Interrupt 1 */
#define ITLINE_EXTI2          ((uint32_t) ((SYSCFG_ITLINE6 << 0x18) | SYSCFG_ITLINE6_SR_EXTI2)) /* External Interrupt 2 */
#define ITLINE_EXTI3          ((uint32_t) ((SYSCFG_ITLINE6 << 0x18) | SYSCFG_ITLINE6_SR_EXTI3)) /* External Interrupt 3 */
#define ITLINE_EXTI4          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI4)) /* EXTI4 Interrupt */
#define ITLINE_EXTI5          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI5)) /* EXTI5 Interrupt */
#define ITLINE_EXTI6          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI6)) /* EXTI6 Interrupt */
#define ITLINE_EXTI7          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI7)) /* EXTI7 Interrupt */
#define ITLINE_EXTI8          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI8)) /* EXTI8 Interrupt */
#define ITLINE_EXTI9          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI9)) /* EXTI9 Interrupt */
#define ITLINE_EXTI10         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI10)) /* EXTI10 Interrupt */
#define ITLINE_EXTI11         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI11)) /* EXTI11 Interrupt */
#define ITLINE_EXTI12         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI12)) /* EXTI12 Interrupt */
#define ITLINE_EXTI13         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI13)) /* EXTI13 Interrupt */
#define ITLINE_EXTI14         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI14)) /* EXTI14 Interrupt */
#define ITLINE_EXTI15         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI15)) /* EXTI15 Interrupt */
#define ITLINE_TSC_EOA        ((uint32_t) ((SYSCFG_ITLINE8 << 0x18) | SYSCFG_ITLINE8_SR_TSC_EOA)) /* Touch control EOA Interrupt */
#define ITLINE_TSC_MCE        ((uint32_t) ((SYSCFG_ITLINE8 << 0x18) | SYSCFG_ITLINE8_SR_TSC_MCE)) /* Touch control MCE Interrupt */
#define ITLINE_DMA1_CH1       ((uint32_t) ((SYSCFG_ITLINE9 << 0x18) | SYSCFG_ITLINE9_SR_DMA1_CH1)) /* DMA1 Channel 1 Interrupt */
#define ITLINE_DMA1_CH2       ((uint32_t) ((SYSCFG_ITLINE10 << 0x18) | SYSCFG_ITLINE10_SR_DMA1_CH2)) /* DMA1 Channel 2 Interrupt */
#define ITLINE_DMA1_CH3       ((uint32_t) ((SYSCFG_ITLINE10 << 0x18) | SYSCFG_ITLINE10_SR_DMA1_CH3)) /* DMA1 Channel 3 Interrupt */
#define ITLINE_DMA2_CH1       ((uint32_t) ((SYSCFG_ITLINE10 << 0x18) | SYSCFG_ITLINE10_SR_DMA2_CH1)) /* DMA2 Channel 1 Interrupt */
#define ITLINE_DMA2_CH2       ((uint32_t) ((SYSCFG_ITLINE10 << 0x18) | SYSCFG_ITLINE10_SR_DMA2_CH2)) /* DMA2 Channel 2 Interrupt */
#define ITLINE_DMA1_CH4       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA1_CH4)) /* DMA1 Channel 4 Interrupt */
#define ITLINE_DMA1_CH5       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA1_CH5)) /* DMA1 Channel 5 Interrupt */
#define ITLINE_DMA1_CH6       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA1_CH6)) /* DMA1 Channel 6 Interrupt */
#define ITLINE_DMA1_CH7       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA1_CH7)) /* DMA1 Channel 7 Interrupt */
#define ITLINE_DMA2_CH3       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA2_CH3)) /* DMA2 Channel 3 Interrupt */
#define ITLINE_DMA2_CH4       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA2_CH4)) /* DMA2 Channel 4 Interrupt */
#define ITLINE_DMA2_CH5       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA2_CH5)) /* DMA2 Channel 5 Interrupt */
#define ITLINE_ADC            ((uint32_t) ((SYSCFG_ITLINE12 << 0x18) | SYSCFG_ITLINE12_SR_ADC)) /* ADC Interrupt */
#define ITLINE_COMP1          ((uint32_t) ((SYSCFG_ITLINE12 << 0x18) | SYSCFG_ITLINE12_SR_COMP1)) /* COMP1 Interrupt -> exti[21] */
#define ITLINE_COMP2          ((uint32_t) ((SYSCFG_ITLINE12 << 0x18) | SYSCFG_ITLINE12_SR_COMP2)) /* COMP2 Interrupt -> exti[21] */
#define ITLINE_TIM1_BRK       ((uint32_t) ((SYSCFG_ITLINE13 << 0x18) | SYSCFG_ITLINE13_SR_TIM1_BRK)) /* TIM1 BRK Interrupt */
#define ITLINE_TIM1_UPD       ((uint32_t) ((SYSCFG_ITLINE13 << 0x18) | SYSCFG_ITLINE13_SR_TIM1_UPD)) /* TIM1 UPD Interrupt */
#define ITLINE_TIM1_TRG       ((uint32_t) ((SYSCFG_ITLINE13 << 0x18) | SYSCFG_ITLINE13_SR_TIM1_TRG)) /* TIM1 TRG Interrupt */
#define ITLINE_TIM1_CCU       ((uint32_t) ((SYSCFG_ITLINE13 << 0x18) | SYSCFG_ITLINE13_SR_TIM1_CCU)) /* TIM1 CCU Interrupt */
#define ITLINE_TIM1_CC        ((uint32_t) ((SYSCFG_ITLINE14 << 0x18) | SYSCFG_ITLINE14_SR_TIM1_CC)) /* TIM1 CC Interrupt */
#define ITLINE_TIM2           ((uint32_t) ((SYSCFG_ITLINE15 << 0x18) | SYSCFG_ITLINE15_SR_TIM2_GLB)) /* TIM2 Interrupt */
#define ITLINE_TIM3           ((uint32_t) ((SYSCFG_ITLINE16 << 0x18) | SYSCFG_ITLINE16_SR_TIM3_GLB)) /* TIM3 Interrupt */
#define ITLINE_DAC            ((uint32_t) ((SYSCFG_ITLINE17 << 0x18) | SYSCFG_ITLINE17_SR_DAC)) /* DAC Interrupt */
#define ITLINE_TIM6           ((uint32_t) ((SYSCFG_ITLINE17 << 0x18) | SYSCFG_ITLINE17_SR_TIM6_GLB)) /* TIM6 Interrupt */
#define ITLINE_TIM7           ((uint32_t) ((SYSCFG_ITLINE18 << 0x18) | SYSCFG_ITLINE18_SR_TIM7_GLB)) /* TIM7 Interrupt */
#define ITLINE_TIM14          ((uint32_t) ((SYSCFG_ITLINE19 << 0x18) | SYSCFG_ITLINE19_SR_TIM14_GLB)) /* TIM14 Interrupt */
#define ITLINE_TIM15          ((uint32_t) ((SYSCFG_ITLINE20 << 0x18) | SYSCFG_ITLINE20_SR_TIM15_GLB)) /* TIM15 Interrupt */
#define ITLINE_TIM16          ((uint32_t) ((SYSCFG_ITLINE21 << 0x18) | SYSCFG_ITLINE21_SR_TIM16_GLB)) /* TIM16 Interrupt */
#define ITLINE_TIM17          ((uint32_t) ((SYSCFG_ITLINE22 << 0x18) | SYSCFG_ITLINE22_SR_TIM17_GLB)) /* TIM17 Interrupt */
#define ITLINE_I2C1           ((uint32_t) ((SYSCFG_ITLINE23 << 0x18) | SYSCFG_ITLINE23_SR_I2C1_GLB)) /* I2C1 Interrupt -> exti[23] */
#define ITLINE_I2C2           ((uint32_t) ((SYSCFG_ITLINE24 << 0x18) | SYSCFG_ITLINE24_SR_I2C2_GLB)) /* I2C2 Interrupt */
#define ITLINE_SPI1           ((uint32_t) ((SYSCFG_ITLINE25 << 0x18) | SYSCFG_ITLINE25_SR_SPI1)) /* I2C1 Interrupt -> exti[23] */
#define ITLINE_SPI2           ((uint32_t) ((SYSCFG_ITLINE26 << 0x18) | SYSCFG_ITLINE26_SR_SPI2)) /* SPI1 Interrupt */
#define ITLINE_USART1         ((uint32_t) ((SYSCFG_ITLINE27 << 0x18) | SYSCFG_ITLINE27_SR_USART1_GLB)) /*!< USART1 GLB Interrupt -> exti[25] */
#define ITLINE_USART2         ((uint32_t) ((SYSCFG_ITLINE28 << 0x18) | SYSCFG_ITLINE28_SR_USART2_GLB)) /*!< USART2 GLB Interrupt -> exti[26] */
#define ITLINE_USART3         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART3_GLB)) /* USART3 Interrupt */
#define ITLINE_USART4         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART4_GLB)) /* USART4 Interrupt */
#define ITLINE_USART5         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART5_GLB)) /* USART5 Interrupt */
#define ITLINE_USART6         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART6_GLB)) /* USART6 Interrupt */
#define ITLINE_USART7         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART7_GLB)) /* USART7 Interrupt */
#define ITLINE_USART8         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART8_GLB)) /* USART8 Interrupt */
#define ITLINE_CAN            ((uint32_t) ((SYSCFG_ITLINE30 << 0x18) | SYSCFG_ITLINE30_SR_CAN)) /* CAN Interrupt */
#define ITLINE_CEC            ((uint32_t) ((SYSCFG_ITLINE30 << 0x18) | SYSCFG_ITLINE30_SR_CEC)) /* CEC Interrupt -> exti[27] */

#define IS_SYSCFG_ITLINE(LINE) (((LINE) == ITLINE_EWDG)       || \
                                ((LINE) == ITLINE_PVDOUT)     || \
                                ((LINE) == ITLINE_VDDIO2)     || \
                                ((LINE) == ITLINE_RTC_WAKEUP) || \
                                ((LINE) == ITLINE_RTC_TSTAMP) || \
                                ((LINE) == ITLINE_RTC_ALRA)   || \
                                ((LINE) == ITLINE_FLASH_ITF)  || \
                                ((LINE) == ITLINE_CRS)        || \
                                ((LINE) == ITLINE_CLK_CTRL)   || \
                                ((LINE) == ITLINE_EXTI0)      || \
                                ((LINE) == ITLINE_EXTI1)      || \
                                ((LINE) == ITLINE_EXTI2)      || \
                                ((LINE) == ITLINE_EXTI3)      || \
                                ((LINE) == ITLINE_EXTI4)      || \
                                ((LINE) == ITLINE_EXTI5)      || \
                                ((LINE) == ITLINE_EXTI6)      || \
                                ((LINE) == ITLINE_EXTI7)      || \
                                ((LINE) == ITLINE_EXTI8)      || \
                                ((LINE) == ITLINE_EXTI9)      || \
                                ((LINE) == ITLINE_EXTI10)     || \
                                ((LINE) == ITLINE_EXTI11)     || \
                                ((LINE) == ITLINE_EXTI12)     || \
                                ((LINE) == ITLINE_EXTI13)     || \
                                ((LINE) == ITLINE_EXTI14)     || \
                                ((LINE) == ITLINE_EXTI15)     || \
                                ((LINE) == ITLINE_TSC_EOA)    || \
                                ((LINE) == ITLINE_TSC_MCE)    || \
                                ((LINE) == ITLINE_DMA1_CH1)   || \
                                ((LINE) == ITLINE_DMA1_CH2)   || \
                                ((LINE) == ITLINE_DMA1_CH3)   || \
                                ((LINE) == ITLINE_DMA1_CH4)   || \
                                ((LINE) == ITLINE_DMA1_CH5)   || \
                                ((LINE) == ITLINE_DMA1_CH6)   || \
                                ((LINE) == ITLINE_DMA1_CH7)   || \
                                ((LINE) == ITLINE_DMA2_CH1)   || \
                                ((LINE) == ITLINE_DMA2_CH2)   || \
                                ((LINE) == ITLINE_DMA2_CH3)   || \
                                ((LINE) == ITLINE_DMA2_CH4)   || \
                                ((LINE) == ITLINE_DMA2_CH5)   || \
                                ((LINE) == ITLINE_ADC)        || \
                                ((LINE) == ITLINE_COMP1)      || \
                                ((LINE) == ITLINE_COMP2)      || \
                                ((LINE) == ITLINE_TIM1_BRK)   || \
                                ((LINE) == ITLINE_TIM1_UPD)   || \
                                ((LINE) == ITLINE_TIM1_TRG)   || \
                                ((LINE) == ITLINE_TIM1_CCU)   || \
                                ((LINE) == ITLINE_TIM1_CC)    || \
                                ((LINE) == ITLINE_TIM2)       || \
                                ((LINE) == ITLINE_TIM3)       || \
                                ((LINE) == ITLINE_DAC)        || \
                                ((LINE) == ITLINE_TIM6)       || \
                                ((LINE) == ITLINE_TIM7)       || \
                                ((LINE) == ITLINE_TIM14)      || \
                                ((LINE) == ITLINE_TIM15)      || \
                                ((LINE) == ITLINE_TIM16)      || \
                                ((LINE) == ITLINE_TIM17)      || \
                                ((LINE) == ITLINE_I2C1)       || \
                                ((LINE) == ITLINE_I2C2)       || \
                                ((LINE) == ITLINE_SPI1)       || \
                                ((LINE) == ITLINE_SPI2)       || \
                                ((LINE) == ITLINE_USART1)     || \
                                ((LINE) == ITLINE_USART2)     || \
                                ((LINE) == ITLINE_USART3)     || \
                                ((LINE) == ITLINE_USART4)     || \
                                ((LINE) == ITLINE_USART5)     || \
                                ((LINE) == ITLINE_USART6)     || \
                                ((LINE) == ITLINE_USART7)     || \
                                ((LINE) == ITLINE_USART8)     || \
                                ((LINE) == ITLINE_CAN)        || \
                                ((LINE) == ITLINE_CEC))

/**
  * @}
  */
/** @defgroup IRDA_ENV_SEL
  * @{
  */
#define SYSCFG_IRDA_ENV_SEL_TIM16     (SYSCFG_CFGR1_IRDA_ENV_SEL_0&SYSCFG_CFGR1_IRDA_ENV_SEL_1)    /* Timer16 is selected as IRDA Modulation envelope source */
#define SYSCFG_IRDA_ENV_SEL_USART1    (SYSCFG_CFGR1_IRDA_ENV_SEL_0)  /* USART1 is selected as IRDA Modulation envelope source.*/
#define SYSCFG_IRDA_ENV_SEL_USART4    (SYSCFG_CFGR1_IRDA_ENV_SEL_1)  /* USART4 is selected as IRDA Modulation envelope source.*/

#define IS_SYSCFG_IRDA_ENV(ENV) (((ENV) == SYSCFG_IRDA_ENV_SEL_TIM16)      || \
                                 ((ENV) == SYSCFG_IRDA_ENV_SEL_USART1)     || \
                                 ((ENV) == SYSCFG_IRDA_ENV_SEL_USART4))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the SYSCFG configuration to the default reset state **/
void SYSCFG_DeInit(void);

/* SYSCFG configuration functions *********************************************/ 
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap);
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState);
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState);
void SYSCFG_IRDAEnvSelection(uint32_t SYSCFG_IRDAEnv);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
uint32_t SYSCFG_GetPendingIT(uint32_t ITSourceLine);
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break);
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag);
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_SYSCFG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_tim.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the TIM 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_TIM_H
#define __STM32F0XX_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  TIM Time Base Init structure definition
  * @note   This sturcture is used with all TIMx.
  */

typedef struct
{
  uint16_t TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TIM_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

  uint32_t TIM_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */ 

  uint16_t TIM_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */

  uint8_t TIM_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF. 
                                       @note This parameter is valid only for TIM1. */
} TIM_TimeBaseInitTypeDef;       

/** 
  * @brief  TIM Output Compare Init structure definition  
  */

typedef struct
{
  uint16_t TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint16_t TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */

  uint16_t TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_state
                                   @note This parameter is valid only for TIM1. */

  uint32_t TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF ( or 0xFFFFFFFF 
                                   for TIM2) */

  uint16_t TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint16_t TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1. */

  uint16_t TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1. */

  uint16_t TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1. */
} TIM_OCInitTypeDef;

/** 
  * @brief  TIM Input Capture Init structure definition  
  */

typedef struct
{

  uint16_t TIM_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

  uint16_t TIM_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint16_t TIM_ICSelection;  /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint16_t TIM_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint16_t TIM_ICFilter;     /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TIM_ICInitTypeDef;

/** 
  * @brief  TIM_BDTR structure definition 
  * @note   This sturcture is used only with TIM1.    
  */

typedef struct
{

  uint16_t TIM_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state */

  uint16_t TIM_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state */

  uint16_t TIM_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref TIM_Lock_level */ 

  uint16_t TIM_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

  uint16_t TIM_Break;            /*!< Specifies whether the TIM Break input is enabled or not. 
                                      This parameter can be a value of @ref TIM_Break_Input_enable_disable */

  uint16_t TIM_BreakPolarity;    /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref TIM_Break_Polarity */

  uint16_t TIM_AutomaticOutput;  /*!< Specifies whether the TIM Automatic Output feature is enabled or not. 
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} TIM_BDTRInitTypeDef;

/** 
  * @brief  TIM Input Capture Init structure definition  
  */

/* Exported constants --------------------------------------------------------*/

  
/** @defgroup TIM_Exported_constants 
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                   ((PERIPH) == TIM2) || \
                                   ((PERIPH) == TIM3) || \
                                   ((PERIPH) == TIM6) || \
                                   ((PERIPH) == TIM7) || \
                                   ((PERIPH) == TIM14)|| \
                                   ((PERIPH) == TIM15)|| \
                                   ((PERIPH) == TIM16)|| \
                                   ((PERIPH) == TIM17))

/* LIST1: TIM 1 */
#define IS_TIM_LIST1_PERIPH(PERIPH)  ((PERIPH) == TIM1)

/* LIST2: TIM 1, 15, 16 and 17 */
#define IS_TIM_LIST2_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM16)|| \
                                     ((PERIPH) == TIM17)) 

/* LIST3: TIM 1, 2 and 3 */
#define IS_TIM_LIST3_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3)) 

/* LIST4: TIM 1, 2, 3, 14, 15, 16 and 17 */
#define IS_TIM_LIST4_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM14) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM16)|| \
                                     ((PERIPH) == TIM17))

/* LIST5: TIM 1, 2, 3, 15, 16 and 17 */
#define IS_TIM_LIST5_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM16)|| \
                                     ((PERIPH) == TIM17))

/* LIST6: TIM 1, 2, 3 and 15 */
#define IS_TIM_LIST6_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM15)) 

/* LIST7: TIM 1, 2, 3, 6, 7 and 14 */
#define IS_TIM_LIST7_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM6) || \
                                      ((PERIPH) == TIM7) || \
                                      ((PERIPH) == TIM14))
                                      
/* LIST8: TIM 1, 2, 3 and 14 */
#define IS_TIM_LIST8_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM14))

/* LIST9: TIM 1, 2, 3, 6, 7 and 15 */
#define IS_TIM_LIST9_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM6) || \
                                      ((PERIPH) == TIM7) || \
                                      ((PERIPH) == TIM15))

/* LIST10: TIM 1, 2, 3, 6, 7, 15, 16 and 17 */
#define IS_TIM_LIST10_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM6) || \
                                     ((PERIPH) == TIM7) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM16)|| \
                                     ((PERIPH) == TIM17))

/* LIST1: TIM 11 */
#define IS_TIM_LIST11_PERIPH(PERIPH)  ((PERIPH) == TIM14)
                                     

/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_and_PWM_modes 
  * @{
  */

#define TIM_OCMode_Timing                  ((uint16_t)0x0000)
#define TIM_OCMode_Active                  ((uint16_t)0x0010)
#define TIM_OCMode_Inactive                ((uint16_t)0x0020)
#define TIM_OCMode_Toggle                  ((uint16_t)0x0030)
#define TIM_OCMode_PWM1                    ((uint16_t)0x0060)
#define TIM_OCMode_PWM2                    ((uint16_t)0x0070)
#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
                              ((MODE) == TIM_OCMode_Active) || \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle)|| \
                              ((MODE) == TIM_OCMode_PWM1) || \
                              ((MODE) == TIM_OCMode_PWM2))
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
                          ((MODE) == TIM_OCMode_Active) || \
                          ((MODE) == TIM_OCMode_Inactive) || \
                          ((MODE) == TIM_OCMode_Toggle)|| \
                          ((MODE) == TIM_OCMode_PWM1) || \
                          ((MODE) == TIM_OCMode_PWM2) ||	\
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode 
  * @{
  */

#define TIM_OPMode_Single                  ((uint16_t)0x0008)
#define TIM_OPMode_Repetitive              ((uint16_t)0x0000)
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))
/**
  * @}
  */ 

/** @defgroup TIM_Channel 
  * @{
  */

#define TIM_Channel_1                      ((uint16_t)0x0000)
#define TIM_Channel_2                      ((uint16_t)0x0004)
#define TIM_Channel_3                      ((uint16_t)0x0008)
#define TIM_Channel_4                      ((uint16_t)0x000C)

#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))
#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))
#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))

/**
  * @}
  */ 

/** @defgroup TIM_Clock_Division_CKD 
  * @{
  */

#define TIM_CKD_DIV1                       ((uint16_t)0x0000)
#define TIM_CKD_DIV2                       ((uint16_t)0x0100)
#define TIM_CKD_DIV4                       ((uint16_t)0x0200)
#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode 
  * @{
  */

#define TIM_CounterMode_Up                 ((uint16_t)0x0000)
#define TIM_CounterMode_Down               ((uint16_t)0x0010)
#define TIM_CounterMode_CenterAligned1     ((uint16_t)0x0020)
#define TIM_CounterMode_CenterAligned2     ((uint16_t)0x0040)
#define TIM_CounterMode_CenterAligned3     ((uint16_t)0x0060)
#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||  \
                                   ((MODE) == TIM_CounterMode_Down) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Polarity 
  * @{
  */

#define TIM_OCPolarity_High                ((uint16_t)0x0000)
#define TIM_OCPolarity_Low                 ((uint16_t)0x0002)
#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity 
  * @{
  */
  
#define TIM_OCNPolarity_High               ((uint16_t)0x0000)
#define TIM_OCNPolarity_Low                ((uint16_t)0x0008)
#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_state
  * @{
  */

#define TIM_OutputState_Disable            ((uint16_t)0x0000)
#define TIM_OutputState_Enable             ((uint16_t)0x0001)
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_state 
  * @{
  */

#define TIM_OutputNState_Disable           ((uint16_t)0x0000)
#define TIM_OutputNState_Enable            ((uint16_t)0x0004)
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_state 
  * @{
  */

#define TIM_CCx_Enable                      ((uint16_t)0x0001)
#define TIM_CCx_Disable                     ((uint16_t)0x0000)
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_N_state 
  * @{
  */

#define TIM_CCxN_Enable                     ((uint16_t)0x0004)
#define TIM_CCxN_Disable                    ((uint16_t)0x0000)
#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
                           ((CCXN) == TIM_CCxN_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Break_Input_enable_disable 
  * @{
  */

#define TIM_Break_Enable                   ((uint16_t)0x1000)
#define TIM_Break_Disable                  ((uint16_t)0x0000)
#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
                                   ((STATE) == TIM_Break_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Break_Polarity 
  * @{
  */

#define TIM_BreakPolarity_Low              ((uint16_t)0x0000)
#define TIM_BreakPolarity_High             ((uint16_t)0x2000)
#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
                                         ((POLARITY) == TIM_BreakPolarity_High))
/**
  * @}
  */ 

/** @defgroup TIM_AOE_Bit_Set_Reset 
  * @{
  */

#define TIM_AutomaticOutput_Enable         ((uint16_t)0x4000)
#define TIM_AutomaticOutput_Disable        ((uint16_t)0x0000)
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Lock_level 
  * @{
  */

#define TIM_LOCKLevel_OFF                  ((uint16_t)0x0000)
#define TIM_LOCKLevel_1                    ((uint16_t)0x0100)
#define TIM_LOCKLevel_2                    ((uint16_t)0x0200)
#define TIM_LOCKLevel_3                    ((uint16_t)0x0300)
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) || \
                                  ((LEVEL) == TIM_LOCKLevel_2) || \
                                  ((LEVEL) == TIM_LOCKLevel_3))
/**
  * @}
  */ 

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state 
  * @{
  */

#define TIM_OSSIState_Enable               ((uint16_t)0x0400)
#define TIM_OSSIState_Disable              ((uint16_t)0x0000)
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))
/**
  * @}
  */

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state 
  * @{
  */

#define TIM_OSSRState_Enable               ((uint16_t)0x0800)
#define TIM_OSSRState_Disable              ((uint16_t)0x0000)
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Idle_State 
  * @{
  */

#define TIM_OCIdleState_Set                ((uint16_t)0x0100)
#define TIM_OCIdleState_Reset              ((uint16_t)0x0000)
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_Idle_State 
  * @{
  */

#define TIM_OCNIdleState_Set               ((uint16_t)0x0200)
#define TIM_OCNIdleState_Reset             ((uint16_t)0x0000)
#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Polarity 
  * @{
  */

#define  TIM_ICPolarity_Rising             ((uint16_t)0x0000)
#define  TIM_ICPolarity_Falling            ((uint16_t)0x0002)
#define  TIM_ICPolarity_BothEdge           ((uint16_t)0x000A)
#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling)|| \
                                      ((POLARITY) == TIM_ICPolarity_BothEdge)) 
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Selection 
  * @{
  */

#define TIM_ICSelection_DirectTI           ((uint16_t)0x0001) /*!< TIM Input 1, 2, 3 or 4 is selected to be 
                                                                   connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSelection_IndirectTI         ((uint16_t)0x0002) /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                   connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_ICSelection_TRC                ((uint16_t)0x0003) /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Prescaler 
  * @{
  */

#define TIM_ICPSC_DIV1                     ((uint16_t)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define TIM_ICPSC_DIV2                     ((uint16_t)0x0004) /*!< Capture performed once every 2 events. */
#define TIM_ICPSC_DIV4                     ((uint16_t)0x0008) /*!< Capture performed once every 4 events. */
#define TIM_ICPSC_DIV8                     ((uint16_t)0x000C) /*!< Capture performed once every 8 events. */
#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))
/**
  * @}
  */ 

/** @defgroup TIM_interrupt_sources 
  * @{
  */

#define TIM_IT_Update                      ((uint16_t)0x0001)
#define TIM_IT_CC1                         ((uint16_t)0x0002)
#define TIM_IT_CC2                         ((uint16_t)0x0004)
#define TIM_IT_CC3                         ((uint16_t)0x0008)
#define TIM_IT_CC4                         ((uint16_t)0x0010)
#define TIM_IT_COM                         ((uint16_t)0x0020)
#define TIM_IT_Trigger                     ((uint16_t)0x0040)
#define TIM_IT_Break                       ((uint16_t)0x0080)
#define IS_TIM_IT(IT) ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) || \
                           ((IT) == TIM_IT_CC1) || \
                           ((IT) == TIM_IT_CC2) || \
                           ((IT) == TIM_IT_CC3) || \
                           ((IT) == TIM_IT_CC4) || \
                           ((IT) == TIM_IT_COM) || \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break))
/**
  * @}
  */ 

/** @defgroup TIM_DMA_Base_address 
  * @{
  */

#define TIM_DMABase_CR1                    ((uint16_t)0x0000)
#define TIM_DMABase_CR2                    ((uint16_t)0x0001)
#define TIM_DMABase_SMCR                   ((uint16_t)0x0002)
#define TIM_DMABase_DIER                   ((uint16_t)0x0003)
#define TIM_DMABase_SR                     ((uint16_t)0x0004)
#define TIM_DMABase_EGR                    ((uint16_t)0x0005)
#define TIM_DMABase_CCMR1                  ((uint16_t)0x0006)
#define TIM_DMABase_CCMR2                  ((uint16_t)0x0007)
#define TIM_DMABase_CCER                   ((uint16_t)0x0008)
#define TIM_DMABase_CNT                    ((uint16_t)0x0009)
#define TIM_DMABase_PSC                    ((uint16_t)0x000A)
#define TIM_DMABase_ARR                    ((uint16_t)0x000B)
#define TIM_DMABase_RCR                    ((uint16_t)0x000C)
#define TIM_DMABase_CCR1                   ((uint16_t)0x000D)
#define TIM_DMABase_CCR2                   ((uint16_t)0x000E)
#define TIM_DMABase_CCR3                   ((uint16_t)0x000F)
#define TIM_DMABase_CCR4                   ((uint16_t)0x0010)
#define TIM_DMABase_BDTR                   ((uint16_t)0x0011)
#define TIM_DMABase_DCR                    ((uint16_t)0x0012)
#define TIM_DMABase_OR                     ((uint16_t)0x0013)
#define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1) || \
                               ((BASE) == TIM_DMABase_CR2) || \
                               ((BASE) == TIM_DMABase_SMCR) || \
                               ((BASE) == TIM_DMABase_DIER) || \
                               ((BASE) == TIM_DMABase_SR) || \
                               ((BASE) == TIM_DMABase_EGR) || \
                               ((BASE) == TIM_DMABase_CCMR1) || \
                               ((BASE) == TIM_DMABase_CCMR2) || \
                               ((BASE) == TIM_DMABase_CCER) || \
                               ((BASE) == TIM_DMABase_CNT) || \
                               ((BASE) == TIM_DMABase_PSC) || \
                               ((BASE) == TIM_DMABase_ARR) || \
                               ((BASE) == TIM_DMABase_RCR) || \
                               ((BASE) == TIM_DMABase_CCR1) || \
                               ((BASE) == TIM_DMABase_CCR2) || \
                               ((BASE) == TIM_DMABase_CCR3) || \
                               ((BASE) == TIM_DMABase_CCR4) || \
                               ((BASE) == TIM_DMABase_BDTR) || \
							   ((BASE) == TIM_DMABase_DCR) || \
                               ((BASE) == TIM_DMABase_OR))
/**
  * @}
  */ 


/** @defgroup TIM_DMA_Burst_Length 
  * @{
  */

#define TIM_DMABurstLength_1Transfer           ((uint16_t)0x0000)
#define TIM_DMABurstLength_2Transfers          ((uint16_t)0x0100)
#define TIM_DMABurstLength_3Transfers          ((uint16_t)0x0200)
#define TIM_DMABurstLength_4Transfers          ((uint16_t)0x0300)
#define TIM_DMABurstLength_5Transfers          ((uint16_t)0x0400)
#define TIM_DMABurstLength_6Transfers          ((uint16_t)0x0500)
#define TIM_DMABurstLength_7Transfers          ((uint16_t)0x0600)
#define TIM_DMABurstLength_8Transfers          ((uint16_t)0x0700)
#define TIM_DMABurstLength_9Transfers          ((uint16_t)0x0800)
#define TIM_DMABurstLength_10Transfers         ((uint16_t)0x0900)
#define TIM_DMABurstLength_11Transfers         ((uint16_t)0x0A00)
#define TIM_DMABurstLength_12Transfers         ((uint16_t)0x0B00)
#define TIM_DMABurstLength_13Transfers         ((uint16_t)0x0C00)
#define TIM_DMABurstLength_14Transfers         ((uint16_t)0x0D00)
#define TIM_DMABurstLength_15Transfers         ((uint16_t)0x0E00)
#define TIM_DMABurstLength_16Transfers         ((uint16_t)0x0F00)
#define TIM_DMABurstLength_17Transfers         ((uint16_t)0x1000)
#define TIM_DMABurstLength_18Transfers         ((uint16_t)0x1100)
#define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Transfer) || \
                                   ((LENGTH) == TIM_DMABurstLength_2Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_3Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_4Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_5Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_6Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_7Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_8Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_9Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_10Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Transfers))
/**
  * @}
  */ 

/** @defgroup TIM_DMA_sources 
  * @{
  */

#define TIM_DMA_Update                     ((uint16_t)0x0100)
#define TIM_DMA_CC1                        ((uint16_t)0x0200)
#define TIM_DMA_CC2                        ((uint16_t)0x0400)
#define TIM_DMA_CC3                        ((uint16_t)0x0800)
#define TIM_DMA_CC4                        ((uint16_t)0x1000)
#define TIM_DMA_COM                        ((uint16_t)0x2000)
#define TIM_DMA_Trigger                    ((uint16_t)0x4000)
#define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Prescaler 
  * @{
  */

#define TIM_ExtTRGPSC_OFF                  ((uint16_t)0x0000)
#define TIM_ExtTRGPSC_DIV2                 ((uint16_t)0x1000)
#define TIM_ExtTRGPSC_DIV4                 ((uint16_t)0x2000)
#define TIM_ExtTRGPSC_DIV8                 ((uint16_t)0x3000)
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))
/**
  * @}
  */ 

/** @defgroup TIM_Internal_Trigger_Selection 
  * @{
  */

#define TIM_TS_ITR0                        ((uint16_t)0x0000)
#define TIM_TS_ITR1                        ((uint16_t)0x0010)
#define TIM_TS_ITR2                        ((uint16_t)0x0020)
#define TIM_TS_ITR3                        ((uint16_t)0x0030)
#define TIM_TS_TI1F_ED                     ((uint16_t)0x0040)
#define TIM_TS_TI1FP1                      ((uint16_t)0x0050)
#define TIM_TS_TI2FP2                      ((uint16_t)0x0060)
#define TIM_TS_ETRF                        ((uint16_t)0x0070)
#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                             ((SELECTION) == TIM_TS_ITR1) || \
                                             ((SELECTION) == TIM_TS_ITR2) || \
                                             ((SELECTION) == TIM_TS_ITR3) || \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1) || \
                                             ((SELECTION) == TIM_TS_TI2FP2) || \
                                             ((SELECTION) == TIM_TS_ETRF))
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))
/**
  * @}
  */ 

/** @defgroup TIM_TIx_External_Clock_Source 
  * @{
  */

#define TIM_TIxExternalCLK1Source_TI1      ((uint16_t)0x0050)
#define TIM_TIxExternalCLK1Source_TI2      ((uint16_t)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED    ((uint16_t)0x0040)

/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Polarity 
  * @{
  */ 
#define TIM_ExtTRGPolarity_Inverted        ((uint16_t)0x8000)
#define TIM_ExtTRGPolarity_NonInverted     ((uint16_t)0x0000)
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))
/**
  * @}
  */

/** @defgroup TIM_Prescaler_Reload_Mode 
  * @{
  */

#define TIM_PSCReloadMode_Update           ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate        ((uint16_t)0x0001)
#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))
/**
  * @}
  */ 

/** @defgroup TIM_Forced_Action 
  * @{
  */

#define TIM_ForcedAction_Active            ((uint16_t)0x0050)
#define TIM_ForcedAction_InActive          ((uint16_t)0x0040)
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))
/**
  * @}
  */ 

/** @defgroup TIM_Encoder_Mode 
  * @{
  */

#define TIM_EncoderMode_TI1                ((uint16_t)0x0001)
#define TIM_EncoderMode_TI2                ((uint16_t)0x0002)
#define TIM_EncoderMode_TI12               ((uint16_t)0x0003)
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))
/**
  * @}
  */ 


/** @defgroup TIM_Event_Source 
  * @{
  */

#define TIM_EventSource_Update             ((uint16_t)0x0001)
#define TIM_EventSource_CC1                ((uint16_t)0x0002)
#define TIM_EventSource_CC2                ((uint16_t)0x0004)
#define TIM_EventSource_CC3                ((uint16_t)0x0008)
#define TIM_EventSource_CC4                ((uint16_t)0x0010)
#define TIM_EventSource_COM                ((uint16_t)0x0020)
#define TIM_EventSource_Trigger            ((uint16_t)0x0040)
#define TIM_EventSource_Break              ((uint16_t)0x0080)
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */ 

/** @defgroup TIM_Update_Source 
  * @{
  */

#define TIM_UpdateSource_Global            ((uint16_t)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
#define TIM_UpdateSource_Regular           ((uint16_t)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Preload_State 
  * @{
  */

#define TIM_OCPreload_Enable               ((uint16_t)0x0008)
#define TIM_OCPreload_Disable              ((uint16_t)0x0000)
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Fast_State 
  * @{
  */

#define TIM_OCFast_Enable                  ((uint16_t)0x0004)
#define TIM_OCFast_Disable                 ((uint16_t)0x0000)
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))
                                     
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Clear_State 
  * @{
  */

#define TIM_OCClear_Enable                 ((uint16_t)0x0080)
#define TIM_OCClear_Disable                ((uint16_t)0x0000)
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Trigger_Output_Source 
  * @{
  */

#define TIM_TRGOSource_Reset               ((uint16_t)0x0000)
#define TIM_TRGOSource_Enable              ((uint16_t)0x0010)
#define TIM_TRGOSource_Update              ((uint16_t)0x0020)
#define TIM_TRGOSource_OC1                 ((uint16_t)0x0030)
#define TIM_TRGOSource_OC1Ref              ((uint16_t)0x0040)
#define TIM_TRGOSource_OC2Ref              ((uint16_t)0x0050)
#define TIM_TRGOSource_OC3Ref              ((uint16_t)0x0060)
#define TIM_TRGOSource_OC4Ref              ((uint16_t)0x0070)
#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))
/**
  * @}
  */ 

/** @defgroup TIM_Slave_Mode 
  * @{
  */

#define TIM_SlaveMode_Reset                ((uint16_t)0x0004)
#define TIM_SlaveMode_Gated                ((uint16_t)0x0005)
#define TIM_SlaveMode_Trigger              ((uint16_t)0x0006)
#define TIM_SlaveMode_External1            ((uint16_t)0x0007)
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
                                 ((MODE) == TIM_SlaveMode_Gated) || \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1))
/**
  * @}
  */ 

/** @defgroup TIM_Master_Slave_Mode 
  * @{
  */

#define TIM_MasterSlaveMode_Enable         ((uint16_t)0x0080)
#define TIM_MasterSlaveMode_Disable        ((uint16_t)0x0000)
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))
/**
  * @}
  */ 
  
/** @defgroup TIM_Flags 
  * @{
  */

#define TIM_FLAG_Update                    ((uint16_t)0x0001)
#define TIM_FLAG_CC1                       ((uint16_t)0x0002)
#define TIM_FLAG_CC2                       ((uint16_t)0x0004)
#define TIM_FLAG_CC3                       ((uint16_t)0x0008)
#define TIM_FLAG_CC4                       ((uint16_t)0x0010)
#define TIM_FLAG_COM                       ((uint16_t)0x0020)
#define TIM_FLAG_Trigger                   ((uint16_t)0x0040)
#define TIM_FLAG_Break                     ((uint16_t)0x0080)
#define TIM_FLAG_CC1OF                     ((uint16_t)0x0200)
#define TIM_FLAG_CC2OF                     ((uint16_t)0x0400)
#define TIM_FLAG_CC3OF                     ((uint16_t)0x0800)
#define TIM_FLAG_CC4OF                     ((uint16_t)0x1000)
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
                               ((FLAG) == TIM_FLAG_CC1) || \
                               ((FLAG) == TIM_FLAG_CC2) || \
                               ((FLAG) == TIM_FLAG_CC3) || \
                               ((FLAG) == TIM_FLAG_CC4) || \
                               ((FLAG) == TIM_FLAG_COM) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) || \
                               ((FLAG) == TIM_FLAG_CC1OF) || \
                               ((FLAG) == TIM_FLAG_CC2OF) || \
                               ((FLAG) == TIM_FLAG_CC3OF) || \
                               ((FLAG) == TIM_FLAG_CC4OF))
                               
                               
#define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (uint16_t)0xE100) == 0x0000) && ((TIM_FLAG) != 0x0000))
/**
  * @}
  */ 


/** @defgroup TIM_Input_Capture_Filer_Value 
  * @{
  */

#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF) 
/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Filter 
  * @{
  */

#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)
/**
  * @}
  */

/** @defgroup TIM_OCReferenceClear 
  * @{
  */
#define TIM_OCReferenceClear_ETRF          ((uint16_t)0x0008)
#define TIM_OCReferenceClear_OCREFCLR      ((uint16_t)0x0000)
#define TIM_OCREFERENCECECLEAR_SOURCE(SOURCE) (((SOURCE) == TIM_OCReferenceClear_ETRF) || \
                                              ((SOURCE) == TIM_OCReferenceClear_OCREFCLR)) 

/**
  * @}
  */
/** @defgroup TIM_Remap 
  * @{
  */
#define TIM14_GPIO                      ((uint16_t)0x0000)
#define TIM14_RTC_CLK                   ((uint16_t)0x0001)
#define TIM14_HSEDiv32                  ((uint16_t)0x0002)
#define TIM14_MCO                       ((uint16_t)0x0003)

#define IS_TIM_REMAP(TIM_REMAP)  (((TIM_REMAP) == TIM14_GPIO)|| \
                                  ((TIM_REMAP) == TIM14_RTC_CLK) || \
                                  ((TIM_REMAP) == TIM14_HSEDiv32) || \
                                  ((TIM_REMAP) == TIM14_MCO))
/**
  * @}
  */

/** @defgroup TIM_Legacy 
  * @{
  */

#define TIM_DMABurstLength_1Byte           TIM_DMABurstLength_1Transfer
#define TIM_DMABurstLength_2Bytes          TIM_DMABurstLength_2Transfers
#define TIM_DMABurstLength_3Bytes          TIM_DMABurstLength_3Transfers
#define TIM_DMABurstLength_4Bytes          TIM_DMABurstLength_4Transfers
#define TIM_DMABurstLength_5Bytes          TIM_DMABurstLength_5Transfers
#define TIM_DMABurstLength_6Bytes          TIM_DMABurstLength_6Transfers
#define TIM_DMABurstLength_7Bytes          TIM_DMABurstLength_7Transfers
#define TIM_DMABurstLength_8Bytes          TIM_DMABurstLength_8Transfers
#define TIM_DMABurstLength_9Bytes          TIM_DMABurstLength_9Transfers
#define TIM_DMABurstLength_10Bytes         TIM_DMABurstLength_10Transfers
#define TIM_DMABurstLength_11Bytes         TIM_DMABurstLength_11Transfers
#define TIM_DMABurstLength_12Bytes         TIM_DMABurstLength_12Transfers
#define TIM_DMABurstLength_13Bytes         TIM_DMABurstLength_13Transfers
#define TIM_DMABurstLength_14Bytes         TIM_DMABurstLength_14Transfers
#define TIM_DMABurstLength_15Bytes         TIM_DMABurstLength_15Transfers
#define TIM_DMABurstLength_16Bytes         TIM_DMABurstLength_16Transfers
#define TIM_DMABurstLength_17Bytes         TIM_DMABurstLength_17Transfers
#define TIM_DMABurstLength_18Bytes         TIM_DMABurstLength_18Transfers
/**
  * @}
  */

/**
  * @}
  */
  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/* TimeBase management ********************************************************/
void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload);
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Advanced-control timers (TIM1) specific features*******************/
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Output Compare management **************************************************/
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_SelectOCREFClear(TIM_TypeDef* TIMx, uint16_t TIM_OCReferenceClear);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Input Capture management ***************************************************/
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);

/* Interrupts, DMA and flags management ***************************************/
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Clocks management **********************************************************/
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);


/* Synchronization management *************************************************/
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);

/* Specific interface management **********************************************/                   
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Specific remapping management **********************************************/
void TIM_RemapConfig(TIM_TypeDef* TIMx, uint16_t TIM_Remap);


#ifdef __cplusplus
}
#endif

#endif /*__STM32F0XX_TIM_H */

/**
  * @}
  */ 

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_usart.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the USART 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_USART_H
#define __STM32F0XX_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

   
   
/** 
  * @brief  USART Init Structure definition  
  */ 

typedef struct
{
  uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5 */

  uint32_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */

  uint32_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  uint32_t USART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
 
  uint32_t USART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  uint32_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control*/
} USART_InitTypeDef;

/** 
  * @brief  USART Clock Init Structure definition
  */ 

typedef struct
{
  uint32_t USART_Clock;             /*!< Specifies whether the USART clock is enabled or disabled.
                                         This parameter can be a value of @ref USART_Clock */

  uint32_t USART_CPOL;              /*!< Specifies the steady state of the serial clock.
                                         This parameter can be a value of @ref USART_Clock_Polarity */

  uint32_t USART_CPHA;              /*!< Specifies the clock transition on which the bit capture is made.
                                         This parameter can be a value of @ref USART_Clock_Phase */

  uint32_t USART_LastBit;           /*!< Specifies whether the clock pulse corresponding to the last transmitted
                                         data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                         This parameter can be a value of @ref USART_Last_Bit */
} USART_ClockInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup USART_Exported_Constants
  * @{
  */ 

#define IS_USART_ALL_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3) || \
                                     ((PERIPH) == USART4) || \
                                     ((PERIPH) == USART5) || \
                                     ((PERIPH) == USART6) || \
                                     ((PERIPH) == USART7) || \
                                     ((PERIPH) == USART8))

#define IS_USART_123_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3))

/** @defgroup USART_Word_Length 
  * @{
  */ 

#define USART_WordLength_8b                  ((uint32_t)0x00000000)
#define USART_WordLength_9b                  USART_CR1_M /* should be ((uint32_t)0x00001000) */
#define USART_WordLength_7b                  ((uint32_t)0x10001000) /*!< only available for STM32F072 and STM32F030 devices */
#define IS_USART_WORD_LENGTH(LENGTH) (((LENGTH) == USART_WordLength_8b) || \
                                      ((LENGTH) == USART_WordLength_9b) || \
                                      ((LENGTH) == USART_WordLength_7b))
/**
  * @}
  */ 

/** @defgroup USART_Stop_Bits 
  * @{
  */ 

#define USART_StopBits_1                     ((uint32_t)0x00000000)
#define USART_StopBits_2                     USART_CR2_STOP_1
#define USART_StopBits_1_5                   (USART_CR2_STOP_0 | USART_CR2_STOP_1)
#define IS_USART_STOPBITS(STOPBITS) (((STOPBITS) == USART_StopBits_1) || \
                                     ((STOPBITS) == USART_StopBits_2) || \
                                     ((STOPBITS) == USART_StopBits_1_5))
/**
  * @}
  */ 

/** @defgroup USART_Parity 
  * @{
  */ 

#define USART_Parity_No                      ((uint32_t)0x00000000)
#define USART_Parity_Even                    USART_CR1_PCE
#define USART_Parity_Odd                     (USART_CR1_PCE | USART_CR1_PS) 
#define IS_USART_PARITY(PARITY) (((PARITY) == USART_Parity_No) || \
                                 ((PARITY) == USART_Parity_Even) || \
                                 ((PARITY) == USART_Parity_Odd))
/**
  * @}
  */ 

/** @defgroup USART_Mode 
  * @{
  */ 

#define USART_Mode_Rx                        USART_CR1_RE
#define USART_Mode_Tx                        USART_CR1_TE
#define IS_USART_MODE(MODE) ((((MODE) & (uint32_t)0xFFFFFFF3) == 0x00) && \
                              ((MODE) != (uint32_t)0x00))
/**
  * @}
  */ 

/** @defgroup USART_Hardware_Flow_Control 
  * @{
  */ 

#define USART_HardwareFlowControl_None       ((uint32_t)0x00000000)
#define USART_HardwareFlowControl_RTS        USART_CR3_RTSE
#define USART_HardwareFlowControl_CTS        USART_CR3_CTSE
#define USART_HardwareFlowControl_RTS_CTS    (USART_CR3_RTSE | USART_CR3_CTSE)
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)\
                              (((CONTROL) == USART_HardwareFlowControl_None) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS) || \
                               ((CONTROL) == USART_HardwareFlowControl_CTS) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS_CTS))
/**
  * @}
  */ 

/** @defgroup USART_Clock 
  * @{
  */ 
  
#define USART_Clock_Disable                  ((uint32_t)0x00000000)
#define USART_Clock_Enable                   USART_CR2_CLKEN
#define IS_USART_CLOCK(CLOCK) (((CLOCK) == USART_Clock_Disable) || \
                               ((CLOCK) == USART_Clock_Enable))
/**
  * @}
  */ 

/** @defgroup USART_Clock_Polarity 
  * @{
  */
  
#define USART_CPOL_Low                       ((uint32_t)0x00000000)
#define USART_CPOL_High                      USART_CR2_CPOL
#define IS_USART_CPOL(CPOL) (((CPOL) == USART_CPOL_Low) || ((CPOL) == USART_CPOL_High))

/**
  * @}
  */ 

/** @defgroup USART_Clock_Phase
  * @{
  */

#define USART_CPHA_1Edge                     ((uint32_t)0x00000000)
#define USART_CPHA_2Edge                     USART_CR2_CPHA
#define IS_USART_CPHA(CPHA) (((CPHA) == USART_CPHA_1Edge) || ((CPHA) == USART_CPHA_2Edge))

/**
  * @}
  */

/** @defgroup USART_Last_Bit
  * @{
  */

#define USART_LastBit_Disable                ((uint32_t)0x00000000)
#define USART_LastBit_Enable                 USART_CR2_LBCL
#define IS_USART_LASTBIT(LASTBIT) (((LASTBIT) == USART_LastBit_Disable) || \
                                   ((LASTBIT) == USART_LastBit_Enable))
/**
  * @}
  */
  
/** @defgroup USART_DMA_Requests 
  * @{
  */

#define USART_DMAReq_Tx                      USART_CR3_DMAT
#define USART_DMAReq_Rx                      USART_CR3_DMAR
#define IS_USART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint32_t)0xFFFFFF3F) == 0x00) && \
                                  ((DMAREQ) != (uint32_t)0x00))

/**
  * @}
  */ 

/** @defgroup USART_DMA_Recception_Error
  * @{
  */

#define USART_DMAOnError_Enable              ((uint32_t)0x00000000)
#define USART_DMAOnError_Disable             USART_CR3_DDRE
#define IS_USART_DMAONERROR(DMAERROR) (((DMAERROR) == USART_DMAOnError_Disable)|| \
                                       ((DMAERROR) == USART_DMAOnError_Enable))
/**
  * @}
  */ 

/** @defgroup USART_MuteMode_WakeUp_methods
  * @{
  */

#define USART_WakeUp_IdleLine                ((uint32_t)0x00000000)
#define USART_WakeUp_AddressMark             USART_CR1_WAKE
#define IS_USART_MUTEMODE_WAKEUP(WAKEUP) (((WAKEUP) == USART_WakeUp_IdleLine) || \
                                          ((WAKEUP) == USART_WakeUp_AddressMark))
/**
  * @}
  */

/** @defgroup USART_Address_Detection
  * @{
  */ 

#define USART_AddressLength_4b               ((uint32_t)0x00000000)
#define USART_AddressLength_7b               USART_CR2_ADDM7
#define IS_USART_ADDRESS_DETECTION(ADDRESS) (((ADDRESS) == USART_AddressLength_4b) || \
                                             ((ADDRESS) == USART_AddressLength_7b))
/**
  * @}
  */ 

/** @defgroup USART_StopMode_WakeUp_methods
  * @note     These parameters are only available for STM32F051 and STM32F072 devices 
  * @{
  */ 

#define USART_WakeUpSource_AddressMatch      ((uint32_t)0x00000000)
#define USART_WakeUpSource_StartBit          USART_CR3_WUS_1
#define USART_WakeUpSource_RXNE              (USART_CR3_WUS_0 | USART_CR3_WUS_1)
#define IS_USART_STOPMODE_WAKEUPSOURCE(SOURCE) (((SOURCE) == USART_WakeUpSource_AddressMatch) || \
                                                ((SOURCE) == USART_WakeUpSource_StartBit) || \
                                                ((SOURCE) == USART_WakeUpSource_RXNE))
/**
  * @}
  */ 

/** @defgroup USART_LIN_Break_Detection_Length 
  * @{
  */
  
#define USART_LINBreakDetectLength_10b       ((uint32_t)0x00000000)
#define USART_LINBreakDetectLength_11b       USART_CR2_LBDL
#define IS_USART_LIN_BREAK_DETECT_LENGTH(LENGTH) \
                               (((LENGTH) == USART_LINBreakDetectLength_10b) || \
                                ((LENGTH) == USART_LINBreakDetectLength_11b))
/**
  * @}
  */

/** @defgroup USART_IrDA_Low_Power 
  * @{
  */

#define USART_IrDAMode_LowPower              USART_CR3_IRLP
#define USART_IrDAMode_Normal                ((uint32_t)0x00000000)
#define IS_USART_IRDA_MODE(MODE) (((MODE) == USART_IrDAMode_LowPower) || \
                                  ((MODE) == USART_IrDAMode_Normal))
/**
  * @}
  */ 

/** @defgroup USART_DE_Polarity 
  * @{
  */

#define USART_DEPolarity_High                ((uint32_t)0x00000000)
#define USART_DEPolarity_Low                 USART_CR3_DEP
#define IS_USART_DE_POLARITY(POLARITY) (((POLARITY) == USART_DEPolarity_Low) || \
                                        ((POLARITY) == USART_DEPolarity_High))
/**
  * @}
  */ 

/** @defgroup USART_Inversion_Pins 
  * @{
  */

#define USART_InvPin_Tx                      USART_CR2_TXINV
#define USART_InvPin_Rx                      USART_CR2_RXINV
#define IS_USART_INVERSTION_PIN(PIN) ((((PIN) & (uint32_t)0xFFFCFFFF) == 0x00) && \
                                       ((PIN) != (uint32_t)0x00))

/**
  * @}
  */ 

/** @defgroup USART_AutoBaudRate_Mode 
  * @{
  */

#define USART_AutoBaudRate_StartBit          ((uint32_t)0x00000000)
#define USART_AutoBaudRate_FallingEdge       USART_CR2_ABRMODE_0
#define IS_USART_AUTOBAUDRATE_MODE(MODE) (((MODE) == USART_AutoBaudRate_StartBit) || \
                                          ((MODE) == USART_AutoBaudRate_FallingEdge))
/**
  * @}
  */ 

/** @defgroup USART_OVR_DETECTION
  * @{
  */

#define USART_OVRDetection_Enable            ((uint32_t)0x00000000)
#define USART_OVRDetection_Disable           USART_CR3_OVRDIS
#define IS_USART_OVRDETECTION(OVR) (((OVR) == USART_OVRDetection_Enable)|| \
                                    ((OVR) == USART_OVRDetection_Disable))
/**
  * @}
  */ 
/** @defgroup USART_Request 
  * @{
  */

#define USART_Request_ABRRQ                  USART_RQR_ABRRQ
#define USART_Request_SBKRQ                  USART_RQR_SBKRQ
#define USART_Request_MMRQ                   USART_RQR_MMRQ
#define USART_Request_RXFRQ                  USART_RQR_RXFRQ
#define USART_Request_TXFRQ                  USART_RQR_TXFRQ

#define IS_USART_REQUEST(REQUEST) (((REQUEST) == USART_Request_TXFRQ) || \
                                   ((REQUEST) == USART_Request_RXFRQ) || \
                                   ((REQUEST) == USART_Request_MMRQ) || \
                                   ((REQUEST) == USART_Request_SBKRQ) || \
                                   ((REQUEST) == USART_Request_ABRRQ))
/**
  * @}
  */ 

/** @defgroup USART_Flags 
  * @{
  */
#define USART_FLAG_REACK                     USART_ISR_REACK
#define USART_FLAG_TEACK                     USART_ISR_TEACK
#define USART_FLAG_WU                        USART_ISR_WUF /*!< Not available for  STM32F030 devices */
#define USART_FLAG_RWU                       USART_ISR_RWU /*!< Not available for  STM32F030 devices */
#define USART_FLAG_SBK                       USART_ISR_SBKF
#define USART_FLAG_CM                        USART_ISR_CMF
#define USART_FLAG_BUSY                      USART_ISR_BUSY
#define USART_FLAG_ABRF                      USART_ISR_ABRF
#define USART_FLAG_ABRE                      USART_ISR_ABRE
#define USART_FLAG_EOB                       USART_ISR_EOBF /*!< Not available for  STM32F030 devices */
#define USART_FLAG_RTO                       USART_ISR_RTOF
#define USART_FLAG_nCTSS                     USART_ISR_CTS 
#define USART_FLAG_CTS                       USART_ISR_CTSIF
#define USART_FLAG_LBD                       USART_ISR_LBD /*!< Not available for  STM32F030 devices */
#define USART_FLAG_TXE                       USART_ISR_TXE
#define USART_FLAG_TC                        USART_ISR_TC
#define USART_FLAG_RXNE                      USART_ISR_RXNE
#define USART_FLAG_IDLE                      USART_ISR_IDLE
#define USART_FLAG_ORE                       USART_ISR_ORE
#define USART_FLAG_NE                        USART_ISR_NE
#define USART_FLAG_FE                        USART_ISR_FE
#define USART_FLAG_PE                        USART_ISR_PE
#define IS_USART_FLAG(FLAG) (((FLAG) == USART_FLAG_PE) || ((FLAG) == USART_FLAG_TXE) || \
                             ((FLAG) == USART_FLAG_TC) || ((FLAG) == USART_FLAG_RXNE) || \
                             ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_LBD) || \
                             ((FLAG) == USART_FLAG_CTS) || ((FLAG) == USART_FLAG_ORE) || \
                             ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE) || \
                             ((FLAG) == USART_FLAG_nCTSS) || ((FLAG) == USART_FLAG_RTO) || \
                             ((FLAG) == USART_FLAG_EOB) || ((FLAG) == USART_FLAG_ABRE) || \
                             ((FLAG) == USART_FLAG_ABRF) || ((FLAG) == USART_FLAG_BUSY) || \
                             ((FLAG) == USART_FLAG_CM) || ((FLAG) == USART_FLAG_SBK) || \
                             ((FLAG) == USART_FLAG_RWU) || ((FLAG) == USART_FLAG_WU) || \
                             ((FLAG) == USART_FLAG_TEACK)|| ((FLAG) == USART_FLAG_REACK))

#define IS_USART_CLEAR_FLAG(FLAG) (((FLAG) == USART_FLAG_WU) || ((FLAG) == USART_FLAG_TC) || \
                                   ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_ORE) || \
                                   ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE) || \
                                   ((FLAG) == USART_FLAG_LBD) || ((FLAG) == USART_FLAG_CTS) || \
                                   ((FLAG) == USART_FLAG_RTO) || ((FLAG) == USART_FLAG_EOB) || \
                                   ((FLAG) == USART_FLAG_CM) || ((FLAG) == USART_FLAG_PE))
/**
  * @}
  */ 

/** @defgroup USART_Interrupt_definition 
  * @brief USART Interrupt definition
  * USART_IT possible values
  * Elements values convention: 0xZZZZYYXX
  *   XX: Position of the corresponding Interrupt
  *   YY: Register index
  *   ZZZZ: Flag position
  * @{
  */

#define USART_IT_WU                          ((uint32_t)0x00140316) /*!< Not available for  STM32F030 devices */
#define USART_IT_CM                          ((uint32_t)0x0011010E)
#define USART_IT_EOB                         ((uint32_t)0x000C011B) /*!< Not available for  STM32F030 devices */
#define USART_IT_RTO                         ((uint32_t)0x000B011A)
#define USART_IT_PE                          ((uint32_t)0x00000108)
#define USART_IT_TXE                         ((uint32_t)0x00070107)
#define USART_IT_TC                          ((uint32_t)0x00060106)
#define USART_IT_RXNE                        ((uint32_t)0x00050105)
#define USART_IT_IDLE                        ((uint32_t)0x00040104)
#define USART_IT_LBD                         ((uint32_t)0x00080206) /*!< Not available for  STM32F030 devices */
#define USART_IT_CTS                         ((uint32_t)0x0009030A) 
#define USART_IT_ERR                         ((uint32_t)0x00000300)
#define USART_IT_ORE                         ((uint32_t)0x00030300)
#define USART_IT_NE                          ((uint32_t)0x00020300)
#define USART_IT_FE                          ((uint32_t)0x00010300)

#define IS_USART_CONFIG_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                                ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                                ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                                ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ERR) || \
                                ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
                                ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))

#define IS_USART_GET_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                             ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                             ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                             ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ORE) || \
                             ((IT) == USART_IT_NE) || ((IT) == USART_IT_FE) || \
                             ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
                             ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))

#define IS_USART_CLEAR_IT(IT) (((IT) == USART_IT_TC) || ((IT) == USART_IT_PE) || \
                               ((IT) == USART_IT_FE) || ((IT) == USART_IT_NE) || \
                               ((IT) == USART_IT_ORE) || ((IT) == USART_IT_IDLE) || \
                               ((IT) == USART_IT_LBD) || ((IT) == USART_IT_CTS) || \
                               ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
                               ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))
/**
  * @}
  */

/** @defgroup USART_Global_definition 
  * @{
  */

#define IS_USART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x005B8D81))
#define IS_USART_DE_ASSERTION_DEASSERTION_TIME(TIME) ((TIME) <= 0x1F)
#define IS_USART_AUTO_RETRY_COUNTER(COUNTER) ((COUNTER) <= 0x7)
#define IS_USART_TIMEOUT(TIMEOUT) ((TIMEOUT) <= 0x00FFFFFF)
#define IS_USART_DATA(DATA) ((DATA) <= 0x1FF)

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_DirectionModeCmd(USART_TypeDef* USARTx, uint32_t USART_DirectionMode, FunctionalState NewState);
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler); /* Not available for STM32F030 devices */
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_MSBFirstCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_DataInvCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_InvPinCmd(USART_TypeDef* USARTx, uint32_t USART_InvPin, FunctionalState NewState);
void USART_SWAPPinCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ReceiverTimeOutCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SetReceiverTimeOut(USART_TypeDef* USARTx, uint32_t USART_ReceiverTimeOut);

/* STOP Mode functions ********************************************************/
void USART_STOPModeCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_StopModeWakeUpSourceConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUpSource); /* Not available for STM32F030 devices */

/* AutoBaudRate functions *****************************************************/
void USART_AutoBaudRateCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_AutoBaudRateConfig(USART_TypeDef* USARTx, uint32_t USART_AutoBaudRate);

/* Data transfers functions ***************************************************/
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);

/* Multi-Processor Communication functions ************************************/
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_MuteModeWakeUpConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUp);
void USART_MuteModeCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_AddressDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_AddressLength);

/* LIN mode functions *********************************************************/
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint32_t USART_LINBreakDetectLength); /* Not available for STM32F030 devices */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState); /* Not available for STM32F030 devices */

/* Half-duplex mode function **************************************************/
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* Smartcard mode functions ***************************************************/
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState); /* Not available for STM32F030 devices */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState); /* Not available for STM32F030 devices */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime); /* Not available for STM32F030 devices */
void USART_SetAutoRetryCount(USART_TypeDef* USARTx, uint8_t USART_AutoCount); /* Not available for STM32F030 devices */
void USART_SetBlockLength(USART_TypeDef* USARTx, uint8_t USART_BlockLength); /* Not available for STM32F030 devices */

/* IrDA mode functions ********************************************************/
void USART_IrDAConfig(USART_TypeDef* USARTx, uint32_t USART_IrDAMode); /* Not available for STM32F030 devices */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState); /* Not available for STM32F030 devices */

/* RS485 mode functions *******************************************************/
void USART_DECmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_DEPolarityConfig(USART_TypeDef* USARTx, uint32_t USART_DEPolarity);
void USART_SetDEAssertionTime(USART_TypeDef* USARTx, uint32_t USART_DEAssertionTime);
void USART_SetDEDeassertionTime(USART_TypeDef* USARTx, uint32_t USART_DEDeassertionTime);

/* DMA transfers management functions *****************************************/
void USART_DMACmd(USART_TypeDef* USARTx, uint32_t USART_DMAReq, FunctionalState NewState);
void USART_DMAReceptionErrorConfig(USART_TypeDef* USARTx, uint32_t USART_DMAOnError);

/* Interrupts and flags management functions **********************************/
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState);
void USART_RequestCmd(USART_TypeDef* USARTx, uint32_t USART_Request, FunctionalState NewState);
void USART_OverrunDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_OVRDetection);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_USART_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_wwdg.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file contains all the functions prototypes for the WWDG 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_WWDG_H
#define __STM32F0XX_WWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup WWDG
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup WWDG_Exported_Constants
  * @{
  */ 
  
/** @defgroup WWDG_Prescaler 
  * @{
  */ 
  
#define WWDG_Prescaler_1    ((uint32_t)0x00000000)
#define WWDG_Prescaler_2    ((uint32_t)0x00000080)
#define WWDG_Prescaler_4    ((uint32_t)0x00000100)
#define WWDG_Prescaler_8    ((uint32_t)0x00000180)
#define IS_WWDG_PRESCALER(PRESCALER) (((PRESCALER) == WWDG_Prescaler_1) || \
                                      ((PRESCALER) == WWDG_Prescaler_2) || \
                                      ((PRESCALER) == WWDG_Prescaler_4) || \
                                      ((PRESCALER) == WWDG_Prescaler_8))
#define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)
#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/*  Function used to set the WWDG configuration to the default reset state ****/  
void WWDG_DeInit(void);

/* Prescaler, Refresh window and Counter configuration functions **************/
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(uint8_t Counter);

/* WWDG activation functions **************************************************/
void WWDG_Enable(uint8_t Counter);

/* Interrupts and flags management functions **********************************/
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_WWDG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
