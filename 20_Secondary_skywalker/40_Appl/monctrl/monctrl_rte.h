/** *****************************************************************************
 * \file    monctrl_rte.h
 * \brief   RTE interface for monctrl.c
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

#ifndef MONCTRL_RTE_H
#define MONCTRL_RTE_H
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

#define Rte_Read_R_10mV_VoltOutExt(var)       ((**var) = RTE_u1610mVVoltOutExt)
#define Rte_Read_R_10mV_VoltOutInt(var)       ((**var) = RTE_u1610mVVoltOutInt)
#define Rte_Read_R_10mA_CurrOut(var)          ((**var) = RTE_u1610mACurrOut)
#define Rte_Read_R_10mA_CurrOutCali(var)      ((**var) = RTE_u1610mACurrOutCali)
#define Rte_Read_R_10mA_CurrOutAvg(var)       ((**var) = RTE_u1610mACurrOutAvg)
#define Rte_Read_R_100mW_PwrOutAvg(var)       ((**var) = RTE_u16100mWPwrOutAvg)


#if MG_RTE_MODULE
/* Read bits */
#define Rte_Read_R_B_LLC_EN                   RTE_B_LLC_EN
#define Rte_Read_R_B_PORT_OVP                 RTE_B_PORT_OVP
#define Rte_Read_R_B_VIN_LINE                 RTE_B_PRIM_VIN_LINE
#define Rte_Read_R_B_LLC_CURR_LIMIT           RTE_B_LLC_CURR_LIMIT
#define Rte_Read_R_B_LLC_FAULT_CLR            RTE_B_LLC_FAULT_CLR
#define Rte_Read_R_B_LLC_OV_LATCH_CLR         RTE_B_LLC_OV_LATCH_CLR
#define Rte_Read_R_B_LLC_UV_LATCH_CLR         RTE_B_LLC_UV_LATCH_CLR
#define Rte_Read_R_B_LLC_OC_LATCH_CLR         RTE_B_LLC_OC_LATCH_CLR
#define Rte_Read_R_B_LLC_OPP_LATCH_CLR        RTE_B_LLC_OPP_LATCH_CLR
#define Rte_Read_R_B_LLC_OCP_CT               RTE_B_LLC_OCP_CT

/* Write bits */
#define Rte_Write_P_B_LLC_OUT_OVP             RTE_B_LLC_OVP
#define Rte_Write_P_B_LLC_OUT_OVW             RTE_B_LLC_OVW
#define Rte_Write_P_B_LLC_OUT_UVP             RTE_B_LLC_UVP
#define Rte_Write_P_B_LLC_OUT_UVW             RTE_B_LLC_UVW
#define Rte_Write_P_B_LLC_OUT_OCP             RTE_B_LLC_OCP
#define Rte_Write_P_B_LLC_OUT_OCW             RTE_B_LLC_OCW
#define Rte_Write_P_B_LLC_OUT_OPP             RTE_B_LLC_OPP
#else
/* Read bits */
#define Rte_Read_R_B_LLC_EN                   0
#define Rte_Read_R_B_PORT_OVP                 0
#define Rte_Read_R_B_VIN_LINE                 0
#define Rte_Read_R_B_LLC_CURR_LIMIT           0
#define Rte_Read_R_B_LLC_FAULT_CLR            0
#define Rte_Read_R_B_LLC_OV_LATCH_CLR         0
#define Rte_Read_R_B_LLC_UV_LATCH_CLR         0
#define Rte_Read_R_B_LLC_OC_LATCH_CLR         0
#define Rte_Read_R_B_LLC_OPP_LATCH_CLR        0
#define Rte_Read_R_B_LLC_OCP_CT               0
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Read data */
inline void MONCTRL_Read_R_10mV_VoltOutExt_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mV_VoltOutExt(&var);
  #endif
}
inline void MONCTRL_Read_R_10mV_VoltOutInt_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mV_VoltOutInt(&var);
  #endif
}
inline void MONCTRL_Read_R_10mA_CurrOut_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mA_CurrOut(&var);
  #endif
}
inline void MONCTRL_Read_R_10mA_CurrOutCali_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mA_CurrOutCali(&var);
  #endif
}
inline void MONCTRL_Read_R_10mA_CurrOutAvg_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mA_CurrOutAvg(&var);
  #endif
}
inline void MONCTRL_Read_R_100mW_PwrOutAvg_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_100mW_PwrOutAvg(&var);
  #endif
}

/* Write bits */
inline void MONCTRL_Write_P_B_LLC_OUT_OVP_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OUT_OVP = u8State;
  #endif
}
inline void MONCTRL_Write_P_B_LLC_OUT_OVW_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OUT_OVW = u8State;
  #endif
}
inline void MONCTRL_Write_P_B_LLC_OUT_UVP_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OUT_UVP = u8State;
  #endif
}
inline void MONCTRL_Write_P_B_LLC_OUT_UVW_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OUT_UVW = u8State;
  #endif
}
inline void MONCTRL_Write_P_B_LLC_OUT_OCP_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OUT_OCP = u8State;
  #endif
}
inline void MONCTRL_Write_P_B_LLC_OUT_OCW_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OUT_OCW = u8State;
  #endif
}
inline void MONCTRL_Write_P_B_LLC_OUT_OPP_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OUT_OPP = u8State;
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* MONCTRL_RTE_H */

  
/*
 * End of file
 */
