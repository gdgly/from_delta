/** *****************************************************************************
 * \file    eeprom_scb.h
 * \brief   Service function call back file for eeprom.c
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

#ifndef EEPROM_SCB_H
#define EEPROM_SCB_H
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
 * \brief         DeInitializes peripherals used by the I2C EEPROM driver.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void EEPROM_vDeInit(void);

/** *****************************************************************************
 * \brief         Initializes peripherals used by the I2C EEPROM driver.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void EEPROM_vInit(void);

#ifdef __cplusplus
  }
#endif
#endif  /* EEPROM_SCB_H */

  
/*
 * End of file
 */
