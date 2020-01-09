/** *****************************************************************************
 * \file    timectrl_rte.h
 * \brief   RTE interface for timectrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
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

#ifndef TIMECTRL_RTE_H
#define TIMECTRL_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

#include "rte.h"
		
/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
    
/***********************************************
 * Input
 **********************************************/

/***********************************************
 * Output
 **********************************************/
/* Registers */

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/
 
/***********************************************
 * Input
 **********************************************/
/* Flags */
#define RTE_Read_B_R_V1_ON                     (RTE_B_SEC_LLC_EN)      /* 1 = V1 ON */
#define RTE_Read_B_R_INPUT_OFF                 (RTE_B_COM_INPUT_OFF)
/* Variables */

#define RTE_Read_R_PmbusHoursUsed(var)         ((**var) = PMBUS_tData.u32HoursUsed.u32Val)
#define RTE_Read_R_PosTotal(var)               ((**var) = PMBUS_tData.u32PosTotal.u32Val)
#define RTE_Read_R_PosLast(var)               ((**var) = PMBUS_tData.u32PosLast.u32Val)

/***********************************************
 * Output
 **********************************************/
/* Flags */
#define RTE_Write_B_P_INPUT_OFF                 (RTE_B_COM_INPUT_OFF)
#define RTE_Write_B_P_HOURS_USED_UPDTING        (PMBUS_uDataUpdStatus.Bits.HOURS_USED_UPDTING)
#define RTE_Write_B_P_PSO_TOTAL_UPDTING         (PMBUS_uDataUpdStatus1.Bits.MFR_POS_TOTAL)
#define RTE_Write_B_P_PSO_LAST_UPDTING          (PMBUS_uDataUpdStatus1.Bits.MFR_POS_LAST)

/* Variables */

#define RTE_Write_P_u32PmbusDataCopy            (PMBUS_tData.u32DataCopy.u32Val)
#define RTE_Write_P_u32PmbusHoursUsed           (PMBUS_tData.u32HoursUsed.u32Val)
#define RTE_Write_P_u32PosTotal(var)            (PMBUS_tData.u32PosTotal.u32Val = var)
#define RTE_Write_P_u32PosLast(var)             (PMBUS_tData.u32PosLast.u32Val = var)
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
/*  Read   */
SINLINE uint8 TIMECTRL_RTE_Read_B_R_V1_ON(void)
{
	return RTE_Read_B_R_V1_ON;
}

SINLINE uint8 TIMECTRL_RTE_Read_B_R_INPUT_OFF(void)
{
	return RTE_Read_B_R_INPUT_OFF;
}


SINLINE void TIMECTRL_RTE_Read_R_PmbusHoursUsed(uint32 *var)
{
	RTE_Read_R_PmbusHoursUsed(&var);
}

SINLINE void TIMECTRL_RTE_Read_R_PosTotal(uint32 *var)
{
	RTE_Read_R_PosTotal(&var);
}

SINLINE void TIMECTRL_RTE_Read_R_PosLast(uint32 *var)
{
	RTE_Read_R_PosLast(&var);
}

/*  Write   */
SINLINE void TIMECTRL_RTE_Write_B_P_INPUT_OFF(uint8 u8State)
{
  RTE_Write_B_P_INPUT_OFF = u8State;
}

SINLINE void TIMECTRL_RTE_Write_P_vDataCopy(uint32 u32Data)
{
	RTE_Write_P_u32PmbusDataCopy = u32Data;
}

SINLINE void TIMECTRL_RTE_Write_P_vWrBitHoursUpd(uint8 u8Data)
{
	RTE_Write_B_P_HOURS_USED_UPDTING  = u8Data;
}

SINLINE void TIMECTRL_RTE_Write_B_P_PSO_TOTAL_UPDTING(uint8 u8Data)
{
	RTE_Write_B_P_PSO_TOTAL_UPDTING  = u8Data;
}

SINLINE void TIMECTRL_RTE_Write_B_P_PSO_LAST_UPDTING(uint8 u8Data)
{
	RTE_Write_B_P_PSO_LAST_UPDTING  = u8Data;
}

SINLINE void TIMECTRL_RTE_Write_P_vWrHoursUsed(uint32 u32Data)
{
  RTE_Write_P_u32PmbusHoursUsed = u32Data;
}

SINLINE void TIMECTRL_RTE_Write_P_u32PosTotal(uint32 u32Data)
{
  RTE_Write_P_u32PosTotal(u32Data);
}

SINLINE void TIMECTRL_RTE_Write_P_u32PosLast(uint32 u32Data)
{
  RTE_Write_P_u32PosLast(u32Data);
}



#ifdef __cplusplus
  }
#endif
#endif  /* TIMECTRL_RTE_H */

  
/*
 * End of file
 */
