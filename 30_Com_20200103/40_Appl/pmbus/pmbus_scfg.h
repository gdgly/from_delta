/** *****************************************************************************
 * \file    pmbus_scfg.h
 * \brief   Server request service file for pmbus.c
 *
 * \section AUTHOR
 *    1. jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-05-08 09:09:27 +0800 (Wed, 08 May 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 179 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PMBUS_SCFG_H
#define PMBUS_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "i2cprt_cfg.h"
#include "i2cprt_api.h"
#include "flash_api.h"
#include "global.h"
#include "uartprt_api.h"
#include "buffer_cfg.h"
#include "buffer_api.h"
#include "mem_api.h"
#include "tempctrl_cfg.h"
#include "tempctrl_api.h"
#include "cali_api.h"
#include "fanctrl_api.h"
#include "blabox_api.h"
#include "tempctrl_cfg.h"
#include "tempctrl_api.h"
		
		
SINLINE void PMBUS_SCFG_vSetBlockWrState(void)
{
	I2CPRT_vSetI2cState(I2CPRT_CFG_E_I2C_BLOCK_WRITE);
}

SINLINE uint32 PMBUS_SCFG_u32ReadWordFlash(uint32 u32Addr)
{
	return FLASH_u32ReadWordFlash(u32Addr);
}

SINLINE void PMBUS_SCFG_vErasePageFlash(uint32 u32Addr)
{
  (void)FLASH_u8ErasePageFlash(u32Addr);
}

SINLINE void PMBUS_SCFG_vWriteWordFlash(uint32 u32Addr, uint32 u32Data)
{
  (void)FLASH_u8WriteWordFlash(u32Addr,u32Data);
}

SINLINE void PMBUS_SCFG_vWriteHalfWordFlash(uint32 u32Addr, uint32 u32Data)
{
  (void)FLASH_u8WriteHalfWordFlash(u32Addr,u32Data);
}

SINLINE void PMBUS_SCFG_vSetBootMode(uint8 u8Index)
{
	UARTPRT_vSetBootMode(u8Index);
}

SINLINE uint16 PMBUS_SCFG_u16GetVsbIntVoltAvg(void)
{
	return BUFFER_u16GetMean1ms(BUFFER_CFG_E_IntVsb);
}

SINLINE uint16 PMBUS_SCFG_u16GetVsbExtVoltAvg(void)
{
	return BUFFER_u16GetMean1ms(BUFFER_CFG_E_ExtVsb);
}

SINLINE uint16 PMBUS_SCFG_u16GetVsbCurrAvg(void)
{
	return BUFFER_u16GetMean1ms(BUFFER_CFG_E_Isb);
}

SINLINE uint16 PMBUS_SCFG_u16GetP1Avg(void)
{
	return BUFFER_u16GetMean10ms(BUFFER_CFG_E_P1);
}

SINLINE uint16 PMBUS_SCFG_u16GetI1Avg(void)
{
	return BUFFER_u16GetMean10ms(BUFFER_CFG_E_I1);
}

SINLINE uint16 PMBUS_SCFG_u16GetIinAvg(void)
{
	return BUFFER_u16GetMean10ms(BUFFER_CFG_E_Iin);
}

SINLINE uint16 PMBUS_SCFG_u16GetPinAvg(void)
{
	return BUFFER_u16GetMean10ms(BUFFER_CFG_E_Pin);
}

SINLINE void PMBUS_SCFG_vReadBlackBoxData(uint8 u8Index, uint8 *pData)
{
	MEM_vReadBlackBoxData(u8Index,pData);
}

SINLINE void PMBUS_SCFG_vWriteBlackBoxData(uint8 u8Index, const uint8 *pData)
{
	MEM_vWriteBlackBoxData(u8Index,pData);
}

SINLINE uint8 PMBUS_SCFG_vReadBlcBoxPageWrDis(void)
{
	return MEM_vReadBlcBoxPageWrDis();;
}

SINLINE void PMBUS_SCFG_vWriteBlcBoxPageWrDis(uint8 u8Data)
{
	MEM_vWriteBlcBoxPageWrDis(u8Data);
}
SINLINE sint16 PMBUS_SCFG_s16ReadInletTemp(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_INLET);
}
SINLINE sint16 PMBUS_SCFG_s16ReadPriPfc(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_PFC);
}

SINLINE sint16 PMBUS_SCFG_s16ReadSecSr(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_SR);
}


SINLINE sint16 PMBUS_SCFG_s16ReadSecOring(void)
{
  return TEMPCTRL_s16ReadTempValue(TEMPCTRL_CFG_E_INDEX_ORING);
}

SINLINE sint16 PMBUS_SCFG_u16ReadAdcAvgInlet(void)
{
  return TEMPCTRL_u16ReadAdcAvgValue(TEMPCTRL_CFG_E_INDEX_INLET);
}

SINLINE void PMBUS_SCFG_vCalibrateV1(void) 
{
  CALI_vCalibrateV1();
}

SINLINE uint16 PMBUS_SCFG_u16ReadFanSpeed(uint8 u8Index)
{
  return FANCTRL_u16ReadFanSpeed(u8Index);
}

SINLINE uint16 PMBUS_SCFG_u16ReadFanCtrlDuty(uint8 u8Index)
{
  return FANCTRL_u16ReadFanCtrlDuty(u8Index);
}

SINLINE void PMBUS_SCFG_vSysSetFanCtrlDuty(uint8 u8Index, uint16 u16Duty)
{
  FANCTRL_vSysSetFanCtrlDuty(u8Index,u16Duty);
}

SINLINE uint8 PMBUS_SCFG_u8ReadFanBitFail(uint8 u8Index)
{
 return FANCTRL_u8ReadFanBitFail(u8Index);
}

SINLINE uint8 PMBUS_SCFG_u8ReadFanBitWarn(uint8 u8Index)
{
 return FANCTRL_u8ReadFanBitWarn(u8Index);
}

SINLINE uint8 PMBUS_SCFG_u8ReadFanBitOvrd(uint8 u8Index)
{
 return FANCTRL_u8ReadFanBitOvrd(u8Index);
}
SINLINE void PMBUS_SCFG_vMFR_ClearBlackBox(void)
{
  BLABOX_vMFR_ClearBlackBox();
}
SINLINE void PMBUS_SCFG_vSetEnableBlackbox(uint8 u8Status)
{
  BLABOX_vSetEnableBlackbox(u8Status);
}
SINLINE void PMBUS_SCFG_vWriteSystemBlackBox(uint8* pu8Buffer)
{
  BLABOX_vMFR_SystemBlackBox(pu8Buffer,TRUE);
}
SINLINE void PMBUS_SCFG_vReadSystemBlackBox(uint8* pu8Buffer)
{
  BLABOX_vMFR_SystemBlackBox(pu8Buffer,FALSE);
}
SINLINE void PMBUS_SCFG_vSetRealTimeClockDataSystemBlackbox(uint32 u32Data)
{
  BLABOX_vSetRealTimeClockDataSystemBlackbox(u32Data);
}

SINLINE uint32 PMBUS_SCFG_u32GetRealTimeClockDataSystemBlackbox(void)
{
  return BLABOX_vGetRealTimeClockDataSystemBlackbox();
}
SINLINE uint8 PMBUS_SCFG_u8GetEnableBlackbox(void)
{
  return BLABOX_vGetEnableBlackbox();
}

SINLINE void PMBUS_SCFG_vReadMfrBlackbox(uint8* pu8Buffer)
{
  (void)BLABOX_vMFR_BLABOX(pu8Buffer);
}

SINLINE void PMBUS_SCFG_vSetOtWarnValue(sint16 s16Data)
{
  TEMPCTRL_vSetOtWarnValue(TEMPCTRL_CFG_E_INDEX_INLET, s16Data);
}

SINLINE void PMBUS_SCFG_vSetFanBlockTest(uint8 u8State)
{
  FANCTRL_vSetFanBlockTest(u8State);
}



#ifdef __cplusplus
  }
#endif
#endif  /* PMBUS_SCFG_H */

  
/*
 * End of file
 */
