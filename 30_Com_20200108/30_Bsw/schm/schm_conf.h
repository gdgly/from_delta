/** *****************************************************************************
 * \file    schm_conf.h
 * \brief   Configurations file for schm.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-01-16 18:46:21 +0800 (Wed, 16 Jan 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 139 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef SCHM_CONF_H
#define SCHM_CONF_H
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

#define MG_TIME_BASE_ISR                0       /* 1 = Time base routine as ISR */
#define MG_TIME_BASE_PERIOD_US          200     /* (uS) */

#define MG_HRTIMER_BASE_FREQ            65000   /* (Hz) */
#define MG_U32_nS_HRTIMER_BASE_PERIOD   (uint32)(F64_ONE_BY_NANO / MG_HRTIMER_BASE_FREQ)

#if DEBUG_SECTION_WDG_DEBUG_DELAY
#define MG_WDG_TIME_OUT_DLY             150     /* (ms) watch dog time out delay */
#else
#define MG_WDG_TIME_OUT_DLY             100     /* (ms) watch dog time out delay */   
#endif

/*******************************************************************************
 * Vector table
 ******************************************************************************/
#define MG_VECT_PFC_CTRL_ISR_A          DMA1_Channel1_IRQHandler(void)
#define MG_VECT_PFC_CTRL_ISR_B          DMA1_Channel2_IRQHandler(void)
#define MG_VECT_PFC_CTRL_ISR            HRTIM1_Master_IRQHandler(void)
#define MG_VECT_TIME_BASE_ISR           TIM1_TRG_COM_TIM17_IRQHandler(void)
#define MG_VECT_USART2_ISR              USART2_IRQHandler(void)

/***************************************
 * Interrupt preemption priority 1 = HIGH .. 7 = LOW
 **************************************/
#define MG_HRTIMER_MASTER_ISR_PRE_PRIO  1
#define MG_ADC_DMA1_CH1_ISR_PRE_PRIO    1
#define MG_ADC_DMA1_CH2_ISR_PRE_PRIO    2
#define MG_USART2_RX_ISR_PRE_PRIO       3
#define MG_TIM17_ISR_PRE_PRIO           4

/***************************************
 * Interrupt sub priority 0 = HIGH .. 7 = LOW
 **************************************/
#define MG_HRTIMER_MASTER_ISR_SUB_PRIO  0
#define MG_ADC_DMA1_CH1_ISR_SUB_PRIO    0
#define MG_ADC_DMA1_CH2_ISR_SUB_PRIO    0
#define MG_USART2_RX_ISR_SUB_PRIO       1
#define MG_TIM17_ISR_SUB_PRIO           0

/*******************************************************************************
 * General purpose section
 ******************************************************************************/

/***************************************
 * Timer ID config
 **************************************/
#define MG_TIM15        15
#define MG_TIM16        16
#define MG_TIM17        17

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
 * UART ID config
 **************************************/
#define MG_UART1        1
#define MG_UART2        2
#define MG_UART3        3

/***************************************
 * DMA channel ID config
 **************************************/
#define MG_DMA1CH1      1
#define MG_DMA1CH2      2
#define MG_DMA1CH3      3
#define MG_DMA1CH4      4
#define MG_DMA1CH5      5
#define MG_DMA1CH6      6
#define MG_DMA1CH7      7


#ifdef __cplusplus
  }
#endif
#endif  /* SCHM_CONF_H */


/*
 * End of file
 */
