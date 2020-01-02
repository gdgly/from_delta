/** *****************************************************************************
 * \file    flash_cfg.h
 * \brief   Server call back service file for flash.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-10-19 16:03:28 +0800 (Fri, 19 Oct 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 73 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef FLASH_CFG_H
#define FLASH_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "rte.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/
#define FALSH_APP_VECTOR_TABLR_ADDR       APP_VECTOR_TABLR_ADDR

#ifdef __cplusplus
  }
#endif
#endif  /* FLASH_CFG_H */

  
/*
 * End of file
 */
