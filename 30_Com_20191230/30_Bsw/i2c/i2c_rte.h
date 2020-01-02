/*******************************************************************************
 * \file    i2c_rte.h
 * \brief   RTE interface for i2c.c
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2018-08-07 18:22:40 +0800 (Tue, 07 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 11 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef I2C_RTE_H
#define I2C_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

#include "global.h"
#include "rte.h"
/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
/***********************************************
 * Input
 **********************************************/
/* Flags */

/* Registers */

/* Definitions */

/***********************************************
 * Output
 **********************************************/

/* Flags */
#define RTE_Write_B_P_I2C_RESET_FLG                 (RTE_I2C_RESET_FLG)

/* Registers */  

/* Definitions */
   
/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

SINLINE void MONCTRL_RTE_Write_B_P_I2C_RESET_FLG(uint8 u8Status)
{
  RTE_Write_B_P_I2C_RESET_FLG =  u8Status;
}


#ifdef __cplusplus
  }
#endif
#endif  /* I2C_RTE_H */

  
/*
 * End of file
 */
