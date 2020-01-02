/** *****************************************************************************
 * \file    clock_conf.h
 * \brief   Configurations file for clock.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
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

#ifndef CLOCK_CONF_H
#define CLOCK_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "rte.h"

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/***************************************
 * CPU clock defines
 **************************************/
#ifndef HSE_VALUE
#define HSE_VALUE  ((uint32)16000000)  /* Value of the External oscillator in Hz*/
#endif

#ifndef HSI_VALUE		
#define HSI_VALUE  ((uint32)8000000u)  /* Value of the Internal High Speed oscillator in Hz. */
#endif

#ifdef __cplusplus
  }
#endif
#endif  /* CLOCK_CONF_H */

  
/*
 * End of file
 */
