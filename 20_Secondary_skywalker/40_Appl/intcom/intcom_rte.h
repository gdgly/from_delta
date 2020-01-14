/** *****************************************************************************
 * \file    intcom_rte.h
 * \brief   RTE interface for intcom.c
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

#ifndef INTCOM_RTE_H
#define INTCOM_RTE_H
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

#define Rte_Read_R_uLlcStatus00(var)          ((**var) = RTE_uLlcStatus00)
#define Rte_Read_R_uLlcStatus01(var)          ((**var) = RTE_uLlcStatus01)
#define Rte_Read_R_uLlcStatus02(var)          ((**var) = RTE_uLlcStatus02)
#define Rte_Read_R_uTempStatus00(var)         ((**var) = RTE_uTempStatus00)
#define Rte_Read_R_u16DebugData0(var)         ((**var) = RTE_u16DebugData0)
#define Rte_Read_R_u16DebugData1(var)         ((**var) = RTE_u16DebugData1)
#define Rte_Read_R_u16DebugData2(var)         ((**var) = RTE_u16DebugData2)
#define Rte_Read_R_u1610mVVoltOutExtAvg(var)  ((**var) = RTE_u1610mVVoltOutExtAvgCom)
#define Rte_Read_R_u1610mVVoltOutIntAvg(var)  ((**var) = RTE_u1610mVVoltOutIntAvgCom)
#define Rte_Read_R_u1610mACurrOutAvg(var)     ((**var) = RTE_u1610mACurrOutAvgCom)
#define Rte_Read_R_u16100mWPwrOutAvg(var)     ((**var) = RTE_u16100mWPwrOutAvgCom)
#define Rte_Read_R_u161mVVoltNtc1(var)        ((**var) = RTE_u161mVVoltNtc1Hwio)
#define Rte_Read_R_u161mVVoltNtc2(var)        ((**var) = RTE_u161mVVoltNtc2Hwio)
#define Rte_Read_R_u161mVIshareAvg(var)       ((**var) = RTE_u1610mAAcsBus)
#define Rte_Read_R_u161mVILocalAvg(var)       ((**var) = RTE_u1610mAAcsLocal)
#define Rte_Read_R_u8BlFwVerMajor(var)        ((**var) = RTE_u8BlFwVerMajor)
#define Rte_Read_R_u8BlFwVerMinor(var)        ((**var) = RTE_u8BlFwVerMinor)
#define Rte_Read_R_u8BlFwVerDebug(var)        ((**var) = RTE_u8BlFwVerDebug)

#define Rte_Write_P_uComStatus00(var)               (RTE_uComStatus00 = (var))
#define Rte_Write_P_u16DebugData0(var)              (RTE_u16DebugData0 = (var))
#define Rte_Write_P_u16q12CalibVoltOutGain(var)     (RTE_u16q12CalibVoltOutGain = (var))
#define Rte_Write_P_u16q12CalibCurrOutGain(var)     (RTE_u16q12CalibCurrOutGain = (var))
#define Rte_Write_P_u16q12CalibIshareGain(var)      (RTE_u16q12CalibIshareGain = (var))
#define Rte_Write_P_s1610mACalibIshareOfs(var)      (RTE_s1610mACalibIshareOfs = (var))
#define Rte_Write_P_u16100mHzVoltInFreq(var)        (RTE_u16100mHzVoltInFreq = (var))
#define Rte_Write_P_s16CalibVoltOutAmp(var)         (RTE_s16CalibVoltOutAmp = (var))
#define Rte_Write_P_s16CalibCurrOutAmp(var)         (RTE_s16CalibCurrOutAmp = (var))
#define Rte_Write_P_s16CalibVoltOutOfs(var)         (RTE_s16CalibVoltOutOfs = (var))
#define Rte_Write_P_s16CalibCurrOutOfs(var)         (RTE_s16CalibCurrOutOfs = (var))

#if MG_RTE_MODULE
/* Write bits */
#define Rte_Write_R_B_LLC_COM_HALT            RTE_B_LLC_COM_HALT
#define Rte_Write_R_B_BL_MODE                 RTE_B_BL_MODE
#define Rte_Write_P_B_LLC_FAULT_CLR           RTE_B_LLC_FAULT_CLR
#define Rte_Write_P_B_VIN_LINE                RTE_B_PRIM_VIN_LINE
#define Rte_Write_P_B_PRIM_VIN_LOST           RTE_B_PRIM_VIN_LOST
#define Rte_Write_P_B_LLC_OVP_TEST            RTE_B_LLC_OVP_TEST
#else
/* Read bits */
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Read data */
inline void INTCOM_Rte_Read_R_uLlcStatus00(GLOBAL_U_U16BIT *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uLlcStatus00(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_uLlcStatus01(GLOBAL_U_U16BIT *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uLlcStatus01(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_uLlcStatus02(GLOBAL_U_U16BIT *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uLlcStatus02(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_uTempStatus00(GLOBAL_U_U8BIT *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uTempStatus00(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u16DebugData0(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u16DebugData0(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u16DebugData1(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u16DebugData1(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u16DebugData2(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u16DebugData2(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u1610mVVoltOutExtAvg(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u1610mVVoltOutExtAvg(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u1610mACurrOutAvg(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u1610mACurrOutAvg(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u16100mWPwrOutAvg(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u16100mWPwrOutAvg(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u161mVVoltNtc1(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u161mVVoltNtc1(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u161mVVoltNtc2(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u161mVVoltNtc2(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u1610mVVoltOutIntAvg(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u1610mVVoltOutIntAvg(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u161mVIshareAvg(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u161mVIshareAvg(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u161mVILocalAvg(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u161mVILocalAvg(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u8BlFwVerMajor(uint8 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u8BlFwVerMajor(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u8BlFwVerMinor(uint8 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u8BlFwVerMinor(&var);
  #endif
}
inline void INTCOM_Rte_Read_R_u8BlFwVerDebug(uint8 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u8BlFwVerDebug(&var);
  #endif
}

/* Write data */
inline void INTCOM_Rte_Write_P_uComStatus00(GLOBAL_U_U16BIT var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uComStatus00(var);
  #endif
}
inline void INTCOM_Rte_Write_P_u16DebugData0(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16DebugData0(var);
  #endif
}
inline void INTCOM_Rte_Write_P_u16q12CalibVoltOutGain(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16q12CalibVoltOutGain(var);
  #endif
}
inline void INTCOM_Rte_Write_P_u16q12CalibCurrOutGain(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16q12CalibCurrOutGain(var);
  #endif
}
inline void INTCOM_Rte_Write_P_u16q12CalibIshareGain(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16q12CalibIshareGain(var);
  #endif
}
inline void INTCOM_Rte_Write_P_s1610mACalibIshareOfs(sint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_s1610mACalibIshareOfs(var);
  #endif
}

/* Write bits */
inline void INTCOM_Rte_Write_P_B_PFC_HALT(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_LLC_COM_HALT = u8State;
  #endif
}
inline void INTCOM_Rte_Write_P_B_BL_MODE(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_BL_MODE = u8State;
  #endif
}
inline void INTCOM_Rte_Write_P_B_LLC_FAULT_CLR(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_FAULT_CLR = u8State;
  #endif
}
inline void INTCOM_Rte_Write_P_B_VIN_LINE(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_VIN_LINE = u8State;
  #endif
}
inline void INTCOM_Rte_Write_P_B_PRIM_VIN_LOST(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PRIM_VIN_LOST = u8State;
  #endif
}
inline void INTCOM_Rte_Write_P_B_LLC_OVP_TEST(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OVP_TEST = u8State;
  #endif
}
inline void INTCOM_Rte_Write_P_u16100mHzVoltInFreq(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16100mHzVoltInFreq(u16Data);
  #endif
}
inline void INTCOM_Rte_Write_P_s16CalibVoltOutAmp(sint16 s16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_s16CalibVoltOutAmp(s16Data);
  #endif
}
inline void INTCOM_Rte_Write_P_s16CalibCurrOutAmp(sint16 s16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_s16CalibCurrOutAmp(s16Data);
  #endif
}
inline void INTCOM_Rte_Write_P_s16CalibVoltOutOfs(sint16 s16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_s16CalibVoltOutOfs(s16Data);
  #endif
}
inline void INTCOM_Rte_Write_P_s16CalibCurrOutOfs(sint16 s16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_s16CalibCurrOutOfs(s16Data);
  #endif
}

#ifdef __cplusplus
  }
#endif
#endif  /* INTCOM_RTE_H */

  
/*
 * End of file
 */
