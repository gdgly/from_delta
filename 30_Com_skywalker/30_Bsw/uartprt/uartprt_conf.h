/** *****************************************************************************
 * \file    uartprt_conf.h
 * \brief   Configurations file for uartprt.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-29 14:18:32 +0800 (Wed, 29 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 16 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef UARTPRT_CONF_H
#define UARTPRT_CONF_H
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
#define MG_UART_NUM_MAX        ((uint8)2u)
/***********************************************
 * Uart
 **********************************************/
#define MG_TX_BUF_SIZE             ((uint16)128U)     /* The buffer size has to meet the buffer array in RTE */
#define MG_RX_BUF_SIZE             ((uint16)128U)     /* The buffer size has to meet the buffer array in RTE */

/***********************************************
 * Define frame format
 **********************************************/
#define MG_FRAME_STX                0xAA              /* Start of a UART frame */
#define MG_FRAME_AUX_LEN            ((uint16)5U)      /* STX,ADDR,LEN,CRC16 */
#define MG_TX_ONCE_RX_ADDR          TRUE              /* Begin to TX once receive local address */
#define MG_UART_STATUS_BYTE_CTR     3U

#define MG_ADDR_DETECT_CTR          ((uint16)700U)    /* GPIO read average counter */

#define MG_ADDR_PRI_1               0x10              /* MCU address */
#define MG_ADDR_PRI_2               0x11
#define MG_ADDR_PRI_ALL             0x1F
#define MG_ADDR_SEC_1               0x20
#define MG_ADDR_SEC_2               0x21
#define MG_ADDR_SEC_ALL             0x2F

#define MG_SLAVE_LOCATION_PRI       TRUE              /* TRUE: PRI, FALSE: SEC */
#if (TRUE == MG_SLAVE_LOCATION_PRI)
  #define MG_SLAVE_BROADCAST_ADDR  MG_ADDR_PRI_ALL
#else
  #define MG_SLAVE_BROADCAST_ADDR  MG_ADDR_SEC_ALL
#endif

#define MG_SLAVE_LOCATION_1        MG_ADDR_PRI_1
#define MG_SLAVE_LOCATION_2        MG_ADDR_SEC_1

static const uint8 au8SlaveAddr[]={MG_SLAVE_LOCATION_1,MG_SLAVE_LOCATION_2};

/***********************************************
 * Define timing
 **********************************************/
#define MG_RX_BYTE_TIMEOUT_4800          5U             /* Value * 1ms = time */
#define MG_RX_BYTE_TIMEOUT_38400         1U             /* Value * 1ms = time */


#define MG_UART_RX_FRAME_TIMEOUT_4800    8U             /* Value * 1ms = time */
#define MG_UART_RX_FRAME_TIMEOUT_38400   4U             /* Value * 1ms = time */

#define MG_UART_TX_TIMEOUT_4800          7U             /* Value * 1ms = time */
#define MG_UART_TX_TIMEOUT_38400         3U             /* Value * 1ms = time */

/***********************************************
 * Define UART fail counter
 **********************************************/
#define MG_FAIL_CNT                 ((uint16)1000U)     /* Value * 1ms = time */

/*******************************************************************************
 * General purpose section
 ******************************************************************************/

#define MG_BAUDRATE_4800            (uint16)4800U
#define MG_BAUDRATE_38400           (uint16)38400U


#ifdef __cplusplus
  }
#endif
#endif  /* UARTPRT_CONF_H */


/*
 * End of file
 */
