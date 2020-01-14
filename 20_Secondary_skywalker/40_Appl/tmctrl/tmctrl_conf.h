/** *****************************************************************************
 * \file    tmctrl_cfg.h
 * \brief   Configuration file for tmctrl.c
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

#ifndef TMCTRL_CONF_H
#define TMCTRL_CONF_H
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
 * Timing Control Status
 **********************************************/
#define MG_B_LLC_EN                     TMCTRL_mg_uTmStatus.Bits.f0  /* 1 = input over voltage */
#define MG_B_LLC_HALT                   TMCTRL_mg_uTmStatus.Bits.f1  /* 1 = LLC in HALT */
#define MG_B_LLC_SWITCH_EN              TMCTRL_mg_uTmStatus.Bits.f2  /* 1 = LLC enabled by switch */
#define MG_B_PRIM_BULK_OK               TMCTRL_mg_uTmStatus.Bits.f3  /* 1 = Bulk OK */
#define MG_B_PRIM_VIN                   TMCTRL_mg_uTmStatus.Bits.f4  /* 1 = Vin */
#define MG_B_LLC_STANDBY                TMCTRL_mg_uTmStatus.Bits.f5  /* 1 = Vin */

/***********************************************
 * LLC control
 **********************************************/
#define MG_LLC_INIT                     0
#define MG_LLC_IDLE                     1
#define MG_LLC_ON                       2
#define MG_LLC_OFF                      3

#define MG_200US_TO_1MS_FACT            5U        /* 1ms / 200uS = 5 */

#define MG_U16_LLC_START_DLY        (uint16)(50U * MG_200US_TO_1MS_FACT)  /* ms (200us * 5 = 1ms) */
#define MG_U16_LLC_RESTART_DLY      (uint16)(100U * MG_200US_TO_1MS_FACT) /* ms (200us * 5 = 1ms) */

#define MG_U16_LLC_RESTART_CTR      (uint16)(0U) /* Number of re-start tries (0 for single start-up) */

/***********************************************
 * GPIO handle
 **********************************************/
#define MG_U16_LLC_ENABLE_DLY       (uint16)(1U * MG_200US_TO_1MS_FACT)    /* ms (200us * 5 = 1ms) */
#define MG_U16_LLC_HALT_DLY         (uint16)(25U * MG_200US_TO_1MS_FACT)   /* ms (200us * 5 = 1ms) */
#define MG_U16_LLC_SWITCH_EN_DLY    (uint16)(1U * MG_200US_TO_1MS_FACT)    /* ms (200us * 5 = 1ms) */
#define MG_U16_LLC_SWITCH_DIS_DLY   (uint16)(25U * MG_200US_TO_1MS_FACT)   /* ms (200us * 5 = 1ms) */
#define MG_U16_LLC_BULK_OK_DLY      (uint16)(100U * MG_200US_TO_1MS_FACT)  /* ms (200us * 5 = 1ms) */
#define MG_U16_LLC_BULK_FAIL_DLY    (uint16)(3U * MG_200US_TO_1MS_FACT)    /* ms (200us * 5 = 1ms) */
#define MG_U16_LLC_VIN_DLY          (uint16)(100U * MG_200US_TO_1MS_FACT)  /* ms (200us * 5 = 1ms) */


#ifdef __cplusplus
  }
#endif
#endif  /* TMCTRL_CONF_H */


/*
 * End of file
 */
