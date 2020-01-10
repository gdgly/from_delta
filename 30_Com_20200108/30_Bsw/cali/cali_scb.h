/** *****************************************************************************
 * \file    cali_scb.h
 * \brief   Service function call back file for cali.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-10-14 17:07:42 +0800 (Mon, 14 Oct 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 234 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef CALI_SCB_H
#define CALI_SCB_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
/*******************************************************************************
 * \brief         Initialize 
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vInit(void);

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
void CALI_vDeInit(void);

/********************************************************************************
 * \brief         Handle calibration and save data into EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCaliHandler(void);

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
void CALI_vCalibrateIShare(void);

/********************************************************************************
 * \brief         Fast Calibrate Vsb current and voltage for monitoring
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCaliFast(void);

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
void CALI_vCalcCaliPara(void);

#ifdef __cplusplus
  }
#endif
#endif  /* CALI_SCB_H */

  
/*
 * End of file
 */
