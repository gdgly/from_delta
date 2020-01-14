/** *****************************************************************************
 * \file    meter_cfg.h
 * \brief   Configuration file for meter.c
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

#ifndef METER_CONF_H
#define METER_CONF_H
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

/* Meter counters */
#define MG_U8_AVG_CTR                     ((uint8)32U)      /* 32 times averaging */

/* Meter constants */
#define MG_U16_Q12_POWER_SCALE            (uint16)U32Q12(1024.0F / 1000.0F)  /* (Q10 / 1000) Q10; from shift, 1000 from 10mA and 10mV to 100mW */


#ifdef __cplusplus
  }
#endif
#endif  /* METER_CONF_H */

  
/*
 * End of file
 */
