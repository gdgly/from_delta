/** *****************************************************************************
 * \file    adc_cfg.h
 * \brief   Server call back service file for adc.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef ADC_CFG_H
#define ADC_CFG_H
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
 
 /* The structure defining the setup of each ADC */
typedef struct
{
  /* Control Channel, e.g. ADC_Channel_0*/
  uint32 u32AdcControlChannel;
	
	/* The sample time value to be set for the selected channel e.g. ADC_SampleTime_1_5Cycles*/
	uint32 u32AdcSampleTime;
} tADCSetup;

/*******************************************************************************
 * Global data
 ******************************************************************************/
#ifdef ADC_EXPORT_H
/* Define the ADC to be initialised */
/*lint -e{9048}
 *
 * Note: 9048 unsigned integer literal without a 'U' suffix
 * [MISRA 2012 Rule 7.2, required]
 *
 * Reason: Applies to TI supplied macros.
 *
 */
static const tADCSetup ADC_CFG_ADC_SETUP[] =
{
{ADC_Channel_0  , ADC_SampleTime_55_5Cycles},
{ADC_Channel_1  , ADC_SampleTime_55_5Cycles},
{ADC_Channel_5  , ADC_SampleTime_55_5Cycles},
{ADC_Channel_6  , ADC_SampleTime_55_5Cycles}
}; /* Max 8 values! */
#endif

/* Helper definition for callers of m_ADC read/write functions */

/* Suggestion received to turn this into #defines, but the type checking is preferred */
  /*
   * Configure ADC inputs: 
   * PA0 = ADC_IN0 NTC Outlet Ambient
   * PA1 = ADC_IN1 Internal Voltage of VSB
	 * PA5 = ADC_IN5 Voltage of VSB
   * PA6 = ADC_IN6 current of VSB
   * PA8 = ADC_IN8 NTC Inlet Ambient
   *
   */
typedef enum M_ADC_CFG_E_INDEX_
{
  ADC_CFG_E_INDEX_PA0_AIN0_INTC = 0,
	ADC_CFG_E_INDEX_PA1_AIN1_OUTNTC,
  ADC_CFG_E_INDEX_PA5_AIN5_IntVsb,
  ADC_CFG_E_INDEX_PA6_AIN6_IVsb,
  ADC_CFG_E_INDEX_COUNT /* Must be last row!*/
} ADC_CFG_E_INDEX;



#ifdef __cplusplus
  }
#endif
#endif  /* ADC_CFG_H */

  
/*
 * End of file
 */
