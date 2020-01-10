/** *****************************************************************************
 * \file    hwio_conf.h
 * \brief   Configurations file for hwio.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2019-01-09 16:18:26 +0800 (Wed, 09 Jan 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 135 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef HWIO_CONF_H
#define HWIO_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
#define HWIO_CONFG_PSKILL_SET_CNT             ((uint16)100u)  /* 100*0.1ms  -- 10ms */
#define HWIO_CONFG_PSKILL_RESET_CNT           ((uint16)3u)    /* 3   *0.1ms -- 300um */		
#define HWIO_CONFG_PSON_SET_CNT               ((uint16)3u)    /* 3   *0.1ms -- 300um */			
#define HWIO_CONFG_PSON_RESET_CNT             ((uint16)100u)  /* 100*0.1ms  -- 10ms */	
#define HWIO_CONFG_VMAIN_FAULT_SET_CNT        ((uint8)0u)     /* 20  *0.1ms -- 2ms */		
#define HWIO_CONFG_VMAIN_FAULT_RESET_CNT      ((uint8)0u)     /* 20  *0.1ms -- 2ms */	
#define HWIO_CONFG_VIN_OK_SET_CNT             ((uint8)10u)    /* 3   *0.1ms -- 0.3ms */		
#define HWIO_CONFG_VIN_OK_RESET_CNT           ((uint8)2u)     /* 3   *0.1ms -- 0.3ms */		
#define HWIO_CONFG_A0_SET_CNT                 ((uint8)20u)    /* 20  *0.1ms -- 2ms */		
#define HWIO_CONFG_A0_RESET_CNT               ((uint8)20u)    /* 20  *0.1ms -- 2ms */	
#define HWIO_CONFG_A1_SET_CNT                 ((uint8)20u)    /* 20  *0.1ms -- 2ms */		
#define HWIO_CONFG_A1_RESET_CNT               ((uint8)20u)    /* 20  *0.1ms -- 2ms */	
#define HWIO_CONFG_A2_SET_CNT                 ((uint8)20u)    /* 20  *0.1ms -- 2ms */		
#define HWIO_CONFG_A2_RESET_CNT               ((uint8)20u)    /* 20  *0.1ms -- 2ms */		

/*******************************************************************************
 * Scaling section
 ******************************************************************************/



/***************************************
 * HrTimer ID config
 **************************************/



#ifdef __cplusplus
  }
#endif
#endif  /* HWIO_CONF_H */


/*
 * End of file
 */
