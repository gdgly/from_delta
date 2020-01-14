/** *****************************************************************************
 * \file    clock_conf.h
 * \brief   Configurations file for clock.c
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

#ifndef CLOCK_CONF_H
#define CLOCK_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/***************************************
 * CPU clock defines
 **************************************/
#if DEBUG_SECTION_INT_OSCILLATOR
#define MG_EXTERNAL_OSCILLATOR        FALSE
#else
#define MG_EXTERNAL_OSCILLATOR        1      /* 1 = External oscillator; 0 = internal oscillator */
#endif

/***************************************
 * Vector table location defines
 **************************************/
/* Relocate vector Table in Internal SRAM */
#define MG_VECT_TAB_SRAM              0
/* Relocate vector Table in CCMRAM */
#define MG_VECT_TAB_CCMRAM            1
/* Relocate vector Table in FLASH */
#define MG_VECT_TAB_FLASH             0
/*!< Vector Table base offset field. This value must be a multiple of 0x200. */
#define MG_VECT_TAB_OFFSET            0x0


#ifdef __cplusplus
  }
#endif
#endif  /* CLOCK_CONF_H */

  
/*
 * End of file
 */
