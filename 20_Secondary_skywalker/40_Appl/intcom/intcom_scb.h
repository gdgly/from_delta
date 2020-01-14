/** *****************************************************************************
 * \file    intcom_scb.h
 * \brief   Service function call back file for intcom.c
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

#ifndef INTCOM_SCB_H
#define INTCOM_SCB_H
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
void INTCOM_vInit(void);

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
void INTCOM_vDeInit(void);

/** *****************************************************************************
 * \brief         Load TX buffer for transmission
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void INTCOM_vTxData(uint8 *pau8TxBuf, uint16 *u16TxDataNbr);

/** *****************************************************************************
 * \brief         Handle data in RX buffer
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void INTCOM_vRxData(uint8 *pau8RxBuf, uint8 u8BroadcastFlg, uint16 u16RxBufCnt);


#ifdef __cplusplus
  }
#endif
#endif  /* INTCOM_SCB_H */

  
/*
 * End of file
 */
