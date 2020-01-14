/** *****************************************************************************
 * \file    clock_api.h
 * \brief   Service function request file for clock.c
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

#ifndef CLOCK_API_H
#define CLOCK_API_H
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
void CLOCK_vInit(void);

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
void CLOCK_vDeInit(void);

/** *****************************************************************************
 * \brief         Initialize the System and the MCU Clock
 *                Called by startup_xxx.s
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void SystemInit(void);

/** *****************************************************************************
 * \brief         Update SystemCoreClock variable according to Clock Register Values
 *                The SystemCoreClock variable contains the core clock (HCLK)
 *                Each time the core clock (HCLK) changes, this function must be called
 *                to update SystemCoreClock variable value
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void CLOCK_vSysCoreClkUpdate(void);


#ifdef __cplusplus
  }
#endif
#endif  /* CLOCK_API_H */

  
/*
 * End of file
 */
