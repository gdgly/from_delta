/** *****************************************************************************
 * \file    timer_api.h
 * \brief   Service function request file for timer.c
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

#ifndef TIMER_API_H
#define TIMER_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "timer_cfg.h"

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
void TIMER_vInit(void);

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
void TIMER_vDeInit(void);

/*******************************************************************************
 * \brief         Clears the TIMx's update interrupt pending bits.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMER_vClearUpdateFlg(TIMER_CFG_E_INDEX eTimerIndex);

/*******************************************************************************
 * \brief         Checks whether the TIM update interrupt has occurred or not.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
uint8 TIMER_u8GetUpdateFlg(TIMER_CFG_E_INDEX eTimerIndex);




#ifdef __cplusplus
  }
#endif
#endif  /* TIMER_API_H */

  
/*
 * End of file
 */
