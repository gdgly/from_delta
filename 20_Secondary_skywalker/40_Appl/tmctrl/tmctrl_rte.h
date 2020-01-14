/** *****************************************************************************
 * \file    tmctrl_rte.h
 * \brief   RTE interface for tmctrl.c
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

#ifndef TMCTRL_RTE_H
#define TMCTRL_RTE_H
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
#define Rte_Read_R_B_LLC_COM_HALT             RTE_B_LLC_COM_HALT
#define Rte_Read_R_B_LLC_FAULT_CLR            RTE_B_LLC_FAULT_CLR
#define Rte_Read_R_B_PRIM_VIN_LOST            RTE_B_PRIM_VIN_LOST
#define Rte_Read_R_B_LLC_OVP                  RTE_B_LLC_OVP
#define Rte_Read_R_B_LLC_UVP                  RTE_B_LLC_UVP
#define Rte_Read_R_B_LLC_OCP                  RTE_B_LLC_OCP
#define Rte_Read_R_B_LLC_OPP                  RTE_B_LLC_OPP
#define Rte_Read_R_B_LLC_FAN_FAIL_1           RTE_B_LLC_FAN_FAIL_1
#define Rte_Read_R_B_LLC_FAN_FAIL_2           RTE_B_LLC_FAN_FAIL_2
#define Rte_Read_R_B_LLC_OT                   RTE_B_PSU_OT
#define Rte_Read_R_B_PORT_LLC_SWITCH_EN       RTE_B_PORT_LLC_SWITCH_EN
#define Rte_Read_R_B_PORT_LLC_HALT            RTE_B_PORT_LLC_HALT
#define Rte_Read_R_B_PORT_BULK_OK             RTE_B_PORT_BULK_OK
#define Rte_Read_R_B_BL_MODE                  RTE_B_BL_MODE
#define Rte_Read_R_B_LLC_SYNC_START_UP        RTE_B_LLC_SYNC_START_UP

/* Write bits */
#define Rte_Write_R_B_LLC_EN                  RTE_B_LLC_EN
#define Rte_Write_R_B_LLC_STANDBY             RTE_B_LLC_STANDBY
#define Rte_Write_R_B_LLC_OV_LATCH_CLR        RTE_B_LLC_OV_LATCH_CLR
#define Rte_Write_R_B_LLC_UV_LATCH_CLR        RTE_B_LLC_UV_LATCH_CLR
#define Rte_Write_R_B_LLC_OC_LATCH_CLR        RTE_B_LLC_OC_LATCH_CLR
#define Rte_Write_R_B_LLC_OPP_LATCH_CLR       RTE_B_LLC_OPP_LATCH_CLR
#define Rte_Write_P_B_PORT_PWM_ON             RTE_B_PORT_PWM_ON
#define Rte_Write_P_B_PORT_OVP_CLR            RTE_B_PORT_OVP_CLR
#define Rte_Write_P_B_PORT_ORING_EN           RTE_B_PORT_ORING_EN
#define Rte_Write_P_B_PORT_ISHARE_ON          RTE_B_PORT_ISHARE_ON
#define Rte_Write_R_B_HRTIMER_PWM_A_ON        RTE_B_HRTIMER_PWM_A_ON
#define Rte_Write_R_B_HRTIMER_PWM_B_ON        RTE_B_HRTIMER_PWM_B_ON
#define Rte_Write_R_B_HRTIMER_PWM_C_ON        RTE_B_HRTIMER_PWM_C_ON
#define Rte_Write_R_B_HRTIMER_PWM_D_ON        RTE_B_HRTIMER_PWM_D_ON
#define Rte_Write_R_B_HRTIMER_PWM_E_ON        RTE_B_HRTIMER_PWM_E_ON
#else
/* Read bits */
#define Rte_Read_R_B_LLC_COM_HALT             0
#define Rte_Read_R_B_LLC_FAULT_CLR            0
#define Rte_Read_R_B_PRIM_VIN_LOST            0
#define Rte_Read_R_B_LLC_OVP                  0
#define Rte_Read_R_B_LLC_UVP                  0
#define Rte_Read_R_B_LLC_OCP                  0
#define Rte_Read_R_B_LLC_FAN_FAIL_1           0
#define Rte_Read_R_B_LLC_FAN_FAIL_2           0
#define Rte_Read_R_B_LLC_OT                   0
#define Rte_Read_R_B_PORT_LLC_SWITCH_EN       0
#define Rte_Read_R_B_PORT_LLC_HALT            0
#define Rte_Read_R_B_PORT_BULK_OK             0
#define Rte_Read_R_B_PORT_VIN                 0
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* RTE module section */
/* Write bits */
inline void TMCTRL_Write_P_B_LLC_EN_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_LLC_EN = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_LLC_STANDBY_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_LLC_STANDBY = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_LLC_OV_LATCH_CLR_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_LLC_OV_LATCH_CLR = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_LLC_UV_LATCH_CLR_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_LLC_UV_LATCH_CLR = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_LLC_OC_LATCH_CLR_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_LLC_OC_LATCH_CLR = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_LLC_OPP_LATCH_CLR_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_LLC_OPP_LATCH_CLR = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_PORT_PWM_ON_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PORT_PWM_ON = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_PORT_OVP_CLR_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PORT_OVP_CLR = u8State;
  #endif
}
inline void TMCTRL_Write_P_PORT_ORING_EN_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PORT_ORING_EN = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_PORT_ISHARE_ON_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_P_B_PORT_ISHARE_ON = u8State;
  #endif
}

inline void TMCTRL_Write_P_B_HRTIMER_PWM_A_ON_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_HRTIMER_PWM_A_ON = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_HRTIMER_PWM_B_ON_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_HRTIMER_PWM_B_ON = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_HRTIMER_PWM_C_ON_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_HRTIMER_PWM_C_ON = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_HRTIMER_PWM_D_ON_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_HRTIMER_PWM_D_ON = u8State;
  #endif
}
inline void TMCTRL_Write_P_B_HRTIMER_PWM_E_ON_rte(uint8 u8State)
{
  #if MG_RTE_MODULE
  Rte_Write_R_B_HRTIMER_PWM_E_ON = u8State;
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* TMCTRL_RTE_H */

  
/*
 * End of file
 */
