/** *****************************************************************************
 * \file    uartprt_scb.h
 * \brief   Service function call back file for uartprt.c
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

#ifndef UARTPRT_SCB_H
#define UARTPRT_SCB_H
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
void UARTPRT_vInit(void);

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
void UARTPRT_vDeInit(void);

/** *****************************************************************************
 * \brief         Load TX buffer for transmission
 *                Note: should be implemented in less than COM frame timeout routine
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
extern void UARTPRT_vHandleTxData(void);

/** *****************************************************************************
 * \brief         Handle RX buffer
 *    _____________________________________________________________________
 *   |     |         |         |       |     |       |          |          |
 *   | STX | MCUADDR | DataLen | Data0 | ... | DataN | CRC16_LB | CRC16_HB |
 *   |_____|_________|_________|_______|_____|_______|__________|__________|         
 *   |     |         |         |       |     |       |          |          |
 *   |  AA |1X/2X    |   N+1   |       | ... |       |          |          |
 *   |_____|_________|_________|_______|_____|_______|__________|__________|
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
extern void UARTPRT_vHandleRxData(void);

/** *****************************************************************************
 * \brief         TX data by UART
 *                Note: should be implemented in <= 1ms routine
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
extern void UARTPRT_vTxData(void);

/** *****************************************************************************
 * \brief         RX data by UART
 *
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
extern void UARTPRT_vUsart2IrqHandler(void);

/** *****************************************************************************
 * \brief         Monitor UART1 timeout
 *
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
extern void UARTPRT_vTmOutMon(void);


#ifdef __cplusplus
  }
#endif
#endif  /* UARTPRT_SCB_H */

  
/*
 * End of file
 */
