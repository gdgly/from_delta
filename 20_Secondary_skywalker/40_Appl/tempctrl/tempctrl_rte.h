/** *****************************************************************************
 * \file    tempctrl_rte.h
 * \brief   RTE interface for tempctrl.c
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

#ifndef TEMPCTRL_RTE_H
#define TEMPCTRL_RTE_H
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

#define Rte_Read_R_1Ohm_ResNtc1(var)           ((**var) = RTE_u161OhmResNtc1Hwio)
#define Rte_Read_R_1Ohm_ResNtc2(var)           ((**var) = RTE_u161OhmResNtc2Hwio)
#define Rte_Read_R_1Ohm_ResNtc3(var)           ((**var) = RTE_u161OhmResNtc3Hwio)
#define Rte_Read_R_1Ohm_ResNtc4(var)           ((**var) = RTE_u161OhmResNtc4Hwio)
#define Rte_Write_P_1Ohm_ResNtc1Avg(var)       (RTE_u161OhmResNtc1Avg = (var))
#define Rte_Write_P_1Ohm_ResNtc2Avg(var)       (RTE_u161OhmResNtc2Avg = (var))
#define Rte_Write_P_1Ohm_ResNtc3Avg(var)       (RTE_u161OhmResNtc3Avg = (var))
#define Rte_Write_P_1Ohm_ResNtc4Avg(var)       (RTE_u161OhmResNtc4Avg = (var))

#if MG_RTE_MODULE
/* Read bits */
#define Rte_Read_R_B_OT_DISABLED                RTE_B_OT_DISABLED
/* Write bits */
#define Rte_Write_P_B_PSU_OT                    RTE_B_PSU_OT
#define Rte_Write_P_B_NTC_1_OT                  RTE_B_NTC_1_OT
#define Rte_Write_P_B_NTC_1_OTW                 RTE_B_NTC_1_OTW
#define Rte_Write_P_B_NTC_2_OT                  RTE_B_NTC_1_OT
#define Rte_Write_P_B_NTC_2_OTW                 RTE_B_NTC_1_OTW
#define Rte_Write_P_B_NTC_3_OT                  RTE_B_NTC_1_OT
#define Rte_Write_P_B_NTC_3_OTW                 RTE_B_NTC_1_OTW
#define Rte_Write_P_B_NTC_4_OT                  RTE_B_NTC_1_OT
#define Rte_Write_P_B_NTC_4_OTW                 RTE_B_NTC_1_OTW
#else
/* Read bits */
#define Rte_Read_R_B_OT_DISABLED                0
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Read data */
inline void TEMPCTRL_Rte_Read_R_1Ohm_ResNtc1(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_1Ohm_ResNtc1(&var);
  #endif
}

inline void TEMPCTRL_Rte_Read_R_1Ohm_ResNtc2(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_1Ohm_ResNtc2(&var);
  #endif
}

inline void TEMPCTRL_Rte_Read_R_1Ohm_ResNtc3(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_1Ohm_ResNtc3(&var);
  #endif
}

inline void TEMPCTRL_Rte_Read_R_1Ohm_ResNtc4(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_1Ohm_ResNtc4(&var);
  #endif
}

/* Write data */
inline void TEMPCTRL_Rte_Write_P_1Ohm_ResNtc1Avg(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1Ohm_ResNtc1Avg(var);
  #endif
}

inline void TEMPCTRL_Rte_Write_P_1Ohm_ResNtc2Avg(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1Ohm_ResNtc2Avg(var);
  #endif
}

inline void TEMPCTRL_Rte_Write_P_1Ohm_ResNtc3Avg(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1Ohm_ResNtc3Avg(var);
  #endif
}

inline void TEMPCTRL_Rte_Write_P_1Ohm_ResNtc4Avg(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_1Ohm_ResNtc4Avg(var);
  #endif
}

/* Write bits */
inline void TEMPCTRL_Rte_Write_P_B_PSU_OT(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PSU_OT = u8State;
  #endif
}

inline void TEMPCTRL_Rte_Write_P_B_NTC_1_OT(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_NTC_1_OT = u8State;
  #endif
}
inline void TEMPCTRL_Rte_Write_P_B_NTC_1_OTW(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_NTC_1_OTW = u8State;
  #endif
}

inline void TEMPCTRL_Rte_Write_P_B_NTC_2_OT(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_NTC_2_OT = u8State;
  #endif
}
inline void TEMPCTRL_Rte_Write_P_B_NTC_2_OTW(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_NTC_2_OTW = u8State;
  #endif
}

inline void TEMPCTRL_Rte_Write_P_B_NTC_3_OT(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_NTC_3_OT = u8State;
  #endif
}
inline void TEMPCTRL_Rte_Write_P_B_NTC_3_OTW(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_NTC_3_OTW = u8State;
  #endif
}

inline void TEMPCTRL_Rte_Write_P_B_NTC_4_OT(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_NTC_4_OT = u8State;
  #endif
}
inline void TEMPCTRL_Rte_Write_P_B_NTC_4_OTW(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_NTC_4_OTW = u8State;
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* TEMPCTRL_RTE_H */

  
/*
 * End of file
 */
