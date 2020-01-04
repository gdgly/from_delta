/** *****************************************************************************
 * \file    i2cprt_conf.h
 * \brief   Configurations file for i2cprt.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-07 18:22:40 +0800 (Tue, 07 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 11 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef I2CPRT_CONF_H
#define I2CPRT_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "rte.h"
		
/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
#define I2CPRT_CONF_RX_BUF_SIZE         I2C_RX_BUF_SIZE
#define I2CPRT_CONF_TX_BUF_SIZE         I2C_TX_BUF_SIZE
/***********************************************
 * Baud rate
 **********************************************/


/***********************************************
 * I2C peripheral register relative definition
 **********************************************/



#ifdef __cplusplus
  }
#endif
#endif  /* I2C_CONF_H */


/*
 * End of file
 */
