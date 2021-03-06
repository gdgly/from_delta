/** *****************************************************************************
 * \file    monctrl_conf.h
 * \brief   Configurations file for monctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-11-22 11:01:57 +0800 (Fri, 22 Nov 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 239 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef MONCATL_CONF_H
#define MONCATL_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "pmbus_cfg.h"
#include "pmbus_rte.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
/* Input for 3.3V on/off *//* following 2 defs not used until 20200110 */
#define VIN_Vsb_ON                     ((uint16)((uint16)((uint32)((85.0f) * 128UL + 8U)>>4) + SCALE_MN3)) /* this value relate to AC_NO_VIN_HIGH */
#define VIN_Vsb_OFF                    ((uint16)((uint16)((uint32)((80.0f) * 128UL + 8U)>>4) + SCALE_MN3))

/* AC input threshold define */
#define AC_DROPOUT_VIN_HIGH            72.0f * VIN_FRC_RESULUTION//((uint16)((uint16)((uint32)((72.0f) * 128UL + 8U)>>4) + SCALE_MN3))
#define AC_DROPOUT_VIN_LOW             20.0f * VIN_FRC_RESULUTION//((uint16)((uint16)((uint32)((20.0f) * 128UL + 8U)>>4) + SCALE_MN3))
#define AC_VIN_UV_HIGH                 86.0f * VIN_FRC_RESULUTION//((uint16)((uint16)((uint32)((85.0f) * 128UL + 8U)>>4) + SCALE_MN3))
#define AC_VIN_UV_LOW                  83.0f * VIN_FRC_RESULUTION//((uint16)((uint16)((uint32)((79.0f) * 128UL + 8U)>>4) + SCALE_MN3))
#define AC_VIN_UVW_VOLT                88.0f * VIN_FRC_RESULUTION//((uint16)((uint16)((uint32)((82.0f) * 128UL + 8U)>>4) + SCALE_MN3))

#define AC_VIN_OV_HIGH                 280.0f *VIN_FRC_RESULUTION//((uint16)((uint16)((uint32)((285.0f) * 128UL + 32U)>>6) + SCALE_MN1))
#define AC_VIN_OV_LOW                  270.0f *VIN_FRC_RESULUTION//((uint16)((uint16)((uint32)((272.0f) * 128UL + 32U)>>6) + SCALE_MN1))
#define AC_VIN_OCW_CURR								 16.0f * IIN_FRC_RESULUTION//16A


/* input check delay */
#define MG_U16_VIN_DROPOUT_DLY         ((uint16)(50))                   /* ms ; drop out delay */
#define MG_U16_VIN_UVP_DLY             ((uint16)(50))                   /* ms ; UV delay */
#define MG_U16_VIN_UVW_DLY             ((uint16)(15000))                /* ms ; UwV delay */
#define MG_U16_VIN_OVP_DLY             ((uint16)(50))                   /* ms ; OV delay */

/* VSB OCP/OCW/OVP/OVW/UVP/UVW */
#define   MG_VSB_OVP_HIGH               PMB_VM_Y_VSB_VOUT(3.762)
#define   MG_VSB_OVP_LOW                PMB_VM_Y_VSB_VOUT(3.63)
#define   MG_VSB_OVW_HIGH               PMB_VM_Y_VSB_VOUT(3.56)
#define   MG_VSB_OVW_LOW                PMB_VM_Y_VSB_VOUT(3.46)
#define   MG_VSB_UVP_HIGH               PMB_VM_Y_VSB_VOUT(2.97)
#define   MG_VSB_UVW_LOW                PMB_VM_Y_VSB_VOUT(2.838)
#define   MG_VSB_UVW_HIGH               PMB_VM_Y_VSB_VOUT(3.14)
#define   MG_VSB_UVP_LOW                PMB_VM_Y_VSB_VOUT(3.04)
#define   MG_VSB_EXT_UVP_LOW            ((uint16)500U)                    /* 500 * 10mv = 5000mv */

//following 3 defs not used until 20200107
#define  MG_VSB_SCP_VOLT_ST             PMB_VM_Y_VSB_VOUT(1.5)
#define  MG_VSB_SCP_VOLT_H              PMB_VM_Y_VSB_VOUT(10.5)
#define  MG_VSB_SCP_VOLT_L              PMB_VM_Y_VSB_VOUT(3.0)

#define   MG_VSB_MUL_128(X)             ((uint16)(X * 128.0F))
#ifdef HALT_TEST_MODE
#define   MG_VSB_SCP_HIGH               MG_VSB_MUL_128(3.0f * 1.20f)
#else
#define   MG_VSB_SCP_HIGH               MG_VSB_MUL_128(3.6)
#endif
#define   MG_VSB_SCP_LOW                MG_VSB_MUL_128(3.0)
#ifdef HALT_TEST_MODE
#define   MG_VSB_OCP_HIGH               MG_VSB_MUL_128(3.0f * 1.20f)
#else
#define   MG_VSB_OCP_HIGH               MG_VSB_MUL_128(2.7)
#endif
#define   MG_VSB_OCP_LOW                MG_VSB_MUL_128(2.5)
#define   MG_VSB_OCW_HIGH               MG_VSB_MUL_128(2.4)
#define   MG_VSB_OCW_LOW                MG_VSB_MUL_128(2.3)
#define		MG_VSB_SCP_ST_DLY             (uint16)(5u)            /*   5  *  1ms = 5ms */
#define		MG_VSB_OCP_ST_DLY             (uint16)(50u)            /*   5  *  1ms = 5ms */
#define		MG_VSB_SCP_DLY                (uint16)(5u)            /*   5  *  1ms = 5ms */
#define		MG_VSB_OCP_DLY                (uint16)(5u)            /*   5  *  1ms = 5ms */
#define		MG_VSB_OCP_OFF_DLY            (uint16)(500u)          /*   500  *  1ms = 5ms */
#define		MG_VSB_OCW_DLY		            (uint16)(50u)           /*  50  * 1ms = 50ms */
#define   MG_VSB_UVP_DLY                (uint16)(100u)          /*  100 * 1ms = 100ms  */
#define   MG_VSB_UVW_DLY                (uint16)(100u)          /*  100 * 1ms = 100ms  */
#define   MG_VSB_OVP_DLY                (uint16)(10u)           /*  10  * 1ms = 100ms  */
#define   MG_VSB_OVW_DLY                (uint16)(10u)           /*  10  * 1ms = 100ms  */

/* POWER_GOOD_ON/OFF */
#define VSB_PWOK_DLY			                (uint8)(100u)
#define VSB_PW_NOK_DLY           		     	(uint8)(10u)

/* AUX Mode Detect */
#define VSB_AUX_MODE_DETECT_DLY           (uint8)(4u)

/*
  define information on the PSU's input line status.
    000; Low line 50Hz, AC present;
    001: No AC input;
    010: High Line 50Hz, AC present;
    011: HVDC input (240Vdc);
    100: Low line 60Hz, AC present;
    101: reserved;
    110: High Line, 60Hz, AC Present;
    111: Reserved;

*/
#define  MG_LOW_LINE_50HZ               (0u)         /* Low line 50Hz, AC present;*/ 
#define  MG_NO_AC_INPUT                 (1u)         /* No AC input*/
#define  MG_HIGH_LINE_50HZ              (2u)         /* HIGH line 50Hz, AC present;*/ 
#define  MG_HVDC_INPUT                  (3u)         /* HVDC input (240Vdc)*/ 
#define  MG_LOW_LINE_60HZ               (4u)         /* Low line 60Hz, AC present;*/ 
#define  MG_HIGH_LINE_60HZ              (6u)         /* HIGH line 60Hz, AC present;*/ 
#define  MG_RESERVED                    (7u)         /* Reserved*/


#ifdef __cplusplus
  }
#endif
#endif  /* MONCATL_CONF_H */


/*
 * End of file
 */
