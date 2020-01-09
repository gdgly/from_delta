/** *****************************************************************************
 * \file    rtc_api.h
 * \brief   Service function request file for rtc.c
 *
 * \section AUTHOR
 *    1. Jeff.Zhou
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

#ifndef RTC_API_H
#define RTC_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

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
void RTC_vDeInit(void);

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
void RTC_vInit(void);
#ifdef __cplusplus
  }
#endif
#endif  /* RTC_API_H */

  
/*
 * End of file
 */
