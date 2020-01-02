/**
  ******************************************************************************
  * @file    stm32f30x_adc.c
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    27-February-2015
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *           + Initialization and Configuration
  *           + Analog Watchdog configuration
  *           + Temperature Sensor, Vbat & Vrefint (Internal Reference Voltage) management 
  *           + Regular Channels Configuration
  *           + Regular Channels DMA Configuration
  *           + Injected channels Configuration
  *           + Interrupts and flags management
  *           + Dual mode configuration  
  *         
  @verbatim
  ==============================================================================
                             ##### How to use this driver #####
  ==============================================================================
    [..]
    (#) select the ADC clock using the function RCC_ADCCLKConfig()
    (#) Enable the ADC interface clock using RCC_AHBPeriphClockCmd();
    (#) ADC pins configuration
        (++) Enable the clock for the ADC GPIOs using the following function:
             RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);
        (++) Configure these ADC pins in analog mode using GPIO_Init();
    (#) Configure the ADC conversion resolution, data alignment, external
        trigger and edge, sequencer lenght and Enable/Disable the continuous mode
        using the ADC_Init() function.
    (#) Activate the ADC peripheral using ADC_Cmd() function.

    *** ADC channels group configuration ***
    ========================================    
    [..] 
    (+) To configure the ADC channels features, use ADC_Init(), ADC_InjectedInit()
        and/or ADC_RegularChannelConfig() functions.
    (+) To activate the continuous mode, use the ADC_ContinuousModeCmd()
        function.
    (+) To activate the Discontinuous mode, use the ADC_DiscModeCmd() functions. 
    (+) To activate the overrun mode, use the ADC_OverrunModeCmd() functions.
    (+) To activate the calibration mode, use the ADC_StartCalibration() functions.
    (+) To read the ADC converted values, use the ADC_GetConversionValue()
        function.

    *** DMA for ADC channels features configuration ***
    ===================================================     
    [..] 
    (+) To enable the DMA mode for ADC channels group, use the ADC_DMACmd() function.
    (+) To configure the DMA transfer request, use ADC_DMAConfig() function.

  @endverbatim
  *
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

/* Includes ------------------------------------------------------------------*/
//#include "includes.h"
//#include "RegBitDefs.h"										// common header file
#include "StdPeriphDriver.h"

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC 
  * @brief ADC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ADC CFGR mask */
#define CFGR1_CLEAR_MASK           ((uint32_t)0xFFFFD203)

/* Calibration time out */
#define CALIBRATION_TIMEOUT        ((uint32_t)0x0000F000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ADC_Private_Functions
  * @{
  */

/** @defgroup ADC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
        (+) Initialize and configure the ADC Prescaler
        (+) ADC Conversion Resolution (12bit..6bit)
        (+) ADC Continuous Conversion Mode (Continuous or Single conversion)
        (+) External trigger Edge and source 
        (+) Converted data alignment (left or right)
        (+) The direction in which the channels will be scanned in the sequence
        (+) Enable or disable the ADC peripheral
   
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes ADC1 peripheral registers to their default reset values.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @retval None
  */
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  if(ADCx == ADC1)
  {
    /* Enable ADC1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* Release ADC1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
  }
}

/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC ( 
  *         Resolution, Data Alignment, continuous mode activation, External 
  *         trigger source and edge, Sequence Scan Direction).   
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains 
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_RESOLUTION(ADC_InitStruct->ADC_Resolution));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
  assert_param(IS_ADC_EXT_TRIG_EDGE(ADC_InitStruct->ADC_ExternalTrigConvEdge));
  assert_param(IS_ADC_EXTERNAL_TRIG_CONV(ADC_InitStruct->ADC_ExternalTrigConv));
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
  assert_param(IS_ADC_SCAN_DIRECTION(ADC_InitStruct->ADC_ScanDirection)); 

  /* Get the ADCx CFGR value */
  tmpreg = ADCx->CFGR1;

  /* Clear SCANDIR, RES[1:0], ALIGN, EXTSEL[2:0], EXTEN[1:0] and CONT bits */
  tmpreg &= CFGR1_CLEAR_MASK;

  /*---------------------------- ADCx CFGR Configuration ---------------------*/

  /* Set RES[1:0] bits according to ADC_Resolution value */
  /* Set CONT bit according to ADC_ContinuousConvMode value */
  /* Set EXTEN[1:0] bits according to ADC_ExternalTrigConvEdge value */
  /* Set EXTSEL[2:0] bits according to ADC_ExternalTrigConv value */
  /* Set ALIGN bit according to ADC_DataAlign value */
  /* Set SCANDIR bit according to ADC_ScanDirection value */
 
  tmpreg  |= (uint32_t)(ADC_InitStruct->ADC_Resolution | ((uint32_t)(ADC_InitStruct->ADC_ContinuousConvMode) << 13) |
             ADC_InitStruct->ADC_ExternalTrigConvEdge | ADC_InitStruct->ADC_ExternalTrigConv |
             ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ScanDirection);

  /* Write to ADCx CFGR */
  ADCx->CFGR1 = tmpreg;
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the ADC ( 
  *         Resolution, Data Alignment, continuous mode activation, External 
  *         trigger source and edge, Sequence Scan Direction).
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */
  /* Initialize the ADC_Resolution member */
  ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;

   /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;

  /* Initialize the ADC_ExternalTrigConvEdge member */
  ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;

  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;

  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;

  /* Initialize the ADC_ScanDirection member */
  ADC_InitStruct->ADC_ScanDirection = ADC_ScanDirection_Upward;
}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ADEN bit to Enable the ADC peripheral */
    ADCx->CR |= (uint32_t)ADC_CR_ADEN;
  }
  else
  {
    /* Set the ADDIS to Disable the ADC peripheral */
    ADCx->CR |= (uint32_t)ADC_CR_ADDIS;
  }
}

/**
  * @brief  Configure the ADC to either be clocked by the asynchronous clock(which is
  *         independent, the dedicated 14MHz clock) or the synchronous clock derived from
  *         the APB clock of the ADC bus interface divided by 2 or 4
  * @note   This function can be called only when ADC is disabled.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_ClockMode: This parameter can be :
  *            @arg ADC_ClockMode_AsynClk: ADC clocked by the dedicated 14MHz clock
  *            @arg ADC_ClockMode_SynClkDiv2: ADC clocked by PCLK/2
  *            @arg ADC_ClockMode_SynClkDiv4: ADC clocked by PCLK/4  
  * @retval None
  */
void ADC_ClockModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_ClockMode)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLOCKMODE(ADC_ClockMode));

    /* Configure the ADC Clock mode according to ADC_ClockMode */
    ADCx->CFGR2 = (uint32_t)ADC_ClockMode;

}

/**
  * @brief  Enables or disables the jitter when the ADC is clocked by PCLK div2
  *         or div4
  * @note   This function is obsolete and maintained for legacy purpose only. ADC_ClockModeConfig()
  *         function should be used instead.  
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_JitterOff: This parameter can be :
  *            @arg ADC_JitterOff_PCLKDiv2: Remove jitter when ADC is clocked by PLCK divided by 2
  *            @arg ADC_JitterOff_PCLKDiv4: Remove jitter when ADC is clocked by PLCK divided by 4
  * @param  NewState: new state of the ADCx jitter. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_JitterCmd(ADC_TypeDef* ADCx, uint32_t ADC_JitterOff, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_JITTEROFF(ADC_JitterOff));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Disable Jitter */
    ADCx->CFGR2 |= (uint32_t)ADC_JitterOff;
  }
  else
  {
    /* Enable Jitter */
    ADCx->CFGR2 &= (uint32_t)(~ADC_JitterOff);
  }
}

/**
  * @}
  */

/** @defgroup ADC_Group2 Power saving functions
 *  @brief   Power saving functions 
 *
@verbatim
 ===============================================================================
          ##### Power saving functions #####
 ===============================================================================
    [..] This section provides functions allowing to reduce power consumption.
    [..] The two function must be combined to get the maximal benefits:
         When the ADC frequency is higher than the CPU one, it is recommended to 
         (#) Enable the Auto Delayed Conversion mode : 
             ==> using ADC_WaitModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
         (#) Enable the power off in Delay phases :
             ==> using ADC_AutoPowerOffCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the ADC Power Off.
  * @note   ADC power-on and power-off can be managed by hardware to cut the 
  *         consumption when the ADC is not converting. 
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @note   The ADC can be powered down: 
  *         - During the Auto delay phase:  The ADC is powered on again at the end
  *           of the delay (until the previous data is read from the ADC data register). 
  *         - During the ADC is waiting for a trigger event: The ADC is powered up
  *           at the next trigger event (when the conversion is started).
  * @param  NewState: new state of the ADCx power Off. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AutoPowerOffCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the ADC Automatic Power-Off */
    ADCx->CFGR1 |= ADC_CFGR1_AUTOFF;
  }
  else
  {
    /* Disable the ADC Automatic Power-Off */
    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_AUTOFF;
  }
}

/**
  * @brief  Enables or disables the Wait conversion mode.
  * @note   When the CPU clock is not fast enough to manage the data rate, a 
  *         Hardware delay can be introduced between ADC conversions to reduce 
  *         this data rate. 
  * @note   The Hardware delay is inserted after each conversions and until the
  *         previous data is read from the ADC data register
  * @note   This is a way to automatically adapt the speed of the ADC to the speed 
  *         of the system which will read the data.
  * @note   Any hardware triggers wich occur while a conversion is on going or 
  *         while the automatic Delay is applied are ignored 
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx Auto-Delay.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_WaitModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the ADC Automatic Delayed conversion */
    ADCx->CFGR1 |= ADC_CFGR1_WAIT;
  }
  else
  {
    /* Disable the ADC Automatic Delayed conversion */
    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_WAIT;
  }
}

/**
  * @}
  */

/** @defgroup ADC_Group3 Analog Watchdog configuration functions
 *  @brief   Analog Watchdog configuration functions 
 *
@verbatim
 ===============================================================================
                   ##### Analog Watchdog configuration functions #####
 ===============================================================================  
    [..] This section provides functions allowing to configure the Analog Watchdog
         (AWD) feature in the ADC.
    [..] A typical configuration Analog Watchdog is done following these steps :
         (#) the ADC guarded channel(s) is (are) selected using the 
             ADC_AnalogWatchdogSingleChannelConfig() function.
         (#) The Analog watchdog lower and higher threshold are configured using the  
             ADC_AnalogWatchdogThresholdsConfig() function.
         (#) The Analog watchdog is enabled and configured to enable the check, on one
             or more channels, using the  ADC_AnalogWatchdogCmd() function.
         (#) Enable the analog watchdog on the selected channel using
             ADC_AnalogWatchdogSingleChannelCmd() function

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the analog watchdog 
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx Analog Watchdog.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the ADC Analog Watchdog */
    ADCx->CFGR1 |= ADC_CFGR1_AWDEN;
  }
  else
  {
    /* Disable the ADC Analog Watchdog */
    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_AWDEN;
  }
}

/**
  * @brief  Configures the high and low thresholds of the analog watchdog. 
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *          This parameter must be a 12bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *          This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));

  /* Set the ADCx high and low threshold */
  ADCx->TR = LowThreshold | ((uint32_t)HighThreshold << 16);

}

/**
  * @brief  Configures the analog watchdog guarded single channel
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_AnalogWatchdog_Channel: the ADC channel to configure for the analog watchdog.
  *          This parameter can be one of the following values:
  *            @arg ADC_AnalogWatchdog_Channel_0: ADC Channel0 selected
  *            @arg ADC_AnalogWatchdog_Channel_1: ADC Channel1 selected
  *            @arg ADC_AnalogWatchdog_Channel_2: ADC Channel2 selected
  *            @arg ADC_AnalogWatchdog_Channel_3: ADC Channel3 selected
  *            @arg ADC_AnalogWatchdog_Channel_4: ADC Channel4 selected
  *            @arg ADC_AnalogWatchdog_Channel_5: ADC Channel5 selected
  *            @arg ADC_AnalogWatchdog_Channel_6: ADC Channel6 selected
  *            @arg ADC_AnalogWatchdog_Channel_7: ADC Channel7 selected
  *            @arg ADC_AnalogWatchdog_Channel_8: ADC Channel8 selected
  *            @arg ADC_AnalogWatchdog_Channel_9: ADC Channel9 selected
  *            @arg ADC_AnalogWatchdog_Channel_10: ADC Channel10 selected, not available for STM32F031 devices
  *            @arg ADC_AnalogWatchdog_Channel_11: ADC Channel11 selected, not available for STM32F031 devices
  *            @arg ADC_AnalogWatchdog_Channel_12: ADC Channel12 selected, not available for STM32F031 devices
  *            @arg ADC_AnalogWatchdog_Channel_13: ADC Channel13 selected, not available for STM32F031 devices
  *            @arg ADC_AnalogWatchdog_Channel_14: ADC Channel14 selected, not available for STM32F031 devices
  *            @arg ADC_AnalogWatchdog_Channel_15: ADC Channel15 selected, not available for STM32F031 devices
  *            @arg ADC_AnalogWatchdog_Channel_16: ADC Channel16 selected
  *            @arg ADC_AnalogWatchdog_Channel_17: ADC Channel17 selected
  *            @arg ADC_AnalogWatchdog_Channel_18: ADC Channel18 selected, not available for STM32F030 devices
  * @note   The channel selected on the AWDCH must be also set into the CHSELR 
  *         register 
  * @retval None
  */
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog_Channel)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_ANALOG_WATCHDOG_CHANNEL(ADC_AnalogWatchdog_Channel));

  /* Get the old register value */
  tmpreg = ADCx->CFGR1;

  /* Clear the Analog watchdog channel select bits */
  tmpreg &= ~ADC_CFGR1_AWDCH;

  /* Set the Analog watchdog channel */
  tmpreg |= ADC_AnalogWatchdog_Channel;

  /* Store the new register value */
  ADCx->CFGR1 = tmpreg;
}

/**
  * @brief  Enables or disables the ADC Analog Watchdog Single Channel.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the ADCx ADC Analog Watchdog Single Channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AnalogWatchdogSingleChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the ADC Analog Watchdog Single Channel */
    ADCx->CFGR1 |= ADC_CFGR1_AWDSGL;
  }
  else
  {
    /* Disable the ADC Analog Watchdog Single Channel */
    ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_AWDSGL;
  }
}

/**
  * @}
  */

/** @defgroup ADC_Group4 Temperature Sensor, Vrefint  and Vbat management functions
 *  @brief   Temperature Sensor, Vrefint  and Vbat management functions
 *
@verbatim
 ===============================================================================
 ##### Temperature Sensor, Vrefint  and Vbat management function #####
 ===============================================================================
    [..] This section provides a function allowing to enable/disable the internal 
         connections between the ADC and the Temperature Sensor, the Vrefint and
         Vbat source.
     
    [..] A typical configuration to get the Temperature sensor, Vrefint and Vbat channels 
         voltages is done following these steps :
         (#) Enable the internal connection of Temperature sensor, Vrefint or Vbat sources 
             with the ADC channels using ADC_TempSensorCmd(), ADC_VrefintCmd() or ADC_VbatCmd()
             functions. 
         (#) select the ADC_Channel_16(Temperature sensor), ADC_Channel_17(Vrefint)
             or ADC_Channel_18(Voltage battery) using ADC_ChannelConfig() function 
         (#) Get the voltage values, using ADC_GetConversionValue() function

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the temperature sensor channel.
  * @param  NewState: new state of the temperature sensor input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TempSensorCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the temperature sensor channel*/
    ADC->CCR |= (uint32_t)ADC_CCR_TSEN;
  }
  else
  {
    /* Disable the temperature sensor channel*/
    ADC->CCR &= (uint32_t)(~ADC_CCR_TSEN);
  }
}

/**
  * @brief  Enables or disables the Vrefint channel.
  * @param  NewState: new state of the Vref input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VrefintCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Vrefint channel*/
    ADC->CCR |= (uint32_t)ADC_CCR_VREFEN;
  }
  else
  {
    /* Disable the Vrefint channel*/
    ADC->CCR &= (uint32_t)(~ADC_CCR_VREFEN);
  }
}

/**
  * @brief  Enables or disables the Vbat channel. 
  * @note   This feature is not applicable for STM32F030 devices. 
  * @param  NewState: new state of the Vbat input channel.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VbatCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Vbat channel*/
    ADC->CCR |= (uint32_t)ADC_CCR_VBATEN;
  }
  else
  {
    /* Disable the Vbat channel*/
    ADC->CCR &= (uint32_t)(~ADC_CCR_VBATEN);
  }
}

/**
  * @}
  */

/** @defgroup ADC_Group5 Channels Configuration functions
 *  @brief    Channels Configuration functions 
 *
@verbatim
 ===============================================================================
            ##### Channels Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to manage the ADC channels,
         it is composed of 3 sub sections :
         (#) Configuration and management functions for ADC channels: This subsection 
             provides functions allowing to configure the ADC channels :    
             (++) Select the ADC channels
             (++) Activate ADC Calibration
             (++) Activate the Overrun Mode.
             (++) Activate the Discontinuous Mode 
             (++) Activate the Continuous Mode.
             (++) Configure the sampling time for each channel
             (++) Select the conversion Trigger and Edge for ADC channels
             (++) Select the scan direction.
             -@@- Please Note that the following features for ADC channels are configurated
                  using the ADC_Init() function : 
                  (+@@) Activate the Continuous Mode (can be also activated by ADC_OverrunModeCmd().
                  (+@@) Select the conversion Trigger and Edge for ADC channels
                  (+@@) Select the scan direction.
         (#) Control the ADC peripheral : This subsection permits to command the ADC:
             (++) Stop or discard an on-going conversion (ADSTP command)
             (++) Start the ADC conversion .
         (#) Get the conversion data: This subsection provides an important function in 
             the ADC peripheral since it returns the converted data of the current 
             ADC channel. When the Conversion value is read, the EOC Flag is 
             automatically cleared.

@endverbatim
  * @{
  */

/**
  * @brief  Configures for the selected ADC and its sampling time.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected, not available for STM32F031 devices
  *            @arg ADC_Channel_11: ADC Channel11 selected, not available for STM32F031 devices
  *            @arg ADC_Channel_12: ADC Channel12 selected, not available for STM32F031 devices
  *            @arg ADC_Channel_13: ADC Channel13 selected, not available for STM32F031 devices
  *            @arg ADC_Channel_14: ADC Channel14 selected, not available for STM32F031 devices
  *            @arg ADC_Channel_15: ADC Channel15 selected, not available for STM32F031 devices
  *            @arg ADC_Channel_16: ADC Channel16 selected
  *            @arg ADC_Channel_17: ADC Channel17 selected
  *            @arg ADC_Channel_18: ADC Channel18 selected, not available for STM32F030 devices
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel. 
  *          This parameter can be one of the following values:
  *            @arg ADC_SampleTime_1_5Cycles: Sample time equal to 1.5 cycles  
  *            @arg ADC_SampleTime_7_5Cycles: Sample time equal to 7.5 cycles
  *            @arg ADC_SampleTime_13_5Cycles: Sample time equal to 13.5 cycles
  *            @arg ADC_SampleTime_28_5Cycles: Sample time equal to 28.5 cycles
  *            @arg ADC_SampleTime_41_5Cycles: Sample time equal to 41.5 cycles
  *            @arg ADC_SampleTime_55_5Cycles: Sample time equal to 55.5 cycles
  *            @arg ADC_SampleTime_71_5Cycles: Sample time equal to 71.5 cycles
  *            @arg ADC_SampleTime_239_5Cycles: Sample time equal to 239.5 cycles
  * @retval None
  */
void ADC_ChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, uint32_t ADC_SampleTime)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

  /* Configure the ADC Channel */
  ADCx->CHSELR |= (uint32_t)ADC_Channel;

  /* Clear the Sampling time Selection bits */
  tmpreg &= ~ADC_SMPR1_SMPR;

  /* Set the ADC Sampling Time register */
  tmpreg |= (uint32_t)ADC_SampleTime;

  /* Configure the ADC Sample time register */
  ADCx->SMPR = tmpreg ;
}

/**
  * @brief  Enable the Continuous mode for the selected ADCx channels.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the Continuous mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves 
  *         as if continuous mode was disabled
  * @retval None
  */
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
  {
    /* Enable the Continuous mode*/
    ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_CONT;
  }
  else
  {
    /* Disable the Continuous mode */
    ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_CONT);
  }
}

/**
  * @brief  Enable the discontinuous mode for the selected ADC channels.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the discontinuous mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves 
  *         as if continuous mode was disabled
  * @retval None
  */
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
  {
    /* Enable the Discontinuous mode */
    ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_DISCEN;
  }
  else
  {
    /* Disable the Discontinuous mode */
    ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_DISCEN);
  }
}

/**
  * @brief  Enable the Overrun mode for the selected ADC channels.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the Overrun mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_OverrunModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
  {
    /* Enable the Overrun mode */
    ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_OVRMOD;
  }
  else
  {
    /* Disable the Overrun mode */
    ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_OVRMOD);
  }
}

/**
  * @brief  Active the Calibration operation for the selected ADC.
  * @note   The Calibration can be initiated only when ADC is still in the 
  *         reset configuration (ADEN must be equal to 0).
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval ADC Calibration factor 
  */
uint32_t ADC_GetCalibrationFactor(ADC_TypeDef* ADCx)
{
  uint32_t tmpreg = 0, calibrationcounter = 0, calibrationstatus = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  /* Set the ADC calibartion */
  ADCx->CR |= (uint32_t)ADC_CR_ADCAL;
  
  /* Wait until no ADC calibration is completed */
  do
  {
    calibrationstatus = ADCx->CR & ADC_CR_ADCAL;
    calibrationcounter++;  
  } while((calibrationcounter != CALIBRATION_TIMEOUT) && (calibrationstatus != 0x00));
    
  if((uint32_t)(ADCx->CR & ADC_CR_ADCAL) == RESET)
  {
    /*Get the calibration factor from the ADC data register */
    tmpreg = ADCx->DR;
  }
  else
  {
    /* Error factor */
    tmpreg = 0x00000000;
  }
  return tmpreg;
}

/**
  * @brief  Stop the on going conversions for the selected ADC.
  * @note   When ADSTP is set, any on going conversion is aborted, and the ADC 
  *         data register is not updated with current conversion. 
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval None
  */
void ADC_StopOfConversion(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  ADCx->CR |= (uint32_t)ADC_CR_ADSTP;
}

/**
  * @brief  Start Conversion for the selected ADC channels.
  * @note   In continuous mode, ADSTART is not cleared by hardware with the 
  *         assertion of EOSEQ because the sequence is automatic relaunched
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval None
  */
void ADC_StartOfConversion(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  ADCx->CR |= (uint32_t)ADC_CR_ADSTART;
}

/**
  * @brief  Returns the last ADCx conversion result data for ADC channel.  
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Return the selected ADC conversion value */
  return (uint16_t) ADCx->DR;
}

/**
  * @}
  */

/** @defgroup ADC_Group6 DMA Configuration functions
 *  @brief   Regular Channels DMA Configuration functions 
 *
@verbatim
 ===============================================================================
          ##### DMA Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to configure the DMA for ADC hannels.
         Since converted channel values are stored into a unique data register, 
         it is useful to use DMA for conversion of more than one channel. This 
         avoids the loss of the data already stored in the ADC Data register. 
         When the DMA mode is enabled (using the ADC_DMACmd() function), after each
         conversion of a channel, a DMA request is generated.
  
    [..] Depending on the "DMA disable selection" configuration (using the 
         ADC_DMARequestModeConfig() function), at the end of the last DMA 
         transfer, two possibilities are allowed:
         (+) No new DMA request is issued to the DMA controller (One Shot Mode) 
         (+) Requests can continue to be generated (Circular Mode).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified ADC DMA request.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  NewState: new state of the selected ADC DMA transfer.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC DMA request */
    ADCx->CFGR1 |= (uint32_t)ADC_CFGR1_DMAEN;
  }
  else
  {
    /* Disable the selected ADC DMA request */
    ADCx->CFGR1 &= (uint32_t)(~ADC_CFGR1_DMAEN);
  }
}

/**
  * @brief  Enables or disables the ADC DMA request after last transfer (Single-ADC mode)
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_DMARequestMode: the ADC channel to configure. 
  *          This parameter can be one of the following values:
  *            @arg ADC_DMAMode_OneShot: DMA One Shot Mode 
  *            @arg ADC_DMAMode_Circular: DMA Circular Mode  
  *  @retval None
  */
void ADC_DMARequestModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMARequestMode)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  ADCx->CFGR1 &= (uint32_t)~ADC_CFGR1_DMACFG;
  ADCx->CFGR1 |= (uint32_t)ADC_DMARequestMode;
}

/**
  * @}
  */

/** @defgroup ADC_Group7 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions.
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This section provides functions allowing to configure the ADC Interrupts 
         and get the status and clear flags and Interrupts pending bits.
  
    [..] The ADC provide 6 Interrupts sources and 11 Flags which can be divided into 
         3 groups:

  *** Flags for ADC status ***
  ======================================================
    [..]
        (+)Flags :
           (##) ADC_FLAG_ADRDY : This flag is set after the ADC has been enabled (bit ADEN=1)
               and when the ADC reaches a state where it is ready to accept conversion requests
           (##) ADC_FLAG_ADEN : This flag is set by software to enable the ADC.
                The ADC will be effectively ready to operate once the ADRDY flag has been set.
           (##) ADC_FLAG_ADDIS : This flag is cleared once the ADC is effectively
                disabled.
           (##) ADC_FLAG_ADSTART : This flag is cleared after the execution of
                ADC_StopOfConversion() function, at the same time as the ADSTP bit is
                cleared by hardware
           (##) ADC_FLAG_ADSTP : This flag is cleared by hardware when the conversion
                is effectively discarded and the ADC is ready to accept a new start conversion
           (##) ADC_FLAG_ADCAL : This flag is set once the calibration is complete.

        (+)Interrupts 
           (##) ADC_IT_ADRDY : specifies the interrupt source for ADC ready event.

  *** Flags and Interrupts for ADC channel conversion ***
  =====================================================
    [..]
        (+)Flags :
           (##) ADC_FLAG_EOC : This flag is set by hardware at the end of each conversion
                of a channel when a new data result is available in the data register
           (##) ADC_FLAG_EOSEQ : This bit is set by hardware at the end of the conversion
                of a sequence of channels selected by ADC_ChannelConfig() function.
           (##) ADC_FLAG_EOSMP : This bit is set by hardware at the end of the sampling phase.
           (##) ADC_FLAG_OVR : This flag is set by hardware when an overrun occurs,
                meaning that a new conversion has complete while the EOC flag was already set.

        (+)Interrupts :
           (##) ADC_IT_EOC : specifies the interrupt source for end of conversion event.
           (##) ADC_IT_EOSEQ : specifies the interrupt source for end of sequence event.
           (##) ADC_IT_EOSMP : specifies the interrupt source for end of sampling event.
           (##) ADC_IT_OVR : specifies the interrupt source for Overrun detection 
                event.

  *** Flags and Interrupts for the Analog Watchdog ***
  ================================================
    [..]
        (+)Flags :
           (##) ADC_FLAG_AWD: This flag is set by hardware when the converted
                voltage crosses the values programmed thrsholds

        (+)Interrupts :
           (##) ADC_IT_AWD : specifies the interrupt source for Analog watchdog 
                event.
  
    [..] The user should identify which mode will be used in his application to 
         manage the ADC controller events: Polling mode or Interrupt mode.
  
    [..] In the Polling Mode it is advised to use the following functions:
         (+) ADC_GetFlagStatus() : to check if flags events occur.
         (+) ADC_ClearFlag()     : to clear the flags events.
  
    [..] In the Interrupt Mode it is advised to use the following functions:
         (+) ADC_ITConfig()       : to enable or disable the interrupt source.
         (+) ADC_GetITStatus()    : to check if Interrupt occurs.
         (+) ADC_ClearITPendingBit() : to clear the Interrupt pending Bit 
             (corresponding Flag).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC ready interrupt 
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: End of conversion interrupt 
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_CONFIG_IT(ADC_IT)); 

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->IER |= ADC_IT;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->IER &= (~(uint32_t)ADC_IT);
  }
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to check. 
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_AWD: Analog watchdog flag
  *            @arg ADC_FLAG_OVR: Overrun flag 
  *            @arg ADC_FLAG_EOSEQ: End of Sequence flag
  *            @arg ADC_FLAG_EOC: End of conversion flag
  *            @arg ADC_FLAG_EOSMP: End of sampling flag
  *            @arg ADC_FLAG_ADRDY: ADC Ready flag
  *            @arg ADC_FLAG_ADEN: ADC enable flag 
  *            @arg ADC_FLAG_ADDIS: ADC disable flag 
  *            @arg ADC_FLAG_ADSTART: ADC start flag 
  *            @arg ADC_FLAG_ADSTP: ADC stop flag
  *            @arg ADC_FLAG_ADCAL: ADC Calibration flag
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

  if((uint32_t)(ADC_FLAG & 0x01000000))
  {
    tmpreg = ADCx->CR & 0xFEFFFFFF;
  }
  else
  {
    tmpreg = ADCx->ISR;
  }
  
  /* Check the status of the specified ADC flag */
  if ((tmpreg & ADC_FLAG) != (uint32_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the ADCx's pending flags.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to clear. 
  *          This parameter can be any combination of the following values:
  *            @arg ADC_FLAG_AWD: Analog watchdog flag
  *            @arg ADC_FLAG_EOC: End of conversion flag
  *            @arg ADC_FLAG_ADRDY: ADC Ready flag
  *            @arg ADC_FLAG_EOSMP: End of sampling flag
  *            @arg ADC_FLAG_EOSEQ: End of Sequence flag
  *            @arg ADC_FLAG_OVR: Overrun flag 
  * @retval None
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

  /* Clear the selected ADC flags */
  ADCx->ISR = (uint32_t)ADC_FLAG;
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral
  * @param  ADC_IT: specifies the ADC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC ready interrupt 
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: End of conversion interrupt 
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
  * @retval The new state of ADC_IT (SET or RESET).
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_IT(ADC_IT));

  /* Get the ADC_IT enable bit status */
  enablestatus = (uint32_t)(ADCx->IER & ADC_IT); 

  /* Check the status of the specified ADC interrupt */
  if (((uint32_t)(ADCx->ISR & ADC_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* ADC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the ADCx's interrupt pending bits.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_IT: specifies the ADC interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_ADRDY: ADC ready interrupt
  *            @arg ADC_IT_EOSMP: End of sampling interrupt
  *            @arg ADC_IT_EOC: End of conversion interrupt
  *            @arg ADC_IT_EOSEQ: End of sequence of conversion interrupt
  *            @arg ADC_IT_OVR: overrun interrupt
  *            @arg ADC_IT_AWD: Analog watchdog interrupt
  * @retval None
  */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_IT(ADC_IT));

  /* Clear the selected ADC interrupt pending bits */
  ADCx->ISR = (uint32_t)ADC_IT; 
}
/**
  ******************************************************************************
  * @file    stm32f0xx_can.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Controller area network (CAN) peripheral and 
  *          applicable only for STM32F072 devices :           
  *           + Initialization and Configuration 
  *           + CAN Frames Transmission 
  *           + CAN Frames Reception    
  *           + Operation modes switch  
  *           + Error management          
  *           + Interrupts and flags        
  *         
  @verbatim
                               
 ===============================================================================      
                      ##### How to use this driver #####
 ===============================================================================                
    [..]
    (#) Enable the CAN controller interface clock using 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);      
    (#) CAN pins configuration:
        (++) Enable the clock for the CAN GPIOs using the following function:
             RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);   
        (++) Connect the involved CAN pins to AF0 using the following function 
             GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_CANx); 
        (++) Configure these CAN pins in alternate function mode by calling
             the function  GPIO_Init();
    (#) Initialise and configure the CAN using CAN_Init() and 
        CAN_FilterInit() functions.   
    (#) Transmit the desired CAN frame using CAN_Transmit() function.
    (#) Check the transmission of a CAN frame using CAN_TransmitStatus() function.
    (#) Cancel the transmission of a CAN frame using CAN_CancelTransmit() function.  
    (#) Receive a CAN frame using CAN_Recieve() function.
    (#) Release the receive FIFOs using CAN_FIFORelease() function.
    (#) Return the number of pending received frames using CAN_MessagePending() function.            
    (#) To control CAN events you can use one of the following two methods:
        (++) Check on CAN flags using the CAN_GetFlagStatus() function.  
        (++) Use CAN interrupts through the function CAN_ITConfig() at initialization 
             phase and CAN_GetITStatus() function into interrupt routines to check 
             if the event has occurred or not.
             After checking on a flag you should clear it using CAN_ClearFlag()
             function. And after checking on an interrupt event you should clear it 
             using CAN_ClearITPendingBit() function.            
                 
  @endverbatim
  *       
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

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CAN 
  * @brief CAN driver modules
  * @{
  */ 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* CAN Master Control Register bits */
#define MCR_DBF           ((uint32_t)0x00010000) /* software master reset */

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ       ((uint32_t)0x00000001) /* Transmit mailbox request */

/* CAN Filter Master Register bits */
#define FMR_FINIT         ((uint32_t)0x00000001) /* Filter init mode */

/* Time out for INAK bit */
#define INAK_TIMEOUT      ((uint32_t)0x00FFFFFF)
/* Time out for SLAK bit */
#define SLAK_TIMEOUT      ((uint32_t)0x00FFFFFF)

/* Flags in TSR register */
#define CAN_FLAGS_TSR     ((uint32_t)0x08000000) 
/* Flags in RF1R register */
#define CAN_FLAGS_RF1R    ((uint32_t)0x04000000) 
/* Flags in RF0R register */
#define CAN_FLAGS_RF0R    ((uint32_t)0x02000000) 
/* Flags in MSR register */
#define CAN_FLAGS_MSR     ((uint32_t)0x01000000) 
/* Flags in ESR register */
#define CAN_FLAGS_ESR     ((uint32_t)0x00F00000) 

/* Mailboxes definition */
#define CAN_TXMAILBOX_0   ((uint8_t)0x00)
#define CAN_TXMAILBOX_1   ((uint8_t)0x01)
#define CAN_TXMAILBOX_2   ((uint8_t)0x02) 

#define CAN_MODE_MASK     ((uint32_t) 0x00000003)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static ITStatus CheckITStatus(uint32_t CAN_Reg, uint32_t It_Bit);

/** @defgroup CAN_Private_Functions
  * @{
  */

/** @defgroup CAN_Group1 Initialization and Configuration functions
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..] This section provides functions allowing to: 
         (+) Initialize the CAN peripherals : Prescaler, operating mode, the maximum 
             number of time quanta to perform resynchronization, the number of time 
             quanta in Bit Segment 1 and 2 and many other modes. 
         (+) Configure the CAN reception filter.                                      
         (+) Select the start bank filter for slave CAN.
         (+) Enable or disable the Debug Freeze mode for CAN.
         (+) Enable or disable the CAN Time Trigger Operation communication mode.
   
@endverbatim
  * @{
  */
  
/**
  * @brief  Deinitializes the CAN peripheral registers to their default reset values.
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_DeInit(CAN_TypeDef* CANx)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
 
  /* Enable CAN reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN, ENABLE);
  /* Release CAN from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN, DISABLE);
}

/**
  * @brief  Initializes the CAN peripheral according to the specified
  *         parameters in the CAN_InitStruct.
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @param  CAN_InitStruct: pointer to a CAN_InitTypeDef structure that contains
  *         the configuration information for the CAN peripheral.
  * @retval Constant indicates initialization succeed which will be 
  *         CAN_InitStatus_Failed or CAN_InitStatus_Success.
  */
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct)
{
  uint8_t InitStatus = CAN_InitStatus_Failed;
  uint32_t wait_ack = 0x00000000;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TTCM));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_ABOM));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_AWUM));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_NART));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_RFLM));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TXFP));
  assert_param(IS_CAN_MODE(CAN_InitStruct->CAN_Mode));
  assert_param(IS_CAN_SJW(CAN_InitStruct->CAN_SJW));
  assert_param(IS_CAN_BS1(CAN_InitStruct->CAN_BS1));
  assert_param(IS_CAN_BS2(CAN_InitStruct->CAN_BS2));
  assert_param(IS_CAN_PRESCALER(CAN_InitStruct->CAN_Prescaler));

  /* Exit from sleep mode */
  CANx->MCR &= (~(uint32_t)CAN_MCR_SLEEP);

  /* Request initialisation */
  CANx->MCR |= CAN_MCR_INRQ ;

  /* Wait the acknowledge */
  while (((CANx->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) && (wait_ack != INAK_TIMEOUT))
  {
    wait_ack++;
  }

  /* Check acknowledge */
  if ((CANx->MSR & CAN_MSR_INAK) != CAN_MSR_INAK)
  {
    InitStatus = CAN_InitStatus_Failed;
  }
  else 
  {
    /* Set the time triggered communication mode */
    if (CAN_InitStruct->CAN_TTCM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_TTCM;
    }
    else
    {
      CANx->MCR &= ~(uint32_t)CAN_MCR_TTCM;
    }

    /* Set the automatic bus-off management */
    if (CAN_InitStruct->CAN_ABOM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_ABOM;
    }
    else
    {
      CANx->MCR &= ~(uint32_t)CAN_MCR_ABOM;
    }

    /* Set the automatic wake-up mode */
    if (CAN_InitStruct->CAN_AWUM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_AWUM;
    }
    else
    {
      CANx->MCR &= ~(uint32_t)CAN_MCR_AWUM;
    }

    /* Set the no automatic retransmission */
    if (CAN_InitStruct->CAN_NART == ENABLE)
    {
      CANx->MCR |= CAN_MCR_NART;
    }
    else
    {
      CANx->MCR &= ~(uint32_t)CAN_MCR_NART;
    }

    /* Set the receive FIFO locked mode */
    if (CAN_InitStruct->CAN_RFLM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_RFLM;
    }
    else
    {
      CANx->MCR &= ~(uint32_t)CAN_MCR_RFLM;
    }

    /* Set the transmit FIFO priority */
    if (CAN_InitStruct->CAN_TXFP == ENABLE)
    {
      CANx->MCR |= CAN_MCR_TXFP;
    }
    else
    {
      CANx->MCR &= ~(uint32_t)CAN_MCR_TXFP;
    }

    /* Set the bit timing register */
    CANx->BTR = (uint32_t)((uint32_t)CAN_InitStruct->CAN_Mode << 30) | \
                ((uint32_t)CAN_InitStruct->CAN_SJW << 24) | \
                ((uint32_t)CAN_InitStruct->CAN_BS1 << 16) | \
                ((uint32_t)CAN_InitStruct->CAN_BS2 << 20) | \
               ((uint32_t)CAN_InitStruct->CAN_Prescaler - 1);

    /* Request leave initialisation */
    CANx->MCR &= ~(uint32_t)CAN_MCR_INRQ;

   /* Wait the acknowledge */
   wait_ack = 0;

   while (((CANx->MSR & CAN_MSR_INAK) == (uint16_t)CAN_MSR_INAK) && (wait_ack != INAK_TIMEOUT))
   {
     wait_ack++;
   }

    /* ...and check acknowledged */
    if ((CANx->MSR & CAN_MSR_INAK) == CAN_MSR_INAK)
    {
      InitStatus = CAN_InitStatus_Failed;
    }
    else
    {
      InitStatus = CAN_InitStatus_Success ;
    }
  }

  /* At this step, return the status of initialization */
  return InitStatus;
}

/**
  * @brief  Configures the CAN reception filter according to the specified
  *         parameters in the CAN_FilterInitStruct.
  * @param  CAN_FilterInitStruct: pointer to a CAN_FilterInitTypeDef structure that
  *         contains the configuration information.
  * @retval None
  */
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{
  uint32_t filter_number_bit_pos = 0;
  /* Check the parameters */
  assert_param(IS_CAN_FILTER_NUMBER(CAN_FilterInitStruct->CAN_FilterNumber));
  assert_param(IS_CAN_FILTER_MODE(CAN_FilterInitStruct->CAN_FilterMode));
  assert_param(IS_CAN_FILTER_SCALE(CAN_FilterInitStruct->CAN_FilterScale));
  assert_param(IS_CAN_FILTER_FIFO(CAN_FilterInitStruct->CAN_FilterFIFOAssignment));
  assert_param(IS_FUNCTIONAL_STATE(CAN_FilterInitStruct->CAN_FilterActivation));

  filter_number_bit_pos = ((uint32_t)1) << CAN_FilterInitStruct->CAN_FilterNumber;

  /* Initialisation mode for the filter */
  CAN->FMR |= FMR_FINIT;

  /* Filter Deactivation */
  CAN->FA1R &= ~(uint32_t)filter_number_bit_pos;

  /* Filter Scale */
  if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_16bit)
  {
    /* 16-bit scale for the filter */
    CAN->FS1R &= ~(uint32_t)filter_number_bit_pos;

    /* First 16-bit identifier and First 16-bit mask */
    /* Or First 16-bit identifier and Second 16-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 = 
       ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdLow) << 16) |
        (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);

    /* Second 16-bit identifier and Second 16-bit mask */
    /* Or Third 16-bit identifier and Fourth 16-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 = 
       ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
        (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh);
  }

  if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_32bit)
  {
    /* 32-bit scale for the filter */
    CAN->FS1R |= filter_number_bit_pos;
    /* 32-bit identifier or First 32-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 = 
       ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh) << 16) |
        (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);
    /* 32-bit mask or Second 32-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 = 
       ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
        (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdLow);
  }

  /* Filter Mode */
  if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
  {
    /*Id/Mask mode for the filter*/
    CAN->FM1R &= ~(uint32_t)filter_number_bit_pos;
  }
  else /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
  {
    /*Identifier list mode for the filter*/
    CAN->FM1R |= (uint32_t)filter_number_bit_pos;
  }

  /* Filter FIFO assignment */
  if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO0)
  {
    /* FIFO 0 assignation for the filter */
    CAN->FFA1R &= ~(uint32_t)filter_number_bit_pos;
  }

  if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO1)
  {
    /* FIFO 1 assignation for the filter */
    CAN->FFA1R |= (uint32_t)filter_number_bit_pos;
  }
  
  /* Filter activation */
  if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE)
  {
    CAN->FA1R |= filter_number_bit_pos;
  }

  /* Leave the initialisation mode for the filter */
  CAN->FMR &= ~FMR_FINIT;
}

/**
  * @brief  Fills each CAN_InitStruct member with its default value.
  * @param  CAN_InitStruct: pointer to a CAN_InitTypeDef structure which ill be initialized.
  * @retval None
  */
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct)
{
  /* Reset CAN init structure parameters values */
  
  /* Initialize the time triggered communication mode */
  CAN_InitStruct->CAN_TTCM = DISABLE;
  
  /* Initialize the automatic bus-off management */
  CAN_InitStruct->CAN_ABOM = DISABLE;
  
  /* Initialize the automatic wake-up mode */
  CAN_InitStruct->CAN_AWUM = DISABLE;
  
  /* Initialize the no automatic retransmission */
  CAN_InitStruct->CAN_NART = DISABLE;
  
  /* Initialize the receive FIFO locked mode */
  CAN_InitStruct->CAN_RFLM = DISABLE;
  
  /* Initialize the transmit FIFO priority */
  CAN_InitStruct->CAN_TXFP = DISABLE;
  
  /* Initialize the CAN_Mode member */
  CAN_InitStruct->CAN_Mode = CAN_Mode_Normal;
  
  /* Initialize the CAN_SJW member */
  CAN_InitStruct->CAN_SJW = CAN_SJW_1tq;
  
  /* Initialize the CAN_BS1 member */
  CAN_InitStruct->CAN_BS1 = CAN_BS1_4tq;
  
  /* Initialize the CAN_BS2 member */
  CAN_InitStruct->CAN_BS2 = CAN_BS2_3tq;
  
  /* Initialize the CAN_Prescaler member */
  CAN_InitStruct->CAN_Prescaler = 1;
}

/**
  * @brief  Select the start bank filter for slave CAN.
  * @param  CAN_BankNumber: Select the start slave bank filter from 1..27.
  * @retval None
  */
void CAN_SlaveStartBank(uint8_t CAN_BankNumber) 
{
  /* Check the parameters */
  assert_param(IS_CAN_BANKNUMBER(CAN_BankNumber));
  
  /* Enter Initialisation mode for the filter */
  CAN->FMR |= FMR_FINIT;
  
  /* Select the start slave bank */
  CAN->FMR &= (uint32_t)0xFFFFC0F1 ;
  CAN->FMR |= (uint32_t)(CAN_BankNumber)<<8;
  
  /* Leave Initialisation mode for the filter */
  CAN->FMR &= ~FMR_FINIT;
}

/**
  * @brief  Enables or disables the DBG Freeze for CAN.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  NewState: new state of the CAN peripheral. 
  *          This parameter can be: ENABLE (CAN reception/transmission is frozen
  *          during debug. Reception FIFOs can still be accessed/controlled normally) 
  *          or DISABLE (CAN is working during debug).
  * @retval None
  */
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Debug Freeze  */
    CANx->MCR |= MCR_DBF;
  }
  else
  {
    /* Disable Debug Freeze */
    CANx->MCR &= ~MCR_DBF;
  }
}

/**
  * @brief  Enables or disables the CAN Time TriggerOperation communication mode.
  * @note   DLC must be programmed as 8 in order Time Stamp (2 bytes) to be 
  *         sent over the CAN bus.  
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  NewState: Mode new state. This parameter can be: ENABLE or DISABLE.
  *         When enabled, Time stamp (TIME[15:0]) value is  sent in the last two
  *         data bytes of the 8-byte message: TIME[7:0] in data byte 6 and TIME[15:8] 
  *         in data byte 7. 
  * @retval None
  */
void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the TTCM mode */
    CANx->MCR |= CAN_MCR_TTCM;

    /* Set TGT bits */
    CANx->sTxMailBox[0].TDTR |= ((uint32_t)CAN_TDT0R_TGT);
    CANx->sTxMailBox[1].TDTR |= ((uint32_t)CAN_TDT1R_TGT);
    CANx->sTxMailBox[2].TDTR |= ((uint32_t)CAN_TDT2R_TGT);
  }
  else
  {
    /* Disable the TTCM mode */
    CANx->MCR &= (uint32_t)(~(uint32_t)CAN_MCR_TTCM);

    /* Reset TGT bits */
    CANx->sTxMailBox[0].TDTR &= ((uint32_t)~CAN_TDT0R_TGT);
    CANx->sTxMailBox[1].TDTR &= ((uint32_t)~CAN_TDT1R_TGT);
    CANx->sTxMailBox[2].TDTR &= ((uint32_t)~CAN_TDT2R_TGT);
  }
}
/**
  * @}
  */


/** @defgroup CAN_Group2 CAN Frames Transmission functions
 *  @brief    CAN Frames Transmission functions 
 *
@verbatim    
 ===============================================================================
                ##### CAN Frames Transmission functions #####
 ===============================================================================  
    [..] This section provides functions allowing to 
         (+) Initiate and transmit a CAN frame message (if there is an empty mailbox).
         (+) Check the transmission status of a CAN Frame.
         (+) Cancel a transmit request.
   
@endverbatim
  * @{
  */

/**
  * @brief  Initiates and transmits a CAN frame message.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  TxMessage: pointer to a structure which contains CAN Id, CAN DLC and CAN data.
  * @retval The number of the mailbox that is used for transmission or
  *         CAN_TxStatus_NoMailBox if there is no empty mailbox.
  */
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{
  uint8_t transmit_mailbox = 0;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_IDTYPE(TxMessage->IDE));
  assert_param(IS_CAN_RTR(TxMessage->RTR));
  assert_param(IS_CAN_DLC(TxMessage->DLC));

  /* Select one empty transmit mailbox */
  if ((CANx->TSR&CAN_TSR_TME0) == CAN_TSR_TME0)
  {
    transmit_mailbox = 0;
  }
  else if ((CANx->TSR&CAN_TSR_TME1) == CAN_TSR_TME1)
  {
    transmit_mailbox = 1;
  }
  else if ((CANx->TSR&CAN_TSR_TME2) == CAN_TSR_TME2)
  {
    transmit_mailbox = 2;
  }
  else
  {
    transmit_mailbox = CAN_TxStatus_NoMailBox;
  }

  if (transmit_mailbox != CAN_TxStatus_NoMailBox)
  {
    /* Set up the Id */
    CANx->sTxMailBox[transmit_mailbox].TIR &= TMIDxR_TXRQ;
    if (TxMessage->IDE == CAN_Id_Standard)
    {
      assert_param(IS_CAN_STDID(TxMessage->StdId));  
      CANx->sTxMailBox[transmit_mailbox].TIR |= ((TxMessage->StdId << 21) | \
                                                  TxMessage->RTR);
    }
    else
    {
      assert_param(IS_CAN_EXTID(TxMessage->ExtId));
      CANx->sTxMailBox[transmit_mailbox].TIR |= ((TxMessage->ExtId << 3) | \
                                                  TxMessage->IDE | \
                                                  TxMessage->RTR);
    }
    
    /* Set up the DLC */
    TxMessage->DLC &= (uint8_t)0x0000000F;
    CANx->sTxMailBox[transmit_mailbox].TDTR &= (uint32_t)0xFFFFFFF0;
    CANx->sTxMailBox[transmit_mailbox].TDTR |= TxMessage->DLC;

    /* Set up the data field */
    CANx->sTxMailBox[transmit_mailbox].TDLR = (((uint32_t)TxMessage->Data[3] << 24) | 
                                             ((uint32_t)TxMessage->Data[2] << 16) |
                                             ((uint32_t)TxMessage->Data[1] << 8) | 
                                             ((uint32_t)TxMessage->Data[0]));
    CANx->sTxMailBox[transmit_mailbox].TDHR = (((uint32_t)TxMessage->Data[7] << 24) | 
                                             ((uint32_t)TxMessage->Data[6] << 16) |
                                             ((uint32_t)TxMessage->Data[5] << 8) |
                                             ((uint32_t)TxMessage->Data[4]));
    /* Request transmission */
    CANx->sTxMailBox[transmit_mailbox].TIR |= TMIDxR_TXRQ;
  }
  return transmit_mailbox;
}

/**
  * @brief  Checks the transmission status of a CAN Frame.
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @param  TransmitMailbox: the number of the mailbox that is used for transmission.
  * @retval CAN_TxStatus_Ok if the CAN driver transmits the message, 
  *         CAN_TxStatus_Failed in an other case.
  */
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox)
{
  uint32_t state = 0;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_TRANSMITMAILBOX(TransmitMailbox));
 
  switch (TransmitMailbox)
  {
    case (CAN_TXMAILBOX_0): 
      state =   CANx->TSR &  (CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_TME0);
      break;
    case (CAN_TXMAILBOX_1): 
      state =   CANx->TSR &  (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_TME1);
      break;
    case (CAN_TXMAILBOX_2): 
      state =   CANx->TSR &  (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_TME2);
      break;
    default:
      state = CAN_TxStatus_Failed;
      break;
  }
  switch (state)
  {
      /* transmit pending  */
    case (0x0): state = CAN_TxStatus_Pending;
      break;
      /* transmit failed  */
     case (CAN_TSR_RQCP0 | CAN_TSR_TME0): state = CAN_TxStatus_Failed;
      break;
     case (CAN_TSR_RQCP1 | CAN_TSR_TME1): state = CAN_TxStatus_Failed;
      break;
     case (CAN_TSR_RQCP2 | CAN_TSR_TME2): state = CAN_TxStatus_Failed;
      break;
      /* transmit succeeded  */
    case (CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_TME0):state = CAN_TxStatus_Ok;
      break;
    case (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_TME1):state = CAN_TxStatus_Ok;
      break;
    case (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_TME2):state = CAN_TxStatus_Ok;
      break;
    default: state = CAN_TxStatus_Failed;
      break;
  }
  return (uint8_t) state;
}

/**
  * @brief  Cancels a transmit request.
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @param  Mailbox: Mailbox number.
  * @retval None
  */
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_TRANSMITMAILBOX(Mailbox));
  /* abort transmission */
  switch (Mailbox)
  {
    case (CAN_TXMAILBOX_0): CANx->TSR |= CAN_TSR_ABRQ0;
      break;
    case (CAN_TXMAILBOX_1): CANx->TSR |= CAN_TSR_ABRQ1;
      break;
    case (CAN_TXMAILBOX_2): CANx->TSR |= CAN_TSR_ABRQ2;
      break;
    default:
      break;
  }
}
/**
  * @}
  */


/** @defgroup CAN_Group3 CAN Frames Reception functions
 *  @brief    CAN Frames Reception functions 
 *
@verbatim    
 ===============================================================================
                  ##### CAN Frames Reception functions #####
 ===============================================================================  
    [..] This section provides functions allowing to 
         (+) Receive a correct CAN frame.
         (+) Release a specified receive FIFO (2 FIFOs are available).
         (+) Return the number of the pending received CAN frames.
   
@endverbatim
  * @{
  */

/**
  * @brief  Receives a correct CAN frame.
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @param  FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @param  RxMessage: pointer to a structure receive frame which contains CAN Id,
  *         CAN DLC, CAN data and FMI number.
  * @retval None
  */
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_FIFO(FIFONumber));
  /* Get the Id */
  RxMessage->IDE = (uint8_t)0x04 & CANx->sFIFOMailBox[FIFONumber].RIR;
  if (RxMessage->IDE == CAN_Id_Standard)
  {
    RxMessage->StdId = (uint32_t)0x000007FF & (CANx->sFIFOMailBox[FIFONumber].RIR >> 21);
  }
  else
  {
    RxMessage->ExtId = (uint32_t)0x1FFFFFFF & (CANx->sFIFOMailBox[FIFONumber].RIR >> 3);
  }
  
  RxMessage->RTR = (uint8_t)0x02 & CANx->sFIFOMailBox[FIFONumber].RIR;
  /* Get the DLC */
  RxMessage->DLC = (uint8_t)0x0F & CANx->sFIFOMailBox[FIFONumber].RDTR;
  /* Get the FMI */
  RxMessage->FMI = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDTR >> 8);
  /* Get the data field */
  RxMessage->Data[0] = (uint8_t)0xFF & CANx->sFIFOMailBox[FIFONumber].RDLR;
  RxMessage->Data[1] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 8);
  RxMessage->Data[2] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 16);
  RxMessage->Data[3] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 24);
  RxMessage->Data[4] = (uint8_t)0xFF & CANx->sFIFOMailBox[FIFONumber].RDHR;
  RxMessage->Data[5] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 8);
  RxMessage->Data[6] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 16);
  RxMessage->Data[7] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 24);
  /* Release the FIFO */
  /* Release FIFO0 */
  if (FIFONumber == CAN_FIFO0)
  {
    CANx->RF0R |= CAN_RF0R_RFOM0;
  }
  /* Release FIFO1 */
  else /* FIFONumber == CAN_FIFO1 */
  {
    CANx->RF1R |= CAN_RF1R_RFOM1;
  }
}

/**
  * @brief  Releases the specified receive FIFO.
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @param  FIFONumber: FIFO to release, CAN_FIFO0 or CAN_FIFO1.
  * @retval None
  */
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_FIFO(FIFONumber));
  /* Release FIFO0 */
  if (FIFONumber == CAN_FIFO0)
  {
    CANx->RF0R |= CAN_RF0R_RFOM0;
  }
  /* Release FIFO1 */
  else /* FIFONumber == CAN_FIFO1 */
  {
    CANx->RF1R |= CAN_RF1R_RFOM1;
  }
}

/**
  * @brief  Returns the number of pending received messages.
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @param  FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @retval NbMessage : which is the number of pending message.
  */
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber)
{
  uint8_t message_pending=0;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_FIFO(FIFONumber));
  if (FIFONumber == CAN_FIFO0)
  {
    message_pending = (uint8_t)(CANx->RF0R&(uint32_t)0x03);
  }
  else if (FIFONumber == CAN_FIFO1)
  {
    message_pending = (uint8_t)(CANx->RF1R&(uint32_t)0x03);
  }
  else
  {
    message_pending = 0;
  }
  return message_pending;
}
/**
  * @}
  */


/** @defgroup CAN_Group4 CAN Operation modes functions
 *  @brief    CAN Operation modes functions 
 *
@verbatim    
 ===============================================================================
                    ##### CAN Operation modes functions #####
 ===============================================================================  
    [..] This section provides functions allowing to select the CAN Operation modes:
         (+) sleep mode.
         (+) normal mode. 
         (+) initialization mode.
   
@endverbatim
  * @{
  */
  
  
/**
  * @brief  Selects the CAN Operation mode.
  * @param  CAN_OperatingMode: CAN Operating Mode.
  *         This parameter can be one of @ref CAN_OperatingMode_TypeDef enumeration.
  * @retval status of the requested mode which can be: 
  *         - CAN_ModeStatus_Failed:  CAN failed entering the specific mode 
  *         - CAN_ModeStatus_Success: CAN Succeed entering the specific mode 
  */
uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode)
{
  uint8_t status = CAN_ModeStatus_Failed;
  
  /* Timeout for INAK or also for SLAK bits*/
  uint32_t timeout = INAK_TIMEOUT; 

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_OPERATING_MODE(CAN_OperatingMode));

  if (CAN_OperatingMode == CAN_OperatingMode_Initialization)
  {
    /* Request initialisation */
    CANx->MCR = (uint32_t)((CANx->MCR & (uint32_t)(~(uint32_t)CAN_MCR_SLEEP)) | CAN_MCR_INRQ);

    /* Wait the acknowledge */
    while (((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_INAK) && (timeout != 0))
    {
      timeout--;
    }
    if ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_INAK)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else  if (CAN_OperatingMode == CAN_OperatingMode_Normal)
  {
    /* Request leave initialisation and sleep mode  and enter Normal mode */
    CANx->MCR &= (uint32_t)(~(CAN_MCR_SLEEP|CAN_MCR_INRQ));

    /* Wait the acknowledge */
    while (((CANx->MSR & CAN_MODE_MASK) != 0) && (timeout!=0))
    {
      timeout--;
    }
    if ((CANx->MSR & CAN_MODE_MASK) != 0)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else  if (CAN_OperatingMode == CAN_OperatingMode_Sleep)
  {
    /* Request Sleep mode */
    CANx->MCR = (uint32_t)((CANx->MCR & (uint32_t)(~(uint32_t)CAN_MCR_INRQ)) | CAN_MCR_SLEEP);

    /* Wait the acknowledge */
    while (((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_SLAK) && (timeout!=0))
    {
      timeout--;
    }
    if ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_SLAK)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else
  {
    status = CAN_ModeStatus_Failed;
  }

  return  (uint8_t) status;
}

/**
  * @brief  Enters the Sleep (low power) mode.
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @retval CAN_Sleep_Ok if sleep entered, CAN_Sleep_Failed otherwise.
  */
uint8_t CAN_Sleep(CAN_TypeDef* CANx)
{
  uint8_t sleepstatus = CAN_Sleep_Failed;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
    
  /* Request Sleep mode */
   CANx->MCR = (((CANx->MCR) & (uint32_t)(~(uint32_t)CAN_MCR_INRQ)) | CAN_MCR_SLEEP);
   
  /* Sleep mode status */
  if ((CANx->MSR & (CAN_MSR_SLAK|CAN_MSR_INAK)) == CAN_MSR_SLAK)
  {
    /* Sleep mode not entered */
    sleepstatus =  CAN_Sleep_Ok;
  }
  /* return sleep mode status */
   return (uint8_t)sleepstatus;
}

/**
  * @brief  Wakes up the CAN peripheral from sleep mode .
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @retval CAN_WakeUp_Ok if sleep mode left, CAN_WakeUp_Failed otherwise.
  */
uint8_t CAN_WakeUp(CAN_TypeDef* CANx)
{
  uint32_t wait_slak = SLAK_TIMEOUT;
  uint8_t wakeupstatus = CAN_WakeUp_Failed;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
    
  /* Wake up request */
  CANx->MCR &= ~(uint32_t)CAN_MCR_SLEEP;
    
  /* Sleep mode status */
  while(((CANx->MSR & CAN_MSR_SLAK) == CAN_MSR_SLAK)&&(wait_slak!=0x00))
  {
   wait_slak--;
  }
  if((CANx->MSR & CAN_MSR_SLAK) != CAN_MSR_SLAK)
  {
   /* wake up done : Sleep mode exited */
    wakeupstatus = CAN_WakeUp_Ok;
  }
  /* return wakeup status */
  return (uint8_t)wakeupstatus;
}
/**
  * @}
  */


/** @defgroup CAN_Group5 CAN Bus Error management functions
 *  @brief    CAN Bus Error management functions 
 *
@verbatim    
 ===============================================================================
                  ##### CAN Bus Error management functions #####
 ===============================================================================  
    [..] This section provides functions allowing to 
         (+) Return the CANx's last error code (LEC).
         (+) Return the CANx Receive Error Counter (REC).
         (+) Return the LSB of the 9-bit CANx Transmit Error Counter(TEC).
    [..]
         (@) If TEC is greater than 255, The CAN is in bus-off state.
         (@) If REC or TEC are greater than 96, an Error warning flag occurs.
         (@) If REC or TEC are greater than 127, an Error Passive Flag occurs.
                        
@endverbatim
  * @{
  */
  
/**
  * @brief  Returns the CANx's last error code (LEC).
  * @param  CANx: where x can be 1 to select the CAN peripheral.
  * @retval Error code: 
  *          - CAN_ERRORCODE_NoErr: No Error  
  *          - CAN_ERRORCODE_StuffErr: Stuff Error
  *          - CAN_ERRORCODE_FormErr: Form Error
  *          - CAN_ERRORCODE_ACKErr : Acknowledgment Error
  *          - CAN_ERRORCODE_BitRecessiveErr: Bit Recessive Error
  *          - CAN_ERRORCODE_BitDominantErr: Bit Dominant Error
  *          - CAN_ERRORCODE_CRCErr: CRC Error
  *          - CAN_ERRORCODE_SoftwareSetErr: Software Set Error  
  */
uint8_t CAN_GetLastErrorCode(CAN_TypeDef* CANx)
{
  uint8_t errorcode=0;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  
  /* Get the error code*/
  errorcode = (((uint8_t)CANx->ESR) & (uint8_t)CAN_ESR_LEC);
  
  /* Return the error code*/
  return errorcode;
}

/**
  * @brief  Returns the CANx Receive Error Counter (REC).
  * @note   In case of an error during reception, this counter is incremented 
  *         by 1 or by 8 depending on the error condition as defined by the CAN 
  *         standard. After every successful reception, the counter is 
  *         decremented by 1 or reset to 120 if its value was higher than 128. 
  *         When the counter value exceeds 127, the CAN controller enters the 
  *         error passive state.  
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.  
  * @retval CAN Receive Error Counter. 
  */
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef* CANx)
{
  uint8_t counter=0;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  
  /* Get the Receive Error Counter*/
  counter = (uint8_t)((CANx->ESR & CAN_ESR_REC)>> 24);
  
  /* Return the Receive Error Counter*/
  return counter;
}


/**
  * @brief  Returns the LSB of the 9-bit CANx Transmit Error Counter(TEC).
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @retval LSB of the 9-bit CAN Transmit Error Counter. 
  */
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx)
{
  uint8_t counter=0;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  
  /* Get the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
  counter = (uint8_t)((CANx->ESR & CAN_ESR_TEC)>> 16);
  
  /* Return the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
  return counter;
}
/**
  * @}
  */

/** @defgroup CAN_Group6 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
              ##### Interrupts and flags management functions #####
 ===============================================================================  
    [..] This section provides functions allowing to configure the CAN Interrupts 
         and to get the status and clear flags and Interrupts pending bits.
    [..] The CAN provides 14 Interrupts sources and 15 Flags:
   
  *** Flags ***
  =============
    [..] The 15 flags can be divided on 4 groups: 
         (+) Transmit Flags:
             (++) CAN_FLAG_RQCP0. 
             (++) CAN_FLAG_RQCP1. 
             (++) CAN_FLAG_RQCP2: Request completed MailBoxes 0, 1 and 2  Flags
                  Set when when the last request (transmit or abort) has 
                  been performed. 
         (+) Receive Flags:
             (++) CAN_FLAG_FMP0.
             (++) CAN_FLAG_FMP1: FIFO 0 and 1 Message Pending Flags; 
                  Set to signal that messages are pending in the receive FIFO.
                  These Flags are cleared only by hardware. 
             (++) CAN_FLAG_FF0.
             (++) CAN_FLAG_FF1: FIFO 0 and 1 Full Flags; 
                  Set when three messages are stored in the selected FIFO.                        
             (++) CAN_FLAG_FOV0.              
             (++) CAN_FLAG_FOV1: FIFO 0 and 1 Overrun Flags; 
                  Set when a new message has been received and passed the filter 
                  while the FIFO was full.         
         (+) Operating Mode Flags: 
             (++) CAN_FLAG_WKU: Wake up Flag; 
                  Set to signal that a SOF bit has been detected while the CAN 
                  hardware was in Sleep mode. 
             (++) CAN_FLAG_SLAK: Sleep acknowledge Flag;
                  Set to signal that the CAN has entered Sleep Mode. 
         (+) Error Flags:  
             (++) CAN_FLAG_EWG: Error Warning Flag;
                  Set when the warning limit has been reached (Receive Error Counter 
                  or Transmit Error Counter greater than 96). 
                  This Flag is cleared only by hardware.
             (++) CAN_FLAG_EPV: Error Passive Flag;
                  Set when the Error Passive limit has been reached (Receive Error 
                  Counter or Transmit Error Counter greater than 127).
                  This Flag is cleared only by hardware.
             (++) CAN_FLAG_BOF: Bus-Off Flag;
                  Set when CAN enters the bus-off state. The bus-off state is 
                  entered on TEC overflow, greater than 255.
                  This Flag is cleared only by hardware.
             (++) CAN_FLAG_LEC: Last error code Flag;
                  Set If a message has been transferred (reception or transmission) 
                  with error, and the error code is hold.                      
  
  *** Interrupts ***
  ==================
    [..] The 14 interrupts can be divided on 4 groups: 
         (+) Transmit interrupt:   
             (++) CAN_IT_TME: Transmit mailbox empty Interrupt;
                  If enabled, this interrupt source is pending when no transmit 
                  request are pending for Tx mailboxes.      
         (+) Receive Interrupts:   
             (++) CAN_IT_FMP0.
             (++) CAN_IT_FMP1: FIFO 0 and FIFO1 message pending Interrupts;
                  If enabled, these interrupt sources are pending when messages 
                  are pending in the receive FIFO.
                  The corresponding interrupt pending bits are cleared only by hardware.
             (++) CAN_IT_FF0.              
             (++) CAN_IT_FF1: FIFO 0 and FIFO1 full Interrupts;
                  If enabled, these interrupt sources are pending when three messages 
                  are stored in the selected FIFO.
             (++) CAN_IT_FOV0.        
             (++) CAN_IT_FOV1: FIFO 0 and FIFO1 overrun Interrupts;        
                  If enabled, these interrupt sources are pending when a new message 
                  has been received and passed the filter while the FIFO was full.
         (+) Operating Mode Interrupts:    
             (++) CAN_IT_WKU: Wake-up Interrupt;
                  If enabled, this interrupt source is pending when a SOF bit has 
                  been detected while the CAN hardware was in Sleep mode.
             (++) CAN_IT_SLK: Sleep acknowledge Interrupt:
                  If enabled, this interrupt source is pending when the CAN has 
                  entered Sleep Mode.       
         (+) Error Interrupts:     
             (++) CAN_IT_EWG: Error warning Interrupt; 
                  If enabled, this interrupt source is pending when the warning limit 
                  has been reached (Receive Error Counter or Transmit Error Counter=96). 
             (++) CAN_IT_EPV: Error passive Interrupt;        
                  If enabled, this interrupt source is pending when the Error Passive 
                  limit has been reached (Receive Error Counter or Transmit Error Counter>127).
             (++) CAN_IT_BOF: Bus-off Interrupt;
                  If enabled, this interrupt source is pending when CAN enters 
                  the bus-off state. The bus-off state is entered on TEC overflow, 
                  greater than 255.
                  This Flag is cleared only by hardware.
             (++) CAN_IT_LEC: Last error code Interrupt;        
                  If enabled, this interrupt source is pending when a message has 
                  been transferred (reception or transmission) with error and the 
                  error code is hold.
             (++) CAN_IT_ERR: Error Interrupt;
                  If enabled, this interrupt source is pending when an error condition 
                  is pending.      
    [..] Managing the CAN controller events: 
         The user should identify which mode will be used in his application to manage 
         the CAN controller events: Polling mode or Interrupt mode.
         (+) In the Polling Mode it is advised to use the following functions:
             (++) CAN_GetFlagStatus() : to check if flags events occur. 
             (++) CAN_ClearFlag()     : to clear the flags events.
         (+) In the Interrupt Mode it is advised to use the following functions:
             (++) CAN_ITConfig()       : to enable or disable the interrupt source.
             (++) CAN_GetITStatus()    : to check if Interrupt occurs.
             (++) CAN_ClearITPendingBit() : to clear the Interrupt pending Bit 
                  (corresponding Flag).
                  This function has no impact on CAN_IT_FMP0 and CAN_IT_FMP1 Interrupts 
                  pending bits since there are cleared only by hardware. 
  
@endverbatim
  * @{
  */ 
/**
  * @brief  Enables or disables the specified CANx interrupts.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_IT: specifies the CAN interrupt sources to be enabled or disabled.
  *          This parameter can be: 
  *            @arg CAN_IT_TME: Transmit mailbox empty Interrupt 
  *            @arg CAN_IT_FMP0: FIFO 0 message pending Interrupt 
  *            @arg CAN_IT_FF0: FIFO 0 full Interrupt
  *            @arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
  *            @arg CAN_IT_FMP1: FIFO 1 message pending Interrupt 
  *            @arg CAN_IT_FF1: FIFO 1 full Interrupt
  *            @arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
  *            @arg CAN_IT_WKU: Wake-up Interrupt
  *            @arg CAN_IT_SLK: Sleep acknowledge Interrupt  
  *            @arg CAN_IT_EWG: Error warning Interrupt
  *            @arg CAN_IT_EPV: Error passive Interrupt
  *            @arg CAN_IT_BOF: Bus-off Interrupt  
  *            @arg CAN_IT_LEC: Last error code Interrupt
  *            @arg CAN_IT_ERR: Error Interrupt
  * @param  NewState: new state of the CAN interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_IT(CAN_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected CANx interrupt */
    CANx->IER |= CAN_IT;
  }
  else
  {
    /* Disable the selected CANx interrupt */
    CANx->IER &= ~CAN_IT;
  }
}
/**
  * @brief  Checks whether the specified CAN flag is set or not.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg CAN_FLAG_RQCP0: Request MailBox0 Flag
  *            @arg CAN_FLAG_RQCP1: Request MailBox1 Flag
  *            @arg CAN_FLAG_RQCP2: Request MailBox2 Flag
  *            @arg CAN_FLAG_FMP0: FIFO 0 Message Pending Flag   
  *            @arg CAN_FLAG_FF0: FIFO 0 Full Flag       
  *            @arg CAN_FLAG_FOV0: FIFO 0 Overrun Flag 
  *            @arg CAN_FLAG_FMP1: FIFO 1 Message Pending Flag   
  *            @arg CAN_FLAG_FF1: FIFO 1 Full Flag        
  *            @arg CAN_FLAG_FOV1: FIFO 1 Overrun Flag     
  *            @arg CAN_FLAG_WKU: Wake up Flag
  *            @arg CAN_FLAG_SLAK: Sleep acknowledge Flag 
  *            @arg CAN_FLAG_EWG: Error Warning Flag
  *            @arg CAN_FLAG_EPV: Error Passive Flag  
  *            @arg CAN_FLAG_BOF: Bus-Off Flag    
  *            @arg CAN_FLAG_LEC: Last error code Flag      
  * @retval The new state of CAN_FLAG (SET or RESET).
  */
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_GET_FLAG(CAN_FLAG));
  

  if((CAN_FLAG & CAN_FLAGS_ESR) != (uint32_t)RESET)
  { 
    /* Check the status of the specified CAN flag */
    if ((CANx->ESR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    { 
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    { 
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  else if((CAN_FLAG & CAN_FLAGS_MSR) != (uint32_t)RESET)
  { 
    /* Check the status of the specified CAN flag */
    if ((CANx->MSR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    { 
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    { 
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  else if((CAN_FLAG & CAN_FLAGS_TSR) != (uint32_t)RESET)
  { 
    /* Check the status of the specified CAN flag */
    if ((CANx->TSR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    { 
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    { 
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  else if((CAN_FLAG & CAN_FLAGS_RF0R) != (uint32_t)RESET)
  { 
    /* Check the status of the specified CAN flag */
    if ((CANx->RF0R & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    { 
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    { 
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  else /* If(CAN_FLAG & CAN_FLAGS_RF1R != (uint32_t)RESET) */
  { 
    /* Check the status of the specified CAN flag */
    if ((uint32_t)(CANx->RF1R & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    { 
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    { 
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  /* Return the CAN_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the CAN's pending flags.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_FLAG: specifies the flag to clear.
  *          This parameter can be one of the following values:
  *            @arg CAN_FLAG_RQCP0: Request MailBox0 Flag
  *            @arg CAN_FLAG_RQCP1: Request MailBox1 Flag
  *            @arg CAN_FLAG_RQCP2: Request MailBox2 Flag 
  *            @arg CAN_FLAG_FF0: FIFO 0 Full Flag       
  *            @arg CAN_FLAG_FOV0: FIFO 0 Overrun Flag  
  *            @arg CAN_FLAG_FF1: FIFO 1 Full Flag        
  *            @arg CAN_FLAG_FOV1: FIFO 1 Overrun Flag     
  *            @arg CAN_FLAG_WKU: Wake up Flag
  *            @arg CAN_FLAG_SLAK: Sleep acknowledge Flag    
  *            @arg CAN_FLAG_LEC: Last error code Flag        
  * @retval None
  */
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG)
{
  uint32_t flagtmp=0;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_CLEAR_FLAG(CAN_FLAG));
  
  if (CAN_FLAG == CAN_FLAG_LEC) /* ESR register */
  {
    /* Clear the selected CAN flags */
    CANx->ESR = (uint32_t)RESET;
  }
  else /* MSR or TSR or RF0R or RF1R */
  {
    flagtmp = CAN_FLAG & 0x000FFFFF;

    if ((CAN_FLAG & CAN_FLAGS_RF0R)!=(uint32_t)RESET)
    {
      /* Receive Flags */
      CANx->RF0R = (uint32_t)(flagtmp);
    }
    else if ((CAN_FLAG & CAN_FLAGS_RF1R)!=(uint32_t)RESET)
    {
      /* Receive Flags */
      CANx->RF1R = (uint32_t)(flagtmp);
    }
    else if ((CAN_FLAG & CAN_FLAGS_TSR)!=(uint32_t)RESET)
    {
      /* Transmit Flags */
      CANx->TSR = (uint32_t)(flagtmp);
    }
    else /* If((CAN_FLAG & CAN_FLAGS_MSR)!=(uint32_t)RESET) */
    {
      /* Operating mode Flags */
      CANx->MSR = (uint32_t)(flagtmp);
    }
  }
}

/**
  * @brief  Checks whether the specified CANx interrupt has occurred or not.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_IT: specifies the CAN interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg CAN_IT_TME: Transmit mailbox empty Interrupt 
  *            @arg CAN_IT_FMP0: FIFO 0 message pending Interrupt 
  *            @arg CAN_IT_FF0: FIFO 0 full Interrupt
  *            @arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
  *            @arg CAN_IT_FMP1: FIFO 1 message pending Interrupt 
  *            @arg CAN_IT_FF1: FIFO 1 full Interrupt
  *            @arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
  *            @arg CAN_IT_WKU: Wake-up Interrupt
  *            @arg CAN_IT_SLK: Sleep acknowledge Interrupt  
  *            @arg CAN_IT_EWG: Error warning Interrupt
  *            @arg CAN_IT_EPV: Error passive Interrupt
  *            @arg CAN_IT_BOF: Bus-off Interrupt  
  *            @arg CAN_IT_LEC: Last error code Interrupt
  *            @arg CAN_IT_ERR: Error Interrupt
  * @retval The current state of CAN_IT (SET or RESET).
  */
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT)
{
  ITStatus itstatus = RESET;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_IT(CAN_IT));
  
  /* check the interrupt enable bit */
 if((CANx->IER & CAN_IT) != RESET)
 {
   /* in case the Interrupt is enabled, .... */
    switch (CAN_IT)
    {
      case CAN_IT_TME:
        /* Check CAN_TSR_RQCPx bits */
        itstatus = CheckITStatus(CANx->TSR, CAN_TSR_RQCP0|CAN_TSR_RQCP1|CAN_TSR_RQCP2);  
        break;
      case CAN_IT_FMP0:
        /* Check CAN_RF0R_FMP0 bit */
        itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FMP0);  
        break;
      case CAN_IT_FF0:
        /* Check CAN_RF0R_FULL0 bit */
        itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FULL0);  
        break;
      case CAN_IT_FOV0:
        /* Check CAN_RF0R_FOVR0 bit */
        itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FOVR0);  
        break;
      case CAN_IT_FMP1:
        /* Check CAN_RF1R_FMP1 bit */
        itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FMP1);  
        break;
      case CAN_IT_FF1:
        /* Check CAN_RF1R_FULL1 bit */
        itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FULL1);  
        break;
      case CAN_IT_FOV1:
        /* Check CAN_RF1R_FOVR1 bit */
        itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FOVR1);  
        break;
      case CAN_IT_WKU:
        /* Check CAN_MSR_WKUI bit */
        itstatus = CheckITStatus(CANx->MSR, CAN_MSR_WKUI);  
        break;
      case CAN_IT_SLK:
        /* Check CAN_MSR_SLAKI bit */
        itstatus = CheckITStatus(CANx->MSR, CAN_MSR_SLAKI);  
        break;
      case CAN_IT_EWG:
        /* Check CAN_ESR_EWGF bit */
        itstatus = CheckITStatus(CANx->ESR, CAN_ESR_EWGF);  
        break;
      case CAN_IT_EPV:
        /* Check CAN_ESR_EPVF bit */
        itstatus = CheckITStatus(CANx->ESR, CAN_ESR_EPVF);  
        break;
      case CAN_IT_BOF:
        /* Check CAN_ESR_BOFF bit */
        itstatus = CheckITStatus(CANx->ESR, CAN_ESR_BOFF);  
        break;
      case CAN_IT_LEC:
        /* Check CAN_ESR_LEC bit */
        itstatus = CheckITStatus(CANx->ESR, CAN_ESR_LEC);  
        break;
      case CAN_IT_ERR:
        /* Check CAN_MSR_ERRI bit */ 
        itstatus = CheckITStatus(CANx->MSR, CAN_MSR_ERRI); 
        break;
      default:
        /* in case of error, return RESET */
        itstatus = RESET;
        break;
    }
  }
  else
  {
   /* in case the Interrupt is not enabled, return RESET */
    itstatus  = RESET;
  }
  
  /* Return the CAN_IT status */
  return  itstatus;
}

/**
  * @brief  Clears the CANx's interrupt pending bits.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_IT: specifies the interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg CAN_IT_TME: Transmit mailbox empty Interrupt
  *            @arg CAN_IT_FF0: FIFO 0 full Interrupt
  *            @arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
  *            @arg CAN_IT_FF1: FIFO 1 full Interrupt
  *            @arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
  *            @arg CAN_IT_WKU: Wake-up Interrupt
  *            @arg CAN_IT_SLK: Sleep acknowledge Interrupt  
  *            @arg CAN_IT_EWG: Error warning Interrupt
  *            @arg CAN_IT_EPV: Error passive Interrupt
  *            @arg CAN_IT_BOF: Bus-off Interrupt  
  *            @arg CAN_IT_LEC: Last error code Interrupt
  *            @arg CAN_IT_ERR: Error Interrupt 
  * @retval None
  */
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_CLEAR_IT(CAN_IT));

  switch (CAN_IT)
  {
    case CAN_IT_TME:
      /* Clear CAN_TSR_RQCPx (rc_w1)*/
      CANx->TSR = CAN_TSR_RQCP0|CAN_TSR_RQCP1|CAN_TSR_RQCP2;  
      break;
    case CAN_IT_FF0:
      /* Clear CAN_RF0R_FULL0 (rc_w1)*/
      CANx->RF0R = CAN_RF0R_FULL0; 
      break;
    case CAN_IT_FOV0:
      /* Clear CAN_RF0R_FOVR0 (rc_w1)*/
      CANx->RF0R = CAN_RF0R_FOVR0; 
      break;
    case CAN_IT_FF1:
      /* Clear CAN_RF1R_FULL1 (rc_w1)*/
      CANx->RF1R = CAN_RF1R_FULL1;  
      break;
    case CAN_IT_FOV1:
      /* Clear CAN_RF1R_FOVR1 (rc_w1)*/
      CANx->RF1R = CAN_RF1R_FOVR1; 
      break;
    case CAN_IT_WKU:
      /* Clear CAN_MSR_WKUI (rc_w1)*/
      CANx->MSR = CAN_MSR_WKUI;  
      break;
    case CAN_IT_SLK:
      /* Clear CAN_MSR_SLAKI (rc_w1)*/ 
      CANx->MSR = CAN_MSR_SLAKI;   
      break;
    case CAN_IT_EWG:
      /* Clear CAN_MSR_ERRI (rc_w1) */
      CANx->MSR = CAN_MSR_ERRI;
       /* @note the corresponding Flag is cleared by hardware depending on the CAN Bus status*/ 
      break;
    case CAN_IT_EPV:
      /* Clear CAN_MSR_ERRI (rc_w1) */
      CANx->MSR = CAN_MSR_ERRI; 
       /* @note the corresponding Flag is cleared by hardware depending on the CAN Bus status*/
      break;
    case CAN_IT_BOF:
      /* Clear CAN_MSR_ERRI (rc_w1) */ 
      CANx->MSR = CAN_MSR_ERRI; 
       /* @note the corresponding Flag is cleared by hardware depending on the CAN Bus status*/
       break;
    case CAN_IT_LEC:
      /*  Clear LEC bits */
      CANx->ESR = RESET; 
      /* Clear CAN_MSR_ERRI (rc_w1) */
      CANx->MSR = CAN_MSR_ERRI; 
      break;
    case CAN_IT_ERR:
      /*Clear LEC bits */
      CANx->ESR = RESET; 
      /* Clear CAN_MSR_ERRI (rc_w1) */
      CANx->MSR = CAN_MSR_ERRI; 
       /* @note BOFF, EPVF and EWGF Flags are cleared by hardware depending on the CAN Bus status*/
       break;
    default:
       break;
   }
}
 /**
  * @}
  */

/**
  * @brief  Checks whether the CAN interrupt has occurred or not.
  * @param  CAN_Reg: specifies the CAN interrupt register to check.
  * @param  It_Bit: specifies the interrupt source bit to check.
  * @retval The new state of the CAN Interrupt (SET or RESET).
  */
static ITStatus CheckITStatus(uint32_t CAN_Reg, uint32_t It_Bit)
{
  ITStatus pendingbitstatus = RESET;
  
  if ((CAN_Reg & It_Bit) != (uint32_t)RESET)
  {
    /* CAN_IT is set */
    pendingbitstatus = SET;
  }
  else
  {
    /* CAN_IT is reset */
    pendingbitstatus = RESET;
  }
  return pendingbitstatus;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */

/**
  ******************************************************************************
  * @file    stm32f0xx_cec.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Consumer Electronics Control (CEC) peripheral
  *          applicable only on STM32F051, STM32F042 and STM32F072 devices:
  *            + Initialization and Configuration
  *            + Data transfers functions
  *            + Interrupts and flags management
  *               
  *  @verbatim
  ==============================================================================
                            ##### CEC features #####
  ==============================================================================
      [..] This device provides some features:
           (#) Supports HDMI-CEC specification 1.4.
           (#) Supports two source clocks(HSI/244 or LSE).
           (#) Works in stop mode(without APB clock, but with CEC clock 32KHz).
               It can genarate an interrupt in the CEC clock domain that the CPU 
               wakes up from the low power mode.
           (#) Configurable Signal Free Time before of transmission start. The 
               number of nominal data bit periods waited before transmission can be
               ruled by Hardware or Software.
           (#) Configurable Peripheral Address (multi-addressing configuration).
           (#) Supports listen mode.The CEC Messages addressed to different destination
               can be received without interfering with CEC bus when Listen mode option is enabled.
           (#) Configurable Rx-Tolerance(Standard and Extended tolerance margin).
           (#) Error detection with configurable error bit generation.
           (#) Arbitration lost error in the case of two CEC devices starting at the same time.

                            ##### How to use this driver ##### 
  ==============================================================================
      [..] This driver provides functions to configure and program the CEC device,
       follow steps below:
           (#) The source clock can be configured using:
               (++) RCC_CECCLKConfig(RCC_CECCLK_HSI_Div244) for HSI(Default) 
               (++) RCC_CECCLKConfig(RCC_CECCLK_LSE) for LSE.
           (#) Enable CEC peripheral clock using RCC_APBPeriphClockCmd(RCC_APBPeriph_CEC, ENABLE).
           (#) Peripherals alternate function.
               (++) Connect the pin to the desired peripherals' Alternate Function (AF) using 
               GPIO_PinAFConfig() function.
               (++) Configure the desired pin in alternate function by:
               GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
               (++) Select the type open-drain and output speed via GPIO_OType 
               and GPIO_Speed members.
               (++) Call GPIO_Init() function.
           (#) Configure the Signal Free Time, Rx Tolerance, Stop reception generation 
               and Bit error generation using the CEC_Init() function.
               The function CEC_Init() must be called when the CEC peripheral is disabled.
           (#) Configure the CEC own address by calling the fuction CEC_OwnAddressConfig().
           (#) Optionally, you can configure the Listen mode using the function CEC_ListenModeCmd().
           (#) Enable the NVIC and the corresponding interrupt using the function 
               CEC_ITConfig() if you need to use interrupt mode.
               CEC_ITConfig() must be called before enabling the CEC peripheral.
           (#) Enable the CEC using the CEC_Cmd() function.
           (#) Charge the first data byte in the TXDR register using CEC_SendDataByte().
           (#) Enable the transmission of the Byte of a CEC message using CEC_StartOfMessage() 
           (#) Transmit single data through the CEC peripheral using CEC_SendDataByte() 
               and Receive the last transmitted byte using CEC_ReceiveDataByte().
           (#) Enable the CEC_EndOfMessage() in order to indicate the last byte of the message.
      [..]
           (@) If the listen mode is enabled, Stop reception generation and Bit error generation 
               must be in reset state.
           (@) If the CEC message consists of only 1 byte, the function CEC_EndOfMessage()
               must be called before CEC_StartOfMessage().
  
   @endverbatim
  *
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CEC 
  * @brief CEC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BROADCAST_ADDRESS      ((uint32_t)0x0000F)
#define CFGR_CLEAR_MASK        ((uint32_t)0x7000FE00)   /* CFGR register Mask */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CEC_Private_Functions 
  * @{
  */

/** @defgroup CEC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim  
 ===============================================================================
                            ##### Initialization and Configuration functions #####
 ===============================================================================
      [..] This section provides functions allowing to initialize:
            (+) CEC own addresses
            (+) CEC Signal Free Time
            (+) CEC Rx Tolerance
            (+) CEC Stop Reception
            (+) CEC Bit Rising Error
            (+) CEC Long Bit Period Error
      [..] This section provides also a function to configure the CEC peripheral in Listen Mode.
           Messages addressed to different destination can be received when Listen mode is 
           enabled without interfering with CEC bus.
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the CEC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CEC_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, DISABLE);
}

/**
  * @brief  Initializes the CEC peripheral according to the specified parameters
  *         in the CEC_InitStruct.
  * @note   The CEC parameters must be configured before enabling the CEC peripheral.
  * @param  CEC_InitStruct: pointer to an CEC_InitTypeDef structure that contains
  *         the configuration information for the specified CEC peripheral.
  * @retval None
  */
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_CEC_SIGNAL_FREE_TIME(CEC_InitStruct->CEC_SignalFreeTime));
  assert_param(IS_CEC_RX_TOLERANCE(CEC_InitStruct->CEC_RxTolerance));
  assert_param(IS_CEC_STOP_RECEPTION(CEC_InitStruct->CEC_StopReception));
  assert_param(IS_CEC_BIT_RISING_ERROR(CEC_InitStruct->CEC_BitRisingError));
  assert_param(IS_CEC_LONG_BIT_PERIOD_ERROR(CEC_InitStruct->CEC_LongBitPeriodError));
  assert_param(IS_CEC_BDR_NO_GEN_ERROR(CEC_InitStruct->CEC_BRDNoGen));
  assert_param(IS_CEC_SFT_OPTION(CEC_InitStruct->CEC_SFTOption));

  /* Get the CEC CFGR value */
  tmpreg = CEC->CFGR;

  /* Clear CFGR bits */
  tmpreg &= CFGR_CLEAR_MASK;

  /* Configure the CEC peripheral */
  tmpreg |= (CEC_InitStruct->CEC_SignalFreeTime | CEC_InitStruct->CEC_RxTolerance |
             CEC_InitStruct->CEC_StopReception  | CEC_InitStruct->CEC_BitRisingError |
             CEC_InitStruct->CEC_LongBitPeriodError| CEC_InitStruct->CEC_BRDNoGen |
             CEC_InitStruct->CEC_SFTOption);

  /* Write to CEC CFGR  register */
  CEC->CFGR = tmpreg;
}

/**
  * @brief  Fills each CEC_InitStruct member with its default value.
  * @param  CEC_InitStruct: pointer to a CEC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void CEC_StructInit(CEC_InitTypeDef* CEC_InitStruct)
{
  CEC_InitStruct->CEC_SignalFreeTime = CEC_SignalFreeTime_Standard;
  CEC_InitStruct->CEC_RxTolerance = CEC_RxTolerance_Standard;
  CEC_InitStruct->CEC_StopReception = CEC_StopReception_Off;
  CEC_InitStruct->CEC_BitRisingError = CEC_BitRisingError_Off;
  CEC_InitStruct->CEC_LongBitPeriodError = CEC_LongBitPeriodError_Off;
  CEC_InitStruct->CEC_BRDNoGen = CEC_BRDNoGen_Off;
  CEC_InitStruct->CEC_SFTOption = CEC_SFTOption_Off;
}

/**
  * @brief  Enables or disables the CEC peripheral.
  * @param  NewState: new state of the CEC peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_Cmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the CEC peripheral */
    CEC->CR |= CEC_CR_CECEN;
  }
  else
  {
    /* Disable the CEC peripheral */
    CEC->CR &= ~CEC_CR_CECEN;
  }
}

/**
  * @brief  Enables or disables the CEC Listen Mode.
  * @param  NewState: new state of the Listen Mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_ListenModeCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Listen Mode */
    CEC->CFGR |= CEC_CFGR_LSTN;
  }
  else
  {
    /* Disable the Listen Mode */
    CEC->CFGR &= ~CEC_CFGR_LSTN;
  }
}

/**
  * @brief  Defines the Own Address of the CEC device.
  * @param  CEC_OwnAddress: The CEC own address.
  * @retval None
  */
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress)
{
  uint32_t tmp =0x00;
  /* Check the parameters */
  assert_param(IS_CEC_ADDRESS(CEC_OwnAddress));
  tmp = 1 <<(CEC_OwnAddress + 16);
  /* Set the CEC own address */
  CEC->CFGR |= tmp;
}

/**
  * @brief  Clears the Own Address of the CEC device.
  * @param  CEC_OwnAddress: The CEC own address.
  * @retval None
  */
void CEC_OwnAddressClear(void)
{
  /* Set the CEC own address */
  CEC->CFGR = 0x0;
}

/**
  * @}
  */

/** @defgroup CEC_Group2 Data transfers functions
 *  @brief    Data transfers functions
 *
@verbatim
 ===============================================================================
                            ##### Data transfers functions #####
 ===============================================================================
    [..] This section provides functions allowing the CEC data transfers.The read 
         access of the CEC_RXDR register can be done using the CEC_ReceiveData()function 
         and returns the Rx buffered value. Whereas a write access to the CEC_TXDR can be 
         done using CEC_SendData() function.
@endverbatim
  * @{
  */

/**
  * @brief  Transmits single data through the CEC peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void CEC_SendData(uint8_t Data)
{
  /* Transmit Data */
  CEC->TXDR = Data;
}

/**
  * @brief  Returns the most recent received data by the CEC peripheral.
  * @param  None
  * @retval The received data.
  */
uint8_t CEC_ReceiveData(void)
{
  /* Receive Data */
  return (uint8_t)(CEC->RXDR);
}

/**
  * @brief  Starts a new message.
  * @param  None
  * @retval None
  */
void CEC_StartOfMessage(void)
{
  /* Starts of new message */
  CEC->CR |= CEC_CR_TXSOM; 
}

/**
  * @brief  Transmits message with an EOM bit.
  * @param  None
  * @retval None
  */
void CEC_EndOfMessage(void)
{
  /* The data byte will be transmitted with an EOM bit */
  CEC->CR |= CEC_CR_TXEOM;
}

/**
  * @}
  */

/** @defgroup CEC_Group3 Interrupts and flags management functions
 *  @brief    Interrupts and flags management functions
*
@verbatim
 ===============================================================================
                            ##### Interrupts and flags management functions ##### 
 ===============================================================================
    [..] This section provides functions allowing to configure the CEC Interrupts
         sources and check or clear the flags or pending bits status.
    [..] The user should identify which mode will be used in his application to manage
         the communication: Polling mode or Interrupt mode.
  
    [..] In polling mode, the CEC can be managed by the following flags:
            (+) CEC_FLAG_TXACKE : to indicate a missing acknowledge in transmission mode.
            (+) CEC_FLAG_TXERR  : to indicate an error occurs during transmission mode.
                                  The initiator detects low impedance in the CEC line.
            (+) CEC_FLAG_TXUDR  : to indicate if an underrun error occurs in transmission mode.
                                  The transmission is enabled while the software has not yet 
                                  loaded any value into the TXDR register.
            (+) CEC_FLAG_TXEND  : to indicate the end of successful transmission.
            (+) CEC_FLAG_TXBR   : to indicate the next transmission data has to be written to TXDR.
            (+) CEC_FLAG_ARBLST : to indicate arbitration lost in the case of two CEC devices
                                  starting at the same time.
            (+) CEC_FLAG_RXACKE : to indicate a missing acknowledge in receive mode.
            (+) CEC_FLAG_LBPE   : to indicate a long bit period error generated during receive mode.
            (+) CEC_FLAG_SBPE   : to indicate a short bit period error generated during receive mode.
            (+) CEC_FLAG_BRE    : to indicate a bit rising error generated during receive mode.
            (+) CEC_FLAG_RXOVR  : to indicate if an overrun error occur while receiving a CEC message.
                                  A byte is not yet received while a new byte is stored in the RXDR register.
            (+) CEC_FLAG_RXEND  : to indicate the end Of reception
            (+) CEC_FLAG_RXBR   : to indicate a new byte has been received from the CEC line and 
                                  stored into the RXDR buffer.
    [..]
           (@)In this Mode, it is advised to use the following functions:
              FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG);
              void CEC_ClearFlag(uint16_t CEC_FLAG);

    [..] In Interrupt mode, the CEC can be managed by the following interrupt sources:
           (+) CEC_IT_TXACKE : to indicate a TX Missing acknowledge 
           (+) CEC_IT_TXACKE : to indicate a missing acknowledge in transmission mode.
           (+) CEC_IT_TXERR  : to indicate an error occurs during transmission mode.
                               The initiator detects low impedance in the CEC line.
           (+) CEC_IT_TXUDR  : to indicate if an underrun error occurs in transmission mode.
                               The transmission is enabled while the software has not yet 
                               loaded any value into the TXDR register.
           (+) CEC_IT_TXEND  : to indicate the end of successful transmission.
           (+) CEC_IT_TXBR   : to indicate the next transmission data has to be written to TXDR register.
           (+) CEC_IT_ARBLST : to indicate arbitration lost in the case of two CEC devices
                                starting at the same time.
           (+) CEC_IT_RXACKE : to indicate a missing acknowledge in receive mode.
           (+) CEC_IT_LBPE   : to indicate a long bit period error generated during receive mode.
           (+) CEC_IT_SBPE   : to indicate a short bit period error generated during receive mode.
           (+) CEC_IT_BRE    : to indicate a bit rising error generated during receive mode.
           (+) CEC_IT_RXOVR  : to indicate if an overrun error occur while receiving a CEC message.
                               A byte is not yet received while a new byte is stored in the RXDR register.
           (+) CEC_IT_RXEND  : to indicate the end Of reception
           (+) CEC_IT_RXBR   : to indicate a new byte has been received from the CEC line and 
                                stored into the RXDR buffer.
    [..]
           (@)In this Mode it is advised to use the following functions:
              void CEC_ITConfig( uint16_t CEC_IT, FunctionalState NewState);
              ITStatus CEC_GetITStatus(uint16_t CEC_IT);
              void CEC_ClearITPendingBit(uint16_t CEC_IT);
              

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the selected CEC interrupts.
  * @param  CEC_IT: specifies the CEC interrupt source to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg CEC_IT_TXACKE: Tx Missing acknowledge Error
  *            @arg CEC_IT_TXERR: Tx Error.
  *            @arg CEC_IT_TXUDR: Tx-Buffer Underrun.
  *            @arg CEC_IT_TXEND: End of Transmission (successful transmission of the last byte).
  *            @arg CEC_IT_TXBR: Tx-Byte Request.
  *            @arg CEC_IT_ARBLST: Arbitration Lost
  *            @arg CEC_IT_RXACKE: Rx-Missing Acknowledge
  *            @arg CEC_IT_LBPE: Rx Long period Error
  *            @arg CEC_IT_SBPE: Rx Short period Error
  *            @arg CEC_IT_BRE: Rx Bit Rising Error
  *            @arg CEC_IT_RXOVR: Rx Overrun.
  *            @arg CEC_IT_RXEND: End Of Reception
  *            @arg CEC_IT_RXBR: Rx-Byte Received
  * @param  NewState: new state of the selected CEC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_ITConfig(uint16_t CEC_IT, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_CEC_IT(CEC_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected CEC interrupt */
    CEC->IER |= CEC_IT;
  }
  else
  {
    CEC_IT =~CEC_IT;
    /* Disable the selected CEC interrupt */
    CEC->IER &= CEC_IT;
  }
}

/**
  * @brief  Gets the CEC flag status.
  * @param  CEC_FLAG: specifies the CEC flag to check.
  *     This parameter can be one of the following values:
  *            @arg CEC_FLAG_TXACKE: Tx Missing acknowledge Error
  *            @arg CEC_FLAG_TXERR: Tx Error.
  *            @arg CEC_FLAG_TXUDR: Tx-Buffer Underrun.
  *            @arg CEC_FLAG_TXEND: End of transmission (successful transmission of the last byte).
  *            @arg CEC_FLAG_TXBR: Tx-Byte Request.
  *            @arg CEC_FLAG_ARBLST: Arbitration Lost
  *            @arg CEC_FLAG_RXACKE: Rx-Missing Acknowledge 
  *            @arg CEC_FLAG_LBPE: Rx Long period Error
  *            @arg CEC_FLAG_SBPE: Rx Short period Error
  *            @arg CEC_FLAG_BRE: Rx Bit Rissing Error
  *            @arg CEC_FLAG_RXOVR: Rx Overrun.
  *            @arg CEC_FLAG_RXEND: End Of Reception.
  *            @arg CEC_FLAG_RXBR: Rx-Byte Received.
  * @retval The new state of CEC_FLAG (SET or RESET)
  */
FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG) 
{
  FlagStatus bitstatus = RESET;
  
  assert_param(IS_CEC_GET_FLAG(CEC_FLAG));
  
  /* Check the status of the specified CEC flag */
  if ((CEC->ISR & CEC_FLAG) != (uint16_t)RESET)
  {
    /* CEC flag is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC flag is reset */
    bitstatus = RESET;
  }

  /* Return the CEC flag status */
  return  bitstatus;
}

/**
  * @brief  Clears the CEC's pending flags.
  * @param  CEC_FLAG: specifies the flag to clear. 
  *          This parameter can be any combination of the following values:
  *            @arg CEC_FLAG_TXACKE: Tx Missing acknowledge Error
  *            @arg CEC_FLAG_TXERR: Tx Error
  *            @arg CEC_FLAG_TXUDR: Tx-Buffer Underrun
  *            @arg CEC_FLAG_TXEND: End of transmission (successful transmission of the last byte).
  *            @arg CEC_FLAG_TXBR: Tx-Byte Request
  *            @arg CEC_FLAG_ARBLST: Arbitration Lost
  *            @arg CEC_FLAG_RXACKE: Rx Missing Acknowledge 
  *            @arg CEC_FLAG_LBPE: Rx Long period Error
  *            @arg CEC_FLAG_SBPE: Rx Short period Error
  *            @arg CEC_FLAG_BRE: Rx Bit Rising Error
  *            @arg CEC_FLAG_RXOVR: Rx Overrun
  *            @arg CEC_FLAG_RXEND: End Of Reception
  *            @arg CEC_FLAG_RXBR: Rx-Byte Received
  * @retval None
  */
void CEC_ClearFlag(uint32_t CEC_FLAG)
{
  assert_param(IS_CEC_CLEAR_FLAG(CEC_FLAG));

  /* Clear the selected CEC flag */
  CEC->ISR = CEC_FLAG;
}

/**
  * @brief  Checks whether the specified CEC interrupt has occurred or not.
  * @param  CEC_IT: specifies the CEC interrupt source to check. 
  *          This parameter can be one of the following values:
  *            @arg CEC_IT_TXACKE: Tx Missing acknowledge Error
  *            @arg CEC_IT_TXERR: Tx Error.
  *            @arg CEC_IT_TXUDR: Tx-Buffer Underrun.
  *            @arg CEC_IT_TXEND: End of transmission (successful transmission of the last byte).
  *            @arg CEC_IT_TXBR: Tx-Byte Request.
  *            @arg CEC_IT_ARBLST: Arbitration Lost.
  *            @arg CEC_IT_RXACKE: Rx-Missing Acknowledge.
  *            @arg CEC_IT_LBPE: Rx Long period Error.
  *            @arg CEC_IT_SBPE: Rx Short period Error.
  *            @arg CEC_IT_BRE: Rx Bit Rising Error.
  *            @arg CEC_IT_RXOVR: Rx Overrun.
  *            @arg CEC_IT_RXEND: End Of Reception.
  *            @arg CEC_IT_RXBR: Rx-Byte Received 
  * @retval The new state of CEC_IT (SET or RESET).
  */
ITStatus CEC_GetITStatus(uint16_t CEC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_CEC_GET_IT(CEC_IT));

  /* Get the CEC IT enable bit status */
  enablestatus = (CEC->IER & CEC_IT);

  /* Check the status of the specified CEC interrupt */
  if (((CEC->ISR & CEC_IT) != (uint32_t)RESET) && enablestatus)
  {
    /* CEC interrupt is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC interrupt is reset */
    bitstatus = RESET;
  }

  /* Return the CEC interrupt status */
  return  bitstatus;
}

/**
  * @brief  Clears the CEC's interrupt pending bits.
  * @param  CEC_IT: specifies the CEC interrupt pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg CEC_IT_TXACKE: Tx Missing acknowledge Error
  *            @arg CEC_IT_TXERR: Tx Error
  *            @arg CEC_IT_TXUDR: Tx-Buffer Underrun
  *            @arg CEC_IT_TXEND: End of Transmission
  *            @arg CEC_IT_TXBR: Tx-Byte Request
  *            @arg CEC_IT_ARBLST: Arbitration Lost
  *            @arg CEC_IT_RXACKE: Rx-Missing Acknowledge
  *            @arg CEC_IT_LBPE: Rx Long period Error
  *            @arg CEC_IT_SBPE: Rx Short period Error
  *            @arg CEC_IT_BRE: Rx Bit Rising Error
  *            @arg CEC_IT_RXOVR: Rx Overrun
  *            @arg CEC_IT_RXEND: End Of Reception
  *            @arg CEC_IT_RXBR: Rx-Byte Received
  * @retval None
  */
void CEC_ClearITPendingBit(uint16_t CEC_IT)
{
  assert_param(IS_CEC_IT(CEC_IT));

  /* Clear the selected CEC interrupt pending bits */
  CEC->ISR = CEC_IT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_comp.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the comparators (COMP1 and COMP2) peripheral
  *          applicable only on STM32F051 and STM32F072 devices: 
  *           + Comparators configuration
  *           + Window mode control
  *
  *  @verbatim
  *
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]           
   
         The device integrates two analog comparators COMP1 and COMP2:
         (+) The non inverting input is set to PA1 for COMP1 and to PA3
             for COMP2.
  
         (+) The inverting input can be selected among: DAC1_OUT, DAC2_OUT 
             1/4 VREFINT, 1/2 VERFINT, 3/4 VREFINT, VREFINT,
             I/O (PA0 for COMP1 and PA2 for COMP2)
  
         (+) The COMP output is internally is available using COMP_GetOutputLevel()
             and can be set on GPIO pins: PA0, PA6, PA11 for COMP1
             and PA2, PA7, PA12 for COMP2
  
         (+) The COMP output can be redirected to embedded timers (TIM1, TIM2
             and TIM3)
  
         (+) The two comparators COMP1 and COMP2 can be combined in window
             mode and only COMP1 non inverting (PA1) can be used as non-
             inverting input.
  
         (+) The two comparators COMP1 and COMP2 have interrupt capability 
             with wake-up from Sleep and Stop modes (through the EXTI controller).
             COMP1 and COMP2 outputs are internally connected to EXTI Line 21
             and EXTI Line 22 respectively.
                   

                     ##### How to configure the comparator #####
 ===============================================================================
    [..] 
           This driver provides functions to configure and program the Comparators 
           of all STM32F0xx devices.
             
    [..]   To use the comparator, perform the following steps:
  
         (#) Enable the SYSCFG APB clock to get write access to comparator
             register using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
         (#) Configure the comparator input in analog mode using GPIO_Init()
  
         (#) Configure the comparator output in alternate function mode
             using GPIO_Init() and use GPIO_PinAFConfig() function to map the
             comparator output to the GPIO pin
  
         (#) Configure the comparator using COMP_Init() function:
                 (++)  Select the inverting input
                 (++)  Select the output polarity  
                 (++)  Select the output redirection
                 (++)  Select the hysteresis level
                 (++)  Select the power mode
    
         (#) Enable the comparator using COMP_Cmd() function
  
         (#) If required enable the COMP interrupt by configuring and enabling
             EXTI line in Interrupt mode and selecting the desired sensitivity
             level using EXTI_Init() function. After that enable the comparator
             interrupt vector using NVIC_Init() function.
  
     @endverbatim
  *    
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


/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup COMP 
  * @brief COMP driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* CSR register Mask */
#define COMP_CSR_CLEAR_MASK              ((uint32_t)0x00003FFE)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup COMP_Private_Functions
  * @{
  */

/** @defgroup COMP_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
               ##### Initialization and Configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */
   
/**
  * @brief  Deinitializes COMP peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  None
  * @retval None
  */
void COMP_DeInit(void)
{
  COMP->CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
}

/**
  * @brief  Initializes the COMP peripheral according to the specified parameters
  *         in COMP_InitStruct
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @note   By default, PA1 is selected as COMP1 non inverting input.
  *         To use PA4 as COMP1 non inverting input call COMP_SwitchCmd() after COMP_Init()
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure that contains 
  *         the configuration information for the specified COMP peripheral.
  * @retval None
  */
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_COMP_INVERTING_INPUT(COMP_InitStruct->COMP_InvertingInput));
  assert_param(IS_COMP_OUTPUT(COMP_InitStruct->COMP_Output));
  assert_param(IS_COMP_OUTPUT_POL(COMP_InitStruct->COMP_OutputPol));
  assert_param(IS_COMP_HYSTERESIS(COMP_InitStruct->COMP_Hysteresis));
  assert_param(IS_COMP_MODE(COMP_InitStruct->COMP_Mode));

  /*!< Get the COMP_CSR register value */
  tmpreg = COMP->CSR;

  /*!< Clear the COMP1SW1, COMPx_IN_SEL, COMPx_OUT_TIM_SEL, COMPx_POL, COMPx_HYST and COMPx_PWR_MODE bits */ 
  tmpreg &= (uint32_t) ~(COMP_CSR_CLEAR_MASK<<COMP_Selection);

  /*!< Configure COMP: inverting input, output redirection, hysteresis value and power mode */
  /*!< Set COMPxINSEL bits according to COMP_InitStruct->COMP_InvertingInput value */
  /*!< Set COMPxOUTSEL bits according to COMP_InitStruct->COMP_Output value */
  /*!< Set COMPxPOL bit according to COMP_InitStruct->COMP_OutputPol value */
  /*!< Set COMPxHYST bits according to COMP_InitStruct->COMP_Hysteresis value */
  /*!< Set COMPxMODE bits according to COMP_InitStruct->COMP_Mode value */   
  tmpreg |= (uint32_t)((COMP_InitStruct->COMP_InvertingInput | COMP_InitStruct->COMP_Output |
                       COMP_InitStruct->COMP_OutputPol | COMP_InitStruct->COMP_Hysteresis |
                       COMP_InitStruct->COMP_Mode)<<COMP_Selection);

  /*!< Write to COMP_CSR register */
  COMP->CSR = tmpreg;  
}

/**
  * @brief  Fills each COMP_InitStruct member with its default value.
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct)
{
  COMP_InitStruct->COMP_InvertingInput = COMP_InvertingInput_1_4VREFINT;
  COMP_InitStruct->COMP_Output = COMP_Output_None;
  COMP_InitStruct->COMP_OutputPol = COMP_OutputPol_NonInverted;
  COMP_InitStruct->COMP_Hysteresis = COMP_Hysteresis_No;
  COMP_InitStruct->COMP_Mode = COMP_Mode_UltraLowPower;
}

/**
  * @brief  Enable or disable the COMP peripheral.
  * @note   If the selected comparator is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  * @param  NewState: new state of the COMP peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, the comparator compares the non inverting input with 
  *         the inverting input and the comparison result is available on comparator output.
  * @note   When disabled, the comparator doesn't perform comparison and the 
  *         output level is low.
  * @retval None
  */
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected COMP peripheral */
    COMP->CSR |= (uint32_t) (1<<COMP_Selection);
  }
  else
  {
    /* Disable the selected COMP peripheral  */
    COMP->CSR &= (uint32_t)(~((uint32_t)1<<COMP_Selection));
  }
}

/**
  * @brief  Close or Open the SW1 switch.
  * @note   This switch is solely intended to redirect signals onto high
  *         impedance input, such as COMP1 non-inverting input (highly resistive switch)
  * @param  NewState: New state of the analog switch.
  *          This parameter can be: ENABLE or DISABLE. 
  * @note   When enabled, the SW1 is closed; PA1 is connected to PA4
  * @note   When disabled, the SW1 switch is open; PA1 is disconnected from PA4
  * @retval None
  */
void COMP_SwitchCmd(FunctionalState NewState)
{
  /* Check the parameter */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Close SW1 switch */
    COMP->CSR |= (uint32_t) (COMP_CSR_COMP1SW1);
  }
  else
  {
    /* Open SW1 switch */
    COMP->CSR &= (uint32_t)(~COMP_CSR_COMP1SW1);
  }
}

/**
  * @brief  Return the output level (high or low) of the selected comparator. 
  * @note   The output level depends on the selected polarity.
  * @note   If the polarity is not inverted:
  *          - Comparator output is low when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is high when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @note   If the polarity is inverted:
  *          - Comparator output is high when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is low when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected  
  * @retval Returns the selected comparator output level: low or high.
  *       
  */
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection)
{
  uint32_t compout = 0x0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Check if selected comparator output is high */
  if ((COMP->CSR & (COMP_CSR_COMP1OUT<<COMP_Selection)) != 0)
  {
    compout = COMP_OutputLevel_High;
  }
  else
  {
    compout = COMP_OutputLevel_Low;
  }

  /* Return the comparator output level */
  return (uint32_t)(compout);
}

/**
  * @}
  */

/** @defgroup COMP_Group2 Window mode control function
 *  @brief   Window mode control function 
 *
@verbatim   
 ===============================================================================
                     ##### Window mode control function #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the window mode.
  * @note   In window mode, COMP1 and COMP2 non inverting inputs are connected
  *         together and only COMP1 non inverting input (PA1) can be used.
  * @param  NewState: new state of the window mode.
  *          This parameter can be :
  *           @arg ENABLE: COMP1 and COMP2 non inverting inputs are connected together.
  *           @arg DISABLE: OMP1 and COMP2 non inverting inputs are disconnected.
  * @retval None
  */
void COMP_WindowCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the window mode */
    COMP->CSR |= (uint32_t) COMP_CSR_WNDWEN;
  }
  else
  {
    /* Disable the window mode */
    COMP->CSR &= (uint32_t)(~COMP_CSR_WNDWEN);
  }
}

/**
  * @}
  */

/** @defgroup COMP_Group3 COMP configuration locking function
 *  @brief   COMP1 and COMP2 configuration locking function
 *           COMP1 and COMP2 configuration can be locked each separately.
 *           Unlocking is performed by system reset.
 *
@verbatim   
 ===============================================================================
                     ##### Configuration Lock function #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected comparator (COMP1/COMP2) configuration.
  * @note   Locking the configuration means that all control bits are read-only.
  *         To unlock the comparator configuration, perform a system reset.
  * @param  COMP_Selection: selects the comparator to be locked 
  *          This parameter can be a value of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 configuration is locked.
  *            @arg COMP_Selection_COMP2: COMP2 configuration is locked.  
  * @retval None
  */
void COMP_LockConfig(uint32_t COMP_Selection)
{
  /* Check the parameter */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Set the lock bit corresponding to selected comparator */
  COMP->CSR |= (uint32_t) (COMP_CSR_COMP1LOCK<<COMP_Selection);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_crc.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of CRC computation unit peripheral:
  *            + Configuration of the CRC computation unit
  *            + CRC computation of one/many 32-bit data
  *            + CRC Independent register (IDR) access
  *
  *  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]
    
         (+) Enable CRC AHB clock using RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE)
             function
         (+) If required, select the reverse operation on input data 
             using CRC_ReverseInputDataSelect()  
         (+) If required, enable the reverse operation on output data
             using CRC_ReverseOutputDataCmd(Enable)
         (+) use CRC_CalcCRC() function to compute the CRC of a 32-bit data
             or use CRC_CalcBlockCRC() function to compute the CRC if a 32-bit 
             data buffer
            (@) To compute the CRC of a new data use CRC_ResetDR() to reset
                 the CRC computation unit before starting the computation
                 otherwise you can get wrong CRC values.
      
     @endverbatim
  *  
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


/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC 
  * @brief CRC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRC_Private_Functions
  * @{
  */

/** @defgroup CRC_Group1 Configuration of the CRC computation unit functions
 *  @brief   Configuration of the CRC computation unit functions 
 *
@verbatim
 ===============================================================================
                     ##### CRC configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes CRC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CRC_DeInit(void)
{
  /* Set DR register to reset value */
  CRC->DR = 0xFFFFFFFF;
  
  /* Set the POL register to the reset value: 0x04C11DB7 */
  CRC->POL = 0x04C11DB7;
  
  /* Reset IDR register */
  CRC->IDR = 0x00;
  
  /* Set INIT register to reset value */
  CRC->INIT = 0xFFFFFFFF;
  
  /* Reset the CRC calculation unit */
  CRC->CR = CRC_CR_RESET;
}

/**
  * @brief  Resets the CRC calculation unit and sets INIT register content in DR register.
  * @param  None
  * @retval None
  */
void CRC_ResetDR(void)
{
  /* Reset CRC generator */
  CRC->CR |= CRC_CR_RESET;
}

/**
  * @brief  Selects the polynomial size. This function is only applicable for 
  *         STM32F072 devices.
  * @param  CRC_PolSize: Specifies the polynomial size.
  *         This parameter can be:
  *          @arg CRC_PolSize_7: 7-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_8: 8-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_16: 16-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_32: 32-bit polynomial for CRC calculation
  * @retval None
  */
void CRC_PolynomialSizeSelect(uint32_t CRC_PolSize)
{
  uint32_t tmpcr = 0;

  /* Check the parameter */
  assert_param(IS_CRC_POL_SIZE(CRC_PolSize));

  /* Get CR register value */
  tmpcr = CRC->CR;

  /* Reset POL_SIZE bits */
  tmpcr &= (uint32_t)~((uint32_t)CRC_CR_POLSIZE);
  /* Set the polynomial size */
  tmpcr |= (uint32_t)CRC_PolSize;

  /* Write to CR register */
  CRC->CR = (uint32_t)tmpcr;
}

/**
  * @brief  Selects the reverse operation to be performed on input data.
  * @param  CRC_ReverseInputData: Specifies the reverse operation on input data.
  *          This parameter can be:
  *            @arg CRC_ReverseInputData_No: No reverse operation is performed
  *            @arg CRC_ReverseInputData_8bits: reverse operation performed on 8 bits
  *            @arg CRC_ReverseInputData_16bits: reverse operation performed on 16 bits
  *            @arg CRC_ReverseInputData_32bits: reverse operation performed on 32 bits
  * @retval None
  */
void CRC_ReverseInputDataSelect(uint32_t CRC_ReverseInputData)
{
  uint32_t tmpcr = 0;

  /* Check the parameter */
  assert_param(IS_CRC_REVERSE_INPUT_DATA(CRC_ReverseInputData));

  /* Get CR register value */
  tmpcr = CRC->CR;

  /* Reset REV_IN bits */
  tmpcr &= (uint32_t)~((uint32_t)CRC_CR_REV_IN);
  /* Set the reverse operation */
  tmpcr |= (uint32_t)CRC_ReverseInputData;

  /* Write to CR register */
  CRC->CR = (uint32_t)tmpcr;
}

/**
  * @brief  Enables or disable the reverse operation on output data.
  *         The reverse operation on output data is performed on 32-bit.
  * @param  NewState: new state of the reverse operation on output data.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRC_ReverseOutputDataCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable reverse operation on output data */
    CRC->CR |= CRC_CR_REV_OUT;
  }
  else
  {
    /* Disable reverse operation on output data */
    CRC->CR &= (uint32_t)~((uint32_t)CRC_CR_REV_OUT);
  }
}

/**
  * @brief  Initializes the INIT register.
  * @note   After resetting CRC calculation unit, CRC_InitValue is stored in DR register
  * @param  CRC_InitValue: Programmable initial CRC value
  * @retval None
  */
void CRC_SetInitRegister(uint32_t CRC_InitValue)
{
  CRC->INIT = CRC_InitValue;
}

/**
  * @brief  Initializes the polynomail coefficients. This function is only 
  *         applicable for STM32F072 devices.
  * @param  CRC_Pol: Polynomial to be used for CRC calculation.
  * @retval None
  */
void CRC_SetPolynomial(uint32_t CRC_Pol)
{
  CRC->POL = CRC_Pol;
}

/**
  * @}
  */

/** @defgroup CRC_Group2 CRC computation of one/many 32-bit data functions
 *  @brief   CRC computation of one/many 32-bit data functions
 *
@verbatim
 ===============================================================================
                     ##### CRC computation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRC_Data: data word(32-bit) to compute its CRC
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcCRC(uint32_t CRC_Data)
{
  CRC->DR = CRC_Data;
  
  return (CRC->DR);
}

/**
  * @brief  Computes the 16-bit CRC of a given 16-bit data. This function is only 
  *         applicable for STM32F072 devices.
  * @param  CRC_Data: data half-word(16-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint32_t CRC_CalcCRC16bits(uint16_t CRC_Data)
{
  *(uint16_t*)(CRC_BASE) = (uint16_t) CRC_Data;
  
  return (CRC->DR);
}

/**
  * @brief  Computes the 8-bit CRC of a given 8-bit data. This function is only 
  *         applicable for STM32F072 devices.
  * @param  CRC_Data: 8-bit data to compute its CRC
  * @retval 8-bit CRC
  */
uint32_t CRC_CalcCRC8bits(uint8_t CRC_Data)
{
  *(uint8_t*)(CRC_BASE) = (uint8_t) CRC_Data;

  return (CRC->DR);
}

/**
  * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  BufferLength: length of the buffer to be computed
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;
  
  for(index = 0; index < BufferLength; index++)
  {
    CRC->DR = pBuffer[index];
  }
  return (CRC->DR);
}

/**
  * @brief  Returns the current CRC value.
  * @param  None
  * @retval 32-bit CRC
  */
uint32_t CRC_GetCRC(void)
{
  return (CRC->DR);
}

/**
  * @}
  */

/** @defgroup CRC_Group3 CRC Independent Register (IDR) access functions
 *  @brief   CRC Independent Register (IDR) access (write/read) functions
 *
@verbatim
 ===============================================================================
           ##### CRC Independent Register (IDR) access functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Stores an 8-bit data in the Independent Data(ID) register.
  * @param  CRC_IDValue: 8-bit value to be stored in the ID register 					
  * @retval None
  */
void CRC_SetIDRegister(uint8_t CRC_IDValue)
{
  CRC->IDR = CRC_IDValue;
}

/**
  * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
  * @param  None
  * @retval 8-bit value of the ID register 
  */
uint8_t CRC_GetIDRegister(void)
{
  return (CRC->IDR);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_crs.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of CRS peripheral applicable only on STM32F042 and 
  *          STM32F072 devices:
  *            + Configuration of the CRS peripheral
  *            + Interrupts and flags management
  *              
  *
  *  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]
    
         (+) Enable CRS AHB clock using RCC_APB1eriphClockCmd(RCC_APB1Periph_CRS, ENABLE)
             function

      
     @endverbatim
  *  
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


/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CRS 
  * @brief CRS driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* CRS Flag Mask */
#define FLAG_MASK_CRS                 ((uint32_t)0x700)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRS_Private_Functions
  * @{
  */

/** @defgroup CRS_Group1 Configuration of the CRS functions
 *  @brief   Configuration of the CRS  functions 
 *
@verbatim
 ===============================================================================
                     ##### CRS configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes CRS peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CRS_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CRS, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CRS, DISABLE);
}

/**
  * @brief  Adjusts the Internal High Speed 48 oscillator (HSI 48) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI48 RC.
  * @note   This function can be called only when the AUTOTRIMEN bit is reset.
  * @param  CRS_HSI48CalibrationValue: 
  * @retval None
  */
void CRS_AdjustHSI48CalibrationValue(uint8_t CRS_HSI48CalibrationValue)
{
  /* Clear TRIM[5:0] bits */
  CRS->CR &= ~CRS_CR_TRIM;
  
  /* Set the TRIM[5:0] bits according to CRS_HSI48CalibrationValue value */
  CRS->CR |= (uint32_t)((uint32_t)CRS_HSI48CalibrationValue << 8);

}

/**
  * @brief  Enables or disables the oscillator clock for frequency error counter.
  * @note   when the CEN bit is set the CRS_CFGR register becomes write-protected.
  * @param  NewState: new state of the frequency error counter.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRS_FrequencyErrorCounterCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
     CRS->CR |= CRS_CR_CEN;
  }
  else
  {
    CRS->CR &= ~CRS_CR_CEN;
  }
}

/**
  * @brief  Enables or disables the automatic hardware adjustement of TRIM bits.
  * @note   When the AUTOTRIMEN bit is set the CRS_CFGR register becomes write-protected.
  * @param  NewState: new state of the automatic trimming.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRS_AutomaticCalibrationCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    CRS->CR |= CRS_CR_AUTOTRIMEN;
  }
else
  {
    CRS->CR &= ~CRS_CR_AUTOTRIMEN;
  }
}

/**
  * @brief  Generate the software synchronization event
  * @param  None
  * @retval None
  */
void CRS_SoftwareSynchronizationGenerate(void)
{
  CRS->CR |= CRS_CR_SWSYNC;
}

/**
  * @brief  Adjusts the Internal High Speed 48 oscillator (HSI 48) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI48 RC.
  * @note   This function can be called only when the CEN bit is reset.
  * @param  CRS_ReloadValue: specifies the HSI calibration trimming value.
  *          This parameter must be a number between 0 and .
  * @retval None
  */
void CRS_FrequencyErrorCounterReload(uint32_t CRS_ReloadValue)
{
 
  /* Clear RELOAD[15:0] bits */
  CRS->CFGR &= ~CRS_CFGR_RELOAD;
  
  /* Set the RELOAD[15:0] bits according to CRS_ReloadValue value */
  CRS->CFGR |= (uint32_t)CRS_ReloadValue;

}

/**
  * @brief  
  * @note   This function can be called only when the CEN bit is reset.
  * @param  CRS_ErrorLimitValue: specifies the HSI calibration trimming value.
  *          This parameter must be a number between 0 and .
  * @retval None
  */
void CRS_FrequencyErrorLimitConfig(uint8_t CRS_ErrorLimitValue)
{
  /* Clear FELIM[7:0] bits */
  CRS->CFGR &= ~CRS_CFGR_FELIM;
  
  /* Set the FELIM[7:0] bits according to CRS_ErrorLimitValue value */
  CRS->CFGR |= (uint32_t)CRS_ErrorLimitValue;
}

/**
  * @brief  
  * @note   This function can be called only when the CEN bit is reset.
  * @param  CRS_Prescaler: specifies the HSI calibration trimming value.
  *          This parameter can be one of the following values:
  *            @arg CRS_SYNC_Div1:   
  *            @arg CRS_SYNC_Div2:   
  *            @arg CRS_SYNC_Div4:   
  *            @arg CRS_SYNC_Div8:   
  *            @arg CRS_SYNC_Div16:  
  *            @arg CRS_SYNC_Div32:  
  *            @arg CRS_SYNC_Div64: 
  *            @arg CRS_SYNC_Div128: 
  * @retval None
  */
void CRS_SynchronizationPrescalerConfig(uint32_t CRS_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_CRS_SYNC_DIV(CRS_Prescaler));
  
  /* Clear SYNCDIV[2:0] bits */
  CRS->CFGR &= ~CRS_CFGR_SYNCDIV;
  
  /* Set the CRS_CFGR_SYNCDIV[2:0] bits according to CRS_Prescaler value */
  CRS->CFGR |= CRS_Prescaler;
}

/**
  * @brief  
  * @note   This function can be called only when the CEN bit is reset.
  * @param  CRS_Source: .
  *          This parameter can be one of the following values:
  *            @arg CRS_SYNCSource_GPIO:   
  *            @arg CRS_SYNCSource_LSE:   
  *            @arg CRS_SYNCSource_USB:   
  * @retval None
  */
void CRS_SynchronizationSourceConfig(uint32_t CRS_Source)
{
  /* Check the parameters */
  assert_param(IS_CRS_SYNC_SOURCE(CRS_Source));
  
  /* Clear SYNCSRC[1:0] bits */
  CRS->CFGR &= ~CRS_CFGR_SYNCSRC;
  
  /* Set the SYNCSRC[1:0] bits according to CRS_Source value */
  CRS->CFGR |= CRS_Source;
}

/**
  * @brief  
  * @note   This function can be called only when the CEN bit is reset.
  * @param  CRS_Polarity: .
  *          This parameter can be one of the following values:
  *            @arg CRS_SYNCPolarity_Rising:   
  *            @arg CRS_SYNCPolarity_Falling:   
  * @retval None
  */
void CRS_SynchronizationPolarityConfig(uint32_t CRS_Polarity)
{
  /* Check the parameters */
  assert_param(IS_CRS_SYNC_POLARITY(CRS_Polarity));
  
  /* Clear SYNCSPOL bit */
  CRS->CFGR &= ~CRS_CFGR_SYNCPOL;
  
  /* Set the SYNCSPOL bits according to CRS_Polarity value */
  CRS->CFGR |= CRS_Polarity;
}

/**
  * @brief  Returns the Relaod value.
  * @param  None
  * @retval The reload value 
  */
uint32_t CRS_GetReloadValue(void)
{
  return ((uint32_t)(CRS->CFGR & CRS_CFGR_RELOAD));
}

/**
  * @brief  Returns the HSI48 Calibration value.
  * @param  None
  * @retval The reload value 
  */
uint32_t CRS_GetHSI48CalibrationValue(void)
{
  return (((uint32_t)(CRS->CR & CRS_CR_TRIM)) >> 8);
}

/**
  * @brief  Returns the frequency error capture.
  * @param  None
  * @retval The frequency error capture value 
  */
uint32_t CRS_GetFrequencyErrorValue(void)
{
  return ((uint32_t)(CRS->ISR & CRS_ISR_FECAP));
}

/**
  * @brief  Returns the frequency error direction.
  * @param  None
  * @retval The frequency error direction. The returned value can be one 
  *         of the following values:
  *           - 0x00: Up counting
  *           - 0x8000: Down counting   
  */
uint32_t CRS_GetFrequencyErrorDirection(void)
{
  return ((uint32_t)(CRS->ISR & CRS_ISR_FEDIR));
}

/** @defgroup CRS_Group2 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================
@endverbatim
  * @{
  */
/**
  * @brief  Enables or disables the specified CRS interrupts.
  * @param  CRS_IT: specifies the RCC interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *              @arg CRS_IT_SYNCOK: 
  *              @arg CRS_IT_SYNCWARN: 
  *              @arg CRS_IT_ERR: 
  *              @arg CRS_IT_ESYNC: 
  * @param  NewState: new state of the specified CRS interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRS_ITConfig(uint32_t CRS_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CRS_IT(CRS_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    CRS->CR |= CRS_IT;
  }
  else
  {
    CRS->CR &= ~CRS_IT;
  }
}

/**
  * @brief  Checks whether the specified CRS flag is set or not.
  * @param  CRS_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *              @arg CRS_FLAG_SYNCOK: 
  *              @arg CRS_FLAG_SYNCWARN: 
  *              @arg CRS_FLAG_ERR: 
  *              @arg CRS_FLAG_ESYNC:   
  *              @arg CRS_FLAG_TRIMOVF: 
  *              @arg CRS_FLAG_SYNCERR: 
  *              @arg CRS_FLAG_SYNCMISS: 
  * @retval The new state of CRS_FLAG (SET or RESET).
  */
FlagStatus CRS_GetFlagStatus(uint32_t CRS_FLAG)
{
  /* Check the parameters */
  assert_param(IS_CRS_FLAG(CRS_FLAG));

  return ((FlagStatus)(CRS->ISR & CRS_FLAG));
}

/**
  * @brief  Clears the CRS specified FLAG.
  * @param  CRS_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *              @arg CRS_FLAG_SYNCOK: 
  *              @arg CRS_FLAG_SYNCWARN: 
  *              @arg CRS_FLAG_ERR: 
  *              @arg CRS_FLAG_ESYNC:   
  *              @arg CRS_FLAG_TRIMOVF: 
  *              @arg CRS_FLAG_SYNCERR: 
  *              @arg CRS_FLAG_SYNCMISS: 
  * @retval None
  */
void CRS_ClearFlag(uint32_t CRS_FLAG)
{
  /* Check the parameters */
  assert_param(IS_CRS_FLAG(CRS_FLAG));
  
  if ((CRS_FLAG & FLAG_MASK_CRS)!= 0)
  {
    CRS->ICR |= CRS_ICR_ERRC;  
  }
  else
  {
    CRS->ICR |= CRS_FLAG;
  }
}

/**
  * @brief  Checks whether the specified CRS IT pending bit is set or not.
  * @param  CRS_IT: specifies the IT pending bit to check.
  *          This parameter can be one of the following values:
  *              @arg CRS_IT_SYNCOK: 
  *              @arg CRS_IT_SYNCWARN: 
  *              @arg CRS_IT_ERR: 
  *              @arg CRS_IT_ESYNC:   
  *              @arg CRS_IT_TRIMOVF: 
  *              @arg CRS_IT_SYNCERR: 
  *              @arg CRS_IT_SYNCMISS: 
  * @retval The new state of CRS_IT (SET or RESET).
  */
ITStatus CRS_GetITStatus(uint32_t CRS_IT)
{
  /* Check the parameters */
  assert_param(IS_CRS_GET_IT(CRS_IT));

  return ((ITStatus)(CRS->ISR & CRS_IT));
}

/**
  * @brief  Clears the CRS specified IT pending bi.
  * @param  CRS_FLAG: specifies the IT pending bi to clear.
  *          This parameter can be one of the following values:
  *              @arg CRS_IT_SYNCOK: 
  *              @arg CRS_IT_SYNCWARN: 
  *              @arg CRS_IT_ERR: 
  *              @arg CRS_IT_ESYNC:   
  *              @arg CRS_IT_TRIMOVF: 
  *              @arg CRS_IT_SYNCERR: 
  *              @arg CRS_IT_SYNCMISS: 
  * @retval None
  */
void CRS_ClearITPendingBit(uint32_t CRS_IT)
{
  /* Check the parameters */
  assert_param(IS_CRS_CLEAR_IT(CRS_IT));
  
  if ((CRS_IT & FLAG_MASK_CRS)!= 0)
  {
    CRS->ICR |= CRS_ICR_ERRC;  
  }
  else
  {
    CRS->ICR |= CRS_IT;
  }
}
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_dac.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Digital-to-Analog Converter (DAC) peripheral
  *          applicable only on STM32F051 and STM32F072 devices:
  *           + DAC channel configuration: trigger, output buffer, data format
  *           + DMA management
  *           + Interrupts and flags management
  *
  *  @verbatim
  *
 ===============================================================================
                        ##### DAC Peripheral features #####
 ===============================================================================
    [..] The device integrates two 12-bit Digital Analog Converters refered as
         DAC channel1 with DAC_OUT1 (PA4) and DAC_OUT2 (PA5) as outputs.
  
    [..] Digital to Analog conversion can be non-triggered using DAC_Trigger_None
         and DAC_OUTx is available once writing to DHRx register using 
         DAC_SetChannel1Data() or DAC_SetChannel2Data() 
  
    [..] Digital to Analog conversion can be triggered by:
         (#) External event: EXTI Line 9 (any GPIOx_Pin9) using DAC_Trigger_Ext_IT9.
             The used pin (GPIOx_Pin9) must be configured in input mode.
  
         (#) Timers TRGO: TIM2, TIM3,TIM7, TIM6 and TIM15 
             (DAC_Trigger_T2_TRGO, DAC_Trigger_T3_TRGO...)
             The timer TRGO event should be selected using TIM_SelectOutputTrigger()
  
         (#) Software using DAC_Trigger_Software
  
    [..] Each DAC integrates an output buffer that can be used to 
         reduce the output impedance, and to drive external loads directly
         without having to add an external operational amplifier.
         To enable the output buffer use  
         DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  
    [..] Refer to the device datasheet for more details about output impedance
         value with and without output buffer.
         
    [..] DAC wave generation feature
         Both DAC channels can be used to generate
             1- Noise wave using DAC_WaveGeneration_Noise
             2- Triangle wave using DAC_WaveGeneration_Triangle
  
    [..] The DAC data format can be:
         (#) 8-bit right alignment using DAC_Align_8b_R
         (#) 12-bit left alignment using DAC_Align_12b_L
         (#) 12-bit right alignment using DAC_Align_12b_R
  
    [..] The analog output voltage on each DAC channel pin is determined
         by the following equation: DAC_OUTx = VREF+ * DOR / 4095
         with  DOR is the Data Output Register
         VEF+ is the input voltage reference (refer to the device datasheet)
         e.g. To set DAC_OUT1 to 0.7V, use
         DAC_SetChannel1Data(DAC_Align_12b_R, 868);
         Assuming that VREF+ = 3.3, DAC_OUT1 = (3.3 * 868) / 4095 = 0.7V
  
    [..] A DMA1 request can be generated when an external trigger (but not
         a software trigger) occurs if DMA1 requests are enabled using
         DAC_DMACmd()
         DMA1 requests are mapped as following:
         (+) DAC channel1 is mapped on DMA1 channel3 which must be already 
             configured
         (+) DAC channel2 is mapped on DMA1 channel4 which must be already 
             configured
    
                      ##### How to use this driver #####
 ===============================================================================
    [..]
         (+) Enable DAC APB1 clock to get write access to DAC registers
             using RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE)
              
         (+) Configure DAC_OUTx (DAC_OUT1: PA4, DAC_OUT2: PA5) in analog mode
             using GPIO_Init() function  
              
         (+) Configure the DAC channel using DAC_Init()
              
         (+) Enable the DAC channel using DAC_Cmd()
  
    @endverbatim
  *
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


/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DAC 
  * @brief DAC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* CR register Mask */
#define CR_CLEAR_MASK              ((uint32_t)0x00000FFE) /* check the value of the mask */

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_SET            ((uint32_t)0x00000003) /*!< Only applicable for STM32F072 devices */
#define DUAL_SWTRIG_RESET          ((uint32_t)0xFFFFFFFC) /*!< Only applicable for STM32F072 devices */

/* DHR registers offsets */
#define DHR12R1_OFFSET             ((uint32_t)0x00000008)
#define DHR12R2_OFFSET             ((uint32_t)0x00000014) /*!< Only applicable for STM32F072 devices */
#define DHR12RD_OFFSET             ((uint32_t)0x00000020) /*!< Only applicable for STM32F072 devices */

/* DOR register offset */
#define DOR_OFFSET                 ((uint32_t)0x0000002C)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup DAC_Private_Functions
  * @{
  */ 

/** @defgroup DAC_Group1 DAC channels configuration
 *  @brief   DAC channels configuration: trigger, output buffer, data format 
 *
@verbatim
 ===============================================================================
  ##### DAC channels configuration: trigger, output buffer, data format #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void DAC_DeInit(void)
{
  /* Enable DAC reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, ENABLE);
  /* Release DAC from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, DISABLE);
}

/**
  * @brief  Initializes the DAC peripheral according to the specified parameters
  *         in the DAC_InitStruct.
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  DAC_InitStruct: pointer to a DAC_InitTypeDef structure that contains
  *         the configuration information for the  specified DAC channel.
  * @retval None
  */
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;

  /* Check the DAC parameters */
  assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
  assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
  assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));

/*---------------------------- DAC CR Configuration --------------------------*/
  /* Get the DAC CR value */
  tmpreg1 = DAC->CR;
  /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
  tmpreg1 &= ~(CR_CLEAR_MASK << DAC_Channel);
  /* Configure for the selected DAC channel: buffer output, trigger, 
     wave generation, mask/amplitude for wave generation */
  /* Set TSELx and TENx bits according to DAC_Trigger value */
  /* Set WAVEx bits according to DAC_WaveGeneration value */
  /* Set MAMPx bits according to DAC_LFSRUnmask_TriangleAmplitude value */ 
  /* Set BOFFx bit according to DAC_OutputBuffer value */   
  tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
             DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | \
             DAC_InitStruct->DAC_OutputBuffer);
  /* Calculate CR register value depending on DAC_Channel */
  tmpreg1 |= tmpreg2 << DAC_Channel;
  /* Write to DAC CR */
  DAC->CR = tmpreg1;
}

/**
  * @brief  Fills each DAC_InitStruct member with its default value.
  * @param  DAC_InitStruct: pointer to a DAC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
/*--------------- Reset DAC init structure parameters values -----------------*/
  /* Initialize the DAC_Trigger member */
  DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
  
  /* Initialize the DAC_WaveGeneration member */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
  
  /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  
  /* Initialize the DAC_OutputBuffer member */
  DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/**
  * @brief  Enables or disables the specified DAC channel.
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  NewState: new state of the DAC channel. 
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When the DAC channel is enabled the trigger source can no more be modified.
  * @retval None
  */
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel */
    DAC->CR |= (DAC_CR_EN1 << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC channel */
    DAC->CR &= (~(DAC_CR_EN1 << DAC_Channel));
  }
}

/**
  * @brief  Enables or disables the selected DAC channel software trigger.
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  NewState: new state of the selected DAC channel software trigger.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for the selected DAC channel */
    DAC->SWTRIGR |= (uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4);
  }
  else
  {
    /* Disable software trigger for the selected DAC channel */
    DAC->SWTRIGR &= ~((uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4));
  }
}

/**
  * @brief  Enables or disables simultaneously the two DAC channels software triggers.
  *         This function is applicable only for STM32F072 devices.  
  * @param  NewState: new state of the DAC channels software triggers.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for both DAC channels */
    DAC->SWTRIGR |= DUAL_SWTRIG_SET;
  }
  else
  {
    /* Disable software trigger for both DAC channels */
    DAC->SWTRIGR &= DUAL_SWTRIG_RESET;
  }
}

/**
  * @brief  Enables or disables the selected DAC channel wave generation.
  *         This function is applicable only for STM32F072 devices.  
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_Wave: specifies the wave type to enable or disable.
  *          This parameter can be:
  *            @arg DAC_Wave_Noise: noise wave generation
  *            @arg DAC_Wave_Triangle: triangle wave generation
  * @param  NewState: new state of the selected DAC channel wave generation.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_WAVE(DAC_Wave)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected wave generation for the selected DAC channel */
    DAC->CR |= DAC_Wave << DAC_Channel;
  }
  else
  {
    /* Disable the selected wave generation for the selected DAC channel */
    DAC->CR &= ~(DAC_Wave << DAC_Channel);
  }
}

/**
  * @brief  Set the specified data holding register value for DAC channel1.
  * @param  DAC_Align: Specifies the data alignment for DAC channel1.
  *          This parameter can be one of the following values:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @param  Data: Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data)
{  
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));
  
  tmp = (uint32_t)DAC_BASE; 
  tmp += DHR12R1_OFFSET + DAC_Align;

  /* Set the DAC channel1 selected data holding register */
  *(__IO uint32_t *) tmp = Data;
}

/**
  * @brief  Sets the specified data holding register value for DAC channel2.
  *         This function is applicable only for STM32F072 devices.  
  * @param  DAC_Align: Specifies the data alignment for DAC channel2.
  *          This parameter can be:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @param  Data: Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));
  
  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12R2_OFFSET + DAC_Align;

  /* Set the DAC channel2 selected data holding register */
  *(__IO uint32_t *)tmp = Data;
}

/**
  * @brief  Sets the specified data holding register value for dual channel DAC.
  *         This function is applicable only for STM32F072 devices.  
  * @param  DAC_Align: Specifies the data alignment for dual channel DAC.
  *          This parameter can be:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @param  Data2: Data for DAC Channel2 to be loaded in the selected data holding register.
  * @param  Data1: Data for DAC Channel1 to be loaded in the selected data  holding register.
  * @note   In dual mode, a unique register access is required to write in both
  *          DAC channels at the same time.
  * @retval None
  */
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
  uint32_t data = 0, tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data1));
  assert_param(IS_DAC_DATA(Data2));
  
  /* Calculate and set dual DAC data holding register value */
  if (DAC_Align == DAC_Align_8b_R)
  {
    data = ((uint32_t)Data2 << 8) | Data1; 
  }
  else
  {
    data = ((uint32_t)Data2 << 16) | Data1;
  }
  
  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12RD_OFFSET + DAC_Align;

  /* Set the dual DAC selected data holding register */
  *(__IO uint32_t *)tmp = data;
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @retval The selected DAC channel data output value.
  */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel)
{
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  
  tmp = (uint32_t) DAC_BASE ;
  tmp += DOR_OFFSET + ((uint32_t)DAC_Channel >> 2);
  
  /* Returns the DAC channel data output register value */
  return (uint16_t) (*(__IO uint32_t*) tmp);
}

/**
  * @}
  */

/** @defgroup DAC_Group2 DMA management functions
 *  @brief   DMA management functions
 *
@verbatim   
 ===============================================================================
                    ##### DMA management functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified DAC channel DMA request.
  *         When enabled DMA1 is generated when an external trigger (EXTI Line9,
  *         TIM2, TIM3, TIM6 or TIM15  but not a software trigger) occurs
  * @param  DAC_Channel: the selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  NewState: new state of the selected DAC channel DMA request.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   The DAC channel1 is mapped on DMA1 channel3 which must be already configured. 
  * @note   The DAC channel2 is mapped on DMA1 channel4 which must be already configured.  
  * @retval None
  */
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel DMA request */
    DAC->CR |= (DAC_CR_DMAEN1 << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC channel DMA request */
    DAC->CR &= (~(DAC_CR_DMAEN1 << DAC_Channel));
  }
}

/**
  * @}
  */

/** @defgroup DAC_Group3 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified DAC interrupts.
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  DAC_IT: specifies the DAC interrupt sources to be enabled or disabled. 
  *          This parameter can be the following values:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @note   The DMA underrun occurs when a second external trigger arrives before the 
  *         acknowledgement for the first external trigger is received (first request).
  * @param  NewState: new state of the specified DAC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */ 
void DAC_ITConfig(uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState)  
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_DAC_IT(DAC_IT)); 

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC interrupts */
    DAC->CR |=  (DAC_IT << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC interrupts */
    DAC->CR &= (~(uint32_t)(DAC_IT << DAC_Channel));
  }
}

/**
  * @brief  Checks whether the specified DAC flag is set or not.
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  DAC_FLAG: specifies the flag to check. 
  *          This parameter can be only of the following value:
  *            @arg DAC_FLAG_DMAUDR: DMA underrun flag
  * @note   The DMA underrun occurs when a second external trigger arrives before the 
  *         acknowledgement for the first external trigger is received (first request).
  * @retval The new state of DAC_FLAG (SET or RESET).
  */
FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  /* Check the status of the specified DAC flag */
  if ((DAC->SR & (DAC_FLAG << DAC_Channel)) != (uint8_t)RESET)
  {
    /* DAC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* DAC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the DAC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the DAC channel's pending flags.
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  DAC_FLAG: specifies the flag to clear. 
  *          This parameter can be of the following value:
  *            @arg DAC_FLAG_DMAUDR: DMA underrun flag                           
  * @retval None
  */
void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  /* Clear the selected DAC flags */
  DAC->SR = (DAC_FLAG << DAC_Channel);
}

/**
  * @brief  Checks whether the specified DAC interrupt has occurred or not.
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  DAC_IT: specifies the DAC interrupt source to check. 
  *          This parameter can be the following values:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @note   The DMA underrun occurs when a second external trigger arrives before the 
  *         acknowledgement for the first external trigger is received (first request).
  * @retval The new state of DAC_IT (SET or RESET).
  */
ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT));

  /* Get the DAC_IT enable bit status */
  enablestatus = (DAC->CR & (DAC_IT << DAC_Channel)) ;
  
  /* Check the status of the specified DAC interrupt */
  if (((DAC->SR & (DAC_IT << DAC_Channel)) != (uint32_t)RESET) && enablestatus)
  {
    /* DAC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* DAC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the DAC_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the DAC channel's interrupt pending bits.
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected, applicable only for STM32F072 devices
  * @param  DAC_IT: specifies the DAC interrupt pending bit to clear.
  *          This parameter can be the following values:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask                                                    
  * @retval None
  */
void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT)); 

  /* Clear the selected DAC interrupt pending bits */
  DAC->SR = (DAC_IT << DAC_Channel);
}

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_dbgmcu.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Debug MCU (DBGMCU) peripheral:
  *           + Device and Revision ID management
  *           + Peripherals Configuration
  *  @verbatim
  *  @endverbatim
  *
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


/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DBGMCU 
  * @brief DBGMCU driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup DBGMCU_Private_Functions 
  * @{
  */
  

/** @defgroup DBGMCU_Group1 Device and Revision ID management functions
 *  @brief   Device and Revision ID management functions
 *
@verbatim
  ==============================================================================
            ##### Device and Revision ID management functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Returns the device revision identifier.
  * @param  None
  * @retval Device revision identifier
  */
uint32_t DBGMCU_GetREVID(void)
{
   return(DBGMCU->IDCODE >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @param  None
  * @retval Device identifier
  */
uint32_t DBGMCU_GetDEVID(void)
{
   return(DBGMCU->IDCODE & IDCODE_DEVID_MASK);
}

/**
  * @}
  */
  
/** @defgroup DBGMCU_Group2 Peripherals Configuration functions
 *  @brief   Peripherals Configuration
 *
@verbatim
  ==============================================================================
               ##### Peripherals Configuration functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Configures low power mode behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the low power mode.
  *          This parameter can be any combination of the following values:
  *             @arg DBGMCU_STOP: Keep debugger connection during STOP mode
  *             @arg DBGMCU_STANDBY: Keep debugger connection during STANDBY mode
  * @param  NewState: new state of the specified low power mode in Debug mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->CR |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->CR &= ~DBGMCU_Periph;
  }
}


/**
  * @brief  Configures APB1 peripheral behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the APB1 peripheral.
  *          This parameter can be any combination of the following values:
  *             @arg DBGMCU_TIM2_STOP: TIM2 counter stopped when Core is halted, 
  *                  not applicable for STM32F030 devices   
  *             @arg DBGMCU_TIM3_STOP: TIM3 counter stopped when Core is halted
  *             @arg DBGMCU_TIM6_STOP: TIM6 counter stopped when Core is halted
  *             @arg DBGMCU_TIM7_STOP: TIM7 counter stopped when Core is halted, 
  *                  applicable only for STM32F072 devices               
  *             @arg DBGMCU_TIM14_STOP: TIM14 counter stopped when Core is halted
  *             @arg DBGMCU_RTC_STOP: RTC Calendar and Wakeup counter stopped 
  *                                   when Core is halted.
  *             @arg DBGMCU_WWDG_STOP: Debug WWDG stopped when Core is halted
  *             @arg DBGMCU_IWDG_STOP: Debug IWDG stopped when Core is halted
  *             @arg DBGMCU_I2C1_SMBUS_TIMEOUT: I2C1 SMBUS timeout mode stopped 
  *                                             when Core is halted
  *             @arg DBGMCU_CAN1_STOP: Debug CAN1 stopped when Core is halted, 
  *                  applicable only for STM32F042 and STM32F072 devices               
  * @param  NewState: new state of the specified APB1 peripheral in Debug mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_APB1PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->APB1FZ |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->APB1FZ &= ~DBGMCU_Periph;
  }
}

/**
  * @brief  Configures APB2 peripheral behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the APB2 peripheral.
  *          This parameter can be any combination of the following values:
  *             @arg DBGMCU_TIM1_STOP: TIM1 counter stopped when Core is halted
  *             @arg DBGMCU_TIM15_STOP: TIM15 counter stopped when Core is halted
  *             @arg DBGMCU_TIM16_STOP: TIM16 counter stopped when Core is halted
  *             @arg DBGMCU_TIM17_STOP: TIM17 counter stopped when Core is halted
  * @param  NewState: new state of the specified APB2 peripheral in Debug mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_APB2PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->APB2FZ |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->APB2FZ &= ~DBGMCU_Periph;
  }
}

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_dma.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Direct Memory Access controller (DMA):
  *           + Initialization and Configuration
  *           + Data Counter
  *           + Interrupts and flags management
  *
  *  @verbatim
  ==============================================================================
                      ##### How to use this driver #####
  ==============================================================================
    [..]
    (#) Enable The DMA controller clock using 
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE) function for DMA1.
    (#) Enable and configure the peripheral to be connected to the DMA channel
       (except for internal SRAM / FLASH memories: no initialization is necessary).
    (#) For a given Channel, program the Source and Destination addresses, 
        the transfer Direction, the Buffer Size, the Peripheral and Memory 
        Incrementation mode and Data Size, the Circular or Normal mode, 
        the channel transfer Priority and the Memory-to-Memory transfer 
        mode (if needed) using the DMA_Init() function.
    (#) Enable the NVIC and the corresponding interrupt(s) using the function 
        DMA_ITConfig() if you need to use DMA interrupts.
    (#) Enable the DMA channel using the DMA_Cmd() function.
    (#) Activate the needed channel Request using PPP_DMACmd() function for 
        any PPP peripheral except internal SRAM and FLASH (ie. SPI, USART ...) 
        The function allowing this operation is provided in each PPP peripheral 
        driver (ie. SPI_DMACmd for SPI peripheral).
    (#) Optionally, you can configure the number of data to be transferred
        when the channel is disabled (ie. after each Transfer Complete event
        or when a Transfer Error occurs) using the function DMA_SetCurrDataCounter().
        And you can get the number of remaining data to be transferred using 
        the function DMA_GetCurrDataCounter() at run time (when the DMA channel is
        enabled and running).
    (#) To control DMA events you can use one of the following two methods:
        (##) Check on DMA channel flags using the function DMA_GetFlagStatus().
        (##) Use DMA interrupts through the function DMA_ITConfig() at initialization
             phase and DMA_GetITStatus() function into interrupt routines in
             communication phase.
             After checking on a flag you should clear it using DMA_ClearFlag()
             function. And after checking on an interrupt event you should 
             clear it using DMA_ClearITPendingBit() function.
    @endverbatim
  *
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


/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DMA 
  * @brief DMA driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CCR_CLEAR_MASK   ((uint32_t)0xFFFF800F) /* DMA Channel config registers Masks */
#define FLAG_Mask        ((uint32_t)0x10000000) /* DMA2 FLAG mask */

/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_CHANNEL1_IT_MASK    ((uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1))
#define DMA1_CHANNEL2_IT_MASK    ((uint32_t)(DMA_ISR_GIF2 | DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TEIF2))
#define DMA1_CHANNEL3_IT_MASK    ((uint32_t)(DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TEIF3))
#define DMA1_CHANNEL4_IT_MASK    ((uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4))
#define DMA1_CHANNEL5_IT_MASK    ((uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5))
#define DMA1_CHANNEL6_IT_MASK    ((uint32_t)(DMA_ISR_GIF6 | DMA_ISR_TCIF6 | DMA_ISR_HTIF6 | DMA_ISR_TEIF6)) /*!< Only applicable for STM32F072 and STM32F091 devices */
#define DMA1_CHANNEL7_IT_MASK    ((uint32_t)(DMA_ISR_GIF7 | DMA_ISR_TCIF7 | DMA_ISR_HTIF7 | DMA_ISR_TEIF7)) /*!< Only applicable for STM32F072 and STM32F091 devices */
    
/* DMA2 Channelx interrupt pending bit masks: Only applicable for STM32F091 devices */
#define DMA2_CHANNEL1_IT_MASK    ((uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1))
#define DMA2_CHANNEL2_IT_MASK    ((uint32_t)(DMA_ISR_GIF2 | DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TEIF2))
#define DMA2_CHANNEL3_IT_MASK    ((uint32_t)(DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TEIF3))
#define DMA2_CHANNEL4_IT_MASK    ((uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4))
#define DMA2_CHANNEL5_IT_MASK    ((uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup DMA_Private_Functions 
  * @{
  */

/** @defgroup DMA_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim   
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This subsection provides functions allowing to initialize the DMA channel 
         source and destination addresses, incrementation and data sizes, transfer 
         direction, buffer size, circular/normal mode selection, memory-to-memory 
         mode selection and channel priority value.
    [..] The DMA_Init() function follows the DMA configuration procedures as described 
         in reference manual (RM0091).
@endverbatim
  * @{
  */
    
/**
  * @brief  Deinitializes the DMAy Channelx registers to their default reset
  *         values.
  * @param  DMAy_Channelx: where y can be 1 to select the DMA and 
  *         x can be 1 to 7 for DMA1 to select the DMA Channel.
  * @note   Channel 6 and 7 are available only for STM32F072 devices.
  * @retval None
  */
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

  /* Disable the selected DMAy Channelx */
  DMAy_Channelx->CCR &= (uint16_t)(~DMA_CCR_EN);

  /* Reset DMAy Channelx control register */
  DMAy_Channelx->CCR  = 0;

  /* Reset DMAy Channelx remaining bytes register */
  DMAy_Channelx->CNDTR = 0;

  /* Reset DMAy Channelx peripheral address register */
  DMAy_Channelx->CPAR  = 0;

  /* Reset DMAy Channelx memory address register */
  DMAy_Channelx->CMAR = 0;

  if (DMAy_Channelx == DMA1_Channel1)
  {
    /* Reset interrupt pending bits for DMA1 Channel1 */
    DMA1->IFCR |= DMA1_CHANNEL1_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel2)
  {
    /* Reset interrupt pending bits for DMA1 Channel2 */
    DMA1->IFCR |= DMA1_CHANNEL2_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel3)
  {
    /* Reset interrupt pending bits for DMA1 Channel3 */
    DMA1->IFCR |= DMA1_CHANNEL3_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel4)
  {
    /* Reset interrupt pending bits for DMA1 Channel4 */
    DMA1->IFCR |= DMA1_CHANNEL4_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel5)
  {
    /* Reset interrupt pending bits for DMA1 Channel5 */
    DMA1->IFCR |= DMA1_CHANNEL5_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel6)
  {
    /* Reset interrupt pending bits for DMA1 Channel6 */
    DMA1->IFCR |= DMA1_CHANNEL6_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel7)
  {
    /* Reset interrupt pending bits for DMA1 Channel7 */
    DMA1->IFCR |= DMA1_CHANNEL7_IT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel1)
  {
    /* Reset interrupt pending bits for DMA2 Channel1 */
    DMA2->IFCR |= DMA2_CHANNEL1_IT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel2)
  {
    /* Reset interrupt pending bits for DMA2 Channel2 */
    DMA2->IFCR |= DMA2_CHANNEL2_IT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel3)
  {
    /* Reset interrupt pending bits for DMA2 Channel3 */
    DMA2->IFCR |= DMA2_CHANNEL3_IT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel4)
  {
    /* Reset interrupt pending bits for DMA2 Channel4 */
    DMA2->IFCR |= DMA2_CHANNEL4_IT_MASK;
  }
  else
  { 
    if (DMAy_Channelx == DMA2_Channel5)
    {
      /* Reset interrupt pending bits for DMA2 Channel5 */
      DMA2->IFCR |= DMA2_CHANNEL5_IT_MASK;
    }
  }
}

/**
  * @brief  Initializes the DMAy Channelx according to the specified parameters 
  *         in the DMA_InitStruct.
  * @param  DMAy_Channelx: where y can be 1 to select the DMA and x can be 1 to 7
  *         for DMA1 to select the DMA Channel and 1 to 5 for DMA2 to select the DMA Channel.
  * @note   DMA1 Channel 6 and 7 are available only for STM32F072 and STM32F091 devices. 
  * @note   DMA2 Channel 1 to 5 are available only for STM32F091 devices.   
  * @param  DMA_InitStruct: pointer to a DMA_InitTypeDef structure that contains
  *         the configuration information for the specified DMA Channel.
  * @retval None
  */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_DIR(DMA_InitStruct->DMA_DIR));
  assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
  assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
  assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
  assert_param(IS_DMA_M2M_STATE(DMA_InitStruct->DMA_M2M));

/*--------------------------- DMAy Channelx CCR Configuration ----------------*/
  /* Get the DMAy_Channelx CCR value */
  tmpreg = DMAy_Channelx->CCR;

  /* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
  tmpreg &= CCR_CLEAR_MASK;

  /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
  /* Set DIR bit according to DMA_DIR value */
  /* Set CIRC bit according to DMA_Mode value */
  /* Set PINC bit according to DMA_PeripheralInc value */
  /* Set MINC bit according to DMA_MemoryInc value */
  /* Set PSIZE bits according to DMA_PeripheralDataSize value */
  /* Set MSIZE bits according to DMA_MemoryDataSize value */
  /* Set PL bits according to DMA_Priority value */
  /* Set the MEM2MEM bit according to DMA_M2M value */
  tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
            DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
            DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
            DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;

  /* Write to DMAy Channelx CCR */
  DMAy_Channelx->CCR = tmpreg;

/*--------------------------- DMAy Channelx CNDTR Configuration --------------*/
  /* Write to DMAy Channelx CNDTR */
  DMAy_Channelx->CNDTR = DMA_InitStruct->DMA_BufferSize;

/*--------------------------- DMAy Channelx CPAR Configuration ---------------*/
  /* Write to DMAy Channelx CPAR */
  DMAy_Channelx->CPAR = DMA_InitStruct->DMA_PeripheralBaseAddr;

/*--------------------------- DMAy Channelx CMAR Configuration ---------------*/
  /* Write to DMAy Channelx CMAR */
  DMAy_Channelx->CMAR = DMA_InitStruct->DMA_MemoryBaseAddr;
}

/**
  * @brief  Fills each DMA_InitStruct member with its default value.
  * @param  DMA_InitStruct: pointer to a DMA_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
/*-------------- Reset DMA init structure parameters values ------------------*/
  /* Initialize the DMA_PeripheralBaseAddr member */
  DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
  /* Initialize the DMA_MemoryBaseAddr member */
  DMA_InitStruct->DMA_MemoryBaseAddr = 0;
  /* Initialize the DMA_DIR member */
  DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralSRC;
  /* Initialize the DMA_BufferSize member */
  DMA_InitStruct->DMA_BufferSize = 0;
  /* Initialize the DMA_PeripheralInc member */
  DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  /* Initialize the DMA_MemoryInc member */
  DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;
  /* Initialize the DMA_PeripheralDataSize member */
  DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  /* Initialize the DMA_MemoryDataSize member */
  DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  /* Initialize the DMA_Mode member */
  DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
  /* Initialize the DMA_Priority member */
  DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
  /* Initialize the DMA_M2M member */
  DMA_InitStruct->DMA_M2M = DMA_M2M_Disable;
}

/**
  * @brief  Enables or disables the specified DMAy Channelx.
  * @param  DMAy_Channelx: where y can be 1 to select the DMA and x can be 1 to 7
  *         for DMA1 to select the DMA Channel and 1 to 5 for DMA2 to select the DMA Channel.
  * @note   DMA1 Channel 6 and 7 are available only for STM32F072 and STM32F091 devices. 
  * @note   DMA2 Channel 1 to 5 are available only for STM32F091 devices. 
  * @param  NewState: new state of the DMAy Channelx. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMAy Channelx */
    DMAy_Channelx->CCR |= DMA_CCR_EN;
  }
  else
  {
    /* Disable the selected DMAy Channelx */
    DMAy_Channelx->CCR &= (uint16_t)(~DMA_CCR_EN);
  }
}

/**
  * @brief  Configure the DMAx channels remapping.
  * @param  DMAy: where x can be 1 or 2 to select the DMA peripheral.    
  * @param  DMAy_CHx_RemapRequest: where y can be 1 or 2 to select the DMA and x can be 1 to 7
  *         for DMA1 to select the DMA1 Channel and can be 1 to 5 for DMA2 to select the DMA2 Channel.
  * @note   This function is available only for STM32F091 devices. 
  * @retval None
  */
void DMA_RemapConfig(DMA_TypeDef* DMAy, uint32_t DMAx_CHy_RemapRequest)
{
  assert_param(IS_DMA_ALL_LIST(DMAy));
  
  if (DMAy == DMA1)
  {
    assert_param(IS_DMA1_REMAP(DMAx_CHy_RemapRequest));  
  }
  else
  {
    assert_param(IS_DMA2_REMAP(DMAx_CHy_RemapRequest)); 
  }

  DMAy->RMPCR &= ~((uint32_t)0x0F << (uint32_t)((DMAx_CHy_RemapRequest >> 28) * 4)); 
  DMAy->RMPCR |= (uint32_t)(DMAx_CHy_RemapRequest & 0x0FFFFFFF);  
}

/**
  * @}
  */

/** @defgroup DMA_Group2 Data Counter functions
 *  @brief   Data Counter functions 
 *
@verbatim
 ===============================================================================
                      ##### Data Counter functions #####
 ===============================================================================
    [..] This subsection provides function allowing to configure and read the buffer 
         size (number of data to be transferred).The DMA data counter can be written 
         only when the DMA channel is disabled (ie. after transfer complete event).
    [..] The following function can be used to write the Channel data counter value:
         (+) void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t 
             DataNumber).
    -@- It is advised to use this function rather than DMA_Init() in situations 
        where only the Data buffer needs to be reloaded.
    [..] The DMA data counter can be read to indicate the number of remaining transfers 
         for the relative DMA channel. This counter is decremented at the end of each 
         data transfer and when the transfer is complete: 
         (+) If Normal mode is selected: the counter is set to 0.
         (+) If Circular mode is selected: the counter is reloaded with the initial 
         value(configured before enabling the DMA channel).
    [..] The following function can be used to read the Channel data counter value:
         (+) uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx).

@endverbatim
  * @{
  */

/**
  * @brief  Sets the number of data units in the current DMAy Channelx transfer.
  * @param  DMAy_Channelx: where y can be 1 to select the DMA and x can be 1 to 7
  *         for DMA1 to select the DMA Channel and 1 to 5 for DMA2 to select the DMA Channel.
  * @note   DMA1 Channel 6 and 7 are available only for STM32F072 and STM32F091 devices. 
  * @note   DMA2 Channel 1 to 5 are available only for STM32F091 devices. 
  * @param  DataNumber: The number of data units in the current DMAy Channelx
  *         transfer.
  * @note   This function can only be used when the DMAy_Channelx is disabled.
  * @retval None.
  */
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

/*--------------------------- DMAy Channelx CNDTR Configuration --------------*/
  /* Write to DMAy Channelx CNDTR */
  DMAy_Channelx->CNDTR = DataNumber;
}

/**
  * @brief  Returns the number of remaining data units in the current
  *         DMAy Channelx transfer.
  * @param  DMAy_Channelx: where y can be 1 to select the DMA and x can be 1 to 7
  *         for DMA1 to select the DMA Channel and 1 to 5 for DMA2 to select the DMA Channel.
  * @note   DMA1 Channel 6 and 7 are available only for STM32F072 and STM32F091 devices. 
  * @note   DMA2 Channel 1 to 5 are available only for STM32F091 devices. 
  * @retval The number of remaining data units in the current DMAy Channelx
  *         transfer.
  */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* Return the number of remaining data units for DMAy Channelx */
  return ((uint16_t)(DMAy_Channelx->CNDTR));
}

/**
  * @}
  */

/** @defgroup DMA_Group3 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim
 ===============================================================================
          ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This subsection provides functions allowing to configure the DMA Interrupts 
         sources and check or clear the flags or pending bits status.
         The user should identify which mode will be used in his application to manage 
         the DMA controller events: Polling mode or Interrupt mode. 
  *** Polling Mode ***
  ====================
    [..] Each DMA channel can be managed through 4 event Flags:(y : DMA Controller 
         number  x : DMA channel number ).
         (#) DMAy_FLAG_TCx : to indicate that a Transfer Complete event occurred.
         (#) DMAy_FLAG_HTx : to indicate that a Half-Transfer Complete event occurred.
         (#) DMAy_FLAG_TEx : to indicate that a Transfer Error occurred.
         (#) DMAy_FLAG_GLx : to indicate that at least one of the events described 
             above occurred.
    -@- Clearing DMAy_FLAG_GLx results in clearing all other pending flags of the 
        same channel (DMAy_FLAG_TCx, DMAy_FLAG_HTx and DMAy_FLAG_TEx).
    [..]In this Mode it is advised to use the following functions:
        (+) FlagStatus DMA_GetFlagStatus(uint32_t DMA_FLAG);
        (+) void DMA_ClearFlag(uint32_t DMA_FLAG);

  *** Interrupt Mode ***
  ======================
    [..] Each DMA channel can be managed through 4 Interrupts:
    (+) Interrupt Source
       (##) DMA_IT_TC: specifies the interrupt source for the Transfer Complete 
            event.
       (##) DMA_IT_HT : specifies the interrupt source for the Half-transfer Complete 
            event.
       (##) DMA_IT_TE : specifies the interrupt source for the transfer errors event.
       (##) DMA_IT_GL : to indicate that at least one of the interrupts described 
            above occurred.
    -@@- Clearing DMA_IT_GL interrupt results in clearing all other interrupts of 
        the same channel (DMA_IT_TCx, DMA_IT_HT and DMA_IT_TE).
    [..]In this Mode it is advised to use the following functions:
        (+) void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, 
            FunctionalState NewState);
        (+) ITStatus DMA_GetITStatus(uint32_t DMA_IT);
        (+) void DMA_ClearITPendingBit(uint32_t DMA_IT);

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified DMAy Channelx interrupts.
  * @param  DMAy_Channelx: where y can be 1 to select the DMA and x can be 1 to 7
  *         for DMA1 to select the DMA Channel and 1 to 5 for DMA2 to select the DMA Channel.
  * @note   DMA1 Channel 6 and 7 are available only for STM32F072 and STM32F091 devices. 
  * @note   DMA2 Channel 1 to 5 are available only for STM32F091 devices.  
  * @param  DMA_IT: specifies the DMA interrupts sources to be enabled
  *         or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC: Transfer complete interrupt mask
  *            @arg DMA_IT_HT: Half transfer interrupt mask
  *            @arg DMA_IT_TE: Transfer error interrupt mask
  * @param  NewState: new state of the specified DMA interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_CONFIG_IT(DMA_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMA interrupts */
    DMAy_Channelx->CCR |= DMA_IT;
  }
  else
  {
    /* Disable the selected DMA interrupts */
    DMAy_Channelx->CCR &= ~DMA_IT;
  }
}

/**
  * @brief  Checks whether the specified DMAy Channelx flag is set or not.
  * @param  DMA_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg DMA1_FLAG_GL1: DMA1 Channel1 global flag.
  *            @arg DMA1_FLAG_TC1: DMA1 Channel1 transfer complete flag.
  *            @arg DMA1_FLAG_HT1: DMA1 Channel1 half transfer flag.
  *            @arg DMA1_FLAG_TE1: DMA1 Channel1 transfer error flag.
  *            @arg DMA1_FLAG_GL2: DMA1 Channel2 global flag.
  *            @arg DMA1_FLAG_TC2: DMA1 Channel2 transfer complete flag.
  *            @arg DMA1_FLAG_HT2: DMA1 Channel2 half transfer flag.
  *            @arg DMA1_FLAG_TE2: DMA1 Channel2 transfer error flag.
  *            @arg DMA1_FLAG_GL3: DMA1 Channel3 global flag.
  *            @arg DMA1_FLAG_TC3: DMA1 Channel3 transfer complete flag.
  *            @arg DMA1_FLAG_HT3: DMA1 Channel3 half transfer flag.
  *            @arg DMA1_FLAG_TE3: DMA1 Channel3 transfer error flag.
  *            @arg DMA1_FLAG_GL4: DMA1 Channel4 global flag.
  *            @arg DMA1_FLAG_TC4: DMA1 Channel4 transfer complete flag.
  *            @arg DMA1_FLAG_HT4: DMA1 Channel4 half transfer flag.
  *            @arg DMA1_FLAG_TE4: DMA1 Channel4 transfer error flag.
  *            @arg DMA1_FLAG_GL5: DMA1 Channel5 global flag.
  *            @arg DMA1_FLAG_TC5: DMA1 Channel5 transfer complete flag.
  *            @arg DMA1_FLAG_HT5: DMA1 Channel5 half transfer flag.
  *            @arg DMA1_FLAG_TE5: DMA1 Channel5 transfer error flag.
  *            @arg DMA1_FLAG_GL6: DMA1 Channel6 global flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_TC6: DMA1 Channel6 transfer complete flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_HT6: DMA1 Channel6 half transfer flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_TE6: DMA1 Channel6 transfer error flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_GL7: DMA1 Channel7 global flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_TC7: DMA1 Channel7 transfer complete flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_HT7: DMA1 Channel7 half transfer flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_TE7: DMA1 Channel7 transfer error flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA2_FLAG_GL1: DMA2 Channel1 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC1: DMA2 Channel1 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT1: DMA2 Channel1 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE1: DMA2 Channel1 transfer error flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_GL2: DMA2 Channel2 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC2: DMA2 Channel2 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT2: DMA2 Channel2 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE2: DMA2 Channel2 transfer error flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_GL3: DMA2 Channel3 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC3: DMA2 Channel3 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT3: DMA2 Channel3 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE3: DMA2 Channel3 transfer error flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_GL4: DMA2 Channel4 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC4: DMA2 Channel4 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT4: DMA2 Channel4 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE4: DMA2 Channel4 transfer error flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_GL5: DMA2 Channel5 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC5: DMA2 Channel5 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT5: DMA2 Channel5 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE5: DMA2 Channel5 transfer error flag, applicable only for STM32FO91 devices.  
  * @note   The Global flag (DMAy_FLAG_GLx) is set whenever any of the other flags 
  *         relative to the same channel is set (Transfer Complete, Half-transfer 
  *         Complete or Transfer Error flags: DMAy_FLAG_TCx, DMAy_FLAG_HTx or 
  *         DMAy_FLAG_TEx). 
  *      
  * @retval The new state of DMA_FLAG (SET or RESET).
  */
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_DMA_GET_FLAG(DMAy_FLAG));

  /* Calculate the used DMAy */
  if ((DMAy_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Get DMA2 ISR register value */
    tmpreg = DMA2->ISR ;
  }
  else
  {
    /* Get DMA1 ISR register value */
    tmpreg = DMA1->ISR ;
  }

  /* Check the status of the specified DMAy flag */
  if ((tmpreg & DMAy_FLAG) != (uint32_t)RESET)
  {
    /* DMAy_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* DMAy_FLAG is reset */
    bitstatus = RESET;
  }
  
  /* Return the DMAy_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the DMAy Channelx's pending flags.
  * @param  DMA_FLAG: specifies the flag to clear.
  *          This parameter can be any combination (for the same DMA) of the following values:
  *            @arg DMA1_FLAG_GL1: DMA1 Channel1 global flag.
  *            @arg DMA1_FLAG_TC1: DMA1 Channel1 transfer complete flag.
  *            @arg DMA1_FLAG_HT1: DMA1 Channel1 half transfer flag.
  *            @arg DMA1_FLAG_TE1: DMA1 Channel1 transfer error flag.
  *            @arg DMA1_FLAG_GL2: DMA1 Channel2 global flag.
  *            @arg DMA1_FLAG_TC2: DMA1 Channel2 transfer complete flag.
  *            @arg DMA1_FLAG_HT2: DMA1 Channel2 half transfer flag.
  *            @arg DMA1_FLAG_TE2: DMA1 Channel2 transfer error flag.
  *            @arg DMA1_FLAG_GL3: DMA1 Channel3 global flag.
  *            @arg DMA1_FLAG_TC3: DMA1 Channel3 transfer complete flag.
  *            @arg DMA1_FLAG_HT3: DMA1 Channel3 half transfer flag.
  *            @arg DMA1_FLAG_TE3: DMA1 Channel3 transfer error flag.
  *            @arg DMA1_FLAG_GL4: DMA1 Channel4 global flag.
  *            @arg DMA1_FLAG_TC4: DMA1 Channel4 transfer complete flag.
  *            @arg DMA1_FLAG_HT4: DMA1 Channel4 half transfer flag.
  *            @arg DMA1_FLAG_TE4: DMA1 Channel4 transfer error flag.
  *            @arg DMA1_FLAG_GL5: DMA1 Channel5 global flag.
  *            @arg DMA1_FLAG_TC5: DMA1 Channel5 transfer complete flag.
  *            @arg DMA1_FLAG_HT5: DMA1 Channel5 half transfer flag.
  *            @arg DMA1_FLAG_TE5: DMA1 Channel5 transfer error flag.
  *            @arg DMA1_FLAG_GL6: DMA1 Channel6 global flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_TC6: DMA1 Channel6 transfer complete flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_HT6: DMA1 Channel6 half transfer flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_TE6: DMA1 Channel6 transfer error flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_GL7: DMA1 Channel7 global flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_TC7: DMA1 Channel7 transfer complete flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_HT7: DMA1 Channel7 half transfer flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_FLAG_TE7: DMA1 Channel7 transfer error flag, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA2_FLAG_GL1: DMA2 Channel1 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC1: DMA2 Channel1 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT1: DMA2 Channel1 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE1: DMA2 Channel1 transfer error flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_GL2: DMA2 Channel2 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC2: DMA2 Channel2 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT2: DMA2 Channel2 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE2: DMA2 Channel2 transfer error flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_GL3: DMA2 Channel3 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC3: DMA2 Channel3 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT3: DMA2 Channel3 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE3: DMA2 Channel3 transfer error flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_GL4: DMA2 Channel4 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC4: DMA2 Channel4 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT4: DMA2 Channel4 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE4: DMA2 Channel4 transfer error flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_GL5: DMA2 Channel5 global flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TC5: DMA2 Channel5 transfer complete flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_HT5: DMA2 Channel5 half transfer flag, applicable only for STM32FO91 devices.
  *            @arg DMA2_FLAG_TE5: DMA2 Channel5 transfer error flag, applicable only for STM32FO91 devices. 
  *              
  * @note   Clearing the Global flag (DMAy_FLAG_GLx) results in clearing all other flags
  *         relative to the same channel (Transfer Complete, Half-transfer Complete and
  *         Transfer Error flags: DMAy_FLAG_TCx, DMAy_FLAG_HTx and DMAy_FLAG_TEx).
  *
  * @retval None
  */
void DMA_ClearFlag(uint32_t DMAy_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_FLAG(DMAy_FLAG));

/* Calculate the used DMAy */
  if ((DMAy_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Clear the selected DMAy flags */
    DMA2->IFCR = DMAy_FLAG;
  }
  else
  {
    /* Clear the selected DMAy flags */
    DMA1->IFCR = DMAy_FLAG;
  }
}

/**
  * @brief  Checks whether the specified DMAy Channelx interrupt has occurred or not.
  * @param  DMA_IT: specifies the DMA interrupt source to check. 
  *          This parameter can be one of the following values:
  *            @arg DMA1_IT_GL1: DMA1 Channel1 global interrupt.
  *            @arg DMA1_IT_TC1: DMA1 Channel1 transfer complete interrupt.
  *            @arg DMA1_IT_HT1: DMA1 Channel1 half transfer interrupt.
  *            @arg DMA1_IT_TE1: DMA1 Channel1 transfer error interrupt.
  *            @arg DMA1_IT_GL2: DMA1 Channel2 global interrupt.
  *            @arg DMA1_IT_TC2: DMA1 Channel2 transfer complete interrupt.
  *            @arg DMA1_IT_HT2: DMA1 Channel2 half transfer interrupt.
  *            @arg DMA1_IT_TE2: DMA1 Channel2 transfer error interrupt.
  *            @arg DMA1_IT_GL3: DMA1 Channel3 global interrupt.
  *            @arg DMA1_IT_TC3: DMA1 Channel3 transfer complete interrupt.
  *            @arg DMA1_IT_HT3: DMA1 Channel3 half transfer interrupt.
  *            @arg DMA1_IT_TE3: DMA1 Channel3 transfer error interrupt.
  *            @arg DMA1_IT_GL4: DMA1 Channel4 global interrupt.
  *            @arg DMA1_IT_TC4: DMA1 Channel4 transfer complete interrupt.
  *            @arg DMA1_IT_HT4: DMA1 Channel4 half transfer interrupt.
  *            @arg DMA1_IT_TE4: DMA1 Channel4 transfer error interrupt.
  *            @arg DMA1_IT_GL5: DMA1 Channel5 global interrupt.
  *            @arg DMA1_IT_TC5: DMA1 Channel5 transfer complete interrupt.
  *            @arg DMA1_IT_HT5: DMA1 Channel5 half transfer interrupt.
  *            @arg DMA1_IT_TE5: DMA1 Channel5 transfer error interrupt.
  *            @arg DMA1_IT_GL6: DMA1 Channel6 global interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_TC6: DMA1 Channel6 transfer complete interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_HT6: DMA1 Channel6 half transfer interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_TE6: DMA1 Channel6 transfer error interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_GL7: DMA1 Channel7 global interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_TC7: DMA1 Channel7 transfer complete interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_HT7: DMA1 Channel7 half transfer interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_TE7: DMA1 Channel7 transfer error interrupt, applicable only for STM32F072 and STM32FO91 devices.  
  *            @arg DMA2_IT_GL1: DMA2 Channel1 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC1: DMA2 Channel1 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT1: DMA2 Channel1 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE1: DMA2 Channel1 transfer error interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_GL2: DMA2 Channel2 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC2: DMA2 Channel2 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT2: DMA2 Channel2 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE2: DMA2 Channel2 transfer error interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_GL3: DMA2 Channel3 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC3: DMA2 Channel3 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT3: DMA2 Channel3 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE3: DMA2 Channel3 transfer error interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_GL4: DMA2 Channel4 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC4: DMA2 Channel4 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT4: DMA2 Channel4 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE4: DMA2 Channel4 transfer error interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_GL5: DMA2 Channel5 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC5: DMA2 Channel5 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT5: DMA2 Channel5 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE5: DMA2 Channel5 transfer error interrupt, applicable only for STM32FO91 devices.   
  * @note   The Global interrupt (DMAy_FLAG_GLx) is set whenever any of the other 
  *         interrupts relative to the same channel is set (Transfer Complete, 
  *         Half-transfer Complete or Transfer Error interrupts: DMAy_IT_TCx, 
  *         DMAy_IT_HTx or DMAy_IT_TEx). 
  *      
  * @retval The new state of DMA_IT (SET or RESET).
  */
ITStatus DMA_GetITStatus(uint32_t DMAy_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_GET_IT(DMAy_IT));

  /* Calculate the used DMA */
  if ((DMAy_IT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Get DMA2 ISR register value */
    tmpreg = DMA2->ISR;
  }
  else
  {
    /* Get DMA1 ISR register value */
    tmpreg = DMA1->ISR;
  }

  /* Check the status of the specified DMAy interrupt */
  if ((tmpreg & DMAy_IT) != (uint32_t)RESET)
  {
    /* DMAy_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* DMAy_IT is reset */
    bitstatus = RESET;
  }
  /* Return the DMAy_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the DMAy Channelx's interrupt pending bits.
  * @param  DMA_IT: specifies the DMA interrupt pending bit to clear.
  *          This parameter can be any combination (for the same DMA) of the following values:
  *            @arg DMA1_IT_GL1: DMA1 Channel1 global interrupt.
  *            @arg DMA1_IT_TC1: DMA1 Channel1 transfer complete interrupt.
  *            @arg DMA1_IT_HT1: DMA1 Channel1 half transfer interrupt.
  *            @arg DMA1_IT_TE1: DMA1 Channel1 transfer error interrupt.
  *            @arg DMA1_IT_GL2: DMA1 Channel2 global interrupt.
  *            @arg DMA1_IT_TC2: DMA1 Channel2 transfer complete interrupt.
  *            @arg DMA1_IT_HT2: DMA1 Channel2 half transfer interrupt.
  *            @arg DMA1_IT_TE2: DMA1 Channel2 transfer error interrupt.
  *            @arg DMA1_IT_GL3: DMA1 Channel3 global interrupt.
  *            @arg DMA1_IT_TC3: DMA1 Channel3 transfer complete interrupt.
  *            @arg DMA1_IT_HT3: DMA1 Channel3 half transfer interrupt.
  *            @arg DMA1_IT_TE3: DMA1 Channel3 transfer error interrupt.
  *            @arg DMA1_IT_GL4: DMA1 Channel4 global interrupt.
  *            @arg DMA1_IT_TC4: DMA1 Channel4 transfer complete interrupt.
  *            @arg DMA1_IT_HT4: DMA1 Channel4 half transfer interrupt.
  *            @arg DMA1_IT_TE4: DMA1 Channel4 transfer error interrupt.
  *            @arg DMA1_IT_GL5: DMA1 Channel5 global interrupt.
  *            @arg DMA1_IT_TC5: DMA1 Channel5 transfer complete interrupt.
  *            @arg DMA1_IT_HT5: DMA1 Channel5 half transfer interrupt.
  *            @arg DMA1_IT_TE5: DMA1 Channel5 transfer error interrupt.
  *            @arg DMA1_IT_GL6: DMA1 Channel6 global interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_TC6: DMA1 Channel6 transfer complete interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_HT6: DMA1 Channel6 half transfer interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_TE6: DMA1 Channel6 transfer error interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_GL7: DMA1 Channel7 global interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_TC7: DMA1 Channel7 transfer complete interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_HT7: DMA1 Channel7 half transfer interrupt, applicable only for STM32F072 and STM32FO91 devices.
  *            @arg DMA1_IT_TE7: DMA1 Channel7 transfer error interrupt, applicable only for STM32F072 and STM32FO91 devices.  
  *            @arg DMA2_IT_GL1: DMA2 Channel1 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC1: DMA2 Channel1 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT1: DMA2 Channel1 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE1: DMA2 Channel1 transfer error interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_GL2: DMA2 Channel2 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC2: DMA2 Channel2 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT2: DMA2 Channel2 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE2: DMA2 Channel2 transfer error interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_GL3: DMA2 Channel3 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC3: DMA2 Channel3 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT3: DMA2 Channel3 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE3: DMA2 Channel3 transfer error interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_GL4: DMA2 Channel4 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC4: DMA2 Channel4 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT4: DMA2 Channel4 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE4: DMA2 Channel4 transfer error interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_GL5: DMA2 Channel5 global interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TC5: DMA2 Channel5 transfer complete interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_HT5: DMA2 Channel5 half transfer interrupt, applicable only for STM32FO91 devices.
  *            @arg DMA2_IT_TE5: DMA2 Channel5 transfer error interrupt, applicable only for STM32FO91 devices.  
  *     
  * @note   Clearing the Global interrupt (DMAy_IT_GLx) results in clearing all other 
  *         interrupts relative to the same channel (Transfer Complete, Half-transfer 
  *         Complete and Transfer Error interrupts: DMAy_IT_TCx, DMAy_IT_HTx and 
  *         DMAy_IT_TEx).  
  *        
  * @retval None
  */
void DMA_ClearITPendingBit(uint32_t DMAy_IT)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_IT(DMAy_IT));
  
  /* Calculate the used DMAy */
  if ((DMAy_IT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Clear the selected DMAy interrupt pending bits */
    DMA2->IFCR = DMAy_IT;
  }
  else
  {
    /* Clear the selected DMAy interrupt pending bits */
    DMA1->IFCR = DMAy_IT;
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_exti.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the EXTI peripheral:
  *           + Initialization and Configuration
  *           + Interrupts and flags management
  *
  *  @verbatim
  ==============================================================================
                            ##### EXTI features ##### 
  ==============================================================================
    [..] External interrupt/event lines are mapped as following:
         (#) All available GPIO pins are connected to the 16 external 
             interrupt/event lines from EXTI0 to EXTI15.
         (#) EXTI line 16 is connected to the PVD output, not applicable for STM32F030 devices.
         (#) EXTI line 17 is connected to the RTC Alarm event.
         (#) EXTI line 18 is connected to the RTC Alarm event, applicable only for STM32F072 devices.
         (#) EXTI line 19 is connected to the RTC Tamper and TimeStamp events.
         (#) EXTI line 20 is connected to the RTC wakeup event, applicable only for STM32F072 devices.
         (#) EXTI line 21 is connected to the Comparator 1 wakeup event, applicable only for STM32F051 and STM32F072 devices. 
         (#) EXTI line 22 is connected to the Comparator 2 wakeup event, applicable only for STM32F051 and STM32F072 devices.
         (#) EXTI line 23 is connected to the I2C1 wakeup event, not applicable for STM32F030 devices.
         (#) EXTI line 25 is connected to the USART1 wakeup event, not applicable for STM32F030 devices.
         (#) EXTI line 26 is connected to the USART2 wakeup event, applicable only for STM32F072 devices.
         (#) EXTI line 27 is connected to the CEC wakeup event, applicable only for STM32F051 and STM32F072 devices.
         (#) EXTI line 31 is connected to the VDD USB monitor event, applicable only for STM32F072 devices.

                       ##### How to use this driver ##### 
  ==============================================================================
    [..] In order to use an I/O pin as an external interrupt source, follow
         steps below:
    (#) Configure the I/O in input mode using GPIO_Init()
    (#) Select the input source pin for the EXTI line using 
        SYSCFG_EXTILineConfig().
    (#) Select the mode(interrupt, event) and configure the trigger selection 
       (Rising, falling or both) using EXTI_Init(). For the internal interrupt,
       the trigger selection is not needed( the active edge is always the rising one).
    (#) Configure NVIC IRQ channel mapped to the EXTI line using NVIC_Init().
    (#) Optionally, you can generate a software interrupt using the function EXTI_GenerateSWInterrupt().
    [..]
    (@) SYSCFG APB clock must be enabled to get write access to SYSCFG_EXTICRx
      registers using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    @endverbatim
  *
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI 
  * @brief EXTI driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EXTI_LINENONE     ((uint32_t)0x00000)        /* No interrupt selected */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup EXTI_Private_Functions
  * @{
  */

/** @defgroup EXTI_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
  ==============================================================================
            ##### Initialization and Configuration functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset 
  *         values.
  * @param  None
  * @retval None
  */
void EXTI_DeInit(void)
{
  EXTI->IMR = 0x0F940000;
  EXTI->EMR = 0x00000000;
  EXTI->RTSR = 0x00000000;
  EXTI->FTSR = 0x00000000;
  EXTI->PR = 0x006BFFFF;
}

/**
  * @brief  Initializes the EXTI peripheral according to the specified
  *         parameters in the EXTI_InitStruct.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure that 
  *         contains the configuration information for the EXTI peripheral.
  * @retval None
  */
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

  tmp = (uint32_t)EXTI_BASE;

  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* Clear EXTI line configuration */
    EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;

    tmp += EXTI_InitStruct->EXTI_Mode;

    *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;

    /* Clear Rising Falling edge configuration */
    EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;

    /* Select the trigger for the selected interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
      EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;

      *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;

    /* Disable the selected external lines */
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}

/**
  * @brief  Fills each EXTI_InitStruct member with its reset value.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @param  EXTI_Line: specifies the EXTI line on which the software interrupt
  *         will be generated.
  *          This parameter can be any combination of EXTI_Linex where x can be (0..27).
  * @retval None
  */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->SWIER |= EXTI_Line;
}

/**
  * @}
  */

/** @defgroup EXTI_Group2 Interrupts and flags management functions
 *  @brief    Interrupts and flags management functions 
 *
@verbatim   
  ==============================================================================
             ##### Interrupts and flags management functions #####
  ==============================================================================
  
@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  EXTI_Line: specifies the EXTI line flag to check.
  *          This parameter can be EXTI_Linex where x can be (0..27).
  * @retval The new state of EXTI_Line (SET or RESET).
  */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
   FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));

  if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the EXTI's line pending flags.
  * @param  EXTI_Line: specifies the EXTI lines flags to clear.
  *          This parameter can be any combination of EXTI_Linex where x can be (0..27).
  * @retval None
  */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->PR = EXTI_Line;
}

/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  EXTI_Line: specifies the EXTI line to check.
  *          This parameter can be EXTI_Linex where x can be (0..27).
  * @retval The new state of EXTI_Line (SET or RESET).
  */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));

  if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the EXTI's line pending bits.
  * @param  EXTI_Line: specifies the EXTI lines to clear.
  *          This parameter can be any combination of EXTI_Linex where x can be (0..27).
  * @retval None
  */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->PR = EXTI_Line;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_flash.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the FLASH peripheral:
  *            - FLASH Interface configuration
  *            - FLASH Memory Programming
  *            - Option Bytes Programming
  *            - Interrupts and flags management
  *
  *  @verbatim
 ===============================================================================
                    ##### How to use this driver #####
 ===============================================================================
    [..] This driver provides functions to configure and program the Flash 
         memory of all STM32F0xx devices. These functions are split in 4 groups
         (#) FLASH Interface configuration functions: this group includes the 
             management of following features:
             (++) Set the latency
             (++) Enable/Disable the prefetch buffer

         (#) FLASH Memory Programming functions: this group includes all needed 
             functions to erase and program the main memory:
             (++) Lock and Unlock the Flash interface.
             (++) Erase function: Erase Page, erase all pages.
             (++) Program functions: Half Word and Word write.

         (#) FLASH Option Bytes Programming functions: this group includes all 
             needed functions to:
             (++) Lock and Unlock the Flash Option bytes.
             (++) Launch the Option Bytes loader
             (++) Erase the Option Bytes
             (++)Set/Reset the write protection
             (++) Set the Read protection Level
             (++) Program the user option Bytes
             (++) Set/Reset the BOOT1 bit
             (++) Enable/Disable the VDDA Analog Monitoring
             (++) Get the user option bytes
             (++) Get the Write protection
             (++) Get the read protection status

         (#) FLASH Interrupts and flag management functions: this group includes 
             all needed functions to:
             (++) Enable/Disable the flash interrupt sources
             (++) Get flags status
             (++) Clear flags
             (++) Get Flash operation status
             (++) Wait for last flash operation

 @endverbatim
  
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH 
  * @brief FLASH driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
 
/** @defgroup FLASH_Private_Functions
  * @{
  */ 

/** @defgroup FLASH_Group1 FLASH Interface configuration functions
  *  @brief   FLASH Interface configuration functions 
 *
@verbatim   
 ===============================================================================
               ##### FLASH Interface configuration functions #####
 ===============================================================================

    [..] FLASH_Interface configuration_Functions, includes the following functions:
       (+) void FLASH_SetLatency(uint32_t FLASH_Latency):
    [..] To correctly read data from Flash memory, the number of wait states (LATENCY) 
     must be correctly programmed according to the frequency of the CPU clock (HCLK) 
    [..]
        +--------------------------------------------- +
        |  Wait states  |   HCLK clock frequency (MHz) |
        |---------------|------------------------------|
        |0WS(1CPU cycle)|       0 < HCLK <= 24         |
        |---------------|------------------------------|
        |1WS(2CPU cycle)|       24 < HCLK <= 48        |
        +----------------------------------------------+
    [..]
       (+) void FLASH_PrefetchBufferCmd(FunctionalState NewState);
    [..]
     All these functions don't need the unlock sequence.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the code latency value.
  * @param  FLASH_Latency: specifies the FLASH Latency value.
  *          This parameter can be one of the following values:
  *             @arg FLASH_Latency_0: FLASH Zero Latency cycle
  *             @arg FLASH_Latency_1: FLASH One Latency cycle
  * @retval None
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
   uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_LATENCY(FLASH_Latency));

  /* Read the ACR register */
  tmpreg = FLASH->ACR;  

  /* Sets the Latency value */
  tmpreg &= (uint32_t) (~((uint32_t)FLASH_ACR_LATENCY));
  tmpreg |= FLASH_Latency;

  /* Write the ACR register */
  FLASH->ACR = tmpreg;
}

/**
  * @brief  Enables or disables the Prefetch Buffer.
  * @param  NewState: new state of the FLASH prefetch buffer.
  *          This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void FLASH_PrefetchBufferCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if(NewState != DISABLE)
  {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  else
  {
    FLASH->ACR &= (uint32_t)(~((uint32_t)FLASH_ACR_PRFTBE));
  }
}

/**
  * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
  * @param  None
  * @retval FLASH Prefetch Buffer Status (SET or RESET).
  */
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((FLASH->ACR & FLASH_ACR_PRFTBS) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
  return bitstatus; 
}

/**
  * @}
  */

/** @defgroup FLASH_Group2 FLASH Memory Programming functions
 *  @brief   FLASH Memory Programming functions
 *
@verbatim   
 ===============================================================================
                ##### FLASH Memory Programming functions #####
 ===============================================================================

    [..] The FLASH Memory Programming functions, includes the following functions:
       (+) void FLASH_Unlock(void);
       (+) void FLASH_Lock(void);
       (+) FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
       (+) FLASH_Status FLASH_EraseAllPages(void);
       (+) FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
       (+) FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

    [..] Any operation of erase or program should follow these steps:
       
       (#) Call the FLASH_Unlock() function to enable the flash control register and 
           program memory access
       (#) Call the desired function to erase page or program data
       (#) Call the FLASH_Lock() to disable the flash program memory access 
      (recommended to protect the FLASH memory against possible unwanted operation)

@endverbatim
  * @{
  */

/**
  * @brief  Unlocks the FLASH control register and program memory access.
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
  if((FLASH->CR & FLASH_CR_LOCK) != RESET)
  {
    /* Unlocking the program memory access */
    FLASH->KEYR = FLASH_FKEY1;
    FLASH->KEYR = FLASH_FKEY2;
  }
}

/**
  * @brief  Locks the Program memory access.
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
  /* Set the LOCK Bit to lock the FLASH control register and program memory access */
  FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * @brief  Erases a specified page in program memory.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Page_Address: The page address in program memory to be erased.
  * @note   A Page is erased in the Program memory only if the address to load 
  *         is the start address of a page (multiple of 1024 bytes).
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Page_Address));
 
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  { 
    /* If the previous operation is completed, proceed to erase the page */
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR  = Page_Address;
    FLASH->CR |= FLASH_CR_STRT;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    /* Disable the PER Bit */
    FLASH->CR &= ~FLASH_CR_PER;
  }
    
  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Erases all FLASH pages.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
     FLASH->CR |= FLASH_CR_MER;
     FLASH->CR |= FLASH_CR_STRT;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    /* Disable the MER Bit */
    FLASH->CR &= ~FLASH_CR_MER;
  }

  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Programs a word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new first 
    half word */
    FLASH->CR |= FLASH_CR_PG;
  
    *(__IO uint16_t*)Address = (uint16_t)Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
 
    if(status == FLASH_COMPLETE)
    {
      /* If the previous operation is completed, proceed to program the new second 
      half word */
      tmp = Address + 2;

      *(__IO uint16_t*) tmp = Data >> 16;
    
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        
      /* Disable the PG Bit */
      FLASH->CR &= ~FLASH_CR_PG;
    }
    else
    {
      /* Disable the PG Bit */
      FLASH->CR &= ~FLASH_CR_PG;
    }
  }
   
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a half word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new data */
    FLASH->CR |= FLASH_CR_PG;
  
    *(__IO uint16_t*)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    /* Disable the PG Bit */
    FLASH->CR &= ~FLASH_CR_PG;
  } 
  
  /* Return the Program Status */
  return status;
}

/**
  * @}
  */
  
/** @defgroup FLASH_Group3 Option Bytes Programming functions
 *  @brief   Option Bytes Programming functions 
 *
@verbatim   
 ===============================================================================
                ##### Option Bytes Programming functions #####
 ===============================================================================

    [..] The FLASH_Option Bytes Programming_functions, includes the following functions:
       (+) void FLASH_OB_Unlock(void);
       (+) void FLASH_OB_Lock(void);
       (+) void FLASH_OB_Launch(void);
       (+) FLASH_Status FLASH_OB_Erase(void);
       (+) FLASH_Status FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState);
       (+) FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP);
       (+) FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
       (+) FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1);
       (+) FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG);
       (+) FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER);
       (+) FLASH_OB_ProgramData(uint32_t Address, uint8_t Data);
       (+) uint8_t FLASH_OB_GetUser(void);
       (+) uint32_t FLASH_OB_GetWRP(void);
       (+) FlagStatus FLASH_OB_GetRDP(void);

    [..] Any operation of erase or program should follow these steps:

   (#) Call the FLASH_OB_Unlock() function to enable the Option Bytes registers access

   (#) Call one or several functions to program the desired option bytes 
      (++) FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP) => to set the desired read Protection Level
      (++) FLASH_Status FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState) 
           => to Enable/Disable the desired sector write protection
      (++) FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY) 
           => to configure the user option Bytes: IWDG, STOP and the Standby.
      (++) FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1)
           => to set or reset BOOT1 
      (++) FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG) 
           => to enable or disable the VDDA Analog Monitoring 			 
      (++) You can write all User Options bytes at once using a single function
           by calling FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER)
      (++) FLASH_OB_ProgramData(uint32_t Address, uint8_t Data) to program the 
           two half word in the option bytes

   (#) Once all needed option bytes to be programmed are correctly written, call the
      FLASH_OB_Launch(void) function to launch the Option Bytes programming process.

   (#) Call the FLASH_OB_Lock() to disable the Option Bytes registers access (recommended
      to protect the option Bytes against possible unwanted operations)

@endverbatim
  * @{
  */

/**
  * @brief  Unlocks the option bytes block access.
  * @param  None
  * @retval None
  */
void FLASH_OB_Unlock(void)
{
  if((FLASH->CR & FLASH_CR_OPTWRE) == RESET)
  { 
    /* Unlocking the option bytes block access */
    FLASH->OPTKEYR = FLASH_OPTKEY1;
    FLASH->OPTKEYR = FLASH_OPTKEY2;
  }
}

/**
  * @brief  Locks the option bytes block access.
  * @param  None
  * @retval None
  */
void FLASH_OB_Lock(void)
{
  /* Set the OPTWREN Bit to lock the option bytes block access */
  FLASH->CR &= ~FLASH_CR_OPTWRE;
}

/**
  * @brief  Launch the option byte loading.
  * @param  None
  * @retval None
  */
void FLASH_OB_Launch(void)
{
  /* Set the OBL_Launch bit to launch the option byte loading */
  FLASH->CR |= FLASH_CR_OBL_LAUNCH;
}

/**
  * @brief  Erases the FLASH option bytes.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @note   This functions erases all option bytes except the Read protection (RDP).
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_Erase(void)
{
  uint16_t rdptmp = OB_RDP_Level_0;

  FLASH_Status status = FLASH_COMPLETE;

  /* Get the actual read protection Option Byte value */ 
  if(FLASH_OB_GetRDP() != RESET)
  {
    rdptmp = 0x00;  
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {   
    /* If the previous operation is completed, proceed to erase the option bytes */
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
       
      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;

      /* Restore the last read protection Option Byte value */
      OB->RDP = (uint16_t)rdptmp; 

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
 
      if(status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }  
  }
  /* Return the erase status */
  return status;
}

/**
  * @brief  Write protects the desired pages
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_WRP: specifies the address of the pages to be write protected.
  *          This parameter can be:
  *             @arg OB_WRP_Pages0to3..OB_WRP_Pages60to63
  *             @arg OB_WRP_AllPages
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP)
{
 uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;

  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_WRP(OB_WRP));

  OB_WRP = (uint32_t)(~OB_WRP);
  WRP0_Data = (uint16_t)(OB_WRP & OB_WRP0_WRP0);
  WRP1_Data = (uint16_t)((OB_WRP >> 8) & OB_WRP0_WRP0);
  WRP2_Data = (uint16_t)((OB_WRP >> 16) & OB_WRP0_WRP0) ;
  WRP3_Data = (uint16_t)((OB_WRP >> 24) & OB_WRP0_WRP0) ;
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTPG;

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 = WRP2_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }    
    if((status == FLASH_COMPLETE) && (WRP3_Data != 0xFF))
    {
      OB->WRP3 = WRP3_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }  
    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  } 
  /* Return the write protection operation Status */
  return status;
}

/**
  * @brief  Enables or disables the read out protection.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  FLASH_ReadProtection_Level: specifies the read protection level. 
  *          This parameter can be:
  *             @arg OB_RDP_Level_0: No protection
  *             @arg OB_RDP_Level_1: Read protection of the memory
  *             @arg OB_RDP_Level_2: Chip protection
  * @note   When enabling OB_RDP level 2 it's no more possible to go back to level 1 or 0
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP)
{
  FLASH_Status status = FLASH_COMPLETE;
  
  /* Check the parameters */
  assert_param(IS_OB_RDP(OB_RDP));
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
      
      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;
       
      OB->RDP = OB_RDP;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT); 
    
      if(status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else 
    {
      if(status != FLASH_TIMEOUT)
      {
        /* Disable the OPTER Bit */
        FLASH->CR &= ~FLASH_CR_OPTER;
      }
    }
  }
  /* Return the protection operation Status */
  return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_IWDG: Selects the WDG mode
  *          This parameter can be one of the following values:
  *             @arg OB_IWDG_SW: Software WDG selected
  *             @arg OB_IWDG_HW: Hardware WDG selected
  * @param  OB_STOP: Reset event when entering STOP mode.
  *          This parameter can be one of the following values:
  *             @arg OB_STOP_NoRST: No reset generated when entering in STOP
  *             @arg OB_STOP_RST: Reset generated when entering in STOP
  * @param  OB_STDBY: Reset event when entering Standby mode.
  *          This parameter can be one of the following values:
  *             @arg OB_STDBY_NoRST: No reset generated when entering in STANDBY
  *             @arg OB_STDBY_RST: Reset generated when entering in STANDBY
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 

    OB->USER = (uint16_t)((uint16_t)(OB_IWDG | OB_STOP) | (uint16_t)(OB_STDBY | 0xF8));
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }    
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the BOOT1 option bit.
  * @param  OB_BOOT1: Set or Reset the BOOT1 option bit.
  *          This parameter can be one of the following values:
  *             @arg OB_BOOT1_RESET: BOOT1 option bit reset
  *             @arg OB_BOOT1_SET: BOOT1 option bit set
  * @retval None
  */
FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_BOOT1(OB_BOOT1));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG;

    OB->USER = OB_BOOT1 | 0xEF;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the BOOT0 option bit.
  * @note   This function is applicable only for the STM32F042 devices.
  * @param  OB_BOOT0: Set or Reset the BOOT0 option bit.
  *          This parameter can be one of the following values:
  *             @arg OB_BOOT0_RESET: BOOT0 option bit reset
  *             @arg OB_BOOT0_SET: BOOT0 option bit set
  * @retval None
  */
FLASH_Status FLASH_OB_BOOT0Config(uint8_t OB_BOOT0)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_BOOT0(OB_BOOT0));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG;

    OB->USER = OB_BOOT0 | 0xF7;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the BOOT0SW option bit.
  * @note   This function is applicable only for the STM32F042 devices.   
  * @param  OB_BOOT0SW: Set or Reset the BOOT0_SW option bit.
  *          This parameter can be one of the following values:
  *             @arg OB_BOOT0_SW: BOOT0_SW option bit reset
  *             @arg OB_BOOT0_HW: BOOT0_SW option bit set
  * @retval None
  */
FLASH_Status FLASH_OB_BOOT0SWConfig(uint8_t OB_BOOT0SW)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_BOOT0SW(OB_BOOT0SW));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG;

    OB->USER = OB_BOOT0SW | 0x7F;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the analogue monitoring on VDDA Power source.
  * @param  OB_VDDA_ANALOG: Selects the analog monitoring on VDDA Power source.
  *          This parameter can be one of the following values:
  *             @arg OB_VDDA_ANALOG_ON: Analog monitoring on VDDA Power source ON
  *             @arg OB_VDDA_ANALOG_OFF: Analog monitoring on VDDA Power source OFF
  * @retval None
  */
FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_VDDA_ANALOG(OB_VDDA_ANALOG));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 

    OB->USER = OB_VDDA_ANALOG | 0xDF;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the SRAM parity.
  * @param  OB_SRAM_Parity: Set or Reset the SRAM parity enable bit.
  *          This parameter can be one of the following values:
  *             @arg OB_SRAM_PARITY_SET: Set SRAM parity.
  *             @arg OB_SRAM_PARITY_RESET: Reset SRAM parity.
  * @retval None
  */
FLASH_Status FLASH_OB_SRAMParityConfig(uint8_t OB_SRAM_Parity)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_SRAM_PARITY(OB_SRAM_Parity));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 

    OB->USER = OB_SRAM_Parity | 0xBF;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW, RST_STOP, RST_STDBY,
  *         BOOT1 and VDDA ANALOG monitoring.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_USER: Selects all user option bytes
  *          This parameter is a combination of the following values:
  *             @arg OB_IWDG_SW / OB_IWDG_HW: Software / Hardware WDG selected
  *             @arg OB_STOP_NoRST / OB_STOP_RST: No reset / Reset generated when entering in STOP
  *             @arg OB_STDBY_NoRST / OB_STDBY_RST: No reset / Reset generated when entering in STANDBY
  *             @arg OB_BOOT1_RESET / OB_BOOT1_SET: BOOT1 Reset / Set
  *             @arg OB_VDDA_ANALOG_ON / OB_VDDA_ANALOG_OFF: Analog monitoring on VDDA Power source ON / OFF 
  *             @arg OB_SRAM_PARITY_SET / OB_SRAM_PARITY_RESET: SRAM Parity SET / RESET
  *             @arg OB_BOOT0_RESET / OB_BOOT0_SET: BOOT0 Reset / Set
  *             @arg OB_BOOT0_SW / OB_BOOT0_SW: BOOT0 pin disabled / BOOT0 pin bonded with GPIO      
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 

    OB->USER = OB_USER;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }    
  /* Return the Option Byte program Status */
  return status;

}

/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  *          This parameter can be 0x1FFFF804 or 0x1FFFF806. 
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_ProgramData(uint32_t Address, uint8_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  assert_param(IS_OB_DATA_ADDRESS(Address));
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    /* Enables the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 
    *(__IO uint16_t*)Address = Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte Data Program Status */
  return status;
}

/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @param  None
  * @retval The FLASH User Option Bytes .
  */
uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)(FLASH->OBR >> 8);
}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes value.
  * @param  None
  * @retval The FLASH Write Protection Option Bytes value
  */
uint32_t FLASH_OB_GetWRP(void)
{
  /* Return the FLASH write protection Register value */
  return (uint32_t)(FLASH->WRPR);
}

/**
  * @brief  Checks whether the FLASH Read out Protection Status is set or not.
  * @param  None
  * @retval FLASH ReadOut Protection Status(SET or RESET)
  */
FlagStatus FLASH_OB_GetRDP(void)
{
  FlagStatus readstatus = RESET;
  
  if ((uint8_t)(FLASH->OBR & (FLASH_OBR_RDPRT1 | FLASH_OBR_RDPRT2)) != RESET)
  {
    readstatus = SET;
  }
  else
  {
    readstatus = RESET;
  }
  return readstatus;
}

/**
  * @}
  */

/** @defgroup FLASH_Group4 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or 
  *         disabled.
  *          This parameter can be any combination of the following values:
  *             @arg FLASH_IT_EOP: FLASH end of programming Interrupt
  *             @arg FLASH_IT_ERR: FLASH Error Interrupt
  * @retval None 
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FLASH_IT(FLASH_IT)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if(NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->CR &= ~(uint32_t)FLASH_IT;
  }
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *          This parameter can be one of the following values:
  *             @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag 
  *             @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *             @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));

  if((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus; 
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *          This parameter can be any combination of the following values:
  *             @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *             @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));
  
  /* Clear the flags */
  FLASH->SR = FLASH_FLAG;
}

/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_BUSY, FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP or FLASH_COMPLETE.
  */
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status FLASHstatus = FLASH_COMPLETE;
  
  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
  {
    FLASHstatus = FLASH_BUSY;
  }
  else 
  {  
    if((FLASH->SR & (uint32_t)FLASH_FLAG_WRPERR)!= (uint32_t)0x00)
    { 
      FLASHstatus = FLASH_ERROR_WRP;
    }
    else 
    {
      if((FLASH->SR & (uint32_t)(FLASH_SR_PGERR)) != (uint32_t)0x00)
      {
        FLASHstatus = FLASH_ERROR_PROGRAM; 
      }
      else
      {
        FLASHstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the FLASH Status */
  return FLASHstatus;
}


/**
  * @brief  Waits for a FLASH operation to complete or a TIMEOUT to occur.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{ 
  FLASH_Status status = FLASH_COMPLETE;
   
  /* Check for the FLASH Status */
  status = FLASH_GetStatus();
  
  /* Wait for a FLASH operation to complete or a TIMEOUT to occur */
  while((status == FLASH_BUSY) && (Timeout != 0x00))
  {
    status = FLASH_GetStatus();
    Timeout--;
  }
  
  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
}

/**
  * @}
  */

/**
  * @}
  */
   
  /**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_gpio.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the GPIO peripheral:
  *           + Initialization and Configuration functions
  *           + GPIO Read and Write functions
  *           + GPIO Alternate functions configuration functions
  *
  *  @verbatim
  *
  *
    ===========================================================================
                         ##### How to use this driver #####
    ===========================================================================
      [..]
      (#) Enable the GPIO AHB clock using RCC_AHBPeriphClockCmd()
      (#) Configure the GPIO pin(s) using GPIO_Init()
          Four possible configuration are available for each pin:
         (++) Input: Floating, Pull-up, Pull-down.
         (++) Output: Push-Pull (Pull-up, Pull-down or no Pull)
                      Open Drain (Pull-up, Pull-down or no Pull).
              In output mode, the speed is configurable: Low, Medium, Fast or High.
         (++) Alternate Function: Push-Pull (Pull-up, Pull-down or no Pull)
                                  Open Drain (Pull-up, Pull-down or no Pull).
         (++) Analog: required mode when a pin is to be used as ADC channel,
              DAC output or comparator input.
      (#) Peripherals alternate function:
         (++) For ADC, DAC and comparators, configure the desired pin in analog 
              mode using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AN
         (++) For other peripherals (TIM, USART...):
              (+++) Connect the pin to the desired peripherals' Alternate 
                    Function (AF) using GPIO_PinAFConfig() function. For PortC, 
                    PortD and PortF, no configuration is needed.
              (+++) Configure the desired pin in alternate function mode using
                    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
              (+++) Select the type, pull-up/pull-down and output speed via 
                    GPIO_PuPd, GPIO_OType and GPIO_Speed members
              (+++) Call GPIO_Init() function
      (#) To get the level of a pin configured in input mode use GPIO_ReadInputDataBit()
      (#) To set/reset the level of a pin configured in output mode use
          GPIO_SetBits()/GPIO_ResetBits()
      (#) During and just after reset, the alternate functions are not active and 
          the GPIO pins are configured in input floating mode (except JTAG pins).
      (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as 
          general-purpose (PC14 and PC15, respectively) when the LSE oscillator 
          is off. The LSE has priority over the GPIO function.
      (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as general-purpose 
          PD0 and PD1, respectively, when the HSE oscillator is off. The HSE has 
          priority over the GPIO function.
    @endverbatim
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO 
  * @brief GPIO driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions 
  * @{
  */

/** @defgroup GPIO_Group1 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
@verbatim
 ===============================================================================
                    ##### Initialization and Configuration #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset 
  *         values.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.    
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if(GPIOx == GPIOA)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, DISABLE);
  }
  else if(GPIOx == GPIOB)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, DISABLE);
  }
  else if(GPIOx == GPIOC)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, DISABLE);
  }
  else if(GPIOx == GPIOD)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, DISABLE);
  }
  else if(GPIOx == GPIOE)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOE, DISABLE);
  }
  else
  {
    if(GPIOx == GPIOF)
    {
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, ENABLE);
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, DISABLE);
    }
  }
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified 
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.   
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /*-------------------------- Configure the port pins -----------------------*/
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;

    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration */
        GPIOx->OTYPER &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos));
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }

      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));

      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      /* Pull-up Pull down resistor configuration */
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Locks GPIO Pins configuration registers.
  * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  * @note   The configuration of the locked GPIO pins can no longer be modified
  *         until the next device reset.
  * @param  GPIOx: where x can be (A or B) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  __IO uint32_t tmp = 0x00010000;

  /* Check the parameters */
  assert_param(IS_GPIO_LIST_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  tmp |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Reset LCKK bit */
  GPIOx->LCKR =  GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit */
  tmp = GPIOx->LCKR;
  /* Read LCKK bit */
  tmp = GPIOx->LCKR;
}

/**
  * @}
  */

/** @defgroup GPIO_Group2 GPIO Read and Write
 *  @brief   GPIO Read and Write
 *
@verbatim   
 ===============================================================================
                      ##### GPIO Read and Write #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.   
  * @param  GPIO_Pin: specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For STM32F051 and STM32F030: (0..15) for GPIOA, GPIOB, GPIOC, (2) for GPIOD and (0..1, 4..7) for GIIOF.
  *         For STM32F072: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
  *         For STM32F031: (0..15) for GPIOA, GPIOB, (13..15) for GPIOC and (0..1, 6..7) for GPIOF.  
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.   
  * @retval The input port pin value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->IDR);
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.   
  * @param  GPIO_Pin: Specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For STM32F051 and STM32F030: (0..15) for GPIOA, GPIOB, GPIOC, (2) for GPIOD and (0..1, 4..7) for GIIOF.
  *         For STM32F072: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
  *         For STM32F031: (0..15) for GPIOA, GPIOB, (13..15) for GPIOC and (0..1, 6..7) for GPIOF. 
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.    
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->ODR);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.    
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For STM32F051 and STM32F030: (0..15) for GPIOA, GPIOB, GPIOC, (2) for GPIOD and (0..1, 4..7) for GIIOF.
  *         For STM32F072: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
  *         For STM32F031: (0..15) for GPIOA, GPIOB, (13..15) for GPIOC and (0..1, 6..7) for GPIOF. 
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->BSRR = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For STM32F051 and STM32F030: (0..15) for GPIOA, GPIOB, GPIOC, (2) for GPIOD and (0..1, 4..7) for GIIOF.
  *         For STM32F072: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
  *         For STM32F031: (0..15) for GPIOA, GPIOB, (13..15) for GPIOC and (0..1, 6..7) for GPIOF. 
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->BRR = GPIO_Pin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.  
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @param  BitVal: specifies the value to be written to the selected bit.
  *          This parameter can be one of the BitAction enumeration values:
  *            @arg Bit_RESET: to clear the port pin
  *            @arg Bit_SET: to set the port pin
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For STM32F051 and STM32F030: (0..15) for GPIOA, GPIOB, GPIOC, (2) for GPIOD and (0..1, 4..7) for GIIOF.
  *         For STM32F072: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
  *         For STM32F031: (0..15) for GPIOA, GPIOB, (13..15) for GPIOC and (0..1, 6..7) for GPIOF.
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BRR = GPIO_Pin ;
  }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.  
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR = PortVal;
}

/**
  * @}
  */

/** @defgroup GPIO_Group3 GPIO Alternate functions configuration functions
 *  @brief   GPIO Alternate functions configuration functions
 *
@verbatim   
 ===============================================================================
          ##### GPIO Alternate functions configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @note   GPIOC, GPIOD, GPIOE and GPIOF  are available only for STM32F072 and STM32F091. 
  * @param  GPIO_PinSource: specifies the pin for the Alternate function.
  *          This parameter can be GPIO_PinSourcex where x can be (0..15) for GPIOA, GPIOB, GPIOD, GPIOE
  *          and (0..12) for GPIOC and (0, 2..5, 9..10) for GPIOF.    
  * @param  GPIO_AF: selects the pin to used as Alternate function.
  *          This parameter can be one of the following value:
  *            @arg GPIO_AF_0:  WKUP, EVENTOUT, TIM15, SPI1, TIM17, MCO, SWDAT, SWCLK,
  *                             TIM14, BOOT, USART1, CEC, IR_OUT, SPI2, TIM3, USART4,
  *                             CAN, USART2, CRS, TIM16, TIM1, TS, USART8 
  *            @arg GPIO_AF_1: USART2, CEC, TIM3, USART1, USART2, EVENTOUT, I2C1,
  *                            I2C2, TIM15, SPI2, USART3, TS, SPI1, USART7, USART8
  *                            USART5, USART4, USART6, I2C1   
  *            @arg GPIO_AF_2: TIM2, TIM1, EVENTOUT, TIM16, TIM17, USB, USART6, USART5,
  *                            USART8, USART7, USART6  
  *            @arg GPIO_AF_3: TS, I2C1, TIM15, EVENTOUT 
  *            @arg GPIO_AF_4: TIM14, USART4, USART3, CRS, CAN, I2C1, USART5
  *            @arg GPIO_AF_5: TIM16, TIM17, TIM15, SPI2, I2C2, USART6, MCO
  *            @arg GPIO_AF_6: EVENTOUT
  *            @arg GPIO_AF_7: COMP1 OUT, COMP2 OUT 
  * @note   The pin should already been configured in Alternate Function mode(AF)
  *         using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
  * @note   Refer to the Alternate function mapping table in the device datasheet 
  *         for the detailed mapping of the system and peripherals'alternate 
  *         function I/O pins.
  * @retval None
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t temp = 0x00;
  uint32_t temp_2 = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_param(IS_GPIO_AF(GPIO_AF));

  temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
  GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
  temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
  GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_i2c.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Inter-Integrated circuit (I2C):
  *           + Initialization and Configuration
  *           + Communications handling
  *           + SMBUS management
  *           + I2C registers management
  *           + Data transfers management
  *           + DMA transfers management
  *           + Interrupts and flags management
  *
  *  @verbatim
 ============================================================================
                     ##### How to use this driver #####
 ============================================================================
   [..]
   (#) Enable peripheral clock using RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2Cx, ENABLE)
       function for I2C1 or I2C2.
   (#) Enable SDA, SCL  and SMBA (when used) GPIO clocks using 
       RCC_AHBPeriphClockCmd() function. 
   (#) Peripherals alternate function: 
       (++) Connect the pin to the desired peripherals' Alternate 
            Function (AF) using GPIO_PinAFConfig() function.
       (++) Configure the desired pin in alternate function by:
            GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
       (++) Select the type, OpenDrain and speed via  
            GPIO_PuPd, GPIO_OType and GPIO_Speed members
       (++) Call GPIO_Init() function.
   (#) Program the Mode, Timing , Own address, Ack and Acknowledged Address 
       using the I2C_Init() function.
   (#) Optionally you can enable/configure the following parameters without
       re-initialization (i.e there is no need to call again I2C_Init() function):
       (++) Enable the acknowledge feature using I2C_AcknowledgeConfig() function.
       (++) Enable the dual addressing mode using I2C_DualAddressCmd() function.
       (++) Enable the general call using the I2C_GeneralCallCmd() function.
       (++) Enable the clock stretching using I2C_StretchClockCmd() function.
       (++) Enable the PEC Calculation using I2C_CalculatePEC() function.
       (++) For SMBus Mode:
            (+++) Enable the SMBusAlert pin using I2C_SMBusAlertCmd() function.
   (#) Enable the NVIC and the corresponding interrupt using the function
       I2C_ITConfig() if you need to use interrupt mode.
   (#) When using the DMA mode 
      (++) Configure the DMA using DMA_Init() function.
      (++) Active the needed channel Request using I2C_DMACmd() function.
   (#) Enable the I2C using the I2C_Cmd() function.
   (#) Enable the DMA using the DMA_Cmd() function when using DMA mode in the 
       transfers. 
   [..]
   (@) When using I2C in Fast Mode Plus, SCL and SDA pin 20mA current drive capability
       must be enabled by setting the driving capability control bit in SYSCFG.

    @endverbatim
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C 
  * @brief I2C driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define CR1_CLEAR_MASK_I2C          ((uint32_t)0x00CFE0FF)  /*<! I2C CR1 clear register Mask */
#define CR2_CLEAR_MASK_I2C          ((uint32_t)0x07FF7FFF)  /*<! I2C CR2 clear register Mask */
#define TIMING_CLEAR_MASK       ((uint32_t)0xF0FFFFFF)  /*<! I2C TIMING clear register Mask */
#define ERROR_IT_MASK           ((uint32_t)0x00003F00)  /*<! I2C Error interrupt register Mask */
#define TC_IT_MASK              ((uint32_t)0x000000C0)  /*<! I2C TC interrupt register Mask */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2C_Private_Functions
  * @{
  */


/** @defgroup I2C_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
           ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provides a set of functions allowing to initialize the I2C Mode,
         I2C Timing, I2C filters, I2C Addressing mode, I2C OwnAddress1.

    [..] The I2C_Init() function follows the I2C configuration procedures (these procedures 
         are available in reference manual).

    [..] When the Software Reset is performed using I2C_SoftwareResetCmd() function, the internal
         states machines are reset and communication control bits, as well as status bits come 
         back to their reset value.

    [..] Before enabling Stop mode using I2C_StopModeCmd() I2C Clock source must be set to
         HSI and Digital filters must be disabled.

    [..] Before enabling Own Address 2 via I2C_DualAddressCmd() function, OA2 and mask should be
         configured using I2C_OwnAddress2Config() function.

    [..] I2C_SlaveByteControlCmd() enable Slave byte control that allow user to get control of 
         each byte in slave mode when NBYTES is set to 0x01.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval None
  */
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  if (I2Cx == I2C1)
  {
    /* Enable I2C1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    /* Release I2C1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
  }
  else
  {
    /* Enable I2C2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
    /* Release I2C2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
  }
}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified
  *         parameters in the I2C_InitStruct.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_ANALOG_FILTER(I2C_InitStruct->I2C_AnalogFilter));
  assert_param(IS_I2C_DIGITAL_FILTER(I2C_InitStruct->I2C_DigitalFilter));
  assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
  assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddress1));
  assert_param(IS_I2C_ACK(I2C_InitStruct->I2C_Ack));
  assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AcknowledgedAddress));

  /* Disable I2Cx Peripheral */
  I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PE);

  /*---------------------------- I2Cx FILTERS Configuration ------------------*/
  /* Get the I2Cx CR1 value */
  tmpreg = I2Cx->CR1;
  /* Clear I2Cx CR1 register */
  tmpreg &= CR1_CLEAR_MASK_I2C;
  /* Configure I2Cx: analog and digital filter */
  /* Set ANFOFF bit according to I2C_AnalogFilter value */
  /* Set DFN bits according to I2C_DigitalFilter value */
  tmpreg |= (uint32_t)I2C_InitStruct->I2C_AnalogFilter |(I2C_InitStruct->I2C_DigitalFilter << 8);

  /* Write to I2Cx CR1 */
  I2Cx->CR1 = tmpreg;

  /*---------------------------- I2Cx TIMING Configuration -------------------*/
  /* Configure I2Cx: Timing */
  /* Set TIMINGR bits according to I2C_Timing */
  /* Write to I2Cx TIMING */
  I2Cx->TIMINGR = I2C_InitStruct->I2C_Timing & TIMING_CLEAR_MASK;

  /* Enable I2Cx Peripheral */
  I2Cx->CR1 |= I2C_CR1_PE;

  /*---------------------------- I2Cx OAR1 Configuration ---------------------*/
  /* Clear tmpreg local variable */
  tmpreg = 0;
  /* Clear OAR1 register */
  I2Cx->OAR1 = (uint32_t)tmpreg;
  /* Clear OAR2 register */
  I2Cx->OAR2 = (uint32_t)tmpreg;
  /* Configure I2Cx: Own Address1 and acknowledged address */
  /* Set OA1MODE bit according to I2C_AcknowledgedAddress value */
  /* Set OA1 bits according to I2C_OwnAddress1 value */
  tmpreg = (uint32_t)((uint32_t)I2C_InitStruct->I2C_AcknowledgedAddress | \
                      (uint32_t)I2C_InitStruct->I2C_OwnAddress1);
  /* Write to I2Cx OAR1 */
  I2Cx->OAR1 = tmpreg;
  /* Enable Own Address1 acknowledgement */
  I2Cx->OAR1 |= I2C_OAR1_OA1EN;

  /*---------------------------- I2Cx MODE Configuration ---------------------*/
  /* Configure I2Cx: mode */
  /* Set SMBDEN and SMBHEN bits according to I2C_Mode value */
  tmpreg = I2C_InitStruct->I2C_Mode;
  /* Write to I2Cx CR1 */
  I2Cx->CR1 |= tmpreg;

  /*---------------------------- I2Cx ACK Configuration ----------------------*/
  /* Get the I2Cx CR2 value */
  tmpreg = I2Cx->CR2;
  /* Clear I2Cx CR2 register */
  tmpreg &= CR2_CLEAR_MASK_I2C;
  /* Configure I2Cx: acknowledgement */
  /* Set NACK bit according to I2C_Ack value */
  tmpreg |= I2C_InitStruct->I2C_Ack;
  /* Write to I2Cx CR2 */
  I2Cx->CR2 = tmpreg;
}

/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
  /*---------------- Reset I2C init structure parameters values --------------*/
  /* Initialize the I2C_Timing member */
  I2C_InitStruct->I2C_Timing = 0;
  /* Initialize the I2C_AnalogFilter member */
  I2C_InitStruct->I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  /* Initialize the I2C_DigitalFilter member */
  I2C_InitStruct->I2C_DigitalFilter = 0;
  /* Initialize the I2C_Mode member */
  I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct->I2C_OwnAddress1 = 0;
  /* Initialize the I2C_Ack member */
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}

/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->CR1 |= I2C_CR1_PE;
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PE);
  }
}

/**
  * @brief  Enables or disables the specified I2C software reset.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval None
  */
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Disable peripheral */
  I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PE);

  /* Perform a dummy read to delay the disable of peripheral for minimum
     3 APB clock cycles to perform the software reset functionality */
  *(__IO uint32_t *)(uint32_t)I2Cx; 

  /* Enable peripheral */
  I2Cx->CR1 |= I2C_CR1_PE;
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_IT_ERRI: Error interrupt mask
  *            @arg I2C_IT_TCI: Transfer Complete interrupt mask
  *            @arg I2C_IT_STOPI: Stop Detection interrupt mask
  *            @arg I2C_IT_NACKI: Not Acknowledge received interrupt mask
  *            @arg I2C_IT_ADDRI: Address Match interrupt mask  
  *            @arg I2C_IT_RXI: RX interrupt mask
  *            @arg I2C_IT_TXI: TX interrupt mask
  * @param  NewState: new state of the specified I2C interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint32_t I2C_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->CR1 |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_IT);
  }
}

/**
  * @brief  Enables or disables the I2C Clock stretching.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx Clock stretching.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable clock stretching */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_NOSTRETCH);    
  }
  else
  {
    /* Disable clock stretching  */
    I2Cx->CR1 |= I2C_CR1_NOSTRETCH;
  }
}

/**
  * @brief  Enables or disables I2C wakeup from stop mode.
  *         This function is not applicable for  STM32F030 devices.  
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx stop mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_StopModeCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable wakeup from stop mode */
    I2Cx->CR1 |= I2C_CR1_WUPEN;   
  }
  else
  {
    /* Disable wakeup from stop mode */    
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_WUPEN); 
  }
}

/**
  * @brief  Enables or disables the I2C own address 2.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C own address 2.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable own address 2 */
    I2Cx->OAR2 |= I2C_OAR2_OA2EN;
  }
  else
  {
    /* Disable own address 2 */
    I2Cx->OAR2 &= (uint32_t)~((uint32_t)I2C_OAR2_OA2EN);
  }
}    

/**
  * @brief  Configures the I2C slave own address 2 and mask.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @param  Mask: specifies own address 2 mask to be programmed.
  *          This parameter can be one of the following values:
  *            @arg I2C_OA2_NoMask: no mask.
  *            @arg I2C_OA2_Mask01: OA2[1] is masked and don't care.
  *            @arg I2C_OA2_Mask02: OA2[2:1] are masked and don't care.
  *            @arg I2C_OA2_Mask03: OA2[3:1] are masked and don't care.
  *            @arg I2C_OA2_Mask04: OA2[4:1] are masked and don't care.
  *            @arg I2C_OA2_Mask05: OA2[5:1] are masked and don't care.
  *            @arg I2C_OA2_Mask06: OA2[6:1] are masked and don't care.
  *            @arg I2C_OA2_Mask07: OA2[7:1] are masked and don't care.
  * @retval None
  */
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_OWN_ADDRESS2(Address));
  assert_param(IS_I2C_OWN_ADDRESS2_MASK(Mask));
  
  /* Get the old register value */
  tmpreg = I2Cx->OAR2;

  /* Reset I2Cx OA2 bit [7:1] and OA2MSK bit [1:0]  */
  tmpreg &= (uint32_t)~((uint32_t)(I2C_OAR2_OA2 | I2C_OAR2_OA2MSK));

  /* Set I2Cx SADD */
  tmpreg |= (uint32_t)(((uint32_t)Address & I2C_OAR2_OA2) | \
            (((uint32_t)Mask << 8) & I2C_OAR2_OA2MSK)) ;

  /* Store the new register value */
  I2Cx->OAR2 = tmpreg;
}

/**
  * @brief  Enables or disables the I2C general call mode.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C general call mode.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable general call mode */
    I2Cx->CR1 |= I2C_CR1_GCEN;
  }
  else
  {
    /* Disable general call mode */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_GCEN);
  }
} 

/**
  * @brief  Enables or disables the I2C slave byte control.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C slave byte control.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_SlaveByteControlCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable slave byte control */
    I2Cx->CR1 |= I2C_CR1_SBC;
  }
  else
  {
    /* Disable slave byte control */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_SBC);
  }
}

/**
  * @brief  Configures the slave address to be transmitted after start generation.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @note   This function should be called before generating start condition.
  * @retval None
  */
void I2C_SlaveAddressConfig(I2C_TypeDef* I2Cx, uint16_t Address)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SLAVE_ADDRESS(Address));
               
  /* Get the old register value */
  tmpreg = I2Cx->CR2;

  /* Reset I2Cx SADD bit [9:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_CR2_SADD);

  /* Set I2Cx SADD */
  tmpreg |= (uint32_t)((uint32_t)Address & I2C_CR2_SADD);

  /* Store the new register value */
  I2Cx->CR2 = tmpreg;
}
  
/**
  * @brief  Enables or disables the I2C 10-bit addressing mode for the master.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C 10-bit addressing mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function should be called before generating start condition.
  * @retval None
  */
void I2C_10BitAddressingModeCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable 10-bit addressing mode */
    I2Cx->CR2 |= I2C_CR2_ADD10;
  }
  else
  {
    /* Disable 10-bit addressing mode */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_ADD10);
  }
} 

/**
  * @}
  */


/** @defgroup I2C_Group2 Communications handling functions
 *  @brief   Communications handling functions 
 *
@verbatim
 ===============================================================================
                  ##### Communications handling functions #####
 ===============================================================================  
    [..] This section provides a set of functions that handles I2C communication.

    [..] Automatic End mode is enabled using I2C_AutoEndCmd() function. When Reload
         mode is enabled via I2C_ReloadCmd() AutoEnd bit has no effect.

    [..] I2C_NumberOfBytesConfig() function set the number of bytes to be transferred,
         this configuration should be done before generating start condition in master 
         mode.

    [..] When switching from master write operation to read operation in 10Bit addressing
         mode, master can only sends the 1st 7 bits of the 10 bit address, followed by 
         Read direction by enabling HEADR bit using I2C_10BitAddressHeader() function.

    [..] In master mode, when transferring more than 255 bytes Reload mode should be used
         to handle communication. In the first phase of transfer, Nbytes should be set to 
         255. After transferring these bytes TCR flag is set and I2C_TransferHandling()
         function should be called to handle remaining communication.

    [..] In master mode, when software end mode is selected when all data is transferred
         TC flag is set I2C_TransferHandling() function should be called to generate STOP
         or generate ReStart.

@endverbatim
  * @{
  */
  
/**
  * @brief  Enables or disables the I2C automatic end mode (stop condition is 
  *         automatically sent when nbytes data are transferred).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C automatic end mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function has effect if Reload mode is disabled.
  * @retval None
  */
void I2C_AutoEndCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Auto end mode */
    I2Cx->CR2 |= I2C_CR2_AUTOEND;
  }
  else
  {
    /* Disable Auto end mode */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_AUTOEND);
  }
} 

/**
  * @brief  Enables or disables the I2C nbytes reload mode.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the nbytes reload mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ReloadCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Auto Reload mode */
    I2Cx->CR2 |= I2C_CR2_RELOAD;
  }
  else
  {
    /* Disable Auto Reload mode */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_RELOAD);
  }
}

/**
  * @brief  Configures the number of bytes to be transmitted/received.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Number_Bytes: specifies the number of bytes to be programmed.
  * @retval None
  */
void I2C_NumberOfBytesConfig(I2C_TypeDef* I2Cx, uint8_t Number_Bytes)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  tmpreg = I2Cx->CR2;

  /* Reset I2Cx Nbytes bit [7:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_CR2_NBYTES);

  /* Set I2Cx Nbytes */
  tmpreg |= (uint32_t)(((uint32_t)Number_Bytes << 16 ) & I2C_CR2_NBYTES);

  /* Store the new register value */
  I2Cx->CR2 = tmpreg;
}  
  
/**
  * @brief  Configures the type of transfer request for the master.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_Direction: specifies the transfer request direction to be programmed.
  *          This parameter can be one of the following values:
  *            @arg I2C_Direction_Transmitter: Master request a write transfer
  *            @arg I2C_Direction_Receiver: Master request a read transfer  
  * @retval None
  */
void I2C_MasterRequestConfig(I2C_TypeDef* I2Cx, uint16_t I2C_Direction)
{
/* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));
  
  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction == I2C_Direction_Transmitter)
  {
    /* Request a write Transfer */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_RD_WRN);
  }
  else
  {
    /* Request a read Transfer */
    I2Cx->CR2 |= I2C_CR2_RD_WRN;
  }
}  
  
/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C START condition generation.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2Cx->CR2 |= I2C_CR2_START;
  }
  else
  {
    /* Disable the START condition generation */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_START);
  }
}  
  
/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C STOP condition generation.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2Cx->CR2 |= I2C_CR2_STOP;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_STOP);
  }
}  

/**
  * @brief  Enables or disables the I2C 10-bit header only mode with read direction.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C 10-bit header only mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This mode can be used only when switching from master transmitter mode 
  *         to master receiver mode.
  * @retval None
  */
void I2C_10BitAddressHeaderCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable 10-bit header only mode */
    I2Cx->CR2 |= I2C_CR2_HEAD10R;
  }
  else
  {
    /* Disable 10-bit header only mode */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_HEAD10R);
  }
}    

/**
  * @brief  Generates I2C communication Acknowledge.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the Acknowledge.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable ACK generation */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_NACK);    
  }
  else
  {
    /* Enable NACK generation */
    I2Cx->CR2 |= I2C_CR2_NACK;
  }
}

/**
  * @brief  Returns the I2C slave matched address .
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The value of the slave matched address .
  */
uint8_t I2C_GetAddressMatched(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the slave matched address in the SR1 register */
  return (uint8_t)(((uint32_t)I2Cx->ISR & I2C_ISR_ADDCODE) >> 16) ;
}

/**
  * @brief  Returns the I2C slave received request.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The value of the received request.
  */
uint16_t I2C_GetTransferDirection(I2C_TypeDef* I2Cx)
{
  uint32_t tmpreg = 0;
  uint16_t direction = 0;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the slave matched address in the SR1 register */
  tmpreg = (uint32_t)(I2Cx->ISR & I2C_ISR_DIR);
  
  /* If write transfer is requested */
  if (tmpreg == 0)
  {
    /* write transfer is requested */
    direction = I2C_Direction_Transmitter;
  }
  else
  {
    /* Read transfer is requested */
    direction = I2C_Direction_Receiver;
  }  
  return direction;
}

/**
  * @brief  Handles I2Cx communication when starting transfer or during transfer (TC or TCR flag are set).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @param  Number_Bytes: specifies the number of bytes to be programmed.
  *          This parameter must be a value between 0 and 255.
  * @param  ReloadEndMode: new state of the I2C START condition generation.
  *          This parameter can be one of the following values:
  *            @arg I2C_Reload_Mode: Enable Reload mode .
  *            @arg I2C_AutoEnd_Mode: Enable Automatic end mode.
  *            @arg I2C_SoftEnd_Mode: Enable Software end mode.
  * @param  StartStopMode: new state of the I2C START condition generation.
  *          This parameter can be one of the following values:
  *            @arg I2C_No_StartStop: Don't Generate stop and start condition.
  *            @arg I2C_Generate_Stop: Generate stop condition (Number_Bytes should be set to 0).
  *            @arg I2C_Generate_Start_Read: Generate Restart for read request.
  *            @arg I2C_Generate_Start_Write: Generate Restart for write request.
  * @retval None
  */
void I2C_TransferHandling(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Number_Bytes, uint32_t ReloadEndMode, uint32_t StartStopMode)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SLAVE_ADDRESS(Address));  
  assert_param(IS_RELOAD_END_MODE(ReloadEndMode));
  assert_param(IS_START_STOP_MODE(StartStopMode));
    
  /* Get the CR2 register value */
  tmpreg = I2Cx->CR2;
  
  /* clear tmpreg specific bits */
  tmpreg &= (uint32_t)~((uint32_t)(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP));
  
  /* update tmpreg */
  tmpreg |= (uint32_t)(((uint32_t)Address & I2C_CR2_SADD) | (((uint32_t)Number_Bytes << 16 ) & I2C_CR2_NBYTES) | \
            (uint32_t)ReloadEndMode | (uint32_t)StartStopMode);
  
  /* update CR2 register */
  I2Cx->CR2 = tmpreg;  
}

/**
  * @}
  */


/** @defgroup I2C_Group3 SMBUS management functions
 *  @brief   SMBUS management functions 
 *
@verbatim
 ===============================================================================
                      ##### SMBUS management functions #####
 ===============================================================================  
    [..] This section provides a set of functions that handles SMBus communication
         and timeouts detection.

    [..] The SMBus Device default address (0b1100 001) is enabled by calling I2C_Init()
         function and setting I2C_Mode member of I2C_InitTypeDef() structure to 
         I2C_Mode_SMBusDevice.

    [..] The SMBus Host address (0b0001 000) is enabled by calling I2C_Init()
         function and setting I2C_Mode member of I2C_InitTypeDef() structure to 
         I2C_Mode_SMBusHost.

    [..] The Alert Response Address (0b0001 100) is enabled using I2C_SMBusAlertCmd()
         function.

    [..] To detect cumulative SCL stretch in master and slave mode, TIMEOUTB should be 
         configured (in accordance to SMBus specification) using I2C_TimeoutBConfig() 
         function then I2C_ExtendedClockTimeoutCmd() function should be called to enable
         the detection.

    [..] SCL low timeout is detected by configuring TIMEOUTB using I2C_TimeoutBConfig()
         function followed by the call of I2C_ClockTimeoutCmd(). When adding to this 
         procedure the call of I2C_IdleClockTimeoutCmd() function, Bus Idle condition 
         (both SCL and SDA high) is detected also.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables I2C SMBus alert.
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx SMBus alert.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_SMBusAlertCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable SMBus alert */
    I2Cx->CR1 |= I2C_CR1_ALERTEN;   
  }
  else
  {
    /* Disable SMBus alert */    
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_ALERTEN); 
  }
}

/**
  * @brief  Enables or disables I2C Clock Timeout (SCL Timeout detection).
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx clock Timeout.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Clock Timeout */
    I2Cx->TIMEOUTR |= I2C_TIMEOUTR_TIMOUTEN;   
  }
  else
  {
    /* Disable Clock Timeout */    
    I2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TIMOUTEN); 
  }
}

/**
  * @brief  Enables or disables I2C Extended Clock Timeout (SCL cumulative Timeout detection).
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx Extended clock Timeout.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ExtendedClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Clock Timeout */
    I2Cx->TIMEOUTR |= I2C_TIMEOUTR_TEXTEN;   
  }
  else
  {
    /* Disable Clock Timeout */    
    I2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TEXTEN); 
  }
}

/**
  * @brief  Enables or disables I2C Idle Clock Timeout (Bus idle SCL and SDA 
  *         high detection).
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx Idle clock Timeout.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_IdleClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Clock Timeout */
    I2Cx->TIMEOUTR |= I2C_TIMEOUTR_TIDLE;   
  }
  else
  {
    /* Disable Clock Timeout */    
    I2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TIDLE); 
  }
}

/**
  * @brief  Configures the I2C Bus Timeout A (SCL Timeout when TIDLE = 0 or Bus 
  *         idle SCL and SDA high when TIDLE = 1).
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  Timeout: specifies the TimeoutA to be programmed. 
  * @retval None
  */
void I2C_TimeoutAConfig(I2C_TypeDef* I2Cx, uint16_t Timeout)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_I2C_TIMEOUT(Timeout));
    
  /* Get the old register value */
  tmpreg = I2Cx->TIMEOUTR;

  /* Reset I2Cx TIMEOUTA bit [11:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TIMEOUTA);

  /* Set I2Cx TIMEOUTA */
  tmpreg |= (uint32_t)((uint32_t)Timeout & I2C_TIMEOUTR_TIMEOUTA) ;

  /* Store the new register value */
  I2Cx->TIMEOUTR = tmpreg;
}

/**
  * @brief  Configures the I2C Bus Timeout B (SCL cumulative Timeout).
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  Timeout: specifies the TimeoutB to be programmed. 
  * @retval None
  */
void I2C_TimeoutBConfig(I2C_TypeDef* I2Cx, uint16_t Timeout)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_I2C_TIMEOUT(Timeout));

  /* Get the old register value */
  tmpreg = I2Cx->TIMEOUTR;

  /* Reset I2Cx TIMEOUTB bit [11:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TIMEOUTB);

  /* Set I2Cx TIMEOUTB */
  tmpreg |= (uint32_t)(((uint32_t)Timeout << 16) & I2C_TIMEOUTR_TIMEOUTB) ;

  /* Store the new register value */
  I2Cx->TIMEOUTR = tmpreg;
}

/**
  * @brief  Enables or disables I2C PEC calculation.
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx PEC calculation.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable PEC calculation */
    I2Cx->CR1 |= I2C_CR1_PECEN;   
  }
  else
  {
    /* Disable PEC calculation */    
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PECEN); 
  }
}

/**
  * @brief  Enables or disables I2C PEC transmission/reception request.
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx PEC request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_PECRequestCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable PEC transmission/reception request */
    I2Cx->CR2 |= I2C_CR2_PECBYTE;   
  }
  else
  {
    /* Disable PEC transmission/reception request */    
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_PECBYTE); 
  }
}

/**
  * @brief  Returns the I2C PEC.
  * @param  I2Cx: where x can be 1 to select the I2C peripheral.
  * @retval The value of the PEC .
  */
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_1_PERIPH(I2Cx));
  
  /* Return the slave matched address in the SR1 register */
  return (uint8_t)((uint32_t)I2Cx->PECR & I2C_PECR_PEC);
}

/**
  * @}
  */  


/** @defgroup I2C_Group4 I2C registers management functions
 *  @brief   I2C registers management functions 
 *
@verbatim
 ===============================================================================
                ##### I2C registers management functions #####
 ===============================================================================  
    [..] This section provides a functions that allow user the management of 
         I2C registers.

@endverbatim
  * @{
  */

  /**
  * @brief  Reads the specified I2C register and returns its value.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_Register: specifies the register to read.
  *          This parameter can be one of the following values:
  *            @arg I2C_Register_CR1: CR1 register.
  *            @arg I2C_Register_CR2: CR2 register.
  *            @arg I2C_Register_OAR1: OAR1 register.
  *            @arg I2C_Register_OAR2: OAR2 register.
  *            @arg I2C_Register_TIMINGR: TIMING register.
  *            @arg I2C_Register_TIMEOUTR: TIMEOUTR register.
  *            @arg I2C_Register_ISR: ISR register.
  *            @arg I2C_Register_ICR: ICR register.
  *            @arg I2C_Register_PECR: PECR register.
  *            @arg I2C_Register_RXDR: RXDR register.
  *            @arg I2C_Register_TXDR: TXDR register.
  * @retval The value of the read register.
  */
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));

  tmp = (uint32_t)I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint32_t *) tmp);
}

/**
  * @}
  */  
  
/** @defgroup I2C_Group5 Data transfers management functions
 *  @brief   Data transfers management functions 
 *
@verbatim
 ===============================================================================
                ##### Data transfers management functions #####
 ===============================================================================  
    [..] This subsection provides a set of functions allowing to manage 
         the I2C data transfers.

    [..] The read access of the I2C_RXDR register can be done using 
         the I2C_ReceiveData() function and returns the received value.
         Whereas a write access to the I2C_TXDR can be done using I2C_SendData()
         function and stores the written data into TXDR.
@endverbatim
  * @{
  */  
  
/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Write in the DR register the data to be sent */
  I2Cx->TXDR = (uint8_t)Data;
}

/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the data in the DR register */
  return (uint8_t)I2Cx->RXDR;
}  

/**
  * @}
  */ 


/** @defgroup I2C_Group6 DMA transfers management functions
 *  @brief   DMA transfers management functions 
 *
@verbatim
 ===============================================================================
                ##### DMA transfers management functions #####
 ===============================================================================  
    [..] This section provides two functions that can be used only in DMA mode.
    [..] In DMA Mode, the I2C communication can be managed by 2 DMA Channel 
         requests:
         (#) I2C_DMAReq_Tx: specifies the Tx buffer DMA transfer request.
         (#) I2C_DMAReq_Rx: specifies the Rx buffer DMA transfer request.
    [..] In this Mode it is advised to use the following function:
         (+) I2C_DMACmd(I2C_TypeDef* I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState);
@endverbatim
  * @{
  */  
    
/**
  * @brief  Enables or disables the I2C DMA interface.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_DMAReq: specifies the I2C DMA transfer request to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_DMAReq_Tx: Tx DMA transfer request
  *            @arg I2C_DMAReq_Rx: Rx DMA transfer request
  * @param  NewState: new state of the selected I2C DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DMACmd(I2C_TypeDef* I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_DMA_REQ(I2C_DMAReq));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C DMA requests */
    I2Cx->CR1 |= I2C_DMAReq;
  }
  else
  {
    /* Disable the selected I2C DMA requests */
    I2Cx->CR1 &= (uint32_t)~I2C_DMAReq;
  }
}
/**
  * @}
  */  


/** @defgroup I2C_Group7 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions  #####
 ===============================================================================  
    [..] This section provides functions allowing to configure the I2C Interrupts 
         sources and check or clear the flags or pending bits status.
         The user should identify which mode will be used in his application to manage 
         the communication: Polling mode, Interrupt mode or DMA mode(refer I2C_Group6).

  *** Polling Mode ***
  ====================
    [..] In Polling Mode, the I2C communication can be managed by 15 flags:
        (#) I2C_FLAG_TXE: to indicate the status of Transmit data register empty flag.
        (#) I2C_FLAG_TXIS: to indicate the status of Transmit interrupt status flag .
        (#) I2C_FLAG_RXNE: to indicate the status of Receive data register not empty flag.
        (#) I2C_FLAG_ADDR: to indicate the status of Address matched flag (slave mode).
        (#) I2C_FLAG_NACKF: to indicate the status of NACK received flag.
        (#) I2C_FLAG_STOPF: to indicate the status of STOP detection flag.
        (#) I2C_FLAG_TC: to indicate the status of Transfer complete flag(master mode).
        (#) I2C_FLAG_TCR: to indicate the status of Transfer complete reload flag.
        (#) I2C_FLAG_BERR: to indicate the status of Bus error flag.
        (#) I2C_FLAG_ARLO: to indicate the status of Arbitration lost flag.
        (#) I2C_FLAG_OVR: to indicate the status of Overrun/Underrun flag.
        (#) I2C_FLAG_PECERR: to indicate the status of PEC error in reception flag.
        (#) I2C_FLAG_TIMEOUT: to indicate the status of Timeout or Tlow detection flag.
        (#) I2C_FLAG_ALERT: to indicate the status of SMBus Alert flag.
        (#) I2C_FLAG_BUSY: to indicate the status of Bus busy flag.

    [..] In this Mode it is advised to use the following functions:
        (+) FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
        (+) void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);

    [..]
        (@)Do not use the BUSY flag to handle each data transmission or reception.It is 
           better to use the TXIS and RXNE flags instead.

  *** Interrupt Mode ***
  ======================
    [..] In Interrupt Mode, the I2C communication can be managed by 7 interrupt sources
         and 15 pending bits: 
    [..] Interrupt Source:
        (#) I2C_IT_ERRI: specifies the interrupt source for the Error interrupt.
        (#) I2C_IT_TCI: specifies the interrupt source for the Transfer Complete interrupt.
        (#) I2C_IT_STOPI: specifies the interrupt source for the Stop Detection interrupt.
        (#) I2C_IT_NACKI: specifies the interrupt source for the Not Acknowledge received interrupt.
        (#) I2C_IT_ADDRI: specifies the interrupt source for the Address Match interrupt.
        (#) I2C_IT_RXI: specifies the interrupt source for the RX interrupt.
        (#) I2C_IT_TXI: specifies the interrupt source for the TX interrupt.

    [..] Pending Bits:
        (#) I2C_IT_TXIS: to indicate the status of Transmit interrupt status flag.
        (#) I2C_IT_RXNE: to indicate the status of Receive data register not empty flag.
        (#) I2C_IT_ADDR: to indicate the status of Address matched flag (slave mode).
        (#) I2C_IT_NACKF: to indicate the status of NACK received flag.
        (#) I2C_IT_STOPF: to indicate the status of STOP detection flag.
        (#) I2C_IT_TC: to indicate the status of Transfer complete flag (master mode).
        (#) I2C_IT_TCR: to indicate the status of Transfer complete reload flag.
        (#) I2C_IT_BERR: to indicate the status of Bus error flag.
        (#) I2C_IT_ARLO: to indicate the status of Arbitration lost flag.
        (#) I2C_IT_OVR: to indicate the status of Overrun/Underrun flag.
        (#) I2C_IT_PECERR: to indicate the status of PEC error in reception flag.
        (#) I2C_IT_TIMEOUT: to indicate the status of Timeout or Tlow detection flag.
        (#) I2C_IT_ALERT: to indicate the status of SMBus Alert flag.

    [..] In this Mode it is advised to use the following functions:
        (+) void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
        (+) ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);

@endverbatim
  * @{
  */  

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_FLAG: specifies the flag to check. 
  *          This parameter can be one of the following values:
  *            @arg I2C_FLAG_TXE: Transmit data register empty
  *            @arg I2C_FLAG_TXIS: Transmit interrupt status
  *            @arg I2C_FLAG_RXNE: Receive data register not empty
  *            @arg I2C_FLAG_ADDR: Address matched (slave mode)
  *            @arg I2C_FLAG_NACKF: NACK received flag
  *            @arg I2C_FLAG_STOPF: STOP detection flag
  *            @arg I2C_FLAG_TC: Transfer complete (master mode)
  *            @arg I2C_FLAG_TCR: Transfer complete reload
  *            @arg I2C_FLAG_BERR: Bus error
  *            @arg I2C_FLAG_ARLO: Arbitration lost
  *            @arg I2C_FLAG_OVR: Overrun/Underrun
  *            @arg I2C_FLAG_PECERR: PEC error in reception
  *            @arg I2C_FLAG_TIMEOUT: Timeout or Tlow detection flag
  *            @arg I2C_FLAG_ALERT: SMBus Alert
  *            @arg I2C_FLAG_BUSY: Bus busy
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
  uint32_t tmpreg = 0;
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));
  
  /* Get the ISR register value */
  tmpreg = I2Cx->ISR;
  
  /* Get flag status */
  tmpreg &= I2C_FLAG;
  
  if(tmpreg != 0)
  {
    /* I2C_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_FLAG is reset */
    bitstatus = RESET;
  }
  return bitstatus;
} 

/**
  * @brief  Clears the I2Cx's pending flags.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_FLAG: specifies the flag to clear. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_FLAG_ADDR: Address matched (slave mode)
  *            @arg I2C_FLAG_NACKF: NACK received flag
  *            @arg I2C_FLAG_STOPF: STOP detection flag
  *            @arg I2C_FLAG_BERR: Bus error
  *            @arg I2C_FLAG_ARLO: Arbitration lost
  *            @arg I2C_FLAG_OVR: Overrun/Underrun
  *            @arg I2C_FLAG_PECERR: PEC error in reception
  *            @arg I2C_FLAG_TIMEOUT: Timeout or Tlow detection flag
  *            @arg I2C_FLAG_ALERT: SMBus Alert
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{ 
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));

  /* Clear the selected flag */
  I2Cx->ICR = I2C_FLAG;
  }

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg I2C_IT_TXIS: Transmit interrupt status
  *            @arg I2C_IT_RXNE: Receive data register not empty
  *            @arg I2C_IT_ADDR: Address matched (slave mode)
  *            @arg I2C_IT_NACKF: NACK received flag
  *            @arg I2C_IT_STOPF: STOP detection flag
  *            @arg I2C_IT_TC: Transfer complete (master mode)
  *            @arg I2C_IT_TCR: Transfer complete reload
  *            @arg I2C_IT_BERR: Bus error
  *            @arg I2C_IT_ARLO: Arbitration lost
  *            @arg I2C_IT_OVR: Overrun/Underrun
  *            @arg I2C_IT_PECERR: PEC error in reception
  *            @arg I2C_IT_TIMEOUT: Timeout or Tlow detection flag
  *            @arg I2C_IT_ALERT: SMBus Alert
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  uint32_t tmpreg = 0;
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_IT(I2C_IT));

  /* Check if the interrupt source is enabled or not */
  /* If Error interrupt */
  if ((uint32_t)(I2C_IT & ERROR_IT_MASK))
  {
    enablestatus = (uint32_t)((I2C_CR1_ERRIE) & (I2Cx->CR1));
  }
  /* If TC interrupt */
  else if ((uint32_t)(I2C_IT & TC_IT_MASK))
  {
    enablestatus = (uint32_t)((I2C_CR1_TCIE) & (I2Cx->CR1));
  }
  else
  {
    enablestatus = (uint32_t)((I2C_IT) & (I2Cx->CR1));
  }
  
  /* Get the ISR register value */
  tmpreg = I2Cx->ISR;

  /* Get flag status */
  tmpreg &= I2C_IT;

  /* Check the status of the specified I2C flag */
  if((tmpreg != RESET) && enablestatus)
  {
    /* I2C_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_IT is reset */
    bitstatus = RESET;
  }

  /* Return the I2C_IT status */
  return bitstatus;
}

/**
  * @brief  Clears the I2Cx's interrupt pending bits.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the interrupt pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg I2C_IT_ADDR: Address matched (slave mode)
  *            @arg I2C_IT_NACKF: NACK received flag
  *            @arg I2C_IT_STOPF: STOP detection flag
  *            @arg I2C_IT_BERR: Bus error
  *            @arg I2C_IT_ARLO: Arbitration lost
  *            @arg I2C_IT_OVR: Overrun/Underrun
  *            @arg I2C_IT_PECERR: PEC error in reception
  *            @arg I2C_IT_TIMEOUT: Timeout or Tlow detection flag
  *            @arg I2C_IT_ALERT: SMBus Alert
  * @retval The new state of I2C_IT (SET or RESET).
  */
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_IT(I2C_IT));

  /* Clear the selected flag */
  I2Cx->ICR = I2C_IT;
}

/**
  * @}
  */  
  
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_iwdg.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Independent watchdog (IWDG) peripheral:           
  *           + Prescaler and Counter configuration
  *           + IWDG activation
  *           + Flag management
  *
  *  @verbatim  
  *  
  ============================================================================== 
                          ##### IWDG features #####
  ============================================================================== 
    [..] The IWDG can be started by either software or hardware (configurable
         through option byte).
             
    [..] The IWDG is clocked by its own dedicated low-speed clock (LSI) and
         thus stays active even if the main clock fails.
         Once the IWDG is started, the LSI is forced ON and cannot be disabled
         (LSI cannot be disabled too), and the counter starts counting down from 
         the reset value of 0xFFF. When it reaches the end of count value (0x000)
         a system reset is generated.
         The IWDG counter should be reloaded at regular intervals to prevent
         an MCU reset.
                             
    [..] The IWDG is implemented in the VDD voltage domain that is still functional
         in STOP and STANDBY mode (IWDG reset can wake-up from STANDBY).
              
    [..] IWDGRST flag in RCC_CSR register can be used to inform when a IWDG
         reset occurs.
              
    [..] Min-max timeout value @40KHz (LSI): ~0.1ms / ~28.3s
         The IWDG timeout may vary due to LSI frequency dispersion. STM32F0xx
         devices provide the capability to measure the LSI frequency (LSI clock
         should be seleted as RTC clock which is internally connected to TIM10 CH1
         input capture). The measured value can be used to have an IWDG timeout with
         an acceptable accuracy. 
         For more information, please refer to the STM32F0xx Reference manual.
            
                          ##### How to use this driver ##### 
  ============================================================================== 
    [..] This driver allows to use IWDG peripheral with either window option enabled
         or disabled. To do so follow one of the two procedures below.
    (#) Window option is enabled:    
        (++) Start the IWDG using IWDG_Enable() function, when the IWDG is used
             in software mode (no need to enable the LSI, it will be enabled
             by hardware).        
        (++) Enable write access to IWDG_PR and IWDG_RLR registers using
             IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable) function.
        (++) Configure the IWDG prescaler using IWDG_SetPrescaler() function.
        (++) Configure the IWDG counter value using IWDG_SetReload() function.
             This value will be loaded in the IWDG counter each time the counter
             is reloaded, then the IWDG will start counting down from this value.
        (++) Wait for the IWDG registers to be updated using IWDG_GetFlagStatus() function.
        (++) Configure the IWDG refresh window using IWDG_SetWindowValue() function.

    (#) Window option is disabled:    
        (++) Enable write access to IWDG_PR and IWDG_RLR registers using
             IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable) function.
        (++) Configure the IWDG prescaler using IWDG_SetPrescaler() function.
        (++) Configure the IWDG counter value using IWDG_SetReload() function.
             This value will be loaded in the IWDG counter each time the counter
             is reloaded, then the IWDG will start counting down from this value.
        (++) Wait for the IWDG registers to be updated using IWDG_GetFlagStatus() function.
        (++) reload the IWDG counter at regular intervals during normal operation 
             to prevent an MCU reset, using IWDG_ReloadCounter() function.
        (++) Start the IWDG using IWDG_Enable() function, when the IWDG is used
             in software mode (no need to enable the LSI, it will be enabled
             by hardware).
              
    @endverbatim
  *    
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup IWDG 
  * @brief IWDG driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------- IWDG registers bit mask ----------------------------*/
/* KR register bit mask */
#define KR_KEY_RELOAD    ((uint16_t)0xAAAA)
#define KR_KEY_ENABLE    ((uint16_t)0xCCCC)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup IWDG_Private_Functions
  * @{
  */

/** @defgroup IWDG_Group1 Prescaler and Counter configuration functions
 *  @brief   Prescaler and Counter configuration functions
 *
@verbatim   
  ==============================================================================
            ##### Prescaler and Counter configuration functions #####
  ==============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables write access to IWDG_PR and IWDG_RLR registers.
  * @param  IWDG_WriteAccess: new state of write access to IWDG_PR and IWDG_RLR registers.
  *          This parameter can be one of the following values:
  *            @arg IWDG_WriteAccess_Enable: Enable write access to IWDG_PR and IWDG_RLR registers
  *            @arg IWDG_WriteAccess_Disable: Disable write access to IWDG_PR and IWDG_RLR registers
  * @retval None
  */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess)
{
  /* Check the parameters */
  assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
  IWDG->KR = IWDG_WriteAccess;
}

/**
  * @brief  Sets IWDG Prescaler value.
  * @param  IWDG_Prescaler: specifies the IWDG Prescaler value.
  *          This parameter can be one of the following values:
  *            @arg IWDG_Prescaler_4: IWDG prescaler set to 4
  *            @arg IWDG_Prescaler_8: IWDG prescaler set to 8
  *            @arg IWDG_Prescaler_16: IWDG prescaler set to 16
  *            @arg IWDG_Prescaler_32: IWDG prescaler set to 32
  *            @arg IWDG_Prescaler_64: IWDG prescaler set to 64
  *            @arg IWDG_Prescaler_128: IWDG prescaler set to 128
  *            @arg IWDG_Prescaler_256: IWDG prescaler set to 256
  * @retval None
  */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));
  IWDG->PR = IWDG_Prescaler;
}

/**
  * @brief  Sets IWDG Reload value.
  * @param  Reload: specifies the IWDG Reload value.
  *          This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  */
void IWDG_SetReload(uint16_t Reload)
{
  /* Check the parameters */
  assert_param(IS_IWDG_RELOAD(Reload));
  IWDG->RLR = Reload;
}

/**
  * @brief  Reloads IWDG counter with value defined in the reload register
  *   (write access to IWDG_PR and IWDG_RLR registers disabled).
  * @param  None
  * @retval None
  */
void IWDG_ReloadCounter(void)
{
  IWDG->KR = KR_KEY_RELOAD;
}


/**
  * @brief  Sets the IWDG window value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  * @retval None
  */
void IWDG_SetWindowValue(uint16_t WindowValue)
{
  /* Check the parameters */
  assert_param(IS_IWDG_WINDOW_VALUE(WindowValue));
  IWDG->WINR = WindowValue;
}

/**
  * @}
  */

/** @defgroup IWDG_Group2 IWDG activation function
 *  @brief   IWDG activation function 
 *
@verbatim   
 ==============================================================================
                          ##### IWDG activation function #####
 ==============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables IWDG (write access to IWDG_PR and IWDG_RLR registers disabled).
  * @param  None
  * @retval None
  */
void IWDG_Enable(void)
{
  IWDG->KR = KR_KEY_ENABLE;
}

/**
  * @}
  */

/** @defgroup IWDG_Group3 Flag management function 
 *  @brief  Flag management function  
 *
@verbatim   
 ===============================================================================
                      ##### Flag management function ##### 
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified IWDG flag is set or not.
  * @param  IWDG_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg IWDG_FLAG_PVU: Prescaler Value Update on going
  *            @arg IWDG_FLAG_RVU: Reload Value Update on going
  *            @arg IWDG_FLAG_WVU: Counter Window Value Update on going
  * @retval The new state of IWDG_FLAG (SET or RESET).
  */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_IWDG_FLAG(IWDG_FLAG));
  if ((IWDG->SR & IWDG_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_misc.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides all the miscellaneous firmware functions (add-on
  *          to CMSIS functions).
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup MISC 
  * @brief MISC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup MISC_Private_Functions
  * @{
  */
/**
  *
@verbatim
 *******************************************************************************
                   ##### Interrupts configuration functions #####
 *******************************************************************************
    [..] This section provide functions allowing to configure the NVIC interrupts
        (IRQ). The Cortex-M0 exceptions are managed by CMSIS functions.
         (#) Enable and Configure the priority of the selected IRQ Channels. 
             The priority can be 0..3. 

        -@- Lower priority values gives higher priority.
        -@- Priority Order:
            (#@) Lowest priority.
            (#@) Lowest hardware priority (IRQn position).  
  
@endverbatim
*/

/**
  * @brief  Initializes the NVIC peripheral according to the specified
  *         parameters in the NVIC_InitStruct.
  * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
  *         the configuration information for the specified NVIC peripheral.
  * @retval None
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
  assert_param(IS_NVIC_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPriority));  
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02];
    tmppriority &= (uint32_t)(~(((uint32_t)0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8)));
    tmppriority |= (uint32_t)((((uint32_t)NVIC_InitStruct->NVIC_IRQChannelPriority << 6) & 0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8));    
    
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/**
  * @brief  Selects the condition for the system to enter low power mode.
  * @param  LowPowerMode: Specifies the new mode for the system to enter low power mode.
  *          This parameter can be one of the following values:
  *            @arg NVIC_LP_SEVONPEND: Low Power SEV on Pend.
  *            @arg NVIC_LP_SLEEPDEEP: Low Power DEEPSLEEP request.
  *            @arg NVIC_LP_SLEEPONEXIT: Low Power Sleep on Exit.
  * @param  NewState: new state of LP condition. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_NVIC_LP(LowPowerMode));
  
  assert_param(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState != DISABLE)
  {
    SCB->SCR |= LowPowerMode;
  }
  else
  {
    SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
  }
}

/**
  * @brief  Configures the SysTick clock source.
  * @param  SysTick_CLKSource: specifies the SysTick clock source.
  *          This parameter can be one of the following values:
  *            @arg SysTick_CLKSource_HCLK_Div8: AHB clock divided by 8 selected as SysTick clock source.
  *            @arg SysTick_CLKSource_HCLK: AHB clock selected as SysTick clock source.
  * @retval None
  */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* Check the parameters */
  assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
  
  if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_pwr.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Backup Domain Access
  *           + PVD configuration
  *           + WakeUp pins configuration
  *           + Low Power modes configuration
  *           + Flags management
  *
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR 
  * @brief PWR driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* ------------------ PWR registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_DS_MASK               ((uint32_t)0xFFFFFFFC)
#define CR_PLS_MASK              ((uint32_t)0xFFFFFF1F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions
  * @{
  */

/** @defgroup PWR_Group1 Backup Domain Access function 
 *  @brief   Backup Domain Access function
 *
@verbatim
  ==============================================================================
                   ##### Backup Domain Access function #####
  ==============================================================================

    [..] After reset, the Backup Domain Registers (RCC BDCR Register, RTC registers
         and RTC backup registers) are protected against possible stray write accesses.
    [..] To enable access to Backup domain use the PWR_BackupAccessCmd(ENABLE) function.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void PWR_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
  * @brief  Enables or disables access to the Backup domain registers.
  * @note   If the HSE divided by 32 is used as the RTC clock, the 
  *         Backup Domain Access should be kept enabled.
  * @param  NewState: new state of the access to the Backup domain registers.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Backup Domain Access */
    PWR->CR |= PWR_CR_DBP;
  }
  else
  {
    /* Disable the Backup Domain Access */
    PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_DBP);
  } 
}

/**
  * @}
  */

/** @defgroup PWR_Group2 PVD configuration functions
 *  @brief   PVD configuration functions 
 *
@verbatim
  ==============================================================================
                    ##### PVD configuration functions #####
  ==============================================================================
  [..]
  (+) The PVD is used to monitor the VDD power supply by comparing it to a threshold
      selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
  (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower than the 
      PVD threshold. This event is internally connected to the EXTI line16
      and can generate an interrupt if enabled through the EXTI registers.
  (+) The PVD is stopped in Standby mode.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @note   This function is not applicable for STM32F030 devices. 
  * @param  PWR_PVDLevel: specifies the PVD detection level
  *          This parameter can be one of the following values:
  *             @arg PWR_PVDLevel_0
  *             @arg PWR_PVDLevel_1
  *             @arg PWR_PVDLevel_2
  *             @arg PWR_PVDLevel_3
  *             @arg PWR_PVDLevel_4
  *             @arg PWR_PVDLevel_5
  *             @arg PWR_PVDLevel_6
  *             @arg PWR_PVDLevel_7
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each 
  *         detection level.
  * @retval None
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
  
  tmpreg = PWR->CR;
  
  /* Clear PLS[7:5] bits */
  tmpreg &= CR_PLS_MASK;
  
  /* Set PLS[7:5] bits according to PWR_PVDLevel value */
  tmpreg |= PWR_PVDLevel;
  
  /* Store the new value */
  PWR->CR = tmpreg;
}

/**
  * @brief  Enables or disables the Power Voltage Detector(PVD).
  * @note   This function is not applicable for STM32F030 devices.    
  * @param  NewState: new state of the PVD.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PVDCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the PVD */
    PWR->CR |= PWR_CR_PVDE;
  }
  else
  {
    /* Disable the PVD */
    PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_PVDE);
  } 
}

/**
  * @}
  */

/** @defgroup PWR_Group3 WakeUp pins configuration functions
 *  @brief   WakeUp pins configuration functions 
 *
@verbatim
  ==============================================================================
               ##### WakeUp pin configuration functions #####
  ==============================================================================

  (+) WakeUp pins are used to wakeup the system from Standby mode. These pins are 
      forced in input pull down configuration and are active on rising edges.
  (+) There are eight WakeUp pins: WakeUp Pin 1 on PA.00 and WakeUp Pin 2 on PC.13. 
      The following WakeUp pins are only applicable for STM32F072 dvices:
      WakeUp Pin 3 on PE.06, WakeUp Pin 4 on PA.02, WakeUp Pin 5 on PC.05, 
      WakeUp Pin 6 on PB.05, WakeUp Pin 7 on PB.15 and WakeUp Pin 8 on PF.02.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the WakeUp Pin functionality.
  * @param  PWR_WakeUpPin: specifies the WakeUpPin.
  *          This parameter can be one of the following values
  *             @arg PWR_WakeUpPin_1
  *             @arg PWR_WakeUpPin_2
  *             @arg PWR_WakeUpPin_3, only applicable for STM32F072 devices
  *             @arg PWR_WakeUpPin_4, only applicable for STM32F072 devices
  *             @arg PWR_WakeUpPin_5, only applicable for STM32F072 devices
  *             @arg PWR_WakeUpPin_6, only applicable for STM32F072 devices
  *             @arg PWR_WakeUpPin_7, only applicable for STM32F072 devices
  *             @arg PWR_WakeUpPin_8, only applicable for STM32F072 devices            
  * @param  NewState: new state of the WakeUp Pin functionality.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(PWR_WakeUpPin));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the EWUPx pin */
    PWR->CSR |= PWR_WakeUpPin;
  }
  else
  {
    /* Disable the EWUPx pin */
    PWR->CSR &= ~PWR_WakeUpPin;
  }
}

/**
  * @}
  */


/** @defgroup PWR_Group4 Low Power modes configuration functions
 *  @brief   Low Power modes configuration functions 
 *
@verbatim
  ==============================================================================
              ##### Low Power modes configuration functions #####
  ==============================================================================

    [..] The devices feature three low-power modes:
    (+) Sleep mode: Cortex-M0 core stopped, peripherals kept running.
    (+) Stop mode: all clocks are stopped, regulator running, regulator in low power mode
    (+) Standby mode: VCORE domain powered off

  *** Sleep mode *** 
  ==================
  [..] 
    (+) Entry:
        (++) The Sleep mode is entered by executing the WFE() or WFI() instructions.
    (+) Exit:
        (++) Any peripheral interrupt acknowledged by the nested vectored interrupt 
             controller (NVIC) can wake up the device from Sleep mode.

  *** Stop mode *** 
  =================
  [..] In Stop mode, all clocks in the VCORE domain are stopped, the PLL, the HSI,
       the HSI14 and the HSE RC oscillators are disabled. Internal SRAM and register 
       contents are preserved.
       The voltage regulator can be configured either in normal or low-power mode.

    (+) Entry:
        (++) The Stop mode is entered using the PWR_EnterSTOPMode(PWR_Regulator_LowPower,) 
             function with regulator in LowPower or with Regulator ON.
    (+) Exit:
        (++) Any EXTI Line (Internal or External) configured in Interrupt/Event mode
             or any internal IPs (I2C, UASRT or CEC) wakeup event.

  *** Standby mode *** 
  ====================
  [..] The Standby mode allows to achieve the lowest power consumption. It is based 
       on the Cortex-M0 deepsleep mode, with the voltage regulator disabled. 
       The VCORE domain is consequently powered off. The PLL, the HSI, the HSI14 
       oscillator and the HSE oscillator are also switched off. SRAM and register 
       contents are lost except for the Backup domain (RTC registers, RTC backup 
       registers and Standby circuitry).
   
  [..] The voltage regulator is OFF.

    (+) Entry:
        (++) The Standby mode is entered using the PWR_EnterSTANDBYMode() function.
    (+) Exit:
        (++) WKUP pin rising edge, RTC alarm (Alarm A and Alarm B), RTC wakeup,
             tamper event, time-stamp event, external reset in NRST pin, IWDG reset.

  *** Auto-wakeup (AWU) from low-power mode *** 
  =============================================
  [..] The MCU can be woken up from low-power mode by an RTC Alarm event, a tamper 
       event, a time-stamp event, or a comparator event, without depending on an 
       external interrupt (Auto-wakeup mode).

    (+) RTC auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to:
             (+++) Configure the EXTI Line 17 to be sensitive to rising edges (Interrupt 
                   or Event modes) using the EXTI_Init() function.
             (+++) Enable the RTC Alarm Interrupt using the RTC_ITConfig() function
             (+++) Configure the RTC to generate the RTC alarm using the RTC_SetAlarm() 
                   and RTC_AlarmCmd() functions.
        (++) To wake up from the Stop mode with an RTC Tamper or time stamp event, it 
             is necessary to:
             (+++) Configure the EXTI Line 19 to be sensitive to rising edges (Interrupt 
                   or Event modes) using the EXTI_Init() function.
             (+++) Enable the RTC Tamper or time stamp Interrupt using the RTC_ITConfig() 
                   function.
             (+++) Configure the RTC to detect the tamper or time stamp event using the
                   RTC_TimeStampConfig(), RTC_TamperTriggerConfig() and RTC_TamperCmd()
                   functions.

    (+) RTC auto-wakeup (AWU) from the Standby mode
        (++) To wake up from the Standby mode with an RTC alarm event, it is necessary to:
             (+++) Enable the RTC Alarm Interrupt using the RTC_ITConfig() function.
             (+++) Configure the RTC to generate the RTC alarm using the RTC_SetAlarm() 
                   and RTC_AlarmCmd() functions.
        (++) To wake up from the Standby mode with an RTC Tamper or time stamp event, it 
             is necessary to:
             (+++) Enable the RTC Tamper or time stamp Interrupt using the RTC_ITConfig() 
                   function.
             (+++) Configure the RTC to detect the tamper or time stamp event using the
                   RTC_TimeStampConfig(), RTC_TamperTriggerConfig() and RTC_TamperCmd()
                   functions.

    (+) Comparator auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an comparator 1 or comparator 2 wakeup
             event, it is necessary to:
             (+++) Configure the EXTI Line 21 for comparator 1 or EXTI Line 22 for comparator 2 
                   to be sensitive to to the selected edges (falling, rising or falling 
                   and rising) (Interrupt or Event modes) using the EXTI_Init() function.
             (+++) Configure the comparator to generate the event.

@endverbatim
  * @{
  */

/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *             @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *             @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));

  /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  
  /* Select SLEEP mode entry -------------------------------------------------*/
  if(PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE(); 
    __WFE();
  }
}

/**
  * @brief  Enters STOP mode.
  * @note   In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note   When exiting Stop mode by issuing an interrupt or a wakeup event, 
  *         the HSI RC oscillator is selected as system clock.
  * @note   When the voltage regulator operates in low power mode, an additional 
  *         startup delay is incurred when waking up from Stop mode. 
  *         By keeping the internal regulator ON during Stop mode, the consumption 
  *         is higher although the startup time is reduced.
  * @param  PWR_Regulator: specifies the regulator state in STOP mode.
  *         This parameter can be one of the following values:
  *             @arg PWR_Regulator_ON: STOP mode with regulator ON
  *             @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
  * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *             @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
  *             @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
                @arg PWR_STOPEntry_SLEEPONEXIT: enter STOP mode with SLEEPONEXIT instruction
  * @retval None
  */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(PWR_Regulator));
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
  
  /* Select the regulator state in STOP mode ---------------------------------*/
  tmpreg = PWR->CR;
  /* Clear PDDS and LPDSR bits */
  tmpreg &= CR_DS_MASK;
  
  /* Set LPDSR bit according to PWR_Regulator value */
  tmpreg |= PWR_Regulator;
  
  /* Store the new value */
  PWR->CR = tmpreg;
  
  /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  
  /* Select STOP mode entry --------------------------------------------------*/
  if(PWR_STOPEntry == PWR_STOPEntry_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk); 
  }
  else if (PWR_STOPEntry == PWR_STOPEntry_WFE)
  {
    /* Request Wait For Event */
    __WFE();
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);   
  }
  else
  {
    /* Set SLEEP on exit bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
  }
}

/**
  * @brief  Enters STANDBY mode.
  * @note   In Standby mode, all I/O pins are high impedance except for:
  *          - Reset pad (still available) 
  *          - RTC_AF1 pin (PC13) if configured for Wakeup pin 2 (WKUP2), tamper, 
  *             time-stamp, RTC Alarm out, or RTC clock calibration out.
  *          - WKUP pin 1 (PA0) if enabled.
  * @note The Wakeup flag (WUF) need to be cleared at application level before to call this function     
  * @param  None
  * @retval None
  */
void PWR_EnterSTANDBYMode(void)
{
  /* Select STANDBY mode */
  PWR->CR |= PWR_CR_PDDS;

  /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @}
  */

/** @defgroup PWR_Group5 Flags management functions
 *  @brief   Flags management functions 
 *
@verbatim
  ==============================================================================
                       ##### Flags management functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified PWR flag is set or not.
  * @param  PWR_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *             @arg PWR_FLAG_WU: Wake Up flag. This flag indicates that a wakeup
  *                  event was received from the WKUP pin or from the RTC alarm 
  *                  (Alarm A or Alarm B), RTC Tamper event or RTC TimeStamp event.
  *             @arg PWR_FLAG_SB: StandBy flag. This flag indicates that the 
  *                  system was resumed from StandBy mode.
  *             @arg PWR_FLAG_PVDO: PVD Output. This flag is valid only if PVD 
  *                  is enabled by the PWR_PVDCmd() function.
  *             @arg PWR_FLAG_VREFINTRDY: Internal Voltage Reference Ready flag. 
  *                  This flag indicates the state of the internal voltage 
  *                  reference, VREFINT.
  * @retval The new state of PWR_FLAG (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

  if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clears the PWR's pending flags.
  * @param  PWR_FLAG: specifies the flag to clear.
  *          This parameter can be one of the following values:
  *             @arg PWR_FLAG_WU: Wake Up flag
  *             @arg PWR_FLAG_SB: StandBy flag
  * @retval None
  */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
  /* Check the parameters */
  assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

  PWR->CR |=  PWR_FLAG << 2;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_rcc.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Reset and clock control (RCC) peripheral:
  *           + Internal/external clocks, PLL, CSS and MCO configuration
  *           + System, AHB and APB busses clocks configuration
  *           + Peripheral clocks configuration
  *           + Interrupts and flags management
  *
 @verbatim

 ===============================================================================
                        ##### RCC specific features #####
 ===============================================================================
    [..] After reset the device is running from HSI (8 MHz) with Flash 0 WS, 
         all peripherals are off except internal SRAM, Flash and SWD.
         (#) There is no prescaler on High speed (AHB) and Low speed (APB) busses;
             all peripherals mapped on these busses are running at HSI speed.
         (#) The clock for all peripherals is switched off, except the SRAM and FLASH.
         (#) All GPIOs are in input floating state, except the SWD pins which
             are assigned to be used for debug purpose.
    [..] Once the device started from reset, the user application has to:
         (#) Configure the clock source to be used to drive the System clock
             (if the application needs higher frequency/performance)
         (#) Configure the System clock frequency and Flash settings
         (#) Configure the AHB and APB busses prescalers
         (#) Enable the clock for the peripheral(s) to be used
         (#) Configure the clock source(s) for peripherals which clocks are not
             derived from the System clock (ADC, CEC, I2C, USART, RTC and IWDG)

 @endverbatim
  
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC 
  * @brief RCC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* ---------------------- RCC registers mask -------------------------------- */
/* RCC Flag Mask */
#define FLAG_MASK_RCC                 ((uint8_t)0x1F)

/* CR register byte 2 (Bits[23:16]) base address */
#define CR_BYTE2_ADDRESS          ((uint32_t)0x40021002)

/* CFGR register byte 3 (Bits[31:23]) base address */
#define CFGR_BYTE3_ADDRESS        ((uint32_t)0x40021007)

/* CIR register byte 1 (Bits[15:8]) base address */
#define CIR_BYTE1_ADDRESS         ((uint32_t)0x40021009)

/* CIR register byte 2 (Bits[23:16]) base address */
#define CIR_BYTE2_ADDRESS         ((uint32_t)0x4002100A)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RCC_Private_Functions
  * @{
  */

/** @defgroup RCC_Group1 Internal and external clocks, PLL, CSS and MCO configuration functions
 *  @brief   Internal and external clocks, PLL, CSS and MCO configuration functions 
 *
@verbatim
 ===============================================================================
 ##### Internal-external clocks, PLL, CSS and MCO configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to configure the internal/external clocks,
         PLL, CSS and MCO.
         (#) HSI (high-speed internal), 8 MHz factory-trimmed RC used directly 
             or through the PLL as System clock source.
             The HSI clock can be used also to clock the USART, I2C and CEC peripherals.
         (#) HSI14 (high-speed internal for ADC), 14 MHz factory-trimmed RC used to clock
             the ADC peripheral.
         (#) LSI (low-speed internal), 40 KHz low consumption RC used as IWDG and/or RTC
             clock source.
         (#) HSE (high-speed external), 4 to 32 MHz crystal oscillator used directly or
             through the PLL as System clock source. Can be used also as RTC clock source.
         (#) LSE (low-speed external), 32 KHz oscillator used as RTC clock source. 
             LSE can be used also to clock the USART and CEC peripherals.   
         (#) PLL (clocked by HSI or HSE), for System clock.
         (#) CSS (Clock security system), once enabled and if a HSE clock failure occurs 
             (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled. 
             The interrupt is linked to the Cortex-M0 NMI (Non-Maskable Interrupt) 
             exception vector.   
         (#) MCO (microcontroller clock output), used to output SYSCLK, HSI, HSI14, LSI,
             HSE, LSE or PLL (divided by 2) clock on PA8 pin.

@endverbatim
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  * @note      HSI ON and used as system clock source 
  * @note      HSI14, HSE and PLL OFF
  * @note      AHB, APB prescaler set to 1.
  * @note      CSS and MCO OFF
  * @note      All interrupts disabled
  * @note   However, this function doesn't modify the configuration of the
  * @note      Peripheral clocks
  * @note      LSI, LSE and RTC clocks
  * @param  None
  * @retval None
  */
void RCC_DeInit(void)
{
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

#if defined (STM32F051)
  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0] and MCOSEL[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FFB80C;
#else
  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits */
  RCC->CFGR &= (uint32_t)0x08FFB80C;
#endif /* STM32F051 */
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  RCC->CFGR &= (uint32_t)0xFFC0FFFF;

  /* Reset PREDIV1[3:0] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;

  /* Reset USARTSW[1:0], I2CSW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFF0FEAC;
  
  /* Reset HSI14 bit */
  RCC->CR2 &= (uint32_t)0xFFFFFFFE;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;
}

/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   This function resets the CSSON bit, so if the Clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  RCC_HSE: specifies the new state of the HSE.
  *          This parameter can be one of the following values:
  *            @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg RCC_HSE_ON: turn ON the HSE oscillator
  *            @arg RCC_HSE_Bypass: HSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_HSEConfig(uint8_t RCC_HSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSE(RCC_HSE));

  /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
  *(__IO uint8_t *) CR_BYTE2_ADDRESS = RCC_HSE_OFF;

  /* Set the new HSE configuration -------------------------------------------*/
  *(__IO uint8_t *) CR_BYTE2_ADDRESS = RCC_HSE;

}

/**
  * @brief  Waits for HSE start-up.
  * @note   This function waits on HSERDY flag to be set and return SUCCESS if 
  *         this flag is set, otherwise returns ERROR if the timeout is reached 
  *         and this flag is not set. The timeout value is defined by the constant
  *         HSE_STARTUP_TIMEOUT in stm32f0xx.h file. You can tailor it depending
  *         on the HSE crystal used in your application.
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: HSE oscillator is stable and ready to use
  *          - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;
  
  /* Wait till HSE is ready and if timeout is reached exit */
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;  
  } while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));
  
  if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
  return (status);
}

/**
  * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  *         Refer to the Application Note AN4067 for more details on how to  
  *         calibrate the HSI.
  * @param  HSICalibrationValue: specifies the HSI calibration trimming value.
  *          This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HSI_CALIBRATION_VALUE(HSICalibrationValue));
  
  tmpreg = RCC->CR;
  
  /* Clear HSITRIM[4:0] bits */
  tmpreg &= ~RCC_CR_HSITRIM;
  
  /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
  tmpreg |= (uint32_t)HSICalibrationValue << 3;

  /* Store the new value */
  RCC->CR = tmpreg;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note   After enabling the HSI, the application software should wait on 
  *         HSIRDY flag to be set indicating that HSI clock is stable and can
  *         be used to clock the PLL and/or system clock.
  * @note   HSI can not be stopped if it is used directly or through the PLL
  *         as system clock. In this case, you have to select another source 
  *         of the system clock then stop the HSI.
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR |= RCC_CR_HSION;
  }
  else
  {
    RCC->CR &= ~RCC_CR_HSION;
  }
}

/**
  * @brief  Adjusts the Internal High Speed oscillator for ADC (HSI14) 
  *         calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  *         Refer to the Application Note AN4067  for more details on how to  
  *         calibrate the HSI14.
  * @param  HSI14CalibrationValue: specifies the HSI14 calibration trimming value.
  *          This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_AdjustHSI14CalibrationValue(uint8_t HSI14CalibrationValue)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HSI14_CALIBRATION_VALUE(HSI14CalibrationValue));
  
  tmpreg = RCC->CR2;
  
  /* Clear HSI14TRIM[4:0] bits */
  tmpreg &= ~RCC_CR2_HSI14TRIM;
  
  /* Set the HSITRIM14[4:0] bits according to HSI14CalibrationValue value */
  tmpreg |= (uint32_t)HSI14CalibrationValue << 3;

  /* Store the new value */
  RCC->CR2 = tmpreg;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator for ADC (HSI14).
  * @note   After enabling the HSI14, the application software should wait on 
  *         HSIRDY flag to be set indicating that HSI clock is stable and can
  *         be used to clock the ADC.
  * @note   The HSI14 is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI14.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI14 is stopped, HSI14RDY flag goes low after 6 HSI14 oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSI14Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR2 |= RCC_CR2_HSI14ON;
  }
  else
  {
    RCC->CR2 &= ~RCC_CR2_HSI14ON;
  }
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator request from ADC.
  * @param  NewState: new state of the HSI14 ADC request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSI14ADCRequestCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR2 &= ~RCC_CR2_HSI14DIS;
  }
  else
  {
    RCC->CR2 |= RCC_CR2_HSI14DIS;
  }
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @note   As the LSE is in the Backup domain and write access is denied to this
  *         domain after reset, you have to enable write access using 
  *         PWR_BackupAccessCmd(ENABLE) function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_Bypass), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  RCC_LSE: specifies the new state of the LSE.
  *          This parameter can be one of the following values:
  *            @arg RCC_LSE_OFF: turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg RCC_LSE_ON: turn ON the LSE oscillator
  *            @arg RCC_LSE_Bypass: LSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_LSEConfig(uint32_t RCC_LSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE(RCC_LSE));

  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* Reset LSEON bit */
  RCC->BDCR &= ~(RCC_BDCR_LSEON);

  /* Reset LSEBYP bit */
  RCC->BDCR &= ~(RCC_BDCR_LSEBYP);

  /* Configure LSE */
  RCC->BDCR |= RCC_LSE;
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE) drive capability.
  * @param  RCC_LSEDrive: specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg RCC_LSEDrive_Low: LSE oscillator low drive capability.
  *            @arg RCC_LSEDrive_MediumLow: LSE oscillator medium low drive capability.
  *            @arg RCC_LSEDrive_MediumHigh: LSE oscillator medium high drive capability.
  *            @arg RCC_LSEDrive_High: LSE oscillator high drive capability.
  * @retval None
  */
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE_DRIVE(RCC_LSEDrive));
  
  /* Clear LSEDRV[1:0] bits */
  RCC->BDCR &= ~(RCC_BDCR_LSEDRV);

  /* Set the LSE Drive */
  RCC->BDCR |= RCC_LSEDrive;
}

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on 
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @param  NewState: new state of the LSI.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_LSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CSR |= RCC_CSR_LSION;
  }
  else
  {
    RCC->CSR &= ~RCC_CSR_LSION;
  }
}

/**
  * @brief  Configures the PLL clock source and multiplication factor.
  * @note   This function must be used only when the PLL is disabled.
  *
  * @param  RCC_PLLSource: specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLLSource_HSI_Div2: HSI oscillator clock selected as PLL clock source
  *            @arg RCC_PLLSource_PREDIV1: PREDIV1 clock selected as PLL clock entry
  *            @arg RCC_PLLSource_HSI48 HSI48 oscillator clock selected as PLL clock source, applicable only for STM32F072 devices
  *            @arg RCC_PLLSource_HSI: HSI clock selected as PLL clock entry, applicable only for STM32F072 devices
  * @note   The minimum input clock frequency for PLL is 2 MHz (when using HSE as
  *         PLL source).
  *
  * @param  RCC_PLLMul: specifies the PLL multiplication factor, which drive the PLLVCO clock
  *          This parameter can be RCC_PLLMul_x where x:[2,16] 
  *
  * @retval None
  */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  /* Check the parameters */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));

  /* Clear PLL Source [16] and Multiplier [21:18] bits */
  RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC);

  /* Set the PLL Source and Multiplier */
  RCC->CFGR |= (uint32_t)(RCC_PLLSource | RCC_PLLMul);
}

/**
  * @brief  Enables or disables the PLL.
  * @note   After enabling the PLL, the application software should wait on 
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The PLL can not be disabled if it is used as system clock source
  * @note   The PLL is disabled by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the PLL.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLLCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR |= RCC_CR_PLLON;
  }
  else
  {
    RCC->CR &= ~RCC_CR_PLLON;
  }
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator for USB (HSI48).
  *         This function is only applicable for STM32F072 devices.  
  * @note   After enabling the HSI48, the application software should wait on 
  *         HSI48RDY flag to be set indicating that HSI48 clock is stable and can
  *         be used to clock the USB.
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI48.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSI48Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR2 |= RCC_CR2_HSI48ON;
  }
  else
  {
    RCC->CR2 &= ~RCC_CR2_HSI48ON;
  }
}

/**
  * @brief  Configures the PREDIV1 division factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PREDIV1_Div: specifies the PREDIV1 clock division factor.
  *          This parameter can be RCC_PREDIV1_Divx where x:[1,16]
  * @retval None
  */
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Div)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_PREDIV1(RCC_PREDIV1_Div));

  tmpreg = RCC->CFGR2;
  /* Clear PREDIV1[3:0] bits */
  tmpreg &= ~(RCC_CFGR2_PREDIV1);
  /* Set the PREDIV1 division factor */
  tmpreg |= RCC_PREDIV1_Div;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}

/**
  * @brief  Enables or disables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to 
  *         the Cortex-M0 NMI (Non-Maskable Interrupt) exception vector.
  * @param  NewState: new state of the Clock Security System.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->CR |= RCC_CR_CSSON;
  }
  else
  {
    RCC->CR &= ~RCC_CR_CSSON;
  }
}

#ifdef STM32F051
/**
  * @brief  Selects the clock source to output on MCO pin (PA8).
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOSource: specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOSource_NoClock: No clock selected.
  *            @arg RCC_MCOSource_HSI14: HSI14 oscillator clock selected.
  *            @arg RCC_MCOSource_LSI: LSI oscillator clock selected.
  *            @arg RCC_MCOSource_LSE: LSE oscillator clock selected.
  *            @arg RCC_MCOSource_SYSCLK: System clock selected.
  *            @arg RCC_MCOSource_HSI: HSI oscillator clock selected.
  *            @arg RCC_MCOSource_HSE: HSE oscillator clock selected.
  *            @arg RCC_MCOSource_PLLCLK_Div2: PLL clock divided by 2 selected.
  * @retval None
  */
void RCC_MCOConfig(uint8_t RCC_MCOSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));

  /* Select MCO clock source and prescaler */
  *(__IO uint8_t *) CFGR_BYTE3_ADDRESS =  RCC_MCOSource;
}
#else

/**
  * @brief  Selects the clock source to output on MCO pin (PA8) and the corresponding
  *         prescsaler.
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOSource: specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOSource_NoClock: No clock selected.
  *            @arg RCC_MCOSource_HSI14: HSI14 oscillator clock selected.
  *            @arg RCC_MCOSource_LSI: LSI oscillator clock selected.
  *            @arg RCC_MCOSource_LSE: LSE oscillator clock selected.
  *            @arg RCC_MCOSource_SYSCLK: System clock selected.
  *            @arg RCC_MCOSource_HSI: HSI oscillator clock selected.
  *            @arg RCC_MCOSource_HSE: HSE oscillator clock selected.
  *            @arg RCC_MCOSource_PLLCLK_Div2: PLL clock divided by 2 selected.
  *            @arg RCC_MCOSource_PLLCLK: PLL clock selected.
  *            @arg RCC_MCOSource_HSI48: HSI48 clock selected.
  * @param  RCC_MCOPrescaler: specifies the prescaler on MCO pin.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOPrescaler_1: MCO clock is divided by 1.
  *            @arg RCC_MCOPrescaler_2: MCO clock is divided by 2.
  *            @arg RCC_MCOPrescaler_4: MCO clock is divided by 4.
  *            @arg RCC_MCOPrescaler_8: MCO clock is divided by 8.
  *            @arg RCC_MCOPrescaler_16: MCO clock is divided by 16.
  *            @arg RCC_MCOPrescaler_32: MCO clock is divided by 32.
  *            @arg RCC_MCOPrescaler_64: MCO clock is divided by 64.
  *            @arg RCC_MCOPrescaler_128: MCO clock is divided by 128.    
  * @retval None
  */
void RCC_MCOConfig(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));
  assert_param(IS_RCC_MCO_PRESCALER(RCC_MCOPrescaler));
    
  /* Get CFGR value */  
  tmpreg = RCC->CFGR;
  /* Clear MCOPRE[2:0] bits */
  tmpreg &= ~(RCC_CFGR_MCO_PRE | RCC_CFGR_MCO | RCC_CFGR_PLLNODIV);
  /* Set the RCC_MCOSource and RCC_MCOPrescaler */
  tmpreg |= (RCC_MCOPrescaler | ((uint32_t)RCC_MCOSource<<24));
  /* Store the new value */
  RCC->CFGR = tmpreg;
}
#endif /* STM32F072 */

/**
  * @}
  */

/** @defgroup RCC_Group2 System AHB and APB busses clocks configuration functions
 *  @brief   System, AHB and APB busses clocks configuration functions
 *
@verbatim
 ===============================================================================
     ##### System, AHB and APB busses clocks configuration functions #####
 ===============================================================================

    [..] This section provide functions allowing to configure the System, AHB and 
         APB busses clocks.
         (#) Several clock sources can be used to drive the System clock (SYSCLK): HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System clock through configurable prescaler
             and used to clock the CPU, memory and peripherals mapped on AHB bus (DMA and GPIO).
             and APB (PCLK) clocks are derived from AHB clock through 
             configurable prescalers and used to clock the peripherals mapped on these busses.
             You can use "RCC_GetClocksFreq()" function to retrieve the frequencies of these clocks.

         -@- All the peripheral clocks are derived from the System clock (SYSCLK) except:
             (+@) The ADC clock which is derived from HSI14 or APB (APB divided by a
                  programmable prescaler: 2 or 4).
             (+@) The CEC clock which is derived from LSE or HSI divided by 244.
             (+@) The I2C clock which is derived from HSI or system clock (SYSCLK).
             (+@) The USART clock which is derived from HSI, system clock (SYSCLK), APB or LSE.
             (+@) The RTC/LCD clock which is derived from the LSE, LSI or 2 MHz HSE_RTC (HSE
                  divided by a programmable prescaler).
                  The System clock (SYSCLK) frequency must be higher or equal to the RTC/LCD
                  clock frequency.
             (+@) IWDG clock which is always the LSI clock.
       
         (#) The maximum frequency of the SYSCLK, HCLK and PCLK is 48 MHz.
             Depending on the maximum frequency, the FLASH wait states (WS) should be 
             adapted accordingly:
        +--------------------------------------------- +
        |  Wait states  |   HCLK clock frequency (MHz) |
        |---------------|------------------------------|
        |0WS(1CPU cycle)|       0 < HCLK <= 24         |
        |---------------|------------------------------|
        |1WS(2CPU cycle)|       24 < HCLK <= 48        |
        +----------------------------------------------+

         (#) After reset, the System clock source is the HSI (8 MHz) with 0 WS and 
             prefetch is disabled.
  
    [..] It is recommended to use the following software sequences to tune the number
         of wait states needed to access the Flash memory with the CPU frequency (HCLK).
         (+) Increasing the CPU frequency
         (++) Program the Flash Prefetch buffer, using "FLASH_PrefetchBufferCmd(ENABLE)" 
              function
         (++) Check that Flash Prefetch buffer activation is taken into account by 
              reading FLASH_ACR using the FLASH_GetPrefetchBufferStatus() function
         (++) Program Flash WS to 1, using "FLASH_SetLatency(FLASH_Latency_1)" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading 
              the clock source status, using "RCC_GetSYSCLKSource()" function 
         (+) Decreasing the CPU frequency
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading 
              the clock source status, using "RCC_GetSYSCLKSource()" function
         (++) Program the new number of WS, using "FLASH_SetLatency()" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Disable the Flash Prefetch buffer using "FLASH_PrefetchBufferCmd(DISABLE)" 
              function
         (++) Check that Flash Prefetch buffer deactivation is taken into account by reading FLASH_ACR
              using the FLASH_GetPrefetchBufferStatus() function.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the system clock (SYSCLK).
  * @note   The HSI is used (enabled by hardware) as system clock source after
  *         startup from Reset, wake-up from STOP and STANDBY mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked). 
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source will be ready. 
  *         You can use RCC_GetSYSCLKSource() function to know which clock is
  *         currently used as system clock source.  
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock source 
  *          This parameter can be one of the following values:
  *            @arg RCC_SYSCLKSource_HSI:    HSI selected as system clock source
  *            @arg RCC_SYSCLKSource_HSE:    HSE selected as system clock source
  *            @arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
  *            @arg RCC_SYSCLKSource_HSI48:  HSI48 selected as system clock source, applicable only for STM32F072 devices  
  * @retval None
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
  
  tmpreg = RCC->CFGR;
  
  /* Clear SW[1:0] bits */
  tmpreg &= ~RCC_CFGR_SW;
  
  /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
  tmpreg |= RCC_SYSCLKSource;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval The clock source used as system clock. The returned value can be one 
  *         of the following values:
  *           - 0x00: HSI used as system clock
  *           - 0x04: HSE used as system clock  
  *           - 0x08: PLL used as system clock
  *           - 0x0C: HSI48 used as system clock, applicable only for STM32F072 devices  
  */
uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR & RCC_CFGR_SWS));
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  RCC_SYSCLK: defines the AHB clock divider. This clock is derived from 
  *         the system clock (SYSCLK).
  *          This parameter can be one of the following values:
  *            @arg RCC_SYSCLK_Div1:   AHB clock = SYSCLK
  *            @arg RCC_SYSCLK_Div2:   AHB clock = SYSCLK/2
  *            @arg RCC_SYSCLK_Div4:   AHB clock = SYSCLK/4
  *            @arg RCC_SYSCLK_Div8:   AHB clock = SYSCLK/8
  *            @arg RCC_SYSCLK_Div16:  AHB clock = SYSCLK/16
  *            @arg RCC_SYSCLK_Div64:  AHB clock = SYSCLK/64
  *            @arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *            @arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *            @arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @retval None
  */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HCLK(RCC_SYSCLK));
  
  tmpreg = RCC->CFGR;
  
  /* Clear HPRE[3:0] bits */
  tmpreg &= ~RCC_CFGR_HPRE;
  
  /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
  tmpreg |= RCC_SYSCLK;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the APB clock (PCLK).
  * @param  RCC_HCLK: defines the APB clock divider. This clock is derived from 
  *         the AHB clock (HCLK).
  *          This parameter can be one of the following values:
  *            @arg RCC_HCLK_Div1: APB clock = HCLK
  *            @arg RCC_HCLK_Div2: APB clock = HCLK/2
  *            @arg RCC_HCLK_Div4: APB clock = HCLK/4
  *            @arg RCC_HCLK_Div8: APB clock = HCLK/8
  *            @arg RCC_HCLK_Div16: APB clock = HCLK/16
  * @retval None
  */
void RCC_PCLKConfig(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  
  tmpreg = RCC->CFGR;
  
  /* Clear PPRE[2:0] bits */
  tmpreg &= ~RCC_CFGR_PPRE;
  
  /* Set PPRE[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the ADC clock (ADCCLK).
  * @note   This function is obsolete.
  *         For proper ADC clock selection, refer to ADC_ClockModeConfig() in the ADC driver
  * @param  RCC_ADCCLK: defines the ADC clock source. This clock is derived 
  *         from the HSI14 or APB clock (PCLK).
  *          This parameter can be one of the following values:
  *             @arg RCC_ADCCLK_HSI14: ADC clock = HSI14 (14MHz)
  *             @arg RCC_ADCCLK_PCLK_Div2: ADC clock = PCLK/2
  *             @arg RCC_ADCCLK_PCLK_Div4: ADC clock = PCLK/4  
  * @retval None
  */
void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_ADCCLK(RCC_ADCCLK));

  /* Clear ADCPRE bit */
  RCC->CFGR &= ~RCC_CFGR_ADCPRE;
  /* Set ADCPRE bits according to RCC_PCLK value */
  RCC->CFGR |= RCC_ADCCLK & 0xFFFF;

  /* Clear ADCSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_ADCSW; 
  /* Set ADCSW bits according to RCC_ADCCLK value */
  RCC->CFGR3 |= RCC_ADCCLK >> 16;  
}

/**
  * @brief  Configures the CEC clock (CECCLK).
  * @param  RCC_CECCLK: defines the CEC clock source. This clock is derived 
  *         from the HSI or LSE clock.
  *          This parameter can be one of the following values:
  *             @arg RCC_CECCLK_HSI_Div244: CEC clock = HSI/244 (32768Hz)
  *             @arg RCC_CECCLK_LSE: CEC clock = LSE
  * @retval None
  */
void RCC_CECCLKConfig(uint32_t RCC_CECCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_CECCLK(RCC_CECCLK));

  /* Clear CECSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_CECSW;
  /* Set CECSW bits according to RCC_CECCLK value */
  RCC->CFGR3 |= RCC_CECCLK;
}

/**
  * @brief  Configures the I2C1 clock (I2C1CLK).
  * @param  RCC_I2CCLK: defines the I2C1 clock source. This clock is derived 
  *         from the HSI or System clock.
  *          This parameter can be one of the following values:
  *             @arg RCC_I2C1CLK_HSI: I2C1 clock = HSI
  *             @arg RCC_I2C1CLK_SYSCLK: I2C1 clock = System Clock
  * @retval None
  */
void RCC_I2CCLKConfig(uint32_t RCC_I2CCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_I2CCLK(RCC_I2CCLK));

  /* Clear I2CSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_I2C1SW;
  /* Set I2CSW bits according to RCC_I2CCLK value */
  RCC->CFGR3 |= RCC_I2CCLK;
}

/**
  * @brief  Configures the USART1 clock (USART1CLK).
  * @param  RCC_USARTCLK: defines the USART clock source. This clock is derived 
  *         from the HSI or System clock.
  *          This parameter can be one of the following values:
  *             @arg RCC_USART1CLK_PCLK: USART1 clock = APB Clock (PCLK)
  *             @arg RCC_USART1CLK_SYSCLK: USART1 clock = System Clock
  *             @arg RCC_USART1CLK_LSE: USART1 clock = LSE Clock
  *             @arg RCC_USART1CLK_HSI: USART1 clock = HSI Clock
  *             @arg RCC_USART2CLK_PCLK: USART2 clock = APB Clock (PCLK), applicable only for STM32F072 and STM32F091 devices
  *             @arg RCC_USART2CLK_SYSCLK: USART2 clock = System Clock, applicable only for STM32F072 and STM32F091 devices
  *             @arg RCC_USART2CLK_LSE: USART2 clock = LSE Clock, applicable only for STM32F072 and STM32F091 devices
  *             @arg RCC_USART2CLK_HSI: USART2 clock = HSI Clock, applicable only for STM32F072 and STM32F091 devices  
  *             @arg RCC_USART3CLK_PCLK: USART3 clock = APB Clock (PCLK), applicable only for STM32F091 devices
  *             @arg RCC_USART3CLK_SYSCLK: USART3 clock = System Clock, applicable only for STM32F091 devices
  *             @arg RCC_USART3CLK_LSE: USART3 clock = LSE Clock, applicable only for STM32F091 devices
  *             @arg RCC_USART3CLK_HSI: USART3 clock = HSI Clock, applicable only for STM32F091 devices   
  * @retval None
  */
void RCC_USARTCLKConfig(uint32_t RCC_USARTCLK)
{ 
  uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_USARTCLK(RCC_USARTCLK));

  /* Get USART index */
  tmp = (RCC_USARTCLK >> 28);

  /* Clear USARTSW[1:0] bit */
  if (tmp == (uint32_t)0x00000001)
  {
    /* Clear USART1SW[1:0] bit */  
    RCC->CFGR3 &= ~RCC_CFGR3_USART1SW;
  }
  else if (tmp == (uint32_t)0x00000002)
  {
    /* Clear USART2SW[1:0] bit */
    RCC->CFGR3 &= ~RCC_CFGR3_USART2SW;
  }
  else 
  {
    /* Clear USART3SW[1:0] bit */
    RCC->CFGR3 &= ~RCC_CFGR3_USART3SW;
  }

  /* Set USARTxSW bits according to RCC_USARTCLK value */
  RCC->CFGR3 |= RCC_USARTCLK;
}

/**
  * @brief  Configures the USB clock (USBCLK).
  *         This function is only applicable for STM32F072 devices.  
  * @param  RCC_USBCLK: defines the USB clock source. This clock is derived 
  *         from the HSI48 or system clock.
  *          This parameter can be one of the following values:
  *             @arg RCC_USBCLK_HSI48: USB clock = HSI48
  *             @arg RCC_USBCLK_PLLCLK: USB clock = PLL clock
  * @retval None
  */
void RCC_USBCLKConfig(uint32_t RCC_USBCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_USBCLK(RCC_USBCLK));

  /* Clear USBSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_USBSW;
  /* Set USBSW bits according to RCC_USBCLK value */
  RCC->CFGR3 |= RCC_USBCLK;
}

/**
  * @brief  Returns the frequencies of the System, AHB and APB busses clocks.
  * @note    The frequency returned by this function is not the real frequency
  *           in the chip. It is calculated based on the predefined constant and
  *           the source selected by RCC_SYSCLKConfig():
  *                                              
  * @note     If SYSCLK source is HSI, function returns constant HSI_VALUE(*)
  *                                              
  * @note     If SYSCLK source is HSE, function returns constant HSE_VALUE(**)
  *                          
  * @note     If SYSCLK source is PLL, function returns constant HSE_VALUE(**) 
  *             or HSI_VALUE(*) multiplied by the PLL factors.
  *               
  * @note     If SYSCLK source is HSI48, function returns constant HSI48_VALUE(***) 
  *             
  * @note     (*) HSI_VALUE is a constant defined in stm32f0xx.h file (default value
  *               8 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature, refer to RCC_AdjustHSICalibrationValue().   
  *    
  * @note     (**) HSE_VALUE is a constant defined in stm32f0xx.h file (default value
  *                8 MHz), user has to ensure that HSE_VALUE is same as the real
  *                frequency of the crystal used. Otherwise, this function may
  *                return wrong result.
  *
  * @note     (***) HSI48_VALUE is a constant defined in stm32f0xx.h file (default value
  *                 48 MHz) but the real value may vary depending on the variations
  *                 in voltage and temperature.
  *                                   
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.   
  *             
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold 
  *         the clocks frequencies. 
  *     
  * @note   This function can be used by the user application to compute the 
  *         baudrate for the communication peripherals or configure other parameters.
  * @note   Each time SYSCLK, HCLK and/or PCLK clock changes, this function
  *         must be called to update the structure's field. Otherwise, any
  *         configuration based on this function will be incorrect.
  *    
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0, presc = 0, pllclk = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        pllclk = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
        /* HSE oscillator clock selected as PREDIV1 clock entry */
        pllclk = (HSE_VALUE / prediv1factor) * pllmull; 
      }
      RCC_Clocks->SYSCLK_Frequency = pllclk;      
      break;
    case 0x0C:  /* HSI48 used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI48_VALUE;
      break;
    default: /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
  }
  /* Compute HCLK, PCLK clocks frequencies -----------------------------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & RCC_CFGR_HPRE;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp]; 
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

  /* Get PCLK prescaler */
  tmp = RCC->CFGR & RCC_CFGR_PPRE;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK clock frequency */
  RCC_Clocks->PCLK_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

  /* ADCCLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_ADCSW) != RCC_CFGR3_ADCSW)
  {
    /* ADC Clock is HSI14 Osc. */
    RCC_Clocks->ADCCLK_Frequency = HSI14_VALUE;
  }
  else
  {
    if((RCC->CFGR & RCC_CFGR_ADCPRE) != RCC_CFGR_ADCPRE)
    {
      /* ADC Clock is derived from PCLK/2 */
      RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK_Frequency >> 1;
    }
    else
    {
      /* ADC Clock is derived from PCLK/4 */
      RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK_Frequency >> 2;
    }
    
  }

  /* CECCLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_CECSW) != RCC_CFGR3_CECSW)
  {
    /* CEC Clock is HSI/244 */
    RCC_Clocks->CECCLK_Frequency = HSI_VALUE / 244;
  }
  else
  {
    /* CECC Clock is LSE Osc. */
    RCC_Clocks->CECCLK_Frequency = LSE_VALUE;
  }

  /* I2C1CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_I2C1SW) != RCC_CFGR3_I2C1SW)
  {
    /* I2C1 Clock is HSI Osc. */
    RCC_Clocks->I2C1CLK_Frequency = HSI_VALUE;
  }
  else
  {
    /* I2C1 Clock is System Clock */
    RCC_Clocks->I2C1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }

  /* USART1CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == 0x0)
  {
    /* USART1 Clock is PCLK */
    RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW_0)
  {
    /* USART1 Clock is System Clock */
    RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW_1)
  {
    /* USART1 Clock is LSE Osc. */
    RCC_Clocks->USART1CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW)
  {
    /* USART1 Clock is HSI Osc. */
    RCC_Clocks->USART1CLK_Frequency = HSI_VALUE;
  }
  
  /* USART2CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_USART2SW) == 0x0)
  {
    /* USART Clock is PCLK */
    RCC_Clocks->USART2CLK_Frequency = RCC_Clocks->PCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART2SW) == RCC_CFGR3_USART2SW_0)
  {
    /* USART Clock is System Clock */
    RCC_Clocks->USART2CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART2SW) == RCC_CFGR3_USART2SW_1)
  {
    /* USART Clock is LSE Osc. */
    RCC_Clocks->USART2CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART2SW) == RCC_CFGR3_USART2SW)
  {
    /* USART Clock is HSI Osc. */
    RCC_Clocks->USART2CLK_Frequency = HSI_VALUE;
  }
  
  /* USART3CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_USART3SW) == 0x0)
  {
    /* USART Clock is PCLK */
    RCC_Clocks->USART3CLK_Frequency = RCC_Clocks->PCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART3SW) == RCC_CFGR3_USART3SW_0)
  {
    /* USART Clock is System Clock */
    RCC_Clocks->USART3CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART3SW) == RCC_CFGR3_USART3SW_1)
  {
    /* USART Clock is LSE Osc. */
    RCC_Clocks->USART3CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART3SW) == RCC_CFGR3_USART3SW)
  {
    /* USART Clock is HSI Osc. */
    RCC_Clocks->USART3CLK_Frequency = HSI_VALUE;
  }
  
  /* USBCLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_USBSW) != RCC_CFGR3_USBSW)
  {
    /* USB Clock is HSI48 */
    RCC_Clocks->USBCLK_Frequency = HSI48_VALUE;
  }
  else
  {
    /* USB Clock is PLL clock */
    RCC_Clocks->USBCLK_Frequency = pllclk;
  }   
}

/**
  * @}
  */

/** @defgroup RCC_Group3 Peripheral clocks configuration functions
 *  @brief   Peripheral clocks configuration functions 
 *
@verbatim
 ===============================================================================
             #####Peripheral clocks configuration functions #####
 ===============================================================================  

    [..] This section provide functions allowing to configure the Peripheral clocks. 
         (#) The RTC clock which is derived from the LSE, LSI or  HSE_Div32 (HSE
             divided by 32).
         (#) After restart from Reset or wakeup from STANDBY, all peripherals are off
             except internal SRAM, Flash and SWD. Before to start using a peripheral you
             have to enable its interface clock. You can do this using RCC_AHBPeriphClockCmd(),
             RCC_APB2PeriphClockCmd() and RCC_APB1PeriphClockCmd() functions.
         (#) To reset the peripherals configuration (to the default state after device reset)
             you can use RCC_AHBPeriphResetCmd(), RCC_APB2PeriphResetCmd() and 
             RCC_APB1PeriphResetCmd() functions.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using PWR_BackupAccessCmd(ENABLE) function before to configure
  *         the RTC clock source (to be done once after reset).    
  * @note   Once the RTC clock is configured it can't be changed unless the RTC
  *         is reset using RCC_BackupResetCmd function, or by a Power On Reset (POR)
  *             
  * @param  RCC_RTCCLKSource: specifies the RTC clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_RTCCLKSource_LSE: LSE selected as RTC clock
  *            @arg RCC_RTCCLKSource_LSI: LSI selected as RTC clock
  *            @arg RCC_RTCCLKSource_HSE_Div32: HSE divided by 32 selected as RTC clock
  *       
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  *             
  * @note   The maximum input clock frequency for RTC is 2MHz (when using HSE as
  *         RTC clock source).
  *                          
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));
  
  /* Select the RTC clock source */
  RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @brief  Enables or disables the RTC clock.
  * @note   This function must be used only after the RTC clock source was selected
  *         using the RCC_RTCCLKConfig function.
  * @param  NewState: new state of the RTC clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->BDCR |= RCC_BDCR_RTCEN;
  }
  else
  {
    RCC->BDCR &= ~RCC_BDCR_RTCEN;
  }
}

/**
  * @brief  Forces or releases the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_BDCR register.
  * @param  NewState: new state of the Backup domain reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->BDCR |= RCC_BDCR_BDRST;
  }
  else
  {
    RCC->BDCR &= ~RCC_BDCR_BDRST;
  }
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.    
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_AHBPeriph_GPIOA: GPIOA clock
  *             @arg RCC_AHBPeriph_GPIOB: GPIOB clock
  *             @arg RCC_AHBPeriph_GPIOC: GPIOC clock
  *             @arg RCC_AHBPeriph_GPIOD: GPIOD clock
  *             @arg RCC_AHBPeriph_GPIOE: GPIOE clock, applicable only for STM32F072 devices  
  *             @arg RCC_AHBPeriph_GPIOF: GPIOF clock
  *             @arg RCC_AHBPeriph_TS:    TS clock
  *             @arg RCC_AHBPeriph_CRC:   CRC clock
  *             @arg RCC_AHBPeriph_FLITF: (has effect only when the Flash memory is in power down mode)  
  *             @arg RCC_AHBPeriph_SRAM:  SRAM clock
  *             @arg RCC_AHBPeriph_DMA1:  DMA1 clock
  *             @arg RCC_AHBPeriph_DMA2:  DMA2 clock  
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *             @arg RCC_APB2Periph_USART6: USART6 clock  
  *             @arg RCC_APB2Periph_USART7: USART7 clock
  *             @arg RCC_APB2Periph_USART8: USART8 clock   
  *             @arg RCC_APB2Periph_ADC1:   ADC1 clock
  *             @arg RCC_APB2Periph_TIM1:   TIM1 clock
  *             @arg RCC_APB2Periph_SPI1:   SPI1 clock
  *             @arg RCC_APB2Periph_USART1: USART1 clock   
  *             @arg RCC_APB2Periph_TIM15:  TIM15 clock
  *             @arg RCC_APB2Periph_TIM16:  TIM16 clock
  *             @arg RCC_APB2Periph_TIM17:  TIM17 clock
  *             @arg RCC_APB2Periph_DBGMCU: DBGMCU clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_APB1Periph_TIM2:   TIM2 clock, applicable only for STM32F051 and STM32F072 devices
  *           @arg RCC_APB1Periph_TIM3:   TIM3 clock
  *           @arg RCC_APB1Periph_TIM6:   TIM6 clock
  *           @arg RCC_APB1Periph_TIM7:   TIM7 clock, applicable only for STM32F072 devices   
  *           @arg RCC_APB1Periph_TIM14:  TIM14 clock
  *           @arg RCC_APB1Periph_WWDG:   WWDG clock
  *           @arg RCC_APB1Periph_SPI2:   SPI2 clock
  *           @arg RCC_APB1Periph_USART2: USART2 clock
  *           @arg RCC_APB1Periph_USART3: USART3 clock, applicable only for STM32F072 and STM32F091 devices 
  *           @arg RCC_APB1Periph_USART4: USART4 clock, applicable only for STM32F072 and STM32F091 devices
  *           @arg RCC_APB1Periph_USART5: USART5 clock, applicable only for STM32F091 devices         
  *           @arg RCC_APB1Periph_I2C1:   I2C1 clock
  *           @arg RCC_APB1Periph_I2C2:   I2C2 clock
  *           @arg RCC_APB1Periph_USB:    USB clock, applicable only for STM32F042 and STM32F072 devices 
  *           @arg RCC_APB1Periph_CAN:    CAN clock, applicable only for STM32F042 and STM32F072 devices 
  *           @arg RCC_APB1Periph_CRS:    CRS clock , applicable only for STM32F042 and STM32F072 devices      
  *           @arg RCC_APB1Periph_PWR:    PWR clock
  *           @arg RCC_APB1Periph_DAC:    DAC clock, applicable only for STM32F051 and STM32F072 devices 
  *           @arg RCC_APB1Periph_CEC:    CEC clock, applicable only for STM32F051, STM32F042 and STM32F072 devices                               
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

/**
  * @brief  Forces or releases AHB peripheral reset.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_AHBPeriph_GPIOA: GPIOA clock
  *             @arg RCC_AHBPeriph_GPIOB: GPIOB clock
  *             @arg RCC_AHBPeriph_GPIOC: GPIOC clock
  *             @arg RCC_AHBPeriph_GPIOD: GPIOD clock
  *             @arg RCC_AHBPeriph_GPIOE: GPIOE clock, applicable only for STM32F072 devices  
  *             @arg RCC_AHBPeriph_GPIOF: GPIOF clock
  *             @arg RCC_AHBPeriph_TS:    TS clock
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_RST_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBRSTR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBRSTR &= ~RCC_AHBPeriph;
  }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *             @arg RCC_APB2Periph_USART6: USART6 clock  
  *             @arg RCC_APB2Periph_USART7: USART7 clock
  *             @arg RCC_APB2Periph_USART8: USART8 clock   
  *             @arg RCC_APB2Periph_ADC1:   ADC1 clock
  *             @arg RCC_APB2Periph_TIM1:   TIM1 clock
  *             @arg RCC_APB2Periph_SPI1:   SPI1 clock
  *             @arg RCC_APB2Periph_USART1: USART1 clock
  *             @arg RCC_APB2Periph_TIM15:  TIM15 clock
  *             @arg RCC_APB2Periph_TIM16:  TIM16 clock
  *             @arg RCC_APB2Periph_TIM17:  TIM17 clock
  *             @arg RCC_APB2Periph_DBGMCU: DBGMCU clock
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_APB1Periph_TIM2:   TIM2 clock, applicable only for STM32F051 and STM32F072 devices
  *           @arg RCC_APB1Periph_TIM3:   TIM3 clock
  *           @arg RCC_APB1Periph_TIM6:   TIM6 clock
  *           @arg RCC_APB1Periph_TIM7:   TIM7 clock, applicable only for STM32F072 devices   
  *           @arg RCC_APB1Periph_TIM14:  TIM14 clock
  *           @arg RCC_APB1Periph_WWDG:   WWDG clock
  *           @arg RCC_APB1Periph_SPI2:   SPI2 clock
  *           @arg RCC_APB1Periph_USART2: USART2 clock
  *           @arg RCC_APB1Periph_USART3: USART3 clock, applicable only for STM32F072 and STM32F091 devices 
  *           @arg RCC_APB1Periph_USART4: USART4 clock, applicable only for STM32F072 and STM32F091 devices
  *           @arg RCC_APB1Periph_USART5: USART5 clock, applicable only for STM32F091 devices         
  *           @arg RCC_APB1Periph_I2C1:   I2C1 clock
  *           @arg RCC_APB1Periph_I2C2:   I2C2 clock
  *           @arg RCC_APB1Periph_USB:    USB clock, applicable only for STM32F042 and STM32F072 devices 
  *           @arg RCC_APB1Periph_CAN:    CAN clock, applicable only for STM32F042 and STM32F072 devices 
  *           @arg RCC_APB1Periph_CRS:    CRS clock , applicable only for STM32F042 and STM32F072 devices      
  *           @arg RCC_APB1Periph_PWR:    PWR clock
  *           @arg RCC_APB1Periph_DAC:    DAC clock, applicable only for STM32F051 and STM32F072 devices 
  *           @arg RCC_APB1Periph_CEC:    CEC clock, applicable only for STM32F051, STM32F042 and STM32F072 devices    
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
  * @}
  */

/** @defgroup RCC_Group4 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified RCC interrupts.
  * @note   The CSS interrupt doesn't have an enable bit; once the CSS is enabled
  *         and if the HSE clock fails, the CSS interrupt occurs and an NMI is
  *         automatically generated. The NMI will be executed indefinitely, and 
  *         since NMI has higher priority than any other IRQ (and main program)
  *         the application will be stacked in the NMI ISR unless the CSS interrupt
  *         pending bit is cleared.
  * @param  RCC_IT: specifies the RCC interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *              @arg RCC_IT_LSIRDY: LSI ready interrupt
  *              @arg RCC_IT_LSERDY: LSE ready interrupt
  *              @arg RCC_IT_HSIRDY: HSI ready interrupt
  *              @arg RCC_IT_HSERDY: HSE ready interrupt
  *              @arg RCC_IT_PLLRDY: PLL ready interrupt
  *              @arg RCC_IT_HSI14RDY: HSI14 ready interrupt
  *              @arg RCC_IT_HSI48RDY: HSI48 ready interrupt, applicable only for STM32F072 devices  
  * @param  NewState: new state of the specified RCC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_IT(RCC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Perform Byte access to RCC_CIR[13:8] bits to enable the selected interrupts */
    *(__IO uint8_t *) CIR_BYTE1_ADDRESS |= RCC_IT;
  }
  else
  {
    /* Perform Byte access to RCC_CIR[13:8] bits to disable the selected interrupts */
    *(__IO uint8_t *) CIR_BYTE1_ADDRESS &= (uint8_t)~RCC_IT;
  }
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *             @arg RCC_FLAG_HSIRDY: HSI oscillator clock ready  
  *             @arg RCC_FLAG_HSERDY: HSE oscillator clock ready
  *             @arg RCC_FLAG_PLLRDY: PLL clock ready
  *             @arg RCC_FLAG_LSERDY: LSE oscillator clock ready
  *             @arg RCC_FLAG_LSIRDY: LSI oscillator clock ready
  *             @arg RCC_FLAG_OBLRST: Option Byte Loader (OBL) reset 
  *             @arg RCC_FLAG_PINRST: Pin reset
  *             @arg RCC_FLAG_V18PWRRSTF:  V1.8 power domain reset  
  *             @arg RCC_FLAG_PORRST: POR/PDR reset
  *             @arg RCC_FLAG_SFTRST: Software reset
  *             @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
  *             @arg RCC_FLAG_WWDGRST: Window Watchdog reset
  *             @arg RCC_FLAG_LPWRRST: Low Power reset
  *             @arg RCC_FLAG_HSI14RDY: HSI14 oscillator clock ready
  *             @arg RCC_FLAG_HSI48RDY: HSI48 oscillator clock ready, applicable only for STM32F072 devices    
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_FLAG(RCC_FLAG));

  /* Get the RCC register index */
  tmp = RCC_FLAG >> 5;

  if (tmp == 0)               /* The flag to check is in CR register */
  {
    statusreg = RCC->CR;
  }
  else if (tmp == 1)          /* The flag to check is in BDCR register */
  {
    statusreg = RCC->BDCR;
  }
  else if (tmp == 2)          /* The flag to check is in CSR register */
  {
    statusreg = RCC->CSR;
  }
  else                        /* The flag to check is in CR2 register */
  {
    statusreg = RCC->CR2;
  }    

  /* Get the flag position */
  tmp = RCC_FLAG & FLAG_MASK_RCC;

  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clears the RCC reset flags.
  *         The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_V18PWRRSTF,
  *         RCC_FLAG_PORRST, RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST,
  *         RCC_FLAG_LPWRRST.
  * @param  None
  * @retval None
  */
void RCC_ClearFlag(void)
{
  /* Set RMVF bit to clear the reset flags */
  RCC->CSR |= RCC_CSR_RMVF;
}

/**
  * @brief  Checks whether the specified RCC interrupt has occurred or not.
  * @param  RCC_IT: specifies the RCC interrupt source to check.
  *          This parameter can be one of the following values:
  *             @arg RCC_IT_LSIRDY: LSI ready interrupt
  *             @arg RCC_IT_LSERDY: LSE ready interrupt
  *             @arg RCC_IT_HSIRDY: HSI ready interrupt
  *             @arg RCC_IT_HSERDY: HSE ready interrupt
  *             @arg RCC_IT_PLLRDY: PLL ready interrupt
  *             @arg RCC_IT_HSI14RDY: HSI14 ready interrupt
  *             @arg RCC_IT_HSI48RDY: HSI48 ready interrupt, applicable only for STM32F072 devices    
  *             @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval The new state of RCC_IT (SET or RESET).
  */
ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_RCC_GET_IT(RCC_IT));
  
  /* Check the status of the specified RCC interrupt */
  if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the RCC_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the RCC's interrupt pending bits.
  * @param  RCC_IT: specifies the interrupt pending bit to clear.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_IT_LSIRDY: LSI ready interrupt
  *             @arg RCC_IT_LSERDY: LSE ready interrupt
  *             @arg RCC_IT_HSIRDY: HSI ready interrupt
  *             @arg RCC_IT_HSERDY: HSE ready interrupt
  *             @arg RCC_IT_PLLRDY: PLL ready interrupt
  *             @arg RCC_IT_HSI48RDY: HSI48 ready interrupt, applicable only for STM32F072 devices 
  *             @arg RCC_IT_HSI14RDY: HSI14 ready interrupt
  *             @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval None
  */
void RCC_ClearITPendingBit(uint8_t RCC_IT)
{
  /* Check the parameters */
  assert_param(IS_RCC_CLEAR_IT(RCC_IT));
  
  /* Perform Byte access to RCC_CIR[23:16] bits to clear the selected interrupt
     pending bits */
  *(__IO uint8_t *) CIR_BYTE2_ADDRESS = RCC_IT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_rtc.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Real-Time Clock (RTC) peripheral:
  *           + Initialization
  *           + Calendar (Time and Date) configuration
  *           + Alarms (Alarm A) configuration
  *           + Daylight Saving configuration
  *           + Output pin Configuration
  *           + Digital Calibration configuration  
  *           + TimeStamp configuration
  *           + Tampers configuration
  *           + Backup Data Registers configuration
  *           + Output Type Config configuration
  *           + Shift control synchronisation  
  *           + Interrupts and flags management
  *
 @verbatim
 ===============================================================================
                    ##### Backup Domain Operating Condition #####
 ===============================================================================
    [..] The real-time clock (RTC) and the RTC backup registers can be powered
         from the VBAT voltage when the main VDD supply is powered off.
         To retain the content of the RTC backup registers and supply the RTC 
         when VDD is turned off, VBAT pin can be connected to an optional
         standby voltage supplied by a battery or by another source.
  
    [..] To allow the RTC to operate even when the main digital supply (VDD) 
         is turned off, the VBAT pin powers the following blocks:
           (#) The RTC
           (#) The LSE oscillator
           (#) PC13 to PC15 I/Os I/Os (when available)
  
    [..] When the backup domain is supplied by VDD (analog switch connected 
         to VDD), the following functions are available:
           (#) PC14 and PC15 can be used as either GPIO or LSE pins
           (#) PC13 can be used as a GPIO or as the RTC_AF1 pin
  
    [..] When the backup domain is supplied by VBAT (analog switch connected 
         to VBAT because VDD is not present), the following functions are available:
           (#) PC14 and PC15 can be used as LSE pins only
           (#) PC13 can be used as the RTC_AF1 pin 
  
                     ##### Backup Domain Reset #####
 ===============================================================================
    [..] The backup domain reset sets all RTC registers and the RCC_BDCR 
         register to their reset values. 
         A backup domain reset is generated when one of the following events
         occurs:
           (#) Software reset, triggered by setting the BDRST bit in the 
               RCC Backup domain control register (RCC_BDCR). You can use the
               RCC_BackupResetCmd().
           (#) VDD or VBAT power on, if both supplies have previously been
               powered off.
  
                     ##### Backup Domain Access #####
 ===============================================================================
    [..] After reset, the backup domain (RTC registers and RTC backup data 
         registers) is protected against possible unwanted write accesses. 
    [..] To enable access to the Backup Domain and RTC registers, proceed as follows:
         (#) Enable the Power Controller (PWR) APB1 interface clock using the
             RCC_APB1PeriphClockCmd() function.
         (#) Enable access to Backup domain using the PWR_BackupAccessCmd() function.
         (#) Select the RTC clock source using the RCC_RTCCLKConfig() function.
         (#) Enable RTC Clock using the RCC_RTCCLKCmd() function.
                                                                                           
  
                     ##### How to use this driver #####
 ===============================================================================
    [..]
        (+) Enable the backup domain access (see description in the section above)
        (+) Configure the RTC Prescaler (Asynchronous and Synchronous) and
            RTC hour format using the RTC_Init() function.
  
 ***Time and Date configuration ***
 ==================================
     [..]
        (+) To configure the RTC Calendar (Time and Date) use the RTC_SetTime()
            and RTC_SetDate() functions.
        (+) To read the RTC Calendar, use the RTC_GetTime() and RTC_GetDate()
            functions.
        (+) To read the RTC subsecond, use the RTC_GetSubSecond() function.
        (+) Use the RTC_DayLightSavingConfig() function to add or sub one
            hour to the RTC Calendar.
  
 ***Alarm configuration ***
 ========================== 
     [..]  
        (+) To configure the RTC Alarm use the RTC_SetAlarm() function.
        (+) Enable the selected RTC Alarm using the RTC_AlarmCmd() function  
        (+) To read the RTC Alarm, use the RTC_GetAlarm() function.
        (+) To read the RTC alarm SubSecond, use the RTC_GetAlarmSubSecond() function.

 ***RTC Wakeup configuration***
 ========================== 
    [..]  
        (+) Configure the RTC Wakeup Clock source use the RTC_WakeUpClockConfig()
            function.
        (+) Configure the RTC WakeUp Counter using the RTC_SetWakeUpCounter() 
            function  
        (+) Enable the RTC WakeUp using the RTC_WakeUpCmd() function  
        (+) To read the RTC WakeUp Counter register, use the RTC_GetWakeUpCounter() 
            function.
  
 ***Outputs configuration ***
 ============================
    [..] The RTC has 2 different outputs:
        (+) AFO_ALARM: this output is used to manage the RTC Alarm A.
            To output the selected RTC signal on RTC_AF1 pin, use the 
            RTC_OutputConfig() function.                
        (+) AFO_CALIB: this output is 512Hz signal or 1Hz .
            To output the RTC Clock on RTC_AF1 pin, use the RTC_CalibOutputCmd()
            function.                
  
 ***Original Digital Calibration configuration ***
 =================================    
    [..] Configure the RTC Original Digital Calibration Value and the corresponding
         calibration cycle period (32s,16s and 8s) using the RTC_SmoothCalibConfig()
         function.
  
 ***TimeStamp configuration ***
 ==============================
    [..]  
        (+) Configure the RTC_AF1 trigger and enables the RTC TimeStamp 
            using the RTC_TimeStampCmd() function.
        (+) To read the RTC TimeStamp Time and Date register, use the 
            RTC_GetTimeStamp() function.
        (+) To read the RTC TimeStamp SubSecond register, use the 
            RTC_GetTimeStampSubSecond() function.
  
 ***Tamper configuration ***
 ===========================
    [..]   
        (+) Configure the Tamper filter count using RTC_TamperFilterConfig()
            function. 
        (+) Configure the RTC Tamper trigger Edge or Level according to the Tamper 
            filter (if equal to 0 Edge else Level) value using the RTC_TamperConfig() function
        (+) Configure the Tamper sampling frequency using RTC_TamperSamplingFreqConfig()
            function.
        (+) Configure the Tamper precharge or discharge duration using 
            RTC_TamperPinsPrechargeDuration() function.
        (+) Enable the Tamper Pull-UP using RTC_TamperPullUpDisableCmd() function.
        (+) Enable the RTC Tamper using the RTC_TamperCmd() function.
        (+) Enable the Time stamp on Tamper detection event using  
            RTC_TSOnTamperDetecCmd() function.     
  
 ***Backup Data Registers configuration ***
 ==========================================
    [..]  
        (+) To write to the RTC Backup Data registers, use the RTC_WriteBackupRegister()
            function.  
        (+) To read the RTC Backup Data registers, use the RTC_ReadBackupRegister()
            function.  
  
                       ##### RTC and low power modes #####
 ===============================================================================
    [..] The MCU can be woken up from a low power mode by an RTC alternate 
         function.
    [..] The RTC alternate functions are the RTC alarm (Alarm A), RTC tamper 
         event detection and RTC time stamp event detection.
         These RTC alternate functions can wake up the system from the Stop 
         and Standby lowpower modes.
         The system can also wake up from low power modes without depending 
         on an external interrupt (Auto-wakeup mode), by using the RTC alarm events.
    [..] The RTC provides a programmable time base for waking up from the 
         Stop or Standby mode at regular intervals.
         Wakeup from STOP and Standby modes is possible only when the RTC 
         clock source is LSE or LSI.
  
               ##### Selection of RTC_AF1 alternate functions #####
 ===============================================================================
    [..] The RTC_AF1 pin (PC13) can be used for the following purposes:
         (+) AFO_ALARM output
         (+) AFO_CALIB output
         (+) AFI_TAMPER
         (+) AFI_TIMESTAMP
  
   +------------------------------------------------------------------------------------------+
   |     Pin         |AFO_ALARM |AFO_CALIB |AFI_TAMPER |AFI_TIMESTAMP | WKUP2  |ALARMOUTTYPE  |
   |  configuration  | ENABLED  | ENABLED  |  ENABLED  |   ENABLED    |ENABLED |  AFO_ALARM   |
   |  and function   |          |          |           |              |        |Configuration |
   |-----------------|----------|----------|-----------|--------------|--------|--------------|
   |   Alarm out     |          |          |           |              | Don't  |              |
   |   output OD     |     1    |    0     |Don't care | Don't care   | care   |      0       |
   |-----------------|----------|----------|-----------|--------------|--------|--------------|
   |   Alarm out     |          |          |           |              | Don't  |              |
   |   output PP     |     1    |    0     |Don't care | Don't care   | care   |      1       |
   |-----------------|----------|----------|-----------|--------------|--------|--------------|
   | Calibration out |          |          |           |              | Don't  |              |
   |   output PP     |     0    |    1     |Don't care | Don't care   | care   |  Don't care  |
   |-----------------|----------|----------|-----------|--------------|--------|--------------|
   |  TAMPER input   |          |          |           |              | Don't  |              |
   |   floating      |     0    |    0     |     1     |      0       | care   |  Don't care  |
   |-----------------|----------|----------|-----------|--------------|--------|--------------|
   |  TIMESTAMP and  |          |          |           |              | Don't  |              |
   |  TAMPER input   |     0    |    0     |     1     |      1       | care   |  Don't care  |
   |   floating      |          |          |           |              |        |              |
   |-----------------|----------|----------|-----------|--------------|--------|--------------|
   | TIMESTAMP input |          |          |           |              | Don't  |              |
   |    floating     |     0    |    0     |     0     |      1       | care   |  Don't care  |
   |-----------------|----------|----------|-----------|--------------|--------|--------------|
   |  Wakeup Pin 2   |     0    |    0     |     0     |      0       |   1    |  Don't care  |
   |-----------------|----------|----------|-----------|--------------|--------|--------------|
   |  Standard GPIO  |     0    |    0     |     0     |      0       |   0    |  Don't care  |
   +------------------------------------------------------------------------------------------+
  
 @endverbatim
 
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC 
  * @brief RTC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Masks Definition */
#define RTC_TR_RESERVED_MASK    ((uint32_t)0x007F7F7F)
#define RTC_DR_RESERVED_MASK    ((uint32_t)0x00FFFF3F) 
#define RTC_INIT_MASK           ((uint32_t)0xFFFFFFFF)  
#define RTC_RSF_MASK            ((uint32_t)0xFFFFFF5F)
#define RTC_FLAGS_MASK          ((uint32_t)(RTC_FLAG_TSOVF | RTC_FLAG_TSF | RTC_FLAG_ALRAF | \
                                            RTC_FLAG_RSF | RTC_FLAG_INITS |RTC_FLAG_INITF | \
                                            RTC_FLAG_TAMP1F | RTC_FLAG_TAMP2F | RTC_FLAG_RECALPF | \
                                            RTC_FLAG_SHPF))

#define INITMODE_TIMEOUT         ((uint32_t) 0x00004000)
#define SYNCHRO_TIMEOUT          ((uint32_t) 0x00008000)
#define RECALPF_TIMEOUT          ((uint32_t) 0x00001000)
#define SHPF_TIMEOUT             ((uint32_t) 0x00001000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/* Private functions ---------------------------------------------------------*/

/** @defgroup RTC_Private_Functions
  * @{
  */ 

/** @defgroup RTC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  

    [..] This section provide functions allowing to initialize and configure the RTC
         Prescaler (Synchronous and Asynchronous), RTC Hour format, disable RTC registers
         Write protection, enter and exit the RTC initialization mode, RTC registers
         synchronization check and reference clock detection enable.
  
         (#) The RTC Prescaler is programmed to generate the RTC 1Hz time base.
             It is split into 2 programmable prescalers to minimize power consumption.
             (++) A 7-bit asynchronous prescaler and A 13-bit synchronous prescaler.
             (++) When both prescalers are used, it is recommended to configure the
                  asynchronous prescaler to a high value to minimize consumption.
         (#) All RTC registers are Write protected. Writing to the RTC registers
             is enabled by writing a key into the Write Protection register, RTC_WPR.
         (#) To Configure the RTC Calendar, user application should enter
             initialization mode. In this mode, the calendar counter is stopped
             and its value can be updated. When the initialization sequence is
             complete, the calendar restarts counting after 4 RTCCLK cycles.
         (#) To read the calendar through the shadow registers after Calendar
             initialization, calendar update or after wakeup from low power modes
             the software must first clear the RSF flag. The software must then
             wait until it is set again before reading the calendar, which means
             that the calendar registers have been correctly copied into the
             RTC_TR and RTC_DR shadow registers.The RTC_WaitForSynchro() function
             implements the above software sequence (RSF clear and RSF check).

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the RTC registers to their default reset values.
  * @note   This function doesn't reset the RTC Clock source and RTC Backup Data
  *         registers.       
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are deinitialized
  *          - ERROR: RTC registers are not deinitialized
  */
ErrorStatus RTC_DeInit(void)
{
  ErrorStatus status = ERROR;
  
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }  
  else
  {
    /* Reset TR, DR and CR registers */
    RTC->TR        = (uint32_t)0x00000000;
    RTC->WUTR      = (uint32_t)0x0000FFFF;
    RTC->DR        = (uint32_t)0x00002101;
    RTC->CR        &= (uint32_t)0x00000000;
    RTC->PRER      = (uint32_t)0x007F00FF;
    RTC->ALRMAR    = (uint32_t)0x00000000;
    RTC->SHIFTR    = (uint32_t)0x00000000;
    RTC->CALR       = (uint32_t)0x00000000;
    RTC->ALRMASSR  = (uint32_t)0x00000000;

    /* Reset ISR register and exit initialization mode */
    RTC->ISR = (uint32_t)0x00000000;
    
    /* Reset Tamper and alternate functions configuration register */
    RTC->TAFCR = 0x00000000;
      
    /* Wait till the RTC RSF flag is set */
    if (RTC_WaitForSynchro() == ERROR)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }

  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;  

  return status;
}

/**
  * @brief  Initializes the RTC registers according to the specified parameters 
  *         in RTC_InitStruct.
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure that contains 
  *         the configuration information for the RTC peripheral.
  * @note   The RTC Prescaler register is write protected and can be written in 
  *         initialization mode only.  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are initialized
  *          - ERROR: RTC registers are not initialized  
  */
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct)
{
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
  assert_param(IS_RTC_ASYNCH_PREDIV(RTC_InitStruct->RTC_AsynchPrediv));
  assert_param(IS_RTC_SYNCH_PREDIV(RTC_InitStruct->RTC_SynchPrediv));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }
  else
  {
    /* Clear RTC CR FMT Bit */
    RTC->CR &= ((uint32_t)~(RTC_CR_FMT));
    /* Set RTC_CR register */
    RTC->CR |=  ((uint32_t)(RTC_InitStruct->RTC_HourFormat));
  
    /* Configure the RTC PRER */
    RTC->PRER = (uint32_t)(RTC_InitStruct->RTC_SynchPrediv);
    RTC->PRER |= (uint32_t)(RTC_InitStruct->RTC_AsynchPrediv << 16);

    /* Exit Initialization mode */
    RTC_ExitInitMode();

    status = SUCCESS;
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;

  return status;
}

/**
  * @brief  Fills each RTC_InitStruct member with its default value.
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure which will be 
  *         initialized.
  * @retval None
  */
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct)
{
  /* Initialize the RTC_HourFormat member */
  RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24;

  /* Initialize the RTC_AsynchPrediv member */
  RTC_InitStruct->RTC_AsynchPrediv = (uint32_t)0x7F;

  /* Initialize the RTC_SynchPrediv member */
  RTC_InitStruct->RTC_SynchPrediv = (uint32_t)0xFF; 
}

/**
  * @brief  Enables or disables the RTC registers write protection.
  * @note   All the RTC registers are write protected except for RTC_ISR[13:8], 
  *         RTC_TAFCR and RTC_BKPxR.
  * @note   Writing a wrong key reactivates the write protection.
  * @note   The protection mechanism is not affected by system reset.
  * @param  NewState: new state of the write protection.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WriteProtectionCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the write protection for RTC registers */
    RTC->WPR = 0xFF;
  }
  else
  {
    /* Disable the write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
  }
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @note   The RTC Initialization mode is write protected, use the 
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC is in Init mode
  *          - ERROR: RTC is not in Init mode
  */
ErrorStatus RTC_EnterInitMode(void)
{
  __IO uint32_t initcounter = 0x00;
  ErrorStatus status = ERROR;
  uint32_t initstatus = 0x00;

  /* Check if the Initialization mode is set */
  if ((RTC->ISR & RTC_ISR_INITF) == (uint32_t)RESET)
  {
    /* Set the Initialization mode */
    RTC->ISR = (uint32_t)RTC_INIT_MASK;
    
    /* Wait till RTC is in INIT state and if Time out is reached exit */
    do
    {
      initstatus = RTC->ISR & RTC_ISR_INITF;
      initcounter++;  
    } while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));
    
    if ((RTC->ISR & RTC_ISR_INITF) != RESET)
    {
      status = SUCCESS;
    }
    else
    {
      status = ERROR;
    }
  }
  else
  {
    status = SUCCESS;
  }

  return (status);
}

/**
  * @brief  Exits the RTC Initialization mode.
  * @note   When the initialization sequence is complete, the calendar restarts 
  *         counting after 4 RTCCLK cycles.  
  * @note   The RTC Initialization mode is write protected, use the 
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.      
  * @param  None
  * @retval None
  */
void RTC_ExitInitMode(void)
{
  /* Exit Initialization mode */
  RTC->ISR &= (uint32_t)~RTC_ISR_INIT;
}

/**
  * @brief  Waits until the RTC Time and Date registers (RTC_TR and RTC_DR) are 
  *         synchronized with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the 
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function. 
  * @note   To read the calendar through the shadow registers after Calendar 
  *         initialization, calendar update or after wakeup from low power modes 
  *         the software must first clear the RSF flag. 
  *         The software must then wait until it is set again before reading 
  *         the calendar, which means that the calendar registers have been 
  *         correctly copied into the RTC_TR and RTC_DR shadow registers.   
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are synchronised
  *          - ERROR: RTC registers are not synchronised
  */
ErrorStatus RTC_WaitForSynchro(void)
{
  __IO uint32_t synchrocounter = 0;
  ErrorStatus status = ERROR;
  uint32_t synchrostatus = 0x00;

  if ((RTC->CR & RTC_CR_BYPSHAD) != RESET)
  {
    /* Bypass shadow mode */
    status = SUCCESS;
  }
  else
  {
    /* Disable the write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* Clear RSF flag */
    RTC->ISR &= (uint32_t)RTC_RSF_MASK;

    /* Wait the registers to be synchronised */
    do
    {
      synchrostatus = RTC->ISR & RTC_ISR_RSF;
      synchrocounter++;  
    } while((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));

    if ((RTC->ISR & RTC_ISR_RSF) != RESET)
    {
      status = SUCCESS;
    }
    else
    {
      status = ERROR;
    }

    /* Enable the write protection for RTC registers */
    RTC->WPR = 0xFF;
  }

  return (status);
}

/**
  * @brief  Enables or disables the RTC reference clock detection.
  * @param  NewState: new state of the RTC reference clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC reference clock detection is enabled
  *          - ERROR: RTC reference clock detection is disabled  
  */
ErrorStatus RTC_RefClockCmd(FunctionalState NewState)
{
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Enable the RTC reference clock detection */
      RTC->CR |= RTC_CR_REFCKON;
    }
    else
    {
      /* Disable the RTC reference clock detection */
      RTC->CR &= ~RTC_CR_REFCKON;
    }
    /* Exit Initialization mode */
    RTC_ExitInitMode();

    status = SUCCESS;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;

  return status;
}

/**
  * @brief  Enables or Disables the Bypass Shadow feature.
  * @note   When the Bypass Shadow is enabled the calendar value are taken 
  *         directly from the Calendar counter.
  * @param  NewState: new state of the Bypass Shadow feature.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
*/
void RTC_BypassShadowCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  if (NewState != DISABLE)
  {
    /* Set the BYPSHAD bit */
    RTC->CR |= (uint8_t)RTC_CR_BYPSHAD;
  }
  else
  {
    /* Reset the BYPSHAD bit */
    RTC->CR &= (uint8_t)~RTC_CR_BYPSHAD;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @}
  */

/** @defgroup RTC_Group2 Time and Date configuration functions
 *  @brief   Time and Date configuration functions
 *
@verbatim
 ===============================================================================
               ##### Time and Date configuration functions #####
 ===============================================================================
    [..]  This section provide functions allowing to program and read the RTC
          Calendar (Time and Date).

@endverbatim
  * @{
  */

/**
  * @brief  Set the RTC current time.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format 
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that contains 
  *                        the time configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Time register is configured
  *          - ERROR: RTC Time register is not configured
  */
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
  uint32_t tmpreg = 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  
  if (RTC_Format == RTC_Format_BIN)
  {
    if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      assert_param(IS_RTC_HOUR12(RTC_TimeStruct->RTC_Hours));
      assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
    }
    else
    {
      RTC_TimeStruct->RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_TimeStruct->RTC_Hours));
    }
    assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
  }
  else
  {
    if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      tmpreg = RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
      assert_param(IS_RTC_HOUR12(tmpreg));
      assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12)); 
    } 
    else
    {
      RTC_TimeStruct->RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
    }
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds)));
  }
  
  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpreg = (((uint32_t)(RTC_TimeStruct->RTC_Hours) << 16) | \
             ((uint32_t)(RTC_TimeStruct->RTC_Minutes) << 8) | \
             ((uint32_t)RTC_TimeStruct->RTC_Seconds) | \
             ((uint32_t)(RTC_TimeStruct->RTC_H12) << 16)); 
  }
  else
  {
    tmpreg = (uint32_t)(((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Hours) << 16) | \
                   ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Minutes) << 8) | \
                   ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Seconds)) | \
                   (((uint32_t)RTC_TimeStruct->RTC_H12) << 16));
  } 

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Set the RTC_TR register */
    RTC->TR = (uint32_t)(tmpreg & RTC_TR_RESERVED_MASK);

    /* Exit Initialization mode */
    RTC_ExitInitMode(); 

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if ((RTC->CR & RTC_CR_BYPSHAD) == RESET)
    {
      if (RTC_WaitForSynchro() == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;
      }
    }
    else
    {
      status = SUCCESS;
    }
  
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
    
  return status;
}

/**
  * @brief  Fills each RTC_TimeStruct member with its default value
  *         (Time = 00h:00min:00sec).
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure which will be 
  *         initialized.
  * @retval None
  */
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct)
{
  /* Time = 00h:00min:00sec */
  RTC_TimeStruct->RTC_H12 = RTC_H12_AM;
  RTC_TimeStruct->RTC_Hours = 0;
  RTC_TimeStruct->RTC_Minutes = 0;
  RTC_TimeStruct->RTC_Seconds = 0; 
}

/**
  * @brief  Get the RTC current Time.
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format 
  *            @arg RTC_Format_BCD:  BCD data format
  * @param RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that will 
  *                        contain the returned current time configuration.
  * @retval None
  */
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(RTC->TR & RTC_TR_RESERVED_MASK); 
  
  /* Fill the structure fields with the read parameters */
  RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & (RTC_TR_HT | RTC_TR_HU)) >> 16);
  RTC_TimeStruct->RTC_Minutes = (uint8_t)((tmpreg & (RTC_TR_MNT | RTC_TR_MNU)) >>8);
  RTC_TimeStruct->RTC_Seconds = (uint8_t)(tmpreg & (RTC_TR_ST | RTC_TR_SU));
  RTC_TimeStruct->RTC_H12 = (uint8_t)((tmpreg & (RTC_TR_PM)) >> 16);  

  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_TimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds);
  }
}

/**
  * @brief  Gets the RTC current Calendar Subseconds value.
  * @note   This function freeze the Time and Date registers after reading the 
  *         SSR register.
  * @param  None
  * @retval RTC current Calendar Subseconds value.
  */
uint32_t RTC_GetSubSecond(void)
{
  uint32_t tmpreg = 0;
  
  /* Get subseconds values from the correspondent registers*/
  tmpreg = (uint32_t)(RTC->SSR);
  
  /* Read DR register to unfroze calendar registers */
  (void) (RTC->DR);
  
  return (tmpreg);
}

/**
  * @brief  Set the RTC current date.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format 
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure that contains 
  *                         the date configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Date register is configured
  *          - ERROR: RTC Date register is not configured
  */
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
  uint32_t tmpreg = 0;
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  if ((RTC_Format == RTC_Format_BIN) && ((RTC_DateStruct->RTC_Month & 0x10) == 0x10))
  {
    RTC_DateStruct->RTC_Month = (RTC_DateStruct->RTC_Month & (uint32_t)~(0x10)) + 0x0A;
  }  
  if (RTC_Format == RTC_Format_BIN)
  {
    assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
    assert_param(IS_RTC_MONTH(RTC_DateStruct->RTC_Month));
    assert_param(IS_RTC_DATE(RTC_DateStruct->RTC_Date));
  }
  else
  {
    assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year)));
    tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
    assert_param(IS_RTC_MONTH(tmpreg));
    tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
    assert_param(IS_RTC_DATE(tmpreg));
  }
  assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->RTC_WeekDay));

  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpreg = ((((uint32_t)RTC_DateStruct->RTC_Year) << 16) | \
              (((uint32_t)RTC_DateStruct->RTC_Month) << 8) | \
              ((uint32_t)RTC_DateStruct->RTC_Date) | \
              (((uint32_t)RTC_DateStruct->RTC_WeekDay) << 13)); 
  }  
  else
  {
    tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Year) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Month) << 8) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Date)) | \
              ((uint32_t)RTC_DateStruct->RTC_WeekDay << 13));
  }

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Set the RTC_DR register */
    RTC->DR = (uint32_t)(tmpreg & RTC_DR_RESERVED_MASK);

    /* Exit Initialization mode */
    RTC_ExitInitMode(); 

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if ((RTC->CR & RTC_CR_BYPSHAD) == RESET)
    {
      if (RTC_WaitForSynchro() == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;
      }
    }
    else
    {
      status = SUCCESS;
    }
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
  
  return status;
}

/**
  * @brief  Fills each RTC_DateStruct member with its default value
  *         (Monday, January 01 xx00).
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure which will be 
  *         initialized.
  * @retval None
  */
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct)
{
  /* Monday, January 01 xx00 */
  RTC_DateStruct->RTC_WeekDay = RTC_Weekday_Monday;
  RTC_DateStruct->RTC_Date = 1;
  RTC_DateStruct->RTC_Month = RTC_Month_January;
  RTC_DateStruct->RTC_Year = 0;
}

/**
  * @brief  Get the RTC current date.
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format 
  *            @arg RTC_Format_BCD: BCD data format
  * @param RTC_DateStruct: pointer to a RTC_DateTypeDef structure that will 
  *                        contain the returned current date configuration.
  * @retval None
  */
void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  
  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(RTC->DR & RTC_DR_RESERVED_MASK); 

  /* Fill the structure fields with the read parameters */
  RTC_DateStruct->RTC_Year = (uint8_t)((tmpreg & (RTC_DR_YT | RTC_DR_YU)) >> 16);
  RTC_DateStruct->RTC_Month = (uint8_t)((tmpreg & (RTC_DR_MT | RTC_DR_MU)) >> 8);
  RTC_DateStruct->RTC_Date = (uint8_t)(tmpreg & (RTC_DR_DT | RTC_DR_DU));
  RTC_DateStruct->RTC_WeekDay = (uint8_t)((tmpreg & (RTC_DR_WDU)) >> 13);  

  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_DateStruct->RTC_Year = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year);
    RTC_DateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
    RTC_DateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
    RTC_DateStruct->RTC_WeekDay = (uint8_t)(RTC_DateStruct->RTC_WeekDay);   
  }
}

/**
  * @}
  */

/** @defgroup RTC_Group3 Alarms configuration functions
 *  @brief   Alarms (Alarm A) configuration functions 
 *
@verbatim
 ===============================================================================
         ##### Alarms (Alarm A and Alarm B) configuration functions #####
 ===============================================================================
    [..] This section provide functions allowing to program and read the RTC 
         Alarms.

@endverbatim
  * @{
  */

/**
  * @brief  Set the specified RTC Alarm.
  * @note   The Alarm register can only be written when the corresponding Alarm
  *         is disabled (Use the RTC_AlarmCmd(DISABLE)).    
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format 
  *            @arg RTC_Format_BCD: BCD data format
  * @param  RTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be one of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that 
  *                          contains the alarm configuration parameters.
  * @retval None
  */
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  assert_param(IS_RTC_ALARM(RTC_Alarm));
  assert_param(IS_RTC_ALARM_MASK(RTC_AlarmStruct->RTC_AlarmMask));
  assert_param(IS_RTC_ALARM_DATE_WEEKDAY_SEL(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel));

  if (RTC_Format == RTC_Format_BIN)
  {
    if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      assert_param(IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
      assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
    } 
    else
    {
      RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
    }
    assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));
    
    if(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel == RTC_AlarmDateWeekDaySel_Date)
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
    }
    else
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
    }
  }
  else
  {
    if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
      assert_param(IS_RTC_HOUR12(tmpreg));
      assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
    } 
    else
    {
      RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)));
    }
    
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)));
    
    if(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel == RTC_AlarmDateWeekDaySel_Date)
    {
      tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(tmpreg));    
    }
    else
    {
      tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(tmpreg));      
    }    
  }

  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpreg = (((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) | \
              ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds) | \
              ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 16) | \
              ((uint32_t)(RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmMask)); 
  }  
  else
  {
    tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)) | \
              ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmMask)); 
  }

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Configure the Alarm register */
  RTC->ALRMAR = (uint32_t)tmpreg;

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Fills each RTC_AlarmStruct member with its default value
  *         (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
  *         all fields are masked).
  * @param  RTC_AlarmStruct: pointer to a @ref RTC_AlarmTypeDef structure which
  *         will be initialized.
  * @retval None
  */
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  /* Alarm Time Settings : Time = 00h:00mn:00sec */
  RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;

  /* Alarm Date Settings : Date = 1st day of the month */
  RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
  RTC_AlarmStruct->RTC_AlarmDateWeekDay = 1;

  /* Alarm Masks Settings : Mask =  all fields are not masked */
  RTC_AlarmStruct->RTC_AlarmMask = RTC_AlarmMask_None;
}

/**
  * @brief  Get the RTC Alarm value and masks.
  * @param  RTC_Format: specifies the format of the output parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format 
  *            @arg RTC_Format_BCD: BCD data format
  * @param  RTC_Alarm: specifies the alarm to be read.
  *          This parameter can be one of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that will 
  *                          contains the output alarm configuration values.
  * @retval None
  */
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  assert_param(IS_RTC_ALARM(RTC_Alarm)); 

  /* Get the RTC_ALRMAR register */
  tmpreg = (uint32_t)(RTC->ALRMAR);

  /* Fill the structure with the read parameters */
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint32_t)((tmpreg & (RTC_ALRMAR_HT | \
                                                     RTC_ALRMAR_HU)) >> 16);
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint32_t)((tmpreg & (RTC_ALRMAR_MNT | \
                                                     RTC_ALRMAR_MNU)) >> 8);
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint32_t)(tmpreg & (RTC_ALRMAR_ST | \
                                                     RTC_ALRMAR_SU));
  RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = (uint32_t)((tmpreg & RTC_ALRMAR_PM) >> 16);
  RTC_AlarmStruct->RTC_AlarmDateWeekDay = (uint32_t)((tmpreg & (RTC_ALRMAR_DT | RTC_ALRMAR_DU)) >> 24);
  RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = (uint32_t)(tmpreg & RTC_ALRMAR_WDSEL);
  RTC_AlarmStruct->RTC_AlarmMask = (uint32_t)(tmpreg & RTC_AlarmMask_All);

  if (RTC_Format == RTC_Format_BIN)
  {
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = RTC_Bcd2ToByte(RTC_AlarmStruct-> \
                                                        RTC_AlarmTime.RTC_Hours);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = RTC_Bcd2ToByte(RTC_AlarmStruct-> \
                                                        RTC_AlarmTime.RTC_Minutes);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = RTC_Bcd2ToByte(RTC_AlarmStruct-> \
                                                        RTC_AlarmTime.RTC_Seconds);
    RTC_AlarmStruct->RTC_AlarmDateWeekDay = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
  }  
}

/**
  * @brief  Enables or disables the specified RTC Alarm.
  * @param  RTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  * @param  NewState: new state of the specified alarm.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Alarm is enabled/disabled
  *          - ERROR: RTC Alarm is not enabled/disabled  
  */
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState)
{
  __IO uint32_t alarmcounter = 0x00;
  uint32_t alarmstatus = 0x00;
  ErrorStatus status = ERROR;
    
  /* Check the parameters */
  assert_param(IS_RTC_CMD_ALARM(RTC_Alarm));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Configure the Alarm state */
  if (NewState != DISABLE)
  {
    RTC->CR |= (uint32_t)RTC_Alarm;

    status = SUCCESS;    
  }
  else
  { 
    /* Disable the Alarm in RTC_CR register */
    RTC->CR &= (uint32_t)~RTC_Alarm;
   
    /* Wait till RTC ALRxWF flag is set and if Time out is reached exit */
    do
    {
      alarmstatus = RTC->ISR & (RTC_Alarm >> 8);
      alarmcounter++;  
    } while((alarmcounter != INITMODE_TIMEOUT) && (alarmstatus == 0x00));
    
    if ((RTC->ISR & (RTC_Alarm >> 8)) == RESET)
    {
      status = ERROR;
    } 
    else
    {
      status = SUCCESS;
    }        
  } 

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
  
  return status;
}

/**
  * @brief  Configure the RTC AlarmA/B Subseconds value and mask.
  * @note   This function is performed only when the Alarm is disabled. 
  * @param  RTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be one of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  * @param  RTC_AlarmSubSecondValue: specifies the Subseconds value.
  *          This parameter can be a value from 0 to 0x00007FFF.
  * @param  RTC_AlarmSubSecondMask:  specifies the Subseconds Mask.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_AlarmSubSecondMask_All: All Alarm SS fields are masked.
  *                                             There is no comparison on sub seconds for Alarm.
  *            @arg RTC_AlarmSubSecondMask_SS14_1: SS[14:1] are don't care in Alarm comparison.
  *                                                Only SS[0] is compared
  *            @arg RTC_AlarmSubSecondMask_SS14_2: SS[14:2] are don't care in Alarm comparison.
  *                                                Only SS[1:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_3: SS[14:3] are don't care in Alarm comparison.
  *                                                Only SS[2:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_4: SS[14:4] are don't care in Alarm comparison.
  *                                                Only SS[3:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_5: SS[14:5] are don't care in Alarm comparison.
  *                                                Only SS[4:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_6: SS[14:6] are don't care in Alarm comparison.
  *                                                Only SS[5:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_7: SS[14:7] are don't care in Alarm comparison.
  *                                                Only SS[6:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_8: SS[14:8] are don't care in Alarm comparison.
  *                                                Only SS[7:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_9: SS[14:9] are don't care in Alarm comparison.
  *                                                Only SS[8:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_10: SS[14:10] are don't care in Alarm comparison.
  *                                                 Only SS[9:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_11: SS[14:11] are don't care in Alarm comparison.
  *                                                 Only SS[10:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_12: SS[14:12] are don't care in Alarm comparison.
  *                                                 Only SS[11:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_13: SS[14:13] are don't care in Alarm comparison.
  *                                                 Only SS[12:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14: SS[14] is don't care in Alarm comparison.
  *                                              Only SS[13:0] are compared
  *            @arg RTC_AlarmSubSecondMask_None: SS[14:0] are compared and must match to activate alarm
  * @retval None
  */
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint8_t RTC_AlarmSubSecondMask)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_ALARM(RTC_Alarm));
  assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(RTC_AlarmSubSecondValue));
  assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(RTC_AlarmSubSecondMask));
  
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /* Configure the Alarm A or Alarm B SubSecond registers */
  tmpreg = (uint32_t) (((uint32_t)(RTC_AlarmSubSecondValue)) | ((uint32_t)(RTC_AlarmSubSecondMask) << 24));
  
  /* Configure the AlarmA SubSecond register */
  RTC->ALRMASSR = tmpreg;

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;

}

/**
  * @brief  Gets the RTC Alarm Subseconds value.
  * @param  RTC_Alarm: specifies the alarm to be read.
  *          This parameter can be one of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  * @param  None
  * @retval RTC Alarm Subseconds value.
  */
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm)
{
  uint32_t tmpreg = 0;
  
  /* Get the RTC_ALRMAR register */
  tmpreg = (uint32_t)((RTC->ALRMASSR) & RTC_ALRMASSR_SS);

  return (tmpreg);
}

/**
  * @}
  */

/** @defgroup RTC_Group4 WakeUp Timer configuration functions
 *  @brief   WakeUp Timer configuration functions 
 *
@verbatim   
 ===============================================================================
            ##### WakeUp Timer configuration functions #####
 ===============================================================================  

    [..] This section provide functions allowing to program and read the RTC WakeUp.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the RTC Wakeup clock source.
  *         This function is available for STM32F072 devices.  
  * @note   The WakeUp Clock source can only be changed when the RTC WakeUp
  *         is disabled (Use the RTC_WakeUpCmd(DISABLE)).
  * @param  RTC_WakeUpClock: Wakeup Clock source.
  *          This parameter can be one of the following values:
  *            @arg RTC_WakeUpClock_RTCCLK_Div16
  *            @arg RTC_WakeUpClock_RTCCLK_Div8
  *            @arg RTC_WakeUpClock_RTCCLK_Div4
  *            @arg RTC_WakeUpClock_RTCCLK_Div2
  *            @arg RTC_WakeUpClock_CK_SPRE_16bits
  *            @arg RTC_WakeUpClock_CK_SPRE_17bits
  * @retval None
  */
void RTC_WakeUpClockConfig(uint32_t RTC_WakeUpClock)
{
  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_CLOCK(RTC_WakeUpClock));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Clear the Wakeup Timer clock source bits in CR register */
  RTC->CR &= (uint32_t)~RTC_CR_WUCKSEL;

  /* Configure the clock source */
  RTC->CR |= (uint32_t)RTC_WakeUpClock;
  
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Configures the RTC Wakeup counter.
  *         This function is available for STM32F072 devices.  
  * @note   The RTC WakeUp counter can only be written when the RTC WakeUp
  *         is disabled (Use the RTC_WakeUpCmd(DISABLE)).
  * @param  RTC_WakeUpCounter: specifies the WakeUp counter.
  *          This parameter can be a value from 0x0000 to 0xFFFF. 
  * @retval None
  */
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter)
{
  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_COUNTER(RTC_WakeUpCounter));
  
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /* Configure the Wakeup Timer counter */
  RTC->WUTR = (uint32_t)RTC_WakeUpCounter;
  
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Returns the RTC WakeUp timer counter value.
  *         This function is available for STM32F072 devices.  
  * @param  None
  * @retval The RTC WakeUp Counter value.
  */
uint32_t RTC_GetWakeUpCounter(void)
{
  /* Get the counter value */
  return ((uint32_t)(RTC->WUTR & RTC_WUTR_WUT));
}

/**
  * @brief  Enables or Disables the RTC WakeUp timer.
  *         This function is available for STM32F072 devices.  
  * @param  NewState: new state of the WakeUp timer.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
ErrorStatus RTC_WakeUpCmd(FunctionalState NewState)
{
  __IO uint32_t wutcounter = 0x00;
  uint32_t wutwfstatus = 0x00;
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  if (NewState != DISABLE)
  {
    /* Enable the Wakeup Timer */
    RTC->CR |= (uint32_t)RTC_CR_WUTE;
    status = SUCCESS;    
  }
  else
  {
    /* Disable the Wakeup Timer */
    RTC->CR &= (uint32_t)~RTC_CR_WUTE;
    /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
    do
    {
      wutwfstatus = RTC->ISR & RTC_ISR_WUTWF;
      wutcounter++;  
    } while((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));
    
    if ((RTC->ISR & RTC_ISR_WUTWF) == RESET)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }    
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
  
  return status;
}

/**
  * @}
  */

/** @defgroup RTC_Group5 Daylight Saving configuration functions
 *  @brief   Daylight Saving configuration functions 
 *
@verbatim   
 ===============================================================================
               ##### WakeUp Timer configuration functions #####
 ===============================================================================
    [..] This section provide functions allowing to program and read the RTC WakeUp. 

  This section provide functions allowing to configure the RTC DayLight Saving.

@endverbatim
  * @{
  */

/**
  * @brief  Adds or substract one hour from the current time.
  * @param  RTC_DayLightSaveOperation: the value of hour adjustment. 
  *          This parameter can be one of the following values:
  *            @arg RTC_DayLightSaving_SUB1H: Substract one hour (winter time)
  *            @arg RTC_DayLightSaving_ADD1H: Add one hour (summer time)
  * @param  RTC_StoreOperation: Specifies the value to be written in the BCK bit 
  *                             in CR register to store the operation.
  *          This parameter can be one of the following values:
  *            @arg RTC_StoreOperation_Reset: BCK Bit Reset
  *            @arg RTC_StoreOperation_Set: BCK Bit Set
  * @retval None
  */
void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation)
{
  /* Check the parameters */
  assert_param(IS_RTC_DAYLIGHT_SAVING(RTC_DayLightSaving));
  assert_param(IS_RTC_STORE_OPERATION(RTC_StoreOperation));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Clear the bits to be configured */
  RTC->CR &= (uint32_t)~(RTC_CR_BCK);

  /* Configure the RTC_CR register */
  RTC->CR |= (uint32_t)(RTC_DayLightSaving | RTC_StoreOperation);

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Returns the RTC Day Light Saving stored operation.
  * @param  None
  * @retval RTC Day Light Saving stored operation.
  *          - RTC_StoreOperation_Reset
  *          - RTC_StoreOperation_Set
  */
uint32_t RTC_GetStoreOperation(void)
{
  return (RTC->CR & RTC_CR_BCK);
}

/**
  * @}
  */

/** @defgroup RTC_Group6 Output pin Configuration function
 *  @brief   Output pin Configuration function 
 *
@verbatim   
 ===============================================================================
                  ##### Output pin Configuration function #####
 ===============================================================================
    [..] This section provide functions allowing to configure the RTC Output source.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the RTC output source (AFO_ALARM).
  * @param  RTC_Output: Specifies which signal will be routed to the RTC output. 
  *          This parameter can be one of the following values:
  *            @arg RTC_Output_Disable: No output selected
  *            @arg RTC_Output_AlarmA: signal of AlarmA mapped to output
  *            @arg RTC_Output_WakeUp: signal of WakeUp mapped to output, available only for STM32F072 devices  
  * @param  RTC_OutputPolarity: Specifies the polarity of the output signal. 
  *          This parameter can be one of the following:
  *            @arg RTC_OutputPolarity_High: The output pin is high when the 
  *                                          ALRAF is high (depending on OSEL)
  *            @arg RTC_OutputPolarity_Low: The output pin is low when the 
  *                                         ALRAF is high (depending on OSEL)
  * @retval None
  */
void RTC_OutputConfig(uint32_t RTC_Output, uint32_t RTC_OutputPolarity)
{
  /* Check the parameters */
  assert_param(IS_RTC_OUTPUT(RTC_Output));
  assert_param(IS_RTC_OUTPUT_POL(RTC_OutputPolarity));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Clear the bits to be configured */
  RTC->CR &= (uint32_t)~(RTC_CR_OSEL | RTC_CR_POL);

  /* Configure the output selection and polarity */
  RTC->CR |= (uint32_t)(RTC_Output | RTC_OutputPolarity);

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @}
  */

/** @defgroup RTC_Group7 Digital Calibration configuration functions
 *  @brief   Digital Calibration configuration functions 
 *
@verbatim   
 ===============================================================================
          ##### Digital Calibration configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the RTC clock to be output through the relative pin.
  * @param  NewState: new state of the digital calibration Output.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_CalibOutputCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  if (NewState != DISABLE)
  {
    /* Enable the RTC clock output */
    RTC->CR |= (uint32_t)RTC_CR_COE;
  }
  else
  { 
    /* Disable the RTC clock output */
    RTC->CR &= (uint32_t)~RTC_CR_COE;
  }
  
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF; 
}

/**
  * @brief  Configure the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
  * @param  RTC_CalibOutput: Select the Calibration output Selection .
  *          This parameter can be one of the following values:
  *            @arg RTC_CalibOutput_512Hz: A signal has a regular waveform at 512Hz. 
  *            @arg RTC_CalibOutput_1Hz: A signal has a regular waveform at 1Hz.
  * @retval None
*/
void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput)
{
  /* Check the parameters */
  assert_param(IS_RTC_CALIB_OUTPUT(RTC_CalibOutput));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /*clear flags before config*/
  RTC->CR &= (uint32_t)~(RTC_CR_CALSEL);

  /* Configure the RTC_CR register */
  RTC->CR |= (uint32_t)RTC_CalibOutput;

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Configures the Smooth Calibration Settings.
  * @param  RTC_SmoothCalibPeriod: Select the Smooth Calibration Period.
  *          This parameter can be can be one of the following values:
  *            @arg RTC_SmoothCalibPeriod_32sec: The smooth calibration periode is 32s.
  *            @arg RTC_SmoothCalibPeriod_16sec: The smooth calibration periode is 16s.
  *            @arg RTC_SmoothCalibPeriod_8sec: The smooth calibartion periode is 8s.
  * @param  RTC_SmoothCalibPlusPulses: Select to Set or reset the CALP bit.
  *          This parameter can be one of the following values:
  *            @arg RTC_SmoothCalibPlusPulses_Set: Add one RTCCLK puls every 2**11 pulses.
  *            @arg RTC_SmoothCalibPlusPulses_Reset: No RTCCLK pulses are added.
  * @param  RTC_SmouthCalibMinusPulsesValue: Select the value of CALM[8:0] bits.
  *          This parameter can be one any value from 0 to 0x000001FF.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Calib registers are configured
  *          - ERROR: RTC Calib registers are not configured
*/
ErrorStatus RTC_SmoothCalibConfig(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue)
{
  ErrorStatus status = ERROR;
  uint32_t recalpfcount = 0;

  /* Check the parameters */
  assert_param(IS_RTC_SMOOTH_CALIB_PERIOD(RTC_SmoothCalibPeriod));
  assert_param(IS_RTC_SMOOTH_CALIB_PLUS(RTC_SmoothCalibPlusPulses));
  assert_param(IS_RTC_SMOOTH_CALIB_MINUS(RTC_SmouthCalibMinusPulsesValue));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /* check if a calibration is pending*/
  if ((RTC->ISR & RTC_ISR_RECALPF) != RESET)
  {
    /* wait until the Calibration is completed*/
    while (((RTC->ISR & RTC_ISR_RECALPF) != RESET) && (recalpfcount != RECALPF_TIMEOUT))
    {
      recalpfcount++;
    }
  }

  /* check if the calibration pending is completed or if there is no calibration operation at all*/
  if ((RTC->ISR & RTC_ISR_RECALPF) == RESET)
  {
    /* Configure the Smooth calibration settings */
    RTC->CALR = (uint32_t)((uint32_t)RTC_SmoothCalibPeriod | (uint32_t)RTC_SmoothCalibPlusPulses | (uint32_t)RTC_SmouthCalibMinusPulsesValue);

    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
  
  return (ErrorStatus)(status);
}

/**
  * @}
  */


/** @defgroup RTC_Group8 TimeStamp configuration functions
 *  @brief   TimeStamp configuration functions 
 *
@verbatim   
 ===============================================================================
          ##### TimeStamp configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or Disables the RTC TimeStamp functionality with the 
  *         specified time stamp pin stimulating edge.
  * @param  RTC_TimeStampEdge: Specifies the pin edge on which the TimeStamp is 
  *         activated.
  *          This parameter can be one of the following:
  *            @arg RTC_TimeStampEdge_Rising: the Time stamp event occurs on the rising 
  *                                           edge of the related pin.
  *            @arg RTC_TimeStampEdge_Falling: the Time stamp event occurs on the 
  *                                            falling edge of the related pin.
  * @param  NewState: new state of the TimeStamp.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_TIMESTAMP_EDGE(RTC_TimeStampEdge));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(RTC->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

  /* Get the new configuration */
  if (NewState != DISABLE)
  {
    tmpreg |= (uint32_t)(RTC_TimeStampEdge | RTC_CR_TSE);
  }
  else
  {
    tmpreg |= (uint32_t)(RTC_TimeStampEdge);
  }

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Configure the Time Stamp TSEDGE and Enable bits */
  RTC->CR = (uint32_t)tmpreg;

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Get the RTC TimeStamp value and masks.
  * @param  RTC_Format: specifies the format of the output parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format 
  *            @arg RTC_Format_BCD: BCD data format
  * @param RTC_StampTimeStruct: pointer to a RTC_TimeTypeDef structure that will 
  *                             contains the TimeStamp time values. 
  * @param RTC_StampDateStruct: pointer to a RTC_DateTypeDef structure that will 
  *                             contains the TimeStamp date values.     
  * @retval None
  */
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct, 
                                      RTC_DateTypeDef* RTC_StampDateStruct)
{
  uint32_t tmptime = 0, tmpdate = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the TimeStamp time and date registers values */
  tmptime = (uint32_t)(RTC->TSTR & RTC_TR_RESERVED_MASK);
  tmpdate = (uint32_t)(RTC->TSDR & RTC_DR_RESERVED_MASK);

  /* Fill the Time structure fields with the read parameters */
  RTC_StampTimeStruct->RTC_Hours = (uint8_t)((tmptime & (RTC_TR_HT | RTC_TR_HU)) >> 16);
  RTC_StampTimeStruct->RTC_Minutes = (uint8_t)((tmptime & (RTC_TR_MNT | RTC_TR_MNU)) >> 8);
  RTC_StampTimeStruct->RTC_Seconds = (uint8_t)(tmptime & (RTC_TR_ST | RTC_TR_SU));
  RTC_StampTimeStruct->RTC_H12 = (uint8_t)((tmptime & (RTC_TR_PM)) >> 16);  

  /* Fill the Date structure fields with the read parameters */
  RTC_StampDateStruct->RTC_Year = 0;
  RTC_StampDateStruct->RTC_Month = (uint8_t)((tmpdate & (RTC_DR_MT | RTC_DR_MU)) >> 8);
  RTC_StampDateStruct->RTC_Date = (uint8_t)(tmpdate & (RTC_DR_DT | RTC_DR_DU));
  RTC_StampDateStruct->RTC_WeekDay = (uint8_t)((tmpdate & (RTC_DR_WDU)) >> 13);

  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the Time structure parameters to Binary format */
    RTC_StampTimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Hours);
    RTC_StampTimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Minutes);
    RTC_StampTimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Seconds);

    /* Convert the Date structure parameters to Binary format */
    RTC_StampDateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Month);
    RTC_StampDateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Date);
    RTC_StampDateStruct->RTC_WeekDay = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_WeekDay);
  }
}

/**
  * @brief  Get the RTC timestamp Subseconds value.
  * @param  None
  * @retval RTC current timestamp Subseconds value.
  */
uint32_t RTC_GetTimeStampSubSecond(void)
{
  /* Get timestamp subseconds values from the correspondent registers */
  return (uint32_t)(RTC->TSSSR);
}

/**
  * @}
  */

/** @defgroup RTC_Group9 Tampers configuration functions
 *  @brief   Tampers configuration functions 
 *
@verbatim   
 ===============================================================================
          ##### Tampers configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Configures the select Tamper pin edge.
  * @param  RTC_Tamper: Selected tamper pin.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_Tamper_1: Select Tamper 1.
  *            @arg RTC_Tamper_2: Select Tamper 2.
  * @param  RTC_TamperTrigger: Specifies the trigger on the tamper pin that 
  *                            stimulates tamper event. 
  *          This parameter can be one of the following values:
  *            @arg RTC_TamperTrigger_RisingEdge: Rising Edge of the tamper pin causes tamper event.
  *            @arg RTC_TamperTrigger_FallingEdge: Falling Edge of the tamper pin causes tamper event.
  *            @arg RTC_TamperTrigger_LowLevel: Low Level of the tamper pin causes tamper event.
  *            @arg RTC_TamperTrigger_HighLevel: High Level of the tamper pin causes tamper event.
  * @retval None
  */
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger)
{
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(RTC_Tamper)); 
  assert_param(IS_RTC_TAMPER_TRIGGER(RTC_TamperTrigger));
 
  if (RTC_TamperTrigger == RTC_TamperTrigger_RisingEdge)
  {  
    /* Configure the RTC_TAFCR register */
    RTC->TAFCR &= (uint32_t)((uint32_t)~(RTC_Tamper << 1));	
  }
  else
  { 
    /* Configure the RTC_TAFCR register */
    RTC->TAFCR |= (uint32_t)(RTC_Tamper << 1);  
  }  
}

/**
  * @brief  Enables or Disables the Tamper detection.
  * @param  RTC_Tamper: Selected tamper pin.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_Tamper_1: Select Tamper 1.
  *            @arg RTC_Tamper_2: Select Tamper 2.
  * @param  NewState: new state of the tamper pin.
  *         This parameter can be: ENABLE or DISABLE.                   
  * @retval None
  */
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(RTC_Tamper));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected Tamper pin */
    RTC->TAFCR |= (uint32_t)RTC_Tamper;
  }
  else
  {
    /* Disable the selected Tamper pin */
    RTC->TAFCR &= (uint32_t)~RTC_Tamper;    
  }  
}

/**
  * @brief  Configures the Tampers Filter.
  * @param  RTC_TamperFilter: Specifies the tampers filter.
  *          This parameter can be one of the following values:
  *            @arg RTC_TamperFilter_Disable: Tamper filter is disabled.
  *            @arg RTC_TamperFilter_2Sample: Tamper is activated after 2 consecutive 
  *                                           samples at the active level 
  *            @arg RTC_TamperFilter_4Sample: Tamper is activated after 4 consecutive 
  *                                           samples at the active level
  *            @arg RTC_TamperFilter_8Sample: Tamper is activated after 8 consecutive 
  *                                           samples at the active level 
  * @retval None
  */
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter)
{
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER_FILTER(RTC_TamperFilter));
   
  /* Clear TAMPFLT[1:0] bits in the RTC_TAFCR register */
  RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPFLT);

  /* Configure the RTC_TAFCR register */
  RTC->TAFCR |= (uint32_t)RTC_TamperFilter;
}

/**
  * @brief  Configures the Tampers Sampling Frequency.
  * @param  RTC_TamperSamplingFreq: Specifies the tampers Sampling Frequency.
  *          This parameter can be one of the following values:
  *            @arg RTC_TamperSamplingFreq_RTCCLK_Div32768: Each of the tamper inputs are sampled
  *                                                         with a frequency =  RTCCLK / 32768
  *            @arg RTC_TamperSamplingFreq_RTCCLK_Div16384: Each of the tamper inputs are sampled
  *                                                         with a frequency =  RTCCLK / 16384
  *            @arg RTC_TamperSamplingFreq_RTCCLK_Div8192: Each of the tamper inputs are sampled
  *                                                        with a frequency =  RTCCLK / 8192
  *            @arg RTC_TamperSamplingFreq_RTCCLK_Div4096: Each of the tamper inputs are sampled
  *                                                        with a frequency =  RTCCLK / 4096
  *            @arg RTC_TamperSamplingFreq_RTCCLK_Div2048: Each of the tamper inputs are sampled
  *                                                        with a frequency =  RTCCLK / 2048
  *            @arg RTC_TamperSamplingFreq_RTCCLK_Div1024: Each of the tamper inputs are sampled
  *                                                        with a frequency =  RTCCLK / 1024
  *            @arg RTC_TamperSamplingFreq_RTCCLK_Div512: Each of the tamper inputs are sampled
  *                                                       with a frequency =  RTCCLK / 512  
  *            @arg RTC_TamperSamplingFreq_RTCCLK_Div256: Each of the tamper inputs are sampled
  *                                                       with a frequency =  RTCCLK / 256  
  * @retval None
  */
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq)
{
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(RTC_TamperSamplingFreq));
 
  /* Clear TAMPFREQ[2:0] bits in the RTC_TAFCR register */
  RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPFREQ);

  /* Configure the RTC_TAFCR register */
  RTC->TAFCR |= (uint32_t)RTC_TamperSamplingFreq;
}

/**
  * @brief  Configures the Tampers Pins input Precharge Duration.
  * @param  RTC_TamperPrechargeDuration: Specifies the Tampers Pins input
  *         Precharge Duration.
  *          This parameter can be one of the following values:
  *            @arg RTC_TamperPrechargeDuration_1RTCCLK: Tamper pins are pre-charged before sampling during 1 RTCCLK cycle
  *            @arg RTC_TamperPrechargeDuration_2RTCCLK: Tamper pins are pre-charged before sampling during 2 RTCCLK cycle
  *            @arg RTC_TamperPrechargeDuration_4RTCCLK: Tamper pins are pre-charged before sampling during 4 RTCCLK cycle    
  *            @arg RTC_TamperPrechargeDuration_8RTCCLK: Tamper pins are pre-charged before sampling during 8 RTCCLK cycle
  * @retval None
  */
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration)
{
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER_PRECHARGE_DURATION(RTC_TamperPrechargeDuration));
   
  /* Clear TAMPPRCH[1:0] bits in the RTC_TAFCR register */
  RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPPRCH);

  /* Configure the RTC_TAFCR register */
  RTC->TAFCR |= (uint32_t)RTC_TamperPrechargeDuration;
}

/**
  * @brief  Enables or Disables the TimeStamp on Tamper Detection Event.
  * @note   The timestamp is valid even the TSE bit in tamper control register 
  *         is reset.   
  * @param  NewState: new state of the timestamp on tamper event.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
   
  if (NewState != DISABLE)
  {
    /* Save timestamp on tamper detection event */
    RTC->TAFCR |= (uint32_t)RTC_TAFCR_TAMPTS;
  }
  else
  {
    /* Tamper detection does not cause a timestamp to be saved */
    RTC->TAFCR &= (uint32_t)~RTC_TAFCR_TAMPTS;    
  }
}

/**
  * @brief  Enables or Disables the Precharge of Tamper pin.
  * @param  NewState: new state of tamper pull up.
  *          This parameter can be: ENABLE or DISABLE.                   
  * @retval None
  */
void RTC_TamperPullUpCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
 if (NewState != DISABLE)
  {
    /* Enable precharge of the selected Tamper pin */
    RTC->TAFCR &= (uint32_t)~RTC_TAFCR_TAMPPUDIS; 
  }
  else
  {
    /* Disable precharge of the selected Tamper pin */
    RTC->TAFCR |= (uint32_t)RTC_TAFCR_TAMPPUDIS;    
  } 
}

/**
  * @}
  */

/** @defgroup RTC_Group10 Backup Data Registers configuration functions
 *  @brief   Backup Data Registers configuration functions  
 *
@verbatim   
 ===============================================================================
          ##### Backup Data Registers configuration functions ##### 
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Writes a data in a specified RTC Backup data register.
  * @param  RTC_BKP_DR: RTC Backup data Register number.
  *          This parameter can be: RTC_BKP_DRx where x can be from 0 to 4 to 
  *                                 specify the register.
  * @param  Data: Data to be written in the specified RTC Backup data register.                     
  * @retval None
  */
void RTC_WriteBackupRegister(uint32_t RTC_BKP_DR, uint32_t Data)
{
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_RTC_BKP(RTC_BKP_DR));

  tmp = RTC_BASE + 0x50;
  tmp += (RTC_BKP_DR * 4);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * @brief  Reads data from the specified RTC Backup data Register.
  * @param  RTC_BKP_DR: RTC Backup data Register number.
  *          This parameter can be: RTC_BKP_DRx where x can be from 0 to 19 to 
  *                          specify the register.                   
  * @retval None
  */
uint32_t RTC_ReadBackupRegister(uint32_t RTC_BKP_DR)
{
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_RTC_BKP(RTC_BKP_DR));

  tmp = RTC_BASE + 0x50;
  tmp += (RTC_BKP_DR * 4);
  
  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}

/**
  * @}
  */

/** @defgroup RTC_Group11 Output Type Config configuration functions
 *  @brief   Output Type Config configuration functions  
 *
@verbatim   
 ===============================================================================
             ##### Output Type Config configuration functions ##### 
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Configures the RTC Output Pin mode. 
  * @param  RTC_OutputType: specifies the RTC Output (PC13) pin mode.
  *          This parameter can be one of the following values:
  *            @arg RTC_OutputType_OpenDrain: RTC Output (PC13) is configured in 
  *                                    Open Drain mode.
  *            @arg RTC_OutputType_PushPull:  RTC Output (PC13) is configured in 
  *                                    Push Pull mode.    
  * @retval None
  */
void RTC_OutputTypeConfig(uint32_t RTC_OutputType)
{
  /* Check the parameters */
  assert_param(IS_RTC_OUTPUT_TYPE(RTC_OutputType));
  
  RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_ALARMOUTTYPE);
  RTC->TAFCR |= (uint32_t)(RTC_OutputType);  
}

/**
  * @}
  */

/** @defgroup RTC_Group12 Shift control synchronisation functions
 *  @brief   Shift control synchronisation functions 
 *
@verbatim   
 ===============================================================================
            ##### Shift control synchronisation functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Configures the Synchronization Shift Control Settings.
  * @note   When REFCKON is set, firmware must not write to Shift control register 
  * @param  RTC_ShiftAdd1S: Select to add or not 1 second to the time Calendar.
  *          This parameter can be one of the following values :
  *            @arg RTC_ShiftAdd1S_Set: Add one second to the clock calendar. 
  *            @arg RTC_ShiftAdd1S_Reset: No effect.
  * @param  RTC_ShiftSubFS: Select the number of Second Fractions to Substitute.
  *         This parameter can be one any value from 0 to 0x7FFF.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Shift registers are configured
  *          - ERROR: RTC Shift registers are not configured
*/
ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS)
{
  ErrorStatus status = ERROR;
  uint32_t shpfcount = 0;

  /* Check the parameters */
  assert_param(IS_RTC_SHIFT_ADD1S(RTC_ShiftAdd1S));
  assert_param(IS_RTC_SHIFT_SUBFS(RTC_ShiftSubFS));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /* Check if a Shift is pending*/
  if ((RTC->ISR & RTC_ISR_SHPF) != RESET)
  {
    /* Wait until the shift is completed*/
    while (((RTC->ISR & RTC_ISR_SHPF) != RESET) && (shpfcount != SHPF_TIMEOUT))
    {
      shpfcount++;
    }
  }

  /* Check if the Shift pending is completed or if there is no Shift operation at all*/
  if ((RTC->ISR & RTC_ISR_SHPF) == RESET)
  {
    /* check if the reference clock detection is disabled */
    if((RTC->CR & RTC_CR_REFCKON) == RESET)
    {
      /* Configure the Shift settings */
      RTC->SHIFTR = (uint32_t)(uint32_t)(RTC_ShiftSubFS) | (uint32_t)(RTC_ShiftAdd1S);
    
      if(RTC_WaitForSynchro() == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;
      }
    }
    else
    {
      status = ERROR;
    }
  }
  else
  {
    status = ERROR;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
  
  return (ErrorStatus)(status);
}

/**
  * @}
  */

/** @defgroup RTC_Group13 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions  
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================  
    [..] All RTC interrupts are connected to the EXTI controller.
 
         (+) To enable the RTC Alarm interrupt, the following sequence is required:
             (++) Configure and enable the EXTI Line 17 in interrupt mode and select the rising 
                  edge sensitivity using the EXTI_Init() function.
             (++) Configure and enable the RTC_Alarm IRQ channel in the NVIC using the NVIC_Init()
                  function.
             (++) Configure the RTC to generate RTC alarms (Alarm A) using
                  the RTC_SetAlarm() and RTC_AlarmCmd() functions.

         (+) To enable the RTC Tamper interrupt, the following sequence is required:
             (++) Configure and enable the EXTI Line 19 in interrupt mode and select the rising 
                  edge sensitivity using the EXTI_Init() function.
             (++) Configure and enable the TAMP_STAMP IRQ channel in the NVIC using the NVIC_Init()
                  function.
             (++) Configure the RTC to detect the RTC tamper event using the 
                  RTC_TamperTriggerConfig() and RTC_TamperCmd() functions.

         (+) To enable the RTC TimeStamp interrupt, the following sequence is required:
             (++) Configure and enable the EXTI Line 19 in interrupt mode and select the rising 
                  edge sensitivity using the EXTI_Init() function.
             (++) Configure and enable the TAMP_STAMP IRQ channel in the NVIC using the NVIC_Init()
                  function.
             (++) Configure the RTC to detect the RTC time-stamp event using the 
                  RTC_TimeStampCmd() functions.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  RTC_IT: specifies the RTC interrupt sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_TS:  Time Stamp interrupt mask
  *            @arg RTC_IT_WUT:  WakeUp Timer interrupt mask, available only for STM32F072 devices  
  *            @arg RTC_IT_ALRA:  Alarm A interrupt mask
  *            @arg RTC_IT_TAMP: Tamper event interrupt mask
  * @param  NewState: new state of the specified RTC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_CONFIG_IT(RTC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  if (NewState != DISABLE)
  {
    /* Configure the Interrupts in the RTC_CR register */
    RTC->CR |= (uint32_t)(RTC_IT & ~RTC_TAFCR_TAMPIE);
    /* Configure the Tamper Interrupt in the RTC_TAFCR */
    RTC->TAFCR |= (uint32_t)(RTC_IT & RTC_TAFCR_TAMPIE);
  }
  else
  {
    /* Configure the Interrupts in the RTC_CR register */
    RTC->CR &= (uint32_t)~(RTC_IT & (uint32_t)~RTC_TAFCR_TAMPIE);
    /* Configure the Tamper Interrupt in the RTC_TAFCR */
    RTC->TAFCR &= (uint32_t)~(RTC_IT & RTC_TAFCR_TAMPIE);
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF; 
}

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg RTC_FLAG_RECALPF: RECALPF event flag
  *            @arg RTC_FLAG_TAMP2F: Tamper 2 event flag   
  *            @arg RTC_FLAG_TAMP1F: Tamper 1 event flag
  *            @arg RTC_FLAG_TSOVF: Time Stamp OverFlow flag
  *            @arg RTC_FLAG_TSF: Time Stamp event flag
  *            @arg RTC_FLAG_WUTF: WakeUp Timer flag, available only for STM32F072 devices  
  *            @arg RTC_FLAG_ALRAF: Alarm A flag
  *            @arg RTC_FLAG_INITF: Initialization mode flag
  *            @arg RTC_FLAG_RSF: Registers Synchronized flag
  *            @arg RTC_FLAG_INITS: Registers Configured flag
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG));
  
  /* Get all the flags */
  tmpreg = (uint32_t)(RTC->ISR & RTC_FLAGS_MASK);
  
  /* Return the status of the flag */
  if ((tmpreg & RTC_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the RTC's pending flags.
  * @param  RTC_FLAG: specifies the RTC flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_FLAG_TAMP2F: Tamper 2 event flag
  *            @arg RTC_FLAG_TAMP1F: Tamper 1 event flag 
  *            @arg RTC_FLAG_TSOVF: Time Stamp Overflow flag 
  *            @arg RTC_FLAG_TSF: Time Stamp event flag
  *            @arg RTC_FLAG_WUTF: WakeUp Timer flag, available only for STM32F072 devices  
  *            @arg RTC_FLAG_ALRAF: Alarm A flag
  *            @arg RTC_FLAG_RSF: Registers Synchronized flag
  * @retval None
  */
void RTC_ClearFlag(uint32_t RTC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));

  /* Clear the Flags in the RTC_ISR register */
  RTC->ISR = (uint32_t)((uint32_t)(~((RTC_FLAG | RTC_ISR_INIT)& 0x0001FFFF) | (uint32_t)(RTC->ISR & RTC_ISR_INIT)));    
}

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTC_IT: specifies the RTC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg RTC_IT_TS: Time Stamp interrupt
  *            @arg RTC_IT_WUT: WakeUp Timer interrupt, available only for STM32F072 devices
  *            @arg RTC_IT_ALRA: Alarm A interrupt 
  *            @arg RTC_IT_TAMP1: Tamper1 event interrupt 
  *            @arg RTC_IT_TAMP2: Tamper2 event interrupt 
  * @retval The new state of RTC_IT (SET or RESET).
  */
ITStatus RTC_GetITStatus(uint32_t RTC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0, enablestatus = 0;
 
  /* Check the parameters */
  assert_param(IS_RTC_GET_IT(RTC_IT));
  
  /* Get the TAMPER Interrupt enable bit and pending bit */
  tmpreg = (uint32_t)(RTC->TAFCR & (RTC_TAFCR_TAMPIE));
 
  /* Get the Interrupt enable Status */
  enablestatus = (uint32_t)((RTC->CR & RTC_IT) | (tmpreg & ((RTC_IT >> (RTC_IT >> 18)) >> 15)));
  
  /* Get the Interrupt pending bit */
  tmpreg = (uint32_t)((RTC->ISR & (uint32_t)(RTC_IT >> 4)));
  
  /* Get the status of the Interrupt */
  if ((enablestatus != (uint32_t)RESET) && ((tmpreg & 0x0000FFFF) != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the RTC's interrupt pending bits.
  * @param  RTC_IT: specifies the RTC interrupt pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_TS: Time Stamp interrupt 
  *            @arg RTC_IT_WUT: WakeUp Timer interrupt, available only for STM32F072 devices
  *            @arg RTC_IT_ALRA: Alarm A interrupt 
  *            @arg RTC_IT_TAMP1: Tamper1 event interrupt
  *            @arg RTC_IT_TAMP2: Tamper2 event interrupt
  * @retval None
  */
void RTC_ClearITPendingBit(uint32_t RTC_IT)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_IT(RTC_IT));

  /* Get the RTC_ISR Interrupt pending bits mask */
  tmpreg = (uint32_t)(RTC_IT >> 4);

  /* Clear the interrupt pending bits in the RTC_ISR register */
  RTC->ISR = (uint32_t)((uint32_t)(~((tmpreg | RTC_ISR_INIT)& 0x0000FFFF) | (uint32_t)(RTC->ISR & RTC_ISR_INIT))); 
}

/**
  * @}
  */

/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  Value: Byte to be converted.
  * @retval Converted byte
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
  uint8_t bcdhigh = 0;
  
  while (Value >= 10)
  {
    bcdhigh++;
    Value -= 10;
  }
  
  return  ((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value: BCD value to be converted.
  * @retval Converted word
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
  uint8_t tmp = 0;
  tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (Value & (uint8_t)0x0F));
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  ******************************************************************************
  * @file    stm32f0xx_spi.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Serial peripheral interface (SPI):
  *           + Initialization and Configuration
  *           + Data transfers functions
  *           + Hardware CRC Calculation
  *           + DMA transfers management
  *           + Interrupts and flags management
  *
  *  @verbatim

 ===============================================================================
                       ##### How to use this driver #####
 ===============================================================================
    [..]
        (#) Enable peripheral clock using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE)
            function for SPI1 or using RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE)
            function for SPI2.
  
        (#) Enable SCK, MOSI, MISO and NSS GPIO clocks using 
            RCC_AHBPeriphClockCmd() function. 
  
        (#) Peripherals alternate function: 
            (++) Connect the pin to the desired peripherals' Alternate 
                 Function (AF) using GPIO_PinAFConfig() function.
            (++) Configure the desired pin in alternate function by:
                 GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
            (++) Select the type, pull-up/pull-down and output speed via 
                 GPIO_PuPd, GPIO_OType and GPIO_Speed members.
            (++) Call GPIO_Init() function.
  
        (#) Program the Polarity, Phase, First Data, Baud Rate Prescaler, Slave 
            Management, Peripheral Mode and CRC Polynomial values using the SPI_Init()
            function.In I2S mode, program the Mode, Standard, Data Format, MCLK 
            Output, Audio frequency and Polarity using I2S_Init() function.
  
        (#) Configure the FIFO threshold using SPI_RxFIFOThresholdConfig() to select 
            at which threshold the RXNE event is generated.
            
        (#) Enable the NVIC and the corresponding interrupt using the function 
            SPI_ITConfig() if you need to use interrupt mode. 
  
        (#) When using the DMA mode 
            (++) Configure the DMA using DMA_Init() function.
            (++) Active the needed channel Request using SPI_I2S_DMACmd() function.
   
        (#) Enable the SPI using the SPI_Cmd() function or enable the I2S using
            I2S_Cmd().
   
        (#) Enable the DMA using the DMA_Cmd() function when using DMA mode. 
  
        (#) Optionally, you can enable/configure the following parameters without
            re-initialization (i.e there is no need to call again SPI_Init() function):
            (++) When bidirectional mode (SPI_Direction_1Line_Rx or SPI_Direction_1Line_Tx)
                 is programmed as Data direction parameter using the SPI_Init() 
                 function it can be possible to switch between SPI_Direction_Tx 
                 or SPI_Direction_Rx using the SPI_BiDirectionalLineConfig() function.
            (++) When SPI_NSS_Soft is selected as Slave Select Management parameter 
                 using the SPI_Init() function it can be possible to manage the 
                 NSS internal signal using the SPI_NSSInternalSoftwareConfig() function.
            (++) Reconfigure the data size using the SPI_DataSizeConfig() function.
            (++) Enable or disable the SS output using the SPI_SSOutputCmd() function.  
  
        (#) To use the CRC Hardware calculation feature refer to the Peripheral 
            CRC hardware Calculation subsection.
  
    @endverbatim 
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup SPI
  * @brief SPI driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* SPI registers Masks */
#define CR1_CLEAR_MASK_SPI       ((uint16_t)0x3040)
#define CR1_CLEAR_MASK2_SPI      ((uint16_t)0xFFFB)
#define CR2_LDMA_MASK        ((uint16_t)0x9FFF)

#define I2SCFGR_CLEAR_Mask   ((uint16_t)0xF040)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SPI_Private_Functions
  * @{
  */

/** @defgroup SPI_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
           ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provides a set of functions allowing to initialize the SPI Direction,
         SPI Mode, SPI Data Size, SPI Polarity, SPI Phase, SPI NSS Management, SPI Baud
         Rate Prescaler, SPI First Bit and SPI CRC Polynomial.

    [..] The SPI_Init() function follows the SPI configuration procedures for Master mode
         and Slave mode (details for these procedures are available in reference manual).
         
    [..] When the Software NSS management (SPI_InitStruct->SPI_NSS = SPI_NSS_Soft) is selected,
         use the following function to manage the NSS bit:
         void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);

    [..] In Master mode, when the Hardware NSS management (SPI_InitStruct->SPI_NSS = SPI_NSS_Hard)
         is selected, use the follwoing function to enable the NSS output feature.
         void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);

    [..] The NSS pulse mode can be managed by the SPI TI mode when enabling it using the following function:
         void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
         And it can be managed by software in the SPI Motorola mode using this function: 
         void SPI_NSSPulseModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);

    [..] This section provides also functions to initialize the I2S Mode, Standard, 
         Data Format, MCLK Output, Audio frequency and Polarity.
  
    [..] The I2S_Init() function follows the I2S configuration procedures for Master mode
         and Slave mode.
  
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the SPIx peripheral registers to their default
  *         reset values.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  *         I2S mode is not supported for STM32F030 devices.      
  * @retval None
  */
void SPI_I2S_DeInit(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if (SPIx == SPI1)
  {
    /* Enable SPI1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
    /* Release SPI1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
  }
  else
  {
    if (SPIx == SPI2)
    {
      /* Enable SPI2 reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
      /* Release SPI2 from reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
    }
  }
}

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
/*--------------- Reset SPI init structure parameters values -----------------*/
  /* Initialize the SPI_Direction member */
  SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  /* Initialize the SPI_Mode member */
  SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
  /* Initialize the SPI_DataSize member */
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
  /* Initialize the SPI_CPOL member */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  /* Initialize the SPI_CPHA member */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  /* Initialize the SPI_NSS member */
  SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
  /* Initialize the SPI_BaudRatePrescaler member */
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  /* Initialize the SPI_FirstBit member */
  SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
  /* Initialize the SPI_CRCPolynomial member */
  SPI_InitStruct->SPI_CRCPolynomial = 7;
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *         parameters in the SPI_InitStruct.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices. 
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
  *         contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  uint16_t tmpreg = 0;

  /* check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Check the SPI parameters */
  assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_DATA_SIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));

  /*---------------------------- SPIx CR1 Configuration ------------------------*/
  /* Get the SPIx CR1 value */
  tmpreg = SPIx->CR1;
  /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, CPOL and CPHA bits */
  tmpreg &= CR1_CLEAR_MASK_SPI;
  /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
  master/slave mode, CPOL and CPHA */
  /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
  /* Set SSM, SSI bit according to SPI_NSS values */
  /* Set LSBFirst bit according to SPI_FirstBit value */
  /* Set BR bits according to SPI_BaudRatePrescaler value */
  /* Set CPOL bit according to SPI_CPOL value */
  /* Set CPHA bit according to SPI_CPHA value */
  tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_FirstBit |
                      SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_CPHA |
                      SPI_InitStruct->SPI_NSS | SPI_InitStruct->SPI_BaudRatePrescaler);  
  /* Write to SPIx CR1 */
  SPIx->CR1 = tmpreg;
  /*-------------------------Data Size Configuration -----------------------*/
  /* Get the SPIx CR2 value */
  tmpreg = SPIx->CR2;
  /* Clear DS[3:0] bits */
  tmpreg &=(uint16_t)~SPI_CR2_DS;
  /* Configure SPIx: Data Size */
  tmpreg |= (uint16_t)(SPI_InitStruct->SPI_DataSize);
  /* Write to SPIx CR2 */
  SPIx->CR2 = tmpreg;
  
  /*---------------------------- SPIx CRCPOLY Configuration --------------------*/
  /* Write to SPIx CRCPOLY */
  SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
  
  /*---------------------------- SPIx CR1 Configuration ------------------------*/
  /* Get the SPIx CR1 value */
  tmpreg = SPIx->CR1;
  /* Clear MSTR bit */
  tmpreg &= CR1_CLEAR_MASK2_SPI;
  /* Configure SPIx: master/slave mode */  
  /* Set MSTR bit according to SPI_Mode */
  tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_Mode);  
  /* Write to SPIx CR1 */
  SPIx->CR1 = tmpreg;  
  
  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
  SPIx->I2SCFGR &= (uint16_t)~((uint16_t)SPI_I2SCFGR_I2SMOD);
}

/**
  * @brief  Fills each I2S_InitStruct member with its default value.
  * @note   This mode is not supported for STM32F030 devices.  
  * @param  I2S_InitStruct: pointer to a I2S_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct)
{
/*--------------- Reset I2S init structure parameters values -----------------*/
  /* Initialize the I2S_Mode member */
  I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;

  /* Initialize the I2S_Standard member */
  I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;

  /* Initialize the I2S_DataFormat member */
  I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;

  /* Initialize the I2S_MCLKOutput member */
  I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;

  /* Initialize the I2S_AudioFreq member */
  I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;

  /* Initialize the I2S_CPOL member */
  I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *         parameters in the I2S_InitStruct.
  * @note   This mode is not supported for STM32F030 devices.  
  * @param  SPIx: where x can be 1 to select the SPI peripheral (configured in I2S mode).  
  * @param  I2S_InitStruct: pointer to an I2S_InitTypeDef structure that
  *         contains the configuration information for the specified SPI peripheral
  *         configured in I2S mode.
  * @note   This function calculates the optimal prescaler needed to obtain the most 
  *         accurate audio frequency (depending on the I2S clock source, the PLL values 
  *         and the product configuration). But in case the prescaler value is greater 
  *         than 511, the default value (0x02) will be configured instead.
  * @retval None
  */
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct)
{
  uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  uint32_t tmp = 0;
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t sourceclock = 0;

  /* Check the I2S parameters */
  assert_param(IS_SPI_1_PERIPH(SPIx));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

/*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  SPIx->I2SCFGR &= I2SCFGR_CLEAR_Mask; 
  SPIx->I2SPR = 0x0002;

  /* Get the I2SCFGR register value */
  tmpreg = SPIx->I2SCFGR;

  /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
  if(I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default)
  {
    i2sodd = (uint16_t)0;
    i2sdiv = (uint16_t)2;   
  }
  /* If the requested audio frequency is not the default, compute the prescaler */
  else
  {
    /* Check the frame length (For the Prescaler computing) */
    if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b)
    {
      /* Packet length is 16 bits */
      packetlength = 1;
    }
    else
    {
      /* Packet length is 32 bits */
      packetlength = 2;
    }

    /* I2S Clock source is System clock: Get System Clock frequency */
    RCC_GetClocksFreq(&RCC_Clocks);      

    /* Get the source clock value: based on System Clock value */
    sourceclock = RCC_Clocks.SYSCLK_Frequency;    

    /* Compute the Real divider depending on the MCLK output state with a floating point */
    if(I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable)
    {
      /* MCLK output is enabled */
      tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    else
    {
      /* MCLK output is disabled */
      tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) *10 ) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    
    /* Remove the floating point */
    tmp = tmp / 10;

    /* Check the parity of the divider */
    i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

    /* Compute the i2sdiv prescaler */
    i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

    /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
    i2sodd = (uint16_t) (i2sodd << 8);
  }

  /* Test if the divider is 1 or 0 or greater than 0xFF */
  if ((i2sdiv < 2) || (i2sdiv > 0xFF))
  {
    /* Set the default values */
    i2sdiv = 2;
    i2sodd = 0;
  }

  /* Write to SPIx I2SPR register the computed value */
  SPIx->I2SPR = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOutput));

  /* Configure the I2S with the SPI_InitStruct values */
  tmpreg |= (uint16_t)(SPI_I2SCFGR_I2SMOD | (uint16_t)(I2S_InitStruct->I2S_Mode | \
                  (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                  (uint16_t)I2S_InitStruct->I2S_CPOL))));

  /* Write to SPIx I2SCFGR */
  SPIx->I2SCFGR = tmpreg;
}

/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  * @param  NewState: new state of the SPIx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral */
    SPIx->CR1 |= SPI_CR1_SPE;
  }
  else
  {
    /* Disable the selected SPI peripheral */
    SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_SPE);
  }
}

/**
  * @brief  Enables or disables the TI Mode.
  *   
  * @note   This function can be called only after the SPI_Init() function has 
  *         been called. 
  * @note   When TI mode is selected, the control bits SSM, SSI, CPOL and CPHA 
  *         are not taken into consideration and are configured by hardware 
  *         respectively to the TI mode requirements.
  *    
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  * @param  NewState: new state of the selected SPI TI communication mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TI mode for the selected SPI peripheral */
    SPIx->CR2 |= SPI_CR2_FRF;
  }
  else
  {
    /* Disable the TI mode for the selected SPI peripheral */
    SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_FRF);
  }
}

/**
  * @brief  Enables or disables the specified SPI peripheral (in I2S mode).
  * @note   This mode is not supported for STM32F030 devices.    
  * @param  SPIx: where x can be 1 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_1_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral in I2S mode */
    SPIx->I2SCFGR |= SPI_I2SCFGR_I2SE;
  }
  else
  {
    /* Disable the selected SPI peripheral in I2S mode */
    SPIx->I2SCFGR &= (uint16_t)~((uint16_t)SPI_I2SCFGR_I2SE);
  }
}

/**
  * @brief  Configures the data size for the selected SPI.
  * @param  SPIx: where x can be 1 or 2  to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices. 
  * @param  SPI_DataSize: specifies the SPI data size.
  *         For the SPIx peripheral this parameter can be one of the following values:
  *            @arg SPI_DataSize_4b: Set data size to 4 bits
  *            @arg SPI_DataSize_5b: Set data size to 5 bits
  *            @arg SPI_DataSize_6b: Set data size to 6 bits
  *            @arg SPI_DataSize_7b: Set data size to 7 bits
  *            @arg SPI_DataSize_8b: Set data size to 8 bits
  *            @arg SPI_DataSize_9b: Set data size to 9 bits
  *            @arg SPI_DataSize_10b: Set data size to 10 bits
  *            @arg SPI_DataSize_11b: Set data size to 11 bits
  *            @arg SPI_DataSize_12b: Set data size to 12 bits
  *            @arg SPI_DataSize_13b: Set data size to 13 bits
  *            @arg SPI_DataSize_14b: Set data size to 14 bits
  *            @arg SPI_DataSize_15b: Set data size to 15 bits
  *            @arg SPI_DataSize_16b: Set data size to 16 bits
  * @retval None
  */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize)
{
  uint16_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DATA_SIZE(SPI_DataSize));
  /* Read the CR2 register */
  tmpreg = SPIx->CR2;
  /* Clear DS[3:0] bits */
  tmpreg &= (uint16_t)~SPI_CR2_DS;
  /* Set new DS[3:0] bits value */
  tmpreg |= SPI_DataSize;
  SPIx->CR2 = tmpreg;
}

/**
  * @brief  Configures the FIFO reception threshold for the selected SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices. 
  * @param  SPI_RxFIFOThreshold: specifies the FIFO reception threshold.
  *          This parameter can be one of the following values:
  *            @arg SPI_RxFIFOThreshold_HF: RXNE event is generated if the FIFO 
  *                                         level is greater or equal to 1/2. 
  *            @arg SPI_RxFIFOThreshold_QF: RXNE event is generated if the FIFO 
  *                                         level is greater or equal to 1/4. 
  * @retval None
  */
void SPI_RxFIFOThresholdConfig(SPI_TypeDef* SPIx, uint16_t SPI_RxFIFOThreshold)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_RX_FIFO_THRESHOLD(SPI_RxFIFOThreshold));

  /* Clear FRXTH bit */
  SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_FRXTH);

  /* Set new FRXTH bit value */
  SPIx->CR2 |= SPI_RxFIFOThreshold;
}

/**
  * @brief  Selects the data transfer direction in bidirectional mode for the specified SPI.
  * @param  SPIx: where x can be 1 or 2  to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices. 
  * @param  SPI_Direction: specifies the data transfer direction in bidirectional mode. 
  *          This parameter can be one of the following values:
  *            @arg SPI_Direction_Tx: Selects Tx transmission direction
  *            @arg SPI_Direction_Rx: Selects Rx receive direction
  * @retval None
  */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DIRECTION(SPI_Direction));
  if (SPI_Direction == SPI_Direction_Tx)
  {
    /* Set the Tx only mode */
    SPIx->CR1 |= SPI_Direction_Tx;
  }
  else
  {
    /* Set the Rx only mode */
    SPIx->CR1 &= SPI_Direction_Rx;
  }
}

/**
  * @brief  Configures internally by software the NSS pin for the selected SPI.
  * @note   This function can be called only after the SPI_Init() function has 
  *         been called.  
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.  
  * @param  SPI_NSSInternalSoft: specifies the SPI NSS internal state.
  *          This parameter can be one of the following values:
  *            @arg SPI_NSSInternalSoft_Set: Set NSS pin internally
  *            @arg SPI_NSSInternalSoft_Reset: Reset NSS pin internally
  * @retval None
  */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));

  if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
  {
    /* Set NSS pin internally by software */
    SPIx->CR1 |= SPI_NSSInternalSoft_Set;
  }
  else
  {
    /* Reset NSS pin internally by software */
    SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
  }
}

/**
  * @brief  Enables or disables the SS output for the selected SPI.
  * @note   This function can be called only after the SPI_Init() function has 
  *         been called and the NSS hardware management mode is selected. 
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.  
  * @param  NewState: new state of the SPIx SS output. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI SS output */
    SPIx->CR2 |= SPI_CR2_SSOE;
  }
  else
  {
    /* Disable the selected SPI SS output */
    SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_SSOE);
  }
}

/**
  * @brief  Enables or disables the NSS pulse management mode.
  * @note   This function can be called only after the SPI_Init() function has 
  *         been called. 
  * @note   When TI mode is selected, the control bits NSSP is not taken into 
  *         consideration and are configured by hardware respectively to the 
  *         TI mode requirements. 
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  * @param  NewState: new state of the NSS pulse management mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_NSSPulseModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the NSS pulse management mode */
    SPIx->CR2 |= SPI_CR2_NSSP;
  }
  else
  {
    /* Disable the NSS pulse management mode */
    SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_NSSP);    
  }
}

/**
  * @}
  */

/** @defgroup SPI_Group2 Data transfers functions
 *  @brief   Data transfers functions
 *
@verbatim
 ===============================================================================
                    ##### Data transfers functions #####
 ===============================================================================
    [..] This section provides a set of functions allowing to manage the SPI or I2S
         data transfers.

    [..] In reception, data are received and then stored into an internal Rx buffer while 
         In transmission, data are first stored into an internal Tx buffer before being 
         transmitted.

    [..] The read access of the SPI_DR register can be done using 
         SPI_ReceiveData8() (when data size is equal or inferior than 8bits) and.
         SPI_I2S_ReceiveData16() (when data size is superior than 8bits)function
         and returns the Rx buffered value. Whereas a write access to the SPI_DR 
         can be done using SPI_SendData8() (when data size is equal or inferior than 8bits)
         and SPI_I2S_SendData16() (when data size is superior than 8bits) function 
         and stores the written data into Tx buffer.

@endverbatim
  * @{
  */

/**
  * @brief  Transmits a Data through the SPIx/I2Sx peripheral.
  * @param  SPIx: where x can be 1 or 2 in SPI mode to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SPI_SendData8(SPI_TypeDef* SPIx, uint8_t Data)
{
  uint32_t spixbase = 0x00;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  spixbase = (uint32_t)SPIx; 
  spixbase += 0x0C;
  
  *(__IO uint8_t *) spixbase = Data;
}

/**
  * @brief  Transmits a Data through the SPIx/I2Sx peripheral.
  * @param  SPIx: where x can be 1 or 2 in SPI mode or 1 in I2S mode to select 
  *         the SPI peripheral. 
  * @note   SPI2 is not available for STM32F031 devices. 
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SPI_I2S_SendData16(SPI_TypeDef* SPIx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  SPIx->DR = (uint16_t)Data;
}

/**
  * @brief  Returns the most recent received data by the SPIx/I2Sx peripheral. 
  * @param  SPIx: where x can be 1 or 2 in SPI mode to select the SPI peripheral. 
  * @note   SPI2 is not available for STM32F031 devices.
  * @retval The value of the received data.
  */
uint8_t SPI_ReceiveData8(SPI_TypeDef* SPIx)
{
  uint32_t spixbase = 0x00;
  
  spixbase = (uint32_t)SPIx; 
  spixbase += 0x0C;
  
  return *(__IO uint8_t *) spixbase;
}

/**
  * @brief  Returns the most recent received data by the SPIx peripheral. 
  * @param  SPIx: where x can be 1 or 2 in SPI mode or 1 in I2S mode to select
  * @note   SPI2 is not available for STM32F031 devices.
  *         the SPI peripheral.  
  * @retval The value of the received data.
  */
uint16_t SPI_I2S_ReceiveData16(SPI_TypeDef* SPIx)
{
  return SPIx->DR;
}
/**
  * @}
  */

/** @defgroup SPI_Group3 Hardware CRC Calculation functions
 *  @brief   Hardware CRC Calculation functions
 *
@verbatim   
 ===============================================================================
                ##### Hardware CRC Calculation functions #####
 ===============================================================================
    [..] This section provides a set of functions allowing to manage the SPI CRC hardware 
         calculation.SPI communication using CRC is possible through the following procedure:

         (#) Program the Data direction, Polarity, Phase, First Data, Baud Rate Prescaler,
             Slave Management, Peripheral Mode and CRC Polynomial values using the SPI_Init()
             function.
         (#) Enable the CRC calculation using the SPI_CalculateCRC() function.
         (#) Enable the SPI using the SPI_Cmd() function
         (#) Before writing the last data to the TX buffer, set the CRCNext bit using the 
             SPI_TransmitCRC() function to indicate that after transmission of the last 
             data, the CRC should be transmitted.
         (#) After transmitting the last data, the SPI transmits the CRC. The SPI_CR1_CRCNEXT
             bit is reset. The CRC is also received and compared against the SPI_RXCRCR 
             value. 
             If the value does not match, the SPI_FLAG_CRCERR flag is set and an interrupt
             can be generated when the SPI_I2S_IT_ERR interrupt is enabled.

    -@-
       (+@) It is advised to don't read the calculate CRC values during the communication.
       (+@) When the SPI is in slave mode, be careful to enable CRC calculation only
       when the clock is stable, that is, when the clock is in the steady state. 
       If not, a wrong CRC calculation may be done. In fact, the CRC is sensitive 
       to the SCK slave input clock as soon as CRCEN is set, and this, whatever 
       the value of the SPE bit.
       (+@) With high bitrate frequencies, be careful when transmitting the CRC.
       As the number of used CPU cycles has to be as low as possible in the CRC 
       transfer phase, it is forbidden to call software functions in the CRC 
       transmission sequence to avoid errors in the last data and CRC reception. 
       In fact, CRCNEXT bit has to be written before the end of the transmission/reception 
       of the last data.
       (+@) For high bit rate frequencies, it is advised to use the DMA mode to avoid the
       degradation of the SPI speed performance due to CPU accesses impacting the 
       SPI bandwidth.
       (+@) When the STM32F0xx are configured as slaves and the NSS hardware mode is 
       used, the NSS pin needs to be kept low between the data phase and the CRC 
       phase.
       (+@) When the SPI is configured in slave mode with the CRC feature enabled, CRC
       calculation takes place even if a high level is applied on the NSS pin. 
       This may happen for example in case of a multislave environment where the 
       communication master addresses slaves alternately.
       (+@) Between a slave deselection (high level on NSS) and a new slave selection
       (low level on NSS), the CRC value should be cleared on both master and slave
       sides in order to resynchronize the master and slave for their respective 
       CRC calculation.

    -@- To clear the CRC, follow the procedure below:
       (#@) Disable SPI using the SPI_Cmd() function
       (#@) Disable the CRC calculation using the SPI_CalculateCRC() function.
       (#@) Enable the CRC calculation using the SPI_CalculateCRC() function.
       (#@) Enable SPI using the SPI_Cmd() function.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the CRC calculation length for the selected SPI.
  * @note   This function can be called only after the SPI_Init() function has 
  *         been called.  
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.  
  * @param  SPI_CRCLength: specifies the SPI CRC calculation length.
  *          This parameter can be one of the following values:
  *            @arg SPI_CRCLength_8b: Set CRC Calculation to 8 bits
  *            @arg SPI_CRCLength_16b: Set CRC Calculation to 16 bits
  * @retval None
  */
void SPI_CRCLengthConfig(SPI_TypeDef* SPIx, uint16_t SPI_CRCLength)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC_LENGTH(SPI_CRCLength));

  /* Clear CRCL bit */
  SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_CRCL);

  /* Set new CRCL bit value */
  SPIx->CR1 |= SPI_CRCLength;
}

/**
  * @brief  Enables or disables the CRC value calculation of the transferred bytes.
  * @note   This function can be called only after the SPI_Init() function has 
  *         been called.   
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  * @param  NewState: new state of the SPIx CRC value calculation.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI CRC calculation */
    SPIx->CR1 |= SPI_CR1_CRCEN;
  }
  else
  {
    /* Disable the selected SPI CRC calculation */
    SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_CRCEN);
  }
}

/**
  * @brief  Transmit the SPIx CRC value.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices. 
  * @retval None
  */
void SPI_TransmitCRC(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Enable the selected SPI CRC transmission */
  SPIx->CR1 |= SPI_CR1_CRCNEXT;
}

/**
  * @brief  Returns the transmit or the receive CRC register value for the specified SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices. 
  * @param  SPI_CRC: specifies the CRC register to be read.
  *          This parameter can be one of the following values:
  *            @arg SPI_CRC_Tx: Selects Tx CRC register
  *            @arg SPI_CRC_Rx: Selects Rx CRC register
  * @retval The selected CRC register value..
  */
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC)
{
  uint16_t crcreg = 0;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC(SPI_CRC));

  if (SPI_CRC != SPI_CRC_Rx)
  {
    /* Get the Tx CRC register */
    crcreg = SPIx->TXCRCR;
  }
  else
  {
    /* Get the Rx CRC register */
    crcreg = SPIx->RXCRCR;
  }
  /* Return the selected CRC register */
  return crcreg;
}

/**
  * @brief  Returns the CRC Polynomial register value for the specified SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices. 
  * @retval The CRC Polynomial register value.
  */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Return the CRC polynomial register */
  return SPIx->CRCPR;
}

/**
  * @}
  */

/** @defgroup SPI_Group4 DMA transfers management functions
 *  @brief   DMA transfers management functions
  *
@verbatim   
 ===============================================================================
                ##### DMA transfers management functions #####
 ===============================================================================
    [..] This section provides two functions that can be used only in DMA mode.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the SPIx/I2Sx DMA interface.
  * @param  SPIx: where x can be 1 or 2 in SPI mode or 1 in I2S mode to select 
  *         the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  *         I2S mode is not supported for STM32F030 devices.  
  * @param  SPI_I2S_DMAReq: specifies the SPI DMA transfer request to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg SPI_I2S_DMAReq_Tx: Tx buffer DMA transfer request
  *            @arg SPI_I2S_DMAReq_Rx: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected SPI DMA transfer request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_DMA_REQ(SPI_I2S_DMAReq));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI DMA requests */
    SPIx->CR2 |= SPI_I2S_DMAReq;
  }
  else
  {
    /* Disable the selected SPI DMA requests */
    SPIx->CR2 &= (uint16_t)~SPI_I2S_DMAReq;
  }
}

/**
  * @brief  Configures the number of data to transfer type(Even/Odd) for the DMA
  *         last transfers and for the selected SPI.
  * @note   This function have a meaning only if DMA mode is selected and if 
  *         the packing mode is used (data length <= 8 and DMA transfer size halfword)  
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  * @param  SPI_LastDMATransfer: specifies the SPI last DMA transfers state.
  *          This parameter can be one of the following values:
  *            @arg SPI_LastDMATransfer_TxEvenRxEven: Number of data for transmission Even
  *                                                   and number of data for reception Even.
  *            @arg SPI_LastDMATransfer_TxOddRxEven: Number of data for transmission Odd
  *                                                  and number of data for reception Even.
  *            @arg SPI_LastDMATransfer_TxEvenRxOdd: Number of data for transmission Even
  *                                                  and number of data for reception Odd.
  *            @arg SPI_LastDMATransfer_TxOddRxOdd: Number of data for transmission Odd
  *                                                 and number of data for reception Odd.
  * @retval None
  */
void SPI_LastDMATransferCmd(SPI_TypeDef* SPIx, uint16_t SPI_LastDMATransfer)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_LAST_DMA_TRANSFER(SPI_LastDMATransfer));

  /* Clear LDMA_TX and LDMA_RX bits */
  SPIx->CR2 &= CR2_LDMA_MASK;

  /* Set new LDMA_TX and LDMA_RX bits value */
  SPIx->CR2 |= SPI_LastDMATransfer; 
}

/**
  * @}
  */

/** @defgroup SPI_Group5 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
  *
@verbatim   
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This section provides a set of functions allowing to configure the SPI/I2S Interrupts 
         sources and check or clear the flags or pending bits status.
         The user should identify which mode will be used in his application to manage 
         the communication: Polling mode, Interrupt mode or DMA mode. 

  *** Polling Mode ***
  ====================
    [..] In Polling Mode, the SPI/I2S communication can be managed by 9 flags:
        (#) SPI_I2S_FLAG_TXE : to indicate the status of the transmit buffer register
        (#) SPI_I2S_FLAG_RXNE : to indicate the status of the receive buffer register
        (#) SPI_I2S_FLAG_BSY : to indicate the state of the communication layer of the SPI.
        (#) SPI_FLAG_CRCERR : to indicate if a CRC Calculation error occur              
        (#) SPI_FLAG_MODF : to indicate if a Mode Fault error occur
        (#) SPI_I2S_FLAG_OVR : to indicate if an Overrun error occur
        (#) SPI_I2S_FLAG_FRE: to indicate a Frame Format error occurs.
        (#) I2S_FLAG_UDR: to indicate an Underrun error occurs.
        (#) I2S_FLAG_CHSIDE: to indicate Channel Side.

    [..]
        (@)Do not use the BSY flag to handle each data transmission or reception. It is better 
           to use the TXE and RXNE flags instead.

    [..] In this Mode it is advised to use the following functions:
        (+) FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
        (+) void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);

  *** Interrupt Mode ***
  ======================
    [..] In Interrupt Mode, the SPI/I2S communication can be managed by 3 interrupt sources
         and 5 pending bits: 
    [..] Pending Bits:
        (#) SPI_I2S_IT_TXE : to indicate the status of the transmit buffer register
        (#) SPI_I2S_IT_RXNE : to indicate the status of the receive buffer register
        (#) SPI_I2S_IT_OVR : to indicate if an Overrun error occur
        (#) I2S_IT_UDR : to indicate an Underrun Error occurs.
        (#) SPI_I2S_FLAG_FRE : to indicate a Frame Format error occurs.

    [..] Interrupt Source:
        (#) SPI_I2S_IT_TXE: specifies the interrupt source for the Tx buffer empty 
            interrupt.  
        (#) SPI_I2S_IT_RXNE : specifies the interrupt source for the Rx buffer not 
            empty interrupt.
        (#) SPI_I2S_IT_ERR : specifies the interrupt source for the errors interrupt.

    [..] In this Mode it is advised to use the following functions:
         (+) void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
         (+) ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);

  *** FIFO Status ***
  ===================
    [..] It is possible to monitor the FIFO status when a transfer is ongoing using the
         following function:
         (+) uint32_t SPI_GetFIFOStatus(uint8_t SPI_FIFO_Direction); 

  *** DMA Mode ***
  ================
    [..] In DMA Mode, the SPI communication can be managed by 2 DMA Channel 
         requests:
        (#) SPI_I2S_DMAReq_Tx: specifies the Tx buffer DMA transfer request.
        (#) SPI_I2S_DMAReq_Rx: specifies the Rx buffer DMA transfer request.

    [..] In this Mode it is advised to use the following function:
        (+) void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified SPI/I2S interrupts.
  * @param  SPIx: where x can be 1 or 2 in SPI mode or 1 in I2S mode to select 
  *         the SPI peripheral.  
  * @note   SPI2 is not available for STM32F031 devices.
  *         I2S mode is not supported for STM32F030 devices.  
  * @param  SPI_I2S_IT: specifies the SPI interrupt source to be enabled or disabled. 
  *          This parameter can be one of the following values:
  *            @arg SPI_I2S_IT_TXE: Tx buffer empty interrupt mask
  *            @arg SPI_I2S_IT_RXNE: Rx buffer not empty interrupt mask
  *            @arg SPI_I2S_IT_ERR: Error interrupt mask
  * @param  NewState: new state of the specified SPI interrupt.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState)
{
  uint16_t itpos = 0, itmask = 0 ;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_CONFIG_IT(SPI_I2S_IT));

  /* Get the SPI IT index */
  itpos = SPI_I2S_IT >> 4;

  /* Set the IT mask */
  itmask = (uint16_t)1 << (uint16_t)itpos;

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI interrupt */
    SPIx->CR2 |= itmask;
  }
  else
  {
    /* Disable the selected SPI interrupt */
    SPIx->CR2 &= (uint16_t)~itmask;
  }
}

/**
  * @brief  Returns the current SPIx Transmission FIFO filled level.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  * @retval The Transmission FIFO filling state.
  *          - SPI_TransmissionFIFOStatus_Empty: when FIFO is empty
  *          - SPI_TransmissionFIFOStatus_1QuarterFull: if more than 1 quarter-full.
  *          - SPI_TransmissionFIFOStatus_HalfFull: if more than 1 half-full.
  *          - SPI_TransmissionFIFOStatus_Full: when FIFO is full.
  */
uint16_t SPI_GetTransmissionFIFOStatus(SPI_TypeDef* SPIx)
{
  /* Get the SPIx Transmission FIFO level bits */
  return (uint16_t)((SPIx->SR & SPI_SR_FTLVL));
}

/**
  * @brief  Returns the current SPIx Reception FIFO filled level.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  * @retval The Reception FIFO filling state.
  *          - SPI_ReceptionFIFOStatus_Empty: when FIFO is empty
  *          - SPI_ReceptionFIFOStatus_1QuarterFull: if more than 1 quarter-full.
  *          - SPI_ReceptionFIFOStatus_HalfFull: if more than 1 half-full.
  *          - SPI_ReceptionFIFOStatus_Full: when FIFO is full.
  */
uint16_t SPI_GetReceptionFIFOStatus(SPI_TypeDef* SPIx)
{
  /* Get the SPIx Reception FIFO level bits */
  return (uint16_t)((SPIx->SR & SPI_SR_FRLVL));
}

/**
  * @brief  Checks whether the specified SPI flag is set or not.
  * @param  SPIx: where x can be 1 or 2 in SPI mode or 1 in I2S mode to select 
  *         the SPI peripheral.    
  * @note   SPI2 is not available for STM32F031 devices.
  *         I2S mode is not supported for STM32F030 devices.  
  * @param  SPI_I2S_FLAG: specifies the SPI flag to check. 
  *          This parameter can be one of the following values:
  *            @arg SPI_I2S_FLAG_TXE: Transmit buffer empty flag.
  *            @arg SPI_I2S_FLAG_RXNE: Receive buffer not empty flag.
  *            @arg SPI_I2S_FLAG_BSY: Busy flag.
  *            @arg SPI_I2S_FLAG_OVR: Overrun flag.
  *            @arg SPI_FLAG_MODF: Mode Fault flag.
  *            @arg SPI_FLAG_CRCERR: CRC Error flag.
  *            @arg SPI_I2S_FLAG_FRE: TI frame format error flag.
  *            @arg I2S_FLAG_UDR: Underrun Error flag.
  *            @arg I2S_FLAG_CHSIDE: Channel Side flag.   
  * @retval The new state of SPI_I2S_FLAG (SET or RESET).
  */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));

  /* Check the status of the specified SPI flag */
  if ((SPIx->SR & SPI_I2S_FLAG) != (uint16_t)RESET)
  {
    /* SPI_I2S_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the SPIx CRC Error (CRCERR) flag.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @note   SPI2 is not available for STM32F031 devices.
  *         I2S mode is not supported for STM32F030 devices.  
  * @param  SPI_I2S_FLAG: specifies the SPI flag to clear. 
  *         This function clears only CRCERR flag.
  * @note   OVR (OverRun error) flag is cleared by software sequence: a read 
  *         operation to SPI_DR register (SPI_I2S_ReceiveData()) followed by  
  *         a read operation to SPI_SR register (SPI_I2S_GetFlagStatus()).
  * @note   MODF (Mode Fault) flag is cleared by software sequence: a read/write 
  *         operation to SPI_SR register (SPI_I2S_GetFlagStatus()) followed by
  *         a write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
  * @retval None
  */
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CLEAR_FLAG(SPI_I2S_FLAG));

  /* Clear the selected SPI CRC Error (CRCERR) flag */
  SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}

/**
  * @brief  Checks whether the specified SPI/I2S interrupt has occurred or not.
  * @param  SPIx: where x can be 1 or 2 in SPI mode or 1 in I2S mode to select 
  *         the SPI peripheral.
  * @param  SPI_I2S_IT: specifies the SPI interrupt source to check. 
  *          This parameter can be one of the following values:
  *            @arg SPI_I2S_IT_TXE: Transmit buffer empty interrupt.
  *            @arg SPI_I2S_IT_RXNE: Receive buffer not empty interrupt.
  *            @arg SPI_IT_MODF: Mode Fault interrupt.
  *            @arg SPI_I2S_IT_OVR: Overrun interrupt.
  *            @arg I2S_IT_UDR: Underrun interrupt.  
  *            @arg SPI_I2S_IT_FRE: Format Error interrupt.  
  * @retval The new state of SPI_I2S_IT (SET or RESET).
  */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)
{
  ITStatus bitstatus = RESET;
  uint16_t itpos = 0, itmask = 0, enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_IT(SPI_I2S_IT));

  /* Get the SPI_I2S_IT index */
  itpos = 0x01 << (SPI_I2S_IT & 0x0F);

  /* Get the SPI_I2S_IT IT mask */
  itmask = SPI_I2S_IT >> 4;

  /* Set the IT mask */
  itmask = 0x01 << itmask;

  /* Get the SPI_I2S_IT enable bit status */
  enablestatus = (SPIx->CR2 & itmask) ;

  /* Check the status of the specified SPI interrupt */
  if (((SPIx->SR & itpos) != (uint16_t)RESET) && enablestatus)
  {
    /* SPI_I2S_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_IT is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_IT status */
  return bitstatus;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_syscfg.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the SYSCFG peripheral:
  *           + Remapping the memory mapped at 0x00000000  
  *           + Remapping the DMA channels
  *           + Enabling I2C fast mode plus driving capability for I2C pins   
  *           + Configuring the EXTI lines connection to the GPIO port
  *           + Configuring the CFGR2 features (Connecting some internal signal
  *             to the break input of TIM1)
  *   
  *  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..] 
               The SYSCFG registers can be accessed only when the SYSCFG 
               interface APB clock is enabled.
               To enable SYSCFG APB clock use:
               RCC_APBPeriphClockCmd(RCC_APBPeriph_SYSCFG, ENABLE).
  *  @endverbatim
  *
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup SYSCFG 
  * @brief SYSCFG driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Functions
  * @{
  */ 

/** @defgroup SYSCFG_Group1 SYSCFG Initialization and Configuration functions
 *  @brief   SYSCFG Initialization and Configuration functions 
 *
@verbatim
 ===============================================================================
        ##### SYSCFG Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the SYSCFG registers to their default reset values.
  * @param  None
  * @retval None
  * @note   MEM_MODE bits are not affected by APB reset.
  * @note   MEM_MODE bits took the value from the user option bytes.
  * @note   CFGR2 register is not affected by APB reset.
  * @note   CLABBB configuration bits are locked when set.
  * @note   To unlock the configuration, perform a system reset.
  */
void SYSCFG_DeInit(void)
{
  /* Set SYSCFG_CFGR1 register to reset value without affecting MEM_MODE bits */
  SYSCFG->CFGR1 &= SYSCFG_CFGR1_MEM_MODE;
  /* Set EXTICRx registers to reset value */
  SYSCFG->EXTICR[0] = 0;
  SYSCFG->EXTICR[1] = 0;
  SYSCFG->EXTICR[2] = 0;
  SYSCFG->EXTICR[3] = 0;
  /* Set CFGR2 register to reset value: clear SRAM parity error flag */
  SYSCFG->CFGR2 |= (uint32_t) SYSCFG_CFGR2_SRAM_PE;
}

/**
  * @brief  Configures the memory mapping at address 0x00000000.
  * @param  SYSCFG_MemoryRemap: selects the memory remapping.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000  
  *            @arg SYSCFG_MemoryRemap_SystemMemory: System Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM mapped at 0x00000000
  * @retval None
  */
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap)
{
  uint32_t tmpctrl = 0;

  /* Check the parameter */
  assert_param(IS_SYSCFG_MEMORY_REMAP(SYSCFG_MemoryRemap));

  /* Get CFGR1 register value */
  tmpctrl = SYSCFG->CFGR1;

  /* Clear MEM_MODE bits */
  tmpctrl &= (uint32_t) (~SYSCFG_CFGR1_MEM_MODE);

  /* Set the new MEM_MODE bits value */
  tmpctrl |= (uint32_t) SYSCFG_MemoryRemap;

  /* Set CFGR1 register with the new memory remap configuration */
  SYSCFG->CFGR1 = tmpctrl;
}

/**
  * @brief  Configure the DMA channels remapping.
  * @param  SYSCFG_DMARemap: selects the DMA channels remap.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_DMARemap_TIM17: Remap TIM17 DMA requests from channel1 to channel2
  *            @arg SYSCFG_DMARemap_TIM16: Remap TIM16 DMA requests from channel3 to channel4
  *            @arg SYSCFG_DMARemap_USART1Rx: Remap USART1 Rx DMA requests from channel3 to channel5
  *            @arg SYSCFG_DMARemap_USART1Tx: Remap USART1 Tx DMA requests from channel2 to channel4
  *            @arg SYSCFG_DMARemap_ADC1: Remap ADC1 DMA requests from channel1 to channel2
  * @param  NewState: new state of the DMA channel remapping. 
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, DMA channel of the selected peripheral is remapped
  * @note   When disabled, Default DMA channel is mapped to the selected peripheral
  * @note   By default TIM17 DMA requests is mapped to channel 1, 
  *         use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Enable) to remap
  *         TIM17 DMA requests to channel 2 and use
  *         SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Disable) to map
  *         TIM17 DMA requests to channel 1 (default mapping)
  * @note   This function is only used for STM32F030, STM32F031, STM32F042, STM32F072 and STM32F051 devices.   
  * @retval None
  */
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_DMA_REMAP(SYSCFG_DMARemap));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Remap the DMA channel */
    SYSCFG->CFGR1 |= (uint32_t)SYSCFG_DMARemap;
  }
  else
  {
    /* use the default DMA channel mapping */
    SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_DMARemap);
  }
}

/**
  * @brief  Configure the I2C fast mode plus driving capability.
  * @param  SYSCFG_I2CFastModePlus: selects the pin.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_I2CFastModePlus_PB6: Configure fast mode plus driving capability for PB6
  *            @arg SYSCFG_I2CFastModePlus_PB7: Configure fast mode plus driving capability for PB7
  *            @arg SYSCFG_I2CFastModePlus_PB8: Configure fast mode plus driving capability for PB8
  *            @arg SYSCFG_I2CFastModePlus_PB9: Configure fast mode plus driving capability for PB9
  *            @arg SYSCFG_I2CFastModePlus_PA9: Configure fast mode plus driving capability for PA9 (only for STM32F031 and STM32F030 devices)
  *            @arg SYSCFG_I2CFastModePlus_PA10: Configure fast mode plus driving capability for PA10 (only for STM32F031 and STM32F030 devices)
  *            @arg SYSCFG_I2CFastModePlus_I2C1: Configure fast mode plus driving capability for PB10, PB11, PF6 and PF7(only for STM32F031 and STM32F030 devices)
  *            @arg SYSCFG_I2CFastModePlus_I2C2: Configure fast mode plus driving capability for I2C2 pins, available only for STM32F072 devices
  *                
  * @param  NewState: new state of the DMA channel remapping. 
  *         This parameter can be:  ENABLE or DISABLE.
  * @note   ENABLE: Enable fast mode plus driving capability for selected I2C pin
  * @note   DISABLE: Disable fast mode plus driving capability for selected I2C pin
  * @note  For I2C1, fast mode plus driving capability can be enabled on all selected
  *        I2C1 pins using SYSCFG_I2CFastModePlus_I2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaining I2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be enabled only by using SYSCFG_I2CFastModePlus_I2C1 parameter.
  * @note  For all I2C2 pins fast mode plus driving capability can be enabled
  *        only by using SYSCFG_I2CFastModePlus_I2C2 parameter.
  * @retval None
  */
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_I2C_FMP(SYSCFG_I2CFastModePlus));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable fast mode plus driving capability for selected pin */
    SYSCFG->CFGR1 |= (uint32_t)SYSCFG_I2CFastModePlus;
  }
  else
  {
    /* Disable fast mode plus driving capability for selected pin */
    SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_I2CFastModePlus);
  }
}

/** @brief  select the modulation envelope source 
  * @param SYSCFG_IRDAEnv: select the envelope source. 
  *        This parameter can be a value 
  *            @arg SYSCFG_IRDA_ENV_SEL_TIM16
  *            @arg SYSCFG_IRDA_ENV_SEL_USART1
  *            @arg SYSCFG_IRDA_ENV_SEL_USART4
  * @retval None      
  */
void SYSCFG_IRDAEnvSelection(uint32_t SYSCFG_IRDAEnv)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_IRDA_ENV(SYSCFG_IRDAEnv));
  
  SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_IRDA_ENV_SEL);
  SYSCFG->CFGR1 |= (SYSCFG_IRDAEnv);
}

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx: selects the GPIO port to be used as source 
  *                               for EXTI lines where x can be (A, B, C, D, E or F).
  * @note   GPIOE is available only for STM32F072.
  * @note   GPIOD is not available for STM32F031.    
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  * @note   This parameter can be EXTI_PinSourcex where x can be:
  *         For STM32F051 and STM32F030: (0..15) for GPIOA, GPIOB, GPIOC, (2) for GPIOD and (0..1, 4..7) for GIIOF.
  *         For STM32F072: (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..10) for GPIOF.
  *         For STM32F031: (0..15) for GPIOA, GPIOB, (13..15) for GPIOC and (0..1, 6..7) for GPIOF.
  * @retval None
  */
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
{
  uint32_t tmp = 0x00;

  /* Check the parameters */
  assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
  assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));
  
  tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
}

/**
  * @brief  check ISR wrapper: Allow to determine interrupt source per line .
  * @param  IT_Source: specifies the interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ITLINE_EWDG                       EWDG has expired 
  *            @arg ITLINE_PVDOUT                     Power voltage detection Interrupt 
  *            @arg ITLINE_VDDIO2                     VDDIO2 Interrupt
  *            @arg ITLINE_RTC_WAKEUP                 RTC WAKEUP -> exti[20] Interrupt 
  *            @arg ITLINE_RTC_TSTAMP                 RTC Time Stamp -> exti[19] interrupt 
  *            @arg ITLINE_RTC_ALRA                   RTC Alarm -> exti[17] interrupt
  *            @arg ITLINE_FLASH_ITF                  Flash ITF Interrupt
  *            @arg ITLINE_CRS                        CRS Interrupt 
  *            @arg ITLINE_CLK_CTRL                   CLK Control Interrupt 
  *            @arg ITLINE_EXTI0                      External Interrupt 0 
  *            @arg ITLINE_EXTI1                      External Interrupt 1 
  *            @arg ITLINE_EXTI2                      External Interrupt 2 
  *            @arg ITLINE_EXTI3                      External Interrupt 3 
  *            @arg ITLINE_EXTI4                      External Interrupt 4 
  *            @arg ITLINE_EXTI5                      External Interrupt 5 
  *            @arg ITLINE_EXTI6                      External Interrupt 6 
  *            @arg ITLINE_EXTI7                      External Interrupt 7 
  *            @arg ITLINE_EXTI8                      External Interrupt 8 
  *            @arg ITLINE_EXTI9                      External Interrupt 9 
  *            @arg ITLINE_EXTI10                     External Interrupt 10 
  *            @arg ITLINE_EXTI11                     External Interrupt 11 
  *            @arg ITLINE_EXTI12                     External Interrupt 12 
  *            @arg ITLINE_EXTI13                     External Interrupt 13 
  *            @arg ITLINE_EXTI14                     External Interrupt 14 
  *            @arg ITLINE_EXTI15                     External Interrupt 15 
  *            @arg ITLINE_TSC_EOA                    Touch control EOA Interrupt 
  *            @arg ITLINE_TSC_MCE                    Touch control MCE Interrupt 
  *            @arg ITLINE_DMA1_CH1                   DMA1 Channel 1 Interrupt 
  *            @arg ITLINE_DMA1_CH2                   DMA1 Channel 2 Interrupt 
  *            @arg ITLINE_DMA1_CH3                   DMA1 Channel 3 Interrupt 
  *            @arg ITLINE_DMA2_CH1                   DMA2 Channel 1 Interrupt 
  *            @arg ITLINE_DMA2_CH2                   DMA2 Channel 2 Interrupt 
  *            @arg ITLINE_DMA1_CH4                   DMA1 Channel 4 Interrupt  
  *            @arg ITLINE_DMA1_CH5                   DMA1 Channel 5 Interrupt 
  *            @arg ITLINE_DMA1_CH6                   DMA1 Channel 6 Interrupt 
  *            @arg ITLINE_DMA1_CH7                   DMA1 Channel 7 Interrupt 
  *            @arg ITLINE_DMA2_CH3                   DMA2 Channel 3 Interrupt 
  *            @arg ITLINE_DMA2_CH4                   DMA2 Channel 4 Interrupt 
  *            @arg ITLINE_DMA2_CH5                   DMA2 Channel 5 Interrupt 
  *            @arg ITLINE_ADC                        ADC Interrupt 
  *            @arg ITLINE_COMP1                      COMP1 Interrupt -> exti[21] 
  *            @arg ITLINE_COMP2                      COMP2 Interrupt -> exti[21] 
  *            @arg ITLINE_TIM1_BRK                   TIM1 BRK Interrupt 
  *            @arg ITLINE_TIM1_UPD                   TIM1 UPD Interrupt 
  *            @arg ITLINE_TIM1_TRG                   TIM1 TRG Interrupt 
  *            @arg ITLINE_TIM1_CCU                   TIM1 CCU Interrupt 
  *            @arg ITLINE_TIM1_CC                    TIM1 CC Interrupt 
  *            @arg ITLINE_TIM2                       TIM2 Interrupt 
  *            @arg ITLINE_TIM3                       TIM3 Interrupt 
  *            @arg ITLINE_DAC                        DAC Interrupt 
  *            @arg ITLINE_TIM6                       TIM6 Interrupt 
  *            @arg ITLINE_TIM7                       TIM7 Interrupt 
  *            @arg ITLINE_TIM14                      TIM14 Interrupt 
  *            @arg ITLINE_TIM15                      TIM15 Interrupt 
  *            @arg ITLINE_TIM16                      TIM16 Interrupt 
  *            @arg ITLINE_TIM17                      TIM17 Interrupt 
  *            @arg ITLINE_I2C1                       I2C1 Interrupt -> exti[23] 
  *            @arg ITLINE_I2C2                       I2C2 Interrupt 
  *            @arg ITLINE_SPI1                       I2C1 Interrupt -> exti[23] 
  *            @arg ITLINE_SPI2                       SPI1 Interrupt 
  *            @arg ITLINE_USART1                     USART1 GLB Interrupt -> exti[25] 
  *            @arg ITLINE_USART2                     USART2 GLB Interrupt -> exti[26] 
  *            @arg ITLINE_USART3                     USART3 Interrupt 
  *            @arg ITLINE_USART4                     USART4 Interrupt 
  *            @arg ITLINE_USART5                     USART5 Interrupt 
  *            @arg ITLINE_USART6                     USART6 Interrupt 
  *            @arg ITLINE_USART7                     USART7 Interrupt 
  *            @arg ITLINE_USART8                     USART8 Interrupt 
  *            @arg ITLINE_CAN                        CAN Interrupt 
  *            @arg ITLINE_CEC                        CEC Interrupt 
  * @retval The new state of IT_LINE_SR.
  */
uint32_t  SYSCFG_GetPendingIT(uint32_t ITSourceLine)
{
   assert_param(IS_SYSCFG_ITLINE(ITSourceLine));
   return(SYSCFG->IT_LINE_SR[(ITSourceLine >> 0x18)] & (ITSourceLine & 0x00FFFFFF));
}

/**
  * @brief  Connect the selected parameter to the break input of TIM1.
  * @note   The selected configuration is locked and can be unlocked by system reset
  * @param  SYSCFG_Break: selects the configuration to be connected to break
  *         input of TIM1
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG_Break_PVD: Connects the PVD event to the Break Input of TIM1,, not available for  STM32F030 devices.
  *            @arg SYSCFG_Break_SRAMParity: Connects the SRAM_PARITY error signal to the Break Input of TIM1 .
  *            @arg SYSCFG_Break_Lockup: Connects Lockup output of CortexM0 to the break input of TIM1.
  * @retval None
  */
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_LOCK_CONFIG(SYSCFG_Break));

  SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Break;
}

/**
  * @brief  Checks whether the specified SYSCFG flag is set or not.
  * @param  SYSCFG_Flag: specifies the SYSCFG flag to check. 
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_FLAG_PE: SRAM parity error flag.
  * @retval The new state of SYSCFG_Flag (SET or RESET).
  */
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameter */
  assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));

  /* Check the status of the specified SPI flag */
  if ((SYSCFG->CFGR2 & SYSCFG_CFGR2_SRAM_PE) != (uint32_t)RESET)
  {
    /* SYSCFG_Flag is set */
    bitstatus = SET;
  }
  else
  {
    /* SYSCFG_Flag is reset */
    bitstatus = RESET;
  }
  /* Return the SYSCFG_Flag status */
  return  bitstatus;
}

/**
  * @brief  Clear the selected SYSCFG flag.
  * @param  SYSCFG_Flag: selects the flag to be cleared.
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG_FLAG_PE: SRAM parity error flag.
  * @retval None
  */
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));

  SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Flag;
}

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  ******************************************************************************
  * @file    stm32f0xx_tim.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the TIM peripheral:
  *            + TimeBase management
  *            + Output Compare management
  *            + Input Capture management
  *            + Interrupts, DMA and flags management
  *            + Clocks management
  *            + Synchronization management
  *            + Specific interface management
  *            + Specific remapping management      
  *              
  *  @verbatim
  
 ===============================================================================
                    ##### How to use this driver #####
 ===============================================================================
    [..] This driver provides functions to configure and program the TIM 
         of all STM32F0xx devices These functions are split in 8 groups: 
         (#) TIM TimeBase management: this group includes all needed functions 
             to configure the TM Timebase unit:
             (++) Set/Get Prescaler.
             (++) Set/Get Autoreload.
             (++) Counter modes configuration.
             (++) Set Clock division.
             (++) Select the One Pulse mode.
             (++) Update Request Configuration.
             (++) Update Disable Configuration.
             (++) Auto-Preload Configuration.
             (++) Enable/Disable the counter.
  
         (#) TIM Output Compare management: this group includes all needed 
             functions to configure the Capture/Compare unit used in Output 
             compare mode: 
             (++) Configure each channel, independently, in Output Compare mode.
             (++) Select the output compare modes.
             (++) Select the Polarities of each channel.
             (++) Set/Get the Capture/Compare register values.
             (++) Select the Output Compare Fast mode. 
             (++) Select the Output Compare Forced mode.  
             (++) Output Compare-Preload Configuration. 
             (++) Clear Output Compare Reference.
             (++) Select the OCREF Clear signal.
             (++) Enable/Disable the Capture/Compare Channels.    
  
         (#) TIM Input Capture management: this group includes all needed 
             functions to configure the Capture/Compare unit used in 
             Input Capture mode:
             (++) Configure each channel in input capture mode.
             (++) Configure Channel1/2 in PWM Input mode.
             (++) Set the Input Capture Prescaler.
             (++) Get the Capture/Compare values.  
             
        (#) Advanced-control timers (TIM1) specific features
            (++) Configures the Break input, dead time, Lock level, the OSSI,
                 the OSSR State and the AOE(automatic output enable)
            (++) Enable/Disable the TIM peripheral Main Outputs
            (++) Select the Commutation event
            (++) Set/Reset the Capture Compare Preload Control bit     
  
         (#) TIM interrupts, DMA and flags management.
             (++) Enable/Disable interrupt sources.
             (++) Get flags status.
             (++) Clear flags/ Pending bits.
             (++) Enable/Disable DMA requests. 
             (++) Configure DMA burst mode.
             (++) Select CaptureCompare DMA request.  
  
         (#) TIM clocks management: this group includes all needed functions 
             to configure the clock controller unit:
             (++) Select internal/External clock.
             (++) Select the external clock mode: ETR(Mode1/Mode2), TIx or ITRx.
  
         (#) TIM synchronization management: this group includes all needed. 
             functions to configure the Synchronization unit:
             (++) Select Input Trigger.  
             (++) Select Output Trigger.  
             (++) Select Master Slave Mode. 
             (++) ETR Configuration when used as external trigger.   
  
         (#) TIM specific interface management, this group includes all 
             needed functions to use the specific TIM interface:
             (++) Encoder Interface Configuration.
             (++) Select Hall Sensor.   
  
         (#) TIM specific remapping management includes the Remapping 
             configuration of specific timers
  
@endverbatim
  *    
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup TIM 
  * @brief TIM driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* ---------------------- TIM registers bit mask ------------------------ */
#define SMCR_ETR_MASK               ((uint16_t)0x00FF) 
#define CCMR_OFFSET                 ((uint16_t)0x0018)
#define CCER_CCE_SET                ((uint16_t)0x0001)
#define CCER_CCNE_SET               ((uint16_t)0x0004) 
  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI3_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI4_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
/* Private functions ---------------------------------------------------------*/

/** @defgroup TIM_Private_Functions
  * @{
  */

/** @defgroup TIM_Group1 TimeBase management functions
 *  @brief   TimeBase management functions 
 *
@verbatim
 ===============================================================================
                 ##### TimeBase management functions #####
 ===============================================================================
  
        *** TIM Driver: how to use it in Timing(Time base) Mode ***
 ===============================================================================
    [..] To use the Timer in Timing(Time base) mode, the following steps are 
         mandatory:
         (#) Enable TIM clock using 
             RCC_APBxPeriphClockCmd(RCC_APBxPeriph_TIMx, ENABLE) function.
         (#) Fill the TIM_TimeBaseInitStruct with the desired parameters.
         (#) Call TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct) to configure 
             the Time Base unit with the corresponding configuration.
         (#) Enable the NVIC if you need to generate the update interrupt. 
         (#) Enable the corresponding interrupt using the function 
             TIM_ITConfig(TIMx, TIM_IT_Update). 
         (#) Call the TIM_Cmd(ENABLE) function to enable the TIM counter.
    [..]
        (@) All other functions can be used seperatly to modify, if needed,
            a specific feature of the Timer. 

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the TIMx peripheral registers to their default reset values.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @retval None
  *   
  */
void TIM_DeInit(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 

  if (TIMx == TIM1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);  
  }     
  else if (TIMx == TIM2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
  }
  else if (TIMx == TIM3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
  }
  else if (TIMx == TIM6)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
  } 
  else if (TIMx == TIM7)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
  }
  else if (TIMx == TIM14) 
  {       
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, DISABLE);  
  }        
  else if (TIMx == TIM15)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, DISABLE);
  } 
  else if (TIMx == TIM16)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, DISABLE);
  } 
  else
  {
    if (TIMx == TIM17)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, DISABLE);
    }  
  }
     
}

/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM 
  *         peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for
  *         the specified TIM peripheral.
  * @retval None
  */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  uint16_t tmpcr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
  assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
  assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));

  tmpcr1 = TIMx->CR1;  

  if((TIMx == TIM1) || (TIMx == TIM2) || (TIMx == TIM3))
  {
    /* Select the Counter Mode */
    tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_CR1_DIR | TIM_CR1_CMS)));
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_CounterMode;
  }
 
  if(TIMx != TIM6)
  {
    /* Set the clock division */
    tmpcr1 &= (uint16_t)(~((uint16_t)TIM_CR1_CKD));
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision;
  }

  TIMx->CR1 = tmpcr1;

  /* Set the Autoreload value */
  TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;
 
  /* Set the Prescaler value */
  TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;
    
  if ((TIMx == TIM1) || (TIMx == TIM15)|| (TIMx == TIM16) || (TIMx == TIM17))  
  {
    /* Set the Repetition Counter value */
    TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
  }

  /* Generate an update event to reload the Prescaler and the Repetition counter
     values immediately */
  TIMx->EGR = TIM_PSCReloadMode_Immediate;           
}

/**
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  /* Set the default configuration */
  TIM_TimeBaseInitStruct->TIM_Period = 0xFFFFFFFF;
  TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
  TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

/**
  * @brief  Configures the TIMx Prescaler.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @param  Prescaler: specifies the Prescaler Register value
  * @param  TIM_PSCReloadMode: specifies the TIM Prescaler Reload mode
  *          This parameter can be one of the following values:
  *            @arg TIM_PSCReloadMode_Update: The Prescaler is loaded at the update event.
  *            @arg TIM_PSCReloadMode_Immediate: The Prescaler is loaded immediatly.
  * @retval None
  */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));
  
  /* Set the Prescaler value */
  TIMx->PSC = Prescaler;
  /* Set or reset the UG Bit */
  TIMx->EGR = TIM_PSCReloadMode;
}

/**
  * @brief  Specifies the TIMx Counter Mode to be used.
  * @param  TIMx: where x can be 1, 2, or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_CounterMode: specifies the Counter Mode to be used
  *          This parameter can be one of the following values:
  *            @arg TIM_CounterMode_Up: TIM Up Counting Mode
  *            @arg TIM_CounterMode_Down: TIM Down Counting Mode
  *            @arg TIM_CounterMode_CenterAligned1: TIM Center Aligned Mode1
  *            @arg TIM_CounterMode_CenterAligned2: TIM Center Aligned Mode2
  *            @arg TIM_CounterMode_CenterAligned3: TIM Center Aligned Mode3
  * @retval None
  */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode)
{
  uint16_t tmpcr1 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));
  
  tmpcr1 = TIMx->CR1;
  /* Reset the CMS and DIR Bits */
  tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_CR1_DIR | TIM_CR1_CMS)));
  /* Set the Counter Mode */
  tmpcr1 |= TIM_CounterMode;
  /* Write to TIMx CR1 register */
  TIMx->CR1 = tmpcr1;
}

/**
  * @brief  Sets the TIMx Counter Register value
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM 
  *          peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter)
{
  /* Check the parameters */
   assert_param(IS_TIM_ALL_PERIPH(TIMx));
   
  /* Set the Counter Register value */
  TIMx->CNT = Counter;
}

/**
  * @brief  Sets the TIMx Autoreload Register value
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @param  Autoreload: specifies the Autoreload register new value.
  * @retval None
  */
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  
  /* Set the Autoreload Register value */
  TIMx->ARR = Autoreload;
}

/**
  * @brief  Gets the TIMx Counter value.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM 
  *         peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @retval Counter Register value.
  */
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  
  /* Get the Counter Register value */
  return TIMx->CNT;
}

/**
  * @brief  Gets the TIMx Prescaler value.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM 
  *         peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @retval Prescaler Register value.
  */
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  
  /* Get the Prescaler Register value */
  return TIMx->PSC;
}

/**
  * @brief  Enables or Disables the TIMx Update event.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM 
  *         peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @param  NewState: new state of the TIMx UDIS bit
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Set the Update Disable Bit */
    TIMx->CR1 |= TIM_CR1_UDIS;
  }
  else
  {
    /* Reset the Update Disable Bit */
    TIMx->CR1 &= (uint16_t)~((uint16_t)TIM_CR1_UDIS);
  }
}

/**
  * @brief  Configures the TIMx Update Request Interrupt source.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM 
  *         peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @param  TIM_UpdateSource: specifies the Update source.
  *          This parameter can be one of the following values:
  *            @arg TIM_UpdateSource_Regular: Source of update is the counter
  *                 overflow/underflow or the setting of UG bit, or an update
  *                 generation through the slave mode controller.
  *            @arg TIM_UpdateSource_Global: Source of update is counter overflow/underflow.
  * @retval None
  */
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));
  
  if (TIM_UpdateSource != TIM_UpdateSource_Global)
  {
    /* Set the URS Bit */
    TIMx->CR1 |= TIM_CR1_URS;
  }
  else
  {
    /* Reset the URS Bit */
    TIMx->CR1 &= (uint16_t)~((uint16_t)TIM_CR1_URS);
  }
}

/**
  * @brief  Enables or disables TIMx peripheral Preload register on ARR.
  * @param  TIMx: where x can be  1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM 
  *         peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  NewState: new state of the TIMx peripheral Preload register
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Set the ARR Preload Bit */
    TIMx->CR1 |= TIM_CR1_ARPE;
  }
  else
  {
    /* Reset the ARR Preload Bit */
    TIMx->CR1 &= (uint16_t)~((uint16_t)TIM_CR1_ARPE);
  }
}

/**
  * @brief  Selects the TIMx's One Pulse Mode.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17 to select the TIM 
  *         peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @param  TIM_OPMode: specifies the OPM Mode to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_OPMode_Single
  *            @arg TIM_OPMode_Repetitive
  * @retval None
  */
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_OPM_MODE(TIM_OPMode));
  
  /* Reset the OPM Bit */
  TIMx->CR1 &= (uint16_t)~((uint16_t)TIM_CR1_OPM);
  /* Configure the OPM Mode */
  TIMx->CR1 |= TIM_OPMode;
}

/**
  * @brief  Sets the TIMx Clock Division value.
  * @param  TIMx: where x can be  1, 2, 3, 14, 15, 16 and 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_CKD: specifies the clock division value.
  *          This parameter can be one of the following value:
  *            @arg TIM_CKD_DIV1: TDTS = Tck_tim
  *            @arg TIM_CKD_DIV2: TDTS = 2*Tck_tim
  *            @arg TIM_CKD_DIV4: TDTS = 4*Tck_tim
  * @retval None
  */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_CKD_DIV(TIM_CKD));
  
  /* Reset the CKD Bits */
  TIMx->CR1 &= (uint16_t)~((uint16_t)TIM_CR1_CKD);
  /* Set the CKD value */
  TIMx->CR1 |= TIM_CKD;
}

/**
  * @brief  Enables or disables the specified TIM peripheral.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 and 17to select the TIMx
  *         peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @param  NewState: new state of the TIMx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the TIM Counter */
    TIMx->CR1 |= TIM_CR1_CEN;
  }
  else
  {
    /* Disable the TIM Counter */
    TIMx->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
  }
}

/**
  * @}
  */

/** @defgroup TIM_Group2 Advanced-control timers (TIM1) specific features
 *  @brief   Advanced-control timers (TIM1) specific features
 *
@verbatim   
 ===============================================================================
      ##### Advanced-control timers (TIM1) specific features #####
 ===============================================================================  
  
       ===================================================================      
              *** TIM Driver: how to use the Break feature ***
       =================================================================== 
       [..] After configuring the Timer channel(s) in the appropriate Output Compare mode: 
                         
           (#) Fill the TIM_BDTRInitStruct with the desired parameters for the Timer
               Break Polarity, dead time, Lock level, the OSSI/OSSR State and the 
               AOE(automatic output enable).
               
           (#) Call TIM_BDTRConfig(TIMx, &TIM_BDTRInitStruct) to configure the Timer
          
           (#) Enable the Main Output using TIM_CtrlPWMOutputs(TIM1, ENABLE) 
          
           (#) Once the break even occurs, the Timer's output signals are put in reset
               state or in a known state (according to the configuration made in
               TIM_BDTRConfig() function).

@endverbatim
  * @{
  */
/**
  * @brief  Configures the: Break feature, dead time, Lock level, OSSI/OSSR State
  *         and the AOE(automatic output enable).
  * @param  TIMx: where x can be  1, 15, 16 or 17 to select the TIM 
  * @param  TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure that
  *         contains the BDTR Register configuration  information for the TIM peripheral.
  * @retval None
  */
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
  assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
  assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
  assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
  assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
  assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));
  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSR State,
     the OSSI State, the dead time value and the Automatic Output Enable Bit */
  TIMx->BDTR = (uint32_t)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
             TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
             TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
             TIM_BDTRInitStruct->TIM_AutomaticOutput;
}

/**
  * @brief  Fills each TIM_BDTRInitStruct member with its default value.
  * @param  TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure which
  *         will be initialized.
  * @retval None
  */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct)
{
  /* Set the default configuration */
  TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/**
  * @brief  Enables or disables the TIM peripheral Main Outputs.
  * @param  TIMx: where x can be 1, 15, 16 or 17 to select the TIMx peripheral.
  * @param  NewState: new state of the TIM peripheral Main Outputs.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the TIM Main Output */
    TIMx->BDTR |= TIM_BDTR_MOE;
  }
  else
  {
    /* Disable the TIM Main Output */
    TIMx->BDTR &= (uint16_t)(~((uint16_t)TIM_BDTR_MOE));
  }  
}

/**
  * @}
  */

/** @defgroup TIM_Group3 Output Compare management functions
 *  @brief    Output Compare management functions 
 *
@verbatim
 ===============================================================================
                ##### Output Compare management functions #####
 ===============================================================================
        *** TIM Driver: how to use it in Output Compare Mode ***
 ===============================================================================
    [..] To use the Timer in Output Compare mode, the following steps are mandatory:
         (#) Enable TIM clock using 
             RCC_APBxPeriphClockCmd(RCC_APBxPeriph_TIMx, ENABLE) function.
         (#) Configure the TIM pins by configuring the corresponding GPIO pins
         (#) Configure the Time base unit as described in the first part of this 
             driver, if needed, else the Timer will run with the default 
             configuration:
             (++) Autoreload value = 0xFFFF.
             (++) Prescaler value = 0x0000.
             (++) Counter mode = Up counting.
             (++) Clock Division = TIM_CKD_DIV1.
         (#) Fill the TIM_OCInitStruct with the desired parameters including:
             (++) The TIM Output Compare mode: TIM_OCMode.
             (++) TIM Output State: TIM_OutputState.
             (++) TIM Pulse value: TIM_Pulse.
             (++) TIM Output Compare Polarity : TIM_OCPolarity.
         (#) Call TIM_OCxInit(TIMx, &TIM_OCInitStruct) to configure the desired 
             channel with the corresponding configuration.
         (#) Call the TIM_Cmd(ENABLE) function to enable the TIM counter.
    [..]
        (@) All other functions can be used separately to modify, if needed,
          a specific feature of the Timer.
        (@) In case of PWM mode, this function is mandatory:
            TIM_OCxPreloadConfig(TIMx, TIM_OCPreload_ENABLE).
        (@) If the corresponding interrupt or DMA request are needed, the user should:
            (#@) Enable the NVIC (or the DMA) to use the TIM interrupts (or DMA requests).
            (#@) Enable the corresponding interrupt (or DMA request) using the function
                 TIM_ITConfig(TIMx, TIM_IT_CCx) (or TIM_DMA_Cmd(TIMx, TIM_DMA_CCx)).

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the TIMx Channel1 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM 
  *         peripheral.
  * @retval None
  */
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
 /* Disable the Channel 1: Reset the CC1E Bit */
  TIMx->CCER &= (uint16_t)(~(uint16_t)TIM_CCER_CC1E);
  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;
  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIMx->CR2;
  
  /* Get the TIMx CCMR1 register value */
  tmpccmrx = TIMx->CCMR1;
    
  /* Reset the Output Compare Mode Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR1_OC1M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR1_CC1S));

  /* Select the Output Compare Mode */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
  
  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC1P));
  /* Set the Output Compare Polarity */
  tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;
  
  /* Set the Output State */
  tmpccer |= TIM_OCInitStruct->TIM_OutputState;
    
  if((TIMx == TIM1) || (TIMx == TIM15) || (TIMx == TIM16) || (TIMx == TIM17))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC1NP));
    /* Set the Output N Polarity */
    tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;
    
    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC1NE));    
    /* Set the Output N State */
    tmpccer |= TIM_OCInitStruct->TIM_OutputNState;
    
    /* Reset the Ouput Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS1));
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS1N));
    
    /* Set the Output Idle state */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
    /* Set the Output N Idle state */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;
  
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse; 
 
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TIMx Channel2 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM 
  *         peripheral.
  * @retval None
  */
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
   /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CCER_CC2E));
  
  /* Get the TIMx CCER register value */  
  tmpccer = TIMx->CCER;
  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIMx->CR2;
  
  /* Get the TIMx CCMR1 register value */
  tmpccmrx = TIMx->CCMR1;
    
  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR1_OC2M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR1_CC2S));
  
  /* Select the Output Compare Mode */
  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
  
  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC2P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);
  
  /* Set the Output State */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 4);
    
  if((TIMx == TIM1) || (TIMx == TIM15))
  {
    /* Check the parameters */
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* Reset the Ouput Compare State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS2));
    
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 2);
    
    if (TIMx == TIM1)
    {    
      /* Check the parameters */
      assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
      assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
      assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
      
      /* Reset the Output N Polarity level */
      tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC2NP));
      /* Set the Output N Polarity */
      tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 4);
      
      /* Reset the Output N State */
      tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC2NE));    
      /* Set the Output N State */
      tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 4);
      
      /* Reset the Output Compare N IDLE State */
      tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS2N));
      
      /* Set the Output N Idle state */
      tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
    }
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;
  
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
  
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TIMx Channel3 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM 
  *         peripheral.
  * @retval None
  */
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CCER_CC3E));
  
  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;
  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIMx->CR2;
  
  /* Get the TIMx CCMR2 register value */
  tmpccmrx = TIMx->CCMR2;
    
  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR2_OC3M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR2_CC3S));  
  /* Select the Output Compare Mode */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
  
  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC3P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 8);
  
  /* Set the Output State */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 8);
    
  if(TIMx == TIM1)
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC3NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 8);
    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC3NE));
    
    /* Set the Output N State */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 8);
    /* Reset the Ouput Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS3));
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS3N));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 4);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;
  
  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
  
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TIMx Channel4 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM 
  *         peripheral.
  * @retval None
  */
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* Disable the Channel 2: Reset the CC4E Bit */
  TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CCER_CC4E));
  
  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;
  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIMx->CR2;
  
  /* Get the TIMx CCMR2 register value */
  tmpccmrx = TIMx->CCMR2;
    
  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR2_OC4M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR2_CC4S));
  
  /* Select the Output Compare Mode */
  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
  
  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC4P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);
  
  /* Set the Output State */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 12);
    
  if(TIMx == TIM1)
  {
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    /* Reset the Ouput Compare IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS4));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;
  
  /* Write to TIMx CCMR2 */  
  TIMx->CCMR2 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
  
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Fills each TIM_OCInitStruct member with its default value.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  /* Set the default configuration */
  TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct->TIM_Pulse = 0x0000000;
  TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/**
  * @brief  Selects the TIM Output Compare Mode.
  * @note   This function disables the selected channel before changing the Output
  *         Compare Mode.
  *         User has to enable this channel using TIM_CCxCmd and TIM_CCxNCmd functions.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_Channel: specifies the TIM Channel
  *          This parameter can be one of the following values:
  *            @arg TIM_Channel_1: TIM Channel 1
  *            @arg TIM_Channel_2: TIM Channel 2
  *            @arg TIM_Channel_3: TIM Channel 3
  *            @arg TIM_Channel_4: TIM Channel 4
  * @param  TIM_OCMode: specifies the TIM Output Compare Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCMode_Timing
  *            @arg TIM_OCMode_Active
  *            @arg TIM_OCMode_Toggle
  *            @arg TIM_OCMode_PWM1
  *            @arg TIM_OCMode_PWM2
  *            @arg TIM_ForcedAction_Active
  *            @arg TIM_ForcedAction_InActive
  * @retval None
  */
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode)
{
  uint32_t tmp = 0;
  uint16_t tmp1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));  
  assert_param(IS_TIM_OCM(TIM_OCMode));
  
  tmp = (uint32_t) TIMx;
  tmp += CCMR_OFFSET;

  tmp1 = CCER_CCE_SET << (uint16_t)TIM_Channel;

  /* Disable the Channel: Reset the CCxE Bit */
  TIMx->CCER &= (uint16_t) ~tmp1;

  if((TIM_Channel == TIM_Channel_1) ||(TIM_Channel == TIM_Channel_3))
  {
    tmp += (TIM_Channel>>1);

    /* Reset the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TIM_CCMR1_OC1M);
   
    /* Configure the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp |= TIM_OCMode;
  }
  else
  {
    tmp += (uint16_t)(TIM_Channel - (uint16_t)4)>> (uint16_t)1;

    /* Reset the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TIM_CCMR1_OC2M);
    
    /* Configure the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp |= (uint16_t)(TIM_OCMode << 8);
  }
}

/**
  * @brief  Sets the TIMx Capture Compare1 Register value
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  Compare1: specifies the Capture Compare1 register new value.
  * @retval None
  */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  
  /* Set the Capture Compare1 Register value */
  TIMx->CCR1 = Compare1;
}

/**
  * @brief  Sets the TIMx Capture Compare2 Register value
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  Compare2: specifies the Capture Compare2 register new value.
  * @retval None
  */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  
  /* Set the Capture Compare2 Register value */
  TIMx->CCR2 = Compare2;
}

/**
  * @brief  Sets the TIMx Capture Compare3 Register value
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @param  Compare3: specifies the Capture Compare3 register new value.
  * @retval None
  */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  
  /* Set the Capture Compare3 Register value */
  TIMx->CCR3 = Compare3;
}

/**
  * @brief  Sets the TIMx Capture Compare4 Register value
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.    
  * @param  Compare4: specifies the Capture Compare4 register new value.
  * @retval None
  */
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  
  /* Set the Capture Compare4 Register value */
  TIMx->CCR4 = Compare4;
}

/**
  * @brief  Forces the TIMx output 1 waveform to active or inactive level.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active: Force active level on OC1REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC1REF.
  * @retval None
  */
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC1M Bits */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC1M);
  /* Configure The Forced output Mode */
  tmpccmr1 |= TIM_ForcedAction;
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}
 
/**
  * @brief  Forces the TIMx output 2 waveform to active or inactive level.
  * @param  TIMx: where x can be 1, 2, 3, or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active: Force active level on OC2REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC2REF.
  * @retval None
  */
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2M Bits */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC2M);
  /* Configure The Forced output Mode */
  tmpccmr1 |= (uint16_t)(TIM_ForcedAction << 8);
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the TIMx output 3 waveform to active or inactive level.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active: Force active level on OC3REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC3REF.
  * @retval None
  */
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC1M Bits */
  tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC3M);
  /* Configure The Forced output Mode */
  tmpccmr2 |= TIM_ForcedAction;
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Forces the TIMx output 4 waveform to active or inactive level.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active: Force active level on OC4REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC4REF.
  * @retval None
  */
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC2M Bits */
  tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC4M);
  /* Configure The Forced output Mode */
  tmpccmr2 |= (uint16_t)(TIM_ForcedAction << 8);
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Sets or Resets the TIM peripheral Capture Compare Preload Control bit.
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIMx peripheral
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  NewState: new state of the Capture Compare Preload Control bit
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the CCPC Bit */
    TIMx->CR2 |= TIM_CR2_CCPC;
  }
  else
  {
    /* Reset the CCPC Bit */
    TIMx->CR2 &= (uint16_t)~((uint16_t)TIM_CR2_CCPC);
  }
}


/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR1.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 and 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC1PE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC1PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= TIM_OCPreload;
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR2.
  * @param  TIMx: where x can be 1, 2, 3 and 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2PE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC2PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= (uint16_t)(TIM_OCPreload << 8);
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR3.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC3PE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC3PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= TIM_OCPreload;
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR4.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC4PE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC4PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= (uint16_t)(TIM_OCPreload << 8);
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TIMx Output Compare 1 Fast feature.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable: TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  
  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC1FE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC1FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= TIM_OCFast;
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Configures the TIMx Output Compare 2 Fast feature.
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable: TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  
  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2FE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC2FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= (uint16_t)(TIM_OCFast << 8);
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Configures the TIMx Output Compare 3 Fast feature.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable: TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  
  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC3FE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC3FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= TIM_OCFast;
  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TIMx Output Compare 4 Fast feature.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable: TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  
  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC4FE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC4FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= (uint16_t)(TIM_OCFast << 8);
  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF1 signal on an external event
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable: TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr1 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC1CE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC1CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= TIM_OCClear;
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF2 signal on an external event
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable: TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr1 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2CE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TIM_CCMR1_OC2CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= (uint16_t)(TIM_OCClear << 8);
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF3 signal on an external event
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable: TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr2 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC3CE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC3CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= TIM_OCClear;
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF4 signal on an external event
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable: TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr2 = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC4CE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TIM_CCMR2_OC4CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= (uint16_t)(TIM_OCClear << 8);
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TIMx channel 1 polarity.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCPolarity: specifies the OC1 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC1P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TIM_CCER_CC1P);
  tmpccer |= TIM_OCPolarity;
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx Channel 1N polarity.
  * @param  TIMx: where x can be 1, 15, 16 or 17 to select the TIM peripheral.
  * @param  TIM_OCNPolarity: specifies the OC1N Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCNPolarity_High: Output Compare active high
  *            @arg TIM_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
   
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC1NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TIM_CCER_CC1NP);
  tmpccer |= TIM_OCNPolarity;
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx channel 2 polarity.
  * @param  TIMx: where x can be 1, 2, 3, or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCPolarity: specifies the OC2 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC2P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TIM_CCER_CC2P);
  tmpccer |= (uint16_t)(TIM_OCPolarity << 4);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx Channel 2N polarity.
  * @param  TIMx: where x can be 1 to select the TIM peripheral.
  * @param  TIM_OCNPolarity: specifies the OC2N Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCNPolarity_High: Output Compare active high
  *            @arg TIM_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST1_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
  
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC2NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TIM_CCER_CC2NP);
  tmpccer |= (uint16_t)(TIM_OCNPolarity << 4);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx channel 3 polarity.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCPolarity: specifies the OC3 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC3P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TIM_CCER_CC3P);
  tmpccer |= (uint16_t)(TIM_OCPolarity << 8);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx Channel 3N polarity.
  * @param  TIMx: where x can be 1 to select the TIM peripheral.
  * @param  TIM_OCNPolarity: specifies the OC3N Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCNPolarity_High: Output Compare active high
  *            @arg TIM_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
 
  /* Check the parameters */
  assert_param(IS_TIM_LIST1_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
    
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC3NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TIM_CCER_CC3NP);
  tmpccer |= (uint16_t)(TIM_OCNPolarity << 8);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx channel 4 polarity.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCPolarity: specifies the OC4 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC4P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TIM_CCER_CC4P);
  tmpccer |= (uint16_t)(TIM_OCPolarity << 12);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Selects the OCReference Clear source.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_OCReferenceClear: specifies the OCReference Clear source.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCReferenceClear_ETRF: The internal OCreference clear input is connected to ETRF.
  *            @arg TIM_OCReferenceClear_OCREFCLR: The internal OCreference clear input is connected to OCREF_CLR input.  
  * @retval None
  */
void TIM_SelectOCREFClear(TIM_TypeDef* TIMx, uint16_t TIM_OCReferenceClear)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(TIM_OCREFERENCECECLEAR_SOURCE(TIM_OCReferenceClear));

  /* Set the TIM_OCReferenceClear source */
  TIMx->SMCR &=  (uint16_t)~((uint16_t)TIM_SMCR_OCCS);
  TIMx->SMCR |=  TIM_OCReferenceClear;
}

/**
  * @brief  Enables or disables the TIM Capture Compare Channel x.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_Channel: specifies the TIM Channel
  *          This parameter can be one of the following values:
  *            @arg TIM_Channel_1: TIM Channel 1
  *            @arg TIM_Channel_2: TIM Channel 2
  *            @arg TIM_Channel_3: TIM Channel 3
  *            @arg TIM_Channel_4: TIM Channel 4
  * @param  TIM_CCx: specifies the TIM Channel CCxE bit new state.
  *          This parameter can be: TIM_CCx_Enable or TIM_CCx_Disable. 
  * @retval None
  */
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx)
{
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx)); 
  assert_param(IS_TIM_CCX(TIM_CCx));

  tmp = CCER_CCE_SET << TIM_Channel;

  /* Reset the CCxE Bit */
  TIMx->CCER &= (uint16_t)~ tmp;

  /* Set or reset the CCxE Bit */ 
  TIMx->CCER |=  (uint16_t)(TIM_CCx << TIM_Channel);
}

/**
  * @brief  Enables or disables the TIM Capture Compare Channel xN.
  * @param  TIMx: where x can be 1, 15, 16 or 17 to select the TIM peripheral.
  * @param  TIM_Channel: specifies the TIM Channel
  *          This parmeter can be one of the following values:
  *            @arg TIM_Channel_1: TIM Channel 1
  *            @arg TIM_Channel_2: TIM Channel 2
  *            @arg TIM_Channel_3: TIM Channel 3
  * @param  TIM_CCxN: specifies the TIM Channel CCxNE bit new state.
  *          This parameter can be: TIM_CCxN_Enable or TIM_CCxN_Disable. 
  * @retval None
  */
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN)
{
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_TIM_COMPLEMENTARY_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCXN(TIM_CCxN));

  tmp = CCER_CCNE_SET << TIM_Channel;

  /* Reset the CCxNE Bit */
  TIMx->CCER &= (uint16_t) ~tmp;

  /* Set or reset the CCxNE Bit */ 
  TIMx->CCER |=  (uint16_t)(TIM_CCxN << TIM_Channel);
}

/**
  * @brief  Selects the TIM peripheral Commutation event.
  * @param  TIMx: where x can be  1, 15, 16 or 17 to select the TIMx peripheral
  * @param  NewState: new state of the Commutation event.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the COM Bit */
    TIMx->CR2 |= TIM_CR2_CCUS;
  }
  else
  {
    /* Reset the COM Bit */
    TIMx->CR2 &= (uint16_t)~((uint16_t)TIM_CR2_CCUS);
  }
}

/**
  * @}
  */

/** @defgroup TIM_Group4 Input Capture management functions
 *  @brief    Input Capture management functions 
 *
@verbatim
 ===============================================================================
               ##### Input Capture management functions #####
 ===============================================================================
   
          *** TIM Driver: how to use it in Input Capture Mode ***
 ===============================================================================
    [..] To use the Timer in Input Capture mode, the following steps are mandatory:
         (#) Enable TIM clock using RCC_APBxPeriphClockCmd(RCC_APBxPeriph_TIMx, ENABLE) 
             function.
         (#) Configure the TIM pins by configuring the corresponding GPIO pins.
         (#) Configure the Time base unit as described in the first part of this 
             driver, if needed, else the Timer will run with the default configuration:
             (++) Autoreload value = 0xFFFF.
             (++) Prescaler value = 0x0000.
             (++) Counter mode = Up counting.
             (++) Clock Division = TIM_CKD_DIV1.
         (#) Fill the TIM_ICInitStruct with the desired parameters including:
             (++) TIM Channel: TIM_Channel.
             (++) TIM Input Capture polarity: TIM_ICPolarity.
             (++) TIM Input Capture selection: TIM_ICSelection.
             (++) TIM Input Capture Prescaler: TIM_ICPrescaler.
             (++) TIM Input CApture filter value: TIM_ICFilter.
         (#) Call TIM_ICInit(TIMx, &TIM_ICInitStruct) to configure the desired 
             channel with the corresponding configuration and to measure only 
             frequency or duty cycle of the input signal,or, Call 
             TIM_PWMIConfig(TIMx, &TIM_ICInitStruct) to configure the desired 
             channels with the corresponding configuration and to measure the 
             frequency and the duty cycle of the input signal.
         (#) Enable the NVIC or the DMA to read the measured frequency.
         (#) Enable the corresponding interrupt (or DMA request) to read 
             the Captured value, using the function TIM_ITConfig(TIMx, TIM_IT_CCx)
             (or TIM_DMA_Cmd(TIMx, TIM_DMA_CCx)).
         (#) Call the TIM_Cmd(ENABLE) function to enable the TIM counter.
         (#) Use TIM_GetCapturex(TIMx); to read the captured value.
    [..]
        (@) All other functions can be used separately to modify, if needed,
            a specific feature of the Timer. 

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the TIM peripheral according to the specified
  *         parameters in the TIM_ICInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
  *         that contains the configuration information for the specified TIM 
  *         peripheral.
  * @retval None
  */
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_ICInitStruct->TIM_Channel));  
  assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
  assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));

  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    /* TI1 Configuration */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
  {
    assert_param(IS_TIM_LIST6_PERIPH(TIMx));
    /* TI2 Configuration */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
  {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    /* TI3 Configuration */
    TI3_Config(TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    /* TI4 Configuration */
    TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/**
  * @brief  Fills each TIM_ICInitStruct member with its default value.
  * @param  TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* Set the default configuration */
  TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
  TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

/**
  * @brief  Configures the TIM peripheral according to the specified
  *         parameters in the TIM_ICInitStruct to measure an external PWM signal.
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
  *         that contains the configuration information for the specified TIM 
  *         peripheral.
  * @retval None
  */
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  uint16_t icoppositepolarity = TIM_ICPolarity_Rising;
  uint16_t icoppositeselection = TIM_ICSelection_DirectTI;
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  /* Select the Opposite Input Polarity */
  if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
  {
    icoppositepolarity = TIM_ICPolarity_Falling;
  }
  else
  {
    icoppositepolarity = TIM_ICPolarity_Rising;
  }
  /* Select the Opposite Input */
  if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
  {
    icoppositeselection = TIM_ICSelection_IndirectTI;
  }
  else
  {
    icoppositeselection = TIM_ICSelection_DirectTI;
  }
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    /* TI2 Configuration */
    TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  { 
    /* TI2 Configuration */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    /* TI1 Configuration */
    TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/**
  * @brief  Gets the TIMx Input Capture 1 value.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @retval Capture Compare 1 Register value.
  */
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  
  /* Get the Capture 1 Register value */
  return TIMx->CCR1;
}

/**
  * @brief  Gets the TIMx Input Capture 2 value.
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @retval Capture Compare 2 Register value.
  */
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  
  /* Get the Capture 2 Register value */
  return TIMx->CCR2;
}

/**
  * @brief  Gets the TIMx Input Capture 3 value.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @retval Capture Compare 3 Register value.
  */
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx)); 
  
  /* Get the Capture 3 Register value */
  return TIMx->CCR3;
}

/**
  * @brief  Gets the TIMx Input Capture 4 value.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @retval Capture Compare 4 Register value.
  */
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  
  /* Get the Capture 4 Register value */
  return TIMx->CCR4;
}

/**
  * @brief  Sets the TIMx Input Capture 1 prescaler.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ICPSC: specifies the Input Capture1 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  
  /* Reset the IC1PSC Bits */
  TIMx->CCMR1 &= (uint16_t)~((uint16_t)TIM_CCMR1_IC1PSC);
  /* Set the IC1PSC value */
  TIMx->CCMR1 |= TIM_ICPSC;
}

/**
  * @brief  Sets the TIMx Input Capture 2 prescaler.
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ICPSC: specifies the Input Capture2 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  
  /* Reset the IC2PSC Bits */
  TIMx->CCMR1 &= (uint16_t)~((uint16_t)TIM_CCMR1_IC2PSC);
  /* Set the IC2PSC value */
  TIMx->CCMR1 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
  * @brief  Sets the TIMx Input Capture 3 prescaler.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ICPSC: specifies the Input Capture3 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  
  /* Reset the IC3PSC Bits */
  TIMx->CCMR2 &= (uint16_t)~((uint16_t)TIM_CCMR2_IC3PSC);
  /* Set the IC3PSC value */
  TIMx->CCMR2 |= TIM_ICPSC;
}

/**
  * @brief  Sets the TIMx Input Capture 4 prescaler.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ICPSC: specifies the Input Capture4 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  
  /* Reset the IC4PSC Bits */
  TIMx->CCMR2 &= (uint16_t)~((uint16_t)TIM_CCMR2_IC4PSC);
  /* Set the IC4PSC value */
  TIMx->CCMR2 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
  * @}
  */

/** @defgroup TIM_Group5 Interrupts DMA and flags management functions
 *  @brief    Interrupts, DMA and flags management functions 
 *
@verbatim
 ===============================================================================
          ##### Interrupts, DMA and flags management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified TIM interrupts.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17 to select the TIMx peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_IT: specifies the TIM interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg TIM_IT_Update: TIM update Interrupt source
  *            @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *            @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *            @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
  *            @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
  *            @arg TIM_IT_COM: TIM Commutation Interrupt source
  *            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *            @arg TIM_IT_Break: TIM Break Interrupt source
  * 
  * @note   TIM6 and TIM7 can only generate an update interrupt.
  * @note   TIM15 can have only TIM_IT_Update, TIM_IT_CC1,TIM_IT_CC2 or TIM_IT_Trigger. 
  * @note   TIM14, TIM16 and TIM17 can have TIM_IT_Update or TIM_IT_CC1.   
  * @note   TIM_IT_Break is used only with TIM1 and TIM15. 
  * @note   TIM_IT_COM is used only with TIM1, TIM15, TIM16 and TIM17.
  *       
  * @param  NewState: new state of the TIM interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState)
{  
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIMx->DIER |= TIM_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIMx->DIER &= (uint16_t)~TIM_IT;
  }
}

/**
  * @brief  Configures the TIMx event to be generate by software.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17 to select the 
  *         TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_EventSource: specifies the event source.
  *          This parameter can be one or more of the following values:  
  *            @arg TIM_EventSource_Update: Timer update Event source
  *            @arg TIM_EventSource_CC1: Timer Capture Compare 1 Event source
  *            @arg TIM_EventSource_CC2: Timer Capture Compare 2 Event source
  *            @arg TIM_EventSource_CC3: Timer Capture Compare 3 Event source
  *            @arg TIM_EventSource_CC4: Timer Capture Compare 4 Event source
  *            @arg TIM_EventSource_COM: Timer COM event source  
  *            @arg TIM_EventSource_Trigger: Timer Trigger Event source
  *            @arg TIM_EventSource_Break: Timer Break event source
  *
  * @note   TIM6 and TIM7 can only generate an update event.  
  * @note   TIM_EventSource_COM and TIM_EventSource_Break are used only with TIM1.
  *             
  * @retval None
  */
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource)
{ 
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource)); 
  /* Set the event sources */
  TIMx->EGR = TIM_EventSource;
}

/**
  * @brief  Checks whether the specified TIM flag is set or not.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg TIM_FLAG_Update: TIM update Flag
  *            @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
  *            @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
  *            @arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
  *            @arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
  *            @arg TIM_FLAG_COM: TIM Commutation Flag
  *            @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *            @arg TIM_FLAG_Break: TIM Break Flag
  *            @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
  *            @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
  *            @arg TIM_FLAG_CC3OF: TIM Capture Compare 3 overcapture Flag
  *            @arg TIM_FLAG_CC4OF: TIM Capture Compare 4 overcapture Flag
  *
  * @note   TIM6 and TIM7 can have only one update flag. 
  * @note   TIM15 can have only TIM_FLAG_Update, TIM_FLAG_CC1, TIM_FLAG_CC2 or TIM_FLAG_Trigger.
  * @note   TIM14, TIM16 and TIM17 can have TIM_FLAG_Update or TIM_FLAG_CC1.   
  * @note   TIM_FLAG_Break is used only with TIM1 and TIM15. 
  * @note   TIM_FLAG_COM is used only with TIM1 TIM15, TIM16 and TIM17.
  *
  * @retval The new state of TIM_FLAG (SET or RESET).
  */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{ 
  ITStatus bitstatus = RESET; 
   
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_FLAG(TIM_FLAG));
  
  if ((TIMx->SR & TIM_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the TIMx's pending flags.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_FLAG: specifies the flag bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg TIM_FLAG_Update: TIM update Flag
  *            @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
  *            @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
  *            @arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
  *            @arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
  *            @arg TIM_FLAG_COM: TIM Commutation Flag
  *            @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *            @arg TIM_FLAG_Break: TIM Break Flag
  *            @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
  *            @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
  *            @arg TIM_FLAG_CC3OF: TIM Capture Compare 3 overcapture Flag
  *            @arg TIM_FLAG_CC4OF: TIM Capture Compare 4 overcapture Flag
  *
  * @note   TIM6 and TIM7 can have only one update flag. 
  * @note   TIM15 can have only TIM_FLAG_Update, TIM_FLAG_CC1,TIM_FLAG_CC2 or 
  *         TIM_FLAG_Trigger. 
  * @note   TIM14, TIM16 and TIM17 can have TIM_FLAG_Update or TIM_FLAG_CC1.   
  * @note   TIM_FLAG_Break is used only with TIM1 and TIM15. 
  * @note   TIM_FLAG_COM is used only with TIM1, TIM15, TIM16 and TIM17.
  *
  * @retval None
  */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{  
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_CLEAR_FLAG(TIM_FLAG));
   
  /* Clear the flags */
  TIMx->SR = (uint16_t)~TIM_FLAG;
}

/**
  * @brief  Checks whether the TIM interrupt has occurred or not.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_IT: specifies the TIM interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg TIM_IT_Update: TIM update Interrupt source
  *            @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *            @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *            @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
  *            @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
  *            @arg TIM_IT_COM: TIM Commutation Interrupt source
  *            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *            @arg TIM_IT_Break: TIM Break Interrupt source
  *
  * @note   TIM6 and TIM7 can generate only an update interrupt.
  * @note   TIM15 can have only TIM_IT_Update, TIM_IT_CC1, TIM_IT_CC2 or TIM_IT_Trigger. 
  * @note   TIM14, TIM16 and TIM17 can have TIM_IT_Update or TIM_IT_CC1.   
  * @note   TIM_IT_Break is used only with TIM1 and TIM15. 
  * @note   TIM_IT_COM is used only with TIM1, TIM15, TIM16 and TIM17.
  *
  * @retval The new state of the TIM_IT(SET or RESET).
  */
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
  ITStatus bitstatus = RESET;  
  uint16_t itstatus = 0x0, itenable = 0x0;
  
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_IT(TIM_IT));
   
  itstatus = TIMx->SR & TIM_IT;
  
  itenable = TIMx->DIER & TIM_IT;
  if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the TIMx's interrupt pending bits.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_IT: specifies the pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg TIM_IT_Update: TIM1 update Interrupt source
  *            @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *            @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *            @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
  *            @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
  *            @arg TIM_IT_COM: TIM Commutation Interrupt source
  *            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *            @arg TIM_IT_Break: TIM Break Interrupt source
  *
  * @note   TIM6 and TIM7 can generate only an update interrupt.
  * @note   TIM15 can have only TIM_IT_Update, TIM_IT_CC1, TIM_IT_CC2 or TIM_IT_Trigger. 
  * @note   TIM14, TIM16 and TIM17 can have TIM_IT_Update or TIM_IT_CC1.   
  * @note   TIM_IT_Break is used only with TIM1 and TIM15. 
  * @note   TIM_IT_COM is used only with TIM1, TIM15, TIM16 and TIM17.
  *
  * @retval None
  */
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
   
  /* Clear the IT pending Bit */
  TIMx->SR = (uint16_t)~TIM_IT;
}

/**
  * @brief  Configures the TIMx's DMA interface.
  * @param  TIMx: where x can be 1, 2, 3, 15, 16 or 17  to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_DMABase: DMA Base address.
  *          This parameter can be one of the following values:
  *            @arg TIM_DMABase_CR1
  *            @arg TIM_DMABase_CR2
  *            @arg TIM_DMABase_SMCR
  *            @arg TIM_DMABase_DIER
  *            @arg TIM_DMABase_SR
  *            @arg TIM_DMABase_EGR
  *            @arg TIM_DMABase_CCMR1
  *            @arg TIM_DMABase_CCMR2
  *            @arg TIM_DMABase_CCER
  *            @arg TIM_DMABase_CNT
  *            @arg TIM_DMABase_PSC
  *            @arg TIM_DMABase_ARR
  *            @arg TIM_DMABase_CCR1
  *            @arg TIM_DMABase_CCR2
  *            @arg TIM_DMABase_CCR3 
  *            @arg TIM_DMABase_CCR4
  *            @arg TIM_DMABase_DCR
  *            @arg TIM_DMABase_OR
  * @param  TIM_DMABurstLength: DMA Burst length. This parameter can be one value
  *         between: TIM_DMABurstLength_1Transfer and TIM_DMABurstLength_18Transfers.
  * @retval None
  */
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_BASE(TIM_DMABase)); 
  assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));
  /* Set the DMA Base and the DMA Burst Length */
  TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}

/**
  * @brief  Enables or disables the TIMx's DMA Requests.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, 15, 16 or 17 to select the TIM peripheral. 
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  TIM_DMASource: specifies the DMA Request sources.
  *          This parameter can be any combination of the following values:
  *            @arg TIM_DMA_Update: TIM update Interrupt source
  *            @arg TIM_DMA_CC1: TIM Capture Compare 1 DMA source
  *            @arg TIM_DMA_CC2: TIM Capture Compare 2 DMA source
  *            @arg TIM_DMA_CC3: TIM Capture Compare 3 DMA source
  *            @arg TIM_DMA_CC4: TIM Capture Compare 4 DMA source
  *            @arg TIM_DMA_COM: TIM Commutation DMA source
  *            @arg TIM_DMA_Trigger: TIM Trigger DMA source
  * @param  NewState: new state of the DMA Request sources.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_TIM_LIST10_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the DMA sources */
    TIMx->DIER |= TIM_DMASource; 
  }
  else
  {
    /* Disable the DMA sources */
    TIMx->DIER &= (uint16_t)~TIM_DMASource;
  }
}

/**
  * @brief  Selects the TIMx peripheral Capture Compare DMA source.
  * @param  TIMx: where x can be 1, 2, 3, 15, 16 or 17  to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.
  * @param  NewState: new state of the Capture Compare DMA source
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST5_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Set the CCDS Bit */
    TIMx->CR2 |= TIM_CR2_CCDS;
  }
  else
  {
    /* Reset the CCDS Bit */
    TIMx->CR2 &= (uint16_t)~((uint16_t)TIM_CR2_CCDS);
  }
}

/**
  * @}
  */

/** @defgroup TIM_Group6 Clocks management functions
 *  @brief    Clocks management functions
 *
@verbatim
 ===============================================================================
                     ##### Clocks management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Configures the TIMx internal Clock
  * @param  TIMx: where x can be 1, 2, 3, or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @retval None
  */
void TIM_InternalClockConfig(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TIMx->SMCR &=  (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
}

/**
  * @brief  Configures the TIMx Internal Trigger as External Clock
  * @param  TIMx: where x can be 1, 2, 3, or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ITRSource: Trigger source.
  *          This parameter can be one of the following values:
  *            @arg  TIM_TS_ITR0: Internal Trigger 0
  *            @arg  TIM_TS_ITR1: Internal Trigger 1
  *            @arg  TIM_TS_ITR2: Internal Trigger 2
  *            @arg  TIM_TS_ITR3: Internal Trigger 3
  * @retval None
  */
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));
  /* Select the Internal Trigger */
  TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);
  /* Select the External clock mode1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @brief  Configures the TIMx Trigger as External Clock
  * @param  TIMx: where x can be 1, 2, 3, or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_TIxExternalCLKSource: Trigger source.
  *          This parameter can be one of the following values:
  *            @arg TIM_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
  *            @arg TIM_TIxExternalCLK1Source_TI1: Filtered Timer Input 1
  *            @arg TIM_TIxExternalCLK1Source_TI2: Filtered Timer Input 2
  * @param  TIM_ICPolarity: specifies the TIx Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  ICFilter: specifies the filter value.
  *          This parameter must be a value between 0x0 and 0xF.
  * @retval None
  */
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
  assert_param(IS_TIM_IC_FILTER(ICFilter));
  
  /* Configure the Timer Input Clock Source */
  if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  /* Select the Trigger source */
  TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
  /* Select the External clock mode1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @brief  Configures the External clock Mode1
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
  *            @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *          This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  
  /* Configure the ETR Clock source */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  
  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;
  /* Reset the SMS Bits */
  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
  /* Select the External clock mode1 */
  tmpsmcr |= TIM_SlaveMode_External1;
  /* Select the Trigger selection : ETRF */
  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_TS));
  tmpsmcr |= TIM_TS_ETRF;
  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @brief  Configures the External clock Mode2
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
  *            @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *          This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  
  /* Configure the ETR Clock source */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  /* Enable the External clock mode2 */
  TIMx->SMCR |= TIM_SMCR_ECE;
}

/**
  * @}
  */

/** @defgroup TIM_Group7 Synchronization management functions
 *  @brief    Synchronization management functions 
 *
@verbatim
 ===============================================================================
               ##### Synchronization management functions #####
 ===============================================================================
        *** TIM Driver: how to use it in synchronization Mode ***
 ===============================================================================
    [..] Case of two/several Timers
         (#) Configure the Master Timers using the following functions:
             (++) void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx,
                  uint16_t TIM_TRGOSource).
             (++) void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx,
                  uint16_t TIM_MasterSlaveMode);  
         (#) Configure the Slave Timers using the following functions: 
             (++) void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, 
                  uint16_t TIM_InputTriggerSource);  
             (++) void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
    [..] Case of Timers and external trigger(ETR pin)
         (#) Configure the Etrenal trigger using this function:
             (++) void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
                  uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);
         (#) Configure the Slave Timers using the following functions:
             (++) void TIM_SelectInputTrigger(TIM_TypeDef* TIMx,
                  uint16_t TIM_InputTriggerSource);
             (++) void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);

@endverbatim
  * @{
  */
/**
  * @brief  Selects the Input Trigger source
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_InputTriggerSource: The Input Trigger source.
  *          This parameter can be one of the following values:
  *            @arg TIM_TS_ITR0: Internal Trigger 0
  *            @arg TIM_TS_ITR1: Internal Trigger 1
  *            @arg TIM_TS_ITR2: Internal Trigger 2
  *            @arg TIM_TS_ITR3: Internal Trigger 3
  *            @arg TIM_TS_TI1F_ED: TI1 Edge Detector
  *            @arg TIM_TS_TI1FP1: Filtered Timer Input 1
  *            @arg TIM_TS_TI2FP2: Filtered Timer Input 2
  *            @arg TIM_TS_ETRF: External Trigger input
  * @retval None
  */
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource)
{
  uint16_t tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx)); 
  assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));

  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;
  /* Reset the TS Bits */
  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_TS));
  /* Set the Input Trigger source */
  tmpsmcr |= TIM_InputTriggerSource;
  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @brief  Selects the TIMx Trigger Output Mode.
  * @param  TIMx: where x can be 1, 2, 3, 6, 7, or 15 to select the TIM peripheral.
  * @note   TIM7 is applicable only for STM32F072 devices
  * @note   TIM6 is not applivable for STM32F031 devices.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_TRGOSource: specifies the Trigger Output source.
  *          This parameter can be one of the following values:
  *
  *   - For all TIMx
  *            @arg TIM_TRGOSource_Reset:  The UG bit in the TIM_EGR register is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_Enable: The Counter Enable CEN is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_Update: The update event is selected as the trigger output (TRGO).
  *
  *   - For all TIMx except TIM6 and TIM7
  *            @arg TIM_TRGOSource_OC1: The trigger output sends a positive pulse when the CC1IF flag
  *                                     is to be set, as soon as a capture or compare match occurs (TRGO).
  *            @arg TIM_TRGOSource_OC1Ref: OC1REF signal is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_OC2Ref: OC2REF signal is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_OC3Ref: OC3REF signal is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_OC4Ref: OC4REF signal is used as the trigger output (TRGO).
  *
  * @retval None
  */
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST9_PERIPH(TIMx));
  assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));

  /* Reset the MMS Bits */
  TIMx->CR2 &= (uint16_t)~((uint16_t)TIM_CR2_MMS);
  /* Select the TRGO source */
  TIMx->CR2 |=  TIM_TRGOSource;
}

/**
  * @brief  Selects the TIMx Slave Mode.
  * @param  TIMx: where x can be 1, 2, 3 or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_SlaveMode: specifies the Timer Slave Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM_SlaveMode_Reset: Rising edge of the selected trigger signal (TRGI) re-initializes
  *                                      the counter and triggers an update of the registers.
  *            @arg TIM_SlaveMode_Gated:     The counter clock is enabled when the trigger signal (TRGI) is high.
  *            @arg TIM_SlaveMode_Trigger:   The counter starts at a rising edge of the trigger TRGI.
  *            @arg TIM_SlaveMode_External1: Rising edges of the selected trigger (TRGI) clock the counter.
  * @retval None
  */
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx)); 
  assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));
  
  /* Reset the SMS Bits */
  TIMx->SMCR &= (uint16_t)~((uint16_t)TIM_SMCR_SMS);
  /* Select the Slave Mode */
  TIMx->SMCR |= TIM_SlaveMode;
}

/**
  * @brief  Sets or Resets the TIMx Master/Slave Mode.
  * @param  TIMx: where x can be 1, 2, 3, or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_MasterSlaveMode: specifies the Timer Master Slave Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM_MasterSlaveMode_Enable: synchronization between the current timer
  *                                             and its slaves (through TRGO).
  *            @arg TIM_MasterSlaveMode_Disable: No action
  * @retval None
  */
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_MSM_STATE(TIM_MasterSlaveMode));
  
  /* Reset the MSM Bit */
  TIMx->SMCR &= (uint16_t)~((uint16_t)TIM_SMCR_MSM);
  
  /* Set or Reset the MSM Bit */
  TIMx->SMCR |= TIM_MasterSlaveMode;
}

/**
  * @brief  Configures the TIMx External Trigger (ETR).
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.   
  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
  *            @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *          This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  
  tmpsmcr = TIMx->SMCR;
  /* Reset the ETR Bits */
  tmpsmcr &= SMCR_ETR_MASK;
  /* Set the Prescaler, the Filter value and the Polarity */
  tmpsmcr |= (uint16_t)(TIM_ExtTRGPrescaler | (uint16_t)(TIM_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @}
  */

/** @defgroup TIM_Group8 Specific interface management functions
 *  @brief    Specific interface management functions 
 *
@verbatim
 ===============================================================================
             ##### Specific interface management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Configures the TIMx Encoder Interface.
  * @param  TIMx: where x can be  1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.   
  * @param  TIM_EncoderMode: specifies the TIMx Encoder Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
  *            @arg TIM_EncoderMode_TI2: Counter counts on TI2FP2 edge depending on TI1FP1 level.
  *            @arg TIM_EncoderMode_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
  *                                       on the level of the other input.
  * @param  TIM_IC1Polarity: specifies the IC1 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_ICPolarity_Falling: IC Falling edge.
  *            @arg TIM_ICPolarity_Rising: IC Rising edge.
  * @param  TIM_IC2Polarity: specifies the IC2 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_ICPolarity_Falling: IC Falling edge.
  *            @arg TIM_ICPolarity_Rising: IC Rising edge.
  * @retval None
  */
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity)
{
  uint16_t tmpsmcr = 0;
  uint16_t tmpccmr1 = 0;
  uint16_t tmpccer = 0;
    
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));
  
  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;
  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;
  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;
  /* Set the encoder Mode */
  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
  tmpsmcr |= TIM_EncoderMode;
  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIM_CCMR1_CC1S)) & (uint16_t)(~((uint16_t)TIM_CCMR1_CC2S)));
  tmpccmr1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
  /* Set the TI1 and the TI2 Polarities */
  tmpccer &= (uint16_t)~((uint16_t)(TIM_CCER_CC1P | TIM_CCER_CC1NP)) & (uint16_t)~((uint16_t)(TIM_CCER_CC2P | TIM_CCER_CC2NP));
  tmpccer |= (uint16_t)(TIM_IC1Polarity | (uint16_t)(TIM_IC2Polarity << (uint16_t)4));
  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Enables or disables the TIMx's Hall sensor interface.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.   
  * @param  NewState: new state of the TIMx Hall sensor interface.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Set the TI1S Bit */
    TIMx->CR2 |= TIM_CR2_TI1S;
  }
  else
  {
    /* Reset the TI1S Bit */
    TIMx->CR2 &= (uint16_t)~((uint16_t)TIM_CR2_TI1S);
  }
}

/**
  * @}
  */

/** @defgroup TIM_Group9 Specific remapping management function
 *  @brief   Specific remapping management function
 *
@verbatim
 ===============================================================================
               ##### Specific remapping management function #####
 ===============================================================================

@endverbatim
  * @{
  */
/**
  * @brief  Configures the TIM14 Remapping input Capabilities.
  * @param  TIMx: where x can be 14 to select the TIM peripheral.
  * @param  TIM_Remap: specifies the TIM input reampping source.
  *          This parameter can be one of the following values:
  *            @arg TIM14_GPIO: TIM14 Channel 1 is connected to GPIO.
  *            @arg TIM14_RTC_CLK: TIM14 Channel 1 is connected to RTC input clock.
  *                                RTC input clock can be LSE, LSI or HSE/div128.
  *            @arg TIM14_HSE_DIV32: TIM14 Channel 1 is connected to HSE/32 clock.  
  *            @arg TIM14_MCO: TIM14 Channel 1 is connected to MCO clock.  
  *                            MCO clock can be HSI14, SYSCLK, HSI, HSE or PLL/2.  
  * @retval None
  */
void TIM_RemapConfig(TIM_TypeDef* TIMx, uint16_t TIM_Remap)
{
 /* Check the parameters */
  assert_param(IS_TIM_LIST11_PERIPH(TIMx));
  assert_param(IS_TIM_REMAP(TIM_Remap));

  /* Set the Timer remapping configuration */
  TIMx->OR =  TIM_Remap;
}

/**
  * @}
  */

/**
  * @brief  Configure the TI1 as Input.
  * @param  TIMx: where x can be 1, 2, 3, 14, 15, 16 or 17 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.   
  * @param  TIM_ICPolarity: The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICSelection_DirectTI: TIM Input 1 is selected to be connected to IC1.
  *            @arg TIM_ICSelection_IndirectTI: TIM Input 1 is selected to be connected to IC2.
  *            @arg TIM_ICSelection_TRC: TIM Input 1 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0;
  /* Disable the Channel 1: Reset the CC1E Bit */
  TIMx->CCER &= (uint16_t)~((uint16_t)TIM_CCER_CC1E);
  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  /* Select the Input and set the filter */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIM_CCMR1_CC1S)) & ((uint16_t)~((uint16_t)TIM_CCMR1_IC1F)));
  tmpccmr1 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));
 
  /* Select the Polarity and set the CC1E Bit */
  tmpccer &= (uint16_t)~((uint16_t)(TIM_CCER_CC1P | TIM_CCER_CC1NP));
  tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CCER_CC1E);
  /* Write to TIMx CCMR1 and CCER registers */
  TIMx->CCMR1 = tmpccmr1;
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TIMx: where x can be 1, 2, 3, or 15 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ICPolarity: The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICSelection_DirectTI: TIM Input 2 is selected to be connected to IC2.
  *            @arg TIM_ICSelection_IndirectTI: TIM Input 2 is selected to be connected to IC1.
  *            @arg TIM_ICSelection_TRC: TIM Input 2 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;
  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= (uint16_t)~((uint16_t)TIM_CCER_CC2E);
  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 4);
  /* Select the Input and set the filter */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIM_CCMR1_CC2S)) & ((uint16_t)~((uint16_t)TIM_CCMR1_IC2F)));
  tmpccmr1 |= (uint16_t)(TIM_ICFilter << 12);
  tmpccmr1 |= (uint16_t)(TIM_ICSelection << 8); 
  /* Select the Polarity and set the CC2E Bit */
  tmpccer &= (uint16_t)~((uint16_t)(TIM_CCER_CC2P | TIM_CCER_CC2NP));
  tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CCER_CC2E);  
  /* Write to TIMx CCMR1 and CCER registers */
  TIMx->CCMR1 = tmpccmr1 ;
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI3 as Input.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.   
  * @param  TIM_ICPolarity: The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICSelection_DirectTI: TIM Input 3 is selected to be connected to IC3.
  *            @arg TIM_ICSelection_IndirectTI: TIM Input 3 is selected to be connected to IC4.
  *            @arg TIM_ICSelection_TRC: TIM Input 3 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI3_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;
  /* Disable the Channel 3: Reset the CC3E Bit */
  TIMx->CCER &= (uint16_t)~((uint16_t)TIM_CCER_CC3E);
  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 8);
  /* Select the Input and set the filter */
  tmpccmr2 &= (uint16_t)(((uint16_t)~((uint16_t)TIM_CCMR2_CC3S)) & ((uint16_t)~((uint16_t)TIM_CCMR2_IC3F)));
  tmpccmr2 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));
  /* Select the Polarity and set the CC3E Bit */
  tmpccer &= (uint16_t)~((uint16_t)(TIM_CCER_CC3P | TIM_CCER_CC3NP));
  tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CCER_CC3E);  
  /* Write to TIMx CCMR2 and CCER registers */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI4 as Input.
  * @param  TIMx: where x can be 1, 2 or 3 to select the TIM peripheral.
  * @note   TIM2 is not applicable for STM32F030 devices.  
  * @param  TIM_ICPolarity: The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICSelection_DirectTI: TIM Input 4 is selected to be connected to IC4.
  *            @arg TIM_ICSelection_IndirectTI: TIM Input 4 is selected to be connected to IC3.
  *            @arg TIM_ICSelection_TRC: TIM Input 4 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI4_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

   /* Disable the Channel 4: Reset the CC4E Bit */
  TIMx->CCER &= (uint16_t)~((uint16_t)TIM_CCER_CC4E);
  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 12);
  /* Select the Input and set the filter */
  tmpccmr2 &= (uint16_t)((uint16_t)(~(uint16_t)TIM_CCMR2_CC4S) & ((uint16_t)~((uint16_t)TIM_CCMR2_IC4F)));
  tmpccmr2 |= (uint16_t)(TIM_ICSelection << 8);
  tmpccmr2 |= (uint16_t)(TIM_ICFilter << 12);  
  /* Select the Polarity and set the CC4E Bit */
  tmpccer &= (uint16_t)~((uint16_t)(TIM_CCER_CC4P | TIM_CCER_CC4NP));
  tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CCER_CC4E);
  /* Write to TIMx CCMR2 and CCER registers */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_usart.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Universal synchronous asynchronous receiver
  *          transmitter (USART):
  *           + Initialization and Configuration
  *           + STOP Mode
  *           + AutoBaudRate
  *           + Data transfers
  *           + Multi-Processor Communication
  *           + LIN mode
  *           + Half-duplex mode
  *           + Smartcard mode
  *           + IrDA mode
  *           + RS485 mode  
  *           + DMA transfers management
  *           + Interrupts and flags management
  *           
  *  @verbatim
 ===============================================================================
                       ##### How to use this driver #####
 ===============================================================================
    [..]
        (#) Enable peripheral clock using RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE)
            function for USART1 or using RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE)
            function for USART2 and USART3.
        (#) According to the USART mode, enable the GPIO clocks using 
            RCC_AHBPeriphClockCmd() function. (The I/O can be TX, RX, CTS, 
            or and SCLK). 
        (#) Peripheral's alternate function: 
            (++) Connect the pin to the desired peripherals' Alternate 
                 Function (AF) using GPIO_PinAFConfig() function.
            (++) Configure the desired pin in alternate function by:
                 GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
            (++) Select the type, pull-up/pull-down and output speed via 
                 GPIO_PuPd, GPIO_OType and GPIO_Speed members.
            (++) Call GPIO_Init() function.        
        (#) Program the Baud Rate, Word Length , Stop Bit, Parity, Hardware 
            flow control and Mode(Receiver/Transmitter) using the SPI_Init()
            function.  
        (#) For synchronous mode, enable the clock and program the polarity,
            phase and last bit using the USART_ClockInit() function.  
        (#) Enable the NVIC and the corresponding interrupt using the function 
            USART_ITConfig() if you need to use interrupt mode.   
        (#) When using the DMA mode: 
            (++) Configure the DMA using DMA_Init() function.
            (++) Active the needed channel Request using USART_DMACmd() function.   
        (#) Enable the USART using the USART_Cmd() function.   
        (#) Enable the DMA using the DMA_Cmd() function, when using DMA mode.   
    [..]
            Refer to Multi-Processor, LIN, half-duplex, Smartcard, IrDA sub-sections
            for more details.
            
@endverbatim
       
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup USART 
  * @brief USART driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*!< USART CR1 register clear Mask ((~(uint32_t)0xFFFFE6F3)) */
#define CR1_CLEAR_MASK_USART            ((uint32_t)(USART_CR1_M | USART_CR1_PCE | \
                                              USART_CR1_PS | USART_CR1_TE | \
                                              USART_CR1_RE))

/*!< USART CR2 register clock bits clear Mask ((~(uint32_t)0xFFFFF0FF)) */
#define CR2_CLOCK_CLEAR_MASK_USART      ((uint32_t)(USART_CR2_CLKEN | USART_CR2_CPOL | \
                                              USART_CR2_CPHA | USART_CR2_LBCL))

/*!< USART CR3 register clear Mask ((~(uint32_t)0xFFFFFCFF)) */
#define CR3_CLEAR_MASK            ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))

/*!< USART Interrupts mask */
#define IT_MASK                   ((uint32_t)0x000000FF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup USART_Private_Functions
  * @{
  */

/** @defgroup USART_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
          ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
        This subsection provides a set of functions allowing to initialize the USART 
        in asynchronous and in synchronous modes.
        (+) For the asynchronous mode only these parameters can be configured: 
          (++) Baud Rate.
          (++) Word Length.
          (++) Stop Bit.
          (++) Parity: If the parity is enabled, then the MSB bit of the data written
               in the data register is transmitted but is changed by the parity bit.
               Depending on the frame length defined by the M bit (8-bits or 9-bits),
               the possible USART frame formats are as listed in the following table:

   +-------------------------------------------------------------+     
   |   M bit |  PCE bit  |            USART frame                |
   |---------------------|---------------------------------------|             
   |    0    |    0      |    | SB | 8 bit data | STB |          |
   |---------|-----------|---------------------------------------|  
   |    0    |    1      |    | SB | 7 bit data | PB | STB |     |
   |---------|-----------|---------------------------------------|  
   |    1    |    0      |    | SB | 9 bit data | STB |          |
   |---------|-----------|---------------------------------------|  
   |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
   +-------------------------------------------------------------+            

          (++) Hardware flow control.
          (++) Receiver/transmitter modes.
    [..] The USART_Init() function follows the USART  asynchronous configuration 
         procedure(details for the procedure are available in reference manual.
        (+) For the synchronous mode in addition to the asynchronous mode parameters
            these parameters should be also configured:
            (++) USART Clock Enabled.
            (++) USART polarity.
            (++) USART phase.
            (++) USART LastBit.
    [..] These parameters can be configured using the USART_ClockInit() function.

@endverbatim
  * @{
  */
  
/**
  * @brief  Deinitializes the USARTx peripheral registers to their default reset values.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices.  
  * @note   USART2 is not available for STM32F031 devices.
  * @retval None
  */
void USART_DeInit(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  if (USARTx == USART1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
  }
  else if (USARTx == USART2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
  }
  else if (USARTx == USART3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
  }
    else if (USARTx == USART4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART4, DISABLE);
  }
  else if (USARTx == USART5)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART5, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART5, DISABLE);
  }
    else if (USARTx == USART6)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, DISABLE);
  }
  else if (USARTx == USART7)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART7, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART7, DISABLE);
  }
  else 
  {
    if  (USARTx == USART8)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART8, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART8, DISABLE);
    }
  }
}

/**
  * @brief  Initializes the USARTx peripheral according to the specified
  *         parameters in the USART_InitStruct .
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.    
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that contains
  *         the configuration information for the specified USART peripheral.
  * @retval None
  */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t divider = 0, apbclock = 0, tmpreg = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));  
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
  
  /* Disable USART */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);
  
  /*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear STOP[13:12] bits */
  tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);
  
  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
  /* Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;
  
  /* Write to USART CR2 */
  USARTx->CR2 = tmpreg;
  
  /*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR1_CLEAR_MASK_USART);
  
  /* Configure the USART Word Length, Parity and mode ----------------------- */
  /* Set the M bits according to USART_WordLength value */
  /* Set PCE and PS bits according to USART_Parity value */
  /* Set TE and RE bits according to USART_Mode value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
    USART_InitStruct->USART_Mode;
  
  /* Write to USART CR1 */
  USARTx->CR1 = tmpreg;
  
  /*---------------------------- USART CR3 Configuration -----------------------*/  
  tmpreg = USARTx->CR3;
  /* Clear CTSE and RTSE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR3_CLEAR_MASK);
  
  /* Configure the USART HFC -------------------------------------------------*/
  /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  
  /* Write to USART CR3 */
  USARTx->CR3 = tmpreg;
  
  /*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  
  if (USARTx == USART1)
  {
    apbclock = RCC_ClocksStatus.USART1CLK_Frequency;
  }
  else if (USARTx == USART2)
  {
    apbclock = RCC_ClocksStatus.USART2CLK_Frequency;
  }
   else if (USARTx == USART3)
  {
    apbclock = RCC_ClocksStatus.USART3CLK_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK_Frequency;
  }
  
  /* Determine the integer part */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* (divider * 10) computing in case Oversampling mode is 8 Samples */
    divider = (uint32_t)((2 * apbclock) / (USART_InitStruct->USART_BaudRate));
    tmpreg  = (uint32_t)((2 * apbclock) % (USART_InitStruct->USART_BaudRate));
  }
  else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
  {
    /* (divider * 10) computing in case Oversampling mode is 16 Samples */
    divider = (uint32_t)((apbclock) / (USART_InitStruct->USART_BaudRate));
    tmpreg  = (uint32_t)((apbclock) % (USART_InitStruct->USART_BaudRate));
  }
  
  /* round the divider : if fractional part i greater than 0.5 increment divider */
  if (tmpreg >=  (USART_InitStruct->USART_BaudRate) / 2)
  {
    divider++;
  } 
  
  /* Implement the divider in case Oversampling mode is 8 Samples */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* get the LSB of divider and shift it to the right by 1 bit */
    tmpreg = (divider & (uint16_t)0x000F) >> 1;
    
    /* update the divider value */
    divider = (divider & (uint16_t)0xFFF0) | tmpreg;
  }
  
  /* Write to USART BRR */
  USARTx->BRR = (uint16_t)divider;
}

/**
  * @brief  Fills each USART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  /* USART_InitStruct members default value */
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_WordLength = USART_WordLength_8b;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity = USART_Parity_No ;
  USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
}

/**
  * @brief  Initializes the USARTx peripheral Clock according to the 
  *         specified parameters in the USART_ClockInitStruct.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.   
  * @param  USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
  *         structure that contains the configuration information for the specified 
  *         USART peripheral.  
  * @retval None
  */
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));
/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear CLKEN, CPOL, CPHA, LBCL and SSM bits */
  tmpreg &= (uint32_t)~((uint32_t)CR2_CLOCK_CLEAR_MASK_USART);
  /* Configure the USART Clock, CPOL, CPHA, LastBit and SSM ------------*/
  /* Set CLKEN bit according to USART_Clock value */
  /* Set CPOL bit according to USART_CPOL value */
  /* Set CPHA bit according to USART_CPHA value */
  /* Set LBCL bit according to USART_LastBit value */
  tmpreg |= (uint32_t)(USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL | 
                       USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit);
  /* Write to USART CR2 */
  USARTx->CR2 = tmpreg;
}

/**
  * @brief  Fills each USART_ClockInitStruct member with its default value.
  * @param  USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
  *         structure which will be initialized.
  * @retval None
  */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct members default value */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
  * @brief  Enables or disables the specified USART peripheral.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.    
  * @param  NewState: new state of the USARTx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_UE;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);
  }
}

/**
  * @brief  Enables or disables the USART's transmitter or receiver.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_Direction: specifies the USART direction.
  *          This parameter can be any combination of the following values:
  *            @arg USART_Mode_Tx: USART Transmitter
  *            @arg USART_Mode_Rx: USART Receiver
  * @param  NewState: new state of the USART transfer direction.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void USART_DirectionModeCmd(USART_TypeDef* USARTx, uint32_t USART_DirectionMode, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_MODE(USART_DirectionMode));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the USART's transfer interface by setting the TE and/or RE bits 
       in the USART CR1 register */
    USARTx->CR1 |= USART_DirectionMode;
  }
  else
  {
    /* Disable the USART's transfer interface by clearing the TE and/or RE bits
       in the USART CR3 register */
    USARTx->CR1 &= (uint32_t)~USART_DirectionMode;
  }
}

/**
  * @brief  Enables or disables the USART's 8x oversampling mode.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  NewState: new state of the USART 8x oversampling mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called before calling USART_Init() function
  *         in order to have correct baudrate Divider value.
  * @retval None
  */
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the 8x Oversampling mode by setting the OVER8 bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_OVER8;
  }
  else
  {
    /* Disable the 8x Oversampling mode by clearing the OVER8 bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_OVER8);
  }
}  

/**
  * @brief  Enables or disables the USART's one bit sampling method.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  NewState: new state of the USART one bit sampling method.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the one bit method by setting the ONEBITE bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_ONEBIT;
  }
  else
  {
    /* Disable the one bit method by clearing the ONEBITE bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_ONEBIT);
  }
}

/**
  * @brief  Enables or disables the USART's most significant bit first 
  *         transmitted/received following the start bit.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  NewState: new state of the USART most significant bit first
  *         transmitted/received following the start bit.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_MSBFirstCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the most significant bit first transmitted/received following the 
       start bit by setting the MSBFIRST bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_MSBFIRST;
  }
  else
  {
    /* Disable the most significant bit first transmitted/received following the 
       start bit by clearing the MSBFIRST bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_MSBFIRST);
  }
}

/**
  * @brief  Enables or disables the binary data inversion.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  NewState: new defined levels for the USART data.
  *          This parameter can be:
  *            @arg ENABLE: Logical data from the data register are send/received in negative
  *                          logic (1=L, 0=H). The parity bit is also inverted.
  *            @arg DISABLE: Logical data from the data register are send/received in positive
  *                          logic (1=H, 0=L) 
  * @note   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_DataInvCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the binary data inversion feature by setting the DATAINV bit in 
       the CR2 register */
    USARTx->CR2 |= USART_CR2_DATAINV;
  }
  else
  {
    /* Disable the binary data inversion feature by clearing the DATAINV bit in 
       the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_DATAINV);
  }
}

/**
  * @brief  Enables or disables the Pin(s) active level inversion.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_InvPin: specifies the USART pin(s) to invert.
  *          This parameter can be any combination of the following values:
  *            @arg USART_InvPin_Tx: USART Tx pin active level inversion.
  *            @arg USART_InvPin_Rx: USART Rx pin active level inversion.
  * @param  NewState: new active level status for the USART pin(s).
  *          This parameter can be:
  *            @arg ENABLE: pin(s) signal values are inverted (Vdd =0, Gnd =1).
  *            @arg DISABLE: pin(s) signal works using the standard logic levels (Vdd =1, Gnd =0).
  * @note   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_InvPinCmd(USART_TypeDef* USARTx, uint32_t USART_InvPin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_INVERSTION_PIN(USART_InvPin));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the active level inversion for selected pins by setting the TXINV 
       and/or RXINV bits in the USART CR2 register */
    USARTx->CR2 |= USART_InvPin;
  }
  else
  {
    /* Disable the active level inversion for selected requests by clearing the 
       TXINV and/or RXINV bits in the USART CR2 register */
    USARTx->CR2 &= (uint32_t)~USART_InvPin;
  }
}

/**
  * @brief  Enables or disables the swap Tx/Rx pins.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  NewState: new state of the USARTx TX/RX pins pinout.
  *          This parameter can be:
  *            @arg ENABLE: The TX and RX pins functions are swapped.
  *            @arg DISABLE: TX/RX pins are used as defined in standard pinout
  * @note   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_SWAPPinCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SWAP feature by setting the SWAP bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_SWAP;
  }
  else
  {
    /* Disable the SWAP feature by clearing the SWAP bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_SWAP);
  }
}

/**
  * @brief  Enables or disables the receiver Time Out feature.
  * @param  USARTx: where x can be 1, 2 or 3 to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.  
  * @param  NewState: new state of the USARTx receiver Time Out.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ReceiverTimeOutCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the receiver time out feature by setting the RTOEN bit in the CR2 
       register */
    USARTx->CR2 |= USART_CR2_RTOEN;
  }
  else
  {
    /* Disable the receiver time out feature by clearing the RTOEN bit in the CR2 
       register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_RTOEN);
  }
}

/**
  * @brief  Sets the receiver Time Out value.
  * @param  USARTx: where x can be 1, 2 or 3 to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.   
  * @param  USART_ReceiverTimeOut: specifies the Receiver Time Out value.
  * @retval None
  */
void USART_SetReceiverTimeOut(USART_TypeDef* USARTx, uint32_t USART_ReceiverTimeOut)
{    
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_TIMEOUT(USART_ReceiverTimeOut));

  /* Clear the receiver Time Out value by clearing the RTO[23:0] bits in the RTOR
     register  */
  USARTx->RTOR &= (uint32_t)~((uint32_t)USART_RTOR_RTO);
  /* Set the receiver Time Out value by setting the RTO[23:0] bits in the RTOR
     register  */
  USARTx->RTOR |= USART_ReceiverTimeOut;
}

/**
  * @brief  Sets the system clock prescaler.
  * @note   This function is not available for STM32F030 devices.    
  * @param  USARTx: where x can be 1, 2 or 3 to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices. 
  * @param  USART_Prescaler: specifies the prescaler clock.
  * @note   This function has to be called before calling USART_Cmd() function.    
  * @retval None
  */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{ 
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  
  /* Clear the USART prescaler */
  USARTx->GTPR &= USART_GTPR_GT;
  /* Set the USART prescaler */
  USARTx->GTPR |= USART_Prescaler;
}

/**
  * @}
  */


/** @defgroup USART_Group2 STOP Mode functions
 *  @brief   STOP Mode functions
 *
@verbatim
 ===============================================================================
                        ##### STOP Mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage 
         WakeUp from STOP mode.

    [..] The USART is able to WakeUp from Stop Mode if USART clock is set to HSI
         or LSI.
         
    [..] The WakeUp source is configured by calling USART_StopModeWakeUpSourceConfig()
         function.
         
    [..] After configuring the source of WakeUp and before entering in Stop Mode 
         USART_STOPModeCmd() function should be called to allow USART WakeUp.
                           
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified USART peripheral in STOP Mode.
  * @param  USARTx: where x can be 1 or 2 or 3  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices.  
  * @note   USART3 is available only for STM32F091 devices.   
  * @param  NewState: new state of the USARTx peripheral state in stop mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called when USART clock is set to HSI or LSE. 
  * @retval None
  */
void USART_STOPModeCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected USART in STOP mode by setting the UESM bit in the CR1
       register */
    USARTx->CR1 |= USART_CR1_UESM;
  }
  else
  {
    /* Disable the selected USART in STOP mode by clearing the UE bit in the CR1
       register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UESM);
  }
}

/**
  * @brief  Selects the USART WakeUp method form stop mode.
  * @note   This function is not available for STM32F030 devices.   
  * @param  USARTx: where x can be 1 or 2 or 3 to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.     
  * @param  USART_WakeUp: specifies the selected USART wakeup method.
  *          This parameter can be one of the following values:
  *            @arg USART_WakeUpSource_AddressMatch: WUF active on address match.
  *            @arg USART_WakeUpSource_StartBit: WUF active on Start bit detection.
  *            @arg USART_WakeUpSource_RXNE: WUF active on RXNE.
  * @note   This function has to be called before calling USART_Cmd() function.   
  * @retval None
  */
void USART_StopModeWakeUpSourceConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUpSource)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_STOPMODE_WAKEUPSOURCE(USART_WakeUpSource));

  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_WUS);
  USARTx->CR3 |= USART_WakeUpSource;
}

/**
  * @}
  */


/** @defgroup USART_Group3 AutoBaudRate functions
 *  @brief   AutoBaudRate functions 
 *
@verbatim
 ===============================================================================
                       ##### AutoBaudRate functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage 
         the AutoBaudRate detections.
         
    [..] Before Enabling AutoBaudRate detection using USART_AutoBaudRateCmd ()
         The character patterns used to calculate baudrate must be chosen by calling 
         USART_AutoBaudRateConfig() function. These function take as parameter :
        (#)USART_AutoBaudRate_StartBit : any character starting with a bit 1.
        (#)USART_AutoBaudRate_FallingEdge : any character starting with a 10xx bit pattern. 
                          
    [..] At any later time, another request for AutoBaudRate detection can be performed
         using USART_RequestCmd() function.
         
    [..] The AutoBaudRate detection is monitored by the status of ABRF flag which indicate
         that the AutoBaudRate detection is completed. In addition to ABRF flag, the ABRE flag
         indicate that this procedure is completed without success. USART_GetFlagStatus () 
         function should be used to monitor the status of these flags.  
             
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the Auto Baud Rate.
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.  
  * @param  NewState: new state of the USARTx auto baud rate.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_AutoBaudRateCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the auto baud rate feature by setting the ABREN bit in the CR2 
       register */
    USARTx->CR2 |= USART_CR2_ABREN;
  }
  else
  {
    /* Disable the auto baud rate feature by clearing the ABREN bit in the CR2 
       register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ABREN);
  }
}

/**
  * @brief  Selects the USART auto baud rate method.
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.  
  * @param  USART_AutoBaudRate: specifies the selected USART auto baud rate method.
  *          This parameter can be one of the following values:
  *            @arg USART_AutoBaudRate_StartBit: Start Bit duration measurement.
  *            @arg USART_AutoBaudRate_FallingEdge: Falling edge to falling edge measurement.
  * @note   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_AutoBaudRateConfig(USART_TypeDef* USARTx, uint32_t USART_AutoBaudRate)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_AUTOBAUDRATE_MODE(USART_AutoBaudRate));

  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ABRMODE);
  USARTx->CR2 |= USART_AutoBaudRate;
}

/**
  * @}
  */


/** @defgroup USART_Group4 Data transfers functions
 *  @brief   Data transfers functions 
 *
@verbatim   
 ===============================================================================
                    ##### Data transfers functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage 
         the USART data transfers.
    [..] During an USART reception, data shifts in least significant bit first 
         through the RX pin. When a transmission is taking place, a write instruction to 
         the USART_TDR register stores the data in the shift register.
    [..] The read access of the USART_RDR register can be done using 
         the USART_ReceiveData() function and returns the RDR value.
         Whereas a write access to the USART_TDR can be done using USART_SendData()
         function and stores the written data into TDR.

@endverbatim
  * @{
  */

/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  Data: the data to transmit.
  * @retval None
  */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data)); 
    
  /* Transmit Data */
  USARTx->TDR = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the USARTx peripheral.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.   
  * @retval The received data.
  */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* Receive Data */
  return (uint16_t)(USARTx->RDR & (uint16_t)0x01FF);
}

/**
  * @}
  */

/** @defgroup USART_Group5 MultiProcessor Communication functions
 *  @brief   Multi-Processor Communication functions 
 *
@verbatim   
 ===============================================================================
             ##### Multi-Processor Communication functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         multiprocessor communication.
    [..] For instance one of the USARTs can be the master, its TX output is
         connected to the RX input of the other USART. The others are slaves,
         their respective TX outputs are logically ANDed together and connected 
         to the RX input of the master. USART multiprocessor communication is 
         possible through the following procedure:
         (#) Program the Baud rate, Word length = 9 bits, Stop bits, Parity, 
             Mode transmitter or Mode receiver and hardware flow control values 
             using the USART_Init() function.
         (#) Configures the USART address using the USART_SetAddress() function.
         (#) Configures the wake up methode (USART_WakeUp_IdleLine or 
             USART_WakeUp_AddressMark) using USART_WakeUpConfig() function only 
             for the slaves.
         (#) Enable the USART using the USART_Cmd() function.
         (#) Enter the USART slaves in mute mode using USART_ReceiverWakeUpCmd() 
             function.
    [..] The USART Slave exit from mute mode when receive the wake up condition.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the address of the USART node.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.   
  * @param  USART_Address: Indicates the address of the USART node.
  * @retval None
  */
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* Clear the USART address */
  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ADD);
  /* Set the USART address node */
  USARTx->CR2 |=((uint32_t)USART_Address << (uint32_t)0x18);
}

/**
  * @brief  Enables or disables the USART's mute mode.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  NewState: new state of the USART mute mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_MuteModeCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState != DISABLE)
  {
    /* Enable the USART mute mode by setting the MME bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_MME;
  }
  else
  {
    /* Disable the USART mute mode by clearing the MME bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_MME);
  }
}

/**
  * @brief  Selects the USART WakeUp method from mute mode.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.   
  * @param  USART_WakeUp: specifies the USART wakeup method.
  *          This parameter can be one of the following values:
  *            @arg USART_WakeUp_IdleLine: WakeUp by an idle line detection
  *            @arg USART_WakeUp_AddressMark: WakeUp by an address mark
  * @retval None
  */
void USART_MuteModeWakeUpConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUp)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_MUTEMODE_WAKEUP(USART_WakeUp));

  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_WAKE);
  USARTx->CR1 |= USART_WakeUp;
}

/**
  * @brief  Configure the the USART Address detection length.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_AddressLength: specifies the USART address length detection.
  *          This parameter can be one of the following values:
  *            @arg USART_AddressLength_4b: 4-bit address length detection 
  *            @arg USART_AddressLength_7b: 7-bit address length detection 
  * @retval None
  */
void USART_AddressDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_AddressLength)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS_DETECTION(USART_AddressLength));

  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ADDM7);
  USARTx->CR2 |= USART_AddressLength;
}

/**
  * @}
  */

/** @defgroup USART_Group6 LIN mode functions
 *  @brief   LIN mode functions 
 *
@verbatim   
 ===============================================================================
                       ##### LIN mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART 
         LIN Mode communication.
    [..] In LIN mode, 8-bit data format with 1 stop bit is required in accordance 
         with the LIN standard.
    [..] Only this LIN Feature is supported by the USART IP:
         (+) LIN Master Synchronous Break send capability and LIN slave break 
             detection capability :  13-bit break generation and 10/11 bit break 
             detection.
    [..] USART LIN Master transmitter communication is possible through the 
         following procedure:
         (#) Program the Baud rate, Word length = 8bits, Stop bits = 1bit, Parity, 
             Mode transmitter or Mode receiver and hardware flow control values 
             using the USART_Init() function.
         (#) Enable the LIN mode using the USART_LINCmd() function.
         (#) Enable the USART using the USART_Cmd() function.
         (#) Send the break character using USART_SendBreak() function.
    [..] USART LIN Master receiver communication is possible through the 
         following procedure:
         (#) Program the Baud rate, Word length = 8bits, Stop bits = 1bit, Parity, 
             Mode transmitter or Mode receiver and hardware flow control values 
             using the USART_Init() function.
         (#) Configures the break detection length 
             using the USART_LINBreakDetectLengthConfig() function.
         (#) Enable the LIN mode using the USART_LINCmd() function.
         -@- In LIN mode, the following bits must be kept cleared:
             (+@) CLKEN in the USART_CR2 register.
             (+@) STOP[1:0], SCEN, HDSEL and IREN in the USART_CR3 register.
         (#) Enable the USART using the USART_Cmd() function.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the USART LIN Break detection length.
  * @note   This function is not available for STM32F030 devices.  
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.
  * @param  USART_LINBreakDetectLength: specifies the LIN break detection length.
  *          This parameter can be one of the following values:
  *            @arg USART_LINBreakDetectLength_10b: 10-bit break detection
  *            @arg USART_LINBreakDetectLength_11b: 11-bit break detection
  * @retval None
  */
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint32_t USART_LINBreakDetectLength)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));

  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_LBDL);
  USARTx->CR2 |= USART_LINBreakDetectLength;  
}

/**
  * @brief  Enables or disables the USART's LIN mode.
  * @note   This function is not available for STM32F030 devices.
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.  
  * @param  NewState: new state of the USART LIN mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the LIN mode by setting the LINEN bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_LINEN;
  }
  else
  {
    /* Disable the LIN mode by clearing the LINEN bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_LINEN);
  }
}

/**
  * @}
  */

/** @defgroup USART_Group7 Halfduplex mode function
 *  @brief   Half-duplex mode function 
 *
@verbatim   
 ===============================================================================
                   ##### Half-duplex mode function #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         Half-duplex communication.
    [..] The USART can be configured to follow a single-wire half-duplex protocol 
         where the TX and RX lines are internally connected.
    [..] USART Half duplex communication is possible through the following procedure:
         (#) Program the Baud rate, Word length, Stop bits, Parity, Mode transmitter 
             or Mode receiver and hardware flow control values using the USART_Init()
            function.
         (#) Configures the USART address using the USART_SetAddress() function.
         (#) Enable the half duplex mode using USART_HalfDuplexCmd() function.
         (#) Enable the USART using the USART_Cmd() function.
         -@- The RX pin is no longer used.
         -@- In Half-duplex mode the following bits must be kept cleared:
             (+@) LINEN and CLKEN bits in the USART_CR2 register.
             (+@) SCEN and IREN bits in the USART_CR3 register.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the USART's Half Duplex communication.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.    
  * @param  NewState: new state of the USART Communication.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Half-Duplex mode by setting the HDSEL bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_HDSEL;
  }
  else
  {
    /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_HDSEL);
  }
}

/**
  * @}
  */


/** @defgroup USART_Group8 Smartcard mode functions
 *  @brief   Smartcard mode functions 
 *
@verbatim   
 ===============================================================================
                     ##### Smartcard mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         Smartcard communication.
    [..] The Smartcard interface is designed to support asynchronous protocol 
         Smartcards as defined in the ISO 7816-3 standard. The USART can provide 
         a clock to the smartcard through the SCLK output. In smartcard mode, 
         SCLK is not associated to the communication but is simply derived from 
         the internal peripheral input clock through a 5-bit prescaler.
    [..] Smartcard communication is possible through the following procedure:
         (#) Configures the Smartcard PrSecler using the USART_SetPrescaler() 
             function.
         (#) Configures the Smartcard Guard Time using the USART_SetGuardTime() 
             function.
         (#) Program the USART clock using the USART_ClockInit() function as following:
             (++) USART Clock enabled.
             (++) USART CPOL Low.
             (++) USART CPHA on first edge.
             (++) USART Last Bit Clock Enabled.
         (#) Program the Smartcard interface using the USART_Init() function as 
             following:
             (++) Word Length = 9 Bits.
             (++) 1.5 Stop Bit.
             (++) Even parity.
             (++) BaudRate = 12096 baud.
             (++) Hardware flow control disabled (RTS and CTS signals).
             (++) Tx and Rx enabled
         (#) Optionally you can enable the parity error interrupt using 
             the USART_ITConfig() function.
         (#) Enable the Smartcard NACK using the USART_SmartCardNACKCmd() function.
         (#) Enable the Smartcard interface using the USART_SmartCardCmd() function.
         (#) Enable the USART using the USART_Cmd() function.
    [..] 
  Please refer to the ISO 7816-3 specification for more details.
    [..] 
         (@) It is also possible to choose 0.5 stop bit for receiving but it is 
             recommended to use 1.5 stop bits for both transmitting and receiving 
             to avoid switching between the two configurations.
         (@) In smartcard mode, the following bits must be kept cleared:
             (+@) LINEN bit in the USART_CR2 register.
             (+@) HDSEL and IREN bits in the USART_CR3 register.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the specified USART guard time.
  * @note   This function is not available for STM32F030 devices.  
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices. 
  * @param  USART_GuardTime: specifies the guard time.
  * @retval None
  */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{    
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));

  /* Clear the USART Guard time */
  USARTx->GTPR &= USART_GTPR_PSC;
  /* Set the USART guard time */
  USARTx->GTPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

/**
  * @brief  Enables or disables the USART's Smart Card mode.
  * @note   This function is not available for STM32F030 devices.  
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices. 
  * @param  NewState: new state of the Smart Card mode.
  *          This parameter can be: ENABLE or DISABLE.      
  * @retval None
  */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the SC mode by setting the SCEN bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_SCEN;
  }
  else
  {
    /* Disable the SC mode by clearing the SCEN bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_SCEN);
  }
}

/**
  * @brief  Enables or disables NACK transmission.
  * @note   This function is not available for STM32F030 devices.  
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.
  * @param  NewState: new state of the NACK transmission.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the NACK transmission by setting the NACK bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_NACK;
  }
  else
  {
    /* Disable the NACK transmission by clearing the NACK bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_NACK);
  }
}

/**
  * @brief  Sets the Smart Card number of retries in transmit and receive.
  * @note   This function is not available for STM32F030 devices.  
  * @param  USARTx: where x can be 1or 3  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.
  * @param  USART_AutoCount: specifies the Smart Card auto retry count.
  * @retval None
  */
void USART_SetAutoRetryCount(USART_TypeDef* USARTx, uint8_t USART_AutoCount)
{    
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_AUTO_RETRY_COUNTER(USART_AutoCount));
  /* Clear the USART auto retry count */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_SCARCNT);
  /* Set the USART auto retry count*/
  USARTx->CR3 |= (uint32_t)((uint32_t)USART_AutoCount << 0x11);
}

/**
  * @brief  Sets the Smart Card Block length.
  * @note   This function is not available for STM32F030 devices.  
  * @param  USARTx: where x can be 1or 3  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.
  * @param  USART_BlockLength: specifies the Smart Card block length.
  * @retval None
  */
void USART_SetBlockLength(USART_TypeDef* USARTx, uint8_t USART_BlockLength)
{    
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));

  /* Clear the Smart card block length */
  USARTx->RTOR &= (uint32_t)~((uint32_t)USART_RTOR_BLEN);
  /* Set the Smart Card block length */
  USARTx->RTOR |= (uint32_t)((uint32_t)USART_BlockLength << 0x18);
}

/**
  * @}
  */

/** @defgroup USART_Group9 IrDA mode functions
 *  @brief   IrDA mode functions 
 *
@verbatim   
 ===============================================================================
                        ##### IrDA mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         IrDA communication.
    [..] IrDA is a half duplex communication protocol. If the Transmitter is busy, 
         any data on the IrDA receive line will be ignored by the IrDA decoder 
         and if the Receiver is busy, data on the TX from the USART to IrDA will 
         not be encoded by IrDA. While receiving data, transmission should be 
         avoided as the data to be transmitted could be corrupted.
    [..] IrDA communication is possible through the following procedure:
         (#) Program the Baud rate, Word length = 8 bits, Stop bits, Parity, 
             Transmitter/Receiver modes and hardware flow control values using 
             the USART_Init() function.
         (#) Configures the IrDA pulse width by configuring the prescaler using  
             the USART_SetPrescaler() function.
         (#) Configures the IrDA  USART_IrDAMode_LowPower or USART_IrDAMode_Normal 
             mode using the USART_IrDAConfig() function.
         (#) Enable the IrDA using the USART_IrDACmd() function.
         (#) Enable the USART using the USART_Cmd() function.         
    [..]
    (@) A pulse of width less than two and greater than one PSC period(s) may or 
        may not be rejected.
    (@) The receiver set up time should be managed by software. The IrDA physical 
        layer specification specifies a minimum of 10 ms delay between 
        transmission and reception (IrDA is a half duplex protocol).
    (@) In IrDA mode, the following bits must be kept cleared:
        (+@) LINEN, STOP and CLKEN bits in the USART_CR2 register.
        (+@) SCEN and HDSEL bits in the USART_CR3 register.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the USART's IrDA interface.
  * @note   This function is not available for STM32F030 devices.  
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices.
  * @param  USART_IrDAMode: specifies the IrDA mode.
  *          This parameter can be one of the following values:
  *            @arg USART_IrDAMode_LowPower
  *            @arg USART_IrDAMode_Normal
  * @retval None
  */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint32_t USART_IrDAMode)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));

  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_IRLP);
  USARTx->CR3 |= USART_IrDAMode;
}

/**
  * @brief  Enables or disables the USART's IrDA interface.
  * @note   This function is not available for STM32F030 devices.  
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @note   USART2 is available only for STM32F072 and STM32F091 devices. 
  * @note   USART3 is available only for STM32F091 devices. 
  * @param  NewState: new state of the IrDA mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_IREN;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_IREN);
  }
}
/**
  * @}
  */

/** @defgroup USART_Group10 RS485 mode function
 *  @brief  RS485 mode function 
 *
@verbatim  
 ===============================================================================
                        ##### RS485 mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         RS485 flow control.
    [..] RS485 flow control (Driver enable feature) handling is possible through
         the following procedure:
         (#) Program the Baud rate, Word length = 8 bits, Stop bits, Parity, 
             Transmitter/Receiver modes and hardware flow control values using 
             the USART_Init() function.
         (#) Enable the Driver Enable using the USART_DECmd() function.
         (#) Configures the Driver Enable polarity using the USART_DEPolarityConfig()
             function.
         (#) Configures the Driver Enable assertion time using USART_SetDEAssertionTime() 
             function and deassertion time using the USART_SetDEDeassertionTime()
             function.    
         (#) Enable the USART using the USART_Cmd() function.
      -@-  
       (+@) The assertion and dessertion times are expressed in sample time units (1/8 or 
            1/16 bit time, depending on the oversampling rate).
       
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the USART's DE functionality.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  NewState: new state of the driver enable mode.
  *          This parameter can be: ENABLE or DISABLE.      
  * @retval None
  */
void USART_DECmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the DE functionality by setting the DEM bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_DEM;
  }
  else
  {
    /* Disable the DE functionality by clearing the DEM bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DEM);
  }
}

/**
  * @brief  Configures the USART's DE polarity
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_DEPolarity: specifies the DE polarity.
  *          This parameter can be one of the following values:
  *            @arg USART_DEPolarity_Low
  *            @arg USART_DEPolarity_High
  * @retval None
  */
void USART_DEPolarityConfig(USART_TypeDef* USARTx, uint32_t USART_DEPolarity)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_POLARITY(USART_DEPolarity));

  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DEP);
  USARTx->CR3 |= USART_DEPolarity;
}

/**
  * @brief  Sets the specified RS485 DE assertion time
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_DEAssertionTime: specifies the time between the activation of
  *         the DE signal and the beginning of the start bit
  * @retval None
  */
void USART_SetDEAssertionTime(USART_TypeDef* USARTx, uint32_t USART_DEAssertionTime)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_ASSERTION_DEASSERTION_TIME(USART_DEAssertionTime)); 

  /* Clear the DE assertion time */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_DEAT);
  /* Set the new value for the DE assertion time */
  USARTx->CR1 |=((uint32_t)USART_DEAssertionTime << (uint32_t)0x15);
}

/**
  * @brief  Sets the specified RS485 DE deassertion time
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_DeassertionTime: specifies the time between the middle of the last 
  *         stop bit in a transmitted message and the de-activation of the DE signal
  * @retval None
  */
void USART_SetDEDeassertionTime(USART_TypeDef* USARTx, uint32_t USART_DEDeassertionTime)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_ASSERTION_DEASSERTION_TIME(USART_DEDeassertionTime)); 

  /* Clear the DE deassertion time */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_DEDT);
  /* Set the new value for the DE deassertion time */
  USARTx->CR1 |=((uint32_t)USART_DEDeassertionTime << (uint32_t)0x10);
}

/**
  * @}
  */

/** @defgroup USART_Group11 DMA transfers management functions
 *  @brief   DMA transfers management functions
 *
@verbatim   
 ===============================================================================
               ##### DMA transfers management functions #####
 ===============================================================================
    [..] This section provides two functions that can be used only in DMA mode.
    [..] In DMA Mode, the USART communication can be managed by 2 DMA Channel 
         requests:
         (#) USART_DMAReq_Tx: specifies the Tx buffer DMA transfer request.
         (#) USART_DMAReq_Rx: specifies the Rx buffer DMA transfer request.
    [..] In this Mode it is advised to use the following function:
         (+) void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, 
             FunctionalState NewState).
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the USART's DMA interface.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_DMAReq: specifies the DMA request.
  *          This parameter can be any combination of the following values:
  *            @arg USART_DMAReq_Tx: USART DMA transmit request
  *            @arg USART_DMAReq_Rx: USART DMA receive request
  * @param  NewState: new state of the DMA Request sources.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void USART_DMACmd(USART_TypeDef* USARTx, uint32_t USART_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DMAREQ(USART_DMAReq));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CR3 |= USART_DMAReq;
  }
  else
  {
    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CR3 &= (uint32_t)~USART_DMAReq;
  }
}

/**
  * @brief  Enables or disables the USART's DMA interface when reception error occurs.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_DMAOnError: specifies the DMA status in case of reception error.
  *          This parameter can be any combination of the following values:
  *            @arg USART_DMAOnError_Enable: DMA receive request enabled when the USART DMA  
  *                                          reception error is asserted.
  *            @arg USART_DMAOnError_Disable: DMA receive request disabled when the USART DMA 
  *                                           reception error is asserted.
  * @retval None
  */
void USART_DMAReceptionErrorConfig(USART_TypeDef* USARTx, uint32_t USART_DMAOnError)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DMAONERROR(USART_DMAOnError)); 
  
  /* Clear the DMA Reception error detection bit */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DDRE);
  /* Set the new value for the DMA Reception error detection bit */
  USARTx->CR3 |= USART_DMAOnError;
}

/**
  * @}
  */
  
/** @defgroup USART_Group12 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to configure the 
         USART Interrupts sources, Requests and check or clear the flags or pending bits status. 
         The user should identify which mode will be used in his application to 
         manage the communication: Polling mode, Interrupt mode.

 *** Polling Mode ***
 ====================
    [..] In Polling Mode, the SPI communication can be managed by these flags:
         (#) USART_FLAG_REACK: to indicate the status of the Receive Enable 
             acknowledge flag
         (#) USART_FLAG_TEACK: to indicate the status of the Transmit Enable 
             acknowledge flag.
         (#) USART_FLAG_WU: to indicate the status of the Wake up flag.
         (#) USART_FLAG_RWU: to indicate the status of the Receive Wake up flag.
         (#) USART_FLAG_SBK: to indicate the status of the Send Break flag.
         (#) USART_FLAG_CM: to indicate the status of the Character match flag.
         (#) USART_FLAG_BUSY: to indicate the status of the Busy flag.
         (#) USART_FLAG_ABRF: to indicate the status of the Auto baud rate flag.
         (#) USART_FLAG_ABRE: to indicate the status of the Auto baud rate error flag.
         (#) USART_FLAG_EOB: to indicate the status of the End of block flag.
         (#) USART_FLAG_RTO: to indicate the status of the Receive time out flag.
         (#) USART_FLAG_nCTSS: to indicate the status of the Inverted nCTS input 
             bit status.
         (#) USART_FLAG_TXE: to indicate the status of the transmit buffer register.
         (#) USART_FLAG_RXNE: to indicate the status of the receive buffer register.
         (#) USART_FLAG_TC: to indicate the status of the transmit operation.
         (#) USART_FLAG_IDLE: to indicate the status of the Idle Line.
         (#) USART_FLAG_CTS: to indicate the status of the nCTS input.
         (#) USART_FLAG_LBD: to indicate the status of the LIN break detection.
         (#) USART_FLAG_NE: to indicate if a noise error occur.
         (#) USART_FLAG_FE: to indicate if a frame error occur.
         (#) USART_FLAG_PE: to indicate if a parity error occur.
         (#) USART_FLAG_ORE: to indicate if an Overrun error occur.
    [..] In this Mode it is advised to use the following functions:
         (+) FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG).
         (+) void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG).

 *** Interrupt Mode ***
 ======================
    [..] In Interrupt Mode, the USART communication can be managed by 8 interrupt 
         sources and 10 pending bits:
         (+) Pending Bits:
             (##) USART_IT_WU: to indicate the status of the Wake up interrupt.
             (##) USART_IT_CM: to indicate the status of Character match interrupt.
             (##) USART_IT_EOB: to indicate the status of End of block interrupt.
             (##) USART_IT_RTO: to indicate the status of Receive time out interrupt.
             (##) USART_IT_CTS: to indicate the status of CTS change interrupt.
             (##) USART_IT_LBD: to indicate the status of LIN Break detection interrupt.
             (##) USART_IT_TC: to indicate the status of Transmission complete interrupt.
             (##) USART_IT_IDLE: to indicate the status of IDLE line detected interrupt.
             (##) USART_IT_ORE: to indicate the status of OverRun Error interrupt.
             (##) USART_IT_NE: to indicate the status of Noise Error interrupt.
             (##) USART_IT_FE: to indicate the status of Framing Error interrupt.
             (##) USART_IT_PE: to indicate the status of Parity Error interrupt.  

         (+) Interrupt Source:
             (##) USART_IT_WU: specifies the interrupt source for Wake up interrupt.
             (##) USART_IT_CM: specifies the interrupt source for Character match 
                  interrupt.
             (##) USART_IT_EOB: specifies the interrupt source for End of block
                  interrupt.
             (##) USART_IT_RTO: specifies the interrupt source for Receive time-out
                  interrupt.
             (##) USART_IT_CTS: specifies the interrupt source for CTS change interrupt.
             (##) USART_IT_LBD: specifies the interrupt source for LIN Break 
                  detection interrupt.
             (##) USART_IT_TXE: specifies the interrupt source for Tansmit Data 
                  Register empty interrupt.
             (##) USART_IT_TC: specifies the interrupt source for Transmission 
                  complete interrupt.
             (##) USART_IT_RXNE: specifies the interrupt source for Receive Data 
                  register not empty interrupt.
             (##) USART_IT_IDLE: specifies the interrupt source for Idle line 
                  detection interrupt.
             (##) USART_IT_PE: specifies the interrupt source for Parity Error interrupt.
             (##) USART_IT_ERR: specifies the interrupt source for Error interrupt
                  (Frame error, noise error, overrun error)
             -@@- Some parameters are coded in order to use them as interrupt 
                 source or as pending bits.
    [..] In this Mode it is advised to use the following functions:
         (+) void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState).
         (+) ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT).
         (+) void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_IT: specifies the USART interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_WU:  Wake up interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_CM:  Character match interrupt.
  *            @arg USART_IT_EOB:  End of block interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_RTO:  Receive time out interrupt.
  *            @arg USART_IT_CTS:  CTS change interrupt.
  *            @arg USART_IT_LBD:  LIN Break detection interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_TXE:  Tansmit Data Register empty interrupt.
  *            @arg USART_IT_TC:  Transmission complete interrupt.
  *            @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
  *            @arg USART_IT_IDLE:  Idle line detection interrupt.
  *            @arg USART_IT_PE:  Parity Error interrupt.
  *            @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @param  NewState: new state of the specified USARTx interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState)
{
  uint32_t usartreg = 0, itpos = 0, itmask = 0;
  uint32_t usartxbase = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  usartxbase = (uint32_t)USARTx;
  
  /* Get the USART register index */
  usartreg = (((uint16_t)USART_IT) >> 0x08);
  
  /* Get the interrupt position */
  itpos = USART_IT & IT_MASK;
  itmask = (((uint32_t)0x01) << itpos);
  
  if (usartreg == 0x02) /* The IT is in CR2 register */
  {
    usartxbase += 0x04;
  }
  else if (usartreg == 0x03) /* The IT is in CR3 register */
  {
    usartxbase += 0x08;
  }
  else /* The IT is in CR1 register */
  {
  }
  if (NewState != DISABLE)
  {
    *(__IO uint32_t*)usartxbase  |= itmask;
  }
  else
  {
    *(__IO uint32_t*)usartxbase &= ~itmask;
  }
}

/**
  * @brief  Enables the specified USART's Request.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_Request: specifies the USART request.
  *          This parameter can be any combination of the following values:
  *            @arg USART_Request_TXFRQ: Transmit data flush ReQuest
  *            @arg USART_Request_RXFRQ: Receive data flush ReQuest
  *            @arg USART_Request_MMRQ: Mute Mode ReQuest
  *            @arg USART_Request_SBKRQ: Send Break ReQuest
  *            @arg USART_Request_ABRRQ: Auto Baud Rate ReQuest
  * @param  NewState: new state of the DMA interface when reception error occurs.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void USART_RequestCmd(USART_TypeDef* USARTx, uint32_t USART_Request, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_REQUEST(USART_Request));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the USART ReQuest by setting the dedicated request bit in the RQR
       register.*/
      USARTx->RQR |= USART_Request;
  }
  else
  {
    /* Disable the USART ReQuest by clearing the dedicated request bit in the RQR
       register.*/
    USARTx->RQR &= (uint32_t)~USART_Request;
  }
}

/**
  * @brief  Enables or disables the USART's Overrun detection.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_OVRDetection: specifies the OVR detection status in case of OVR error.
  *          This parameter can be any combination of the following values:
  *            @arg USART_OVRDetection_Enable: OVR error detection enabled when
  *                                            the USART OVR error is asserted.
  *            @arg USART_OVRDetection_Disable: OVR error detection disabled when
  *                                             the USART OVR error is asserted.
  * @retval None
  */
void USART_OverrunDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_OVRDetection)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_OVRDETECTION(USART_OVRDetection));
  
  /* Clear the OVR detection bit */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_OVRDIS);
  /* Set the new value for the OVR detection bit */
  USARTx->CR3 |= USART_OVRDetection;
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg USART_FLAG_REACK:  Receive Enable acknowledge flag.
  *            @arg USART_FLAG_TEACK:  Transmit Enable acknowledge flag.
  *            @arg USART_FLAG_WU:  Wake up flag, not available for  STM32F030 devices.
  *            @arg USART_FLAG_RWU:  Receive Wake up flag, not available for  STM32F030 devices.
  *            @arg USART_FLAG_SBK:  Send Break flag.
  *            @arg USART_FLAG_CM:  Character match flag.
  *            @arg USART_FLAG_BUSY:  Busy flag.
  *            @arg USART_FLAG_ABRF:  Auto baud rate flag.
  *            @arg USART_FLAG_ABRE:  Auto baud rate error flag.
  *            @arg USART_FLAG_EOB:  End of block flag, not available for  STM32F030 devices.
  *            @arg USART_FLAG_RTO:  Receive time out flag.
  *            @arg USART_FLAG_nCTSS:  Inverted nCTS input bit status.
  *            @arg USART_FLAG_CTS:  CTS Change flag.
  *            @arg USART_FLAG_LBD:  LIN Break detection flag, not available for  STM32F030 devices.
  *            @arg USART_FLAG_TXE:  Transmit data register empty flag.
  *            @arg USART_FLAG_TC:  Transmission Complete flag.
  *            @arg USART_FLAG_RXNE:  Receive data register not empty flag.
  *            @arg USART_FLAG_IDLE:  Idle Line detection flag.
  *            @arg USART_FLAG_ORE:  OverRun Error flag.
  *            @arg USART_FLAG_NE:  Noise Error flag.
  *            @arg USART_FLAG_FE:  Framing Error flag.
  *            @arg USART_FLAG_PE:  Parity Error flag.
  * @retval The new state of USART_FLAG (SET or RESET).
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));
  
  if ((USARTx->ISR & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the USARTx's pending flags.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_FLAG: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg USART_FLAG_WU:  Wake up flag, not available for  STM32F030 devices.
  *            @arg USART_FLAG_CM:  Character match flag.
  *            @arg USART_FLAG_EOB:  End of block flag, not available for  STM32F030 devices.
  *            @arg USART_FLAG_RTO:  Receive time out flag.
  *            @arg USART_FLAG_CTS:  CTS Change flag.
  *            @arg USART_FLAG_LBD:  LIN Break detection flag, not available for  STM32F030 devices.
  *            @arg USART_FLAG_TC:  Transmission Complete flag.
  *            @arg USART_FLAG_IDLE:  IDLE line detected flag.
  *            @arg USART_FLAG_ORE:  OverRun Error flag.
  *            @arg USART_FLAG_NE: Noise Error flag.
  *            @arg USART_FLAG_FE: Framing Error flag.
  *            @arg USART_FLAG_PE:   Parity Errorflag.
  *   
  * @note     RXNE pending bit is cleared by a read to the USART_RDR register 
  *           (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register
  *           USART_RQR (USART_RequestCmd()).
  * @note     TC flag can be also cleared by software sequence: a read operation
  *           to USART_SR register (USART_GetFlagStatus()) followed by a write 
  *           operation to USART_TDR register (USART_SendData()).
  * @note     TXE flag is cleared by a write to the USART_TDR register (USART_SendData())
  *           or by writing 1 to the TXFRQ in the register USART_RQR (USART_RequestCmd()).
  * @note     SBKF flag is cleared by 1 to the SBKRQ in the register USART_RQR
  *           (USART_RequestCmd()).
  * @retval None
  */
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
     
  USARTx->ICR = USART_FLAG;
}

/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_IT: specifies the USART interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_WU:  Wake up interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_CM:  Character match interrupt.
  *            @arg USART_IT_EOB:  End of block interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_RTO:  Receive time out interrupt.
  *            @arg USART_IT_CTS:  CTS change interrupt.
  *            @arg USART_IT_LBD:  LIN Break detection interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_TXE:  Tansmit Data Register empty interrupt.
  *            @arg USART_IT_TC:  Transmission complete interrupt.
  *            @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
  *            @arg USART_IT_IDLE:  Idle line detection interrupt.
  *            @arg USART_IT_ORE:  OverRun Error interrupt.
  *            @arg USART_IT_NE:  Noise Error interrupt.
  *            @arg USART_IT_FE:  Framing Error interrupt.
  *            @arg USART_IT_PE:  Parity Error interrupt.
  * @retval The new state of USART_IT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT)
{
  uint32_t bitpos = 0, itmask = 0, usartreg = 0;
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_GET_IT(USART_IT)); 
  
  /* Get the USART register index */
  usartreg = (((uint16_t)USART_IT) >> 0x08);
  /* Get the interrupt position */
  itmask = USART_IT & IT_MASK;
  itmask = (uint32_t)0x01 << itmask;
  
  if (usartreg == 0x01) /* The IT  is in CR1 register */
  {
    itmask &= USARTx->CR1;
  }
  else if (usartreg == 0x02) /* The IT  is in CR2 register */
  {
    itmask &= USARTx->CR2;
  }
  else /* The IT  is in CR3 register */
  {
    itmask &= USARTx->CR3;
  }
  
  bitpos = USART_IT >> 0x10;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->ISR;
  if ((itmask != (uint16_t)RESET)&&(bitpos != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return bitstatus;  
}

/**
  * @brief  Clears the USARTx's interrupt pending bits.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @note   USART3 and USART4 are available only for STM32F072 and STM32F091 devices.
  * @note   USART5, USART6, USART7 and USART8 are available only for STM32F091 devices. 
  * @note   USART2 is not available for STM32F031 devices.  
  * @param  USART_IT: specifies the interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_WU:  Wake up interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_CM:  Character match interrupt.
  *            @arg USART_IT_EOB:  End of block interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_RTO:  Receive time out interrupt.
  *            @arg USART_IT_CTS:  CTS change interrupt.
  *            @arg USART_IT_LBD:  LIN Break detection interrupt, not available for  STM32F030 devices.
  *            @arg USART_IT_TC:  Transmission complete interrupt.
  *            @arg USART_IT_IDLE:  IDLE line detected interrupt.
  *            @arg USART_IT_ORE:  OverRun Error interrupt.
  *            @arg USART_IT_NE:  Noise Error interrupt.
  *            @arg USART_IT_FE:  Framing Error interrupt.
  *            @arg USART_IT_PE:  Parity Error interrupt.
  *
  * @note     RXNE pending bit is cleared by a read to the USART_RDR register 
  *           (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register 
  *           USART_RQR (USART_RequestCmd()).
  * @note     TC pending bit can be also cleared by software sequence: a read 
  *           operation to USART_SR register (USART_GetITStatus()) followed by  
  *           a write operation to USART_TDR register (USART_SendData()).
  * @note     TXE pending bit is cleared by a write to the USART_TDR register 
  *           (USART_SendData()) or by writing 1 to the TXFRQ in the register 
  *           USART_RQR (USART_RequestCmd()).
  * @retval None
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT)
{
  uint32_t bitpos = 0, itmask = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT)); 
  
  bitpos = USART_IT >> 0x10;
  itmask = ((uint32_t)0x01 << (uint32_t)bitpos);
  USARTx->ICR = (uint32_t)itmask;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/**
  ******************************************************************************
  * @file    stm32f0xx_wwdg.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Window watchdog (WWDG) peripheral:
  *           + Prescaler, Refresh window and Counter configuration
  *           + WWDG activation
  *           + Interrupts and flags management
  *             
  *  @verbatim
  *    
  ============================================================================== 
                           ##### WWDG features ##### 
  ============================================================================== 
    [..] Once enabled the WWDG generates a system reset on expiry of a programmed
        time period, unless the program refreshes the counter (downcounter) 
        before to reach 0x3F value (i.e. a reset is generated when the counter
        value rolls over from 0x40 to 0x3F). 
    [..] An MCU reset is also generated if the counter value is refreshed
         before the counter has reached the refresh window value. This 
         implies that the counter must be refreshed in a limited window.

    [..] Once enabled the WWDG cannot be disabled except by a system reset.

    [..] WWDGRST flag in RCC_CSR register can be used to inform when a WWDG
         reset occurs.

    [..] The WWDG counter input clock is derived from the APB clock divided 
         by a programmable prescaler.

    [..] WWDG counter clock = PCLK1 / Prescaler.
    [..] WWDG timeout = (WWDG counter clock) * (counter value).

    [..] Min-max timeout value @32MHz (PCLK1): ~85us / ~43ms.

                       ##### How to use this driver ##### 
  ==============================================================================
    [..]
        (#) Enable WWDG clock using RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE) 
            function.
              
        (#) Configure the WWDG prescaler using WWDG_SetPrescaler() function.
                             
        (#) Configure the WWDG refresh window using WWDG_SetWindowValue() function.
              
        (#) Set the WWDG counter value and start it using WWDG_Enable() function.
            When the WWDG is enabled the counter value should be configured to 
            a value greater than 0x40 to prevent generating an immediate reset.
              
        (#) Optionally you can enable the Early wakeup interrupt which is 
            generated when the counter reach 0x40.
            Once enabled this interrupt cannot be disabled except by a system reset.
                   
        (#) Then the application program must refresh the WWDG counter at regular
            intervals during normal operation to prevent an MCU reset, using
            WWDG_SetCounter() function. This operation must occur only when
            the counter value is lower than the refresh window value, 
            programmed using WWDG_SetWindowValue().
  
  *  @endverbatim
  *
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

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup WWDG 
  * @brief WWDG driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* --------------------- WWDG registers bit mask ---------------------------- */
/* CFR register bit mask */
#define CFR_WDGTB_MASK    ((uint32_t)0xFFFFFE7F)
#define CFR_W_MASK        ((uint32_t)0xFFFFFF80)
#define BIT_MASK          ((uint8_t)0x7F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup WWDG_Private_Functions
  * @{
  */

/** @defgroup WWDG_Group1 Prescaler, Refresh window and Counter configuration functions
 *  @brief   Prescaler, Refresh window and Counter configuration functions 
 *
@verbatim   
  ==============================================================================
    ##### Prescaler, Refresh window and Counter configuration functions #####
  ==============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WWDG_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/**
  * @brief  Sets the WWDG Prescaler.
  * @param  WWDG_Prescaler: specifies the WWDG Prescaler.
  *          This parameter can be one of the following values:
  *            @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
  *            @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
  *            @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
  *            @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
  * @retval None
  */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
  /* Clear WDGTB[1:0] bits */
  tmpreg = WWDG->CFR & CFR_WDGTB_MASK;
  /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
  tmpreg |= WWDG_Prescaler;
  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/**
  * @brief  Sets the WWDG window value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  *          This parameter value must be lower than 0x80.
  * @retval None
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
  /* Clear W[6:0] bits */

  tmpreg = WWDG->CFR & CFR_W_MASK;

  /* Set W[6:0] bits according to WindowValue value */
  tmpreg |= WindowValue & (uint32_t) BIT_MASK;

  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/**
  * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
  * @note   Once enabled this interrupt cannot be disabled except by a system reset. 
  * @param  None
  * @retval None
  */
void WWDG_EnableIT(void)
{
  WWDG->CFR |= WWDG_CFR_EWI;
}

/**
  * @brief  Sets the WWDG counter value.
  * @param  Counter: specifies the watchdog counter value.
  *          This parameter must be a number between 0x40 and 0x7F (to prevent 
  *          generating an immediate reset).
  * @retval None
  */
void WWDG_SetCounter(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  /* Write to T[6:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CR = Counter & BIT_MASK;
}

/**
  * @}
  */

/** @defgroup WWDG_Group2 WWDG activation functions
 *  @brief   WWDG activation functions 
 *
@verbatim   
  ==============================================================================
                     ##### WWDG activation function #####
  ==============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables WWDG and load the counter value.                  
  * @param  Counter: specifies the watchdog counter value.
  *          This parameter must be a number between 0x40 and 0x7F (to prevent 
  *          generating an immediate reset).
  * @retval None
  */
void WWDG_Enable(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  WWDG->CR = WWDG_CR_WDGA | Counter;
}

/**
  * @}
  */

/** @defgroup WWDG_Group3 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
  ==============================================================================
                ##### Interrupts and flags management functions #####
  ==============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
  * @param  None
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET).
  */
FlagStatus WWDG_GetFlagStatus(void)
{
  FlagStatus bitstatus = RESET;
    
  if ((WWDG->SR) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears Early Wakeup interrupt flag.
  * @param  None
  * @retval None
  */
void WWDG_ClearFlag(void)
{
  WWDG->SR = (uint32_t)RESET;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
