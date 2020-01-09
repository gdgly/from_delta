/** *****************************************************************************
 * \file    i2cprt_api.h
 * \brief   Service function request file for i2cprt.c
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

#ifndef I2CPRT_API_H
#define I2CPRT_API_H
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
void I2CPRT_vSetI2cState(uint8 u8State);

#ifdef __cplusplus
  }
#endif
#endif  /* EEPROM_API_H */

  
/*
 * End of file
 */
