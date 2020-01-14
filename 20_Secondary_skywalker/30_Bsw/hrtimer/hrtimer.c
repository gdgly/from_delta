/** *****************************************************************************
 * \file    hrtimer.c
 * \brief   High resolution timer configurations
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
#define HRTIMER_EXPORT_H
  #include "hrtimer_api.h"
  #include "hrtimer_scb.h"
  #include "hrtimer_cfg.h"
  #include "hrtimer_scfg.h"
  #include "hrtimer_conf.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static uint32 mg_u32SysClockSrc;
static uint32 mg_u32SysClock;
static uint64 mg_u64HresTimClock;
static uint32 mg_u64HresTimDtClock;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void HRTIMER_vGetSysClk(void);
static void HRTIMER_vHrTimerCommonInit(void);
static void HRTIMER_vHrTimerMasterHwInit(void);
static void HRTIMER_vHrTimerAHwInit(void);
static void HRTIMER_vHrTimerBHwInit(void);
static void HRTIMER_vHrTimerCHwInit(void);
static void HRTIMER_vHrTimerDHwInit(void);
static void HRTIMER_vHrTimerEHwInit(void);

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
void HRTIMER_vInit(void)
{
  /* Setup common high resoltion timer init */
  HRTIMER_vHrTimerCommonInit();
  /* Get the system clock. NOTE: Necessary for the time to timer factor determination */
  HRTIMER_vGetSysClk();
  /* Init high resolution master timer */
  HRTIMER_vMasterTimerInit();
  /* Initialize the PWM's for primary drive and SR */
  HRTIMER_vPrimDrvTimerInit();
  HRTIMER_vSrDrvTimerInit();
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
void HRTIMER_vDeInit(void)
{
  /* Disable drive */
  MG_REG_PWM_A_OFF;
  MG_REG_PWM_B_OFF;
  MG_REG_PWM_C_OFF;
  MG_REG_PWM_D_OFF;
  MG_REG_PWM_E_OFF;
  /* Deinit HRTIMER1 */
  HRTIM_DeInit(HRTIM1);
}

/** *****************************************************************************
 * \brief         Start the high resolution timers synchronized
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vSyncStartHrTimer(void)
{
  /* Start and syncronize CPU timers */
  HRTIM_WaveformCounterStart(HRTIM1, HRTIM_TIMERID_MASTER | HRTIM_TIMERID_TIMER_A | HRTIM_TIMERID_TIMER_B | HRTIM_TIMERID_TIMER_C | HRTIM_TIMERID_TIMER_D| HRTIM_TIMERID_TIMER_E);
}

/** *****************************************************************************
 * \brief         Set high resolution timer period
 *
 * \param[in]     u8TimerId: 0 - 5; HrTimerPeriod: period in ns
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vHrTimerSetPeriod(uint8 u8TimerId, uint32 u32nsHrTimerPeriod)
{
  switch (u8TimerId)
  {
    case MG_HRTIM_MST:
    {
      /* HRTIMER MASTER */
      MG_REG_HRTIMER1_MST_PERIOD = (uint16)((mg_u32q12nsTimerMstConvFact * u32nsHrTimerPeriod) >> 12);
      break;
    }
    case MG_HRTIM_A:
    {
      /* HRTIMER A */
      MG_REG_HRTIMER1_A_PERIOD = (uint16)((mg_u32q12nsTimerAConvFact * u32nsHrTimerPeriod) >> 12);
      break;
    }
    case MG_HRTIM_B:
    {
      /* HRTIMER B */
      MG_REG_HRTIMER1_B_PERIOD = (uint16)((mg_u32q12nsTimerBConvFact * u32nsHrTimerPeriod) >> 12);
      break;
    }
    case MG_HRTIM_C:
    {
      /* HRTIMER C */
      MG_REG_HRTIMER1_C_PERIOD = (uint16)((mg_u32q12nsTimerCConvFact * u32nsHrTimerPeriod) >> 12);
      break;
    }
    case MG_HRTIM_D:
    {
      /* HRTIMER D */
      MG_REG_HRTIMER1_D_PERIOD = (uint16)((mg_u32q12nsTimerDConvFact * u32nsHrTimerPeriod) >> 12);
      break;
    }
    case MG_HRTIM_E:
    {
      /* HRTIMER E */
      MG_REG_HRTIMER1_E_PERIOD = (uint16)((mg_u32q12nsTimerEConvFact * u32nsHrTimerPeriod) >> 12);
      break;
    }
  }
}

/** *****************************************************************************
 * \brief         Enable PWM drive
 *
 * \param[in]     u8TimerId: 0 - 5 (MASTER TIMER - TIMER E); Status: Enable or disable
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vHrTimerDrvEnable(uint8 u8TimerId, uint8 u8Status)
{
  switch (u8TimerId)
  {
    /* HRTIMER A */
    case MG_HRTIM_A:
    {
      /* Enable drive */
      if (u8Status == SET)
      {
        MG_REG_PWM_A_ON;
      }
      /* Disable drive */
      else
      {
        MG_REG_PWM_A_OFF;
      }
      break;
    }
    /* HRTIMER B */
    case MG_HRTIM_B:
    {
      /* Enable drive */
      if (u8Status == SET)
      {
        MG_REG_PWM_B_ON;
      }
      /* Disable drive */
      else
      {
        MG_REG_PWM_B_OFF;
      }
      break;
    }
    /* HRTIMER C */
    case MG_HRTIM_C:
    {
      /* Enable drive */
      if (u8Status == SET)
      {
        MG_REG_PWM_C_ON;
      }
      /* Disable drive */
      else
      {
        MG_REG_PWM_C_OFF;
      }
      break;
    }
    /* HRTIMER D */
    case MG_HRTIM_D:
    {
      /* Enable drive */
      if (u8Status == SET)
      {
        MG_REG_PWM_D_ON;
      }
      /* Disable drive */
      else
      {
        MG_REG_PWM_D_OFF;
      }
      break;
    }
    /* HRTIMER E */
    case MG_HRTIM_E:
    {
      /* Enable drive */
      if (u8Status == SET)
      {
        MG_REG_PWM_E_ON;
      }
      /* Disable drive */
      else
      {
        MG_REG_PWM_E_OFF;
      }
      break;
    }
  }
}

/** *****************************************************************************
 * \brief         Initialize master timer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vMasterTimerInit(void)
{
  /* Init high resolution master timer */
  HRTIMER_vHrTimerMasterHwInit();
}

/** *****************************************************************************
 * \brief         Initialize primary side MOSFET drive timer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vPrimDrvTimerInit(void)
{
  /* Init high resolution timer A */
  HRTIMER_vHrTimerAHwInit();
}

/** *****************************************************************************
 * \brief         Initialize SR drive timer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vSrDrvTimerInit(void)
{
  /* Init high resolution timer B */
  HRTIMER_vHrTimerBHwInit();
}

/** *****************************************************************************
 * \brief         Initialize general purpose timer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vGp2TimerInit(void)
{
  /* Init high resolution timer C */
  HRTIMER_vHrTimerCHwInit();
}

/** *****************************************************************************
 * \brief         Initialize active current share timer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vIshareTimerInit(void)
{
  /* Init high resolution timer D */
  HRTIMER_vHrTimerDHwInit();
}

/** *****************************************************************************
 * \brief         Initialize general purpose timer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vGpTimerInit(void)
{
  /* Init high resolution timer E */
  HRTIMER_vHrTimerEHwInit();
}

/** *****************************************************************************
 * \brief         HRTIMER NVIC configuration
 *
 * \param[in]     HrTimChId: can be 0 to 5. PrePriority: can be 1 to 7. SubPriority: can be 1 to 7
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HRTIMER_vHrTimerIsrNvicCfg(uint8 u8HrTimChId, uint8 u8PrePriority, uint8 u8SubPriority)
{
  static uint8 u8IrqCh = 0;

  /* DMA Channel 1 */
  if (u8HrTimChId == MG_HRTIM_MST)
  {
    u8IrqCh = HRTIM1_Master_IRQn;
  }
  /* DMA Channel 2 */
  if (u8HrTimChId == MG_HRTIM_A)
  {
    u8IrqCh = HRTIM1_TIMA_IRQn;
  }
  /* DMA Channel 3 */
  if (u8HrTimChId == MG_HRTIM_B)
  {
    u8IrqCh = HRTIM1_TIMB_IRQn;
  }
  /* DMA Channel 4 */
  if (u8HrTimChId == MG_HRTIM_C)
  {
    u8IrqCh = HRTIM1_TIMC_IRQn;
  }
  /* DMA Channel 5 */
  if (u8HrTimChId == MG_HRTIM_D)
  {
    u8IrqCh = HRTIM1_TIMD_IRQn;
  }
  /* DMA Channel 6 */
  if (u8HrTimChId == MG_HRTIM_E)
  {
    u8IrqCh = HRTIM1_TIME_IRQn;
  }

  /* Temporary typedefs */
  NVIC_InitTypeDef      NVIC_InitCfg;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  /* Configure NVIC to enable HRTIMER interrupt */
  NVIC_InitCfg.NVIC_IRQChannel = u8IrqCh;
  NVIC_InitCfg.NVIC_IRQChannelPreemptionPriority = u8PrePriority;
  NVIC_InitCfg.NVIC_IRQChannelSubPriority = u8SubPriority;
  NVIC_InitCfg.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitCfg);
}

/*******************************************************************************
 * Local functions (privat for module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initialize the high resolution common setup
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void HRTIMER_vHrTimerCommonInit(void)
{
  /***********************************************
   * High Resolution Timer
   * HRTIM global initialization: Clock, DLL init
   **********************************************/
  /* Use the PLLx2 clock for HRTIM */
  RCC_HRTIM1CLKConfig(RCC_HRTIM1CLK_PLLCLK);
  /* Enable HRTIM peripheral clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_HRTIM1, ENABLE);

  /* HRTIM DLL calibration: periodic calibration, set period to 14us */
  HRTIM_DLLCalibrationStart(HRTIM1, HRTIM_CALIBRATIONRATE_14);
  /* Wait calibration completion */
  while(HRTIM_GetCommonFlagStatus(HRTIM1, HRTIM_ISR_DLLRDY) == RESET);
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
static void HRTIMER_vGetSysClk(void)
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

  /* Get the high resolution clock */
  mg_u64HresTimClock = (uint64)mg_u32SysClock * MG_U8_HRTIM_MST_CLK_PRESCALER;
  /* Calculate the conversion factor for nano seconds to timer value */
  mg_u32q12nsTimerMstConvFact = U32Q12(F64_NANO * mg_u64HresTimClock);

  /* Get the high resolution clock */
  mg_u64HresTimClock = (uint64)mg_u32SysClock * MG_U8_HRTIM_A_CLK_PRESCALER;
  /* Calculate the conversion factor for nano seconds to timer value */
  mg_u32q12nsTimerAConvFact = U32Q12(F64_NANO * mg_u64HresTimClock);
  /* Get the dead time resolution clock */
  mg_u64HresTimDtClock = (uint64)mg_u32SysClock * MG_U16_HRTIM_A_DT_PRESCALER;
  /* Calculate the conversion factor for nano seconds to dead time value */
  mg_u32q12nsTimerADtConvFact = U32Q12(F64_NANO * mg_u64HresTimDtClock);

  /* Get the high resolution clock */
  mg_u64HresTimClock = (uint64)mg_u32SysClock * MG_U8_HRTIM_B_CLK_PRESCALER;
  /* Calculate the conversion factor for nano seconds to timer value */
  mg_u32q12nsTimerBConvFact = U32Q12(F64_NANO * mg_u64HresTimClock);
  /* Get the dead time resolution clock */
  mg_u64HresTimDtClock = (uint64)mg_u32SysClock * MG_U16_HRTIM_B_DT_PRESCALER;
  /* Calculate the conversion factor for nano seconds to dead time value */
  mg_u32q12nsTimerBDtConvFact = U32Q12(F64_NANO * mg_u64HresTimDtClock);

  /* Get the high resolution clock */
  mg_u64HresTimClock = (uint64)mg_u32SysClock * MG_U8_HRTIM_C_CLK_PRESCALER;
  /* Calculate the conversion factor for nano seconds to timer value */
  mg_u32q12nsTimerCConvFact = U32Q12(F64_NANO * mg_u64HresTimClock);
  /* Get the dead time resolution clock */
  mg_u64HresTimDtClock = (uint64)mg_u32SysClock * MG_U16_HRTIM_C_DT_PRESCALER;
  /* Calculate the conversion factor for nano seconds to dead time value */
  mg_u32q12nsTimerCDtConvFact = U32Q12(F64_NANO * mg_u64HresTimDtClock);

  /* Get the high resolution clock */
  mg_u64HresTimClock = (uint64)mg_u32SysClock * MG_U8_HRTIM_D_CLK_PRESCALER;
  /* Calculate the conversion factor for nano seconds to timer value */
  mg_u32q12nsTimerDConvFact = U32Q12(F64_NANO * mg_u64HresTimClock);
  /* Get the dead time resolution clock */
  mg_u64HresTimDtClock = (uint64)mg_u32SysClock * MG_U16_HRTIM_D_DT_PRESCALER;
  /* Calculate the conversion factor for nano seconds to dead time value */
  mg_u32q12nsTimerDDtConvFact = U32Q12(F64_NANO * mg_u64HresTimDtClock);

  /* Get the high resolution clock */
  mg_u64HresTimClock = (uint64)mg_u32SysClock * MG_U8_HRTIM_E_CLK_PRESCALER;
  /* Calculate the conversion factor for nano seconds to timer value */
  mg_u32q12nsTimerEConvFact = U32Q12(F64_NANO * mg_u64HresTimClock);
  /* Get the dead time resolution clock */
  mg_u64HresTimDtClock = (uint64)mg_u32SysClock * MG_U16_HRTIM_E_DT_PRESCALER;
  /* Calculate the conversion factor for nano seconds to dead time value */
  mg_u32q12nsTimerEDtConvFact = U32Q12(F64_NANO * mg_u64HresTimDtClock);
}

/** *****************************************************************************
 * \brief         Initialize and configure high resolution master timer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void HRTIMER_vHrTimerMasterHwInit(void)
{
  /* Temporary typedefs */
  HRTIM_BaseInitTypeDef               HRTIM_BaseInitCfg;
  HRTIM_TimerInitTypeDef              HRTIM_TimerInitCfg;

  /***********************************************
   * MASTER TIMER
   **********************************************/
  /* PWM period initialized to base value */
  HRTIM_BaseInitCfg.Period = 0x1FFE;
  /* Repetition counter */
  HRTIM_BaseInitCfg.RepetitionCounter = 0;
  /* Set prescaler to x16 (x32 will casue overflow) */
  HRTIM_BaseInitCfg.PrescalerRatio = HRTIM_MST_PRESCALERRATIO;
  /* Set mode to continous */
  HRTIM_BaseInitCfg.Mode = HRTIM_MODE_CONTINOUS;
  /* Halfmode enable */
  HRTIM_TimerInitCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  /* Start, reset on sync and DAC sync disabled */
  HRTIM_TimerInitCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  HRTIM_TimerInitCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  HRTIM_TimerInitCfg.DACSynchro = HRTIM_DACSYNC_NONE;
  /* Set HRTIM to independent updategating */
  HRTIM_TimerInitCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  /* Burst mode maintained from clock */
  HRTIM_TimerInitCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  /* Update on repetition disabled */
  HRTIM_TimerInitCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
  /* Preload enable (shadow register mode) */
  HRTIM_TimerInitCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;

  /* Use initialized structure for HRTIM waveform generation */
  HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_MASTER, &HRTIM_BaseInitCfg, &HRTIM_TimerInitCfg);

  /***********************************************
   * Configure ADC trigger
   **********************************************/
   #if 0
  HRTIM_ADCTriggerCfgTypeDef          HRTIM_ADCTriggerCfg;
  /* Configure master HRTIM ADC trigger to trigger regular conversion */
  HRTIM_ADCTriggerCfg.Trigger = HRTIM_ADCTRIGGEREVENT13_MASTER_PERIOD;
  /* Update trigger source from preload register synchronized to master HRTIMER */
  HRTIM_ADCTriggerCfg.UpdateSource = HRTIM_ADCTRIGGERUPDATE_MASTER;
  /* Use initialized structure for ADC triggering */
  HRTIM_ADCTriggerConfig(HRTIM1, HRTIM_ADCTRIGGER_1, &HRTIM_ADCTriggerCfg);
  #endif
  
  /* Update configuration from preload register to Master Timer register */
  HRTIM1->HRTIM_COMMON.CR2 |= (MG_HRTIMER1_MASTER_UPDATE);
}

/** *****************************************************************************
 * \brief         Initialize and configure high resolution timer A
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void HRTIMER_vHrTimerAHwInit(void)
{
  /* Temporary typedefs */
  HRTIM_BaseInitTypeDef               HRTIM_BaseInitCfg;
  HRTIM_TimerInitTypeDef              HRTIM_TimerInitCfg;
  HRTIM_OutputCfgTypeDef              HRTIM_TIM_OutputCfg;
  HRTIM_CompareCfgTypeDef             HRTIM_CompareCfg;
  HRTIM_TimerCfgTypeDef               HRTIM_TimerCfg;
  HRTIM_EventCfgTypeDef               HRTIM_EventCfg;
  HRTIM_DeadTimeCfgTypeDef            HRTIM_DeadTimeCfg;

  /***********************************************
   * HRTIMER1A
   **********************************************/
  /* PWM period initialized to base value */
  HRTIM_BaseInitCfg.Period = 0x0FFF;
  /* Repetition counter */
  HRTIM_BaseInitCfg.RepetitionCounter = 0;
  /* Set prescaler to x16 (x32 will casue overflow) */
  HRTIM_BaseInitCfg.PrescalerRatio = HRTIM_A_PRESCALERRATIO;
  /* Set mode to continous */
  HRTIM_BaseInitCfg.Mode = HRTIM_MODE_CONTINOUS;

  /* Halfmode disable */
  HRTIM_TimerInitCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  /* Start, reset on sync and DAC sync disabled */
  HRTIM_TimerInitCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  HRTIM_TimerInitCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  HRTIM_TimerInitCfg.DACSynchro = HRTIM_DACSYNC_NONE;
  /* Set HRTIM to independent updategating */
  HRTIM_TimerInitCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  /* Burst mode maintained from clock */
  HRTIM_TimerInitCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  /* Update on repetition disabled */
  HRTIM_TimerInitCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
  /* Preload enable (shadow register mode) */
  HRTIM_TimerInitCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;

  /* Use initialized structure for HRTIM waveform generation */
  HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, &HRTIM_BaseInitCfg, &HRTIM_TimerInitCfg);

  /* Do nothing in idle mode and set output to inactive in idle and fault state (used only for ST burst mode) */
  HRTIM_TIM_OutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  HRTIM_TIM_OutputCfg.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;
  HRTIM_TIM_OutputCfg.FaultState = HRTIM_OUTPUTFAULTSTATE_INACTIVE;
  /* Disable chopper mode */
  HRTIM_TIM_OutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  /* No delay when entering burst mode */
  HRTIM_TIM_OutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Set output high at timer compare 1 */
  HRTIM_TIM_OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
  /* Set output low at timer compare 2 */
  HRTIM_TIM_OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP2 | HRTIM_OUTPUTRESET_TIMCMP3 | HRTIM_OUTPUTRESET_TIMPER | HRTIM_OUTPUTRESET_RESYNC;
  /* Use initialized structure as output configuration for output TA1 */
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1, &HRTIM_TIM_OutputCfg);

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Set output high at timer compare 3 */
  HRTIM_TIM_OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP3;
  /* Set output low at timer compare 4 */
  HRTIM_TIM_OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP4 | HRTIM_OUTPUTRESET_TIMCMP1 | HRTIM_OUTPUTRESET_TIMPER | HRTIM_OUTPUTRESET_RESYNC;
  /* Use initialized structure as output configuration for output TA2 */
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA2, &HRTIM_TIM_OutputCfg);

  /* Auto-delay disabled */
  HRTIM_CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  HRTIM_CompareCfg.AutoDelayedTimeout = 0;

  /*
   * Compare values:
   * NOTE: There are hardware limitations of the HRTIMER (Datasheet: 20.3.4 Timer A..E timing units table 78)
   * Minimum value must be greater than or equal to 3 periods of the fHRTIM clock
   * Maximum value must be less than or equal to 0xFFFF - 1 periods of the fHRTIM clock
   * If these conditions are violated, the related compares will be ignored!
   */
  /* PWM compare value 1 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWMA (TIMER1A) */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, &HRTIM_CompareCfg);
  /* PWM compare value 2 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWMA (TIMER1A) */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_2, &HRTIM_CompareCfg);
  /* PWM compare value 3 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWMA (TIMER1A) */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_3, &HRTIM_CompareCfg);
  /* PWM compare value 4 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWMA (TIMER1A) */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_4, &HRTIM_CompareCfg);

  /* Push-pull enable */
  HRTIM_TimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
  /* Fault condition defines */
  HRTIM_TimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
  HRTIM_TimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
  /* Dead-time insertion enable */
  HRTIM_TimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
  /* Delayed protection mode enable (EEV 6,7 only at TIMER A,B,C; EEV 8,9 only at TIMER D,E) */
  HRTIM_TimerCfg.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DELAYEDBOTH_EEV68;
  /* No update trigger */
  HRTIM_TimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
  /* Reset timer at master period to ensure syncronization */
  HRTIM_TimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_MASTER_PER;
  /* Update timer registers on reset */
  HRTIM_TimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;

  /* Use initialized structure for PWMA (TIMER1A) */
  HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, &HRTIM_TimerCfg);

  /* Deadtime clock prescalor */
  HRTIM_DeadTimeCfg.Prescaler = MG_HRTIM_A_DTPRESCALERRATIO;
  /* Deadtime rising value, Bst Mosfet Deadtime */
  HRTIM_DeadTimeCfg.RisingValue = 60U;
  /* Deadtime rising sign */
  HRTIM_DeadTimeCfg.RisingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE;
  /* Deadtime rising value lock */
  HRTIM_DeadTimeCfg.RisingLock = HRTIM_TIMDEADTIME_RISINGLOCK_WRITE;
  /* Deadtime rising sign lock */
  HRTIM_DeadTimeCfg.RisingSignLock = HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE;
  /* Deadtime falling value, SR Deadtime*/
  HRTIM_DeadTimeCfg.FallingValue = 60U;
  /* Deadtime falling sign */
  HRTIM_DeadTimeCfg.FallingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE;
  /* Deadtime falling value lock */
  HRTIM_DeadTimeCfg.FallingLock = HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE;
  /* Deadtime falling sign lock*/
  HRTIM_DeadTimeCfg.FallingSignLock = HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE;

  /* Use initialized structure for PWMA (TIMER1A CH1 & CH2) Deadtime */
  HRTIM_DeadTimeConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, &HRTIM_DeadTimeCfg);
  /* Make sure that the DT sign locks are written */
  HRTIM1->HRTIM_TIMERx[HRTIM_TIMERINDEX_TIMER_A].DTxR |= (HRTIM_DTR_DTRSLK | HRTIM_DTR_DTFSLK);

  /*
   * Configure external events to reset PWM
   * When using FAST MODE with blanking. Several limitation are applicable
   * - Only level sensitivity is available
   * - No latching, event postponement & windowing timeout feature are supported
   */
  HRTIM_EventCfg.Source = HRTIM_EVENTSRC_2;     /* Select comparators as event source */
  HRTIM_EventCfg.Polarity = HRTIM_EVENTPOLARITY_HIGH;
  HRTIM_EventCfg.Sensitivity = HRTIM_EVENTSENSITIVITY_LEVEL;
  HRTIM_EventCfg.Filter = HRTIM_EVENTFILTER_NONE;
  HRTIM_EventCfg.FastMode = HRTIM_EVENTFASTMODE_ENABLE;
  /* Use initialized structure for HRTIM1 */
  HRTIM_EventConfig(HRTIM1, HRTIM_EVENT_6, &HRTIM_EventCfg);  /* Select COMP2 output */

  /* Disable TA1 and TA2 outputs to keep rails off */
  HRTIM1->HRTIM_COMMON.DISR = (HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2);

  /* Update configuration from preload register to TimerA register */
  HRTIM1->HRTIM_COMMON.CR2 |= (MG_HRTIMER1_A_UPDATE);
}

/** *****************************************************************************
 * \brief         Initialize and configure high resolution timer for PWM's
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void HRTIMER_vHrTimerBHwInit(void)
{
  /* Temporary typedefs */
  HRTIM_BaseInitTypeDef               HRTIM_BaseInitCfg;
  HRTIM_TimerInitTypeDef              HRTIM_TimerInitCfg;
  HRTIM_OutputCfgTypeDef              HRTIM_TIM_OutputCfg;
  HRTIM_CompareCfgTypeDef             HRTIM_CompareCfg;
  HRTIM_TimerCfgTypeDef               HRTIM_TimerCfg;
  HRTIM_EventCfgTypeDef               HRTIM_EventCfg;
  HRTIM_DeadTimeCfgTypeDef            HRTIM_DeadTimeCfg;

  /***********************************************
   * HRTIMER1B
   **********************************************/
  /* PWM period initialized to base value */
  HRTIM_BaseInitCfg.Period = 0x0FFF;
  /* Repetition counter */
  HRTIM_BaseInitCfg.RepetitionCounter = 0;
  /* Set prescaler to x16 (x32 will cause overflow) */
  HRTIM_BaseInitCfg.PrescalerRatio = HRTIM_B_PRESCALERRATIO;
  /* Set mode to continous */
  HRTIM_BaseInitCfg.Mode = HRTIM_MODE_CONTINOUS;

  /* Halfmode disable */
  HRTIM_TimerInitCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  /* Start, reset on sync and DAC sync disabled */
  HRTIM_TimerInitCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  HRTIM_TimerInitCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  HRTIM_TimerInitCfg.DACSynchro = HRTIM_DACSYNC_NONE;
  /* Set HRTIM to independent updategating */
  HRTIM_TimerInitCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  /* Burst mode maintained from clock */
  HRTIM_TimerInitCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  /* Update on repetition disabled */
  HRTIM_TimerInitCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
  /* Preload enable (shadow register mode) */
  HRTIM_TimerInitCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;

  /* Use initialized structure for HRTIM waveform generation */
  HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, &HRTIM_BaseInitCfg, &HRTIM_TimerInitCfg);

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Do nothing in idle mode and set output to inactive in idle and fault state */
  HRTIM_TIM_OutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  HRTIM_TIM_OutputCfg.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;
  HRTIM_TIM_OutputCfg.FaultState = HRTIM_OUTPUTFAULTSTATE_INACTIVE;
  /* Disable chopper mode */
  HRTIM_TIM_OutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  /* No delay when entering burst mode */
  HRTIM_TIM_OutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Set output high at timer compare 1 */
  HRTIM_TIM_OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
  /* Set output low at timer compare 2 */
  HRTIM_TIM_OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP2 | HRTIM_OUTPUTRESET_TIMCMP3 | HRTIM_OUTPUTRESET_TIMPER | HRTIM_OUTPUTRESET_RESYNC;
  /* Use initialized structure as output configuration for output TB1 */
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB1, &HRTIM_TIM_OutputCfg);

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Set output high at timer compare 3 */
  HRTIM_TIM_OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP3;
  /* Set output low at timer compare 4 */
  HRTIM_TIM_OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP4 | HRTIM_OUTPUTRESET_TIMCMP1 | HRTIM_OUTPUTRESET_TIMPER | HRTIM_OUTPUTRESET_RESYNC;
  /* Use initialized structure as output configuration for output TB2 */
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB2, &HRTIM_TIM_OutputCfg);

  /* Auto-delay disabled */
  HRTIM_CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  HRTIM_CompareCfg.AutoDelayedTimeout = 0;
  /*
   * Compare values:
   * NOTE: There are hardware limitations of the HRTIMER (Datasheet: 20.3.4 Timer A..E timing units table 78)
   * Minimum value must be greater than or equal to 3 periods of the fHRTIM clock
   * Maximum value must be less than or equal to 0xFFFF - 1 periods of the fHRTIM clock
   * If these conditions are violated, the related compares will be ignored!
   */
  /* PWM compare value 1 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWM */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_1, &HRTIM_CompareCfg);
  /* PWM compare value 2 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWM */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_2, &HRTIM_CompareCfg);
  /* PWM compare value 3 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWM */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_3, &HRTIM_CompareCfg);
  /* PWM compare value 4 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWM */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_4, &HRTIM_CompareCfg);

  /* Push-pull disable */
  HRTIM_TimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
  /* Fault condition defines */
  HRTIM_TimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
  HRTIM_TimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
  /* Dead-time insertion disable */
  HRTIM_TimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
  /* Delayed protection mode enable (EEV 6,7 only at TIMER A,B,C; EEV 8,9 only at TIMER D,E) */
  HRTIM_TimerCfg.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DELAYEDBOTH_EEV68;
  /* No update trigger */
  HRTIM_TimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
  /* Timer counter reset trigger off */
  HRTIM_TimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_MASTER_PER;
  /* Update timer registers on reset */
  HRTIM_TimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;

  /* Use initialized structure for PWM */
  HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, &HRTIM_TimerCfg);

  /* Deadtime clock prescalor */
  HRTIM_DeadTimeCfg.Prescaler = MG_HRTIM_B_DTPRESCALERRATIO;
  /* Deadtime rising value */
  HRTIM_DeadTimeCfg.RisingValue = 130U;
  /* Deadtime rising sign */
  HRTIM_DeadTimeCfg.RisingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE;
  /* Deadtime rising value lock */
  HRTIM_DeadTimeCfg.RisingLock = HRTIM_TIMDEADTIME_RISINGLOCK_WRITE;
  /* Deadtime rising sign lock */
  HRTIM_DeadTimeCfg.RisingSignLock = HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE;
  /* Deadtime falling value */
  HRTIM_DeadTimeCfg.FallingValue = 130U;
  /* Deadtime falling sign */
  HRTIM_DeadTimeCfg.FallingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE;
  /* Deadtime falling value lock */
  HRTIM_DeadTimeCfg.FallingLock = HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE;
  /* Deadtime falling sign lock*/
  HRTIM_DeadTimeCfg.FallingSignLock = HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE;

  /* Use initialized structure for PWM (CH1 & CH2) Deadtime */
  HRTIM_DeadTimeConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_B, &HRTIM_DeadTimeCfg);
  /* Make sure that the DT sign locks are written */
  HRTIM1->HRTIM_TIMERx[HRTIM_TIMERINDEX_TIMER_B].DTxR |= (HRTIM_DTR_DTRSLK | HRTIM_DTR_DTFSLK);

  /*
   * Configure external events to reset PWM
   * When using FAST MODE with blanking. Several limitation are applicable
   * - Only level sensitivity is available
   * - No latching, event postponement & windowing timeout feature are supported
   */
  HRTIM_EventCfg.Source = HRTIM_EVENTSRC_2;     /* Select comparators as event source */
  HRTIM_EventCfg.Polarity = HRTIM_EVENTPOLARITY_HIGH;
  HRTIM_EventCfg.Sensitivity = HRTIM_EVENTSENSITIVITY_LEVEL;
  HRTIM_EventCfg.Filter = HRTIM_EVENTFILTER_NONE;
  HRTIM_EventCfg.FastMode = HRTIM_EVENTFASTMODE_ENABLE;
  /* Use initialized structure for HRTIM1 */
  HRTIM_EventConfig(HRTIM1, HRTIM_EVENT_6, &HRTIM_EventCfg);  /* Select COMP2 output */

  /* Disable TB1 and TB2 outputs to keep rails off */
  HRTIM1->HRTIM_COMMON.DISR = (HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TB2);

  /* Update configuration from preload register to Timer register */
  HRTIM1->HRTIM_COMMON.CR2 |= (MG_HRTIMER1_B_UPDATE);
}

/** *****************************************************************************
 * \brief         Initialize and configure high resolution timer for PWM's
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void HRTIMER_vHrTimerCHwInit(void)
{
  /* Temporary typedefs */
  HRTIM_BaseInitTypeDef               HRTIM_BaseInitCfg;
  HRTIM_TimerInitTypeDef              HRTIM_TimerInitCfg;
  HRTIM_OutputCfgTypeDef              HRTIM_TIM_OutputCfg;
  HRTIM_CompareCfgTypeDef             HRTIM_CompareCfg;
  HRTIM_TimerCfgTypeDef               HRTIM_TimerCfg;
  HRTIM_DeadTimeCfgTypeDef            HRTIM_DeadTimeCfg;

  /***********************************************
   * HRTIMER1C
   **********************************************/
  /* PWM period initialized to base value */
  HRTIM_BaseInitCfg.Period = 0x0FFF;
  /* Repetition counter */
  HRTIM_BaseInitCfg.RepetitionCounter = 0;
  /* Set prescaler to x16 (x32 will cause overflow) */
  HRTIM_BaseInitCfg.PrescalerRatio = HRTIM_C_PRESCALERRATIO;
  /* Set mode to continous */
  HRTIM_BaseInitCfg.Mode = HRTIM_MODE_CONTINOUS;

  /* Halfmode disable */
  HRTIM_TimerInitCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  /* Start, reset on sync and DAC sync disabled */
  HRTIM_TimerInitCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  HRTIM_TimerInitCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  HRTIM_TimerInitCfg.DACSynchro = HRTIM_DACSYNC_NONE;
  /* Set HRTIM to independent updategating */
  HRTIM_TimerInitCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  /* Burst mode maintained from clock */
  HRTIM_TimerInitCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  /* Update on repetition disabled */
  HRTIM_TimerInitCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
  /* Preload enable (shadow register mode) */
  HRTIM_TimerInitCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;

  /* Use initialized structure for HRTIM waveform generation */
  HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, &HRTIM_BaseInitCfg, &HRTIM_TimerInitCfg);

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Do nothing in idle mode and set output to inactive in idle and fault state */
  HRTIM_TIM_OutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  HRTIM_TIM_OutputCfg.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;
  HRTIM_TIM_OutputCfg.FaultState = HRTIM_OUTPUTFAULTSTATE_INACTIVE;
  /* Disable chopper mode */
  HRTIM_TIM_OutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  /* No delay when entering burst mode */
  HRTIM_TIM_OutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Set output high at timer compare 1 */
  HRTIM_TIM_OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
  /* Set output low at timer compare 2 */
  HRTIM_TIM_OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP2 | HRTIM_OUTPUTRESET_TIMPER;
  /* Use initialized structure as output configuration for output TC1 */
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC1, &HRTIM_TIM_OutputCfg);

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Set output high at timer compare 3 */
  HRTIM_TIM_OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
  /* Set output low at timer compare 4 */
  HRTIM_TIM_OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP2 | HRTIM_OUTPUTRESET_TIMPER;
  /* Use initialized structure as output configuration for output TC2 */
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC2, &HRTIM_TIM_OutputCfg);

  /* Auto-delay disabled */
  HRTIM_CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  HRTIM_CompareCfg.AutoDelayedTimeout = 0;
  /*
   * Compare values:
   * NOTE: There are hardware limitations of the HRTIMER (Datasheet: 20.3.4 Timer A..E timing units table 78)
   * Minimum value must be greater than or equal to 3 periods of the fHRTIM clock
   * Maximum value must be less than or equal to 0xFFFF - 1 periods of the fHRTIM clock
   * If these conditions are violated, the related compares will be ignored!
   */
  /* PWM compare value 1 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWMC (TIMER1C) */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_1, &HRTIM_CompareCfg);
  /* PWM compare value 2 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWMC (TIMER1C) */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_2, &HRTIM_CompareCfg);
  /* PWM compare value 3 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWMC (TIMER1C) */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_3, &HRTIM_CompareCfg);
  /* PWM compare value 4 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWMC (TIMER1C) */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_4, &HRTIM_CompareCfg);

  /* Push-pull disable */
  HRTIM_TimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
  /* Fault condition defines */
  HRTIM_TimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
  HRTIM_TimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
  /* Dead-time insertion disable */
  HRTIM_TimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
  /* Delayed protection mode enable (EEV 6,7 only at TIMER A,B,C; EEV 8,9 only at TIMER D,E) */
  HRTIM_TimerCfg.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DISABLED;
  /* No update trigger */
  HRTIM_TimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
  /* Timer counter reset trigger off */
  HRTIM_TimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
  /* Update timer registers on reset */
  HRTIM_TimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;

  /* Use initialized structure for PWMD (TIMER1C) */
  HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, &HRTIM_TimerCfg);

  /* Deadtime clock prescalor */
  HRTIM_DeadTimeCfg.Prescaler = MG_HRTIM_C_DTPRESCALERRATIO;
  /* Deadtime rising value, Bst Mosfet Deadtime */
  HRTIM_DeadTimeCfg.RisingValue = 130U;
  /* Deadtime rising sign */
  HRTIM_DeadTimeCfg.RisingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE;
  /* Deadtime rising value lock */
  HRTIM_DeadTimeCfg.RisingLock = HRTIM_TIMDEADTIME_RISINGLOCK_WRITE;
  /* Deadtime rising sign lock */
  HRTIM_DeadTimeCfg.RisingSignLock = HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE;
  /* Deadtime falling value, SR Deadtime*/
  HRTIM_DeadTimeCfg.FallingValue = 130U;
  /* Deadtime falling sign */
  HRTIM_DeadTimeCfg.FallingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE;
  /* Deadtime falling value lock */
  HRTIM_DeadTimeCfg.FallingLock = HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE;
  /* Deadtime falling sign lock*/
  HRTIM_DeadTimeCfg.FallingSignLock = HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE;

  /* Use initialized structure for PWMA (TIMER1A CH1 & CH2) Deadtime */
  HRTIM_DeadTimeConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_C, &HRTIM_DeadTimeCfg);
  /* Make sure that the DT sign locks are written */
  HRTIM1->HRTIM_TIMERx[HRTIM_TIMERINDEX_TIMER_C].DTxR |= (HRTIM_DTR_DTRSLK | HRTIM_DTR_DTFSLK);

  /*
   * Configure external events to reset PWM
   * When using FAST MODE with blanking. Several limitation are applicable
   * - Only level sensitivity is available
   * - No latching, event postponement & windowing timeout feature are supported
   */

  /* Disable TC1 and TC2 outputs to keep rails off */
  HRTIM1->HRTIM_COMMON.DISR = (HRTIM_OUTPUT_TC1 | HRTIM_OUTPUT_TC2);

  /* Update configuration from preload register to TimerC register */
  HRTIM1->HRTIM_COMMON.CR2 |= (MG_HRTIMER1_C_UPDATE);
}

/** *****************************************************************************
 * \brief         Initialize and configure high resolution timer for PWM's
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void HRTIMER_vHrTimerDHwInit(void)
{
  /* Temporary typedefs */
  HRTIM_BaseInitTypeDef               HRTIM_BaseInitCfg;
  HRTIM_TimerInitTypeDef              HRTIM_TimerInitCfg;
  HRTIM_OutputCfgTypeDef              HRTIM_TIM_OutputCfg;
  HRTIM_CompareCfgTypeDef             HRTIM_CompareCfg;
  HRTIM_TimerCfgTypeDef               HRTIM_TimerCfg;

  /***********************************************
   * HRTIMER1D
   **********************************************/
  /* PWM period initialized to base value */
  HRTIM_BaseInitCfg.Period = 0x0FFF;
  /* Repetition counter */
  HRTIM_BaseInitCfg.RepetitionCounter = 0;
  /* Set prescaler to x16 (x32 will cause overflow) */
  HRTIM_BaseInitCfg.PrescalerRatio = HRTIM_D_PRESCALERRATIO;
  /* Set mode to continous */
  HRTIM_BaseInitCfg.Mode = HRTIM_MODE_CONTINOUS;

  /* Halfmode disable */
  HRTIM_TimerInitCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  /* Start, reset on sync and DAC sync disabled */
  HRTIM_TimerInitCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  HRTIM_TimerInitCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  HRTIM_TimerInitCfg.DACSynchro = HRTIM_DACSYNC_NONE;
  /* Set HRTIM to independent updategating */
  HRTIM_TimerInitCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  /* Burst mode maintained from clock */
  HRTIM_TimerInitCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  /* Update on repetition disabled */
  HRTIM_TimerInitCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
  /* Preload enable (shadow register mode) */
  HRTIM_TimerInitCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;

  /* Use initialized structure for HRTIM waveform generation */
  HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, &HRTIM_BaseInitCfg, &HRTIM_TimerInitCfg);

  /* Do nothing in idle mode and set output to inactive in idle and fault state */
  HRTIM_TIM_OutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  HRTIM_TIM_OutputCfg.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;
  HRTIM_TIM_OutputCfg.FaultState = HRTIM_OUTPUTFAULTSTATE_INACTIVE;
  /* Disable chopper mode */
  HRTIM_TIM_OutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  /* No delay when entering burst mode */
  HRTIM_TIM_OutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;

  /* Choose polarity to active high */
  HRTIM_TIM_OutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  /* Set output high at timer compare 1 */
  HRTIM_TIM_OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
  /* Set output low at timer compare 2 */
  HRTIM_TIM_OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP2;

  /* Use initialized structure as output configuration for output TD1 */
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD1, &HRTIM_TIM_OutputCfg);

  /* Auto-delay disabled */
  HRTIM_CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  HRTIM_CompareCfg.AutoDelayedTimeout = 0;
  /*
   * Compare values:
   * NOTE: There are hardware limitations of the HRTIMER (Datasheet: 20.3.4 Timer A..E timing units table 78)
   * Minimum value must be greater than or equal to 3 periods of the fHRTIM clock
   * Maximum value must be less than or equal to 0xFFFF - 1 periods of the fHRTIM clock
   * If these conditions are violated, the related compares will be ignored!
   */
  /* PWM compare value 1 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWM */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_1, &HRTIM_CompareCfg);
  /* PWM compare value 2 initialized to zero */
  HRTIM_CompareCfg.CompareValue = 0;
  /* Use initialized structure for PWM */
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_2, &HRTIM_CompareCfg);

  /* Push-pull disable */
  HRTIM_TimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
  /* Fault condition defines */
  HRTIM_TimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
  HRTIM_TimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
  /* Dead-time insertion disable */
  HRTIM_TimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
  /* Delayed protection mode disable (EEV 6,7 only at TIMER A,B,C; EEV 8,9 only at TIMER D,E) */
  HRTIM_TimerCfg.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DISABLED;
  /* No update trigger */
  HRTIM_TimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
  /* Timer counter reset trigger off */
  HRTIM_TimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
  /* Update timer registers on reset */
  HRTIM_TimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;

  /* Use initialized structure for PWM */
  HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, &HRTIM_TimerCfg);

  /* Disable TD1 and TD2 outputs to keep rails off */
  HRTIM1->HRTIM_COMMON.DISR = (HRTIM_OUTPUT_TD1 | HRTIM_OUTPUT_TD2);

  /* Update configuration from preload register to Timer register */
  HRTIM1->HRTIM_COMMON.CR2 |= (MG_HRTIMER1_D_UPDATE);
}

/** *****************************************************************************
 * \brief         Initialize the high resolution timer for time base
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void HRTIMER_vHrTimerEHwInit(void)
{
  /*
   * High Resolution TIMER1E
   * HRTIMER1E global initialization for high resolution time base usage
   */
  /* Temporary typedefs */
  HRTIM_BaseInitTypeDef               HRTIM_BaseInitCfg;
  HRTIM_TimerInitTypeDef              HRTIM_TimerInitCfg;
  HRTIM_TimerCfgTypeDef               HRTIM_TimerCfg;

  /* PWM period initialized to base value */
  HRTIM_BaseInitCfg.Period = 0xFFFF;
  /* Repetition counter */
  HRTIM_BaseInitCfg.RepetitionCounter = 0U;
  /* Set prescaler to x16 (x32 will casue overflow) */
  HRTIM_BaseInitCfg.PrescalerRatio = HRTIM_E_PRESCALERRATIO;
  /* Set mode to continous */
  HRTIM_BaseInitCfg.Mode = HRTIM_MODE_CONTINOUS;

  /* Halfmode disable */
  HRTIM_TimerInitCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  /* Start, reset on sync and DAC sync disabled */
  HRTIM_TimerInitCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  HRTIM_TimerInitCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  HRTIM_TimerInitCfg.DACSynchro = HRTIM_DACSYNC_NONE;
  /* Set HRTIM to independent updategating */
  HRTIM_TimerInitCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  /* Burst mode maintained from clock */
  HRTIM_TimerInitCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  /* Update on repetition disabled */
  HRTIM_TimerInitCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
  /* Preload enable (shadow register mode) */
  HRTIM_TimerInitCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;

  /* Use initialized structure for HRTIM waveform generation */
  HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_E, &HRTIM_BaseInitCfg, &HRTIM_TimerInitCfg);

  /* Push-pull disable */
  HRTIM_TimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
  /* Fault condition defines */
  HRTIM_TimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
  HRTIM_TimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
  /* Dead-time insertion disable */
  HRTIM_TimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_ENABLED;
  /* Delayed protection mode disable (EEV 6,7 only at TIMER A,B,C; EEV 8,9 only at TIMER D,E) */
  HRTIM_TimerCfg.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DISABLED;
  /* No update trigger */
  HRTIM_TimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
  /* Timer counter reset trigger at TIMERA CMP4 event */
  HRTIM_TimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_OTHER1_CMP4;
  /* Update timer registers on reset */
  HRTIM_TimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;

  /* Use initialized structure for TIMER1E */
  HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_E, &HRTIM_TimerCfg);

  /* Configure the capture 1 */
  HRTIM1->HRTIM_TIMERx[HRTIM_TIMERINDEX_TIMER_E].CPT1xCR = HRTIM_CAPTURETRIGGER_TIMERA_CMP1;
  /* Configure the capture 2 */
  HRTIM1->HRTIM_TIMERx[HRTIM_TIMERINDEX_TIMER_E].CPT2xCR = HRTIM_CAPTURETRIGGER_TIMERB_CMP1;

  /* Update configuration from preload register to TimerD register */
  HRTIM1->HRTIM_COMMON.CR2 |= (MG_HRTIMER1_E_UPDATE);
}


/*
 * End of file
 */
