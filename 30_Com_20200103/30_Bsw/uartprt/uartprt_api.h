/** *****************************************************************************
 * \file    uartprt_api.h
 * \brief   Service function request file for uartprt.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-09-10 08:40:13 +0800 (Mon, 10 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 24 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef UARTPRT_API_H
#define UARTPRT_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/** *****************************************************************************
 * \brief         Set boot mode 
 *
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void UARTPRT_vSetBootMode(uint8 u8Index);

#ifdef __cplusplus
  }
#endif
#endif  /* UARTPRT_API_H */

  
/*
 * End of file
 */
