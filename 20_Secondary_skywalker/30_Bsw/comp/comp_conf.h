/** *****************************************************************************
 * \file    comp_conf.h
 * \brief   Configurations file for comp.c
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

#ifndef COMP_CONF_H
#define COMP_CONF_H
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

#define MG_COMP_2_ENA     1
#define MG_COMP_4_ENA     0
#define MG_COMP_6_ENA     0

/*******************************************************************************
 * General purpose section
 ******************************************************************************/
#define MG_COMP_MAX_REF_VOLT    3.3   /* (V) Max reference voltage */

/* Define comparator resolution */
#define MG_DAC_BIT_RESOLUTION   12    /* 12bit DAC */

/* Define DAC registers */
#define MG_DAC1_CH1             ((uint32_t)0x00000040)
#define MG_DAC1_CH2             ((uint32_t)0x00000050)
#define MG_DAC2_CH1             ((uint32_t)0x00400000)

/* Define DAC ID's */
#define MG_DAC1                 1
#define MG_DAC2                 2
/* Define DAC channels */
#define MG_CH1                  1
#define MG_CH2                  2

/* Registers */
#define MG_REG_DAC1_CHANNEL1_DATA    *(__IO uint32_t *) (uint32)((uint32_t)DAC1 + (uint32)0x00000008 + DAC_Align_12b_R)
#define MG_REG_DAC1_CHANNEL2_DATA    *(__IO uint32_t *) (uint32)((uint32_t)DAC1 + (uint32)0x00000014 + DAC_Align_12b_R)
#define MG_REG_DAC2_CHANNEL1_DATA    *(__IO uint32_t *) (uint32)((uint32_t)DAC2 + (uint32)0x00000008 + DAC_Align_12b_R)

#define MG_REG_COMP2_OUT             (COMP2->CSR & COMP2_CSR_COMP2OUT) != 0
#define MG_REG_COMP4_OUT             (COMP4->CSR & COMP4_CSR_COMP4OUT) != 0
#define MG_REG_COMP6_OUT             (COMP6->CSR & COMP6_CSR_COMP6OUT) != 0

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
 * Scaling section
 ******************************************************************************/
#define MG_U16Q12_COMP_REF_SCALE_FACT   (uint16)(U32Q12(4095.0 / (MG_COMP_MAX_REF_VOLT * F32_1_MILLI)))

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

#if defined(COMP_EXPORT_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN uint32 mg_u32q12Comp2ScaleFact;
EXTERN uint32 mg_u32q12Comp4ScaleFact;
EXTERN uint32 mg_u32q12Comp6ScaleFact;

#undef EXTERN


#ifdef __cplusplus
  }
#endif
#endif  /* COMP_CONF_H */

  
/*
 * End of file
 */
