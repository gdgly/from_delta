/** *****************************************************************************
 * \file    pwm_cfg.h
 * \brief   Server call back service file for pwm.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-03-01 14:35:06 +0800 (Fri, 01 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 145 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PWM_CFG_H
#define PWM_CFG_H
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
#include "rte.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/
#define PWM_CFG_PWM_FRQ_FAN              ((uint32)25000)    /* Fan control frequence 25K */
#define PWM_CFG_PWM_FRQ_VSB_TRIM         ((uint32)100000)    /* Vsb trim control frequence 25K */
#define PWM_CFG_PWM_FRQ_VSB_OVP          ((uint32)100000)    /* Vsb trim control frequence 25K */
		
#define PWM_CFG_PWM_FAN_PERIOD           ((uint16)(RTE_U32_CPU_CLK_FREQ/PWM_CFG_PWM_FRQ_FAN - 1u))
#define PWM_CFG_PWM_FAN_SPEED_INIT       ((uint32)((uint32)PWM_CFG_PWM_FAN_PERIOD*90U/100U))

#define PWM_CFG_PWM_VSB_TRIM_PERIOD      ((uint16)(RTE_U32_CPU_CLK_FREQ/PWM_CFG_PWM_FRQ_VSB_TRIM - 1u))
#define PWM_CFG_PWM_VSB_TRIM_INIT        ((uint32)((uint32)PWM_CFG_PWM_VSB_TRIM_PERIOD*RTE_VSB_TRIM_DUTY_INIT/1000U))

#define PWM_CFG_PWM_VSB_OVP_PERIOD       ((uint16)(RTE_U32_CPU_CLK_FREQ/PWM_CFG_PWM_FRQ_VSB_OVP - 1u))
#define PWM_CFG_PWM_VSB_OVP_INIT         ((uint32)((uint32)PWM_CFG_PWM_VSB_OVP_PERIOD*1U/100U))


/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/
 
 #ifdef PWM_EXPORT_H
typedef enum PWM_CFG_E_TIM_CH_
{
	PWM_CFG_E_TIM_CH_1=0,
	PWM_CFG_E_TIM_CH_2,
	PWM_CFG_E_TIM_CH_3,
	PWM_CFG_E_TIM_CH_4
}PWM_CFG_E_TIM_CH;

/* The structure defining the setup of each timer PWM output */
typedef struct
{
  /* Peripheral (Tivaware sysctl.h values required, e.g. SYSCTL_PERIPH_TIMER0) */
  uint32 u32Perip;
  
  /* Enables or disables the High Speed APB (APB2) peripheral clock */
  void (* PeriphClockCmd)(uint32_t RCC_Periph, FunctionalState NewState);

  /* Timer base (Tivaware hw_memmap.h values required, e.g. TIMER0_BASE)*/
  TIM_TypeDef *pTimx;

  /* Values that can be passed to most of the timer APIs as the ui32Timer
      parameter. (Tivaware timer.h values required, e.g. TIMER_A)*/
  uint8 u8Channel;

  /* the timer load value, which used for set PWM output frequence. */
  uint16 u16TimPeriod;
	
	/* Specifies the pulse value to be loaded into the Capture Compare Register. */
	uint32 u32TimPulse;

  /* Specifies the TIM mode.*/
  uint16 u16TimMode;
	
	/* Specifies the output polarity. */
	uint16 u16TOCPolarity;    
}tPwmSetup;

static const tPwmSetup PWM_CFG_PWM_SETUP[] =
{
/* timer1 channel1 for PWM to be initialised*/
{
 .u32Perip       = RCC_APB2Periph_TIM15,
 .PeriphClockCmd = RCC_APB2PeriphClockCmd,
 .pTimx          = TIM15,
 .u8Channel      = (uint8)PWM_CFG_E_TIM_CH_2,
 .u16TimPeriod   = PWM_CFG_PWM_FAN_PERIOD,
 .u32TimPulse    = PWM_CFG_PWM_FAN_SPEED_INIT,
 .u16TimMode     = TIM_OCMode_PWM1,
 .u16TOCPolarity = TIM_OCPolarity_Low
},
/* timer14 channel1 for PWM to be initialised*/
{
 .u32Perip       = RCC_APB1Periph_TIM14,
 .PeriphClockCmd = RCC_APB1PeriphClockCmd,
 .pTimx          = TIM14,
 .u8Channel      = (uint8)PWM_CFG_E_TIM_CH_1,
 .u16TimPeriod   = PWM_CFG_PWM_VSB_TRIM_PERIOD,
 .u32TimPulse    = PWM_CFG_PWM_VSB_TRIM_INIT,
 .u16TimMode     = TIM_OCMode_PWM1,
 .u16TOCPolarity = TIM_OCPolarity_Low
},
/* timer3 channel2 for PWM to be initialised*/
{
 .u32Perip       = RCC_APB1Periph_TIM3,
 .PeriphClockCmd = RCC_APB1PeriphClockCmd,
 .pTimx          = TIM3,
 .u8Channel      = (uint8)PWM_CFG_E_TIM_CH_2,
 .u16TimPeriod   = PWM_CFG_PWM_VSB_OVP_PERIOD,
 .u32TimPulse    = PWM_CFG_PWM_VSB_OVP_INIT,
 .u16TimMode     = TIM_OCMode_PWM1,
 .u16TOCPolarity = TIM_OCPolarity_Low
},
}; /* */
#endif

typedef enum PWM_CFG_E_INDEX_
{
  PWM_CFG_E_INDEX_PWM_Fan_Ctrl = 0,
  PWM_CFG_E_INDEX_PWM_Vsb_Trim,
  PWM_CFG_E_INDEX_PWM_Vsb_Ovp,
  PWM_CFG_E_INDEX_PWM_COUNT
} PWM_CFG_E_INDEX;

#ifdef __cplusplus
  }
#endif
#endif  /* PWM_CFG_H */

  
/*
 * End of file
 */
