/** *****************************************************************************
 * \file    trap_rte.h
 * \brief   RTE interface for trap.c
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
 ***************************************************************************** */

#ifndef TRAP_RTE_H
#define TRAP_RTE_H
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
#define RTE_REG_PWM_PFC_PWMA_OFF      RTE_REG_PWM_PWMA_OFF      /* PWMA software turn off */
#define RTE_REG_PWM_PFC_PWMB_OFF      RTE_REG_PWM_PWMB_OFF      /* PWMB software turn off */
#define RTE_REG_PWM_EXT_PWM_OFF       RTE_REG_PWM_EXT_OFF       /* Ext PWM software turn off */

#define RTE_REG_PORT_PFC_DIS          RTE_REG_PORT_PWM_DIS      /* PWMA&B hardware turn off */
#define RTE_REG_PORT_PFC_BULK_NOT_OK  RTE_REG_PORT_BULK_NOT_OK  /* Bulk voltage not OK */
#define RTE_REG_PORT_PFC_VIN_NOT_OK   RTE_REG_PORT_VIN_NOT_OK   /* Input voltage not OK */

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/
 
/***********************************************
 * Output
 **********************************************/
/* Flags */
#define RTE_B_PFC_EN                RTE_FLG_PFC_EN
#define RTE_B_EXT_EN                RTE_FLG_EXT_EN

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/


#ifdef __cplusplus
  }
#endif
#endif  /* TMCTRL_H */

  
/*
 * End of file
 */
