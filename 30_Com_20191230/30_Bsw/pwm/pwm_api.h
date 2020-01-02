/** *****************************************************************************
 * \file    pwm_api.h
 * \brief   Service function request file for pwm.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-10 18:40:44 +0800 (Fri, 10 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 12 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PWM_API_H
#define PWM_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "pwm_cfg.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Set PWM duty
 *                
 * \param[in]     u16Duty  duty set
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void PWM_vPwmDutyUpdate(PWM_CFG_E_INDEX ePwmIndex,uint16 u16Duty);


#ifdef __cplusplus
  }
#endif
#endif  /* PWM_API_H */

  
/*
 * End of file
 */
