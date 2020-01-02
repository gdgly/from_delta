/** *****************************************************************************
 * \file    mem_rte.h
 * \brief   RTE interface for mem.c
 *
 * \section AUTHOR
 *    1. Jackie Chen
 *
 * \section SVN
 *  $Date: 2019-02-19 14:24:47 +0800 (Tue, 19 Feb 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 142 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#ifndef MEM_RTE_H
#define MEM_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_RTE_MODULE           (1u)

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
/***********************************************
 * Input
 **********************************************/
		
#define RTE_Read_B_R_V1_TRIM                      (RTE_B_PSUCTRL_V1_TRIM)
#define RTE_Read_B_R_VSB_TRIM                     (RTE_B_PSUCTRL_VSB_TRIM)
#define RTE_Read_B_R_PRI_REV_UPDATE               (RTE_B_PRI_REV_UPDATE)
#define RTE_Read_B_R_SEC_REV_UPDATE               (RTE_B_SEC_REV_UPDATE) 
#define RTE_Read_B_R_AC_OFFSET_NEED_SAVE          (RTE_B_COM_AC_OFFSET_NEED_SAVE)
#define Rte_Read_B_R_MFR_INFO_UPDATE              (PMBUS_uSysStatu0.Bits.MFR_INFO_UPDATE)  

/* Variables */
#define Rte_Read_R_u16TrimV1Gain(var)             ((**var) = RTE_u16TrimV1Gain.u16Val)
#define Rte_Read_R_u16TrimVsbGain(var)            ((**var) = RTE_u16TrimVsbGain.u16Val)
#define Rte_Read_R_u32PmbusFwRevSec(var)          ((**var) = RTE_u32PmbusFwRevSec1.u32Val)
#define Rte_Read_R_u32PmbusFwRevPri(var)          ((**var) = RTE_u32PmbusFwRevPri1.u32Val)		
#define Rte_Read_R_u32PmbusBlRevSec(var)          ((**var) = RTE_u32PmbusBootFwRevSec1.u32Val)
#define Rte_Read_R_u32PmbusBlRevPri(var)          ((**var) = RTE_u32PmbusBootFwRevPri1.u32Val)	
#define Rte_Read_R_uAcOffset(var)                 ((**var) = RTE_Pri.u16AcOffset)
#define Rte_Read_R_au8MfrInfo(var,index)          ((*(*var+index)) = *(&RTE_au8MfrData[0][0] + index))

/***********************************************
 * Output
 **********************************************/
/* Flags */
#define Rte_Write_B_R_V1_TRIM                    (RTE_B_PSUCTRL_V1_TRIM)
#define Rte_Write_B_R_VSB_TRIM                   (RTE_B_PSUCTRL_VSB_TRIM)
#define Rte_Write_B_R_PRI_REV_UPDATE             (RTE_B_PRI_REV_UPDATE)
#define Rte_Write_B_R_SEC_REV_UPDATE             (RTE_B_SEC_REV_UPDATE)
#define RTE_Write_B_P_AC_OFFSET_SAVEED           (RTE_B_COM_AC_OFFSET_SAVEED) 
#define RTE_Write_B_P_AC_OFFSET_NEED_SAVE        (RTE_B_COM_AC_OFFSET_NEED_SAVE) 
#define Rte_Write_B_P_MFR_INFO_UPDATE            (PMBUS_uSysStatu0.Bits.MFR_INFO_UPDATE) 
/* Registers */
#define Rte_Write_R_s16AcOffset                  (RTE_Pri.u16AcOffset.s16Val)
#define Rte_Write_R_u16TrimV1Gain                (RTE_u16TrimV1Gain.u16Val)
#define Rte_Write_R_u16TrimVsbGain               (RTE_u16TrimVsbGain.u16Val)
#define Rte_Write_R_u32PmbusFwRevSec             (RTE_u32PmbusFwRevSec1.u32Val)
#define Rte_Write_R_u32PmbusFwRevPri             (RTE_u32PmbusFwRevPri1.u32Val)
#define Rte_Write_R_u32PmbusFwRevCom             (RTE_u32PmbusFwRevCom.u32Val)
#define Rte_Write_R_u32PmbusBlRevSec             (RTE_u32PmbusBootFwRevSec1.u32Val)
#define Rte_Write_R_u32PmbusBlRevPri             (RTE_u32PmbusBootFwRevPri1.u32Val)
#define Rte_Write_R_u32PmbusBlRevCom             (RTE_u32PmbusBootFwRevCom.u32Val)
#define Rte_Write_P_u8MfrInfo(var,index)         (*(&RTE_au8MfrData[0][0] + index) = var)
#define RTE_Write_P_u16TrimV1GainAct             (RTE_u16TrimV1GainAct.u16Val)
/*******************************************************************************
 * Global data types (public typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

SINLINE uint8 MEM_RTE_Read_B_R_AC_OFFSET_NEED_SAVE(void)
{
	return RTE_Read_B_R_AC_OFFSET_NEED_SAVE;
}
SINLINE uint8 MEM_RTE_Read_B_R_V1_TRIM(void)
{
	return RTE_Read_B_R_V1_TRIM;
}
SINLINE uint8 MEM_RTE_Read_B_R_VSB_TRIM(void)
{
	return RTE_Read_B_R_VSB_TRIM;
}
SINLINE uint8 MEM_RTE_Read_B_R_PRI_REV_UPDATE(void)
{
	return RTE_Read_B_R_PRI_REV_UPDATE;
}
SINLINE uint8 MEM_RTE_Read_B_R_SEC_REV_UPDATE(void)
{
	return RTE_Read_B_R_SEC_REV_UPDATE;
}
SINLINE uint8 MEM_Rte_Read_B_R_MFR_INFO_UPDATE(void)
{
  #if MG_RTE_MODULE
  return Rte_Read_B_R_MFR_INFO_UPDATE;
  #endif
}
SINLINE void MEM_RTE_Read_R_uTrimV1Gain(uint16 *var)
{
	Rte_Read_R_u16TrimV1Gain(&var);
}
SINLINE void MEM_RTE_Read_R_uTrimVsbGain(uint16 *var)
{
	Rte_Read_R_u16TrimVsbGain(&var);
}
SINLINE void MEM_RTE_Read_R_uPmbusFwRevSec(uint32 *var)
{
	Rte_Read_R_u32PmbusFwRevSec(&var);
}
SINLINE void MEM_RTE_Read_R_uPmbusFwRevPri(uint32 *var)
{
	Rte_Read_R_u32PmbusFwRevPri(&var);
}
SINLINE void MEM_RTE_Read_R_uPmbusBlRevSec(uint32 *var)
{
	Rte_Read_R_u32PmbusBlRevSec(&var);
}
SINLINE void MEM_RTE_Read_R_uPmbusBlRevPri(uint32 *var)
{
	Rte_Read_R_u32PmbusBlRevPri(&var);
}

inline void MEM_Rte_Read_R_uAcOffset(WORD_VAL *var)
{
  Rte_Read_R_uAcOffset(&var);
}
SINLINE void MEM_Rte_Read_R_au8MfrInfo(uint8 *var)
{
  #if MG_RTE_MODULE
  uint8 u8Loop;
  
  for(u8Loop=0;u8Loop<102;u8Loop++)
  {
    Rte_Read_R_au8MfrInfo(&var,u8Loop);
  }
  #endif
}

/* Write */
SINLINE void MEM_Rte_Write_B_R_V1_TRIM(uint8 u8Status)
{
	Rte_Write_B_R_V1_TRIM = u8Status;
}
SINLINE void MEM_Rte_Write_B_R_VSB_TRIM(uint8 u8Status)
{
	Rte_Write_B_R_VSB_TRIM = u8Status;
}
SINLINE void MEM_Rte_Write_B_R_PRI_REV_UPDATE(uint8 u8Status)
{
	Rte_Write_B_R_PRI_REV_UPDATE = u8Status;
}
SINLINE void MEM_Rte_Write_B_R_SEC_REV_UPDATE(uint8 u8Status)
{
	Rte_Write_B_R_SEC_REV_UPDATE = u8Status;
}
SINLINE void MONCTRL_Rte_Write_B_P_AC_OFFSET_SAVEED(uint8 u8Status)
{
  RTE_Write_B_P_AC_OFFSET_SAVEED =  u8Status;
}
SINLINE void MONCTRL_Rte_Write_B_P_AC_OFFSET_NEED_SAVE(uint8 u8Status)
{
  RTE_Write_B_P_AC_OFFSET_NEED_SAVE =  u8Status;
}
SINLINE void MONCTRL_Rte_Write_B_P_MFR_INFO_UPDATE(uint8 u8Status)
{
  #if MG_RTE_MODULE
  Rte_Write_B_P_MFR_INFO_UPDATE =  u8Status;
  #endif
}


/* Registers */

SINLINE void MONCTRL_Rte_Write_R_s16AcOffset(sint16 s16Data)
{
  Rte_Write_R_s16AcOffset =  s16Data;
}
SINLINE void MONCTRL_Rte_Write_P_u16TrimV1Gain(uint16 u16Data)
{
  Rte_Write_R_u16TrimV1Gain =  u16Data;
}
SINLINE void MONCTRL_Rte_Write_P_u16TrimVsbGain(uint16 u16Data)
{
  Rte_Write_R_u16TrimVsbGain =  u16Data;
}
SINLINE void MONCTRL_Rte_Write_R_u32PmbusFwRevSec(uint32 u32Data)
{
  Rte_Write_R_u32PmbusFwRevSec =  u32Data;
}
SINLINE void MONCTRL_Rte_Write_R_u32PmbusFwRevPri(uint32 u32Data)
{
  Rte_Write_R_u32PmbusFwRevPri =  u32Data;
}
SINLINE void MONCTRL_Rte_Write_R_u32PmbusFwRevCom(uint32 u32Data)
{
  Rte_Write_R_u32PmbusFwRevCom =  u32Data;
}

SINLINE void MONCTRL_Rte_Write_R_u32PmbusBlRevSec(uint32 u32Data)
{
  Rte_Write_R_u32PmbusBlRevSec =  u32Data;
}
SINLINE void MONCTRL_Rte_Write_R_u32PmbusBlRevPri(uint32 u32Data)
{
  Rte_Write_R_u32PmbusBlRevPri =  u32Data;
}
SINLINE void MONCTRL_Rte_Write_R_u32PmbusBlRevCom(uint32 u32Data)
{
  Rte_Write_R_u32PmbusBlRevCom =  u32Data;
}
SINLINE void MONCTRL_Rte_Write_P_u8MfrInfo(uint8 var, uint8 index)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u8MfrInfo(var,index);
  #endif
}
SINLINE void MONCTRL_Rte_Write_P_u16TrimV1GainAct(uint16 u16Data)
{
  #if MG_RTE_MODULE
	RTE_Write_P_u16TrimV1GainAct = u16Data;
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* MEM_RTE_H */


/*
 * End of file
 */





