/*******************************************************************************
 * \file    psuctrl_rte.h
 * \brief   RTE interface for psuctrl.c
 *
 * \section AUTHOR
 *    1. Jackie Chen
 *
 * \section SVN
 *  $Date: 2019-08-21 16:58:00 +0800 (Wed, 21 Aug 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 221 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#ifndef PSUCTRL_RTE_H
#define PSUCTRL_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif
		
#include "global.h"
#include "rte.h"

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
#define MG_U8_ON                            (0x80u)
#define MG_U8_OFF                           (0x00u)
/***********************************************
 * Input
 **********************************************/

/* Flags */
#define RTE_Read_B_R_STA_VSB_ON                 (RTE_B_COM_VSB_ON)
#define RTE_Read_B_R_VSB_LATCH                  (RTE_B_COM_VSB_LATCH)	
#define RTE_Read_B_R_VSB_OCP                    (RTE_B_COM_VSB_OCP)
#define RTE_Read_B_R_KILL_ACTIVE                (RTE_B_DIO_PS_KILL_ACTIVE)
#define RTE_Read_B_R_PSON_ACTIVE                (RTE_B_DIO_PSON_ACTIVE)
#define RTE_Read_B_R_BULK_OK                    (RTE_B_PRI_BULK_OK)
#define RTE_Read_B_R_PFC_OVP                    (RTE_B_PRI_PFC_OVP)
#define RTE_Read_B_R_RELAY_ON                   (RTE_B_PRI_RELAY_ON)
#define RTE_Read_B_R_VSB_MONI_EN                (RTE_B_COM_VSB_MONI_EN)
#define RTE_Read_B_R_V1_LATCHED                 (RTE_B_COM_V1_LATCHED)
#define RTE_Read_B_R_VIN_OK                     (RTE_B_COM_VIN_OK)
#define RTE_Read_B_R_TEMP_ANY_OTP               (RTE_B_TEMP_ANY_OTP)
#define RTE_Read_B_R_ORING_TEST_FAIL            (RTE_B_PSUCTRL_ORING_TEST_FAIL)
#define RTE_Read_B_R_BOOT_RESET_FLAG            (PMBUS_uSysStatu1.Bits.BOOT_RESET_FLAG)
#define RTE_Read_B_R_V1_ON                      (RTE_B_SEC_LLC_EN)
#define RTE_Read_B_R_V1_OVP                     (RTE_B_COM_V1_OVP)
#define RTE_Read_B_R_V1_OCP                     (RTE_B_COM_V1_OCP)
#define RTE_Read_B_R_V1_UVP                     (RTE_B_COM_V1_UVP)
#define RTE_Read_B_R_AUX_MODE                   (PMBUS_uSysStatu0.Bits.AUX_MODE)
#define RTE_Read_B_R_REMOTE_ON                  (RTE_B_TO_SEC_STA_REMOTE_ON)
#define RTE_Read_B_R_VSB_TRIM                   (RTE_B_PSUCTRL_VSB_TRIM)
#define RTE_Read_B_R_V1_TRIM                    (RTE_B_PSUCTRL_V1_TRIM)
#define RTE_Read_B_R_VSB_OVP_TEST               (RTE_B_PSUCTRL_VSB_OVP_TEST)
#define RTE_Read_B_R_V1_OVP_TEST                (RTE_B_PSUCTRL_V1_OVP_TEST)
#define RTE_Read_B_R_VSB_UVP                    (RTE_B_COM_VSB_UVP)
#define RTE_Read_B_R_VIN_OK_PRI                 (RTE_B_DIO_VIN_OK_ACTIVE)
#define RTE_Read_B_R_V1_FAULT_ACTIVE            (RTE_B_DIO_54V_FAULT_ACTIVE)


/* Variables */

#define Rte_Read_R_u8PmbusCmdOperation(var)     ((**var) = PMBUS_uOperation.ALL)
#define Rte_Read_R_u16TrimVsbGain(var)          ((**var) = RTE_u16TrimVsbGain.u16Val)
#define Rte_Read_R_u16TrimVsbGainOvp(var)       ((**var) = RTE_u16TrimVsbGainOvp.u16Val)
#define Rte_Read_R_u16TrimV1Gain(var)           ((**var) = RTE_u16TrimV1Gain.u16Val)
#define Rte_Read_R_u16TrimV1GainOvp(var)        ((**var) = RTE_u16TrimV1GainOvp.u16Val)
#define Rte_Read_R_u16TrimVsbGainAct(var)       ((**var) = RTE_u16TrimVsbGainAct.u16Val)
#define Rte_Read_R_u16TrimV1GainAct(var)        ((**var) = RTE_u16TrimV1GainAct.u16Val)

/* Registers */

/***********************************************
 * Output
 **********************************************/
/* Flags */
#define RTE_Write_B_P_SYNC_INTERNAL_ON	            (RTE_B_DIO_SYNC_INTERNAL_ON)
#define RTE_Write_B_P_VSB_ON                        (RTE_B_DIO_VSB_ON)
#define RTE_Write_B_P_VSB_OVPTEST_ACTIVE            (RTE_B_DIO_VSB_OVPTEST_ACTIVE)
#define RTE_Write_B_P_STA_VSB_ON                    (RTE_B_COM_VSB_ON)
#define RTE_Write_B_P_VSB_LATCH                     (RTE_B_COM_VSB_LATCH)
#define RTE_Write_B_P_VSB_MONI_EN                   (RTE_B_COM_VSB_MONI_EN)
#define RTE_Write_B_P_VSB_UVP                       (RTE_B_COM_VSB_UVP)
#define RTE_Write_B_P_VSB_UVW                       (RTE_B_COM_VSB_UVW)
#define RTE_Write_B_P_VSB_PWOK                      (RTE_B_COM_VSB_PWOK)
#define RTE_Write_B_P_V1_OFF_BY_VIN_OFF             (RTE_FLG_V1_OFF_BY_VIN_OFF)
#define RTE_Write_B_P_ORING_TEST_FAIL               (RTE_B_PSUCTRL_ORING_TEST_FAIL)
#define RTE_Write_B_P_OUTPUT_OK                     (RTE_B_COM_OUTPUT_OK)
#define RTE_Write_B_P_VSB_OVP_TEST                  (RTE_B_PSUCTRL_VSB_OVP_TEST)
#define RTE_Write_B_P_VSB_TRIM                      (RTE_B_PSUCTRL_VSB_TRIM)
#define RTE_Write_B_P_V1_OVP_TEST                   (RTE_B_PSUCTRL_V1_OVP_TEST)
#define RTE_Write_B_P_COM_TO_SEC_STA_OVP_TEST       (RTE_B_TO_SEC_STA_OVP_TEST)
#define RTE_Write_B_P_V1_TRIM                       (RTE_B_PSUCTRL_V1_TRIM)
#define RTE_Write_B_P_ORING_TEST                    (RTE_B_SEC_ORING_TEST)
#define RTE_Write_B_P_TURN_ON_MAIN                  (RTE_B_TO_SEC_STA_TURN_ON_MAIN)
#define RTE_Write_B_P_STA_V1_ON                     (RTE_B_COM_V1_ON)
#define RTE_Write_B_P_V1_MONI_EN                    (RTE_B_COM_V1_MONI_EN)
#define RTE_Write_B_P_V1_LATCHED                    (RTE_B_COM_V1_LATCHED)
#define RTE_Write_B_P_VSB_OK                        (RTE_B_COM_VSB_OK)

/* Registers */ 

#define RTE_Write_P_u16TrimVsbGain                  (RTE_u16TrimVsbGain.u16Val)
#define RTE_Write_P_u16TrimV1Gain                   (RTE_u16TrimV1Gain.u16Val)
#define RTE_Write_P_u16TrimVsbGainAct               (RTE_u16TrimVsbGainAct.u16Val)
#define RTE_Write_P_u16TrimV1GainAct                (RTE_u16TrimV1GainAct.u16Val)
#define RTE_Write_P_u16TrimVsbGainOvp               (RTE_u16TrimVsbGainOvp.u16Val)
#define RTE_Write_P_u16TrimV1GainOvp                (RTE_u16TrimV1GainOvp.u16Val)

 
/*******************************************************************************
 * Global data types (public typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
 /* Read */
SINLINE uint8 PSUCTRL_RTE_Read_B_R_V1_LATCHED(void)
{
	return RTE_Read_B_R_V1_LATCHED;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_STA_VSB_ON(void)
{
	return RTE_Read_B_R_STA_VSB_ON;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_VSB_LATCH(void)
{
	return RTE_Read_B_R_VSB_LATCH;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_VSB_OCP(void)
{
	return RTE_Read_B_R_VSB_OCP;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_KILL_ACTIVE(void)
{
	return RTE_Read_B_R_KILL_ACTIVE;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_PSON_ACTIVE(void)
{
	return RTE_Read_B_R_PSON_ACTIVE;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_BULK_OK(void)
{
	return RTE_Read_B_R_BULK_OK;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_PFC_OVP(void)
{
	return RTE_Read_B_R_PFC_OVP;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_RELAY_ON(void)
{
	return RTE_Read_B_R_RELAY_ON;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_VSB_MONI_EN(void)
{
	return RTE_Read_B_R_VSB_MONI_EN;
}


SINLINE uint8 PSUCTRL_RTE_Read_B_R_V1_OVP(void)
{
	return RTE_Read_B_R_V1_OVP;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_V1_OCP(void)
{
	return RTE_Read_B_R_V1_OCP;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_V1_UVP(void)
{
	return RTE_Read_B_R_V1_UVP;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_VIN_OK(void)
{
	return RTE_Read_B_R_VIN_OK;
}

SINLINE uint8 PSUCTRL_Rte_Read_B_R_TEMP_ANY_OTP(void)
{
	return RTE_Read_B_R_TEMP_ANY_OTP;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_ORING_TEST_FAIL(void)
{
	return RTE_Read_B_R_ORING_TEST_FAIL;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_BOOT_RESET_FLAG(void)
{
	return RTE_Read_B_R_BOOT_RESET_FLAG;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_V1_ON(void)
{
	return RTE_Read_B_R_V1_ON;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_AUX_MODE(void)
{
	return RTE_Read_B_R_AUX_MODE;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_REMOTE_ON(void)
{
	return RTE_Read_B_R_REMOTE_ON;
}

SINLINE uint8 PSUCTRL_RTE_Read_B_R_VSB_TRIM(void)
{
	return RTE_Read_B_R_VSB_TRIM;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_V1_TRIM(void)
{
	return RTE_Read_B_R_V1_TRIM;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_VSB_OVP_TEST(void)
{
	return RTE_Read_B_R_VSB_OVP_TEST;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_V1_OVP_TEST(void)
{
	return RTE_Read_B_R_V1_OVP_TEST;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_VSB_UVP(void)
{
	return RTE_Read_B_R_VSB_UVP;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_VIN_OK_PRI(void)
{
	return RTE_Read_B_R_VIN_OK_PRI;
}
SINLINE uint8 PSUCTRL_RTE_Read_B_R_V1_FAULT_ACTIVE(void)
{
	return RTE_Read_B_R_V1_FAULT_ACTIVE;
}



SINLINE void PSUCTRL_Rte_Read_R_u8PmbusCmdOperation(uint8 *var)
{
  Rte_Read_R_u8PmbusCmdOperation(&var);
}

SINLINE void PSUCTRL_Rte_Read_R_u16TrimVsbGain(uint16 *var)
{
  Rte_Read_R_u16TrimVsbGain(&var);
}

SINLINE void PSUCTRL_Rte_Read_R_u16TrimVsbGainOvp(uint16 *var)
{
  Rte_Read_R_u16TrimVsbGainOvp(&var);
}

SINLINE void PSUCTRL_Rte_Read_R_u16TrimV1Gain(uint16 *var)
{
  Rte_Read_R_u16TrimV1Gain(&var);
}

SINLINE void PSUCTRL_Rte_Read_R_u16TrimV1GainOvp(uint16 *var)
{
  Rte_Read_R_u16TrimV1GainOvp(&var);
}

SINLINE void PSUCTRL_Rte_Read_R_u16TrimVsbGainAct(uint16 *var)
{
  Rte_Read_R_u16TrimVsbGainAct(&var);
}

SINLINE void PSUCTRL_Rte_Read_R_u16TrimV1GainAct(uint16 *var)
{
  Rte_Read_R_u16TrimV1GainAct(&var);
}


 /* Write */
SINLINE void PSUCTRL_Rte_Write_B_P_SYNC_INTERNAL_ON(uint8 u8Status)
{
	RTE_Write_B_P_SYNC_INTERNAL_ON = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_V1_LATCHED (uint8 u8Status)
{
	RTE_Write_B_P_V1_LATCHED = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_ON(uint8 u8Status)
{
	RTE_Write_B_P_VSB_ON = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_OVPTEST_ACTIVE(uint8 u8Status)
{
	RTE_Write_B_P_VSB_OVPTEST_ACTIVE = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_STA_VSB_ON(uint8 u8Status)
{
	RTE_Write_B_P_STA_VSB_ON = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_LATCH(uint8 u8Status)
{
	RTE_Write_B_P_VSB_LATCH = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_MONI_EN(uint8 u8Status)
{
	RTE_Write_B_P_VSB_MONI_EN = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_UVP(uint8 u8Status)
{
	RTE_Write_B_P_VSB_UVP = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_UVW(uint8 u8Status)
{
	RTE_Write_B_P_VSB_UVW = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_PWOK(uint8 u8Status)
{
	RTE_Write_B_P_VSB_PWOK = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_ORING_TEST_FAIL(uint8 u8Status)
{
	RTE_Write_B_P_ORING_TEST_FAIL = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_OUTPUT_OK(uint8 u8Status)
{
	RTE_Write_B_P_OUTPUT_OK = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_OVP_TEST(uint8 u8Status)
{
	RTE_Write_B_P_VSB_OVP_TEST = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_VSB_TRIM(uint8 u8Status)
{
	RTE_Write_B_P_VSB_TRIM = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_V1_OVP_TEST(uint8 u8Status)
{
	RTE_Write_B_P_V1_OVP_TEST = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_COM_TO_SEC_STA_OVP_TEST(uint8 u8Status)
{
	RTE_Write_B_P_COM_TO_SEC_STA_OVP_TEST = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_V1_TRIM(uint8 u8Status)
{
	RTE_Write_B_P_V1_TRIM = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_ORING_TEST(uint8 u8Status)
{
	RTE_Write_B_P_ORING_TEST = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_TURN_ON_MAIN(uint8 u8Status)
{
	RTE_Write_B_P_TURN_ON_MAIN = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_STA_V1_ON(uint8 u8Status)
{
	RTE_Write_B_P_STA_V1_ON = u8Status;
}

SINLINE void PSUCTRL_Rte_Write_B_P_V1_MONI_EN(uint8 u8Status)
{
	RTE_Write_B_P_V1_MONI_EN = u8Status;
}


SINLINE void PSUCTRL_Rte_Write_P_u16TrimVsbGain(uint16 u16Data)
{
	RTE_Write_P_u16TrimVsbGain = u16Data;
}

SINLINE void PSUCTRL_Rte_Write_P_u16TrimVsbGainOvp(uint16 u16Data)
{
	RTE_Write_P_u16TrimVsbGainOvp = u16Data;
}

SINLINE void PSUCTRL_Rte_Write_P_u16TrimVsbGainAct(uint16 u16Data)
{
	RTE_Write_P_u16TrimVsbGainAct = u16Data;
}

SINLINE void PSUCTRL_Rte_Write_P_u16TrimV1Gain(uint16 u16Data)
{
	RTE_Write_P_u16TrimV1Gain = u16Data;
}

SINLINE void PSUCTRL_Rte_Write_P_u16TrimV1GainAct(uint16 u16Data)
{
	RTE_Write_P_u16TrimV1GainAct = u16Data;
}

SINLINE void PSUCTRL_Rte_Write_P_u16TrimV1GainOvp(uint16 u16Data)
{
	RTE_Write_P_u16TrimV1GainOvp = u16Data;
}



#ifdef __cplusplus
  }
#endif
#endif  /* PSUCTRL_RTE_H */


/*
 * End of file
 */





