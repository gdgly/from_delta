/** *****************************************************************************
 * \file    intcom.c
 * \brief   Internal communication data processing
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

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/* Module header */
#define INTCOM_EXPORT_H
#include "intcom_api.h"
#include "intcom_scb.h"
#include "intcom_cfg.h"
#include "intcom_scfg.h"
#include "intcom_rte.h"
#include "intcom_conf.h"

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
static uint32 mg_u32Com1MonCnt;
static uint32 mg_u32Com2MonCnt;
/*******************************************************************************
 * Local function prototypes (private to module)
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
void INTCOM_vInit(void)
{
	mg_u32Com1MonCnt = 1000u;
	mg_u32Com2MonCnt = 1000u;
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
void INTCOM_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         Load TX buffer for transmission
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void INTCOM_vCom1TxData(uint8 *pau8TxBuf, uint16 *u16TxDataNbr)
{
	GLOBAL_U_U16BIT uCom2Pri00;
	WORD_VAL uDebugData0Addr;
	WORD_VAL uAcoffset;
	WORD_VAL uVinCaliAmp;
	WORD_VAL uVinCaliOfs;
	WORD_VAL uFanDuty[2];
	
	/* Read data from RTE */
	INTCOM_Rte_Read_R_uComToPriStatus(&uCom2Pri00);
	INTCOM_Rte_Read_R_uComToPriDebug(&uDebugData0Addr);
	INTCOM_Rte_Read_R_uAcOffset(&uAcoffset);
	INTCOM_Rte_Read_R_uVinCaliAmp(&uVinCaliAmp.s16Val);
	INTCOM_Rte_Read_R_uVinCaliOfs(&uVinCaliOfs.s16Val);
	INTCOM_Rte_Read_R_uFanDuty(&uFanDuty[0],&uFanDuty[1]);

	/* Fill buffer */
	pau8TxBuf[(*u16TxDataNbr)++] = uCom2Pri00.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCom2Pri00.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uDebugData0Addr.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uDebugData0Addr.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uAcoffset.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uAcoffset.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uVinCaliAmp.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uVinCaliAmp.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uVinCaliOfs.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uVinCaliOfs.Bytes.HB;

  /* fanduty, send to Pri */
	pau8TxBuf[(*u16TxDataNbr)++] = uFanDuty[0].Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uFanDuty[0].Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uFanDuty[1].Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uFanDuty[1].Bytes.HB;
	
}

/** *****************************************************************************
 * \brief         Handle data in RX buffer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void INTCOM_vCom1RxData(uint8 *pau8RxBuf, uint8 u8BroadcastFlg, uint16 u16RxBufCnt)
{
	/* Init data */
	GLOBAL_U_U16BIT uPfcStatus00;
	GLOBAL_U_U16BIT uPfcStatus01;
	GLOBAL_U_U8BIT  uTempStatus00;
	WORD_VAL u16DebugData0;
	WORD_VAL u16DebugData1;
	WORD_VAL u16DebugData2;
	WORD_VAL u1610mVVoltInRmsAvg;
	WORD_VAL u161mACurrInRmsAvg;
	WORD_VAL u16100mWPwrInRmsAvg;
	WORD_VAL u16100mHzVoltInFreq;
	WORD_VAL u16q16PwrFact;
	WORD_VAL u16PfcNtcAdcAvg;
	WORD_VAL u16LlcNtcAdcAvg;
	WORD_VAL u16VBusAdcAvg;
	WORD_VAL uAcOffset;
	DWORD_VAL u32AppFwRev;
	DWORD_VAL u32BootFwRev;
	uint32 u32PreAppFwRev;
	uint32 u32PreBootFwRev;
	uint8 u8ComStatus;
	WORD_VAL u16FanCnt[2];

	u8ComStatus                   = pau8RxBuf[u16RxBufCnt++]; /* COM status */
	u32AppFwRev.Bytes.LB          = pau8RxBuf[u16RxBufCnt++]; /* MAJOR_REV */
	u32AppFwRev.Bytes.HB          = pau8RxBuf[u16RxBufCnt++]; /* MINOR_REV */
	u32AppFwRev.Bytes.UB          = pau8RxBuf[u16RxBufCnt++]; /* DEBUG_REV */
	u32BootFwRev.Bytes.LB         = pau8RxBuf[u16RxBufCnt++]; /* MAJOR_REV */
	u32BootFwRev.Bytes.HB         = pau8RxBuf[u16RxBufCnt++]; /* MINOR_REV */
	u32BootFwRev.Bytes.UB         = pau8RxBuf[u16RxBufCnt++]; /* DEBUG_REV */
	uPfcStatus00.Bytes.LB         = pau8RxBuf[u16RxBufCnt++]; /* PFC status00 low byte*/
	uPfcStatus00.Bytes.HB         = pau8RxBuf[u16RxBufCnt++]; /* PFC status00 high byte*/
	uPfcStatus01.Bytes.LB         = pau8RxBuf[u16RxBufCnt++]; /* PFC status01 low byte*/
	uPfcStatus01.Bytes.HB         = pau8RxBuf[u16RxBufCnt++]; /* PFC status01 high byte*/
	uTempStatus00.ALL             = pau8RxBuf[u16RxBufCnt++]; /* PFC temperature status */
	u16DebugData0.Bytes.LB        = pau8RxBuf[u16RxBufCnt++]; /* Dubug register0 low byte */
	u16DebugData0.Bytes.HB        = pau8RxBuf[u16RxBufCnt++]; /* Dubug register0 low byte */
	u16DebugData1.Bytes.LB        = pau8RxBuf[u16RxBufCnt++]; /* Dubug register1 low byte */
	u16DebugData1.Bytes.HB        = pau8RxBuf[u16RxBufCnt++]; /* Dubug register1 low byte */
	u16DebugData2.Bytes.LB        = pau8RxBuf[u16RxBufCnt++]; /* Dubug register2 low byte */
	u16DebugData2.Bytes.HB        = pau8RxBuf[u16RxBufCnt++]; /* Dubug register2 low byte */
	u1610mVVoltInRmsAvg.Bytes.LB	= pau8RxBuf[u16RxBufCnt++]; /* AC voltage RMS adc average value low byte */
	u1610mVVoltInRmsAvg.Bytes.HB	= pau8RxBuf[u16RxBufCnt++]; /* AC voltage RMS adc average value high byte */
	u161mACurrInRmsAvg.Bytes.LB	  = pau8RxBuf[u16RxBufCnt++]; /* AC current RMS adc average value low byte */
	u161mACurrInRmsAvg.Bytes.HB	  = pau8RxBuf[u16RxBufCnt++]; /* AC current RMS adc average value high byte */
	u16100mWPwrInRmsAvg.Bytes.LB	= pau8RxBuf[u16RxBufCnt++]; /* AC power RMS adc average value low byte */
	u16100mWPwrInRmsAvg.Bytes.HB	= pau8RxBuf[u16RxBufCnt++]; /* AC power RMS adc average value high byte */
	u16100mHzVoltInFreq.Bytes.LB	= pau8RxBuf[u16RxBufCnt++]; /* The frequency of AC low byte , 0.1 Hz */
	u16100mHzVoltInFreq.Bytes.HB	= pau8RxBuf[u16RxBufCnt++]; /* The frequency of AC high byte , 0.1 Hz */
	u16q16PwrFact.Bytes.LB	      = pau8RxBuf[u16RxBufCnt++]; /* Power fact low byte */
	u16q16PwrFact.Bytes.HB	      = pau8RxBuf[u16RxBufCnt++]; /* Power fact high byte */
	u16PfcNtcAdcAvg.Bytes.LB	    = pau8RxBuf[u16RxBufCnt++]; /* NTC adc average value low byte */
	u16PfcNtcAdcAvg.Bytes.HB	    = pau8RxBuf[u16RxBufCnt++]; /* NTC adc average value high byte */
	u16VBusAdcAvg.Bytes.LB	      = pau8RxBuf[u16RxBufCnt++]; /* Bus voltage adc average value low byte */
	u16VBusAdcAvg.Bytes.HB	      = pau8RxBuf[u16RxBufCnt++]; /* Bus voltage adc average value high byte */
	uAcOffset.Bytes.LB            = pau8RxBuf[u16RxBufCnt++];
	uAcOffset.Bytes.HB            = pau8RxBuf[u16RxBufCnt++];

	u16LlcNtcAdcAvg.Bytes.LB      = pau8RxBuf[u16RxBufCnt++];
	u16LlcNtcAdcAvg.Bytes.HB      = pau8RxBuf[u16RxBufCnt++];
	u16FanCnt[0].Bytes.LB 			  = pau8RxBuf[u16RxBufCnt++];
	u16FanCnt[0].Bytes.HB 		    = pau8RxBuf[u16RxBufCnt++];
	u16FanCnt[1].Bytes.LB 		  	= pau8RxBuf[u16RxBufCnt++];
	u16FanCnt[1].Bytes.HB 		  	= pau8RxBuf[u16RxBufCnt++];
	
	/* Write data from RTE */
	INTCOM_Rte_Write_P_uPriComStatus(u8ComStatus);
	INTCOM_Rte_Read_R_uAppFwRevPri(&u32PreAppFwRev);
	INTCOM_Rte_Read_R_uBootFwRevPri(&u32PreBootFwRev);

	if ((u32PreAppFwRev != u32AppFwRev.u32Val) ||
	    (u32PreBootFwRev != u32BootFwRev.u32Val))
	{
		INTCOM_Rte_Write_P_u32AppFwRevPri(u32AppFwRev.u32Val);
		INTCOM_Rte_Write_P_u32BootFwRevPri(u32BootFwRev.u32Val);
		INTCOM_RTE_Write_B_P_PRI_REV_UPDATE(TRUE);
	}

	if (FALSE == INTCOM_RTE_Read_B_R_AC_OFFSET_SAVEED())
	{
		if (FALSE != INTCOM_RTE_B_IIN_OFFSET_CALIB())
		{
			INTCOM_RTE_Write_B_P_AC_OFFSET_NEED_SAVE(TRUE);
			INTCOM_Rte_Write_P_s16AcOffset(uAcOffset.s16Val);
		}
	}
	else
	{
		/* do nothing */
	}

	INTCOM_Rte_Write_P_uPfcStatus00(uPfcStatus00.ALL);
	INTCOM_Rte_Write_P_uPfcStatus01(uPfcStatus01.ALL);
	INTCOM_Rte_Write_P_uTempStatus00Pri(uTempStatus00.ALL);
	INTCOM_Rte_Write_P_u16DebugData0Pri(u16DebugData0.u16Val);
	INTCOM_Rte_Write_P_u16DebugData1Pri(u16DebugData1.u16Val);
	INTCOM_Rte_Write_P_u16DebugData2Pri(u16DebugData2.u16Val);
	INTCOM_Rte_Write_P_u1610mVVinRmsAvg(u1610mVVoltInRmsAvg.u16Val);
	INTCOM_Rte_Write_P_u161mAIinRmsAvg(u161mACurrInRmsAvg.u16Val);
	INTCOM_Rte_Write_P_u16100mWPwrInRmsAvg(u16100mWPwrInRmsAvg.u16Val);
	INTCOM_Rte_Write_P_u16100mHzVoltInFreq(u16100mHzVoltInFreq.u16Val);
	INTCOM_Rte_Write_P_u16q16PwrFact(u16q16PwrFact.u16Val);
	INTCOM_Rte_Write_P_u16PfcNtcAdcAvg(u16PfcNtcAdcAvg.u16Val);
	
	INTCOM_Rte_Write_P_u16VbulkAdc(u16VBusAdcAvg.u16Val);
	u16VBusAdcAvg.u16Val = (uint16)(((uint32)u16VBusAdcAvg.u16Val * 128u) / 100u);
	INTCOM_Rte_Write_P_u16Vcap_Mul_128(u16VBusAdcAvg.u16Val);

	INTCOM_RTE_Write_B_P_AC_LOST(INTCOM_RTE_Read_B_R_PRI_VIN_DROPOUT());
	INTCOM_RTE_Write_B_P_VIN_LINE_LOW(INTCOM_RTE_Read_B_R_PRI_VIN_LINE());

	mg_u32Com1MonCnt = 1000u;
	INTCOM_RTE_Write_B_P_PRI_UART_FAIL(FALSE);
	INTCOM_RTE_Write_B_P_PRI_NO_RX_PKG(FALSE);
	INTCOM_RTE_Write_B_P_PRI_RX_PKG(TRUE);
	
	INTCOM_Rte_Write_P_u16LlcNtcAdcAvg(u16LlcNtcAdcAvg.u16Val);
	INTCOM_Rte_Write_P_u16FanCnt(0,u16FanCnt[0].u16Val);
	INTCOM_Rte_Write_P_u16FanCnt(1,u16FanCnt[1].u16Val);
	
}

/** *****************************************************************************
 * \brief         Load TX buffer for transmission
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void INTCOM_vCom2TxData(uint8 *pau8TxBuf, uint16 *u16TxDataNbr)
{
	GLOBAL_U_U16BIT uCom2Sec00;
	WORD_VAL uDebugData0Addr;
	WORD_VAL uV1Gain;
	WORD_VAL uIshareGain;
	WORD_VAL uIshareOfs;
	WORD_VAL uIGain;
	WORD_VAL u100mHzVoltInFreq;
	WORD_VAL uCaliV1Amp;
	WORD_VAL uCaliV1Ofs;
	WORD_VAL uCaliI1Amp;
	WORD_VAL uCaliI1Ofs;
	
	/* Read data from RTE */
	INTCOM_Rte_Read_R_uComToSecStatus(&uCom2Sec00);
	INTCOM_Rte_Read_R_uComToSecDebug(&uDebugData0Addr);
	INTCOM_Rte_Read_R_uV1Gain(&uV1Gain);
	INTCOM_Rte_Read_R_uIshareGain(&uIshareGain);
	INTCOM_Rte_Read_R_u16IShareOfs(&uIshareOfs);
	INTCOM_Rte_Read_R_uIGain(&uIGain);
	INTCOM_Rte_Read_R_u16100mHzVoltInFreq(&u100mHzVoltInFreq);
	INTCOM_Rte_Read_R_uCaliV1Amp(&uCaliV1Amp);
	INTCOM_Rte_Read_R_uCaliV1Ofs(&uCaliV1Ofs);
	INTCOM_Rte_Read_R_uCaliI1Amp(&uCaliI1Amp);
	INTCOM_Rte_Read_R_uCaliI1Ofs(&uCaliI1Ofs);

	/* Fill buffer */
	pau8TxBuf[(*u16TxDataNbr)++] = uCom2Sec00.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCom2Sec00.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uDebugData0Addr.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uDebugData0Addr.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uV1Gain.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uV1Gain.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uIGain.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uIGain.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uIshareGain.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uIshareGain.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = u100mHzVoltInFreq.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = u100mHzVoltInFreq.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uIshareOfs.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uIshareOfs.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCaliV1Amp.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCaliV1Amp.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCaliV1Ofs.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCaliV1Ofs.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCaliI1Amp.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCaliI1Amp.Bytes.HB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCaliI1Ofs.Bytes.LB;
	pau8TxBuf[(*u16TxDataNbr)++] = uCaliI1Ofs.Bytes.HB;
	

}

/** *****************************************************************************
 * \brief         Handle data in RX buffer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void INTCOM_vCom2RxData(uint8 *pau8RxBuf, uint8 u8BroadcastFlg, uint16 u16RxBufCnt)
{
	/* Init data */
	DWORD_VAL uAppFwRev;
	DWORD_VAL uBootFwRev;
	GLOBAL_U_U16BIT uLlcStatus00;
	GLOBAL_U_U16BIT uLlcStatus01;
	GLOBAL_U_U16BIT uLlcStatus02;
	GLOBAL_U_U8BIT  uTempStatus00;
	WORD_VAL uDebugData0;
	WORD_VAL uDebugData1;
	WORD_VAL uDebugData2;
	WORD_VAL u10mVVoltOutExtAvg;
	WORD_VAL u10mVVoltOutIntAvg;
	WORD_VAL u10mACurrOutAvg;
	WORD_VAL u100mWPwrOutAvg;
	WORD_VAL u1mVVoltNtc1Avg;

	WORD_VAL u1mVIShareAvg;
	WORD_VAL u1mVILocalAvg;
	uint32 u32PreAppFwRev;
	uint32 u32PreBootFwRev;
	uint8 u8ComStatus;
	boolean bIsV1OcpTest;

	u8ComStatus                   = pau8RxBuf[u16RxBufCnt++]; /* COM status */
	uAppFwRev.Bytes.LB            = pau8RxBuf[u16RxBufCnt++]; /* MAJOR_REV */
	uAppFwRev.Bytes.HB            = pau8RxBuf[u16RxBufCnt++]; /* MINOR_REV */
	uAppFwRev.Bytes.UB            = pau8RxBuf[u16RxBufCnt++]; /* DEBUG_REV */
	uBootFwRev.Bytes.LB           = pau8RxBuf[u16RxBufCnt++]; /* MAJOR_REV */
	uBootFwRev.Bytes.HB           = pau8RxBuf[u16RxBufCnt++]; /* MINOR_REV */
	uBootFwRev.Bytes.UB           = pau8RxBuf[u16RxBufCnt++]; /* DEBUG_REV */
	uLlcStatus00.Bytes.LB         = pau8RxBuf[u16RxBufCnt++];
	uLlcStatus00.Bytes.HB         = pau8RxBuf[u16RxBufCnt++];
	uLlcStatus01.Bytes.LB         = pau8RxBuf[u16RxBufCnt++];
	uLlcStatus01.Bytes.HB         = pau8RxBuf[u16RxBufCnt++];
	uLlcStatus02.Bytes.LB         = pau8RxBuf[u16RxBufCnt++];
	uLlcStatus02.Bytes.HB         = pau8RxBuf[u16RxBufCnt++];
	uTempStatus00.ALL             = pau8RxBuf[u16RxBufCnt++];
	uDebugData0.Bytes.LB          = pau8RxBuf[u16RxBufCnt++];
	uDebugData0.Bytes.HB          = pau8RxBuf[u16RxBufCnt++];
	uDebugData1.Bytes.LB          = pau8RxBuf[u16RxBufCnt++];
	uDebugData1.Bytes.HB          = pau8RxBuf[u16RxBufCnt++];
	uDebugData2.Bytes.LB          = pau8RxBuf[u16RxBufCnt++];
	uDebugData2.Bytes.HB          = pau8RxBuf[u16RxBufCnt++];
	u10mVVoltOutExtAvg.Bytes.LB	  = pau8RxBuf[u16RxBufCnt++];
	u10mVVoltOutExtAvg.Bytes.HB	  = pau8RxBuf[u16RxBufCnt++];
	u10mACurrOutAvg.Bytes.LB	    = pau8RxBuf[u16RxBufCnt++];
	u10mACurrOutAvg.Bytes.HB	    = pau8RxBuf[u16RxBufCnt++];
	u100mWPwrOutAvg.Bytes.LB	    = pau8RxBuf[u16RxBufCnt++];
	u100mWPwrOutAvg.Bytes.HB	    = pau8RxBuf[u16RxBufCnt++];
	u1mVVoltNtc1Avg.Bytes.LB	    = pau8RxBuf[u16RxBufCnt++];
	u1mVVoltNtc1Avg.Bytes.HB	    = pau8RxBuf[u16RxBufCnt++];
	u10mVVoltOutIntAvg.Bytes.LB	  = pau8RxBuf[u16RxBufCnt++];
	u10mVVoltOutIntAvg.Bytes.HB	  = pau8RxBuf[u16RxBufCnt++];
	u1mVIShareAvg.Bytes.LB	      = pau8RxBuf[u16RxBufCnt++];
	u1mVIShareAvg.Bytes.HB	      = pau8RxBuf[u16RxBufCnt++];
	u1mVILocalAvg.Bytes.LB	      = pau8RxBuf[u16RxBufCnt++];
	u1mVILocalAvg.Bytes.HB	      = pau8RxBuf[u16RxBufCnt++];

	/* Write data to RTE */
	INTCOM_Rte_Write_P_uSecComStatus(u8ComStatus);
	INTCOM_Rte_Read_R_uAppFwRevSec(&u32PreAppFwRev);
	INTCOM_Rte_Read_R_uBootFwRevSec(&u32PreBootFwRev);

	if ((u32PreAppFwRev != uAppFwRev.u32Val) ||
	    (u32PreBootFwRev != uBootFwRev.u32Val))
	{
		INTCOM_Rte_Write_P_u32AppFwRevSec(uAppFwRev.u32Val);
		INTCOM_Rte_Write_P_u32BootFwRevSec(uBootFwRev.u32Val);
		INTCOM_RTE_Write_B_P_SEC_REV_UPDATE(TRUE);
	}

	INTCOM_Rte_Write_P_u16LlcStatus00(uLlcStatus00.ALL);
	INTCOM_Rte_Write_P_u16LlcStatus01(uLlcStatus01.ALL);

	if (FALSE != INTCOM_RTE_Read_B_R_COM_V1_MONI_EN())
	{
		INTCOM_Rte_Write_B_P_V1_OVP(INTCOM_Rte_Read_B_R_SEC_OVP());
		INTCOM_Rte_Write_B_P_V1_UVP(INTCOM_Rte_Read_B_R_SEC_UVP());
		INTCOM_Rte_Read_R_bIsV1OcpTest(&bIsV1OcpTest);

		if (FALSE != bIsV1OcpTest)
		{
			INTCOM_Rte_Write_B_P_V1_OCP(TRUE);
		}
		else
		{
			INTCOM_Rte_Write_B_P_V1_OCP(INTCOM_Rte_Read_B_R_SEC_OCP() |
			                            INTCOM_Rte_Read_B_R_SEC_OCP_CT() |
			                            INTCOM_Rte_Read_B_R_SEC_OPP());
		}

		INTCOM_Rte_Write_B_P_V1_OCW(INTCOM_Rte_Read_B_R_SEC_OCW());
	}

	INTCOM_Rte_Write_P_u16LlcStatus02(uLlcStatus02.ALL);
	INTCOM_Rte_Write_P_u8TempStatus00Sec(uTempStatus00.ALL);
	INTCOM_Rte_Write_P_u16DebugData0Sec(uDebugData0.u16Val);
	INTCOM_Rte_Write_P_u16DebugData1Sec(uDebugData1.u16Val);
	INTCOM_Rte_Write_P_u16DebugData2Sec(uDebugData2.u16Val);
	INTCOM_Rte_Write_P_u1610mVV1ExtAvg(u10mVVoltOutExtAvg.u16Val);
	INTCOM_Rte_Write_P_u1610mVVoltOutIntAvg(u10mVVoltOutIntAvg.u16Val);
	INTCOM_Rte_Write_P_u161mAIV1Avg(u10mACurrOutAvg.u16Val);
	INTCOM_Rte_Write_P_u16100mWPwrOutAvg(u100mWPwrOutAvg.u16Val);
	INTCOM_Rte_Write_P_u16SrNtcAdcAvg(u1mVVoltNtc1Avg.u16Val);
	INTCOM_Rte_Write_P_u16VIShareAdcAvg(u1mVIShareAvg.u16Val);
	INTCOM_Rte_Write_P_u16VILocalAdcAvg(u1mVILocalAvg.u16Val);

	mg_u32Com2MonCnt = 1000u;
	INTCOM_RTE_Write_B_P_SEC_UART_FAIL(FALSE);
	INTCOM_RTE_Write_B_P_SEC_NO_RX_PKG(FALSE);
}

/** *****************************************************************************
 * \brief         Monitor intnal communication
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void INTCOM_vTmOutMon(void)
{
	if (mg_u32Com1MonCnt != 0)
	{
		mg_u32Com1MonCnt--;
	}
	else
	{
		INTCOM_RTE_Write_B_P_PRI_UART_FAIL(TRUE);
		INTCOM_RTE_Write_B_P_PRI_NO_RX_PKG(TRUE);
		INTCOM_RTE_Write_B_P_PRI_RX_PKG(FALSE);

		if (FALSE != INTCOM_RTE_Read_B_R_VIN_OK_ACTIVE())
		{
			INTCOM_RTE_Write_B_P_COMMS_FAULT(TRUE);
		}
	}

	if (mg_u32Com2MonCnt != 0)
	{
		mg_u32Com2MonCnt--;
	}
	else
	{
		INTCOM_RTE_Write_B_P_SEC_UART_FAIL(TRUE);
		INTCOM_RTE_Write_B_P_SEC_NO_RX_PKG(TRUE);

		if (FALSE != INTCOM_RTE_Read_B_R_VIN_OK_ACTIVE())
		{
			INTCOM_RTE_Write_B_P_COMMS_FAULT(TRUE);
		}
	}
}

/*
 * End of file
 */
