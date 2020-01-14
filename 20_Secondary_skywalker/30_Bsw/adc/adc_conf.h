/** *****************************************************************************
 * \file    adc_conf.h
 * \brief   Configurations file for adc.c
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

#ifndef ADC_CONF_H
#define ADC_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/* ADC resolution */
#define MG_ADC_BIT_RESOLUTION            12   /* ADC bit resolution. Can be a value between 8-15 */

/* Hardware address of ADC result register */
#define MG_U32_ADC1_DATA_REG_ADDR_DR      0x50000040
#define MG_U32_ADC2_DATA_REG_ADDR_DR      0x50000140
#define MG_U32_ADC1_2_DATA_REG_ADDR_CDR   0x5000030C

/* Number of sampled ADC channels (simultaneous mode -> ADC1 and ADC2 equal number of conversions) */
#define MG_NUM_OF_ADC_CHANNEL             6
/* Order of sampling sequence ADC 1 */
#define MG_ADC_1_SAMPLE_V_OUT_EXT         1
#define MG_ADC_1_SAMPLE_V_OUT_INT         2
#define MG_ADC_1_SAMPLE_I_OUT             3
#define MG_ADC_1_SAMPLE_ACS_BUS           4
#define MG_ADC_1_SAMPLE_ACS_LOCAL         5
#define MG_ADC_1_SAMPLE_2V5REF            6
/* Order of sampling sequence ADC 2 */
#define MG_ADC_2_SAMPLE_NTC_ORING         1
#define MG_ADC_2_SAMPLE_NTC_SR            2
#define MG_ADC_2_SAMPLE_DUMMY_1           3
#define MG_ADC_2_SAMPLE_DUMMY_2           4
#define MG_ADC_2_SAMPLE_DUMMY_3           5
#define MG_ADC_2_SAMPLE_DUMMY_4           6
#define MG_ADC_2_SAMPLE_DUMMY_5           1

#define MG_ADC_1_BUFFER_V_OUT_EXT         mg_u16q12Adc12Buffer[((MG_ADC_1_SAMPLE_V_OUT_EXT - 1) * 2)]
#define MG_ADC_1_BUFFER_V_OUT_INT         mg_u16q12Adc12Buffer[((MG_ADC_1_SAMPLE_V_OUT_INT - 1) * 2)]
#define MG_ADC_1_BUFFER_I_OUT             mg_u16q12Adc12Buffer[((MG_ADC_1_SAMPLE_I_OUT - 1) * 2)]
#define MG_ADC_1_BUFFER_ACS_BUS           mg_u16q12Adc12Buffer[((MG_ADC_1_SAMPLE_ACS_BUS - 1) * 2)]
#define MG_ADC_1_BUFFER_ACS_LOCAL         mg_u16q12Adc12Buffer[((MG_ADC_1_SAMPLE_ACS_LOCAL - 1) * 2)]
#define MG_ADC_1_BUFFER_2V5REF            mg_u16q12Adc12Buffer[((MG_ADC_1_SAMPLE_2V5REF - 1) * 2)]

#define MG_ADC_2_BUFFER_NTC_ORING         mg_u16q12Adc12Buffer[((MG_ADC_2_SAMPLE_NTC_ORING * 2) - 1)]
#define MG_ADC_2_BUFFER_NTC_SR            mg_u16q12Adc12Buffer[((MG_ADC_2_SAMPLE_NTC_SR * 2) - 1)]
#define MG_ADC_2_BUFFER_DUMMY_1           mg_u16q12Adc12Buffer[((MG_ADC_2_SAMPLE_DUMMY_1 * 2) - 1)]
#define MG_ADC_2_BUFFER_DUMMY_2           mg_u16q12Adc12Buffer[((MG_ADC_2_SAMPLE_DUMMY_2 * 2) - 1)]
#define MG_ADC_2_BUFFER_DUMMY_3           mg_u16q12Adc12Buffer[((MG_ADC_2_SAMPLE_DUMMY_3 * 2) - 1)]
#define MG_ADC_2_BUFFER_DUMMY_4           mg_u16q12Adc12Buffer[((MG_ADC_2_SAMPLE_DUMMY_4 * 2) - 1)]
#define MG_ADC_2_BUFFER_DUMMY_5           mg_u16q12Adc12Buffer[((MG_ADC_2_SAMPLE_DUMMY_5 * 2) - 1)]

#define MG_REG_DMA_CLR_DMA1_HT1_FLG       (DMA1->IFCR = DMA1_FLAG_HT1)   /* Clear interrupt flag for DMA1CH1 half transfer complete */
#define MG_REG_DMA_CLR_DMA1_HT2_FLG       (DMA1->IFCR = DMA1_FLAG_HT2)   /* Clear interrupt flag for DMA1CH2 half transfer complete */
#define MG_REG_DMA_CLR_DMA1_TC1_FLG       (DMA1->IFCR = DMA1_FLAG_TC1)   /* Clear interrupt flag for DMA1CH1 transfer complete */
#define MG_REG_DMA_CLR_DMA1_TC2_FLG       (DMA1->IFCR = DMA1_FLAG_TC2)   /* Clear interrupt flag for DMA1CH2 transfer complete */

/*******************************************************************************
 * General purpose section
 ******************************************************************************/

/* Define DMA channel ID's */
#define MG_DMA1CH1      1
#define MG_DMA1CH2      2
#define MG_DMA1CH3      3
#define MG_DMA1CH4      4
#define MG_DMA1CH5      5
#define MG_DMA1CH6      6
#define MG_DMA1CH7      7

/* Define ADC resolutions */
#if (MG_ADC_BIT_RESOLUTION == 8)
#define MG_ADC_RESOLUTION     256
#endif
#if (MG_ADC_BIT_RESOLUTION == 9)
#define MG_ADC_RESOLUTION     512
#endif
#if (MG_ADC_BIT_RESOLUTION == 10)
#define MG_ADC_RESOLUTION     1024
#endif
#if (MG_ADC_BIT_RESOLUTION == 11)
#define MG_ADC_RESOLUTION     2048
#endif
#if (MG_ADC_BIT_RESOLUTION == 12)
#define MG_ADC_RESOLUTION     4096
#endif
#if (MG_ADC_BIT_RESOLUTION == 13)
#define MG_ADC_RESOLUTION     8192
#endif
#if (MG_ADC_BIT_RESOLUTION == 14)
#define MG_ADC_RESOLUTION     16384
#endif
#if (MG_ADC_BIT_RESOLUTION == 15)
#define MG_ADC_RESOLUTION     32768
#endif

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

#if defined(ADC_EXPORT_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN uint16 mg_u16q12Adc12Buffer[MG_NUM_OF_ADC_CHANNEL << 1];
EXTERN uint32 mg_u32q12AdcScaleFactVoltOutExt;
EXTERN uint32 mg_u32q12AdcScaleFactVoltOutInt;
EXTERN uint32 mg_u32q12AdcScaleFactCurrOut;
EXTERN uint32 mg_u32q12AdcScaleFactVoltRef3V3;
EXTERN uint32 mg_u32q12AdcScaleFactAcsBus;
EXTERN uint32 mg_u32q12AdcScaleFactAcsLocal;
EXTERN uint32 mg_u321OhmAdcScaleFactResNtc;

#undef EXTERN


#ifdef __cplusplus
  }
#endif
#endif  /* ADC_CONF_H */

  
/*
 * End of file
 */
