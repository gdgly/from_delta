/** *****************************************************************************
 * \file    dac_conf.h
 * \brief   Configurations file for dac.c
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

#ifndef DAC_CONF_H
#define DAC_CONF_H
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

/* Define DAC resolution */
#define MG_DAC_BIT_RESOLUTION   12    /* 12bit DAC */

/* Registers */
#define MG_REG_DAC1_CHANNEL1_DATA    *(__IO uint32_t *) (uint32)((uint32_t)DAC1 + (uint32)0x00000008 + DAC_Align_12b_R)
#define MG_REG_DAC1_CHANNEL2_DATA    *(__IO uint32_t *) (uint32)((uint32_t)DAC1 + (uint32)0x00000014 + DAC_Align_12b_R)
#define MG_REG_DAC2_CHANNEL1_DATA    *(__IO uint32_t *) (uint32)((uint32_t)DAC2 + (uint32)0x00000008 + DAC_Align_12b_R)

/* Define DAC ID's */
#define MG_DAC1     1
#define MG_DAC2     2
/* Define DAC channels */
#define MG_CH1      1
#define MG_CH2      2

/*******************************************************************************
 * General purpose section
 ******************************************************************************/

/* Define ADC resolutions */
#if (MG_DAC_BIT_RESOLUTION == 8)
#define MG_DAC_RESOLUTION     256
#endif
#if (MG_DAC_BIT_RESOLUTION == 9)
#define MG_DAC_RESOLUTION     512
#endif
#if (MG_DAC_BIT_RESOLUTION == 10)
#define MG_DAC_RESOLUTION     1024
#endif
#if (MG_DAC_BIT_RESOLUTION == 11)
#define MG_DAC_RESOLUTION     2048
#endif
#if (MG_DAC_BIT_RESOLUTION == 12)
#define MG_DAC_RESOLUTION     4096
#endif
#if (MG_DAC_BIT_RESOLUTION == 13)
#define MG_DAC_RESOLUTION     8192
#endif
#if (MG_DAC_BIT_RESOLUTION == 14)
#define MG_DAC_RESOLUTION     16384
#endif
#if (MG_DAC_BIT_RESOLUTION == 15)
#define MG_DAC_RESOLUTION     32768
#endif

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

extern uint32 mg_u32q12Dac1Ch1ScaleFact;
extern uint32 mg_u32q12Dac1Ch2ScaleFact;
extern uint32 mg_u32q12Dac2Ch1ScaleFact;


#ifdef __cplusplus
  }
#endif
#endif  /* DAC_CONF_H */

  
/*
 * End of file
 */
