/** *****************************************************************************
 * \file    pmbus_cfg.h
 * \brief   Server call back service file for pmbus.c
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

#ifndef PMBUS_CFG_H
#define PMBUS_CFG_H
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
#include "i2cprt_cfg.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* Power Supply Management Interface(PSMI)  */
#define PSMI_02_READ_TEMPERATURE_1			0x02
#define PSMI_03_READ_TEMPERATURE_2		  0x03
#define PSMI_20_READ_FAN_SPEED_1				0x20
#define PSMI_21_READ_FAN_SPEED_2				0x21
#define	PSMI_28_READ_VOUT 							0x28
#define PSMI_32_READ_AC_VIN							0x32
#define PSMI_33_READ_IOUT								0x33
#define PSMI_35_READ_AC_PIN 						0x35
#define PSMI_36_READ_POUT								0x36
#define PSMI_3D_READ_AC_IIN							0x3D
#define PSMI_5E_SHUTDOWN_EVENTS					0x5E
#define PSMI_5F_THERMAL_WARNING_EVENTS	0x5F
#define PSMI_60_IOUT_WARNING_EVENT			0x60
#define PSMI_61_INPUT_WARNING_EVENT			0x61
#define PSMI_62_STATUS									0x62
#define PSMI_24_FAN_COMMAND_1						0x24
#define PSMI_25_FAN_COMMAND_2 					0x25

/***/

#define PMBUS_CFG_I2C_DEFAULT_VAL     I2CPRT_CFG_I2C_DEFAULT_VAL

/* Standard PMBus commands */
#define PMB_00_PAGE                     0x00
#define PMB_01_OPERATION                0x01
#define PMB_02_ON_OFF_CONFIG            0x02
#define PMB_03_CLEAR_FAULTS             0x03
#define PMB_05_PAGE_PLUS_WRITE          0x05
#define PMB_06_PAGE_PLUS_READ           0x06
/* 0x07 ~ 0x0F    Reserved */

#define PMB_10_WRITE_PROTECT            0x10
#define PMB_11_STORE_DEFAULT_ALL        0x11
#define PMB_12_RESTORE_DEFAULT_ALL      0x12
#define PMB_13_STORE_DEFAULT_CODE       0x13
#define PMB_14_RESTORE_DEFAULT_CODE     0x14
#define PMB_15_STORE_USER_ALL           0x15
#define PMB_16_RESTORE_USER_ALL         0x16
#define PMB_17_STORE_USER_CODE          0x17
#define PMB_18_RESTORE_USER_CODE        0x18
#define PMB_19_CAPABILITY               0x19
#define PMB_1A_QUERY                    0x1A
#define PMB_1B_SMBALERT_MASK            0x1B

#define PMB_20_VOUT_MODE                0x20
#define PMB_21_VOUT_COMMAND             0x21

#define PMB_30_COEFFICIENTS             0x30
#define PMB_3A_FAN_CONFIG_1_2           0x3A
#define PMB_3B_FAN_COMMAND_1            0x3B
#define PMB_3C_FAN_COMMAND_2            0x3C
#define PMB_3D_FAN_CONFIG_3_4           0x3D
#define PMB_3E_FAN_COMMAND_3            0x3E
#define PMB_3F_FAN_COMMAND_4            0x3F

#define PMB_40_VOUT_OV_FAULT_LIMIT      0x40
#define PMB_41_VOUT_OV_FAULT_RESPONSE   0x41
#define PMB_42_VOUT_OV_WARN_LIMIT       0x42
#define PMB_43_VOUT_UV_WARN_LIMIT       0x43
#define PMB_44_VOUT_UV_FAULT_LIMIT      0x44
#define PMB_45_VOUT_UV_FAULT_RESPONSE   0x45
#define PMB_46_IOUT_OC_FAULT_LIMIT      0x46
#define PMB_47_IOUT_OC_FAULT_RESPONSE   0x47
#define PMB_4A_IOUT_OC_WARN_LIMIT       0x4A
#define PMB_4F_OT_FAULT_LIMIT           0x4F

#define PMB_50_OT_FAULT_RESPONSE        0x50
#define PMB_51_OT_WARN_LIMIT            0x51
#define PMB_55_VIN_OV_FAULT_LIMIT       0x55
#define PMB_56_VIN_OV_FAULT_RESPONSE    0x56
#define PMB_57_VIN_OV_WARN_LIMIT        0x57
#define PMB_58_VIN_UV_WARN_LIMIT        0x58
#define PMB_59_VIN_UV_FAULT_LIMIT       0x59
#define PMB_5A_VIN_UV_FAULT_RESPONSE    0x5A
#define PMB_5D_IIN_OC_WARN_LIMIT        0x5D
#define PMB_5E_POWER_GOOD_ON            0x5E
#define PMB_5F_POWER_GOOD_OFF           0x5F

#define PMB_68_POUT_OP_FAULT_LIMIT      0x68
#define PMB_69_POUT_OP_FAULT_RESPONSE   0x69
#define PMB_6A_POUT_OP_WARN_LIMIT       0x6A
#define PMB_6B_PIN_OP_WARN_LIMIT        0x6B

#define PMB_72_TEST_INP_ORG_A           0x72
#define PMB_73_TEST_INP_ORG_B           0x73
#define PMB_74_TEST_OUT_ORG             0x74
#define PMB_78_STATUS_BYTE              0x78
#define PMB_79_STATUS_WORD              0x79
#define PMB_7A_STATUS_VOUT              0x7A
#define PMB_7B_STATUS_IOUT              0x7B
#define PMB_7C_STATUS_INPUT             0x7C
#define PMB_7D_STATUS_TEMPERATURE       0x7D
#define PMB_7E_STATUS_CML               0x7E
#define PMB_7F_STATUS_OTHER             0x7F

#define PMB_80_STATUS_MFR_SPECIFIC      0x80
#define PMB_81_STATUS_FANS_1_2          0x81
#define PMB_82_STATUS_FANS_3_4          0x82
#define PMB_86_READ_EIN                 0x86
#define PMB_87_READ_EOUT                0x87
#define PMB_88_READ_VIN                 0x88
#define PMB_89_READ_IIN                 0x89
#define PMB_8A_READ_VCAP                0x8A
#define PMB_8B_READ_VOUT                0x8B
#define PMB_8C_READ_IOUT                0x8C
#define PMB_8D_READ_TEMPERATURE_1       0x8D    /* AMB ILT */
#define PMB_8E_READ_TEMPERATURE_2       0x8E    /* Sec Hotspot */
#define PMB_8F_READ_TEMPERATURE_3       0x8F    /* Pri Hotspot */

#define PMB_90_READ_FAN_SPEED_1         0x90
#define PMB_91_READ_FAN_SPEED_2         0x91
#define PMB_92_READ_FAN_SPEED_3         0x92
#define PMB_93_READ_FAN_SPEED_4         0x93

#define PMB_96_READ_POUT                0x96
#define PMB_97_READ_PIN                 0x97
#define PMB_98_PMBUS_REVISION           0x98
#define PMB_99_MFR_ID                   0x99
#define PMB_9A_MFR_MODEL                0x9A
#define PMB_9B_MFR_REVISION             0x9B
#define PMB_9C_MFR_LOCATION             0x9C
#define PMB_9D_MFR_DATE                 0x9D
#define PMB_9E_MFR_SERIAL               0x9E
#define PMB_9F_APP_PROFILE_SUPPORT      0x9F
#define PMB_A0_MFR_VIN_MIN              0xA0
#define PMB_A1_MFR_VIN_MAX              0xA1
#define PMB_A2_MFR_IIN_MAX              0xA2
#define PMB_A3_MFR_PIN_MAX              0xA3
#define PMB_A4_MFR_VOUT_MIN             0xA4
#define PMB_A5_MFR_VOUT_MAX             0xA5
#define PMB_A6_MFR_IOUT_MAX             0xA6
#define PMB_A7_MFR_POUT_MAX             0xA7
#define PMB_A8_MFR_TAMBIENT_MAX         0xA8
#define PMB_A9_MFR_TAMBIENT_MIN         0xA9
#define PMB_AA_EFFICIENCY_LL            0xAA
#define PMB_AB_EFFICIENCY_HL            0xAB

#define PMB_C0_MFR_MAX_TEMP_1           0xC0
#define PMB_C1_MFR_MAX_TEMP_2           0xC1
#define PMB_C2_MFR_MAX_TEMP_3           0xC2


/* Internal PMBus commands DELTA */
#define PMB_C3_TRIM_VOUT                0xC3
#define PMB_C4_OVP_TEST_VOUT            0xC4
#define PMB_C5_CURR_SHARE               0xC5
#define PMB_C6_NTC_TEST                 0xC6
#define PMB_C7_OCP_TEST                 0xC7
#define PMB_C9_CALIBRATION              0xC9
#define PMB_CA_ISHARE_CALIBRATION       0xCA
#define PMB_CB_READ_TEST_REVISION       0xCB
#define PMB_CC_READ_BL_REVISION         0xCC
#define PMB_CD_TIME_CLEAR               0xCD
#define PMB_CE_AC_CURR_SAVE_FLG         0xCE
#define PMB_CF_ORING_TEST               0xCF
#define PMB_CMD_DELTA_INT_STR           PMB_C3_TRIM_VOUT
#define PMB_CMD_DELTA_INT_END           PMB_CF_ORING_TEST

#define PMB_F5_DEBUG_REG                0xF5
#define PMB_F6_UNLOCK_DEBUG             0xF6

/* used for internal debug, and need lock */
#define PMBUS_ADR_PRIM_STATUS00         0xD0  /* No change  */
#define PMBUS_ADR_PRIM_STATUS01         0xD1  /* No change  */
#define PMBUS_ADR_SEC_FLAG0             0xD2  /* No change  */
#define PMBUS_ADR_SEC_FLAG1             0xD3  /* No change  */
#define PMBUS_ADR_SEC_FLAG2             0xD4  /* No change  */
#define PMBUS_ADR_SEC_V1_VOL_EXT        0xD5  /* No change  */
#define PMBUS_ADR_PRIM_FW_REV_DEBUG     0xD6  /* No change  */
#define PMB_D8_MFR_LINE_STATUS          0xD8  /* No change  */

#define PMBUS_ADR_SEC_AVAILABLE_POWER   0xD7  /* Add by Hulk 20180515 */

#define PMB_E5_MFR_POS_TOTAL            0xE5  /* the Total Power On Seconds */
#define PMB_E6_MFR_POS_LAST             0xE6  /* the last total Power On Seconds */
#define PMBUS_ADR_ADJUST_VSB_VOL_GAIN   0xE9  /* No change */
#define PMBUS_ADR_ADJUST_V1_VOL_GAIN    0xEA  /* No change */
#define PMBUS_ADR_ADJUST_V1_CUR_GAIN    0xEB  /* No change */
#define PMBUS_ADR_ADJUST_V1_CUR_OFFSET  0xEC  /* No change */
#define PMBUS_ADR_VSB_OVP_TRIM          0xED  /* No change */
#define PMBUS_ADR_CALIBRATION_DATA      0xEE  /* No change */

/*
 * Non-Standard PMBus commands
 */
#define PMB_DC_MFR_BLACK_BOX            0xDC
#define PMB_DD_MFR_REAL_TIME_BLACK_BOX  0xDD
#define PMB_DE_MFR_SYSTEM_BLCAKBOX      0xDE
#define PMB_DF_MFR_BLCAKBOX_CONFIG      0xDF
#define PMB_E0_MFR_CLEAR_BLACKBOX       0xE0


#define PMB_E1_READ_BOOT_FW_REVISION    0xE1  /* before BOOT_SET_FLAG  */
#define PMB_E2_READ_APP_FW_REVISION     0xE2  /* before BOOT_SET_FLAG  */
#define PMB_E3_READ_HOURS_USED          0xE3  /* Changed from FB to E3  */
#define PMB_EB_READ_APP_FW_DUG_REV      0xEB

#define PMB_F0_UNLOCK_FW_UPGRADE_MODE   0xF0
#define PMB_F1_SET_BOOT_FLAG            0xF1

#define PMB_FA_MFR_FUNCTION_CTRL        0xFA

/* PMBus command code */
#define PMB_01_OPERATION_ON             0x80
#define PMB_01_OPERATION_OFF            0x00

#define PMB_E1_EEPROM_ENABLE            0x01
#define PMB_E1_EEPROM_DISABLE           0x00

#define PMB_E6_WRITE_FLT_ENABLE         0x01
#define PMB_E6_WRITE_FLT_DISABLE        0x00

#define PMB_98_VERSION                  0x22

#define PMB_DATA_00_AUX_MODE            0x00

#define PMBUS_PARA_3A_FAN_CFG_1_2       0x99
#define PMBUS_PARA_3D_FAN_CFG_3_4       0x00

#define PMBUS_TEMPERATURE_0_LB          0x40
#define PMBUS_TEMPERATURE_0_HB          0x00
#define PMBUS_TEMPERATURE_0_C           0x40

/* PMBus Format Setting */
#define EXP_N_MINUS_0               0x00       /*  N = 32 - 32 = 0 */
#define EXP_N_MINUS_1               0x1F       /*  N = 31 - 32 = -1 */
#define EXP_N_MINUS_2               0x1E       /*  N = 30 - 32 = -2 */
#define EXP_N_MINUS_3               0x1D       /*  N = 29 - 32 = -3 */
#define EXP_N_MINUS_4               0x1C       /*  N = 28 - 32 = -4 */
#define EXP_N_MINUS_5               0x1B       /*  N = 27 - 32 = -5 */
#define EXP_N_MINUS_6               0x1A       /*  N = 26 - 32 = -6 */
#define EXP_N_MINUS_7               0x19       /*  N = 25 - 32 = -7 */
#define EXP_N_MINUS_8               0x18       /*  N = 24 - 32 = -8 */
#define EXP_N_MINUS_9               0x17       /*  N = 23 - 32 = -9 */
#define EXP_N_MINUS_10              0x16       /*  N = 22 - 32 = -10 */
#define EXP_N_MINUS_11              0x15       /*  N = 21 - 32 = -11 */

#define MODE_FACTOR_1               0x00       /*  N = 32 - 32 = 0 */
#define MODE_FACTOR_2               0x1F       /*  N = 31 - 32 = -1 */
#define MODE_FACTOR_4               0x1E       /*  N = 30 - 32 = -2 */
#define MODE_FACTOR_8               0x1D       /*  N = 29 - 32 = -3 */
#define MODE_FACTOR_16              0x1C       /*  N = 28 - 32 = -4 */
#define MODE_FACTOR_32              0x1B       /*  N = 27 - 32 = -5 */
#define MODE_FACTOR_64              0x1A       /*  N = 26 - 32 = -6 */
#define MODE_FACTOR_128             0x19       /*  N = 25 - 32 = -7 */
#define MODE_FACTOR_256             0x18       /*  N = 24 - 32 = -8 */
#define MODE_FACTOR_512             0x17       /*  N = 23 - 32 = -9 */
#define MODE_FACTOR_1024            0x16       /*  N = 22 - 32 = -10 */
#define MODE_FACTOR_2048            0x15       /*  N = 21 - 32 = -11 */

#define SCALE_MN15                  0x8800     /* N=-15 */
#define SCALE_MN14                  0x9000     /* N=-14 */
#define SCALE_MN13                  0x9800     /* N=-13 */
#define SCALE_MN12                  0xA000     /* N=-12 */
#define SCALE_MN11                  0xA800     /* N=-11 */
#define SCALE_MN10                  0xB000     /* N=-10 */
#define SCALE_MN9                   0xB800     /* N=-9 */
#define SCALE_MN8                   0xC000     /* N=-8 */
#define SCALE_MN7                   0xC800     /* N=-7 */
#define SCALE_MN6                   0xD000     /* N=-6 */
#define SCALE_MN5                   0xD800     /* N=-5 */
#define SCALE_MN4                   0xE000     /* N=-4 */
#define SCALE_MN3                   0xE800     /* N=-3 */
#define SCALE_MN2                   0xF000     /* N=-2 */
#define SCALE_MN1                   0xF800     /* N=-1 */
#define SCALE_N0                    0x0000     /* N=0 */
#define SCALE_N1                    0x0800     /* N=1 */
#define SCALE_N2                    0x1000     /* N=2 */
#define SCALE_N3                    0x1800     /* N=3 */
#define SCALE_N4                    0x2000     /* N=4 */
#define SCALE_N5                    0x2800     /* N=5 */
#define SCALE_N6                    0x3000     /* N=6 */
#define SCALE_N7                    0x3800     /* N=7 */
#define SCALE_N8                    0x4000     /* N=8 */
#define SCALE_N9                    0x4800     /* N=9 */
#define SCALE_N10                   0x5000     /* N=10 */
#define SCALE_N11                   0x5800     /* N=11 */
#define SCALE_N12                   0x6000     /* N=12 */
#define SCALE_N13                   0x6800     /* N=13 */
#define SCALE_N14                   0x7000     /* N=14 */
#define SCALE_N15                   0x7800     /* N=15 */

#define N0_LIMIT                    1023       /* (2^0 * (2^10-1)) */
#define N1_LIMIT                    2046       /* (2^1 * (2^10-1)) */
#define N2_LIMIT                    4092       /* (2^2 * (2^10-1)) */
#define N3_LIMIT                    8184       /* (2^3 * (2^10-1)) */
#define N4_LIMIT                    16368      /* (2^4 * (2^10-1)) */
#define N5_LIMIT                    32736      /* (2^5 * (2^10-1)) */
#define N6_LIMIT                    65472      /* (2^6 * (2^10-1)) */
#define N7_LIMIT                    130944     /* (2^7 * (2^10-1)) */
#define N8_LIMIT                    261888     /* (2^8 * (2^10-1)) */
#define N9_LIMIT                    523776     /* (2^9 * (2^10-1)) */
#define N10_LIMIT                   1047552    /* (2^10 * (2^10-1)) */
#define N11_LIMIT                   2095104    /* (2^11 * (2^10-1)) */
#define N12_LIMIT                   4190208    /* (2^12 * (2^10-1)) */
#define N13_LIMIT                   8380416    /* (2^13 * (2^10-1)) */
#define N14_LIMIT                   16760832   /* (2^14 * (2^10-1)) */
#define N15_LIMIT                   33521664   /* (2^15 * (2^10-1)) */

#define MAX_LINEAR_DATA_FORMAT_VAL   33521664  /* 1023*(2^15) */
#define MAX_DIRECT_DATA_FORMAT_VAL   32767     /* Ymax = 2^15 - 1, M = 1, B = 0, R = 0 */

/*******************************************************************************
 * PMBus Parameters Setting
 ******************************************************************************/
#define SUPPORT_100K                 0x00	   /* Support 100Kbps?no PEC, no ALERT#	 */
#define SUPPORT_PEC_100K             0x80	   /* Support 100Kbps?PEC?no ALERT#  */
#define SUPPORT_100K_ALERT           0x10	   /* Support 100Kbps?no PEC, with ALERT#  */
#define SUPPORT_PEC_100K_ALERT       0x90	   /* Support 100Kbps?PEC? with ALERT#	  */
#define SUPPORT_PEC_100K_COLD_REDUNT 0x81	   /* Support 100Kbps?PEC? no ALERT#, code redundancy */

#define SUPPORT_400K                 0x20	   /* Support 400Kbps?no PEC, no ALERT#	  */
#define SUPPORT_PEC_400K             0xA0	   /* Support 400Kbps?PEC?no ALERT#  */
#define SUPPORT_400K_ALERT           0x30	   /* Support 400Kbps?no PEC, with ALERT#  */
#define SUPPORT_PEC_400K_ALERT       0xB0	   /* Support 400Kbps?PEC? with ALERT#  */

#define FAN1_NOT_INST                0x00      /* Fan1 is not installed, default as duty control fan speed, 1 pulse per revolution  */
#define FAN1_INST_DUTY_CTRL_1_PULSE  0x80      /* Fan1 is installed, Using duty control fan speed, 1 pulse per revolution  */
#define FAN1_INST_DUTY_CTRL_2_PULSE  0x90      /* Fan1 is installed, Using duty control fan speed, 2 pulse per revolution  */
#define FAN1_INST_DUTY_CTRL_3_PULSE  0xA0      /* Fan1 is installed, Using duty control fan speed, 3 pulse per revolution  */
#define FAN1_INST_DUTY_CTRL_4_PULSE  0xB0      /* Fan1 is installed, Using duty control fan speed, 4 pulse per revolution  */
#define FAN1_INST_RPM_CTRL_1_PULSE   0xC0      /* Fan1 is installed, Using RPM control fan speed, 1 pulse per revolution  */
#define FAN1_INST_RPM_CTRL_2_PULSE   0xD0      /* Fan1 is installed, Using RPM control fan speed, 2 pulse per revolution  */
#define FAN1_INST_RPM_CTRL_3_PULSE   0xE0      /* Fan1 is installed, Using RPM control fan speed, 3 pulse per revolution  */
#define FAN1_INST_RPM_CTRL_4_PULSE   0xF0      /* Fan1 is installed, Using RPM control fan speed, 4 pulse per revolution  */

#define FAN2_NOT_INST                0x00      /* Fan2 is not installed, default as duty control fan speed, 1 pulse per revolution  */
#define FAN2_INST_DUTY_CTRL_1_PULSE  0x08      /* Fan2 is installed, Using duty control fan speed, 1 pulse per revolution */
#define FAN2_INST_DUTY_CTRL_2_PULSE  0x09      /* Fan2 is installed, Using duty control fan speed, 2 pulse per revolution */
#define FAN2_INST_DUTY_CTRL_3_PULSE  0x0A      /* Fan2 is installed, Using duty control fan speed, 3 pulse per revolution */
#define FAN2_INST_DUTY_CTRL_4_PULSE  0x0B      /* Fan2 is installed, Using duty control fan speed, 4 pulse per revolution */
#define FAN2_INST_RPM_CTRL_1_PULSE   0x0C      /* Fan2 is installed, Using RPM control fan speed, 1 pulse per revolution */
#define FAN2_INST_RPM_CTRL_2_PULSE   0x0D      /* Fan2 is installed, Using RPM control fan speed, 2 pulse per revolution */
#define FAN2_INST_RPM_CTRL_3_PULSE   0x0E      /* Fan2 is installed, Using RPM control fan speed, 3 pulse per revolution */
#define FAN2_INST_RPM_CTRL_4_PULSE   0x0F      /* Fan2 is installed, Using RPM control fan speed, 4 pulse per revolution */

#define PMBUS_PARA_FAN_CONFIG_1_2	  (	FAN1_INST_RPM_CTRL_2_PULSE | FAN2_NOT_INST )   /* 0xD0 */

#define PMBUS_REV_1p3		          0x33	   /* V1.3(2013-09-06)	*/
#define PMBUS_REV_1p2		          0x22     /* V1.2(2010-09-06) */
#define PMBUS_REV_1p1		          0x11	   /* V1.1(2007-02-05)	*/
#define PMBUS_REV_1p0		          0x00	   /* V1.0(2005-03-28) */
#define PMBUS_PARA_REVISION		    PMBUS_REV_1p2

#define PMBUS_VOUT_MODE_LINEAR    0x17	   /* Linear, N = 9 */
#define PMBUS_VOUT_MODE_VID       0x2D	   /* VID */
#define PMBUS_VOUT_MODE_DIRECT    0x40	   /* Linear */

#define PMBUS_WR_PRT_80		          0x80     /* Disable all writes except to the WRITE_PROTECT command */
#define PMBUS_WR_PRT_40		          0x40     /* Disable all writes except to the WRITE_PROTECT, OPERATION and PAGE commands */
#define PMBUS_WR_PRT_20		          0x20     /* Disable all writes except to the WRITE_PROTECT, OPERATION, PAGE, ON_OFF_CONFIG and VOUT_COMMAND commands */
#define PMBUS_WR_PRT_00		          0x00     /* Enable writes to all commands. (Default) */
#define WRITE_PROTECT_DEFAULT		  PMBUS_WR_PRT_00

/* PMBUS_ADR_COEFFICIENTS_MBR */
#define COEFF_M_EIN_EOUT_LB           0x01     /* m, the slope coefficient, is a two byte, two?s complement integer */
#define COEFF_M_EIN_EOUT_HB           0x00
#define COEFF_B_EIN_EOUT_LB           0x00     /* b, the offset, is a two byte, two?s complement integer */
#define COEFF_B_EIN_EOUT_HB           0x00
#define COEFF_R_EIN_EOUT              0x00     /* R, the exponent, is a one byte, two?s complement integer */
#define COEFF_BYTE_COUNT_5            0x05     /* Block count=5 Byte */

///* Controller ID Definition */
//#define	PRI_uC_A                      (0x10U)
//#define	PRI_uC_B                      (0x11U)
//#define	SEC_uC_A                      (0x20U)
//#define	SEC_uC_B                      (0x21U)
//#define	COM_uC_S                      (0x30U)
//#define	PRI_uC_ALL                    (0x1FU)
//#define	SEC_uC_ALL                    (0x2FU)

/* Boot Loader Setting */
#define BOOT_CLR_STATUS               ((uint8)0x00U)
#define FW_UPDATE_RESET               ((uint8)0x01U)
#define BOOT_SEC_MCU                  ((uint8)0x02U)
#define PSU_REBOOT                    ((uint8)0x03U)
#define BOOT_PRI_MCU                  ((uint8)0x04U)

#define BOOT_FLAG_SET_PRI             ((uint8)0x10U)
#define BOOT_FLAG_SET_SEC             ((uint8)0x20U)

/* CR mode defination */
#define U8_CR_NORMAL_MODE             ((uint8)0x00)
#define U8_CR_ACTIVE_MODE             ((uint8)0x01)
#define U8_CR_STANDBY_MODE            ((uint8)0x02)
#if 0
#define U8_CR_MASTER_MODE             ((uint8)0x03)
#define U8_CR_SLAVE2_MODE             ((uint8)0x04)
#define U8_CR_SLAVE3_MODE             ((uint8)0x05)
#define U8_CR_SLAVE4_MODE             ((uint8)0x06)
#endif

#define U8_CR_PSUUNITS_01             ((uint8)0x01)
#define U8_CR_PSUUNITS_02             ((uint8)0x02)
#define U8_CR_PSUUNITS_03             ((uint8)0x03)
#define U8_CR_PSUUNITS_04             ((uint8)0x04)

/* Fault limit data */
#define V1_VOUT_OV_FAULT_LIMIT           (uint16)(60.0 * 512)                     /* 60.0V in Linear format */
#define V1_IOUT_OC_FAULT_LIMIT_HL        (uint16)((uint16)(88.9 * 2) + SCALE_MN1) /* 84.5A in Linear Data format */
#define V1_IOUT_OC_FAULT_LIMIT_LL        (uint16)((uint16)(73.0 * 2) + SCALE_MN1) /* 69.0A in Linear Data format */
#define V1_IOUT_OC_WARN_LIMIT_HL         (uint16)((uint16)(77.8 * 2) + SCALE_MN1) /* 74.0A in Linear Data format */
#define V1_IOUT_OC_WARN_LIMIT_LL         (uint16)((uint16)(73.0 * 2) + SCALE_MN1) /* 69.0A in Linear Data format */
#define V1_IOUT_OT_FAULT_LIMIT           (uint16)(70)                             /* 55 in Linear Data format */
#define V1_IOUT_OT_WARN_LIMIT            (uint16)(65)                             /* 45 in Linear Data format */

#define VSB_VOUT_OV_FAULT_LIMIT          (uint16)(13.9 * 512)                     /* 13.9V in Linear format */
#define VSB_IOUT_OC_FAULT_LIMIT_HL       (uint16)((uint16)(3.60 * 2) + SCALE_MN1) /* 3.6A in Linear Data format */
#define VSB_IOUT_OC_FAULT_LIMIT_LL       (uint16)((uint16)(3.00 * 2) + SCALE_MN1) /* 3.0A in Linear Data format */
#define VSB_IOUT_OC_WARN_LIMIT_HL        (uint16)((uint16)(3.20 * 2) + SCALE_MN1) /* 3.2A in Linear Data format */
#define VSB_IOUT_OC_WARN_LIMIT_LL        (uint16)((uint16)(3.00 * 2) + SCALE_MN1) /* 3.0A in Linear Data format */
#define VSB_IOUT_OT_FAULT_LIMIT          (uint16)(55)                             /* 55 in Linear Data format */
#define VSB_IOUT_OT_WARN_LIMIT           (uint16)(45)                             /* 45 in Linear Data format */

#define VIN_OV_FAULT_LIMIT_AC            (uint16)((uint16)(310  * 2) + SCALE_MN1) /* 310V in Linear Data format */
#define VIN_OV_FAULT_LIMIT_DC            (uint16)((uint16)(410  * 2) + SCALE_MN1) /* 410V in Linear Data format */
#define VIN_UV_FAULT_LIMIT_AC            (uint16)((uint16)(80   * 2) + SCALE_MN1) /* 80V in Linear Data format */
#define VIN_UV_FAULT_LIMIT_DC            (uint16)((uint16)(182  * 2) + SCALE_MN1) /* 182V in Linear Data format */

/* MFR Data */
#define MFR_VIN_AC_MIN                   (uint16)((uint16)(90.0 * 2) + SCALE_MN1) /* 90V    AC in Linear Data format */
#define MFR_VIN_DC_MIN                   (uint16)((uint16)(190.0 * 2) + SCALE_MN1) /* 190V  DC in Linear Data format */
#define MFR_VIN_AC_MAX                   (uint16)((uint16)(264  * 2) + SCALE_MN1) /* 264V   AC in Linear Data format */
#define MFR_VIN_DC_MAX                   (uint16)((uint16)(400  * 2) + SCALE_MN1) /* 400V   DC in Linear Data format */
#define MFR_IIN_AC_MAX                   (uint16)((uint16)(23.0 * 4) + SCALE_MN2) /* 22A  AC in Linear Data format */
//#define MFR_PIN_LL_MAX                   (0x02BC + SCALE_N1)                      /* 1400W in LL,  in Linear Data format */
#define MFR_PIN_HL_MAX                   (uint16)((uint16)(4000 / 8) + SCALE_N3)  /* 4400W in HL,  in Linear Data format */
#define MFR_V1OUT_MIN                    (uint16)(53.35 * 512)                    /* 53.35V in Linear format */
#define MFR_V1OUT_MAX                    (uint16)(55.62 * 512)                    /* 55.62V in Linear format */
//#define MFR_I1OUT_LL_MAX                 (0x00C8 + SCALE_MN1)                     /* 100A in Linear Data format */
#define MFR_I1OUT_HL_MAX                 (uint16)((uint16)(74.1 * 2) + SCALE_MN1) /* 70.4A in Linear Data format */
#define MFR_P1OUT_MAX                    (uint16)((uint16)(4000 / 4) + SCALE_N2)  /* 3800W in Linear Data format */
#define MFR_VOUT_VSB_MIN                 (uint16)(11.64 * 512)                    /* 11.4V in Linear Data format */
#define MFR_VOUT_VSB_MAX                 (uint16)(12.36 * 512)                    /* 12.6V in Linear Data format */
#define MFR_IOUT_VSB_MAX                 (uint16)((uint16)(3  * 4) + SCALE_MN2)   /* 3 A in Linear Data format */
#define MFR_POUT_VSB_MAX                 (uint16)((uint16)(36 * 2) + SCALE_MN1)   /* 36W in Linear Data format */
#define MFR_TAMBIENT_MAX                 (uint16)((uint16)(50 * 1) + SCALE_N0)    /* 50 Linear Data format */
#define MFR_TAMBIENT_MIN                 (uint16)((uint16)(0  * 1) + SCALE_N0)    /*  Linear Data format */
#define MFR_MAX_TEMP_1                   (uint16)(70)                             /* 70 C° Ambient */
#define MFR_MAX_TEMP_2                   (uint16)(125)                            /* 115 C° Hot Spot */
#define MFR_MAX_TEMP_3                   (uint16)(125)                            /* 115 C° Primary side Hot Spot */

/* MFR_EFFICIENCY_HL */
#define EFFICIENCY_HL_VIN               ((uint16)(230.0 * 2) + SCALE_MN1)     /* 230V   AC in Linear Data format */
#define EFFICIENCY_HL_VIN_LB            LOBYTE( EFFICIENCY_HL_VIN )
#define EFFICIENCY_HL_VIN_HB            HIBYTE( EFFICIENCY_HL_VIN )

#define EFFICIENCY_HL_L_POWER          ((uint16)(800.0 / 2) + SCALE_N1)       /* Power ,800W, low power efficiency */
#define EFFICIENCY_HL_L_POWER_LB       LOBYTE( EFFICIENCY_HL_L_POWER )
#define EFFICIENCY_HL_L_POWER_HB       HIBYTE( EFFICIENCY_HL_L_POWER )

#define EFFICIENCY_HL_L_EFFICY         ((uint16)(94.0 * 2) + SCALE_MN1)       /* The efficiency, 90%, at low power*/
#define EFFICIENCY_HL_L_EFFICY_LB      LOBYTE( EFFICIENCY_HL_L_EFFICY )
#define EFFICIENCY_HL_L_EFFICY_HB      HIBYTE( EFFICIENCY_HL_L_EFFICY )

#define EFFICIENCY_HL_M_POWER          ((uint16)(2000.0 / 4) + SCALE_N2)       /* Power,2000W, medium power efficiency */
#define EFFICIENCY_HL_M_POWER_LB       LOBYTE( EFFICIENCY_HL_M_POWER )
#define EFFICIENCY_HL_M_POWER_HB       HIBYTE( EFFICIENCY_HL_M_POWER )

#define EFFICIENCY_HL_M_EFFICY         ((uint16)(96.0 * 2) + SCALE_MN1)      /* The efficiency, 94%, at medium power*/
#define EFFICIENCY_HL_M_EFFICY_LB      LOBYTE( EFFICIENCY_HL_M_EFFICY )
#define EFFICIENCY_HL_M_EFFICY_HB      HIBYTE( EFFICIENCY_HL_M_EFFICY )

#define EFFICIENCY_HL_H_POWER          ((uint16)(4000.0 / 8) + SCALE_N3)       /* Power,4000W, high power efficiency */
#define EFFICIENCY_HL_H_POWER_LB       LOBYTE( EFFICIENCY_HL_H_POWER )
#define EFFICIENCY_HL_H_POWER_HB       HIBYTE( EFFICIENCY_HL_H_POWER )

#define EFFICIENCY_HL_H_EFFICY         ((uint16)(94.0 * 2) + SCALE_MN1)      /* The efficiency, 91%, at high power*/
#define EFFICIENCY_HL_H_EFFICY_LB      LOBYTE( EFFICIENCY_HL_H_EFFICY )
#define EFFICIENCY_HL_H_EFFICY_HB      HIBYTE( EFFICIENCY_HL_H_EFFICY )

/* MFR_EFFICIENCY_LL */
#define EFFICIENCY_LL_VIN             ((uint16)(115.0 * 2) + SCALE_MN1)       /* 115V   AC in Linear Data format */
#define EFFICIENCY_LL_VIN_LB          LOBYTE( EFFICIENCY_LL_VIN )
#define EFFICIENCY_LL_VIN_HB          HIBYTE( EFFICIENCY_LL_VIN )

#define EFFICIENCY_LL_L_POWER          ((uint16)(400.0 / 1) + SCALE_N0)       /* Power ,400W, low power efficiency */
#define EFFICIENCY_LL_L_POWER_LB       LOBYTE( EFFICIENCY_LL_L_POWER )
#define EFFICIENCY_LL_L_POWER_HB       HIBYTE( EFFICIENCY_LL_L_POWER )

#define EFFICIENCY_LL_L_EFFICY         ((uint16)(90.0 * 2) + SCALE_MN1)       /* The efficiency, 90%, at low power*/
#define EFFICIENCY_LL_L_EFFICY_LB      LOBYTE( EFFICIENCY_LL_L_EFFICY )
#define EFFICIENCY_LL_L_EFFICY_HB      HIBYTE( EFFICIENCY_LL_L_EFFICY )

#define EFFICIENCY_LL_M_POWER          ((uint16)(1000.0 / 2) + SCALE_N1)       /* Power,1000W, medium power efficiency */
#define EFFICIENCY_LL_M_POWER_LB       LOBYTE( EFFICIENCY_LL_M_POWER )
#define EFFICIENCY_LL_M_POWER_HB       HIBYTE( EFFICIENCY_LL_M_POWER )

#define EFFICIENCY_LL_M_EFFICY         ((uint16)(94.0 * 2) + SCALE_MN1)      /* The efficiency, 94%, at medium power*/
#define EFFICIENCY_LL_M_EFFICY_LB      LOBYTE( EFFICIENCY_LL_M_EFFICY )
#define EFFICIENCY_LL_M_EFFICY_HB      HIBYTE( EFFICIENCY_LL_M_EFFICY )

#define EFFICIENCY_LL_H_POWER          ((uint16)(2000.0 / 4) + SCALE_N2)       /* Power,2000W, high power efficiency */
#define EFFICIENCY_LL_H_POWER_LB       LOBYTE( EFFICIENCY_LL_H_POWER )
#define EFFICIENCY_LL_H_POWER_HB       HIBYTE( EFFICIENCY_LL_H_POWER )

#define EFFICIENCY_LL_H_EFFICY         ((uint16)(91.0 * 2) + SCALE_MN1)      /* The efficiency, 91%, at high power*/
#define EFFICIENCY_LL_H_EFFICY_LB      LOBYTE( EFFICIENCY_LL_H_EFFICY )
#define EFFICIENCY_LL_H_EFFICY_HB      HIBYTE( EFFICIENCY_LL_H_EFFICY )

#define PMB_CMD_DELTA_INT_STR          PMB_C3_TRIM_VOUT
#define PMB_CMD_DELTA_INT_END          PMB_CF_ORING_TEST
/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/


/*******************************************************************************
 * Global data
 ******************************************************************************/


#ifdef __cplusplus
}
#endif
#endif  /* PMBUS_CFG_H */


/*
 * End of file
 */
