/** *****************************************************************************
 * \file    acsctrl_rte.h
 * \brief   RTE interface for acsctrl.c
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

#ifndef ACSCTRL_RTE_H
#define ACSCTRL_RTE_H
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

#define Rte_Read_R_q12_CalibIshareGain(var)             ((**var) = RTE_u16q12CalibIshareGain)
#define Rte_Read_R_s16_10mA_CalibIshareOfs(var)         ((**var) = RTE_s1610mACalibIshareOfs)
#define Rte_Read_R_10mV_VoltOutExt(var)                 ((**var) = RTE_u1610mVVoltOutExt)

#define Rte_Write_P_10mV_MainVoltAdjCurrShare(var)      (RTE_s1610mVMainVoltAdjCurrShare = (var))

#if MG_RTE_MODULE
/* Read bits */
#define Rte_Read_R_B_LLC_EN                             RTE_B_LLC_EN
#define Rte_Read_R_B_SOFT_START                         RTE_B_LLC_SOFT_START
#define Rte_Read_R_B_LLC_STANDBY                        RTE_B_LLC_STANDBY
/* Write bits */
#define Rte_Write_R_B_LLC_SYNC_START_UP                 RTE_B_LLC_SYNC_START_UP
#else
/* Read bits */
#define Rte_Read_R_B_LLC_EN                             0
#define Rte_Read_R_B_SOFT_START                         0
#define Rte_Read_R_B_PORT_BULK_OK                       0
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Write bits */
inline void ACSCTRL_Write_P_B_LLC_SYNC_START_UP_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_LLC_SYNC_START_UP = u8State;
  #endif
}

/* Read data */
inline void ACSCTRL_Read_R_q12_CalibIshareGain_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_q12_CalibIshareGain(&var);
  #endif
}
inline void ACSCTRL_Read_R_s16_10mA_CalibIshareOfs_rte(sint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_s16_10mA_CalibIshareOfs(&var);
  #endif
}
inline void ACSCTRL_Read_R_10mV_VoltOutExt_rte(uint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_10mV_VoltOutExt(&var);
  #endif
}

/* Write data */
inline void ACSCTRL_Write_P_10mV_MainVoltAdjCurrShare_rte(sint16 s1610mVVoltAdjCurrShare)
{
  #if MG_RTE_MODULE
  Rte_Write_P_10mV_MainVoltAdjCurrShare(s1610mVVoltAdjCurrShare);
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* ACSCTRL_RTE_H */

  
/*
 * End of file
 */
