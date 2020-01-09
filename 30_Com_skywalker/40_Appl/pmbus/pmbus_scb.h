/** *****************************************************************************
 * \file    pmbus_scb.h
 * \brief   Service function call back file for pmbus.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-01-11 10:40:42 +0800 (Fri, 11 Jan 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 137 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PMBUS_SCB_H
#define PMBUS_SCB_H
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
 * \brief         Initialize PMBus data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vInit(void);

/*******************************************************************************
 * \brief         DeInitialize PMBus data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vDeInit(void);

/*******************************************************************************
 * \brief          Check boot mode
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCheckBootMode(void);

/*******************************************************************************
 * \brief         Copy sensor data to PMBus sensor registers
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCopySensorData(void);

/*******************************************************************************
 * \brief         Copy sensor data to PMBus sensor registers
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCopyStatusData(void);

/*******************************************************************************
 * \brief         Update PEC Error and Oring Fault to E5 and E7
 *                which need to be updated fast
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCopyPecAndOringStatus(void);



/*******************************************************************************
 * \brief         Copy debug data to PMBus debug registers
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCopyDebugData(void);

/********************************************************************************
 * \brief         - PMBUS_BlackBoxSaveData to buffer 1ms cycle
 *
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vSaveBlackBoxData2Buff(void);

void PMBUS_vSaveBlackBoxVinData2Buff(void);

#ifdef __cplusplus
  }
#endif
#endif  /* PMBUS_SCB_H */

  
/*
 * End of file
 */
