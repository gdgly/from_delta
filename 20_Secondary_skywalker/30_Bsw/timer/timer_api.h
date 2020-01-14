/** *****************************************************************************
 * \file    timer_api.h
 * \brief   Service function request file for timer.c
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

#ifndef TIMER_API_H
#define TIMER_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "timer_conf.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TIMER_vInit(void);

/** *****************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TIMER_vDeInit(void);

/** *****************************************************************************
 * \brief         Clear timer interrupt or event flag
 *
 * \param[in]     TimerId: can be 15 to 17
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TIMER_vTimerClrIrFlg(uint8 u8TimerId);

/** *****************************************************************************
 * \brief         Read timer interrupt flag
 *
 * \param[in]     TimerId: can be 15 to 17
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint16 TIMER_u16TimerReadIrFlg(uint8 u8TimerId);

/** *****************************************************************************
 * \brief         Set timer NVIC configuration
 *
 * \param[in]     TimerId: can be 15 to 17. PrePriority: can be 1 to 7. SubPriority: can be 1 to 7
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TIMER_vTimerNvicCfg(uint8 u8TimerId, uint8 u8PrePriority, uint8 u8SubPriority);

/** *****************************************************************************
 * \brief         Set timer period
 *
 * \param[in]     TimerId: can be 15 to 17. usTimerPeriod: period in uS
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TIMER_vTimerSetPeriod(uint8 u8TimerId, uint16 u16usTimerPeriod);

/** *****************************************************************************
 * \brief         Set timer Frequency
 *
 * \param[in]     TimerId: can be 15 to 17. usTimerPeriod: period in Hz
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TIMER_vTimerSetFrequency(uint8 u8TimerId, uint32 u32HzTimerFrequency);

/** *****************************************************************************
 * \brief         Set duty cycle
 *
 * \param[in]     Duty cycle
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void TIMER_vTimer1Ch1DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER1_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER1_CH1_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer1Ch2DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER1_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER1_CH2_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer1Ch3DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER1_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER1_CH3_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer1Ch4DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER1_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER1_CH4_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer2Ch1DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER2_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER2_CH1_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer2Ch2DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER2_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER2_CH2_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer2Ch3DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER2_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER2_CH3_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer2Ch4DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER2_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER2_CH4_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer3Ch1DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER3_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER3_CH1_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer3Ch2DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER3_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER3_CH2_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer3Ch3DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER3_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER3_CH3_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}

__attribute__((section ("ccram")))
extern inline void TIMER_vTimer3Ch4DutyCycle(uint16 u16q16DutyCycle)
{
  static uint32 u32PwmPeriod = 0U;

  /* Get half period */
  u32PwmPeriod = MG_REG_TIMER3_PERIOD;
  /* Up count PWM */
  /* Set the compare value (output high) */
  MG_REG_TIMER3_CH4_CCR = (uint16)((u32PwmPeriod * u16q16DutyCycle) >> 16);
}


#ifdef __cplusplus
  }
#endif
#endif  /* TIMER_API_H */

  
/*
 * End of file
 */
