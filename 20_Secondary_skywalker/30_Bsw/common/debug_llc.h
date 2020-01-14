/** *****************************************************************************
 * \file    debug_llc.h
 * \brief   Common header for boost debugging
 *
 * \section AUTHOR
 *    1. HDC Software Team
 *    2. BDC Software Team
 *
 * \section SVN
 *  $Date$
 *  $Author$
 *  $Revision$
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

#ifndef DEBUG_LLC_H
#define DEBUG_LLC_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/
/* Control the debug mode */
#define DEBUG_MODE                          1   /* 1 = Debug mode on; 0 = All debug sections ignored */

/* DEBUG MODE ON */
#if DEBUG_MODE
  #define DEBUG_SECTION_INT_OSCILLATOR      0   /* 1 = Internal oscillator */
  #define DEBUG_SECTION_WDG_DEBUG_DELAY     0   /* 1 = Long watchdog timeout delay */
  #define DEBUG_SECTION_PIN_DRV_OFF         0   /* 1 = PWM hardware drives are kept off */
  #define DEBUG_SECTION_PWM_DRV_OFF         0   /* 1 = All PWM drives are kept off */
  #define DEBUG_SECTION_SR_DRV_OFF          0   /* 1 = SR always off; 0 = SR active */
  #define DEBUG_SECTION_PWM_A_DRV_OFF       0   /* 1 = PWM A drive is kept off */
  #define DEBUG_SECTION_PWM_B_DRV_OFF       0   /* 1 = PWM B drive is kept off */
  #define DEBUG_SECTION_PWM_C_DRV_OFF       0   /* 1 = PWM C drive is kept off */
  #define DEBUG_SECTION_PWM_D_DRV_OFF       0   /* 1 = PWM D drive is kept off */
  #define DEBUG_SECTION_PWM_E_DRV_OFF       0   /* 1 = PWM E drive is kept off */

  /* Drive debugging */
  #define DEBUG_SECTION_FIXED_FREQ_DRV_ON   0   /* 1 = The PWM drive is always enabled (bypass software protection and timing control) */
  #define DEBUG_SECTION_FIXED_FREQ_MODE     0   /* 1 = Drive PWM with fixed frequency */
  #define DEBUG_SECTION_FIXED_FREQ     200000   /* (Hz) Fixed frequency */
  #define DEBUG_SECTION_FIXED_PERIOD   (uint32)(F64_ONE_BY_NANO / DEBUG_SECTION_FIXED_FREQ)
  #define DEBUG_SECTION_PIN_DRV_ON          0   /* 1 = Driver always enabled */

  #define DEBUG_SECTION_OVP_TEST            0   /* 1 = Over voltage test enabled */

  #define DEBUG_SECTION_OCP_LATCH           0   /* 1 = Over current protection latch; Latch is cleared every restart cycle */
  #define DEBUG_SECTION_OTP_DISABLE         0   /* 1 = Over temperature protection disable */
  #define DEBUG_SECTION_OVP_DISABLE         0   /* 1 = Over voltage protection disable */
  #define DEBUG_SECTION_UVP_DISABLE         0   /* 1 = Under voltage protection disable */

  /* Debug pin */
  #if 1
  #include "StdPeriphDriver.h"
  #include "port_conf.h"
  #define DEBUG_SECTION_PIN_DEBUG_SET       MG_PORT_DEBUG_PIN_SET
  #define DEBUG_SECTION_PIN_DEBUG_RESET     MG_PORT_DEBUG_PIN_RESET
  #define DEBUG_SECTION_PIN_DEBUG_TOGGLE    MG_PORT_DEBUG_PIN_TOGGLE
  #endif

  /* Debug DAC */
  #if 1
  #include "StdPeriphDriver.h"
  #include "dac_conf.h"
  #define DEBUG_SECTION_DAC1_CH2(var)       MG_REG_DAC1_CHANNEL2_DATA = var;
  #endif

  /* Debug variables */
  #if 1
  #include "global.h"
  /* NOTE: before debug variables are available, put "#define DEBUG_VAR" before "debug_llc.h" header include in a maximum of one source file */
  #ifndef DEBUG_VAR
    #define _DECL extern
    #define _INIT(x)
  #else
    #define _DECL
    #define _INIT(x) = x
  #endif
  _DECL sint32 DEBUG_s32_variable_1 _INIT(0);
  _DECL sint32 DEBUG_s32_variable_2 _INIT(0);
  _DECL sint32 DEBUG_s32_variable_3 _INIT(0);
  _DECL sint32 DEBUG_s32_variable_4 _INIT(0);
  _DECL sint32 DEBUG_s32_variable_5 _INIT(0);
  _DECL sint32 DEBUG_s32_variable_6 _INIT(0);
#endif

#else
  /* Debug pin */
  #define DEBUG_SECTION_PIN_DEBUG_SET
  #define DEBUG_SECTION_PIN_DEBUG_RESET
  #define DEBUG_SECTION_PIN_DEBUG_TOGGLE
  /* Debug DAC */
  #define DEBUG_SECTION_DAC1_CH2(var)
#endif


#ifdef __cplusplus
  }
#endif
#endif  /* DEBUG_LLC_H */


/*
 * End of file
 */
