/*******************************************************************************
 * \file    timer.c
 * \brief   MCU timer and high resolution timer configuration
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2019-03-01 14:35:06 +0800 (Fri, 01 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 145 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>

/* Module header */
#define TIMER_EXPORT_H
	#include "timer_api.h"
  #include "timer_scb.h"
  #include "timer_cfg.h"
  #include "timer_scfg.h"
  #include "timer_conf.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/* Define TIMER17 period in microseconds */
#define MG_U16_TIMER15_PERIOD_US     ((uint16)19U)
/* Convert period into compare value */
#define MG_U16_TIMER15_PERIOD        (uint16_t)(RTE_U32_CPU_CLK_FREQ / (1000000 / MG_U16_TIMER15_PERIOD_US))
  
#define MG_SCHM_CLEAR_INT_FLAG   TIM15->SR = (~TIM_FLAG_Update)
/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/


/*******************************************************************************
 * \brief         Initialize Timer for cycle
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMER_vInit(void)
{
  /* Temporary typedefs */
	uint8 u8Loop;
	TIM_TimeBaseInitTypeDef	TIMx_TimerInitCfg;	
	
	for(u8Loop=0;u8Loop<(uint8)TIMER_CFG_E_INDEX_TIMER_COUNT;u8Loop++)
	{
		/*
		 * 16-bit TIMERx
		 * TIMERx global initialization for time base usage
		 */

		/* Enable TIMER15 peripheral clock */
		TIMER_CFG_TIMER_SETUP[u8Loop].PeriphClockCmd(TIMER_CFG_TIMER_SETUP[u8Loop].u32Perip, ENABLE);
		/* Set timer period value */
		TIMx_TimerInitCfg.TIM_Period = TIMER_CFG_TIMER_SETUP[u8Loop].u32Period;
		/* INTCLOCK division set to 1 */
		TIMx_TimerInitCfg.TIM_ClockDivision = TIMER_CFG_TIMER_SETUP[u8Loop].u16ClockDivision;
		/* Counter mode to up-count */
		TIMx_TimerInitCfg.TIM_CounterMode = TIMER_CFG_TIMER_SETUP[u8Loop].u16CounterMode;
		/* Prescaler to 0 */
		TIMx_TimerInitCfg.TIM_Prescaler = TIMER_CFG_TIMER_SETUP[u8Loop].u16Prescaler;
		/* Repetition counter to 0 */
		TIMx_TimerInitCfg.TIM_RepetitionCounter = TIMER_CFG_TIMER_SETUP[u8Loop].u8RepetitionCounter;

		/* Use initialized structure for TIMER15 */
		TIM_TimeBaseInit(TIMER_CFG_TIMER_SETUP[u8Loop].pTimx, &TIMx_TimerInitCfg);
		
		if(FALSE == TIMER_CFG_TIMER_SETUP[u8Loop].u8IsEnableIT)
		{
			TIM_GenerateEvent(TIMER_CFG_TIMER_SETUP[u8Loop].pTimx, TIMER_CFG_TIMER_SETUP[u8Loop].u16TIM_EventSource);
		}
		else
		{
			/* Turn on timer interrupt */
			TIM_ITConfig(TIMER_CFG_TIMER_SETUP[u8Loop].pTimx, TIMER_CFG_TIMER_SETUP[u8Loop].u16TIM_IT, ENABLE);
		}
		
		/* Enable TIMER */
		TIM_Cmd(TIMER_CFG_TIMER_SETUP[u8Loop].pTimx, ENABLE);
  }
}

/*******************************************************************************
 * \brief         DeInitialize Timer for cycle
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMER_vDeInit(void)
{
}


/*******************************************************************************
 * \brief         Clears the TIMx's update interrupt pending bits.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMER_vClearUpdateFlg(TIMER_CFG_E_INDEX eTimerIndex)
{
	TIM_ClearFlag(TIMER_CFG_TIMER_SETUP[eTimerIndex].pTimx,TIMER_CFG_TIMER_SETUP[eTimerIndex].u16TIM_EventSource);
}

/*******************************************************************************
 * \brief         Checks whether the TIM update interrupt has occurred or not.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
uint8 TIMER_u8GetUpdateFlg(TIMER_CFG_E_INDEX eTimerIndex)
{
	return (uint8)TIM_GetFlagStatus(TIMER_CFG_TIMER_SETUP[eTimerIndex].pTimx,TIMER_CFG_TIMER_SETUP[eTimerIndex].u16TIM_EventSource);
}



/*
 * End of file
 */
