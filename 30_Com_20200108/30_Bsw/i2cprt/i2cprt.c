/*******************************************************************************
 * \file    i2cprt.c
 * \brief   Init I2C
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-11-22 11:01:57 +0800 (Fri, 22 Nov 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 239 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>

/* Module header */
#define I2C_EXPORT_H
  #include "i2cprt_api.h"
  #include "i2cprt_scb.h"
  #include "i2cprt_cfg.h"
  #include "i2cprt_scfg.h"
  #include "i2cprt_conf.h"
  #include "i2cprt_rte.h"

/*******************************************************************************
 * Global data
 ******************************************************************************/
volatile static uint8 mg_u8I2cTxCnt;
volatile static uint8 mg_u8I2cRxLen;

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static GLOBAL_U_U8BIT  mg_u8I2cAddrWr;  
static GLOBAL_U_U8BIT  mg_u8I2cAddrWrOld;
static GLOBAL_U_U8BIT  mg_u8I2cAddrRd; 

static uint8 mg_u8I2cState;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
 
static void mg_vSetI2cAddress( uint8 u8Addr );

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/********************************************************************************
 * \brief         Init I2cprt module.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_vInit(void)
{
  uint8 u8Cnt;

  for (u8Cnt = 0; u8Cnt < I2CPRT_CONF_RX_BUF_SIZE; u8Cnt++) 
  {
    I2CPRT_CFG_au8I2cRxBuf[u8Cnt] = 0x00;
  }
  
  for (u8Cnt = 0; u8Cnt < I2CPRT_CONF_TX_BUF_SIZE; u8Cnt++)
  {
    I2CPRT_Rte_Write_P_u8TxBuf(0x00,u8Cnt);
  }

  I2CPRT_Rte_Write_P_u8I2cPEC(0x00);
  I2CPRT_Rte_Write_P_u8PecErrCmd(0x00);
  I2CPRT_Rte_Write_P_u8I2cTxLen(0x00);
  I2CPRT_Rte_Write_P_u8I2cRxCnt(0x00);
  I2CPRT_Rte_Write_P_u8I2cExpTxCnt(0x00);
  I2CPRT_Rte_Write_P_u8I2cExpRxCnt(0x00); 
	
	mg_u8I2cTxCnt             = 0x00;
  mg_u8I2cAddrWr.ALL        = I2CPRT_CFG_BASE_SLA_ADR;
  mg_u8I2cAddrRd.ALL        = mg_u8I2cAddrWr.ALL + 0x01u;
} /* I2C_vI2cDataInit() */

/********************************************************************************
 * \brief         De-Init I2cprt module.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_vDeInit(void)
{
}

/********************************************************************************
 * \brief         if the slave address is not fixed check 
 *                the address every 10ms in schm.c.
 * \param[in]     u8DlyEn   Delay is for anti-shake
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_vUpdateI2cAddress( uint8 u8DlyEn )
{
  static uint8  u8AddrMatchDly = 0;
	GLOBAL_U_U8BIT uI2cAddr;

	uI2cAddr.ALL = mg_u8I2cAddrWr.ALL;
  uI2cAddr.Bits.f1 = I2CPRT_RTE_Read_B_R_I2C_ADDRESS0(); 
  uI2cAddr.Bits.f2 = I2CPRT_RTE_Read_B_R_I2C_ADDRESS1(); 
	/* Nokia sHUB only A0&A1 */
  uI2cAddr.Bits.f3 = 1;//I2CPRT_RTE_Read_B_R_I2C_ADDRESS2();
	
  mg_u8I2cAddrWr.ALL = uI2cAddr.ALL;
	
  if (FALSE == u8DlyEn) 
  {
    mg_vSetI2cAddress( mg_u8I2cAddrWr.ALL );
    mg_u8I2cAddrRd.ALL = mg_u8I2cAddrWr.ALL + 1u;
    mg_u8I2cAddrWrOld.ALL = mg_u8I2cAddrWr.ALL;
  }
  else 
  {
    if (mg_u8I2cAddrWrOld.ALL != mg_u8I2cAddrWr.ALL) 
    {
      if (u8AddrMatchDly > 30u)
      { /*delay 200ms */
        mg_u8I2cAddrWrOld.ALL = mg_u8I2cAddrWr.ALL;
        mg_u8I2cAddrRd.ALL = mg_u8I2cAddrWr.ALL + 1u;
        mg_vSetI2cAddress( mg_u8I2cAddrWr.ALL );
      }
      else
      {
        u8AddrMatchDly ++;
      }
    }
    else
    {
      u8AddrMatchDly = 0;
    }
  }  
}

/********************************************************************************
 * \brief         I2C interrupt. called in int.c when there is an interrupt.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_CFG_vI2cIsr( void ) 
{
	uint8 u8I2cRxCnt;
	uint8 u8I2cTxLen;
	uint8 u8I2cPEC;
  
  uint32 u32Isr;
  
  
	u32Isr = I2C1->ISR;
  
	I2CPRT_SCFG_vClearTimeoutCnt();     /* clear timerout timer */
  
	if(u32Isr & I2C_IT_OVR) //(I2CPRT_SCFG_eGetRxOVRFlg())          /* Overrun error detect */
	{
		I2CPRT_SCFG_vClearRxOVRFlg();        /* clear interrupt flag */
	}
	else if(u32Isr & I2C_IT_ARLO) // (I2CPRT_SCFG_eGetRxARLOFlg())          /* Arbitration lost interrupt */
	{
		I2CPRT_SCFG_vClearRxARLOFlg();        /* clear interrupt flag */
	}
	else if(u32Isr & I2C_IT_BERR) // (I2CPRT_SCFG_eGetRxBERRFlg())          /* Bus error interrupt */
	{
		I2CPRT_SCFG_vClearRxBERRFlg();        /* clear interrupt flag */
	}
	else if(u32Isr & I2C_IT_NACKF) //  (I2CPRT_SCFG_eGetNACKFlg())          /* Bus error interrupt */
	{
		I2CPRT_SCFG_vClearNACKFlg();        /* clear interrupt flag */
	}
  else
  {
    if (mg_u8I2cState == I2CPRT_CFG_E_I2C_IDLE)
    {
      I2CPRT_Rte_Write_P_u8I2cTxLen(0x00);
      I2CPRT_Rte_Write_P_u8I2cRxCnt(0x00);
      I2CPRT_Rte_Write_P_u8I2cExpTxCnt(0x00);
      I2CPRT_Rte_Write_P_u8I2cExpRxCnt(0x00); 
      I2CPRT_Rte_Write_P_u8I2cPEC(0x00);
      mg_u8I2cTxCnt = 0;
    }

    if(u32Isr & I2C_IT_ADDR) // (I2CPRT_SCFG_eGetRxADDRFlg())
    {
      I2CPRT_SCFG_vClearRxADDRFlg();
      if(I2CPRT_SCFG_u16TransferDirection())
      {
        /* Last received byte is slave address */
        I2CPRT_Rte_Write_P_u8I2cTxLen(0x00);
        mg_u8I2cTxCnt = 0;

        if(I2CPRT_RTE_Read_B_R_PEC_Enable())
        {
          I2CPRT_Rte_Write_P_u8I2cPEC(I2CPRT_SCFG_u8GetCrc8(RTE_u8I2cPEC, mg_u8I2cAddrRd.ALL));
        }
        I2CPRT_SCFG_vPMBusSendData();
        mg_u8I2cState = I2CPRT_CFG_E_I2C_READ;
      }
      else
      {
        I2CPRT_SCFG_vClearTxEFlg();    /* start a new frame, clear the TXDR register */
        /* Slave address match and slave ACK */
        if (mg_u8I2cState != I2CPRT_CFG_E_I2C_IDLE) 
        { 
          /* Cmd process not finished then next cmd is coming , or page and write/read */
          if ((mg_u8I2cState == I2CPRT_CFG_E_I2C_READ)
            || (mg_u8I2cState == I2CPRT_CFG_E_I2C_WRITE)
            || (mg_u8I2cState == I2CPRT_CFG_E_I2C_BLOCK_WRITE)) 
          {
            I2CPRT_RTE_Write_B_P_CMD_WAIT_FLG(TRUE);
            I2CPRT_vProcessReceiveData();
          }
          I2CPRT_Rte_Write_P_u8I2cTxLen(0x00);
          mg_u8I2cTxCnt = 0;
          I2CPRT_Rte_Write_P_u8I2cRxCnt(0x00);
        }

        /* Calculate the PEC if supported */
        if(I2CPRT_RTE_Read_B_R_PEC_Enable())
        {
          I2CPRT_Rte_Write_P_u8I2cPEC(I2CPRT_SCFG_u8GetCrc8(0x00, mg_u8I2cAddrWr.ALL));
        }

        mg_u8I2cState = I2CPRT_CFG_E_I2C_WRITE;
      }
    }
    else if(u32Isr & I2C_IT_RXNE) //(I2CPRT_SCFG_eGetRxNEFlg() )
    {
      uint8 u8Data;
      
      u8Data = I2CPRT_SCFG_u8ReadData();         /* Get received byte, reset RBF flag */; 
                                              
      /* Write operation, input to slave */
      /* Calculate the PEC if supported */
      if(I2CPRT_RTE_Read_B_R_PEC_Enable())
      {
        I2CPRT_Rte_Write_P_u8I2cPEC(I2CPRT_SCFG_u8GetCrc8(RTE_u8I2cPEC, u8Data));
      }

      I2CPRT_Rte_Read_R_u8I2cRxCnt(&u8I2cRxCnt);
      /* Last received byte is data */
      if (mg_u8I2cState == I2CPRT_CFG_E_I2C_WRITE)
      {
        if (u8I2cRxCnt < I2C_RX_BUF_SIZE)
        {
          I2CPRT_CFG_au8I2cRxBuf[u8I2cRxCnt] = u8Data;
          I2CPRT_Rte_Write_P_u8I2cRxCnt(u8I2cRxCnt+1u);
          I2CPRT_SCFG_vCmdCheck();
        }
      }
      else if (mg_u8I2cState == I2CPRT_CFG_E_I2C_BLOCK_WRITE)
      {
        I2CPRT_Rte_Write_P_u8I2cExpRxCnt(u8Data + 2u);    /* Block Write, Page_Plus_Wr/Rd: cmd + cnt */
        I2CPRT_CFG_au8I2cRxBuf[u8I2cRxCnt] = u8Data;
        I2CPRT_Rte_Write_P_u8I2cRxCnt(u8I2cRxCnt+1u);
        mg_u8I2cState = I2CPRT_CFG_E_I2C_WRITE;
      }
    } 
    else if(u32Isr & I2C_IT_TXIS) //(I2CPRT_SCFG_eGetTxISFlg())
    {
      uint8 u8data;
      /* Read operation, output from slave */
      /* Last received byte is data */
      I2CPRT_Rte_Read_R_u8I2cTxLen(&u8I2cTxLen);
      if ((u8I2cTxLen != 0) 
          && (mg_u8I2cTxCnt <= u8I2cTxLen)) 
      {
        if (mg_u8I2cTxCnt == u8I2cTxLen) 
        {
          if(I2CPRT_RTE_Read_B_R_PEC_Enable())
          {
            I2CPRT_Rte_Read_R_u8I2cPEC(&u8I2cPEC);
            I2CPRT_Rte_Write_P_u8TxBuf(u8I2cPEC,mg_u8I2cTxCnt);
          }
          else
          {
            I2CPRT_Rte_Write_P_u8TxBuf(I2CPRT_CFG_I2C_DEFAULT_VAL,mg_u8I2cTxCnt);
          }
        }
        u8data = I2CPRT_Rte_Read_R_u8TxBuf(mg_u8I2cTxCnt);
        mg_u8I2cTxCnt++;
      } /* end else */ 
      else
      {
        u8data = I2CPRT_CFG_I2C_DEFAULT_VAL;
      }
      
      I2CPRT_SCFG_u8WriteData(u8data); 	

      /* Calculate the PEC if supported */
      if(I2CPRT_RTE_Read_B_R_PEC_Enable())
      {
        I2CPRT_Rte_Write_P_u8I2cPEC(I2CPRT_SCFG_u8GetCrc8(RTE_u8I2cPEC, u8data)); 
      }
    }
  }
} /* I2C_vI2cIsr */

/********************************************************************************
 * \brief         Detect Stop bit and check wait flag to handle received frame 
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void I2CPRT_vProcessReceiveData( void )
{
	uint8 u8I2cRxCnt;
	uint8 u8I2cExpRxCnt;
	uint8 u8I2cPEC;
	uint8 u8PMBusCmd;
	
	
  if (I2CPRT_SCFG_eGetRxSTOPFlg() || I2CPRT_RTE_Read_B_R_CMD_WAIT_FLG()) 
  {
		I2CPRT_RTE_Write_B_P_CMD_DETECTED(FALSE);
		
		I2CPRT_SCFG_vDisableInt();        		     /* Disable I2C interrupt */

		I2CPRT_Rte_Read_R_u8I2cRxCnt(&u8I2cRxCnt);
		I2CPRT_Rte_Read_R_u8I2cExpRxCnt(&u8I2cExpRxCnt);
		I2CPRT_Rte_Read_R_u8I2cPEC(&u8I2cPEC);
    if ((u8I2cRxCnt > 0) &&
        ((mg_u8I2cState == I2CPRT_CFG_E_I2C_WRITE)  ||
         (mg_u8I2cState == I2CPRT_CFG_E_I2C_BLOCK_WRITE))
		   ) 
    {
      if (u8I2cRxCnt == u8I2cExpRxCnt)  /* Correct byte count */
      {
        if (0U == u8I2cPEC)                 /* PEC is correct */
        {     
          if(TRUE == I2CPRT_RTE_Read_B_R_PEC_ERR_FLG()) 
          {
            I2CPRT_RTE_Write_B_P_PEC_ERR_FLG(FALSE);
            I2CPRT_RTE_Write_B_P_PEC_CHANGE_FLG(TRUE);
          }
          
          I2CPRT_SCFG_vPMBusHandleData(); 
        }
        else 
        {
          if(FALSE == I2CPRT_RTE_Read_B_R_PEC_ERR_FLG()) 
          { 
            I2CPRT_RTE_Write_B_P_PEC_ERR_FLG(TRUE);
            I2CPRT_RTE_Write_B_P_PEC_CHANGE_FLG(TRUE);
						I2CPRT_Rte_Read_R_u8PMBusCmd(&u8PMBusCmd);
            I2CPRT_Rte_Write_P_u8PecErrCmd(u8PMBusCmd);
						I2CPRT_RTE_Write_B_P_PMBUS_PEC_FAULT(TRUE);
          }
        }
      }
      I2CPRT_Rte_Write_P_u8I2cRxCnt(0x00);           
    } 
    if(I2CPRT_SCFG_eGetRxSTOPFlg())
    {
      I2CPRT_SCFG_vClearRxSTOPFlg();
      mg_u8I2cState = I2CPRT_CFG_E_I2C_IDLE; 
    }
    I2CPRT_SCFG_vEnableInt();              /* Enable I2C interrupt */
    I2CPRT_RTE_Write_B_P_CMD_WAIT_FLG(FALSE);
  } /* end if */
} /* I2CPRT_vProcessReceiveData() */

void I2CPRT_vSetI2cState(uint8 u8State)
{
	mg_u8I2cState = u8State;
}
/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/********************************************************************************
 * \brief         set I2C slave address
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vSetI2cAddress( uint8 u8Addr )
{
  I2CPRT_SCFG_vDisableOAR1();   /* Address bits can be written only when OA1EN=0(DISABLE) */
  I2CPRT_SCFG_vSetOAR1(u8Addr);   
  I2CPRT_SCFG_vEnableOAR1();   /* After change the Addr, set OA1EN=1(ENABLE). This operation only supply on STM32 MCU*/
}

/* End of file */
