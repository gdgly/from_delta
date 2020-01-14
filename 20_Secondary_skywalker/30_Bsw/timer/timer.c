/** *****************************************************************************
 * \file    timer.c
 * \brief   MCU timer and high resolution timer configuration
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

/*******************************************************************************
 * Included header
 ******************************************************************************/
 
#include "StdPeriphDriver.h"
#include "global.h"
#include "debug_llc.h"

/* Module header */
#define TIMER_EXPORT_H
  #include "timer_api.h"
  #include "timer_scb.h"
  #include "timer_cfg.h"
  #include "timer_scfg.h"
  #include "timer_conf.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
 
static uint32 mg_u32SysClockSrc;
static uint32 mg_u32SysClock;
static uint32 mg_u32q12usTimer1ConvFact;
static uint32 mg_u32q12usTimer2ConvFact;
static uint32 mg_u32q12usTimer3ConvFact;
static uint32 mg_u32q12usTimer15ConvFact;
static uint32 mg_u32q12usTimer16ConvFact;
static uint32 mg_u32q12usTimer17ConvFact;

static uint32 mg_u32HzTimer1Clk;
static uint32 mg_u32HzTimer2Clk;
static uint32 mg_u32HzTimer3Clk;
static uint32 mg_u32HzTimer15Clk;
static uint32 mg_u32HzTimer16Clk;
static uint32 mg_u32HzTimer17Clk;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void TIMER_vGetSysClk(void);
static void TIMER_vTimerHwInit(void);
#if MG_TIM1_ENA
static void mg_vTimer1HwInit(void);
#endif
#if MG_TIM2_ENA
static void mg_vTimer2HwInit(void);
#endif
#if MG_TIM3_ENA
static void mg_vTimer3HwInit(void);
#endif
#if MG_TIM15_ENA
static void mg_vTimer15HwInit(void);
#endif
#if MG_TIM16_ENA
static void mg_vTimer16HwInit(void);
#endif
#if MG_TIM17_ENA
static void mg_vTimer17HwInit(void);
#endif

/*******************************************************************************
 * Global functions (public to other modules)
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
void TIMER_vInit(void)
{
  /* Get the system clock */
  TIMER_vGetSysClk();
  /* Init timer */
  TIMER_vTimerHwInit();
}

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
void TIMER_vDeInit(void)
{
  TIM_DeInit(TIM1);
  TIM_DeInit(TIM2);
  TIM_DeInit(TIM3);
  TIM_DeInit(TIM15);
  TIM_DeInit(TIM16);
  TIM_DeInit(TIM17);
}

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
void TIMER_vTimerClrIrFlg(uint8 u8TimerId)
{
  /* TIM15 */
  if (u8TimerId == MG_TIM15)
  {
    /* Clear Timer15 Interrupt Flag */
    (TIM15->SR = (uint16)~TIM_FLAG_Update);
  }
  /* TIM16 */
  if (u8TimerId == MG_TIM16)
  {
    /* Clear Timer16 Interrupt Flag */
    (TIM16->SR = (uint16)~TIM_FLAG_Update);
  }
  /* TIM17 */
  if (u8TimerId == MG_TIM17)
  {
    /* Clear Timer17 Interrupt Flag */
    (TIM17->SR = (uint16)~TIM_FLAG_Update);
  }
}

/** *****************************************************************************
 * \brief         Check if timer 17 interrupt or event flag occured
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint16 TIMER_u16TimerReadIrFlg(uint8 u8TimerId)
{
  uint16 u16TimerIrFlg;
  /* TIM15 */
  if (u8TimerId == MG_TIM15)
  {
    /* Read Timer15 interrupt flag */
    u16TimerIrFlg = (TIM15->SR & TIM_FLAG_Update);
  }
  /* TIM16 */
  if (u8TimerId == MG_TIM16)
  {
    /* Read Timer16 interrupt flag */
    u16TimerIrFlg = (TIM16->SR & TIM_FLAG_Update);
  }
  /* TIM17 */
  if (u8TimerId == MG_TIM17)
  {
    /* Read Timer17 interrupt flag */
    u16TimerIrFlg = (TIM17->SR & TIM_FLAG_Update);
  }
  return u16TimerIrFlg;
}

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
void TIMER_vTimerNvicCfg(uint8 u8TimerId, uint8 u8PrePriority, uint8 u8SubPriority)
{
  static uint8 u8IrqCh = 0;
  
  /* TIM15 */
  if (u8TimerId == MG_TIM15)
  {
    u8IrqCh = TIM1_BRK_TIM15_IRQn;
  }
  /* TIM16 */
  if (u8TimerId == MG_TIM16)
  {
    u8IrqCh = TIM1_UP_TIM16_IRQn;
  }
  /* TIM17 */
  if (u8TimerId == MG_TIM17)
  {
    u8IrqCh = TIM1_TRG_COM_TIM17_IRQn;
  }
  
  /* Temporary typedefs */
  NVIC_InitTypeDef      NVIC_InitCfg;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  /* Enable the TIM17 gloabal Interrupt. Priority is lower than the above three */
  NVIC_InitCfg.NVIC_IRQChannel = u8IrqCh;
  NVIC_InitCfg.NVIC_IRQChannelPreemptionPriority = u8PrePriority;
  NVIC_InitCfg.NVIC_IRQChannelSubPriority = u8SubPriority;
  NVIC_InitCfg.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitCfg);
}

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
void TIMER_vTimerSetPeriod(uint8 u8TimerId, uint16 u16usTimerPeriod)
{
  /* TIM1 */
  if (u8TimerId == MG_TIM1)
  {
    /* Convert us to timer value */
    u16usTimerPeriod = (uint16)((mg_u32q12usTimer1ConvFact * u16usTimerPeriod) >> 12);
    /* Set the period value */
    MG_REG_TIMER1_PERIOD = u16usTimerPeriod;
  }
  /* TIM2 */
  if (u8TimerId == MG_TIM2)
  {
    /* Convert us to timer value */
    u16usTimerPeriod = (uint16)((mg_u32q12usTimer2ConvFact * u16usTimerPeriod) >> 12);
    /* Set the period value */
    MG_REG_TIMER2_PERIOD = u16usTimerPeriod;
  }
  /* TIM3 */
  if (u8TimerId == MG_TIM3)
  {
    /* Convert us to timer value */
    u16usTimerPeriod = (uint16)((mg_u32q12usTimer3ConvFact * u16usTimerPeriod) >> 12);
    /* Set the period value */
    MG_REG_TIMER3_PERIOD = u16usTimerPeriod;
  }

  /* TIM15 */
  if (u8TimerId == MG_TIM15)
  {
    /* Convert us to timer value */
    u16usTimerPeriod = (uint16)((mg_u32q12usTimer15ConvFact * u16usTimerPeriod) >> 12);
    /* Set the period value */
    MG_REG_TIMER15_PERIOD = u16usTimerPeriod;
  }
  /* TIM16 */
  if (u8TimerId == MG_TIM16)
  {
    /* Convert us to timer value */
    u16usTimerPeriod = (uint16)((mg_u32q12usTimer16ConvFact * u16usTimerPeriod) >> 12);
    /* Set the period value */
    MG_REG_TIMER16_PERIOD = u16usTimerPeriod;
  }
  /* TIM17 */
  if (u8TimerId == MG_TIM17)
  {
    /* Convert us to timer value */
    u16usTimerPeriod = (uint16)((mg_u32q12usTimer17ConvFact * u16usTimerPeriod) >> 12);
    /* Set the period value */
    MG_REG_TIMER17_PERIOD = u16usTimerPeriod;
  }
}

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
void TIMER_vTimerSetFrequency(uint8 u8TimerId, uint32 u32HzTimerFrequency)
{
  /* TIM1 */
  if (u8TimerId == MG_TIM1)
  {
    /* Set the period value */
    MG_REG_TIMER1_PERIOD = (uint16)((mg_u32HzTimer1Clk / u32HzTimerFrequency) - 1);
  }
  /* TIM2 */
  if (u8TimerId == MG_TIM2)
  {
    /* Set the period value */
    MG_REG_TIMER2_PERIOD = (uint16)((mg_u32HzTimer2Clk / u32HzTimerFrequency) - 1);
  }
  /* TIM3 */
  if (u8TimerId == MG_TIM3)
  {
    /* Set the period value */
    MG_REG_TIMER3_PERIOD = (uint16)((mg_u32HzTimer3Clk / u32HzTimerFrequency) - 1);
  }
  /* TIM15 */
  if (u8TimerId == MG_TIM15)
  {
    /* Set the period value */
    MG_REG_TIMER15_PERIOD = (uint16)((mg_u32HzTimer15Clk / u32HzTimerFrequency) - 1);
  }
  /* TIM16 */
  if (u8TimerId == MG_TIM16)
  {
    /* Set the period value */
    MG_REG_TIMER16_PERIOD = (uint16)((mg_u32HzTimer16Clk / u32HzTimerFrequency) - 1);
  }
  /* TIM17 */
  if (u8TimerId == MG_TIM17)
  {
    /* Set the period value */
    MG_REG_TIMER17_PERIOD = (uint16)((mg_u32HzTimer17Clk / u32HzTimerFrequency) - 1);
  }
}
  
/*******************************************************************************
 * Local functions (privat for module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initialize timer for input capture and timer base
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void TIMER_vGetSysClk(void)
{
  /* 
   * 1 : External oscillator
   * 0 : Internal oscilator
   */
  /* Read the clock source */
  mg_u32SysClockSrc = RCC->CFGR & RCC_CFGR_PLLSRC;
  /* Assume 72MHz clock when external oscillator is used */
  if (mg_u32SysClockSrc)
  {
    mg_u32SysClock = 72000000U;
  }
  /* Assume 64MHz clock when internal oscillator is used */
  else
  {
    mg_u32SysClock = 64000000U;
  }
}

/** *****************************************************************************
 * \brief         Setup all required timers
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void TIMER_vTimerHwInit(void)
{
  /* Setup timers */
  #if MG_TIM1_ENA
  mg_vTimer1HwInit();
  #endif
  #if MG_TIM2_ENA
  mg_vTimer2HwInit();
  #endif
  #if MG_TIM3_ENA
  mg_vTimer3HwInit();
  #endif
  #if MG_TIM15_ENA
  mg_vTimer15HwInit();
  #endif
  #if MG_TIM16_ENA
  mg_vTimer16HwInit();
  #endif
  #if MG_TIM17_ENA
  mg_vTimer17HwInit();
  #endif
}

/** *****************************************************************************
 * \brief         Initialize timer for input capture and timer base
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
#if MG_TIM1_ENA
static void mg_vTimer1HwInit(void)
{
  /*
   * 16-bit TIMER1
   */
  /* Temporary typedefs */
  TIM_TimeBaseInitTypeDef   TIM1_TimerInitCfg;
  TIM_OCInitTypeDef         TIM1_OCInitCfg;

  /* Enable TIMER3 peripheral clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* Set timer period value */
  TIM1_TimerInitCfg.TIM_Period = 0x0FFF;
  /* INTCLOCK division set to 1 */
  TIM1_TimerInitCfg.TIM_ClockDivision = TIM_CKD_DIV1;
  /* Counter mode to up-count */
  TIM1_TimerInitCfg.TIM_CounterMode = TIM_CounterMode_Up;
  /* Prescaler to 64 (scale down to 1MHz) */
  TIM1_TimerInitCfg.TIM_Prescaler = MG_TIM1_PRESCALER;
  /* Repetition counter to 0 */
  TIM1_TimerInitCfg.TIM_RepetitionCounter = 0x0000;

  /* Use initialized structure for TIMER */
  TIM_TimeBaseInit(TIM1, &TIM1_TimerInitCfg);

  /* Channel 1 configuration in PWM mode */
  TIM1_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM2;
  TIM1_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable;
  TIM1_OCInitCfg.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM1_OCInitCfg.TIM_Pulse = 0x0000;
  TIM1_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM1_OCInitCfg.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM1_OCInitCfg.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM1_OCInitCfg.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  /* Use initialized structure for TIMER */
  TIM_OC1Init(TIM1, &TIM1_OCInitCfg);
  //TIM_OC2Init(TIM1, &TIM1_OCInitCfg);
  //TIM_OC3Init(TIM1, &TIM1_OCInitCfg);
  //TIM_OC4Init(TIM1, &TIM1_OCInitCfg);

  /* Enable timer preload */
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  //TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
  //TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
  //TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* Enable TIMER */
  TIM_Cmd(TIM1, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

  /* Calculate the conversion factor for micro seconds to timer value */
  mg_u32q12usTimer1ConvFact = U32Q12(F64_MICRO * mg_u32SysClock / (MG_TIM1_PRESCALER + 1));
  mg_u32HzTimer1Clk = mg_u32SysClock / (MG_TIM1_PRESCALER + 1);
}
#endif

#if MG_TIM2_ENA
static void mg_vTimer2HwInit(void)
{
  /*
   * 32-bit TIMER2
   */
  /* Temporary typedefs */
  TIM_TimeBaseInitTypeDef   TIM2_TimerInitCfg;
  TIM_OCInitTypeDef         TIM2_OCInitCfg;

  /* Enable TIMER2 peripheral clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* Set timer period value */
  TIM2_TimerInitCfg.TIM_Period = 0x0FFF;
  /* INTCLOCK division set to 1 */
  TIM2_TimerInitCfg.TIM_ClockDivision = TIM_CKD_DIV1;
  /* Counter mode to up-count */
  TIM2_TimerInitCfg.TIM_CounterMode = TIM_CounterMode_Up;
  /* Prescaler to 64 (scale down to 1MHz) */
  TIM2_TimerInitCfg.TIM_Prescaler = MG_TIM2_PRESCALER;
  /* Repetition counter to 0 */
  TIM2_TimerInitCfg.TIM_RepetitionCounter = 0x0000;

  /* Use initialized structure for TIMER2 */
  TIM_TimeBaseInit(TIM2, &TIM2_TimerInitCfg);

  /* Channel 1 configuration in PWM mode */
  TIM2_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM2;
  TIM2_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable;
  TIM2_OCInitCfg.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM2_OCInitCfg.TIM_Pulse = 0x0000;
  TIM2_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM2_OCInitCfg.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM2_OCInitCfg.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM2_OCInitCfg.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  /* Use initialized structure for TIMER2 */
  TIM_OC1Init(TIM2, &TIM2_OCInitCfg);
  TIM_OC2Init(TIM2, &TIM2_OCInitCfg);
  TIM_OC3Init(TIM2, &TIM2_OCInitCfg);
  TIM_OC4Init(TIM2, &TIM2_OCInitCfg);
  
  /* Enable timer preload */
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* Enable TIMER2 */
  TIM_Cmd(TIM2, ENABLE);

  /* Main Output Enable */
  //TIM_CtrlPWMOutputs(TIM2, ENABLE);

  /* Calculate the conversion factor for micro seconds to timer value */
  mg_u32q12usTimer2ConvFact = U32Q12(F64_MICRO * mg_u32SysClock / (MG_TIM2_PRESCALER + 1));
  mg_u32HzTimer2Clk = mg_u32SysClock / (MG_TIM2_PRESCALER + 1);
}
#endif

#if MG_TIM3_ENA
static void mg_vTimer3HwInit(void)
{
  /*
   * 16-bit TIMER3
   */
  TIM_TimeBaseInitTypeDef   TIM3_TimerInitCfg;
  TIM_OCInitTypeDef         TIM3_OCInitCfg;

  /* Enable TIMER3 peripheral clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* Set timer period value */
  TIM3_TimerInitCfg.TIM_Period = 0x0FFF;
  /* INTCLOCK division set to 1 */
  TIM3_TimerInitCfg.TIM_ClockDivision = TIM_CKD_DIV1;
  /* Counter mode to up-count */
  TIM3_TimerInitCfg.TIM_CounterMode = TIM_CounterMode_Up;
  /* Prescaler to 64 (scale down to 1MHz) */
  TIM3_TimerInitCfg.TIM_Prescaler = MG_TIM3_PRESCALER;
  /* Repetition counter to 0 */
  TIM3_TimerInitCfg.TIM_RepetitionCounter = 0x0000;

  /* Use initialized structure for TIMER2 */
  TIM_TimeBaseInit(TIM3, &TIM3_TimerInitCfg);

  /* Channel 1 configuration in PWM mode */
  TIM3_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM2;
  TIM3_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable;
  TIM3_OCInitCfg.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM3_OCInitCfg.TIM_Pulse = 0x0000;
  TIM3_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM3_OCInitCfg.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM3_OCInitCfg.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM3_OCInitCfg.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  /* Use initialized structure for TIMER2 */
  TIM_OC1Init(TIM3, &TIM3_OCInitCfg);
  TIM_OC2Init(TIM3, &TIM3_OCInitCfg);
  TIM_OC3Init(TIM3, &TIM3_OCInitCfg);
  TIM_OC4Init(TIM3, &TIM3_OCInitCfg);

  /* Enable timer preload */
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* Enable TIMER2 */
  TIM_Cmd(TIM3, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM3, ENABLE);

  /* Calculate the conversion factor for micro seconds to timer value */
  mg_u32q12usTimer3ConvFact = U32Q12(F64_MICRO * mg_u32SysClock / (MG_TIM3_PRESCALER + 1));
  mg_u32HzTimer3Clk = mg_u32SysClock / (MG_TIM3_PRESCALER + 1);
}
#endif

#if MG_TIM15_ENA
static void mg_vTimer15HwInit(void)
{
  /*
   * 16-bit TIMER15
   */
  /* Temporary typedefs */
  TIM_TimeBaseInitTypeDef   TIM15_TimerInitCfg;

  /* Enable TIMER15 peripheral clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);
  
  /* Set timer period value */
  TIM15_TimerInitCfg.TIM_Period = 0x0FFF;
  /* INTCLOCK division set to 1 */
  TIM15_TimerInitCfg.TIM_ClockDivision = TIM_CKD_DIV1;
  /* Counter mode to up-count */
  TIM15_TimerInitCfg.TIM_CounterMode = TIM_CounterMode_Up;
  /* Set prescaler */
  TIM15_TimerInitCfg.TIM_Prescaler = MG_TIM15_PRESCALER;
  /* Repetition counter to 0 */
  TIM15_TimerInitCfg.TIM_RepetitionCounter = 0U;

  /* Use initialized structure for TIMER17 */
  TIM_TimeBaseInit(TIM15, &TIM15_TimerInitCfg);

  /* Turn off timer15 interrupt */
  TIM_ITConfig(TIM15, TIM_IT_Update, DISABLE);
  /* Set the event register to generate an event FLAG on counter reload */
  TIM_SelectOutputTrigger(TIM15,TIM_TRGOSource_Update);

  /* Enable TIMER15 */
  TIM_Cmd(TIM15, ENABLE);

  /* Calculate the conversion factor for micro seconds to timer value */
  mg_u32q12usTimer15ConvFact = U32Q12(F64_MICRO * mg_u32SysClock / (MG_TIM15_PRESCALER + 1));
  mg_u32HzTimer15Clk = mg_u32SysClock / (MG_TIM15_PRESCALER + 1);
}
#endif

#if MG_TIM16_ENA
static void mg_vTimer16HwInit(void)
{
  /*
   * 16-bit TIMER16
   */
}
#endif

#if MG_TIM17_ENA
static void mg_vTimer17HwInit(void)
{
  /*
   * 16-bit TIMER17
   * TIMER17 global initialization for time base usage
   */
  /* Temporary typedefs */
  TIM_TimeBaseInitTypeDef   TIM17_TimerInitCfg;

  /* Enable TIMER17 peripheral clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);
  
  /* Set timer period value */
  TIM17_TimerInitCfg.TIM_Period = 0x0FFF;
  /* INTCLOCK division set to 1 */
  TIM17_TimerInitCfg.TIM_ClockDivision = TIM_CKD_DIV1;
  /* Counter mode to up-count */
  TIM17_TimerInitCfg.TIM_CounterMode = TIM_CounterMode_Up;
  /* Set prescaler */
  TIM17_TimerInitCfg.TIM_Prescaler = MG_TIM17_PRESCALER;
  /* Repetition counter to 0 */
  TIM17_TimerInitCfg.TIM_RepetitionCounter = 0U;

  /* Use initialized structure for TIMER17 */
  TIM_TimeBaseInit(TIM17, &TIM17_TimerInitCfg);

  /* Turn on timer17 interrupt */
  TIM_ITConfig(TIM17, TIM_IT_Update, ENABLE);
  /* Set the event register to generate an event FLAG on counter reload */
  TIM_GenerateEvent(TIM17, TIM_EventSource_Update);

  /* Enable TIMER17 */
  TIM_Cmd(TIM17, ENABLE);

  /* Calculate the conversion factor for micro seconds to timer value */
  mg_u32q12usTimer17ConvFact = U32Q12(F64_MICRO * mg_u32SysClock / (MG_TIM17_PRESCALER + 1));
  mg_u32HzTimer17Clk = mg_u32SysClock / (MG_TIM17_PRESCALER + 1);
}
#endif

/*
 * End of file
 */
