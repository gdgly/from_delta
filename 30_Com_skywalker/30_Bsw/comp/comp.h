/*******************************************************************************
 * \file    comp.h
 * \brief   Global interface for comp.c
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

#ifndef COMP_H
#define COMP_H
#ifdef __cplusplus
  extern "C"  {
#endif
    
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize and configure MCU comparators (current limitation)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void COMP_vCompHwInit(void);

#ifdef __cplusplus
  }
#endif
#endif  /* COMP_H */

  
/*
 * End of file
 */
