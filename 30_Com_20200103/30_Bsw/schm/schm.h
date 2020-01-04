/*******************************************************************************
 * \file    schm.h
 * \brief   Global interface for schm.c
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef SCHM_H
#define SCHM_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
    
#if !RTE_ISR_MAIN
/*******************************************************************************
 * \brief         Scheme routine for task processings
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void SCHM_vSchem(void);
#endif
    

#ifdef __cplusplus
  }
#endif
#endif  /* SCHM_H */

  
/*
 * End of file
 */
