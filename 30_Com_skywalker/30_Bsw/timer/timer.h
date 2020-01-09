/*******************************************************************************
 * \file    timer.h
 * \brief   Global interface for timer.c
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef TIMER_H
#define TIMER_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize Timer for input capture and timer base
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void TIMER_vTimerHwInit(void);
    
/*******************************************************************************
 * \brief         Initialize the complete system. CPU timers and aux timer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void TIMER_vHrTimerHwInit(void);

#ifdef __cplusplus
  }
#endif
#endif  /* TIMER_H */

  
/*
 * End of file
 */
