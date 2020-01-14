/** *****************************************************************************
 * \file    acsctrl_scfg.h
 * \brief   Server request service file for acsctrl.c
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

#ifndef ACSCTRL_SCFG_H
#define ACSCTRL_SCFG_H
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
inline uint16 ACSCTRL_scfg_u16AdcSampleAcsBus(void)
{
  #if MG_HWIO_MODULE
  return HWIO_u16AdcSampleAcsBus();
  #else
  return 0;
  #endif
}
__attribute__((section ("ccram")))
inline uint16 ACSCTRL_scfg_u16AdcSampleAcsLocal(void)
{
  #if MG_HWIO_MODULE
  return HWIO_u16AdcSampleAcsLocal();
  #else
  return 0;
  #endif
}
__attribute__((section ("ccram")))
inline uint16 ACSCTRL_scfg_u16AdcSampleCurrOut(void)
{
  #if MG_HWIO_MODULE
  return HWIO_u16AdcSampleCurrOut();
  #else
  return 0;
  #endif
}

/* HRTIMER module section */
inline void ACSCTRL_scfg_vIshareTimerInit(void)
{
  #if MG_HWIO_MODULE
  HWIO_vIshareTimerInit();
  #endif
}

__attribute__((section ("ccram")))
inline void ACSCTRL_scfg_vSetAcsBus(sint16 s1610mAAcsLocal)
{
  #if MG_HWIO_MODULE
  HWIO_vSetAcsBus(s1610mAAcsLocal);
  #endif
}

#if 0
__attribute__((section ("ccram")))
inline void ACSCTRL_scfg_vHrTimerBPwmOff(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerBPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void ACSCTRL_scfg_vHrTimerBPwmOn(void)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerBPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void ACSCTRL_scfg_vHrTimerBSetPeriod(uint32 u321nsHrTimerPeriod)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerBSetPeriod(u321nsHrTimerPeriod);
  #endif
}

__attribute__((section ("ccram")))
inline void ACSCTRL_scfg_vHrTimerBSetDutyCycle(uint16 u16q16DutyCycle)
{
  #if MG_HWIO_MODULE
  HWIO_vHrTimerBSetDutyCycle(u16q16DutyCycle);
  #endif
}
#endif


#ifdef __cplusplus
  }
#endif
#endif  /* ACSCTRL_SCFG_H */

  
/*
 * End of file
 */
