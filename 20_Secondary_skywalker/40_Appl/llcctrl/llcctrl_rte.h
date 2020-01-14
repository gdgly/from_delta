/** *****************************************************************************
 * \file    llcctrl_rte.h
 * \brief   RTE interface for llcctrl.c
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

#ifndef LLCCTRL_RTE_H
#define LLCCTRL_RTE_H
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

#define Rte_Read_R_q12_VoltRefCaliFact(var)       ((**var) = RTE_u16q12VoltRefCaliFact)
#define Rte_Read_R_q12_CalibVoltOutGain(var)      ((**var) = RTE_u16q12CalibVoltOutGain)
#define Rte_Read_R_q12_CalibCurrOutGain(var)      ((**var) = RTE_u16q12CalibCurrOutGain)
#define Rte_Read_R_100mHz_VoltInFreq(var)         ((**var) = RTE_u16100mHzVoltInFreq)
#define Rte_Read_R_10mV_MainVoltAdjCurrShare(var) ((**var) = RTE_s1610mVMainVoltAdjCurrShare)

#if MG_RTE_MODULE
/* Read bits */
#define Rte_Read_R_B_LLC_EN                     RTE_B_LLC_EN
#define Rte_Read_R_B_VIN_LINE                   RTE_B_PRIM_VIN_LINE
#define Rte_Read_R_B_LLC_OVP                    RTE_B_LLC_OVP
#define Rte_Read_R_B_LLC_OVP_TEST               RTE_B_LLC_OVP_TEST
#define Rte_Read_R_B_LLC_OC_LATCH_CLR           RTE_B_LLC_OC_LATCH_CLR

/* Write bits */
#define Rte_Write_P_B_LLC_CURR_LIMIT            RTE_B_LLC_CURR_LIMIT
#define Rte_Write_P_B_LLC_SOFT_START            RTE_B_LLC_SOFT_START
#define Rte_Write_P_B_LLC_OCP_CT                RTE_B_LLC_OCP_CT
#else
/* Read bits */
#define Rte_Read_R_B_LLC_EN                     0
#define Rte_Read_R_B_VIN_LINE                   0
#define Rte_Read_R_B_LLC_OVP                    0
#define Rte_Read_R_B_LLC_OVP_TEST               0
Rte_Read_R_B_LLC_OC_LATCH_CLR                   0
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Read data */
inline void LLCCTRL_Read_R_q12_VoltRefCaliFact_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_q12_VoltRefCaliFact(&var);
  #endif
}

inline void LLCCTRL_Read_R_q12_CalibVoltOutGain_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_q12_CalibVoltOutGain(&var);
  #endif
}

inline void LLCCTRL_Read_R_q12_CalibCurrOutGain_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_q12_CalibCurrOutGain(&var);
  #endif
}

inline void LLCCTRL_Read_R_100mHz_VoltInFreq_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_100mHz_VoltInFreq(&var);
  #endif
}

inline void LLCCTRL_Read_R_10mV_MainVoltAdjCurrShare_rte(sint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mV_MainVoltAdjCurrShare(&var);
  #endif
}

/* Write bits */
inline void LLCCTRL_Write_P_B_LLC_CURR_LIMIT_EN_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_CURR_LIMIT = u8State;
  #endif
}

inline void LLCCTRL_Write_P_B_LLC_SOFT_START_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_SOFT_START = u8State;
  #endif
}

inline void LLCCTRL_Write_P_B_LLC_OCP_CT_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_LLC_OCP_CT = u8State;
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* LLCCTRL_RTE_H */

  
/*
 * End of file
 */
