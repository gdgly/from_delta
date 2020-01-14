/** *****************************************************************************
 * \file    llcctrl_scb.h
 * \brief   Service function call back file for llcctrl.c
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

#ifndef LLCCTRL_SCB_H
#define LLCCTRL_SCB_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vInit(void);

/** *****************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vDeInit(void);

/** *****************************************************************************
 * \brief         Booster control ISR A
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vLlcCtrlIsr(void);

/** *****************************************************************************
 * \brief         Update the status of LLC control loop
 *                Repetition time: 200uS
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vStatusUpdate(void);
  
/** *****************************************************************************
 * \brief         Adjust parameters accordingly to low or high line
 *                Repetition time: 200uS
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vLlHlAdjust(void);

/** *****************************************************************************
 * \brief         Process output double line ripple IIR-Gain filter
 *                Notch frequency 95.0 - 125.0Hz
 *                Notch filter Bandwidth 10Hz
 *                5kHz sampling frequency (repetition time: 200uS)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void LLCCTRL_vIirRippleFlt(void);


#ifdef __cplusplus
  }
#endif
#endif  /* LLCCTRL_SCB_H */

  
/*
 * End of file
 */
