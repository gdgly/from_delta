/** *****************************************************************************
 * \file    port_api.h
 * \brief   Service function request file for port.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-09-28 17:18:22 +0800 (Fri, 28 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 47 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PORT_API_H
#define PORT_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "port_cfg.h"

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
void PORT_vInit(void);

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
void PORT_vDeInit(void);

/** *****************************************************************************
 * \brief         Set or reset GPIO pin
 *
 * \param[in]     Set or Reset
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void PORT_vSetGpioPin(PORT_CFG_E_INDEX ePortIndex,uint8 u8Status);

/** *****************************************************************************
 * \brief         Read GPIO pin
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    Pin status
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 PORT_u8ReadGpioPin(PORT_CFG_E_INDEX ePortIndex);

/** *****************************************************************************
 * \brief         Toggle GPIO pin
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void PORT_vSetGpioPinToggle(PORT_CFG_E_INDEX ePortIndex);

/** *****************************************************************************
 * \brief         Set the GPIO mode
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void PORT_vSetGpioMode(PORT_CFG_E_INDEX ePortIndex, PORT_CFG_E_GPIO_MODE eGpioMode);


#ifdef __cplusplus
  }
#endif
#endif  /* PORT_API_H */

  
/*
 * End of file
 */
