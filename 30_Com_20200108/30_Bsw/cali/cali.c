/** *****************************************************************************
 * \file    cali.c
 * \brief   MCU calibration
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-10-14 17:07:42 +0800 (Mon, 14 Oct 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 234 $
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
#define CALI_EXPORT_H
  #include "cali_api.h"
  #include "cali_scb.h"
  #include "cali_cfg.h"
  #include "cali_scfg.h"
  #include "cali_rte.h"
  #include "cali_conf.h"

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static uint8 mg_u8CaliSensor = 0;
static uint8 mg_u8DataBuf[10];
static uint16 mg_u16Tmp;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void   mg_vSaveCaliData(void);
static void   mg_vCopyCaliData(uint8 u8Mode, uint8 u8Line);
static void   mg_vCopyDataToBuf(CALI_S_COMMON *psThis, CALI_S_COMMON *psCopy);
static void   mg_vReadEepData(uint16 u16StartAddr, uint8 u8LineMax, CALI_S_COMMON *psThis);
static sint32 mg_s32GetCalibratedData(uint16 u16AdcAvg, uint8 u8MaxLine, CALI_S_COMMON *pCal);

static void mg_vCalibrateVin(void);
static void mg_vCalibrateIin(void);
static void mg_vCalibratePin(void);
static void mg_vCalibrateV1(void);
static void mg_vCalibrateVsb(void);
static void mg_vCalibrateV1Sense(void);
static void mg_vCalibrateIShave(void);


static void mg_vSetDefaultCaliData(void);
static void mg_vCaliDefaultVinAc(void);
static void mg_vCaliDefaultIinAc(void);
static void mg_vCaliDefaultPinAc(void);
static void mg_vCaliDefaultVoutV1(void);
static void mg_vCaliDefaultIoutV1(void);
static void mg_vCaliDefaultVoutVsb(void);
static void mg_vCaliDefaultIoutVsb(void);
static void mg_vCaliDefaultV1IShare(void);
static void mg_vCalcV1CurrentGain(void);

static void mg_vReadCalibPara(uint8 u8Mode, uint8 u8Line);

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Set initial value for calibration data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vInit(void)
{
  /* Set all default calibration data */
  mg_vSetDefaultCaliData();

  /* Load Sensor Calibration Data from EEPROM if CRC is correct */
  mg_vReadEepData(EEPROM_ADR_VIN_AC_BASE, CALI_VIN_AC_LINE_NUM,  &CALI_RTE_W_sData.sVinAc[0]);      /* VIN_AC */
  mg_vReadEepData(EEPROM_ADR_IIN_AC_BASE, CALI_IIN_AC_LINE_NUM,  &CALI_RTE_W_sData.sIinAc[0]);      /* IIN_AC */
//  mg_vReadEepData(EEPROM_ADR_PIN_AC_BASE, CALI_PIN_AC_LINE_NUM,  &CALI_RTE_W_sData.sPinAc[0]);      /* PIN_AC */

  mg_vReadEepData(EEPROM_ADR_V_V1_BASE,   CALI_V_V1_LINE_NUM,    &CALI_RTE_W_sData.sVoutV1[0]);     /* V_V1 */
  mg_vReadEepData(EEPROM_ADR_I_V1_BASE,   CALI_I_V1_LINE_NUM,    &CALI_RTE_W_sData.sIoutV1[0]);     /* I_V1 */
  mg_vReadEepData(EEPROM_ADR_V_VSB_BASE,  CALI_V_VSB_LINE_NUM,   &CALI_RTE_W_sData.sVoutVsb[0]);    /* V_VSB */
  mg_vReadEepData(EEPROM_ADR_I_VSB_BASE,  CALI_I_VSB_LINE_NUM,   &CALI_RTE_W_sData.sIoutVsb[0]);    /* I_VSB */
	
  mg_vReadEepData(EEPROM_ADR_V1_ISHARE_BASE,  CALI_V1_ISHARE_LINE_NUM, &CALI_RTE_W_sData.sV1IShare[0]);    /* V1 I share */
  
  mg_vCalcV1CurrentGain();

} /* CALI_vInit */

/*******************************************************************************
 * \brief         De-Initialize
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vDeInit(void)
{
}

/********************************************************************************
 * \brief         Handle calibration and save data in EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCaliHandler(void)
{

  if (TRUE == CALI_uStatus.Bits.CALI_COMMAND)
  {
    /* cali mode, when recived data to copy and save data  */
    mg_vCopyCaliData(CALI_sPara.u8DataMode, CALI_sPara.u8DataLine);

    if (CALI_uStatus.Bits.CALI_SAVE_NEED)
    {
      mg_vSaveCaliData();
      CALI_uStatus.Bits.CALI_SAVE_NEED = FALSE;
    }
    CALI_uStatus.Bits.CALI_COMMAND = FALSE;
  }
  else
  {
    /* normal mode, to update output sensors  */
    switch (mg_u8CaliSensor)
    {
      case MG_E_DO_CALI_VIN:
      {
        mg_vCalibrateVin();
        mg_u8CaliSensor = MG_E_DO_CALI_IIN;
        break;
      }

      case MG_E_DO_CALI_IIN:
      {
        mg_vCalibrateIin();
        mg_u8CaliSensor = MG_E_DO_CALI_PIN;
        break;
      }

      case MG_E_DO_CALI_PIN:
      {
        mg_vCalibratePin();
        mg_u8CaliSensor = MG_E_DO_CALI_V1;
        break;
      }
      case MG_E_DO_CALI_V1:
      {
        mg_vCalibrateV1();
        mg_u8CaliSensor = MG_E_DO_CALI_VSB;
        break;
      }

      case MG_E_DO_CALI_VSB:
      {
        mg_vCalibrateVsb();
        mg_u8CaliSensor = MG_E_DO_CALI_V1SENSE;
        break;
      }
			
			case MG_E_DO_CALI_V1SENSE:
			{
        mg_vCalibrateV1Sense();
        mg_u8CaliSensor = MG_E_DO_CALI_V1ISHARE;
			}
			
			case MG_E_DO_CALI_V1ISHARE:
			{
        mg_vCalibrateIShave();
        mg_u8CaliSensor = MG_E_DO_CALI_VIN;
				break;
			}

      default:
      {
        mg_u8CaliSensor = MG_E_DO_CALI_VIN;
        break;
      }
    }
  }
} /* CALI_vCaliHandler */

/********************************************************************************
 * \brief         Calibrate the Iout for OCP
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCalibrateIout(void)
{
  RTE_u16CaliIout = mg_s32GetCalibratedData( RTE_Sec.u1610mAIoutAvg.u16Val,
                                             CALI_I_V1_LINE_NUM,
                                             (CALI_S_COMMON*)&CALI_RTE_R_sData.sIoutV1 );
}

/********************************************************************************
 * \brief         Calibrate the Ishare Gain for secondary side.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCalibrateIShare(void)
{
  uint8  u8Cnt     = 0;
  WORD_VAL u161mAV1Current;
  uint16 u16V1CurrentGain;
  sint16 s16Ofs;
  
  CALI_Rte_Read_R_u1610mAIoutAvg(&u161mAV1Current);

  for (u8Cnt = 0; u8Cnt < CALI_V1_ISHARE_LINE_NUM; u8Cnt++)
  {
    if (u161mAV1Current.u16Val < CALI_RTE_R_sData.sV1IShare[u8Cnt].s16Thr)
    {
      u16V1CurrentGain = CALI_RTE_R_sData.sV1IShare[u8Cnt].s16Amp;
      s16Ofs = CALI_RTE_R_sData.sV1IShare[u8Cnt].s16Ofs;
      break;
    }
  }
  
  CALI_Rte_Write_P_u16IShareGain(u16V1CurrentGain);
  CALI_Rte_Write_P_u16IShareOfs(s16Ofs);
}

/********************************************************************************
 * \brief         Calibrate the voltage and current of V1.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCalibrateV1(void)
{
  mg_vCalibrateV1();
}

void CALI_vCaliFast(void)
{
  CALI_SCFG_vGetVsbIntVolt(&mg_u16Tmp);

  mg_u16Tmp = mg_s32GetCalibratedData( mg_u16Tmp,
                                       CALI_V_VSB_LINE_NUM,
                                       (CALI_S_COMMON*)&CALI_RTE_R_sData.sVoutVsb[0]);
  CALI_Rte_Write_P_u16VoutIntVsbFast(mg_u16Tmp<<2);

#if 0 /*  */
  CALI_SCFG_vGetVsbExtVolt(&mg_u16Tmp);

  mg_u16Tmp = mg_s32GetCalibratedData( mg_u16Tmp,
                                       CALI_V_VSB_LINE_NUM,
                                       (CALI_S_COMMON*)&CALI_RTE_R_sData.sVoutVsb[0]);

  CALI_Rte_Write_P_u16VoutExtVsbFast(mg_u16Tmp<<2);
#endif

  CALI_SCFG_vGetVsbCurr(&mg_u16Tmp);

  mg_u16Tmp = (uint16)(((uint32)mg_u16Tmp * RTE_CALI_sData.sIoutVsb[CALI_I_VSB_LINE_NUM -1u].s16Amp + 4096) >> 13);

  CALI_Rte_Write_P_u16IoutVsbFast(mg_u16Tmp);
}

/********************************************************************************
 * \brief         Calibrate the Ishare Gain for secondary side.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCalcCaliPara(void)
{
  uint8  u8Cnt;
  WORD_VAL u16Data;
  sint16 s16Amp;
  sint16 s16Ofs;
  
  CALI_Rte_Read_R_u1610mAIoutAvg(&u16Data);

  for (u8Cnt = 0; u8Cnt < CALI_I_V1_LINE_NUM; u8Cnt++)
  {
    if (u16Data.u16Val < CALI_RTE_R_sData.sIoutV1[u8Cnt].s16Thr)
    {
      s16Amp = CALI_RTE_R_sData.sIoutV1[u8Cnt].s16Amp;
      s16Ofs = CALI_RTE_R_sData.sIoutV1[u8Cnt].s16Ofs;
      break;
    }
  }
  
  CALI_Rte_Write_P_u16CaliI1Amp(s16Amp);
  CALI_Rte_Write_P_u16CaliI1Ofs(s16Ofs);
  
  CALI_Rte_Read_R_u1610mVVoutAvg(&u16Data);

  for (u8Cnt = 0; u8Cnt < CALI_V_V1_LINE_NUM; u8Cnt++)
  {
    if (u16Data.u16Val < CALI_RTE_R_sData.sVoutV1[u8Cnt].s16Thr)
    {
      s16Amp = CALI_RTE_R_sData.sVoutV1[u8Cnt].s16Amp;
      s16Ofs = CALI_RTE_R_sData.sVoutV1[u8Cnt].s16Ofs;
      break;
    }
  }
  
  CALI_Rte_Write_P_u16CaliV1Amp(s16Amp);
  CALI_Rte_Write_P_u16CaliV1Ofs(s16Ofs);
  
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/********************************************************************************
 * \brief         Calibrate the Vin
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCalibrateVin(void)
{
  uint16 u16CaliVin = 0;
  
  /* AC input */
  u16CaliVin = mg_s32GetCalibratedData( RTE_Pri.u1610mVVinAvg.u16Val,
                                        CALI_VIN_AC_LINE_NUM,
                                       (CALI_S_COMMON*)&CALI_RTE_R_sData.sVinAc[0] );
  
  if(FALSE != CALI_Rte_Read_B_R_VIN_OK())
  {
    RTE_PMB_Write_u16Vin_Mul_128_Box(u16CaliVin);
  }

  RTE_PMB_Write_u16Vin_Mul_128 ( u16CaliVin );
} /* mg_vCalibrateVin */


/********************************************************************************
 * \brief         Calibrate the Iin
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCalibrateIin(void)
{
  uint16 u16CaliIin;
  uint32 u32CaliPin;
  uint16 u16Temp;

  /* AC input */
  u16CaliIin = mg_s32GetCalibratedData( RTE_Pri.u161mAIinAvg.u16Val,
                                        CALI_IIN_AC_LINE_NUM,
                                       (CALI_S_COMMON*)&CALI_RTE_R_sData.sIinAc[0]);
  
  if(FALSE != CALI_Rte_Read_B_R_VIN_OK())
  {
    RTE_PMB_Write_u16Iin_Mul_128_Box(u16CaliIin);
  }

  RTE_PMB_Write_u16Iin_Mul_128 ( u16CaliIin );

  if (0 < RTE_Pri.u16q16PwrFact.u16Val)
  {
    u16Temp = RTE_Pri.u16q16PwrFact.u16Val;
  }
  else
  {
    /* no need to add below compensation if use primary power factor calc */    
    u16Temp = (uint16)((((uint32)RTE_Pri.u161mAIinAvg.u16Val) * ((uint32)RTE_Pri.u1610mVVinAvg.u16Val)) / 10000u);
    if(1u >  u16Temp)
    {
      u16Temp = 1u;
    }
    u16Temp = (uint16)(((uint32)RTE_Pri.u16100mAPinAvg.u16Val << 16)/u16Temp);
    if (u16Temp > 65535u)
    {
      u16Temp = 65535u;
    }
  }
  if(RTE_B_PRI_VDC_IN)  /* DC input */
  {
    u16Temp = 65535u;
  }

  u32CaliPin = (((((uint32)RTE_PMB_Read_u16Iin_Mul_128() * (uint32)RTE_PMB_Read_u16Vin_Mul_128()))>>11u) * u16Temp) >> 12u;
  
  if(u32CaliPin < RTE_PMB_Read_u32Pout_V1_Mul_128())
  {
    u32CaliPin = RTE_PMB_Read_u32Pout_V1_Mul_128() + 64u;
  }
  RTE_PMB_Write_u32Pin_Mul_128 ( u32CaliPin );
  
  if(FALSE != CALI_Rte_Read_B_R_VIN_OK())
  {
    RTE_PMB_Write_u32Pin_Mul_128_Box(u32CaliPin);
  }
} /* mg_vCalibrateIin */

/********************************************************************************
 * \brief         Calibrate the Pin
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCalibratePin(void)
{
//  uint32 u32CaliPin = 0;

//  /* AC input */
//  u32CaliPin = mg_s32GetCalibratedData( RTE_Pri.u16100mAPinAvg.u16Val,
//                                        CALI_PIN_AC_LINE_NUM,
//                                       (CALI_S_COMMON*)&CALI_RTE_R_sData.sPinAc[0] );

//  RTE_PMB_Write_u32Pin_Mul_128( u32CaliPin );
} /* mg_vCalibratePin */

/********************************************************************************
 * \brief         Calibrate the Vout,Iout,and calculate Pout of 54V output1
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCalibrateV1(void)
{
  uint16 u16CaliVout = 0;
  uint16 u16CaliIout = 0;
  uint32 u32CaliPout = 0;
  uint32 u32Dummy1 = 0;
  uint32 u32Dummy2 = 0;

	u16CaliVout = mg_s32GetCalibratedData( RTE_Sec.u1610mVIntV1Avg.u16Val,
																			 CALI_V_V1_LINE_NUM,
																			(CALI_S_COMMON*)&CALI_RTE_R_sData.sVoutV1[0] );

	u16CaliIout = mg_s32GetCalibratedData( RTE_Sec.u1610mAIoutAvg.u16Val,
																			 CALI_I_V1_LINE_NUM,
																			(CALI_S_COMMON*)&CALI_RTE_R_sData.sIoutV1[0] );
	
	RTE_PMB_Write_u16Vout_V1_Mul_512_Box ( (u16CaliVout << 2) );
	RTE_PMB_Write_u16Iout_V1_Mul_128_Box ( u16CaliIout );
	
  /* Calibrate Vout V1 */
  if (CALI_Rte_Read_B_R_V1_ON())
  {
    u32Dummy1 =  (uint32)(u16CaliVout);
    u32Dummy1 *= (uint32)(u16CaliIout);
    u32Dummy2 = (u32Dummy1 + 64u) >> 7;
    u32CaliPout = (uint32)u32Dummy2;
  }
  else
  {
    u16CaliVout = 0;
    u16CaliIout = 0;
    u32CaliPout = 0;
  }

  RTE_PMB_Write_u16Vout_V1_Mul_512 ( (u16CaliVout << 2) );
  RTE_PMB_Write_u16Iout_V1_Mul_128 ( u16CaliIout );
  RTE_PMB_Write_u32Pout_V1_Mul_128 ( u32CaliPout );
} /* mg_vCalibrateV1 */

/********************************************************************************
 * \brief         Calibrate the Vsb voltage and current
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCalibrateVsb(void)
{
  uint16 u16CaliVoutVsb = 0;
  uint16 u16CaliIoutVsb = 0;
  uint32 u32CaliPoutVsb = 0;
  uint32 u32Dummy1 = 0;
  uint32 u32Dummy2 = 0;
	
	u16CaliVoutVsb = mg_s32GetCalibratedData( CALI_SCFG_u16GetVsbIntVoltAvg(),
																						CALI_V_VSB_LINE_NUM,
																					 (CALI_S_COMMON*)&CALI_RTE_R_sData.sVoutVsb[0]);
	
	u16CaliIoutVsb = mg_s32GetCalibratedData( CALI_SCFG_u16GetVsbCurrAvg(),
																						CALI_I_VSB_LINE_NUM,
																					 (CALI_S_COMMON*)&CALI_RTE_R_sData.sIoutVsb[0] );
	
  RTE_PMB_Write_u16Vout_VSB_Mul_512_Box ( (u16CaliVoutVsb << 2) );
  RTE_PMB_Write_u16Iout_VSB_Mul_128_Box ( u16CaliIoutVsb );

  /* Calibrate Vout VSB */
  if(FALSE != CALI_Rte_Read_B_R_VSB_ON())
//	if(1)//for test
  {
    u32Dummy1 =  (uint32)(u16CaliVoutVsb);
    u32Dummy1 *= (uint32)(u16CaliIoutVsb);
    u32Dummy2 = (u32Dummy1 + 64u) >> 7;
    u32CaliPoutVsb = (uint32)u32Dummy2;
  }
  else
  {
    u16CaliVoutVsb = 0;
    u16CaliIoutVsb = 0;
  }
	
  RTE_PMB_Write_u16Vout_VSB_Mul_128 ( u16CaliVoutVsb );
  RTE_PMB_Write_u16Iout_VSB_Mul_128 ( u16CaliIoutVsb );
  RTE_PMB_Write_u32Pout_VSB_Mul_128 ( u32CaliPoutVsb );
} /* mg_vCalibrateVsb */

/********************************************************************************
 * \brief         Calibrate the V1 sense voltage
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCalibrateV1Sense(void)
{
	uint16 u16CaliV1Sense;
	uint32 u32Dummy;
	
	u32Dummy = ((uint32)(MG_V1_SENSE_AMP_DEFAULT))* ((uint32)RTE_Sec.u1610mVExtV1Avg.u16Val);
	u16CaliV1Sense = (uint16) ((u32Dummy + 256u) >> 7);
	
	RTE_PMB_Write_u16Vout_V1Sense_Mul_128(u16CaliV1Sense);
}

/********************************************************************************
 * \brief         Calibrate the I Share voltage
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCalibrateIShave(void)
{
	uint16 u16CaliISense;
	uint32 u32Dummy;
	
	u32Dummy = ((uint32)(MG_ISHARE_AMP_DEFAULT))* ((uint32)RTE_Sec.u16VIShareAdcAvgAdc.u16Val);
	u16CaliISense = (uint16) ((u32Dummy + 256u) >> 7);
	
	RTE_PMB_Write_u16Vout_V1IShare_Mul_128(u16CaliISense);
	
}

/********************************************************************************
 * \brief         Copy calibration data from I2C to RAM
 *
 * \param[in]     - u8CaliMode, bCaliLine
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCopyCaliData(uint8 u8Mode, uint8 u8Line)
{
  uint8  u8CaliLine = 0;
  uint8  u8CaliValid = 0;
  uint16 u16AddrOffset = 0;

  CALI_uStatus.Bits.CALI_DEFAULT = FALSE;
  CALI_uStatus.Bits.CALI_SAVE_NEED = FALSE;

  if (u8Mode == CALI_DEF_MODE)
  {
    mg_vSetDefaultCaliData();
  }
  else
  {
    if (CALI_uStatus.Bits.CALI_READ) 
    {
      mg_vReadCalibPara(u8Mode,u8Line);
      return;
    }

    if (u8Line > 0)
    {
      u8CaliLine = u8Line - 1;
      u16AddrOffset = u8CaliLine << 3;
    }
    switch (u8Mode)
    {
      case CALI_VIN_AC:
      {
        if (u8CaliLine < CALI_VIN_AC_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_RTE_W_sData.sVinAc[u8CaliLine],  &CALI_sPara.sUser);
          CALI_sPara.u16SaveAddr = EEPROM_ADR_VIN_AC_BASE + u16AddrOffset;
          u8CaliValid = 1;
        }
        break;
      }

      case CALI_IIN_AC:
      {
        if (u8CaliLine < CALI_IIN_AC_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_RTE_W_sData.sIinAc[u8CaliLine],  &CALI_sPara.sUser);
          CALI_sPara.u16SaveAddr = EEPROM_ADR_IIN_AC_BASE + u16AddrOffset;
          u8CaliValid = 1;
        }
        break;
      }

      case CALI_PIN_AC:
      {
        if (u8CaliLine < CALI_PIN_AC_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_RTE_W_sData.sPinAc[u8CaliLine],  &CALI_sPara.sUser);
          CALI_sPara.u16SaveAddr = EEPROM_ADR_PIN_AC_BASE + u16AddrOffset;
          u8CaliValid = 1;
        }
        break;
      }
      case CALI_V_V1:
      {
        if (u8CaliLine < CALI_V_V1_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_RTE_W_sData.sVoutV1[u8CaliLine],  &CALI_sPara.sUser);
          CALI_sPara.u16SaveAddr = EEPROM_ADR_V_V1_BASE + u16AddrOffset;
          u8CaliValid = 1;
        }
        break;
      }

      case CALI_I_V1:
      {
        if (u8CaliLine < CALI_I_V1_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_RTE_W_sData.sIoutV1[u8CaliLine],  &CALI_sPara.sUser);
          CALI_sPara.u16SaveAddr = EEPROM_ADR_I_V1_BASE + u16AddrOffset;
          
          if(u8CaliLine == (CALI_I_V1_LINE_NUM - 1u))
          {
            mg_vCalcV1CurrentGain();
          }
          u8CaliValid = 1;
        }
        break;
      }

      case CALI_V_VSB:
      {
        if (u8CaliLine < CALI_V_VSB_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_RTE_W_sData.sVoutVsb[u8CaliLine],  &CALI_sPara.sUser);
          CALI_sPara.u16SaveAddr = EEPROM_ADR_V_VSB_BASE + u16AddrOffset;
          u8CaliValid = 1;
        }
        break;
      }

      case CALI_I_VSB:
      {
        if (u8CaliLine < CALI_I_VSB_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_RTE_W_sData.sIoutVsb[u8CaliLine],  &CALI_sPara.sUser);
          CALI_sPara.u16SaveAddr = EEPROM_ADR_I_VSB_BASE + u16AddrOffset;
          u8CaliValid = 1;
        }
        break;
      }
			
      case CALI_V1_ISHARE:
      {
        if (u8CaliLine < CALI_V1_ISHARE_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_RTE_W_sData.sV1IShare[u8CaliLine],  &CALI_sPara.sUser);
          CALI_sPara.u16SaveAddr = EEPROM_ADR_V1_ISHARE_BASE + u16AddrOffset;
          u8CaliValid = 1;
        }
        break;
      }

      default:
      {
        break;
      }
    }

    if (u8CaliValid)
    {
      CALI_uStatus.Bits.CALI_SAVE_NEED = TRUE;
    }
  }
} /* CALI_vCalibrate() */

/********************************************************************************
 * \brief         Read calibration data from EEPROM and check CRC value
 *
 * \param[in]     uint16 u16StartAddr, uint8 u8LineMax, CALI_S_COMMON *psThis
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vReadEepData(uint16 u16StartAddr, uint8 u8LineMax, CALI_S_COMMON *psThis)
{
  uint8 u8CaliLine = 0;
  uint8 u8Crc = 0;
  uint8 u8Cnt = 0;
  CALI_S_COMMON *psTarget;

  for (u8CaliLine = 0; u8CaliLine < u8LineMax ; u8CaliLine ++)
  {
    CALI_SCFG_vReadMem(mg_u8DataBuf,(u16StartAddr  + ((uint16)u8CaliLine * 8u)),MG_SEVEN_BYTES);

    u8Crc = CRC_INIT_02;
    for (u8Cnt = 0; u8Cnt < 7; u8Cnt ++)
    {
      u8Crc = CALI_SCFG_u8GetCrc8( u8Crc, mg_u8DataBuf[u8Cnt] );
    }
    if (0U == u8Crc)
    {
      psTarget = psThis + u8CaliLine;
      psTarget->s16Amp = (sint16)(GET_WORD(mg_u8DataBuf[1], mg_u8DataBuf[0]));
      psTarget->s16Ofs = (sint16)(GET_WORD(mg_u8DataBuf[3], mg_u8DataBuf[2]));
      psTarget->s16Thr = (sint16)(GET_WORD(mg_u8DataBuf[5], mg_u8DataBuf[4]));
    }
    else
    {
      /* do nothing */
    }
    
  }
} /* mg_vReadEepData */

/********************************************************************************
 * \brief         Save calibration data to EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vSaveCaliData(void)
{
  uint8 u8Crc = 0;
  CALI_S_TEMP sEepromTemp;

  if ((CALI_sPara.u16SaveAddr >= CALI_EEP_DATA_STR)
    && (CALI_sPara.u16SaveAddr <= CALI_EEP_DATA_END)
    && (TRUE == CALI_uStatus.Bits.CALI_NEW_DATA))
  {
    sEepromTemp.s16Amp = CALI_sPara.sUser.s16Amp;
    sEepromTemp.s16Ofs = CALI_sPara.sUser.s16Ofs;
    sEepromTemp.s16Thr = CALI_sPara.sUser.s16Thr;

    u8Crc = CRC_INIT_02;
    u8Crc = CALI_SCFG_u8GetCrc8( u8Crc,LOBYTE(sEepromTemp.s16Amp));
    u8Crc = CALI_SCFG_u8GetCrc8( u8Crc,HIBYTE(sEepromTemp.s16Amp));
    u8Crc = CALI_SCFG_u8GetCrc8( u8Crc,LOBYTE(sEepromTemp.s16Ofs));
    u8Crc = CALI_SCFG_u8GetCrc8( u8Crc,HIBYTE(sEepromTemp.s16Ofs));
    u8Crc = CALI_SCFG_u8GetCrc8( u8Crc,LOBYTE(sEepromTemp.s16Thr));
    u8Crc = CALI_SCFG_u8GetCrc8( u8Crc,HIBYTE(sEepromTemp.s16Thr));
    sEepromTemp.u8Crc8 = u8Crc;
		
		if(CALI_SCFG_u8IsEepromStandbyState() == TRUE)
		{
			CALI_SCFG_vWriteMem(CALI_sPara.u16SaveAddr, (uint8*)&sEepromTemp.s16Amp, MG_SEVEN_BYTES);
			CALI_uStatus.Bits.CALI_NEW_DATA = FALSE;
		}
  }
} /* mg_vSaveCaliData */

/********************************************************************************
 * \brief         copy calibration data to buffer
 *
 * \param[in]     *psThis,  *psCopy
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        - sint32 s32Dummy
 *
 *******************************************************************************/
static void mg_vCopyDataToBuf(CALI_S_COMMON *psThis, CALI_S_COMMON *psCopy)
{
  psThis->s16Amp = psCopy->s16Amp;
  psThis->s16Ofs = psCopy->s16Ofs;
  psThis->s16Thr = psCopy->s16Thr;
} /* mg_vCopyDataToBuf */

/********************************************************************************
 * \brief         calcualte calibrated data
 *
 * \param[in]     - uint16 u16AdcAvg,uint8 u8MaxLine, sint16 *ps16CaliAmp, sint16 *ps16CaliOffset, sint16 *ps16CaliThr
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        - sint32 s32Dummy
 *
 *******************************************************************************/
static sint32 mg_s32GetCalibratedData(uint16 u16AdcAvg, uint8 u8MaxLine, CALI_S_COMMON *pCal)
{
  uint8  u8Cnt     = 0;
  uint32 u32Result = 0;
  uint16 u16Dummy = u16AdcAvg;
  sint32 s32Dummy = 0 ;

  if (u16Dummy > 0)
  {
    for (u8Cnt = 0; u8Cnt < u8MaxLine; u8Cnt++)
    {
      if (u16Dummy < pCal[u8Cnt].s16Thr)
      {
        s32Dummy = ((sint32)(pCal[u8Cnt].s16Amp))* ((sint32)u16Dummy);
        s32Dummy = (sint32)(s32Dummy + 4096u) >> 13;
        s32Dummy += pCal[u8Cnt].s16Ofs;
        break;
      }
    }
  }
  if (s32Dummy < 0)
  {
    s32Dummy = 0;
  }
  u32Result = (uint32)s32Dummy;
  return (u32Result);
} /* mg_s32GetCalibratedData */

/*******************************************************************************
 * \brief         Set default calibration data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vSetDefaultCaliData(void)
{
  mg_vCaliDefaultVinAc();
  mg_vCaliDefaultIinAc();
  mg_vCaliDefaultPinAc();
	
  mg_vCaliDefaultVoutV1();
  mg_vCaliDefaultIoutV1();
  mg_vCaliDefaultVoutVsb();
  mg_vCaliDefaultIoutVsb();
  mg_vCaliDefaultV1IShare();

  CALI_uStatus.ALL = 0;
} /* mg_vSetDefaultCaliData */

/********************************************************************************
 * \brief         set default value for Vin 1
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCaliDefaultVinAc(void)
{
  uint8 u8CaliLine = 0;

  for (u8CaliLine = 0; u8CaliLine < CALI_VIN_AC_LINE_NUM; u8CaliLine ++)
  {
    CALI_RTE_W_sData.sVinAc[u8CaliLine].s16Amp = MG_VIN_AC_AMP_DEFAULT;
    CALI_RTE_W_sData.sVinAc[u8CaliLine].s16Ofs = MG_VIN_AC_OFS_DEFAULT;
    CALI_RTE_W_sData.sVinAc[u8CaliLine].s16Thr = MG_SENSOR_THR_DEFAULT;
  }
} /* mg_vCaliDefaultVinAc() */

/********************************************************************************
 * \brief         set default value for Iin 1
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCaliDefaultIinAc(void)
{
  uint8 u8CaliLine = 0;

  for (u8CaliLine = 0; u8CaliLine < CALI_IIN_AC_LINE_NUM; u8CaliLine ++)
  {
    CALI_RTE_W_sData.sIinAc[u8CaliLine].s16Amp = MG_IIN_AC_AMP_DEFAULT;
    CALI_RTE_W_sData.sIinAc[u8CaliLine].s16Ofs = MG_IIN_AC_OFS_DEFAULT;
    CALI_RTE_W_sData.sIinAc[u8CaliLine].s16Thr = MG_SENSOR_THR_DEFAULT;
  }
} /* mg_vCaliDefaultIinAc() */

/********************************************************************************
 * \brief         set default value for Pin 1
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCaliDefaultPinAc(void)
{
  uint8 u8CaliLine = 0;

  for (u8CaliLine = 0; u8CaliLine < CALI_PIN_AC_LINE_NUM; u8CaliLine ++)
  {
    CALI_RTE_W_sData.sPinAc[u8CaliLine].s16Amp = MG_PIN_AC_AMP_DEFAULT;
    CALI_RTE_W_sData.sPinAc[u8CaliLine].s16Ofs = MG_PIN_AC_OFS_DEFAULT;
    CALI_RTE_W_sData.sPinAc[u8CaliLine].s16Thr = MG_SENSOR_THR_DEFAULT;
  }
} /* mg_vCaliDefaultPinAc() */

/********************************************************************************
 * \brief         set default value for Vout V1
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCaliDefaultVoutV1(void)
{
  uint8 u8CaliLine = 0;

  for (u8CaliLine = 0; u8CaliLine < CALI_V_V1_LINE_NUM; u8CaliLine ++)
  {
    CALI_RTE_W_sData.sVoutV1[u8CaliLine].s16Amp = MG_V_V1_AMP_DEFAULT;
    CALI_RTE_W_sData.sVoutV1[u8CaliLine].s16Ofs = MG_V_V1_OFS_DEFAULT;
    CALI_RTE_W_sData.sVoutV1[u8CaliLine].s16Thr = MG_SENSOR_THR_DEFAULT;
  }
} /* mg_vCaliDefaultVoutV1() */

/********************************************************************************
 * \brief         set default value for Iout 54V 1
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCaliDefaultIoutV1( void )
{
  uint8 u8CaliLine = 0;

  for (u8CaliLine = 0; u8CaliLine < CALI_I_V1_LINE_NUM; u8CaliLine ++)
  {
    CALI_RTE_W_sData.sIoutV1[u8CaliLine].s16Amp = MG_I_V1_AMP_DEFAULT;
    CALI_RTE_W_sData.sIoutV1[u8CaliLine].s16Ofs = MG_I_V1_OFS_DEFAULT;
    CALI_RTE_W_sData.sIoutV1[u8CaliLine].s16Thr = MG_SENSOR_THR_DEFAULT;
  }
} /* mg_vCaliDefaultIoutV1() */

/********************************************************************************
 * \brief         set default value for Vout VSB
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCaliDefaultVoutVsb( void )
{
  uint8 u8CaliLine = 0;

  for (u8CaliLine = 0; u8CaliLine < CALI_V_VSB_LINE_NUM; u8CaliLine ++)
  {
    CALI_RTE_W_sData.sVoutVsb[u8CaliLine].s16Amp = MG_V_VSB_AMP_DEFAULT;
    CALI_RTE_W_sData.sVoutVsb[u8CaliLine].s16Ofs = MG_V_VSB_OFS_DEFAULT;
    CALI_RTE_W_sData.sVoutVsb[u8CaliLine].s16Thr = MG_SENSOR_THR_DEFAULT;
  }
} /* mg_vCaliDefaultVoutVsb() */

/********************************************************************************
 * \brief         set default value for Iout VSB
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCaliDefaultIoutVsb( void )
{
  uint8 u8CaliLine = 0;

  for (u8CaliLine = 0; u8CaliLine < CALI_I_VSB_LINE_NUM; u8CaliLine ++)
  {
    CALI_RTE_W_sData.sIoutVsb[u8CaliLine].s16Amp = MG_I_VSB_AMP_DEFAULT;
    CALI_RTE_W_sData.sIoutVsb[u8CaliLine].s16Ofs = MG_I_VSB_OFS_DEFAULT;
    CALI_RTE_W_sData.sIoutVsb[u8CaliLine].s16Thr = MG_SENSOR_THR_DEFAULT;
  }
} /* mg_vCaliDefaultIoutVsb() */

/********************************************************************************
 * \brief         set default value for Iout VSB
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCaliDefaultV1IShare( void )
{
  uint8 u8CaliLine = 0;

  for (u8CaliLine = 0; u8CaliLine < CALI_V1_ISHARE_LINE_NUM; u8CaliLine ++)
  {
    CALI_RTE_W_sData.sV1IShare[u8CaliLine].s16Amp = MG_V1_ISHARE_AMP_DEFAULT;
    CALI_RTE_W_sData.sV1IShare[u8CaliLine].s16Ofs = MG_V1_ISHARE_OFS_DEFAULT;
    CALI_RTE_W_sData.sV1IShare[u8CaliLine].s16Thr = MG_SENSOR_THR_DEFAULT;
  }
} /* mg_vCaliDefaultIoutVsb() */

/********************************************************************************
 * \brief         Calculate the V1 current gain for secondary
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vCalcV1CurrentGain(void)
{
  uint16 u16V1CurrentGain;
  
  u16V1CurrentGain = (uint16)((((sint32)(CALI_RTE_W_sData.sIoutV1[CALI_I_V1_LINE_NUM - 1u].s16Amp)) * 4095)/MG_I_V1_AMP_DEFAULT + 
                              + (sint32)(CALI_RTE_W_sData.sIoutV1[CALI_I_V1_LINE_NUM - 1u].s16Ofs)/(7000* 128));

  CALI_Rte_Write_P_u16V1CurrentGain(u16V1CurrentGain);
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/
static void mg_vReadCalibPara(uint8 u8Mode, uint8 u8Line)
{
  uint8  u8CaliLine = 0;
  
   if (u8Line > 0)
    {
      u8CaliLine = u8Line - 1;
    }
    switch (u8Mode)
    {
      case CALI_VIN_AC:
      {
        if (u8CaliLine < CALI_VIN_AC_LINE_NUM)
        {
          mg_vCopyDataToBuf(&CALI_sPara.sUser, &CALI_RTE_W_sData.sVinAc[u8CaliLine]);
        }
        break;
      }

      case CALI_IIN_AC:
      {
        if (u8CaliLine < CALI_IIN_AC_LINE_NUM)
        {
          mg_vCopyDataToBuf(&CALI_sPara.sUser, &CALI_RTE_W_sData.sIinAc[u8CaliLine]);
        }
        break;
      }

      case CALI_PIN_AC:
      {
        if (u8CaliLine < CALI_PIN_AC_LINE_NUM)
        {
          mg_vCopyDataToBuf(&CALI_sPara.sUser, &CALI_RTE_W_sData.sPinAc[u8CaliLine]);
        }
        break;
      }
      case CALI_V_V1:
      {
        if (u8CaliLine < CALI_V_V1_LINE_NUM)
        {
          mg_vCopyDataToBuf(&CALI_sPara.sUser, &CALI_RTE_W_sData.sVoutV1[u8CaliLine]);
        }
        break;
      }

      case CALI_I_V1:
      {
        if (u8CaliLine < CALI_I_V1_LINE_NUM)
        {
          mg_vCopyDataToBuf(&CALI_sPara.sUser, &CALI_RTE_W_sData.sIoutV1[u8CaliLine] );
        }
        break;
      }

      case CALI_V_VSB:
      {
        if (u8CaliLine < CALI_V_VSB_LINE_NUM)
        {
          mg_vCopyDataToBuf(&CALI_sPara.sUser, &CALI_RTE_W_sData.sVoutVsb[u8CaliLine]);
        }
        break;
      }

      case CALI_I_VSB:
      {
        if (u8CaliLine < CALI_I_VSB_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_sPara.sUser,&CALI_RTE_W_sData.sIoutVsb[u8CaliLine] );
        }
        break;
      }
			
      case CALI_V1_ISHARE:
      {
        if (u8CaliLine < CALI_V1_ISHARE_LINE_NUM)
        {
          mg_vCopyDataToBuf( &CALI_sPara.sUser,&CALI_RTE_W_sData.sV1IShare[u8CaliLine]);
        }
        break;
      }

      default:
      {
        break;
      }
   }
}
/*
 * End of file
 */
