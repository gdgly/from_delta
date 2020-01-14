/** *****************************************************************************
 * \file    llcctrl_conf.h
 * \brief   Configuration file for llcctrl.c
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

#ifndef LLCCTRL_CONF_H
#define LLCCTRL_CONF_H
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
#define MG_IIR_RIPPLE_FLT           1  /* 1 = 90-120Hz ripple cancellation filter */
#define MG_CURR_LIMIT_MODE          1  /* 1 = Constant current limit mode */
#define MG_PWM_CTRL_MODE            1  /* 1 = PWM mode instead of burst mode */
#define MG_CALIBRATE_VREF_IOUT      1  /* 1 = Calibrate the output voltage and current */
#define MG_OVER_LAOD_DROOP          1  /* 1 = Over load droop function implemented (increased droop when taking over load) */
#define MG_OCP_LATCH                1  /* 1 = CT OC latch */
#define MG_POSITONAL_INCREMENTAL_PI 1  /* 1 = Positional PI, 0 =  Incremental PI */
#define MG_VEXT_FBK_LOOP            1  /* 1 = Use Vext to do close loop, 0 =  Use Vint to do close loop */

/***********************************************
 * LoopStatus
 **********************************************/
#define MG_B_LLC_BM                 LLCCTRL_mg_uCtrlStatus.Bits.f0  /* 1 = LLC in burst mode operation */
#define MG_B_LLC_SOFT_START         LLCCTRL_mg_uCtrlStatus.Bits.f1  /* 1 = LLC in soft start mode */
#define MG_B_LLC_CURR_LIMIT_MODE    LLCCTRL_mg_uCtrlStatus.Bits.f2  /* 1 = LLC in constant current limit mode */
#define MG_B_LLC_PWM_MODE           LLCCTRL_mg_uCtrlStatus.Bits.f3  /* 1 = LLC in PWM mode */
#define MG_B_LLC_CT_OCP             LLCCTRL_mg_uCtrlStatus.Bits.f4  /* 1 = CT over current occured and triggered delayed protection */
#define MG_B_LLC_CT_OCP_TO_MON      LLCCTRL_mg_uCtrlStatus.Bits.f5  /* 1 = CT over current and report to monitor */
#define MG_B_LLC_BM_TIMEOUT         LLCCTRL_mg_uCtrlStatus.Bits.f6  /* 1 = LLC burst mode timeout occured */

/***********************************************
 * Measurements 
 **********************************************/
#define  MG_F32_K1_IOUT_FLT               0.5F  /* (100%) old value */
#define  MG_F32_K2_IOUT_FLT               0.5F  /* (100%) new value */

/* Vint to Vext transition voltage */
#define  MG_F32_VOLT_VINT_TO_VEXT_TRANS   4.0F  /* (V) voltage when transition takes place */

/***********************************************
 * Voltage control loop
 **********************************************/
/* Control parameters: soft start mode */
#define MG_F32_VOLT_SS_B0            1.133263F
#define MG_F32_VOLT_SS_B1           -0.941044F
#define MG_F32_VOLT_SS_B2            0.000000F
#define MG_F32_VOLT_SS_B3            0.000000F
#define MG_F32_VOLT_SS_A1            1.000000F
#define MG_F32_VOLT_SS_A2            0.000000F
#define MG_F32_VOLT_SS_A3            0.000000F

/* Control parameters: regular operation mode */
#if 0
#define MG_F32_VOLT_RO_0_B0          1.848150F
#define MG_F32_VOLT_RO_0_B1         -1.480333F
#define MG_F32_VOLT_RO_0_B2         -1.829850F
#define MG_F32_VOLT_RO_0_B3          1.498634F
#define MG_F32_VOLT_RO_0_A1          1.052857F
#define MG_F32_VOLT_RO_0_A2          0.854358F 
#define MG_F32_VOLT_RO_0_A3         -0.907215F
#endif
#if 0
#define MG_F32_VOLT_RO_0_B0          2.016164F
#define MG_F32_VOLT_RO_0_B1         -1.614909F
#define MG_F32_VOLT_RO_0_B2         -1.996200F
#define MG_F32_VOLT_RO_0_B3          1.634873F
#define MG_F32_VOLT_RO_0_A1          1.052857F
#define MG_F32_VOLT_RO_0_A2          0.854358F 
#define MG_F32_VOLT_RO_0_A3         -0.907215F
#endif
#if 0
#define MG_F32_VOLT_RO_0_B0          2.184177F
#define MG_F32_VOLT_RO_0_B1         -1.749485F
#define MG_F32_VOLT_RO_0_B2         -2.162549F
#define MG_F32_VOLT_RO_0_B3          1.771113F
#define MG_F32_VOLT_RO_0_A1          1.052857F
#define MG_F32_VOLT_RO_0_A2          0.854358F 
#define MG_F32_VOLT_RO_0_A3         -0.907215F
#endif
#if 1
#define MG_F32_VOLT_RO_0_B0          5.029079F
#define MG_F32_VOLT_RO_0_B1         -4.293651F
#define MG_F32_VOLT_RO_0_B2         -5.002460F
#define MG_F32_VOLT_RO_0_B3          4.320270F
#define MG_F32_VOLT_RO_0_A1          1.052857F
#define MG_F32_VOLT_RO_0_A2          0.854358F
#define MG_F32_VOLT_RO_0_A3         -0.907215F
#endif

/* Limitations */
#define MG_F32_MAX_V_ERR                  1.5F
#define MG_F32_MIN_V_ERR                 -1.5F
#define MG_F32_MAX_V_ERR_HC               0.9F

/***********************************************
 * Main output voltage
 **********************************************/
/* Droop control */
#define MG_F32_LLC_VOLT_OUT_ZERO_LOAD       54.50F  /* (V) Zero load voltage */
#define MG_F32_LLC_VOLT_OUT_MAX_LOAD        53.50F  /* (V) Max load voltage */
#define MG_F32_LLC_CURR_OUT_MAX_LOAD        74.07F  /* (A) Max load current */

#if MG_OVER_LAOD_DROOP
#define MG_F32_LLC_VOLT_OUT_OVERLOAD        52.50F  /* (V) Overload load voltage */
#define MG_F32_LLC_CURR_OUT_OVERLOAD       148.14F  /* (A) Overload load current */
#endif
#define MG_F32_LLC_CURR_LIMIT_ERR            80.0F  /* (A) Limit votlage error */

/* Soft start */
#define MG_F32_ISR_FREQUENCY              60000.0F  /* (Hz) Interrupt frequency (NOTE: for exact timing it has to match the real ISR frequency) */
#define MG_F32_SOFT_START_TIME_ZERO_LOAD    100.0F  /* (ms) Soft start time in millisecond */
#define MG_F32_SOFT_START_TIME_MAX_LOAD     250.0F  /* (ms) Soft start time in millisecond */

/* Vout over voltage protection point (no latch) */
#define MG_F32_LLC_VOLT_OUT_OVP              57.5F  /* (V) Over voltage */

/* OVP test */
#define MG_F32_VOUT_OVP_TEST_VREF            60.0F  /* (V) Over voltage test point */

/***********************************************
 * Main current
 **********************************************/
#define MG_F32_LLC_CURR_CT_OCP              60.00F  /* (A) Main transformer over current */

/***********************************************
 * Switchinng frequency
 **********************************************/
#define MG_LLC_FREQ_MAX                     320000  /* (Hz) */
#define MG_LLC_FREQ_MIN                      71000  /* (Hz) */

/* PWM mode frequencies */
#define MG_LLC_FREQ_PWM_SS                  300000  /* (Hz) Soft start frequency */
#define MG_LLC_FREQ_PWM                     150000  /* (Hz) Normal operation frequency */

/* Burst mode frequencies */
#define MG_LLC_FREQ_BURST                   275000  /* (Hz) Burst mode frequency */
#define MG_LLC_FREQ_BURST_IN                265000  /* (Hz) Enter burst mode frequency*/
#define MG_LLC_FREQ_FBURST                  320000  /* (Hz) Frequency burst mode frequency */
#define MG_LLC_FREQ_FBURST_IN               300000  /* (Hz) Enter frequency burst mode frequency*/

/* CT protection mode frequency */
#define MG_LLC_FREQ_CT_PEAK_OVP             145000  /* (Hz) */ 

/***********************************************
 * LLC and SR duty cycle and deatime control
 **********************************************/
/* Duty cycle */
#define MG_F32_MAX_DUTY_CYCLE                 0.5F  /* (100%) Note: do not increase above 0.5!!! */
#define MG_F32_MIN_DUTY_CYCLE                 0.0F  /* (100%) Note: do not reduce below 0.0!!! */

#define MG_PWM_LLC_DEAD_TIME_1                 200  /* (ns) LLC dead time at frequency 1; NOTE: negative values are not allowed!!! */
#define MG_PWM_LLC_DEAD_TIME_2                 160  /* (ns) LLC dead time at frequency 2; NOTE: negative values are not allowed!!! */
#define MG_PWM_LLC_DT_FREQ_1                200000  /* (Hz) Frequency 1 and limit for dead time adjustment */
#define MG_PWM_LLC_DT_FREQ_2                120000  /* (Hz) Frequency 2 and limit for dead time adjustment */

#define MG_PWM_SR_ON_DEAD_TIME_1               450  /* (ns) SR turn on dead time at frequency 1; NOTE: negative value will cause SR turn on earlier than primary side */
#define MG_PWM_SR_ON_DEAD_TIME_2                80  /* (ns) SR turn on dead time at frequency 2; NOTE: negative value will cause SR turn on earlier than primary side */
#define MG_PWM_SR_ON_DEAD_TIME_3                50  /* (ns) SR turn on dead time at frequency 3; NOTE: negative value will cause SR turn on earlier than primary side */
#define MG_PWM_SR_ON_DT_FREQ_1              300000  /* (Hz) Frequency 1 and limit for dead time adjustment */
#define MG_PWM_SR_ON_DT_FREQ_2              220000  /* (Hz) Frequency 2 and limit for dead time adjustment */
#define MG_PWM_SR_ON_DT_FREQ_3              115000  /* (Hz) Frequency 3 and limit for dead time adjustment */

#define MG_PWM_SR_OFF_DEAD_TIME_1              200  /* (ns) SR turn off dead time at frequency 1; NOTE: negative value will cause SR turn off later than primary side */
#define MG_PWM_SR_OFF_DEAD_TIME_2             2200  /* (ns) SR turn off dead time at frequency 2; NOTE: negative value will cause SR turn off later than primary side */
#define MG_PWM_SR_OFF_DEAD_TIME_3             3250  /* (ns) SR turn off dead time at frequency 3; NOTE: negative value will cause SR turn off later than primary side */
#define MG_PWM_SR_OFF_DT_FREQ_1             125000  /* (Hz) Frequency 1 and limit for dead time adjustment */
#define MG_PWM_SR_OFF_DT_FREQ_2              85000  /* (Hz) Frequency 2 */
#define MG_PWM_SR_OFF_DT_FREQ_3              71000  /* (Hz) Frequency 3 and limit for dead time adjustment */

#if MG_CURR_LIMIT_MODE
/***********************************************
 * Current limit mode
 **********************************************/
#define MG_F32_CURR_LIMIT_KP               0.4000F  /* KP parameter */
#define MG_F32_CURR_LIMIT_KI               0.0100F  /* KI parameter */

#define MG_F32_CC_IOUT_SS_LL                 80.0F  /* (A) Constant current soft start low line */
#define MG_F32_CC_IOUT_LL                    85.0F  /* (A) Constant current low line */

#define MG_F32_CC_IOUT_SS_HL                120.0F  /* (A) Constant current soft start high line */
#define MG_F32_CC_IOUT_HL                   160.0F  /* (A) Constant current high line */

#define MG_F32_CC_VOUT_ADJ_MAX                0.0F  /* (V) CC mode maximum added reference voltage; NOTE: Best keep this at zero */
#endif

#if MG_PWM_CTRL_MODE
/***********************************************
 * PWM control mode
 **********************************************/
#define MG_F32_PWM_CTRL_KP               100.0000F  /* KP parameter */
#define MG_F32_PWM_CTRL_KI                 4.0000F  /* KI parameter */
/* Limitations */
#define MG_F32_MAX_PWM_ERR                    5.0F
#define MG_F32_MIN_PWM_ERR                   -5.0F

#else
/***********************************************
 * Burst mode
 **********************************************/
#define MG_F32_CURR_BM_ON                     3.5F  /* (A) If current lower, then turn on burst mode */
#define MG_F32_CURR_BM_OFF                    4.0F  /* (A) If current higher, then turn off burst mode */

#define MG_F32_VOLT_BM_ERR_OFFSET             0.0F  /* (V) Reference error signal for burst mode voltage adjustment */
#define MG_F32_VOLT_BM_ADJ_MAX                0.1F  /* (V) Maximum output voltage adjustment of burst mode (Vref + adjust) */
#define MG_F32_VOLT_BM_ADJ_MIN                0.6F  /* (V) Minimum output voltage adjustment of burst mode (Vref - adjust) */
#define MG_U16_BM_TIMEOUT_VAL      ((uint16)1000U)  /* Number which has to be reached by counter to cause burst mode time out */
#define MG_U16_BM_TIMEOUT_RESET     ((uint16)100U)  /* Number which resets the burst mode time out counter */
#define MG_U16_BM_TIMEOUT_SET_1      ((uint16)10U)  /* Number which increments the burst mode time out counter at error 1 range */
#define MG_U16_BM_TIMEOUT_SET_2     ((uint16)200U)  /* Number which increments the burst mode time out counter at error 2 range */
#define MG_U16_BM_TIMEOUT_SET_3     ((uint16)300U)  /* Number which increments the burst mode time out counter at error 3 range */
#define MG_F32_BM_TIMEOUT_VOLT_ERR_1          0.0F  /* (V) Error 1 range (errors between error 1 and error 2) */
#define MG_F32_BM_TIMEOUT_VOLT_ERR_2          0.3F  /* (V) Error 2 range (errors between error 2 and error 3) */
#define MG_F32_BM_TIMEOUT_VOLT_ERR_3          0.5F  /* (V) Error 3 range (errors larger than error 3) */
#endif

#if MG_IIR_RIPPLE_FLT
/***********************************************
 * IIR ripple filter
 **********************************************/
#define MG_F32_IIR_FLT_GAIN                   3.0F  /* Gain of IIR ripple filter */
/* IIR ripple filter impact limitation */
#define MG_F32_IIR_IN_LIMIT                   0.5F  /* (V) Maximum input signal amplitude */
#define MG_F32_IIR_OUT_LIMIT                  0.5F  /* (V) Maximum output signal amplitude */
#endif


/*******************************************************************************
 * Scaling section
 ******************************************************************************/

#define MG_U16Q15_K1_IOUT_FLT               (uint16)U32Q15(MG_F32_K1_IOUT_FLT)
#define MG_U16Q15_K2_IOUT_FLT               (uint16)U32Q15(MG_F32_K2_IOUT_FLT)

#define MG_S16_10mV_MAX_VOUT_DIFF           (sint16)(MG_F32_VOLT_VINT_TO_VEXT_TRANS * F32_10_MILLI)
#define MG_U16Q15_VOUT_TRANS_FACT           (uint16)U32Q15(1.0F / (MG_F32_VOLT_VINT_TO_VEXT_TRANS * F32_10_MILLI))
#define MG_U16_10mV_LLC_VOLT_OUT_OVP        (uint16)(MG_F32_LLC_VOLT_OUT_OVP * F32_10_MILLI)

#define MG_S32Q24_VOLT_SS_B0                ((sint32)S32Q24(MG_F32_VOLT_SS_B0))
#define MG_S32Q24_VOLT_SS_B1                ((sint32)S32Q24(MG_F32_VOLT_SS_B1))
#define MG_S32Q24_VOLT_SS_B2                ((sint32)S32Q24(MG_F32_VOLT_SS_B2))
#define MG_S32Q24_VOLT_SS_B3                ((sint32)S32Q24(MG_F32_VOLT_SS_B3))
#define MG_S32Q24_VOLT_SS_A1                ((sint32)S32Q24(MG_F32_VOLT_SS_A1))
#define MG_S32Q24_VOLT_SS_A2                ((sint32)S32Q24(MG_F32_VOLT_SS_A2))
#define MG_S32Q24_VOLT_SS_A3                ((sint32)S32Q24(MG_F32_VOLT_SS_A3))

#define MG_S32Q24_VOLT_RO_0_B0              ((sint32)S32Q24(MG_F32_VOLT_RO_0_B0))
#define MG_S32Q24_VOLT_RO_0_B1              ((sint32)S32Q24(MG_F32_VOLT_RO_0_B1))
#define MG_S32Q24_VOLT_RO_0_B2              ((sint32)S32Q24(MG_F32_VOLT_RO_0_B2))
#define MG_S32Q24_VOLT_RO_0_B3              ((sint32)S32Q24(MG_F32_VOLT_RO_0_B3))
#define MG_S32Q24_VOLT_RO_0_A1              ((sint32)S32Q24(MG_F32_VOLT_RO_0_A1))
#define MG_S32Q24_VOLT_RO_0_A2              ((sint32)S32Q24(MG_F32_VOLT_RO_0_A2))
#define MG_S32Q24_VOLT_RO_0_A3              ((sint32)S32Q24(MG_F32_VOLT_RO_0_A3))

#define MG_S16_10mV_MAX_V_ERR               (sint16)(MG_F32_MAX_V_ERR * F32_10_MILLI)
#define MG_S16_10mV_MIN_V_ERR               (sint16)(MG_F32_MIN_V_ERR * F32_10_MILLI)
#define MG_S16_10mV_MAX_V_ERR_HC            (sint16)(MG_F32_MAX_V_ERR_HC * F32_10_MILLI)

#define MG_U16_10mV_LLC_VOLT_OUT_ZERO_LOAD  (uint16)(MG_F32_LLC_VOLT_OUT_ZERO_LOAD * F32_10_MILLI)
#define MG_U16_10mV_LLC_VOLT_OUT_MAX_LOAD   (uint16)(MG_F32_LLC_VOLT_OUT_MAX_LOAD * F32_10_MILLI)
#define MG_U16_10mV_LLC_VOUT_OVP_TEST_VREF  (uint16)(MG_F32_VOUT_OVP_TEST_VREF * F32_10_MILLI)

#define MG_U16_10mA_LLC_CURR_OUT_MAX_LOAD   (uint16)(MG_F32_LLC_CURR_OUT_MAX_LOAD * F32_10_MILLI)
#define MG_U16_10mA_LLC_CURR_CT_OCP         (uint16)(MG_F32_LLC_CURR_CT_OCP * F32_10_MILLI)

#define MG_U16_10mA_LLC_CURR_LIMIT_ERR      (uint16)(MG_F32_LLC_CURR_LIMIT_ERR * F32_10_MILLI)

#define MG_U32Q15_DROOP_FACT                (uint32)(U32Q15(SAT_L((MG_F32_LLC_VOLT_OUT_ZERO_LOAD - MG_F32_LLC_VOLT_OUT_MAX_LOAD), 0U)) \
                                                       / MG_F32_LLC_CURR_OUT_MAX_LOAD)

#define MG_U32Q15_DROOP_FACT_OVL            (uint32)(U32Q15(SAT_L(((MG_F32_LLC_VOLT_OUT_MAX_LOAD - MG_F32_LLC_VOLT_OUT_OVERLOAD) \
                                                         - (MG_F32_LLC_VOLT_OUT_ZERO_LOAD - MG_F32_LLC_VOLT_OUT_MAX_LOAD)), 0U)) \
                                                         / (MG_F32_LLC_CURR_OUT_OVERLOAD - MG_F32_LLC_CURR_OUT_MAX_LOAD))

#define MG_U16Q8_10mV_SS_ZERO_LOAD_FACT      (uint16)(U32Q8((MG_F32_LLC_VOLT_OUT_ZERO_LOAD * F32_10_MILLI) \
                                                      / (MG_F32_ISR_FREQUENCY * (MG_F32_SOFT_START_TIME_ZERO_LOAD / 1000.0F)))) /* for ISR freq, (divide by 1000 -> ms) */
#define MG_U16Q8_10mV_SS_MAX_LOAD_FACT      (uint16)(U32Q8((MG_F32_LLC_VOLT_OUT_MAX_LOAD * F32_10_MILLI) \
                                                      / (MG_F32_ISR_FREQUENCY * (MG_F32_SOFT_START_TIME_MAX_LOAD / 1000.0F))))  /* for ISR freq, (divide by 1000 -> ms) */
#define MG_U32Q23_10mV_SS_LOAD_FACT         (uint32)(U32Q15(MG_U16Q8_10mV_SS_ZERO_LOAD_FACT - MG_U16Q8_10mV_SS_MAX_LOAD_FACT) \
                                                      / MG_U16_10mA_LLC_CURR_OUT_MAX_LOAD)

#define MG_U32_nS_LLC_PERIOD_MIN            (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_MAX)
#define MG_U32_nS_LLC_PERIOD_MAX            (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_MIN)
#define MG_U32Q4_nS_LLC_PERIOD_MAX          (uint32)(MG_U32_nS_LLC_PERIOD_MAX << 4)
#define MG_U32_nS_LLC_PERIOD_CT_PEAK_OVP    (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_CT_PEAK_OVP)
#define MG_U32Q4_nS_LLC_PERIOD_CT_PEAK_OVP  (uint32)(MG_U32_nS_LLC_PERIOD_CT_PEAK_OVP << 4)
#define MG_U32_nS_LLC_PERIOD_BURST          (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_BURST)
#define MG_U32_nS_LLC_PERIOD_BURST_IN       (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_BURST_IN)
#define MG_U32_nS_LLC_PERIOD_FBURST         (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_FBURST)
#define MG_U32_nS_LLC_PERIOD_FBURST_IN      (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_FBURST_IN)

#define MG_U32_nS_LLC_PERIOD_PWM_SS         (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_PWM_SS)
#define MG_U32_nS_LLC_PERIOD_PWM            (uint32)(F64_ONE_BY_NANO / MG_LLC_FREQ_PWM)
#define MG_U32Q10_nS_PWM_FREQ_FACT          (uint32)(U32Q10(MG_U32_nS_LLC_PERIOD_PWM - MG_U32_nS_LLC_PERIOD_PWM_SS) \
                                                         / MG_U16_10mV_LLC_VOLT_OUT_MAX_LOAD)

#define MG_U16Q16_MAX_DUTY_CYCLE            ((uint16)SAT_H((S32Q16(MG_F32_MAX_DUTY_CYCLE)), (S32Q16(0.5F))))
#define MG_U16Q16_MIN_DUTY_CYCLE            ((uint16)SAT_L((S32Q16(MG_F32_MIN_DUTY_CYCLE)), (S32Q16(0.0F))))

#define MG_U16_nS_PWM_LLC_DT                (uint16)(MG_PWM_LLC_DT / 2)  /* DT divided by 2 because of center aligne */

#define MG_S16_nS_PWM_LLC_DEAD_TIME_1       (sint16)(SAT_L(MG_PWM_LLC_DEAD_TIME_1, 0))  /* Limit the dead time to zero to ensure no negative DT */
#define MG_S16_nS_PWM_LLC_DEAD_TIME_2       (sint16)(SAT_L(MG_PWM_LLC_DEAD_TIME_2, 0))  /* Limit the dead time to zero to ensure no negative DT */
#define MG_U32_nS_PWM_LLC_DT_PERIOD_1       (uint32)(F64_ONE_BY_NANO / MG_PWM_LLC_DT_FREQ_1)
#define MG_U32_nS_PWM_LLC_DT_PERIOD_2       (uint32)(F64_ONE_BY_NANO / MG_PWM_LLC_DT_FREQ_2)
#define MG_S16_nS_PWM_LLC_DT_MIN            (sint16)(MIN(MG_S16_nS_PWM_LLC_DEAD_TIME_1, MG_S16_nS_PWM_LLC_DEAD_TIME_2))
#define MG_S16_nS_PWM_LLC_DT_MAX            (sint16)(MAX(MG_S16_nS_PWM_LLC_DEAD_TIME_1, MG_S16_nS_PWM_LLC_DEAD_TIME_2))

#define MG_S32Q12_LLC_DT_FACT_1             (sint32)(S32Q12(((sint32)MG_S16_nS_PWM_LLC_DEAD_TIME_1 - (sint32)MG_S16_nS_PWM_LLC_DEAD_TIME_2)) \
                                                      / ((sint32)MG_U32_nS_PWM_LLC_DT_PERIOD_2 - (sint32)MG_U32_nS_PWM_LLC_DT_PERIOD_1))                                           
#define MG_S16_nS_LLC_DT_MIN_1              (sint16)(MIN((MG_S16_nS_PWM_LLC_DEAD_TIME_2 - MG_S16_nS_PWM_LLC_DEAD_TIME_1), 0))
#define MG_S16_nS_LLC_DT_MAX_1              (sint16)(MAX((MG_S16_nS_PWM_LLC_DEAD_TIME_2 - MG_S16_nS_PWM_LLC_DEAD_TIME_1), 0))

#define MG_S16_nS_PWM_SR_ON_DEAD_TIME_1     (sint16)(MG_PWM_SR_ON_DEAD_TIME_1)
#define MG_S16_nS_PWM_SR_ON_DEAD_TIME_2     (sint16)(MG_PWM_SR_ON_DEAD_TIME_2)
#define MG_S16_nS_PWM_SR_ON_DEAD_TIME_3     (sint16)(MG_PWM_SR_ON_DEAD_TIME_3)
#define MG_U32_nS_PWM_SR_ON_DT_PERIOD_1     (uint32)(F64_ONE_BY_NANO / MG_PWM_SR_ON_DT_FREQ_1)
#define MG_U32_nS_PWM_SR_ON_DT_PERIOD_2     (uint32)(F64_ONE_BY_NANO / MG_PWM_SR_ON_DT_FREQ_2)
#define MG_U32_nS_PWM_SR_ON_DT_PERIOD_3     (uint32)(F64_ONE_BY_NANO / MG_PWM_SR_ON_DT_FREQ_3)
#define MG_S16_nS_PWM_SR_ON_DT_MIN          (sint16)(MIN(MG_S16_nS_PWM_SR_ON_DEAD_TIME_1, MG_S16_nS_PWM_SR_ON_DEAD_TIME_3))
#define MG_S16_nS_PWM_SR_ON_DT_MAX          (sint16)(MAX(MG_S16_nS_PWM_SR_ON_DEAD_TIME_1, MG_S16_nS_PWM_SR_ON_DEAD_TIME_3))

#define MG_S32Q12_SR_ON_DT_FACT_1           (sint32)(S32Q12(((sint32)MG_S16_nS_PWM_SR_ON_DEAD_TIME_1 - (sint32)MG_S16_nS_PWM_SR_ON_DEAD_TIME_2)) \
                                                      / ((sint32)MG_U32_nS_PWM_SR_ON_DT_PERIOD_2 - (sint32)MG_U32_nS_PWM_SR_ON_DT_PERIOD_1))
#define MG_S32Q12_SR_ON_DT_FACT_2           (sint32)(S32Q12(((sint32)MG_S16_nS_PWM_SR_ON_DEAD_TIME_2 - (sint32)MG_S16_nS_PWM_SR_ON_DEAD_TIME_3)) \
                                                      / ((sint32)MG_U32_nS_PWM_SR_ON_DT_PERIOD_3 - (sint32)MG_U32_nS_PWM_SR_ON_DT_PERIOD_2))
#define MG_S16_nS_SR_ON_DT_MIN_1            (sint16)(MIN((MG_S16_nS_PWM_SR_ON_DEAD_TIME_2 - MG_S16_nS_PWM_SR_ON_DEAD_TIME_1), 0))
#define MG_S16_nS_SR_ON_DT_MIN_2            (sint16)(MIN((MG_S16_nS_PWM_SR_ON_DEAD_TIME_3 - MG_S16_nS_PWM_SR_ON_DEAD_TIME_2), 0))
#define MG_S16_nS_SR_ON_DT_MAX_1            (sint16)(MAX((MG_S16_nS_PWM_SR_ON_DEAD_TIME_2 - MG_S16_nS_PWM_SR_ON_DEAD_TIME_1), 0))
#define MG_S16_nS_SR_ON_DT_MAX_2            (sint16)(MAX((MG_S16_nS_PWM_SR_ON_DEAD_TIME_3 - MG_S16_nS_PWM_SR_ON_DEAD_TIME_2), 0))

#define MG_S16_nS_PWM_SR_OFF_DEAD_TIME_1    (sint16)(MG_PWM_SR_OFF_DEAD_TIME_1)
#define MG_S16_nS_PWM_SR_OFF_DEAD_TIME_2    (sint16)(MG_PWM_SR_OFF_DEAD_TIME_2)
#define MG_S16_nS_PWM_SR_OFF_DEAD_TIME_3    (sint16)(MG_PWM_SR_OFF_DEAD_TIME_3)
#define MG_U32_nS_PWM_SR_OFF_DT_PERIOD_1    (uint32)(F64_ONE_BY_NANO / MG_PWM_SR_OFF_DT_FREQ_1)
#define MG_U32_nS_PWM_SR_OFF_DT_PERIOD_2    (uint32)(F64_ONE_BY_NANO / MG_PWM_SR_OFF_DT_FREQ_2)
#define MG_U32_nS_PWM_SR_OFF_DT_PERIOD_3    (uint32)(F64_ONE_BY_NANO / MG_PWM_SR_OFF_DT_FREQ_3)
#define MG_S16_nS_PWM_SR_OFF_DT_MIN         (sint16)(MIN(MG_S16_nS_PWM_SR_OFF_DEAD_TIME_1, MG_S16_nS_PWM_SR_OFF_DEAD_TIME_3))
#define MG_S16_nS_PWM_SR_OFF_DT_MAX         (sint16)(MAX(MG_S16_nS_PWM_SR_OFF_DEAD_TIME_1, MG_S16_nS_PWM_SR_OFF_DEAD_TIME_3))

#define MG_S32Q12_SR_OFF_DT_FACT_1          (sint32)(S32Q12(((sint32)MG_S16_nS_PWM_SR_OFF_DEAD_TIME_1 - (sint32)MG_S16_nS_PWM_SR_OFF_DEAD_TIME_2)) \
                                                      / ((sint32)MG_U32_nS_PWM_SR_OFF_DT_PERIOD_2 - (sint32)MG_U32_nS_PWM_SR_OFF_DT_PERIOD_1))
#define MG_S32Q12_SR_OFF_DT_FACT_2          (sint32)(S32Q12(((sint32)MG_S16_nS_PWM_SR_OFF_DEAD_TIME_2 - (sint32)MG_S16_nS_PWM_SR_OFF_DEAD_TIME_3)) \
                                                      / ((sint32)MG_U32_nS_PWM_SR_OFF_DT_PERIOD_3 - (sint32)MG_U32_nS_PWM_SR_OFF_DT_PERIOD_2))
#define MG_S16_nS_SR_OFF_DT_MIN_1           (sint16)(MIN((MG_S16_nS_PWM_SR_OFF_DEAD_TIME_2 - MG_S16_nS_PWM_SR_OFF_DEAD_TIME_1), 0))
#define MG_S16_nS_SR_OFF_DT_MIN_2           (sint16)(MIN((MG_S16_nS_PWM_SR_OFF_DEAD_TIME_3 - MG_S16_nS_PWM_SR_OFF_DEAD_TIME_2), 0))
#define MG_S16_nS_SR_OFF_DT_MAX_1           (sint16)(MAX((MG_S16_nS_PWM_SR_OFF_DEAD_TIME_2 - MG_S16_nS_PWM_SR_OFF_DEAD_TIME_1), 0))
#define MG_S16_nS_SR_OFF_DT_MAX_2           (sint16)(MAX((MG_S16_nS_PWM_SR_OFF_DEAD_TIME_3 - MG_S16_nS_PWM_SR_OFF_DEAD_TIME_2), 0))

#if MG_CURR_LIMIT_MODE
#define MG_U16_10mA_CC_IOUT_SS_LL           (uint16)(MG_F32_CC_IOUT_SS_LL * F32_10_MILLI)
#define MG_U16_10mA_CC_IOUT_LL              (uint16)(MG_F32_CC_IOUT_LL * F32_10_MILLI)
#define MG_U16_10mA_CC_IOUT_SS_HL           (uint16)(MG_F32_CC_IOUT_SS_HL * F32_10_MILLI)
#define MG_U16_10mA_CC_IOUT_HL              (uint16)(MG_F32_CC_IOUT_HL * F32_10_MILLI)

#define MG_S32Q15_CURR_LIMIT_KP             ((sint32)S32Q15(MG_F32_CURR_LIMIT_KP))
#define MG_S32Q15_CURR_LIMIT_KI             ((sint32)S32Q15(MG_F32_CURR_LIMIT_KI))
#define MG_S32Q15_CURR_LIMIT_B0             ((sint32)S32Q15(MG_F32_CURR_LIMIT_KP + (MG_F32_CURR_LIMIT_KI / 2)))
#define MG_S32Q15_CURR_LIMIT_B1             ((sint32)S32Q15(-MG_F32_CURR_LIMIT_KP + (MG_F32_CURR_LIMIT_KI / 2)))

#define MG_S16_10mV_CC_VOUT_ADJ_MAX         (sint16)(MG_F32_CC_VOUT_ADJ_MAX * F32_10_MILLI)
#endif

#if MG_PWM_CTRL_MODE
#define MG_S32Q8_PWM_CTRL_KP                ((sint32)S32Q8(MG_F32_PWM_CTRL_KP))
#define MG_S32Q8_PWM_CTRL_KI                ((sint32)S32Q8(MG_F32_PWM_CTRL_KI))
#define MG_S32Q8_PWM_CTRL_B0                ((sint32)S32Q8(MG_F32_PWM_CTRL_KP + (MG_F32_PWM_CTRL_KI / 2)))
#define MG_S32Q8_PWM_CTRL_B1                ((sint32)S32Q8(-MG_F32_PWM_CTRL_KP + (MG_F32_PWM_CTRL_KI / 2)))

#define MG_S16_10mV_MAX_PWM_ERR             (sint16)(MG_F32_MAX_PWM_ERR * F32_10_MILLI)
#define MG_S16_10mV_MIN_PWM_ERR             (sint16)(MG_F32_MIN_PWM_ERR * F32_10_MILLI)

#else
#define MG_S16_10mV_VOLT_BM_ERR_OFFSET      (sint16)(MG_F32_VOLT_BM_ERR_OFFSET * F32_10_MILLI)
#define MG_S16_10mV_VOLT_BM_ADJ_MAX         (sint16)(MG_F32_VOLT_BM_ADJ_MAX * F32_10_MILLI)
#define MG_S16_10mV_VOLT_BM_ADJ_MIN         (sint16)(MG_F32_VOLT_BM_ADJ_MIN * F32_10_MILLI)
#define MG_U16_10mV_CURR_BM_ON              (uint16)(MG_F32_CURR_BM_ON * F32_10_MILLI)
#define MG_U16_10mV_CURR_BM_OFF             (uint16)(MG_F32_CURR_BM_OFF * F32_10_MILLI)

#define MG_S16_10mV_BM_TIMEOUT_VOLT_ERR_1   (sint16)(MG_F32_BM_TIMEOUT_VOLT_ERR_1 * F32_10_MILLI)
#define MG_S16_10mV_BM_TIMEOUT_VOLT_ERR_2   (sint16)(MG_F32_BM_TIMEOUT_VOLT_ERR_2 * F32_10_MILLI)
#define MG_S16_10mV_BM_TIMEOUT_VOLT_ERR_3   (sint16)(MG_F32_BM_TIMEOUT_VOLT_ERR_3 * F32_10_MILLI)
#endif

#if MG_IIR_RIPPLE_FLT
#define MG_S32Q8_IIR_FLT_GAIN               (sint32)S32Q8(MG_F32_IIR_FLT_GAIN)
#define MG_S16_10mV_IIR_IN_LIMIT            (sint16)(MG_F32_IIR_IN_LIMIT * F32_10_MILLI)
#define MG_S16_10mV_IIR_OUT_LIMIT           (sint16)(MG_F32_IIR_OUT_LIMIT * F32_10_MILLI)
#endif


#ifdef __cplusplus
  }
#endif
#endif  /* LLCCTRL_CONF_H */

  
/*
 * End of file
 */
