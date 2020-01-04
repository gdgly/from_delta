/** *****************************************************************************
 * \file    psuctrl_api.h
 * \brief   Service function request file for psuctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-23 15:34:14 +0800 (Thu, 23 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 14 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PSUCTRL_API_H
#define PSUCTRL_API_H
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
void PSCTRL_vSetV1RstTim(uint16 u16Value);


#ifdef __cplusplus
  }
#endif
#endif  /* PSUCTRL_API_H */

  
/*
 * End of file
 */
