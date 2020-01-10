/*******************************************************************************
 * \file    tempctrl.h
 * \brief   Global interface for tempctrl.c
 *
 * \section AUTHOR
 *    1. Fred Ji
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef TEMPCTRL_H
#define TEMPCTRL_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
 
/*******************************************************************************
 * \brief         Initialize temperature data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void TEMPCTRL_vTempDataInit(void);

/*******************************************************************************
 * \brief         NTC voltage calculation and filter
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void TEMPCTRL_vNtcVoltAverage(void);

/*******************************************************************************
 * Function:        LookUpNtcTemperature
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Look up temperature value from table
 *
 ******************************************************************************/ 
extern void TEMPCTRL_vLookUpNtcTemperature(void);

/*******************************************************************************
 * \brief         NTC OTP monitor
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void TEMPCTRL_vNtcTempMonitor(void);


#ifdef __cplusplus
  }
#endif
#endif  /* TEMPCTRL_H */

  
/*
 * End of file
 */
