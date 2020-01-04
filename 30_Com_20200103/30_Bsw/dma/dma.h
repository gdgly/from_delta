/*******************************************************************************
 * \file    dma.h
 * \brief   Global interface for dma.c
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

#ifndef DMA_H
#define DMA_H
#ifdef __cplusplus
  extern "C"  {
#endif
    
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Allows direct memory access and data 
 *                transfer (buffer sampled ADC values)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void DMA_vDmaInit(void);

#ifdef __cplusplus
  }
#endif
#endif  /* DMA_H */

  
/*
 * End of file
 */
