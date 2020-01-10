/** *****************************************************************************
 * \file    uartprt.c
 * \brief   UART communication protocol
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-10-31 13:45:45 +0800 (Wed, 31 Oct 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 95 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/* Module header */
#define UARTPRT_EXPORT_H
  #include "uartprt_api.h"
  #include "uartprt_scb.h"
  #include "uartprt_cfg.h"
  #include "uartprt_scfg.h"
  #include "uartprt_rte.h"
  #include "uartprt_conf.h"

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

typedef union MG_U_UARTPRT_STATUS_
{
  struct
  {
    uint8 u8BootMode   : 1;   /* bit0 */
    uint8 u8CrcErr     : 1;   /* bit1 */
    uint8 u8McuAddrErr : 1;   /* bit2 */
    uint8 u8LenErr     : 1;   /* bit3 */
    uint8 u8ByteTmout  : 1;   /* bit4 */
    uint8 u8FrameTmout : 1;   /* bit5 */
    uint8 u8InvalidData: 1;   /* bit6 */
    uint8 u8UartRegErr : 1;   /* bit7 */
  } Bit;
  uint8 ALL;
} MG_U_UARTPRT_STATUS;

typedef union MG_U_UARTPRT_CTRL_
{
  struct
  {
    uint16 bRxByteTmOutEna   : 1;   /* bit0 */
    uint16 bTxTmOutEna       : 1;   /* bit1 */
    uint16 bTxBufUpdated     : 1;   /* bit2 */
    uint16 bRxNewFrame       : 1;   /* bit3 */
    uint16 bUartStaClrFlg    : 1;   /* bit4 */
    uint16 bAddrMatch        : 1;   /* bit5 */
		uint16 bRxFrameTmOutEna  : 1;   /* bit6 */
    uint16 bTxTmoutFlg       : 1;   /* bit7 */
		uint16 bFrameTmoutFlg    : 1;   /* bit8 */
		uint16 bRxDurTxFlg       : 1;   /* bit9 */
		uint16 bByteTmoutFlg     : 1;   /* bit10 */
  } Bit;
  uint16 ALL;
} MG_U_UARTPRT_CTRL; 

typedef struct MG_S_UARTPRT_DATA_
{
  uint16 u16TxDataCnt;
  uint16 u16RxDataCnt;
  uint16 u16RxByteTmOutCnt;
	uint16 u16RxFrameTmOutCnt;
	uint16 u16TxTmOutCnt;
  uint16 u16TxDataNbr;
  uint16 u16RxDataNbr;
  uint16 u16RxCrc;
  uint8  u8SlaveAddr;
  MG_U_UARTPRT_STATUS uStatus;
  MG_U_UARTPRT_CTRL   uCtrl;
} MG_S_UARTPRT_DATA;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
static uint8 mg_au8SlaveAddress[MG_UART_NUM_MAX];
static uint16 mg_u16Crc[MG_UART_NUM_MAX];

static MG_S_UARTPRT_DATA mg_uUartPrtData[MG_UART_NUM_MAX];

static uint8 mg_u8RxTimeOutDly[MG_UART_NUM_MAX];
static uint8 mg_u8RxFrameTimeOutDly[MG_UART_NUM_MAX];
static uint8 mg_u8TxTimeOutDly[MG_UART_NUM_MAX];
uint8 mg_au8UartTxBuf[MG_UART_NUM_MAX][MG_TX_BUF_SIZE];
static uint8 mg_au8UartRxBuf[MG_UART_NUM_MAX][MG_RX_BUF_SIZE];

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
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
void UARTPRT_vInit(void)
{
  uint16 u16BaudRate;
	uint32 u32Loop;

	for(u32Loop=0;u32Loop<MG_UART_NUM_MAX;u32Loop++)
	{
		mg_uUartPrtData[u32Loop].u16TxDataCnt = 0;
		mg_uUartPrtData[u32Loop].u16RxDataCnt = 0;
		mg_uUartPrtData[u32Loop].u16TxDataNbr = 0;
		mg_uUartPrtData[u32Loop].u16RxDataNbr = 0;	
		mg_uUartPrtData[u32Loop].u16RxCrc = CRC_INIT_02;
		mg_uUartPrtData[u32Loop].uStatus.ALL = 0;
		mg_uUartPrtData[u32Loop].uCtrl.ALL = 0;
		
		mg_uUartPrtData[u32Loop].uCtrl.Bit.bByteTmoutFlg  = TRUE;
		mg_uUartPrtData[u32Loop].uCtrl.Bit.bFrameTmoutFlg = TRUE;
		mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxTmoutFlg    = TRUE;
		

		u16BaudRate = UARTPRT_scfg_u16UartReadBaudrate(u32Loop);

		if (MG_BAUDRATE_4800 == u16BaudRate)
		{
			mg_u8RxTimeOutDly[u32Loop] = MG_RX_BYTE_TIMEOUT_4800;
			mg_uUartPrtData[u32Loop].u16RxByteTmOutCnt = mg_u8RxTimeOutDly[u32Loop];
			mg_u8RxFrameTimeOutDly[u32Loop] = MG_UART_RX_FRAME_TIMEOUT_4800; 
			mg_uUartPrtData[u32Loop].u16RxFrameTmOutCnt = mg_u8RxFrameTimeOutDly[u32Loop];
			mg_u8TxTimeOutDly[u32Loop] = MG_UART_TX_TIMEOUT_4800;
			mg_uUartPrtData[u32Loop].u16TxTmOutCnt = mg_u8TxTimeOutDly[u32Loop];
		}
		else if (MG_BAUDRATE_38400 == u16BaudRate)
		{
			mg_u8RxTimeOutDly[u32Loop] = MG_RX_BYTE_TIMEOUT_38400;
			mg_uUartPrtData[u32Loop].u16RxByteTmOutCnt = mg_u8RxTimeOutDly[u32Loop];
			mg_u8RxFrameTimeOutDly[u32Loop] = MG_UART_RX_FRAME_TIMEOUT_38400; 
			mg_uUartPrtData[u32Loop].u16RxFrameTmOutCnt = mg_u8RxFrameTimeOutDly[u32Loop];
			mg_u8TxTimeOutDly[u32Loop] = MG_UART_TX_TIMEOUT_38400;
			mg_uUartPrtData[u32Loop].u16TxTmOutCnt = mg_u8TxTimeOutDly[u32Loop];
		}
		else
		{
			mg_u8RxTimeOutDly[u32Loop] = MG_RX_BYTE_TIMEOUT_38400;
			mg_uUartPrtData[u32Loop].u16RxByteTmOutCnt = mg_u8RxTimeOutDly[u32Loop];
			mg_u8RxFrameTimeOutDly[u32Loop] = MG_UART_RX_FRAME_TIMEOUT_38400; 
			mg_uUartPrtData[u32Loop].u16RxFrameTmOutCnt = mg_u8RxFrameTimeOutDly[u32Loop];
			mg_u8TxTimeOutDly[u32Loop] = MG_UART_TX_TIMEOUT_38400;
			mg_uUartPrtData[u32Loop].u16TxTmOutCnt = mg_u8TxTimeOutDly[u32Loop];
		}
		
		mg_u16Crc[u32Loop] = CRC_INIT_02;
		
		mg_au8SlaveAddress[u32Loop] = au8SlaveAddr[u32Loop];
		
			/* Read local MCU address */
		mg_uUartPrtData[u32Loop].u8SlaveAddr = mg_au8SlaveAddress[u32Loop];
  }
}

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
void UARTPRT_vDeInit(void)
{
  
}

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
void UARTPRT_vHandleTxData(void)
{
	uint32 u32Loop;
	
	for(u32Loop=0;u32Loop<MG_UART_NUM_MAX;u32Loop++)
	{
		if ((FALSE == mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxBufUpdated)       &&    /* Last frame has been TX */
				(((FALSE == mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxNewFrame)&&           /* Rx have finished */
				  (FALSE != mg_uUartPrtData[u32Loop].uCtrl.Bit.bByteTmoutFlg))||        /* Rx byte time out*/
				 (FALSE != mg_uUartPrtData[u32Loop].uCtrl.Bit.bFrameTmoutFlg)   ) &&    /* Rx Frame time out */
				(FALSE != mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxTmoutFlg)               /* Last time Tx have time out */
			 )
		{
			/* Clear Rx and Tx monitor timeout flag */
			mg_uUartPrtData[u32Loop].uCtrl.Bit.bFrameTmoutFlg = FALSE;
			mg_uUartPrtData[u32Loop].uCtrl.Bit.bByteTmoutFlg  = FALSE;
			mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxTmoutFlg    = FALSE;
			mg_uUartPrtData[u32Loop].uCtrl.Bit.bAddrMatch     = FALSE;
			mg_uUartPrtData[u32Loop].u16TxDataNbr             = 0;

			mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataNbr++] = MG_FRAME_STX; /* STX */
			mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataNbr++] = mg_uUartPrtData[u32Loop].u8SlaveAddr; /* ADDR */
			mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataNbr++] = 0; /* dummy LEN */
			mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataNbr++] = mg_uUartPrtData[u32Loop].uStatus.ALL; /* DATA0 is fixed for Comm status */

			UARTPRT_cfg_vIntComTxData(u32Loop,mg_au8UartTxBuf[u32Loop], &mg_uUartPrtData[u32Loop].u16TxDataNbr); /* Load application data to TX buffer */

			/* Calculate crc when TX data byte, add dummy crc here */
			mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataNbr++] = CRC_INIT_02; /* dummy CRC16 */
			mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataNbr++] = CRC_INIT_02; /* dummy CRC16 */
			
			mg_au8UartTxBuf[u32Loop][2] = mg_uUartPrtData[u32Loop].u16TxDataNbr - MG_FRAME_AUX_LEN; /* Fill LEN in TX buffer */
			
			mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxBufUpdated = TRUE; /* Begin to TX */
		}
	}
}

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
void UARTPRT_vHandleRxData(void)
{
  uint8 u8FrameCheckOk;
  uint8 u8BroadcastFlg;
	uint32 u32Loop;

	for(u32Loop=0;u32Loop<MG_UART_NUM_MAX;u32Loop++)
	{
		u8FrameCheckOk = FALSE; /* In order to judge uart fail */
		if (mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxNewFrame) /* A new frame received */
		{
			/* Check frame start */  
			if (MG_FRAME_STX != mg_au8UartRxBuf[u32Loop][0]) /* Check STX */
			{
				mg_uUartPrtData[u32Loop].uStatus.Bit.u8InvalidData = TRUE;
			} 
			else if (mg_uUartPrtData[u32Loop].u8SlaveAddr != mg_au8UartRxBuf[u32Loop][1]) /* Check MCU address */
			{
				mg_uUartPrtData[u32Loop].uStatus.Bit.u8McuAddrErr = TRUE;
			}  
			else if (mg_uUartPrtData[u32Loop].u16RxDataNbr != mg_au8UartRxBuf[u32Loop][2] + MG_FRAME_AUX_LEN) /* Check length of data */
			{
				mg_uUartPrtData[u32Loop].uStatus.Bit.u8LenErr = TRUE;
			}   
			else
			{
				if (mg_uUartPrtData[u32Loop].u16RxCrc) /* Check frame crc16 */
				{
					mg_uUartPrtData[u32Loop].uStatus.Bit.u8CrcErr = TRUE;
				}
				else
				{
					u8FrameCheckOk = TRUE;
				}
			}
			/* Check frame end */
			mg_uUartPrtData[u32Loop].u16RxCrc = CRC_INIT_02;
			mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxNewFrame = FALSE; /* Begin to fill TX buffer */
		}

		/* Frame format is correct, Handle data */
		if (u8FrameCheckOk) 
		{
			/* Clear UART status once on the first successful RX */
			if (FALSE == mg_uUartPrtData[u32Loop].uCtrl.Bit.bUartStaClrFlg)
			{
				mg_uUartPrtData[u32Loop].uStatus.ALL = 0;
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bUartStaClrFlg = TRUE;
			}
			
			UARTPRT_cfg_vIntComRxData(u32Loop,mg_au8UartRxBuf[u32Loop], u8BroadcastFlg, MG_UART_STATUS_BYTE_CTR); /* Handle application data */
		}
  }
}

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
void UARTPRT_vTxData(void)
{ 
  static WORD_VAL u16CrcTemp[MG_UART_NUM_MAX];
	uint32 u32Loop;

	for(u32Loop=0;u32Loop<MG_UART_NUM_MAX;u32Loop++)
	{
		if (FALSE != mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxBufUpdated) /* Txbuf array is updated */
		{
			if (UARTPRT_scfg_u8UartReadTxEmptyFlg(u32Loop)) /* Last data TX is complete */
			{
				if (mg_uUartPrtData[u32Loop].u16TxDataCnt < mg_uUartPrtData[u32Loop].u16TxDataNbr)
				{
					if (mg_uUartPrtData[u32Loop].u16TxDataCnt == mg_uUartPrtData[u32Loop].u16TxDataNbr - 2u)
					{
						u16CrcTemp[u32Loop].u16Val = mg_u16Crc[u32Loop];
						mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataCnt] = u16CrcTemp[u32Loop].Bytes.LB; /* Add real crc16 into TxBuf */
					}
					else if (mg_uUartPrtData[u32Loop].u16TxDataCnt == mg_uUartPrtData[u32Loop].u16TxDataNbr - 1u)
					{
						mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataCnt] = u16CrcTemp[u32Loop].Bytes.HB; /* Add real crc16 into TxBuf */
					}				
					else
					{
						mg_u16Crc[u32Loop] = CRC_u16GetCrc16(mg_u16Crc[u32Loop], mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataCnt]);
					}
					UARTPRT_scfg_vUartWriteTxReg(u32Loop,mg_au8UartTxBuf[u32Loop][mg_uUartPrtData[u32Loop].u16TxDataCnt++]);
				}
				else /* A frame Tx complete */
				{
					mg_u16Crc[u32Loop] = CRC_INIT_02; /* Reset crc for next frame */
					mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxBufUpdated = FALSE; /* Tx array can be updated again */
					mg_uUartPrtData[u32Loop].u16TxDataCnt = 0;
					
					/* Begin to monitor rx frame timeout */
					if((FALSE == mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxDurTxFlg))
					{
						mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxFrameTmOutEna = TRUE;
						mg_uUartPrtData[u32Loop].u16RxFrameTmOutCnt = mg_u8RxFrameTimeOutDly[u32Loop];
					}
					mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxDurTxFlg = FALSE;
					
					/* Begin to monitor TX timeout, the minimum duration between two TX */
					mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxTmOutEna = TRUE;
					mg_uUartPrtData[u32Loop].u16TxTmOutCnt = mg_u8TxTimeOutDly[u32Loop];
				}
			}
		}
  }
}

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
void UARTPRT_vUsartIrqHandler(uint8 u8UartIndex)
{
	uint8 u8Dummy;

  u8Dummy = UARTPRT_scfg_u8UartReadRxReg(u8UartIndex); /* Read RX REG */ 
	
  mg_uUartPrtData[u8UartIndex].uCtrl.Bit.bRxByteTmOutEna = FALSE; /* Stop timer */

  if (FALSE == mg_uUartPrtData[u8UartIndex].uCtrl.Bit.bRxNewFrame) /* Last frame has been handled */
  {
    mg_au8UartRxBuf[u8UartIndex][mg_uUartPrtData[u8UartIndex].u16RxDataCnt++] = u8Dummy; /* RX data */
    mg_uUartPrtData[u8UartIndex].u16RxCrc = UARTPRT_scfg_u16GetCrc16(mg_uUartPrtData[u8UartIndex].u16RxCrc, u8Dummy);

    if (mg_uUartPrtData[u8UartIndex].u16RxDataCnt < MG_RX_BUF_SIZE)
    {
      /* Begin to monitor rx byte timeout */
      mg_uUartPrtData[u8UartIndex].uCtrl.Bit.bRxByteTmOutEna = TRUE;
      mg_uUartPrtData[u8UartIndex].u16RxByteTmOutCnt = mg_u8RxTimeOutDly[1];
    }
    else /* Rx buffer if full, begin to handle frame */
    {
      mg_uUartPrtData[u8UartIndex].uCtrl.Bit.bRxByteTmOutEna = FALSE;
      mg_uUartPrtData[u8UartIndex].u16RxDataNbr = mg_uUartPrtData[u8UartIndex].u16RxDataCnt;
      mg_uUartPrtData[u8UartIndex].u16RxDataCnt = 0;
      mg_uUartPrtData[u8UartIndex].uStatus.Bit.u8ByteTmout = TRUE;
      mg_uUartPrtData[u8UartIndex].uCtrl.Bit.bRxNewFrame   = TRUE;
    }
		
    /* if slaver begins to TX when receive local address */
    if (FALSE != mg_uUartPrtData[u8UartIndex].uCtrl.Bit.bTxBufUpdated) 
    {
      mg_uUartPrtData[u8UartIndex].uCtrl.Bit.bRxDurTxFlg = TRUE;/* data received when Tx is ongoing */
    }
  }
  else /* Tx too fast, Rx buffer has not been handled */
  {
    mg_uUartPrtData[u8UartIndex].uStatus.Bit.u8InvalidData = TRUE;
  }
}
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
void UARTPRT_vTmOutMon(void)
{
	uint32 u32Loop;

	for(u32Loop=0;u32Loop<MG_UART_NUM_MAX;u32Loop++)
	{
		/* Byte timeout timer */
		if (TRUE == mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxByteTmOutEna)
		{
			if (0U < mg_uUartPrtData[u32Loop].u16RxByteTmOutCnt)
			{
				mg_uUartPrtData[u32Loop].u16RxByteTmOutCnt--;
			}
			else
			{
				/* Timeout, stop timer */
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxByteTmOutEna = FALSE;

				/* Byte timeout, new frame is received */
				mg_uUartPrtData[u32Loop].uStatus.Bit.u8ByteTmout = TRUE; /* note: this is not a fault condition */
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bByteTmoutFlg = TRUE; 
				mg_uUartPrtData[u32Loop].u16RxDataNbr = mg_uUartPrtData[u32Loop].u16RxDataCnt;
				mg_uUartPrtData[u32Loop].u16RxDataCnt = 0;
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bByteTmoutFlg = TRUE;
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxNewFrame   = TRUE; /* Begin to handle data in RX buffer */
			}
		}
			
		/* Frame timeout timer */
		if (TRUE == mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxFrameTmOutEna)
		{
			if (0U < mg_uUartPrtData[u32Loop].u16RxFrameTmOutCnt)
			{
				mg_uUartPrtData[u32Loop].u16RxFrameTmOutCnt--;
			}
			else
			{
				/* Timeout, stop timer */
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bRxFrameTmOutEna = FALSE;
				
				/* Frame timeout, no data received, if host, begin to TX again */
				mg_uUartPrtData[u32Loop].uStatus.Bit.u8FrameTmout = TRUE;
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bFrameTmoutFlg = TRUE;
			}
		}

		/* TX timeout timer */
		if (TRUE == mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxTmOutEna)
		{
			if (0U < mg_uUartPrtData[u32Loop].u16TxTmOutCnt)
			{
				mg_uUartPrtData[u32Loop].u16TxTmOutCnt--;
			}
			else
			{
				/* Timeout, stop timer */
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxTmOutEna = FALSE;
				
				/* Tx timeout, it's time to Tx next frame */
				mg_uUartPrtData[u32Loop].uCtrl.Bit.bTxTmoutFlg = TRUE;
			}
		}

  }
}

/** *****************************************************************************
 * \brief         Set boot mode 
 *
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void UARTPRT_vSetBootMode(uint8 u8Index)
{
  mg_uUartPrtData[u8Index].uStatus.Bit.u8BootMode = TRUE;
}

/*
 * End of file
 */
