/** *****************************************************************************
 * \file    hwio_rte.h
 * \brief   RTE interface file for hwio.c
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

#ifndef HWIO_RTE_H
#define HWIO_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_RTE_MODULE           1

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"

#if MG_RTE_MODULE
#include "rte.h"
#endif

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
 
#define Rte_Read_R_s16CalibCurrOutAmp(var)    ((**var) = RTE_s16CalibCurrOutAmp)
#define Rte_Read_R_s16CalibCurrOutOfs(var)    ((**var) = RTE_s16CalibCurrOutOfs)

#define Rte_Write_P_10mV_VoltOutExt(var)      (RTE_u1610mVVoltOutExt = (var))
#define Rte_Write_P_10mV_VoltOutInt(var)      (RTE_u1610mVVoltOutInt = (var))
#define Rte_Write_P_10mA_CurrOut(var)         (RTE_u1610mACurrOut = (var))
#define Rte_Write_P_10mA_CurrOutCali(var)     (RTE_u1610mACurrOutCali = (var))
#define Rte_Write_P_10mA_AcsBus(var)          (RTE_u1610mAAcsBus = (var))
#define Rte_Write_P_10mA_AcsLocal(var)        (RTE_u1610mAAcsLocal = (var))
#define Rte_Write_P_1mV_VoltRef3V3(var)       (RTE_u161mVVoltRef3V3 = (var))
#define Rte_Write_P_q12_VoltRefCaliFact(var)  (RTE_u16q12VoltRefCaliFact = (var))
#define Rte_Write_P_1Ohm_ResNtcOring(var)     (RTE_u161OhmResNtc1Hwio = (var))
#define Rte_Write_P_1Ohm_ResNtcSr(var)        (RTE_u161OhmResNtc2Hwio = (var))
#define Rte_Write_P_1mV_VoltNtcOring(var)     (RTE_u161mVVoltNtc1Hwio = (var))
#define Rte_Write_P_1mV_VoltNtcSr(var)        (RTE_u161mVVoltNtc2Hwio = (var))
#define Rte_Write_P_BlFwVerMajor(var)         (RTE_u8BlFwVerMajor = (var))
#define Rte_Write_P_BlFwVerMinor(var)         (RTE_u8BlFwVerMinor = (var))
#define Rte_Write_P_BlFwVerDebug(var)         (RTE_u8BlFwVerDebug = (var))

#if MG_RTE_MODULE
/* Read bits */
#define Rte_Read_R_B_PORT_PWM_ON              RTE_B_PORT_PWM_ON
#define Rte_Read_R_B_PORT_ISHARE_ON           RTE_B_PORT_ISHARE_ON
#define Rte_Read_R_B_PORT_ORING_PULSE         RTE_B_PORT_ORING_PULSE
#define Rte_Read_R_B_PORT_ORING_EN            RTE_B_PORT_ORING_EN
#define Rte_Read_R_B_PORT_LLC_FAULT           RTE_B_PORT_LLC_FAULT
#define Rte_Read_R_B_PORT_OVP_CLR             RTE_B_PORT_OVP_CLR
#define Rte_Read_R_B_PWM_A_ON                 RTE_B_HRTIMER_PWM_A_ON
#define Rte_Read_R_B_PWM_B_ON                 RTE_B_HRTIMER_PWM_B_ON
#define Rte_Read_R_B_PWM_C_ON                 RTE_B_HRTIMER_PWM_C_ON
#define Rte_Read_R_B_PWM_D_ON                 RTE_B_HRTIMER_PWM_D_ON
#define Rte_Read_R_B_PWM_E_ON                 RTE_B_HRTIMER_PWM_E_ON
/* Write bits */
#define Rte_Write_P_B_PORT_BULK_OK            RTE_B_PORT_BULK_OK
#define Rte_Write_P_B_PORT_OVP                RTE_B_PORT_OVP
#define Rte_Write_P_B_PORT_LLC_SWITCH_EN      RTE_B_PORT_LLC_SWITCH_EN
#define Rte_Write_P_B_PORT_LLC_HALT           RTE_B_PORT_LLC_HALT
#define Rte_Write_P_B_BL_EXIST                RTE_B_BL_EXIST
#define Rte_Write_P_B_Port_LLC_FAULT          RTE_B_PORT_LLC_FAULT
#else
/* Read bits */
#define Rte_Read_R_B_PORT_PWM_ON              0
#define Rte_Read_R_B_PORT_ISHARE_ON           0
#define Rte_Read_R_B_PORT_OVP_CLR             0
#define Rte_Read_R_B_PWM_A_ON                 FALSE
#define Rte_Read_R_B_PWM_B_ON                 FALSE
#define Rte_Read_R_B_PWM_C_ON                 FALSE
#define Rte_Read_R_B_PWM_D_ON                 FALSE
#define Rte_Read_R_B_PWM_E_ON                 FALSE
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Read data */
inline void HWIO_Read_R_s16CalibCurrOutAmp_rte(sint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_s16CalibCurrOutAmp(&var);
  #endif
}
inline void HWIO_Read_R_s16CalibCurrOutOfs_rte(sint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_s16CalibCurrOutOfs(&var);
  #endif
}

/* Write data */
inline void HWIO_Write_P_10mV_VoltOutExt_rte(uint16 u1610mVVoltOutExt)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mV_VoltOutExt(u1610mVVoltOutExt);
  #endif
}
inline void HWIO_Write_P_10mV_VoltOutInt_rte(uint16 u1610mVVoltOutInt)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mV_VoltOutInt(u1610mVVoltOutInt);
  #endif
}
inline void HWIO_Write_P_10mA_CurrOut_rte(uint16 u1610mACurrOut)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mA_CurrOut(u1610mACurrOut);
  #endif
}
inline void HWIO_Write_P_10mA_CurrOutCali_rte(uint16 u1610mACurrOutCali)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mA_CurrOutCali(u1610mACurrOutCali);
  #endif
}
inline void HWIO_Write_P_10mA_AcsBus_rte(uint16 u1610mAAcsBus)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mA_AcsBus(u1610mAAcsBus);
  #endif
}
inline void HWIO_Write_P_10mA_AcsLocal_rte(uint16 u1610mAAcsLocal)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mA_AcsLocal(u1610mAAcsLocal);
  #endif
}
inline void HWIO_Write_P_1mV_VoltRef3V3_rte(uint16 u161mVVoltRef3V3)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1mV_VoltRef3V3(u161mVVoltRef3V3);
  #endif
}
inline void HWIO_Write_P_q12_VoltRefCaliFact_rte(uint16 u16q12VoltRefCaliFact)
{
  #if MG_RTE_MODULE
  Rte_Write_P_q12_VoltRefCaliFact(u16q12VoltRefCaliFact);
  #endif
}
inline void HWIO_Write_P_1Ohm_ResNtcOring_rte(uint16 u161OhmNtcOring)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1Ohm_ResNtcOring(u161OhmNtcOring);
  #endif
}
inline void HWIO_Write_P_1Ohm_ResNtcSr_rte(uint16 u161OhmNtcSr)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1Ohm_ResNtcSr(u161OhmNtcSr);
  #endif
}
inline void HWIO_Write_P_1mV_VoltNtcOring_rte(uint16 u161OhmNtcOring)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1mV_VoltNtcOring(u161OhmNtcOring);
  #endif
}
inline void HWIO_Write_P_1mV_VoltNtcSr_rte(uint16 u161OhmNtcSr)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1mV_VoltNtcSr(u161OhmNtcSr);
  #endif
}
inline void HWIO_Write_P_B_PORT_BULK_OK_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PORT_BULK_OK = u8State;
  #endif
}
inline void HWIO_Write_P_B_PORT_OVP_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PORT_OVP = u8State;
  #endif
}
inline void HWIO_Write_P_B_PORT_LLC_SWITCH_EN_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PORT_LLC_SWITCH_EN = u8State;
  #endif
}
inline void HWIO_Write_P_B_PORT_LLC_HALT_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PORT_LLC_HALT = u8State;
  #endif
}
inline void HWIO_Write_P_B_BL_EXIST_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_BL_EXIST = u8State;
  #endif
}
inline void HWIO_Rte_Write_P_BlFwVerMajor(uint8 u8Major)
{
  #if MG_RTE_MODULE
  Rte_Write_P_BlFwVerMajor(u8Major);
  #endif
}
inline void HWIO_Rte_Write_P_BlFwVerMinor(uint8 u8Minor)
{
  #if MG_RTE_MODULE
  Rte_Write_P_BlFwVerMinor(u8Minor);
  #endif
}
inline void HWIO_Rte_Write_P_BlFwVerDebug(uint8 u8Debug)
{
  #if MG_RTE_MODULE
  Rte_Write_P_BlFwVerDebug(u8Debug);
  #endif
}

#ifdef __cplusplus
  }
#endif
#endif  /* HWIO_RTE_H */

  
/*
 * End of file
 */
