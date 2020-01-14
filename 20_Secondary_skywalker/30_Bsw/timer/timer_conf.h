/** *****************************************************************************
 * \file    timer_conf.h
 * \brief   Configurations file for timer.c
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

#ifndef TIMER_CONF_H
#define TIMER_CONF_H
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

#define MG_TIM1_ENA         1
#define MG_TIM2_ENA         0
#define MG_TIM3_ENA         0
#define MG_TIM15_ENA        1
#define MG_TIM16_ENA        0
#define MG_TIM17_ENA        1

#define MG_TIM1_PRESCALER   0
#define MG_TIM2_PRESCALER   0
#define MG_TIM3_PRESCALER   0
#define MG_TIM15_PRESCALER  0
#define MG_TIM16_PRESCALER  0
#define MG_TIM17_PRESCALER  0

/*******************************************************************************
 * General purpose section
 ******************************************************************************/
#define MG_TIM1             1
#define MG_TIM2             2
#define MG_TIM3             3
#define MG_TIM15            15
#define MG_TIM16            16
#define MG_TIM17            17

#define MG_REG_TIMER1_PERIOD          TIM1->ARR
#define MG_REG_TIMER1_CH1_CCR         TIM1->CCR1
#define MG_REG_TIMER1_CH2_CCR         TIM1->CCR2
#define MG_REG_TIMER1_CH3_CCR         TIM1->CCR3
#define MG_REG_TIMER1_CH4_CCR         TIM1->CCR4
#define MG_REG_TIMER1_PWM_ENABLE      TIM1->BDTR |= TIM_BDTR_MOE
#define MG_REG_TIMER1_PWM_DISABLE     TIM1->BDTR &= (uint16_t)~TIM_BDTR_MOE

#define MG_REG_TIMER2_PERIOD          TIM2->ARR
#define MG_REG_TIMER2_CH1_CCR         TIM2->CCR1
#define MG_REG_TIMER2_CH2_CCR         TIM2->CCR2
#define MG_REG_TIMER2_CH3_CCR         TIM2->CCR3
#define MG_REG_TIMER2_CH4_CCR         TIM2->CCR4
#define MG_REG_TIMER2_PWM_ENABLE      TIM2->BDTR |= TIM_BDTR_MOE
#define MG_REG_TIMER2_PWM_DISABLE     TIM2->BDTR &= (uint16_t)~TIM_BDTR_MOE

#define MG_REG_TIMER3_PERIOD          TIM3->ARR
#define MG_REG_TIMER3_CH1_CCR         TIM3->CCR1
#define MG_REG_TIMER3_CH2_CCR         TIM3->CCR2
#define MG_REG_TIMER3_CH3_CCR         TIM3->CCR3
#define MG_REG_TIMER3_CH4_CCR         TIM3->CCR4
#define MG_REG_TIMER3_PWM_ENABLE      TIM3->BDTR |= TIM_BDTR_MOE
#define MG_REG_TIMER3_PWM_DISABLE     TIM3->BDTR &= (uint16_t)~TIM_BDTR_MOE

#define MG_REG_TIMER15_PERIOD         TIM15->ARR
#define MG_REG_TIMER16_PERIOD         TIM16->ARR
#define MG_REG_TIMER17_PERIOD         TIM17->ARR


#ifdef __cplusplus
  }
#endif
#endif  /* TIMER_CONF_H */


/*
 * End of file
 */
