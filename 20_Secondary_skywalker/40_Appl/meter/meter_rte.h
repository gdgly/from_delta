/** *****************************************************************************
 * \file    meter_rte.h
 * \brief   RTE interface for meter.c
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

#ifndef METER_RTE_H
#define METER_RTE_H
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

#define Rte_Read_R_10mV_VoltOutExt(var)         ((**var) = RTE_u1610mVVoltOutExt)
#define Rte_Read_R_10mV_VoltOutInt(var)         ((**var) = RTE_u1610mVVoltOutInt)
#define Rte_Read_R_10mA_CurrOut(var)            ((**var) = RTE_u1610mACurrOut)
#define Rte_Read_R_q12_CalibVoltOutGain(var)    ((**var) = RTE_u16q12CalibVoltOutGain)
#define Rte_Read_R_q12_CalibCurrOutGain(var)    ((**var) = RTE_u16q12CalibCurrOutGain)

#define Rte_Write_P_10mV_VoltOutExtAvg(var)     (RTE_u1610mVVoltOutExtAvg = (var))
#define Rte_Write_P_10mV_VoltOutIntAvg(var)     (RTE_u1610mVVoltOutIntAvg = (var))
#define Rte_Write_P_10mA_CurrOutAvg(var)        (RTE_u1610mACurrOutAvg = (var))
#define Rte_Write_P_100mW_PwrOutAvg(var)        (RTE_u16100mWPwrOutAvg = (var))
#define Rte_Write_P_10mV_VoltOutExtAvgCom(var)  (RTE_u1610mVVoltOutExtAvgCom = (var))
#define Rte_Write_P_10mV_VoltOutIntAvgCom(var)  (RTE_u1610mVVoltOutIntAvgCom = (var))
#define Rte_Write_P_10mA_CurrOutAvgCom(var)     (RTE_u1610mACurrOutAvgCom = (var))
#define Rte_Write_P_100mW_PwrOutAvgCom(var)     (RTE_u16100mWPwrOutAvgCom = (var))

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* Read data */
inline void METER_Read_R_10mV_VoltOutExt_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mV_VoltOutExt(&var);
  #endif
}
inline void METER_Read_R_10mV_VoltOutInt_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mV_VoltOutInt(&var);
  #endif
}
inline void METER_Read_R_10mA_CurrOut_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mA_CurrOut(&var);
  #endif
}
inline void METER_Read_R_q12_CalibVoltOutGain_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_q12_CalibVoltOutGain(&var);
  #endif
}

inline void METER_Read_R_q12_CalibCurrOutGain_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_q12_CalibCurrOutGain(&var);
  #endif
}

/* Write data */
inline void METER_Write_P_10mV_VoltOutExtAvg_rte(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mV_VoltOutExtAvg(var);
  #endif
}
inline void METER_Write_P_10mV_VoltOutIntAvg_rte(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mV_VoltOutIntAvg(var);
  #endif
}
inline void METER_Write_P_10mA_CurrOutAvg_rte(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mA_CurrOutAvg(var);
  #endif
}
inline void METER_Write_P_100mW_PwrOutAvg_rte(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_100mW_PwrOutAvg(var);
  #endif
}
inline void METER_Write_P_10mV_VoltOutExtAvgCom_rte(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mV_VoltOutExtAvgCom(var);
  #endif
}
inline void METER_Write_P_10mV_VoltOutIntAvgCom_rte(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mV_VoltOutIntAvgCom(var);
  #endif
}
inline void METER_Write_P_10mA_CurrOutAvgCom_rte(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mA_CurrOutAvgCom(var);
  #endif
}
inline void METER_Write_P_100mW_PwrOutAvgCom_rte(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_100mW_PwrOutAvgCom(var);
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* METER_RTE_H */

  
/*
 * End of file
 */
