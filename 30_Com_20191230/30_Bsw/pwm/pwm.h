/********************************************************************************
 * \file    pwm.h
 * \brief   init pwm module
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 *******************************************************************************/

#ifndef PWM_H
#define PWM_H
#ifdef __cplusplus
  extern "C"  {
#endif
/*******************************************************************************
 * Included header
 ******************************************************************************/


/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/
#define PWM_FAN_CONTROL_PERIOD       (uint16)1919    //  48M/(1919+1)=25KHz
#define PWM_FAN_CONTROL_SPEED_INIT   (uint16)1728    //  Fan Init-speed is 90%
		
#define PWM_VSB_TRIM_PERIOD          (uint16)1919    //  48M/(1919+1)=25KHz
#define PWM_VSB_TRIM_INIT            (uint16)1596     //  3.3V Trim Init-speed is 78%

		
/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize and configure PWM modules
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void PWM_vPwmHwInit(void);

/*******************************************************************************
 * \brief         Set 5V trim duty
 *                CCP1 : 5V trim  Pin36 RC2,
 * \param[in]     u16Duty  duty set
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void PWM_vVsbTrimDutyUpdate(uint16 u16q10Duty);

/*******************************************************************************
 * \brief         This function update fan duty pwm register.
 *                
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void PWM_vFanDutyUpdate(uint16 u16q10Duty);


#ifdef __cplusplus
  }
#endif
#endif /* PWM_H */


/* 
 * End of file
 */
