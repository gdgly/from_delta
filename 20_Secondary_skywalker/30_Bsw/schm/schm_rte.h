/** *****************************************************************************
 * \file    schm_rte.h
 * \brief   RTE interface for schm.c
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

#ifndef SCHM_RTE_H
#define SCHM_RTE_H
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


#ifdef __cplusplus
  }
#endif
#endif  /* SCHM_RTE_H */

  
/*
 * End of file
 */
