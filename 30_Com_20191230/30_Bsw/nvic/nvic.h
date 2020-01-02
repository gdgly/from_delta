/*******************************************************************************
 * \file    nvic.h
 * \brief   Global interface for nvic.c
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

#ifndef NVIC_H
#define NVIC_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
    
/*******************************************************************************
 * \brief         Initialize the nested interrupt vector controller
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void NVIC_vInitNVIC(void);
    
extern void NVIC_I2C1_INT_DISABLE(void);
		
extern void NVIC_I2C1_INT_ENABLE(void);

extern void NVIC_I2C2_INT_ENABLE(void);

#ifdef __cplusplus
  }
#endif
#endif  /* NVIC_H */

  
/*
 * End of file
 */
