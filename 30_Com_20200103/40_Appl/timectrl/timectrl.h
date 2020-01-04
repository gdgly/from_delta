/*******************************************************************************
 * \file    timectrl.h
 * \brief   
 *
 * \section AUTHOR
 *    1. Gary.Weng
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

#ifndef TIMECTRL_H
#define TIMECTRL_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes
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
extern void TIMECTRL_vInit(void);

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
extern void TIMECTRL_vSaveHoursUsed( void );

#ifdef __cplusplus
  }
#endif
#endif /* ledctrl */


/*
 * End of file
 */

