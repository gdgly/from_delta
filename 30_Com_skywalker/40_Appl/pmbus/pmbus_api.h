/** *****************************************************************************
 * \file    pmbus_api.h
 * \brief   Service function request file for pmbus.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-10-30 16:15:41 +0800 (Tue, 30 Oct 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 93 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PMBUS_API_H
#define PMBUS_API_H
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
/*******************************************************************************
 * \brief         Prehandle the received bytes by command
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCmdCheck(void);

/*******************************************************************************
 * \brief          Clear fault or warning status
 *                  ucPage: page0, 1, FF
 *                  ucMode: 1: clear All, and can restart ( OPERATION )
 *                          2: clear All except STA_MFR, and can restart ( PS_ON, PS_KILL )
 *                          3: clear All, and can't restart ( CLEAR_FAULT, CLEAR_BITS )
 *                          4: clear All except STA_MFR, and can't restart
 *
 * \param[in]     -ucPage, ucMode
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
 void PMBUS_vClearAllPageFault(void);

/*******************************************************************************
 * Function:        PMBUS_SendData
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     PSU -> SYS
 *
 ******************************************************************************/
void PMBUS_vSendData(void);

void vPMBus_HandleData(void);

uint8 PMBUS_u8GetBootMcuId(void);

void PMBUS_vClearAllFault(void);

void PMBUS_vClearPowerOffFault(void);

#ifdef __cplusplus
  }
#endif
#endif  /* PMBUS_API_H */

  
/*
 * End of file
 */
