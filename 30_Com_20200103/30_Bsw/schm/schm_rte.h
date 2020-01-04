/*******************************************************************************
 * \file    schm_rte.h
 * \brief   RTE interface for schm.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *    2. Fred Ji
 *    3. Harry Huang
 *
 * \section SVN
 *  $Date: 2018-08-23 15:34:14 +0800 (Thu, 23 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 14 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ******************************************************************************/

#ifndef SCHM_RTE_H
#define SCHM_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
		
/***********************************************
 * Output
 **********************************************/
/* Registers */
#define TM17_REG_INT_FLG_CLR     (TIM17->SR = (uint16)~TIM_FLAG_Update)
  
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/


#ifdef __cplusplus
  }
#endif
#endif  /* SCHM_RTE_H */

  
/*
 * End of file
 */
