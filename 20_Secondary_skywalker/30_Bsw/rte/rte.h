/** *****************************************************************************
 * \file    rte.h
 * \brief   Global interface for rte.c
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

#ifndef RTE_H
#define RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

#if defined(RTE_EXPORT_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/* Status bits */
#define RTE_B_LLC_COM_HALT            RTE_uLlcStatus00.Bits.f0    /* 1 = LLC controlled by com */
#define RTE_B_LLC_EN                  RTE_uLlcStatus00.Bits.f1    /* 1 = LLC enabled */
#define RTE_B_LLC_CURR_LIMIT          RTE_uLlcStatus00.Bits.f2    /* 1 = Current limit mode active */
#define RTE_B_LLC_SOFT_START          RTE_uLlcStatus00.Bits.f3    /* 1 = Soft start active */
#define RTE_B_LLC_ISHARE_EN           RTE_uLlcStatus00.Bits.f4    /* 1 = Active current share enabled */
#define RTE_B_PRIM_VIN_LOST           RTE_uLlcStatus00.Bits.f6    /* 1 = Primary side input voltage lost */
#define RTE_B_PRIM_VIN_LINE           RTE_uLlcStatus00.Bits.f7    /* 1 = Primary side input voltage line: 1 = Vin high line; 0 = Vin low line */
#define RTE_B_LLC_STANDBY             RTE_uLlcStatus00.Bits.f8    /* 1 = LLC in stand-by mode */
#define RTE_B_LLC_SYNC_START_UP       RTE_uLlcStatus00.Bits.f9    /* 1 = Synced start-up */
#define RTE_B_OT_DISABLED             RTE_uLlcStatus00.Bits.fc    /* 1 = Disabled OT judgement */
#define RTE_B_LLC_OVP_TEST            RTE_uLlcStatus00.Bits.fd    /* 1 = Over voltage protection test */
#define RTE_B_BL_MODE                 RTE_uLlcStatus00.Bits.fe    /* 1 = Boot loader mode */
#define RTE_B_BL_EXIST                RTE_uLlcStatus00.Bits.ff    /* 1 = Boot loader is existing */
/* Fault status bits */
#define RTE_B_LLC_OVP                 RTE_uLlcStatus01.Bits.f0    /* 1 = LLC over voltage */
#define RTE_B_LLC_OVW                 RTE_uLlcStatus01.Bits.f1    /* 1 = LLC over voltage warning */
#define RTE_B_LLC_UVP                 RTE_uLlcStatus01.Bits.f2    /* 1 = LLC under voltage */
#define RTE_B_LLC_UVW                 RTE_uLlcStatus01.Bits.f3    /* 1 = LLC under voltage warning */
#define RTE_B_LLC_OCP                 RTE_uLlcStatus01.Bits.f4    /* 1 = LLC over current */
#define RTE_B_LLC_OCW                 RTE_uLlcStatus01.Bits.f5    /* 1 = LLC over current warning */
#define RTE_B_LLC_OCP_CT              RTE_uLlcStatus01.Bits.f8    /* 1 = LLC CT over current */
#define RTE_B_LLC_OPP                 RTE_uLlcStatus01.Bits.f9    /* 1 = LLC stage over power */
#define RTE_B_LLC_FAN_FAIL_1          RTE_uLlcStatus01.Bits.fa    /* 1 = Fan 1 fail */
#define RTE_B_LLC_FAN_FAIL_2          RTE_uLlcStatus01.Bits.fb    /* 1 = Fan 2 fail */
#define RTE_B_LLC_FAN_SPD_LOW_1       RTE_uLlcStatus01.Bits.fc    /* 1 = Fan 1 low speed */
#define RTE_B_LLC_FAN_SPD_LOW_2       RTE_uLlcStatus01.Bits.fd    /* 1 = Fan 2 low speed */
#define RTE_B_PSU_OT                  RTE_uLlcStatus01.Bits.fe    /* 1 = LLC over temperature */
/* Fault status clear bits */
#define RTE_B_LLC_FAULT_CLR           RTE_uLlcStatus02.Bits.f0    /* 1 = LLC fault clear */
#define RTE_B_LLC_OV_LATCH_CLR        RTE_uLlcStatus02.Bits.f1    /* 1 = LLC OVP latch clear */
#define RTE_B_LLC_UV_LATCH_CLR        RTE_uLlcStatus02.Bits.f2    /* 1 = LLC UVP latch clear */
#define RTE_B_LLC_OC_LATCH_CLR        RTE_uLlcStatus02.Bits.f3    /* 1 = LLC OCP latch clear */
#define RTE_B_LLC_OPP_LATCH_CLR       RTE_uLlcStatus02.Bits.f4    /* 1 = LLC OPP latch clear */
/* NTC temperature status */
#define RTE_B_NTC_1_OT                RTE_uTempStatus00.Bits.f0   /* 1 = PSU is over temperature */
#define RTE_B_NTC_1_OTW               RTE_uTempStatus00.Bits.f1   /* 1 = PFC stage over temperature */
#define RTE_B_NTC_2_OT                RTE_uTempStatus00.Bits.f2   /* 1 = PSU is over temperature */
#define RTE_B_NTC_2_OTW               RTE_uTempStatus00.Bits.f3   /* 1 = PFC stage over temperature */
#define RTE_B_NTC_3_OT                RTE_uTempStatus00.Bits.f4   /* 1 = PSU is over temperature */
#define RTE_B_NTC_3_OTW               RTE_uTempStatus00.Bits.f5   /* 1 = PFC stage over temperature */
#define RTE_B_NTC_4_OT                RTE_uTempStatus00.Bits.f6   /* 1 = PSU is over temperature */
#define RTE_B_NTC_4_OTW               RTE_uTempStatus00.Bits.f7   /* 1 = PFC stage over temperature */
/* Port bits */
#define RTE_B_PORT_PWM_ON             RTE_uLlcPort00.Bits.f0      /* 1 = LLC PWM on */
#define RTE_B_PORT_ISHARE_ON          RTE_uLlcPort00.Bits.f1      /* 1 = LLC active current share enabled */
#define RTE_B_PORT_OVP_CLR            RTE_uLlcPort00.Bits.f2      /* 1 = LLC over voltage clear */
#define RTE_B_PORT_BULK_OK            RTE_uLlcPort00.Bits.f3      /* 1 = Bulk OK port high */
#define RTE_B_PORT_OVP                RTE_uLlcPort00.Bits.f4      /* 1 = Output OVP port high */
#define RTE_B_PORT_LLC_SWITCH_EN      RTE_uLlcPort00.Bits.f5      /* 1 = LLC output enabled by switch */
#define RTE_B_PORT_LLC_HALT           RTE_uLlcPort00.Bits.f6      /* 1 = LLC HALT port high (controlled by com) */
#define RTE_B_PORT_ORING_EN           RTE_uLlcPort00.Bits.f8      /* 1 = Oring Enable */
#define RTE_B_PORT_LLC_FAULT          RTE_uLlcPort00.Bits.f9      /* 1 = LLC fault */
/* HRTIMER bits */
#define RTE_B_HRTIMER_PWM_A_ON        RTE_uLlcHrTimer00.Bits.f0   /* 1 = PWM A drive on */
#define RTE_B_HRTIMER_PWM_B_ON        RTE_uLlcHrTimer00.Bits.f1   /* 1 = PWM B drive on */
#define RTE_B_HRTIMER_PWM_C_ON        RTE_uLlcHrTimer00.Bits.f2   /* 1 = PWM D drive on */
#define RTE_B_HRTIMER_PWM_D_ON        RTE_uLlcHrTimer00.Bits.f3   /* 1 = PWM D drive on */
#define RTE_B_HRTIMER_PWM_E_ON        RTE_uLlcHrTimer00.Bits.f4   /* 1 = PWM E drive on */

/* Status data */
EXTERN GLOBAL_U_U16BIT RTE_uLlcStatus00;
EXTERN GLOBAL_U_U16BIT RTE_uLlcStatus01;
EXTERN GLOBAL_U_U16BIT RTE_uLlcStatus02;
EXTERN GLOBAL_U_U8BIT  RTE_uTempStatus00;
EXTERN GLOBAL_U_U16BIT RTE_uComStatus00;
EXTERN GLOBAL_U_U16BIT RTE_uLlcPort00;
EXTERN GLOBAL_U_U8BIT  RTE_uLlcHrTimer00;
/* HWIO data */
EXTERN uint16 RTE_u1610mVVoltOutExt;
EXTERN uint16 RTE_u1610mVVoltOutInt;
EXTERN uint16 RTE_u1610mACurrOut;
EXTERN uint16 RTE_u1610mACurrOutCali;
EXTERN uint16 RTE_u1610mAAcsBus;
EXTERN uint16 RTE_u1610mAAcsLocal;
EXTERN uint16 RTE_u161mVVoltRef3V3;
EXTERN uint16 RTE_u161OhmResNtc1Hwio;
EXTERN uint16 RTE_u161OhmResNtc2Hwio;
EXTERN uint16 RTE_u161OhmResNtc3Hwio;
EXTERN uint16 RTE_u161OhmResNtc4Hwio;
EXTERN uint16 RTE_u161mVVoltNtc1Hwio;
EXTERN uint16 RTE_u161mVVoltNtc2Hwio;
EXTERN uint16 RTE_u16q12VoltRefCaliFact;
/* Meter data */
EXTERN uint16 RTE_u1610mVVoltOutExtAvg;
EXTERN uint16 RTE_u1610mVVoltOutIntAvg;
EXTERN uint16 RTE_u1610mACurrOutAvg;
EXTERN uint16 RTE_u16100mWPwrOutAvg;
EXTERN uint16 RTE_u1610mVVoltOutExtAvgCom;
EXTERN uint16 RTE_u1610mVVoltOutIntAvgCom;
EXTERN uint16 RTE_u1610mACurrOutAvgCom;
EXTERN uint16 RTE_u16100mWPwrOutAvgCom;
/* TempCtrl data */
EXTERN uint16 RTE_u161OhmResNtc1Avg;
EXTERN uint16 RTE_u161OhmResNtc2Avg;
EXTERN uint16 RTE_u161OhmResNtc3Avg;
EXTERN uint16 RTE_u161OhmResNtc4Avg;
/* UART data */
EXTERN uint16 RTE_u16q12CalibVoltOutGain;
EXTERN uint16 RTE_u16q12CalibCurrOutGain;
EXTERN uint16 RTE_u16q12CalibIshareGain;
EXTERN sint16 RTE_s1610mACalibIshareOfs;
EXTERN uint16 RTE_u16100mHzVoltInFreq;
EXTERN sint16 RTE_s16CalibVoltOutAmp;
EXTERN sint16 RTE_s16CalibCurrOutAmp;
EXTERN sint16 RTE_s16CalibVoltOutOfs;
EXTERN sint16 RTE_s16CalibCurrOutOfs;
/* Active current share data */
EXTERN sint16 RTE_s1610mVMainVoltAdjCurrShare;
/* Debug data (can be used to report data to system) */
EXTERN uint16 RTE_u16DebugData0;
EXTERN uint16 RTE_u16DebugData1;
EXTERN uint16 RTE_u16DebugData2;
/* Bootloader firmware version */
EXTERN uint8 RTE_u8BlFwVerMajor;
EXTERN uint8 RTE_u8BlFwVerMinor;
EXTERN uint8 RTE_u8BlFwVerDebug;

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

EXTERN void RTE_vInit(void);
EXTERN void RTE_vDeInit(void);

#undef EXTERN


#ifdef __cplusplus
  }
#endif
#endif  /* RTE_H */

