/** *****************************************************************************
 * \file    hwio_scfg.h
 * \brief   Server request service file for hwio.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-09-10 08:40:13 +0800 (Mon, 10 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 24 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef HWIO_SCFG_H
#define HWIO_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/

    
/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"
#include "port_cfg.h"
#include "port_api.h"

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* ADC module section */
SINLINE uint8 HWIO_SCFG_u8RdPortPsKill(void)
{
	return PORT_u8ReadGpioPin(PORT_CFG_E_A15_PSKILL);
}

SINLINE uint8 HWIO_SCFG_u8RdPortPsOn(void)
{
	return PORT_u8ReadGpioPin(PORT_CFG_E_A10_PSON_L);
}

SINLINE uint8 HWIO_SCFG_u8RdPortVmFault(void)
{
	return PORT_u8ReadGpioPin(PORT_CFG_E_B0_54V_FAULT);
}

SINLINE uint8 HWIO_SCFG_u8RdPortVinOk(void)
{
	return PORT_u8ReadGpioPin(PORT_CFG_E_B13_VIN_OK_IN);
}

SINLINE uint8 HWIO_SCFG_u8RdPortA0(void)
{
	return PORT_u8ReadGpioPin(PORT_CFG_E_B5_I2C_PA0);
}

SINLINE uint8 HWIO_SCFG_u8RdPortA1(void)
{
	return PORT_u8ReadGpioPin(PORT_CFG_E_B4_I2C_PA1);
}

SINLINE void HWIO_SCFG_vSetPortVinOk(uint8 u8Status)
{
	PORT_vSetGpioPin(PORT_CFG_E_B14_ACOK_OUT,u8Status);
}

SINLINE void HWIO_SCFG_vSetPortOutputOk(uint8 u8Status)
{
	PORT_vSetGpioPin(PORT_CFG_E_A11_PW_OK,u8Status);
}

SINLINE void HWIO_SCFG_vSetPortSMBAlert(uint8 u8Status)
{
	PORT_vSetGpioPin(PORT_CFG_E_A12_SMBALERT_L,u8Status);
}

SINLINE void HWIO_SCFG_vSetPortSyncInt(uint8 u8Status)
{
	PORT_vSetGpioPin(PORT_CFG_E_B12_SYNC_INTERNAL,(u8Status==FALSE?TRUE:FALSE));
}

SINLINE void HWIO_SCFG_vSetVsbOvp(uint8 u8Status)
{
	PORT_vSetGpioPin(PORT_CFG_E_A7_VSB_OVP_TEST,(u8Status==FALSE?TRUE:FALSE));
}

SINLINE void HWIO_SCFG_vSetVinLine(uint8 u8Status)
{
	PORT_vSetGpioPin(PORT_CFG_E_B3_VIN_LINE,(u8Status==FALSE?TRUE:FALSE));
}
#ifdef __cplusplus
  }
#endif
#endif  /* HWIO_SCFG_H */

  
/*
 * End of file
 */
