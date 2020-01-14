/** *****************************************************************************
 * \file    hwio_scfg.h
 * \brief   Server request service file for hwio.c
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

#ifndef HWIO_SCFG_H
#define HWIO_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_ADC_MODULE             1
#define MG_PORT_MODULE            1
#define MG_HRTIMER_MODULE         1
#define MG_COMP_MODULE            1
#define MG_FLASH_MODULE           1
#define MG_DAC_MODULE             1
#define MG_TIMER_MODULE           1
#define MG_WDG_MODULE             1

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"
#include "hwio_conf.h"

#if MG_ADC_MODULE
#include "adc_api.h"
#endif
#if MG_PORT_MODULE
#include "port_api.h"
#endif
#if MG_HRTIMER_MODULE
#include "hrtimer_api.h"
#endif
#if MG_COMP_MODULE
#include "comp_api.h"
#endif
#if MG_FLASH_MODULE
#include "flash_api.h"
#endif
#if MG_DAC_MODULE
#include "dac_api.h"
#endif
#if MG_TIMER_MODULE
#include "timer_api.h"
#endif
#if MG_WDG_MODULE
#include "wdg_api.h"
#endif

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* ADC module section */
inline void HWIO_scfg_vAdcVoltOutExtScale(uint16 u16ScaleFact)
{
  #if MG_ADC_MODULE
  ADC_vVoltOutExtScale(u16ScaleFact);
  #endif
}
inline void HWIO_scfg_vAdcVoltOutIntScale(uint16 u16ScaleFact)
{
  #if MG_ADC_MODULE
  ADC_vVoltOutIntScale(u16ScaleFact);
  #endif
}
inline void HWIO_scfg_vAdcCurrOutScale(uint16 u16ScaleFact)
{
  #if MG_ADC_MODULE
  ADC_vCurrOutScale(u16ScaleFact);
  #endif
}
inline void HWIO_scfg_vAdcAcsBusScale(uint16 u16ScaleFact)
{
  #if MG_ADC_MODULE
  ADC_vAcsBusScale(u16ScaleFact);
  #endif
}
inline void HWIO_scfg_vAdcAcsLocalScale(uint16 u16ScaleFact)
{
  #if MG_ADC_MODULE
  ADC_vAcsLocalScale(u16ScaleFact);
  #endif
}
inline void HWIO_scfg_vAdcVoltRef3V3Scale(uint16 u16ScaleFact)
{
  #if MG_ADC_MODULE
  ADC_vVoltRef3V3Scale(u16ScaleFact);
  #endif
}
inline void HWIO_scfg_vAdcResNtcScale(uint16 u16ScaleFact)
{
  #if MG_ADC_MODULE
  ADC_vAdcResNtcScale(u16ScaleFact);
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16AdcSampleVoltOutExt(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleVoltOutExt();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16AdcSampleVoltOutInt(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleVoltOutInt();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16AdcSampleCurrOut(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleCurrOut();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16AdcSampleAcsBus(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleAcsBus();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16AdcSampleAcsLocal(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleAcsLocal();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16VoltRef3V3(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleVoltRef3V3();
  #else
  return 0U;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16NtcOringSample(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleNtcOring();
  #else
  return 0U;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16NtcSrSample(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleNtcSr();
  #else
  return 0U;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16NtcOringSamplemV(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleNtcOringmV();
  #else
  return 0U;
  #endif
}

__attribute__((section ("ccram")))
inline uint16 HWIO_scfg_u16NtcSrSamplemV(void)
{
  #if MG_ADC_MODULE
  return ADC_u16AdcSampleNtcSrmV();
  #else
  return 0U;
  #endif
}

/* PORT module section */
inline void HWIO_scfg_vSetGpioPortPwmOn(uint8 u8Status)
{
  #if MG_PORT_MODULE
  PORT_vSetGpioPinPwmOn(u8Status);
  #endif
}
inline void HWIO_scfg_vSetGpioPortIshareOn(uint8 u8Status)
{
  #if MG_PORT_MODULE
  PORT_vSetGpioPinIshareOn(u8Status);
  #endif
}
inline void HWIO_scfg_vSetGpioPortOvpClr(uint8 u8Status)
{
  #if MG_PORT_MODULE
  PORT_vSetGpioPinOvpClr(u8Status);
  #endif
}
inline void HWIO_scfg_vSetGpioPortOringEn(uint8 u8Status)
{
  #if MG_PORT_MODULE
  PORT_vSetGpioPinOringEn(u8Status);
  #endif
}
inline void HWIO_scfg_vSetGpioPortLlcFault(uint8 u8Status)
{
  #if MG_PORT_MODULE
  PORT_vSetGpioPinLlcFault(u8Status);
  #endif
}
inline void HWIO_scfg_vInputGpioPinOvpClr(void)
{
  #if MG_PORT_MODULE
  PORT_vInputGpioPinOvpClr();
  #endif
}
inline void HWIO_scfg_vOutputGpioPinOvpClr(void)
{
  #if MG_PORT_MODULE
  PORT_vOutputGpioPinOvpClr();
  #endif
}

inline uint8 HWIO_scfg_u8ReadGpioPortBulkOk(void)
{
  #if MG_PORT_MODULE
  return PORT_u8ReadGpioPinBulkOk();
  #else
  return RESET;
  #endif
}

inline uint8 HWIO_scfg_u8ReadGpioPortOvp(void)
{
  #if MG_PORT_MODULE
  return PORT_u8ReadGpioPinOvp();
  #else
  return RESET;
  #endif
}

//inline uint8 HWIO_scfg_u8ReadGpioPortLlcSwitchEn(void)
//{
//  #if MG_PORT_MODULE
//  return PORT_u8ReadGpioPinLlcSwitchEn();
//  #else
//  return RESET;
//  #endif
//}

inline uint8 HWIO_scfg_u8ReadGpioPortLlcHalt(void)
{
  #if MG_PORT_MODULE
  return PORT_u8ReadGpioPinLlcHalt();
  #else
  return RESET;
  #endif
}

/* HRTIMER module section */
inline void HWIO_scfg_vHrTimerDrvEnable(uint8 u8TimerId, uint8 u8Status)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerDrvEnable(u8TimerId, u8Status);
  #endif
}

inline void HWIO_scfg_vIshareTimerInit(void)
{
  #if MG_HWIO_MODULE
  HRTIMER_vIshareTimerInit();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerAPwmOff(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerAPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerBPwmOff(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerBPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerCPwmOff(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerCPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerDPwmOff(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerDPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerEPwmOff(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerEPwmOff();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerAPwmOn(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerAPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerBPwmOn(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerBPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerCPwmOn(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerCPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerDPwmOn(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerDPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerEPwmOn(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerEPwmOn();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerSetPwm(uint32 u321nsHrTimerPeriod, uint16 u16q16DutyCycle, uint16 u161nSLlcDeadTime, sint16 s161nsSrDeadTimeOn, sint16 s161nsSrDeadTimeOff)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerSetPwm(u321nsHrTimerPeriod, u16q16DutyCycle, u161nSLlcDeadTime, s161nsSrDeadTimeOn, s161nsSrDeadTimeOff);
  #endif
}

__attribute__((section ("ccram")))
inline uint8 HWIO_scfg_u8HrTimerAReadDlyProtFlg(void)
{
  #if MG_HRTIMER_MODULE
  return HRTIMER_u8HrTimerAReadDlyProtFlg();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerAClearDlyProtFlg(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerAClearDlyProtFlg();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerUpdateEn(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerUpdateEn();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerUpdateDis(void)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerUpdateDis();
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerDSetPeriod(uint32 u321nsHrTimerPeriod)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerDPeriod(u321nsHrTimerPeriod);
  #endif
}

__attribute__((section ("ccram")))
inline void HWIO_scfg_vHrTimerDSetDutyCycle(uint16 u16q16DutyCycle)
{
  #if MG_HRTIMER_MODULE
  HRTIMER_vHrTimerDDutyCycle(u16q16DutyCycle);
  #endif
}

/* COMP module section */
inline void HWIO_scfg_vSetComp2Ref(uint32 u32CompRef)
{
  #if MG_COMP_MODULE
  COMP_vSetComp2Ref(u32CompRef);
  #endif
}

inline void HWIO_scfg_vSetComp4Ref(uint32 u32CompRef)
{
  #if MG_COMP_MODULE
  COMP_vSetComp4Ref(u32CompRef);
  #endif
}

inline void HWIO_scfg_vSetComp6Ref(uint32 u32CompRef)
{
  #if MG_COMP_MODULE
  COMP_vSetComp6Ref(u32CompRef);
  #endif
}

__attribute__((section ("ccram")))
inline uint8 HWIO_scfg_u8Comp2OutputStatus(void)
{
  #if MG_COMP_MODULE
  return COMP_u8Comp2OutputStatus();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint8 HWIO_scfg_u8Comp4OutputStatus(void)
{
  #if MG_COMP_MODULE
  return COMP_u8Comp4OutputStatus();
  #else
  return 0;
  #endif
}

__attribute__((section ("ccram")))
inline uint8 HWIO_scfg_u8Comp6OutputStatus(void)
{
  #if MG_COMP_MODULE
  return COMP_u8Comp6OutputStatus();
  #else
  return 0;
  #endif
}

inline void HWIO_scfg_vCompCurrCtOcScale(uint32 u32ScaleFact)
{
  #if MG_COMP_MODULE
  COMP_vComp2Scale(u32ScaleFact);
  #endif
}

/* Flash module section */
inline uint8 HWIO_scfg_u8FlashReadBlExistFlg(void)
{
  #if MG_FLASH_MODULE
  return FLASH_u8ReadBlExistFlg();
  #else
  return 0;
  #endif
}

/* Flash module section */
inline uint32 HWIO_scfg_u32FlashReadBlFwVer(void)
{
  #if MG_FLASH_MODULE
  return FLASH_u32ReadBlFwVer();
  #else
  return 0;
  #endif
}

/* Flash module section */
inline void HWIO_scfg_vFlashWriteUpgradeFlg(void)
{
  #if MG_FLASH_MODULE
  FLASH_vWriteUpgradeFlg();
  #endif
}

/* DAC module section */
inline void HWIO_scfg_vSetAcsBus(sint16 s1610mAAcsLocal)
{
  #if MG_DAC_MODULE
  s1610mAAcsLocal = LIMIT(s1610mAAcsLocal, (sint16)0U, MG_U16_10mA_I_OUT_SCALE_FACT);
  DAC_vSetDac1Ch1Scaled(s1610mAAcsLocal);
  #endif
}

inline void HWIO_scfg_vDacAcsScale(uint32 u32ScaleFact)
{
  #if MG_DAC_MODULE
  DAC_vDac1Ch1Scale(u32ScaleFact);
  #endif
}

/* TIMER module section */
inline void HWIO_scfg_vTimerSetPeriod(uint8 u8TimerId, uint16 u16usTimerPeriod)
{
  #if MG_TIMER_MODULE
  TIMER_vTimerSetPeriod(u8TimerId, u16usTimerPeriod);
  #endif
}

inline void HWIO_scfg_vTimer1Ch1DutyCycle(uint16 u16q16DutyCycle)
{
  #if MG_TIMER_MODULE
  TIMER_vTimer1Ch1DutyCycle(u16q16DutyCycle);
  #endif
}

/* WDG module section */
inline void HWIO_scfg_vWdgSysReset(void)
{
  #if MG_WDG_MODULE
  WDG_vSysReset();
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* HWIO_SCFG_H */

  
/*
 * End of file
 */
