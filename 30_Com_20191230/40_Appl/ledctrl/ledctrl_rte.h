/** *****************************************************************************
 * \file    ledctrl_rte.h
 * \brief   RTE interface for ledctrl.c
 *
 * \section AUTHOR
 *    1. Fred Ji
 *
 * \section SVN
 *  $Date: 2019-03-18 10:51:05 +0800 (Mon, 18 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 150 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

#ifndef LEDCTRL_RTE_H
#define LEDCTRL_RTE_H
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
/* Definitions */
#define RTE_Read_B_R_PS_KILL_ACTIVE			(RTE_B_DIO_PS_KILL_ACTIVE)
#define RTE_Read_B_R_PSON_ACTIVE        (RTE_B_DIO_PSON_ACTIVE)
#define RTE_Read_B_R_VIN_OK             (RTE_B_COM_VIN_OK)
#define RTE_Read_B_R_V1_OVP             (RTE_B_COM_V1_OVP)         /* 1 = V1 OVP */
#define RTE_Read_B_R_V1_UVP             (RTE_B_COM_V1_UVP)         /* 1 = V1 UVP */
#define RTE_Read_B_R_V1_OCP             (RTE_B_COM_V1_OCP)         /* 1 = V1 OCP */		
#define RTE_Read_B_R_V1_OCW             (RTE_B_COM_V1_OCW)         /* 1 = V1 OCW */
#define RTE_Read_B_R_V1_ON              (RTE_B_SEC_LLC_EN)   
#define RTE_Read_B_R_BOOT_MODE          (PMBUS_uSysStatu1.Bits.BOOT_RESET_FLAG)
#define RTE_Read_B_R_VSB_ON             (RTE_B_COM_VSB_ON)
#define RTE_Read_B_R_VSB_OCW            (RTE_B_COM_VSB_OCW)
#define RTE_Read_B_R_Aux_Mode           (PMBUS_uSysStatu0.Bits.AUX_MODE)
#define RTE_Read_B_R_OUTPUT_OK          (RTE_B_COM_OUTPUT_OK)
#define RTE_Read_B_R_VSB_OVP            (RTE_B_COM_VSB_OVP)         /* 1 = V1 OVP */
#define RTE_Read_B_R_VSB_UVP            (RTE_B_COM_VSB_UVP)         /* 1 = V1 UVP */
#define RTE_Read_B_R_VSB_OCP            (RTE_B_COM_VSB_OCP)         /* 1 = V1 OCP */
#define RTE_Read_B_R_TEMP_OTP           (RTE_B_TEMP_ANY_OTP)
#define RTE_Read_B_R_TEMP_OTW           (RTE_B_TEMP_ANY_OTW)
#define RTE_Read_B_R_VIN_UVW            (RTE_B_COM_VIN_UVW)

#define RTE_Read_R_uPmBusOperation      (PMBUS_uOperation.ALL)
#define RTE_Read_B_R_CML                (PMBUS_tStatus.u16StatusWordP0.Bits.CML)


/***********************************************
 * Output
 **********************************************/
/* Registers */


/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
SINLINE uint8 LEDCTRL_RTE_Read_B_R_PSKILL(void)
{
	return RTE_Read_B_R_PS_KILL_ACTIVE;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_PSON(void)
{
	return RTE_Read_B_R_PSON_ACTIVE;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_VIN_OK(void)
{
	return RTE_Read_B_R_VIN_OK;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_V1_ON(void)
{
	return RTE_Read_B_R_V1_ON;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_BOOT_MODE(void)
{
	return RTE_Read_B_R_BOOT_MODE;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_VSB_ON(void)
{
	return RTE_Read_B_R_VSB_ON;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_VSB_OCW(void)
{
	return RTE_Read_B_R_VSB_OCW;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_V1_OVP(void)
{
	return RTE_Read_B_R_V1_OVP;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_V1_UVP(void)
{
	return RTE_Read_B_R_V1_UVP;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_V1_OCP(void)
{
	return RTE_Read_B_R_V1_OCP;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_VSB_OVP(void)
{
	return RTE_Read_B_R_VSB_OVP;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_VSB_UVP(void)
{
	return RTE_Read_B_R_VSB_UVP;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_VSB_OCP(void)
{
	return RTE_Read_B_R_VSB_OCP;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_V1_OCW(void)
{
	return RTE_Read_B_R_V1_OCW;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_Aux_Mode(void)
{
	return RTE_Read_B_R_Aux_Mode;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_TEMP_OTP(void)
{
	return RTE_Read_B_R_TEMP_OTP;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_TEMP_OTW(void)
{
	return RTE_Read_B_R_TEMP_OTW;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_VIN_UVW(void)
{
	return RTE_Read_B_R_VIN_UVW;
}



SINLINE uint8 LEDCTRL_RTE_Read_R_u8PmBusOperation(void)
{
	return RTE_Read_R_uPmBusOperation;
}

SINLINE uint8 LEDCTRL_RTE_Read_R_VMAIN_OK(void)
{
	return RTE_Read_B_R_OUTPUT_OK;
}

SINLINE uint8 LEDCTRL_RTE_Read_B_R_CML(void)
{
	return RTE_Read_B_R_CML;
}



#ifdef __cplusplus
  }
#endif
#endif  /* LEDCTRL_RTE_H */

  
/*
 * End of file
 */
