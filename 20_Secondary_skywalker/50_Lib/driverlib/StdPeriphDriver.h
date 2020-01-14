/**
  ******************************************************************************
  * @file    stm32f30x_adc.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the ADC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_ADC_H
#define __STM32F30x_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"
#include "stdint.h"
#include "RegBitDefs.h"                    // common header file   
/** @addtogroup STM32F30x_StdPeriph_Driver
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

  uint32_t ADC_ContinuousConvMode;        /*!< Specifies whether the conversion is performed in
                                               Continuous or Single mode.
                                               This parameter can be set to ENABLE or DISABLE. */
  uint32_t ADC_Resolution;                /*!< Configures the ADC resolution.
                                               This parameter can be a value of @ref ADC_resolution */ 
  uint32_t ADC_ExternalTrigConvEvent;      /*!< Defines the external trigger used to start the analog
                                               to digital conversion of regular channels. This parameter
                                               can be a value of @ref ADC_external_trigger_sources_for_regular_channels_conversion */
  uint32_t ADC_ExternalTrigEventEdge;      /*!< Select the external trigger edge and enable the trigger of a regular group.                                               
                                               This parameter can be a value of 
                                               @ref ADC_external_trigger_edge_for_regular_channels_conversion */
  uint32_t ADC_DataAlign;                 /*!< Specifies whether the ADC data alignment is left or right.
                                               This parameter can be a value of @ref ADC_data_align */
  uint32_t ADC_OverrunMode;               /*!< Specifies the way data overrun are managed.
                                               This parameter can be set to ENABLE or DISABLE. */
  uint32_t ADC_AutoInjMode;               /*!< Enable/disable automatic injected group conversion after
                                               regular group conversion.
                                               This parameter can be set to ENABLE or DISABLE. */
  uint8_t ADC_NbrOfRegChannel;            /*!< Specifies the number of ADC channels that will be converted
                                               using the sequencer for regular channel group.
                                               This parameter must range from 1 to 16. */
}ADC_InitTypeDef;

/**
  * @}
  */
/** 
  * @brief  ADC Init structure definition  
  */
typedef struct
{

   uint32_t ADC_ExternalTrigInjecConvEvent;     /*!< Defines the external trigger used to start the analog
                                                     to digital conversion of injected channels. This parameter
                                                     can be a value of @ref ADC_external_trigger_sources_for_Injected_channels_conversion */
  uint32_t ADC_ExternalTrigInjecEventEdge;     /*!< Select the external trigger edge and enable the trigger of an injected group. 
                                                    This parameter can be a value of 
                                                    @ref ADC_external_trigger_edge_for_Injected_channels_conversion */
  uint8_t ADC_NbrOfInjecChannel;               /*!< Specifies the number of ADC channels that will be converted
                                                    using the sequencer for injected channel group.
                                                    This parameter must range from 1 to 4. */ 
  uint32_t ADC_InjecSequence1; 
  uint32_t ADC_InjecSequence2;
  uint32_t ADC_InjecSequence3;
  uint32_t ADC_InjecSequence4;                                            
}ADC_InjectedInitTypeDef;

/**
  * @}
  */
typedef struct 
{
  uint32_t ADC_Mode;                      /*!< Configures the ADC to operate in 
                                               independent or multi mode. 
                                               This parameter can be a value of @ref ADC_mode */                                              
  uint32_t ADC_Clock;                    /*!< Select the clock of the ADC. The clock is common for both master 
                                              and slave ADCs.
                                              This parameter can be a value of @ref ADC_Clock */
  uint32_t ADC_DMAAccessMode;             /*!< Configures the Direct memory access mode for multi ADC mode.                                               
                                               This parameter can be a value of 
                                               @ref ADC_Direct_memory_access_mode_for_multi_mode */
  uint32_t ADC_DMAMode;                  /*!< Configures the DMA mode for ADC.                                             
                                              This parameter can be a value of @ref ADC_DMA_Mode_definition */
  uint8_t ADC_TwoSamplingDelay;          /*!< Configures the Delay between 2 sampling phases.
                                               This parameter can be a value between  0x0 and 0xF  */
  
}ADC_CommonInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */ 

#define IS_ADC_ALL_PERIPH(PERIPH) (((PERIPH) == ADC1) || \
                                   ((PERIPH) == ADC2) || \
                                   ((PERIPH) == ADC3) || \
                                   ((PERIPH) == ADC4))

#define IS_ADC_DMA_PERIPH(PERIPH) (((PERIPH) == ADC1) || \
                                   ((PERIPH) == ADC2) || \
                                   ((PERIPH) == ADC3) || \
                                   ((PERIPH) == ADC4))

/** @defgroup ADC_ContinuousConvMode 
  * @{
  */
#define ADC_ContinuousConvMode_Enable   ((uint32_t)0x00002000)  /*!<  ADC continuous conversion mode enable */
#define ADC_ContinuousConvMode_Disable   ((uint32_t)0x00000000)  /*!<  ADC continuous conversion mode disable */
#define IS_ADC_CONVMODE(MODE) (((MODE) == ADC_ContinuousConvMode_Enable) || \
                               ((MODE) == ADC_ContinuousConvMode_Disable))
/**
  * @}
  */
/** @defgroup ADC_OverunMode 
  * @{
  */
#define ADC_OverrunMode_Enable   ((uint32_t)0x00001000)  /*!<  ADC Overrun Mode enable */
#define ADC_OverrunMode_Disable   ((uint32_t)0x00000000)  /*!<  ADC Overrun Mode disable */
#define IS_ADC_OVRUNMODE(MODE) (((MODE) == ADC_OverrunMode_Enable) || \
                                ((MODE) == ADC_OverrunMode_Disable))
/**
  * @}
  */
/** @defgroup ADC_AutoInjecMode 
  * @{
  */
#define ADC_AutoInjec_Enable   ((uint32_t)0x02000000)  /*!<  ADC Auto injected Mode enable */
#define ADC_AutoInjec_Disable   ((uint32_t)0x00000000)  /*!<  ADC Auto injected Mode disable */
#define IS_ADC_AUTOINJECMODE(MODE) (((MODE) == ADC_AutoInjec_Enable) || \
                                    ((MODE) == ADC_AutoInjec_Disable))
/**
  * @}
  */
/** @defgroup ADC_resolution 
  * @{
  */ 
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)  /*!<  ADC 12-bit resolution */
#define ADC_Resolution_10b                         ((uint32_t)0x00000008)  /*!<  ADC 10-bit resolution */
#define ADC_Resolution_8b                          ((uint32_t)0x00000010)  /*!<  ADC 8-bit resolution */
#define ADC_Resolution_6b                          ((uint32_t)0x00000018)  /*!<  ADC 6-bit resolution */
#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) || \
                                       ((RESOLUTION) == ADC_Resolution_10b) || \
                                       ((RESOLUTION) == ADC_Resolution_8b) || \
                                       ((RESOLUTION) == ADC_Resolution_6b))
                                      
/**
  * @}
  */ 
  
  
/** @defgroup ADC_external_trigger_edge_for_regular_channels_conversion 
  * @{
  */
#define ADC_ExternalTrigEventEdge_None            ((uint16_t)0x0000)     /*!<  ADC No external trigger for regular conversion */
#define ADC_ExternalTrigEventEdge_RisingEdge      ((uint16_t)0x0400)     /*!<  ADC external trigger rising edge for regular conversion */
#define ADC_ExternalTrigEventEdge_FallingEdge     ((uint16_t)0x0800)     /*!<  ADC ADC external trigger falling edge for regular conversion */
#define ADC_ExternalTrigEventEdge_BothEdge        ((uint16_t)0x0C00)     /*!<  ADC ADC external trigger both edges for regular conversion */

#define IS_EXTERNALTRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigEventEdge_None) || \
                                    ((EDGE) == ADC_ExternalTrigEventEdge_RisingEdge) || \
                                    ((EDGE) == ADC_ExternalTrigEventEdge_FallingEdge) || \
                                    ((EDGE) == ADC_ExternalTrigEventEdge_BothEdge))
  
/**
  * @}
  */
   
/** @defgroup ADC_external_trigger_edge_for_Injected_channels_conversion 
  * @{
  */     
#define ADC_ExternalTrigInjecEventEdge_None         ((uint16_t)0x0000)    /*!<  ADC No external trigger for regular conversion */
#define ADC_ExternalTrigInjecEventEdge_RisingEdge   ((uint16_t)0x0040)    /*!<  ADC external trigger rising edge for injected conversion */
#define ADC_ExternalTrigInjecEventEdge_FallingEdge   ((uint16_t)0x0080)  /*!<  ADC external trigger falling edge for injected conversion */
#define ADC_ExternalTrigInjecEventEdge_BothEdge       ((uint16_t)0x00C0)  /*!<  ADC external trigger both edges for injected conversion */

#define IS_EXTERNALTRIGINJ_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigInjecEventEdge_None) || \
                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_RisingEdge) || \
                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_FallingEdge) || \
                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_BothEdge))
  
/** @defgroup ADC_external_trigger_sources_for_regular_channels_conversion 
  * @{
  */
#define ADC_ExternalTrigConvEvent_0              ((uint16_t)0x0000)   /*!<  ADC external trigger event 0 */
#define ADC_ExternalTrigConvEvent_1              ((uint16_t)0x0040)   /*!<  ADC external trigger event 1 */
#define ADC_ExternalTrigConvEvent_2              ((uint16_t)0x0080)   /*!<  ADC external trigger event 2 */
#define ADC_ExternalTrigConvEvent_3              ((uint16_t)0x00C0)   /*!<  ADC external trigger event 3 */
#define ADC_ExternalTrigConvEvent_4              ((uint16_t)0x0100)   /*!<  ADC external trigger event 4 */
#define ADC_ExternalTrigConvEvent_5              ((uint16_t)0x0140)   /*!<  ADC external trigger event 5 */
#define ADC_ExternalTrigConvEvent_6              ((uint16_t)0x0180)   /*!<  ADC external trigger event 6 */
#define ADC_ExternalTrigConvEvent_7              ((uint16_t)0x01C0)   /*!<  ADC external trigger event 7 */
#define ADC_ExternalTrigConvEvent_8              ((uint16_t)0x0200)   /*!<  ADC external trigger event 8 */
#define ADC_ExternalTrigConvEvent_9              ((uint16_t)0x0240)   /*!<  ADC external trigger event 9 */
#define ADC_ExternalTrigConvEvent_10             ((uint16_t)0x0280)   /*!<  ADC external trigger event 10 */
#define ADC_ExternalTrigConvEvent_11             ((uint16_t)0x02C0)   /*!<  ADC external trigger event 11 */
#define ADC_ExternalTrigConvEvent_12             ((uint16_t)0x0300)   /*!<  ADC external trigger event 12 */
#define ADC_ExternalTrigConvEvent_13             ((uint16_t)0x0340)   /*!<  ADC external trigger event 13 */
#define ADC_ExternalTrigConvEvent_14             ((uint16_t)0x0380)   /*!<  ADC external trigger event 14 */
#define ADC_ExternalTrigConvEvent_15             ((uint16_t)0x03C0)   /*!<  ADC external trigger event 15 */

#define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_ExternalTrigConvEvent_0) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_5) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_6) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_7) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_8) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_9) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_10) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_11) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_12) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_13) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_14) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_15))

/**
  * @}
  */

/** @defgroup ADC_external_trigger_sources_for_Injected_channels_conversion 
  * @{
  */
        
#define ADC_ExternalTrigInjecConvEvent_0              ((uint16_t)0x0000)  /*!<  ADC external trigger for injected conversion event 0 */
#define ADC_ExternalTrigInjecConvEvent_1              ((uint16_t)0x0004)  /*!<  ADC external trigger for injected conversion event 1 */
#define ADC_ExternalTrigInjecConvEvent_2              ((uint16_t)0x0008)  /*!<  ADC external trigger for injected conversion event 2 */
#define ADC_ExternalTrigInjecConvEvent_3              ((uint16_t)0x000C)  /*!<  ADC external trigger for injected conversion event 3 */
#define ADC_ExternalTrigInjecConvEvent_4              ((uint16_t)0x0010)  /*!<  ADC external trigger for injected conversion event 4 */
#define ADC_ExternalTrigInjecConvEvent_5              ((uint16_t)0x0014)  /*!<  ADC external trigger for injected conversion event 5 */
#define ADC_ExternalTrigInjecConvEvent_6              ((uint16_t)0x0018)  /*!<  ADC external trigger for injected conversion event 6 */
#define ADC_ExternalTrigInjecConvEvent_7              ((uint16_t)0x001C)  /*!<  ADC external trigger for injected conversion event 7 */
#define ADC_ExternalTrigInjecConvEvent_8              ((uint16_t)0x0020)  /*!<  ADC external trigger for injected conversion event 8 */
#define ADC_ExternalTrigInjecConvEvent_9              ((uint16_t)0x0024)  /*!<  ADC external trigger for injected conversion event 9 */
#define ADC_ExternalTrigInjecConvEvent_10             ((uint16_t)0x0028)  /*!<  ADC external trigger for injected conversion event 10 */
#define ADC_ExternalTrigInjecConvEvent_11             ((uint16_t)0x002C)  /*!<  ADC external trigger for injected conversion event 11 */
#define ADC_ExternalTrigInjecConvEvent_12             ((uint16_t)0x0030)  /*!<  ADC external trigger for injected conversion event 12 */
#define ADC_ExternalTrigInjecConvEvent_13             ((uint16_t)0x0034)  /*!<  ADC external trigger for injected conversion event 13 */
#define ADC_ExternalTrigInjecConvEvent_14             ((uint16_t)0x0038)  /*!<  ADC external trigger for injected conversion event 14 */
#define ADC_ExternalTrigInjecConvEvent_15             ((uint16_t)0x003C)  /*!<  ADC external trigger for injected conversion event 15 */

#define IS_ADC_EXT_INJEC_TRIG(INJTRIG) (((INJTRIG) == ADC_ExternalTrigInjecConvEvent_0) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_1) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_2) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_3) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_5) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_6) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_7) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_8) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_9) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_10) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_11) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_12) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_13) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_14) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_15))
/**
  * @}
  */
/** @defgroup ADC_data_align 
  * @{
  */

#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)  /*!<  ADC Data alignment right */
#define ADC_DataAlign_Left                         ((uint32_t)0x00000020)  /*!<  ADC Data alignment left */
#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */

/** @defgroup ADC_channels 
  * @{
  */

#define ADC_Channel_1                               ((uint8_t)0x01)    /*!<  ADC Channel 1 */
#define ADC_Channel_2                               ((uint8_t)0x02)    /*!<  ADC Channel 2 */
#define ADC_Channel_3                               ((uint8_t)0x03)    /*!<  ADC Channel 3 */
#define ADC_Channel_4                               ((uint8_t)0x04)    /*!<  ADC Channel 4 */
#define ADC_Channel_5                               ((uint8_t)0x05)    /*!<  ADC Channel 5 */
#define ADC_Channel_6                               ((uint8_t)0x06)    /*!<  ADC Channel 6 */
#define ADC_Channel_7                               ((uint8_t)0x07)    /*!<  ADC Channel 7 */
#define ADC_Channel_8                               ((uint8_t)0x08)    /*!<  ADC Channel 8 */
#define ADC_Channel_9                               ((uint8_t)0x09)    /*!<  ADC Channel 9 */
#define ADC_Channel_10                              ((uint8_t)0x0A)    /*!<  ADC Channel 10 */
#define ADC_Channel_11                              ((uint8_t)0x0B)    /*!<  ADC Channel 11 */
#define ADC_Channel_12                              ((uint8_t)0x0C)    /*!<  ADC Channel 12 */
#define ADC_Channel_13                              ((uint8_t)0x0D)    /*!<  ADC Channel 13 */
#define ADC_Channel_14                              ((uint8_t)0x0E)    /*!<  ADC Channel 14 */
#define ADC_Channel_15                              ((uint8_t)0x0F)    /*!<  ADC Channel 15 */
#define ADC_Channel_16                              ((uint8_t)0x10)    /*!<  ADC Channel 16 */
#define ADC_Channel_17                              ((uint8_t)0x11)    /*!<  ADC Channel 17 */
#define ADC_Channel_18                              ((uint8_t)0x12)    /*!<  ADC Channel 18 */

#define ADC_Channel_TempSensor                      ((uint8_t)ADC_Channel_16)
#define ADC_Channel_Vrefint                         ((uint8_t)ADC_Channel_18)
#define ADC_Channel_Vbat                            ((uint8_t)ADC_Channel_17)

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_1)  || \
                                 ((CHANNEL) == ADC_Channel_2)  || \
                                 ((CHANNEL) == ADC_Channel_3)  || \
                                 ((CHANNEL) == ADC_Channel_4)  || \
                                 ((CHANNEL) == ADC_Channel_5)  || \
                                 ((CHANNEL) == ADC_Channel_6)  || \
                                 ((CHANNEL) == ADC_Channel_7)  || \
                                 ((CHANNEL) == ADC_Channel_8)  || \
                                 ((CHANNEL) == ADC_Channel_9)  || \
                                 ((CHANNEL) == ADC_Channel_10) || \
                                 ((CHANNEL) == ADC_Channel_11) || \
                                 ((CHANNEL) == ADC_Channel_12) || \
                                 ((CHANNEL) == ADC_Channel_13) || \
                                 ((CHANNEL) == ADC_Channel_14) || \
                                 ((CHANNEL) == ADC_Channel_15) || \
                                 ((CHANNEL) == ADC_Channel_16) || \
                                 ((CHANNEL) == ADC_Channel_17) || \
                                 ((CHANNEL) == ADC_Channel_18))
#define IS_ADC_DIFFCHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_1)  || \
                                     ((CHANNEL) == ADC_Channel_2)  || \
                                     ((CHANNEL) == ADC_Channel_3)  || \
                                     ((CHANNEL) == ADC_Channel_4)  || \
                                     ((CHANNEL) == ADC_Channel_5)  || \
                                     ((CHANNEL) == ADC_Channel_6)  || \
                                     ((CHANNEL) == ADC_Channel_7)  || \
                                     ((CHANNEL) == ADC_Channel_8)  || \
                                     ((CHANNEL) == ADC_Channel_9)  || \
                                     ((CHANNEL) == ADC_Channel_10) || \
                                     ((CHANNEL) == ADC_Channel_11) || \
                                     ((CHANNEL) == ADC_Channel_12) || \
                                     ((CHANNEL) == ADC_Channel_13) || \
                                     ((CHANNEL) == ADC_Channel_14))
/**
  * @}
  */

/** @defgroup ADC_mode 
  * @{
  */    
#define ADC_Mode_Independent                  ((uint32_t)0x00000000) /*!<  ADC independent mode */
#define ADC_Mode_CombRegSimulInjSimul         ((uint32_t)0x00000001) /*!<  ADC multi ADC mode: Combined Regular simultaneous injected simultaneous mode */
#define ADC_Mode_CombRegSimulAltTrig          ((uint32_t)0x00000002) /*!<  ADC multi ADC mode: Combined Regular simultaneous Alternate trigger mode */
#define ADC_Mode_InjSimul                     ((uint32_t)0x00000005) /*!<  ADC multi ADC mode: Injected simultaneous mode */
#define ADC_Mode_RegSimul                     ((uint32_t)0x00000006) /*!<  ADC multi ADC mode: Regular simultaneous mode */
#define ADC_Mode_Interleave                   ((uint32_t)0x00000007) /*!<  ADC multi ADC mode: Interleave mode */
#define ADC_Mode_AltTrig                      ((uint32_t)0x00000009) /*!<  ADC multi ADC mode: Alternate Trigger mode */

#define IS_ADC_MODE(MODE) (((MODE) == ADC_Mode_Independent) || \
                           ((MODE) == ADC_Mode_CombRegSimulInjSimul) || \
                           ((MODE) == ADC_Mode_CombRegSimulAltTrig) || \
                           ((MODE) == ADC_Mode_InjSimul) || \
                           ((MODE) == ADC_Mode_RegSimul) || \
                           ((MODE) == ADC_Mode_Interleave) || \
                           ((MODE) == ADC_Mode_AltTrig))
                                     
/**
  * @}
  */

/** @defgroup ADC_Clock 
  * @{
  */ 
#define ADC_Clock_AsynClkMode                  ((uint32_t)0x00000000)   /*!< ADC Asynchronous clock mode */
#define ADC_Clock_SynClkModeDiv1               ((uint32_t)0x00010000)   /*!< Synchronous clock mode divided by 1 */
#define ADC_Clock_SynClkModeDiv2               ((uint32_t)0x00020000)   /*!<  Synchronous clock mode divided by 2 */
#define ADC_Clock_SynClkModeDiv4               ((uint32_t)0x00030000)   /*!<  Synchronous clock mode divided by 4 */
#define IS_ADC_CLOCKMODE(CLOCK) (((CLOCK) == ADC_Clock_AsynClkMode) ||\
        ((CLOCK) == ADC_Clock_SynClkModeDiv1) ||\
        ((CLOCK) == ADC_Clock_SynClkModeDiv2)||\
        ((CLOCK) == ADC_Clock_SynClkModeDiv4))
/**
  * @}
  */
/** @defgroup ADC_Direct_memory_access_mode_for_multi_mode 
  * @{
  */ 
#define ADC_DMAAccessMode_Disabled      ((uint32_t)0x00000000)     /*!<  DMA mode disabled */
#define ADC_DMAAccessMode_1             ((uint32_t)0x00008000)     /*!<  DMA mode enabled for 12 and 10-bit resolution (6 bit) */
#define ADC_DMAAccessMode_2             ((uint32_t)0x0000C000)     /*!<  DMA mode enabled for 8 and 6-bit resolution (8bit) */
#define IS_ADC_DMA_ACCESS_MODE(MODE) (((MODE) == ADC_DMAAccessMode_Disabled) || \
                                      ((MODE) == ADC_DMAAccessMode_1) || \
                                      ((MODE) == ADC_DMAAccessMode_2))
                                     
/**
  * @}
  */
/** @defgroup ADC_sampling_time 
  * @{
  */

#define ADC_SampleTime_1Cycles5                    ((uint8_t)0x00)   /*!<  ADC sampling time 1.5 cycle */
#define ADC_SampleTime_2Cycles5                    ((uint8_t)0x01)   /*!<  ADC sampling time 2.5 cycles */
#define ADC_SampleTime_4Cycles5                    ((uint8_t)0x02)   /*!<  ADC sampling time 4.5 cycles */
#define ADC_SampleTime_7Cycles5                    ((uint8_t)0x03)   /*!<  ADC sampling time 7.5 cycles */
#define ADC_SampleTime_19Cycles5                   ((uint8_t)0x04)   /*!<  ADC sampling time 19.5 cycles */
#define ADC_SampleTime_61Cycles5                   ((uint8_t)0x05)   /*!<  ADC sampling time 61.5 cycles */
#define ADC_SampleTime_181Cycles5                  ((uint8_t)0x06)   /*!<  ADC sampling time 181.5 cycles */
#define ADC_SampleTime_601Cycles5                  ((uint8_t)0x07)   /*!<  ADC sampling time 601.5 cycles */
#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SampleTime_1Cycles5) || \
                                  ((TIME) == ADC_SampleTime_2Cycles5) || \
                                  ((TIME) == ADC_SampleTime_4Cycles5) || \
                                  ((TIME) == ADC_SampleTime_7Cycles5) || \
                                  ((TIME) == ADC_SampleTime_19Cycles5) || \
                                  ((TIME) == ADC_SampleTime_61Cycles5) || \
                                  ((TIME) == ADC_SampleTime_181Cycles5) || \
                                  ((TIME) == ADC_SampleTime_601Cycles5))
/**
  * @}
  */

/** @defgroup ADC_injected_Channel_selection 
  * @{
  */

#define ADC_InjectedChannel_1                       ADC_Channel_1        /*!<  ADC Injected channel 1 */
#define ADC_InjectedChannel_2                       ADC_Channel_2        /*!<  ADC Injected channel 2 */
#define ADC_InjectedChannel_3                       ADC_Channel_3        /*!<  ADC Injected channel 3 */
#define ADC_InjectedChannel_4                       ADC_Channel_4        /*!<  ADC Injected channel 4 */
#define ADC_InjectedChannel_5                       ADC_Channel_5        /*!<  ADC Injected channel 5 */
#define ADC_InjectedChannel_6                       ADC_Channel_6        /*!<  ADC Injected channel 6 */
#define ADC_InjectedChannel_7                       ADC_Channel_7        /*!<  ADC Injected channel 7 */
#define ADC_InjectedChannel_8                       ADC_Channel_8        /*!<  ADC Injected channel 8 */
#define ADC_InjectedChannel_9                       ADC_Channel_9        /*!<  ADC Injected channel 9 */
#define ADC_InjectedChannel_10                      ADC_Channel_10       /*!<  ADC Injected channel 10 */
#define ADC_InjectedChannel_11                      ADC_Channel_11       /*!<  ADC Injected channel 11 */
#define ADC_InjectedChannel_12                      ADC_Channel_12       /*!<  ADC Injected channel 12 */
#define ADC_InjectedChannel_13                      ADC_Channel_13       /*!<  ADC Injected channel 13 */
#define ADC_InjectedChannel_14                      ADC_Channel_14       /*!<  ADC Injected channel 14 */
#define ADC_InjectedChannel_15                      ADC_Channel_15       /*!<  ADC Injected channel 15 */
#define ADC_InjectedChannel_16                      ADC_Channel_16       /*!<  ADC Injected channel 16 */
#define ADC_InjectedChannel_17                      ADC_Channel_17       /*!<  ADC Injected channel 17 */
#define ADC_InjectedChannel_18                      ADC_Channel_18       /*!<  ADC Injected channel 18 */

#define IS_ADC_INJECTED_CHANNEL(CHANNEL) (((CHANNEL) == ADC_InjectedChannel_1) || \
                                          ((CHANNEL) == ADC_InjectedChannel_2) || \
                                          ((CHANNEL) == ADC_InjectedChannel_3) || \
                                          ((CHANNEL) == ADC_InjectedChannel_4) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_5) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_6) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_7) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_8) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_9) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_10) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_11) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_12) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_13) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_14) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_15) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_16) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_17) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_18))
/**
  * @}
  */

/** @defgroup ADC_injected_Sequence_selection 
  * @{
  */

#define ADC_InjectedSequence_1                       ADC_Channel_1        /*!<  ADC Injected sequence 1 */
#define ADC_InjectedSequence_2                       ADC_Channel_2        /*!<  ADC Injected sequence 2 */
#define ADC_InjectedSequence_3                       ADC_Channel_3        /*!<  ADC Injected sequence 3 */
#define ADC_InjectedSequence_4                       ADC_Channel_4        /*!<  ADC Injected sequence 4 */
#define IS_ADC_INJECTED_SEQUENCE(SEQUENCE) (((SEQUENCE) == ADC_InjectedSequence_1) || \
                                            ((SEQUENCE) == ADC_InjectedSequence_2) || \
                                            ((SEQUENCE) == ADC_InjectedSequence_3) || \
                                            ((SEQUENCE) == ADC_InjectedSequence_4))
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_selection 
  * @{
  */

#define ADC_AnalogWatchdog_SingleRegEnable         ((uint32_t)0x00C00000)    /*!<  ADC Analog watchdog single regular mode */
#define ADC_AnalogWatchdog_SingleInjecEnable       ((uint32_t)0x01400000)    /*!<  ADC Analog watchdog single injected mode */
#define ADC_AnalogWatchdog_SingleRegOrInjecEnable  ((uint32_t)0x01C00000)    /*!<  ADC Analog watchdog single regular or injected mode */
#define ADC_AnalogWatchdog_AllRegEnable            ((uint32_t)0x00800000)    /*!<  ADC Analog watchdog all regular mode */
#define ADC_AnalogWatchdog_AllInjecEnable          ((uint32_t)0x01000000)    /*!<  ADC Analog watchdog all injected mode */
#define ADC_AnalogWatchdog_AllRegAllInjecEnable    ((uint32_t)0x01800000)    /*!<  ADC Analog watchdog all regular and all injected mode */
#define ADC_AnalogWatchdog_None                    ((uint32_t)0x00000000)    /*!<  ADC Analog watchdog off */

#define IS_ADC_ANALOG_WATCHDOG(WATCHDOG) (((WATCHDOG) == ADC_AnalogWatchdog_SingleRegEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleRegOrInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegAllInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_None))
/**
  * @}
  */

/** @defgroup ADC_Calibration_Mode_definition 
  * @{
  */
#define ADC_CalibrationMode_Single         ((uint32_t)0x00000000)   /*!<  ADC Calibration for single ended channel */
#define ADC_CalibrationMode_Differential   ((uint32_t)0x40000000)   /*!<  ADC Calibration for differential channel */

#define IS_ADC_CALIBRATION_MODE(MODE) (((MODE) == ADC_CalibrationMode_Single) ||((MODE) == ADC_CalibrationMode_Differential))

/**
  * @}
  */

/** @defgroup ADC_DMA_Mode_definition 
  * @{
  */
#define ADC_DMAMode_OneShot     ((uint32_t)0x00000000)   /*!<  ADC DMA Oneshot mode */
#define ADC_DMAMode_Circular   ((uint32_t)0x00000002)   /*!<  ADC DMA circular mode */

#define IS_ADC_DMA_MODE(MODE) (((MODE) == ADC_DMAMode_OneShot) || ((MODE) == ADC_DMAMode_Circular))
/**
  * @}
  */

/** @defgroup ADC_interrupts_definition 
  * @{
  */

#define ADC_IT_RDY           ((uint16_t)0x0001)  /*!< ADC Ready (ADRDY) interrupt source */
#define ADC_IT_EOSMP         ((uint16_t)0x0002)  /*!< ADC End of Sampling interrupt source */
#define ADC_IT_EOC           ((uint16_t)0x0004)  /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_EOS           ((uint16_t)0x0008)  /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IT_OVR           ((uint16_t)0x0010)  /*!< ADC overrun interrupt source */
#define ADC_IT_JEOC          ((uint16_t)0x0020)  /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IT_JEOS          ((uint16_t)0x0040)  /*!< ADC End of Injected sequence of Conversions interrupt source */
#define ADC_IT_AWD1          ((uint16_t)0x0080)  /*!< ADC Analog watchdog 1 interrupt source */
#define ADC_IT_AWD2          ((uint16_t)0x0100)  /*!< ADC Analog watchdog 2 interrupt source */
#define ADC_IT_AWD3          ((uint16_t)0x0200)  /*!< ADC Analog watchdog 3 interrupt source */
#define ADC_IT_JQOVF         ((uint16_t)0x0400)  /*!< ADC Injected Context Queue Overflow interrupt source */


#define IS_ADC_IT(IT) ((((IT) & (uint16_t)0xF800) == 0x0000) && ((IT) != 0x0000))

#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_RDY) || ((IT) == ADC_IT_EOSMP) || \
                           ((IT) == ADC_IT_EOC) || ((IT) == ADC_IT_EOS) || \
                           ((IT) == ADC_IT_OVR) || ((IT) == ADC_IT_EOS) || \
                           ((IT) == ADC_IT_JEOS) || ((IT) == ADC_IT_AWD1) || \
                           ((IT) == ADC_IT_AWD2) || ((IT) == ADC_IT_AWD3) || \
                           ((IT) == ADC_IT_JQOVF))
/**
  * @}
  */

/** @defgroup ADC_flags_definition 
  * @{
  */
  
#define ADC_FLAG_RDY           ((uint16_t)0x0001)  /*!< ADC Ready (ADRDY) flag */
#define ADC_FLAG_EOSMP         ((uint16_t)0x0002)  /*!< ADC End of Sampling flag */
#define ADC_FLAG_EOC           ((uint16_t)0x0004)  /*!< ADC End of Regular Conversion flag */
#define ADC_FLAG_EOS           ((uint16_t)0x0008)  /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_FLAG_OVR           ((uint16_t)0x0010)  /*!< ADC overrun flag */
#define ADC_FLAG_JEOC          ((uint16_t)0x0020)  /*!< ADC End of Injected Conversion flag */
#define ADC_FLAG_JEOS          ((uint16_t)0x0040)  /*!< ADC End of Injected sequence of Conversions flag */
#define ADC_FLAG_AWD1          ((uint16_t)0x0080)  /*!< ADC Analog watchdog 1 flag */
#define ADC_FLAG_AWD2          ((uint16_t)0x0100)  /*!< ADC Analog watchdog 2 flag */
#define ADC_FLAG_AWD3          ((uint16_t)0x0200)  /*!< ADC Analog watchdog 3 flag */
#define ADC_FLAG_JQOVF         ((uint16_t)0x0400)  /*!< ADC Injected Context Queue Overflow flag */

#define IS_ADC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xF800) == 0x0000) && ((FLAG) != 0x0000))
#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_RDY) || ((FLAG) == ADC_FLAG_EOSMP) || \
                               ((FLAG) == ADC_FLAG_EOC) || ((FLAG) == ADC_FLAG_EOS) || \
                               ((FLAG) == ADC_FLAG_OVR) || ((FLAG) == ADC_FLAG_JEOC) || \
                               ((FLAG) == ADC_FLAG_JEOS) || ((FLAG) == ADC_FLAG_AWD1) || \
                               ((FLAG) == ADC_FLAG_AWD2) || ((FLAG) == ADC_FLAG_AWD3) || \
                               ((FLAG) == ADC_FLAG_JQOVF))
/**
  * @}
  */

/** @defgroup ADC_Common_flags_definition 
  * @{
  */
  
#define ADC_FLAG_MSTRDY           ((uint32_t)0x00000001)  /*!< ADC Master Ready (ADRDY) flag */
#define ADC_FLAG_MSTEOSMP         ((uint32_t)0x00000002)  /*!< ADC Master End of Sampling flag */
#define ADC_FLAG_MSTEOC           ((uint32_t)0x00000004)  /*!< ADC Master End of Regular Conversion flag */
#define ADC_FLAG_MSTEOS           ((uint32_t)0x00000008)  /*!< ADC Master End of Regular sequence of Conversions flag */
#define ADC_FLAG_MSTOVR           ((uint32_t)0x00000010)  /*!< ADC Master overrun flag */
#define ADC_FLAG_MSTJEOC          ((uint32_t)0x00000020)  /*!< ADC Master End of Injected Conversion flag */
#define ADC_FLAG_MSTJEOS          ((uint32_t)0x00000040)  /*!< ADC Master End of Injected sequence of Conversions flag */
#define ADC_FLAG_MSTAWD1          ((uint32_t)0x00000080)  /*!< ADC Master Analog watchdog 1 flag */
#define ADC_FLAG_MSTAWD2          ((uint32_t)0x00000100)  /*!< ADC Master Analog watchdog 2 flag */
#define ADC_FLAG_MSTAWD3          ((uint32_t)0x00000200)  /*!< ADC Master Analog watchdog 3 flag */
#define ADC_FLAG_MSTJQOVF         ((uint32_t)0x00000400)  /*!< ADC Master Injected Context Queue Overflow flag */

#define ADC_FLAG_SLVRDY           ((uint32_t)0x00010000)  /*!< ADC Slave Ready (ADRDY) flag */
#define ADC_FLAG_SLVEOSMP         ((uint32_t)0x00020000)  /*!< ADC Slave End of Sampling flag */
#define ADC_FLAG_SLVEOC           ((uint32_t)0x00040000)  /*!< ADC Slave End of Regular Conversion flag */
#define ADC_FLAG_SLVEOS           ((uint32_t)0x00080000)  /*!< ADC Slave End of Regular sequence of Conversions flag */
#define ADC_FLAG_SLVOVR           ((uint32_t)0x00100000)  /*!< ADC Slave overrun flag */
#define ADC_FLAG_SLVJEOC          ((uint32_t)0x00200000)  /*!< ADC Slave End of Injected Conversion flag */
#define ADC_FLAG_SLVJEOS          ((uint32_t)0x00400000)  /*!< ADC Slave End of Injected sequence of Conversions flag */
#define ADC_FLAG_SLVAWD1          ((uint32_t)0x00800000)  /*!< ADC Slave Analog watchdog 1 flag */
#define ADC_FLAG_SLVAWD2          ((uint32_t)0x01000000)  /*!< ADC Slave Analog watchdog 2 flag */
#define ADC_FLAG_SLVAWD3          ((uint32_t)0x02000000)  /*!< ADC Slave Analog watchdog 3 flag */
#define ADC_FLAG_SLVJQOVF         ((uint32_t)0x04000000)  /*!< ADC Slave Injected Context Queue Overflow flag */

#define IS_ADC_CLEAR_COMMONFLAG(FLAG) ((((FLAG) & (uint32_t)0xF800F800) == 0x0000) && ((FLAG) != 0x00000000))
#define IS_ADC_GET_COMMONFLAG(FLAG) (((FLAG) == ADC_FLAG_MSTRDY) || ((FLAG) == ADC_FLAG_MSTEOSMP) || \
                                     ((FLAG) == ADC_FLAG_MSTEOC) || ((FLAG) == ADC_FLAG_MSTEOS) || \
                                     ((FLAG) == ADC_FLAG_MSTOVR) || ((FLAG) == ADC_FLAG_MSTEOS) || \
                                     ((FLAG) == ADC_FLAG_MSTJEOS) || ((FLAG) == ADC_FLAG_MSTAWD1) || \
                                     ((FLAG) == ADC_FLAG_MSTAWD2) || ((FLAG) == ADC_FLAG_MSTAWD3) || \
                                     ((FLAG) == ADC_FLAG_MSTJQOVF) || \
                                     ((FLAG) == ADC_FLAG_SLVRDY) || ((FLAG) == ADC_FLAG_SLVEOSMP) || \
                                     ((FLAG) == ADC_FLAG_SLVEOC) || ((FLAG) == ADC_FLAG_SLVEOS) || \
                                     ((FLAG) == ADC_FLAG_SLVOVR) || ((FLAG) == ADC_FLAG_SLVEOS) || \
                                     ((FLAG) == ADC_FLAG_SLVJEOS) || ((FLAG) == ADC_FLAG_SLVAWD1) || \
                                     ((FLAG) == ADC_FLAG_SLVAWD2) || ((FLAG) == ADC_FLAG_SLVAWD3) || \
                                     ((FLAG) == ADC_FLAG_SLVJQOVF))
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

/** @defgroup ADC_injected_offset 
  * @{
  */

#define IS_ADC_OFFSET(OFFSET) ((OFFSET) <= 0xFFF)   

/**
  * @}
  */

/** @defgroup ADC_injected_length 
  * @{
  */

#define IS_ADC_INJECTED_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))

/**
  * @}
  */


/** @defgroup ADC_regular_length 
  * @{
  */

#define IS_ADC_REGULAR_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10)) 
/**
  * @}
  */

/** @defgroup ADC_regular_discontinuous_mode_number 
  * @{
  */

#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER) (((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))  

/**
  * @}
  */

/** @defgroup ADC_two_sampling_delay_number 
  * @{
  */
#define IS_ADC_TWOSAMPLING_DELAY(DELAY)  (((DELAY) <= 0xF))

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
void ADC_InjectedInit(ADC_TypeDef* ADCx, ADC_InjectedInitTypeDef* ADC_InjectedInitStruct); 
void ADC_InjectedStructInit(ADC_InjectedInitTypeDef* ADC_InjectedInitStruct);
void ADC_CommonInit(ADC_TypeDef* ADCx, ADC_CommonInitTypeDef* ADC_CommonInitStruct);    
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct);

void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_StartCalibration(ADC_TypeDef* ADCx); 
uint32_t ADC_GetCalibrationValue(ADC_TypeDef* ADCx);
void ADC_SetCalibrationValue(ADC_TypeDef* ADCx, uint32_t ADC_Calibration);
void ADC_SelectCalibrationMode(ADC_TypeDef* ADCx, uint32_t ADC_CalibrationMode); 
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_DisableCmd(ADC_TypeDef* ADCx); 
FlagStatus ADC_GetDisableCmdStatus(ADC_TypeDef* ADCx); 
void ADC_VoltageRegulatorCmd(ADC_TypeDef* ADCx, FunctionalState NewState);  
void ADC_SelectDifferentialMode(ADC_TypeDef* ADCx, uint8_t ADC_Channel, FunctionalState NewState);
void ADC_SelectQueueOfContextMode(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_AutoDelayCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 

/* Analog Watchdog configuration functions ************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog); 
void ADC_AnalogWatchdog1ThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);  
void ADC_AnalogWatchdog2ThresholdsConfig(ADC_TypeDef* ADCx, uint8_t HighThreshold, uint8_t LowThreshold);  
void ADC_AnalogWatchdog3ThresholdsConfig(ADC_TypeDef* ADCx, uint8_t HighThreshold, uint8_t LowThreshold);  
void ADC_AnalogWatchdog1SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel); 
void ADC_AnalogWatchdog2SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);   
void ADC_AnalogWatchdog3SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel); 

/* Temperature Sensor, Vrefint and Vbat management function */
void ADC_TempSensorCmd(ADC_TypeDef* ADCx, FunctionalState NewState);  
void ADC_VrefintCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_VbatCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 

/* Channels Configuration functions ***********************************/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_RegularChannelSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t SequencerLength); 
void ADC_ExternalTriggerConfig(ADC_TypeDef* ADCx, uint16_t ADC_ExternalTrigConvEvent, uint16_t ADC_ExternalTrigEventEdge); 
 
void ADC_StartConversion(ADC_TypeDef* ADCx);
FlagStatus ADC_GetStartConversionStatus(ADC_TypeDef* ADCx);
void ADC_StopConversion(ADC_TypeDef* ADCx);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number);  
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);
uint32_t ADC_GetDualModeConversionValue(ADC_TypeDef* ADCx);

void ADC_SetChannelOffset1(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset);  
void ADC_SetChannelOffset2(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset);  
void ADC_SetChannelOffset3(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset);  
void ADC_SetChannelOffset4(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset);  

void ADC_ChannelOffset1Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);  
void ADC_ChannelOffset2Cmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_ChannelOffset3Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);  
void ADC_ChannelOffset4Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);  

/* Regular Channels DMA Configuration functions *******************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_DMAConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMAMode);  

/* Injected channels Configuration functions **********************************/
void ADC_InjectedChannelSampleTimeConfig(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint8_t ADC_SampleTime);
void ADC_StartInjectedConversion(ADC_TypeDef* ADCx); 
FlagStatus ADC_GetStartInjectedConversionStatus(ADC_TypeDef* ADCx); 
void ADC_StopInjectedConversion(ADC_TypeDef* ADCx); 
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel);  

/* ADC Dual Modes Configuration functions *************************************/
FlagStatus ADC_GetCommonFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearCommonFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG); 

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState); 
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG); 
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT);  
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT);  

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_ADC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_can.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the CAN firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_CAN_H
#define __STM32F30x_CAN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup CAN
  * @{
  */

/* Exported types ------------------------------------------------------------*/

#define IS_CAN_ALL_PERIPH(PERIPH) (((PERIPH) == CAN1))

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
#define  CAN_ErrorCode_StuffErr        ((uint8_t)0x10) /*!< Stuff Error */ 
#define  CAN_ErrorCode_FormErr         ((uint8_t)0x20) /*!< Form Error */ 
#define  CAN_ErrorCode_ACKErr          ((uint8_t)0x30) /*!< Acknowledgment Error */ 
#define  CAN_ErrorCode_BitRecessiveErr ((uint8_t)0x40) /*!< Bit Recessive Error */ 
#define  CAN_ErrorCode_BitDominantErr  ((uint8_t)0x50) /*!< Bit Dominant Error */ 
#define  CAN_ErrorCode_CRCErr          ((uint8_t)0x60) /*!< CRC Error  */ 
#define  CAN_ErrorCode_SoftwareSetErr  ((uint8_t)0x70) /*!< Software Set Error */ 
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

#endif /* __STM32F30x_CAN_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_comp.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the COMP firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_COMP_H
#define __STM32F30x_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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

  uint32_t COMP_NonInvertingInput;  /*!< Selects the non inverting input of the comparator.
                                         This parameter can be a value of @ref COMP_NonInvertingInput */

  uint32_t COMP_Output;             /*!< Selects the output redirection of the comparator.
                                          This parameter can be a value of @ref COMP_Output */

  uint32_t COMP_BlankingSrce;      /*!< Selects the output blanking source of the comparator.
                                          This parameter can be a value of @ref COMP_BlankingSrce */

  uint32_t COMP_OutputPol;         /*!< Selects the output polarity of the comparator.
                                          This parameter can be a value of @ref COMP_OutputPoloarity */

  uint32_t COMP_Hysteresis;        /*!< Selects the hysteresis voltage of the comparator.
                                          This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t COMP_Mode;              /*!< Selects the operating mode of the comparator
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
#define COMP_Selection_COMP2                    ((uint32_t)0x00000004) /*!< COMP2 Selection */
#define COMP_Selection_COMP3                    ((uint32_t)0x00000008) /*!< COMP3 Selection */
#define COMP_Selection_COMP4                    ((uint32_t)0x0000000C) /*!< COMP4 Selection */
#define COMP_Selection_COMP5                    ((uint32_t)0x00000010) /*!< COMP5 Selection */
#define COMP_Selection_COMP6                    ((uint32_t)0x00000014) /*!< COMP6 Selection */
#define COMP_Selection_COMP7                    ((uint32_t)0x00000018) /*!< COMP7 Selection */

#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP_Selection_COMP1) || \
                                    ((PERIPH) == COMP_Selection_COMP2) || \
                                    ((PERIPH) == COMP_Selection_COMP3) || \
                                    ((PERIPH) == COMP_Selection_COMP4) || \
                                    ((PERIPH) == COMP_Selection_COMP5) || \
                                    ((PERIPH) == COMP_Selection_COMP6) || \
                                    ((PERIPH) == COMP_Selection_COMP7))
 
/**
  * @}
  */ 

/** @defgroup COMP_InvertingInput
  * @{
  */

#define COMP_InvertingInput_1_4VREFINT          ((uint32_t)0x00000000) /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_1_2VREFINT          COMP_CSR_COMPxINSEL_0  /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_3_4VREFINT          COMP_CSR_COMPxINSEL_1  /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_VREFINT             ((uint32_t)0x00000030) /*!< VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_DAC1OUT1            COMP_CSR_COMPxINSEL_2  /*!< DAC1_OUT1 (PA4) connected to comparator inverting input */
#define COMP_InvertingInput_DAC1OUT2            ((uint32_t)0x00000050) /*!< DAC1_OUT2 (PA5) connected to comparator inverting input */

#define COMP_InvertingInput_IO1                 ((uint32_t)0x00000060) /*!< I/O1 (PA0 for COMP1, PA2 for COMP2, PD15 for COMP3, 
                                                                            PE8 for COMP4, PD13 for COMP5, PD10 for COMP6,
                                                                            PC0 for COMP7) connected to comparator inverting input */

#define COMP_InvertingInput_IO2                 COMP_CSR_COMPxINSEL    /*!< I/O2 (PB12 for COMP3, PB2 for COMP4, PB10 for COMP5,
                                                                            PB15 for COMP6) connected to comparator inverting input. 
                                      It is valid only for STM32F303xC devices */

#define COMP_InvertingInput_DAC2OUT1            COMP_CSR_COMPxINSEL_3  /*!< DAC2_OUT1 (PA6) connected to comparator inverting input */

#define IS_COMP_INVERTING_INPUT(INPUT) (((INPUT) == COMP_InvertingInput_1_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_1_2VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_3_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_VREFINT)    || \
                                        ((INPUT) == COMP_InvertingInput_DAC1OUT1)   || \
                                        ((INPUT) == COMP_InvertingInput_DAC1OUT2)   || \
                                        ((INPUT) == COMP_InvertingInput_IO1)        || \
                                        ((INPUT) == COMP_InvertingInput_IO2)        || \
                                        ((INPUT) == COMP_InvertingInput_DAC2OUT1))
/**
  * @}
  */ 

/** @defgroup COMP_NonInvertingInput
  * @{
  */

#define COMP_NonInvertingInput_IO1                 ((uint32_t)0x00000000) /*!< I/O1 (PA1 for COMP1, PA7 for COMP2, PB14 for COMP3, 
                                                                               PB0 for COMP4, PD12 for COMP5, PD11 for COMP6,
                                                                               PA0 for COMP7) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO2                 COMP_CSR_COMPxNONINSEL /*!< I/O2 (PA3 for COMP2, PD14 for COMP3, PE7 for COMP4, PB13 for COMP5,
                                                                               PB11 for COMP6, PC1 for COMP7) connected to comparator non inverting input */

#define IS_COMP_NONINVERTING_INPUT(INPUT) (((INPUT) == COMP_NonInvertingInput_IO1) || \
                                           ((INPUT) == COMP_NonInvertingInput_IO2))
/**
  * @}
  */ 

/** @defgroup COMP_Output
  * @{
  */

#define COMP_Output_None                            ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */

/* Output Redirection common for all comparators COMP1...COMP7 */
#define COMP_Output_TIM1BKIN                        COMP_CSR_COMPxOUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_Output_TIM1BKIN2                       ((uint32_t)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
#define COMP_Output_TIM8BKIN                        ((uint32_t)0x00000C00)   /*!< COMP output connected to TIM8 Break Input (BKIN) */
#define COMP_Output_TIM8BKIN2                       ((uint32_t)0x00001000)   /*!< COMP output connected to TIM8 Break Input 2 (BKIN2) */
#define COMP_Output_TIM1BKIN2_TIM8BKIN2             ((uint32_t)0x00001400)   /*!< COMP output connected to TIM1 Break Input 2 and TIM8 Break Input 2 */
#define COMP_Output_TIM20BKIN                       ((uint32_t)0x00003000)   /*!< COMP output connected to TIM20 Break Input (BKIN) */
#define COMP_Output_TIM20BKIN2                      ((uint32_t)0x00003400)  /*!< COMP output connected to TIM20 Break Input 2 (BKIN2) */
#define COMP_Output_TIM1BKIN2_TIM8BKIN2_TIM20BKIN2  ((uint32_t)0x00001400)   /*!< COMP output connected to TIM1 Break Input 2, TIM8 Break Input 2 and TIM20 Break Input2 */

/* Output Redirection common for COMP1 and COMP2 */
#define COMP_Output_TIM1OCREFCLR                    ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_Output_TIM1IC1                         ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_Output_TIM2IC4                         ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_Output_TIM2OCREFCLR                    ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM3IC1                         ((uint32_t)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_Output_TIM3OCREFCLR                    ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */

/* Output Redirection specific to COMP2 */
#define COMP_Output_HRTIM1_FLT6                     ((uint32_t)0x00003000)   /*!< COMP output connected to HRTIM1 FLT6 */
#define COMP_Output_HRTIM1_EE1_2                    ((uint32_t)0x00003400)   /*!< COMP output connected to HRTIM1 EE1_2*/
#define COMP_Output_HRTIM1_EE6_2                    ((uint32_t)0x00003800)   /*!< COMP output connected to HRTIM1 EE6_2 */
#define COMP_Output_TIM20OCREFCLR                   ((uint32_t)0x00003C00)   /*!< COMP output connected to TIM20 OCREF Clear */

/* Output Redirection specific to COMP3 */
#define COMP_Output_TIM4IC1                         ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM4 Input Capture 1 */
#define COMP_Output_TIM3IC2                         ((uint32_t)0x00002000)   /*!< COMP output connected to TIM3 Input Capture 2 */
#define COMP_Output_TIM15IC1                        ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 Input Capture 1 */
#define COMP_Output_TIM15BKIN                       ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM15 Break Input (BKIN) */

/* Output Redirection specific to COMP4 */
#define COMP_Output_TIM3IC3                         ((uint32_t)0x00001800)   /*!< COMP output connected to TIM3 Input Capture 3 */
#define COMP_Output_TIM8OCREFCLR                    ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM8 OCREF Clear */
#define COMP_Output_TIM15IC2                        ((uint32_t)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_Output_TIM4IC2                         ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 2 */
#define COMP_Output_TIM15OCREFCLR                   ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */

#define COMP_Output_HRTIM1_FLT7                     ((uint32_t)0x00003000)   /*!< COMP output connected to HRTIM1 FLT7 */
#define COMP_Output_HRTIM1_EE2_2                    ((uint32_t)0x00003400)   /*!< COMP output connected to HRTIM1 EE2_2*/
#define COMP_Output_HRTIM1_EE7_2                    ((uint32_t)0x00003800)   /*!< COMP output connected to HRTIM1 EE7_2 */

/* Output Redirection specific to COMP5 */
#define COMP_Output_TIM2IC1                         ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 1 */
#define COMP_Output_TIM17IC1                        ((uint32_t)0x00002000)   /*!< COMP output connected to TIM17 Input Capture 1 */
#define COMP_Output_TIM4IC3                         ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 3 */
#define COMP_Output_TIM16BKIN                       ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Break Input (BKIN) */

/* Output Redirection specific to COMP6 */
#define COMP_Output_TIM2IC2                         ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_Output_COMP6TIM2OCREFCLR               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM16OCREFCLR                   ((uint32_t)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_Output_TIM16IC1                        ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */
#define COMP_Output_TIM4IC4                         ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM4 Input Capture 4 */

#define COMP_Output_HRTIM1_FLT8                     ((uint32_t)0x00003000)   /*!< COMP output connected to HRTIM1 FLT8 */
#define COMP_Output_HRTIM1_EE3_2                    ((uint32_t)0x00003400)   /*!< COMP output connected to HRTIM1 EE3_2*/
#define COMP_Output_HRTIM1_EE8_2                    ((uint32_t)0x00003800)   /*!< COMP output connected to HRTIM1 EE8_2 */

/* Output Redirection specific to COMP7 */
#define COMP_Output_TIM2IC3                         ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 3 */
#define COMP_Output_TIM1IC2                         ((uint32_t)0x00002400)   /*!< COMP output connected to TIM1 Input Capture 2 */
#define COMP_Output_TIM17OCREFCLR                   ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_Output_TIM17BKIN                       ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM16 Break Input (BKIN) */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_Output_None)                || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_Output_TIM1IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_TIM2IC4)             || \
                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_COMP6TIM2OCREFCLR)   || \
                                ((OUTPUT) == COMP_Output_TIM3IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM3OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_TIM8BKIN)            || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN2)           || \
                                ((OUTPUT) == COMP_Output_TIM8BKIN2)           || \
                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN2_TIM8BKIN2) || \
                                ((OUTPUT) == COMP_Output_TIM3IC2)             || \
                                ((OUTPUT) == COMP_Output_TIM4IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM15IC1)            || \
                                ((OUTPUT) == COMP_Output_TIM15BKIN)           || \
                                ((OUTPUT) == COMP_Output_TIM8OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_TIM3IC3)             || \
                                ((OUTPUT) == COMP_Output_TIM4IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM15IC1)            || \
                                ((OUTPUT) == COMP_Output_TIM2IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM4IC3)             || \
                                ((OUTPUT) == COMP_Output_TIM16BKIN)           || \
                                ((OUTPUT) == COMP_Output_TIM17IC1)            || \
                                ((OUTPUT) == COMP_Output_TIM2IC2)             || \
                                ((OUTPUT) == COMP_Output_TIM16IC1)            || \
                                ((OUTPUT) == COMP_Output_TIM4IC4)             || \
                                ((OUTPUT) == COMP_Output_TIM16OCREFCLR)       || \
                                ((OUTPUT) == COMP_Output_TIM2IC3)             || \
                                ((OUTPUT) == COMP_Output_TIM1IC2)             || \
                                ((OUTPUT) == COMP_Output_TIM17BKIN)           || \
                                ((OUTPUT) == COMP_Output_TIM17OCREFCLR)       || \
                                ((OUTPUT) == COMP_Output_HRTIM1_FLT6)         || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE1_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE6_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_FLT7)         || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE2_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE7_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_FLT8)         || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE3_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE8_2)        || \
                                ((OUTPUT) == COMP_Output_TIM20BKIN)           || \
                                ((OUTPUT) == COMP_Output_TIM20BKIN2)         || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN2_TIM8BKIN2_TIM20BKIN2)|| \
                                ((OUTPUT) == COMP_Output_TIM20OCREFCLR))
                                
/**
  * @}
  */ 

/** @defgroup COMP_BlankingSrce
  * @{
  */

/* No blanking source can be selected for all comparators */
#define COMP_BlankingSrce_None                   ((uint32_t)0x00000000)    /*!< No blanking source */

/* Blanking source common for COMP1, COMP2, COMP3 and COMP7 */
#define COMP_BlankingSrce_TIM1OC5                COMP_CSR_COMPxBLANKING_0  /*!< TIM1 OC5 selected as blanking source for compartor */

/* Blanking source common for COMP1 and COMP2 */
#define COMP_BlankingSrce_TIM2OC3                COMP_CSR_COMPxBLANKING_1  /*!< TIM2 OC5 selected as blanking source for compartor */

/* Blanking source common for COMP1, COMP2 and COMP5 */
#define COMP_BlankingSrce_TIM3OC3                ((uint32_t)0x000C0000)    /*!< TIM2 OC3 selected as blanking source for compartor */

/* Blanking source common for COMP3 and COMP6 */
#define COMP_BlankingSrce_TIM2OC4                ((uint32_t)0x000C0000)  /*!< TIM2 OC4 selected as blanking source for compartor */

/* Blanking source common for COMP4, COMP5, COMP6 and COMP7 */
#define COMP_BlankingSrce_TIM8OC5                COMP_CSR_COMPxBLANKING_1  /*!< TIM8 OC5 selected as blanking source for compartor */

/* Blanking source for COMP4 */
#define COMP_BlankingSrce_TIM3OC4                COMP_CSR_COMPxBLANKING_0  /*!< TIM3 OC4 selected as blanking source for compartor */
#define COMP_BlankingSrce_TIM15OC1               ((uint32_t)0x000C0000)    /*!< TIM15 OC1 selected as blanking source for compartor */

/* Blanking source common for COMP6 and COMP7 */
#define COMP_BlankingSrce_TIM15OC2               COMP_CSR_COMPxBLANKING_2    /*!< TIM15 OC2 selected as blanking source for compartor */

#define IS_COMP_BLANKING_SOURCE(SOURCE) (((SOURCE) == COMP_BlankingSrce_None)     || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM1OC5)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM2OC3)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM3OC3)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM2OC4)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM8OC5)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM3OC4)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM15OC1) || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM15OC2))
/**
  * @}
  */ 

/** @defgroup COMP_OutputPoloarity
  * @{
  */
#define COMP_OutputPol_NonInverted          ((uint32_t)0x00000000)  /*!< COMP output on GPIO isn't inverted */
#define COMP_OutputPol_Inverted             COMP_CSR_COMPxPOL       /*!< COMP output on GPIO is inverted */

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
#define COMP_Hysteresis_Low                        COMP_CSR_COMPxHYST_0 /*!< Hysteresis level low */
#define COMP_Hysteresis_Medium                     COMP_CSR_COMPxHYST_1 /*!< Hysteresis level medium */
#define COMP_Hysteresis_High                       COMP_CSR_COMPxHYST   /*!< Hysteresis level high */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_Hysteresis_No)     || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Low)    || \
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
#define COMP_Mode_MediumSpeed                   COMP_CSR_COMPxMODE_0  /*!< Medium Speed */
#define COMP_Mode_LowPower                      COMP_CSR_COMPxMODE_1  /*!< Low power mode */
#define COMP_Mode_UltraLowPower                 COMP_CSR_COMPxMODE    /*!< Ultra-low power mode */

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
#define COMP_OutputLevel_High                   COMP_CSR_COMPxOUT
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputLevel_Low                    ((uint32_t)0x00000000)

/**
  * @}
  */ 

/** @defgroup COMP_WindowMode
  * @{
  */
#define IS_COMP_WINDOW(WINDOW)  (((WINDOW) == COMP_Selection_COMP2) || \
                                 ((WINDOW) == COMP_Selection_COMP4) || \
                                 ((WINDOW) == COMP_Selection_COMP6))
/**
  * @}
  */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_DeInit(uint32_t COMP_Selection);

/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct);
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct);
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
void COMP_SwitchCmd(uint32_t COMP_Selection, FunctionalState NewState);
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection);

/* Window mode control function ***********************************************/
void COMP_WindowCmd(uint32_t COMP_Selection, FunctionalState NewState);

/* COMP configuration locking function ****************************************/
void COMP_LockConfig(uint32_t COMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_COMP_H */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_crc.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the CRC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_CRC_H
#define __STM32F30x_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/*!< Includes ----------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
void CRC_PolynomialSizeSelect(uint32_t CRC_PolSize); 
void CRC_ReverseInputDataSelect(uint32_t CRC_ReverseInputData);
void CRC_ReverseOutputDataCmd(FunctionalState NewState);
void CRC_SetInitRegister(uint32_t CRC_InitValue); 
void CRC_SetPolynomial(uint32_t CRC_Pol);

/* CRC computation ************************************************************/
uint32_t CRC_CalcCRC(uint32_t CRC_Data);
uint32_t CRC_CalcCRC16bits(uint16_t CRC_Data);
uint32_t CRC_CalcCRC8bits(uint8_t CRC_Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);

/* Independent register (IDR) access (write/read) *****************************/
void CRC_SetIDRegister(uint8_t CRC_IDValue);
uint8_t CRC_GetIDRegister(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_CRC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_dac.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the DAC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_DAC_H
#define __STM32F30x_DAC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup DAC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
#define DAC_CR_DMAUDRIE                  ((uint32_t)0x00002000)        /*!< DAC channel DMA underrun interrupt enable */

/** 
  * @brief  DAC Init structure definition
  */

typedef struct
{
  uint32_t DAC_Trigger;                      /*!< Specifies the external trigger for the selected DAC channel.
                                                  This parameter can be a value of @ref DAC_trigger_selection */

  uint32_t DAC_WaveGeneration;               /*!< Specifies whether DAC channel noise waves or triangle waves
                                                  are generated, or whether no wave is generated.
                                                  This parameter can be a value of @ref DAC_wave_generation */

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; /*!< Specifies the LFSR mask for noise wave generation or
                                                  the maximum amplitude triangle generation for the DAC channel. 
                                                  This parameter can be a value of @ref DAC_lfsrunmask_triangleamplitude */

  uint32_t DAC_Buffer_Switch;                /*!< Specifies whether the DAC channel output buffer is enabled or disabled or 
                                                  the DAC channel output switch is enabled or disabled.
                                                  This parameter can be a value of @ref DAC_buffer_switch */
}DAC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DAC_Exported_Constants
  * @{
  */

#define IS_DAC_ALL_PERIPH(PERIPH) (((PERIPH) == DAC1) || \
                                   ((PERIPH) == DAC2))

#define IS_DAC_LIST1_PERIPH(PERIPH) (((PERIPH) == DAC1))

/** @defgroup DAC_trigger_selection 
  * @{
  */

#define DAC_Trigger_None                     ((uint32_t)0x00000000) /*!< Conversion is automatic once the DAC1_DHRxxxx register 
                                                                         has been loaded, and not by external trigger */
#define DAC_Trigger_T6_TRGO                  ((uint32_t)0x00000004) /*!< TIM6 TRGO selected as external conversion trigger for DAC1/2 channel1/2 */
#define DAC_Trigger_T3_TRGO                  ((uint32_t)0x0000000C) /*!< TIM3 TRGO selected as external conversion trigger for DAC1/2 channel1/2 */
#define DAC_Trigger_T8_TRGO                  ((uint32_t)0x0000000C) /*!< TIM8 TRGO selected as external conversion trigger for DAC1 channel1/2 */
#define DAC_Trigger_T7_TRGO                  ((uint32_t)0x00000014) /*!< TIM7 TRGO selected as external conversion trigger for DAC1/2 channel1/2 */
#define DAC_Trigger_T15_TRGO                 ((uint32_t)0x0000001C) /*!< TIM15 TRGO selected as external conversion trigger for DAC1/2 channel1/2 */
#define DAC_Trigger_HRTIM1_DACTRG1           ((uint32_t)0x0000001C)  /*!< HRTIM1 DACTRG1 selected as external conversion trigger for DAC1 channel1/2 */                                                                         
#define DAC_Trigger_T2_TRGO                  ((uint32_t)0x00000024) /*!< TIM2 TRGO selected as external conversion trigger for DAC1/2 channel1/2 */
#define DAC_Trigger_T4_TRGO                  ((uint32_t)0x0000002C) /*!< TIM4 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_HRTIM1_DACTRG2           ((uint32_t)0x0000002C) /*!< HRTIM1 DACTRG2 selected as external conversion trigger for DAC1 channel1/2 */
#define DAC_Trigger_HRTIM1_DACTRG3           ((uint32_t)0x0000002C) /*!< HRTIM1 DACTRG3 selected as external conversion trigger for DAC2 channel1 */
#define DAC_Trigger_Ext_IT9                  ((uint32_t)0x00000034) /*!< EXTI Line9 event selected as external conversion trigger for DAC1/2 channel1/2 */
#define DAC_Trigger_Software                 ((uint32_t)0x0000003C) /*!< Conversion started by software trigger for DAC1/2 channel1/2 */

#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_None)          || \
                                 ((TRIGGER) == DAC_Trigger_T6_TRGO)       || \
                                 ((TRIGGER) == DAC_Trigger_T3_TRGO)       || \
                                 ((TRIGGER) == DAC_Trigger_T8_TRGO)       || \
                                 ((TRIGGER) == DAC_Trigger_T7_TRGO)       || \
                                 ((TRIGGER) == DAC_Trigger_T15_TRGO)      || \
                                 ((TRIGGER) == DAC_Trigger_HRTIM1_DACTRG1)|| \
                                 ((TRIGGER) == DAC_Trigger_T2_TRGO)       || \
                                 ((TRIGGER) == DAC_Trigger_T4_TRGO)       || \
                                 ((TRIGGER) == DAC_Trigger_HRTIM1_DACTRG2)|| \
                                 ((TRIGGER) == DAC_Trigger_HRTIM1_DACTRG3)|| \
                                 ((TRIGGER) == DAC_Trigger_Ext_IT9)       || \
                                 ((TRIGGER) == DAC_Trigger_Software))

/**
  * @}
  */

/** @defgroup DAC_wave_generation 
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

/** @defgroup DAC_buffer_switch 
  * @{
  */
#define DAC_OutputSwitch_Disable                 ((uint32_t)0x00000000)
#define DAC_OutputSwitch_Enable                  ((uint32_t)0x00000002)

#define IS_DAC_OUTPUT_SWITCH_STATE(STATE) (((STATE) == DAC_OutputSwitch_Enable) || \
                                           ((STATE) == DAC_OutputSwitch_Disable))
                                           
#define DAC_BufferSwitch_Disable                 ((uint32_t)0x00000002)
#define DAC_BufferSwitch_Enable                  ((uint32_t)0x00000000)

#define IS_DAC_BUFFER_SWITCH_STATE(STATE) (((STATE) == DAC_BufferSwitch_Enable) || \
                                           ((STATE) == DAC_BufferSwitch_Disable))
/**
  * @}
  */

/** @defgroup DAC_Channel_selection 
  * @{
  */
#define DAC_Channel_1                     ((uint32_t)0x00000000)
#define DAC_Channel_2                     ((uint32_t)0x00000010)

#define IS_DAC_CHANNEL(CHANNEL) (((CHANNEL) == DAC_Channel_1) || \
                                 ((CHANNEL) == DAC_Channel_2))
/**
  * @}
  */

/** @defgroup DAC_data_alignement 
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
#define DAC_IT_DMAUDR                      ((uint32_t)0x00002000)  
#define IS_DAC_IT(IT) (((IT) == DAC_IT_DMAUDR)) 

/**
  * @}
  */ 

/** @defgroup DAC_flags_definition 
  * @{
  */ 
  
#define DAC_FLAG_DMAUDR                    ((uint32_t)0x00002000)  
#define IS_DAC_FLAG(FLAG) (((FLAG) == DAC_FLAG_DMAUDR))  

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/  

/*  Function used to set the DAC configuration to the default reset state *****/  
void DAC_DeInit(DAC_TypeDef* DACx);

/*  DAC channels configuration: trigger, output buffer, data format functions */
void DAC_Init(DAC_TypeDef* DACx, uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(DAC_TypeDef* DACx, uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(DAC_TypeDef* DACx, uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(DAC_TypeDef* DACx, FunctionalState NewState);
void DAC_WaveGenerationCmd(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(DAC_TypeDef* DACx, uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(DAC_TypeDef* DACx, uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(DAC_TypeDef* DACx, uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetDataOutputValue(DAC_TypeDef* DACx, uint32_t DAC_Channel);

/* DMA management functions ***************************************************/
void DAC_DMACmd(DAC_TypeDef* DACx, uint32_t DAC_Channel, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void DAC_ITConfig(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState);
FlagStatus DAC_GetFlagStatus(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_FLAG);
void DAC_ClearFlag(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_FLAG);
ITStatus DAC_GetITStatus(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_IT);
void DAC_ClearITPendingBit(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_DAC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_dbgmcu.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the DBGMCU firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_DBGMCU_H
#define __STM32F30x_DBGMCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
#define DBGMCU_SLEEP                          ((uint32_t)0x00000001)
#define DBGMCU_STOP                           ((uint32_t)0x00000002)
#define DBGMCU_STANDBY                        ((uint32_t)0x00000004)
#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFF8) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM2_STOP             ((uint32_t)0x00000001)
#define DBGMCU_TIM3_STOP             ((uint32_t)0x00000002)
#define DBGMCU_TIM4_STOP             ((uint32_t)0x00000004)
#define DBGMCU_TIM6_STOP             ((uint32_t)0x00000010)
#define DBGMCU_TIM7_STOP             ((uint32_t)0x00000020)
#define DBGMCU_RTC_STOP              ((uint32_t)0x00000400)
#define DBGMCU_WWDG_STOP             ((uint32_t)0x00000800)
#define DBGMCU_IWDG_STOP             ((uint32_t)0x00001000)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((uint32_t)0x00200000)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((uint32_t)0x00400000)
#define DBGMCU_CAN1_STOP             ((uint32_t)0x02000000)
#define DBGMCU_I2C3_SMBUS_TIMEOUT    ((uint32_t)0x40000000)

#define IS_DBGMCU_APB1PERIPH(PERIPH) ((((PERIPH) & 0xBD9FE3C8) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM1_STOP             ((uint32_t)0x00000001)
#define DBGMCU_TIM8_STOP             ((uint32_t)0x00000002)
#define DBGMCU_TIM15_STOP            ((uint32_t)0x00000004)
#define DBGMCU_TIM16_STOP            ((uint32_t)0x00000008)
#define DBGMCU_TIM17_STOP            ((uint32_t)0x00000010)
#define DBGMCU_TIM20_STOP            ((uint32_t)0x00000020)
#define IS_DBGMCU_APB2PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFC0) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
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

#endif /* __STM32F30x_DBGMCU_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_dma.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the DMA firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_DMA_H
#define __STM32F30x_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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

  uint16_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel. 
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction.    */

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

/** @defgroup DMA_interrupts_definition
  * @{
  */

#define DMA_IT_TC                          ((uint32_t)0x00000002)
#define DMA_IT_HT                          ((uint32_t)0x00000004)
#define DMA_IT_TE                          ((uint32_t)0x00000008)
#define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00))

#define DMA1_IT_GL1                        ((uint32_t)0x00000001)
#define DMA1_IT_TC1                        ((uint32_t)0x00000002)
#define DMA1_IT_HT1                        ((uint32_t)0x00000004)
#define DMA1_IT_TE1                        ((uint32_t)0x00000008)
#define DMA1_IT_GL2                        ((uint32_t)0x00000010)
#define DMA1_IT_TC2                        ((uint32_t)0x00000020)
#define DMA1_IT_HT2                        ((uint32_t)0x00000040)
#define DMA1_IT_TE2                        ((uint32_t)0x00000080)
#define DMA1_IT_GL3                        ((uint32_t)0x00000100)
#define DMA1_IT_TC3                        ((uint32_t)0x00000200)
#define DMA1_IT_HT3                        ((uint32_t)0x00000400)
#define DMA1_IT_TE3                        ((uint32_t)0x00000800)
#define DMA1_IT_GL4                        ((uint32_t)0x00001000)
#define DMA1_IT_TC4                        ((uint32_t)0x00002000)
#define DMA1_IT_HT4                        ((uint32_t)0x00004000)
#define DMA1_IT_TE4                        ((uint32_t)0x00008000)
#define DMA1_IT_GL5                        ((uint32_t)0x00010000)
#define DMA1_IT_TC5                        ((uint32_t)0x00020000)
#define DMA1_IT_HT5                        ((uint32_t)0x00040000)
#define DMA1_IT_TE5                        ((uint32_t)0x00080000)
#define DMA1_IT_GL6                        ((uint32_t)0x00100000)
#define DMA1_IT_TC6                        ((uint32_t)0x00200000)
#define DMA1_IT_HT6                        ((uint32_t)0x00400000)
#define DMA1_IT_TE6                        ((uint32_t)0x00800000)
#define DMA1_IT_GL7                        ((uint32_t)0x01000000)
#define DMA1_IT_TC7                        ((uint32_t)0x02000000)
#define DMA1_IT_HT7                        ((uint32_t)0x04000000)
#define DMA1_IT_TE7                        ((uint32_t)0x08000000)

#define DMA2_IT_GL1                        ((uint32_t)0x10000001)
#define DMA2_IT_TC1                        ((uint32_t)0x10000002)
#define DMA2_IT_HT1                        ((uint32_t)0x10000004)
#define DMA2_IT_TE1                        ((uint32_t)0x10000008)
#define DMA2_IT_GL2                        ((uint32_t)0x10000010)
#define DMA2_IT_TC2                        ((uint32_t)0x10000020)
#define DMA2_IT_HT2                        ((uint32_t)0x10000040)
#define DMA2_IT_TE2                        ((uint32_t)0x10000080)
#define DMA2_IT_GL3                        ((uint32_t)0x10000100)
#define DMA2_IT_TC3                        ((uint32_t)0x10000200)
#define DMA2_IT_HT3                        ((uint32_t)0x10000400)
#define DMA2_IT_TE3                        ((uint32_t)0x10000800)
#define DMA2_IT_GL4                        ((uint32_t)0x10001000)
#define DMA2_IT_TC4                        ((uint32_t)0x10002000)
#define DMA2_IT_HT4                        ((uint32_t)0x10004000)
#define DMA2_IT_TE4                        ((uint32_t)0x10008000)
#define DMA2_IT_GL5                        ((uint32_t)0x10010000)
#define DMA2_IT_TC5                        ((uint32_t)0x10020000)
#define DMA2_IT_HT5                        ((uint32_t)0x10040000)
#define DMA2_IT_TE5                        ((uint32_t)0x10080000)

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
  
#define DMA1_FLAG_GL1                      ((uint32_t)0x00000001)
#define DMA1_FLAG_TC1                      ((uint32_t)0x00000002)
#define DMA1_FLAG_HT1                      ((uint32_t)0x00000004)
#define DMA1_FLAG_TE1                      ((uint32_t)0x00000008)
#define DMA1_FLAG_GL2                      ((uint32_t)0x00000010)
#define DMA1_FLAG_TC2                      ((uint32_t)0x00000020)
#define DMA1_FLAG_HT2                      ((uint32_t)0x00000040)
#define DMA1_FLAG_TE2                      ((uint32_t)0x00000080)
#define DMA1_FLAG_GL3                      ((uint32_t)0x00000100)
#define DMA1_FLAG_TC3                      ((uint32_t)0x00000200)
#define DMA1_FLAG_HT3                      ((uint32_t)0x00000400)
#define DMA1_FLAG_TE3                      ((uint32_t)0x00000800)
#define DMA1_FLAG_GL4                      ((uint32_t)0x00001000)
#define DMA1_FLAG_TC4                      ((uint32_t)0x00002000)
#define DMA1_FLAG_HT4                      ((uint32_t)0x00004000)
#define DMA1_FLAG_TE4                      ((uint32_t)0x00008000)
#define DMA1_FLAG_GL5                      ((uint32_t)0x00010000)
#define DMA1_FLAG_TC5                      ((uint32_t)0x00020000)
#define DMA1_FLAG_HT5                      ((uint32_t)0x00040000)
#define DMA1_FLAG_TE5                      ((uint32_t)0x00080000)
#define DMA1_FLAG_GL6                      ((uint32_t)0x00100000)
#define DMA1_FLAG_TC6                      ((uint32_t)0x00200000)
#define DMA1_FLAG_HT6                      ((uint32_t)0x00400000)
#define DMA1_FLAG_TE6                      ((uint32_t)0x00800000)
#define DMA1_FLAG_GL7                      ((uint32_t)0x01000000)
#define DMA1_FLAG_TC7                      ((uint32_t)0x02000000)
#define DMA1_FLAG_HT7                      ((uint32_t)0x04000000)
#define DMA1_FLAG_TE7                      ((uint32_t)0x08000000)

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

#endif /*__STM32F30x_DMA_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_exti.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the EXTI 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_EXTI_H
#define __STM32F30x_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
                                         This parameter can be a value of @ref EXTITrigger_TypeDef */

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

#define EXTI_Line0       ((uint32_t)0x00)  /*!< External interrupt line 0  */
#define EXTI_Line1       ((uint32_t)0x01)  /*!< External interrupt line 1  */
#define EXTI_Line2       ((uint32_t)0x02)  /*!< External interrupt line 2  */
#define EXTI_Line3       ((uint32_t)0x03)  /*!< External interrupt line 3  */
#define EXTI_Line4       ((uint32_t)0x04)  /*!< External interrupt line 4  */
#define EXTI_Line5       ((uint32_t)0x05)  /*!< External interrupt line 5  */
#define EXTI_Line6       ((uint32_t)0x06)  /*!< External interrupt line 6  */
#define EXTI_Line7       ((uint32_t)0x07)  /*!< External interrupt line 7  */
#define EXTI_Line8       ((uint32_t)0x08)  /*!< External interrupt line 8  */
#define EXTI_Line9       ((uint32_t)0x09)  /*!< External interrupt line 9  */
#define EXTI_Line10      ((uint32_t)0x0A)  /*!< External interrupt line 10 */
#define EXTI_Line11      ((uint32_t)0x0B)  /*!< External interrupt line 11 */
#define EXTI_Line12      ((uint32_t)0x0C)  /*!< External interrupt line 12 */
#define EXTI_Line13      ((uint32_t)0x0D)  /*!< External interrupt line 13 */
#define EXTI_Line14      ((uint32_t)0x0E)  /*!< External interrupt line 14 */
#define EXTI_Line15      ((uint32_t)0x0F)  /*!< External interrupt line 15 */
#define EXTI_Line16      ((uint32_t)0x10)  /*!< External interrupt line 16 
                                                      Connected to the PVD Output */
#define EXTI_Line17      ((uint32_t)0x11)  /*!< Internal interrupt line 17 
                                                      Connected to the RTC Alarm 
                                                      event */
#define EXTI_Line18      ((uint32_t)0x12)  /*!< Internal interrupt line 18 
                                                      Connected to the USB Device
                                                      Wakeup from suspend event */
#define EXTI_Line19      ((uint32_t)0x13)  /*!< Internal interrupt line 19
                                                      Connected to the RTC Tamper
                                                      and Time Stamp events */
#define EXTI_Line20      ((uint32_t)0x14)  /*!< Internal interrupt line 20
                                                      Connected to the RTC wakeup
                                                      event */                                                      
#define EXTI_Line21      ((uint32_t)0x15)  /*!< Internal interrupt line 21
                                                      Connected to the Comparator 1
                                                      event */
#define EXTI_Line22      ((uint32_t)0x16)  /*!< Internal interrupt line 22
                                                      Connected to the Comparator 2
                                                      event */
#define EXTI_Line23      ((uint32_t)0x17)  /*!< Internal interrupt line 23
                                                      Connected to the I2C1 wakeup
                                                      event */
#define EXTI_Line24      ((uint32_t)0x18)  /*!< Internal interrupt line 24
                                                      Connected to the I2C2 wakeup
                                                      event */
#define EXTI_Line25      ((uint32_t)0x19)  /*!< Internal interrupt line 25
                                                      Connected to the USART1 wakeup
                                                      event */
#define EXTI_Line26      ((uint32_t)0x1A)  /*!< Internal interrupt line 26
                                                      Connected to the USART2 wakeup
                                                      event */
#define EXTI_Line27      ((uint32_t)0x1B)  /*!< Internal interrupt line 27
                                                       reserved */
#define EXTI_Line28      ((uint32_t)0x1C)  /*!< Internal interrupt line 28
                                                      Connected to the USART3 wakeup
                                                      event */
#define EXTI_Line29      ((uint32_t)0x1D)  /*!< Internal interrupt line 29
                                                      Connected to the Comparator 3 
                                                      event */
#define EXTI_Line30      ((uint32_t)0x1E)  /*!< Internal interrupt line 30
                                                      Connected to the Comparator 4 
                                                      event */
#define EXTI_Line31      ((uint32_t)0x1F)  /*!< Internal interrupt line 31
                                                      Connected to the Comparator 5 
                                                      event */
#define EXTI_Line32      ((uint32_t)0x20)  /*!< Internal interrupt line 32
                                                      Connected to the Comparator 6 
                                                      event */
#define EXTI_Line33      ((uint32_t)0x21)  /*!< Internal interrupt line 33
                                                      Connected to the Comparator 7 
                                                      event */
#define EXTI_Line34      ((uint32_t)0x22)  /*!< Internal interrupt line 34
                                                      Connected to the USART4 wakeup
                                                      event */
#define EXTI_Line35      ((uint32_t)0x23)  /*!< Internal interrupt line 35
                                                      Connected to the USART5 wakeup
                                                      event */
                                                                                                                                                                                                                                                                                                                                                                                                                                                
#define IS_EXTI_LINE_ALL(LINE) ((LINE) <= 0x23)
#define IS_EXTI_LINE_EXT(LINE) (((LINE) <= 0x16) || (((LINE) == EXTI_Line29) || ((LINE) == EXTI_Line30) || \
                               ((LINE) == EXTI_Line31) || ((LINE) == EXTI_Line32) || ((LINE) == EXTI_Line33)))

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
                                ((LINE) == EXTI_Line22) || ((LINE) == EXTI_Line29) || \
                                ((LINE) == EXTI_Line30) || ((LINE) == EXTI_Line31) || \
                                ((LINE) == EXTI_Line32) || ((LINE) == EXTI_Line33))
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

#endif /* __STM32F30x_EXTI_H */
/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_flash.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the FLASH 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_FLASH_H
#define __STM32F30x_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief FLASH Status  
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

/** @defgroup Flash_Latency 
  * @{
  */ 
#define FLASH_Latency_0                ((uint8_t)0x0000)    /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                FLASH_ACR_LATENCY_0  /*!< FLASH One Latency cycle */
#define FLASH_Latency_2                FLASH_ACR_LATENCY_1  /*!< FLASH Two Latency cycles */

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1) || \
                                   ((LATENCY) == FLASH_Latency_2))
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
  
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0803FFFF))

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

/** @defgroup Option_Bytes_Write_Protection 
  * @{
  */
  
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

#ifdef STM32F303xE
#define OB_WRP_Pages62to263            ((uint32_t)0x80000000) /* Write protection of page 62 to 263 */
#else
#define OB_WRP_Pages62to127            ((uint32_t)0x80000000) /* Write protection of page 62 to 127 */
#endif  /* STM32F303xE */

#define OB_WRP_AllPages                ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Sectors */

#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))

/**
  * @}
  */

/** @defgroup Option_Bytes_Read_Protection 
  * @{
  */ 

/** 
  * @brief  Read Protection Level  
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

/** @defgroup Option_Bytes_IWatchdog 
  * @{
  */

#define OB_IWDG_SW                     ((uint8_t)0x01)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware IWDG selected */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

/**
  * @}
  */

/** @defgroup Option_Bytes_nRST_STOP 
  * @{
  */

#define OB_STOP_NoRST                  ((uint8_t)0x02) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))

/**
  * @}
  */

/** @defgroup Option_Bytes_nRST_STDBY 
  * @{
  */

#define OB_STDBY_NoRST                 ((uint8_t)0x04) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))

/**
  * @}
  */
/** @defgroup Option_Bytes_BOOT1
  * @{
  */

#define OB_BOOT1_RESET                 ((uint8_t)0x00) /*!< BOOT1 Reset */
#define OB_BOOT1_SET                   ((uint8_t)0x10) /*!< BOOT1 Set */
#define IS_OB_BOOT1(BOOT1) (((BOOT1) == OB_BOOT1_RESET) || ((BOOT1) == OB_BOOT1_SET))

/**
  * @}
  */  
/** @defgroup Option_Bytes_VDDA_Analog_Monitoring
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
/** @defgroup Timeout_definition 
  * @{
  */ 
#define FLASH_ER_PRG_TIMEOUT         ((uint32_t)0x000B0000)

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/* FLASH Interface configuration functions ************************************/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(FunctionalState NewState);
void FLASH_PrefetchBufferCmd(FunctionalState NewState);

/* FLASH Memory Programming functions *****************************************/   
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

/* Option Bytes Programming functions *****************************************/ 
void FLASH_OB_Unlock(void);
void FLASH_OB_Lock(void);
void FLASH_OB_Launch(void);
FLASH_Status FLASH_OB_Erase(void);
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP);
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP);
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1);
FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG);
FLASH_Status FLASH_OB_SRAMParityConfig(uint8_t OB_SRAM_Parity);
FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);
uint8_t FLASH_OB_GetUser(void);
uint32_t FLASH_OB_GetWRP(void);
FlagStatus FLASH_OB_GetRDP(void);

/* Interrupts and flags management functions **********************************/
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_FLASH_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_fmc.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the FMC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_FMC_H
#define __STM32F30x_FMC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup FMC
  * @{
  */

/* Exported types ------------------------------------------------------------*/  
   
/** 
  * @brief  Timing parameters For NOR/SRAM Banks  
  */
typedef struct
{
  uint32_t FMC_AddressSetupTime;       /*!< Defines the number of HCLK cycles to configure
                                             the duration of the address setup time. 
                                             This parameter can be a value between 0 and 15.
                                             @note This parameter is not used with synchronous NOR Flash memories. */

  uint32_t FMC_AddressHoldTime;        /*!< Defines the number of HCLK cycles to configure
                                             the duration of the address hold time.
                                             This parameter can be a value between 1 and 15. 
                                             @note This parameter is not used with synchronous NOR Flash memories.*/

  uint32_t FMC_DataSetupTime;          /*!< Defines the number of HCLK cycles to configure
                                             the duration of the data setup time.
                                             This parameter can be a value between 1 and 255.
                                             @note This parameter is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories. */

  uint32_t FMC_BusTurnAroundDuration;  /*!< Defines the number of HCLK cycles to configure
                                             the duration of the bus turnaround.
                                             This parameter can be a value between 0 and 15.
                                             @note This parameter is only used for multiplexed NOR Flash memories. */

  uint32_t FMC_CLKDivision;            /*!< Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
                                             This parameter can be a value between 2 and 16.
                                             @note This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses. */

  uint32_t FMC_DataLatency;            /*!< Defines the number of memory clock cycles to issue
                                             to the memory before getting the first data.
                                             The parameter value depends on the memory type as shown below:
                                              - It must be set to 0 in case of a CRAM
                                              - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                              - It may assume a value between 2 and 17 in NOR Flash memories
                                                with synchronous burst mode enable */

  uint32_t FMC_AccessMode;             /*!< Specifies the asynchronous access mode. 
                                             This parameter can be a value of @ref FMC_Access_Mode */
}FMC_NORSRAMTimingInitTypeDef;

/** 
  * @brief  FMC NOR/SRAM Init structure definition
  */
typedef struct
{
  uint32_t FMC_Bank;                /*!< Specifies the NOR/SRAM memory bank that will be used.
                                          This parameter can be a value of @ref FMC_NORSRAM_Bank */

  uint32_t FMC_DataAddressMux;      /*!< Specifies whether the address and data values are
                                          multiplexed on the databus or not. 
                                          This parameter can be a value of @ref FMC_Data_Address_Bus_Multiplexing */

  uint32_t FMC_MemoryType;          /*!< Specifies the type of external memory attached to
                                          the corresponding memory bank.
                                          This parameter can be a value of @ref FMC_Memory_Type */

  uint32_t FMC_MemoryDataWidth;     /*!< Specifies the external memory device width.
                                          This parameter can be a value of @ref FMC_NORSRAM_Data_Width */

  uint32_t FMC_BurstAccessMode;     /*!< Enables or disables the burst access mode for Flash memory,
                                          valid only with synchronous burst Flash memories.
                                          This parameter can be a value of @ref FMC_Burst_Access_Mode */                                        

  uint32_t FMC_WaitSignalPolarity;  /*!< Specifies the wait signal polarity, valid only when accessing
                                          the Flash memory in burst mode.
                                          This parameter can be a value of @ref FMC_Wait_Signal_Polarity */

  uint32_t FMC_WrapMode;            /*!< Enables or disables the Wrapped burst access mode for Flash
                                          memory, valid only when accessing Flash memories in burst mode.
                                          This parameter can be a value of @ref FMC_Wrap_Mode */

  uint32_t FMC_WaitSignalActive;    /*!< Specifies if the wait signal is asserted by the memory one
                                          clock cycle before the wait state or during the wait state,
                                          valid only when accessing memories in burst mode. 
                                          This parameter can be a value of @ref FMC_Wait_Timing */

  uint32_t FMC_WriteOperation;      /*!< Enables or disables the write operation in the selected bank by the FMC. 
                                          This parameter can be a value of @ref FMC_Write_Operation */

  uint32_t FMC_WaitSignal;          /*!< Enables or disables the wait state insertion via wait
                                          signal, valid for Flash memory access in burst mode. 
                                          This parameter can be a value of @ref FMC_Wait_Signal */

  uint32_t FMC_ExtendedMode;        /*!< Enables or disables the extended mode.
                                          This parameter can be a value of @ref FMC_Extended_Mode */
  
  uint32_t FMC_AsynchronousWait;     /*!< Enables or disables wait signal during asynchronous transfers,
                                          valid only with asynchronous Flash memories.
                                          This parameter can be a value of @ref FMC_AsynchronousWait */  

  uint32_t FMC_WriteBurst;          /*!< Enables or disables the write burst operation.
                                          This parameter can be a value of @ref FMC_Write_Burst */

  
  FMC_NORSRAMTimingInitTypeDef* FMC_ReadWriteTimingStruct; /*!< Timing Parameters for write and read access if the  Extended Mode is not used*/  

  FMC_NORSRAMTimingInitTypeDef* FMC_WriteTimingStruct;     /*!< Timing Parameters for write access if the  Extended Mode is used*/      
}FMC_NORSRAMInitTypeDef;

/** 
  * @brief  Timing parameters For FMC NAND and PCCARD Banks
  */
typedef struct
{
  uint32_t FMC_SetupTime;      /*!< Defines the number of HCLK cycles to setup address before
                                     the command assertion for NAND-Flash read or write access
                                     to common/Attribute or I/O memory space (depending on
                                     the memory space timing to be configured).
                                     This parameter can be a value between 0 and 255.*/

  uint32_t FMC_WaitSetupTime;  /*!< Defines the minimum number of HCLK cycles to assert the
                                     command for NAND-Flash read or write access to
                                     common/Attribute or I/O memory space (depending on the
                                     memory space timing to be configured). 
                                     This parameter can be a number between 0 and 255 */

  uint32_t FMC_HoldSetupTime;  /*!< Defines the number of HCLK clock cycles to hold address
                                     (and data for write access) after the command de-assertion
                                     for NAND-Flash read or write access to common/Attribute
                                     or I/O memory space (depending on the memory space timing
                                     to be configured).
                                     This parameter can be a number between 0 and 255 */

  uint32_t FMC_HiZSetupTime;   /*!< Defines the number of HCLK clock cycles during which the
                                     databus is kept in HiZ after the start of a NAND-Flash
                                     write access to common/Attribute or I/O memory space (depending
                                     on the memory space timing to be configured).
                                     This parameter can be a number between 0 and 255 */
}FMC_NAND_PCCARDTimingInitTypeDef;

/** 
  * @brief  FMC NAND Init structure definition
  */
typedef struct
{
  uint32_t FMC_Bank;              /*!< Specifies the NAND memory bank that will be used.
                                      This parameter can be a value of @ref FMC_NAND_Bank */

  uint32_t FMC_Waitfeature;      /*!< Enables or disables the Wait feature for the NAND Memory Bank.
                                       This parameter can be any value of @ref FMC_Wait_feature */

  uint32_t FMC_MemoryDataWidth;  /*!< Specifies the external memory device width.
                                       This parameter can be any value of @ref FMC_NAND_Data_Width */

  uint32_t FMC_ECC;              /*!< Enables or disables the ECC computation.
                                       This parameter can be any value of @ref FMC_ECC */

  uint32_t FMC_ECCPageSize;      /*!< Defines the page size for the extended ECC.
                                       This parameter can be any value of @ref FMC_ECC_Page_Size */

  uint32_t FMC_TCLRSetupTime;    /*!< Defines the number of HCLK cycles to configure the
                                       delay between CLE low and RE low.
                                       This parameter can be a value between 0 and 255. */

  uint32_t FMC_TARSetupTime;     /*!< Defines the number of HCLK cycles to configure the
                                       delay between ALE low and RE low.
                                       This parameter can be a number between 0 and 255 */ 

  FMC_NAND_PCCARDTimingInitTypeDef*  FMC_CommonSpaceTimingStruct;   /*!< FMC Common Space Timing */ 

  FMC_NAND_PCCARDTimingInitTypeDef*  FMC_AttributeSpaceTimingStruct; /*!< FMC Attribute Space Timing */
}FMC_NANDInitTypeDef;

/** 
  * @brief  FMC PCCARD Init structure definition
  */

typedef struct
{
  uint32_t FMC_Waitfeature;    /*!< Enables or disables the Wait feature for the Memory Bank.
                                    This parameter can be any value of @ref FMC_Wait_feature */

  uint32_t FMC_TCLRSetupTime;  /*!< Defines the number of HCLK cycles to configure the
                                     delay between CLE low and RE low.
                                     This parameter can be a value between 0 and 255. */

  uint32_t FMC_TARSetupTime;   /*!< Defines the number of HCLK cycles to configure the
                                     delay between ALE low and RE low.
                                     This parameter can be a number between 0 and 255 */ 

  
  FMC_NAND_PCCARDTimingInitTypeDef*  FMC_CommonSpaceTimingStruct; /*!< FMC Common Space Timing */

  FMC_NAND_PCCARDTimingInitTypeDef*  FMC_AttributeSpaceTimingStruct;  /*!< FMC Attribute Space Timing */ 
  
  FMC_NAND_PCCARDTimingInitTypeDef*  FMC_IOSpaceTimingStruct; /*!< FMC IO Space Timing */  
}FMC_PCCARDInitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup FMC_Exported_Constants
  * @{
  */ 

/** @defgroup FMC_NORSRAM_Bank 
  * @{
  */
#define FMC_Bank1_NORSRAM1                      ((uint32_t)0x00000000)
#define FMC_Bank1_NORSRAM2                      ((uint32_t)0x00000002)
#define FMC_Bank1_NORSRAM3                      ((uint32_t)0x00000004)
#define FMC_Bank1_NORSRAM4                      ((uint32_t)0x00000006)

#define IS_FMC_NORSRAM_BANK(BANK) (((BANK) == FMC_Bank1_NORSRAM1) || \
                                   ((BANK) == FMC_Bank1_NORSRAM2) || \
                                   ((BANK) == FMC_Bank1_NORSRAM3) || \
                                   ((BANK) == FMC_Bank1_NORSRAM4))
/**
  * @}
  */

/** @defgroup FMC_NAND_Bank 
  * @{
  */  
#define FMC_Bank2_NAND                          ((uint32_t)0x00000010)
#define FMC_Bank3_NAND                          ((uint32_t)0x00000100)

#define IS_FMC_NAND_BANK(BANK) (((BANK) == FMC_Bank2_NAND) || \
                                ((BANK) == FMC_Bank3_NAND))
/**
  * @}
  */

/** @defgroup FMC_PCCARD_Bank 
  * @{
  */    
#define FMC_Bank4_PCCARD                        ((uint32_t)0x00001000)
/**
  * @}                                                         
  */                              

                              
/** @defgroup FMC_NOR_SRAM_Controller 
  * @{
  */

/** @defgroup FMC_Data_Address_Bus_Multiplexing 
  * @{
  */

#define FMC_DataAddressMux_Disable                ((uint32_t)0x00000000)
#define FMC_DataAddressMux_Enable                 ((uint32_t)0x00000002)

#define IS_FMC_MUX(MUX) (((MUX) == FMC_DataAddressMux_Disable) || \
                         ((MUX) == FMC_DataAddressMux_Enable))
/**
  * @}
  */

/** @defgroup FMC_Memory_Type 
  * @{
  */

#define FMC_MemoryType_SRAM                     ((uint32_t)0x00000000)
#define FMC_MemoryType_PSRAM                    ((uint32_t)0x00000004)
#define FMC_MemoryType_NOR                      ((uint32_t)0x00000008)

#define IS_FMC_MEMORY(MEMORY) (((MEMORY) == FMC_MemoryType_SRAM) || \
                               ((MEMORY) == FMC_MemoryType_PSRAM)|| \
                               ((MEMORY) == FMC_MemoryType_NOR))
/**
  * @}
  */

/** @defgroup FMC_NORSRAM_Data_Width 
  * @{
  */

#define FMC_NORSRAM_MemoryDataWidth_8b                  ((uint32_t)0x00000000)
#define FMC_NORSRAM_MemoryDataWidth_16b                 ((uint32_t)0x00000010)

#define IS_FMC_NORSRAM_MEMORY_WIDTH(WIDTH) (((WIDTH) == FMC_NORSRAM_MemoryDataWidth_8b)  || \
                                            ((WIDTH) == FMC_NORSRAM_MemoryDataWidth_16b))
/**
  * @}
  */

/** @defgroup FMC_Burst_Access_Mode 
  * @{
  */

#define FMC_BurstAccessMode_Disable             ((uint32_t)0x00000000) 
#define FMC_BurstAccessMode_Enable              ((uint32_t)0x00000100)

#define IS_FMC_BURSTMODE(STATE) (((STATE) == FMC_BurstAccessMode_Disable) || \
                                  ((STATE) == FMC_BurstAccessMode_Enable))
/**
  * @}
  */
    
/** @defgroup FMC_AsynchronousWait 
  * @{
  */
#define FMC_AsynchronousWait_Disable            ((uint32_t)0x00000000)
#define FMC_AsynchronousWait_Enable             ((uint32_t)0x00008000)

#define IS_FMC_ASYNWAIT(STATE) (((STATE) == FMC_AsynchronousWait_Disable) || \
                                 ((STATE) == FMC_AsynchronousWait_Enable))
/**
  * @}
  */

/** @defgroup FMC_Wait_Signal_Polarity 
  * @{
  */
#define FMC_WaitSignalPolarity_Low              ((uint32_t)0x00000000)
#define FMC_WaitSignalPolarity_High             ((uint32_t)0x00000200)

#define IS_FMC_WAIT_POLARITY(POLARITY) (((POLARITY) == FMC_WaitSignalPolarity_Low) || \
                                         ((POLARITY) == FMC_WaitSignalPolarity_High))
/**
  * @}
  */

/** @defgroup FMC_Wrap_Mode 
  * @{
  */
#define FMC_WrapMode_Disable                    ((uint32_t)0x00000000)
#define FMC_WrapMode_Enable                     ((uint32_t)0x00000400) 

#define IS_FMC_WRAP_MODE(MODE) (((MODE) == FMC_WrapMode_Disable) || \
                                 ((MODE) == FMC_WrapMode_Enable))
/**
  * @}
  */

/** @defgroup FMC_Wait_Timing 
  * @{
  */
#define FMC_WaitSignalActive_BeforeWaitState    ((uint32_t)0x00000000)
#define FMC_WaitSignalActive_DuringWaitState    ((uint32_t)0x00000800) 

#define IS_FMC_WAIT_SIGNAL_ACTIVE(ACTIVE) (((ACTIVE) == FMC_WaitSignalActive_BeforeWaitState) || \
                                            ((ACTIVE) == FMC_WaitSignalActive_DuringWaitState))
/**
  * @}
  */

/** @defgroup FMC_Write_Operation 
  * @{
  */
#define FMC_WriteOperation_Disable                     ((uint32_t)0x00000000)
#define FMC_WriteOperation_Enable                      ((uint32_t)0x00001000)

#define IS_FMC_WRITE_OPERATION(OPERATION) (((OPERATION) == FMC_WriteOperation_Disable) || \
                                            ((OPERATION) == FMC_WriteOperation_Enable))                         
/**
  * @}
  */

/** @defgroup FMC_Wait_Signal 
  * @{
  */
#define FMC_WaitSignal_Disable                  ((uint32_t)0x00000000)
#define FMC_WaitSignal_Enable                   ((uint32_t)0x00002000) 

#define IS_FMC_WAITE_SIGNAL(SIGNAL) (((SIGNAL) == FMC_WaitSignal_Disable) || \
                                      ((SIGNAL) == FMC_WaitSignal_Enable))
/**
  * @}
  */

/** @defgroup FMC_Extended_Mode 
  * @{
  */
#define FMC_ExtendedMode_Disable                ((uint32_t)0x00000000)
#define FMC_ExtendedMode_Enable                 ((uint32_t)0x00004000)

#define IS_FMC_EXTENDED_MODE(MODE) (((MODE) == FMC_ExtendedMode_Disable) || \
                                     ((MODE) == FMC_ExtendedMode_Enable)) 
/**
  * @}
  */

/** @defgroup FMC_Write_Burst 
  * @{
  */

#define FMC_WriteBurst_Disable                  ((uint32_t)0x00000000)
#define FMC_WriteBurst_Enable                   ((uint32_t)0x00080000) 

#define IS_FMC_WRITE_BURST(BURST) (((BURST) == FMC_WriteBurst_Disable) || \
                                    ((BURST) == FMC_WriteBurst_Enable))
/**
  * @}
  */
  
/** @defgroup FMC_Continous_Clock 
  * @{
  */

#define FMC_CClock_SyncOnly                     ((uint32_t)0x00000000)
#define FMC_CClock_SyncAsync                    ((uint32_t)0x00100000) 

#define IS_FMC_CONTINOUS_CLOCK(CCLOCK) (((CCLOCK) == FMC_CClock_SyncOnly) || \
                                        ((CCLOCK) == FMC_CClock_SyncAsync))
/**
  * @}
  */  

/** @defgroup FMC_Address_Setup_Time 
  * @{
  */
#define IS_FMC_ADDRESS_SETUP_TIME(TIME) ((TIME) <= 15)
/**
  * @}
  */

/** @defgroup FMC_Address_Hold_Time 
  * @{
  */
#define IS_FMC_ADDRESS_HOLD_TIME(TIME) (((TIME) > 0) && ((TIME) <= 15))
/**
  * @}
  */

/** @defgroup FMC_Data_Setup_Time 
  * @{
  */
#define IS_FMC_DATASETUP_TIME(TIME) (((TIME) > 0) && ((TIME) <= 255))
/**
  * @}
  */

/** @defgroup FMC_Bus_Turn_around_Duration 
  * @{
  */
#define IS_FMC_TURNAROUND_TIME(TIME) ((TIME) <= 15)
/**
  * @}
  */

/** @defgroup FMC_CLK_Division 
  * @{
  */
#define IS_FMC_CLK_DIV(DIV) (((DIV) > 1) && ((DIV) <= 16))
/**
  * @}
  */

/** @defgroup FMC_Data_Latency 
  * @{
  */
#define IS_FMC_DATA_LATENCY(LATENCY) (((LATENCY) > 1) && ((LATENCY) <= 17))
/**
  * @}
  */

/** @defgroup FMC_Access_Mode 
  * @{
  */
#define FMC_AccessMode_A                        ((uint32_t)0x00000000)
#define FMC_AccessMode_B                        ((uint32_t)0x10000000) 
#define FMC_AccessMode_C                        ((uint32_t)0x20000000)
#define FMC_AccessMode_D                        ((uint32_t)0x30000000)

#define IS_FMC_ACCESS_MODE(MODE) (((MODE) == FMC_AccessMode_A)  || \
                                   ((MODE) == FMC_AccessMode_B) || \
                                   ((MODE) == FMC_AccessMode_C) || \
                                   ((MODE) == FMC_AccessMode_D))
/**
  * @}
  */

/**
  * @}
  */
  
/** @defgroup FMC_NAND_PCCARD_Controller 
  * @{
  */

/** @defgroup FMC_Wait_feature 
  * @{
  */
#define FMC_Waitfeature_Disable                 ((uint32_t)0x00000000)
#define FMC_Waitfeature_Enable                  ((uint32_t)0x00000002)

#define IS_FMC_WAIT_FEATURE(FEATURE) (((FEATURE) == FMC_Waitfeature_Disable) || \
                                       ((FEATURE) == FMC_Waitfeature_Enable))
/**
  * @}
  */

/** @defgroup FMC_NAND_Data_Width 
  * @{
  */
#define FMC_NAND_MemoryDataWidth_8b             ((uint32_t)0x00000000)
#define FMC_NAND_MemoryDataWidth_16b            ((uint32_t)0x00000010)

#define IS_FMC_NAND_MEMORY_WIDTH(WIDTH) (((WIDTH) == FMC_NAND_MemoryDataWidth_8b) || \
                                         ((WIDTH) == FMC_NAND_MemoryDataWidth_16b))
/**
  * @}
  */

/** @defgroup FMC_ECC 
  * @{
  */
#define FMC_ECC_Disable                         ((uint32_t)0x00000000)
#define FMC_ECC_Enable                          ((uint32_t)0x00000040)

#define IS_FMC_ECC_STATE(STATE) (((STATE) == FMC_ECC_Disable) || \
                                  ((STATE) == FMC_ECC_Enable))
/**
  * @}
  */

/** @defgroup FMC_ECC_Page_Size 
  * @{
  */
#define FMC_ECCPageSize_256Bytes                ((uint32_t)0x00000000)
#define FMC_ECCPageSize_512Bytes                ((uint32_t)0x00020000)
#define FMC_ECCPageSize_1024Bytes               ((uint32_t)0x00040000)
#define FMC_ECCPageSize_2048Bytes               ((uint32_t)0x00060000)
#define FMC_ECCPageSize_4096Bytes               ((uint32_t)0x00080000)
#define FMC_ECCPageSize_8192Bytes               ((uint32_t)0x000A0000)

#define IS_FMC_ECCPAGE_SIZE(SIZE) (((SIZE) == FMC_ECCPageSize_256Bytes)   || \
                                    ((SIZE) == FMC_ECCPageSize_512Bytes)  || \
                                    ((SIZE) == FMC_ECCPageSize_1024Bytes) || \
                                    ((SIZE) == FMC_ECCPageSize_2048Bytes) || \
                                    ((SIZE) == FMC_ECCPageSize_4096Bytes) || \
                                    ((SIZE) == FMC_ECCPageSize_8192Bytes))
/**
  * @}
  */

/** @defgroup FMC_TCLR_Setup_Time 
  * @{
  */
#define IS_FMC_TCLR_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FMC_TAR_Setup_Time 
  * @{
  */
#define IS_FMC_TAR_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FMC_Setup_Time 
  * @{
  */
#define IS_FMC_SETUP_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FMC_Wait_Setup_Time 
  * @{
  */
#define IS_FMC_WAIT_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FMC_Hold_Setup_Time 
  * @{
  */
#define IS_FMC_HOLD_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FMC_HiZ_Setup_Time 
  * @{
  */
#define IS_FMC_HIZ_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */ 

/**
  * @}
  */  

/** @defgroup FMC_Interrupt_sources 
  * @{
  */
#define FMC_IT_RisingEdge                       ((uint32_t)0x00000008)
#define FMC_IT_Level                            ((uint32_t)0x00000010)
#define FMC_IT_FallingEdge                      ((uint32_t)0x00000020)

#define IS_FMC_IT(IT) ((((IT) & (uint32_t)0xFFFFBFC7) == 0x00000000) && ((IT) != 0x00000000))
#define IS_FMC_GET_IT(IT) (((IT) == FMC_IT_RisingEdge)  || \
                           ((IT) == FMC_IT_Level)       || \
                           ((IT) == FMC_IT_FallingEdge)) 
                           
#define IS_FMC_IT_BANK(BANK) (((BANK) == FMC_Bank2_NAND)   || \
                              ((BANK) == FMC_Bank3_NAND)   || \
                              ((BANK) == FMC_Bank4_PCCARD))                           
/**
  * @}
  */

/** @defgroup FMC_Flags 
  * @{
  */
#define FMC_FLAG_RisingEdge                     ((uint32_t)0x00000001)
#define FMC_FLAG_Level                          ((uint32_t)0x00000002)
#define FMC_FLAG_FallingEdge                    ((uint32_t)0x00000004)
#define FMC_FLAG_FEMPT                          ((uint32_t)0x00000040)

#define IS_FMC_GET_FLAG(FLAG) (((FLAG) == FMC_FLAG_RisingEdge)       || \
                               ((FLAG) == FMC_FLAG_Level)            || \
                               ((FLAG) == FMC_FLAG_FallingEdge)      || \
                               ((FLAG) == FMC_FLAG_FEMPT))

#define IS_FMC_GETFLAG_BANK(BANK) (((BANK) == FMC_Bank2_NAND)    || \
                                   ((BANK) == FMC_Bank3_NAND)    || \
                                   ((BANK) == FMC_Bank4_PCCARD))
                                   
#define IS_FMC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFF8) == 0x00000000) && ((FLAG) != 0x00000000))


/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/* NOR/SRAM Controller functions **********************************************/
void FMC_NORSRAMDeInit(uint32_t FMC_Bank);
void FMC_NORSRAMInit(FMC_NORSRAMInitTypeDef* FMC_NORSRAMInitStruct);
void FMC_NORSRAMStructInit(FMC_NORSRAMInitTypeDef* FMC_NORSRAMInitStruct);
void FMC_NORSRAMCmd(uint32_t FMC_Bank, FunctionalState NewState);

/* NAND Controller functions **************************************************/
void     FMC_NANDDeInit(uint32_t FMC_Bank);
void     FMC_NANDInit(FMC_NANDInitTypeDef* FMC_NANDInitStruct);
void     FMC_NANDStructInit(FMC_NANDInitTypeDef* FMC_NANDInitStruct);
void     FMC_NANDCmd(uint32_t FMC_Bank, FunctionalState NewState);
void     FMC_NANDECCCmd(uint32_t FMC_Bank, FunctionalState NewState);
uint32_t FMC_GetECC(uint32_t FMC_Bank);

/* PCCARD Controller functions ************************************************/
void FMC_PCCARDDeInit(void);
void FMC_PCCARDInit(FMC_PCCARDInitTypeDef* FMC_PCCARDInitStruct);
void FMC_PCCARDStructInit(FMC_PCCARDInitTypeDef* FMC_PCCARDInitStruct);
void FMC_PCCARDCmd(FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void       FMC_ITConfig(uint32_t FMC_Bank, uint32_t FMC_IT, FunctionalState NewState);
FlagStatus FMC_GetFlagStatus(uint32_t FMC_Bank, uint32_t FMC_FLAG);
void       FMC_ClearFlag(uint32_t FMC_Bank, uint32_t FMC_FLAG);
ITStatus   FMC_GetITStatus(uint32_t FMC_Bank, uint32_t FMC_IT);
void       FMC_ClearITPendingBit(uint32_t FMC_Bank, uint32_t FMC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_FMC_H */
/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_gpio.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the GPIO 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_GPIO_H
#define __STM32F30x_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
                                    ((PERIPH) == GPIOF) || \
                                    ((PERIPH) == GPIOG) || \
                                    ((PERIPH) == GPIOH))  
                                    
#define IS_GPIO_LIST_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                     ((PERIPH) == GPIOB) || \
                                     ((PERIPH) == GPIOC)|| \
                                     ((PERIPH) == GPIOD) || \
                                     ((PERIPH) == GPIOF))  
/** @defgroup Configuration_Mode_enumeration 
  * @{
  */ 
typedef enum
{ 
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
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
  GPIO_Speed_Level_1  = 0x01, /*!< Fast Speed     */
  GPIO_Speed_Level_2  = 0x02, /*!< Meduim Speed   */
  GPIO_Speed_Level_3  = 0x03  /*!< High Speed     */
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
#define GPIO_AF_0            ((uint8_t)0x00) /* JTCK-SWCLK, JTDI, JTDO/TRACESW0, JTMS-SWDAT,  
                                                MCO, NJTRST, TRACED, TRACECK */
/** 
  * @brief  AF 1 selection
  */ 
#define GPIO_AF_1            ((uint8_t)0x01) /*  OUT, TIM2, TIM15, TIM16, TIM17 */

/** 
  * @brief  AF 2 selection
  */ 
#define GPIO_AF_2            ((uint8_t)0x02) /* COMP1_OUT, TIM1, TIM2, TIM3, TIM4, TIM8, TIM15, TIM16 */

/** 
  * @brief  AF 3 selection
  */ 
#define GPIO_AF_3            ((uint8_t)0x03) /* COMP7_OUT, TIM8, TIM15, Touch, HRTIM1 */

/** 
  * @brief  AF 4 selection
  */ 
#define GPIO_AF_4            ((uint8_t)0x04) /* I2C1, I2C2, TIM1, TIM8, TIM16, TIM17 */

/** 
  * @brief  AF 5 selection
  */ 
#define GPIO_AF_5            ((uint8_t)0x05) /* IR_OUT, I2S2, I2S3, SPI1, SPI2, TIM8, USART4, USART5 */

/** 
  * @brief  AF 6 selection
  */ 
#define GPIO_AF_6            ((uint8_t)0x06) /*  IR_OUT, I2S2, I2S3, SPI2, SPI3, TIM1, TIM8 */

/** 
  * @brief  AF 7 selection
  */ 
#define GPIO_AF_7            ((uint8_t)0x07) /* AOP2_OUT, CAN, COMP3_OUT, COMP5_OUT, COMP6_OUT, 
                                                USART1, USART2, USART3 */

/** 
  * @brief  AF 8 selection
  */ 
#define GPIO_AF_8            ((uint8_t)0x08) /* COMP1_OUT, COMP2_OUT, COMP3_OUT, COMP4_OUT, 
                                                COMP5_OUT, COMP6_OUT */

/** 
  * @brief  AF 9 selection
  */ 
#define GPIO_AF_9            ((uint8_t)0x09) /* AOP4_OUT, CAN, TIM1, TIM8, TIM15 */

/** 
  * @brief  AF 10 selection
  */ 
#define GPIO_AF_10            ((uint8_t)0x0A) /* AOP1_OUT, AOP3_OUT, TIM2, TIM3, TIM4, TIM8, TIM17 */

/** 
  * @brief  AF 11 selection
  */ 
#define GPIO_AF_11            ((uint8_t)0x0B) /* TIM1, TIM8 */

/** 
   * @brief  AF 12 selection
   */ 
#define GPIO_AF_12            ((uint8_t)0x0C) /* TIM1, HRTIM1 */

/** 
   * @brief  AF 13 selection
   */ 
#define GPIO_AF_13            ((uint8_t)0x0D) /* HRTIM1, AOP2_OUT */

/** 
  * @brief  AF 14 selection
  */ 
#define GPIO_AF_14            ((uint8_t)0x0E) /* USBDM, USBDP */

/** 
  * @brief  AF 15 selection
  */ 
#define GPIO_AF_15            ((uint8_t)0x0F) /* OUT */

#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_0)||((AF) == GPIO_AF_1)||\
                          ((AF) == GPIO_AF_2)||((AF) == GPIO_AF_3)||\
                          ((AF) == GPIO_AF_4)||((AF) == GPIO_AF_5)||\
                          ((AF) == GPIO_AF_6)||((AF) == GPIO_AF_7)||\
                          ((AF) == GPIO_AF_8)||((AF) == GPIO_AF_9)||\
                          ((AF) == GPIO_AF_10)||((AF) == GPIO_AF_11)||\
                          ((AF) == GPIO_AF_12)||((AF) == GPIO_AF_13)||\
                          ((AF) == GPIO_AF_14)||((AF) == GPIO_AF_15))

/**
  * @}
  */

/** @defgroup GPIO_Speed_Legacy 
  * @{
  */

#define GPIO_Speed_10MHz GPIO_Speed_Level_1   /*!< Fast Speed:10MHz   */
#define GPIO_Speed_2MHz  GPIO_Speed_Level_2   /*!< Medium Speed:2MHz  */
#define GPIO_Speed_50MHz GPIO_Speed_Level_3   /*!< High Speed:50MHz   */

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
void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Alternate functions configuration functions ***************************/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_GPIO_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_hrtim.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the HRTIM firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_HRTIM_H
#define __STM32F30x_HRTIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief  HRTIM Configuration Structure definition - Time base related parameters
  */
typedef struct
{
  uint32_t Period;                 /*!< Specifies the timer period
                                        The period value must be above 3 periods of the fHRTIM clock.
                                        Maximum value is = 0xFFDF */
  uint32_t RepetitionCounter;      /*!< Specifies the timer repetition period
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */ 
  uint32_t PrescalerRatio;         /*!< Specifies the timer clock prescaler ratio. 
                                        This parameter can be any value of @ref HRTIM_PrescalerRatio   */           
  uint32_t Mode;                   /*!< Specifies the counter operating mode
                                        This parameter can be any value of @ref HRTIM_Mode   */           
} HRTIM_BaseInitTypeDef;

/** 
  * @brief  Waveform mode initialization parameters definition
  */
typedef struct {
  uint32_t HalfModeEnable;    /*!< Specifies whether or not half mode is enabled
                                   This parameter can be a combination of @ref HRTIM_HalfModeEnable  */
  uint32_t StartOnSync;       /*!< Specifies whether or not timer is reset by a rising edge on the synchronization input (when enabled)
                                   This parameter can be a combination of @ref HRTIM_StartOnSyncInputEvent  */
  uint32_t ResetOnSync;        /*!< Specifies whether or not timer is reset by a rising edge on the synchronization input (when enabled)
                                   This parameter can be a combination of @ref HRTIM_ResetOnSyncInputEvent  */
  uint32_t DACSynchro;        /*!< Indicates whether or not the a DAC synchronization event is generated 
                                   This parameter can be any value of @ref HRTIM_DACSynchronization   */
  uint32_t PreloadEnable;     /*!< Specifies whether or not register preload is enabled
                                   This parameter can be a combination of @ref HRTIM_RegisterPreloadEnable  */
  uint32_t UpdateGating;      /*!< Specifies how the update occurs with respect to a burst DMA transaction or
                                   update enable inputs (Slave timers only)  
                                   This parameter can be any value of @ref HRTIM_UpdateGating   */
  uint32_t BurstMode;         /*!< Specifies how the timer behaves during a burst mode operation
                                    This parameter can be a combination of @ref HRTIM_TimerBurstMode  */
  uint32_t RepetitionUpdate;  /*!< Specifies whether or not registers update is triggered by the repetition event 
                                   This parameter can be a combination of @ref HRTIM_TimerRepetitionUpdate */
} HRTIM_TimerInitTypeDef;

/** 
  * @brief  Basic output compare mode configuration definition
  */
typedef struct {
  uint32_t Mode;       /*!< Specifies the output compare mode (toggle, active, inactive)
                            This parameter can be a combination of @ref HRTIM_BasicOCMode */ 
  uint32_t Pulse;      /*!< Specifies the compare value to be loaded into the Compare Register. 
                            The compare value must be above or equal to 3 periods of the fHRTIM clock */
  uint32_t Polarity;   /*!< Specifies the output polarity 
                            This parameter can be any value of @ref HRTIM_Output_Polarity */
  uint32_t IdleState;  /*!< Specifies whether the output level is active or inactive when in IDLE state  
                            This parameter can be any value of @ref HRTIM_OutputIDLEState */
} HRTIM_BasicOCChannelCfgTypeDef;

/** 
  * @brief  Basic PWM output mode configuration definition
  */
typedef struct {
  uint32_t Pulse;            /*!< Specifies the compare value to be loaded into the Compare Register. 
                                  The compare value must be above or equal to 3 periods of the fHRTIM clock */
  uint32_t Polarity;        /*!< Specifies the output polarity 
                                 This parameter can be any value of @ref HRTIM_OutputPolarity */
  uint32_t IdleState;       /*!< Specifies whether the output level is active or inactive when in IDLE state  
                                 This parameter can be any value of @ref HRTIM_OutputIDLEState */
} HRTIM_BasicPWMChannelCfgTypeDef;

/** 
  * @brief  Basic capture mode configuration definition
  */
typedef struct {
  uint32_t CaptureUnit;      /*!< Specifies the external event Channel 
                                   This parameter can be any 'EEVx' value of @ref HRTIM_CaptureUnit */
  uint32_t Event;             /*!< Specifies the external event triggering the capture 
                                   This parameter can be any 'EEVx' value of @ref HRTIM_ExternalEventChannels */
  uint32_t EventPolarity;     /*!< Specifies the polarity of the external event (in case of level sensitivity) 
                                   This parameter can be a value of @ref HRTIM_ExternalEventPolarity */ 
  uint32_t EventSensitivity;  /*!< Specifies the sensitivity of the external event 
                                   This parameter can be a value of @ref HRTIM_ExternalEventSensitivity */ 
  uint32_t EventFilter;       /*!< Defines the frequency used to sample the External Event and the length of the digital filter 
                                   This parameter can be a value of @ref HRTIM_ExternalEventFilter */ 
} HRTIM_BasicCaptureChannelCfgTypeDef;

/** 
  * @brief  Basic One Pulse mode configuration definition
  */
typedef struct {
  uint32_t Pulse;             /*!< Specifies the compare value to be loaded into the Compare Register. 
                                   The compare value must be above or equal to 3 periods of the fHRTIM clock */
  uint32_t OutputPolarity;    /*!< Specifies the output polarity 
                                   This parameter can be any value of @ref HRTIM_Output_Polarity */
  uint32_t OutputIdleState;   /*!< Specifies whether the output level is active or inactive when in IDLE state  
                                   This parameter can be any value of @ref HRTIM_Output_IDLE_State */
  uint32_t Event;             /*!< Specifies the external event triggering the pulse generation 
                                   This parameter can be any 'EEVx' value of @ref HRTIM_Capture_Unit_Trigger */
  uint32_t EventPolarity;     /*!< Specifies the polarity of the external event (in case of level sensitivity) 
                                   This parameter can be a value of @ref HRTIM_ExternalEventPolarity */ 
  uint32_t EventSensitivity;  /*!< Specifies the sensitivity of the external event 
                                   This parameter can be a value of @ref HRTIM_ExternalEventSensitivity */ 
  uint32_t EventFilter;       /*!< Defines the frequency used to sample the External Event and the length of the digital filter 
                                   This parameter can be a value of @ref HRTIM_ExternalEventFilter */ 
} HRTIM_BasicOnePulseChannelCfgTypeDef;

/** 
  * @brief  Timer configuration definition
  */
typedef struct {
  uint32_t PushPull;                  /*!< Specifies whether or not the push-pull mode is enabled
                                           This parameter can be a value of @ref HRTIM_TimerPushPullMode */
  uint32_t FaultEnable;               /*!< Specifies which fault channels are enabled for the timer
                                           This parameter can be a combination of @ref HRTIM_TimerFaultEnabling  */
  uint32_t FaultLock;                 /*!< Specifies whether or not fault enabling status is write protected
                                           This parameter can be a value of @ref HRTIM_TimerFaultLock */
  uint32_t DeadTimeInsertion;         /*!< Specifies whether or not dead time insertion is enabled for the timer
                                           This parameter can be a value of @ref HRTIM_TimerDeadtimeInsertion */
  uint32_t DelayedProtectionMode;     /*!< Specifies the delayed protection mode 
                                          This parameter can be a value of @ref HRTIM_TimerDelayedProtectionMode */
  uint32_t UpdateTrigger;             /*!< Specifies source(s) triggering the timer registers update 
                                            This parameter can be a combination of @ref HRTIM_TimerUpdateTrigger */
  uint32_t ResetTrigger;              /*!< Specifies source(s) triggering the timer counter reset 
                                           This parameter can be a combination of @ref HRTIM_TimerResetTrigger */
  uint32_t ResetUpdate;              /*!< Specifies whether or not registers update is triggered when the timer counter is reset 
                                           This parameter can be a combination of @ref HRTIM_TimerResetUpdate */
} HRTIM_TimerCfgTypeDef;

/** 
  * @brief  Compare unit configuration definition
  */
typedef struct {
  uint32_t CompareValue;         /*!< Specifies the compare value of the timer compare unit 
                                      the minimum value must be greater than or equal to 3 periods of the fHRTIM clock
                                      the maximum value must be less than or equal to 0xFFFF - 1 periods of the fHRTIM clock */
  uint32_t AutoDelayedMode;      /*!< Specifies the auto delayed mode for compare unit 2 or 4 
                                      This parameter can be a value of @ref HRTIM_CompareUnitAutoDelayedMode */
  uint32_t AutoDelayedTimeout;   /*!< Specifies compare value for timing unit 1 or 3 when auto delayed mode with time out is selected 
                                      CompareValue +  AutoDelayedTimeout must be less than 0xFFFF */
} HRTIM_CompareCfgTypeDef;

/** 
  * @brief  Capture unit configuration definition
  */
typedef struct {
  uint32_t Trigger;   /*!< Specifies source(s) triggering the capture 
                           This parameter can be a combination of @ref HRTIM_CaptureUnitTrigger */
} HRTIM_CaptureCfgTypeDef;

/** 
  * @brief  Output configuration definition
  */
typedef struct {
  uint32_t Polarity;              /*!< Specifies the output polarity 
                                       This parameter can be any value of @ref HRTIM_Output_Polarity */
  uint32_t SetSource;             /*!< Specifies the event(s) transitioning the output from its inactive level to its active level  
                                       This parameter can be any value of @ref HRTIM_OutputSetSource */
  uint32_t ResetSource;           /*!< Specifies the event(s) transitioning the output from its active level to its inactive level  
                                       This parameter can be any value of @ref HRTIM_OutputResetSource */
  uint32_t IdleMode;              /*!< Specifies whether or not the output is affected by a burst mode operation  
                                       This parameter can be any value of @ref HRTIM_OutputIdleMode */
  uint32_t IdleState;             /*!< Specifies whether the output level is active or inactive when in IDLE state  
                                       This parameter can be any value of @ref HRTIM_OutputIDLEState */
  uint32_t FaultState;            /*!< Specifies whether the output level is active or inactive when in FAULT state  
                                       This parameter can be any value of @ref HRTIM_OutputFAULTState */
  uint32_t ChopperModeEnable;     /*!< Indicates whether or not the chopper mode is enabled 
                                       This parameter can be any value of @ref HRTIM_OutputChopperModeEnable */
  uint32_t BurstModeEntryDelayed;  /* !<Indicates whether or not deadtime is inserted when entering the IDLE state
                                        during a burst mode operation
                                        This parameters can be any value of @ref HRTIM_OutputBurstModeEntryDelayed */
} HRTIM_OutputCfgTypeDef;

/** 
  * @brief  External event filtering in timing units configuration definition
  */ 
typedef struct {
  uint32_t Filter;       /*!< Specifies the type of event filtering within the timing unit 
                             This parameter can be a value of @ref HRTIM_TimerExternalEventFilter */ 
  uint32_t Latch;       /*!< Specifies whether or not the signal is latched
                             This parameter can be a value of @ref HRTIM_TimerExternalEventLatch */
} HRTIM_TimerEventFilteringCfgTypeDef;

/** 
  * @brief  Dead time feature configuration definition
  */
typedef struct {
  uint32_t Prescaler;       /*!< Specifies the Deadtime Prescaler 
                                 This parameter can be a number between 0x0 and = 0x7 */ 
  uint32_t RisingValue;     /*!< Specifies the Deadtime following a rising edge 
                                 This parameter can be a number between 0x0 and 0xFF */ 
  uint32_t RisingSign;      /*!< Specifies whether the deadtime is positive or negative on rising edge
                                 This parameter can be a value of @ref HRTIM_DeadtimeRisingSign */ 
  uint32_t RisingLock;      /*!< Specifies whether or not deadtime rising settings (value and sign) are write protected 
                                 This parameter can be a value of @ref HRTIM_DeadtimeRisingLock */ 
  uint32_t RisingSignLock;  /*!< Specifies whether or not deadtime rising sign is write protected 
                                 This parameter can be a value of @ref HRTIM_DeadtimeRisingSignLock */ 
  uint32_t FallingValue;    /*!< Specifies the Deadtime following a falling edge 
                                This parameter can be a number between 0x0 and 0xFF */ 
  uint32_t FallingSign;     /*!< Specifies whether the deadtime is positive or negative on falling edge 
                                This parameter can be a value of @ref HRTIM_DeadtimeFallingSign */ 
  uint32_t FallingLock;     /*!< Specifies whether or not deadtime falling settings (value and sign) are write protected 
                                This parameter can be a value of @ref HRTIM_DeadtimeFallingLock */ 
  uint32_t FallingSignLock; /*!< Specifies whether or not deadtime falling sign is write protected 
                                This parameter can be a value of @ref HRTIM_DeadtimeFallingSignLock */ 
} HRTIM_DeadTimeCfgTypeDef;

/** 
  * @brief  Chopper mode configuration definition
  */
typedef struct {
  uint32_t CarrierFreq;  /*!< Specifies the Timer carrier frequency value.
                              This parameter can be a value between 0 and 0xF */
  uint32_t DutyCycle;   /*!< Specifies the Timer chopper duty cycle value.
                             This parameter can be a value between 0 and 0x7 */
  uint32_t StartPulse;  /*!< Specifies the Timer pulse width value.
                             This parameter can be a value between 0 and 0xF */   
} HRTIM_ChopperModeCfgTypeDef;

/** 
  * @brief  Master synchronization configuration definition
  */
typedef struct {
  uint32_t SyncInputSource;     /*!< Specifies the external synchronization input source 
                                     This parameter can be a value of @ref HRTIM_SynchronizationInputSource */
  uint32_t SyncOutputSource;    /*!< Specifies the source and event to be sent on the external synchronization outputs 
                                     This parameter can be a value of @ref HRTIM_SynchronizationOutputSource */
  uint32_t SyncOutputPolarity;  /*!< Specifies the conditioning of the event to be sent on the external synchronization outputs 
                                     This parameter can be a value of @ref HRTIM_SynchronizationOutputPolarity */
} HRTIM_SynchroCfgTypeDef;

/** 
  * @brief  External event channel configuration definition
  */ 
typedef struct {
  uint32_t Source;        /*!< Identifies the source of the external event 
                                This parameter can be a value of @ref HRTIM_ExternalEventSources */ 
  uint32_t Polarity;      /*!< Specifies the polarity of the external event (in case of level sensitivity) 
                               This parameter can be a value of @ref HRTIM_ExternalEventPolarity */ 
  uint32_t Sensitivity;   /*!< Specifies the sensitivity of the external event 
                               This parameter can be a value of @ref HRTIM_ExternalEventSensitivity */ 
  uint32_t Filter;        /*!< Defines the frequency used to sample the External Event and the length of the digital filter 
                               This parameter can be a value of @ref HRTIM_ExternalEventFilter */ 
  uint32_t FastMode;     /*!< Indicates whether or not low latency mode is enabled for the external event 
                              This parameter can be a value of @ref HRTIM_ExternalEventFastMode */
} HRTIM_EventCfgTypeDef;

/** 
  * @brief  Fault channel configuration definition
  */ 
typedef struct {
  uint32_t Source;        /*!< Identifies the source of the fault 
                                This parameter can be a value of @ref HRTIM_FaultSources */ 
  uint32_t Polarity;      /*!< Specifies the polarity of the fault event 
                               This parameter can be a value of @ref HRTIM_FaultPolarity */ 
  uint32_t Filter;        /*!< Defines the frequency used to sample the Fault input and the length of the digital filter 
                               This parameter can be a value of @ref HRTIM_FaultFilter */ 
  uint32_t Lock;          /*!< Indicates whether or not fault programming bits are write protected 
                              This parameter can be a value of @ref HRTIM_FaultLock */
} HRTIM_FaultCfgTypeDef;

/** 
  * @brief  Burst mode configuration definition
  */
typedef struct {
  uint32_t Mode;           /*!< Specifies the burst mode operating mode
                                This parameter can be a value of @ref HRTIM_BurstModeOperatingMode */
  uint32_t ClockSource;    /*!< Specifies the burst mode clock source
                                This parameter can be a value of @ref HRTIM_BurstModeClockSource */
  uint32_t Prescaler;      /*!< Specifies the burst mode prescaler
                                This parameter can be a value of @ref HRTIM_BurstModePrescaler */
  uint32_t PreloadEnable;  /*!< Specifies whether or not preload is enabled for burst mode related registers (HRTIM_BMCMPR and HRTIM_BMPER)
                                This parameter can be a combination of @ref HRTIM_BurstModeRegisterPreloadEnable  */
  uint32_t Trigger;        /*!< Specifies the event(s) triggering the burst operation 
                                This parameter can be a combination of @ref HRTIM_BurstModeTrigger  */
  uint32_t IdleDuration;   /*!< Specifies number of periods during which the selected timers are in idle state 
                                This parameter can be a number between 0x0 and 0xFFFF  */
  uint32_t Period;        /*!< Specifies burst mode repetition period 
                                This parameter can be a number between 0x1 and 0xFFFF  */
} HRTIM_BurstModeCfgTypeDef;

/** 
  * @brief  ADC trigger configuration definition
  */
typedef struct {
  uint32_t UpdateSource;  /*!< Specifies the ADC trigger update source  
                               This parameter can be a combination of @ref HRTIM_ADCTriggerUpdateSource  */
  uint32_t Trigger;      /*!< Specifies the event(s) triggering the ADC conversion  
                              This parameter can be a combination of @ref HRTIM_ADCTriggerEvent  */
} HRTIM_ADCTriggerCfgTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup HRTIM_Exported_Constants
  * @{
  */

/** @defgroup HRTIM_TimerIndex 
  * @{
  * @brief Constants defining the timer indexes
  */
#define HRTIM_TIMERINDEX_TIMER_A (uint32_t)0x0   /*!< Index associated to timer A */
#define HRTIM_TIMERINDEX_TIMER_B (uint32_t)0x1   /*!< Index associated to timer B */
#define HRTIM_TIMERINDEX_TIMER_C (uint32_t)0x2   /*!< Index associated to timer C */
#define HRTIM_TIMERINDEX_TIMER_D (uint32_t)0x3   /*!< Index associated to timer D */
#define HRTIM_TIMERINDEX_TIMER_E (uint32_t)0x4   /*!< Index associated to timer E */
#define HRTIM_TIMERINDEX_MASTER  (uint32_t)0x5   /*!< Index associated to master timer */
#define HRTIM_COMMONINDEX        (uint32_t)0x6   /*!< Index associated to Common space */

#define IS_HRTIM_TIMERINDEX(TIMERINDEX)\
    (((TIMERINDEX) == HRTIM_TIMERINDEX_MASTER)   || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_A)  || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_B)  || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_C)  || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_D)  || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_E))

#define IS_HRTIM_TIMING_UNIT(TIMERINDEX)\
     (((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_A)  || \
      ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_B)  || \
      ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_C)  || \
      ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_D)  || \
      ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_E))
/**
  * @}
  */
    
/** @defgroup HRTIM_TimerIdentifier 
  * @{
  * @brief Constants defining timer identifiers
  */ 
#define HRTIM_TIMERID_MASTER  (HRTIM_MCR_MCEN)   /*!< Master identifier*/
#define HRTIM_TIMERID_TIMER_A (HRTIM_MCR_TACEN)  /*!< Timer A identifier */
#define HRTIM_TIMERID_TIMER_B (HRTIM_MCR_TBCEN)  /*!< Timer B identifier */
#define HRTIM_TIMERID_TIMER_C (HRTIM_MCR_TCCEN)  /*!< Timer C identifier */
#define HRTIM_TIMERID_TIMER_D (HRTIM_MCR_TDCEN)  /*!< Timer D identifier */
#define HRTIM_TIMERID_TIMER_E (HRTIM_MCR_TECEN)  /*!< Timer E identifier */

#define IS_HRTIM_TIMERID(TIMERID)\
    (((TIMERID) == HRTIM_TIMERID_MASTER)   || \
     ((TIMERID) == HRTIM_TIMERID_TIMER_A)  || \
     ((TIMERID) == HRTIM_TIMERID_TIMER_B)  || \
     ((TIMERID) == HRTIM_TIMERID_TIMER_C)  || \
     ((TIMERID) == HRTIM_TIMERID_TIMER_D)  || \
     ((TIMERID) == HRTIM_TIMERID_TIMER_E))
/**
 * @}
 */
    
/** @defgroup HRTIM_CompareUnit 
  * @{
  * @brief Constants defining compare unit identifiers
  */  
#define HRTIM_COMPAREUNIT_1 (uint32_t)0x00000001  /*!< Compare unit 1 identifier */
#define HRTIM_COMPAREUNIT_2 (uint32_t)0x00000002  /*!< Compare unit 2 identifier */
#define HRTIM_COMPAREUNIT_3 (uint32_t)0x00000004  /*!< Compare unit 3 identifier */
#define HRTIM_COMPAREUNIT_4 (uint32_t)0x00000008  /*!< Compare unit 4 identifier */

#define IS_HRTIM_COMPAREUNIT(COMPAREUNIT)\
    (((COMPAREUNIT) == HRTIM_COMPAREUNIT_1)  || \
     ((COMPAREUNIT) == HRTIM_COMPAREUNIT_2)  || \
     ((COMPAREUNIT) == HRTIM_COMPAREUNIT_3)  || \
     ((COMPAREUNIT) == HRTIM_COMPAREUNIT_4))
 /**
  * @}
  */
    
/** @defgroup HRTIM_CaptureUnit 
  * @{
  * @brief Constants defining capture unit identifiers
  */  
#define HRTIM_CAPTUREUNIT_1 (uint32_t)0x00000001  /*!< Capture unit 1 identifier */
#define HRTIM_CAPTUREUNIT_2 (uint32_t)0x00000002  /*!< Capture unit 2 identifier */

#define IS_HRTIM_CAPTUREUNIT(CAPTUREUNIT)\
    (((CAPTUREUNIT) == HRTIM_CAPTUREUNIT_1)   || \
     ((CAPTUREUNIT) == HRTIM_CAPTUREUNIT_2))
/**
  * @}
  */
 
/** @defgroup HRTIM_TimerOutput 
  * @{
  * @brief Constants defining timer output identifiers
  */  
#define HRTIM_OUTPUT_TA1  (uint32_t)0x00000001  /*!< Timer A - Output 1 identifier */
#define HRTIM_OUTPUT_TA2  (uint32_t)0x00000002  /*!< Timer A - Output 2 identifier */
#define HRTIM_OUTPUT_TB1  (uint32_t)0x00000004  /*!< Timer B - Output 1 identifier */
#define HRTIM_OUTPUT_TB2  (uint32_t)0x00000008  /*!< Timer B - Output 2 identifier */
#define HRTIM_OUTPUT_TC1  (uint32_t)0x00000010  /*!< Timer C - Output 1 identifier */
#define HRTIM_OUTPUT_TC2  (uint32_t)0x00000020  /*!< Timer C - Output 2 identifier */
#define HRTIM_OUTPUT_TD1  (uint32_t)0x00000040  /*!< Timer D - Output 1 identifier */
#define HRTIM_OUTPUT_TD2  (uint32_t)0x00000080  /*!< Timer D - Output 2 identifier */
#define HRTIM_OUTPUT_TE1  (uint32_t)0x00000100  /*!< Timer E - Output 1 identifier */
#define HRTIM_OUTPUT_TE2  (uint32_t)0x00000200  /*!< Timer E - Output 2 identifier */
      
#define IS_HRTIM_OUTPUT(OUTPUT)\
    (((OUTPUT) == HRTIM_OUTPUT_TA1)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TA2)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TB1)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TB2)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TC1)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TC2)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TD1)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TD2)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TE1)   || \
     ((OUTPUT) == HRTIM_OUTPUT_TE2))
      
#define IS_HRTIM_TIMER_OUTPUT(TIMER, OUTPUT)\
    ((((TIMER) == HRTIM_TIMERINDEX_TIMER_A) &&   \
     (((OUTPUT) == HRTIM_OUTPUT_TA1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TA2)))           \
    ||                                           \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_B) &&    \
     (((OUTPUT) == HRTIM_OUTPUT_TB1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TB2)))           \
    ||                                           \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_C) &&    \
     (((OUTPUT) == HRTIM_OUTPUT_TC1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TC2)))           \
    ||                                           \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_D) &&    \
     (((OUTPUT) == HRTIM_OUTPUT_TD1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TD2)))           \
    ||                                           \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_E) &&    \
     (((OUTPUT) == HRTIM_OUTPUT_TE1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TE2))))
/**
  * @}
  */
    
/** @defgroup HRTIM_ADCTrigger
  * @{
  * @brief Constants defining ADC triggers identifiers
  */
#define HRTIM_ADCTRIGGER_1  (uint32_t)0x00000001  /*!< ADC trigger 1 identifier */
#define HRTIM_ADCTRIGGER_2  (uint32_t)0x00000002  /*!< ADC trigger 1 identifier */
#define HRTIM_ADCTRIGGER_3  (uint32_t)0x00000004  /*!< ADC trigger 1 identifier */
#define HRTIM_ADCTRIGGER_4  (uint32_t)0x00000008  /*!< ADC trigger 1 identifier */

#define IS_HRTIM_ADCTRIGGER(ADCTRIGGER)\
    (((ADCTRIGGER) == HRTIM_ADCTRIGGER_1)   || \
     ((ADCTRIGGER) == HRTIM_ADCTRIGGER_2)   || \
     ((ADCTRIGGER) == HRTIM_ADCTRIGGER_3)   || \
     ((ADCTRIGGER) == HRTIM_ADCTRIGGER_4))
/**
  * @}
  */

/** @defgroup HRTIM_ExternalEventChannels
  * @{
  * @brief Constants defining external event channel identifiers
  */
#define HRTIM_EVENT_NONE     ((uint32_t)0x00000000)     /*!< Undefined event channel */
#define HRTIM_EVENT_1        ((uint32_t)0x00000001)     /*!< External event channel 1 identifier */
#define HRTIM_EVENT_2        ((uint32_t)0x00000002)     /*!< External event channel 2 identifier */
#define HRTIM_EVENT_3        ((uint32_t)0x00000004)     /*!< External event channel 3 identifier */
#define HRTIM_EVENT_4        ((uint32_t)0x00000008)     /*!< External event channel 4 identifier */
#define HRTIM_EVENT_5        ((uint32_t)0x00000010)     /*!< External event channel 5 identifier */
#define HRTIM_EVENT_6        ((uint32_t)0x00000020)     /*!< External event channel 6 identifier */
#define HRTIM_EVENT_7        ((uint32_t)0x00000040)     /*!< External event channel 7 identifier */
#define HRTIM_EVENT_8        ((uint32_t)0x00000080)     /*!< External event channel 8 identifier */
#define HRTIM_EVENT_9        ((uint32_t)0x00000100)     /*!< External event channel 9 identifier */
#define HRTIM_EVENT_10       ((uint32_t)0x00000200)     /*!< External event channel 10 identifier */

#define IS_HRTIM_EVENT(EVENT)\
      (((EVENT) == HRTIM_EVENT_1)   || \
       ((EVENT) == HRTIM_EVENT_2)   || \
       ((EVENT) == HRTIM_EVENT_3)   || \
       ((EVENT) == HRTIM_EVENT_4)   || \
       ((EVENT) == HRTIM_EVENT_5)   || \
       ((EVENT) == HRTIM_EVENT_6)   || \
       ((EVENT) == HRTIM_EVENT_7)   || \
       ((EVENT) == HRTIM_EVENT_8)   || \
       ((EVENT) == HRTIM_EVENT_9)   || \
       ((EVENT) == HRTIM_EVENT_10))
/**
  * @}
  */
    
/** @defgroup HRTIM_FaultChannel
  * @{
  * @brief Constants defining fault channel identifiers
  */ 
#define HRTIM_FAULT_1      ((uint32_t)0x01)     /*!< Fault channel 1 identifier */
#define HRTIM_FAULT_2      ((uint32_t)0x02)     /*!< Fault channel 2 identifier */
#define HRTIM_FAULT_3      ((uint32_t)0x04)     /*!< Fault channel 3 identifier */
#define HRTIM_FAULT_4      ((uint32_t)0x08)     /*!< Fault channel 4 identifier */
#define HRTIM_FAULT_5      ((uint32_t)0x10)     /*!< Fault channel 5 identifier */

#define IS_HRTIM_FAULT(FAULT)\
      (((FAULT) == HRTIM_FAULT_1)   || \
       ((FAULT) == HRTIM_FAULT_2)   || \
       ((FAULT) == HRTIM_FAULT_3)   || \
       ((FAULT) == HRTIM_FAULT_4)   || \
       ((FAULT) == HRTIM_FAULT_5))
/**
  * @}
  */


 /** @defgroup HRTIM_PrescalerRatio 
  * @{
  * @brief Constants defining timer high-resolution clock prescaler ratio.
  */  
#define HRTIM_PRESCALERRATIO_MUL32    ((uint32_t)0x00000000)  /*!< fHRCK: 4.608 GHz - Resolution: 217 ps - Min PWM frequency: 70.3 kHz (fHRTIM=144MHz)      */
#define HRTIM_PRESCALERRATIO_MUL16    ((uint32_t)0x00000001)  /*!< fHRCK: 2.304 GHz - Resolution: 434 ps - Min PWM frequency: 35.1 KHz (fHRTIM=144MHz)      */
#define HRTIM_PRESCALERRATIO_MUL8     ((uint32_t)0x00000002)  /*!< fHRCK: 1.152 GHz - Resolution: 868 ps - Min PWM frequency: 17.6 kHz (fHRTIM=144MHz)      */
#define HRTIM_PRESCALERRATIO_MUL4     ((uint32_t)0x00000003)  /*!< fHRCK: 576 MHz - Resolution: 1.73 ns - Min PWM frequency: 8.8 kHz (fHRTIM=144MHz)      */
#define HRTIM_PRESCALERRATIO_MUL2     ((uint32_t)0x00000004)  /*!< fHRCK: 288 MHz - Resolution: 3.47 ns - Min PWM frequency: 4.4 kHz (fHRTIM=144MHz)      */
#define HRTIM_PRESCALERRATIO_DIV1     ((uint32_t)0x00000005)  /*!< fHRCK: 144 MHz - Resolution: 6.95 ns - Min PWM frequency: 2.2 kHz (fHRTIM=144MHz)      */
#define HRTIM_PRESCALERRATIO_DIV2     ((uint32_t)0x00000006)  /*!< fHRCK: 72 MHz - Resolution: 13.88 ns- Min PWM frequency: 1.1 kHz (fHRTIM=144MHz)      */
#define HRTIM_PRESCALERRATIO_DIV4     ((uint32_t)0x00000007)  /*!< fHRCK: 36 MHz - Resolution: 27.7 ns- Min PWM frequency: 550Hz (fHRTIM=144MHz)      */

#define IS_HRTIM_PRESCALERRATIO(PRESCALERRATIO)\
        (((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_MUL32) || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_MUL16) || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_MUL8)  || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_MUL4)  || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_MUL2)  || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_DIV1)  || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_DIV2)  || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_DIV4))        
/**
  * @}
  */

  /** @defgroup HRTIM_DeadtimePrescaler 
  * @{
  * @brief Constants defining timer deadtime clock.
  */  
#define HRTIM_DEADTIMPRESCALERRATIO_MUL1    ((uint32_t)0x00000000)  /* tDTx min 0.87 ns, max 0.44 us */
#define HRTIM_DEADTIMPRESCALERRATIO_MUL2    ((uint32_t)0x00000001)  /* tDTx min 1.74 ns, max 0.89 us */
#define HRTIM_DEADTIMPRESCALERRATIO_MUL4    ((uint32_t)0x00000002)  /* tDTx min 3.47 ns, max 1.77 us */ 
#define HRTIM_DEADTIMPRESCALERRATIO_MUL8    ((uint32_t)0x00000003)  /* tDTx min 6.94 ns, max 3.54 us */ 
#define HRTIM_DEADTIMPRESCALERRATIO_MUL16   ((uint32_t)0x00000004)  /* tDTx min 13.89 ns, max 7.10 us */ 
#define HRTIM_DEADTIMPRESCALERRATIO_MUL32   ((uint32_t)0x00000005)  /* tDTx min 27.78 ns, max 14.19 us */  
#define HRTIM_DEADTIMPRESCALERRATIO_MUL64   ((uint32_t)0x00000006)  /* tDTx min 55.55 ns, max 28.39 us */
#define HRTIM_DEADTIMPRESCALERRATIO_MUL128  ((uint32_t)0x00000007)  /* tDTx min 111.10 ns, max 56.77 us */     
/**
  * @}
  */ 

/** @defgroup HRTIM_Mode 
  * @{
  * @brief Constants defining timer counter operating mode.
  */  
#define HRTIM_MODE_CONTINOUS                ((uint32_t)0x00000008)  /*!< The timer operates in continuous (free-running) mode */
#define HRTIM_MODE_SINGLESHOT               ((uint32_t)0x00000000)  /*!< The timer operates in non retriggerable single-shot mode */
#define HRTIM_MODE_SINGLESHOT_RETRIGGERABLE ((uint32_t)0x00000010)  /*!< The timer operates in retriggerable single-shot mode */

#define IS_HRTIM_MODE(MODE)\
          (((MODE) == HRTIM_MODE_CONTINOUS)  ||  \
           ((MODE) == HRTIM_MODE_SINGLESHOT) || \
           ((MODE) == HRTIM_MODE_SINGLESHOT_RETRIGGERABLE))
            
#define IS_HRTIM_MODE_ONEPULSE(MODE)\
          (((MODE) == HRTIM_MODE_SINGLESHOT) || \
           ((MODE) == HRTIM_MODE_SINGLESHOT_RETRIGGERABLE))
            
/**
  * @}
  */
  
/** @defgroup HRTIM_HalfModeEnable 
  * @{
  * @brief Constants defining half mode enabling status.
  */  
#define HRTIM_HALFMODE_DISABLED ((uint32_t)0x00000000)  /*!< Half mode is disabled */
#define HRTIM_HALFMODE_ENABLED  ((uint32_t)0x00000020)  /*!< Half mode is enabled */

#define IS_HRTIM_HALFMODE(HALFMODE)\
            (((HALFMODE) == HRTIM_HALFMODE_DISABLED)  ||  \
             ((HALFMODE) == HRTIM_HALFMODE_ENABLED))
/**
  * @}
  */
              
/** @defgroup HRTIM_StartOnSyncInputEvent 
  * @{
  * @brief Constants defining the timer behaviour following the synchronization event
  */
#define HRTIM_SYNCSTART_DISABLED ((uint32_t)0x00000000)  /*!< Synchronization input event has effect on the timer */
#define HRTIM_SYNCSTART_ENABLED  (HRTIM_MCR_SYNCSTRTM)   /*!< Synchronization input event starts the timer */

#define IS_HRTIM_SYNCSTART(SYNCSTART)\
              (((SYNCSTART) == HRTIM_SYNCSTART_DISABLED)  ||  \
               ((SYNCSTART) == HRTIM_SYNCSTART_ENABLED))
/**
  * @}
  */
              
/** @defgroup HRTIM_ResetOnSyncInputEvent 
  * @{
  * @brief Constants defining the timer behaviour following the synchronization event
  */  
#define HRTIM_SYNCRESET_DISABLED ((uint32_t)0x00000000)  /*!< Synchronization input event has effect on the timer */
#define HRTIM_SYNCRESET_ENABLED  (HRTIM_MCR_SYNCRSTM)    /*!< Synchronization input event resets the timer */

#define IS_HRTIM_SYNCRESET(SYNCRESET)\
                (((SYNCRESET) == HRTIM_SYNCRESET_DISABLED)  ||  \
                 ((SYNCRESET) == HRTIM_SYNCRESET_ENABLED))
/**
  * @}
  */    

/** @defgroup HRTIM_DACSynchronization 
  * @{
  * @brief Constants defining on which output the DAC synchronization event is sent
  */ 
#define HRTIM_DACSYNC_NONE          (uint32_t)0x00000000                        /*!< No DAC synchronization event generated */
#define HRTIM_DACSYNC_DACTRIGOUT_1  (HRTIM_MCR_DACSYNC_0)                       /*!< DAC synchronization event generated on DACTrigOut1 output upon timer update */
#define HRTIM_DACSYNC_DACTRIGOUT_2  (HRTIM_MCR_DACSYNC_1)                       /*!< DAC synchronization event generated on DACTrigOut2 output upon timer update */
#define HRTIM_DACSYNC_DACTRIGOUT_3  (HRTIM_MCR_DACSYNC_1 | HRTIM_MCR_DACSYNC_0) /*!< DAC update generated on DACTrigOut3 output upon timer update */

#define IS_HRTIM_DACSYNC(DACSYNC)\
                (((DACSYNC) == HRTIM_DACSYNC_NONE)          ||  \
                 ((DACSYNC) == HRTIM_DACSYNC_DACTRIGOUT_1)  ||  \
                 ((DACSYNC) == HRTIM_DACSYNC_DACTRIGOUT_2)  ||  \
                 ((DACSYNC) == HRTIM_DACSYNC_DACTRIGOUT_3))
/**
  * @}
  */         

/** @defgroup HRTIM_RegisterPreloadEnable 
  * @{
  * @brief Constants defining whether a write access into a preloadable
  *        register is done into the active or the preload register.
  */  
#define HRTIM_PRELOAD_DISABLED ((uint32_t)0x00000000)  /*!< Preload disabled: the write access is directly done into the active register */
#define HRTIM_PRELOAD_ENABLED  (HRTIM_MCR_PREEN)       /*!< Preload enabled: the write access is done into the preload register */

#define IS_HRTIM_PRELOAD(PRELOAD)\
                (((PRELOAD) == HRTIM_PRELOAD_DISABLED)  ||  \
                 ((PRELOAD) == HRTIM_PRELOAD_ENABLED))
/**
  * @}
  */   

/** @defgroup HRTIM_UpdateGating 
  * @{
  * @brief Constants defining how the update occurs relatively to the burst DMA 
  *        transaction and the external update request on update enable inputs 1 to 3.
  */
#define HRTIM_UPDATEGATING_INDEPENDENT     (uint32_t)0x00000000                                                  /*!< Update done independently from the DMA burst transfer completion */
#define HRTIM_UPDATEGATING_DMABURST        (HRTIM_TIMCR_UPDGAT_0)                                                /*!< Update done when the DMA burst transfer is completed */
#define HRTIM_UPDATEGATING_DMABURST_UPDATE (HRTIM_TIMCR_UPDGAT_1)                                                /*!< Update done on timer roll-over following a DMA burst transfer completion*/
#define HRTIM_UPDATEGATING_UPDEN1          (HRTIM_TIMCR_UPDGAT_1 | HRTIM_TIMCR_UPDGAT_0)                         /*!< Slave timer only - Update done on a rising edge of HRTIM update enable input 1 */
#define HRTIM_UPDATEGATING_UPDEN2          (HRTIM_TIMCR_UPDGAT_2)                                                /*!< Slave timer only - Update done on a rising edge of HRTIM update enable input 2 */
#define HRTIM_UPDATEGATING_UPDEN3          (HRTIM_TIMCR_UPDGAT_2 | HRTIM_TIMCR_UPDGAT_0)                         /*!< Slave timer only - Update done on a rising edge of HRTIM update enable input 3 */
#define HRTIM_UPDATEGATING_UPDEN1_UPDATE   (HRTIM_TIMCR_UPDGAT_2 | HRTIM_TIMCR_UPDGAT_1)                         /*!< Slave timer only -  Update done on the update event following a rising edge of HRTIM update enable input 1 */
#define HRTIM_UPDATEGATING_UPDEN2_UPDATE   (HRTIM_TIMCR_UPDGAT_2 | HRTIM_TIMCR_UPDGAT_1 | HRTIM_TIMCR_UPDGAT_0)  /*!< Slave timer only -  Update done on the update event following a rising edge of HRTIM update enable input 2 */
#define HRTIM_UPDATEGATING_UPDEN3_UPDATE   (HRTIM_TIMCR_UPDGAT_3)                                                /*!< Slave timer only -  Update done on the update event following a rising edge of HRTIM update enable input 3 */

#define IS_HRTIM_UPDATEGATING_MASTER(UPDATEGATING)\
                (((UPDATEGATING) == HRTIM_UPDATEGATING_INDEPENDENT)      ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_DMABURST)         ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_DMABURST_UPDATE))
                  
#define IS_HRTIM_UPDATEGATING_TIM(UPDATEGATING)\
                (((UPDATEGATING) == HRTIM_UPDATEGATING_INDEPENDENT)      ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_DMABURST)         ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_DMABURST_UPDATE)  ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN1)           ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN2)           ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN3)           ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN1_UPDATE)    ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN2_UPDATE)    ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN3_UPDATE))                  
/**
  * @}
  */ 
                  
/** @defgroup HRTIM_TimerBurstMode 
  * @{
  * @brief Constants defining how the timer behaves during a burst
            mode operation.
  */
#define HRTIM_TIMERBURSTMODE_MAINTAINCLOCK (uint32_t)0x000000 /*!< Timer counter clock is maintained and the timer operates normally */
#define HRTIM_TIMERBURSTMODE_RESETCOUNTER  (HRTIM_BMCR_MTBM)  /*!< Timer counter clock is stopped and the counter is reset */

#define IS_HRTIM_TIMERBURSTMODE(TIMERBURSTMODE)                               \
                (((TIMERBURSTMODE) == HRTIM_TIMERBURSTMODE_MAINTAINCLOCK)  || \
                 ((TIMERBURSTMODE) == HRTIM_TIMERBURSTMODE_RESETCOUNTER))
/**
  * @}
  */ 

/** @defgroup HRTIM_TimerRepetitionUpdate
  * @{
  * @brief Constants defining whether registers are updated when the timer
  *        repetition period is completed (either due to roll-over or
  *        reset events)
  */
#define HRTIM_UPDATEONREPETITION_DISABLED (uint32_t)0x00000000 /*!< Update on repetition disabled */
#define HRTIM_UPDATEONREPETITION_ENABLED  (HRTIM_MCR_MREPU)    /*!< Update on repetition enabled */

#define IS_HRTIM_UPDATEONREPETITION(UPDATEONREPETITION)                               \
                (((UPDATEONREPETITION) == HRTIM_UPDATEONREPETITION_DISABLED)  || \
                 ((UPDATEONREPETITION) == HRTIM_UPDATEONREPETITION_ENABLED))
/**
  * @}
  */
            

/** @defgroup HRTIM_TimerPushPullMode
  * @{
  * @brief Constants defining whether or not the push-pull mode is enabled for
  *        a timer.
  */
#define HRTIM_TIMPUSHPULLMODE_DISABLED   ((uint32_t)0x00000000)          /*!< Push-Pull mode disabled */ 
#define HRTIM_TIMPUSHPULLMODE_ENABLED    ((uint32_t)HRTIM_TIMCR_PSHPLL)  /*!< Push-Pull mode enabled */

#define IS_HRTIM_TIMPUSHPULLMODE(TIMPUSHPULLMODE)\
                  (((TIMPUSHPULLMODE) == HRTIM_TIMPUSHPULLMODE_DISABLED) || \
                   ((TIMPUSHPULLMODE) == HRTIM_TIMPUSHPULLMODE_ENABLED))
/**
  * @}
  */

/** @defgroup HRTIM_TimerFaultEnabling
  * @{
  * @brief Constants defining whether a faut channel is enabled for a timer
  */
#define HRTIM_TIMFAULTENABLE_NONE     (uint32_t)0x00000000  /*!< No fault enabled */ 
#define HRTIM_TIMFAULTENABLE_FAULT1   (HRTIM_FLTR_FLT1EN)   /*!< Fault 1 enabled */ 
#define HRTIM_TIMFAULTENABLE_FAULT2   (HRTIM_FLTR_FLT2EN)   /*!< Fault 2 enabled */ 
#define HRTIM_TIMFAULTENABLE_FAULT3   (HRTIM_FLTR_FLT3EN)   /*!< Fault 3 enabled */
#define HRTIM_TIMFAULTENABLE_FAULT4   (HRTIM_FLTR_FLT4EN)   /*!< Fault 4 enabled */
#define HRTIM_TIMFAULTENABLE_FAULT5   (HRTIM_FLTR_FLT5EN)   /*!< Fault 5 enabled */

#define IS_HRTIM_TIMFAULTENABLE(TIMFAULTENABLE) (((TIMFAULTENABLE) & 0xFFFFFFE0) == 0x00000000)

/**
  * @}
  */

/** @defgroup HRTIM_TimerFaultLock
  * @{
  * @brief Constants defining whether or not fault enabling bits are write 
  *        protected for a timer
  */
#define HRTIM_TIMFAULTLOCK_READWRITE ((uint32_t)0x00000000)  /*!< Timer fault enabling bits are read/write */
#define HRTIM_TIMFAULTLOCK_READONLY  (HRTIM_FLTR_FLTCLK)       /*!< Timer fault enabling bits are read only */

#define IS_HRTIM_TIMFAULTLOCK(TIMFAULTLOCK)\
      (((TIMFAULTLOCK) == HRTIM_TIMFAULTLOCK_READWRITE) || \
       ((TIMFAULTLOCK) == HRTIM_TIMFAULTLOCK_READONLY))
/**
  * @}
  */

/** @defgroup HRTIM_TimerDeadtimeInsertion
  * @{
  * @brief Constants defining whether or not fault the dead time insertion  
  *        feature is enabled for a timer
  */
#define HRTIM_TIMDEADTIMEINSERTION_DISABLED   ((uint32_t)0x00000000)  /*!< Output 1 and output 2 signals are independent */
#define HRTIM_TIMDEADTIMEINSERTION_ENABLED    HRTIM_OUTR_DTEN         /*!< Deadtime is inserted between output 1 and output 2 */

#define IS_HRTIM_TIMDEADTIMEINSERTION(TIMDEADTIMEINSERTION)\
        (((TIMDEADTIMEINSERTION) == HRTIM_TIMDEADTIMEINSERTION_DISABLED) || \
         ((TIMDEADTIMEINSERTION) == HRTIM_TIMDEADTIMEINSERTION_ENABLED))
/**
  * @}
  */

/** @defgroup HRTIM_TimerDelayedProtectionMode
  * @{
  * @brief Constants defining all possible delayed protection modes 
  *        for a timer. Also define the source and outputs on which the delayed 
  *        protection schemes are applied
  */
#define HRTIM_TIMDELAYEDPROTECTION_DISABLED           ((uint32_t)0x00000000)                                                                   /*!< No action */    
#define HRTIM_TIMDELAYEDPROTECTION_DELAYEDOUT1_EEV68  (HRTIM_OUTR_DLYPRTEN)                                                                     /*!< Output 1 delayed Idle on external Event 6 or 8 */      
#define HRTIM_TIMDELAYEDPROTECTION_DELAYEDOUT2_EEV68  (HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                                              /*!< Output 2 delayed Idle on external Event 6 or 8 */      
#define HRTIM_TIMDELAYEDPROTECTION_DELAYEDBOTH_EEV68  (HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRTEN)                                              /*!< Output 1 and output 2 delayed Idle on external Event 6 or 8 */      
#define HRTIM_TIMDELAYEDPROTECTION_BALANCED_EEV68     (HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                        /*!< Balanced Idle on external Event 6 or 8 */      
#define HRTIM_TIMDELAYEDPROTECTION_DELAYEDOUT1_DEEV79 (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRTEN)                                              /*!< Output 1 delayed Idle on external Event 7 or 9 */      
#define HRTIM_TIMDELAYEDPROTECTION_DELAYEDOUT2_DEEV79 (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                        /*!< Output 2 delayed Idle on external Event 7 or 9 */      
#define HRTIM_TIMDELAYEDPROTECTION_DELAYEDBOTH_EEV79  (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRTEN)                        /*!< Output 1 and output2 delayed Idle on external Event 7 or 9 */      
#define HRTIM_TIMDELAYEDPROTECTION_BALANCED_EEV79     (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)  /*!< Balanced Idle on external Event 7 or 9 */      

#define IS_HRTIM_TIMDELAYEDPROTECTION(TIMDELAYEDPROTECTION)\
          (((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_DISABLED)           || \
           ((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_DELAYEDOUT1_EEV68)  || \
           ((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_DELAYEDOUT2_EEV68)  || \
           ((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_DELAYEDBOTH_EEV68)  || \
           ((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_BALANCED_EEV68)     || \
           ((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_DELAYEDOUT1_DEEV79) || \
           ((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_DELAYEDOUT2_DEEV79) || \
           ((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_DELAYEDBOTH_EEV79)  || \
           ((TIMDELAYEDPROTECTION) == HRTIM_TIMDELAYEDPROTECTION_BALANCED_EEV79))
/**
  * @}
  */

/** @defgroup HRTIM_TimerUpdateTrigger
  * @{
  * @brief Constants defining whether the registers update is done synchronously 
  *        with any other timer or master update
  */
#define HRTIM_TIMUPDATETRIGGER_NONE     (uint32_t)0x00000000 /*!< Register update is disabled */    
#define HRTIM_TIMUPDATETRIGGER_MASTER   (HRTIM_TIMCR_MSTU)   /*!< Register update is triggered by the master timer update */    
#define HRTIM_TIMUPDATETRIGGER_TIMER_A  (HRTIM_TIMCR_TAU)    /*!< Register update is triggered by the timer A update */    
#define HRTIM_TIMUPDATETRIGGER_TIMER_B  (HRTIM_TIMCR_TBU)    /*!< Register update is triggered by the timer B update */    
#define HRTIM_TIMUPDATETRIGGER_TIMER_C  (HRTIM_TIMCR_TCU)    /*!< Register update is triggered by the timer C update*/    
#define HRTIM_TIMUPDATETRIGGER_TIMER_D  (HRTIM_TIMCR_TDU)    /*!< Register update is triggered by the timer D update */    
#define HRTIM_TIMUPDATETRIGGER_TIMER_E  (HRTIM_TIMCR_TEU)    /*!< Register update is triggered by the timer E update */    

#define IS_HRTIM_TIMUPDATETRIGGER(TIMUPDATETRIGGER) (((TIMUPDATETRIGGER) & 0xFE07FFFF) == 0x00000000)
/**
  * @}
  */

/** @defgroup HRTIM_TimerResetTrigger
  * @{
  * @brief Constants defining the events that can be selected to trigger the reset 
  *        of the timer counter
  */
#define HRTIM_TIMRESETTRIGGER_NONE        (uint32_t)0x00000000   /*!< No counter reset trigger */    
#define HRTIM_TIMRESETTRIGGER_UPDATE      (HRTIM_RSTR_UPDATE)    /*!< The timer counter is reset upon update event */    
#define HRTIM_TIMRESETTRIGGER_CMP2        (HRTIM_RSTR_CMP2)      /*!< The timer counter is reset upon Timer Compare 2 event */    
#define HRTIM_TIMRESETTRIGGER_CMP4        (HRTIM_RSTR_CMP4)      /*!< The timer counter is reset upon Timer Compare 4 event */    
#define HRTIM_TIMRESETTRIGGER_MASTER_PER  (HRTIM_RSTR_MSTPER)    /*!< The timer counter is reset upon master timer period event */    
#define HRTIM_TIMRESETTRIGGER_MASTER_CMP1 (HRTIM_RSTR_MSTCMP1)   /*!< The timer counter is reset upon master timer Compare 1 event */    
#define HRTIM_TIMRESETTRIGGER_MASTER_CMP2 (HRTIM_RSTR_MSTCMP2)   /*!< The timer counter is reset upon master timer Compare 2 event */    
#define HRTIM_TIMRESETTRIGGER_MASTER_CMP3 (HRTIM_RSTR_MSTCMP3)   /*!< The timer counter is reset upon master timer Compare 3 event */    
#define HRTIM_TIMRESETTRIGGER_MASTER_CMP4 (HRTIM_RSTR_MSTCMP4)   /*!< The timer counter is reset upon master timer Compare 4 event */    
#define HRTIM_TIMRESETTRIGGER_EEV_1       (HRTIM_RSTR_EXTEVNT1)  /*!< The timer counter is reset upon external event 1 */    
#define HRTIM_TIMRESETTRIGGER_EEV_2       (HRTIM_RSTR_EXTEVNT2)  /*!< The timer counter is reset upon external event 2 */    
#define HRTIM_TIMRESETTRIGGER_EEV_3       (HRTIM_RSTR_EXTEVNT3)  /*!< The timer counter is reset upon external event 3 */    
#define HRTIM_TIMRESETTRIGGER_EEV_4       (HRTIM_RSTR_EXTEVNT4)  /*!< The timer counter is reset upon external event 4 */    
#define HRTIM_TIMRESETTRIGGER_EEV_5       (HRTIM_RSTR_EXTEVNT5)  /*!< The timer counter is reset upon external event 5 */    
#define HRTIM_TIMRESETTRIGGER_EEV_6       (HRTIM_RSTR_EXTEVNT6)  /*!< The timer counter is reset upon external event 6 */    
#define HRTIM_TIMRESETTRIGGER_EEV_7       (HRTIM_RSTR_EXTEVNT7)  /*!< The timer counter is reset upon external event 7 */    
#define HRTIM_TIMRESETTRIGGER_EEV_8       (HRTIM_RSTR_EXTEVNT8)  /*!< The timer counter is reset upon external event 8 */    
#define HRTIM_TIMRESETTRIGGER_EEV_9       (HRTIM_RSTR_EXTEVNT9)  /*!< The timer counter is reset upon external event 9 */    
#define HRTIM_TIMRESETTRIGGER_EEV_10      (HRTIM_RSTR_EXTEVNT10) /*!< The timer counter is reset upon external event 10 */    
#define HRTIM_TIMRESETTRIGGER_OTHER1_CMP1 (HRTIM_RSTR_TIMBCMP1)  /*!< The timer counter is reset upon other timer Compare 1 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER1_CMP2 (HRTIM_RSTR_TIMBCMP2)  /*!< The timer counter is reset upon other timer Compare 2 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER1_CMP4 (HRTIM_RSTR_TIMBCMP4)  /*!< The timer counter is reset upon other timer Compare 4 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER2_CMP1 (HRTIM_RSTR_TIMCCMP1)  /*!< The timer counter is reset upon other timer Compare 1 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER2_CMP2 (HRTIM_RSTR_TIMCCMP2)  /*!< The timer counter is reset upon other timer Compare 2 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER2_CMP4 (HRTIM_RSTR_TIMCCMP4)  /*!< The timer counter is reset upon other timer Compare 4 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER3_CMP1 (HRTIM_RSTR_TIMDCMP1)  /*!< The timer counter is reset upon other timer Compare 1 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER3_CMP2 (HRTIM_RSTR_TIMDCMP2)  /*!< The timer counter is reset upon other timer Compare 2 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER3_CMP4 (HRTIM_RSTR_TIMDCMP4)  /*!< The timer counter is reset upon other timer Compare 4 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER4_CMP1 (HRTIM_RSTR_TIMECMP1)  /*!< The timer counter is reset upon other timer Compare 1 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER4_CMP2 (HRTIM_RSTR_TIMECMP2)  /*!< The timer counter is reset upon other timer Compare 2 event */    
#define HRTIM_TIMRESETTRIGGER_OTHER4_CMP4 (HRTIM_RSTR_TIMECMP4)  /*!< The timer counter is reset upon other timer Compare 4 event */    

#define IS_HRTIM_TIMRESETTRIGGER(TIMRESETTRIGGER) (((TIMRESETTRIGGER) & 0x800000001) == 0x00000000)

/**
  * @}
  */

/** @defgroup HRTIM_TimerResetUpdate
  * @{
  * @brief Constants defining whether the register are updated upon Timerx 
  *        counter reset or rollover to 0 after reaching the period value
  *        in continuous mode
  */
#define HRTIM_TIMUPDATEONRESET_DISABLED (uint32_t)0x00000000  /*!< Update by timer x reset / rollover disabled */
#define HRTIM_TIMUPDATEONRESET_ENABLED (HRTIM_TIMCR_TRSTU)    /*!< Update by timer x reset / rollover enabled */

#define IS_HRTIM_TIMUPDATEONRESET(TIMUPDATEONRESET)                       \
              (((TIMUPDATEONRESET) == HRTIM_TIMUPDATEONRESET_DISABLED) || \
               ((TIMUPDATEONRESET) == HRTIM_TIMUPDATEONRESET_ENABLED))
/**
  * @}
  */
              
/** @defgroup HRTIM_CompareUnitAutoDelayedMode
  * @{
  * @brief Constants defining whether the compare register is behaving in 
  *        regular mode (compare match issued as soon as counter equal compare),
  *        or in auto-delayed mode
  */
#define HRTIM_AUTODELAYEDMODE_REGULAR                 ((uint32_t)0x00000000)                          /*!< standard compare mode */    
#define HRTIM_AUTODELAYEDMODE_AUTODELAYED_NOTIMEOUT   (HRTIM_TIMCR_DELCMP2_0)                         /*!< Compare event generated only if a capture has occurred */    
#define HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1 (HRTIM_TIMCR_DELCMP2_1)                         /*!< Compare event generated if a capture has occurred or after a Compare 1 match (timeout if capture event is missing) */    
#define HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3 (HRTIM_TIMCR_DELCMP2_1 | HRTIM_TIMCR_DELCMP2_0) /*!< Compare event generated if a capture has occurred or after a Compare 3 match (timeout if capture event is missing) */    
         
#define IS_HRTIM_AUTODELAYEDMODE(AUTODELAYEDMODE)\
              (((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_REGULAR)                  || \
               ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_NOTIMEOUT)    || \
               ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1)  || \
               ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3))

/* Auto delayed mode is only available for compare units 2 and 4 */
#define IS_HRTIM_COMPAREUNIT_AUTODELAYEDMODE(COMPAREUNIT, AUTODELAYEDMODE)     \
    ((((COMPAREUNIT) == HRTIM_COMPAREUNIT_1) &&                                \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_REGULAR))                    \
    ||                                                                         \
    (((COMPAREUNIT) == HRTIM_COMPAREUNIT_2) &&                                 \
     (((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_REGULAR)                 ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_NOTIMEOUT)   ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1) ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3)))   \
    ||                                                                         \
    (((COMPAREUNIT) == HRTIM_COMPAREUNIT_3) &&                                 \
     ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_REGULAR))                     \
    ||                                                                         \
    (((COMPAREUNIT) == HRTIM_COMPAREUNIT_4) &&                                 \
     (((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_REGULAR)                 ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_NOTIMEOUT)   ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1) ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3))))
/**
  * @}
  */

/** @defgroup HRTIM_BasicOCMode
  * @{
  * @brief Constants defining the behaviour of the output signal when the timer
           operates in basic output compare mode
  */              
#define HRTIM_BASICOCMODE_TOGGLE    ((uint32_t)0x00000001)  /*!< Output toggles when the timer counter reaches the compare value */
#define HRTIM_BASICOCMODE_INACTIVE  ((uint32_t)0x00000002)  /*!< Output forced to active level when the timer counter reaches the compare value */
#define HRTIM_BASICOCMODE_ACTIVE    ((uint32_t)0x00000003)  /*!< Output forced to inactive level when the timer counter reaches the compare value */

#define IS_HRTIM_BASICOCMODE(BASICOCMODE)\
              (((BASICOCMODE) == HRTIM_BASICOCMODE_TOGGLE)   || \
               ((BASICOCMODE) == HRTIM_BASICOCMODE_INACTIVE) || \
               ((BASICOCMODE) == HRTIM_BASICOCMODE_ACTIVE))
/**
  * @}
  */

/** @defgroup HRTIM_OutputPolarity
  * @{
  * @brief Constants defining the polarity of a timer output
  */              
#define HRTIM_OUTPUTPOLARITY_HIGH    ((uint32_t)0x00000000)  /*!< Output is active HIGH */
#define HRTIM_OUTPUTPOLARITY_LOW     (HRTIM_OUTR_POL1)       /*!< Output is active LOW */

#define IS_HRTIM_OUTPUTPOLARITY(OUTPUTPOLARITY)\
              (((OUTPUTPOLARITY) == HRTIM_OUTPUTPOLARITY_HIGH) || \
               ((OUTPUTPOLARITY) == HRTIM_OUTPUTPOLARITY_LOW))
/**
  * @}
  */

/** @defgroup HRTIM_OutputSetSource
  * @{
  * @brief Constants defining the events that can be selected to configure the
  *        set crossbar of a timer output
  */
#define HRTIM_OUTPUTSET_NONE       (uint32_t)0x00000000    /*!< Reset the output set crossbar */
#define HRTIM_OUTPUTSET_RESYNC     (HRTIM_SET1R_RESYNC)    /*!< Timer reset event coming solely from software or SYNC input forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMPER     (HRTIM_SET1R_PER)       /*!< Timer period event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMCMP1    (HRTIM_SET1R_CMP1)      /*!< Timer compare 1 event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMCMP2    (HRTIM_SET1R_CMP2)      /*!< Timer compare 2 event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMCMP3    (HRTIM_SET1R_CMP3)      /*!< Timer compare 3 event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMCMP4    (HRTIM_SET1R_CMP4)      /*!< Timer compare 4 event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERPER  (HRTIM_SET1R_MSTPER)    /*!< The master timer period event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERCMP1 (HRTIM_SET1R_MSTCMP1)   /*!< Master Timer compare 1 event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERCMP2 (HRTIM_SET1R_MSTCMP2)   /*!< Master Timer compare 2 event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERCMP3 (HRTIM_SET1R_MSTCMP3)   /*!< Master Timer compare 3 event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERCMP4 (HRTIM_SET1R_MSTCMP4)   /*!< Master Timer compare 4 event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_1    (HRTIM_SET1R_TIMEVNT1)  /*!< Timer event 1 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_2    (HRTIM_SET1R_TIMEVNT2)  /*!< Timer event 2 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_3    (HRTIM_SET1R_TIMEVNT3)  /*!< Timer event 3 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_4    (HRTIM_SET1R_TIMEVNT4)  /*!< Timer event 4 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_5    (HRTIM_SET1R_TIMEVNT5)  /*!< Timer event 5 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_6    (HRTIM_SET1R_TIMEVNT6)  /*!< Timer event 6 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_7    (HRTIM_SET1R_TIMEVNT7)  /*!< Timer event 7 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_8    (HRTIM_SET1R_TIMEVNT8)  /*!< Timer event 8 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_9    (HRTIM_SET1R_TIMEVNT9)  /*!< Timer event 9 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_1      (HRTIM_SET1R_EXTVNT1)   /*!< External event 1 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_2      (HRTIM_SET1R_EXTVNT2)   /*!< External event 2 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_3      (HRTIM_SET1R_EXTVNT3)   /*!< External event 3 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_4      (HRTIM_SET1R_EXTVNT4)   /*!< External event 4 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_5      (HRTIM_SET1R_EXTVNT5)   /*!< External event 5 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_6      (HRTIM_SET1R_EXTVNT6)   /*!< External event 6 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_7      (HRTIM_SET1R_EXTVNT7)   /*!< External event 7 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_8      (HRTIM_SET1R_EXTVNT8)   /*!< External event 8 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_9      (HRTIM_SET1R_EXTVNT9)   /*!< External event 9 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_10     (HRTIM_SET1R_EXTVNT10)  /*!< External event 10 forces the output to its active state */
#define HRTIM_OUTPUTSET_UPDATE     (HRTIM_SET1R_UPDATE)    /*!< Timer register update event forces the output to its active state */

#define IS_HRTIM_OUTPUTSET(OUTPUTSET)\
              (((OUTPUTSET) == HRTIM_OUTPUTSET_NONE)       || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_RESYNC)     || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMPER)     || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMCMP1)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMCMP2)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMCMP3)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMCMP4)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERPER)  || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERCMP1) || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERCMP2) || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERCMP3) || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERCMP4) || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_1)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_2)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_3)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_4)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_5)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_6)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_7)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_8)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_9)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_1)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_2)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_3)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_4)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_5)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_6)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_7)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_8)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_9)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_10)     || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_UPDATE))
/**
  * @}
  */

/** @defgroup HRTIM_OutputResetSource
  * @{
  * @brief Constants defining the events that can be selected to configure the
  *        set crossbar of a timer output
  */  
#define HRTIM_OUTPUTRESET_NONE       (uint32_t)0x00000000    /*!< Reset the output reset crossbar */
#define HRTIM_OUTPUTRESET_RESYNC     (HRTIM_RST1R_RESYNC)    /*!< Timer reset event coming solely from software or SYNC input forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMPER     (HRTIM_RST1R_PER)       /*!< Timer period event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMCMP1    (HRTIM_RST1R_CMP1)      /*!< Timer compare 1 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMCMP2    (HRTIM_RST1R_CMP2)      /*!< Timer compare 2 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMCMP3    (HRTIM_RST1R_CMP3)      /*!< Timer compare 3 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMCMP4    (HRTIM_RST1R_CMP4)      /*!< Timer compare 4 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERPER  (HRTIM_RST1R_MSTPER)    /*!< The master timer period event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERCMP1 (HRTIM_RST1R_MSTCMP1)   /*!< Master Timer compare 1 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERCMP2 (HRTIM_RST1R_MSTCMP2)   /*!< Master Timer compare 2 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERCMP3 (HRTIM_RST1R_MSTCMP3)   /*!< Master Timer compare 3 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERCMP4 (HRTIM_RST1R_MSTCMP4)   /*!< Master Timer compare 4 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_1    (HRTIM_RST1R_TIMEVNT1)  /*!< Timer event 1 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_2    (HRTIM_RST1R_TIMEVNT2)  /*!< Timer event 2 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_3    (HRTIM_RST1R_TIMEVNT3)  /*!< Timer event 3 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_4    (HRTIM_RST1R_TIMEVNT4)  /*!< Timer event 4 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_5    (HRTIM_RST1R_TIMEVNT5)  /*!< Timer event 5 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_6    (HRTIM_RST1R_TIMEVNT6)  /*!< Timer event 6 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_7    (HRTIM_RST1R_TIMEVNT7)  /*!< Timer event 7 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_8    (HRTIM_RST1R_TIMEVNT8)  /*!< Timer event 8 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_9    (HRTIM_RST1R_TIMEVNT9)  /*!< Timer event 9 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_1      (HRTIM_RST1R_EXTVNT1)   /*!< External event 1 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_2      (HRTIM_RST1R_EXTVNT2)   /*!< External event 2 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_3      (HRTIM_RST1R_EXTVNT3)   /*!< External event 3 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_4      (HRTIM_RST1R_EXTVNT4)   /*!< External event 4 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_5      (HRTIM_RST1R_EXTVNT5)   /*!< External event 5 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_6      (HRTIM_RST1R_EXTVNT6)   /*!< External event 6 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_7      (HRTIM_RST1R_EXTVNT7)   /*!< External event 7 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_8      (HRTIM_RST1R_EXTVNT8)   /*!< External event 8 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_9      (HRTIM_RST1R_EXTVNT9)   /*!< External event 9 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_10     (HRTIM_RST1R_EXTVNT10)  /*!< External event 10 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_UPDATE     (HRTIM_RST1R_UPDATE)    /*!< Timer register update event forces the output to its inactive state */

#define IS_HRTIM_OUTPUTRESET(OUTPUTRESET)\
              (((OUTPUTRESET) == HRTIM_OUTPUTRESET_NONE)       || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_RESYNC)     || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMPER)     || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMCMP1)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMCMP2)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMCMP3)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMCMP4)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERPER)  || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERCMP1) || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERCMP2) || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERCMP3) || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERCMP4) || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_1)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_2)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_3)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_4)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_5)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_6)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_7)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_8)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_9)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_1)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_2)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_3)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_4)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_5)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_6)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_7)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_8)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_9)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_10)     || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_UPDATE))
/**
  * @}
  */

/** @defgroup HRTIM_OutputIdleMode
  * @{
  * @brief Constants defining whether or not the timer output transition to its 
           IDLE state when burst mode is entered
  */  
#define HRTIM_OUTPUTIDLEMODE_NONE     (uint32_t)0x00000000  /*!< The output is not affected by the burst mode operation */
#define HRTIM_OUTPUTIDLEMODE_IDLE     (HRTIM_OUTR_IDLM1)    /*!< The output is in idle state when requested by the burst mode controller */
              
#define IS_HRTIM_OUTPUTIDLEMODE(OUTPUTIDLEMODE)\
              (((OUTPUTIDLEMODE) == HRTIM_OUTPUTIDLEMODE_NONE) || \
               ((OUTPUTIDLEMODE) == HRTIM_OUTPUTIDLEMODE_IDLE))
 /**
  * @}
  */

/** @defgroup HRTIM_OutputIDLEState
  * @{
  * @brief Constants defining the IDLE state of a timer output
  */  
#define HRTIM_OUTPUTIDLESTATE_INACTIVE   (uint32_t)0x00000000  /*!< Output at inactive level when in IDLE state */
#define HRTIM_OUTPUTIDLESTATE_ACTIVE     (HRTIM_OUTR_IDLES1)   /*!< Output at active level when in IDLE state */
              
#define IS_HRTIM_OUTPUTIDLESTATE(OUTPUTIDLESTATE)\
              (((OUTPUTIDLESTATE) == HRTIM_OUTPUTIDLESTATE_INACTIVE) || \
               ((OUTPUTIDLESTATE) == HRTIM_OUTPUTIDLESTATE_ACTIVE))
/**
  * @}
  */

/** @defgroup HRTIM_OutputFAULTState
  * @{
  * @brief Constants defining the FAULT state of a timer output
  */  
#define HRTIM_OUTPUTFAULTSTATE_NONE      (uint32_t)0x00000000                         /*!< The output is not affected by the fault input */
#define HRTIM_OUTPUTFAULTSTATE_ACTIVE    (HRTIM_OUTR_FAULT1_0)                        /*!< Output at active level when in FAULT state */
#define HRTIM_OUTPUTFAULTSTATE_INACTIVE  (HRTIM_OUTR_FAULT1_1)                        /*!< Output at inactive level when in FAULT state */
#define HRTIM_OUTPUTFAULTSTATE_HIGHZ     (HRTIM_OUTR_FAULT1_1 | HRTIM_OUTR_FAULT1_0)  /*!< Output is tri-stated when in FAULT state */
              
#define IS_HRTIM_OUTPUTFAULTSTATE(OUTPUTFAULTSTATE)\
              (((OUTPUTFAULTSTATE) == HRTIM_OUTPUTFAULTSTATE_NONE)     || \
               ((OUTPUTFAULTSTATE) == HRTIM_OUTPUTFAULTSTATE_ACTIVE)   || \
               ((OUTPUTFAULTSTATE) == HRTIM_OUTPUTFAULTSTATE_INACTIVE) || \
               ((OUTPUTFAULTSTATE) == HRTIM_OUTPUTFAULTSTATE_HIGHZ))
/**
  * @}
  */

/** @defgroup HRTIM_OutputChopperModeEnable
  * @{
  * @brief Constants defining whether or not chopper mode is enabled for a timer
           output
  */  
#define HRTIM_OUTPUTCHOPPERMODE_DISABLED   (uint32_t)0x00000000  /*!< The output is not affected by the fault input */
#define HRTIM_OUTPUTCHOPPERMODE_ENABLED    (HRTIM_OUTR_CHP1)     /*!< Output at active level when in FAULT state */

#define IS_HRTIM_OUTPUTCHOPPERMODE(OUTPUTCHOPPERMODE)\
              (((OUTPUTCHOPPERMODE) == HRTIM_OUTPUTCHOPPERMODE_DISABLED)  || \
               ((OUTPUTCHOPPERMODE) == HRTIM_OUTPUTCHOPPERMODE_ENABLED))
/**
  * @}
  */

/** @defgroup HRTIM_OutputBurstModeEntryDelayed
  * @{
  * @brief Constants defining the idle mode entry is delayed by forcing a 
           deadtime insertion before switching the outputs to their idle state
  */ 
#define HRTIM_OUTPUTBURSTMODEENTRY_REGULAR   (uint32_t)0x00000000  /*!< The programmed Idle state is applied immediately to the Output */
#define HRTIM_OUTPUTBURSTMODEENTRY_DELAYED   (HRTIM_OUTR_DIDL1)    /*!< Deadtime is inserted on output before entering the idle mode */

#define IS_HRTIM_OUTPUTBURSTMODEENTRY(OUTPUTBURSTMODEENTRY)\
              (((OUTPUTBURSTMODEENTRY) == HRTIM_OUTPUTBURSTMODEENTRY_REGULAR)  || \
               ((OUTPUTBURSTMODEENTRY) == HRTIM_OUTPUTBURSTMODEENTRY_DELAYED))
/**
  * @}
  */

/** @defgroup HRTIM_CaptureUnitTrigger
  * @{
  * @brief Constants defining the events that can be selected to trigger the 
  *        capture of the timing unit counter
  */
#define HRTIM_CAPTURETRIGGER_NONE         (uint32_t)0x00000000     /*!< Capture trigger is disabled */    
#define HRTIM_CAPTURETRIGGER_UPDATE       (HRTIM_CPT1CR_UPDCPT)    /*!< The update event triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_1        (HRTIM_CPT1CR_EXEV1CPT)  /*!< The External event 1 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_2        (HRTIM_CPT1CR_EXEV2CPT)  /*!< The External event 2 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_3        (HRTIM_CPT1CR_EXEV3CPT)  /*!< The External event 3 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_4        (HRTIM_CPT1CR_EXEV4CPT)  /*!< The External event 4 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_5        (HRTIM_CPT1CR_EXEV5CPT)  /*!< The External event 5 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_6        (HRTIM_CPT1CR_EXEV6CPT)  /*!< The External event 6 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_7        (HRTIM_CPT1CR_EXEV7CPT)  /*!< The External event 7 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_8        (HRTIM_CPT1CR_EXEV8CPT)  /*!< The External event 8 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_9        (HRTIM_CPT1CR_EXEV9CPT)  /*!< The External event 9 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_EEV_10       (HRTIM_CPT1CR_EXEV10CPT) /*!< The External event 10 triggers the Capture */    
#define HRTIM_CAPTURETRIGGER_TA1_SET      (HRTIM_CPT1CR_TA1SET)    /*!< Capture is triggered by TA1 output inactive to active transition */    
#define HRTIM_CAPTURETRIGGER_TA1_RESET    (HRTIM_CPT1CR_TA1RST)    /*!< Capture is triggered by TA1 output active to inactive transition */    
#define HRTIM_CAPTURETRIGGER_TIMERA_CMP1  (HRTIM_CPT1CR_TA1CMP1)  /*!< Timer A Compare 1 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TIMERA_CMP2  (HRTIM_CPT1CR_TA1CMP2)  /*!< Timer A Compare 2 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TB1_SET      (HRTIM_CPT1CR_TB1SET)    /*!< Capture is triggered by TB1 output inactive to active transition */    
#define HRTIM_CAPTURETRIGGER_TB1_RESET    (HRTIM_CPT1CR_TB1RST)    /*!< Capture is triggered by TB1 output active to inactive transition */    
#define HRTIM_CAPTURETRIGGER_TIMERB_CMP1  (HRTIM_CPT1CR_TB1CMP1)  /*!< Timer B Compare 1 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TIMERB_CMP2  (HRTIM_CPT1CR_TB1CMP2)  /*!< Timer B Compare 2 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TC1_SET      (HRTIM_CPT1CR_TC1SET)    /*!< Capture is triggered by TC1 output inactive to active transition */    
#define HRTIM_CAPTURETRIGGER_TC1_RESET    (HRTIM_CPT1CR_TC1RST)    /*!< Capture is triggered by TC1 output active to inactive transition */    
#define HRTIM_CAPTURETRIGGER_TIMERC_CMP1  (HRTIM_CPT1CR_TC1CMP1)  /*!< Timer C Compare 1 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TIMERC_CMP2  (HRTIM_CPT1CR_TC1CMP2)  /*!< Timer C Compare 2 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TD1_SET      (HRTIM_CPT1CR_TD1SET)    /*!< Capture is triggered by TD1 output inactive to active transition */    
#define HRTIM_CAPTURETRIGGER_TD1_RESET    (HRTIM_CPT1CR_TD1RST)    /*!< Capture is triggered by TD1 output active to inactive transition */    
#define HRTIM_CAPTURETRIGGER_TIMERD_CMP1  (HRTIM_CPT1CR_TD1CMP1)  /*!< Timer D Compare 1 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TIMERD_CMP2  (HRTIM_CPT1CR_TD1CMP2)  /*!< Timer D Compare 2 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TE1_SET      (HRTIM_CPT1CR_TE1SET)    /*!< Capture is triggered by TE1 output inactive to active transition */    
#define HRTIM_CAPTURETRIGGER_TE1_RESET    (HRTIM_CPT1CR_TE1RST)    /*!< Capture is triggered by TE1 output active to inactive transition */    
#define HRTIM_CAPTURETRIGGER_TIMERE_CMP1  (HRTIM_CPT1CR_TE1CMP1)  /*!< Timer E Compare 1 triggers Capture */    
#define HRTIM_CAPTURETRIGGER_TIMERE_CMP2  (HRTIM_CPT1CR_TE1CMP2)  /*!< Timer E Compare 2 triggers Capture */             

#define IS_HRTIM_TIMER_CAPTURETRIGGER(TIMER, CAPTURETRIGGER)    \
   (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_NONE)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_UPDATE)         || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_1)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_2)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_3)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_4)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_5)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_6)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_7)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_8)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_9)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_10)            \
   ||                                                           \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_A) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP2)))  \
    ||                                                          \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_B) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP2)))  \
    ||                                                          \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_C) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP2)))  \
    ||                                                          \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_D) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP2)))  \
    ||                                                          \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_E) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP2))))
/**
  * @}
  */   

/** @defgroup HRTIM_TimerExternalEventFilter
  * @{
  * @brief Constants defining the event filtering applied to external events
  *        by a timer
  */
#define HRTIM_TIMEVENTFILTER_NONE             (0x00000000)        
#define HRTIM_TIMEVENTFILTER_BLANKINGCMP1     (HRTIM_EEFR1_EE1FLTR_0)                                                                                                                           /*!< Blanking from counter reset/roll-over to Compare 1 */
#define HRTIM_TIMEVENTFILTER_BLANKINGCMP2     (HRTIM_EEFR1_EE1FLTR_1)                                                                                                                           /*!< Blanking from counter reset/roll-over to Compare 2 */
#define HRTIM_TIMEVENTFILTER_BLANKINGCMP3     (HRTIM_EEFR1_EE1FLTR_1 | HRTIM_EEFR1_EE1FLTR_0)                                                                                                   /*!< Blanking from counter reset/roll-over to Compare 3 */
#define HRTIM_TIMEVENTFILTER_BLANKINGCMP4     (HRTIM_EEFR1_EE1FLTR_2)                                                                                                                           /*!< Blanking from counter reset/roll-over to Compare 4 */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR1    (HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_0)                                                                                                   /*!< Blanking from another timing unit: TIMFLTR1 source */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR2    (HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_1)                                                                                                   /*!< Blanking from another timing unit: TIMFLTR2 source */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR3    (HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_1 | HRTIM_EEFR1_EE1FLTR_0)                                                                           /*!< Blanking from another timing unit: TIMFLTR3 source */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR4    (HRTIM_EEFR1_EE1FLTR_3)                                                                                                                           /*!< Blanking from another timing unit: TIMFLTR4 source */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR5    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_0)                                                                                                   /*!< Blanking from another timing unit: TIMFLTR5 source */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR6    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_1)                                                                                                   /*!< Blanking from another timing unit: TIMFLTR6 source */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR7    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_1 | HRTIM_EEFR1_EE1FLTR_0)                                                                           /*!< Blanking from another timing unit: TIMFLTR7 source */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR8    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2)                                                                                                   /*!< Blanking from another timing unit: TIMFLTR8 source */
#define HRTIM_TIMEVENTFILTER_WINDOWINGCMP2    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_0)                                                                           /*!< Windowing from counter reset/roll-over to Compare 2 */
#define HRTIM_TIMEVENTFILTER_WINDOWINGCMP3    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_1)                                                                           /*!< Windowing from counter reset/roll-over to Compare 3 */
#define HRTIM_TIMEVENTFILTER_WINDOWINGTIM     (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_1 | HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_0)  /*!< Windowing from another timing unit: TIMWIN source */

#define IS_HRTIM_TIMEVENTFILTER(TIMEVENTFILTER)\
                (((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_NONE)           || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGCMP1)   || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGCMP2)   || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGCMP3)   || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGCMP4)   || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR1)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR2)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR3)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR4)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR5)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR6)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR7)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR8)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_WINDOWINGCMP2)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_WINDOWINGCMP3)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_WINDOWINGTIM))
/**
  * @}
  */

/** @defgroup HRTIM_TimerExternalEventLatch
  * @{
  * @brief Constants defining whether or not the external event is
  *        memorized (latched) and generated as soon as the blanking period
  *        is completed or the window ends
  */
#define HRTIM_TIMEVENTLATCH_DISABLED    ((uint32_t)0x00000000)  /*!< Event is ignored if it happens during a blank, or passed through during a window */
#define HRTIM_TIMEVENTLATCH_ENABLED     HRTIM_EEFR1_EE1LTCH     /*!< Event 1 is latched and delayed till the end of the blanking or windowing period */                         /*!< Blanking from counter reset/roll-over to Compare 1 */

#define IS_HRTIM_TIMEVENTLATCH(TIMEVENTLATCH)\
              (((TIMEVENTLATCH) == HRTIM_TIMEVENTLATCH_DISABLED) || \
               ((TIMEVENTLATCH) == HRTIM_TIMEVENTLATCH_ENABLED))
/**
  * @}
  */
    
/** @defgroup HRTIM_DeadtimeRisingSign
  * @{
  * @brief Constants defining whether the deadtime is positive or negative
  *        (overlapping signal) on rising edge
  */ 
#define HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE    ((uint32_t)0x00000000)  /*!< Positive deadtime on rising edge */
#define HRTIM_TIMDEADTIME_RISINGSIGN_NEGATIVE    (HRTIM_DTR_SDTR)        /*!< Negative deadtime on rising edge */

#define IS_HRTIM_TIMDEADTIME_RISINGSIGN(RISINGSIGN)\
                (((RISINGSIGN) == HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE)    || \
                 ((RISINGSIGN) == HRTIM_TIMDEADTIME_RISINGSIGN_NEGATIVE))
/**
  * @}
  */

/** @defgroup HRTIM_DeadtimeRisingLock
  * @{
  * @brief Constants defining whether or not the deadtime (rising sign and
  *        value) is write protected
  */ 
#define HRTIM_TIMDEADTIME_RISINGLOCK_WRITE    ((uint32_t)0x00000000)  /*!< Deadtime rising value and sign is writable */
#define HRTIM_TIMDEADTIME_RISINGLOCK_READONLY (HRTIM_DTR_DTRLK)       /*!< Deadtime rising value and sign is read-only */

#define IS_HRTIM_TIMDEADTIME_RISINGLOCK(RISINGLOCK)\
                    (((RISINGLOCK) == HRTIM_TIMDEADTIME_RISINGLOCK_WRITE)    || \
                     ((RISINGLOCK) == HRTIM_TIMDEADTIME_RISINGLOCK_READONLY))
/**
  * @}
  */

/** @defgroup HRTIM_DeadtimeRisingSignLock
  * @{
  * @brief Constants defining whether or not the deadtime rising sign is write
  *        protected
  */ 
#define HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE    ((uint32_t)0x00000000)  /*!< Deadtime rising sign is writable */
#define HRTIM_TIMDEADTIME_RISINGSIGNLOCK_READONLY (HRTIM_DTR_DTRSLK)      /*!< Deadtime rising sign is read-only */

#define IS_HRTIM_TIMDEADTIME_RISINGSIGNLOCK(RISINGSIGNLOCK)\
                  (((RISINGSIGNLOCK) == HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE)    || \
                   ((RISINGSIGNLOCK) == HRTIM_TIMDEADTIME_RISINGSIGNLOCK_READONLY))
/**
  * @}
  */

/** @defgroup HRTIM_DeadtimeFallingSign
  * @{
  * @brief Constants defining whether the deadtime is positive or negative
  *        (overlapping signal) on falling edge
  */ 
#define HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE    ((uint32_t)0x00000000)  /*!< Positive deadtime on falling edge */
#define HRTIM_TIMDEADTIME_FALLINGSIGN_NEGATIVE    (HRTIM_DTR_SDTF)        /*!< Negative deadtime on falling edge */

#define IS_HRTIM_TIMDEADTIME_FALLINGSIGN(FALLINGSIGN)\
                      (((FALLINGSIGN) == HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE)    || \
                       ((FALLINGSIGN) == HRTIM_TIMDEADTIME_FALLINGSIGN_NEGATIVE))
/**
  * @}
  */

/** @defgroup HRTIM_DeadtimeFallingLock
  * @{
  * @brief Constants defining whether or not the deadtime (falling sign and
  *        value) is write protected
  */ 
#define HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE    ((uint32_t)0x00000000)  /*!< Deadtime falling value and sign is writable */
#define HRTIM_TIMDEADTIME_FALLINGLOCK_READONLY (HRTIM_DTR_DTFLK)       /*!< Deadtime falling value and sign is read-only */

#define IS_HRTIM_TIMDEADTIME_FALLINGLOCK(FALLINGLOCK)\
                          (((FALLINGLOCK) == HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE)    || \
                           ((FALLINGLOCK) == HRTIM_TIMDEADTIME_FALLINGLOCK_READONLY))
/**
  * @}
  */

/** @defgroup HRTIM_DeadtimeFallingSignLock
  * @{
  * @brief Constants defining whether or not the deadtime falling sign is write
  *        protected
  */ 
#define HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE    ((uint32_t)0x00000000)  /*!< Deadtime falling sign is writable */
#define HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_READONLY (HRTIM_DTR_DTFSLK)      /*!< Deadtime falling sign is read-only */

#define IS_HRTIM_TIMDEADTIME_FALLINGSIGNLOCK(FALLINGSIGNLOCK)\
                        (((FALLINGSIGNLOCK) == HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE)    || \
                         ((FALLINGSIGNLOCK) == HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_READONLY))
/**
  * @}
  */

/** @defgroup HRTIM_SynchronizationInputSource
  * @{
  * @brief Constants defining defining the synchronization input source
  */ 
#define HRTIM_SYNCINPUTSOURCE_NONE           (uint32_t)0x00000000                         /*!< disabled. HRTIM is not synchronized and runs in standalone mode */
#define HRTIM_SYNCINPUTSOURCE_INTERNALEVENT  HRTIM_MCR_SYNC_IN_1                          /*!< The HRTIM is synchronized with the on-chip timer */
#define HRTIM_SYNCINPUTSOURCE_EXTERNALEVENT  (HRTIM_MCR_SYNC_IN_1 | HRTIM_MCR_SYNC_IN_0)  /*!< A positive pulse on SYNCIN input triggers the HRTIM */

#define IS_HRTIM_SYNCINPUTSOURCE(SYNCINPUTSOURCE)\
              (((SYNCINPUTSOURCE) == HRTIM_SYNCINPUTSOURCE_NONE)             || \
               ((SYNCINPUTSOURCE) == HRTIM_SYNCINPUTSOURCE_INTERNALEVENT)    || \
               ((SYNCINPUTSOURCE) == HRTIM_SYNCINPUTSOURCE_EXTERNALEVENT))
/**
  * @}
  */

/** @defgroup HRTIM_SynchronizationOutputSource
  * @{
  * @brief Constants defining the source and event to be sent on the 
  *        synchronization outputs
  */
#define HRTIM_SYNCOUTPUTSOURCE_MASTER_START (uint32_t)0x00000000                           /*!< A pulse is sent on the SYNCOUT output (16x fHRTIM clock cycles) upon master timer start event */
#define HRTIM_SYNCOUTPUTSOURCE_MASTER_CMP1  (HRTIM_MCR_SYNC_SRC_0)                         /*!< A pulse is sent on the SYNCOUT output (16x fHRTIM clock cycles) upon master timer compare 1 event*/
#define HRTIM_SYNCOUTPUTSOURCE_TIMA_START   (HRTIM_MCR_SYNC_SRC_1)                         /*!< A pulse is sent on the SYNCOUT output (16x fHRTIM clock cycles) upon timer A start or reset events */
#define HRTIM_SYNCOUTPUTSOURCE_TIMA_CMP1    (HRTIM_MCR_SYNC_SRC_1 | HRTIM_MCR_SYNC_SRC_0)  /*!< A pulse is sent on the SYNCOUT output (16x fHRTIM clock cycles) upon timer A compare 1 event */

#define IS_HRTIM_SYNCOUTPUTSOURCE(SYNCOUTPUTSOURCE)\
              (((SYNCOUTPUTSOURCE) == HRTIM_SYNCOUTPUTSOURCE_MASTER_START)  || \
               ((SYNCOUTPUTSOURCE) == HRTIM_SYNCOUTPUTSOURCE_MASTER_CMP1)   || \
               ((SYNCOUTPUTSOURCE) == HRTIM_SYNCOUTPUTSOURCE_TIMA_START)    || \
               ((SYNCOUTPUTSOURCE) == HRTIM_SYNCOUTPUTSOURCE_TIMA_CMP1))                
/**
  * @}
  */

/** @defgroup HRTIM_SynchronizationOutputPolarity
  * @{
  * @brief Constants defining the routing and conditioning of the synchronization output event
  */ 
#define HRTIM_SYNCOUTPUTPOLARITY_NONE      (uint32_t)0x00000000                          /*!< Synchronization output event is disabled */
#define HRTIM_SYNCOUTPUTPOLARITY_POSITIVE  (HRTIM_MCR_SYNC_OUT_0)                        /*!< Positive pulse on SCOUT output (16x fHRTIM clock cycles) */
#define HRTIM_SYNCOUTPUTPOLARITY_NEGATIVE  (HRTIM_MCR_SYNC_OUT_1 | HRTIM_MCR_SYNC_OUT_0) /*!< Positive pulse on SCOUT output (16x fHRTIM clock cycles) */

#define IS_HRTIM_SYNCOUTPUTPOLARITY(SYNCOUTPUTPOLARITY)\
              (((SYNCOUTPUTPOLARITY) == HRTIM_SYNCOUTPUTPOLARITY_NONE)  || \
               ((SYNCOUTPUTPOLARITY) == HRTIM_SYNCOUTPUTPOLARITY_POSITIVE)  || \
               ((SYNCOUTPUTPOLARITY) == HRTIM_SYNCOUTPUTPOLARITY_NEGATIVE))    
/**
  * @}
  */

/** @defgroup HRTIM_ExternalEventSources
  * @{
  * @brief Constants defining available sources associated to external events
  */
#define HRTIM_EVENTSRC_1         ((uint32_t)0x00000000)                         /*!< External event source 1 */
#define HRTIM_EVENTSRC_2         (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 */
#define HRTIM_EVENTSRC_3         (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 */
#define HRTIM_EVENTSRC_4         (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 */

#define IS_HRTIM_EVENTSRC(EVENTSRC)\
                (((EVENTSRC) == HRTIM_EVENTSRC_1)   || \
                 ((EVENTSRC) == HRTIM_EVENTSRC_2)   || \
                 ((EVENTSRC) == HRTIM_EVENTSRC_3)   || \
                 ((EVENTSRC) == HRTIM_EVENTSRC_4))
/**
  * @}
  */

/** @defgroup HRTIM_ExternalEventPolarity
  * @{
  * @brief Constants defining the polarity of an external event
  */
#define HRTIM_EVENTPOLARITY_HIGH    ((uint32_t)0x00000000)  /*!< External event is active high */
#define HRTIM_EVENTPOLARITY_LOW     (HRTIM_EECR1_EE1POL)    /*!< External event is active low */

#define IS_HRTIM_EVENTPOLARITY(EVENTPOLARITY)\
                  (((EVENTPOLARITY) == HRTIM_EVENTPOLARITY_HIGH)  || \
                   ((EVENTPOLARITY) == HRTIM_EVENTPOLARITY_LOW))
/**
  * @}
  */

/** @defgroup HRTIM_ExternalEventSensitivity
  * @{
  * @brief Constants defining the sensitivity (level-sensitive or edge-sensitive)
  *        of an external event
  */
#define HRTIM_EVENTSENSITIVITY_LEVEL          ((uint32_t)0x00000000)                         /*!< External event is active on level */
#define HRTIM_EVENTSENSITIVITY_RISINGEDGE     (HRTIM_EECR1_EE1SNS_0)                         /*!< External event is active on Rising edge */
#define HRTIM_EVENTSENSITIVITY_FALLINGEDGE    (HRTIM_EECR1_EE1SNS_1)                         /*!< External event is active on Falling edge */
#define HRTIM_EVENTSENSITIVITY_BOTHEDGES      (HRTIM_EECR1_EE1SNS_1 | HRTIM_EECR1_EE1SNS_0)  /*!< External event is active on Rising and Falling edges */

#define IS_HRTIM_EVENTSENSITIVITY(EVENTSENSITIVITY)\
                    (((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_LEVEL)       || \
                     ((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_RISINGEDGE)  || \
                     ((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_FALLINGEDGE) || \
                     ((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_BOTHEDGES))
/**
  * @}
  */

/** @defgroup HRTIM_ExternalEventFastMode
  * @{
  * @brief Constants defining whether or not an external event is programmed in
           fast mode
  */
#define HRTIM_EVENTFASTMODE_DISABLE         ((uint32_t)0x00000000)   /*!< External Event is acting asynchronously on outputs (low latency mode) */
#define HRTIM_EVENTFASTMODE_ENABLE          (HRTIM_EECR1_EE1FAST)    /*!< External Event is re-synchronized by the HRTIM logic before acting on outputs */

#define IS_HRTIM_EVENTFASTMODE(EVENTFASTMODE)\
                      (((EVENTFASTMODE) == HRTIM_EVENTFASTMODE_ENABLE)    || \
                       ((EVENTFASTMODE) == HRTIM_EVENTFASTMODE_DISABLE))

#define IS_HRTIM_FASTMODE_AVAILABLE(EVENT)\
              (((EVENT) == HRTIM_EVENT_1)    || \
               ((EVENT) == HRTIM_EVENT_2)    || \
               ((EVENT) == HRTIM_EVENT_3)    || \
               ((EVENT) == HRTIM_EVENT_4)    || \
               ((EVENT) == HRTIM_EVENT_5))
/**
  * @}
  */

/** @defgroup HRTIM_ExternalEventFilter
  * @{
  * @brief Constants defining the frequency used to sample an external event 6
  *        input and the length (N) of the digital filter applied
  */
#define HRTIM_EVENTFILTER_NONE      ((uint32_t)0x00000000)                                                                /*!< Filter disabled */
#define HRTIM_EVENTFILTER_1         (HRTIM_EECR3_EE6F_0)                                                                  /*!< fSAMPLING= fHRTIM, N=2 */
#define HRTIM_EVENTFILTER_2         (HRTIM_EECR3_EE6F_1)                                                                  /*!< fSAMPLING= fHRTIM, N=4 */
#define HRTIM_EVENTFILTER_3         (HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING= fHRTIM, N=8 */
#define HRTIM_EVENTFILTER_4         (HRTIM_EECR3_EE6F_2)                                                                  /*!< fSAMPLING= fEEVS/2, N=6 */
#define HRTIM_EVENTFILTER_5         (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING= fEEVS/2, N=8 */
#define HRTIM_EVENTFILTER_6         (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_1)                                             /*!< fSAMPLING= fEEVS/4, N=6 */
#define HRTIM_EVENTFILTER_7         (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                        /*!< fSAMPLING= fEEVS/4, N=8 */
#define HRTIM_EVENTFILTER_8         (HRTIM_EECR3_EE6F_3)                                                                  /*!< fSAMPLING= fEEVS/8, N=6 */
#define HRTIM_EVENTFILTER_9         (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING= fEEVS/8, N=8 */
#define HRTIM_EVENTFILTER_10        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_1)                                             /*!< fSAMPLING= fEEVS/16, N=5 */
#define HRTIM_EVENTFILTER_11        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                        /*!< fSAMPLING= fEEVS/16, N=6 */
#define HRTIM_EVENTFILTER_12        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2)                                             /*!< fSAMPLING= fEEVS/16, N=8 */
#define HRTIM_EVENTFILTER_13        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_0)                       /*!< fSAMPLING= fEEVS/32, N=5 */
#define HRTIM_EVENTFILTER_14        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_1)                       /*!< fSAMPLING= fEEVS/32, N=6 */
#define HRTIM_EVENTFILTER_15        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)  /*!< fSAMPLING= fEEVS/32, N=8 */

#define IS_HRTIM_EVENTFILTER(EVENTFILTER)\
                (((EVENTFILTER) == HRTIM_EVENTFILTER_NONE) || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_1)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_2)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_3)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_4)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_5)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_6)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_7)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_8)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_9)    || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_10)   || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_11)   || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_12)   || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_13)   || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_14)   || \
                 ((EVENTFILTER) == HRTIM_EVENTFILTER_15))
/**
  * @}
  */

/** @defgroup HRTIM_ ExternalEventPrescaler
  * @{
  * @brief Constants defining division ratio between the timer clock frequency 
  *        fHRTIM) and the external event signal sampling clock (fEEVS)
  *        used by the digital filters
  */
#define HRTIM_EVENTPRESCALER_DIV1    ((uint32_t)0x00000000)                          /*!< fEEVS=fHRTIM */
#define HRTIM_EVENTPRESCALER_DIV2    (HRTIM_EECR3_EEVSD_0)                           /*!< fEEVS=fHRTIM / 2 */
#define HRTIM_EVENTPRESCALER_DIV4    (HRTIM_EECR3_EEVSD_1)                           /*!< fEEVS=fHRTIM / 4 */
#define HRTIM_EVENTPRESCALER_DIV8    (HRTIM_EECR3_EEVSD_1 | HRTIM_EECR3_EEVSD_0)     /*!< fEEVS=fHRTIM / 8 */

#define IS_HRTIM_EVENTPRESCALER(EVENTPRESCALER)\
             (((EVENTPRESCALER) == HRTIM_EVENTPRESCALER_DIV1)  || \
              ((EVENTPRESCALER) == HRTIM_EVENTPRESCALER_DIV2)   || \
              ((EVENTPRESCALER) == HRTIM_EVENTPRESCALER_DIV4)   || \
              ((EVENTPRESCALER) == HRTIM_EVENTPRESCALER_DIV8))
/**
  * @}
  */

/** @defgroup HRTIM_FaultSources
  * @{
  * @brief Constants defining whether a faults is be triggered by any external 
  *        or internal fault source
  */ 
#define HRTIM_FAULTSOURCE_DIGITALINPUT      ((uint32_t)0x00000000)     /*!< Fault input is FLT input pin */
#define HRTIM_FAULTSOURCE_INTERNAL          (HRTIM_FLTINR1_FLT1SRC)    /*!< Fault input is FLT_Int signal (e.g. internal comparator) */


#define IS_HRTIM_FAULTSOURCE(FAULTSOURCE)\
              (((FAULTSOURCE) == HRTIM_FAULTSOURCE_DIGITALINPUT) || \
               ((FAULTSOURCE) == HRTIM_FAULTSOURCE_INTERNAL))
/**
  * @}
  */

/** @defgroup HRTIM_FaultPolarity
  * @{
  * @brief Constants defining the polarity of a fault event
  */
#define HRTIM_FAULTPOLARITY_LOW     ((uint32_t)0x00000000)   /*!< Fault input is active low */
#define HRTIM_FAULTPOLARITY_HIGH    (HRTIM_FLTINR1_FLT1P)    /*!< Fault input is active high */

#define IS_HRTIM_FAULTPOLARITY(HRTIM_FAULTPOLARITY)\
              (((HRTIM_FAULTPOLARITY) == HRTIM_FAULTPOLARITY_LOW) || \
               ((HRTIM_FAULTPOLARITY) == HRTIM_FAULTPOLARITY_HIGH))
/**
  * @}
  */

/** @defgroup HRTIM_FaultFilter
  * @{
  * @ brief Constants defining the frequency used to sample the fault input and
  *         the length (N) of the digital filter applied
  */
#define HRTIM_FAULTFILTER_NONE      ((uint32_t)0x00000000)                                                                           /*!< Filter disabled */
#define HRTIM_FAULTFILTER_1         (HRTIM_FLTINR1_FLT1F_0)                                                                          /*!< fSAMPLING= fHRTIM, N=2 */
#define HRTIM_FAULTFILTER_2         (HRTIM_FLTINR1_FLT1F_1)                                                                          /*!< fSAMPLING= fHRTIM, N=4 */
#define HRTIM_FAULTFILTER_3         (HRTIM_FLTINR1_FLT1F_1 | HRTIM_FLTINR1_FLT1F_0)                                                  /*!< fSAMPLING= fHRTIM, N=8 */
#define HRTIM_FAULTFILTER_4         (HRTIM_FLTINR1_FLT1F_2)                                                                          /*!< fSAMPLING= fFLTS/2, N=6 */
#define HRTIM_FAULTFILTER_5         (HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_0)                                                  /*!< fSAMPLING= fFLTS/2, N=8 */
#define HRTIM_FAULTFILTER_6         (HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_1)                                                  /*!< fSAMPLING= fFLTS/4, N=6 */
#define HRTIM_FAULTFILTER_7         (HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_1 | HRTIM_FLTINR1_FLT1F_0)                          /*!< fSAMPLING= fFLTS/4, N=8 */
#define HRTIM_FAULTFILTER_8         (HRTIM_FLTINR1_FLT1F_3)                                                                          /*!< fSAMPLING= fFLTS/8, N=6 */
#define HRTIM_FAULTFILTER_9         (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_0)                                                  /*!< fSAMPLING= fFLTS/8, N=8 */
#define HRTIM_FAULTFILTER_10        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_1)                                                  /*!< fSAMPLING= fFLTS/16, N=5 */
#define HRTIM_FAULTFILTER_11        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_1 | HRTIM_FLTINR1_FLT1F_0)                          /*!< fSAMPLING= fFLTS/16, N=6 */
#define HRTIM_FAULTFILTER_12        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_2)                                                  /*!< fSAMPLING= fFLTS/16, N=8 */
#define HRTIM_FAULTFILTER_13        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_0)                          /*!< fSAMPLING= fFLTS/32, N=5 */
#define HRTIM_FAULTFILTER_14        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_1)                          /*!< fSAMPLING= fFLTS/32, N=6 */
#define HRTIM_FAULTFILTER_15        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_1 | HRTIM_FLTINR1_FLT1F_0)  /*!< fSAMPLING= fFLTS/32, N=8 */

#define IS_HRTIM_FAULTFILTER(FAULTFILTER)\
                (((FAULTFILTER) == HRTIM_FAULTFILTER_NONE) || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_1)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_2)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_3)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_4)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_5)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_6)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_7)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_8)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_9)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_10)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_11)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_12)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_13)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_14)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_15))
/**
  * @}
  */
              
/** @defgroup HRTIM_FaultLock
  * @{
  * @brief Constants defining whether or not the fault programming bits are
           write protected
  */
#define HRTIM_FAULTLOCK_READWRITE       ((uint32_t)0x00000000)                /*!< Fault settings bits are read/write */
#define HRTIM_FAULTLOCK_READONLY        (HRTIM_FLTINR1_FLT1LCK)     /*!< Fault settings bits are read only */
              
#define IS_HRTIM_FAULTLOCK(FAULTLOCK)\
              (((FAULTLOCK) == HRTIM_FAULTLOCK_READWRITE) || \
               ((FAULTLOCK) == HRTIM_FAULTLOCK_READONLY))
/**
  * @}
  */

/** @defgroup HRTIM_ExternalFaultPrescaler
  * @{
  * @brief Constants defining the division ratio between the timer clock 
  *        frequency (fHRTIM) and the fault signal sampling clock (fFLTS) used 
  *        by the digital filters.
  */
#define HRTIM_FAULTPRESCALER_DIV1    ((uint32_t)0x00000000)                            /*!< fFLTS=fHRTIM */
#define HRTIM_FAULTPRESCALER_DIV2    (HRTIM_FLTINR2_FLTSD_0)                           /*!< fFLTS=fHRTIM / 2 */
#define HRTIM_FAULTPRESCALER_DIV4    (HRTIM_FLTINR2_FLTSD_1)                           /*!< fFLTS=fHRTIM / 4 */
#define HRTIM_FAULTPRESCALER_DIV8    (HRTIM_FLTINR2_FLTSD_1 | HRTIM_FLTINR2_FLTSD_0)   /*!< fFLTS=fHRTIM / 8 */

#define IS_HRTIM_FAULTPRESCALER(FAULTPRESCALER)\
             (((FAULTPRESCALER) == HRTIM_FAULTPRESCALER_DIV1)  || \
              ((FAULTPRESCALER) == HRTIM_FAULTPRESCALER_DIV2)   || \
              ((FAULTPRESCALER) == HRTIM_FAULTPRESCALER_DIV4)   || \
              ((FAULTPRESCALER) == HRTIM_FAULTPRESCALER_DIV8))
/**
  * @}
  */

/** @defgroup HRTIM_BurstModeOperatingmode
  * @{
  * @brief Constants defining if the burst mode is entered once or if it is 
  *        continuously operating
  */
#define HRTIM_BURSTMODE_SINGLESHOT ((uint32_t)0x00000000)  /*!< Burst mode operates in single shot mode */
#define HRTIM_BURSTMODE_CONTINOUS   (HRTIM_BMCR_BMOM)      /*!< Burst mode operates in continuous mode */

#define IS_HRTIM_BURSTMODE(BURSTMODE)\
              (((BURSTMODE) == HRTIM_BURSTMODE_SINGLESHOT)  || \
               ((BURSTMODE) == HRTIM_BURSTMODE_CONTINOUS))    
/**
  * @}
  */

/** @defgroup HRTIM_BurstModeClockSource
  * @{
  * @brief Constants defining the clock source for the burst mode counter
  */ 
#define HRTIM_BURSTMODECLOCKSOURCE_MASTER     ((uint32_t)0x00000000)                                           /*!< Master timer counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_A    (HRTIM_BMCR_BMCLK_0)                                            /*!< Timer A counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_B    (HRTIM_BMCR_BMCLK_1)                                            /*!< Timer B counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_C    (HRTIM_BMCR_BMCLK_1 | HRTIM_BMCR_BMCLK_0)                       /*!< Timer C counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_D    (HRTIM_BMCR_BMCLK_2)                                            /*!< Timer D counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_E    (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_0)                       /*!< Timer E counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_ONCHIPEV_1 (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_1)                       /*!< On-chip Event 1 (BMClk[1]), acting as a burst mode counter clock */
#define HRTIM_BURSTMODECLOCKSOURCE_ONCHIPEV_2 (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_1 | HRTIM_BMCR_BMCLK_0)  /*!< On-chip Event 2 (BMClk[2]), acting as a burst mode counter clock */
#define HRTIM_BURSTMODECLOCKSOURCE_ONCHIPEV_3 (HRTIM_BMCR_BMCLK_3)                                            /*!< On-chip Event 3 (BMClk[3]), acting as a burst mode counter clock */
#define HRTIM_BURSTMODECLOCKSOURCE_ONCHIPEV_4 (HRTIM_BMCR_BMCLK_3 | HRTIM_BMCR_BMCLK_0)                       /*!< On-chip Event 4 (BMClk[4]), acting as a burst mode counter clock */
#define HRTIM_BURSTMODECLOCKSOURCE_FHRTIM     (HRTIM_BMCR_BMCLK_3 | HRTIM_BMCR_BMCLK_1)                       /*!< Prescaled fHRTIM clock is used as clock source for the burst mode counter */

#define IS_HRTIM_BURSTMODECLOCKSOURCE(BURSTMODECLOCKSOURCE)\
              (((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_MASTER)      || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_A)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_B)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_C)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_D)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_E)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_ONCHIPEV_1)  || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_ONCHIPEV_2)  || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_ONCHIPEV_3)  || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_ONCHIPEV_4)  || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_FHRTIM))                   
/**
  * @}
  */

/** @defgroup HRTIM_BurstModePrescaler
  * @{
  * @brief Constants defining the prescaling ratio of the fHRTIM clock 
  *        for the burst mode controller
  */
#define HRTIM_BURSTMODEPRESCALER_DIV1     ((uint32_t)0x00000000)                                                              /*!< fBRST = fHRTIM */
#define HRTIM_BURSTMODEPRESCALER_DIV2     (HRTIM_BMCR_BMPSC_0)                                                                /*!< fBRST = fHRTIM/2 */
#define HRTIM_BURSTMODEPRESCALER_DIV4     (HRTIM_BMCR_BMPSC_1)                                                                /*!< fBRST = fHRTIM/4 */
#define HRTIM_BURSTMODEPRESCALER_DIV8     (HRTIM_BMCR_BMPSC_1 | HRTIM_BMCR_BMPSC_0)                                          /*!< fBRST = fHRTIM/8 */
#define HRTIM_BURSTMODEPRESCALER_DIV16    (HRTIM_BMCR_BMPSC_2)                                                                 /*!< fBRST = fHRTIM/16 */
#define HRTIM_BURSTMODEPRESCALER_DIV32    (HRTIM_BMCR_BMPSC_2 | HRTIM_BMCR_BMPSC_0)                                           /*!< fBRST = fHRTIM/32 */
#define HRTIM_BURSTMODEPRESCALER_DIV64    (HRTIM_BMCR_BMPSC_2 | HRTIM_BMCR_BMPSC_1)                                           /*!< fBRST = fHRTIM/64 */
#define HRTIM_BURSTMODEPRESCALER_DIV128   (HRTIM_BMCR_BMPSC_2 | HRTIM_BMCR_BMPSC_1 | HRTIM_BMCR_BMPSC_0)                      /*!< fBRST = fHRTIM/128 */
#define HRTIM_BURSTMODEPRESCALER_DIV256   (HRTIM_BMCR_BMPSC_3)                                                                /*!< fBRST = fHRTIM/256 */
#define HRTIM_BURSTMODEPRESCALER_DIV512   (HRTIM_BMCR_BMPSC_3 | HRTIM_BMCR_BMPSC_0)                                           /*!< fBRST = fHRTIM/512 */
#define HRTIM_BURSTMODEPRESCALER_DIV1024  (HRTIM_BMCR_BMPSC_3 | HRTIM_BMCR_BMPSC_1)                                           /*!< fBRST = fHRTIM/1024 */
#define HRTIM_BURSTMODEPRESCALER_DIV2048  (HRTIM_BMCR_BMPSC_3 | HRTIM_BMCR_BMPSC_1 | HRTIM_BMCR_BMPSC_0)                      /*!< fBRST = fHRTIM/2048*/
#define HRTIM_BURSTMODEPRESCALER_DIV4096  (HRTIM_BMCR_BMPSC_3 | HRTIM_BMCR_BMPSC_2)                                           /*!< fBRST = fHRTIM/4096 */
#define HRTIM_BURSTMODEPRESCALER_DIV8192  (HRTIM_BMCR_BMPSC_3 | HRTIM_BMCR_BMPSC_2 | HRTIM_BMCR_BMPSC_0)                      /*!< fBRST = fHRTIM/8192 */
#define HRTIM_BURSTMODEPRESCALER_DIV16384 (HRTIM_BMCR_BMPSC_3 | HRTIM_BMCR_BMPSC_2 | HRTIM_BMCR_BMPSC_1)                      /*!< fBRST = fHRTIM/16384 */
#define HRTIM_BURSTMODEPRESCALER_DIV32768 (HRTIM_BMCR_BMPSC_3 | HRTIM_BMCR_BMPSC_2 | HRTIM_BMCR_BMPSC_1 | HRTIM_BMCR_BMPSC_0) /*!< fBRST = fHRTIM/32768 */

#define IS_HRTIM_HRTIM_BURSTMODEPRESCALER(BURSTMODEPRESCALER)\
              (((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV1)     || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV2)     || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV4)     || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV8)     || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV16)    || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV32)    || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV64)    || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV128)   || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV256)   || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV512)   || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV1024)  || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV2048)  || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV4096)  || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV8192)  || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV16384) || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV32768))                   
/**
  * @}
  */
                
/** @defgroup HRTIM_BurstModeRegisterPreloadEnable
  * @{
  * @brief Constants defining whether or not burst mode registers preload 
           mechanism is enabled, i.e. a write access into a preloadable register
          (HRTIM_BMCMPR, HRTIM_BMPER) is done into the active or the preload register
  */
#define HRIM_BURSTMODEPRELOAD_DISABLED ((uint32_t)0x00000000)  /*!< Preload disabled: the write access is directly done into active registers */
#define HRIM_BURSTMODEPRELOAD_ENABLED  (HRTIM_BMCR_BMPREN)     /*!< Preload enabled: the write access is done into preload registers */

#define IS_HRTIM_BURSTMODEPRELOAD(BURSTMODEPRELOAD)\
              (((BURSTMODEPRELOAD) == HRIM_BURSTMODEPRELOAD_DISABLED)  || \
               ((BURSTMODEPRELOAD) == HRIM_BURSTMODEPRELOAD_ENABLED))                   
/**
  * @}
  */
                
/** @defgroup HRTIM_BurstModeTrigger
  * @{
  * @brief Constants defining the events that can be used tor trig the burst
  *        mode operation
  */
#define HRTIM_BURSTMODETRIGGER_NONE               (uint32_t)0x00000000    
#define HRTIM_BURSTMODETRIGGER_SOFTWARE           (HRTIM_BMTRGR_SW)       /*!<  Software trigger */
#define HRTIM_BURSTMODETRIGGER_MASTER_RESET       (HRTIM_BMTRGR_MSTRST)   /*!<  Master reset */
#define HRTIM_BURSTMODETRIGGER_MASTER_REPETITION  (HRTIM_BMTRGR_MSTREP)   /*!<  Master repetition */
#define HRTIM_BURSTMODETRIGGER_MASTER_CMP1        (HRTIM_BMTRGR_MSTCMP1)  /*!<  Master compare 1 */
#define HRTIM_BURSTMODETRIGGER_MASTER_CMP2        (HRTIM_BMTRGR_MSTCMP2)  /*!<  Master compare 2 */
#define HRTIM_BURSTMODETRIGGER_MASTER_CMP3        (HRTIM_BMTRGR_MSTCMP3)  /*!<  Master compare 3 */
#define HRTIM_BURSTMODETRIGGER_MASTER_CMP4        (HRTIM_BMTRGR_MSTCMP4)  /*!<  Master compare 4 */
#define HRTIM_BURSTMODETRIGGER_TIMERA_RESET       (HRTIM_BMTRGR_TARST)    /*!< Timer A reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERA_REPETITION  (HRTIM_BMTRGR_TAREP)    /*!< Timer A repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERA_CMP1        (HRTIM_BMTRGR_TACMP1)   /*!< Timer A compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERA_CMP2        (HRTIM_BMTRGR_TACMP2)   /*!< Timer A compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERB_RESET       (HRTIM_BMTRGR_TBRST)    /*!< Timer B reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERB_REPETITION  (HRTIM_BMTRGR_TBREP)    /*!< Timer B repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERB_CMP1        (HRTIM_BMTRGR_TBCMP1)   /*!< Timer B compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERB_CMP2        (HRTIM_BMTRGR_TBCMP2)   /*!< Timer B compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERC_RESET       (HRTIM_BMTRGR_TCRST)    /*!< Timer C reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERC_REPETITION  (HRTIM_BMTRGR_TCREP)    /*!< Timer C repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERC_CMP1        (HRTIM_BMTRGR_TCCMP1)   /*!< Timer C compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERC_CMP2        (HRTIM_BMTRGR_TCCMP2)   /*!< Timer C compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_RESET       (HRTIM_BMTRGR_TDRST)    /*!< Timer D reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_REPETITION  (HRTIM_BMTRGR_TDREP)    /*!< Timer D repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_CMP1        (HRTIM_BMTRGR_TDCMP1)   /*!< Timer D compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_CMP2        (HRTIM_BMTRGR_TDCMP2)   /*!< Timer D compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERE_RESET       (HRTIM_BMTRGR_TERST)    /*!< Timer E reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERE_REPETITION  (HRTIM_BMTRGR_TEREP)    /*!< Timer E repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERE_CMP1        (HRTIM_BMTRGR_TECMP1)   /*!< Timer E compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERE_CMP2        (HRTIM_BMTRGR_TECMP2)   /*!< Timer E compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERA_EVENT7      (HRTIM_BMTRGR_TAEEV7)   /*!< Timer A period following External Event 7  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_EVENT8      (HRTIM_BMTRGR_TDEEV8)   /*!< Timer D period following External Event 8  */
#define HRTIM_BURSTMODETRIGGER_EVENT_7            (HRTIM_BMTRGR_EEV7)     /*!< External Event 7 */
#define HRTIM_BURSTMODETRIGGER_EVENT_8            (HRTIM_BMTRGR_EEV8)     /*!< External Event 8 */
#define HRTIM_BURSTMODETRIGGER_EVENT_ONCHIP       (HRTIM_BMTRGR_OCHPEV)   /*!< On-chip Event */

#define IS_HRTIM_BURSTMODETRIGGER(BURSTMODETRIGGER)\
              (((BURSTMODETRIGGER) == HRTIM_BURSTMODETRIGGER_NONE)               || \
               ((BURSTMODETRIGGER) == HRTIM_BURSTMODETRIGGER_MASTER_RESET)       || \
               ((BURSTMODETRIGGER) == HRTIM_BURSTMODETRIGGER_MASTER_REPETITION)  || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_MASTER_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_MASTER_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_MASTER_CMP3)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_MASTER_CMP4)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERB_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERB_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERB_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERB_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERC_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERC_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERC_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERC_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERE_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERE_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERE_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERE_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_EVENT7)     || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_EVENT8)     || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_EVENT_7)           || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_EVENT_8)           || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_EVENT_ONCHIP))
/**
  * @}
  */

/** @defgroup HRTIM_ADCTriggerUpdateSource
  * @{
  * @brief constants defining the source triggering the update of the 
     HRTIM_ADCxR register (transfer from preload to active register).
  */
#define HRTIM_ADCTRIGGERUPDATE_MASTER  (uint32_t)0x00000000                          /*!< Master timer */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_A (HRTIM_CR1_ADC1USRC_0)                        /*!< Timer A */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_B (HRTIM_CR1_ADC1USRC_1)                        /*!< Timer B */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_C (HRTIM_CR1_ADC1USRC_1 | HRTIM_CR1_ADC1USRC_0) /*!< Timer C */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_D (HRTIM_CR1_ADC1USRC_2)                        /*!< Timer D */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_E (HRTIM_CR1_ADC1USRC_2 | HRTIM_CR1_ADC1USRC_0) /*!< Timer E */

#define IS_HRTIM_ADCTRIGGERUPDATE(ADCTRIGGERUPDATE)\
             (((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_MASTER)   || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_A)  || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_B)  || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_C)  || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_D)  || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_E))      
/**
  * @}
  */
                
/** @defgroup HRTIM_ADCTriggerEvent
  * @{
  * @brief constants defining the events triggering ADC conversion.
  *        HRTIM_ADCTRIGGEREVENT13_*: ADC Triggers 1 and 3
  *        HRTIM_ADCTRIGGEREVENT24_*: ADC Triggers 2 and 4
  */
#define HRTIM_ADCTRIGGEREVENT13_NONE           (uint32_t)0x00000000     /*!< No ADC trigger event */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_CMP1    (HRTIM_ADC1R_AD1MC1)     /*!< ADC Trigger on master compare 1 */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_CMP2    (HRTIM_ADC1R_AD1MC2)     /*!< ADC Trigger on master compare 2 */ 
#define HRTIM_ADCTRIGGEREVENT13_MASTER_CMP3    (HRTIM_ADC1R_AD1MC3)     /*!< ADC Trigger on master compare 3 */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_CMP4    (HRTIM_ADC1R_AD1MC4)     /*!< ADC Trigger on master compare 4 */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_PERIOD  (HRTIM_ADC1R_AD1MPER)    /*!< ADC Trigger on master period */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_1        (HRTIM_ADC1R_AD1EEV1)    /*!< ADC Trigger on external event 1 */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_2        (HRTIM_ADC1R_AD1EEV2)    /*!< ADC Trigger on external event 2 */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_3        (HRTIM_ADC1R_AD1EEV3)    /*!< ADC Trigger on external event 3 */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_4        (HRTIM_ADC1R_AD1EEV4)    /*!< ADC Trigger on external event 4 */ 
#define HRTIM_ADCTRIGGEREVENT13_EVENT_5        (HRTIM_ADC1R_AD1EEV5)    /*!< ADC Trigger on external event 5 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_CMP2    (HRTIM_ADC1R_AD1TAC2)    /*!< ADC Trigger on Timer A compare 2 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_CMP3    (HRTIM_ADC1R_AD1TAC3)    /*!< ADC Trigger on Timer A compare 3 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_CMP4    (HRTIM_ADC1R_AD1TAC4)    /*!< ADC Trigger on Timer A compare 4 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_PERIOD  (HRTIM_ADC1R_AD1TAPER)   /*!< ADC Trigger on Timer A period */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_RESET   (HRTIM_ADC1R_AD1TARST)   /*!< ADC Trigger on Timer A reset */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_CMP2    (HRTIM_ADC1R_AD1TBC2)    /*!< ADC Trigger on Timer B compare 2 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_CMP3    (HRTIM_ADC1R_AD1TBC3)    /*!< ADC Trigger on Timer B compare 3 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_CMP4    (HRTIM_ADC1R_AD1TBC4)    /*!< ADC Trigger on Timer B compare 4 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_PERIOD  (HRTIM_ADC1R_AD1TBPER)   /*!< ADC Trigger on Timer B period */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_RESET   (HRTIM_ADC1R_AD1TBRST)   /*!< ADC Trigger on Timer B reset */
#define HRTIM_ADCTRIGGEREVENT13_TIMERC_CMP2    (HRTIM_ADC1R_AD1TCC2)    /*!< ADC Trigger on Timer C compare 2 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERC_CMP3    (HRTIM_ADC1R_AD1TCC3)    /*!< ADC Trigger on Timer C compare 3 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERC_CMP4    (HRTIM_ADC1R_AD1TCC4)    /*!< ADC Trigger on Timer C compare 4 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERC_PERIOD  (HRTIM_ADC1R_AD1TCPER)   /*!< ADC Trigger on Timer C period */
#define HRTIM_ADCTRIGGEREVENT13_TIMERD_CMP2    (HRTIM_ADC1R_AD1TDC2)    /*!< ADC Trigger on Timer D compare 2 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERD_CMP3    (HRTIM_ADC1R_AD1TDC3)    /*!< ADC Trigger on Timer D compare 3 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERD_CMP4    (HRTIM_ADC1R_AD1TDC4)    /*!< ADC Trigger on Timer D compare 4 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERD_PERIOD  (HRTIM_ADC1R_AD1TDPER)   /*!< ADC Trigger on Timer D period */
#define HRTIM_ADCTRIGGEREVENT13_TIMERE_CMP2    (HRTIM_ADC1R_AD1TEC2)    /*!< ADC Trigger on Timer E compare 2 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERE_CMP3    (HRTIM_ADC1R_AD1TEC3)    /*!< ADC Trigger on Timer E compare 3 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERE_CMP4    (HRTIM_ADC1R_AD1TEC4)    /*!< ADC Trigger on Timer E compare 4 */
#define HRTIM_ADCTRIGGEREVENT13_TIMERE_PERIOD  (HRTIM_ADC1R_AD1TEPER)   /*!< ADC Trigger on Timer E period */

#define HRTIM_ADCTRIGGEREVENT24_NONE           (uint32_t)0x00000000     /*!< No ADC trigger event */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_CMP1    (HRTIM_ADC2R_AD2MC1)     /*!< ADC Trigger on master compare 1 */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_CMP2    (HRTIM_ADC2R_AD2MC2)     /*!< ADC Trigger on master compare 2 */ 
#define HRTIM_ADCTRIGGEREVENT24_MASTER_CMP3    (HRTIM_ADC2R_AD2MC3)     /*!< ADC Trigger on master compare 3 */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_CMP4    (HRTIM_ADC2R_AD2MC4)     /*!< ADC Trigger on master compare 4 */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_PERIOD  (HRTIM_ADC2R_AD2MPER)    /*!< ADC Trigger on master period */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_6        (HRTIM_ADC2R_AD2EEV6)    /*!< ADC Trigger on external event 6 */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_7        (HRTIM_ADC2R_AD2EEV7)    /*!< ADC Trigger on external event 7 */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_8        (HRTIM_ADC2R_AD2EEV8)    /*!< ADC Trigger on external event 8 */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_9        (HRTIM_ADC2R_AD2EEV9)    /*!< ADC Trigger on external event 9 */ 
#define HRTIM_ADCTRIGGEREVENT24_EVENT_10       (HRTIM_ADC2R_AD2EEV10)   /*!< ADC Trigger on external event 10 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERA_CMP2    (HRTIM_ADC2R_AD2TAC2)    /*!< ADC Trigger on Timer A compare 2 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERA_CMP3    (HRTIM_ADC2R_AD2TAC3)    /*!< ADC Trigger on Timer A compare 3 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERA_CMP4    (HRTIM_ADC2R_AD2TAC4)    /*!< ADC Trigger on Timer A compare 4 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERA_PERIOD  (HRTIM_ADC2R_AD2TAPER)   /*!< ADC Trigger on Timer A period */
#define HRTIM_ADCTRIGGEREVENT24_TIMERB_CMP2    (HRTIM_ADC2R_AD2TBC2)    /*!< ADC Trigger on Timer B compare 2 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERB_CMP3    (HRTIM_ADC2R_AD2TBC3)    /*!< ADC Trigger on Timer B compare 3 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERB_CMP4    (HRTIM_ADC2R_AD2TBC4)    /*!< ADC Trigger on Timer B compare 4 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERB_PERIOD  (HRTIM_ADC2R_AD2TBPER)   /*!< ADC Trigger on Timer B period */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_CMP2    (HRTIM_ADC2R_AD2TCC2)    /*!< ADC Trigger on Timer C compare 2 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_CMP3    (HRTIM_ADC2R_AD2TCC3)    /*!< ADC Trigger on Timer C compare 3 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_CMP4    (HRTIM_ADC2R_AD2TCC4)    /*!< ADC Trigger on Timer C compare 4 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_PERIOD  (HRTIM_ADC2R_AD2TCPER)   /*!< ADC Trigger on Timer C period */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_RESET   (HRTIM_ADC2R_AD2TCRST)   /*!< ADC Trigger on Timer C reset */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_CMP2    (HRTIM_ADC2R_AD2TDC2)    /*!< ADC Trigger on Timer D compare 2 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_CMP3    (HRTIM_ADC2R_AD2TDC3)    /*!< ADC Trigger on Timer D compare 3 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_CMP4    (HRTIM_ADC2R_AD2TDC4)    /*!< ADC Trigger on Timer D compare 4 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_PERIOD  (HRTIM_ADC2R_AD2TDPER)   /*!< ADC Trigger on Timer D period */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_RESET   (HRTIM_ADC2R_AD2TDRST)   /*!< ADC Trigger on Timer D reset */
#define HRTIM_ADCTRIGGEREVENT24_TIMERE_CMP2    (HRTIM_ADC2R_AD2TEC2)    /*!< ADC Trigger on Timer E compare 2 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERE_CMP3    (HRTIM_ADC2R_AD2TEC3)    /*!< ADC Trigger on Timer E compare 3 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERE_CMP4    (HRTIM_ADC2R_AD2TEC4)    /*!< ADC Trigger on Timer E compare 4 */
#define HRTIM_ADCTRIGGEREVENT24_TIMERE_RESET   (HRTIM_ADC2R_AD2TERST)   /*!< ADC Trigger on Timer E reset */

/**
  * @}
  */

/** @defgroup HRTIM_DLLCalibrationRate 
  * @{
  * @brief Constants defining the DLL calibration periods (in micro seconds)
  */

#define HRTIM_SINGLE_CALIBRATION    (uint32_t)0xFFFFFFFF                           /*!< Non periodic DLL calibration */               
#define HRTIM_CALIBRATIONRATE_7300  (uint32_t)0x00000000                           /*!< 1048576 * tHRTIM (7.3 ms) */
#define HRTIM_CALIBRATIONRATE_910   (HRTIM_DLLCR_CALRTE_0)                         /*!< 131072 * tHRTIM (910 µs) */
#define HRTIM_CALIBRATIONRATE_114   (HRTIM_DLLCR_CALRTE_1)                         /*!< 131072 * tHRTIM (910 µs) */
#define HRTIM_CALIBRATIONRATE_14    (HRTIM_DLLCR_CALRTE_1 | HRTIM_DLLCR_CALRTE_0)  /*!< 131072 * tHRTIM (910 µs) */

#define IS_HRTIM_CALIBRATIONRATE(CALIBRATIONRATE)\
    (((CALIBRATIONRATE) == HRTIM_CALIBRATIONRATE_7300)   || \
     ((CALIBRATIONRATE) == HRTIM_CALIBRATIONRATE_910)  || \
     ((CALIBRATIONRATE) == HRTIM_CALIBRATIONRATE_114)  || \
     ((CALIBRATIONRATE) == HRTIM_CALIBRATIONRATE_14))
/**
  * @}
  */

/** @defgroup HRTIM_BurstDMARegistersUpdate 
  * @{
  * @brief Constants defining the registers that can be written during a burst
  *        DMA operation
  */ 
#define HRTIM_BURSTDMA_NONE  (uint32_t)0x00000000      /*!< No register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CR    (HRTIM_BDTUPR_TIMCR)      /*!< MCR or TIMxCR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_ICR   (HRTIM_BDTUPR_TIMICR)     /*!< MICR or TIMxICR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_DIER  (HRTIM_BDTUPR_TIMDIER)    /*!< MDIER or TIMxDIER register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CNT   (HRTIM_BDTUPR_TIMCNT)     /*!< MCNTR or CNTxCR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_PER   (HRTIM_BDTUPR_TIMPER)     /*!< MPER or PERxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_REP   (HRTIM_BDTUPR_TIMREP)     /*!< MREPR or REPxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CMP1  (HRTIM_BDTUPR_TIMCMP1)    /*!< MCMP1R or CMP1xR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CMP2  (HRTIM_BDTUPR_TIMCMP2)    /*!< MCMP2R or CMP2xR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CMP3  (HRTIM_BDTUPR_TIMCMP3)    /*!< MCMP3R or CMP3xR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CMP4  (HRTIM_BDTUPR_TIMCMP4)    /*!< MCMP4R or CMP4xR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_DTR   (HRTIM_BDTUPR_TIMDTR)     /*!< TDxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_SET1R (HRTIM_BDTUPR_TIMSET1R)   /*!< SET1R register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_RST1R (HRTIM_BDTUPR_TIMRST1R)   /*!< RST1R register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_SET2R (HRTIM_BDTUPR_TIMSET2R)   /*!< SET2R register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_RST2R (HRTIM_BDTUPR_TIMRST2R)   /*!< RST1R register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_EEFR1 (HRTIM_BDTUPR_TIMEEFR1)   /*!< EEFxR1 register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_EEFR2 (HRTIM_BDTUPR_TIMEEFR2)   /*!< EEFxR2 register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_RSTR  (HRTIM_BDTUPR_TIMRSTR)    /*!< RSTxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CHPR  (HRTIM_BDTUPR_TIMCHPR)    /*!< CHPxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_OUTR  (HRTIM_BDTUPR_TIMOUTR)    /*!< OUTxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_FLTR  (HRTIM_BDTUPR_TIMFLTR)    /*!< FLTxR register is updated by Burst DMA accesses */
      
#define IS_HRTIM_TIMER_BURSTDMA(TIMER, BURSTDMA)                                       \
   ((((TIMER) == HRTIM_TIMERINDEX_MASTER) && (((BURSTDMA) & 0xFFFFFC000) == 0x00000000)) \
    ||                                                                                 \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_A) && (((BURSTDMA) & 0xFFE00000) == 0x00000000)) \
    ||                                                                                 \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_B) && (((BURSTDMA) & 0xFFE00000) == 0x00000000)) \
    ||                                                                                 \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_C) && (((BURSTDMA) & 0xFFE00000) == 0x00000000)) \
    ||                                                                                 \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_D) && (((BURSTDMA) & 0xFFE00000) == 0x00000000)) \
    ||                                                                                 \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_E) && (((BURSTDMA) & 0xFFE00000) == 0x00000000)))   
/**
  * @}
  */

/** @defgroup HRTIM_BursttModeControl 
  * @{
  * @brief Constants used to enable or disable the burst mode controller
  */ 
#define HRTIM_BURSTMODECTL_DISABLED (uint32_t)0x00000000 /*!< Burst mode disabled */
#define HRTIM_BURSTMODECTL_ENABLED  (HRTIM_BMCR_BME)     /*!< Burst mode enabled */

#define IS_HRTIM_BURSTMODECTL(BURSTMODECTL)\
    (((BURSTMODECTL) == HRTIM_BURSTMODECTL_DISABLED)  || \
     ((BURSTMODECTL) == HRTIM_BURSTMODECTL_ENABLED))
/**
  * @}
  */

/** @defgroup HRTIM_FaultModeControl 
  * @{
  * @brief Constants used to enable or disable the Fault mode
  */ 
#define HRTIM_FAULT_DISABLED   (uint32_t)0x00000000 /*!< Fault mode disabled */
#define HRTIM_FAULT_ENABLED    (HRTIM_FLTINR1_FLT1E)     /*!< Fault mode enabled */

#define IS_HRTIM_FAULTCTL(FAULTCTL)\
    (((FAULTCTL) == HRTIM_FAULT_DISABLED)  || \
     ((FAULTCTL) == HRTIM_FAULT_ENABLED))
/**
  * @}
  */      
      
/** @defgroup HRTIM_SoftwareTimerUpdate 
  * @{
  * @brief Constants used to force timer registers update
  */ 
#define HRTIM_TIMERUPDATE_MASTER    (HRTIM_CR2_MSWU)     /*!< Forces an immediate transfer from the preload to the active register in the master timer */
#define HRTIM_TIMERUPDATE_A         (HRTIM_CR2_TASWU)    /*!< Forces an immediate transfer from the preload to the active register in the timer A */
#define HRTIM_TIMERUPDATE_B         (HRTIM_CR2_TBSWU)    /*!< Forces an immediate transfer from the preload to the active register in the timer B */
#define HRTIM_TIMERUPDATE_C         (HRTIM_CR2_TCSWU)    /*!< Forces an immediate transfer from the preload to the active register in the timer C */
#define HRTIM_TIMERUPDATE_D         (HRTIM_CR2_TDSWU)    /*!< Forces an immediate transfer from the preload to the active register in the timer D */
#define HRTIM_TIMERUPDATE_E         (HRTIM_CR2_TESWU)    /*!< Forces an immediate transfer from the preload to the active register in the timer E */

#define IS_HRTIM_TIMERUPDATE(TIMERUPDATE) (((TIMERUPDATE) & 0xFFFFFFC0) == 0x00000000)
/**
  * @}
  */

/** @defgroup HRTIM_SoftwareTimerReset 
  * @{
  * @brief Constants used to force timer counter reset
  */ 
#define HRTIM_TIMERRESET_MASTER    (HRTIM_CR2_MRST)     /*!< Resets the master timer counter */
#define HRTIM_TIMERRESET_A         (HRTIM_CR2_TARST)    /*!< Resets the timer A counter */
#define HRTIM_TIMERRESET_B         (HRTIM_CR2_TBRST)    /*!< Resets the timer B counter */
#define HRTIM_TIMERRESET_C         (HRTIM_CR2_TCRST)    /*!< Resets the timer C counter */
#define HRTIM_TIMERRESET_D         (HRTIM_CR2_TDRST)    /*!< Resets the timer D counter */
#define HRTIM_TIMERRESET_E         (HRTIM_CR2_TERST)    /*!< Resets the timer E counter */

#define IS_HRTIM_TIMERRESET(TIMERRESET) (((TIMERRESET) & 0xFFFFC0FF) == 0x00000000)
/**
  * @}
  */

/** @defgroup HRTIM_OutputLevel 
  * @{
  * @brief Constants defining the level of a timer output
  */ 
#define HRTIM_OUTPUTLEVEL_ACTIVE     (uint32_t)0x00000001 /*!< Forces the output to its active state */
#define HRTIM_OUTPUTLEVEL_INACTIVE   (uint32_t)0x00000002 /*!< Forces the output to its inactive state */
      
#define IS_HRTIM_OUTPUTLEVEL(OUTPUTLEVEL)\
    (((OUTPUTLEVEL) == HRTIM_OUTPUTLEVEL_ACTIVE)  || \
     ((OUTPUTLEVEL) == HRTIM_OUTPUTLEVEL_INACTIVE))
/**
  * @}
  */

/** @defgroup HRTIM_OutputState 
  * @{
  * @brief Constants defining the state of a timer output
  */ 
#define HRTIM_OUTPUTSTATE_IDLE     (uint32_t)0x00000001  /*!< Main operating mode, where the output can take the active or 
                                                              inactive level as programmed in the crossbar unit */
#define HRTIM_OUTPUTSTATE_RUN      (uint32_t)0x00000002  /*!< Default operating state (e.g. after an HRTIM reset, when the 
                                                              outputs are disabled by software or during a burst mode operation */
#define HRTIM_OUTPUTSTATE_FAULT    (uint32_t)0x00000003  /*!< Safety state, entered in case of a shut-down request on
                                                              FAULTx inputs */
/**
  * @}
  */

/** @defgroup HRTIM_BurstModeStatus 
  * @{
  * @brief Constants defining the operating state of the burst mode controller
  */ 
#define HRTIM_BURSTMODESTATUS_NORMAL  (uint32_t) 0x00000000 /*!< Normal operation */
#define HRTIM_BURSTMODESTATUS_ONGOING (HRTIM_BMCR_BMSTAT)   /*!< Burst operation on-going */
/**
  * @}
  */
   
/** @defgroup HRTIM_CurrentPushPullStatus 
  * @{
  * @brief Constants defining on which output the signal is currently applied
  *        in push-pull mode
  */ 
#define HRTIM_PUSHPULL_CURRENTSTATUS_OUTPUT1   (uint32_t) 0x00000000   /*!< Signal applied on output 1 and output 2 forced inactive */
#define HRTIM_PUSHPULL_CURRENTSTATUS_OUTPUT2   (HRTIM_TIMISR_CPPSTAT)  /*!< Signal applied on output 2 and output 1 forced inactive */
/**
  * @}
  */
   
/** @defgroup HRTIM_IdlePushPullStatus 
  * @{
  * @brief Constants defining on which output the signal was applied, in 
  *        push-pull mode balanced fault mode or delayed idle mode, when the 
  *        protection was triggered
  */ 
#define HRTIM_PUSHPULL_IDLESTATUS_OUTPUT1   (uint32_t) 0x00000000      /*!< Protection occurred when the output 1 was active and output 2 forced inactive */
#define HRTIM_PUSHPULL_IDLESTATUS_OUTPUT2   (HRTIM_TIMISR_IPPSTAT)     /*!< Protection occurred when the output 2 was active and output 1 forced inactive */
/**
  * @}
  */
   
/** @defgroup HRTIM_CommonInterrupt
  * @{
  */ 
#define HRTIM_IT_FLT1           HRTIM_ISR_FLT1    /*!< Fault 1 interrupt flag */
#define HRTIM_IT_FLT2           HRTIM_ISR_FLT2    /*!< Fault 2 interrupt flag */
#define HRTIM_IT_FLT3           HRTIM_ISR_FLT3    /*!< Fault 3 interrupt flag */
#define HRTIM_IT_FLT4           HRTIM_ISR_FLT4    /*!< Fault 4 interrupt flag */
#define HRTIM_IT_FLT5           HRTIM_ISR_FLT5    /*!< Fault 5 interrupt flag */
#define HRTIM_IT_SYSFLT         HRTIM_ISR_SYSFLT  /*!< System Fault interrupt flag */
#define HRTIM_IT_DLLRDY         HRTIM_ISR_DLLRDY  /*!< DLL ready interrupt flag */
#define HRTIM_IT_BMPER          HRTIM_ISR_BMPER   /*!<  Burst mode period interrupt flag */

#define IS_HRTIM_IT(IT)\
               (((IT) == HRTIM_ISR_FLT1)   || \
                ((IT) == HRTIM_ISR_FLT2)   || \
                ((IT) == HRTIM_ISR_FLT3)   || \
                ((IT) == HRTIM_ISR_FLT4)   || \
                ((IT) == HRTIM_ISR_FLT5)   || \
                ((IT) == HRTIM_ISR_SYSFLT) || \
                ((IT) == HRTIM_ISR_DLLRDY) || \
                ((IT) == HRTIM_ISR_BMPER))

/**
  * @}
  */                 
/** @defgroup HRTIM_CommonFlag
  * @{
  */ 
#define HRTIM_FLAG_FLT1           HRTIM_ISR_FLT1    /*!< Fault 1 interrupt flag */
#define HRTIM_FLAG_FLT2           HRTIM_ISR_FLT2    /*!< Fault 2 interrupt flag */
#define HRTIM_FLAG_FLT3           HRTIM_ISR_FLT3    /*!< Fault 3 interrupt flag */
#define HRTIM_FLAG_FLT4           HRTIM_ISR_FLT4    /*!< Fault 4 interrupt flag */
#define HRTIM_FLAG_FLT5           HRTIM_ISR_FLT5    /*!< Fault 5 interrupt flag */
#define HRTIM_FLAG_SYSFLT         HRTIM_ISR_SYSFLT  /*!< System Fault interrupt flag */
#define HRTIM_FLAG_DLLRDY         HRTIM_ISR_DLLRDY  /*!< DLL ready interrupt flag */
#define HRTIM_FLAG_BMPER          HRTIM_ISR_BMPER   /*!<  Burst mode period interrupt flag */

#define IS_HRTIM_FLAG(FLAG)\
               (((FLAG) == HRTIM_ISR_FLT1)   || \
                ((FLAG) == HRTIM_ISR_FLT2)   || \
                ((FLAG) == HRTIM_ISR_FLT3)   || \
                ((FLAG) == HRTIM_ISR_FLT4)   || \
                ((FLAG) == HRTIM_ISR_FLT5)   || \
                ((FLAG) == HRTIM_ISR_SYSFLT) || \
                ((FLAG) == HRTIM_ISR_DLLRDY) || \
                ((FLAG) == HRTIM_ISR_BMPER))                 
/**
  * @}
  */

/** @defgroup HRTIM_MasterInterrupt
  * @{
  */ 
#define HRTIM_MASTER_IT_MCMP1        HRTIM_MDIER_MCMP1IE    /*!< Master compare 1 interrupt flag */
#define HRTIM_MASTER_IT_MCMP2        HRTIM_MDIER_MCMP2IE    /*!< Master compare 2 interrupt flag */
#define HRTIM_MASTER_IT_MCMP3        HRTIM_MDIER_MCMP3IE    /*!< Master compare 3 interrupt flag */
#define HRTIM_MASTER_IT_MCMP4        HRTIM_MDIER_MCMP4IE   /*!< Master compare 4 interrupt flag */
#define HRTIM_MASTER_IT_MREP         HRTIM_MDIER_MREPIE    /*!< Master Repetition interrupt flag */
#define HRTIM_MASTER_IT_SYNC         HRTIM_MDIER_SYNCIE    /*!< Synchronization input interrupt flag */
#define HRTIM_MASTER_IT_MUPD         HRTIM_MDIER_MUPDIE    /*!< Master update interrupt flag */

#define IS_HRTIM_MASTER_IT(IT)\
                 (((IT) == HRTIM_MDIER_MCMP1IE)  || \
                  ((IT) == HRTIM_MDIER_MCMP2IE)  || \
                  ((IT) == HRTIM_MDIER_MCMP3IE)  || \
                  ((IT) == HRTIM_MDIER_MCMP4IE)  || \
                  ((IT) == HRTIM_MDIER_MREPIE)   || \
                  ((IT) == HRTIM_MDIER_SYNCIE)   || \
                  ((IT) == HRTIM_MDIER_MUPDIE))

/** @defgroup HRTIM_MasterFlag
  * @{
  */ 
#define HRTIM_MASTER_FLAG_MCMP1        HRTIM_MISR_MCMP1    /*!< Master compare 1 interrupt flag */
#define HRTIM_MASTER_FLAG_MCMP2        HRTIM_MISR_MCMP2    /*!< Master compare 2 interrupt flag */
#define HRTIM_MASTER_FLAG_MCMP3        HRTIM_MISR_MCMP3    /*!< Master compare 3 interrupt flag */
#define HRTIM_MASTER_FLAG_MCMP4        HRTIM_MISR_MCMP4   /*!< Master compare 4 interrupt flag */
#define HRTIM_MASTER_FLAG_MREP         HRTIM_MISR_MREP    /*!< Master Repetition interrupt flag */
#define HRTIM_MASTER_FLAG_SYNC         HRTIM_MISR_SYNC    /*!< Synchronization input interrupt flag */
#define HRTIM_MASTER_FLAG_MUPD         HRTIM_MISR_MUPD    /*!< Master update interrupt flag */

#define IS_HRTIM_MASTER_FLAG(FLAG)\
                 (((FLAG) == HRTIM_MISR_MCMP1)  || \
                  ((FLAG) == HRTIM_MISR_MCMP2)  || \
                  ((FLAG) == HRTIM_MISR_MCMP3)  || \
                  ((FLAG) == HRTIM_MISR_MCMP4)  || \
                  ((FLAG) == HRTIM_MISR_MREP)   || \
                  ((FLAG) == HRTIM_MISR_SYNC)   || \
                  ((FLAG) == HRTIM_MISR_MUPD))                   
/**
  * @}
  */

/** @defgroup HRTIM_TimingUnitInterrupt
  * @{
  */ 
#define HRTIM_TIM_IT_CMP1       HRTIM_TIMDIER_CMP1IE      /*!< Timer compare 1 interrupt flag */
#define HRTIM_TIM_IT_CMP2       HRTIM_TIMDIER_CMP2IE      /*!< Timer compare 2 interrupt flag */
#define HRTIM_TIM_IT_CMP3       HRTIM_TIMDIER_CMP3IE      /*!< Timer compare 3 interrupt flag */
#define HRTIM_TIM_IT_CMP4       HRTIM_TIMDIER_CMP4IE      /*!< Timer compare 4 interrupt flag */
#define HRTIM_TIM_IT_REP        HRTIM_TIMDIER_REPIE       /*!< Timer repetition interrupt flag */
#define HRTIM_TIM_IT_UPD        HRTIM_TIMDIER_UPDIE       /*!< Timer update interrupt flag */
#define HRTIM_TIM_IT_CPT1       HRTIM_TIMDIER_CPT1IE      /*!< Timer capture 1 interrupt flag */
#define HRTIM_TIM_IT_CPT2       HRTIM_TIMDIER_CPT2IE      /*!< Timer capture 2 interrupt flag */
#define HRTIM_TIM_IT_SET1       HRTIM_TIMDIER_SET1IE      /*!< Timer output 1 set interrupt flag */
#define HRTIM_TIM_IT_RST1       HRTIM_TIMDIER_RST1IE      /*!< Timer output 1 reset interrupt flag */
#define HRTIM_TIM_IT_SET2       HRTIM_TIMDIER_SET2IE      /*!< Timer output 2 set interrupt flag */
#define HRTIM_TIM_IT_RST2       HRTIM_TIMDIER_RST2IE      /*!< Timer output 2 reset interrupt flag */
#define HRTIM_TIM_IT_RST        HRTIM_TIMDIER_RSTIE       /*!< Timer reset interrupt flag */
#define HRTIM_TIM_IT_DLYPRT     HRTIM_TIMDIER_DLYPRTIE    /*!< Timer delay protection interrupt flag */

#define IS_HRTIM_TIM_IT(IT)\
                   (((IT) == HRTIM_TIMDIER_CMP1IE)    || \
                    ((IT) == HRTIM_TIMDIER_CMP2IE)    || \
                    ((IT) == HRTIM_TIMDIER_CMP3IE)    || \
                    ((IT) == HRTIM_TIMDIER_CMP4IE)    || \
                    ((IT) == HRTIM_TIMDIER_REPIE)     || \
                    ((IT) == HRTIM_TIMDIER_UPDIE)     || \
                    ((IT) == HRTIM_TIMDIER_CPT1IE)    || \
                    ((IT) == HRTIM_TIMDIER_CPT2IE)    || \
                    ((IT) == HRTIM_TIMDIER_SET1IE)    || \
                    ((IT) == HRTIM_TIMDIER_RST1IE)    || \
                    ((IT) == HRTIM_TIMDIER_SET2IE)    || \
                    ((IT) == HRTIM_TIMDIER_RST2IE)    || \
                    ((IT) == HRTIM_TIMDIER_RSTIE)     || \
                    ((IT) == HRTIM_TIMDIER_DLYPRTIE))

/**
  * @}
  */

/** @defgroup HRTIM_TimingUnitFlag
  * @{
  */ 
#define HRTIM_TIM_FLAG_CMP1       HRTIM_TIMISR_CMP1      /*!< Timer compare 1 interrupt flag */
#define HRTIM_TIM_FLAG_CMP2       HRTIM_TIMISR_CMP2      /*!< Timer compare 2 interrupt flag */
#define HRTIM_TIM_FLAG_CMP3       HRTIM_TIMISR_CMP3      /*!< Timer compare 3 interrupt flag */
#define HRTIM_TIM_FLAG_CMP4       HRTIM_TIMISR_CMP4      /*!< Timer compare 4 interrupt flag */
#define HRTIM_TIM_FLAG_REP        HRTIM_TIMISR_REP       /*!< Timer repetition interrupt flag */
#define HRTIM_TIM_FLAG_UPD        HRTIM_TIMISR_UPD       /*!< Timer update interrupt flag */
#define HRTIM_TIM_FLAG_CPT1       HRTIM_TIMISR_CPT1      /*!< Timer capture 1 interrupt flag */
#define HRTIM_TIM_FLAG_CPT2       HRTIM_TIMISR_CPT2      /*!< Timer capture 2 interrupt flag */
#define HRTIM_TIM_FLAG_SET1       HRTIM_TIMISR_SET1      /*!< Timer output 1 set interrupt flag */
#define HRTIM_TIM_FLAG_RST1       HRTIM_TIMISR_RST1      /*!< Timer output 1 reset interrupt flag */
#define HRTIM_TIM_FLAG_SET2       HRTIM_TIMISR_SET2      /*!< Timer output 2 set interrupt flag */
#define HRTIM_TIM_FLAG_RST2       HRTIM_TIMISR_RST2      /*!< Timer output 2 reset interrupt flag */
#define HRTIM_TIM_FLAG_RST        HRTIM_TIMDIER_RSTIE       /*!< Timer reset interrupt flag */
#define HRTIM_TIM_FLAG_DLYPRT1    HRTIM_TIMISR_DLYPRT    /*!< Timer delay protection interrupt flag */

#define IS_HRTIM_TIM_FLAG(FLAG)\
                   (((FLAG) == HRTIM_TIM_FLAG_CMP1)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_CMP2)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_CMP3)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_CMP4)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_REP)     || \
                    ((FLAG) == HRTIM_TIM_FLAG_UPD)     || \
                    ((FLAG) == HRTIM_TIM_FLAG_CPT1)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_CPT2)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_SET1)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_RST1)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_SET2)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_RST2)    || \
                    ((FLAG) == HRTIM_TIM_FLAG_RST)     || \
                    ((FLAG) == HRTIM_TIM_FLAG_DLYPRT1))

/**
  * @}
  */                     
                     
/** @defgroup HRTIM_MasterDMARequest
  * @{
  */ 
#define HRTIM_MASTER_DMA_MCMP1        HRTIM_MDIER_MCMP1DE    /*!< Master compare 1 DMA request flag */
#define HRTIM_MASTER_DMA_MCMP2        HRTIM_MDIER_MCMP2DE    /*!< Master compare 2 DMA request flag */
#define HRTIM_MASTER_DMA_MCMP3        HRTIM_MDIER_MCMP3DE    /*!< Master compare 3 DMA request flag */
#define HRTIM_MASTER_DMA_MCMP4        HRTIM_MDIER_MCMP4DE   /*!< Master compare 4 DMA request flag */
#define HRTIM_MASTER_DMA_MREP         HRTIM_MDIER_MREPDE    /*!< Master Repetition DMA request flag */
#define HRTIM_MASTER_DMA_SYNC         HRTIM_MDIER_SYNCDE    /*!< Synchronization input DMA request flag */
#define HRTIM_MASTER_DMA_MUPD         HRTIM_MDIER_MUPDDE    /*!< Master update DMA request flag */

#define IS_HRTIM_MASTER_DMA(DMA)\
                 (((DMA) == HRTIM_MDIER_MCMP1DE)  || \
                  ((DMA) == HRTIM_MDIER_MCMP2DE)  || \
                  ((DMA) == HRTIM_MDIER_MCMP3DE)  || \
                  ((DMA) == HRTIM_MDIER_MCMP4DE)  || \
                  ((DMA) == HRTIM_MDIER_MREPDE)   || \
                  ((DMA) == HRTIM_MDIER_SYNCDE)   || \
                  ((DMA) == HRTIM_MDIER_MUPDDE))
/**
  * @}
  */

/** @defgroup HRTIM_TimingUnitDMARequest
  * @{
  */ 
#define HRTIM_TIM_DMA_CMP1       HRTIM_TIMDIER_CMP1DE      /*!< Timer compare 1 interrupt flag */
#define HRTIM_TIM_DMA_CMP2       HRTIM_TIMDIER_CMP2DE      /*!< Timer compare 2 interrupt flag */
#define HRTIM_TIM_DMA_CMP3       HRTIM_TIMDIER_CMP3DE      /*!< Timer compare 3 interrupt flag */
#define HRTIM_TIM_DMA_CMP4       HRTIM_TIMDIER_CMP4DE      /*!< Timer compare 4 interrupt flag */
#define HRTIM_TIM_DMA_REP        HRTIM_TIMDIER_REPDE       /*!< Timer repetition interrupt flag */
#define HRTIM_TIM_DMA_UPD        HRTIM_TIMDIER_UPDDE       /*!< Timer update interrupt flag */
#define HRTIM_TIM_DMA_CPT1       HRTIM_TIMDIER_CPT1DE      /*!< Timer capture 1 interrupt flag */
#define HRTIM_TIM_DMA_CPT2       HRTIM_TIMDIER_CPT2DE      /*!< Timer capture 2 interrupt flag */
#define HRTIM_TIM_DMA_SET1       HRTIM_TIMDIER_SET1DE      /*!< Timer output 1 set interrupt flag */
#define HRTIM_TIM_DMA_RST1       HRTIM_TIMDIER_RST1DE      /*!< Timer output 1 reset interrupt flag */
#define HRTIM_TIM_DMA_SET2       HRTIM_TIMDIER_SET2DE      /*!< Timer output 2 set interrupt flag */
#define HRTIM_TIM_DMA_RST2       HRTIM_TIMDIER_RST2DE      /*!< Timer output 2 reset interrupt flag */
#define HRTIM_TIM_DMA_RST        HRTIM_TIMDIER_RSTDE       /*!< Timer reset interrupt flag */
#define HRTIM_TIM_DMA_DLYPRT     HRTIM_TIMDIER_DLYPRTDE    /*!< Timer delay protection interrupt flag */

#define IS_HRTIM_TIM_DMA(DMA)\
                   (((DMA) == HRTIM_TIMDIER_CMP1DE)    || \
                    ((DMA) == HRTIM_TIMDIER_CMP2DE)    || \
                    ((DMA) == HRTIM_TIMDIER_CMP3DE)    || \
                    ((DMA) == HRTIM_TIMDIER_CMP4DE)    || \
                    ((DMA) == HRTIM_TIMDIER_REPDE)     || \
                    ((DMA) == HRTIM_TIMDIER_UPDDE)     || \
                    ((DMA) == HRTIM_TIMDIER_CPT1DE)    || \
                    ((DMA) == HRTIM_TIMDIER_CPT2DE)    || \
                    ((DMA) == HRTIM_TIMDIER_SET1DE)    || \
                    ((DMA) == HRTIM_TIMDIER_RST1DE)    || \
                    ((DMA) == HRTIM_TIMDIER_SET2DE)    || \
                    ((DMA) == HRTIM_TIMDIER_RST2DE)    || \
                    ((DMA) == HRTIM_TIMDIER_RSTDE)     || \
                    ((DMA) == HRTIM_TIMDIER_DLYPRTDE))

/**
  * @}
  */
                
/**
  * @}
  */

/** @defgroup HRTIM_Instancedefinition 
  * @{
  */ 
#define IS_HRTIM_INSTANCE(INSTANCE) (INSTANCE) == HRTIM1)
/**
  * @}
  */

/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/

  
/** @brief  Enables or disables the timer counter(s)
  * @param  __HANDLE__: specifies the HRTIM Handle.
  * @param  __TIMERS__: timers to enable/disable
  *        This parameter can be any combinations of the following values:
  *            @arg HRTIM_TIMERID_MASTER: Master timer identifier
  *            @arg HRTIM_TIMERID_TIMER_A: Timer A identifier
  *            @arg HRTIM_TIMERID_TIMER_B: Timer B identifier
  *            @arg HRTIM_TIMERID_TIMER_C: Timer C identifier
  *            @arg HRTIM_TIMERID_TIMER_D: Timer D identifier
  *            @arg HRTIM_TIMERID_TIMER_E: Timer E identifier
  * @retval None
  */
#define __HRTIM_ENABLE(__HANDLE__, __TIMERS__)   ((__HANDLE__)->HRTIM_MASTER.MCR |= (__TIMERS__))
                     
/* The counter of a timing unit is disabled only if all the timer outputs */
/* are disabled and no capture is configured                              */                         
#define HRTIM_TAOEN_MASK (HRTIM_OENR_TA2OEN | HRTIM_OENR_TA1OEN)                 
#define HRTIM_TBOEN_MASK (HRTIM_OENR_TB2OEN | HRTIM_OENR_TB1OEN)                 
#define HRTIM_TCOEN_MASK (HRTIM_OENR_TC2OEN | HRTIM_OENR_TC1OEN)                 
#define HRTIM_TDOEN_MASK (HRTIM_OENR_TD2OEN | HRTIM_OENR_TD1OEN)                 
#define HRTIM_TEOEN_MASK (HRTIM_OENR_TE2OEN | HRTIM_OENR_TE1OEN)                 
#define __HRTIM_DISABLE(__HANDLE__, __TIMERS__)\
  do {\
    if (((__TIMERS__) & HRTIM_TIMERID_MASTER) == HRTIM_TIMERID_MASTER)\
      {\
        ((__HANDLE__)->HRTIM_MASTER.MCR &= ~HRTIM_TIMERID_MASTER);\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_A) == HRTIM_TIMERID_TIMER_A)\
      {\
        if (((__HANDLE__)->HRTIM_COMMON.OENR & HRTIM_TAOEN_MASK) == RESET)\
          {\
            ((__HANDLE__)->HRTIM_MASTER.MCR &= ~HRTIM_TIMERID_TIMER_A);\
          }\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_B) == HRTIM_TIMERID_TIMER_B)\
      {\
        if (((__HANDLE__)->HRTIM_COMMON.OENR & HRTIM_TBOEN_MASK) == RESET)\
          {\
            ((__HANDLE__)->HRTIM_MASTER.MCR &= ~HRTIM_TIMERID_TIMER_B);\
          }\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_C) == HRTIM_TIMERID_TIMER_C)\
      {\
        if (((__HANDLE__)->HRTIM_COMMON.OENR & HRTIM_TCOEN_MASK) == RESET)\
          {\
            ((__HANDLE__)->HRTIM_MASTER.MCR &= ~HRTIM_TIMERID_TIMER_C);\
          }\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_D) == HRTIM_TIMERID_TIMER_D)\
      {\
        if (((__HANDLE__)->HRTIM_COMMON.OENR & HRTIM_TDOEN_MASK) == RESET)\
          {\
            ((__HANDLE__)->HRTIM_MASTER.MCR &= ~HRTIM_TIMERID_TIMER_D);\
          }\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_E) == HRTIM_TIMERID_TIMER_E)\
      {\
        if (((__HANDLE__)->HRTIM_COMMON.OENR & HRTIM_TEOEN_MASK) == RESET)\
          {\
            ((__HANDLE__)->HRTIM_MASTER.MCR &= ~HRTIM_TIMERID_TIMER_E);\
          }\
      }\
  } while(0)
                       
/* Exported functions --------------------------------------------------------*/

/* Simple time base related functions  *****************************************/
void HRTIM_SimpleBase_Init(HRTIM_TypeDef* HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct);

void HRTIM_DeInit(HRTIM_TypeDef* HRTIMx);

void HRTIM_SimpleBaseStart(HRTIM_TypeDef *HRTIMx, uint32_t TimerIdx);
void HRTIM_SimpleBaseStop(HRTIM_TypeDef *HRTIMx, uint32_t TimerIdx);

/* Simple output compare related functions  ************************************/
void HRTIM_SimpleOC_Init(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct);

void HRTIM_SimpleOCChannelConfig(HRTIM_TypeDef *HRTIMx,
                                                 uint32_t TimerIdx,
                                                 uint32_t OCChannel,
                                                 HRTIM_BasicOCChannelCfgTypeDef* pBasicOCChannelCfg);

void HRTIM_SimpleOCStart(HRTIM_TypeDef *HRTIMx,
                                         uint32_t TimerIdx,
                                         uint32_t OCChannel);
void HRTIM_SimpleOCStop(HRTIM_TypeDef * HRTIMx,
                                        uint32_t TimerIdx,
                                        uint32_t OCChannel);
/* Simple PWM output related functions  ****************************************/
void HRTIM_SimplePWM_Init(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct);

void HRTIM_SimplePWMChannelConfig(HRTIM_TypeDef *HRTIMx,
                                                  uint32_t TimerIdx,
                                                  uint32_t PWMChannel,
                                                  HRTIM_BasicPWMChannelCfgTypeDef* pBasicPWMChannelCfg);

void HRTIM_SimplePWMStart(HRTIM_TypeDef * HRTIMx,
                                          uint32_t TimerIdx,
                                          uint32_t PWMChannel);
void HRTIM_SimplePWMStop(HRTIM_TypeDef * HRTIMx,
                                         uint32_t TimerIdx,
                                         uint32_t PWMChannel);
/* Simple capture related functions  *******************************************/
void HRTIM_SimpleCapture_Init(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct);

void HRTIM_SimpleCaptureChannelConfig(HRTIM_TypeDef *HRTIMx,
                                                      uint32_t TimerIdx,
                                                      uint32_t CaptureChannel,
                                                      HRTIM_BasicCaptureChannelCfgTypeDef* pBasicCaptureChannelCfg);

void HRTIM_SimpleCaptureStart(HRTIM_TypeDef * HRTIMx,
                                              uint32_t TimerIdx,
                                              uint32_t CaptureChannel);
void HRTIM_SimpleCaptureStop(HRTIM_TypeDef * HRTIMx,
                                             uint32_t TimerIdx,
                                             uint32_t CaptureChannel);
/* SImple one pulse related functions  *****************************************/
void HRTIM_SimpleOnePulse_Init(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct);

void HRTIM_SimpleOnePulseChannelConfig(HRTIM_TypeDef *HRTIMx,
                                                       uint32_t TimerIdx,
                                                       uint32_t OnePulseChannel,
                                                       HRTIM_BasicOnePulseChannelCfgTypeDef* pBasicOnePulseChannelCfg);

void HRTIM_SimpleOnePulseStart(HRTIM_TypeDef * HRTIMx,
                                                uint32_t TimerIdx,
                                                uint32_t OnePulseChannel);
void HRTIM_SimpleOnePulseStop(HRTIM_TypeDef * HRTIM_,
                                              uint32_t TimerIdx,
                                              uint32_t OnePulseChannel);
/* Waveform related functions *************************************************/
void HRTIM_Waveform_Init(HRTIM_TypeDef * HRTIMx,
                                         uint32_t TimerIdx,
                                         HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct,
                                         HRTIM_TimerInitTypeDef* HRTIM_TimerInitStruct);

void HRTIM_WaveformTimerConfig(HRTIM_TypeDef *HRTIMx,
                                                uint32_t TimerIdx,
                                                HRTIM_TimerCfgTypeDef * HRTIM_TimerCfgStruct);

void HRTIM_WaveformCompareConfig(HRTIM_TypeDef *HRTIMx,
                                                  uint32_t TimerIdx,
                                                  uint32_t CompareUnit,
                                                  HRTIM_CompareCfgTypeDef* pCompareCfg);

void HRTIM_SlaveSetCompare(HRTIM_TypeDef * HRTIMx,
                                                  uint32_t TimerIdx,
                                                  uint32_t CompareUnit,
                                                  uint32_t Compare);

void HRTIM_MasterSetCompare(HRTIM_TypeDef * HRTIMx,
                                                  uint32_t CompareUnit,
                                                  uint32_t Compare);

void HRTIM_WaveformCaptureConfig(HRTIM_TypeDef *HRTIMx,
                                                  uint32_t TimerIdx,
                                                  uint32_t CaptureUnit,
                                                  HRTIM_CaptureCfgTypeDef* pCaptureCfg);

void HRTIM_TimerEventFilteringConfig(HRTIM_TypeDef *HRTIMx,
                                                      uint32_t TimerIdx,
                                                      uint32_t Event,
                                                      HRTIM_TimerEventFilteringCfgTypeDef * pTimerEventFilteringCfg);

void HRTIM_DeadTimeConfig(HRTIM_TypeDef *HRTIMx,
                                           uint32_t TimerIdx,
                                           HRTIM_DeadTimeCfgTypeDef* pDeadTimeCfg);

void HRTIM_ChopperModeConfig(HRTIM_TypeDef *HRTIMx,
                                              uint32_t TimerIdx,
                                              HRTIM_ChopperModeCfgTypeDef* pChopperModeCfg);

void HRTIM_BurstDMAConfig(HRTIM_TypeDef *HRTIMx,
                                           uint32_t TimerIdx,
                                           uint32_t RegistersToUpdate);

void HRTIM_SynchronizationConfig(HRTIM_TypeDef *HRTIMx,
                                                  HRTIM_SynchroCfgTypeDef * pSynchroCfg);

void HRTIM_BurstModeConfig(HRTIM_TypeDef *HRTIMx,
                                            HRTIM_BurstModeCfgTypeDef* pBurstModeCfg);

void HRTIM_EventConfig(HRTIM_TypeDef *HRTIMx,
                                        uint32_t Event,
                                        HRTIM_EventCfgTypeDef* pEventCfg);

void HRTIM_EventPrescalerConfig(HRTIM_TypeDef *HRTIMx,
                                                 uint32_t Prescaler);
 
void HRTIM_FaultConfig(HRTIM_TypeDef *hrtim,
                                        HRTIM_FaultCfgTypeDef* pFaultCfg,
                                        uint32_t Fault);

void HRTIM_FaultPrescalerConfig(HRTIM_TypeDef *HRTIMx,
                                                 uint32_t Prescaler);
void HRTIM_FaultModeCtl(HRTIM_TypeDef * HRTIMx, uint32_t Fault, uint32_t Enable);

void HRTIM_ADCTriggerConfig(HRTIM_TypeDef *HRTIMx,
                                             uint32_t ADCTrigger,
                                             HRTIM_ADCTriggerCfgTypeDef* pADCTriggerCfg);

void HRTIM_WaveformCounterStart(HRTIM_TypeDef *HRTIMx,
                                                 uint32_t TimersToStart);

void HRTIM_WaveformCounterStop(HRTIM_TypeDef *HRTIMx,
                                                 uint32_t TimersToStop);

void HRTIM_WaveformOutputStart(HRTIM_TypeDef *HRTIMx,
                                                uint32_t OutputsToStart);
void HRTIM_WaveformOutputStop(HRTIM_TypeDef * HRTIM_,
                                               uint32_t OutputsToStop);

void HRTIM_DLLCalibrationStart(HRTIM_TypeDef *HRTIMx,
                                                uint32_t CalibrationRate);
 
/* Interrupt/flags and DMA management */
void HRTIM_ITConfig(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_TIM_IT, FunctionalState NewState);
void HRTIM_ITCommonConfig(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonIT, FunctionalState NewState);

void HRTIM_ClearFlag(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_FLAG);
void HRTIM_ClearCommonFlag(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonFLAG);

void HRTIM_ClearITPendingBit(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_IT);
void HRTIM_ClearCommonITPendingBit(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonIT);

FlagStatus HRTIM_GetFlagStatus(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_FLAG);
FlagStatus HRTIM_GetCommonFlagStatus(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonFLAG);

ITStatus HRTIM_GetITStatus(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_IT);
ITStatus HRTIM_GetCommonITStatus(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonIT);


void HRTIM_DMACmd(HRTIM_TypeDef* HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_DMA, FunctionalState NewState);

void HRTIM_BurstModeCtl(HRTIM_TypeDef *HRTIMx,
                                         uint32_t Enable);

void HRTIM_SoftwareCapture(HRTIM_TypeDef *HRTIMx,
                                            uint32_t TimerIdx,
                                            uint32_t CaptureUnit);

void HRTIM_SoftwareUpdate(HRTIM_TypeDef *HRTIMx,
                                           uint32_t TimersToUpdate);

void HRTIM_SoftwareReset(HRTIM_TypeDef *HRTIMx,
                                          uint32_t TimersToReset);


uint32_t HRTIM_GetCapturedValue(HRTIM_TypeDef *HRTIMx,
                                    uint32_t TimerIdx,
                                    uint32_t CaptureUnit);

void HRTIM_WaveformOutputConfig(HRTIM_TypeDef * HRTIMx,
                                                uint32_t TimerIdx,
                                                uint32_t Output,
                                                HRTIM_OutputCfgTypeDef * pOutputCfg);

void HRTIM_WaveformSetOutputLevel(HRTIM_TypeDef *HRTIMx,
                                                   uint32_t TimerIdx,
                                                   uint32_t Output, 
                                                   uint32_t OutputLevel);

uint32_t HRTIM_WaveformGetOutputLevel(HRTIM_TypeDef *HRTIMx,
                                          uint32_t TimerIdx,
                                          uint32_t Output);

uint32_t HRTIM_WaveformGetOutputState(HRTIM_TypeDef * HRTIMx,
                                          uint32_t TimerIdx,
                                          uint32_t Output);
                                          
uint32_t HRTIM_GetDelayedProtectionStatus(HRTIM_TypeDef *HRTIMx,
                                              uint32_t TimerIdx,
                                              uint32_t Output);

uint32_t HRTIM_GetBurstStatus(HRTIM_TypeDef *HRTIMx);

uint32_t HRTIM_GetCurrentPushPullStatus(HRTIM_TypeDef *HRTIMx,
                                            uint32_t TimerIdx);

uint32_t HRTIM_GetIdlePushPullStatus(HRTIM_TypeDef *HRTIMx,
                                         uint32_t TimerIdx);
/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_HRTIM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_i2c.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the I2C firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_I2C_H
#define __STM32F30x_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
                                         This parameter calculated by referring to I2C initialization 
                                         section in Reference manual*/

  uint32_t I2C_AnalogFilter;        /*!< Enables or disables analog noise filter.
                                         This parameter can be a value of @ref I2C_Analog_Filter */

  uint32_t I2C_DigitalFilter;       /*!< Configures the digital noise filter.
                                         This parameter can be a number between 0x00 and 0x0F */

  uint32_t I2C_Mode;                /*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode */

  uint32_t I2C_OwnAddress1;         /*!< Specifies the device own address 1.
                                         This parameter can be a 7-bit or 10-bit address */

  uint32_t I2C_Ack;                 /*!< Enables or disables the acknowledgement.
                                         This parameter can be a value of @ref I2C_acknowledgement */

  uint32_t I2C_AcknowledgedAddress; /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                         This parameter can be a value of @ref I2C_acknowledged_address */
}I2C_InitTypeDef;

/* Exported constants --------------------------------------------------------*/


/** @defgroup I2C_Exported_Constants
  * @{
  */

#define IS_I2C_ALL_PERIPH(PERIPH)       (((PERIPH) == I2C1) || \
                                         ((PERIPH) == I2C2))

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
void I2C_StopModeCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
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

#endif /*__STM32F30x_I2C_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_iwdg.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_IWDG_H
#define __STM32F30x_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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

#define IWDG_FLAG_PVU               ((uint16_t)0x0001)
#define IWDG_FLAG_RVU               ((uint16_t)0x0002)
#define IWDG_FLAG_WVU               ((uint16_t)0x0002)
#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU)  || \
                            ((FLAG) == IWDG_FLAG_WVU))
/**
  * @}
  */
  
/** @defgroup IWDG_Reload_Value
  * @{
  */
#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)

/**
  * @}
  */

/** @defgroup IWDG_CounterWindow_Value
  * @{
  */
#define IS_IWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0xFFF)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

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

#endif /* __STM32F30x_IWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_misc.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the miscellaneous
  *          firmware library functions (add-on to CMSIS functions).
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_MISC_H
#define __STM32F30x_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
  uint8_t NVIC_IRQChannel;                    /*!< Specifies the IRQ channel to be enabled or disabled.
                                                   This parameter can be a value of @ref IRQn_Type (For 
                                                   the complete STM32 Devices IRQ Channels list, please
                                                    refer to stm32f30x.h file) */

  uint8_t NVIC_IRQChannelPreemptionPriority;  /*!< Specifies the pre-emption priority for the IRQ channel
                                                   specified in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15.
                                                   A lower priority value indicates a higher priority */
                                                   

  uint8_t NVIC_IRQChannelSubPriority;         /*!< Specifies the subpriority level for the IRQ channel specified
                                                   in NVIC_IRQChannel. This parameter can be a value 
                                                   between 0 and 15.
                                                   A lower priority value indicates a higher priority */

  FunctionalState NVIC_IRQChannelCmd;         /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                                   will be enabled or disabled. 
                                                   This parameter can be set either to ENABLE or DISABLE */   
} NVIC_InitTypeDef;

/**  
  *
@verbatim   
 The table below gives the allowed values of the pre-emption priority and subpriority according
 to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
@endverbatim
*/
 
/* Exported constants --------------------------------------------------------*/

/** @defgroup MISC_Exported_Constants
  * @{
  */

/** @defgroup MISC_Vector_Table_Base 
  * @{
  */

#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
#define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == NVIC_VectTab_RAM) || \
                                  ((VECTTAB) == NVIC_VectTab_FLASH))
/**
  * @}
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

#define NVIC_PriorityGroup_0         ((uint32_t)0x700) /*!< 0 bits for pre-emption priority
                                                            4 bits for subpriority */
#define NVIC_PriorityGroup_1         ((uint32_t)0x600) /*!< 1 bits for pre-emption priority
                                                            3 bits for subpriority */
#define NVIC_PriorityGroup_2         ((uint32_t)0x500) /*!< 2 bits for pre-emption priority
                                                            2 bits for subpriority */
#define NVIC_PriorityGroup_3         ((uint32_t)0x400) /*!< 3 bits for pre-emption priority
                                                            1 bits for subpriority */
#define NVIC_PriorityGroup_4         ((uint32_t)0x300) /*!< 4 bits for pre-emption priority
                                                            0 bits for subpriority */

#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PriorityGroup_0) || \
                                       ((GROUP) == NVIC_PriorityGroup_1) || \
                                       ((GROUP) == NVIC_PriorityGroup_2) || \
                                       ((GROUP) == NVIC_PriorityGroup_3) || \
                                       ((GROUP) == NVIC_PriorityGroup_4))

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)

/**
  * @}
  */

/** @defgroup MISC_SysTick_clock_source 
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
/* Exported functions --------------------------------------------------------*/

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_MISC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_opamp.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the operational
  *          amplifiers (OPAMP) firmware library.         
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_OPAMP_H
#define __STM32F30x_OPAMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup OPAMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  OPAMP Init structure definition  
  */
  
typedef struct
{

  uint32_t OPAMP_InvertingInput;     /*!< Selects the inverting input of the operational amplifier.
                                          This parameter can be a value of @ref OPAMP_InvertingInput */

  uint32_t OPAMP_NonInvertingInput;  /*!< Selects the non inverting input of the operational amplifier.
                                         This parameter can be a value of @ref OPAMP_NonInvertingInput */

}OPAMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Constants
  * @{
  */ 

/** @defgroup OPAMP_Selection
  * @{
  */

#define OPAMP_Selection_OPAMP1                    ((uint32_t)0x00000000) /*!< OPAMP1 Selection */
#define OPAMP_Selection_OPAMP2                    ((uint32_t)0x00000004) /*!< OPAMP2 Selection */
#define OPAMP_Selection_OPAMP3                    ((uint32_t)0x00000008) /*!< OPAMP3 Selection */
#define OPAMP_Selection_OPAMP4                    ((uint32_t)0x0000000C) /*!< OPAMP4 Selection */

#define IS_OPAMP_ALL_PERIPH(PERIPH) (((PERIPH) == OPAMP_Selection_OPAMP1) || \
                                     ((PERIPH) == OPAMP_Selection_OPAMP2) || \
                                     ((PERIPH) == OPAMP_Selection_OPAMP3) || \
                                     ((PERIPH) == OPAMP_Selection_OPAMP4))
 
/**
  * @}
  */

/** @defgroup OPAMP_InvertingInput
  * @{
  */

#define OPAMP_InvertingInput_IO1          ((uint32_t)0x00000000) /*!< IO1 (PC5 for OPAMP1 and OPAMP2, PB10 for OPAMP3 and OPAMP4)
                                                                     connected to OPAMPx inverting input */
#define OPAMP_InvertingInput_IO2          OPAMP_CSR_VMSEL_0      /*!< IO2 (PA3 for OPAMP1, PA5 for OPAMP2, PB2 for OPAMP3, PD8 for OPAMP4)
                                                                      connected to OPAMPx inverting input */
#define OPAMP_InvertingInput_PGA          OPAMP_CSR_VMSEL_1      /*!< Resistor feedback output connected to OPAMPx inverting input (PGA mode) */
#define OPAMP_InvertingInput_Vout         OPAMP_CSR_VMSEL        /*!< Vout connected to OPAMPx inverting input (follower mode) */

#define IS_OPAMP_INVERTING_INPUT(INPUT) (((INPUT) == OPAMP_InvertingInput_IO1) || \
                                         ((INPUT) == OPAMP_InvertingInput_IO2) || \
                                         ((INPUT) == OPAMP_InvertingInput_PGA) || \
                                         ((INPUT) == OPAMP_InvertingInput_Vout))
/**
  * @}
  */

/** @defgroup OPAMP_NonInvertingInput
  * @{
  */

#define OPAMP_NonInvertingInput_IO1          ((uint32_t)0x00000000) /*!< IO1 (PA7 for OPAMP1, PD14 for OPAMP2, PB13 for OPAMP3, PD11 for OPAMP4)
                                                                        connected to OPAMPx non inverting input */
#define OPAMP_NonInvertingInput_IO2          OPAMP_CSR_VPSEL_0      /*!< IO2 (PA5 for OPAMP1, PB14 for OPAMP2, PA5 for OPAMP3, PB11 for OPAMP4)
                                                                         connected to OPAMPx non inverting input */
#define OPAMP_NonInvertingInput_IO3          OPAMP_CSR_VPSEL_1      /*!< IO3 (PA3 for OPAMP1, PB0 for OPAMP2, PA1 for OPAMP3, PA4 for OPAMP4)
                                                                         connected to OPAMPx non inverting input */
#define OPAMP_NonInvertingInput_IO4          OPAMP_CSR_VPSEL        /*!< IO4 (PA1 for OPAMP1, PA7 for OPAMP2, PB0 for OPAMP3, PB13 for OPAMP4)
                                                                         connected to OPAMPx non inverting input */

#define IS_OPAMP_NONINVERTING_INPUT(INPUT) (((INPUT) == OPAMP_NonInvertingInput_IO1) || \
                                            ((INPUT) == OPAMP_NonInvertingInput_IO2) || \
                                            ((INPUT) == OPAMP_NonInvertingInput_IO3) || \
                                            ((INPUT) == OPAMP_NonInvertingInput_IO4))
/**
  * @}
  */

/** @defgroup OPAMP_PGAGain_Config
  * @{
  */

#define OPAMP_OPAMP_PGAGain_2                ((uint32_t)0x00000000)
#define OPAMP_OPAMP_PGAGain_4                OPAMP_CSR_PGGAIN_0
#define OPAMP_OPAMP_PGAGain_8                OPAMP_CSR_PGGAIN_1
#define OPAMP_OPAMP_PGAGain_16               ((uint32_t)0x0000C000)

#define IS_OPAMP_PGAGAIN(GAIN) (((GAIN) == OPAMP_OPAMP_PGAGain_2) || \
                                ((GAIN) == OPAMP_OPAMP_PGAGain_4) || \
                                ((GAIN) == OPAMP_OPAMP_PGAGain_8) || \
                                ((GAIN) == OPAMP_OPAMP_PGAGain_16))
/**
  * @}
  */

/** @defgroup OPAMP_PGAConnect_Config
  * @{
  */

#define OPAMP_PGAConnect_No                ((uint32_t)0x00000000)
#define OPAMP_PGAConnect_IO1               OPAMP_CSR_PGGAIN_3
#define OPAMP_PGAConnect_IO2               ((uint32_t)0x00030000)

#define IS_OPAMP_PGACONNECT(CONNECT) (((CONNECT) == OPAMP_PGAConnect_No)  || \
                                      ((CONNECT) == OPAMP_PGAConnect_IO1) || \
                                      ((CONNECT) == OPAMP_PGAConnect_IO2))
/**
  * @}
  */

/** @defgroup OPAMP_SecondaryInvertingInput
  * @{
  */

#define IS_OPAMP_SECONDARY_INVINPUT(INVINPUT) (((INVINPUT) == OPAMP_InvertingInput_IO1) || \
                                               ((INVINPUT) == OPAMP_InvertingInput_IO2))
/**
  * @}
  */

/** @defgroup OPAMP_Input
  * @{
  */

#define OPAMP_Input_Inverting                 ((uint32_t)0x00000018) /*!< Inverting input */
#define OPAMP_Input_NonInverting              ((uint32_t)0x00000013) /*!< Non inverting input */

#define IS_OPAMP_INPUT(INPUT) (((INPUT) == OPAMP_Input_Inverting) || \
                               ((INPUT) == OPAMP_Input_NonInverting))

/**
  * @}
  */ 

/** @defgroup OPAMP_Vref
  * @{
  */

#define OPAMP_Vref_3VDDA                    ((uint32_t)0x00000000) /*!< OPMAP Vref = 3.3% VDDA */
#define OPAMP_Vref_10VDDA                    OPAMP_CSR_CALSEL_0     /*!< OPMAP Vref = 10% VDDA  */
#define OPAMP_Vref_50VDDA                    OPAMP_CSR_CALSEL_1     /*!< OPMAP Vref = 50% VDDA  */
#define OPAMP_Vref_90VDDA                    OPAMP_CSR_CALSEL       /*!< OPMAP Vref = 90% VDDA  */

#define IS_OPAMP_VREF(VREF) (((VREF) == OPAMP_Vref_3VDDA)  || \
                             ((VREF) == OPAMP_Vref_10VDDA) || \
                             ((VREF) == OPAMP_Vref_50VDDA) || \
                             ((VREF) == OPAMP_Vref_90VDDA))

/**
  * @}
  */

/** @defgroup OPAMP_Trimming
  */

#define OPAMP_Trimming_Factory        ((uint32_t)0x00000000) /*!< Factory trimming */
#define OPAMP_Trimming_User           OPAMP_CSR_USERTRIM     /*!< User trimming */

#define IS_OPAMP_TRIMMING(TRIMMING) (((TRIMMING) == OPAMP_Trimming_Factory) || \
                                     ((TRIMMING) == OPAMP_Trimming_User))

/**
  * @}
  */ 

/** @defgroup OPAMP_TrimValue
  * @{
  */

#define IS_OPAMP_TRIMMINGVALUE(VALUE) ((VALUE) <= 0x0000001F) /*!< Trimming value */

/**
  * @}
  */

/** @defgroup OPAMP_OutputLevel
  * @{
  */

#define OPAMP_OutputLevel_High                   OPAMP_CSR_OUTCAL
#define OPAMP_OutputLevel_Low                    ((uint32_t)0x00000000)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the OPAMP configuration to the default reset state ***/
void OPAMP_DeInit(uint32_t OPAMP_Selection);

/* Initialization and Configuration functions *********************************/
void OPAMP_Init(uint32_t OPAMP_Selection, OPAMP_InitTypeDef* OPAMP_InitStruct);
void OPAMP_StructInit(OPAMP_InitTypeDef* OPAMP_InitStruct);
void OPAMP_PGAConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_PGAGain, uint32_t OPAMP_PGAConnect);
void OPAMP_VrefConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Vref);
void OPAMP_VrefConnectADCCmd(uint32_t OPAMP_Selection, FunctionalState NewState);
void OPAMP_TimerControlledMuxConfig(uint32_t OPAMP_Selection, OPAMP_InitTypeDef* OPAMP_InitStruct);
void OPAMP_TimerControlledMuxCmd(uint32_t OPAMP_Selection, FunctionalState NewState);
void OPAMP_Cmd(uint32_t OPAMP_Selection, FunctionalState NewState);
uint32_t OPAMP_GetOutputLevel(uint32_t OPAMP_Selection);

/* Calibration functions ******************************************************/
void OPAMP_VrefConnectNonInvertingInput(uint32_t OPAMP_Selection, FunctionalState NewState);
void OPAMP_OffsetTrimModeSelect(uint32_t OPAMP_Selection, uint32_t OPAMP_Trimming);
void OPAMP_OffsetTrimConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue);
void OPAMP_StartCalibration(uint32_t OPAMP_Selection, FunctionalState NewState);

/* OPAMP configuration locking function ***************************************/
void OPAMP_LockConfig(uint32_t OPAMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_OPAMP_H */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_pwr.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the PWR firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_PWR_H
#define __STM32F30x_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
#define PWR_WakeUpPin_3                 PWR_CSR_EWUP3
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WakeUpPin_1) || \
                                ((PIN) == PWR_WakeUpPin_2) || \
                                ((PIN) == PWR_WakeUpPin_3))
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
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE))
 
/**
  * @}
  */

/** @defgroup PWR_Flag 
  * @{
  */

#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO
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
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_PVDCmd(FunctionalState NewState);

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

#endif /* __STM32F30x_PWR_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_rcc.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the RCC 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_RCC_H
#define __STM32F30x_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
  uint32_t PCLK1_Frequency;
  uint32_t PCLK2_Frequency;
  uint32_t ADC12CLK_Frequency;
  uint32_t ADC34CLK_Frequency;
  uint32_t I2C1CLK_Frequency;
  uint32_t I2C2CLK_Frequency;
  uint32_t I2C3CLK_Frequency;
  uint32_t TIM1CLK_Frequency;
  uint32_t HRTIM1CLK_Frequency;
  uint32_t TIM8CLK_Frequency;
  uint32_t TIM2CLK_Frequency;
  uint32_t TIM3CLK_Frequency;
  uint32_t USART1CLK_Frequency;
  uint32_t USART2CLK_Frequency;
  uint32_t USART3CLK_Frequency;
  uint32_t UART4CLK_Frequency;
  uint32_t UART5CLK_Frequency;
  uint32_t TIM15CLK_Frequency;
  uint32_t TIM16CLK_Frequency;
  uint32_t TIM17CLK_Frequency;  
  uint32_t TIM20CLK_Frequency;
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
#define RCC_PLLSource_HSI                RCC_CFGR_PLLSRC_HSI_PREDIV     /*!< Only applicable for STM32F303xE devices */
#define RCC_PLLSource_HSI_Div2           RCC_CFGR_PLLSRC_HSI_Div2
#define RCC_PLLSource_PREDIV1            RCC_CFGR_PLLSRC_PREDIV1
 
#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_PREDIV1)|| \
                   ((SOURCE) == RCC_PLLSource_HSI))
                   
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
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
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

/** @defgroup RCC_APB1_APB2_clock_source 
  * @{
  */

#define RCC_HCLK_Div1                    ((uint32_t)0x00000000)
#define RCC_HCLK_Div2                    ((uint32_t)0x00000400)
#define RCC_HCLK_Div4                    ((uint32_t)0x00000500)
#define RCC_HCLK_Div8                    ((uint32_t)0x00000600)
#define RCC_HCLK_Div16                   ((uint32_t)0x00000700)
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))
/**
  * @}
  */
  
/** @defgroup RCC_ADC_clock_source 
  * @{
  */
  
/* ADC1 & ADC2 */
#define RCC_ADC12PLLCLK_OFF                    ((uint32_t)0x00000000)
#define RCC_ADC12PLLCLK_Div1                   ((uint32_t)0x00000100)
#define RCC_ADC12PLLCLK_Div2                   ((uint32_t)0x00000110)
#define RCC_ADC12PLLCLK_Div4                   ((uint32_t)0x00000120)
#define RCC_ADC12PLLCLK_Div6                   ((uint32_t)0x00000130)
#define RCC_ADC12PLLCLK_Div8                   ((uint32_t)0x00000140)
#define RCC_ADC12PLLCLK_Div10                  ((uint32_t)0x00000150)
#define RCC_ADC12PLLCLK_Div12                  ((uint32_t)0x00000160)
#define RCC_ADC12PLLCLK_Div16                  ((uint32_t)0x00000170)
#define RCC_ADC12PLLCLK_Div32                  ((uint32_t)0x00000180)
#define RCC_ADC12PLLCLK_Div64                  ((uint32_t)0x00000190)
#define RCC_ADC12PLLCLK_Div128                 ((uint32_t)0x000001A0)
#define RCC_ADC12PLLCLK_Div256                 ((uint32_t)0x000001B0)

/* ADC3 & ADC4 */
#define RCC_ADC34PLLCLK_OFF                    ((uint32_t)0x10000000)
#define RCC_ADC34PLLCLK_Div1                   ((uint32_t)0x10002000)
#define RCC_ADC34PLLCLK_Div2                   ((uint32_t)0x10002200)
#define RCC_ADC34PLLCLK_Div4                   ((uint32_t)0x10002400)
#define RCC_ADC34PLLCLK_Div6                   ((uint32_t)0x10002600)
#define RCC_ADC34PLLCLK_Div8                   ((uint32_t)0x10002800)
#define RCC_ADC34PLLCLK_Div10                  ((uint32_t)0x10002A00)
#define RCC_ADC34PLLCLK_Div12                  ((uint32_t)0x10002C00)
#define RCC_ADC34PLLCLK_Div16                  ((uint32_t)0x10002E00)
#define RCC_ADC34PLLCLK_Div32                  ((uint32_t)0x10003000)
#define RCC_ADC34PLLCLK_Div64                  ((uint32_t)0x10003200)
#define RCC_ADC34PLLCLK_Div128                 ((uint32_t)0x10003400)
#define RCC_ADC34PLLCLK_Div256                 ((uint32_t)0x10003600)

#define IS_RCC_ADCCLK(ADCCLK) (((ADCCLK) == RCC_ADC12PLLCLK_OFF) || ((ADCCLK) == RCC_ADC12PLLCLK_Div1) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div2) || ((ADCCLK) == RCC_ADC12PLLCLK_Div4) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div6) || ((ADCCLK) == RCC_ADC12PLLCLK_Div8) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div10) || ((ADCCLK) == RCC_ADC12PLLCLK_Div12) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div16) || ((ADCCLK) == RCC_ADC12PLLCLK_Div32) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div64) || ((ADCCLK) == RCC_ADC12PLLCLK_Div128) || \
                               ((ADCCLK) == RCC_ADC12PLLCLK_Div256) || ((ADCCLK) == RCC_ADC34PLLCLK_OFF) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div1) || ((ADCCLK) == RCC_ADC34PLLCLK_Div2) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div4) || ((ADCCLK) == RCC_ADC34PLLCLK_Div6) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div8) || ((ADCCLK) == RCC_ADC34PLLCLK_Div10) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div12) || ((ADCCLK) == RCC_ADC34PLLCLK_Div16) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div32) || ((ADCCLK) == RCC_ADC34PLLCLK_Div64) || \
                               ((ADCCLK) == RCC_ADC34PLLCLK_Div128) || ((ADCCLK) == RCC_ADC34PLLCLK_Div256))

/**
  * @}
  */

/** @defgroup RCC_TIM_clock_source 
  * @{
  */

#define RCC_TIM1CLK_PCLK                  ((uint32_t)0x00000000)
#define RCC_TIM1CLK_PLLCLK                RCC_CFGR3_TIM1SW

#define RCC_TIM8CLK_PCLK                  ((uint32_t)0x10000000)
#define RCC_TIM8CLK_PLLCLK                ((uint32_t)0x10000200)

#define RCC_TIM15CLK_PCLK                 ((uint32_t)0x20000000)
#define RCC_TIM15CLK_PLLCLK               ((uint32_t)0x20000400)

#define RCC_TIM16CLK_PCLK                 ((uint32_t)0x30000000)
#define RCC_TIM16CLK_PLLCLK               ((uint32_t)0x30000800)

#define RCC_TIM17CLK_PCLK                 ((uint32_t)0x40000000)
#define RCC_TIM17CLK_PLLCLK               ((uint32_t)0x40002000)

#define RCC_TIM20CLK_PCLK                 ((uint32_t)0x50000000)
#define RCC_TIM20CLK_PLLCLK               ((uint32_t)0x50008000)

#define RCC_TIM2CLK_PCLK                  ((uint32_t)0x60000000)
#define RCC_TIM2CLK_PLLCLK                ((uint32_t)0x61000000)

#define RCC_TIM3TIM4CLK_PCLK              ((uint32_t)0x70000000)
#define RCC_TIM3TIM4CLK_PLLCLK            ((uint32_t)0x72000000)

#define IS_RCC_TIMCLK(TIMCLK) (((TIMCLK) == RCC_TIM1CLK_PCLK) || ((TIMCLK) == RCC_TIM1CLK_PLLCLK) || \
                               ((TIMCLK) == RCC_TIM8CLK_PCLK) || ((TIMCLK) == RCC_TIM8CLK_PLLCLK) || \
                               ((TIMCLK) == RCC_TIM15CLK_PCLK) || ((TIMCLK) == RCC_TIM15CLK_PLLCLK) || \
                               ((TIMCLK) == RCC_TIM16CLK_PCLK) || ((TIMCLK) == RCC_TIM16CLK_PLLCLK) || \
                               ((TIMCLK) == RCC_TIM17CLK_PCLK) || ((TIMCLK) == RCC_TIM17CLK_PLLCLK)|| \
                               ((TIMCLK) == RCC_TIM20CLK_PCLK) || ((TIMCLK) == RCC_TIM20CLK_PLLCLK)|| \
                               ((TIMCLK) == RCC_TIM2CLK_PCLK) || ((TIMCLK) == RCC_TIM2CLK_PLLCLK)|| \
                               ((TIMCLK) == RCC_TIM3TIM4CLK_PCLK) || ((TIMCLK) == RCC_TIM3TIM4CLK_PLLCLK))
/* legacy RCC_TIM_clock_source*/                
#define RCC_TIM1CLK_HCLK   RCC_TIM1CLK_PCLK                
#define RCC_TIM8CLK_HCLK   RCC_TIM8CLK_PCLK
#define RCC_TIM15CLK_HCLK  RCC_TIM15CLK_PCLK                 
#define RCC_TIM16CLK_HCLK  RCC_TIM16CLK_PCLK
#define RCC_TIM17CLK_HCLK  RCC_TIM17CLK_PCLK
#define RCC_TIM20CLK_HCLK  RCC_TIM20CLK_PCLK
#define RCC_TIM2CLK_HCLK   RCC_TIM2CLK_PCLK
#define RCC_TIM3CLK_HCLK   RCC_TIM3TIM4CLK_PCLK
#define RCC_TIM3CLK_PLLCLK RCC_TIM3TIM4CLK_PLLCLK
/**
  * @}
  */

/** @defgroup RCC_HRTIM_clock_source 
  * @{
  */

#define RCC_HRTIM1CLK_HCLK                  ((uint32_t)0x00000000)
#define RCC_HRTIM1CLK_PLLCLK                RCC_CFGR3_HRTIM1SW

#define IS_RCC_HRTIMCLK(HRTIMCLK) (((HRTIMCLK) == RCC_HRTIM1CLK_HCLK) || ((HRTIMCLK) == RCC_HRTIM1CLK_PLLCLK))

/**
  * @}
  */
  
/** @defgroup RCC_I2C_clock_source 
  * @{
  */

#define RCC_I2C1CLK_HSI                   ((uint32_t)0x00000000)
#define RCC_I2C1CLK_SYSCLK                RCC_CFGR3_I2C1SW

#define RCC_I2C2CLK_HSI                   ((uint32_t)0x10000000)
#define RCC_I2C2CLK_SYSCLK                ((uint32_t)0x10000020)

#define RCC_I2C3CLK_HSI                   ((uint32_t)0x20000000)
#define RCC_I2C3CLK_SYSCLK                ((uint32_t)0x20000040)

#define IS_RCC_I2CCLK(I2CCLK) (((I2CCLK) == RCC_I2C1CLK_HSI) || ((I2CCLK) == RCC_I2C1CLK_SYSCLK) || \
                               ((I2CCLK) == RCC_I2C2CLK_HSI) || ((I2CCLK) == RCC_I2C2CLK_SYSCLK) || \
                               ((I2CCLK) == RCC_I2C3CLK_HSI) || ((I2CCLK) == RCC_I2C3CLK_SYSCLK))

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

#define RCC_USART2CLK_PCLK                  ((uint32_t)0x20000000)
#define RCC_USART2CLK_SYSCLK                ((uint32_t)0x20010000)
#define RCC_USART2CLK_LSE                   ((uint32_t)0x20020000)
#define RCC_USART2CLK_HSI                   ((uint32_t)0x20030000)

#define RCC_USART3CLK_PCLK                  ((uint32_t)0x30000000)
#define RCC_USART3CLK_SYSCLK                ((uint32_t)0x30040000)
#define RCC_USART3CLK_LSE                   ((uint32_t)0x30080000)
#define RCC_USART3CLK_HSI                   ((uint32_t)0x300C0000)

#define RCC_UART4CLK_PCLK                   ((uint32_t)0x40000000)
#define RCC_UART4CLK_SYSCLK                 ((uint32_t)0x40100000)
#define RCC_UART4CLK_LSE                    ((uint32_t)0x40200000)
#define RCC_UART4CLK_HSI                    ((uint32_t)0x40300000)

#define RCC_UART5CLK_PCLK                   ((uint32_t)0x50000000)
#define RCC_UART5CLK_SYSCLK                 ((uint32_t)0x50400000)
#define RCC_UART5CLK_LSE                    ((uint32_t)0x50800000)
#define RCC_UART5CLK_HSI                    ((uint32_t)0x50C00000)

#define IS_RCC_USARTCLK(USARTCLK) (((USARTCLK) == RCC_USART1CLK_PCLK) || ((USARTCLK) == RCC_USART1CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART1CLK_LSE) || ((USARTCLK) == RCC_USART1CLK_HSI) ||\
                                   ((USARTCLK) == RCC_USART2CLK_PCLK) || ((USARTCLK) == RCC_USART2CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART2CLK_LSE) || ((USARTCLK) == RCC_USART2CLK_HSI) || \
                                   ((USARTCLK) == RCC_USART3CLK_PCLK) || ((USARTCLK) == RCC_USART3CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_USART3CLK_LSE) || ((USARTCLK) == RCC_USART3CLK_HSI) || \
                                   ((USARTCLK) == RCC_UART4CLK_PCLK) || ((USARTCLK) == RCC_UART4CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_UART4CLK_LSE) || ((USARTCLK) == RCC_UART4CLK_HSI) || \
                                   ((USARTCLK) == RCC_UART5CLK_PCLK) || ((USARTCLK) == RCC_UART5CLK_SYSCLK) || \
                                   ((USARTCLK) == RCC_UART5CLK_LSE) || ((USARTCLK) == RCC_UART5CLK_HSI))

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
#define RCC_IT_CSS                       ((uint8_t)0x80)

#define IS_RCC_IT(IT) ((((IT) & (uint8_t)0xC0) == 0x00) && ((IT) != 0x00))

#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS))
                           

#define IS_RCC_CLEAR_IT(IT) ((((IT) & (uint8_t)0x40) == 0x00) && ((IT) != 0x00))

/**
  * @}
  */
  
/** @defgroup RCC_LSE_configuration 
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

/** @defgroup RCC_I2S_Clock_Source
  * @{
  */
#define RCC_I2S2CLKSource_SYSCLK             ((uint8_t)0x00)
#define RCC_I2S2CLKSource_Ext                ((uint8_t)0x01)

#define IS_RCC_I2SCLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2S2CLKSource_SYSCLK) || ((SOURCE) == RCC_I2S2CLKSource_Ext)) 

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

#define RCC_AHBPeriph_ADC34               RCC_AHBENR_ADC34EN
#define RCC_AHBPeriph_ADC12               RCC_AHBENR_ADC12EN
#define RCC_AHBPeriph_GPIOA               RCC_AHBENR_GPIOAEN
#define RCC_AHBPeriph_GPIOB               RCC_AHBENR_GPIOBEN
#define RCC_AHBPeriph_GPIOC               RCC_AHBENR_GPIOCEN
#define RCC_AHBPeriph_GPIOD               RCC_AHBENR_GPIODEN
#define RCC_AHBPeriph_GPIOE               RCC_AHBENR_GPIOEEN
#define RCC_AHBPeriph_GPIOF               RCC_AHBENR_GPIOFEN
#define RCC_AHBPeriph_GPIOG               RCC_AHBENR_GPIOGEN
#define RCC_AHBPeriph_GPIOH               RCC_AHBENR_GPIOHEN
#define RCC_AHBPeriph_TS                  RCC_AHBENR_TSEN
#define RCC_AHBPeriph_CRC                 RCC_AHBENR_CRCEN
#define RCC_AHBPeriph_FMC                 RCC_AHBENR_FMCEN
#define RCC_AHBPeriph_FLITF               RCC_AHBENR_FLITFEN
#define RCC_AHBPeriph_SRAM                RCC_AHBENR_SRAMEN
#define RCC_AHBPeriph_DMA2                RCC_AHBENR_DMA2EN
#define RCC_AHBPeriph_DMA1                RCC_AHBENR_DMA1EN

#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xCE00FF88) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB_RST_PERIPH(PERIPH) ((((PERIPH) & 0xCE00FFDF) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripherals 
  * @{
  */

#define RCC_APB2Periph_SYSCFG            RCC_APB2ENR_SYSCFGEN
#define RCC_APB2Periph_TIM1              RCC_APB2ENR_TIM1EN
#define RCC_APB2Periph_SPI1              RCC_APB2ENR_SPI1EN
#define RCC_APB2Periph_TIM8              RCC_APB2ENR_TIM8EN
#define RCC_APB2Periph_USART1            RCC_APB2ENR_USART1EN
#define RCC_APB2Periph_SPI4              RCC_APB2ENR_SPI4EN
#define RCC_APB2Periph_TIM15             RCC_APB2ENR_TIM15EN
#define RCC_APB2Periph_TIM16             RCC_APB2ENR_TIM16EN
#define RCC_APB2Periph_TIM17             RCC_APB2ENR_TIM17EN
#define RCC_APB2Periph_TIM20             RCC_APB2ENR_TIM20EN
#define RCC_APB2Periph_HRTIM1            RCC_APB2ENR_HRTIM1

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xDFE807FE) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */ 

/** @defgroup RCC_APB1_Peripherals 
  * @{
  */
#define RCC_APB1Periph_TIM2              RCC_APB1ENR_TIM2EN
#define RCC_APB1Periph_TIM3              RCC_APB1ENR_TIM3EN
#define RCC_APB1Periph_TIM4              RCC_APB1ENR_TIM4EN
#define RCC_APB1Periph_TIM6              RCC_APB1ENR_TIM6EN
#define RCC_APB1Periph_TIM7              RCC_APB1ENR_TIM7EN
#define RCC_APB1Periph_WWDG              RCC_APB1ENR_WWDGEN
#define RCC_APB1Periph_SPI2              RCC_APB1ENR_SPI2EN
#define RCC_APB1Periph_SPI3              RCC_APB1ENR_SPI3EN
#define RCC_APB1Periph_USART2            RCC_APB1ENR_USART2EN
#define RCC_APB1Periph_USART3            RCC_APB1ENR_USART3EN
#define RCC_APB1Periph_UART4             RCC_APB1ENR_UART4EN
#define RCC_APB1Periph_UART5             RCC_APB1ENR_UART5EN
#define RCC_APB1Periph_I2C1              RCC_APB1ENR_I2C1EN
#define RCC_APB1Periph_I2C2              RCC_APB1ENR_I2C2EN
#define RCC_APB1Periph_USB               RCC_APB1ENR_USBEN
#define RCC_APB1Periph_CAN1              RCC_APB1ENR_CAN1EN
#define RCC_APB1Periph_PWR               RCC_APB1ENR_PWREN
#define RCC_APB1Periph_DAC1              RCC_APB1ENR_DAC1EN
#define RCC_APB1Periph_I2C3              RCC_APB1ENR_I2C3EN
#define RCC_APB1Periph_DAC2              RCC_APB1ENR_DAC2EN
#define RCC_APB1Periph_DAC               RCC_APB1Periph_DAC1


#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0x890137C8) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */

/** @defgroup RCC_MCO_Clock_Source
  * @{
  */

#define RCC_MCOSource_NoClock            ((uint8_t)0x00)
#define RCC_MCOSource_LSI                ((uint8_t)0x02)
#define RCC_MCOSource_LSE                ((uint8_t)0x03)
#define RCC_MCOSource_SYSCLK             ((uint8_t)0x04)
#define RCC_MCOSource_HSI                ((uint8_t)0x05)
#define RCC_MCOSource_HSE                ((uint8_t)0x06)
#define RCC_MCOSource_PLLCLK_Div2        ((uint8_t)0x07)
#define RCC_MCOSource_PLLCLK             ((uint8_t)0x87)

#define IS_RCC_MCO_SOURCE(SOURCE) (((SOURCE) == RCC_MCOSource_NoClock) ||((SOURCE) == RCC_MCOSource_SYSCLK) ||\
                                   ((SOURCE) == RCC_MCOSource_HSI)  || ((SOURCE) == RCC_MCOSource_HSE) || \
                                   ((SOURCE) == RCC_MCOSource_LSI)  || ((SOURCE) == RCC_MCOSource_LSE) || \
                                   ((SOURCE) == RCC_MCOSource_PLLCLK_Div2)|| ((SOURCE) == RCC_MCOSource_PLLCLK))
/**
  * @}
  */ 

/** @defgroup RCC_MCOPrescaler
  * @{
  */

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
/**
  * @}
  */ 

/** @defgroup RCC_USB_Device_clock_source 
  * @{
  */

#define RCC_USBCLKSource_PLLCLK_1Div5   ((uint8_t)0x00)
#define RCC_USBCLKSource_PLLCLK_Div1    ((uint8_t)0x01)

#define IS_RCC_USBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_USBCLKSource_PLLCLK_1Div5) || \
                                      ((SOURCE) == RCC_USBCLKSource_PLLCLK_Div1))
/**
  * @}
  */

/** @defgroup RCC_Flag 
  * @{
  */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x01)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x11)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x19)
#define RCC_FLAG_MCOF                    ((uint8_t)0x9C)
#define RCC_FLAG_LSERDY                  ((uint8_t)0x21)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x41)
#define RCC_FLAG_OBLRST                  ((uint8_t)0x59)
#define RCC_FLAG_PINRST                  ((uint8_t)0x5A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x5B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x5C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x5D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x5E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x5F)

#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
                           ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
                           ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_OBLRST) || \
                           ((FLAG) == RCC_FLAG_PINRST) || ((FLAG) == RCC_FLAG_PORRST) || \
                           ((FLAG) == RCC_FLAG_SFTRST) || ((FLAG) == RCC_FLAG_IWDGRST)|| \
                           ((FLAG) == RCC_FLAG_WWDGRST)|| ((FLAG) == RCC_FLAG_LPWRRST)|| \
                           ((FLAG) == RCC_FLAG_MCOF))

#define IS_RCC_HSI_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)

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
void RCC_LSEConfig(uint32_t RCC_LSE);
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive);
void RCC_LSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Div);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
#ifdef STM32F303xC
 void RCC_MCOConfig(uint8_t RCC_MCOSource);
#else
 void RCC_MCOConfig(uint8_t RCC_MCOSource,uint32_t RCC_MCOPrescaler);
#endif /* STM32F303xC */

/* System, AHB and APB busses clocks configuration functions ******************/
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

/* Peripheral clocks configuration functions **********************************/
void RCC_ADCCLKConfig(uint32_t RCC_PLLCLK);
void RCC_I2CCLKConfig(uint32_t RCC_I2CCLK);
void RCC_TIMCLKConfig(uint32_t RCC_TIMCLK);
void RCC_HRTIM1CLKConfig(uint32_t RCC_HRTIMCLK);
void RCC_I2SCLKConfig(uint32_t RCC_I2SCLKSource); 
void RCC_USARTCLKConfig(uint32_t RCC_USARTCLK);
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);

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

#endif /* __STM32F30x_RCC_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_rtc.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the RTC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_RTC_H
#define __STM32F30x_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
  
  uint8_t RTC_Month;   /*!< Specifies the RTC Date Month (in BCD format).
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
                                     If the Alarm Date is selected, this parameter
                                     must be set to a value in the 1-31 range.
                                     If the Alarm WeekDay is selected, this 
                                     parameter can be a value of @ref RTC_WeekDay_Definitions */
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

/* Coded in BCD format */
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
  
#define RTC_Weekday_Monday             ((uint8_t)0x01)
#define RTC_Weekday_Tuesday            ((uint8_t)0x02)
#define RTC_Weekday_Wednesday          ((uint8_t)0x03)
#define RTC_Weekday_Thursday           ((uint8_t)0x04)
#define RTC_Weekday_Friday             ((uint8_t)0x05)
#define RTC_Weekday_Saturday           ((uint8_t)0x06)
#define RTC_Weekday_Sunday             ((uint8_t)0x07)
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
#define IS_ALARM_MASK(MASK)  (((MASK) & 0x7F7F7F7F) == (uint32_t)RESET)

/**
  * @}
  */ 

/** @defgroup RTC_Alarms_Definitions 
  * @{
  */ 
#define RTC_Alarm_A                       ((uint32_t)0x00000100)
#define RTC_Alarm_B                       ((uint32_t)0x00000200)
#define IS_RTC_ALARM(ALARM)     (((ALARM) == RTC_Alarm_A) || ((ALARM) == RTC_Alarm_B))
#define IS_RTC_CMD_ALARM(ALARM) (((ALARM) & (RTC_Alarm_A | RTC_Alarm_B)) != (uint32_t)RESET)

/**
  * @}
  */ 

/** @defgroup RTC_Alarm_Sub_Seconds_Masks_Definitions
  * @{
  */ 
#define RTC_AlarmSubSecondMask_All         ((uint32_t)0x00000000) /*!< All Alarm SS fields are masked. 
                                                                       There is no comparison on sub seconds 
                                                                       for Alarm */
#define RTC_AlarmSubSecondMask_SS14_1      ((uint32_t)0x01000000) /*!< SS[14:1] are don't care in Alarm 
                                                                       comparison. Only SS[0] is compared. */
#define RTC_AlarmSubSecondMask_SS14_2      ((uint32_t)0x02000000) /*!< SS[14:2] are don't care in Alarm 
                                                                       comparison. Only SS[1:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_3      ((uint32_t)0x03000000) /*!< SS[14:3] are don't care in Alarm 
                                                                       comparison. Only SS[2:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_4      ((uint32_t)0x04000000) /*!< SS[14:4] are don't care in Alarm 
                                                                       comparison. Only SS[3:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_5      ((uint32_t)0x05000000) /*!< SS[14:5] are don't care in Alarm 
                                                                       comparison. Only SS[4:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_6      ((uint32_t)0x06000000) /*!< SS[14:6] are don't care in Alarm 
                                                                       comparison. Only SS[5:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_7      ((uint32_t)0x07000000) /*!< SS[14:7] are don't care in Alarm 
                                                                       comparison. Only SS[6:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_8      ((uint32_t)0x08000000) /*!< SS[14:8] are don't care in Alarm 
                                                                       comparison. Only SS[7:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_9      ((uint32_t)0x09000000) /*!< SS[14:9] are don't care in Alarm 
                                                                       comparison. Only SS[8:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_10     ((uint32_t)0x0A000000) /*!< SS[14:10] are don't care in Alarm 
                                                                       comparison. Only SS[9:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_11     ((uint32_t)0x0B000000) /*!< SS[14:11] are don't care in Alarm 
                                                                       comparison. Only SS[10:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_12     ((uint32_t)0x0C000000) /*!< SS[14:12] are don't care in Alarm 
                                                                       comparison.Only SS[11:0] are compared */
#define RTC_AlarmSubSecondMask_SS14_13     ((uint32_t)0x0D000000) /*!< SS[14:13] are don't care in Alarm 
                                                                       comparison. Only SS[12:0] are compared */
#define RTC_AlarmSubSecondMask_SS14        ((uint32_t)0x0E000000) /*!< SS[14] is don't care in Alarm 
                                                                       comparison.Only SS[13:0] are compared */
#define RTC_AlarmSubSecondMask_None        ((uint32_t)0x0F000000) /*!< SS[14:0] are compared and must match 
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
#define RTC_Output_AlarmB              ((uint32_t)0x00400000)
#define RTC_Output_WakeUp              ((uint32_t)0x00600000)
 
#define IS_RTC_OUTPUT(OUTPUT) (((OUTPUT) == RTC_Output_Disable) || \
                               ((OUTPUT) == RTC_Output_AlarmA) || \
                               ((OUTPUT) == RTC_Output_AlarmB) || \
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

/** @defgroup RTC_Digital_Calibration_Definitions 
  * @{
  */ 
#define RTC_CalibSign_Positive            ((uint32_t)0x00000000) 
#define RTC_CalibSign_Negative            ((uint32_t)0x00000080)
#define IS_RTC_CALIB_SIGN(SIGN) (((SIGN) == RTC_CalibSign_Positive) || \
                                 ((SIGN) == RTC_CalibSign_Negative))
#define IS_RTC_CALIB_VALUE(VALUE) ((VALUE) < 0x20)

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
#define IS_RTC_DAYLIGHT_SAVING(SAVE) (((SAVE) == RTC_DayLightSaving_SUB1H) || \
                                      ((SAVE) == RTC_DayLightSaving_ADD1H))

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
#define RTC_TamperSamplingFreq_RTCCLK_Div32768  ((uint32_t)0x00000000) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 32768 */
#define RTC_TamperSamplingFreq_RTCCLK_Div16384  ((uint32_t)0x000000100) /*!< Each of the tamper inputs are sampled
                                                                            with a frequency =  RTCCLK / 16384 */
#define RTC_TamperSamplingFreq_RTCCLK_Div8192   ((uint32_t)0x00000200) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 8192  */
#define RTC_TamperSamplingFreq_RTCCLK_Div4096   ((uint32_t)0x00000300) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 4096  */
#define RTC_TamperSamplingFreq_RTCCLK_Div2048   ((uint32_t)0x00000400) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 2048  */
#define RTC_TamperSamplingFreq_RTCCLK_Div1024   ((uint32_t)0x00000500) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 1024  */
#define RTC_TamperSamplingFreq_RTCCLK_Div512    ((uint32_t)0x00000600) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 512   */
#define RTC_TamperSamplingFreq_RTCCLK_Div256    ((uint32_t)0x00000700) /*!< Each of the tamper inputs are sampled
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
                                                      input tamper 3 */

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
#define RTC_BKP_DR5                       ((uint32_t)0x00000005)
#define RTC_BKP_DR6                       ((uint32_t)0x00000006)
#define RTC_BKP_DR7                       ((uint32_t)0x00000007)
#define RTC_BKP_DR8                       ((uint32_t)0x00000008)
#define RTC_BKP_DR9                       ((uint32_t)0x00000009)
#define RTC_BKP_DR10                      ((uint32_t)0x0000000A)
#define RTC_BKP_DR11                      ((uint32_t)0x0000000B)
#define RTC_BKP_DR12                      ((uint32_t)0x0000000C)
#define RTC_BKP_DR13                      ((uint32_t)0x0000000D)
#define RTC_BKP_DR14                      ((uint32_t)0x0000000E)
#define RTC_BKP_DR15                      ((uint32_t)0x0000000F)
#define IS_RTC_BKP(BKP)                   (((BKP) == RTC_BKP_DR0) || \
                                           ((BKP) == RTC_BKP_DR1) || \
                                           ((BKP) == RTC_BKP_DR2) || \
                                           ((BKP) == RTC_BKP_DR3) || \
                                           ((BKP) == RTC_BKP_DR4) || \
                                           ((BKP) == RTC_BKP_DR5) || \
                                           ((BKP) == RTC_BKP_DR6) || \
                                           ((BKP) == RTC_BKP_DR7) || \
                                           ((BKP) == RTC_BKP_DR8) || \
                                           ((BKP) == RTC_BKP_DR9) || \
                                           ((BKP) == RTC_BKP_DR10) || \
                                           ((BKP) == RTC_BKP_DR11) || \
                                           ((BKP) == RTC_BKP_DR12) || \
                                           ((BKP) == RTC_BKP_DR13) || \
                                           ((BKP) == RTC_BKP_DR14) || \
                                           ((BKP) == RTC_BKP_DR15))
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
#define RTC_FLAG_RECALPF                  ((uint32_t)0x00010000)
#define RTC_FLAG_TAMP3F                   ((uint32_t)0x00008000)
#define RTC_FLAG_TAMP2F                   ((uint32_t)0x00004000)
#define RTC_FLAG_TAMP1F                   ((uint32_t)0x00002000)
#define RTC_FLAG_TSOVF                    ((uint32_t)0x00001000)
#define RTC_FLAG_TSF                      ((uint32_t)0x00000800)
#define RTC_FLAG_WUTF                     ((uint32_t)0x00000400)
#define RTC_FLAG_ALRBF                    ((uint32_t)0x00000200)
#define RTC_FLAG_ALRAF                    ((uint32_t)0x00000100)
#define RTC_FLAG_INITF                    ((uint32_t)0x00000040)
#define RTC_FLAG_RSF                      ((uint32_t)0x00000020)
#define RTC_FLAG_INITS                    ((uint32_t)0x00000010)
#define RTC_FLAG_SHPF                     ((uint32_t)0x00000008)
#define RTC_FLAG_WUTWF                    ((uint32_t)0x00000004)
#define RTC_FLAG_ALRBWF                   ((uint32_t)0x00000002)
#define RTC_FLAG_ALRAWF                   ((uint32_t)0x00000001)
#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_TSOVF) || ((FLAG) == RTC_FLAG_TSF) || \
                               ((FLAG) == RTC_FLAG_WUTF) || ((FLAG) == RTC_FLAG_ALRBF) || \
                               ((FLAG) == RTC_FLAG_ALRAF) || ((FLAG) == RTC_FLAG_INITF) || \
                               ((FLAG) == RTC_FLAG_RSF) || ((FLAG) == RTC_FLAG_WUTWF) || \
                               ((FLAG) == RTC_FLAG_ALRBWF) || ((FLAG) == RTC_FLAG_ALRAWF) || \
                               ((FLAG) == RTC_FLAG_TAMP1F) || ((FLAG) == RTC_FLAG_TAMP2F) || \
                                ((FLAG) == RTC_FLAG_TAMP3F) || ((FLAG) == RTC_FLAG_RECALPF) || \
                                ((FLAG) == RTC_FLAG_SHPF))
#define IS_RTC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFF00DF) == (uint32_t)RESET))

/**
  * @}
  */ 

/** @defgroup RTC_Interrupts_Definitions 
  * @{
  */ 
#define RTC_IT_TS                         ((uint32_t)0x00008000)
#define RTC_IT_WUT                        ((uint32_t)0x00004000)
#define RTC_IT_ALRB                       ((uint32_t)0x00002000)
#define RTC_IT_ALRA                       ((uint32_t)0x00001000)
#define RTC_IT_TAMP                       ((uint32_t)0x00000004) /* Used only to Enable the Tamper Interrupt */
#define RTC_IT_TAMP1                      ((uint32_t)0x00020000)
#define RTC_IT_TAMP2                      ((uint32_t)0x00040000)
#define RTC_IT_TAMP3                      ((uint32_t)0x00080000)


#define IS_RTC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFF0FFB) == (uint32_t)RESET))
#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_TS)    || ((IT) == RTC_IT_WUT) || \
                           ((IT) == RTC_IT_ALRB)  || ((IT) == RTC_IT_ALRA) || \
                           ((IT) == RTC_IT_TAMP1) || ((IT) == RTC_IT_TAMP2) || \
                           ((IT) == RTC_IT_TAMP3))
#define IS_RTC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFF10FFF) == (uint32_t)RESET))

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

/* Alarms (Alarm A and Alarm B) configuration functions  **********************/ 
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct);
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState);
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask);
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm);

/* WakeUp Timer configuration functions ***************************************/ 
void RTC_WakeUpClockConfig(uint32_t RTC_WakeUpClock);
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter);
uint32_t RTC_GetWakeUpCounter(void);
ErrorStatus RTC_WakeUpCmd(FunctionalState NewState);

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
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct, 
                                      RTC_DateTypeDef* RTC_StampDateStruct);
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

#endif /*__STM32F30x_RTC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_spi.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the SPI 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_SPI_H
#define __STM32F30x_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint16_t SPI_CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */
}SPI_InitTypeDef;


/** 
  * @brief  I2S Init structure definition  
  */

typedef struct
{
  uint16_t I2S_Mode;         /*!< Specifies the I2S operating mode.
                                  This parameter can be a value of @ref I2S_Mode */

  uint16_t I2S_Standard;     /*!< Specifies the standard used for the I2S communication.
                                  This parameter can be a value of @ref I2S_Standard */

  uint16_t I2S_DataFormat;   /*!< Specifies the data format for the I2S communication.
                                  This parameter can be a value of @ref I2S_Data_Format */

  uint16_t I2S_MCLKOutput;   /*!< Specifies whether the I2S MCLK output is enabled or not.
                                  This parameter can be a value of @ref I2S_MCLK_Output */

  uint32_t I2S_AudioFreq;    /*!< Specifies the frequency selected for the I2S communication.
                                  This parameter can be a value of @ref I2S_Audio_Frequency */

  uint16_t I2S_CPOL;         /*!< Specifies the idle state of the I2S clock.
                                  This parameter can be a value of @ref I2S_Clock_Polarity */
}I2S_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3) || \
                                   ((PERIPH) == SPI4))

#define IS_SPI_ALL_PERIPH_EXT(PERIPH) (((PERIPH) == SPI1) || \
                                       ((PERIPH) == SPI2) || \
                                       ((PERIPH) == SPI3) || \
                                       ((PERIPH) == SPI4) || \
                                       ((PERIPH) == I2S2ext) || \
                                       ((PERIPH) == I2S3ext))

#define IS_SPI_23_PERIPH(PERIPH)  (((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3))

#define IS_SPI_23_PERIPH_EXT(PERIPH)  (((PERIPH) == SPI2) || \
                                       ((PERIPH) == SPI3) || \
                                       ((PERIPH) == I2S2ext) || \
                                       ((PERIPH) == I2S3ext))

#define IS_I2S_EXT_PERIPH(PERIPH)  (((PERIPH) == I2S2ext) || \
                                    ((PERIPH) == I2S3ext))

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
#define SPI_CRCLength_16b               ((uint16_t)0x0800)
#define IS_SPI_CRC_LENGTH(LENGTH) (((LENGTH) == SPI_CRCLength_8b) || \
                                   ((LENGTH) == SPI_CRCLength_16b))
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity 
  * @{
  */

#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   ((uint16_t)0x0002)
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase 
  * @{
  */

#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  ((uint16_t)0x0001)
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management 
  * @{
  */

#define SPI_NSS_Soft                    ((uint16_t)0x0200)
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
#define SPI_FirstBit_LSB                ((uint16_t)0x0080)
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))
/**
  * @}
  */
  
/** @defgroup I2S_Mode 
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

/** @defgroup I2S_Standard 
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

/** @defgroup I2S_Data_Format 
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

/** @defgroup I2S_MCLK_Output 
  * @{
  */

#define I2S_MCLKOutput_Enable           ((uint16_t)0x0200)
#define I2S_MCLKOutput_Disable          ((uint16_t)0x0000)
#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOutput_Enable) || \
                                    ((OUTPUT) == I2S_MCLKOutput_Disable))
/**
  * @}
  */

/** @defgroup I2S_Audio_Frequency 
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

/** @defgroup I2S_Clock_Polarity 
  * @{
  */

#define I2S_CPOL_Low                    ((uint16_t)0x0000)
#define I2S_CPOL_High                   ((uint16_t)0x0008)
#define IS_I2S_CPOL(CPOL) (((CPOL) == I2S_CPOL_Low) || \
                           ((CPOL) == I2S_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_FIFO_reception_threshold 
  * @{
  */

#define SPI_RxFIFOThreshold_HF          ((uint16_t)0x0000)
#define SPI_RxFIFOThreshold_QF          ((uint16_t)0x1000)
#define IS_SPI_RX_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == SPI_RxFIFOThreshold_HF) || \
                                             ((THRESHOLD) == SPI_RxFIFOThreshold_QF))
/**
  * @}
  */

/** @defgroup SPI_I2S_DMA_transfer_requests 
  * @{
  */

#define SPI_I2S_DMAReq_Tx               ((uint16_t)0x0002)
#define SPI_I2S_DMAReq_Rx               ((uint16_t)0x0001)
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

#define SPI_NSSInternalSoft_Set         ((uint16_t)0x0100)
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

#define SPI_I2S_FLAG_RXNE               ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TXE                ((uint16_t)0x0002)
#define I2S_FLAG_CHSIDE                 ((uint16_t)0x0004)
#define I2S_FLAG_UDR                    ((uint16_t)0x0008)
#define SPI_FLAG_CRCERR                 ((uint16_t)0x0010)
#define SPI_FLAG_MODF                   ((uint16_t)0x0020)
#define SPI_I2S_FLAG_OVR                ((uint16_t)0x0040)
#define SPI_I2S_FLAG_BSY                ((uint16_t)0x0080)
#define SPI_I2S_FLAG_FRE                ((uint16_t)0x0100)



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

/* Function used to set the SPI configuration to the default reset state*******/
void SPI_I2S_DeInit(SPI_TypeDef* SPIx);

/* Initialization and Configuration functions *********************************/
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_NSSPulseModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_RxFIFOThresholdConfig(SPI_TypeDef* SPIx, uint16_t SPI_RxFIFOThreshold);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_FullDuplexConfig(SPI_TypeDef* I2Sxext, I2S_InitTypeDef* I2S_InitStruct);

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

#endif /*__STM32F30x_SPI_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_syscfg.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the SYSCFG firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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

/*!< Define to prevent recursive inclusion -----------------------------------*/
#ifndef __STM32F30x_SYSCFG_H
#define __STM32F30x_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/*!< Includes ----------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
#define EXTI_PortSourceGPIOD       ((uint8_t)0x03)
#define EXTI_PortSourceGPIOE       ((uint8_t)0x04)
#define EXTI_PortSourceGPIOF       ((uint8_t)0x05)
#define EXTI_PortSourceGPIOG       ((uint8_t)0x06)
#define EXTI_PortSourceGPIOH       ((uint8_t)0x07)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOF)|| \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOG)|| \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOH)) 
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
#define SYSCFG_MemoryRemap_FMC                  ((uint8_t)0x04)


#define IS_SYSCFG_MEMORY_REMAP(REMAP) (((REMAP) == SYSCFG_MemoryRemap_Flash)        || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SystemMemory) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SRAM) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_FMC))

/**
  * @}
  */

/** @defgroup SYSCFG_DMA_Remap_Config 
  * @{
  */ 
#define SYSCFG_DMARemap_TIM17              SYSCFG_CFGR1_TIM17_DMA_RMP        /*!< Remap TIM17 DMA requests from channel1 to channel2 */
#define SYSCFG_DMARemap_TIM16              SYSCFG_CFGR1_TIM16_DMA_RMP        /*!< Remap TIM16 DMA requests from channel3 to channel4 */
#define SYSCFG_DMARemap_ADC2ADC4           SYSCFG_CFGR1_ADC24_DMA_RMP        /*!< Remap ADC2 and ADC4 DMA requests */

#define SYSCFG_DMARemap_TIM6DAC1Ch1        SYSCFG_CFGR1_TIM6DAC1Ch1_DMA_RMP  /* Remap TIM6/DAC1 Ch1 DMA requests */
#define SYSCFG_DMARemap_TIM7DAC1Ch2        SYSCFG_CFGR1_TIM7DAC1Ch2_DMA_RMP  /* Remap TIM7/DAC1 Ch2 DMA requests */
#define SYSCFG_DMARemap_DAC2Ch1            SYSCFG_CFGR1_DAC2Ch1_DMA_RMP      /* Remap DAC2 Ch1 DMA requests */

#define SYSCFG_DMARemapCh2_SPI1_RX         ((uint32_t)0x80000003)            /* Remap SPI1 RX DMA CH2 requests */
#define SYSCFG_DMARemapCh4_SPI1_RX         ((uint32_t)0x80000001)            /* Remap SPI1 RX DMA CH4 requests */
#define SYSCFG_DMARemapCh6_SPI1_RX         ((uint32_t)0x80000002)            /* Remap SPI1 RX DMA CH6 requests */

#define SYSCFG_DMARemapCh3_SPI1_TX         ((uint32_t)0x8000000C)            /* Remap SPI1 TX DMA CH2 requests */
#define SYSCFG_DMARemapCh5_SPI1_TX         ((uint32_t)0x80000004)            /* Remap SPI1 TX DMA CH5 requests */
#define SYSCFG_DMARemapCh7_SPI1_TX         ((uint32_t)0x80000008)            /* Remap SPI1 TX DMA CH7 requests */

#define SYSCFG_DMARemapCh7_I2C1_RX         ((uint32_t)0x80000030)            /* Remap I2C1 RX DMA CH7 requests */
#define SYSCFG_DMARemapCh3_I2C1_RX         ((uint32_t)0x80000010)            /* Remap I2C1 RX DMA CH3 requests */
#define SYSCFG_DMARemapCh5_I2C1_RX         ((uint32_t)0x80000020)            /* Remap I2C1 RX DMA CH5 requests */

#define SYSCFG_DMARemapCh6_I2C1_TX         ((uint32_t)0x800000C0)            /* Remap I2C1 TX DMA CH6 requests */
#define SYSCFG_DMARemapCh2_I2C1_TX         ((uint32_t)0x80000040)            /* Remap I2C1 TX DMA CH2 requests */
#define SYSCFG_DMARemapCh4_I2C1_TX         ((uint32_t)0x80000080)            /* Remap I2C1 TX DMA CH4 requests */

#define SYSCFG_DMARemapCh4_ADC2            ((uint32_t)0x80000300)            /* Remap ADC2 DMA1 Ch4 requests */
#define SYSCFG_DMARemapCh2_ADC2            ((uint32_t)0x80000200)            /* Remap ADC2 DMA1 Ch2 requests */

/* SYSCFG_DMA_Remap_Legacy */ 
#define SYSCFG_DMARemap_TIM6DAC1           SYSCFG_DMARemap_TIM6DAC1Ch1       /*!< Remap TIM6/DAC1 DMA requests */
#define SYSCFG_DMARemap_TIM7DAC2           SYSCFG_DMARemap_TIM7DAC1Ch2       /*!< Remap TIM7/DAC2 DMA requests */
    
#define IS_SYSCFG_DMA_REMAP(REMAP) (((REMAP) == SYSCFG_DMARemap_TIM17)    || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM16)    || \
                                    ((REMAP) == SYSCFG_DMARemap_ADC2ADC4) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM6DAC1Ch1) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM7DAC1Ch2) || \
                                    ((REMAP) == SYSCFG_DMARemap_DAC2Ch1)    || \
                                    ((REMAP) == SYSCFG_DMARemapCh2_SPI1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh4_SPI1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh6_SPI1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh5_SPI1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh5_SPI1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh7_SPI1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh7_I2C1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh3_I2C1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh5_I2C1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh6_I2C1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh2_I2C1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh4_I2C1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh4_ADC2)    || \
                                    ((REMAP) == SYSCFG_DMARemapCh2_ADC2))

/**
  * @}
  */

/** @defgroup SYSCFG_Trigger_Remap_Config 
  * @{
  */ 
#define SYSCFG_TriggerRemap_DACTIM3              SYSCFG_CFGR1_DAC1_TRIG1_RMP     /*!< Remap DAC trigger to TIM3 */
#define SYSCFG_TriggerRemap_TIM1TIM17            SYSCFG_CFGR1_TIM1_ITR3_RMP      /*!< Remap TIM1 ITR3 to TIM17 OC */
#define SYSCFG_TriggerRemap_DACHRTIM1_TRIG1      ((uint32_t)0x80010000)          /*!< Remap DAC trigger to HRTIM1 TRIG1 */
#define SYSCFG_TriggerRemap_DACHRTIM1_TRIG2      ((uint32_t)0x80020000)          /*!< Remap DAC trigger to HRTIM1 TRIG2 */

#define IS_SYSCFG_TRIGGER_REMAP(REMAP) (((REMAP) == SYSCFG_TriggerRemap_DACTIM3)         || \
                                        ((REMAP) == SYSCFG_TriggerRemap_DACHRTIM1_TRIG1) || \
                                        ((REMAP) == SYSCFG_TriggerRemap_DACHRTIM1_TRIG2) || \
                                        ((REMAP) == SYSCFG_TriggerRemap_TIM1TIM17))

/**
  * @}
  */

/** @defgroup SYSCFG_EncoderRemap_Config 
  * @{
  */ 
#define SYSCFG_EncoderRemap_No              ((uint32_t)0x00000000)      /*!< No redirection */
#define SYSCFG_EncoderRemap_TIM2            SYSCFG_CFGR1_ENCODER_MODE_0 /*!< Timer 2 IC1 and IC2 connected to TIM15 IC1 and IC2 */
#define SYSCFG_EncoderRemap_TIM3            SYSCFG_CFGR1_ENCODER_MODE_1 /*!< Timer 3 IC1 and IC2 connected to TIM15 IC1 and IC2 */
#define SYSCFG_EncoderRemap_TIM4            SYSCFG_CFGR1_ENCODER_MODE   /*!< Timer 4 IC1 and IC2 connected to TIM15 IC1 and IC2 */

#define IS_SYSCFG_ENCODER_REMAP(REMAP) (((REMAP) == SYSCFG_EncoderRemap_No)    || \
                                        ((REMAP) == SYSCFG_EncoderRemap_TIM2)  || \
                                        ((REMAP) == SYSCFG_EncoderRemap_TIM3)  || \
                                        ((REMAP) == SYSCFG_EncoderRemap_TIM4))

/**
  * @}
  */

/** @defgroup SYSCFG_I2C_FastModePlus_Config 
  * @{
  */ 
#define SYSCFG_I2CFastModePlus_PB6       SYSCFG_CFGR1_I2C_PB6_FMP  /*!< Enable Fast Mode Plus on PB6 */
#define SYSCFG_I2CFastModePlus_PB7       SYSCFG_CFGR1_I2C_PB7_FMP  /*!< Enable Fast Mode Plus on PB7 */
#define SYSCFG_I2CFastModePlus_PB8       SYSCFG_CFGR1_I2C_PB8_FMP  /*!< Enable Fast Mode Plus on PB8 */
#define SYSCFG_I2CFastModePlus_PB9       SYSCFG_CFGR1_I2C_PB9_FMP  /*!< Enable Fast Mode Plus on PB9 */
#define SYSCFG_I2CFastModePlus_I2C1      SYSCFG_CFGR1_I2C1_FMP     /*!< Enable Fast Mode Plus on I2C1 pins */
#define SYSCFG_I2CFastModePlus_I2C2      SYSCFG_CFGR1_I2C2_FMP     /*!< Enable Fast Mode Plus on I2C2 pins */
#define SYSCFG_I2CFastModePlus_I2C3      SYSCFG_CFGR1_I2C3_FMP     /*!< Enable Fast Mode Plus on I2C3 pins */

#define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C2)|| \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C3))

/**
  * @}
  */

/** @defgroup SYSCFG_FPU_Interrupt_Config 
  * @{
  */ 
#define SYSCFG_IT_IXC              SYSCFG_CFGR1_FPU_IE_5  /*!< Inexact Interrupt enable (interrupt disabled by default) */
#define SYSCFG_IT_IDC              SYSCFG_CFGR1_FPU_IE_4  /*!< Input denormal Interrupt enable */
#define SYSCFG_IT_OFC              SYSCFG_CFGR1_FPU_IE_3  /*!< Overflow Interrupt enable */
#define SYSCFG_IT_UFC              SYSCFG_CFGR1_FPU_IE_2  /*!< Underflow Interrupt enable */
#define SYSCFG_IT_DZC              SYSCFG_CFGR1_FPU_IE_1  /*!< Divide-by-zero Interrupt enable */
#define SYSCFG_IT_IOC              SYSCFG_CFGR1_FPU_IE_0  /*!< Invalid operation Interrupt enable */

#define IS_SYSCFG_IT(IT) ((((IT) & (uint32_t)0x03FFFFFF) == 0) && ((IT) != 0))

/**
  * @}
  */

/** @defgroup SYSCFG_Lock_Config
  * @{
  */
#define SYSCFG_Break_PVD                     SYSCFG_CFGR2_PVD_LOCK          /*!< Enables and locks the PVD connection with TIM1/8/15/16/17 Break Input and also the PVD_EN and PVDSEL[2:0] bits of the Power Control Interface */
#define SYSCFG_Break_SRAMParity              SYSCFG_CFGR2_SRAM_PARITY_LOCK  /*!< Enables and locks the SRAM_PARITY error signal with Break Input of TIM1/8/15/16/17 */
#define SYSCFG_Break_Lockup                  SYSCFG_CFGR2_LOCKUP_LOCK       /*!< Enables and locks the LOCKUP output of CortexM4 with Break Input of TIM1/8/15/16/17 */

#define IS_SYSCFG_LOCK_CONFIG(CONFIG) (((CONFIG) == SYSCFG_Break_PVD)        || \
                                       ((CONFIG) == SYSCFG_Break_SRAMParity) || \
                                       ((CONFIG) == SYSCFG_Break_Lockup))

/**
  * @}
  */

/** @defgroup ADC_Trigger_Remapping
  * @{
  */
#define REMAPADCTRIGGER_ADC12_EXT2        SYSCFG_CFGR4_ADC12_EXT2_RMP   /*!< Input trigger of ADC12 regular channel EXT2
                                                                                 0: No remap (TIM1_CC3)
                                                                                 1: Remap (TIM20_TRGO) */
#define REMAPADCTRIGGER_ADC12_EXT3        SYSCFG_CFGR4_ADC12_EXT3_RMP   /*!< Input trigger of ADC12 regular channel EXT3
                                                                                 0: No remap (TIM2_CC2)
                                                                                 1: Remap (TIM20_TRGO2) */
#define REMAPADCTRIGGER_ADC12_EXT5        SYSCFG_CFGR4_ADC12_EXT5_RMP   /*!< Input trigger of ADC12 regular channel EXT5
                                                                                 0: No remap (TIM4_CC4)
                                                                                 1: Remap (TIM20_CC1) */
#define REMAPADCTRIGGER_ADC12_EXT13       SYSCFG_CFGR4_ADC12_EXT13_RMP  /*!< Input trigger of ADC12 regular channel EXT13
                                                                                 0: No remap (TIM6_TRGO)
                                                                                 1: Remap (TIM20_CC2) */
#define REMAPADCTRIGGER_ADC12_EXT15       SYSCFG_CFGR4_ADC12_EXT15_RMP  /*!< Input trigger of ADC12 regular channel EXT15
                                                                                 0: No remap (TIM3_CC4)
                                                                                 1: Remap (TIM20_CC3) */
#define REMAPADCTRIGGER_ADC12_JEXT3       SYSCFG_CFGR4_ADC12_JEXT3_RMP  /*!< Input trigger of ADC12 injected channel JEXT3
                                                                                 0: No remap (TIM2_CC1)
                                                                                 1: Remap (TIM20_TRGO) */
#define REMAPADCTRIGGER_ADC12_JEXT6       SYSCFG_CFGR4_ADC12_JEXT6_RMP  /*!< Input trigger of ADC12 injected channel JEXT6
                                                                                 0: No remap (EXTI line 15)
                                                                                 1: Remap (TIM20_TRGO2) */
#define REMAPADCTRIGGER_ADC12_JEXT13      SYSCFG_CFGR4_ADC12_JEXT13_RMP  /*!< Input trigger of ADC12 injected channel JEXT13
                                                                                 0: No remap (TIM3_CC1)
                                                                                 1: Remap (TIM20_CC4) */
#define REMAPADCTRIGGER_ADC34_EXT5        SYSCFG_CFGR4_ADC34_EXT5_RMP   /*!< Input trigger of ADC34 regular channel EXT5
                                                                                 0: No remap (EXTI line 2)
                                                                                 1: Remap (TIM20_TRGO) */
#define REMAPADCTRIGGER_ADC34_EXT6        SYSCFG_CFGR4_ADC34_EXT6_RMP   /*!< Input trigger of ADC34 regular channel EXT6
                                                                                 0: No remap (TIM4_CC1)
                                                                                 1: Remap (TIM20_TRGO2) */
#define REMAPADCTRIGGER_ADC34_EXT15       SYSCFG_CFGR4_ADC34_EXT15_RMP  /*!< Input trigger of ADC34 regular channel EXT15
                                                                                 0: No remap (TIM2_CC1)
                                                                                 1: Remap (TIM20_CC1) */
#define REMAPADCTRIGGER_ADC34_JEXT5       SYSCFG_CFGR4_ADC34_JEXT5_RMP  /*!< Input trigger of ADC34 injected channel JEXT5
                                                                                 0: No remap (TIM4_CC3)
                                                                                 1: Remap (TIM20_TRGO) */
#define REMAPADCTRIGGER_ADC34_JEXT11      SYSCFG_CFGR4_ADC34_JEXT11_RMP /*!< Input trigger of ADC34 injected channel JEXT11
                                                                                 0: No remap (TIM1_CC3)
                                                                                 1: Remap (TIM20_TRGO2) */
#define REMAPADCTRIGGER_ADC34_JEXT14      SYSCFG_CFGR4_ADC34_JEXT14_RMP /*!< Input trigger of ADC34 injected channel JEXT14
                                                                                 0: No remap (TIM7_TRGO)
                                                                                 1: Remap (TIM20_CC2) */

#define IS_SYSCFG_ADC_TRIGGER_REMAP(RMP) (((RMP) == REMAPADCTRIGGER_ADC12_EXT2)   || \
                                          ((RMP) == REMAPADCTRIGGER_ADC12_EXT3)   || \
                                          ((RMP) == REMAPADCTRIGGER_ADC12_EXT5)   || \
                                          ((RMP) == REMAPADCTRIGGER_ADC12_EXT13)  || \
                                          ((RMP) == REMAPADCTRIGGER_ADC12_EXT15)  || \
                                          ((RMP) == REMAPADCTRIGGER_ADC12_JEXT3)  || \
                                          ((RMP) == REMAPADCTRIGGER_ADC12_JEXT6)  || \
                                          ((RMP) == REMAPADCTRIGGER_ADC12_JEXT13) || \
                                          ((RMP) == REMAPADCTRIGGER_ADC34_EXT5)   || \
                                          ((RMP) == REMAPADCTRIGGER_ADC34_EXT6)   || \
                                          ((RMP) == REMAPADCTRIGGER_ADC34_EXT15)  || \
                                          ((RMP) == REMAPADCTRIGGER_ADC34_JEXT5)  || \
                                          ((RMP) == REMAPADCTRIGGER_ADC34_JEXT11) || \
                                          ((RMP) == REMAPADCTRIGGER_ADC34_JEXT14))
                                      
/**
  * @}
  */
  
/** @defgroup SYSCFG_SRAMWRP_Config
  * @{
  */
#define SYSCFG_SRAMWRP_Page0                 SYSCFG_RCR_PAGE0  /*!< ICODE SRAM Write protection page 0 */
#define SYSCFG_SRAMWRP_Page1                 SYSCFG_RCR_PAGE1  /*!< ICODE SRAM Write protection page 1 */
#define SYSCFG_SRAMWRP_Page2                 SYSCFG_RCR_PAGE2  /*!< ICODE SRAM Write protection page 2 */
#define SYSCFG_SRAMWRP_Page3                 SYSCFG_RCR_PAGE3  /*!< ICODE SRAM Write protection page 3 */
#define SYSCFG_SRAMWRP_Page4                 SYSCFG_RCR_PAGE4  /*!< ICODE SRAM Write protection page 4 */
#define SYSCFG_SRAMWRP_Page5                 SYSCFG_RCR_PAGE5  /*!< ICODE SRAM Write protection page 5 */
#define SYSCFG_SRAMWRP_Page6                 SYSCFG_RCR_PAGE6  /*!< ICODE SRAM Write protection page 6 */
#define SYSCFG_SRAMWRP_Page7                 SYSCFG_RCR_PAGE7  /*!< ICODE SRAM Write protection page 7 */
#define SYSCFG_SRAMWRP_Page8                 SYSCFG_RCR_PAGE8  /*!< ICODE SRAM Write protection page 8 */
#define SYSCFG_SRAMWRP_Page9                 SYSCFG_RCR_PAGE9  /*!< ICODE SRAM Write protection page 9 */
#define SYSCFG_SRAMWRP_Page10                SYSCFG_RCR_PAGE10 /*!< ICODE SRAM Write protection page 10 */
#define SYSCFG_SRAMWRP_Page11                SYSCFG_RCR_PAGE11 /*!< ICODE SRAM Write protection page 11 */
#define SYSCFG_SRAMWRP_Page12                SYSCFG_RCR_PAGE12 /*!< ICODE SRAM Write protection page 12 */
#define SYSCFG_SRAMWRP_Page13                SYSCFG_RCR_PAGE13 /*!< ICODE SRAM Write protection page 13 */
#define SYSCFG_SRAMWRP_Page14                SYSCFG_RCR_PAGE14 /*!< ICODE SRAM Write protection page 14 */
#define SYSCFG_SRAMWRP_Page15                SYSCFG_RCR_PAGE15 /*!< ICODE SRAM Write protection page 15 */

#define IS_SYSCFG_PAGE(PAGE)((((PAGE) & (uint32_t)0xFFFF0000) == 0x00000000) && ((PAGE) != 0x00000000))

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
void SYSCFG_TriggerRemapConfig(uint32_t SYSCFG_TriggerRemap, FunctionalState NewState);
void SYSCFG_EncoderRemapConfig(uint32_t SYSCFG_EncoderRemap);
void SYSCFG_USBInterruptLineRemapCmd(FunctionalState NewState);
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState);
void SYSCFG_ITConfig(uint32_t SYSCFG_IT, FunctionalState NewState);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break);
void SYSCFG_BypassParityCheckDisable(void);
void SYSCFG_ADCTriggerRemapConfig(uint32_t SYSCFG_ADCTriggerRemap, FunctionalState NewState);
void SYSCFG_SRAMWRPEnable(uint32_t SYSCFG_SRAMWRP);
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag);
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_SYSCFG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_tim.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the TIM firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_TIM_H
#define __STM32F30x_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup stm32f30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  TIM Time Base Init structure definition  
  * @note   This structure is used with all TIMx except for TIM6 and TIM7.  
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

  uint16_t TIM_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF. 
                                       @note This parameter is valid only for TIM1 and TIM8. */
} TIM_TimeBaseInitTypeDef; 

/** 
  * @brief  TIM Output Compare Init structure definition  
  */

typedef struct
{
  uint32_t TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint16_t TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_State */

  uint16_t TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint32_t TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint16_t TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16_t TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16_t TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
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
  * @brief  BDTR structure definition 
  * @note   This structure is used only with TIM1 and TIM8.    
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

/* Exported constants --------------------------------------------------------*/

/** @defgroup TIM_Exported_constants 
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                   ((PERIPH) == TIM2) || \
                                   ((PERIPH) == TIM3) || \
                                   ((PERIPH) == TIM4) || \
                                   ((PERIPH) == TIM6) || \
                                   ((PERIPH) == TIM7) || \
                                   ((PERIPH) == TIM8) || \
                                   ((PERIPH) == TIM15) || \
                                   ((PERIPH) == TIM16) || \
                                   ((PERIPH) == TIM17) || \
                                   ((PERIPH) == TIM20))
                                   
/* LIST1: TIM1, TIM2, TIM3, TIM4, TIM8, TIM15, TIM16, TIM20 and TIM17 */                                         
#define IS_TIM_LIST1_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15) || \
                                     ((PERIPH) == TIM16) || \
                                     ((PERIPH) == TIM17) || \
                                     ((PERIPH) == TIM20))
                                     
/* LIST2: TIM1, TIM2, TIM3, TIM4, TIM8, TIM20 and TIM15 */ 
#define IS_TIM_LIST2_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM20))
                                     
/* LIST3: TIM1, TIM2, TIM3, TIM4, TIM20 and TIM8 */ 
#define IS_TIM_LIST3_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM20))
                                     
/* LIST4: TIM1, TIM20 and TIM8 */ 
#define IS_TIM_LIST4_PERIPH(PERIPH) (((PERIPH) == TIM1) ||\
                                     ((PERIPH) == TIM8) ||\
                                     ((PERIPH) == TIM20))
                                     
/* LIST5: TIM1, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7 and TIM8 */
#define IS_TIM_LIST5_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM6) || \
                                     ((PERIPH) == TIM7) || \
                                     ((PERIPH) == TIM8))
/* LIST6: TIM1, TIM8, TIM15, TIM16, TIM20 and TIM17 */                               
#define IS_TIM_LIST6_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15) || \
                                     ((PERIPH) == TIM16) || \
                                     ((PERIPH) == TIM17) || \
                                     ((PERIPH) == TIM20))

/* LIST5: TIM1, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7, TIM20 and TIM8 */
#define IS_TIM_LIST7_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM6) || \
                                     ((PERIPH) == TIM7) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM20))
                                     
/* LIST8: TIM16 (option register) */                               
#define IS_TIM_LIST8_PERIPH(PERIPH) (((PERIPH) == TIM16)||  \
                                     ((PERIPH) == TIM1) ||\
                                     ((PERIPH) == TIM8) ||\
                                     ((PERIPH) == TIM20))

/** @defgroup TIM_Output_Compare_and_PWM_modes 
  * @{
  */

#define TIM_OCMode_Timing                  ((uint32_t)0x00000)
#define TIM_OCMode_Active                  ((uint32_t)0x00010)
#define TIM_OCMode_Inactive                ((uint32_t)0x00020)
#define TIM_OCMode_Toggle                  ((uint32_t)0x00030)
#define TIM_OCMode_PWM1                    ((uint32_t)0x00060)
#define TIM_OCMode_PWM2                    ((uint32_t)0x00070)

#define TIM_OCMode_Retrigerrable_OPM1      ((uint32_t)0x10000)
#define TIM_OCMode_Retrigerrable_OPM2      ((uint32_t)0x10010)
#define TIM_OCMode_Combined_PWM1           ((uint32_t)0x10040)
#define TIM_OCMode_Combined_PWM2           ((uint32_t)0x10050)
#define TIM_OCMode_Asymmetric_PWM1         ((uint32_t)0x10060)
#define TIM_OCMode_Asymmetric_PWM2         ((uint32_t)0x10070)

#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
                              ((MODE) == TIM_OCMode_Active) || \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle)|| \
                              ((MODE) == TIM_OCMode_PWM1) || \
                              ((MODE) == TIM_OCMode_PWM2) || \
                              ((MODE) == TIM_OCMode_Retrigerrable_OPM1) || \
                              ((MODE) == TIM_OCMode_Retrigerrable_OPM2) || \
                              ((MODE) == TIM_OCMode_Combined_PWM1) || \
                              ((MODE) == TIM_OCMode_Combined_PWM2) || \
                              ((MODE) == TIM_OCMode_Asymmetric_PWM1) || \
                              ((MODE) == TIM_OCMode_Asymmetric_PWM2))
                              
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
                          ((MODE) == TIM_OCMode_Active) || \
                          ((MODE) == TIM_OCMode_Inactive) || \
                          ((MODE) == TIM_OCMode_Toggle)|| \
                          ((MODE) == TIM_OCMode_PWM1) || \
                          ((MODE) == TIM_OCMode_PWM2) ||  \
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive) || \
                          ((MODE) == TIM_OCMode_Retrigerrable_OPM1) || \
                          ((MODE) == TIM_OCMode_Retrigerrable_OPM2) || \
                          ((MODE) == TIM_OCMode_Combined_PWM1) || \
                          ((MODE) == TIM_OCMode_Combined_PWM2) || \
                          ((MODE) == TIM_OCMode_Asymmetric_PWM1) || \
                          ((MODE) == TIM_OCMode_Asymmetric_PWM2))
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
#define TIM_Channel_5                      ((uint16_t)0x0010)
#define TIM_Channel_6                      ((uint16_t)0x0014)
                                 
#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))
                                 
#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))
#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))
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

/** @defgroup TIM_Output_Compare_State 
  * @{
  */

#define TIM_OutputState_Disable            ((uint16_t)0x0000)
#define TIM_OutputState_Enable             ((uint16_t)0x0001)
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_State
  * @{
  */

#define TIM_OutputNState_Disable           ((uint16_t)0x0000)
#define TIM_OutputNState_Enable            ((uint16_t)0x0004)
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_State
  * @{
  */

#define TIM_CCx_Enable                      ((uint16_t)0x0001)
#define TIM_CCx_Disable                     ((uint16_t)0x0000)
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_N_State
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

/** @defgroup TIM_Break1_Input_enable_disable 
  * @{
  */

#define TIM_Break1_Enable                   ((uint32_t)0x00001000)
#define TIM_Break1_Disable                  ((uint32_t)0x00000000)
#define IS_TIM_BREAK1_STATE(STATE) (((STATE) == TIM_Break1_Enable) || \
                                   ((STATE) == TIM_Break1_Disable))
/**
  * @}
  */

/** @defgroup TIM_Break2_Input_enable_disable 
  * @{
  */

#define TIM_Break2_Enable                   ((uint32_t)0x01000000)
#define TIM_Break2_Disable                  ((uint32_t)0x00000000)
#define IS_TIM_BREAK2_STATE(STATE) (((STATE) == TIM_Break2_Enable) || \
                                   ((STATE) == TIM_Break2_Disable))
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

/** @defgroup TIM_Break1_Polarity 
  * @{
  */

#define TIM_Break1Polarity_Low              ((uint32_t)0x00000000)
#define TIM_Break1Polarity_High             ((uint32_t)0x00002000)
#define IS_TIM_BREAK1_POLARITY(POLARITY) (((POLARITY) == TIM_Break1Polarity_Low) || \
                                         ((POLARITY) == TIM_Break1Polarity_High))
/**
  * @}
  */ 

/** @defgroup TIM_Break2_Polarity 
  * @{
  */

#define TIM_Break2Polarity_Low              ((uint32_t)0x00000000)
#define TIM_Break2Polarity_High             ((uint32_t)0x02000000)
#define IS_TIM_BREAK2_POLARITY(POLARITY) (((POLARITY) == TIM_Break2Polarity_Low) || \
                                         ((POLARITY) == TIM_Break2Polarity_High))
/**
  * @}
  */ 

/** @defgroup TIM_Break1_Filter 
  * @{
  */

#define IS_TIM_BREAK1_FILTER(FILTER) ((FILTER) <= 0xF)
/**
  * @}
  */ 

/** @defgroup TIM_Break2_Filter 
  * @{
  */

#define IS_TIM_BREAK2_FILTER(FILTER) ((FILTER) <= 0xF)
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
#define TIM_DMABase_CCMR3                  ((uint16_t)0x0014)
#define TIM_DMABase_CCR5                   ((uint16_t)0x0015)
#define TIM_DMABase_CCR6                   ((uint16_t)0x0016)
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
                               ((BASE) == TIM_DMABase_OR) || \
                               ((BASE) == TIM_DMABase_CCMR3) || \
                               ((BASE) == TIM_DMABase_CCR5) || \
                               ((BASE) == TIM_DMABase_CCR6))                     
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
#define TIM_EventSource_Break2             ((uint16_t)0x0100)
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0xFE00) == 0x0000) && ((SOURCE) != 0x0000))                                          
  
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


#define TIM_TRGO2Source_Reset                             ((uint32_t)0x00000000)
#define TIM_TRGO2Source_Enable                            ((uint32_t)0x00100000)
#define TIM_TRGO2Source_Update                            ((uint32_t)0x00200000)
#define TIM_TRGO2Source_OC1                               ((uint32_t)0x00300000)
#define TIM_TRGO2Source_OC1Ref                            ((uint32_t)0x00400000)
#define TIM_TRGO2Source_OC2Ref                            ((uint32_t)0x00500000)
#define TIM_TRGO2Source_OC3Ref                            ((uint32_t)0x00600000)
#define TIM_TRGO2Source_OC4Ref                            ((uint32_t)0x00700000)
#define TIM_TRGO2Source_OC5Ref                            ((uint32_t)0x00800000)
#define TIM_TRGO2Source_OC6Ref                            ((uint32_t)0x00900000)
#define TIM_TRGO2Source_OC4Ref_RisingFalling              ((uint32_t)0x00A00000)
#define TIM_TRGO2Source_OC6Ref_RisingFalling              ((uint32_t)0x00B00000)
#define TIM_TRGO2Source_OC4RefRising_OC6RefRising         ((uint32_t)0x00C00000)
#define TIM_TRGO2Source_OC4RefRising_OC6RefFalling        ((uint32_t)0x00D00000)
#define TIM_TRGO2Source_OC5RefRising_OC6RefRising         ((uint32_t)0x00E00000)
#define TIM_TRGO2Source_OC5RefRising_OC6RefFalling        ((uint32_t)0x00F00000)
#define IS_TIM_TRGO2_SOURCE(SOURCE) (((SOURCE) == TIM_TRGO2Source_Reset) || \
                                     ((SOURCE) == TIM_TRGO2Source_Enable) || \
                                     ((SOURCE) == TIM_TRGO2Source_Update) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC1) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC1Ref) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC2Ref) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC3Ref) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC4Ref) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC5Ref) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC6Ref) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC4Ref_RisingFalling) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC6Ref_RisingFalling) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC4RefRising_OC6RefRising) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC4RefRising_OC6RefFalling) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC5RefRising_OC6RefRising) || \
                                     ((SOURCE) == TIM_TRGO2Source_OC5RefRising_OC6RefFalling))
/**
  * @}
  */ 

/** @defgroup TIM_Slave_Mode 
  * @{
  */

#define TIM_SlaveMode_Reset                       ((uint32_t)0x00004)
#define TIM_SlaveMode_Gated                       ((uint32_t)0x00005)
#define TIM_SlaveMode_Trigger                     ((uint32_t)0x00006)
#define TIM_SlaveMode_External1                   ((uint32_t)0x00007)
#define TIM_SlaveMode_Combined_ResetTrigger       ((uint32_t)0x10000)
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
                                 ((MODE) == TIM_SlaveMode_Gated) || \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1) || \
                                 ((MODE) == TIM_SlaveMode_Combined_ResetTrigger))
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
/** @defgroup TIM_Remap 
  * @{
  */
#define TIM16_GPIO                      ((uint16_t)0x0000)
#define TIM16_RTC_CLK                   ((uint16_t)0x0001)
#define TIM16_HSEDiv32                  ((uint16_t)0x0002)
#define TIM16_MCO                       ((uint16_t)0x0003)

#define TIM1_ADC1_AWDG1                ((uint16_t)0x0001)
#define TIM1_ADC1_AWDG2                ((uint16_t)0x0002)
#define TIM1_ADC1_AWDG3                ((uint16_t)0x0003)
#define TIM1_ADC4_AWDG1                ((uint16_t)0x0004)
#define TIM1_ADC4_AWDG2                ((uint16_t)0x0008)
#define TIM1_ADC4_AWDG3                ((uint16_t)0x000C)

#define TIM8_ADC2_AWDG1                ((uint16_t)0x0001)
#define TIM8_ADC2_AWDG2                ((uint16_t)0x0002)
#define TIM8_ADC2_AWDG3                ((uint16_t)0x0003)
#define TIM8_ADC3_AWDG1                ((uint16_t)0x0004)
#define TIM8_ADC3_AWDG2                ((uint16_t)0x0008)
#define TIM8_ADC3_AWDG3                ((uint16_t)0x000C)

#define TIM20_ADC3_AWDG1               ((uint16_t)0x0001)
#define TIM20_ADC3_AWDG2               ((uint16_t)0x0002)
#define TIM20_ADC3_AWDG3               ((uint16_t)0x0003)
#define TIM20_ADC4_AWDG1               ((uint16_t)0x0004)
#define TIM20_ADC4_AWDG2               ((uint16_t)0x0008)
#define TIM20_ADC4_AWDG3               ((uint16_t)0x000C)

#define IS_TIM_REMAP(TIM_REMAP)  (((TIM_REMAP) == TIM16_GPIO)|| \
                                  ((TIM_REMAP) == TIM16_RTC_CLK) || \
                                  ((TIM_REMAP) == TIM16_HSEDiv32) || \
                                  ((TIM_REMAP) == TIM16_MCO) ||\
                                  ((TIM_REMAP) == TIM1_ADC1_AWDG1) ||\
                                  ((TIM_REMAP) == TIM1_ADC1_AWDG2) ||\
                                  ((TIM_REMAP) == TIM1_ADC1_AWDG3) ||\
                                  ((TIM_REMAP) == TIM1_ADC4_AWDG1) ||\
                                  ((TIM_REMAP) == TIM1_ADC4_AWDG2) ||\
                                  ((TIM_REMAP) == TIM1_ADC4_AWDG3) ||\
                                  ((TIM_REMAP) == TIM8_ADC2_AWDG1) ||\
                                  ((TIM_REMAP) == TIM8_ADC2_AWDG2) ||\
                                  ((TIM_REMAP) == TIM8_ADC2_AWDG3) ||\
                                  ((TIM_REMAP) == TIM8_ADC3_AWDG1) ||\
                                  ((TIM_REMAP) == TIM8_ADC3_AWDG2) ||\
                                  ((TIM_REMAP) == TIM8_ADC3_AWDG3) ||\
                                  ((TIM_REMAP) == TIM20_ADC3_AWDG1)||\
                                  ((TIM_REMAP) == TIM20_ADC3_AWDG2)||\
                                  ((TIM_REMAP) == TIM20_ADC3_AWDG3)||\
                                  ((TIM_REMAP) == TIM20_ADC4_AWDG1)||\
                                  ((TIM_REMAP) == TIM20_ADC4_AWDG2)||\
                                  ((TIM_REMAP) == TIM20_ADC4_AWDG3))                                  

/**
  * @}
  */ 
/** @defgroup TIM_Flags 
  * @{
  */

#define TIM_FLAG_Update                    ((uint32_t)0x00001)
#define TIM_FLAG_CC1                       ((uint32_t)0x00002)
#define TIM_FLAG_CC2                       ((uint32_t)0x00004)
#define TIM_FLAG_CC3                       ((uint32_t)0x00008)
#define TIM_FLAG_CC4                       ((uint32_t)0x00010)
#define TIM_FLAG_COM                       ((uint32_t)0x00020)
#define TIM_FLAG_Trigger                   ((uint32_t)0x00040)
#define TIM_FLAG_Break                     ((uint32_t)0x00080)
#define TIM_FLAG_Break2                    ((uint32_t)0x00100)
#define TIM_FLAG_CC1OF                     ((uint32_t)0x00200)
#define TIM_FLAG_CC2OF                     ((uint32_t)0x00400)
#define TIM_FLAG_CC3OF                     ((uint32_t)0x00800)
#define TIM_FLAG_CC4OF                     ((uint32_t)0x01000)
#define TIM_FLAG_CC5                       ((uint32_t)0x10000)
#define TIM_FLAG_CC6                       ((uint32_t)0x20000)
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
                               ((FLAG) == TIM_FLAG_CC1) || \
                               ((FLAG) == TIM_FLAG_CC2) || \
                               ((FLAG) == TIM_FLAG_CC3) || \
                               ((FLAG) == TIM_FLAG_CC4) || \
                               ((FLAG) == TIM_FLAG_COM) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) || \
                               ((FLAG) == TIM_FLAG_Break2) || \
                               ((FLAG) == TIM_FLAG_CC1OF) || \
                               ((FLAG) == TIM_FLAG_CC2OF) || \
                               ((FLAG) == TIM_FLAG_CC3OF) || \
                               ((FLAG) == TIM_FLAG_CC4OF) ||\
                               ((FLAG) == TIM_FLAG_CC5) ||\
                               ((FLAG) == TIM_FLAG_CC6))

#define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (uint32_t)0xE000) == 0x0000) && ((TIM_FLAG) != 0x0000))
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
/* Exported functions --------------------------------------------------------*/ 

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
void TIM_UIFRemap(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Output Compare management **************************************************/
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC5Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC6Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_SelectGC5C1(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectGC5C2(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectGC5C3(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint32_t TIM_OCMode);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4);
void TIM_SetCompare5(TIM_TypeDef* TIMx, uint32_t Compare5);
void TIM_SetCompare6(TIM_TypeDef* TIMx, uint32_t Compare6);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC5Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC6Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC5PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC6PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC5Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC6Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_SelectOCREFClear(TIM_TypeDef* TIMx, uint16_t TIM_OCReferenceClear);  
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC5PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC6PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);

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

/* Advanced-control timers (TIM1 and TIM8) specific features ******************/
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_Break1Config(TIM_TypeDef* TIMx, uint32_t TIM_Break1Polarity, uint8_t TIM_Break1Filter);
void TIM_Break2Config(TIM_TypeDef* TIMx, uint32_t TIM_Break2Polarity, uint8_t TIM_Break2Filter);
void TIM_Break1Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_Break2Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Interrupts, DMA and flags management ***************************************/
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint32_t TIM_FLAG);
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
void TIM_SelectOutputTrigger2(TIM_TypeDef* TIMx, uint32_t TIM_TRGO2Source);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint32_t TIM_SlaveMode);
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

#endif /*__STM32F30x_TIM_H */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_usart.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the USART 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_USART_H
#define __STM32F30x_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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
 
  uint32_t USART_Mode;                /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  uint32_t USART_HardwareFlowControl; /*!< Specifies whether the hardware flow control mode is enabled
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
                                     ((PERIPH) == UART4) || \
                                     ((PERIPH) == UART5))

#define IS_USART_123_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3))

#define IS_USART_1234_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                      ((PERIPH) == USART2) || \
                                      ((PERIPH) == USART3) || \
                                      ((PERIPH) == UART4))


/** @defgroup USART_Word_Length 
  * @{
  */ 

#define USART_WordLength_8b                  ((uint32_t)0x00000000)
#define USART_WordLength_9b                  USART_CR1_M
#define IS_USART_WORD_LENGTH(LENGTH) (((LENGTH) == USART_WordLength_8b) || \
                                      ((LENGTH) == USART_WordLength_9b))
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
  * @{
  */ 

#define USART_WakeUpSource_AddressMatch      ((uint32_t)0x00000000)
#define USART_WakeUpSource_StartBit          USART_CR3_WUS_1
#define USART_WakeUpSource_RXNE              (uint32_t)(USART_CR3_WUS_0 | USART_CR3_WUS_1)
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

#define USART_AutoBaudRate_StartBit                 ((uint32_t)0x00000000)
#define USART_AutoBaudRate_FallingEdge              USART_CR2_ABRMODE_0
#define USART_AutoBaudRate_0x7FFrame                USART_CR2_ABRMODE_1
#define USART_AutoBaudRate_0x55Frame                (USART_CR2_ABRMODE_0 | USART_CR2_ABRMODE_1)
#define IS_USART_AUTOBAUDRATE_MODE(MODE) (((MODE) == USART_AutoBaudRate_StartBit) || \
                                          ((MODE) == USART_AutoBaudRate_FallingEdge) || \
                                          ((MODE) == USART_AutoBaudRate_0x7FFrame) || \
                                          ((MODE) == USART_AutoBaudRate_0x55Frame))
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
#define USART_FLAG_WU                        USART_ISR_WUF
#define USART_FLAG_RWU                       USART_ISR_RWU
#define USART_FLAG_SBK                       USART_ISR_SBKF
#define USART_FLAG_CM                        USART_ISR_CMF
#define USART_FLAG_BUSY                      USART_ISR_BUSY
#define USART_FLAG_ABRF                      USART_ISR_ABRF
#define USART_FLAG_ABRE                      USART_ISR_ABRE
#define USART_FLAG_EOB                       USART_ISR_EOBF
#define USART_FLAG_RTO                       USART_ISR_RTOF
#define USART_FLAG_nCTSS                     USART_ISR_CTS 
#define USART_FLAG_CTS                       USART_ISR_CTSIF
#define USART_FLAG_LBD                       USART_ISR_LBD
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

#define USART_IT_WU                          ((uint32_t)0x00140316)
#define USART_IT_CM                          ((uint32_t)0x0011010E)
#define USART_IT_EOB                         ((uint32_t)0x000C011B)
#define USART_IT_RTO                         ((uint32_t)0x000B011A)
#define USART_IT_PE                          ((uint32_t)0x00000108)
#define USART_IT_TXE                         ((uint32_t)0x00070107)
#define USART_IT_TC                          ((uint32_t)0x00060106)
#define USART_IT_RXNE                        ((uint32_t)0x00050105)
#define USART_IT_IDLE                        ((uint32_t)0x00040104)
#define USART_IT_LBD                         ((uint32_t)0x00080206)
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
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);
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
void USART_StopModeWakeUpSourceConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUpSource);

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
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint32_t USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* Half-duplex mode function **************************************************/
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* Smartcard mode functions ***************************************************/
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);
void USART_SetAutoRetryCount(USART_TypeDef* USARTx, uint8_t USART_AutoCount);
void USART_SetBlockLength(USART_TypeDef* USARTx, uint8_t USART_BlockLength);

/* IrDA mode functions ********************************************************/
void USART_IrDAConfig(USART_TypeDef* USARTx, uint32_t USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);

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

#endif /* __STM32F30x_USART_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    stm32f30x_wwdg.h
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file contains all the functions prototypes for the WWDG 
  *          firmware library.    
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32F30x_WWDG_H
#define __STM32F30x_WWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
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

#endif /* __STM32F30x_WWDG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
