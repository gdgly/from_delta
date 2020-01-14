/** *****************************************************************************
 * \file    hwio_conf.h
 * \brief   Configurations file for hwio.c
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

#ifndef HWIO_CONF_H
#define HWIO_CONF_H
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
#define MG_OVP_CLEAR_BY_MOSFET               1    /* 1 = OVP HW latch cleared by MOSFET; 0 = OVP HW latch cleared by pull-down */

#define MG_F32_VOUT_EXT_MAX            69.699F    /* (V) Maximum detectable external output voltage */
#define MG_F32_VOUT_INT_MAX            69.453F    /* (V) Maximum detectable internal output voltage */
#define MG_F32_I_OUT_MAX              159.794F    /* (A) Maximum detectable output current */
#define MG_F32_I_CT_MAX                64.095F    /* (A) Maximum detectable CT current */
#define MG_F32_VREF_3V3                 3.287F    /* (V) 3.3V uC ADC precision */
#define MG_F32_VREF_EXTERNAL            2.495F    /* (V) External voltage reference for ADC calibration */
#define MG_F32_NTC_PULL_UP_RES           2.21F    /* (kOhm) NTC pull-up resistor */

#define MG_F32_VREF_EXT_LIMIT_HIGH      2.590F    /* (V) External voltage reference limitation */
#define MG_F32_VREF_EXT_LIMIT_LOW       2.390F    /* (V) External voltage reference limitation */

#define MG_U16Q15_K1_I_OUT_FLT        (uint16)U32Q15(0.5F) /* old value */
#define MG_U16Q15_K2_I_OUT_FLT        (uint16)U32Q15(0.5F) /* new value */ 

#define MG_U16Q15_K1_REF_FLT          (uint16)U32Q15(0.9F)  /* old value */
#define MG_U16Q15_K2_REF_FLT          (uint16)U32Q15(0.1f)  /* new value */

#define MG_TIMER_1_FREQUENCY          100000                /* (Hz) */
#define MG_Q16_TIMER_1_DUTY_CYCLE     (uint16)U32Q16(0.5F)  /* Duty cycle */

/*******************************************************************************
 * Scaling section
 ******************************************************************************/

#define MG_U16_10mV_VOUT_EXT_SCALE_FACT   (uint16)(MG_F32_VOUT_EXT_MAX * F32_10_MILLI)  /* 10mV per digit */
#define MG_U16_10mV_VOUT_INT_SCALE_FACT   (uint16)(MG_F32_VOUT_INT_MAX * F32_10_MILLI)  /* 10mV per digit */
#define MG_U16_10mA_I_OUT_SCALE_FACT      (uint16)(MG_F32_I_OUT_MAX * F32_10_MILLI)     /* 10mA per digit */
#define MG_U16_1mV_VREF_SCALE_FACT        (uint16)(MG_F32_VREF_3V3 * F32_1_MILLI)       /* 1mV per digit */

#define MG_U16_1mV_VREF_EXTERNAL          (uint16)(MG_F32_VREF_EXTERNAL * F32_1_MILLI)  /* 1mV per digit */
#define MG_U16_1mV_VREF_EXT_LIMIT_HIGH    (uint16)(MG_F32_VREF_EXT_LIMIT_HIGH * F32_1_MILLI) /* 1mV per digit */
#define MG_U16_1mV_VREF_EXT_LIMIT_LOW     (uint16)(MG_F32_VREF_EXT_LIMIT_LOW * F32_1_MILLI)  /* 1mV per digit */

#define MG_U32_10mA_I_CT_COMP_SCALE_FACT  (uint32)(MG_F32_I_CT_MAX * F32_10_MILLI)      /* 10mA per digit */

#define MG_U16_1Ohm_NTC_PULL_UP_RES       (uint16)(MG_F32_NTC_PULL_UP_RES * F64_KILO)   /* 1 Ohm per digit */

#define MG_TIMER_1_PERIOD_US              (uint32)(F64_ONE_BY_MICRO / MG_TIMER_1_FREQUENCY)

/***************************************
 * HrTimer ID config
 **************************************/
#define MG_HRTIM_MST    0
#define MG_HRTIM_A      1
#define MG_HRTIM_B      2
#define MG_HRTIM_C      3
#define MG_HRTIM_D      4
#define MG_HRTIM_E      5

/***************************************
 * Timer ID config
 **************************************/
#define MG_TIM1         1
#define MG_TIM2         2
#define MG_TIM3         3
#define MG_TIM15        15
#define MG_TIM16        16
#define MG_TIM17        17


#ifdef __cplusplus
  }
#endif
#endif  /* HWIO_CONF_H */


/*
 * End of file
 */
