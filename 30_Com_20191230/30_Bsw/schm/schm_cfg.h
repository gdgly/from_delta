/** *****************************************************************************
 * \file    schm_cfg.h
 * \brief   Server call back service file for schm.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-10-14 17:07:42 +0800 (Mon, 14 Oct 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 234 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef SCHM_CFG_H
#define SCHM_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
/* BSW modules */
#define MG_RTE_MODULE             1
#define MG_HWIO_MODULE            1
#define MG_UARTPRT_MODULE         1
#define MG_CRC_MODULE             1
#define MG_BUFFER_MODULE          1
#define MG_EEPROM_MODULE          1
#define MG_I2CPRT_MODULE          1
#define MG_CALI_MODULE            1
#define MG_MEM_MODULE             1
/* CDD modules */
/* APPL modules */
#define MG_EXTCTRL_MODULE         0
#define MG_MONCTRL_MODULE         1
#define MG_TMCTRL_MODULE          0
#define MG_INTCOM_MODULE          1
#define MG_TEMPCTRL_MODULE        1
#define MG_METER_MODULE           0
#define MG_PMBUS_MODULE           1
#define MG_FANCTRL_MODULE         1
#define MG_LEDCTRL_MODULE         1
#define MG_TIMECTRL_MODULE        1
#define MG_PSUCTRL_MODULE         1
#define MG_BLABOX_MODULE          1

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/* BSW modules */
#if MG_RTE_MODULE
#include "rte.h"
#endif
#if MG_HWIO_MODULE
#include "hwio_scb.h"
#endif
#if MG_UARTPRT_MODULE
#include "uartprt_scb.h"
#endif
#if MG_CRC_MODULE
#include "crc_scb.h"
#endif
#if MG_BUFFER_MODULE
#include "buffer_scb.h"
#endif
#if MG_EEPROM_MODULE
#include "eeprom_scb.h"
#endif
#if MG_I2CPRT_MODULE
#include "i2cprt_scb.h"
#endif
#if MG_CALI_MODULE
#include "cali_scb.h"
#endif
#if MG_MEM_MODULE
#include "mem_scb.h"
#endif
/* CDD modules */
/* APPL modules */
#if MG_PFCCTRL_MODULE
#include "pfcctrl_scb.h"
#endif
#if MG_EXTCTRL_MODULE
#include "extctrl_scb.h"
#endif
#if MG_BUFFER_MODULE
#include "buffer_scb.h"
#endif
#if MG_MONCTRL_MODULE
#include "monctrl_scb.h"
#endif
#if MG_TMCTRL_MODULE
#include "tmctrl_scb.h"
#endif
#if MG_INTCOM_MODULE
#include "intcom_scb.h"
#endif
#if MG_TEMPCTRL_MODULE
#include "tempctrl_scb.h"
#endif
#if MG_PMBUS_MODULE
#include "pmbus_scb.h"
#endif
#if MG_FANCTRL_MODULE 
#include "fanctrl_scb.h"
#endif
#if MG_LEDCTRL_MODULE 
#include "ledctrl_scb.h"
#endif
#if MG_TIMECTRL_MODULE
#include "timectrl_scb.h"
#endif
#if MG_PSUCTRL_MODULE
#include "psuctrl_scb.h"
#endif
#if MG_BLABOX_MODULE
#include "blabox_scb.h"
#endif


/*******************************************************************************
 * Module interface
 ******************************************************************************/

/***************************************
 * BSW modules
 **************************************/
/* RTE module section */
SINLINE void SCHM_cfg_vRteInit(void)
{
  #if MG_RTE_MODULE
  RTE_vInit();
  #endif
}

SINLINE void SCHM_cfg_vRteDeInit(void)
{
  #if MG_RTE_MODULE
  RTE_vDeInit();
  #endif
}

/* HWIO module section */
SINLINE void SCHM_cfg_vHwioInit(void)
{
  #if MG_HWIO_MODULE
  HWIO_vInit();
  #endif
}

SINLINE void SCHM_cfg_vHwioDeInit(void)
{
  #if MG_HWIO_MODULE
  HWIO_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vHwioReadAdcUnits(void)
{
  #if MG_HWIO_MODULE
  HWIO_vReadAdcUnits();
  #endif
}

SINLINE void SCHM_cfg_vHwioSetGpioPin(void)
{
  #if MG_HWIO_MODULE
  HWIO_vSetGpioPort();
  #endif
}

SINLINE void SCHM_cfg_vHwioReadGpioPin(void)
{
  #if MG_HWIO_MODULE
  HWIO_vReadGpioPort();
  #endif
}

SINLINE void SCHM_cfg_vHwioEnablePwm(void)
{
  #if MG_HWIO_MODULE
  HWIO_vEnablePwm();
  #endif
}

SINLINE void SCHM_cfg_vHwioCheckBootLoaderExistFlg(void)
{
  #if MG_HWIO_MODULE
  HWIO_vCheckBootLoaderExistFlg();
  #endif
}

/* UART protocol module section */
SINLINE void SCHM_cfg_vUartPrtInit(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vInit();
  #endif
}

SINLINE void SCHM_cfg_vUartPrtDeInit(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vUartPrtHandleTxData(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vHandleTxData();
  #endif
}

SINLINE void SCHM_cfg_vUartPrtHandleRxData(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vHandleRxData();
  #endif
}

SINLINE void SCHM_cfg_vUartPrtTxData(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vTxData();
  #endif
}

SINLINE void SCHM_cfg_vUartPrtTmOutMon(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vTmOutMon();
  #endif
}

/* CRC module section */
SINLINE void SCHM_cfg_vCrcInit(void)
{
  #if MG_CRC_MODULE
  CRC_vInit();
  #endif
}

SINLINE void SCHM_cfg_vCrcDeInit(void)
{
  #if MG_CRC_MODULE
  CRC_vDeInit();
  #endif
}

/* Buffer module section*/
SINLINE void SCHM_cfg_vBufferInit(void)
{
  #if MG_BUFFER_MODULE
	BUFFER_SCB_vInit();
	#endif
}

SINLINE void SCHM_cfg_vBufferDeInit(void)
{
  #if MG_BUFFER_MODULE
	BUFFER_SCB_vDeInit();
	#endif
}

SINLINE void SCHM_cfg_vBufferCalc1ms(void)
{
  #if MG_BUFFER_MODULE
	BUFFER_SCB_vLoop1msTask();
	#endif
}

SINLINE void SCHM_cfg_vBufferCalc10ms(void)
{
  #if MG_BUFFER_MODULE
	BUFFER_SCB_vLoop10msTask();
	#endif
}

/* EEPROM module section*/
SINLINE void SCHM_cfg_vEepromInit(void)
{
  #if MG_EEPROM_MODULE
	EEPROM_vInit();
	#endif
}

SINLINE void SCHM_cfg_vEepromDeInit(void)
{
  #if MG_EEPROM_MODULE
	EEPROM_vDeInit();
	#endif
}

/* I2CPRT module section*/
SINLINE void SCHM_cfg_vI2cprtInit(void)
{
  #if MG_I2CPRT_MODULE
	I2CPRT_vInit();
	#endif
}

SINLINE void SCHM_cfg_vI2cprtDeInit(void)
{
  #if MG_I2CPRT_MODULE
	I2CPRT_vDeInit();
	#endif
}

SINLINE void SCHM_cfg_vI2cprtUpdateI2cAddr(void)
{
  #if MG_I2CPRT_MODULE
//	I2CPRT_vUpdateI2cAddress(20u);
	#endif
}

SINLINE void SCHM_cfg_vI2cprtProcessRxData(void)
{
  #if MG_I2CPRT_MODULE
	I2CPRT_vProcessReceiveData();
	#endif
}

/* CALI module section*/
SINLINE void SCHM_cfg_vCaliInit(void)
{
  #if MG_CALI_MODULE
	CALI_vInit();
	#endif
}

SINLINE void SCHM_cfg_vCaliDeInit(void)
{
  #if MG_CALI_MODULE
	CALI_vDeInit();
	#endif
}

SINLINE void SCHM_cfg_vCaliHandler(void)
{
  #if MG_CALI_MODULE
	CALI_vCaliHandler();
	#endif
}

SINLINE void SCHM_cfg_vCaliFast(void)
{
  #if MG_CALI_MODULE
	CALI_vCaliFast();
	#endif
}

SINLINE void SCHM_cfg_vCalcCaliPara(void)
{
  #if MG_CALI_MODULE
	CALI_vCalcCaliPara();
	#endif
}



SINLINE void SCHM_cfg_vCalibrateIShare(void)
{
  #if MG_CALI_MODULE
	CALI_vCalibrateIShare();
	#endif
}

/* memory manager module section*/
SINLINE void SCHM_cfg_vMemInit(void)
{
  #if MG_MEM_MODULE
	MEM_vInit();
	#endif
}

SINLINE void SCHM_cfg_vMemDeInit(void)
{
  #if MG_MEM_MODULE
	MEM_vDeInit();
	#endif
}

SINLINE void SCHM_cfg_vMemSaveData(void)
{
  #if MG_MEM_MODULE
	MEM_vSaveData();
	#endif
}

/***************************************
 * CDD modules
 **************************************/

/***************************************
 * APPL modules
 **************************************/
/* PFC control module section */

/* Extender control module section */

/* Internal communication module section */
SINLINE void SCHM_cfg_vIntComInit(void)
{
  #if MG_INTCOM_MODULE
  INTCOM_vInit();
  #endif
}

SINLINE void SCHM_cfg_vIntComDeInit(void)
{
  #if MG_INTCOM_MODULE
  INTCOM_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vIntComTmOutMOn(void)
{
  #if MG_INTCOM_MODULE
  INTCOM_vTmOutMon();
  #endif
}

/* Monitor control module section */
SINLINE void SCHM_cfg_vMonCtrlInit(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vInit();
  #endif
}

SINLINE void SCHM_cfg_vMonCtrlDeInit(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vMonCtrlUpdateStatus(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vUpdateStatus();
  #endif
}

SINLINE void SCHM_cfg_vMonCtrlAxuModeDetect(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vAxuModeDetect();
  #endif
}

SINLINE void SCHM_cfg_vMonCtrlCheckStatusReset(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vCheckStatusReset();
  #endif
}

SINLINE void SCHM_cfg_vMonCtrlVin(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vVin();
  #endif
}


SINLINE void SCHM_cfg_vMonCtrlCheckVsbOvp(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vCheckVsbOvp();
  #endif
}

SINLINE void SCHM_cfg_vMonCtrlVsbOutput(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vVsbOutput();
  #endif
}



/* Temperature control module section */
SINLINE void SCHM_cfg_vTempCtrlInit(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vInit();
  #endif
}

SINLINE void SCHM_cfg_vTempCtrlDeInit(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vTempCtrlNtcVoltAverage(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vNtcVoltAverage();
  #endif
}

SINLINE void SCHM_cfg_vTempCtrlLookUpNtcTemperature(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vLookUpNtcTemperature();
  #endif
}

SINLINE void SCHM_cfg_vTempCtrlNtcVoltMonitor(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vNtcTempMonitor();
  #endif
}

/* pmbus module section */
SINLINE void SCHM_cfg_vPmbusInit(void)
{
  #if MG_PMBUS_MODULE
  PMBUS_vInit();
  #endif
}

SINLINE void SCHM_cfg_vPmbusDeInit(void)
{
  #if MG_PMBUS_MODULE
  PMBUS_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vPmbusCheckBootMode(void)
{
  #if MG_PMBUS_MODULE
  PMBUS_vCheckBootMode();
  #endif
}

SINLINE void SCHM_cfg_vPmbusCopySensorData(void)
{
  #if MG_PMBUS_MODULE
  PMBUS_vCopySensorData();
  #endif
}


SINLINE void SCHM_cfg_vPmbusCopyStatusData(void)
{
  #if MG_PMBUS_MODULE
  PMBUS_vCopyStatusData();
  #endif
}


SINLINE void SCHM_cfg_vPmbusCopyPecAndOringStatus(void)
{
  #if MG_PMBUS_MODULE
  PMBUS_vCopyPecAndOringStatus();
  #endif
}

SINLINE void SCHM_cfg_vPmbusCopyDebugData(void)
{
  #if MG_PMBUS_MODULE
  PMBUS_vCopyDebugData();
  #endif
}

/* fanctrl module section */
SINLINE void SCHM_cfg_vFanCtrlInit(void)
{
  #if MG_FANCTRL_MODULE
  FANCTRL_vInit();
  #endif
}

SINLINE void SCHM_cfg_vFanCtrlDeInit(void)
{
  #if MG_FANCTRL_MODULE
  FANCTRL_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vFanCtrl(void)
{
  #if MG_FANCTRL_MODULE
  FANCTRL_vFanCtrl();
  #endif
}

SINLINE void SCHM_cfg_vFanSpeedCalc(void)
{
  #if MG_FANCTRL_MODULE
  FANCTRL_vFanSpeedCalc();
  #endif
}

SINLINE void SCHM_cfg_vFanSpeedCnt(void)
{
  #if MG_FANCTRL_MODULE
  FANCTRL_vFanSpeedCnt();
  #endif
}

/* ledctrl module section */
SINLINE void SCHM_cfg_vLedCtrlInit(void)
{
  #if MG_LEDCTRL_MODULE
  LEDCTRL_vInit();
  #endif
}

SINLINE void SCHM_cfg_vLedCtrlDeInit(void)
{
  #if MG_LEDCTRL_MODULE
  LEDCTRL_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vLedControl(void)
{
  #if MG_LEDCTRL_MODULE
  LEDCTRL_vLedControl();
  #endif
}

/* timectrl module section */
SINLINE void SCHM_cfg_vTimeCtrlInit(void)
{
  #if MG_TIMECTRL_MODULE
  TIMECTRL_vInit();
  #endif
}

SINLINE void SCHM_cfg_vTimeCtrlDeInit(void)
{
  #if MG_TIMECTRL_MODULE
  TIMECTRL_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vTimeCtrlSaveHoursUsed(void)
{
  #if MG_TIMECTRL_MODULE
  TIMECTRL_vSaveHoursUsed();
  #endif
}

/* psuctrl module section */
SINLINE void SCHM_cfg_vPsuCtrlInit(void)
{
  #if MG_PSUCTRL_MODULE
  PSUCTRL_vInit();
  #endif
}

SINLINE void SCHM_cfg_vPsuCtrlDeInit(void)
{
  #if MG_PSUCTRL_MODULE
  PSUCTRL_vDeInit();
  #endif
}

SINLINE void SCHM_cfg_vPsuCtrlVsbOut(void)
{
  #if MG_PSUCTRL_MODULE
  PSUCTRL_vVsbOut();
  #endif
}

SINLINE void SCHM_cfg_vPsuCtrlV1Out(void)
{
  #if MG_PSUCTRL_MODULE
  PSUCTRL_vV1Out();
  #endif
}

SINLINE void SCHM_cfg_vPsuCtrlTrim(void)
{
  #if MG_PSUCTRL_MODULE
  PSUCTRL_vTrim();
  #endif
}

SINLINE void SCHM_cfg_vPsuCtrlTestOutputOring(void)
{
  #if MG_PSUCTRL_MODULE
//  PSUCTRL_vTestOutputOring();
  #endif
}

SINLINE void SCHM_cfg_vPsuCtrlV1OffDly4VsbOff(void)
{
  #if MG_PSUCTRL_MODULE
 // PSUCTRL_vV1OffDly4VsbOff();
  #endif
}

/* blabox module section */
SINLINE void SCHM_cfg_vBlaboxInit(void)
{
  #if MG_BLABOX_MODULE
  BLABOX_vInit();
  #endif
}

SINLINE void SCHM_cfg_vProcessBlackbox(void)
{
  #if MG_BLABOX_MODULE
  BLABOX_vProcessBlackbox();
  #endif
}

SINLINE void SCHM_cfg_vCheckPSONBlackBox(void)
{
  #if MG_BLABOX_MODULE
  BLABOX_vMFR_CheckPSONBlackBox();
  #endif
}
SINLINE void SCHM_cfg_vCheckACBlackBox(void)
{
  #if MG_BLABOX_MODULE
  BLABOX_vMFR_CheckACBlackBox();
  #endif
}
SINLINE void SCHM_cfg_vTimePSONBlackBox(void)
{
  #if MG_BLABOX_MODULE
  BLABOX_vMFR_TimePSONBlackBox();
  #endif
}
SINLINE void SCHM_cfg_vCountRealTimeClockDataSystemBlackbox(void)
{
  #if MG_BLABOX_MODULE
  BLABOX_vCountRealTimeClockDataSystemBlackbox();
  #endif
}
SINLINE void SCHM_cfg_vClearWarning(void)
{
  #if MG_BLABOX_MODULE
  BLABOX_vClearWarning();
  #endif
}



#ifdef __cplusplus
  }
#endif
#endif  /* SCHM_CFG_H */

  
/*
 * End of file
 */
