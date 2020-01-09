/** *****************************************************************************
 * \file    ledctrl_conf.h
 * \brief   Configurations file for ledctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef LEDCTRL_CONF_H
#define LEDCTRL_CONF_H
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
typedef enum MG_E_LED_STATE_
{
  MG_E_LED_OFF = 0,       
  MG_E_LED_ON,
  MG_E_LED_BLINK_1HZ,
	MG_E_LED_BLINK_2HZ
} MG_E_LED_STATE;

typedef enum MG_E_FAIL_ID_LED_STATE_
{
  MG_E_FAIL_ID_LED_OFF = 0,
  MG_E_FAIL_ID_LED_AMBER_ON,
  MG_E_FAIL_ID_LED_AMBER_BLINKING_1HZ,
  MG_E_FAIL_ID_LED_AMBER_BLINKING_2HZ,
  MG_E_FAIL_ID_LED_BLUE_ON,
  MG_E_FAIL_ID_LED_BLUE_BLINKING_1HZ,
  MG_E_FAIL_ID_LED_BLUE_BLINKING_2HZ,
  MG_E_FAIL_ID_LED_AMBER_BLUE_BLINKING_1HZ,
} MG_E_FAIL_ID_LED_STATE;


#ifdef __cplusplus
  }
#endif
#endif  /* LEDCTRL_CONF_H */


/*
 * End of file
 */
