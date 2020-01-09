/** *****************************************************************************
 * \file    cali_rte.h
 * \brief   RTE interface for cali.c
 *
 * \section AUTHOR
 *    1. Jackie Chen
 *
 * \section SVN
 *  $Date: 2019-10-14 17:07:42 +0800 (Mon, 14 Oct 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 234 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#ifndef CALI_RTE_H
#define CALI_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

#include "pmbus_cfg.h"
#include "pmbus_rte.h"
#include "rte.h"
		
/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
#define MG_RTE_MODULE     1U
/***********************************************
 * Input
 **********************************************/
/* Flags */
#define RTE_Read_B_R_V1_ON                      (RTE_B_COM_V1_MONI_EN)
#define RTE_Read_B_R_VSB_ON 		                (RTE_B_COM_VSB_MONI_EN)
#define Rte_Read_B_R_VIN_OK                     (RTE_B_PRI_VIN_OK)
/* Definitions */

#define CALI_RTE_R_sData          RTE_CALI_sData
    
#define Rte_Read_R_u1610mAIoutAvg(var)          ((**var) = RTE_Sec.u1610mAIoutAvg)
#define Rte_Read_R_u1610mVVoutAvg(var)          ((**var) = RTE_Sec.u1610mVIntV1Avg)
/***********************************************
 * Output
 **********************************************/
/* Flags */

/* Registers */
#define CALI_RTE_W_sData                    RTE_CALI_sData
#define Rte_Write_P_u16IShareGain(var)      (RTE_u16IShareGain.u16Val = var)
#define Rte_Write_P_u16IShareOfs(var)       (RTE_u16IShareOfs.s16Val = var)
#define Rte_Write_P_u16V1CurrentGain(var)   (RTE_u16V1CurrentGain.u16Val = var)
#define Rte_Write_P_u16VoutIntVsbFast(var)  (RTE_u16VoutIntVsbFast = var)
#define Rte_Write_P_u16VoutExtVsbFast(var)  (RTE_u16VoutExtVsbFast = var)
#define Rte_Write_P_u16IoutVsbFast(var)     (RTE_u16IoutVsbFast = var)

#define Rte_Write_P_uCaliV1Amp(var)         (RTE_uCaliV1Amp.s16Val = (var))
#define Rte_Write_P_uCaliV1Ofs(var)         (RTE_uCaliV1Ofs.s16Val = (var))
#define Rte_Write_P_uCaliI1Amp(var)         (RTE_uCaliI1Amp.s16Val = (var))
#define Rte_Write_P_uCaliI1Ofs(var)         (RTE_uCaliI1Ofs.s16Val = (var))

/*******************************************************************************
 * Global data types (public typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/
#define CALI_RTE_VIN_LOW_LINE           RTE_VIN_LOW_LINE
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
SINLINE uint8 CALI_Rte_Read_B_R_V1_ON(void)
{
	return RTE_Read_B_R_V1_ON;
}

SINLINE uint8 CALI_Rte_Read_B_R_VSB_ON(void)
{
	return RTE_Read_B_R_VSB_ON;
}

SINLINE uint8 CALI_Rte_Read_B_R_VIN_OK(void)
{
	return Rte_Read_B_R_VIN_OK;
}

SINLINE void CALI_Rte_Read_R_u1610mAIoutAvg(WORD_VAL *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_u1610mAIoutAvg(&var);
#endif
}
inline void CALI_Rte_Read_R_u1610mVVoutAvg(WORD_VAL *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_u1610mVVoutAvg(&var);
#endif
}



inline void CALI_Rte_Write_P_u16IShareGain(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16IShareGain(u16Data);
  #endif
}
inline void CALI_Rte_Write_P_u16IShareOfs(sint16 s16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16IShareOfs(s16Data);
  #endif
}
inline void CALI_Rte_Write_P_u16V1CurrentGain(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16V1CurrentGain(u16Data);
  #endif
}
SINLINE void CALI_Rte_Write_P_u16VoutIntVsbFast(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16VoutIntVsbFast(u16Data);
  #endif
}
SINLINE void CALI_Rte_Write_P_u16VoutExtVsbFast(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16VoutExtVsbFast(u16Data);
  #endif
}
SINLINE void CALI_Rte_Write_P_u16IoutVsbFast(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16IoutVsbFast(u16Data);
  #endif
}
SINLINE void CALI_Rte_Write_P_u16CaliV1Amp(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uCaliV1Amp(u16Data);
  #endif
}
SINLINE void CALI_Rte_Write_P_u16CaliV1Ofs(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uCaliV1Ofs(u16Data);
  #endif
}
SINLINE void CALI_Rte_Write_P_u16CaliI1Amp(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uCaliI1Amp(u16Data);
  #endif
}
SINLINE void CALI_Rte_Write_P_u16CaliI1Ofs(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uCaliI1Ofs(u16Data);
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* CALI_RTE_H */


/*
 * End of file
 */





