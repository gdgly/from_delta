/*******************************************************************************
 * \file    pwm.c
 * \brief   init PWM
 *
 * \section AUTHOR
 *    1. Gary.Weng
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
#define PWM_EXPORT_H
	#include "pwm_api.h"
  #include "pwm_scb.h"
  #include "pwm_cfg.h"
  #include "pwm_scfg.h"
  #include "pwm_conf.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

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
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize and configure PWM modules
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void PWM_vInit(void)
{  
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
	uint8 u8Loop;
	
	for(u8Loop=0;u8Loop<(uint8)PWM_CFG_E_INDEX_PWM_COUNT;u8Loop++)
	{
		/* TIM clock enable */
		PWM_CFG_PWM_SETUP[u8Loop].PeriphClockCmd(PWM_CFG_PWM_SETUP[u8Loop].u32Perip, ENABLE);
		
		/* Time Base configuration */
		TIM_TimeBaseStructure.TIM_Prescaler         = 0;
		TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period            = PWM_CFG_PWM_SETUP[u8Loop].u16TimPeriod;
		TIM_TimeBaseStructure.TIM_ClockDivision     = 0;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		/* Use initialized structure for TIM1 Configuration */
		TIM_TimeBaseInit(PWM_CFG_PWM_SETUP[u8Loop].pTimx, &TIM_TimeBaseStructure);

		/* Channel 1 Configuration in PWM mode */
		TIM_OCInitStructure.TIM_OCMode       = PWM_CFG_PWM_SETUP[u8Loop].u16TimMode;
		TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_Pulse        = PWM_CFG_PWM_SETUP[u8Loop].u32TimPulse;
		TIM_OCInitStructure.TIM_OCPolarity   = PWM_CFG_PWM_SETUP[u8Loop].u16TOCPolarity;
		TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

    switch(PWM_CFG_PWM_SETUP[u8Loop].u8Channel)
		{
			case PWM_CFG_E_TIM_CH_1:
			{
				/* Use initialized structure for TIMx Configuration */
				TIM_OC1Init(PWM_CFG_PWM_SETUP[u8Loop].pTimx, &TIM_OCInitStructure);
				TIM_OC1PreloadConfig(PWM_CFG_PWM_SETUP[u8Loop].pTimx, TIM_OCPreload_Enable);
				break;
			}
			case PWM_CFG_E_TIM_CH_2:
			{
				/* Use initialized structure for TIMx Configuration */
				TIM_OC2Init(PWM_CFG_PWM_SETUP[u8Loop].pTimx, &TIM_OCInitStructure);
				TIM_OC2PreloadConfig(PWM_CFG_PWM_SETUP[u8Loop].pTimx, TIM_OCPreload_Enable);
				break;
			}
			case PWM_CFG_E_TIM_CH_3:
			{
				/* Use initialized structure for TIMx Configuration */
				TIM_OC3Init(PWM_CFG_PWM_SETUP[u8Loop].pTimx, &TIM_OCInitStructure);
				TIM_OC3PreloadConfig(PWM_CFG_PWM_SETUP[u8Loop].pTimx, TIM_OCPreload_Enable);
				break;
			}
			case PWM_CFG_E_TIM_CH_4:
			{
				/* Use initialized structure for TIMx Configuration */
				TIM_OC4Init(PWM_CFG_PWM_SETUP[u8Loop].pTimx, &TIM_OCInitStructure);
				TIM_OC4PreloadConfig(PWM_CFG_PWM_SETUP[u8Loop].pTimx, TIM_OCPreload_Enable);
				break;
			}
      default:
		  {
				break;
			}
	  }
		
		/* TIM counter enable */
		TIM_Cmd(PWM_CFG_PWM_SETUP[u8Loop].pTimx, ENABLE);
		
		/* TIM Main Output Enable */
		TIM_CtrlPWMOutputs(PWM_CFG_PWM_SETUP[u8Loop].pTimx, ENABLE);
	}
  
} /* PWM_vPwmHwInit() */

/*******************************************************************************
 * \brief         Initialize and configure PWM modules
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void PWM_vDeInit(void)
{
}

/*******************************************************************************
 * \brief         Set PWM duty
 *                
 * \param[in]     u16Duty  duty set
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void PWM_vPwmDutyUpdate(PWM_CFG_E_INDEX ePwmIndex,uint16 u16Duty)
{
  uint16 u16Dummy; 

  u16Dummy = (uint16)(((uint32)(u16Duty) * (PWM_CFG_PWM_SETUP[ePwmIndex].u16TimPeriod)) / 1000u);
 
	switch(PWM_CFG_PWM_SETUP[ePwmIndex].u8Channel)
	{
		case PWM_CFG_E_TIM_CH_1:
		{
			/* Use initialized structure for TIMx Configuration */
			TIM_SetCompare1(PWM_CFG_PWM_SETUP[ePwmIndex].pTimx, u16Dummy); 
			break;
		}
		case PWM_CFG_E_TIM_CH_2:
		{
			/* Use initialized structure for TIMx Configuration */
			TIM_SetCompare2(PWM_CFG_PWM_SETUP[ePwmIndex].pTimx, u16Dummy); 
			break;
		}
		case PWM_CFG_E_TIM_CH_3:
		{
			/* Use initialized structure for TIMx Configuration */
			TIM_SetCompare3(PWM_CFG_PWM_SETUP[ePwmIndex].pTimx, u16Dummy); 
			break;
		}
		case PWM_CFG_E_TIM_CH_4:
		{
			/* Use initialized structure for TIMx Configuration */
			TIM_SetCompare4(PWM_CFG_PWM_SETUP[ePwmIndex].pTimx, u16Dummy); 
			break;
		}
		default:
		{
			break;
		}
	}
} /* PWM_vPwmDutyUpdate() */

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/* 
 * End of file
 */
