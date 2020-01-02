/*******************************************************************************
 * \file    dio.c
 * \brief   Read digital input GPIO and write digital output GPIO
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-03-01 14:35:06 +0800 (Fri, 01 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 145 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/* Module header */
#define DIO_EXPORT_H
  #include "hwio_api.h"
  #include "hwio_scb.h"
  #include "hwio_cfg.h"
  #include "hwio_scfg.h"
  #include "hwio_rte.h"
  #include "hwio_conf.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/
/** *****************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vInit(void)
{
}

/** *****************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vDeInit(void)
{

}
/** *****************************************************************************
 * \brief         Enable PWM's
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vEnablePwm(void)
{

}

/** *****************************************************************************
 * \brief         Set GPIO ports
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vSetGpioPort(void)
{
	/* Set Vin OK to system */
	if((HWIO_Rte_Read_B_R_VIN_OK() && HWIO_Rte_Read_B_R_COM_VIN_OK()) != HWIO_Rte_Read_B_R_VINOK_ENA())
	{
		HWIO_SCFG_vSetPortVinOk(HWIO_Rte_Read_B_R_VIN_OK() && HWIO_Rte_Read_B_R_COM_VIN_OK());
		HWIO_RTE_Write_B_P_VINOK_ENA(HWIO_Rte_Read_B_R_VIN_OK()&& HWIO_Rte_Read_B_R_COM_VIN_OK());
	}

	/* Set output power OK */
	if(HWIO_Rte_Read_B_R_OUTPUT_OK()!= HWIO_Rte_Read_B_R_PWOK_ENA())
	{
		HWIO_SCFG_vSetPortOutputOk(HWIO_Rte_Read_B_R_OUTPUT_OK());
		HWIO_RTE_Write_B_P_PWOK_ENA(HWIO_Rte_Read_B_R_OUTPUT_OK());
	}
	
	/* Set SMBAlert  */
	if(HWIO_Rte_Read_B_R_SMBALLERT_ST() != HWIO_Rte_Read_B_R_SMBALERT_ENA())
	{
		HWIO_SCFG_vSetPortSMBAlert(HWIO_Rte_Read_B_R_SMBALLERT_ST());
		HWIO_RTE_Write_B_P_SMBALERT_ENA(HWIO_Rte_Read_B_R_SMBALLERT_ST());
	}
	
	/* Set sync internal */
	if((HWIO_Rte_Read_B_R_V1_ON() && (FALSE == HWIO_RTE_Read_B_R_PSKILL_ACTIVE())) != HWIO_Rte_Read_B_R_SYNC_INTERNAL_ON())
	{
		HWIO_SCFG_vSetPortSyncInt(HWIO_Rte_Read_B_R_V1_ON() && (FALSE == HWIO_RTE_Read_B_R_PSKILL_ACTIVE()));
		HWIO_RTE_Write_B_P_SYNC_INTERNAL_ON(HWIO_Rte_Read_B_R_V1_ON() && (FALSE == HWIO_RTE_Read_B_R_PSKILL_ACTIVE()));
	}
	
	/*** Nokia sHUB 2KW ***/
	/* Set AC_HIGH_LINE_PSUCON, high line is 1;low line is 0*/
	/*  */
	if((HWIO_Rte_Read_B_R_VIN_LINE_LOW()))
	{
		
		HWIO_RTE_Write_B_P_VINOK_ENA(HWIO_Rte_Read_B_R_VIN_LINE_LOW());
	}
	else
	{
		
	}
	
}

/** *****************************************************************************
 * \brief         Read GPIO ports
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vReadGpioPort(void)
{
  static uint16 u16PsKillCountSet    = 0;
	static uint16 u16PsKillCountClear  = 0;
  static uint16 u16PsOnCountSet      = 0;
	static uint16 u16PsOnCountClear    = 0;
  static uint8 u8VmFaultCountSet   = 0;
	static uint8 u8VmFaultCountClear = 0;
  static uint8 u8VinOkCountSet     = 0;
	static uint8 u8VinOkCountClear   = 0;	
	static uint8 u8I2cA0CountSet     = 0;
	static uint8 u8I2cA0CountClear   = 0;
	static uint8 u8I2cA1CountSet     = 0;
	static uint8 u8I2cA1CountClear   = 0;
	static uint8 u8I2cA2CountSet     = 0;
	static uint8 u8I2cA2CountClear   = 0;

  /************ 1. PS Kill *************/
  if(HWIO_SCFG_u8RdPortPsKill() != FALSE)
  {
    if(HWIO_CONFG_PSKILL_SET_CNT < u16PsKillCountSet)
    { 
      HWIO_RTE_Write_B_P_PSKILL_ACTIVE(TRUE);
    }
    else if(HWIO_CONFG_PSKILL_SET_CNT >= u16PsKillCountSet)
    {
      u16PsKillCountSet++;
    }
		u16PsKillCountClear = 0;
  }
	else
  {
    if(HWIO_CONFG_PSKILL_RESET_CNT < u16PsKillCountClear)
    { 
      HWIO_RTE_Write_B_P_PSKILL_ACTIVE(FALSE);
    }
    else if(HWIO_CONFG_PSKILL_RESET_CNT >= u16PsKillCountClear)
    {
      u16PsKillCountClear++;
    }
		u16PsKillCountSet = 0;
  }
	
  /************ 2. PS ON *************/
  if(HWIO_SCFG_u8RdPortPsOn() == TRUE)
  {
    if(HWIO_CONFG_PSON_SET_CNT < u16PsOnCountSet)
    { 
      HWIO_RTE_Write_B_P_PSON_ACTIVE(FALSE);
    }
    else if(HWIO_CONFG_PSON_SET_CNT >= u16PsOnCountSet)
    {
      u16PsOnCountSet++;
    }
		u16PsOnCountClear = 0;
  }
	else
  {
    if(HWIO_CONFG_PSON_RESET_CNT < u16PsOnCountClear)
    { 
      HWIO_RTE_Write_B_P_PSON_ACTIVE(TRUE);
    }
    else if(HWIO_CONFG_PSON_RESET_CNT >= u16PsOnCountClear)
    {
      u16PsOnCountClear++;
    }
		u16PsOnCountSet = 0;
  }
	
  /************ 3. Vmain fault *************/
  if(HWIO_SCFG_u8RdPortVmFault() != FALSE)
  {
    if(HWIO_CONFG_VMAIN_FAULT_SET_CNT < u8VmFaultCountSet)
    { 
      HWIO_RTE_Write_B_P_54V_FAULT_ACTIVE(TRUE);
    }
    else if(HWIO_CONFG_VMAIN_FAULT_SET_CNT >= u8VmFaultCountSet)
    {
      u8VmFaultCountSet++;
    }
		
		HWIO_RTE_Write_B_P_OUTPUT_OK(FALSE);
		u8VmFaultCountClear = 0;
  }
	else
  {
    if(HWIO_CONFG_VMAIN_FAULT_RESET_CNT < u8VmFaultCountClear)
    { 
      HWIO_RTE_Write_B_P_54V_FAULT_ACTIVE(FALSE);
    }
    else if(HWIO_CONFG_VMAIN_FAULT_RESET_CNT >= u8VmFaultCountClear)
    {
      u8VmFaultCountClear++;
    }
		u8VmFaultCountSet = 0;
  }
	
  /************ 5. Vin Ok *************/
  if(HWIO_SCFG_u8RdPortVinOk() != FALSE)
  {
    if(HWIO_CONFG_VIN_OK_SET_CNT < u8VinOkCountSet)
    { 
      HWIO_RTE_Write_B_P_VIN_OK_ACTIVE(TRUE);
    }
    else if(HWIO_CONFG_VIN_OK_SET_CNT >= u8VinOkCountSet)
    {
      u8VinOkCountSet++;
    }
		u8VinOkCountClear = 0;
  }
	else
  {
    if(HWIO_CONFG_VIN_OK_RESET_CNT < u8VinOkCountClear)
    { 
      HWIO_RTE_Write_B_P_VIN_OK_ACTIVE(FALSE);
    }
    else if(HWIO_CONFG_VIN_OK_RESET_CNT >= u8VinOkCountClear)
    {
      u8VinOkCountClear++;
    }
		u8VinOkCountSet = 0;
  }
	
  if(HWIO_SCFG_u8RdPortA0() != FALSE)
  {
    if(HWIO_CONFG_A0_SET_CNT < u8I2cA0CountSet)
    { 
      HWIO_RTE_Write_B_P_I2C_ADDRESS0(TRUE);
    }
    else if(HWIO_CONFG_A0_SET_CNT >= u8I2cA0CountSet)
    {
      u8I2cA0CountSet++;
    }
		u8I2cA0CountClear = 0;
  }
	else
  {
    if(HWIO_CONFG_A0_RESET_CNT < u8I2cA0CountClear)
    { 
      HWIO_RTE_Write_B_P_I2C_ADDRESS0(FALSE);
    }
    else if(HWIO_CONFG_A0_RESET_CNT >= u8I2cA0CountClear)
    {
      u8I2cA0CountClear++;
    }
		u8I2cA0CountSet = 0;
  }
	
  if(HWIO_SCFG_u8RdPortA1() != FALSE)
  {
    if(HWIO_CONFG_A1_SET_CNT < u8I2cA1CountSet)
    { 
      HWIO_RTE_Write_B_P_I2C_ADDRESS1(TRUE);
    }
    else if(HWIO_CONFG_A1_SET_CNT >= u8I2cA1CountSet)
    {
      u8I2cA1CountSet++;
    }
		u8I2cA1CountClear = 0;
  }
	else
  {
    if(HWIO_CONFG_A1_RESET_CNT < u8I2cA1CountClear)
    { 
      HWIO_RTE_Write_B_P_I2C_ADDRESS1(FALSE);
    }
    else if(HWIO_CONFG_A1_RESET_CNT >= u8I2cA1CountClear)
    {
      u8I2cA1CountClear++;
    }
		u8I2cA1CountSet = 0;
  }
	
  if(HWIO_SCFG_u8RdPortA2() != FALSE)
  {
    if(HWIO_CONFG_A2_SET_CNT < u8I2cA2CountSet)
    { 
      HWIO_RTE_Write_B_P_I2C_ADDRESS2(TRUE);
    }
    else if(HWIO_CONFG_A2_SET_CNT >= u8I2cA2CountSet)
    {
      u8I2cA2CountSet++;
    }
		u8I2cA2CountClear = 0;
  }
	else
  {
    if(HWIO_CONFG_A2_RESET_CNT < u8I2cA2CountClear)
    { 
      HWIO_RTE_Write_B_P_I2C_ADDRESS2(FALSE);
    }
    else if(HWIO_CONFG_A2_RESET_CNT >= u8I2cA2CountClear)
    {
      u8I2cA2CountClear++;
    }
		u8I2cA2CountSet = 0;
  }
}

/** *****************************************************************************
 * \brief         Read boot loader existing flag from flash and write it to RTE
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void HWIO_vCheckBootLoaderExistFlg(void)
{

}


/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/*
 * End of file
 */
