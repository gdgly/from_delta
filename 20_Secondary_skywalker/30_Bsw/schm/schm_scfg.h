/** *****************************************************************************
 * \file    schm_scfg.h
 * \brief   Server request service file for schm.c
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
#define MG_HRTIMER_MODULE         1
#define MG_WDG_MODULE             1
#define MG_COMP_MODULE            1
#define MG_PORT_MODULE            1
#define MG_EXTI_MODULE            1
#define MG_DAC_MODULE             1
#define MG_UART_MODULE            1
#define MG_FLASH_MODULE           1

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
inline void SCHM_scfg_vClockInit(void)
{
  #if MG_CLOCK_MODULE
  CLOCK_vInit();
  #endif
}

inline void SCHM_scfg_vClockDeInit(void)
{
  #if MG_CLOCK_MODULE
  CLOCK_vDeInit();
  #endif
}

/* ADC module section */
inline void SCHM_scfg_vAdcInit(void)
{
  #if MG_ADC_MODULE
  ADC_vInit();
  #endif
}

inline void SCHM_scfg_vAdcDeInit(void)
{
  #if MG_ADC_MODULE
  ADC_vDeInit();
  #endif
}

inline void SCHM_scfg_vAdcDmaNvicCfg(uint8 u8DmaChId, uint8 u8PrePriority, uint8 u8SubPriority)
{
  #if MG_ADC_MODULE
  ADC_vAdcDmaNvicCfg(u8DmaChId, u8PrePriority, u8SubPriority);
  #endif
}

__attribute__((section ("ccram")))
inline void SCHM_scfg_vAdcDma1Ch1IsrFlgReset(void)
{
  #if MG_ADC_MODULE
  ADC_vAdcDma1Ch1IsrFlgReset();
  #endif
}

__attribute__((section ("ccram")))
inline void SCHM_scfg_vAdcDma1Ch2IsrFlgReset(void)
{
  #if MG_ADC_MODULE
  ADC_vAdcDma1Ch2IsrFlgReset();
  #endif
}

/* TIMER module section */
inline void SCHM_scfg_vTimerInit(void)
{
  #if MG_TIMER_MODULE
  TIMER_vInit();
  #endif
}

inline void SCHM_scfg_vTimerDeInit(void)
{
  #if MG_TIMER_MODULE
  TIMER_vDeInit();
  #endif
}

inline void SCHM_scfg_vTimerClrIrFlg(uint8 u8TimerId)
{
  #if MG_TIMER_MODULE
  TIMER_vTimerClrIrFlg(u8TimerId);
  #endif
}

inline uint16 SCHM_scfg_u16TimerReadIrFlg(uint8 u8TimerId)
{
  #if MG_TIMER_MODULE
  return TIMER_u16TimerReadIrFlg(u8TimerId);
  #else
  return 0;
  #endif
}

inline void SCHM_scfg_vTimerSetPeriod(uint8 u8TimerId, uint16 u16usTimerPeriod)
{
  #if MG_TIMER_MODULE
  TIMER_vTimerSetPeriod(u8TimerId, u16usTimerPeriod);
  #endif
}

inline void SCHM_scfg_vTimerSetFrequency(uint8 u8TimerId, uint32 u32HzTimerFrequency)
{
  #if MG_TIMER_MODULE
  TIMER_vTimerSetFrequency(u8TimerId, u32HzTimerFrequency);
  #endif
}

inline void SCHM_scfg_vTimerNvicCfg(uint8 u8TimerId, uint8 u8PrePriority, uint8 u8SubPriority)
{
  #if MG_TIMER_MODULE
  TIMER_vTimerNvicCfg(u8TimerId, u8PrePriority, u8SubPriority);
  #endif
}

/* HRTIMER module section */
inline void SCHM_scfg_vHrTimerInit(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vInit();
  #endif
}

inline void SCHM_scfg_vHrTimerDeInit(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vDeInit();
  #endif
}

inline void SCHM_scfg_vSyncStartHrTimer(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vSyncStartHrTimer();
  #endif
}

inline void SCHM_scfg_vHrTimerIsrNvicCfg(uint8 u8HrTimChId, uint8 u8PrePriority, uint8 u8SubPriority)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerIsrNvicCfg(u8HrTimChId, u8PrePriority, u8SubPriority);
  #endif
}

__attribute__((section ("ccram")))
inline void SCHM_scfg_vHrTimerMstRepIsrFlgReset(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerMstRepIsrFlgReset();
  #endif
}

__attribute__((section ("ccram")))
inline uint8 SCHM_scfg_u8HrTimerMstRepReadIsrFlg(void)
{
  #if MG_HRTIMER_MODULE
  return HRTIMER_u8HrTimerMstRepReadIsrFlg();
  #else
  return 0;
  #endif
}

inline void SCHM_scfg_vHrTimerSetPeriod(uint8 u8TimerId, uint32 u321nsHrTimerPeriod)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerSetPeriod(u8TimerId, u321nsHrTimerPeriod);
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
  PORT_vInit();
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

inline void SCHM_scfg_vUartNvicCfg(uint8 u8UartId, uint8 u8PrePriority, uint8 u8SubPriority)
{
  #if MG_UART_MODULE
  UART_vUartNvicCfg(u8UartId, u8PrePriority, u8SubPriority);
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


#ifdef __cplusplus
  }
#endif
#endif  /* SCHM_SCFG_H */

  
/*
 * End of file
 */
