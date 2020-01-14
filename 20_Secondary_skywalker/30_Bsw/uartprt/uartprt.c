/** *****************************************************************************
 * \file    uartprt.c
 * \brief   UART communication protocol
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

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "debug_llc.h"

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
    uint8 u8RxByteTmOutEna   : 1;   /* bit0 */
    uint8 u8ByteTmoutFlg     : 1;   /* bit1 */
    uint8 u8TxBufUpdated     : 1;   /* bit2 */
    uint8 u8RxNewFrame       : 1;   /* bit3 */
    uint8 u8UartStaClrFlg    : 1;   /* bit4 */
    uint8 u8AddrMatch        : 1;   /* bit5 */
    uint8 u8Reserved         : 2;   /* bit6~7 */
  } Bit;
  uint8 ALL;
} MG_U_UARTPRT_CTRL; 

typedef struct MG_S_UARTPRT_DATA_
{
  uint16 u16TxDataCnt;
  uint16 u16RxDataCnt;
  uint16 u16RxByteTmOutCnt;
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

static MG_S_UARTPRT_DATA UARTPRT_mg_uUartPrtData;

static uint8 UARTPRT_mg_u8RxTimeOutDly;
static uint8 UARTPRT_mg_au8UartTxBuf[MG_TX_BUF_SIZE];
uint8 UARTPRT_mg_au8UartRxBuf[MG_RX_BUF_SIZE];

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
  uint16 u16GpioRead = 0U;
  uint16 u16GpioReadCtr = 0U;

  UARTPRT_mg_uUartPrtData.u16TxDataCnt = 0U;
  UARTPRT_mg_uUartPrtData.u16RxDataCnt = 0U;
  UARTPRT_mg_uUartPrtData.u16TxDataNbr = 0U;
  UARTPRT_mg_uUartPrtData.u16RxDataNbr = 0U;  
  UARTPRT_mg_uUartPrtData.u16RxCrc = CRC_INIT_02;
  UARTPRT_mg_uUartPrtData.uStatus.ALL = 0U;
  UARTPRT_mg_uUartPrtData.uCtrl.ALL = 0U;

  u16BaudRate = UARTPRT_scfg_u16UartReadBaudrate();

  if (MG_BAUDRATE_4800 == u16BaudRate)
  {
    UARTPRT_mg_u8RxTimeOutDly = MG_RX_BYTE_TIMEOUT_4800;
    UARTPRT_mg_uUartPrtData.u16RxByteTmOutCnt = UARTPRT_mg_u8RxTimeOutDly;
  }
  else if (MG_BAUDRATE_38400 == u16BaudRate)
  {
    UARTPRT_mg_u8RxTimeOutDly = MG_RX_BYTE_TIMEOUT_38400;
    UARTPRT_mg_uUartPrtData.u16RxByteTmOutCnt = UARTPRT_mg_u8RxTimeOutDly;
  }
  else
  {
    UARTPRT_mg_u8RxTimeOutDly = MG_RX_BYTE_TIMEOUT_38400;
    UARTPRT_mg_uUartPrtData.u16RxByteTmOutCnt = UARTPRT_mg_u8RxTimeOutDly;
  }

  /* Average the address GPIO reading */
  for (u16GpioReadCtr = 0U; u16GpioReadCtr <= MG_ADDR_DETECT_CTR; u16GpioReadCtr++)
  {
    u16GpioRead = u16GpioRead + UARTPRT_scfg_u8ReadGpioPortUartAddr();
  }

  /* Read local MCU address */
#if (TRUE == MG_SLAVE_LOCATION_PRI)
  if ((MG_ADDR_DETECT_CTR >> 1) < u16GpioRead)
  {
    UARTPRT_mg_uUartPrtData.u8SlaveAddr = MG_ADDR_PRI_2;
  }
  else
  {
    UARTPRT_mg_uUartPrtData.u8SlaveAddr = MG_ADDR_PRI_1;
  }
#else
  if ((MG_ADDR_DETECT_CTR >> 1) < u16GpioRead)
  {
    UARTPRT_mg_uUartPrtData.u8SlaveAddr = MG_ADDR_SEC_2;
  }
  else
  {
    UARTPRT_mg_uUartPrtData.u8SlaveAddr = MG_ADDR_SEC_1;
  }
#endif
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
#if (TRUE == MG_TX_ONCE_RX_ADDR)
  /* Slaver begins to TX when RX local address rather than RX whole frame */
  if (UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8AddrMatch)    /* COM TX to Local MCU */
#else
  /* Slaver begins to TX when RX buf has been handled or frame */
  if ((UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8ByteTmoutFlg) && (!(UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxNewFrame)) && /* RX buf was handled */
      (UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8AddrMatch)) /* COM TX to Local MCU, not broadcast */
#endif
  {
    if (!(UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8TxBufUpdated)) /* Last frame has been TX */
    {
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8ByteTmoutFlg = FALSE;
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8AddrMatch = FALSE;
      UARTPRT_mg_uUartPrtData.u16TxDataNbr = 0U;

      UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataNbr++] = MG_FRAME_STX; /* STX */
      UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataNbr++] = UARTPRT_mg_uUartPrtData.u8SlaveAddr; /* ADDR */
      UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataNbr++] = 0U; /* dummy LEN */
      UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataNbr++] = UARTPRT_mg_uUartPrtData.uStatus.ALL; /* DATA0 is fixed for Comm status */

      UARTPRT_cfg_vIntComTxData(UARTPRT_mg_au8UartTxBuf, &UARTPRT_mg_uUartPrtData.u16TxDataNbr); /* Load application data to TX buffer */

      /* Calculate crc when TX data byte, add dummy crc here */
      UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataNbr++] = CRC_INIT_02; /* dummy CRC16 */
      UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataNbr++] = CRC_INIT_02; /* dummy CRC16 */
      
      UARTPRT_mg_au8UartTxBuf[2] = UARTPRT_mg_uUartPrtData.u16TxDataNbr - MG_FRAME_AUX_LEN; /* Fill LEN in TX buffer */
      
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8TxBufUpdated = TRUE; /* Begin to TX */
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
  
  u8FrameCheckOk = FALSE; /* In order to judge uart fail */
  if (UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxNewFrame) /* A new frame received */
  {
    /* Check frame start */  
    if (MG_FRAME_STX != UARTPRT_mg_au8UartRxBuf[0]) /* Check STX */
    {
      UARTPRT_mg_uUartPrtData.uStatus.Bit.u8InvalidData = TRUE;
    } 
    else if ((UARTPRT_mg_uUartPrtData.u8SlaveAddr != UARTPRT_mg_au8UartRxBuf[1]) && /* Check MCU address */
             (MG_SLAVE_BROADCAST_ADDR != UARTPRT_mg_au8UartRxBuf[1]))
    {
      UARTPRT_mg_uUartPrtData.uStatus.Bit.u8McuAddrErr = TRUE;
    }  
    else if (UARTPRT_mg_uUartPrtData.u16RxDataNbr != UARTPRT_mg_au8UartRxBuf[2] + MG_FRAME_AUX_LEN) /* Check length of data */
    {
      UARTPRT_mg_uUartPrtData.uStatus.Bit.u8LenErr = TRUE;
    }   
    else
    {
      if (UARTPRT_mg_uUartPrtData.u16RxCrc) /* Check frame crc16 */
      {
        UARTPRT_mg_uUartPrtData.uStatus.Bit.u8CrcErr = TRUE;
      }
      else
      {
        u8FrameCheckOk = TRUE;
      }
    }
    /* Check frame end */
    UARTPRT_mg_uUartPrtData.u16RxCrc = CRC_INIT_02;
    UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxNewFrame = FALSE; /* Begin to fill TX buffer */
  }

  /* Frame format is correct, Handle data */
  if (u8FrameCheckOk) 
  {
    /* Clear UART status once on the first successful RX */
    if (FALSE == UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8UartStaClrFlg)
    {
      UARTPRT_mg_uUartPrtData.uStatus.ALL = 0U;
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8UartStaClrFlg = TRUE;
    }
    
#if (FALSE == MG_TX_ONCE_RX_ADDR)    
    if (UARTPRT_mg_uUartPrtData.u8SlaveAddr == UARTPRT_mg_au8UartRxBuf[1]) /* COM TX to local MCU */
    {
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8AddrMatch = TRUE;  
    }
#endif

    if (MG_SLAVE_BROADCAST_ADDR == UARTPRT_mg_au8UartRxBuf[1])
    {
      u8BroadcastFlg = TRUE;
    }
    else
    {
      u8BroadcastFlg = FALSE;
    }
    UARTPRT_cfg_vIntComRxData(UARTPRT_mg_au8UartRxBuf, u8BroadcastFlg, MG_UART_STATUS_BYTE_CTR); /* Handle application data */
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
  static uint16 u16Crc = CRC_INIT_02;
  static GLOBAL_WORD_VAL u16CrcTemp;
  
  if (UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8TxBufUpdated) /* Txbuf array is updated */
  {
    if (UARTPRT_scfg_u8UartReadTxEmptyFlg()) /* Last data TX is complete */
    {
      if (UARTPRT_mg_uUartPrtData.u16TxDataCnt < UARTPRT_mg_uUartPrtData.u16TxDataNbr)
      {
        if (UARTPRT_mg_uUartPrtData.u16TxDataCnt == UARTPRT_mg_uUartPrtData.u16TxDataNbr - 2U)
        {
          u16CrcTemp.u16Val = u16Crc;
          UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataCnt] = u16CrcTemp.Bytes.LB; /* Add real crc16 into TxBuf */
        }
        else if (UARTPRT_mg_uUartPrtData.u16TxDataCnt == UARTPRT_mg_uUartPrtData.u16TxDataNbr - 1U)
        {
          UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataCnt] = u16CrcTemp.Bytes.HB; /* Add real crc16 into TxBuf */
        }        
        else
        {
          u16Crc = CRC_u16GetCrc16(u16Crc, UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataCnt]);
        }
        UARTPRT_scfg_vUartWriteTxReg(UARTPRT_mg_au8UartTxBuf[UARTPRT_mg_uUartPrtData.u16TxDataCnt++]);
      }
      else /* A frame Tx complete */
      {
        u16Crc = CRC_INIT_02; /* Reset crc for next frame */
        UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8TxBufUpdated = FALSE; /* Tx array can be updated again */
        UARTPRT_mg_uUartPrtData.u16TxDataCnt = 0U;
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
void UARTPRT_vUsart2IrqHandler(void)
{
  uint8 u8Dummy;

  u8Dummy = UARTPRT_scfg_u8UartReadRxReg(); /* Read RX REG */   
  UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxByteTmOutEna = FALSE; /* Stop timer */

  if (!(UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxNewFrame)) /* Last frame has been handled */
  {
    UARTPRT_mg_au8UartRxBuf[UARTPRT_mg_uUartPrtData.u16RxDataCnt++] = u8Dummy; /* RX data */
    UARTPRT_mg_uUartPrtData.u16RxCrc = UARTPRT_scfg_u16GetCrc16(UARTPRT_mg_uUartPrtData.u16RxCrc, u8Dummy);

#if (TRUE == MG_TX_ONCE_RX_ADDR)
    if (2U == UARTPRT_mg_uUartPrtData.u16RxDataCnt)
    {
      if ((MG_FRAME_STX == UARTPRT_mg_au8UartRxBuf[0]) &&
          (UARTPRT_mg_uUartPrtData.u8SlaveAddr == UARTPRT_mg_au8UartRxBuf[1]))
      {
        UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8AddrMatch = TRUE; /* Begin to TX once receive local address */
      }
    }
#endif

    if (UARTPRT_mg_uUartPrtData.u16RxDataCnt < MG_RX_BUF_SIZE)
    {
      /* Begin to monitor rx byte timeout */
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxByteTmOutEna = TRUE;
      UARTPRT_mg_uUartPrtData.u16RxByteTmOutCnt = UARTPRT_mg_u8RxTimeOutDly;
    }
    else /* Rx buffer if full, begin to handle frame */
    {
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxByteTmOutEna = FALSE;
      UARTPRT_mg_uUartPrtData.u16RxDataNbr = UARTPRT_mg_uUartPrtData.u16RxDataCnt;
      UARTPRT_mg_uUartPrtData.u16RxDataCnt = 0U;
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8ByteTmoutFlg = TRUE;
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxNewFrame = TRUE;
    }
  }
  else /* Tx too fast, Rx buffer has not been handled */
  {
    UARTPRT_mg_uUartPrtData.uStatus.Bit.u8InvalidData = TRUE;
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
  /* Byte timeout timer */
  if (TRUE == UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxByteTmOutEna)
  {
    if (0U < UARTPRT_mg_uUartPrtData.u16RxByteTmOutCnt)
    {
      UARTPRT_mg_uUartPrtData.u16RxByteTmOutCnt--;
    }
    else
    {
      /* Timeout, stop timer */
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxByteTmOutEna = FALSE;

      /* Byte timeout, new frame is received */
      UARTPRT_mg_uUartPrtData.uStatus.Bit.u8ByteTmout = TRUE; /* note: this is not a fault condition */
      UARTPRT_mg_uUartPrtData.u16RxDataNbr = UARTPRT_mg_uUartPrtData.u16RxDataCnt;
      UARTPRT_mg_uUartPrtData.u16RxDataCnt = 0U;
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8ByteTmoutFlg = TRUE;
      UARTPRT_mg_uUartPrtData.uCtrl.Bit.u8RxNewFrame = TRUE; /* Begin to handle data in RX buffer */
    }
  }
}


/*
 * End of file
 */
