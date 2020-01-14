/** *****************************************************************************
 * \file    hrtimer_api.h
 * \brief   Service function request file for hrtimer.c
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

#ifndef HRTIMER_API_H
#define HRTIMER_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "hrtimer_conf.h"

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
void HRTIMER_vInit(void);

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
void HRTIMER_vDeInit(void);

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
void HRTIMER_vSyncStartHrTimer(void);

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
void HRTIMER_vMasterTimerInit(void);

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
void HRTIMER_vHrTimerSetPeriod(uint8 u8TimerId, uint32 u32nsHrTimerPeriod);

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
void HRTIMER_vHrTimerIsrNvicCfg(uint8 u8HrTimChId, uint8 u8PrePriority, uint8 u8SubPriority);

/** *****************************************************************************
 * \brief         Reset master timer ISR flag
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerMstCmp2IsrFlgReset(void)
{
  MG_REG_HRTIMER1_MST_CMP2_IR_CLR;
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerMstRepIsrFlgReset(void)
{
  MG_REG_HRTIMER1_MST_REP_IR_CLR;
}

/** *****************************************************************************
 * \brief         Read master timer ISR flag
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline uint8 HRTIMER_u8HrTimerMstCmp2ReadIsrFlg(void)
{
  return MG_REG_HRTIMER1_MST_CMP2_IR_RD;
}

__attribute__((section ("ccram")))
extern inline uint8 HRTIMER_u8HrTimerMstRepReadIsrFlg(void)
{
  return MG_REG_HRTIMER1_MST_REP_IR_RD;
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
void HRTIMER_vHrTimerDrvEnable(uint8 u8TimerId, uint8 u8Status);

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
void HRTIMER_vPrimDrvTimerInit(void);

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
void HRTIMER_vSrDrvTimerInit(void);

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
void HRTIMER_vIshareTimerInit(void);

/** *****************************************************************************
 * \brief         Turn off high resolution timer PWM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerAPwmOff()
{
  MG_REG_PWM_A_OFF;
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerBPwmOff()
{
  MG_REG_PWM_B_OFF;
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerCPwmOff()
{
  MG_REG_PWM_C_OFF;
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerDPwmOff()
{
  MG_REG_PWM_D_OFF;
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerEPwmOff()
{
  MG_REG_PWM_E_OFF;
}

/** *****************************************************************************
 * \brief         Turn on high resolution timer PWM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerAPwmOn()
{
  #if (!DEBUG_SECTION_PWM_A_DRV_OFF)
  MG_REG_PWM_A_ON;
  #endif
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerBPwmOn()
{
  #if (!DEBUG_SECTION_PWM_B_DRV_OFF)
  MG_REG_PWM_B_ON;
  #endif
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerCPwmOn()
{
  #if (!DEBUG_SECTION_PWM_C_DRV_OFF)
  MG_REG_PWM_C_ON;
  #endif
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerDPwmOn()
{
  #if (!DEBUG_SECTION_PWM_D_DRV_OFF)
  MG_REG_PWM_D_ON;
  #endif
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerEPwmOn()
{
  #if (!DEBUG_SECTION_PWM_E_DRV_OFF)
  MG_REG_PWM_E_ON;
  #endif
}

/** *****************************************************************************
 * \brief         Set high resolution timer period
 *
 * \param[in]     Period in ns
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerMstPeriod(uint32 u321nsHrTimerPeriod)
{
  /* Scale ns to timer value and set period */
  MG_REG_HRTIMER1_MST_PERIOD = ((mg_u32q12nsTimerMstConvFact * u321nsHrTimerPeriod) >> 12);
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerAPeriod(uint32 u321nsHrTimerPeriod)
{
  /* Scale ns to timer value and set period */
  MG_REG_HRTIMER1_A_PERIOD = ((mg_u32q12nsTimerAConvFact * u321nsHrTimerPeriod) >> 12);
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerBPeriod(uint32 u321nsHrTimerPeriod)
{
  /* Scale ns to timer value and set period */
  MG_REG_HRTIMER1_B_PERIOD = ((mg_u32q12nsTimerBConvFact * u321nsHrTimerPeriod) >> 12);
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerCPeriod(uint32 u321nsHrTimerPeriod)
{
  /* Scale ns to timer value and set period */
  MG_REG_HRTIMER1_C_PERIOD = ((mg_u32q12nsTimerCConvFact * u321nsHrTimerPeriod) >> 12);
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerDPeriod(uint32 u321nsHrTimerPeriod)
{
  /* Scale ns to timer value and set period */
  MG_REG_HRTIMER1_D_PERIOD = ((mg_u32q12nsTimerDConvFact * u321nsHrTimerPeriod) >> 12);
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerEPeriod(uint32 u321nsHrTimerPeriod)
{
  /* Scale ns to timer value and set period */
  MG_REG_HRTIMER1_E_PERIOD = ((mg_u32q12nsTimerEConvFact * u321nsHrTimerPeriod) >> 12);
}

/** *****************************************************************************
 * \brief         Primary side LLC half bridge drive: Set period, determine compare values from duty cycle, set dead time
 *
 * \param[in]     Period in ns, duty cycle as Q16, dead time in ns
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerSetPwm(uint32 u321nsHrTimerPeriod, uint16 u16q16DutyCycle, uint16 u161nSLlcDeadTime, sint16 s161nsSrDeadTimeOn, sint16 s161nsSrDeadTimeOff)
{
  static uint16 u16PwmPeriod = 0U;
  static uint32 u32PwmHalfPeriod = 0U;
  static uint16 u16PwmQuarterPeriod = 0U;
  static sint32 s32LlcPwmOnTime = 0U;
  static sint32 s32LlcPwmOn = 0U;
  static sint32 s32LlcPwmOff = 0U;
  static sint32 s32LlcPwmOn2 = 0U;
  static sint32 s32LlcPwmOff2 = 0U;
  static uint16 u16LlcPwmDeadTime = 0U;
  static sint32 s32SrPwmOn = 0U;
  static sint32 s32SrPwmOff = 0U;
  static sint32 s32SrPwmOn2 = 0U;
  static sint32 s32SrPwmOff2 = 0U;
  static sint32 s32SrPwmDeadTimeOn = 0U;
  static sint32 s32SrPwmDeadTimeOff = 0U;

  /*******************************************************************************
   * Determine period, duty cycle and dead time
   *******************************************************************************/
  /* Scale ns to timer value */
  u16PwmPeriod = ((mg_u32q12nsTimerAConvFact * u321nsHrTimerPeriod) >> 12);     /* divided by 1 due to pushpull mode (doubles period) */
  /* Scale ns to timer value */
  u16LlcPwmDeadTime = ((mg_u32q12nsTimerAConvFact * u161nSLlcDeadTime) >> 12);
  u16LlcPwmDeadTime = SAT_L(u16LlcPwmDeadTime, (uint16)100U);
  /* Scale ns to timer value */
  s32SrPwmDeadTimeOn = (((sint32)mg_u32q12nsTimerBConvFact * s161nsSrDeadTimeOn) >> 12);
  /* Scale ns to timer value */
  s32SrPwmDeadTimeOff = (((sint32)mg_u32q12nsTimerBConvFact * s161nsSrDeadTimeOff) >> 12);

  /* Get half and quarter period for further processing */
  u32PwmHalfPeriod = (u16PwmPeriod >> 1);
  u16PwmQuarterPeriod = (u16PwmPeriod >> 2);

  /* Limit the duty cycle to 0.49998474 */
  u16q16DutyCycle = SAT_H(u16q16DutyCycle, 32767);

  /* Determine LLC on time, hlaf of the on time */
  s32LlcPwmOnTime = ((uint32)u32PwmHalfPeriod * u16q16DutyCycle) >> 16;
  /* Determine LLC turn on */
  #if 0
  s32LlcPwmOn = u16PwmQuarterPeriod - s32LlcPwmOnTime;
  s32LlcPwmOn = SAT_L(s32LlcPwmOn, u16LlcPwmDeadTime);
  #else
  s32LlcPwmOn = u16PwmQuarterPeriod - SAT_L(s32LlcPwmOnTime - (sint16)u16LlcPwmDeadTime, (sint16)0);
  #endif
  /* Determine LLC turn off */
  s32LlcPwmOff = u32PwmHalfPeriod - s32LlcPwmOn;
  /* TA2 on setup */
  s32LlcPwmOn2 = (uint16)(s32LlcPwmOn + u32PwmHalfPeriod);
  /* TA2 off setup */
  s32LlcPwmOff2 = (uint16)(s32LlcPwmOff + u32PwmHalfPeriod);

  /* Determine SR turn on */
  s32SrPwmOn = s32LlcPwmOn + s32SrPwmDeadTimeOn;
  s32SrPwmOn = LIMIT(s32SrPwmOn, 100, s32LlcPwmOff);  /* 100 for minimum compare value (HRTIMER limitation) and minimum forced dead time; NOTE: do not change!!! */
  /* Determine SR turn off */
  s32SrPwmOff = s32LlcPwmOff - s32SrPwmDeadTimeOff;
  s32SrPwmOff = LIMIT(s32SrPwmOff, s32SrPwmOn, u32PwmHalfPeriod);
  /* TB2 on setup */
  s32SrPwmOn2 = (uint16)(s32SrPwmOn + u32PwmHalfPeriod);
  /* TB2 off setup */
  s32SrPwmOff2 = (uint16)(s32SrPwmOff + u32PwmHalfPeriod);

  /* Disable repetition update */
  MG_REG_HRTIMER1_UPDATE_DIS;

  /* Write new period values */
  MG_REG_HRTIMER1_A_PERIOD = u16PwmPeriod;
  MG_REG_HRTIMER1_B_PERIOD = u16PwmPeriod;
  MG_REG_HRTIMER1_MST_PERIOD = u16PwmPeriod;
  /* Due to push-pull mode, both outputs share the same compares */
  /* Set the compare 1 value (output A1 high) */
  MG_REG_HRTIMER1_A_CMP1 = s32LlcPwmOn;
  /* Set the compare 2 value (output A1 low) */
  MG_REG_HRTIMER1_A_CMP2 = s32LlcPwmOff;
  /* Set the compare 1 value (output A2 high) */
  MG_REG_HRTIMER1_A_CMP3 = s32LlcPwmOn2;
  /* Set the compare 2 value (output A2 low) */
  MG_REG_HRTIMER1_A_CMP4 = s32LlcPwmOff2;

  /* Due to push-pull mode, both outputs share the same compares */
  /* Set the compare 1 value (output B1 high) */
  MG_REG_HRTIMER1_B_CMP1 = s32SrPwmOn;
  /* Set the compare 2 value (output B1 low) */
  MG_REG_HRTIMER1_B_CMP2 = s32SrPwmOff;

  /* Set the compare 1 value (output B2 high) */
  MG_REG_HRTIMER1_B_CMP3 = s32SrPwmOn2;
  /* Set the compare 2 value (output B2 low) */
  MG_REG_HRTIMER1_B_CMP4 = s32SrPwmOff2;

  /* Enable repetition update */
  MG_REG_HRTIMER1_UPDATE_EN;
}

/** *****************************************************************************
 * \brief         Set duty cycle
 *
 * \param[in]     Duty cycle as Q16
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerDDutyCycle(uint16 u16q16DutyCycle)
{
  static uint16 u16PwmHalfPeriod = 0U;

  /* Get half period */
  u16PwmHalfPeriod = (MG_REG_HRTIMER1_D_PERIOD >> 1);
  /* Up-down-count PWM */
  /* Set the compare 1 value (output high) */
  MG_REG_HRTIMER1_D_CMP1 = u16PwmHalfPeriod - (((uint32)u16PwmHalfPeriod * u16q16DutyCycle) >> 16);
  /* Set the compare 2 value (output low) */
  MG_REG_HRTIMER1_D_CMP2 = u16PwmHalfPeriod + (((uint32)u16PwmHalfPeriod * u16q16DutyCycle) >> 16);
}

/** *****************************************************************************
 * \brief         Check if high resolution timer delayed protection occured
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        Flag status
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline uint8 HRTIMER_u8HrTimerAReadDlyProtFlg()
{
  return MG_REG_HRTIMER1_A_DLYPROT;
}

__attribute__((section ("ccram")))
extern inline uint8 HRTIMER_u8HrTimerBReadDlyProtFlg()
{
  return MG_REG_HRTIMER1_B_DLYPROT;
}

__attribute__((section ("ccram")))
extern inline uint8 HRTIMER_u8HrTimerCReadDlyProtFlg()
{
  return MG_REG_HRTIMER1_C_DLYPROT;
}

/** *****************************************************************************
 * \brief         Clear the high resolution timer delayed protection flag
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerAClearDlyProtFlg()
{
  MG_REG_HRTIMER1_A_DLYPROT_CLR;
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerBClearDlyProtFlg()
{
  MG_REG_HRTIMER1_B_DLYPROT_CLR;
}

__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerCClearDlyProtFlg()
{
  MG_REG_HRTIMER1_C_DLYPROT_CLR;
}

/** *****************************************************************************
 * \brief         Enable high resolution update
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerUpdateEn()
{
  MG_REG_HRTIMER1_UPDATE_EN;
}

/** *****************************************************************************
 * \brief         Disable high resolution update
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void HRTIMER_vHrTimerUpdateDis()
{
  MG_REG_HRTIMER1_UPDATE_DIS;
}


#ifdef __cplusplus
  }
#endif
#endif  /* HRTIMER_API_H */


/*
 * End of file
 */
