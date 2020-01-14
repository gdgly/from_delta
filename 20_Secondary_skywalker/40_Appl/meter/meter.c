/** *****************************************************************************
 * \file    meter.c
 * \brief   Input voltage/current/power calculation
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
#define METER_EXPORT_H
  #include "meter_api.h"
  #include "meter_scb.h"
  #include "meter_cfg.h"
  #include "meter_scfg.h"
  #include "meter_rte.h"
  #include "meter_conf.h"

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

typedef struct
{
  uint32 u32100mWPwrOutSum;
  uint16 u16100mWPwrOutAvg;

  uint32 u3210mVVoltOutExtSum;
  uint16 u1610mVVoltOutExtAvg;
  uint16 u1610mVVoltOutExt;
  
  uint32 u3210mVVoltOutIntSum;
  uint16 u1610mVVoltOutIntAvg;
  uint16 u1610mVVoltOutInt;

  uint32 u3210mACurrOutSum;
  uint16 u1610mACurrOutAvg;
  uint16 u1610mACurrOut;

  uint16 u16Ctr;
} MG_S_METER;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static MG_S_METER       METER_mg_sMeter;

static uint16 METER_mg_u16q12CalibVoltOutGain;
static uint16 METER_mg_u16q12CalibCurrOutGain;

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
void METER_vInit(void)
{
  METER_mg_sMeter.u16Ctr = 0U;
  /* Get inital calibration data */
  METER_Read_R_q12_CalibVoltOutGain_rte(&METER_mg_u16q12CalibVoltOutGain);
  METER_Read_R_q12_CalibCurrOutGain_rte(&METER_mg_u16q12CalibCurrOutGain);
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
void METER_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         Output current and voltage averaging
 *                Repetition time: 200uS
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void METER_vMeterAvg(void)
{
  /* Get RTE data */
  METER_Read_R_10mV_VoltOutExt_rte(&METER_mg_sMeter.u1610mVVoltOutExt);
  METER_Read_R_10mV_VoltOutInt_rte(&METER_mg_sMeter.u1610mVVoltOutInt);
  METER_Read_R_10mA_CurrOut_rte(&METER_mg_sMeter.u1610mACurrOut);

  /*******************************************************************************
   * Integrate and process measurements
   *******************************************************************************/
  METER_mg_sMeter.u32100mWPwrOutSum += (((uint32)METER_mg_sMeter.u1610mVVoltOutInt * METER_mg_sMeter.u1610mACurrOut) >> 10);
  METER_mg_sMeter.u3210mVVoltOutExtSum += METER_mg_sMeter.u1610mVVoltOutExt;
  METER_mg_sMeter.u3210mVVoltOutIntSum += METER_mg_sMeter.u1610mVVoltOutInt;
  METER_mg_sMeter.u3210mACurrOutSum += METER_mg_sMeter.u1610mACurrOut;
  METER_mg_sMeter.u16Ctr++;

  /* If average counter reached averaging value */
  if (MG_U8_AVG_CTR <= METER_mg_sMeter.u16Ctr)
  {
    /* Get calibration data from RTE */
    METER_Read_R_q12_CalibVoltOutGain_rte(&METER_mg_u16q12CalibVoltOutGain);
    METER_Read_R_q12_CalibCurrOutGain_rte(&METER_mg_u16q12CalibCurrOutGain);

    /* Output power average; Limit max power to 6553 Watt to avoid overflow; Divide by 1000 to achieve 100mW per digit */
    METER_mg_sMeter.u16100mWPwrOutAvg = SAT_H((((METER_mg_sMeter.u32100mWPwrOutSum / METER_mg_sMeter.u16Ctr) * MG_U16_Q12_POWER_SCALE) >> 12), 65535);
    METER_mg_sMeter.u32100mWPwrOutSum = 0U;
    METER_Write_P_100mW_PwrOutAvgCom_rte(METER_mg_sMeter.u16100mWPwrOutAvg);
    METER_Write_P_100mW_PwrOutAvg_rte(((((uint32)METER_mg_sMeter.u16100mWPwrOutAvg * METER_mg_u16q12CalibVoltOutGain) >> 12) * METER_mg_u16q12CalibCurrOutGain) >> 12);
    /* External output voltage average */
    METER_mg_sMeter.u1610mVVoltOutExtAvg = (METER_mg_sMeter.u3210mVVoltOutExtSum / METER_mg_sMeter.u16Ctr);
    METER_mg_sMeter.u3210mVVoltOutExtSum = 0U;
    METER_Write_P_10mV_VoltOutExtAvgCom_rte(METER_mg_sMeter.u1610mVVoltOutExtAvg);
    METER_Write_P_10mV_VoltOutExtAvg_rte(((uint32)METER_mg_sMeter.u1610mVVoltOutExtAvg * METER_mg_u16q12CalibVoltOutGain) >> 12);
    /* Internal output voltage average */
    METER_mg_sMeter.u1610mVVoltOutIntAvg = (METER_mg_sMeter.u3210mVVoltOutIntSum / METER_mg_sMeter.u16Ctr);
    METER_mg_sMeter.u3210mVVoltOutIntSum = 0U;
    METER_Write_P_10mV_VoltOutIntAvgCom_rte(METER_mg_sMeter.u1610mVVoltOutIntAvg);
    METER_Write_P_10mV_VoltOutIntAvg_rte(((uint32)METER_mg_sMeter.u1610mVVoltOutIntAvg * METER_mg_u16q12CalibVoltOutGain) >> 12);
    /* Output current average */
    METER_mg_sMeter.u1610mACurrOutAvg = (METER_mg_sMeter.u3210mACurrOutSum / METER_mg_sMeter.u16Ctr);
    METER_mg_sMeter.u3210mACurrOutSum = 0U;
    METER_Write_P_10mA_CurrOutAvgCom_rte(METER_mg_sMeter.u1610mACurrOutAvg);
    METER_Write_P_10mA_CurrOutAvg_rte(((uint32)METER_mg_sMeter.u1610mACurrOutAvg * METER_mg_u16q12CalibCurrOutGain) >> 12);

    /* Reset measurement counter */
    METER_mg_sMeter.u16Ctr = 0U;
  }
}


/*
 * End of file
 */
