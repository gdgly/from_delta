/** *****************************************************************************
 * \file    timectrl_scb.h
 * \brief   Service function call back file for timectrl.c
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

#ifndef TIMECATL_SCB_H
#define TIMECATL_SCB_H
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
 * \brief         Read operating minutes and calculate Hours used
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMECTRL_vInit(void);

/*******************************************************************************
 * \brief         Read operating minutes and calculate Hours used
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMECTRL_vDeInit(void);

/*******************************************************************************
 * \brief         Calculate Hours Used and save operating minutes 
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMECTRL_vSaveHoursUsed( void );

#ifdef __cplusplus
  }
#endif
#endif  /* TIMECATL_SCB_H */

  
/*
 * End of file
 */
