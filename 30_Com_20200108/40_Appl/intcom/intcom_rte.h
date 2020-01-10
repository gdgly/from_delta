/** *****************************************************************************
 * \file    intcom_rte.h
 * \brief   RTE interface for intcom.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-11-22 11:01:57 +0800 (Fri, 22 Nov 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 239 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef INTCOM_RTE_H
#define INTCOM_RTE_H
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
#define RTE_Read_B_R_PRI_VIN_OK                      (RTE_B_PRI_VIN_OK)
#define RTE_Read_B_R_PRI_VIN_LINE                    (RTE_B_PRI_VIN_LINE_LOW)
#define RTE_Read_B_R_PRI_VIN_DROPOUT                 (RTE_B_PRI_VIN_DROPOUT)
#define RTE_Read_B_R_VIN_OK_ACTIVE                   (RTE_B_DIO_VIN_OK_ACTIVE)
#define RTE_Read_B_R_AC_OFFSET_SAVEED                (RTE_B_COM_AC_OFFSET_SAVEED) 
#define RTE_Read_B_R_IIN_OFFSET_CALIB                (RTE_B_IIN_OFFSET_CALIB)
#define RTE_Read_B_R_COM_V1_MONI_EN                  (RTE_B_COM_V1_MONI_EN)

#define RTE_Read_B_R_SEC_OVP                          (RTE_B_SEC_OVP)
#define RTE_Read_B_R_SEC_UVP                          (RTE_B_SEC_UVP)
#define RTE_Read_B_R_SEC_OCP                          (RTE_B_SEC_OCP)
#define RTE_Read_B_R_SEC_OCW                          (RTE_B_SEC_OCW)
#define RTE_Read_B_R_SEC_OCP_CT                      (RTE_B_SEC_OCP_CT)
#define RTE_Read_B_R_SEC_OPP                         (RTE_B_SEC_OPP)
  
#define RTE_Write_B_P_AC_LOST                        (RTE_B_TO_SEC_STA_AC_LOST)
#define RTE_Write_B_P_VIN_LINE_LOW                   (RTE_B_TO_SEC_STA_VIN_LINE_LOW)
#define RTE_Write_B_P_PRI_UART_FAIL                  (RTE_B_PRI_UART_FAIL)
#define RTE_Write_B_P_SEC_UART_FAIL                  (RTE_B_SEC_UART_FAIL)
#define RTE_Write_B_P_PRI_NO_RX_PKG                  (RTE_B_PRI_NO_RX_PKG)
#define RTE_Write_B_P_SEC_NO_RX_PKG                  (RTE_B_SEC_NO_RX_PKG)
#define RTE_Write_B_P_PRI_RX_PKG                     (RTE_B_PRI_RX_PKG)
#define RTE_Write_B_P_SEC_RX_PKG                     (RTE_B_SEC_RX_PKG)
#define RTE_Write_B_P_PRI_REV_UPDATE                 (RTE_B_PRI_REV_UPDATE)
#define RTE_Write_B_P_SEC_REV_UPDATE                 (RTE_B_SEC_REV_UPDATE)
#define RTE_Write_B_P_COMMS_FAULT                    (PMBUS_tStatus.u8StatusCmlP0.Bits.COMMS_FAULT)         
#define RTE_Write_B_P_AC_OFFSET_NEED_SAVE            (RTE_B_COM_AC_OFFSET_NEED_SAVE)        
#define RTE_Write_B_P_V1_OVP                         (RTE_B_COM_V1_OVP)
#define RTE_Write_B_P_V1_UVP                         (RTE_B_COM_V1_UVP)
#define RTE_Write_B_P_V1_OCP                         (RTE_B_COM_V1_OCP)
#define RTE_Write_B_P_V1_OCW                         (RTE_B_COM_V1_OCW)


#define Rte_Write_P_u32AppFwRevPri(var)              (RTE_u32PmbusFwRevPri1.u32Val = (var))
#define Rte_Write_P_u32BootFwRevPri(var)             (RTE_u32PmbusBootFwRevPri1.u32Val = (var))
#define Rte_Write_P_uPfcStatus00(var)                (RTE_Pri.u16PriStatus00.ALL = (var))
#define Rte_Write_P_uPfcStatus01(var)                (RTE_Pri.u16PriStatus01.ALL = (var))
#define Rte_Write_P_uTempStatus00Pri(var)            (RTE_Pri.uTempStatus00.ALL = (var))
#define Rte_Write_P_u16DebugData0Pri(var)            (RTE_Pri.u16PriDebug0.u16Val = (var))
#define Rte_Write_P_u16DebugData1Pri(var)            (RTE_Pri.u16PriDebug1.u16Val = (var))
#define Rte_Write_P_u16DebugData2Pri(var)            (RTE_Pri.u16PriDebug2.u16Val = (var))
#define Rte_Write_P_u1610mVVinRmsAvg(var)            (RTE_Pri.u1610mVVinAvg.u16Val = (var))
#define Rte_Write_P_u161mAIinRmsAvg(var)             (RTE_Pri.u161mAIinAvg.u16Val = (var))
#define Rte_Write_P_u16100mWPwrInRmsAvg(var)         (RTE_Pri.u16100mAPinAvg.u16Val = (var))
#define Rte_Write_P_u16100mHzVoltInFreq(var)         (RTE_Pri.u16100mHzVoltInFreq.u16Val = (var))
#define Rte_Write_P_u16q16PwrFact(var)               (RTE_Pri.u16q16PwrFact.u16Val = (var))
#define Rte_Write_P_u16PfcNtcAdcAvg(var)             (RTE_Pri.u16PfcNtcAdcAvg.u16Val = (var))
#define Rte_Write_P_u16VbulkAdc(var)                 (RTE_Pri.u16q12VbulkAdc.u16Val  = (var))
#define Rte_Write_P_uPriComStatus(var)               (RTE_Pri.uComStatus.ALL  = (var))
#define Rte_Write_P_s16AcOffset(var)                 (RTE_Pri.u16AcOffset.s16Val = (var))
#define Rte_Write_P_u16LlcNtcAdcAvg(var)             (RTE_Pri.u16LlcNtcAdcAvg.u16Val = (var))
#define Rte_Write_P_u16FanCnt(index,var)			  		 (RTE_Pri.u16FanCnt[index].u16Val = (var))

#define Rte_Write_P_u32AppFwRevSec(var)              (RTE_u32PmbusFwRevSec1.u32Val = (var))                          
#define Rte_Write_P_u32BootFwRevSec(var)             (RTE_u32PmbusBootFwRevSec1.u32Val = (var))                          
#define Rte_Write_P_u16LlcStatus00(var)              (RTE_Sec.u16SecStatus00.ALL = (var))                          
#define Rte_Write_P_u16LlcStatus01(var)              (RTE_Sec.u16SecStatus01.ALL = (var))                          
#define Rte_Write_P_u16LlcStatus02(var)              (RTE_Sec.u16SecStatus02.ALL = (var))                          
#define Rte_Write_P_u8TempStatus00Sec(var)           (RTE_Sec.uTempStatus00.ALL = (var))                          
#define Rte_Write_P_u16DebugData0Sec(var)            (RTE_Sec.u16SecDebug0.u16Val = (var))                          
#define Rte_Write_P_u16DebugData1Sec(var)            (RTE_Sec.u16SecDebug1.u16Val = (var))                          
#define Rte_Write_P_u16DebugData2Sec(var)            (RTE_Sec.u16SecDebug2.u16Val = (var))                          
#define Rte_Write_P_u1610mVV1ExtAvg(var)             (RTE_Sec.u1610mVExtV1Avg.u16Val = (var))  
#define Rte_Write_P_u1610mVV1IntExtAvg(var)          (RTE_Sec.u1610mVIntV1Avg.u16Val = (var))   
#define Rte_Write_P_u161mAIV1Avg(var)                (RTE_Sec.u1610mAIoutAvg.u16Val = (var))                          
#define Rte_Write_P_u16100mWPwrOutAvg(var)           (RTE_Sec.u16100mWPwrOutAvg.u16Val = (var))                          
#define Rte_Write_P_u16SrNtcAdcAvg(var)              (RTE_Sec.u161mVSrNtcAvg.u16Val = (var))                          
#define Rte_Write_P_u16OringNtcAdcAvg(var)           (RTE_Sec.u161mVOringNtcAvg.u16Val = (var))   
#define Rte_Write_P_u16VIShareAdcAvg(var)            (RTE_Sec.u16VIShareAdcAvgAdc.u16Val = (var)) 
#define Rte_Write_P_u16VILocalAdcAvg(var)            (RTE_Sec.u16VILocalAdcAvgAdc.u16Val = (var)) 
#define Rte_Write_P_uSecComStatus(var)               (RTE_Sec.uComStatus.ALL  = (var))
#define Rte_Write_P_u16Vcap_Mul_128(var)             (PMBUS_tData.u16Vcap_Mul_128.u16Val  = (var))



#define Rte_Read_R_uComToPriStatus(var)              ((**var) = RTE_uComToPriStatus)
#define Rte_Read_R_uComToPriDebug(var)               ((**var) = RTE_u16ComToPriDebug)
#define Rte_Read_R_uComToSecStatus(var)              ((**var) = RTE_uComToSecStatus)
#define Rte_Read_R_uV1Gain(var)                      ((**var) = RTE_u16TrimV1GainAct)
#define Rte_Read_R_uIshareGain(var)                  ((**var) = RTE_u16IShareGain)
#define Rte_Read_R_u16IShareOfs(var)                  ((**var) = RTE_u16IShareOfs)
#define Rte_Read_R_uIGain(var)                       ((**var) = RTE_u16V1CurrentGain)

#define Rte_Read_R_uAppFwRevSec(var)                 ((**var) = RTE_u32PmbusFwRevSec1.u32Val )
#define Rte_Read_R_uBootFwRevSec(var)                ((**var) = RTE_u32PmbusBootFwRevSec1.u32Val)
#define Rte_Read_R_uAppFwRevPri(var)                 ((**var) = RTE_u32PmbusFwRevPri1.u32Val )
#define Rte_Read_R_uBootFwRevPri(var)                ((**var) = RTE_u32PmbusBootFwRevPri1.u32Val)
#define Rte_Read_R_u16100mHzVoltInFreq(var)          ((**var) = RTE_Pri.u16100mHzVoltInFreq)
#define Rte_Read_R_uAcOffset(var)                    ((**var) = RTE_Pri.u16AcOffset)

#define Rte_Read_R_uVinCaliAmp(var)                  ((**var) = RTE_CALI_sData.sVinAc[0].s16Amp)
#define Rte_Read_R_uVinCaliOfs(var)                  ((**var) = RTE_CALI_sData.sVinAc[0].s16Ofs)

#define Rte_Read_R_uCaliV1Amp(var)                   ((**var) = RTE_uCaliV1Amp)
#define Rte_Read_R_uCaliV1Ofs(var)                   ((**var) = RTE_uCaliV1Ofs)
#define Rte_Read_R_uCaliI1Amp(var)                   ((**var) = RTE_uCaliI1Amp)
#define Rte_Read_R_uCaliI1Ofs(var)                   ((**var) = RTE_uCaliI1Ofs)
#define Rte_Read_R_bIsV1OcpTest(var)                 ((**var) = RTE_bIsV1OcpTest)

//Nokia sHUB, FanCtrl is in the Pri, and 2 fans;
#define Rte_Read_R_uFanDuty(index,var)							 ((**var) = RTE_uFanDuty[index])		



#if MG_RTE_MODULE
/* Write bits */
#define Rte_Write_R_B_PFC_HALT                       RTE_B_PFC_HALT
#define Rte_Write_R_B_BL_MODE                        RTE_B_BL_MODE
#else
/* Read bits */
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Read data */
SINLINE uint8 INTCOM_Rte_Read_B_R_SEC_OVP(void)
{
	return RTE_Read_B_R_SEC_OVP;
}
SINLINE uint8 INTCOM_Rte_Read_B_R_SEC_UVP(void)
{
	return RTE_Read_B_R_SEC_UVP;
}
SINLINE uint8 INTCOM_Rte_Read_B_R_SEC_OCP(void)
{
	return RTE_Read_B_R_SEC_OCP;
}
SINLINE uint8 INTCOM_Rte_Read_B_R_SEC_OCW(void)
{
	return RTE_Read_B_R_SEC_OCW;
}
SINLINE uint8 INTCOM_Rte_Read_B_R_SEC_OCP_CT(void)
{
	return RTE_Read_B_R_SEC_OCP_CT;
}
SINLINE uint8 INTCOM_Rte_Read_B_R_SEC_OPP(void)
{
	return RTE_Read_B_R_SEC_OPP;
}

SINLINE uint8 INTCOM_RTE_Read_B_R_COM_V1_MONI_EN(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_COM_V1_MONI_EN;
	#endif
}
SINLINE uint8 INTCOM_RTE_Read_B_R_PRI_VIN_OK(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_PRI_VIN_OK;
	#endif
}
SINLINE uint8 INTCOM_RTE_B_IIN_OFFSET_CALIB(void)
{
  #if MG_RTE_MODULE
	return RTE_B_IIN_OFFSET_CALIB;
	#endif
}

SINLINE uint8 INTCOM_RTE_Read_B_R_AC_OFFSET_SAVEED(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_AC_OFFSET_SAVEED;
	#endif
}

SINLINE uint8 INTCOM_RTE_Read_B_R_PRI_VIN_LINE(void)
{
	#if MG_RTE_MODULE
	return RTE_Read_B_R_PRI_VIN_LINE;
	#endif
}
SINLINE uint8 INTCOM_RTE_Read_B_R_PRI_VIN_DROPOUT(void)
{
	#if MG_RTE_MODULE
	return RTE_Read_B_R_PRI_VIN_DROPOUT;
	#endif
}
SINLINE uint8 INTCOM_RTE_Read_B_R_VIN_OK_ACTIVE(void)
{
	#if MG_RTE_MODULE
	return RTE_Read_B_R_VIN_OK_ACTIVE;
	#endif
}

SINLINE void INTCOM_Rte_Read_R_u16100mHzVoltInFreq(WORD_VAL *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_u16100mHzVoltInFreq(&var);
#endif
}
SINLINE void INTCOM_Rte_Read_R_uComToPriStatus(GLOBAL_U_U16BIT *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_uComToPriStatus(&var);
#endif
}
SINLINE void INTCOM_Rte_Read_R_uComToPriDebug(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uComToPriDebug(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uComToSecStatus(GLOBAL_U_U16BIT *var)
{
#if MG_RTE_MODULE
  Rte_Read_R_uComToSecStatus(&var);
#endif
}
SINLINE void INTCOM_Rte_Read_R_uComToSecDebug(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uComToPriDebug(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uAppFwRevSec(uint32 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uAppFwRevSec(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uBootFwRevSec(uint32 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uBootFwRevSec(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uAppFwRevPri(uint32 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uAppFwRevPri(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uBootFwRevPri(uint32 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uBootFwRevPri(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uV1Gain(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uV1Gain(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uIshareGain(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uIshareGain(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_u16IShareOfs(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u16IShareOfs(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uIGain(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uIGain(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uAcOffset(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uAcOffset(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uVinCaliAmp(sint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uVinCaliAmp(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uVinCaliOfs(sint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uVinCaliOfs(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uCaliV1Amp(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uCaliV1Amp(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uCaliV1Ofs(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uCaliV1Ofs(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uCaliI1Amp(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uCaliI1Amp(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_uCaliI1Ofs(WORD_VAL *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_uCaliI1Ofs(&var);
  #endif
}
SINLINE void INTCOM_Rte_Read_R_bIsV1OcpTest(boolean *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_bIsV1OcpTest(&var);
  #endif
}

SINLINE void INTCOM_Rte_Read_R_uFanDuty(WORD_VAL *var1,WORD_VAL *var2)
{
	#if MG_RTE_MODULE
	Rte_Read_R_uFanDuty(0,&var1);
	Rte_Read_R_uFanDuty(1,&var2);
	#endif
}


/* Write Data */
SINLINE void INTCOM_RTE_Write_B_P_AC_OFFSET_NEED_SAVE(uint8 u8Status)
{
	RTE_Write_B_P_AC_OFFSET_NEED_SAVE = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_AC_LOST(uint8 u8Status)
{
	RTE_Write_B_P_AC_LOST = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_VIN_LINE_LOW(uint8 u8Status)
{
	RTE_Write_B_P_VIN_LINE_LOW = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_PRI_UART_FAIL(uint8 u8Status)
{
	RTE_Write_B_P_PRI_UART_FAIL = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_SEC_UART_FAIL(uint8 u8Status)
{
	RTE_Write_B_P_SEC_UART_FAIL = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_PRI_NO_RX_PKG(uint8 u8Status)
{
	RTE_Write_B_P_PRI_NO_RX_PKG = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_SEC_NO_RX_PKG(uint8 u8Status)
{
	RTE_Write_B_P_SEC_NO_RX_PKG = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_PRI_RX_PKG(uint8 u8Status)
{
	RTE_Write_B_P_PRI_RX_PKG = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_SEC_RX_PKG(uint8 u8Status)
{
	RTE_Write_B_P_SEC_RX_PKG = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_PRI_REV_UPDATE(uint8 u8Status)
{
	RTE_Write_B_P_PRI_REV_UPDATE = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_SEC_REV_UPDATE(uint8 u8Status)
{
	RTE_Write_B_P_SEC_REV_UPDATE = u8Status;
}
SINLINE void INTCOM_RTE_Write_B_P_COMMS_FAULT(uint8 u8Status)
{
	RTE_Write_B_P_COMMS_FAULT = u8Status;
}


SINLINE void INTCOM_Rte_Write_P_u32AppFwRevPri(uint32 u32Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u32AppFwRevPri(u32Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u32BootFwRevPri(uint32 u32Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u32BootFwRevPri(u32Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_uPfcStatus00(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uPfcStatus00(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_uPfcStatus01(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uPfcStatus01(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_uTempStatus00Pri(uint8 u8Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uTempStatus00Pri(u8Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16DebugData0Pri(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16DebugData0Pri(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16DebugData1Pri(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16DebugData1Pri(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16DebugData2Pri(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16DebugData2Pri(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u1610mVVinRmsAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u1610mVVinRmsAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u161mAIinRmsAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u161mAIinRmsAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16100mWPwrInRmsAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16100mWPwrInRmsAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16100mHzVoltInFreq(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16100mHzVoltInFreq(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16q16PwrFact(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16q16PwrFact(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16PfcNtcAdcAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16PfcNtcAdcAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16LlcNtcAdcAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16LlcNtcAdcAvg(u16Data);
  #endif
}

SINLINE void INTCOM_Rte_Write_P_u16VbulkAdc(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16VbulkAdc(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_uPriComStatus(uint8 u8Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uPriComStatus(u8Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_s16AcOffset(sint16 s16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_s16AcOffset(s16Data);
  #endif
}

SINLINE void INTCOM_Rte_Write_P_u32AppFwRevSec(uint32 u32Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u32AppFwRevSec(u32Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u32BootFwRevSec(uint32 u32Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u32BootFwRevSec(u32Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16LlcStatus00(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16LlcStatus00(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16LlcStatus01(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16LlcStatus01(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16LlcStatus02(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16LlcStatus02(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u8TempStatus00Sec(uint8 u8Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u8TempStatus00Sec(u8Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16DebugData0Sec(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16DebugData0Sec(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16DebugData1Sec(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16DebugData1Sec(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16DebugData2Sec(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16DebugData2Sec(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u1610mVV1ExtAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u1610mVV1ExtAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u1610mVVoltOutIntAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u1610mVV1IntExtAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u161mAIV1Avg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u161mAIV1Avg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16100mWPwrOutAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16100mWPwrOutAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16SrNtcAdcAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16SrNtcAdcAvg(u16Data);
  #endif
}

SINLINE void INTCOM_Rte_Write_P_u16VIShareAdcAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16VIShareAdcAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16VILocalAdcAvg(uint16 u16Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16VILocalAdcAvg(u16Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_uSecComStatus(uint8 u8Data)
{
  #if MG_RTE_MODULE
  Rte_Write_P_uSecComStatus(u8Data);
  #endif
}
SINLINE void INTCOM_Rte_Write_P_u16Vcap_Mul_128(uint16 var)
{
  #if MG_RTE_MODULE
  Rte_Write_P_u16Vcap_Mul_128(var);
  #endif
}

SINLINE void INTCOM_Rte_Write_B_P_V1_OVP(uint8 u8Status)
{
	RTE_Write_B_P_V1_OVP = u8Status;
}

SINLINE void INTCOM_Rte_Write_B_P_V1_UVP(uint8 u8Status)
{
	RTE_Write_B_P_V1_UVP = u8Status;
}

SINLINE void INTCOM_Rte_Write_B_P_V1_OCP(uint8 u8Status)
{
	RTE_Write_B_P_V1_OCP = u8Status;
}

SINLINE void INTCOM_Rte_Write_B_P_V1_OCW(uint8 u8Status)
{
	RTE_Write_B_P_V1_OCW = u8Status;
}

SINLINE void INTCOM_Rte_Write_P_u16FanCnt(uint8 u8Index,uint16 u16Data)
{
  #if MG_RTE_MODULE
	Rte_Write_P_u16FanCnt(u8Index,u16Data);
  #endif
}

#ifdef __cplusplus
  }
#endif
#endif  /* INTCOM_RTE_H */

  
/*
 * End of file
 */
