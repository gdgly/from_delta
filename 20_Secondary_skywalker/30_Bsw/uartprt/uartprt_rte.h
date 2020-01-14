/** *****************************************************************************
 * \file    uartprt_rte.h
 * \brief   RTE interface for uartprt.c
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

#ifndef UARTPRT_RTE_H
#define UARTPRT_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif


/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_RTE_MODULE           1

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"

#if MG_RTE_MODULE
#include "rte.h"
#endif


/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/

#if MG_RTE_MODULE
/* Read bits */
#else
/* Read bits */
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Read data */
/* Write data */


#ifdef __cplusplus
  }
#endif
#endif  /* UARTPRT_RTE_H */

  
/*
 * End of file
 */
