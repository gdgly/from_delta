/** *****************************************************************************
 * \file    cali_cfg.h
 * \brief   Server call back service file for cali.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-09-26 11:19:59 +0800 (Wed, 26 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 42 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef CALI_CFG_H
#define CALI_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* Calibration Mode  */
#define NO_CALI_MODE                0x00
#define CALI_VIN_AC                 0x10
#define CALI_IIN_AC                 0x20
#define CALI_PIN_AC                 0x30
#define CALI_V_V1                   0x40
#define CALI_I_V1                   0x50
#define CALI_V_VSB                  0x60
#define CALI_I_VSB                  0x70
#define CALI_V1_SENSE               0x80
#define CALI_V1_ISHARE              0x90
#define CALI_DEF_MODE               0xFE
#define CALI_DONE_MODE              0xFF

/* Calibration Line Number for all Cali_Mode  */
#define EEP_REGION_STR              0x0000
#define EE_ADR_CALI_DATA_STR        0x0100
#define CALI_EEP_DATA_STR           (EE_ADR_CALI_DATA_STR + EEP_REGION_STR)

#define EEPROM_ADR_VIN_AC_BASE      0x0100
#define CALI_VIN_AC_DATA_SIZE       (CALI_VIN_AC_LINE_NUM << 3)
#define EEPROM_ADR_VIN_AC_END       EEPROM_ADR_VIN_AC_BASE + CALI_VIN_AC_DATA_SIZE - 1

#define EEPROM_ADR_IIN_AC_BASE      0x0120
#define CALI_IIN_AC_DATA_SIZE       (CALI_IIN_AC_LINE_NUM << 3)
#define EEPROM_ADR_IIN_AC_END  	    EEPROM_ADR_IIN_AC_BASE + CALI_IIN_AC_DATA_SIZE - 1

#define EEPROM_ADR_PIN_AC_BASE      0x0160
#define CALI_PIN_AC_DATA_SIZE       (CALI_PIN_AC_LINE_NUM << 3)
#define EEPROM_ADR_PIN_AC_END  	    EEPROM_ADR_PIN_AC_BASE + CALI_PIN_AC_DATA_SIZE - 1

#define EEPROM_ADR_V_V1_BASE        0x01A0
#define CALI_V_V1_DATA_SIZE         (CALI_V_V1_LINE_NUM << 3)
#define EEPROM_ADR_V_V1_END    	    EEPROM_ADR_V_V1_BASE + CALI_V_V1_DATA_SIZE - 1

#define EEPROM_ADR_I_V1_BASE        0x01C0
#define CALI_I_V1_DATA_SIZE         (CALI_I_V1_LINE_NUM << 3)
#define EEPROM_ADR_I_V1_END         EEPROM_ADR_I_V1_BASE + CALI_I_V1_DATA_SIZE - 1

#define EEPROM_ADR_V_VSB_BASE       0x0200
#define CALI_V_VSB_DATA_SIZE        (CALI_V_VSB_LINE_NUM << 3)
#define EEPROM_ADR_V_VSB_END  	    EEPROM_ADR_V_VSB_BASE + CALI_V_VSB_DATA_SIZE - 1

#define EEPROM_ADR_I_VSB_BASE       0x0220
#define CALI_I_VSB_DATA_SIZE        (CALI_I_VSB_LINE_NUM << 3)
#define EEPROM_ADR_I_VSB_END  	    EEPROM_ADR_I_VSB_BASE + CALI_I_VSB_DATA_SIZE - 1

#define EEPROM_ADR_V1_ISHARE_BASE   0x0260
#define CALI_V1_ISHARE_DATA_SIZE    (CALI_V1_ISHARE_LINE_NUM << 3)
#define EEPROM_ADR_V1_ISHARE_END  	EEPROM_ADR_V1_ISHARE_BASE + CALI_V1_ISHARE_DATA_SIZE - 1

#define CALI_EEP_DATA_END           (EEPROM_ADR_V1_ISHARE_END + 16)		

#ifdef __cplusplus
  }
#endif
#endif  /* CALI_CFG_H */

  
/*
 * End of file
 */
