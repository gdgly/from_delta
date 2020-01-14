/** *****************************************************************************
 * \file    intcom_conf.h
 * \brief   Configuration file for intcom.c
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

#ifndef INTCOM_CONF_H
#define INTCOM_CONF_H
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

#define MG_BOOT_MASK          0x01

#ifdef HALT_TEST_MODE
#define  SPECIAL_SW_VERSION   0x80u
#else
#define  SPECIAL_SW_VERSION   0x00u
#endif

#define MG_APP_MAJOR_REV      (2U + SPECIAL_SW_VERSION)
#define MG_APP_MINOR_REV      2
#define MG_APP_DEBUG_REV      'a'
#define MG_BOOT_MAJOR_REV     1
#define MG_BOOT_MINOR_REV     0
#define MG_BOOT_DEBUG_REV     'a'

/* Calibration limitation */
#define MG_F32_CALIB_GAIN_MAX        1.2F   /* (100%) Max calibration gain */
#define MG_F32_CALIB_GAIN_MIN        0.8F   /* (100%) Min calibration gain */
#define MG_F32_CALIB_OFS_MIN        -5.0F   /* (A) Min calibration offset */
#define MG_F32_CALIB_OFS_MAX         5.0F   /* (A) Max calibration offset */

/*******************************************************************************
 * Scaling section
 ******************************************************************************/

#define MG_U16Q12_CALIB_GAIN_MAX     ((uint16)U32Q12(MG_F32_CALIB_GAIN_MAX))
#define MG_U16Q12_CALIB_GAIN_MIN     ((uint16)U32Q12(MG_F32_CALIB_GAIN_MIN))
#define MG_S16_10mA_CALIB_OFS_MAX    ((sint16)MG_F32_CALIB_OFS_MAX * F32_10_MILLI)
#define MG_S16_10mA_CALIB_OFS_MIN    ((sint16)MG_F32_CALIB_OFS_MIN * F32_10_MILLI)

#ifdef __cplusplus
  }
#endif
#endif  /* INTCOM_CONF_H */

  
/*
 * End of file
 */
