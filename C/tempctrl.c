/*******************************************************************************
 * \file    tempctrl.c
 * \brief   Temperature related routines
 *
 * \section AUTHOR
 *    1. Jackie Chen
 *
 * \section SVN
 *  $Date: 2019-10-31 15:53:09 +0800 (Thu, 31 Oct 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 237 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"

#define TEMPCTRL_EXPORT_H
	#include "tempctrl_api.h"
	#include "tempctrl_cfg.h"
	#include "tempctrl_conf.h"
	#include "tempctrl_scb.h"
	#include "tempctrl_scfg.h"
  #include "tempctrl_rte.h"
  #include "tempctrl.h"
  

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
#define MG_S16_NTC_TEMP_MAX     149
#define MG_S16_NTC_TEMP_MIN     (signed int)-40
#define MG_U16_TABLE_NUMBER     ((uint16)(MG_S16_NTC_TEMP_MAX - MG_S16_NTC_TEMP_MIN + 1))
#define MG_S16_NTC_FAULT_UP     (1010U)     /* if the ADC value Q10 is large than it, set NTC fault */
#define MG_S16_NTC_FAULT_LOW    (20U)       /* if the ADC value Q10 is samll than it, set NTC fault */
/* 
 *  Delta PN:0911035016, RES NTC 10Kohm F 3435K +/-1% SMD 0603 TP, Pull up:2.21K, Vref:3.3V 
 */
const uint16 TEMPCTRL_mg_au16NtcTable1[MG_U16_TABLE_NUMBER] = 
{  /* from -40¡ãC to 149¡ãC */
1012 	,1011 ,1011 ,1010 ,1009 ,1009 ,1008 ,1007 ,1006 ,1005 ,   // -40 ~ -31
1004 	,1003 ,1002 ,1001 ,1000 ,999 	,998 	,996 	,995 	,993 	,   // -30 ~ -21
992 	,990 	,989 	,987 	,985 	,984 	,982 	,980 	,978 	,976 	,   // -20 ~ -11
974 	,971 	,969 	,967 	,964 	,962 	,959 	,956 	,953 	,950 	,   // -10 ~ -1
947 	,944 	,941 	,938 	,934 	,931 	,927 	,923 	,920 	,916 	,   // 0 ~ 9
912 	,908 	,903 	,899 	,894 	,890 	,885 	,880 	,875 	,870 	,   // 10 ~ 19
865 	,860 	,855 	,849 	,844 	,838 	,832 	,826 	,820 	,814 	,   // 20 ~ 29
808 	,801 	,795 	,789 	,782 	,775 	,768 	,762 	,755 	,748 	,   // 30 ~ 39   
741 	,733 	,726 	,719 	,712 	,704 	,697 	,689 	,682 	,674 	,   // 40 ~ 49
667 	,659 	,651 	,644 	,636 	,628 	,620 	,613 	,605 	,597 	,   // 50 ~ 59
589 	,582 	,574 	,566 	,559 	,551 	,543 	,536 	,528 	,520 	,   // 60 ~ 69
513 	,505 	,498 	,490 	,483 	,476 	,468 	,461 	,454 	,447 	,   // 70 ~ 79
440 	,433 	,426 	,419 	,412 	,406 	,399 	,392 	,386 	,379 	,   // 80 ~ 89
373 	,367 	,360 	,354 	,348 	,342 	,336 	,330 	,325 	,319 	,   // 90 ~ 99
313 	,308 	,302 	,297 	,292 	,287 	,282 	,277 	,272 	,267 	,   // 100 ~ 109
262 	,257 	,253 	,248 	,244 	,239 	,235 	,231 	,227 	,223 	,   // 110 ~ 119
219 	,215 	,211 	,208 	,204 	,200  ,195  ,191  ,188  ,184 	,   // 120 ~ 129
181   ,178  ,175  ,172  ,169  ,166  ,163  ,160  ,157  ,154  ,   // 130 ~ 139
152   ,150  ,148  ,146  ,144  ,142  ,40   ,40   ,40   ,40       // 140 ~ 149
};

#define MG_U16_NTC_ADC_30C           808U
     
/***********************************************
 * Over temperature detection setting
 **********************************************/

#define MG_NTC_OPEN_FAULT_DLY                    ((uint8)20U)   /* N*8*10ms */
#define MG_U8_HIGH_BIT                           ((uint8)15U)

/***********************************************
 * Measurement settings
 **********************************************/ 

#define MG_U16_NTC_AVG_CTR                       ((uint16)128U)      /* 128 times averaging */

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
typedef struct MG_sNtc_
{
  uint16 u16q12VoltRaw;
  uint16 u16q12VoltMax;
  uint16 u16q12VoltMin;
  uint32 u32q12VoltSum;
  uint16 u16Cnt;
} MG_sNtc;

typedef struct MG_sTemp_
{
  WORD_VAL u16q10VoltAvg;
  sint16 s16OTPSetPoint;
  sint16 s16OTPResetPoint;
  sint16 s16OTWSetPoint;
  sint16 s16OTWResetPoint;
  uint16 u16OTPDlyCnt;
  uint16 u16OTWDlyCnt;
  sint16 s16Temperature;
  uint16 u16Index;
}MG_sTemp;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/* assign a huge data block to different data bank */

static MG_sNtc  mg_sNtc[TEMPCTRL_CFG_E_INDEX_COUNT];
static MG_sTemp  mg_sTemp[TEMPCTRL_CFG_E_INDEX_COUNT];

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize temperature data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TEMPCTRL_vInit(void)
{
  uint8 ui8Index;

  /* Set initial data for NTC's */
  for (ui8Index = 0U; ui8Index < TEMPCTRL_CFG_E_INDEX_COUNT; ui8Index++)
  {
    mg_sNtc[ui8Index].u16q12VoltRaw = 0U;
    mg_sNtc[ui8Index].u32q12VoltSum = 0U;
    mg_sNtc[ui8Index].u16q12VoltMax = 0U;
    mg_sNtc[ui8Index].u16q12VoltMin = 0xffff;
    mg_sNtc[ui8Index].u16Cnt = 0U;
    
    mg_sTemp[ui8Index].u16q10VoltAvg.u16Val = MG_U16Q10_NTC_ADC_0C;
    mg_sTemp[ui8Index].u16OTPDlyCnt = 0U;
    mg_sTemp[ui8Index].u16OTWDlyCnt = 0U;
    mg_sTemp[ui8Index].s16Temperature = 0U;
    mg_sTemp[ui8Index].u16Index = 70U;
    
    mg_sTemp[ui8Index].s16OTPSetPoint   = TEMPCTRL_CFG_CONF[ui8Index].s16OTPSetPoint;
    mg_sTemp[ui8Index].s16OTPResetPoint = TEMPCTRL_CFG_CONF[ui8Index].s16OTPResetPoint;
    mg_sTemp[ui8Index].s16OTWSetPoint   = TEMPCTRL_CFG_CONF[ui8Index].s16OTWSetPoint;
    mg_sTemp[ui8Index].s16OTWResetPoint = TEMPCTRL_CFG_CONF[ui8Index].s16OTWResetPoint;
  }
}

/*******************************************************************************
 * \brief         DeInitialize temperature data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TEMPCTRL_vDeInit(void)
{
}

/*******************************************************************************
 * \brief         NTC voltage calculation and filter
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TEMPCTRL_vNtcVoltAverage(void)
{
  static uint8 u8NtcIndex = 0U;
  
  mg_sNtc[u8NtcIndex].u16q12VoltRaw = TEMPCTRL_CFG_CONF[u8NtcIndex].u16ReadAdcValue();
  
  /* Get maximum detected NTC voltage */
  if (mg_sNtc[u8NtcIndex].u16q12VoltRaw > mg_sNtc[u8NtcIndex].u16q12VoltMax)
  {
    mg_sNtc[u8NtcIndex].u16q12VoltMax = mg_sNtc[u8NtcIndex].u16q12VoltRaw;
  }
  /* Get mainimum detected NTC voltage */
  else if (mg_sNtc[u8NtcIndex].u16q12VoltRaw < mg_sNtc[u8NtcIndex].u16q12VoltMin)
  {
    mg_sNtc[u8NtcIndex].u16q12VoltMin = mg_sNtc[u8NtcIndex].u16q12VoltRaw;
  }
  /* Integrate ADC RAW values */
  mg_sNtc[u8NtcIndex].u32q12VoltSum += mg_sNtc[u8NtcIndex].u16q12VoltRaw;
  
  /*******************************************************************************
   * Average calculation
   *******************************************************************************/
  /* Count up average counter */
  mg_sNtc[u8NtcIndex].u16Cnt++;
  /* Wait until average counter reaches the defined limit (+2 for max and min subtraction) */
  if ((MG_U16_NTC_AVG_CTR + 2U) <= mg_sNtc[u8NtcIndex].u16Cnt)
  {
    mg_sNtc[u8NtcIndex].u32q12VoltSum = mg_sNtc[u8NtcIndex].u32q12VoltSum -
                                                 mg_sNtc[u8NtcIndex].u16q12VoltMax - 
                                                 mg_sNtc[u8NtcIndex].u16q12VoltMin;
    mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val = ((mg_sNtc[u8NtcIndex].u32q12VoltSum) >> 9);

    /* Reset variables */
    mg_sNtc[u8NtcIndex].u16q12VoltMax = 0U;
    mg_sNtc[u8NtcIndex].u16q12VoltMin = 0xffffU;
    mg_sNtc[u8NtcIndex].u32q12VoltSum = 0U;
    mg_sNtc[u8NtcIndex].u16Cnt = 0U;
  }
  /* Count up NTC index counter */
  u8NtcIndex++;
  /* If max NTC index value reached, reset counter */
  if (TEMPCTRL_CFG_E_INDEX_COUNT <= u8NtcIndex)
  {
    u8NtcIndex = 0U;
  }
}

/*******************************************************************************
 * Function:        LookUpNtcTemperature
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Look up temperature value from table
 *
 ******************************************************************************/ 
void TEMPCTRL_vLookUpNtcTemperature(void) 
{
  const uint16 *uiTablePointer;
  static uint8 u8NtcIndex = 0;  
  static sint16 s16TmpMax = 0;
  uint8 uiTimeOutL = 10;  
  static uint8 u8NtcFaultNbr = 0;

  
  uint8 u8TestIndex;
  
  TEMPCTRL_Rte_Read_R_u8TempTestIndex(&u8TestIndex);
  
  if(u8TestIndex == u8NtcIndex)
  {
    TEMPCTRL_Rte_Read_R_s16TempTestValue(&mg_sTemp[u8NtcIndex].s16Temperature,u8TestIndex);
  }
  else
  {
    /* sensor fault judgement */
    if ((mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val > 1010u) ||
        (mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val < 20u))
    {
      SETBIT(RTE_uSensorFaultStatus.ALL, u8NtcIndex);
      u8NtcFaultNbr++;
      mg_sTemp[u8NtcIndex].s16Temperature = 150;
    }
    else
    {
      CLRBIT(RTE_uSensorFaultStatus.ALL, u8NtcIndex);
      uiTablePointer = &TEMPCTRL_mg_au16NtcTable1[mg_sTemp[u8NtcIndex].u16Index];
     
      uiTimeOutL = 10;
      if ((*uiTablePointer) != mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val)
      {
        if ((*uiTablePointer) > mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val)   
        {
          while ((mg_sTemp[u8NtcIndex].u16Index < (MG_U16_TABLE_NUMBER - 2u)) &&
                 (mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val < (*uiTablePointer)) &&
                 (mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val < (*(uiTablePointer+1u))) &&
                 (uiTimeOutL != 0))
          {
            uiTablePointer++;
            mg_sTemp[u8NtcIndex].u16Index ++;
            uiTimeOutL -- ;
          }
        }
        else
        {
          while ((mg_sTemp[u8NtcIndex].u16Index > 1u) &&
                 (mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val > (*uiTablePointer)) &&
                 (mg_sTemp[u8NtcIndex].u16q10VoltAvg.u16Val > (*(uiTablePointer-1u))) &&
                 (uiTimeOutL != 0))
          { 
            uiTablePointer --;
            mg_sTemp[u8NtcIndex].u16Index --;
            uiTimeOutL -- ;
          }
        }
      }  

      mg_sTemp[u8NtcIndex].s16Temperature = (sint16)(MG_S16_NTC_TEMP_MIN + mg_sTemp[u8NtcIndex].u16Index);
    }

    if (u8NtcIndex == 0)
    {
      s16TmpMax = mg_sTemp[u8NtcIndex].s16Temperature;
    }
    if (mg_sTemp[u8NtcIndex].s16Temperature > s16TmpMax)
    {
      s16TmpMax = mg_sTemp[u8NtcIndex].s16Temperature;
    }
  }
  
  u8NtcIndex ++;
  if (u8NtcIndex >= TEMPCTRL_CFG_E_INDEX_COUNT)
  {
    u8NtcIndex = 0;
    
    if (u8NtcFaultNbr)
    {
      RTE_TEMP_NTC_FAULT = 1u;
    }
    else
    {
      RTE_TEMP_NTC_FAULT = 0;
    }
    u8NtcFaultNbr = 0;
  }
}

/*******************************************************************************
 * \brief         NTC OTP monitor             10ms
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TEMPCTRL_vNtcTempMonitor(void)
{
  static uint8  u8NtcIndex = 0U;
  sint16 s16DiffByFanFail;
  
  /* At Fan_Fault condition, OTP and OTW point should decrease to prevent PSU being damage.*/
  if(FALSE != TEMPCTRL_SCFG_u8ReadFanBitFail())
  {
    s16DiffByFanFail = TEMPCTRL_CFG_CONF[u8NtcIndex].s16DiffByFanFail;
  }
  else
  {
    s16DiffByFanFail = 0;
  }

  if (mg_sTemp[u8NtcIndex].s16Temperature > (mg_sTemp[u8NtcIndex].s16OTWSetPoint - s16DiffByFanFail))
  {
    if (mg_sTemp[u8NtcIndex].u16OTWDlyCnt > TEMPCTRL_CFG_CONF[u8NtcIndex].u16OTWDlyTime)
    {
      SETBIT(RTE_uTempOtwStatus.ALL, u8NtcIndex);
			SETBIT(RTE_uTempOtwStatus.ALL, MG_U8_HIGH_BIT);
    }
    else
    {
      mg_sTemp[u8NtcIndex].u16OTWDlyCnt++;
    }

    if (mg_sTemp[u8NtcIndex].s16Temperature > (mg_sTemp[u8NtcIndex].s16OTPSetPoint - s16DiffByFanFail))
    {
      if (mg_sTemp[u8NtcIndex].u16OTPDlyCnt > TEMPCTRL_CFG_CONF[u8NtcIndex].u16OTPDlyTime)
      {
        if(FALSE == TEMPCTRL_Rte_Read_B_R_DISABLE_OT())
        {
#ifndef HALT_TEST_MODE
          SETBIT(RTE_uTempOtpStatus.ALL, u8NtcIndex);
          SETBIT(RTE_uTempOtpStatus.ALL, MG_U8_HIGH_BIT);
#endif
        }
      }
      else
      {
        mg_sTemp[u8NtcIndex].u16OTPDlyCnt++;
      }
    }
  }
  else
  {
    if (mg_sTemp[u8NtcIndex].s16Temperature < (mg_sTemp[u8NtcIndex].s16OTPResetPoint - s16DiffByFanFail))
    {
      if (mg_sTemp[u8NtcIndex].u16OTPDlyCnt > 0)
      {
        mg_sTemp[u8NtcIndex].u16OTPDlyCnt--;
      }
      else
      {
        CLRBIT(RTE_uTempOtpStatus.ALL, u8NtcIndex);
      }
      
      if (mg_sTemp[u8NtcIndex].s16Temperature < (mg_sTemp[u8NtcIndex].s16OTPResetPoint - s16DiffByFanFail))
      {
        if (mg_sTemp[u8NtcIndex].u16OTWDlyCnt > 0)
        {
          mg_sTemp[u8NtcIndex].u16OTWDlyCnt--;
        }
        else
        {
          CLRBIT(RTE_uTempOtwStatus.ALL, u8NtcIndex);
        }
      }
    }
  }

  u8NtcIndex++;
  if (u8NtcIndex >= TEMPCTRL_CFG_E_INDEX_COUNT)
  {
    u8NtcIndex = 0;
  }
	
	if((RTE_uTempOtwStatus.ALL & 0x7Fu) == 0)
	{
		CLRBIT(RTE_uTempOtwStatus.ALL, MG_U8_HIGH_BIT);
	}
	
	if((RTE_uTempOtpStatus.ALL & 0x7Fu) == 0)
	{
		CLRBIT(RTE_uTempOtpStatus.ALL, MG_U8_HIGH_BIT);
	}
}

/*******************************************************************************
 * \brief         Read temperature value
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
sint16 TEMPCTRL_s16ReadTempValue(uint8 u8Index)
{
  return mg_sTemp[u8Index].s16Temperature;
}

/*******************************************************************************
 * \brief         Read Adc average value
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
uint16 TEMPCTRL_u16ReadAdcAvgValue(uint8 u8Index)
{
  return mg_sTemp[u8Index].u16q10VoltAvg.u16Val;
}

/*******************************************************************************
 * \brief         Set OT Warning Limit value
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TEMPCTRL_vSetOtWarnValue(uint8 u8Index, sint16 s16Data)
{
  mg_sTemp[u8Index].s16OTWSetPoint = s16Data;
}


/*
 * End of file
 */
