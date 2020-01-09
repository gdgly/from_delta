/*******************************************************************************
 * \file    rte.c
 * \brief   rte config
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-11-22 11:01:57 +0800 (Fri, 22 Nov 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 239 $
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
#define TMR_EXPORT_H
  #include "rte.h"


/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

volatile GLOBAL_U_U8BIT MUX_INPUT_SIGNAL;
boolean RTE_bPEC_Enable;

//#pragma udata BANK_PMB4 = 0x600
uint8  RTE_au8Uart1TxBuf[RTE_UART1_TX_BUF_SIZE];
uint8  RTE_au8Uart1RxBuf[RTE_UART1_RX_BUF_SIZE];
uint16 RTE_u16Uart1TxDataNbr;
uint16 RTE_u16Uart1RxDataNbr;
uint8  RTE_u8Uart1TxBufUpdated;
uint8  RTE_u8Uart1RxNewFrame;
uint8  RTE_u8Uart1FrameTmoutFlg;
uint8  RTE_u8Uart1ByteTmoutFlg;
uint8  RTE_u8Uart1TxTmoutFlg;
uint8  RTE_u8Uart1BroadcastFlg;
uint8  RTE_u8Uart1RxCrc;
GLOBAL_U_U16BIT  RTE_uUart1Pri1VinAD;
GLOBAL_U_U16BIT  RTE_uUart1Pri2VinAD;
RTE_U_UARTSTATUS RTE_uUart1Status;
RTE_U_PMBUS_OPERATION RTE_uPmbusOperation;
//#pragma udata BANK_PMB5 = 0x700
#if (2U == RTE_UART_CHANNEL_USED)
  uint8  RTE_au8Uart2TxBuf[RTE_UART2_TX_BUF_SIZE];
  uint8  RTE_au8Uart2RxBuf[RTE_UART2_RX_BUF_SIZE];
  uint16 RTE_u16Uart2TxDataNbr;
  uint16 RTE_u16Uart2RxDataNbr;
  uint8  RTE_u8Uart2TxBufUpdated;
  uint8  RTE_u8Uart2RxNewFrame;
  uint8  RTE_u8Uart2FrameTmoutFlg;
  uint8  RTE_u8Uart2ByteTmoutFlg;
  uint8  RTE_u8Uart2TxTmoutFlg;
  uint8  RTE_u8Uart2BroadcastFlg;
  uint8  RTE_u8Uart2RxCrc;
  RTE_U_UARTSTATUS RTE_uUart2Status;
#endif
//#pragma udata
GLOBAL_U_U16BIT RTE_uTempOtwStatus;
GLOBAL_U_U16BIT RTE_uTempOtpStatus;
GLOBAL_U_U16BIT RTE_uSensorFaultStatus;
GLOBAL_U_U16BIT RTE_uTempStatus;
GLOBAL_U_U16BIT RTE_uDioInStatus;
GLOBAL_U_U16BIT RTE_uDioOutStatus;
GLOBAL_U_U16BIT RTE_uPsuCtrlStatus;
GLOBAL_U_U16BIT RTE_uIntcom1Status;
GLOBAL_U_U16BIT RTE_uIntcom2Status;
GLOBAL_U_U16BIT RTE_uComToSecStatus;
GLOBAL_U_U16BIT RTE_uComToPriStatus;
GLOBAL_U_U16BIT RTE_uComStatus00;
GLOBAL_U_U16BIT RTE_uComStatus01;
GLOBAL_U_U16BIT RTE_uComStatus02;

WORD_VAL RTE_u16TrimV1Gain;
WORD_VAL RTE_u16TrimV1GainOvp;
WORD_VAL RTE_u16TrimV1GainAct;

WORD_VAL RTE_u16TrimVsbGain;
WORD_VAL RTE_u16TrimVsbGainOvp;
WORD_VAL RTE_u16TrimVsbGainAct;

WORD_VAL RTE_u16V1CurrentGain;
WORD_VAL RTE_u16IShareGain;
WORD_VAL RTE_u16IShareOfs;

GLOBAL_U_U16BIT RTE_u16MonCtrlInputType;

DWORD_VAL RTE_u32PmbusFwRevPri1;
DWORD_VAL RTE_u32PmbusBootFwRevPri1;
DWORD_VAL RTE_u32PmbusFwRevSec1;
DWORD_VAL RTE_u32PmbusBootFwRevSec1;
DWORD_VAL RTE_u32PmbusFwRevPri1Old;
DWORD_VAL RTE_u32PmbusBootFwRevPri1Old;
DWORD_VAL RTE_u32PmbusFwRevSec1Old;
DWORD_VAL RTE_u32PmbusBootFwRevSec1Old;
DWORD_VAL RTE_u32PmbusFwRevCom;
DWORD_VAL RTE_u32PmbusBootFwRevCom;

WORD_VAL  RTE_u16ComToPriDebug;
WORD_VAL  RTE_u16ComToSecDebug;

volatile GLOBAL_U_U16BIT RTE_sV1FaultFlag00, RTE_sVsbFaultFlag00;
volatile GLOBAL_U_U16BIT RTE_sVoutStateFlag, RTE_sSysStateFlag00;

uint16 RTE_u161mAIinAvgAvgPri;
uint16 RTE_u16100mAPinAvgAvgPri;
uint16 RTE_u1610mVIntV1AvgAvgSec;
uint16 RTE_u1610mVExtV1AvgAvgSec;
uint16 RTE_u1610mAIoutAvgAvgSec;

uint16 RTE_u16CaliIout;
RTE_S_ADJ_Data   RTE_sAdjustData;

//#pragma udata BANK_PMB3 = 0x500
uint8 RTE_u8PmbusCommand;


//#pragma udata

//#pragma udata BANK_INTCOM = 0x800
RTE_S_INTCOM1_DATA RTE_Pri;
RTE_S_INTCOM2_DATA RTE_Sec;
WORD_VAL RTE_u16ComToSecDebug1;
WORD_VAL RTE_u16ComToSecDebug2;
CALI_S_DATA RTE_CALI_sData;
uint8  RTE_au8MfrData[6][17];
//#pragma udata

volatile GLOBAL_U_U16BIT  RTE_u16I2cStatus0;

uint8 RTE_ModelNumber[11] = "ECD56020015";


volatile uint8 RTE_u8I2cExpTxCnt;
volatile uint8 RTE_u8I2cExpRxCnt;
volatile uint8 RTE_u8I2cRxCnt;
volatile uint8 RTE_u8I2cPECErrCmd;
volatile uint8 RTE_u8I2cTxLen;
volatile uint8 RTE_u8I2cPEC;
volatile uint8 RTE_au8I2cTxBuf[I2C_TX_BUF_SIZE+1];
volatile uint8 RTE_au8I2cRxBuf[I2C_RX_BUF_SIZE+1];

uint8 RTE_u8InputLedState;

CALI_U_STATUS CALI_uStatus;
CALI_S_PARAMETER CALI_sPara;

FANCTRL_U_STATUS_12 FANCTRL_uFanStatus12;
FANCTRL_U_STATUS_12 FANCTRL_uFanStatus34;

PMBUS_U_OPERATION PMBUS_uOperation;
PMBUS_U_SYS_STATUS0 PMBUS_uSysStatu0;
PMBUS_U_SYS_STATUS1 PMBUS_uSysStatu1;
PMBUS_U_UPD_STATUS0 PMBUS_uDataUpdStatus;
PMBUS_U_UPD_STATUS1 PMBUS_uDataUpdStatus1;
PMBUS_S_DATA   PMBUS_tData;
PMBUS_S_STATUS PMBUS_tStatus;
PMBUS_S_STATUS PMBUS_tStatusOld;
uint16  RTE_u16ComDebug[4]={0};

uint8 RTE_u8AcLineStatus;

uint16 RTE_u16VoutIntVsbFast;
uint16 RTE_u16VoutExtVsbFast;
uint16 RTE_u16IoutVsbFast;

sint16 RTE_s16TempTest[RTE_TEMP_TOTAL_NUM];
uint8  RTE_u8TempTestIndex;
boolean  RTE_bIsV1OcpTest;
boolean  RTE_bIsVsbOcpTest;

GLOBAL_U_U16BIT RTE_uFunctionCtrl;
sint16 RTE_s16OtWarning;

WORD_VAL RTE_uCaliV1Amp;
WORD_VAL RTE_uCaliV1Ofs;
WORD_VAL RTE_uCaliI1Amp;
WORD_VAL RTE_uCaliI1Ofs;
/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize and configure timer modules for 100us system time slice
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void RTE_vInit(void)
{
  RTE_uTempOtwStatus.ALL = 0;
  RTE_uTempOtpStatus.ALL = 0;
  RTE_uSensorFaultStatus.ALL = 0;
  RTE_uTempStatus.ALL = 0;
  RTE_uDioInStatus.ALL = 0;
  RTE_uDioOutStatus.ALL = 0;
  RTE_uPsuCtrlStatus.ALL = 0;
  RTE_uIntcom1Status.ALL = 0;
  RTE_uIntcom2Status.ALL = 0;
  RTE_uComToPriStatus.ALL = 0;
  RTE_uComToSecStatus.ALL = 0;
  RTE_uComStatus00.ALL = 0;
  RTE_uComStatus01.ALL = 0;

  RTE_Pri.u1610mVVinAvg.u16Val = 0;
  RTE_Pri.u161mAIinAvg.u16Val = 0;
  RTE_Pri.u16100mAPinAvg.u16Val = 0;
  RTE_Pri.u16q12VbulkAdc.u16Val = 0;
  RTE_Pri.u16PriStatus00.ALL = 0;
  RTE_Pri.u16PriStatus01.ALL = 0;
  RTE_Pri.u16PriDebug1.u16Val = 0;
  RTE_Pri.u16PriDebug2.u16Val = 0;
  RTE_Pri.u16MeterIcVin.u16Val = 0;
  RTE_Pri.u16MeterIcIin.u16Val = 0;
  RTE_Pri.u16MeterIcPin.u16Val = 0;

  RTE_Sec.u1610mVIntV1Avg.u16Val = 0;
  RTE_Sec.u1610mVExtV1Avg.u16Val = 0;
  RTE_Sec.u1610mAIoutAvg.u16Val = 0;
  RTE_Sec.u16SecStatus00.ALL = 0;
  RTE_Sec.u16SecStatus01.ALL = 0;
  RTE_Sec.u16SecDebug1.u16Val = 0;
  RTE_Sec.u16SecDebug2.u16Val = 0;
	RTE_Sec.u161mVSrNtcAvg.u16Val = 0;
	RTE_Sec.u161mVOringNtcAvg.u16Val = 0;
	
	RTE_sV1FaultFlag00.ALL = 0x00u;
	RTE_sVsbFaultFlag00.ALL = 0x00u;
  RTE_sVoutStateFlag.ALL = 0x00u;
	RTE_sSysStateFlag00.ALL = 0x00u;

  RTE_u16ComToSecDebug1.u16Val = 0;
  RTE_u16ComToSecDebug2.u16Val = 0;
  
  RTE_u161mAIinAvgAvgPri = 0;
  RTE_u16100mAPinAvgAvgPri = 0;
  RTE_u1610mVIntV1AvgAvgSec = 0;
  RTE_u1610mVExtV1AvgAvgSec = 0;
  RTE_u1610mAIoutAvgAvgSec = 0;

  RTE_u16TrimVsbGainOvp.u16Val = 0;
  RTE_u16TrimV1GainOvp.u16Val = 0;
  RTE_u16TrimVsbGainAct.u16Val = RTE_VSB_TRIM_DUTY_INIT;
  RTE_u16TrimV1GainAct.u16Val  = 4095u;
  RTE_u16V1CurrentGain.u16Val  = 4095u;
  RTE_u16IShareOfs.u16Val = 0;
  RTE_u16IShareGain.u16Val     = 4095u;
  RTE_B_DIO_VINOK_ENA = 1u;
  RTE_u8TempTestIndex = 0xFFu;
  
  RTE_uFunctionCtrl.ALL = 0u;
  
  RTE_u8AcLineStatus = 0x01u;
  
  RTE_s16OtWarning = RTE_AMB_OT_WARN_LIMIT;
  
  RTE_bPEC_Enable = TRUE;  
} /* RTE_vRteDataInit() */

/*******************************************************************************
 * \brief         De-Initialize and configure timer modules for 100us system time slice
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void RTE_vDeInit(void)
{
}

/*******************************************************************************
 * Function:        RTE_VsbIShareControl 100us cycle
 *
 * Parameters:      - AD value of Ilocal and Ishunt
 * Returned value:  -the Duty of I local generation PWM
 *
 * Description:     Current Share control, I_Local generation
 *
 ******************************************************************************/
//uint16 RTE_VsbIShareControl(void)
//{
//  static uint16_t IshareDuty = 0;
//  static uint16_t mg_s16IshareAmp = 0;
//  static int16_t e0_ibus = 0;
//  static int16_t e1_ibus = 0;
//  static int32_t u0_ibus = 0;
//  static int32_t u1_ibus = 0;
//  static uint16 mg_u163V3IlocalADCTemp = 0;
//  static sint16 mg_s16IshareOft = 0;
//  uint8  u8Cnt     = 0;
//  CALI_S_COMMON *psSource;

//  if(RTE_B_PSUCTRL_LS_CALI_MODE)     //at calibration mode, 
//  {
//    for (u8Cnt = 0; u8Cnt < CALI_LS_V1_1_LINE_NUM; u8Cnt++)    //V1 cali data
//    {
//      RTE_Cali_Common_sIShareV1_1_Act[u8Cnt].s16Amp = 4096;
//      RTE_Cali_Common_sIShareV1_1_Act[u8Cnt].s16Ofs = 0;
//      RTE_Cali_Common_sIShareV1_1_Act[u8Cnt].s16Thr = 16384;
//    }
//    mg_s16IshareAmp = 4096;
//    mg_s16IshareOft = 0;
//  }
//  else
//  {
//    for (u8Cnt = 0; u8Cnt < CALI_LS_V1_1_LINE_NUM; u8Cnt++)    //V1 cali data
//    {
//      RTE_Cali_Common_sIShareV1_1_Act[u8Cnt].s16Amp = RTE_Cali_Common_sIShareV1_1[u8Cnt].s16Amp;
//      RTE_Cali_Common_sIShareV1_1_Act[u8Cnt].s16Ofs = RTE_Cali_Common_sIShareV1_1[u8Cnt].s16Ofs;
//      RTE_Cali_Common_sIShareV1_1_Act[u8Cnt].s16Thr = RTE_Cali_Common_sIShareV1_1[u8Cnt].s16Thr;
//    }
//    for (u8Cnt = 0; u8Cnt < CALI_LS_VSB_LINE_NUM; u8Cnt++)
//    {
//      psSource = (CALI_S_COMMON*)&RTE_Cali_Common_sIShareVsb[CALI_LS_VSB_LINE_STR] + u8Cnt;
//      if (RTE_au16q12AdcResult[RTE_ADC_E_INDEX_VSB_CURRENT] < psSource->s16Thr)
//      {
//        mg_s16IshareAmp = psSource->s16Amp;
//        mg_s16IshareOft = psSource->s16Ofs;
//        break;
//      }
//    }
//  }
//  
//  mg_u163V3IlocalADCTemp = ((int32_t)RTE_au16q12AdcResult[RTE_ADC_E_INDEX_VSB_CURRENT] * mg_s16IshareAmp) >> 12;
//  if (mg_s16IshareOft < 0)
//  {
//    if (mg_u163V3IlocalADCTemp < (-mg_s16IshareOft))
//    {
//      mg_u163V3IlocalADCTemp = - mg_s16IshareOft;
//    }
//  }
//  mg_u163V3IlocalADCTemp = mg_u163V3IlocalADCTemp + mg_s16IshareOft;
//  e0_ibus = (int16_t)mg_u163V3IlocalADCTemp - RTE_au16q12AdcResult[RTE_ADC_E_INDEX_VSB_CURRENT];

//  /*the Kp and Ki need debug*/
//  //u0_ibus = u1_ibus + (int32_t)Q10(0.5) * e0_ibus + (int32_t)Q10(-0.475) * e1_ibus;
//  u0_ibus = u1_ibus + (int32_t)Q10(0.5) * e0_ibus + (int32_t)Q10(-0.475) * e1_ibus;
// 
//  if (u0_ibus < 0)
//  {
//    u0_ibus = 0;
//  }
//  else if (u0_ibus > Q23(1.0))
//  {
//    u0_ibus = Q23(1.0);
//  }

//  u1_ibus = u0_ibus;
//  e1_ibus = e0_ibus;
//  IshareDuty = u0_ibus >> 11;
//  return ((uint16)IshareDuty);
//}

/* End of file */

