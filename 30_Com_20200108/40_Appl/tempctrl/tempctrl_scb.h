/** *****************************************************************************
 * \file    tempctrl_scb.h
 * \brief   Service function call back file for tempctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-09-20 11:15:53 +0800 (Thu, 20 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 41 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef TEMPCTRL_SCB_H
#define TEMPCTRL_SCB_H
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
/********************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void TEMPCTRL_vDeInit(void);

/********************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void TEMPCTRL_vInit(void);

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
void TEMPCTRL_vNtcVoltAverage(void);

/*******************************************************************************
 * Function:        LookUpNtcTemperature
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Look up temperature value from table
 *
 ******************************************************************************/ 
void TEMPCTRL_vLookUpNtcTemperature(void);

/*******************************************************************************
 * \brief         NTC OTP monitor
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TEMPCTRL_vNtcTempMonitor(void);

#ifdef __cplusplus
  }
#endif
#endif  /* TEMPCTRL_SCB_H */

  
/*
 * End of file
 */
