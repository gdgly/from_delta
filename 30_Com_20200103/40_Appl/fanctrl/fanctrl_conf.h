/** *****************************************************************************
 * \file    fanctrl_conf.h
 * \brief   Configurations file for fanctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-05-17 15:22:20 +0800 (Fri, 17 May 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 181 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef FANCTRL_CONF_H
#define FANCTRL_CONF_H
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
																											
#define MG_S16_FAN_CTRL_TEMP_THR_0                  ((sint16)-8)
#define MG_S16_FAN_CTRL_TEMP_THR_1                  ((sint16)5)
#define MG_S16_FAN_CTRL_TEMP_THR_2                  ((sint16)30)
#define MG_S16_FAN_CTRL_TEMP_THR_3                  ((sint16)40)

#define MG_S16_FAN_CTRL_SPEED_THR_1                 ((sint16)5900)
#define MG_S16_FAN_CTRL_SPEED_THR_0                 ((sint16)(0.4 * MG_S16_FAN_CTRL_SPEED_THR_1))
#define MG_S16_FAN_CTRL_SPEED_THR_2                 ((sint16)10000)
#define MG_S16_FAN_CTRL_SPEED_MAX                   ((sint16)23600)
#define MG_S16_FAN_CTRL_SPEED_MIN                   ((sint16)2100)

#define MG_S16_FAN_CTRL_LOAD_MAX                    ((sint16)4000)
#define MG_S16_FAN_CTRL_LOAD_THR_0                  ((sint16)MG_S16_FAN_CTRL_LOAD_MAX * 0.5 )

#define MG_U32_FAN_SCALING_FACT_1                   ((uint32)(MG_S16_FAN_CTRL_SPEED_THR_2 - MG_S16_FAN_CTRL_SPEED_THR_1) \
                                                              / (uint32)(MG_S16_FAN_CTRL_TEMP_THR_3 - MG_S16_FAN_CTRL_TEMP_THR_2))
#define MG_U32_FAN_SCALING_FACT_2                   (((uint32)MG_S16_FAN_CTRL_SPEED_MAX - (uint32)MG_S16_FAN_CTRL_SPEED_THR_0) << 7 \
                                                              / (uint32)(MG_S16_FAN_CTRL_LOAD_MAX - MG_S16_FAN_CTRL_LOAD_THR_0))


/* fan regulate step X/1000, change the can change the Fan speed regulate loop */
#define MG_U8_FAN_REGULATE_FAST_FAST_STEP             ((uint8)50u)
#define MG_U8_FAN_REGULATE_FAST_STEP                  ((uint8)30u)
#define MG_U8_FAN_REGULATE_SLOW_STEP                  ((uint8)1u)


/* When fan speed error bigger then below vaule, use fase control */
#define MG_S16_FAN_FAST_FAST_CTRL_VALUE               ((sint16)4000)
#define MG_S16_FAN_FAST_CTRL_VALUE                    ((sint16)2000)
#define MG_S16_FAN_SYS_CTRL_VALUE                     ((sint16)500)

/* Set the MAX fan Speed */
#define FANCTRL_CONF_U16_FAN_SPEED_MAX                ((uint16)26500)
/* Set the MIN fan Speed */
#define MG_U16_FAN_SPEED_MIN                          ((uint16)5500)
/* Set the MAX fan Duty */
#define MG_U16_FAN_DUTY_MAX                           ((uint16)1000)
/* Set the MIN fan Duty */
#define MG_U16_FAN_DUTY_MIN                           ((uint16)(((float32)MG_U16_FAN_SPEED_MIN * 1000.0F) / (float32)FANCTRL_CONF_U16_FAN_SPEED_MAX))


/* If fan speed samller than below speed, set fan warn and  fail */
#define MG_U16_FAN_FAIL_SPEED                         ((uint16)1500)
#define MG_U16_FAN_WARN_SPEED                         ((uint16)2000)
/* If fan speed Larger than below speed, set fan OK */
#define MG_U16_FAN_OK_SPEED                           ((uint16)3500)
/* Set fan Fail delay time */
#define MG_U8_FAN_FAIL_SET_DLY                        ((uint8)20)  /* delay = X * 500ms */
/* Set fan Warning delay time */
#define MG_U8_FAN_WARN_SET_DLY                        ((uint8)20)  /* delay = X * 500ms */
/* Set fan OK delay time */
#define MG_U8_FAN_OK_DLY                              ((uint8)2)   /* delay = X * 500ms */

#define FANCTRL_CONF_DUTY_INIT                         ((uint16)300u)   /* 30% -- 0.001 */
#define FANCTRL_CONF_DUTY_BOOT_MODE                    ((uint16)350u)   /* 35% -- 0.001  */
#define FANCTRL_CONF_DUTY_AC_OFF                       ((uint16)500u)   /* 50% -- 0.001  */
		

#ifdef __cplusplus
  }
#endif
#endif  /* FANCTRL_CONF_H */


/*
 * End of file
 */
