/********************************************************************************
 * \file    monctrl_rte.h
 * \brief   RTE interface for monctrl.c
 *
 * \section AUTHOR
 *    1. Fred Ji
 *
 * \section SVN
 *  $Date: 2019-11-22 11:01:57 +0800 (Fri, 22 Nov 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 239 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 *******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#ifndef MONCTRL_RTE_H
#define MONCTRL_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif
		
#include "rte.h"

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
#define MG_RTE_MODULE       1
/***********************************************
 * Input
 **********************************************/

/* Flags */
#define RTE_Read_B_R_VDC_IN	            (RTE_B_PRI_VDC_IN)
#define RTE_Read_B_R_PRI1_NO_RX_PKG     (RTE_B_PRI_NO_RX_PKG)
#define RTE_Read_B_R_SEC1_NO_RX_PKG     (RTE_B_SEC_NO_RX_PKG)
#define RTE_Read_B_R_PRI1_RX_PKG        (RTE_B_PRI_RX_PKG)
#define RTE_Read_B_R_NO_VIN             (RTE_B_COM_NO_VIN)
#define RTE_Read_B_R_VIN_DROPOUT        (RTE_B_PRI_VIN_DROPOUT)
#define RTE_Read_B_R_VIN_LINE_LOW       (RTE_B_PRI_VIN_LINE_LOW)
		
#define RTE_Read_B_R_RELAY_ON	          (RTE_B_PRI_RELAY_ON) 
#define RTE_Read_B_R_EXTRDY_VSB         (RTE_B_COM_EXTRDY_VSB)	
#define RTE_Read_B_R_NTC_FAULT		      (RTE_TEMP_NTC_FAULT)	
#define RTE_Read_B_R_VIN_UV             (RTE_B_COM_VIN_UV)
#define RTE_Read_B_R_VIN_OV             (RTE_B_COM_VIN_OV)
#define RTE_Read_B_R_PSON_ACTIVE        (RTE_B_DIO_PSON_ACTIVE)
#define RTE_Read_B_R_OUTPUT_OK          (RTE_B_COM_OUTPUT_OK)
#define RTE_Read_B_R_PS_KILL_ACTIVE     (RTE_B_DIO_PS_KILL_ACTIVE)
#define RTE_Read_B_R_V1_MONI_EN         (RTE_B_COM_V1_MONI_EN)
#define RTE_Read_B_R_VIN_LINE           (RTE_B_PRI_VIN_LINE_LOW)
#define RTE_Read_B_R_VSB_ON_DIO         (RTE_B_DIO_VSB_ON)
#define RTE_Read_B_R_VSB_MONI_EN        (RTE_B_COM_VSB_MONI_EN)
#define RTE_Read_B_R_VSB_ON             (RTE_B_COM_VSB_ON)
#define RTE_Read_B_R_V1_ON              (RTE_B_COM_V1_ON)
#define RTE_Read_B_R_REMOTE_ON          (RTE_B_TO_SEC_STA_REMOTE_ON)
#define RTE_Read_B_R_VIN_OK_PRI         (RTE_B_PRI_VIN_OK)
#define RTE_Read_B_R_SEC_FAULT_CLR      (RTE_B_SEC_FAULT_CLR)
#define RTE_Read_B_R_VSB_LATCH          (RTE_B_COM_VSB_LATCH)
#define RTE_Read_B_R_TEMP_OTP           (RTE_B_TEMP_ANY_OTP)
#define RTE_Read_B_R_VSB_OVP            (RTE_B_COM_VSB_OVP)
#define RTE_Read_B_R_V1_OVP             (RTE_B_COM_V1_OVP)
#define RTE_Read_B_R_V1_UVP             (RTE_B_COM_V1_UVP)
#define RTE_Read_B_R_V1_OCP             (RTE_B_COM_V1_OCP)

/* Variables */
#define Rte_Read_R_u16VinLinear(var)          ((**var) = PMBUS_tData.u16Vin_Linear.u16Val)
#define Rte_Read_R_u16IoutV1Linear(var)       ((**var) = PMBUS_tData.u16Iout_V1_Linear.u16Val)
#define Rte_Read_R_u16VsbLinear(var)          ((**var) = RTE_u16VoutIntVsbFast)
#define Rte_Read_R_u16VsbLinearExt(var)       ((**var) = RTE_u16VoutExtVsbFast)
#define Rte_Read_R_u16IoutVsbLinear(var)      ((**var) = RTE_u16IoutVsbFast)

#define Rte_Read_R_u16VinMul128(var)          ((**var) = PMBUS_tData.u16Vin_Mul_128.u16Val)
#define Rte_Read_R_u16IntV1Adc(var)           ((**var) = RTE_Sec.u1610mVIntV1Avg.u16Val)

#define Rte_Read_R_u8PmbusOperation(var)      ((**var) = PMBUS_uOperation.ALL)

#define Rte_Read_R_u16100mHzVoltInFreq(var)   ((**var) = RTE_Pri.u16100mHzVoltInFreq.u16Val)

#define Rte_Read_R_bIsVsbOcpTest(var)         ((**var) = RTE_bIsVsbOcpTest)

/* Registers */

/* Definitions */

/***********************************************
 * Output
 **********************************************/

/* Flags */
#define RTE_Write_B_P_EXTRDY_VSB        RTE_B_COM_EXTRDY_VSB
#define RTE_Write_B_P_ANY_NTC_FAULT     RTE_B_COM_ANY_NTC_FAULT	
#define RTE_Write_B_P_NO_VIN            RTE_B_COM_NO_VIN	
#define RTE_Write_B_P_VIN_UV            RTE_B_COM_VIN_UV
#define RTE_Write_B_P_VIN_UVW           RTE_B_COM_VIN_UVW
#define RTE_Write_B_P_VIN_OV            RTE_B_COM_VIN_OV
#define RTE_Write_B_P_VIN_OK            RTE_B_COM_VIN_OK
#define RTE_Write_B_P_INPUT_OFF         RTE_B_COM_INPUT_OFF
#define RTE_Write_B_P_VSB_OVP           RTE_B_COM_VSB_OVP
#define RTE_Write_B_P_VSB_OVW           RTE_B_COM_VSB_OVW
#define RTE_Write_B_P_VSB_LATCH         RTE_B_COM_VSB_LATCH
#define RTE_Write_B_P_VSB_UVP           RTE_B_COM_VSB_UVP
#define RTE_Write_B_P_VSB_UVW           RTE_B_COM_VSB_UVW
#define RTE_Write_B_P_VSB_OCP           RTE_B_COM_VSB_OCP
#define RTE_Write_B_P_VSB_OCW           RTE_B_COM_VSB_OCW
#define RTE_Write_B_P_V1_OVP           (RTE_B_COM_V1_OVP)
#define RTE_Write_B_P_V1_UVP           (RTE_B_COM_V1_UVP)
#define RTE_Write_B_P_V1_OCP           (RTE_B_COM_V1_OCP)
#define RTE_Write_B_P_V1_OCW           (RTE_B_COM_V1_OCW)
#define RTE_Write_B_P_V1_OVP_TEST      (RTE_B_PSUCTRL_V1_OVP_TEST)
#define RTE_Write_B_P_VSB_OVP_TEST     (RTE_B_PSUCTRL_VSB_OVP_TEST)

#define RTE_Write_B_P_AC_LOST            (RTE_B_TO_SEC_STA_AC_LOST)
#define RTE_Write_B_P_REMOTE_ON          (RTE_B_TO_SEC_STA_REMOTE_ON)
#define RTE_Write_B_P_VIN_LINE_LOW       (RTE_B_TO_SEC_STA_VIN_LINE_LOW)
#define RTE_Write_B_P_CLEAR_LATCH_FAULT  (RTE_B_TO_SEC_STA_CLEAR_LATCH_FAULT)
#define RTE_Write_B_P_STB_MODE           (PMBUS_uSysStatu1.Bits.STB_MODE)
#define RTE_Write_B_P_V1_LATCHED         (RTE_B_COM_V1_LATCHED)


/* Registers */    

#define RTE_Write_P_uComStatus01                    (RTE_uComStatus01.ALL)
#define RTE_Write_P_u16TrimVsbGain                  (RTE_u16TrimVsbGain.u16Val)
#define RTE_Write_P_u16TrimV1Gain                   (RTE_u16TrimV1Gain.u16Val)
#define RTE_Write_P_u16TrimVsbGainAct               (RTE_u16TrimVsbGainAct.u16Val)
#define RTE_Write_P_u16TrimV1GainAct                (RTE_u16TrimV1GainAct.u16Val)
#define RTE_Write_P_u16TrimVsbGainOvp               (RTE_u16TrimVsbGainOvp.u16Val)
#define RTE_Write_P_u16TrimV1GainOvp                (RTE_u16TrimV1GainOvp.u16Val)

#define RTE_Write_P_u8AcLineStatus(var)             (RTE_u8AcLineStatus = var)

/*******************************************************************************
 * Global data types (public typedefs / structs / enums)
 ******************************************************************************/


/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
 
SINLINE uint8 MONCTRL_Rte_Read_B_R_VIN_LINE_LOW(void)
{
	return RTE_Read_B_R_VIN_LINE_LOW;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_V1_ON(void)
{
	return RTE_Read_B_R_V1_ON;
}
SINLINE uint8 MONCTRL_RTE_Read_B_R_V1_OVP(void)
{
	return RTE_Read_B_R_V1_OVP;
}
SINLINE uint8 MONCTRL_RTE_Read_B_R_V1_UVP(void)
{
	return RTE_Read_B_R_V1_UVP;
}
SINLINE uint8 MONCTRL_RTE_Read_B_R_V1_OCP(void)
{
	return RTE_Read_B_R_V1_OCP;
}
SINLINE uint8 MONCTRL_RTE_Read_B_R_VDC_IN(void)
{
	return RTE_Read_B_R_VDC_IN;
}

SINLINE uint8 INTCOM_RTE_Read_B_R_VIN_OK_PRI(void)
{
	return RTE_Read_B_R_VIN_OK_PRI;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_PRI1_NO_RX_PKG(void)
{
	return RTE_Read_B_R_PRI1_NO_RX_PKG;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_PRI1_RX_PKG(void)
{
	return RTE_Read_B_R_PRI1_RX_PKG;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_SEC1_NO_RX_PKG(void)
{
	return RTE_Read_B_R_SEC1_NO_RX_PKG;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_RELAY_ON(void)
{
	return RTE_Read_B_R_RELAY_ON;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_VIN_DROPOUT(void)
{
	return RTE_Read_B_R_VIN_DROPOUT;
}
SINLINE uint8 MONCTRL_RTE_Read_B_R_VSB_OVP(void)
{
	return RTE_Read_B_R_VSB_OVP;
}


SINLINE uint8 MONCTRL_RTE_Read_B_R_NTC_FAULT(void)
{
	return RTE_Read_B_R_NTC_FAULT;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_TEMP_OTP(void)
{
	return RTE_Read_B_R_TEMP_OTP;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_NO_VIN(void)
{
	return RTE_Read_B_R_NO_VIN;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_VIN_UV(void)
{
	return RTE_Read_B_R_VIN_UV;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_VIN_OV(void)
{
	return RTE_Read_B_R_VIN_OV;
}


SINLINE uint8 MONCTRL_RTE_Read_B_R_PSON_ACTIVE(void)
{
	return RTE_Read_B_R_PSON_ACTIVE;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_OUTPUT_OK(void)
{
	return RTE_Read_B_R_OUTPUT_OK;
}

SINLINE uint8 MONCTRL_RTE_Read_B_P_VSB_ON(void)
{
	return RTE_Read_B_R_VSB_ON;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_VSB_ON_DIO(void)
{
	return RTE_Read_B_R_VSB_ON_DIO;
}


SINLINE uint8 MONCTRL_RTE_Read_B_R_PS_KILL_ACTIVE(void)
{
	return RTE_Read_B_R_PS_KILL_ACTIVE;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_V1_MONI_EN(void)
{
	return RTE_Read_B_R_V1_MONI_EN;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_VIN_LINE(void)
{
	return RTE_Read_B_R_VIN_LINE;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_VSB_MONI_EN(void)
{
	return RTE_Read_B_R_VSB_MONI_EN;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_REMOTE_ON(void)
{
	return RTE_Read_B_R_REMOTE_ON;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_SEC_FAULT_CLR(void)
{
	return RTE_Read_B_R_SEC_FAULT_CLR;
}

SINLINE uint8 MONCTRL_RTE_Read_B_R_VSB_LATCH(void)
{
	return RTE_Read_B_R_VSB_LATCH;
}

SINLINE void MONCTRL_RTE_Read_R_vVinLinear(uint16 *var)
{
	Rte_Read_R_u16VinLinear(&var);
}

SINLINE void MONCTRL_RTE_Read_R_vIoutV1Linear(uint16 *var)
{
	Rte_Read_R_u16IoutV1Linear(&var);
}

SINLINE void MONCTRL_RTE_Read_R_vVsbLinear(uint16 *var)
{
	Rte_Read_R_u16VsbLinear(&var);
}
SINLINE void MONCTRL_Rte_Read_R_u16VsbLinearExt(uint16 *var)
{
	Rte_Read_R_u16VsbLinearExt(&var);
}


SINLINE void MONCTRL_RTE_Read_R_vIoutVsbLinear(uint16 *var)
{
	Rte_Read_R_u16IoutVsbLinear(&var);
}

SINLINE void MONCTRL_RTE_Read_R_u16VinMul128(uint16 *var)
{
	Rte_Read_R_u16VinMul128(&var);
}

SINLINE void MONCTRL_RTE_Read_R_u16IntV1Adc(uint16 *var)
{
	Rte_Read_R_u16IntV1Adc(&var);
}

SINLINE void MONCTRL_Rte_Read_R_u16100mHzVoltInFreq(uint16 *var)
{
	Rte_Read_R_u16100mHzVoltInFreq(&var);
}

SINLINE void MONCTRL_RTE_Read_R_u8PmbusOperation(uint8 *var)
{
	Rte_Read_R_u8PmbusOperation(&var);
}

SINLINE void MONCTRL_Rte_Read_R_bIsVsbOcpTest(boolean *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_bIsVsbOcpTest(&var);
  #endif
}




/* Write */
SINLINE void MONCTRL_RTE_Write_B_P_ANY_NTC_FAULT(uint8 u8Status)
{
	RTE_Write_B_P_ANY_NTC_FAULT = u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_NO_VIN(uint8 u8Status)
{
	RTE_Write_B_P_NO_VIN = u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VIN_UV(uint8 u8Status)
{
	RTE_Write_B_P_VIN_UV = u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VIN_UVW(uint8 u8Status)
{
	RTE_Write_B_P_VIN_UVW = u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VIN_OV(uint8 u8Status)
{
	RTE_Write_B_P_VIN_OV = u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VIN_OK(uint8 u8Status)
{
	RTE_Write_B_P_VIN_OK = u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_INPUT_OFF(uint8 u8Status)
{
	RTE_Write_B_P_INPUT_OFF = u8Status; 
}

SINLINE void MONCTRL_RTE_Write_B_P_CLEAR_LATCH_FAULT(uint8 u8Status)
{
	RTE_Write_B_P_CLEAR_LATCH_FAULT =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VSB_OVP(uint8 u8Status)
{
  RTE_Write_B_P_VSB_OVP =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VSB_OVW(uint8 u8Status)
{
  RTE_Write_B_P_VSB_OVW =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VSB_LATCH(uint8 u8Status)
{
	RTE_Write_B_P_VSB_LATCH =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VSB_UVP(uint8 u8Status)
{
  RTE_Write_B_P_VSB_UVP =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VSB_UVW(uint8 u8Status)
{
  RTE_Write_B_P_VSB_UVW =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VSB_OCP(uint8 u8Status)
{
  RTE_Write_B_P_VSB_OCP =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VSB_OCW(uint8 u8Status)
{
  RTE_Write_B_P_VSB_OCW =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_REMOTE_ON(uint8 u8Status)
{
  RTE_Write_B_P_REMOTE_ON =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_AC_LOST(uint8 u8Status)
{
  RTE_Write_B_P_AC_LOST =  u8Status;
}

SINLINE void MONCTRL_RTE_Write_B_P_VIN_LINE_LOW(uint8 u8Status)
{
  RTE_Write_B_P_VIN_LINE_LOW  =  u8Status;
}

SINLINE void MONCTRL_Rte_Write_B_P_STB_MODE(uint8 u8Status)
{
	RTE_Write_B_P_STB_MODE = u8Status;
}

SINLINE void MONCTRL_RTE_Write_P_TrimVsbGain(uint16 u16Data)
{
  RTE_Write_P_u16TrimVsbGain =  u16Data; 
}

SINLINE void MONCTRL_RTE_Write_P_TrimVsbGainOvp(uint16 u16Data)
{
  RTE_Write_P_u16TrimVsbGainOvp =  u16Data; 
}

SINLINE void MONCTRL_RTE_Write_P_TrimV1GainOvpA(uint16 u16Data)
{
  RTE_Write_P_u16TrimV1GainOvp =  u16Data;
}

SINLINE void MONCTRL_RTE_Write_P_uComStatus01(uint16 u16Data)
{
  RTE_Write_P_uComStatus01 =  u16Data;
}

SINLINE void MONCTRL_Rte_Write_B_P_V1_OVP_TEST(uint8 u8Status)
{
	RTE_Write_B_P_V1_OVP_TEST = u8Status;
}

SINLINE void MONCTRL_Rte_Write_B_P_VSB_OVP_TEST(uint8 u8Status)
{
	RTE_Write_B_P_VSB_OVP_TEST = u8Status;
}

SINLINE void MONCTRL_Rte_Write_B_P_V1_OVP(uint8 u8Status)
{
	RTE_Write_B_P_V1_OVP = u8Status;
}

SINLINE void MONCTRL_Rte_Write_B_P_V1_UVP(uint8 u8Status)
{
	RTE_Write_B_P_V1_UVP = u8Status;
}

SINLINE void MONCTRL_Rte_Write_B_P_V1_OCP(uint8 u8Status)
{
	RTE_Write_B_P_V1_OCP = u8Status;
}

SINLINE void MONCTRL_Rte_Write_B_P_V1_OCW(uint8 u8Status)
{
	RTE_Write_B_P_V1_OCW = u8Status;
}

SINLINE void MONCTRL_Rte_Write_B_P_V1_LATCHED (uint8 u8Status)
{
	RTE_Write_B_P_V1_LATCHED = u8Status;
}

SINLINE void MONCTRL_RTE_Write_P_u8AcLineStatus (uint8 u8Status)
{
	RTE_Write_P_u8AcLineStatus(u8Status);
}







#ifdef __cplusplus
  }
#endif
#endif  /* MONCTRL_RTE_H */


/*
 * End of file
 */





