/** *****************************************************************************
 * \file    hwio_rte.h
 * \brief   RTE interface file for hwio.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-01-11 10:40:42 +0800 (Fri, 11 Jan 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 137 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef HWIO_RTE_H
#define HWIO_RTE_H
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
/***********************************************
 * Input
 **********************************************/

/* Flags */
#define RTE_Read_B_R_PSKILL_ACTIVE           (RTE_B_DIO_PS_KILL_ACTIVE)
#define RTE_Read_B_R_PSON_ACTIVE             (RTE_B_DIO_PSON_ACTIVE) 
#define RTE_Read_B_R_VSB_OVP_ACTIVE          (RTE_B_DIO_VSB_OVP_ACTIVE) 
#define RTE_Read_B_R_54V_FAULT_ACTIVE        (RTE_B_DIO_54V_FAULT_ACTIVE)
#define RTE_Read_B_R_VIN_OK_ACTIVE           (RTE_B_DIO_VIN_OK_ACTIVE)
#define RTE_Read_B_R_I2C_ADDRESS0            (RTE_B_DIO_I2C_ADDRESS0)
#define RTE_Read_B_R_I2C_ADDRESS1            (RTE_B_DIO_I2C_ADDRESS1)
#define RTE_Read_B_R_I2C_ADDRESS2            (RTE_B_DIO_I2C_ADDRESS2)

#define RTE_Read_B_R_VIN_OK                  (RTE_B_DIO_VIN_OK_ACTIVE)
#define RTE_Read_B_R_OUTPUT_OK               (RTE_B_COM_OUTPUT_OK)
#define RTE_Read_B_R_COM_VIN_OK              (RTE_B_COM_VIN_OK)
#define RTE_Read_B_R_SMBALLERT_ST            (RTE_B_COM_SMBALLERT_ST)
#define RTE_Read_B_R_V1_ON                   (RTE_B_COM_V1_ON)
#define RTE_Read_B_R_VSB_OVP_TEST            (RTE_B_PSUCTRL_VSB_OVP_TEST)
#define RTE_Read_B_R_VIN_LINE_LOW            (RTE_B_PRI_VIN_LINE_LOW)
 
#define RTE_Read_B_R_PWOK_ENA                (RTE_B_DIO_PWOK_ENA)           
#define RTE_Read_B_R_SMBALERT_ENA            (RTE_B_DIO_SMBALERT_ENA)  
#define RTE_Read_B_R_SYNC_INTERNAL_ON        (RTE_B_DIO_SYNC_INTERNAL_ON)  
#define RTE_Read_B_R_VINOK_ENA               (RTE_B_DIO_VINOK_ENA)
#define RTE_Read_B_R_VSB_OVPTEST_ACTIVE      (RTE_B_DIO_VSB_OVPTEST_ACTIVE)
#define RTE_Read_B_R_HIGH_LINE_ENA					 (RTE_B_DIO_HIGH_LINE_ENA)

/* Registers */

/* Definitions */

/***********************************************
 * Output
 **********************************************/

/* Flags */
#define RTE_Write_B_P_PSKILL_ACTIVE           (RTE_B_DIO_PS_KILL_ACTIVE)
#define RTE_Write_B_P_PSON_ACTIVE             (RTE_B_DIO_PSON_ACTIVE) 
#define RTE_Write_B_P_VSB_OVP_ACTIVE          (RTE_B_DIO_VSB_OVP_ACTIVE) 
#define RTE_Write_B_P_54V_FAULT_ACTIVE        (RTE_B_DIO_54V_FAULT_ACTIVE)
#define RTE_Write_B_P_VIN_OK_ACTIVE           (RTE_B_DIO_VIN_OK_ACTIVE)
#define RTE_Write_B_P_I2C_ADDRESS0            (RTE_B_DIO_I2C_ADDRESS0)
#define RTE_Write_B_P_I2C_ADDRESS1            (RTE_B_DIO_I2C_ADDRESS1)
#define RTE_Write_B_P_I2C_ADDRESS2            (RTE_B_DIO_I2C_ADDRESS2)

#define RTE_Write_B_P_PWOK_ENA                (RTE_B_DIO_PWOK_ENA)           
#define RTE_Write_B_P_SMBALERT_ENA            (RTE_B_DIO_SMBALERT_ENA)  
#define RTE_Write_B_P_SYNC_INTERNAL_ON        (RTE_B_DIO_SYNC_INTERNAL_ON)  
#define RTE_Write_B_P_VINOK_ENA               (RTE_B_DIO_VINOK_ENA)
#define RTE_Write_B_P_VSB_OVPTEST_ACTIVE      (RTE_B_DIO_VSB_OVPTEST_ACTIVE)

#define RTE_Write_B_P_OUTPUT_OK               (RTE_B_COM_OUTPUT_OK)
#define RTE_Write_B_P_HIGH_LINE_ENA						(RTE_B_DIO_HIGH_LINE_ENA)


/* Registers */

/* Definitions */

/*******************************************************************************
 * Module interface
 ******************************************************************************/
SINLINE uint8 HWIO_RTE_Read_B_R_PSKILL_ACTIVE(void)
{
	return RTE_Read_B_R_PSKILL_ACTIVE;
}

SINLINE uint8 HWIO_RTE_Read_B_R_PSON_ACTIVE(void)
{
	return RTE_Read_B_R_PSON_ACTIVE;
}

SINLINE uint8 HWIO_RTE_Read_B_R_VSB_OVP_ACTIVE(void)
{
	return RTE_Read_B_R_VSB_OVP_ACTIVE;
}

SINLINE uint8 HWIO_RTE_Read_B_R_54V_FAULT_ACTIVE(void)
{
	return RTE_Read_B_R_54V_FAULT_ACTIVE;
}

SINLINE uint8 HWIO_RTE_Read_B_R_VIN_OK_ACTIVE(void)
{
	return RTE_Read_B_R_VIN_OK_ACTIVE;
}

SINLINE uint8 HWIO_RTE_Read_B_R_I2C_ADDRESS0(void)
{
	return RTE_Read_B_R_I2C_ADDRESS0;
}

SINLINE uint8 HWIO_RTE_Read_B_R_I2C_ADDRESS1(void)
{
	return RTE_Read_B_R_I2C_ADDRESS1;
}

SINLINE uint8 HWIO_RTE_Read_B_R_I2C_ADDRESS2(void)
{
	return RTE_Read_B_R_I2C_ADDRESS2;
}

SINLINE uint8 HWIO_Rte_Read_B_R_VIN_OK (void)
{
	return RTE_Read_B_R_VIN_OK;
}

SINLINE uint8 HWIO_Rte_Read_B_R_VSB_OVP_TEST(void)
{
	return RTE_Read_B_R_VSB_OVP_TEST;
}

SINLINE uint8 HWIO_Rte_Read_B_R_VSB_OVPTEST_ACTIVE(void)
{
	return RTE_Read_B_R_VSB_OVPTEST_ACTIVE;
}

SINLINE uint8 HWIO_Rte_Read_B_R_OUTPUT_OK (void)
{
	return RTE_Read_B_R_OUTPUT_OK;
}

SINLINE uint8 HWIO_Rte_Read_B_R_VIN_LINE_LOW (void)
{
	return RTE_Read_B_R_VIN_LINE_LOW;
}

SINLINE uint8 HWIO_Rte_Read_B_R_SMBALLERT_ST (void)
{
	return RTE_Read_B_R_SMBALLERT_ST;
}

SINLINE uint8 HWIO_Rte_Read_B_R_V1_ON (void)
{
	return RTE_Read_B_R_V1_ON;
}

SINLINE uint8 HWIO_Rte_Read_B_R_PWOK_ENA  (void)
{
	return RTE_Read_B_R_PWOK_ENA ;
}

SINLINE uint8 HWIN_Rte_Read_B_R_HIGH_LINE_ENA (void)
{
	return RTE_Read_B_R_HIGH_LINE_ENA;
}

SINLINE uint8 HWIO_Rte_Read_B_R_SMBALERT_ENA (void)
{
	return RTE_Read_B_R_SMBALERT_ENA ;
}

SINLINE uint8 HWIO_Rte_Read_B_R_SYNC_INTERNAL_ON (void)
{
	return RTE_Read_B_R_SYNC_INTERNAL_ON ;
}

SINLINE uint8 HWIO_Rte_Read_B_R_VINOK_ENA (void)
{
	return RTE_Read_B_R_VINOK_ENA ;
}

SINLINE uint8 HWIO_Rte_Read_B_R_COM_VIN_OK (void)
{
	return RTE_Read_B_R_COM_VIN_OK ;
}

/* Write */
SINLINE void HWIO_RTE_Write_B_P_PSKILL_ACTIVE(uint8 u8Status)
{
	RTE_Write_B_P_PSKILL_ACTIVE = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_PSON_ACTIVE(uint8 u8Status)
{
	RTE_Write_B_P_PSON_ACTIVE = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_VSB_OVP_ACTIVE(uint8 u8Status)
{
	RTE_Write_B_P_VSB_OVP_ACTIVE = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_54V_FAULT_ACTIVE(uint8 u8Status)
{
	RTE_Write_B_P_54V_FAULT_ACTIVE = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_VIN_OK_ACTIVE(uint8 u8Status)
{
	RTE_Write_B_P_VIN_OK_ACTIVE = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_I2C_ADDRESS0(uint8 u8Status)
{
	RTE_Write_B_P_I2C_ADDRESS0 = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_I2C_ADDRESS1(uint8 u8Status)
{
	RTE_Write_B_P_I2C_ADDRESS1 = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_I2C_ADDRESS2(uint8 u8Status)
{
	RTE_Write_B_P_I2C_ADDRESS2 = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_PWOK_ENA(uint8 u8Status)
{
	RTE_Write_B_P_PWOK_ENA = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_SMBALERT_ENA(uint8 u8Status)
{
	RTE_Write_B_P_SMBALERT_ENA = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_SYNC_INTERNAL_ON(uint8 u8Status)
{
	RTE_Write_B_P_SYNC_INTERNAL_ON = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_VINOK_ENA(uint8 u8Status)
{
	RTE_Write_B_P_VINOK_ENA = u8Status;
}

SINLINE void HWIO_RTE_Wriet_B_P_HIGH_LINE_ENA(uint8 u8Status)
{
	RTE_Write_B_P_HIGH_LINE_ENA = u8Status;
}

SINLINE void HWIO_RTE_Write_B_P_VSB_OVPTEST_ACTIVE(uint8 u8Status)
{
	RTE_Write_B_P_VSB_OVPTEST_ACTIVE = u8Status;
}
SINLINE void HWIO_RTE_Write_B_P_OUTPUT_OK(uint8 u8Status)
{
	RTE_Write_B_P_OUTPUT_OK = u8Status;
}



#ifdef __cplusplus
  }
#endif
#endif  /* HWIO_RTE_H */

  
/*
 * End of file
 */
