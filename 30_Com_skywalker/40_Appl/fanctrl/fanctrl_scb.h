/** *****************************************************************************
 * \file    fanctrl_scb.h
 * \brief   Service function call back file for fanctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-10 18:40:44 +0800 (Fri, 10 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 12 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef FANCTRL_SCB_H
#define FANCTRL_SCB_H
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
 * \brief         Fan Data init
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vInit(void);
		
/*******************************************************************************
 * \brief         Fan Data De-init
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vDeInit(void);

/** *****************************************************************************
 * \brief         Fan Speed control
 *                Speed = FAN_SPEED_MIN + LOAD_SPEED + TEMP_SPEED + VIN_SPEED
 *                regulate the fan speed by change the the PWM duty
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vFanCtrl(void);

/** *****************************************************************************
 * \brief         Fan Speed calculate, every 100ms
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vFanSpeedCalc(void);

/** *****************************************************************************
 * \brief         Fan Speed counter
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vFanSpeedCnt(void);

#ifdef __cplusplus
  }
#endif
#endif  /* FANCTRL_SCB_H */

  
/*
 * End of file
 */
