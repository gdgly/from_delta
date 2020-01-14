/** *****************************************************************************
 * \file    llcctrl_scfg.h
 * \brief   Server request service file for llcctrl.c
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

#ifndef LLCCTRL_SCFG_H
#define LLCCTRL_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_HWIO_MODULE            1

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"

#if MG_HWIO_MODULE
#include "hwio_api.h"
#endif

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* ADC module section */
__attribute__((section ("ccram")))
inline uint16 LLCCTRL_scfg_u16AdcSampleVoltOutExt(void)
{
  #if MG_HWIO_MODULE
  return HWIO_u16AdcSampleVoltOutExt();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 LLCCTRL_scfg_u16AdcSampleVoltOutInt(void)
{
  #if MG_HWIO_MODULE
  return HWIO_u16AdcSampleVoltOutInt();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 LLCCTRL_scfg_u16AdcSampleCurrOut(void)
{
  #if MG_HWIO_MODULE
  return HWIO_u16AdcSampleCurrOut();
  #else
  return 0;
  #endif
}

/* HRTIMER module section */
__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerAPwmOff(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerAPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerBPwmOff(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerBPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerDPwmOff(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerDPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerAPwmOn(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerAPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerBPwmOn(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerBPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerDPwmOn(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerDPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerSetPwm(uint32 u321nsHrTimerPeriod, uint16 u16q16DutyCycle, uint16 u161nSLlcDeadTime, sint16 s161nsSrDeadTimeOn, sint16 s161nsSrDeadTimeOff)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerSetPwm(u321nsHrTimerPeriod, u16q16DutyCycle, u161nSLlcDeadTime, s161nsSrDeadTimeOn, s161nsSrDeadTimeOff);
  #endif
}

__attribute__((section ("ccram")))
inline uint8 LLCCTRL_scfg_u8HrTimerAReadDlyProtFlg(void)
{
  #if MG_HWIO_MODULE
  return HWIO_u8HrTimerAReadDlyProtFlg();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerAClearDlyProtFlg(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerAClearDlyProtFlg();
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerUpdateEn(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerUpdateEn();
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vHrTimerUpdateDis(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerUpdateDis();
  #endif
}

/* COMP module section */
__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vSetCompRef(uint32 u32CompRef)
{
  #if MG_HWIO_MODULE
  HWIO_vSetComp2Ref(u32CompRef);
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vSetComp4Ref(uint32 u32CompRef)
{
  #if MG_HWIO_MODULE
  HWIO_vSetComp4Ref(u32CompRef);
  #endif
}

__attribute__((section ("ccram")))
inline void LLCCTRL_scfg_vSetComp6Ref(uint32 u32CompRef)
{
  #if MG_HWIO_MODULE
  HWIO_vSetComp6Ref(u32CompRef);
  #endif
}

__attribute__((section ("ccram")))
inline uint8 LLCCTRL_scfg_u8CompOutputStatus(void)
{
  #if MG_HWIO_MODULE
  return HWIO_u8Comp2OutputStatus();
  #else
  return 0;
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* LLCCTRL_SCFG_H */

  
/*
 * End of file
 */
