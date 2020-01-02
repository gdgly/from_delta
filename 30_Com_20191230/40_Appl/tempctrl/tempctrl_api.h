/** *****************************************************************************
 * \file    tempctrl_api.h
 * \brief   Service function request file for tempctrl.c
 *
 * \section AUTHOR
 *    1. Jeff.Zhou
 *
 * \section SVN
 *  $Date: 2019-03-01 14:35:06 +0800 (Fri, 01 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 145 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef TEMPCTRL_API_H
#define TEMPCTRL_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

sint16 TEMPCTRL_s16ReadTempValue(uint8 u8Index);
uint16 TEMPCTRL_u16ReadAdcAvgValue(uint8 u8Index);
/*******************************************************************************
 * \brief         Set OT Warning Limit value
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TEMPCTRL_vSetOtWarnValue(uint8 u8Index, sint16 s16Data);

#ifdef __cplusplus
  }
#endif
#endif  /* TEMPCTRL_API_H */

  
/*
 * End of file
 */
