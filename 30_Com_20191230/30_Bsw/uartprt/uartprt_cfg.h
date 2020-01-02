/** *****************************************************************************
 * \file    uartprt_cfg.h
 * \brief   Server call back service file for uartprt.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-03 17:54:42 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 9 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef UARTPRT_CFG_H
#define UARTPRT_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_INTCOM_MODULE         1

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"

#if MG_INTCOM_MODULE
#include "intcom_scb.h"
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/

/* Internal communication module section */
inline void UARTPRT_cfg_vIntComTxData(uint8 u8ComIndex, uint8 *pau8TxBuf, uint16 *u16TxDataNbr)
{
  #if MG_INTCOM_MODULE
	switch(u8ComIndex)
	{
		case 0:
		{
       INTCOM_vCom1TxData(pau8TxBuf, u16TxDataNbr);
			 break;
		}
		case 1u:
		{
       INTCOM_vCom2TxData(pau8TxBuf, u16TxDataNbr);
			break;
		}
		default:
		{
			break;
		}
	}
  #endif
}

inline void UARTPRT_cfg_vIntComRxData(uint8 u8ComIndex, uint8 *pau8RxBuf, uint8 u8BroadcastFlg, uint16 u16RxBufCnt)
{
#if MG_INTCOM_MODULE
	switch(u8ComIndex)
	{
		case 0:
		{
       INTCOM_vCom1RxData(pau8RxBuf, u8BroadcastFlg, u16RxBufCnt);
			 break;
		}
		case 1u:
		{
       INTCOM_vCom2RxData(pau8RxBuf, u8BroadcastFlg, u16RxBufCnt);
			break;
		}
		default:
		{
			break;
		}
	}
#endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* UARTPRT_CFG_H */

  
/*
 * End of file
 */
