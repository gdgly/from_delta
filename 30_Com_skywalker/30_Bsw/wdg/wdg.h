/*******************************************************************************
 * \file    wdg.h
 * \brief   Global interface for wdg.c
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
 ******************************************************************************/

#ifndef WDG_H
#define WDG_H
#ifdef __cplusplus
  extern "C"  {
#endif
   
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Feed the watch dog (reset watch dog counter)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void WDG_vWatchDogFeed(void);

/*******************************************************************************
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
 ******************************************************************************/
extern void WDG_vWatchDogEn(void);

/*******************************************************************************
 * \brief         System/MCU reset
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void WDG_vSysReset(void);


#ifdef __cplusplus
  }
#endif
#endif  /* WDG_H */

  
/*
 * End of file
 */
