/** *****************************************************************************
 * \file    hwio_api.h
 * \brief   Service function request file for hwio.c
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

#ifndef HWIO_API_H
#define HWIO_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "hwio_scfg.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/* ADC module section */
__attribute__((section ("ccram")))
extern inline uint16 HWIO_u16AdcSampleVoltOutExt(void)
{
  return HWIO_scfg_u16AdcSampleVoltOutExt();
}

__attribute__((section ("ccram")))
extern inline uint16 HWIO_u16AdcSampleVoltOutInt(void)
{
  return HWIO_scfg_u16AdcSampleVoltOutInt();
}

__attribute__((section ("ccram")))
extern inline uint16 HWIO_u16AdcSampleCurrOut(void)
{
  return HWIO_scfg_u16AdcSampleCurrOut();
}

__attribute__((section ("ccram")))
extern inline uint16 HWIO_u16AdcSampleAcsBus(void)
{
  return HWIO_scfg_u16AdcSampleAcsBus();
}

__attribute__((section ("ccram")))
extern inline uint16 HWIO_u16AdcSampleAcsLocal(void)
{
  return HWIO_scfg_u16AdcSampleAcsLocal();
}

/* HRTIMER module section */
__attribute__((section ("ccram")))
extern inline void HWIO_vIshareTimerInit(void)
{
  HWIO_scfg_vIshareTimerInit();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerAPwmOff(void)
{
  HWIO_scfg_vHrTimerAPwmOff();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerBPwmOff(void)
{
  HWIO_scfg_vHrTimerBPwmOff();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerCPwmOff(void)
{
  HWIO_scfg_vHrTimerCPwmOff();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerDPwmOff(void)
{
  HWIO_scfg_vHrTimerDPwmOff();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerEPwmOff(void)
{
  HWIO_scfg_vHrTimerEPwmOff();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerAPwmOn(void)
{
  HWIO_scfg_vHrTimerAPwmOn();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerBPwmOn(void)
{
  HWIO_scfg_vHrTimerBPwmOn();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerCPwmOn(void)
{
  HWIO_scfg_vHrTimerCPwmOn();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerDPwmOn(void)
{
  HWIO_scfg_vHrTimerDPwmOn();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerEPwmOn(void)
{
  HWIO_scfg_vHrTimerEPwmOn();
}

__attribute__((section ("ccram")))
inline void HWIO_vHrTimerSetPwm(uint32 u321nsHrTimerPeriod, uint16 u16q16DutyCycle, uint16 u161nSLlcDeadTime, sint16 s161nsSrDeadTimeOn, sint16 s161nsSrDeadTimeOff)
{
  HWIO_scfg_vHrTimerSetPwm(u321nsHrTimerPeriod, u16q16DutyCycle, u161nSLlcDeadTime, s161nsSrDeadTimeOn, s161nsSrDeadTimeOff);
}

__attribute__((section ("ccram")))
extern inline uint8 HWIO_u8HrTimerAReadDlyProtFlg(void)
{
  return HWIO_scfg_u8HrTimerAReadDlyProtFlg();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerAClearDlyProtFlg(void)
{
  HWIO_scfg_vHrTimerAClearDlyProtFlg();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerUpdateEn(void)
{
  HWIO_scfg_vHrTimerUpdateEn();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerUpdateDis(void)
{
  HWIO_scfg_vHrTimerUpdateDis();
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerDSetPeriod(uint32 u321nsHrTimerPeriod)
{
  HWIO_scfg_vHrTimerDSetPeriod(u321nsHrTimerPeriod);
}

__attribute__((section ("ccram")))
extern inline void HWIO_vHrTimerDSetDutyCycle(uint16 u16q16DutyCycle)
{
  HWIO_scfg_vHrTimerDSetDutyCycle(u16q16DutyCycle);
}

/* COMP module section */
__attribute__((section ("ccram")))
extern inline void HWIO_vSetComp2Ref(uint32 u32CompRef)
{
  HWIO_scfg_vSetComp2Ref(u32CompRef);
}

__attribute__((section ("ccram")))
extern inline void HWIO_vSetComp4Ref(uint32 u32CompRef)
{
  HWIO_scfg_vSetComp4Ref(u32CompRef);
}

__attribute__((section ("ccram")))
extern inline void HWIO_vSetComp6Ref(uint32 u32CompRef)
{
  HWIO_scfg_vSetComp6Ref(u32CompRef);
}

__attribute__((section ("ccram")))
extern inline uint8 HWIO_u8Comp2OutputStatus(void)
{
  return HWIO_scfg_u8Comp2OutputStatus();
}

__attribute__((section ("ccram")))
extern inline uint8 HWIO_u8Comp4OutputStatus(void)
{
  return HWIO_scfg_u8Comp4OutputStatus();
}

__attribute__((section ("ccram")))
extern inline uint8 HWIO_u8Comp6OutputStatus(void)
{
  return HWIO_scfg_u8Comp6OutputStatus();
}

/* DAC module section */
__attribute__((section ("ccram")))
extern inline void HWIO_vSetAcsBus(sint16 s1610mAAcsLocal)
{
  HWIO_scfg_vSetAcsBus(s1610mAAcsLocal);
}

/* WDG module section */
extern inline void HWIO_vWdgSysReset(void)
{
  HWIO_scfg_vWdgSysReset();
}

/* Flash module section */
extern inline void HWIO_vSetFwUpgradeFlg(void)
{
  HWIO_scfg_vFlashWriteUpgradeFlg();
}


#ifdef __cplusplus
  }
#endif
#endif  /* HWIO_API_H */

  
/*
 * End of file
 */
