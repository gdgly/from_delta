/** *****************************************************************************
 * \file    psuctrl_cfg.h
 * \brief   Server call back service file for psuctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-01-11 10:40:42 +0800 (Fri, 11 Jan 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 137 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PSUCTRL_CFG_H
#define PSUCTRL_CFG_H
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
#include "blabox_scb.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/
SINLINE void PSUCTRL_CFG_vBlaboxClearFault(void)
{
  BLABOX_vClearFault();
}


#ifdef __cplusplus
  }
#endif
#endif  /* PSUCTRL_CFG_H */

  
/*
 * End of file
 */
