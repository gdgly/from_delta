/** *****************************************************************************
 * \file    port_api.h
 * \brief   Service function request file for port.c
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

#ifndef PORT_API_H
#define PORT_API_H
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
void PORT_vSetGpioPinPwmOn(uint8 u8Status);
void PORT_vSetGpioPinIshareOn(uint8 u8Status);
void PORT_vSetGpioPinOvpClr(uint8 u8Status);
void PORT_vInputGpioPinOvpClr(void);
void PORT_vOutputGpioPinOvpClr(void);
void PORT_vSetGpioPinOringPulse(uint8 u8Status);
void PORT_vSetGpioPinOringEn(uint8 u8Status);
void PORT_vSetGpioPinLlcFault(uint8 u8Status);

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
uint8 PORT_u8ReadGpioPinVinOk(void);
uint8 PORT_u8ReadGpioPinBulkOk(void);
uint8 PORT_u8ReadGpioPinOvp(void);
uint8 PORT_u8ReadGpioPinLlcSwitchEn(void);
uint8 PORT_u8ReadGpioPinLlcHalt(void);
uint8 PORT_u8ReadGpioPinUartAddr(void);


#ifdef __cplusplus
  }
#endif
#endif  /* PORT_API_H */

  
/*
 * End of file
 */
