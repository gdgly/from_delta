/** *****************************************************************************
 * \file    fanctrl_api.h
 * \brief   Service function request file for fanctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-03-22 10:27:54 +0800 (Fri, 22 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 152 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef FANCTRL_API_H
#define FANCTRL_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "fanctrl_cfg.h"
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
/** *****************************************************************************
 * \brief         Read fan speed
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint16 FANCTRL_u16ReadFanSpeed(uint8 u8Index);

/** *****************************************************************************
 * \brief         Read fan control duty
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint16 FANCTRL_u16ReadFanCtrlDuty(uint8 u8Index);

/** *****************************************************************************
 * \brief         Set fan system control duty
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vSysSetFanCtrlDuty(uint8 u8Index, uint16 u16Duty);

/** *****************************************************************************
 * \brief         Read fan Fail bit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 FANCTRL_u8ReadFanBitFail(uint8 u8Index);
/** *****************************************************************************
 * \brief         Write fan Fail bit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_u8WriteFanBitFail(uint8 u8Index, uint8 u8Value);
/** *****************************************************************************
 * \brief         Read fan warning bit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 FANCTRL_u8ReadFanBitWarn(uint8 u8Index);
/** *****************************************************************************
 * \brief         Write fan warning bit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_u8WriteFanBitWarn(uint8 u8Index, uint8 u8Value);
/** *****************************************************************************
 * \brief         Read fan Fail bit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 FANCTRL_u8ReadFanBitOvrd(uint8 u8Index);

/** *****************************************************************************
 * \brief         Set Fan Block test flag
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vSetFanBlockTest(uint8 u8State);


#ifdef __cplusplus
  }
#endif
#endif  /* FANCTRL_API_H */

  
/*
 * End of file
 */
