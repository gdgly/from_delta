/** *****************************************************************************
 * \file    timer_cfg.h
 * \brief   Server call back service file for timer.c
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

#ifndef TIMER_CFG_H
#define TIMER_CFG_H
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
#define TIMER_CFG_TIMER_FRQ_SCHM              ((uint32)10000)    /* Schm frequency is 5K */
		
#define TIMER_CFG_TIMER_SCHM_PERIOD           ((uint16)(RTE_U32_CPU_CLK_FREQ/TIMER_CFG_TIMER_FRQ_SCHM - 1u))

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/
 
 #ifdef TIMER_EXPORT_H

/* The structure defining the setup of each timer PWM output */
typedef struct
{
  /* Peripheral (Tivaware sysctl.h values required, e.g. SYSCTL_PERIPH_TIMER0) */
  uint32 u32Perip;
  
  /* Enables or disables the High Speed APB (APB2) peripheral clock */
  void (* PeriphClockCmd)(uint32_t RCC_Periph, FunctionalState NewState);

  /* Timer base (Tivaware hw_memmap.h values required, e.g. TIMER0_BASE)*/
  TIM_TypeDef *pTimx;

	/*!< Specifies the prescaler value used to divide the TIM clock.
       This parameter can be a number between 0x0000 and 0xFFFF */
  uint16 u16Prescaler;         

	/*!< Specifies the counter mode.
       This parameter can be a value of @ref TIM_Counter_Mode */
  uint16 u16CounterMode;       

	/*!< Specifies the period value to be loaded into the active
			 Auto-Reload Register at the next update event.
			 This parameter must be a number between 0x0000 and 0xFFFF.  */
  uint32 u32Period;             

	/*!< Specifies the clock division.
       This parameter can be a value of @ref TIM_Clock_Division_CKD */
  uint16 u16ClockDivision;


  /*!< Specifies the repetition counter value.  
       @note This parameter is valid only for TIM1. */  
  uint8 u8RepetitionCounter;  
	
	uint8 u8IsEnableIT;
	
	uint16 u16TIM_IT;
	uint16 u16TIM_EventSource;
	
}tTimerSetup;

static const tTimerSetup TIMER_CFG_TIMER_SETUP[] =
{
/* timer15  to be initialised*/
{
 .u32Perip             = RCC_APB2Periph_TIM17,
 .PeriphClockCmd       = RCC_APB2PeriphClockCmd,
 .pTimx                = TIM17,
 .u16Prescaler         = TIM_CKD_DIV1,
 .u16CounterMode       = TIM_CounterMode_Up,
 .u32Period            = TIMER_CFG_TIMER_SCHM_PERIOD,
 .u16ClockDivision     = 0x0000u,
 .u8RepetitionCounter  = 0x00,
 .u8IsEnableIT         = FALSE,
 .u16TIM_IT            = 0x00,
 .u16TIM_EventSource   = TIM_EventSource_Update
}
}; /* */
#endif

typedef enum TIMER_CFG_E_INDEX_
{
  TIMER_CFG_E_INDEX_TIMER_Schm = 0,
  TIMER_CFG_E_INDEX_TIMER_COUNT
} TIMER_CFG_E_INDEX;

#ifdef __cplusplus
  }
#endif
#endif  /* TIMER_CFG_H */

  
/*
 * End of file
 */
