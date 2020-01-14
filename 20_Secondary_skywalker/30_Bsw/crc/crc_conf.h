/** *****************************************************************************
 * \file    crc_conf.h
 * \brief   Configurations file for crc.c
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

#ifndef CRC_CONF_H
#define CRC_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

#define MG_CRC8_LOOKUP_TABLE    0
#define MG_CRC8_USED            0

#define MG_CRC16_LOOKUP_TABLE   1
#define MG_CRC16_USED           1


#ifdef __cplusplus
  }
#endif
#endif  /* CRC_CONF_H */


/*
 * End of file
 */
