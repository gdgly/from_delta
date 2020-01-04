/** *****************************************************************************
 * \file    adc_conf.h
 * \brief   Configurations file for adc.c
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
#define MG_ADC_BIT_RESOLUTION             12   /* ADC bit resolution. Can be a value between 8-15 */

/* Hardware address of ADC result register */
#define MG_U32_ADC1_DATA_REG_ADDR_DR      0x50000040
#define MG_U32_ADC2_DATA_REG_ADDR_DR      0x50000140
#define MG_U32_ADC1_2_DATA_REG_ADDR_CDR   0x5000030C

/* Number of sampled ADC 1 channels */
#define MG_NUM_OF_ADC_1_CHANNEL           4
/* Number of sampled ADC 2 channels */
#define MG_NUM_OF_ADC_2_CHANNEL           4
/* Order of sampling sequence ADC 1 */
#define MG_ADC_1_SAMPLE_PHS_A             1
#define MG_ADC_1_SAMPLE_V_IN_L            2
#define MG_ADC_1_SAMPLE_V_IN_N            3
#define MG_ADC_1_SAMPLE_I_IN              4
#define MG_ADC_1_SAMPLE_V_IN              2
/* Order of sampling sequence ADC 2 */
#define MG_ADC_2_SAMPLE_PHS_B             1
#define MG_ADC_2_SAMPLE_V_BULK            2
#define MG_ADC_2_SAMPLE_V_REF_3V3         3
#define MG_ADC_2_SAMPLE_NTC_1             4
#define MG_ADC_2_SAMPLE_V_EXT             2

#define MG_ADC_1_BUFFER_PHS_A             mg_u16q12Adc1Buffer[(MG_ADC_1_SAMPLE_PHS_A - 1)]             
#define MG_ADC_1_BUFFER_V_IN_L            mg_u16q12Adc1Buffer[(MG_ADC_1_SAMPLE_V_IN_L - 1)]
#define MG_ADC_1_BUFFER_V_IN_N            mg_u16q12Adc1Buffer[(MG_ADC_1_SAMPLE_V_IN_N - 1)]
#define MG_ADC_1_BUFFER_I_IN              mg_u16q12Adc1Buffer[(MG_ADC_1_SAMPLE_I_IN - 1)]
#define MG_ADC_1_BUFFER_V_IN              mg_u16q12Adc1Buffer[(MG_ADC_1_SAMPLE_V_IN - 1)]

#define MG_ADC_2_BUFFER_PHS_B             mg_u16q12Adc2Buffer[(MG_ADC_2_SAMPLE_PHS_B - 1)]
#define MG_ADC_2_BUFFER_V_BULK            mg_u16q12Adc2Buffer[(MG_ADC_2_SAMPLE_V_BULK - 1)]
#define MG_ADC_2_BUFFER_V_REF_3V3         mg_u16q12Adc2Buffer[(MG_ADC_2_SAMPLE_V_REF_3V3 - 1)]
#define MG_ADC_2_BUFFER_NTC_1             mg_u16q12Adc2Buffer[(MG_ADC_2_SAMPLE_NTC_1 - 1)]
#define MG_ADC_2_BUFFER_V_EXT             mg_u16q12Adc2Buffer[(MG_ADC_2_SAMPLE_V_EXT - 1)]

#define MG_REG_DMA_CLR_DMA1_HT1_FLG       (DMA1->IFCR = DMA1_FLAG_HT1)   /* Clear interrupt flag for DMA1CH1 half transfer complete */
#define MG_REG_DMA_CLR_DMA1_HT2_FLG       (DMA1->IFCR = DMA1_FLAG_HT2)   /* Clear interrupt flag for DMA1CH2 half transfer complete */

/*******************************************************************************
 * General purpose section
 ******************************************************************************/

/* Define DMA channel ID's */
#define MG_DMA1CH1      1U
#define MG_DMA1CH2      2U
#define MG_DMA1CH3      3U
#define MG_DMA1CH4      4U
#define MG_DMA1CH5      5U
#define MG_DMA1CH6      6U
#define MG_DMA1CH7      7U

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

EXTERN uint16 mg_u16q12Adc1Buffer[MG_NUM_OF_ADC_1_CHANNEL];
EXTERN uint16 mg_u16q12Adc2Buffer[MG_NUM_OF_ADC_2_CHANNEL];
EXTERN uint32 mg_u32q12AdcScaleFactPhsA;
EXTERN uint32 mg_u32q12AdcScaleFactPhsB;
EXTERN uint32 mg_u32q12AdcScaleFactCurrIn;
EXTERN uint32 mg_u32q12AdcScaleFactVoltInL;
EXTERN uint32 mg_u32q12AdcScaleFactVoltInN;
EXTERN uint32 mg_u32q12AdcScaleFactVoltIn;
EXTERN uint32 mg_u32q12AdcScaleFactVoltBulk;
EXTERN uint32 mg_u32q12AdcScaleFactVoltRef3V3;
EXTERN uint32 mg_u32q12AdcScaleFactVoltNtc1;
EXTERN uint32 mg_u32q12AdcScaleFactVoltExt;

#undef EXTERN


#ifdef __cplusplus
  }
#endif
#endif  /* ADC_CONF_H */

  
/*
 * End of file
 */
