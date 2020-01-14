/** *****************************************************************************
 * \file    wdg_conf.h
 * \brief   Configurations file for wdg.c
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

#ifndef WDG_CONF_H
#define WDG_CONF_H
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

/*
 * IWDG independent low speed clock = 41KHz (LSI)
 * 12-bit max counter value (4096)
 * 41kHz / 4 (prescaler) = 10250/s -> 10.25/ms
 */
#define MG_F32_MS_WDG_CONV_FACT     (float32)(10.25F)


#ifdef __cplusplus
  }
#endif
#endif  /* WDG_CONF_H */


/*
 * End of file
 */
