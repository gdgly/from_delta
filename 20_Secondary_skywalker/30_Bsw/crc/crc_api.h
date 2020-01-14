/** *****************************************************************************
 * \file    crc_api.h
 * \brief   Service function request file for crc.c
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

#ifndef CRC_API_H
#define CRC_API_H
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
 * \brief         Calculate crc16
 *
 * \param[in]     uint16 * pu16InCrc  uint8 u8InData
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
uint16 CRC_u16GetCrc16(uint16 u16InCrc, uint8 u8InData);

/** *****************************************************************************
 * \brief         Calculate crc8. Add data to crc calculated as 16 bit value 
 *                used the polynominal value 0x8005.
 * \param[in]     crc - pointer to crc byte
 *                data - data for crc calculation
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        uint8
 *
 *******************************************************************************/
uint8 CRC_u8GetCrc8(uint8 u8InCrc, uint8 u8InData);


#ifdef __cplusplus
  }
#endif
#endif  /* CRC_API_H */

  
/*
 * End of file
 */
