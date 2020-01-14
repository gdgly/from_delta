/** *****************************************************************************
 * \file    intcom.c
 * \brief   Internal communication data processing
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

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "debug_llc.h"

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
void INTCOM_vTxData(uint8 *pau8TxBuf, uint16 *u16TxDataNbr)
{
  /* Init data */
  GLOBAL_U_U16BIT uLlcStatus00;
  GLOBAL_U_U16BIT uLlcStatus01;
  GLOBAL_U_U16BIT uLlcStatus02;
  GLOBAL_U_U8BIT  uTempStatus00;
  uint16 u16DebugData0;
  uint16 u16DebugData1;
  uint16 u16DebugData2;
  uint16 u1610mVVoltOutExtAvg;
  uint16 u1610mACurrOutAvg;
  uint16 u16100mWPwrOutAvg;
  uint16 u161mVVoltNtc1;
  uint16 u161mVVoltNtc2;
  uint16 u1610mVVoltOutIntAvg;
  uint16 u161mVIshareAvg;
  uint16 u161mVILocalAvg;
  uint8 u8BlFwVerMajor;
  uint8 u8BlFwVerMinor;
  uint8 u8BlFwVerDebug;   

  /* Read data from RTE */
  INTCOM_Rte_Read_R_uLlcStatus00(&uLlcStatus00);
  INTCOM_Rte_Read_R_uLlcStatus01(&uLlcStatus01);
  INTCOM_Rte_Read_R_uLlcStatus02(&uLlcStatus02);
  INTCOM_Rte_Read_R_uTempStatus00(&uTempStatus00);
  INTCOM_Rte_Read_R_u16DebugData0(&u16DebugData0);
  INTCOM_Rte_Read_R_u16DebugData1(&u16DebugData1);
  INTCOM_Rte_Read_R_u16DebugData2(&u16DebugData2);
  INTCOM_Rte_Read_R_u1610mVVoltOutExtAvg(&u1610mVVoltOutExtAvg);
  INTCOM_Rte_Read_R_u1610mACurrOutAvg(&u1610mACurrOutAvg);
  INTCOM_Rte_Read_R_u16100mWPwrOutAvg(&u16100mWPwrOutAvg);
  INTCOM_Rte_Read_R_u161mVVoltNtc1(&u161mVVoltNtc1);
  INTCOM_Rte_Read_R_u161mVVoltNtc2(&u161mVVoltNtc2);
  INTCOM_Rte_Read_R_u1610mVVoltOutIntAvg(&u1610mVVoltOutIntAvg);
  INTCOM_Rte_Read_R_u161mVIshareAvg(&u161mVIshareAvg);
  INTCOM_Rte_Read_R_u161mVILocalAvg(&u161mVILocalAvg);
  INTCOM_Rte_Read_R_u8BlFwVerMajor(&u8BlFwVerMajor);
  INTCOM_Rte_Read_R_u8BlFwVerMinor(&u8BlFwVerMinor);
  INTCOM_Rte_Read_R_u8BlFwVerDebug(&u8BlFwVerDebug);

  /* Fill buffer */
  pau8TxBuf[(*u16TxDataNbr)++] = MG_APP_MAJOR_REV;
  pau8TxBuf[(*u16TxDataNbr)++] = MG_APP_MINOR_REV;
  pau8TxBuf[(*u16TxDataNbr)++] = MG_APP_DEBUG_REV;
  pau8TxBuf[(*u16TxDataNbr)++] = u8BlFwVerMajor;
  pau8TxBuf[(*u16TxDataNbr)++] = u8BlFwVerMinor;
  pau8TxBuf[(*u16TxDataNbr)++] = u8BlFwVerDebug;
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&uLlcStatus00));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&uLlcStatus00) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&uLlcStatus01));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&uLlcStatus01) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&uLlcStatus02));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&uLlcStatus02) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&uTempStatus00));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u16DebugData0));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u16DebugData0) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u16DebugData1));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u16DebugData1) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u16DebugData2));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u16DebugData2) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u1610mVVoltOutExtAvg));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u1610mVVoltOutExtAvg) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u1610mACurrOutAvg));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u1610mACurrOutAvg) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u16100mWPwrOutAvg));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u16100mWPwrOutAvg) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u161mVVoltNtc1));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u161mVVoltNtc1) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u161mVVoltNtc2));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u161mVVoltNtc2) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u1610mVVoltOutIntAvg));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u1610mVVoltOutIntAvg) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u161mVIshareAvg));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u161mVIshareAvg) + 1U);
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u161mVILocalAvg));
  pau8TxBuf[(*u16TxDataNbr)++] = *((uint8 *)(&u161mVILocalAvg) + 1U);
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
void INTCOM_vRxData(uint8 *pau8RxBuf, uint8 u8BroadcastFlg, uint16 u16RxBufCnt)
{
  GLOBAL_U_U16BIT uCom2Pri00;
  GLOBAL_U_U16BIT uDebugData0Addr;
  GLOBAL_WORD_VAL u16q12CalibVoltOutGain;
  GLOBAL_WORD_VAL u16q12CalibCurrOutGain;
  GLOBAL_WORD_VAL u16q12CalibIshareGain;
  GLOBAL_WORD_VAL u100mHzVoltInFreq;
  GLOBAL_WORD_VAL u16q12CalibIshareOfs;
  GLOBAL_WORD_VAL s16CalibVoltOutAmp;
  GLOBAL_WORD_VAL s16CalibCurrOutAmp;
  GLOBAL_WORD_VAL s16CalibVoltOutOfs;
  GLOBAL_WORD_VAL s16CalibCurrOutOfs;

  if ( pau8RxBuf[u16RxBufCnt++] & MG_BOOT_MASK) /* Check if slave in boot mode */
  {
    /* Go to Boot Aera */
    INTCOM_Rte_Write_P_B_BL_MODE(TRUE);
    INTCOM_Rte_Write_P_B_PFC_HALT(TRUE);
  }
  else
  {
    /* Com2SecStatus:
     * bit0 Enable V1
     * bit1 Enable V1 OVP Test
     * bit2 AC Lost
     * bit3 Remote On
     * bit4 Vin Line Low
     * bit5 Clear Latch Fault
     * bit6 Disable Vshare    
     */ 
    if (u8BroadcastFlg)
    {
      /* Read data from buffer */
      uCom2Pri00.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uCom2Pri00.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      uDebugData0Addr.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uDebugData0Addr.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibVoltOutGain.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibVoltOutGain.Bytes.HB = pau8RxBuf[u16RxBufCnt++];

      /* Write data to RTE */
      INTCOM_Rte_Write_P_uComStatus00(uCom2Pri00);
      INTCOM_Rte_Write_P_u16DebugData0(*((uint16 *)(uDebugData0Addr.ALL + 0x08000000)));
    }
    else
    {
      /* Read data from buffer */
      uCom2Pri00.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uCom2Pri00.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      uDebugData0Addr.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uDebugData0Addr.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibVoltOutGain.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibVoltOutGain.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibCurrOutGain.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibCurrOutGain.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibIshareGain.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibIshareGain.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      u100mHzVoltInFreq.Bytes.LB = pau8RxBuf[u16RxBufCnt++];  
      u100mHzVoltInFreq.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      u16q12CalibIshareOfs.Bytes.LB = pau8RxBuf[u16RxBufCnt++]; 
      u16q12CalibIshareOfs.Bytes.HB = pau8RxBuf[u16RxBufCnt++];    
      s16CalibVoltOutAmp.Bytes.LB = pau8RxBuf[u16RxBufCnt++]; 
      s16CalibVoltOutAmp.Bytes.HB = pau8RxBuf[u16RxBufCnt++];  
      s16CalibVoltOutOfs.Bytes.LB = pau8RxBuf[u16RxBufCnt++]; 
      s16CalibVoltOutOfs.Bytes.HB = pau8RxBuf[u16RxBufCnt++];   
      s16CalibCurrOutAmp.Bytes.LB = pau8RxBuf[u16RxBufCnt++]; 
      s16CalibCurrOutAmp.Bytes.HB = pau8RxBuf[u16RxBufCnt++]; 
      s16CalibCurrOutOfs.Bytes.LB = pau8RxBuf[u16RxBufCnt++]; 
      s16CalibCurrOutOfs.Bytes.HB = pau8RxBuf[u16RxBufCnt++];  

      /* Process data */
      u16q12CalibVoltOutGain.s16Val = LIMIT(u16q12CalibVoltOutGain.s16Val, MG_U16Q12_CALIB_GAIN_MIN, MG_U16Q12_CALIB_GAIN_MAX);
      u16q12CalibCurrOutGain.s16Val = LIMIT(u16q12CalibCurrOutGain.s16Val, MG_U16Q12_CALIB_GAIN_MIN, MG_U16Q12_CALIB_GAIN_MAX);
      u16q12CalibIshareGain.s16Val = LIMIT(u16q12CalibIshareGain.s16Val, MG_U16Q12_CALIB_GAIN_MIN, MG_U16Q12_CALIB_GAIN_MAX);
      u16q12CalibIshareOfs.s16Val = LIMIT(u16q12CalibIshareOfs.s16Val, MG_S16_10mA_CALIB_OFS_MIN, MG_S16_10mA_CALIB_OFS_MAX);
      
      /* Write data to RTE */
      INTCOM_Rte_Write_P_uComStatus00(uCom2Pri00);
      INTCOM_Rte_Write_P_u16DebugData0(*((uint16 *)(uDebugData0Addr.ALL + 0x08000000)));
      INTCOM_Rte_Write_P_u16q12CalibVoltOutGain(u16q12CalibVoltOutGain.s16Val);
      INTCOM_Rte_Write_P_u16q12CalibCurrOutGain(u16q12CalibCurrOutGain.s16Val);
      INTCOM_Rte_Write_P_u16q12CalibIshareGain(u16q12CalibIshareGain.s16Val);
      INTCOM_Rte_Write_P_s1610mACalibIshareOfs(u16q12CalibIshareOfs.s16Val);
      INTCOM_Rte_Write_P_u16100mHzVoltInFreq(u100mHzVoltInFreq.u16Val);
      INTCOM_Rte_Write_P_s16CalibVoltOutAmp(s16CalibVoltOutAmp.s16Val);
      INTCOM_Rte_Write_P_s16CalibCurrOutAmp(s16CalibCurrOutAmp.s16Val);
      INTCOM_Rte_Write_P_s16CalibVoltOutOfs(s16CalibVoltOutOfs.s16Val);
      INTCOM_Rte_Write_P_s16CalibCurrOutOfs(s16CalibCurrOutOfs.s16Val);

      INTCOM_Rte_Write_P_B_LLC_FAULT_CLR(uCom2Pri00.Bits.f5);
      INTCOM_Rte_Write_P_B_VIN_LINE(uCom2Pri00.Bits.f4 == 0?1u:0);
      INTCOM_Rte_Write_P_B_PRIM_VIN_LOST(uCom2Pri00.Bits.f2);
      INTCOM_Rte_Write_P_B_LLC_OVP_TEST(uCom2Pri00.Bits.f1);
    }
  }
}


/*
 * End of file
 */
