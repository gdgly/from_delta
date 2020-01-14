/** *****************************************************************************
 * \file    schm_cfg.h
 * \brief   Server call back service file for schm.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date$
 *  $Author$
 *  $Revision$
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
/* CDD modules */
/* APPL modules */
#define MG_LLCCTRL_MODULE         1
#define MG_ACSCTRL_MODULE         1
#define MG_MONCTRL_MODULE         1
#define MG_TMCTRL_MODULE          1
#define MG_INTCOM_MODULE          1
#define MG_TEMPCTRL_MODULE        1
#define MG_METER_MODULE           1

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
/* CDD modules */
/* APPL modules */
#if MG_LLCCTRL_MODULE
#include "llcctrl_scb.h"
#endif
#if MG_ACSCTRL_MODULE
#include "acsctrl_scb.h"
#endif
#if MG_METER_MODULE
#include "meter_scb.h"
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

/*******************************************************************************
 * Module interface
 ******************************************************************************/

/***************************************
 * BSW modules
 **************************************/
/* RTE module section */
inline void SCHM_cfg_vRteInit(void)
{
  #if MG_RTE_MODULE
  RTE_vInit();
  #endif
}

inline void SCHM_cfg_vRteDeInit(void)
{
  #if MG_RTE_MODULE
  RTE_vDeInit();
  #endif
}

/* HWIO module section */
inline void SCHM_cfg_vHwioInit(void)
{
  #if MG_HWIO_MODULE
  HWIO_vInit();
  #endif
}

inline void SCHM_cfg_vHwioDeInit(void)
{
  #if MG_HWIO_MODULE
  HWIO_vDeInit();
  #endif
}

inline void SCHM_cfg_vHwioReadAdcUnits(void)
{
  #if MG_HWIO_MODULE
  HWIO_vReadAdcUnits();
  #endif
}

inline void SCHM_cfg_vHwioSetGpioPin(void)
{
  #if MG_HWIO_MODULE
  HWIO_vSetGpioPort();
  #endif
}

inline void SCHM_cfg_vHwioReadGpioPin(void)
{
  #if MG_HWIO_MODULE
  HWIO_vReadGpioPort();
  #endif
}

inline void SCHM_cfg_vHwioEnablePwm(void)
{
  #if MG_HWIO_MODULE
  HWIO_vEnablePwm();
  #endif
}

inline void SCHM_cfg_vHwioCheckBootLoaderExistFlg(void)
{
  #if MG_HWIO_MODULE
  HWIO_vCheckBootLoaderExistFlg();
  #endif
}

inline void SCHM_cfg_vHwioReadBootLoaderFwVer(void)
{
  #if MG_HWIO_MODULE
  HWIO_vReadBootLoaderFwVersion();
  #endif
}

/* UART protocol module section */
inline void SCHM_cfg_vUartPrtInit(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vInit();
  #endif
}

inline void SCHM_cfg_vUartPrtDeInit(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vDeInit();
  #endif
}

inline void SCHM_cfg_vUartPrtHandleTxData(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vHandleTxData();
  #endif
}

inline void SCHM_cfg_vUartPrtHandleRxData(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vHandleRxData();
  #endif
}

inline void SCHM_cfg_vUartPrtTxData(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vTxData();
  #endif
}

inline void SCHM_cfg_vUsart2IrqHandler(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vUsart2IrqHandler();
  #endif
}

inline void SCHM_cfg_vUartPrtTmOutMon(void)
{
  #if MG_UARTPRT_MODULE
  UARTPRT_vTmOutMon();
  #endif
}

/* CRC module section */
inline void SCHM_cfg_vCrcInit(void)
{
  #if MG_CRC_MODULE
  CRC_vInit();
  #endif
}

inline void SCHM_cfg_vCrcDeInit(void)
{
  #if MG_CRC_MODULE
  CRC_vDeInit();
  #endif
}

/***************************************
 * CDD modules
 **************************************/

/***************************************
 * APPL modules
 **************************************/
/* LLC control module section */
inline void SCHM_cfg_vLlcCtrlInit(void)
{
  #if MG_LLCCTRL_MODULE
  LLCCTRL_vInit();
  #endif
}

inline void SCHM_cfg_vLlcCtrlDeInit(void)
{
  #if MG_LLCCTRL_MODULE
  LLCCTRL_vDeInit();
  #endif
}

__attribute__((section ("ccram")))  /* Load ISR into CCRAM for max processing speed */
inline void SCHM_cfg_vLlcCtrlIsr(void)
{
  #if MG_LLCCTRL_MODULE
  LLCCTRL_vLlcCtrlIsr();
  #endif
}

inline void SCHM_cfg_vLlcctrlIirRippleFlt(void)
{
  #if MG_LLCCTRL_MODULE
  LLCCTRL_vIirRippleFlt();
  #endif
}

__attribute__((section ("ccram")))  /* Load ISR into CCRAM for max processing speed */
inline void SCHM_cfg_vLlcctrlStatusUpdate(void)
{
  #if MG_LLCCTRL_MODULE
  LLCCTRL_vStatusUpdate();
  #endif
}

inline void SCHM_cfg_vLlcctrlLlHlAdjust(void)
{
  #if MG_LLCCTRL_MODULE
  LLCCTRL_vLlHlAdjust();
  #endif
}

/* Active current share module section */
inline void SCHM_cfg_vAcsctrlInit(void)
{
  #if MG_ACSCTRL_MODULE
  ACSCTRL_vInit();
  #endif
}

inline void SCHM_cfg_vAcsctrlDeInit(void)
{
  #if MG_ACSCTRL_MODULE
  ACSCTRL_vDeInit();
  #endif
}
__attribute__((section ("ccram")))  /* Load ISR into CCRAM for max processing speed */
inline void SCHM_cfg_vAcsctrlActiveCurrShare(void)
{
  #if MG_ACSCTRL_MODULE
  ACSCTRL_vAcsCtrl();
  #endif
}

inline void SCHM_cfg_vAcsctrlSyncCtrl(void)
{
  #if MG_ACSCTRL_MODULE
  ACSCTRL_vSyncCtrl();
  #endif
}

/* Meter module section */
inline void SCHM_cfg_vMeterInit(void)
{
  #if MG_METER_MODULE
  METER_vInit();
  #endif
}

inline void SCHM_cfg_vMeterDeInit(void)
{
  #if MG_METER_MODULE
  METER_vDeInit();
  #endif
}

inline void SCHM_cfg_vMeterAvg(void)
{
  #if MG_METER_MODULE
  METER_vMeterAvg();
  #endif
}

/* Internal communication module section */
inline void SCHM_cfg_vIntComInit(void)
{
  #if MG_INTCOM_MODULE
  INTCOM_vInit();
  #endif
}

inline void SCHM_cfg_vIntComDeInit(void)
{
  #if MG_INTCOM_MODULE
  INTCOM_vDeInit();
  #endif
}

/* Timing control module section */
inline void SCHM_cfg_vTmCtrlInit(void)
{
  #if MG_TMCTRL_MODULE
  TMCTRL_vInit();
  #endif
}

inline void SCHM_cfg_vTmCtrlDeInit(void)
{
  #if MG_TMCTRL_MODULE
  TMCTRL_vDeInit();
  #endif
}

inline void SCHM_cfg_vTmCtrlLlcCtrl(void)
{
  #if MG_TMCTRL_MODULE
  TMCTRL_vLlcCtrl();
  #endif
}

inline void SCHM_cfg_vTmCtrlWriteUpgradeFlgAndReset(void)
{
  #if MG_TMCTRL_MODULE
  TMCTRL_vWriteUpgradeFlgAndReset();
  #endif
}

/* Monitor control module section */
inline void SCHM_cfg_vMonCtrlInit(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vInit();
  #endif
}

inline void SCHM_cfg_vMonCtrlDeInit(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vDeInit();
  #endif
}

inline void SCHM_cfg_vMonCtrlOutFaultMon(void)
{
  #if MG_MONCTRL_MODULE
  MONCTRL_vOutFaultMon();
  #endif
}

/* Temperature control module section */
inline void SCHM_cfg_vTempCtrlInit(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vInit();
  #endif
}

inline void SCHM_cfg_vTempCtrlDeInit(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vDeInit();
  #endif
}

inline void SCHM_cfg_vTempCtrlNtcVoltAverage(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vNtcVoltAverage();
  #endif
}

inline void SCHM_cfg_vTempCtrlNtcOtMonitor(void)
{
  #if MG_TEMPCTRL_MODULE
  TEMPCTRL_vNtcOtMonitor();
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* SCHM_CFG_H */

  
/*
 * End of file
 */
