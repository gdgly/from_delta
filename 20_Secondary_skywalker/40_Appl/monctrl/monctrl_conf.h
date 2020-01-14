/** *****************************************************************************
 * \file    monctrl_conf.h
 * \brief   Configuration file for monctrl.c
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

#ifndef MONCTRL_CONF_H
#define MONCTRL_CONF_H
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

/***********************************************
 * Configuration
 **********************************************/
#define MG_3_LEVEL_OCP                  1         /* 1 = Three OCP points available */

/***********************************************
 * MonitorStatus
 **********************************************/
#define MG_B_LLC_OUT_OVP                  MONCTRL_mg_uMonStatus.Bits.f0  /* 1 = output over voltage */
#define MG_B_LLC_OUT_OVW                  MONCTRL_mg_uMonStatus.Bits.f1  /* 1 = output over voltage warning */
#define MG_B_LLC_OUT_UVP                  MONCTRL_mg_uMonStatus.Bits.f2  /* 1 = output under voltage */
#define MG_B_LLC_OUT_UVW                  MONCTRL_mg_uMonStatus.Bits.f3  /* 1 = output under voltage warning */
#define MG_B_LLC_OUT_OCP                  MONCTRL_mg_uMonStatus.Bits.f4  /* 1 = output over current */
#define MG_B_LLC_OUT_OCW                  MONCTRL_mg_uMonStatus.Bits.f5  /* 1 = output over current warning */
#define MG_B_LLC_OUT_OPP                  MONCTRL_mg_uMonStatus.Bits.f6  /* 1 = output over power */

/***********************************************
 * Over voltage protection
 **********************************************/
#define MG_F32_LLC_VOLT_OUT_OVP           59.5F     /* (V) Over voltage */
#define MG_F32_LLC_VOLT_OUT_OVW           59.0F     /* (V) Over voltage warning */
#define MG_F32_LLC_VOLT_OUT_OVP_DLY        1.0F     /* (ms) Max resolution = 0.2mS */
#define MG_F32_LLC_VOLT_OUT_OVW_DLY       20.0F     /* (ms) Max resolution = 0.2mS */

/***********************************************
 * Under voltage protection
 **********************************************/
#define MG_F32_LLC_VOUT_UVP               42.0F     /* (V) Under voltage */
#define MG_F32_LLC_VOUT_UVP_DLY          300.0F     /* (ms) Max resolution = 0.2mS */

/***********************************************
 * Over current protection
 **********************************************/
#define MG_F32_LLC_IOUT_OCP_1_HL          91.0F     /* (A) Over current 1 high line (e.g. > 120%) */
#define MG_F32_LLC_IOUT_OCP_2_HL         115.0F     /* (A) Over current 2 high line (e.g. > 140%) */
#define MG_F32_LLC_IOUT_OCP_3_HL         135.0F     /* (A) Over current 3 high line (e.g. > 160%) */
#define MG_F32_LLC_CURRENT_MODE_OCP_HL   155.0F     /* (A) Constant current mode OCP */
#define MG_F32_LLC_IOUT_OCW_HL            81.5F     /* (A) Over current warning high line */

#define MG_F32_LLC_IOUT_OCP_1_LL          45.3F     /* (A) Over current 1 low line (e.g. > 120%) */
#define MG_F32_LLC_IOUT_OCP_2_LL          56.0F     /* (A) Over current 2 low line (e.g. > 140%) */
#define MG_F32_LLC_IOUT_OCP_3_LL          65.0F     /* (A) Over current 3 low line (e.g. > 160%) */
#define MG_F32_LLC_CURRENT_MODE_OCP_LL    80.0F     /* (A) Constant current mode OCP */
#define MG_F32_LLC_IOUT_OCW_LL            40.8F     /* (A) Over current warning high line */

#define MG_F32_LLC_IOUT_OCP_1_DLY        100.0F     /* (ms) Max resolution = 0.2mS */
#define MG_F32_LLC_IOUT_OCP_2_DLY         10.0F     /* (ms) Max resolution = 0.2mS */
#define MG_F32_LLC_IOUT_OCP_3_DLY          1.5F     /* (ms) Max resolution = 0.2mS */
#define MG_F32_LLC_IOUT_OCW_DLY            2.0F     /* (ms) Max resolution = 0.2mS */

/***********************************************
 * Over power protection
 **********************************************/
#define MG_F32_LLC_POUT_OPP             4800.0F     /* (W) Over power 120% */
#define MG_F32_LLC_POUT_OPP_DLY        10000.0F     /* (ms) Max resolution = 0.2mS */

#define MG_200US_TO_1MS_FACT                 5U     /* 1ms / 200uS = 5 */

/*******************************************************************************
 * Scaling section
 ******************************************************************************/

#define MG_U16_10mV_LLC_VOLT_OUT_OVP        (uint16)(MG_F32_LLC_VOLT_OUT_OVP * F32_10_MILLI)
#define MG_U16_10mV_LLC_VOLT_OUT_OVW        (uint16)(MG_F32_LLC_VOLT_OUT_OVW * F32_10_MILLI)
#define MG_U16_LLC_VOUT_OVP_DLY             (uint16)(MG_F32_LLC_VOLT_OUT_OVP_DLY * MG_200US_TO_1MS_FACT)    /* 200us * 5 = 1ms */
#define MG_U16_LLC_VOUT_OVW_DLY             (uint16)(MG_F32_LLC_VOLT_OUT_OVW_DLY * MG_200US_TO_1MS_FACT)    /* 200us * 5 = 1ms */

#define MG_U16_10mV_LLC_VOUT_UVP            (uint16)(MG_F32_LLC_VOUT_UVP * F32_10_MILLI)
#define MG_U16_LLC_VOUT_UVP_DLY             (uint16)(MG_F32_LLC_VOUT_UVP_DLY * MG_200US_TO_1MS_FACT)        /* 200us * 5 = 1ms */

#define MG_U16_10mA_LLC_IOUT_OCP_1_HL       (uint16)(MG_F32_LLC_IOUT_OCP_1_HL * F32_10_MILLI)
#define MG_U16_10mA_LLC_IOUT_OCP_2_HL       (uint16)(MG_F32_LLC_IOUT_OCP_2_HL * F32_10_MILLI)
#define MG_U16_10mA_LLC_IOUT_OCP_3_HL       (uint16)(MG_F32_LLC_IOUT_OCP_3_HL * F32_10_MILLI)
#define MG_U16_10mA_LLC_CURRENT_MODE_OCP_HL (uint16)(MG_F32_LLC_CURRENT_MODE_OCP_HL * F32_10_MILLI)
#define MG_U16_10mA_LLC_IOUT_OCW_HL         (uint16)(MG_F32_LLC_IOUT_OCW_HL * F32_10_MILLI)

#define MG_U16_10mA_LLC_IOUT_OCP_1_LL       (uint16)(MG_F32_LLC_IOUT_OCP_1_LL * F32_10_MILLI)
#define MG_U16_10mA_LLC_IOUT_OCP_2_LL       (uint16)(MG_F32_LLC_IOUT_OCP_2_LL * F32_10_MILLI)
#define MG_U16_10mA_LLC_IOUT_OCP_3_LL       (uint16)(MG_F32_LLC_IOUT_OCP_3_LL * F32_10_MILLI)
#define MG_U16_10mA_LLC_CURRENT_MODE_OCP_LL (uint16)(MG_F32_LLC_CURRENT_MODE_OCP_LL * F32_10_MILLI)
#define MG_U16_10mA_LLC_IOUT_OCW_LL         (uint16)(MG_F32_LLC_IOUT_OCW_LL * F32_10_MILLI)

#define MG_U16_LLC_IOUT_OCP_1_DLY           (uint16)(MG_F32_LLC_IOUT_OCP_1_DLY * MG_200US_TO_1MS_FACT)      /* 200us * 5 = 1ms */
#define MG_U16_LLC_IOUT_OCP_2_DLY           (uint16)(MG_F32_LLC_IOUT_OCP_2_DLY * MG_200US_TO_1MS_FACT)      /* 200us * 5 = 1ms */
#define MG_U16_LLC_IOUT_OCP_3_DLY           (uint16)(MG_F32_LLC_IOUT_OCP_3_DLY * MG_200US_TO_1MS_FACT)      /* 200us * 5 = 1ms */
#define MG_U16_LLC_IOUT_OCW_DLY             (uint16)(MG_F32_LLC_IOUT_OCW_DLY * MG_200US_TO_1MS_FACT)        /* 200us * 5 = 1ms */

#define MG_U16_100mW_LLC_POUT_OPP           (uint16)(MG_F32_LLC_POUT_OPP * F32_100_MILLI)
#define MG_U16_LLC_POUT_OPP_DLY             (uint16)(MG_F32_LLC_POUT_OPP_DLY * MG_200US_TO_1MS_FACT)        /* 200us * 5 = 1ms */


#ifdef __cplusplus
  }
#endif
#endif  /* MONCTRL_CONF_H */


/*
 * End of file
 */
