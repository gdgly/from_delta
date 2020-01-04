/*******************************************************************************
 * \file    blabox_rte.h
 * \brief   RTE interface for blabox.c
 *
 * \section AUTHOR
 *    1. Jeff.Zhou
 *
 * \section SVN
 *  $Date: 2018-11-09 11:10:05 +0800 (Fri, 09 Nov 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 115 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef BLABOX_RTE_H
#define BLABOX_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif
		
#include "rte.h"
#include "fanctrl_api.h"

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
#define MG_RTE_MODULE               1u
/***********************************************
 * Input
 **********************************************/
/* Flags */
#define Rte_Read_B_R_AUX_MODE             (PMBUS_uSysStatu0.Bits.AUX_MODE)
#define Rte_Read_B_R_VOUT_OV_FAULT        (PMBUS_tStatus.u8StatusVoutP0.Bits.VOUT_OV_FAULT)
#define Rte_Read_B_R_VOUT_UV_FAULT        (PMBUS_tStatus.u8StatusVoutP0.Bits.VOUT_UV_FAULT)
#define Rte_Read_B_R_IOUT_OC_WARN         (PMBUS_tStatus.u8StatusIoutP0.Bits.IOUT_OC_WARN)	
#define Rte_Read_B_R_IOUT_OC_FAULT        (PMBUS_tStatus.u8StatusIoutP0.Bits.IOUT_OC_FAULT)	

#define Rte_Read_B_R_VSB_OV_FAULT         (PMBUS_tStatus.u8StatusVoutP1.Bits.VOUT_OV_FAULT)
#define Rte_Read_B_R_VSB_UV_FAULT         (PMBUS_tStatus.u8StatusVoutP1.Bits.VOUT_UV_FAULT)
#define Rte_Read_B_R_ISB_OC_FAULT         (PMBUS_tStatus.u8StatusIoutP1.Bits.IOUT_OC_FAULT)	
		
#define Rte_Read_B_R_VIN_UV_FAULT         (PMBUS_tStatus.u8StatusInputP0.Bits.VIN_UV_FAULT)	
#define Rte_Read_B_R_VIN_OV_FAULT         (PMBUS_tStatus.u8StatusInputP0.Bits.VIN_OV_FAULT)	
#define Rte_Read_B_R_FAN_1_FAULT          (PMBUS_tStatus.u8StatusFan12P0.Bits.FAN_1_FAULT)	
#define Rte_Read_B_R_FAN_2_FAULT          (PMBUS_tStatus.u8StatusFan12P0.Bits.FAN_2_FAULT)	

#define Rte_Read_B_R_OT_FAULT             (PMBUS_tStatus.u8StatusTempP0.Bits.OT_FAULT)
#define Rte_Read_B_R_OT_WARN              (PMBUS_tStatus.u8StatusTempP0.Bits.OT_WARN)	

#define Rte_Read_B_R_UINT_OFF             (PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF)
#define Rte_Read_B_R_POWER_GOOD_N         (PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N)		
#define Rte_Read_B_R_IOUT_POUT_F_OR_W     (PMBUS_tStatus.u16StatusWordP0.Bits.IOUT_POUT_F_OR_W)

#define Rte_Read_B_R_VSB_OFF              (PMBUS_tStatus.u16StatusWordP1.Bits.UINT_OFF)
#define Rte_Read_B_R_VSB_OV_FAULT         (PMBUS_tStatus.u8StatusVoutP1.Bits.VOUT_OV_FAULT)
#define Rte_Read_B_R_VSB_UV_FAULT         (PMBUS_tStatus.u8StatusVoutP1.Bits.VOUT_UV_FAULT)
#define Rte_Read_B_R_VSB_OC_FAULT         (PMBUS_tStatus.u8StatusIoutP1.Bits.IOUT_OC_FAULT)	
#define Rte_Read_B_R_CML                  (PMBUS_tStatus.u16StatusWordP0.Bits.CML)

#define Rte_Read_B_R_V1_OVP               (RTE_B_COM_V1_OVP) 
#define Rte_Read_B_R_V1_UVP               (RTE_B_COM_V1_UVP) 
#define Rte_Read_B_R_V1_OCW               (RTE_B_COM_V1_OCW) 
#define Rte_Read_B_R_V1_OCP               (RTE_B_COM_V1_OCP) 	
#define Rte_Read_B_R_VIN_UV               (RTE_B_COM_VIN_UV)
#define Rte_Read_B_R_VIN_OV               (RTE_B_COM_VIN_OV) 
#define Rte_Read_B_R_ANY_OTP              (RTE_B_TEMP_ANY_OTP) 
#define Rte_Read_B_R_ANY_OTW              (RTE_B_TEMP_ANY_OTW)
#define Rte_Read_B_R_VSB_OVP              (RTE_B_COM_VSB_OVP)
#define Rte_Read_B_R_VSB_OCP              (RTE_B_COM_VSB_OCP)
#define Rte_Read_B_R_VSB_UVP              (RTE_B_COM_VSB_UVP)
#define Rte_Read_B_R_BULK_OVP             (RTE_B_PRI_PFC_OVP)

#define Rte_Read_B_R_PSON_ACTIVE          (RTE_B_DIO_PSON_ACTIVE)

/* Variables */
#define Rte_Read_R_StatusWord(var)        ((**var) = PMBUS_tStatus.u16StatusWordP0.ALL)
#define Rte_Read_R_StatusIout(var)        ((**var) = PMBUS_tStatus.u8StatusIoutP0.ALL)
#define Rte_Read_R_StatusInput(var)       ((**var) = PMBUS_tStatus.u8StatusInputP0.ALL)
#define Rte_Read_R_StatusTemp(var)        ((**var) = PMBUS_tStatus.u8StatusTempP0.ALL)
#define Rte_Read_R_StatusFan12(var)       ((**var) = PMBUS_tStatus.u8StatusFan12P0.ALL)
#define Rte_Read_R_ReadVin(var)           ((**var) = PMBUS_tData.u16Vin_Linear_Box.u16Val)
#define Rte_Read_R_ReadIin(var)           ((**var) = PMBUS_tData.u16Iin_Linear_Box.u16Val)
#define Rte_Read_R_ReadIout(var)          ((**var) = PMBUS_tData.u16Iout_V1_Linear_Box.u16Val)
#define Rte_Read_R_ReadTemp1(var)         ((**var) = PMBUS_tData.u16Temperatue_1_Linear.u16Val)
#define Rte_Read_R_ReadTemp2(var)         ((**var) = PMBUS_tData.u16Temperatue_2_Linear.u16Val)
#define Rte_Read_R_ReadFan1(var)          ((**var) = PMBUS_tData.u16FanSpeed_1_Linear.u16Val)
#define Rte_Read_R_ReadPin(var)           ((**var) = PMBUS_tData.u16Pin_Linear_Box.u16Val)
#define Rte_Read_R_ReadVout(var)          ((**var) = PMBUS_tData.u16Vout_V1_Linear_Box.u16Val)

/***********************************************
 * Output
 **********************************************/
/* Flags */

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
SINLINE uint8 BLABOX_Rte_Read_B_R_AUX_MODE(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_AUX_MODE;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_VOUT_OV_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_VOUT_OV_FAULT && Rte_Read_B_R_UINT_OFF && Rte_Read_B_R_V1_OVP;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_VOUT_UV_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_VOUT_UV_FAULT && Rte_Read_B_R_UINT_OFF && Rte_Read_B_R_V1_UVP;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_IOUT_OC_WARN(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_IOUT_OC_WARN && Rte_Read_B_R_V1_OCW && Rte_Read_B_R_IOUT_POUT_F_OR_W && (Rte_Read_B_R_POWER_GOOD_N == FALSE);
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_IOUT_OC_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_IOUT_OC_FAULT && Rte_Read_B_R_V1_OCP && Rte_Read_B_R_UINT_OFF;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_VIN_OV_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_VIN_OV_FAULT && Rte_Read_B_R_VIN_OV && Rte_Read_B_R_UINT_OFF;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_VIN_UV_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_VIN_UV_FAULT && Rte_Read_B_R_VIN_UV && Rte_Read_B_R_UINT_OFF;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_FAN_FAULT(void)
{
  #if MG_RTE_MODULE
	return (Rte_Read_B_R_FAN_1_FAULT && FANCTRL_u8ReadFanBitFail(0)) || (Rte_Read_B_R_FAN_2_FAULT && FANCTRL_u8ReadFanBitFail(1));
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_OT_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_OT_FAULT && Rte_Read_B_R_ANY_OTP && Rte_Read_B_R_UINT_OFF;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_OT_WARN(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_OT_WARN && Rte_Read_B_R_ANY_OTW;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_GENERAL_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_CML;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_LOSS_INPUT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_VIN_UV && (FALSE == Rte_Read_B_R_AUX_MODE);
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_PSON_FAULT(void)
{
  #if MG_RTE_MODULE
	return (Rte_Read_B_R_PSON_ACTIVE == FALSE);
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_AC_POWER_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_VIN_UV;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_IOUT_WARN(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_V1_OCW;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_FAN_WARN(void)
{
	return FANCTRL_u8ReadFanBitWarn(0) || FANCTRL_u8ReadFanBitWarn(1);
}
SINLINE uint8 BLABOX_Rte_Read_B_R_TEMP_WARN(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_ANY_OTW;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_VSB_OV_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_VSB_OV_FAULT && Rte_Read_B_R_UINT_OFF && Rte_Read_B_R_VSB_OVP;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_VSB_UV_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_VSB_UV_FAULT && Rte_Read_B_R_UINT_OFF && Rte_Read_B_R_VSB_UVP;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_ISB_OC_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_ISB_OC_FAULT && Rte_Read_B_R_VSB_OCP && Rte_Read_B_R_UINT_OFF;
	#endif
}
SINLINE uint8 BLABOX_Rte_Read_B_R_BULK_OV_FAULT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_BULK_OVP && Rte_Read_B_R_UINT_OFF;
	#endif
}


SINLINE void BLABOX_Rte_Read_R_StatusWord(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_StatusWord(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_StatusIout(uint8 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_StatusIout(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_StatusInput(uint8 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_StatusInput(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_StatusTemp(uint8 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_StatusTemp(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_StatusFan12(uint8 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_StatusFan12(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_ReadVin(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_ReadVin(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_ReadIin(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_ReadIin(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_ReadIout(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_ReadIout(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_ReadTemp1(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_ReadTemp1(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_ReadTemp2(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_ReadTemp2(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_ReadFan1(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_ReadFan1(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_ReadPin(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_ReadPin(&var);
#endif
}
SINLINE void BLABOX_Rte_Read_R_ReadVout(uint16 *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_ReadVout(&var);
#endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* FANCTRL_RTE_H */


/*
 * End of file
 */
