/** *****************************************************************************
 * \file    pmbus_conf.h
 * \brief   Configurations file for pmbus.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-09-10 08:40:13 +0800 (Mon, 10 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 24 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PMBUS_CONF_H
#define PMBUS_CONF_H
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

/* I2C debug register definition */
#define RTE_DEBUG_ADR_PRI_VIN_ADC        0x00
#define RTE_DEBUG_ADR_PRI_IIN_ADC        0x01
#define RTE_DEBUG_ADR_PRI_PIN_ADC        0x02
#define RTE_DEBUG_ADR_PRI_VBULK_ADC      0x03
#define RTE_DEBUG_ADR_PRI_NTC_PFC_ADC    0x04
#define RTE_DEBUG_ADR_PRI_STATUS_00      0x05
#define RTE_DEBUG_ADR_PRI_STATUS_01      0x06
#define RTE_DEBUG_ADR_PRI_DEBUG_0        0x07
#define RTE_DEBUG_ADR_PRI_DEBUG_1        0x08
#define RTE_DEBUG_ADR_PRI_DEBUG_2        0x09
#define RTE_DEBUG_ADR_PRI_VIN_FREQ       0x0A
#define RTE_DEBUG_ADR_PRI_PWR_FACT       0x0B
#define RTE_DEBUG_ADR_PRI_TEMP_STATUS    0x0C
#define RTE_DEBUG_ADR_PRI_NTC_LLC_ADC    0x0D

#define RTE_DEBUG_ADR_SEC_V1_INT_ADC     0x10
#define RTE_DEBUG_ADR_SEC_V1_EXT_ADC     0x11
#define RTE_DEBUG_ADR_SEC_V1_I_ADC       0x12
#define RTE_DEBUG_ADR_SEC_V1_PWR_ADC     0x13
#define RTE_DEBUG_ADR_SEC_ISHARE_ADC     0x14
#define RTE_DEBUG_ADR_SEC_ILOCAL_ADC     0x15
#define RTE_DEBUG_ADR_SEC_NTC_RECDIO_ADC 0x16
#define RTE_DEBUG_ADR_SEC_STATUS_00      0x18
#define RTE_DEBUG_ADR_SEC_STATUS_01      0x19
#define RTE_DEBUG_ADR_SEC_STATUS_02      0x1a
#define RTE_DEBUG_ADR_SEC_DEBUG_0        0x1b
#define RTE_DEBUG_ADR_SEC_DEBUG_1        0x1c
#define RTE_DEBUG_ADR_SEC_DEBUG_2        0x1d

#define RTE_DEBUG_ADR_TEMP_OTW_STATUS      0x20
#define RTE_DEBUG_ADR_TEMP_OTP_STATUS      0x21
#define RTE_DEBUG_ADR_DIO_IN_STATUS        0x22
#define RTE_DEBUG_ADR_DIO_OUT_STATUS       0x23
#define RTE_DEBUG_ADR_COM_TO_PRI_STATUS    0x24
#define RTE_DEBUG_ADR_COM_TO_SEC_STATUS    0x25
#define RTE_DEBUG_ADR_COM_STATUS_00        0x26
#define RTE_DEBUG_ADR_COM_STATUS_01        0x27
#define RTE_DEBUG_ADR_COM_STATUS_02        0x28

#define RTE_DEBUG_ADR_V_VSB_INT_AVG        0x50
#define RTE_DEBUG_ADR_V_VSB_EXT_AVG        0x51
#define RTE_DEBUG_ADR_I_VSB_AVG            0x52
#define RTE_DEBUG_ADR_NTC_INLET_ADC_AVG    0x53
#define RTE_DEBUG_ADR_FAN_DUTY             0x54
#define RTE_DEBUG_ADR_FAN_SPEED_1          0x55
#define RTE_DEBUG_ADR_FAN_SPEED_2          0x56
#define RTE_DEBUG_ADR_COM_DEBUG_0          0x57
#define RTE_DEBUG_ADR_COM_DEBUG_1          0x58
#define RTE_DEBUG_ADR_COM_DEBUG_2          0x59
#define RTE_DEBUG_ADR_COM_DEBUG_3          0x5A
#define RTE_DEBUG_ADR_NTC_OUTLET_ADC_AVG   0x5B

#define RTE_PMB_Read_u8PecErrCmd()         (RTE_u8I2cPECErrCmd)
#define RTE_PMB_Write_u8PecErrCmd(u8Val)   (RTE_u8I2cPECErrCmd = (u8Val))



#ifdef __cplusplus
  }
#endif
#endif  /* I2C_CONF_H */


/*
 * End of file
 */
