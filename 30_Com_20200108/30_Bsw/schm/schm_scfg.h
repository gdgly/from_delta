/** *****************************************************************************
 * \file    schm_scfg.h
 * \brief   Server request service file for schm.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-03-18 10:51:05 +0800 (Mon, 18 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 150 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef SCHM_SCFG_H
#define SCHM_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
/* MCAL modules */
#define MG_CLOCK_MODULE           1
#define MG_ADC_MODULE             1
#define MG_TIMER_MODULE           1
#define MG_HRTIMER_MODULE         0
#define MG_WDG_MODULE             0
#define MG_COMP_MODULE            0
#define MG_PORT_MODULE            1
#define MG_EXTI_MODULE            0
#define MG_DAC_MODULE             0
#define MG_UART_MODULE            1
#define MG_FLASH_MODULE           1
#define MG_I2C_MODULE             1
#define MG_RTC_MODULE             1
#define MG_PWM_MODULE             1

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/* MCAL modules */
#if MG_CLOCK_MODULE
#include "clock_api.h"
#endif
#if MG_ADC_MODULE
#include "adc_api.h"
#endif
#if MG_TIMER_MODULE
#include "timer_api.h"
#endif
#if MG_HRTIMER_MODULE
#include "hrtimer_api.h"
#endif
#if MG_WDG_MODULE
#include "wdg_api.h"
#endif
#if MG_COMP_MODULE
#include "comp_api.h"
#endif
#if MG_PORT_MODULE
#include "port_api.h"
#endif
#if MG_EXTI_MODULE
#include "exti_api.h"
#endif
#if MG_DAC_MODULE
#include "dac_api.h"
#endif
#if MG_UART_MODULE
#include "uart_api.h"
#endif
#if MG_FLASH_MODULE
#include "flash_api.h"
#endif
#if MG_I2C_MODULE
#include "i2c_api.h"
#endif
#if MG_RTC_MODULE
#include "rtc_api.h"
#endif
#if MG_PWM_MODULE
#include "pwm_scb.h"
#endif

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Module interface
 ******************************************************************************/

/***************************************
 * MCAL modules
 **************************************/
/* CLOCK module section */
SINLINE void SCHM_scfg_vClockInit(void)
{
  #if MG_CLOCK_MODULE
  CLOCK_vInit();
  #endif
}

SINLINE void SCHM_scfg_vClockDeInit(void)
{
  #if MG_CLOCK_MODULE
  CLOCK_vDeInit();
  #endif
}

/* ADC module section */
SINLINE void SCHM_scfg_vAdcInit(void)
{
  #if MG_ADC_MODULE
  ADC_vInit();
  #endif
}

SINLINE void SCHM_scfg_vAdcDeInit(void)
{
  #if MG_ADC_MODULE
  ADC_vDeInit();
  #endif
}

/* TIMER module section */
SINLINE void SCHM_scfg_vTimerInit(void)
{
  #if MG_TIMER_MODULE
  TIMER_vInit();
  #endif
}

SINLINE void SCHM_scfg_vTimerDeInit(void)
{
  #if MG_TIMER_MODULE
  TIMER_vDeInit();
  #endif
}

SINLINE void SCHM_scfg_vTimerClearUpdateItFlg(void)
{
  #if MG_TIMER_MODULE
  TIMER_vClearUpdateFlg(TIMER_CFG_E_INDEX_TIMER_Schm);
  #endif
}

SINLINE uint8 SCHM_scfg_u8TimerGetUpdateItFlg(void)
{
  #if MG_TIMER_MODULE
  return TIMER_u8GetUpdateFlg(TIMER_CFG_E_INDEX_TIMER_Schm);
  #endif
}

/* HRTIMER module section */
SINLINE void SCHM_scfg_vHrTimerInit(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vInit();
  #endif
}

SINLINE void SCHM_scfg_vHrTimerDeInit(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vDeInit();
  #endif
}

SINLINE void SCHM_scfg_vSyncStartHrTimer(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vSyncStartHrTimer();
  #endif
}

/* Watchdog module section */
inline void SCHM_scfg_vWdgInit(void)
{
  #if MG_WDG_MODULE
  WDG_vInit();
  #endif
}

inline void SCHM_scfg_vWdgDeInit(void)
{
  #if MG_WDG_MODULE
  WDG_vDeInit();
  #endif
}

inline void SCHM_scfg_vWdgEn(void)
{
  #if MG_WDG_MODULE
  WDG_vWatchDogEn();
  #endif
}

inline void SCHM_scfg_vWdgFeed(void)
{
  #if MG_WDG_MODULE
  WDG_vWatchDogFeed();
  #endif
}

inline void SCHM_scfg_vWdgSetTimeOutDly(uint16 u16msTimeOutDly)
{
  #if MG_WDG_MODULE
  WDG_vWdgSetTimeOutDly(u16msTimeOutDly);
  #endif
}

inline void SCHM_scfg_vWdgSysReset(void)
{
  #if MG_WDG_MODULE
  WDG_vSysReset();
  #endif
}

/* Comparator module section */
inline void SCHM_scfg_vCompInit(void)
{
  #if MG_COMP_MODULE
  COMP_vInit();
  #endif
}

inline void SCHM_scfg_vCompDeInit(void)
{
  #if MG_COMP_MODULE
  COMP_vDeInit();
  #endif
}

/* Port module section */
inline void SCHM_scfg_vPortInit(void)
{
  #if MG_PORT_MODULE
  PORT_vSetGpioPin(PORT_CFG_E_B12_SYNC_INTERNAL,TRUE);
  PORT_vInit();
	/*     
  *PORT_vSetGpioMode(PORT_CFG_E_A7_VSB_OVP_TEST,PORT_CFG_E_GPIO_MODE_OUT);
  *PORT_vSetGpioPin(PORT_CFG_E_A7_VSB_OVP_TEST,TRUE);
	*/ /* not sure if pin A7 used to trim or ovp test */
  #endif
}

inline void SCHM_scfg_vPortDeInit(void)
{
  #if MG_PORT_MODULE
  PORT_vDeInit();
  #endif
}

/* External event module section */
inline void SCHM_scfg_vExtiInit(void)
{
  #if MG_EXTI_MODULE
  EXTI_vInit();
  #endif
}

inline void SCHM_scfg_vExtiDeInit(void)
{
  #if MG_EXTI_MODULE
  EXTI_vDeInit();
  #endif
}

/* DAC module section */
inline void SCHM_scfg_vDacInit(void)
{
  #if MG_DAC_MODULE
  DAC_vInit();
  #endif
}

inline void SCHM_scfg_vDacDeInit(void)
{
  #if MG_DAC_MODULE
  DAC_vDeInit();
  #endif
}

/* UART module section */
inline void SCHM_scfg_vUartInit(void)
{
  #if MG_UART_MODULE
  UART_vInit();
  #endif
}

inline void SCHM_scfg_vUartDeInit(void)
{
  #if MG_UART_MODULE
  UART_vDeInit();
  #endif
}

/* Flash module section */
inline void SCHM_scfg_vFlashInit(void)
{
  #if MG_FLASH_MODULE
  FLASH_vInit();
  #endif
}

inline void SCHM_scfg_vFlashDeInit(void)
{
  #if MG_FLASH_MODULE
  FLASH_vDeInit();
  #endif
}

/* I2C module section */
inline void SCHM_scfg_vI2cInit(void)
{
  #if MG_I2C_MODULE
  I2C_vInit();
  #endif
}

inline void SCHM_scfg_vI2cDeInit(void)
{
  #if MG_I2C_MODULE
  I2C_vDeInit();
  #endif
}

inline void SCHM_scfg_vI2cTimeOutHandler(void)
{
  #if MG_I2C_MODULE
  I2C_vI2cTimeOutHandler();
  #endif
}


/* RTC module section */
inline void SCHM_scfg_vRtcInit(void)
{
  #if MG_RTC_MODULE
  RTC_vInit();
  #endif
}

inline void SCHM_scfg_vRtcDeInit(void)
{
  #if MG_RTC_MODULE
  RTC_vDeInit();
  #endif
}

/* PWM manager module section*/
SINLINE void SCHM_scfg_vPWMInit(void)
{
  #if MG_PWM_MODULE
	PWM_vInit();
	#endif
}

SINLINE void SCHM_scfg_vPWMDeInit(void)
{
  #if MG_PWM_MODULE
	PWM_vDeInit();
	#endif
}

SINLINE void SCHM_scfg_vDisableIrq(void)
{
	__disable_irq();
}

SINLINE void SCHM_scfg_vEnableIrq(void)
{
	__enable_irq();
}


#ifdef __cplusplus
  }
#endif
#endif  /* SCHM_SCFG_H */

  
/*
 * End of file
 */
