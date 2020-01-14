/** *****************************************************************************
 * \file    rte.c
 * \brief   Run time environment
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *    2. Fred Ji
 *    3. Harry Huang
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
#define RTE_EXPORT_H
  #include "rte.h"

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
void RTE_vInit(void)
{
  RTE_uLlcStatus00.ALL = 0U;
  RTE_uLlcStatus01.ALL = 0U;
  RTE_uLlcStatus02.ALL = 0U;
  RTE_uTempStatus00.ALL = 0U;
  RTE_uComStatus00.ALL = 0U;
  RTE_uLlcPort00.ALL = 0U;
  RTE_uLlcHrTimer00.ALL = 0U;
  RTE_B_LLC_COM_HALT = FALSE;

  RTE_u1610mVVoltOutExt = 0U;
  RTE_u1610mVVoltOutInt = 0U;
  RTE_u1610mACurrOut = 0U;
  RTE_u1610mACurrOutCali = 0U;

  RTE_u1610mVVoltOutExtAvg = 0U;
  RTE_u1610mVVoltOutIntAvg = 0U;
  RTE_u1610mACurrOutAvg = 0U;
  RTE_u16100mWPwrOutAvg = 0U;
  RTE_u1610mVVoltOutExtAvgCom = 0U;
  RTE_u1610mVVoltOutIntAvgCom = 0U;
  RTE_u1610mACurrOutAvgCom = 0U;
  RTE_u16100mWPwrOutAvgCom = 0U;

  RTE_u161OhmResNtc1Avg = 890U;
  RTE_u161OhmResNtc2Avg = 890U;
  RTE_u161OhmResNtc3Avg = 890U;
  RTE_u161OhmResNtc4Avg = 890U;
  RTE_u16q12VoltRefCaliFact = 4095;
  RTE_u16100mHzVoltInFreq = 500U;
  RTE_s1610mVMainVoltAdjCurrShare = 0U;

  /* Calibration default values */
  RTE_u16q12CalibVoltOutGain = 4095U;
  RTE_u16q12CalibCurrOutGain = 4095U;
  RTE_u16q12CalibIshareGain = 4095U;
  RTE_s1610mACalibIshareOfs = 0;
  RTE_s16CalibVoltOutAmp = 10485;
  RTE_s16CalibCurrOutAmp = 10485;
  RTE_s16CalibVoltOutOfs = 0;
  RTE_s16CalibCurrOutOfs = 0;
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
void RTE_vDeInit(void)
{
  RTE_uLlcHrTimer00.ALL = 0U;
  RTE_uLlcPort00.ALL = 0U;
  RTE_uLlcStatus00.ALL = 0U;
  RTE_uLlcStatus01.ALL = 0U;
  RTE_uLlcStatus02.ALL = 0U;
}


/*
 * End of file
 */
