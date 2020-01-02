/** *****************************************************************************
 * \file    wdg_api.h
 * \brief   Service function request file for wdg.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef WDG_API_H
#define WDG_API_H
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
void WDG_vInit(void);

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
void WDG_vDeInit(void);
    
/** *****************************************************************************
 * \brief         Feed the watch dog (reset watch dog counter)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void WDG_vWatchDogFeed(void);

/** *****************************************************************************
 * \brief         Enable the Independent Watchdog Timer
 *                The IWDG uses its own clock and is independet from the main clock
 *                --> lower timing accuqracy, but higher safety level
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void WDG_vWatchDogEn(void);

/** *****************************************************************************
 * \brief         Set watch dog time out delay
 *
 * \param[in]     msTimeOutDly: Time out delay in ms
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void WDG_vWdgSetTimeOutDly(uint16 u16msTimeOutDly);

/** *****************************************************************************
 * \brief         System/MCU reset
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void WDG_vSysReset(void);


#ifdef __cplusplus
  }
#endif
#endif  /* WDG_API_H */

  
/*
 * End of file
 */
