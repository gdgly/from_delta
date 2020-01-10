/** *****************************************************************************
 * \file    cali_api.h
 * \brief   Service function request file for cali.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-11-02 18:17:25 +0800 (Fri, 02 Nov 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 100 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef CALI_API_H
#define CALI_API_H
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

/********************************************************************************
 * \brief         Calibrate the Iout for OCP
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCalibrateIout(void);

/********************************************************************************
 * \brief         Calibrate the voltage and current of V1.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void CALI_vCalibrateV1(void);


#ifdef __cplusplus
  }
#endif
#endif  /* CALI_API_H */

  
/*
 * End of file
 */
