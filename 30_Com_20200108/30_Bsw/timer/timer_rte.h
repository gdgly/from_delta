/** *****************************************************************************
 * \file    timer_rte.h
 * \brief   RTE interface for timer.c
 *
 * \section AUTHOR
 *    1. Jackie Chen
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

#ifndef TIMER_RTE_H
#define TIMER_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif
/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "rte.h"
/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
 
/***********************************************
 * Input
 **********************************************/

/***********************************************
 * Output
 **********************************************/
#define RTE_u8Timer0Tick           RTE_u8Timer0Tick


/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

extern DWORD_VAL TMR_u32HoursUsed;   /* 3byte used for USED_HOURS */
extern DWORD_VAL TMR_u32MinutesUsed; /* 4byte used for USED_MINUTES */

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/


#ifdef __cplusplus
  }
#endif
#endif  /* TIMER_RTE_H */

  
/*
 * End of file
 */
