/** *****************************************************************************
 * \file    tmctrl_scb.h
 * \brief   Service function call back file for tmctrl.c
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

#ifndef TMCTRL_SCB_H
#define TMCTRL_SCB_H
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
void TMCTRL_vInit(void);

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
void TMCTRL_vDeInit(void);

/** *****************************************************************************
 * \brief         Booster control on/off timing (200us repetition)
 *                INIT: Turn off booster, Turn off D2D, Turn off Relay, Wait for delay passed
 *                INRUSH: Check relay enable conditions and turn on relay, Wait until Vin okay
 *                BOOST_ON: Turn on booster and control D2D
 *                BOOST_OFF: Wait for D2D turn off and turn off booster
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TMCTRL_vLlcCtrl(void);

/** *****************************************************************************
 * \brief         Upgrade flag and MCU reset
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TMCTRL_vWriteUpgradeFlgAndReset(void);


#ifdef __cplusplus
  }
#endif
#endif  /* TMCTRL_SCB_H */

  
/*
 * End of file
 */
