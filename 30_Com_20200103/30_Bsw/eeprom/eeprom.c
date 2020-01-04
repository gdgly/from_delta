/** *****************************************************************************
 * \file    eeprom.c
 * \brief   MCU flash configuration
 *
 * \section AUTHOR
 *    1. Jeff.Zhou
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>

/* Module header */
#define PWM_EXPORT_H
  #include "eeprom_api.h"
  #include "eeprom_scb.h"
  #include "eeprom_cfg.h"
  #include "eeprom_scfg.h"
  #include "eeprom_rte.h"
  #include "eeprom_conf.h"
	
/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/


__IO uint16  EEPROMAddress = 0;   
__IO uint32  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
__IO uint16  EEPROMDataNum;
  
/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
static uint32 mg_u32TimeoutUserCallback(void);

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         DeInitializes peripherals used by the I2C EEPROM driver.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void EEPROM_vDeInit(void)
{
 // EEPROM_vI2cLowLevelDeInit(); 
}

/** *****************************************************************************
 * \brief         Initializes peripherals used by the I2C EEPROM driver.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void EEPROM_vInit(void)
{ 
  EEPROMAddress = EEPROM_CONF_HW_ADDRESS;      
}

/** *****************************************************************************
 * \brief         Reads a block of data from the EEPROM.
 *
 * \param[in]     ReadAddr : EEPROM's internal address to start reading from.
 *                NumByteToRead : pointer to the variable holding number of bytes to 
 *                                be read from the EEPROM.
 * \param[in,out] -
 * \param[out]    pBuffer : pointer to the buffer that receives the data read from 
 *                          the EEPROM.
 * \return        EEPROM_CONF_OK (0) if operation is correctly performed, else return value 
 *                different from EEPROM_CONF_OK (0) or the timeout user callback.
 *
 ***************************************************************************** */
uint32 EEPROM_u32ReadBuffer(uint8* pBuffer, uint16 ReadAddr, uint16 NumByteToRead)
{  
  uint32 NumbOfSingle = 0, Count = 0, DataNum = 0, StartCom = 0;
  
  /* Get number of reload cycles */
  Count = NumByteToRead / 255;  
  NumbOfSingle = NumByteToRead % 255;
  
#ifdef EEPROM_M24C08
  
  /* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }
  
  /* Send memory address */
  I2C_SendData(EEPROM_CFG_I2C, (uint8)ReadAddr);
  
#elif defined(EEPROM_M24M01) || defined(EEPROM_M24C64_32) || defined (EEPROM_M24LR64) || defined(EEPROM_M24C512) 
  
  /* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 2, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }
  
  /* Send MSB of memory address */
  I2C_SendData(EEPROM_CFG_I2C, (uint8)((ReadAddr & 0xFF00) >> 8));
  
  /* Wait until TXIS flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;  
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }
  
  /* Send LSB of memory address  */
  I2C_SendData(EEPROM_CFG_I2C, (uint8)(ReadAddr & 0x00FF));
  
#endif /*!< EEPROM_M24C08 */ 
  
  /* Wait until TC flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TC) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }  
  
  /* If number of Reload cycles is not equal to 0 */
  if (Count != 0)
  {
    /* Starting communication */
    StartCom = 1;
    
    /* Wait until all reload cycles are performed */
    while( Count != 0)
    { 
      /* If a read transfer is performed */
      if (StartCom == 0)      
      {
        /* Wait until TCR flag is set */
        EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT; 
        while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TCR) == RESET)
        {
          if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
        }
      }      
      
      /* if remains one read cycle */
      if ((Count == 1) && (NumbOfSingle == 0))
      {
        /* if starting communication */
        if (StartCom != 0)
        {
          /* Configure slave address, end mode and start condition */
          I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 255, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
        }
        else
        {
          /* Configure slave address, end mode */
          I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 255, I2C_AutoEnd_Mode, I2C_No_StartStop);          
        }
      }
      else 
      {
        /* if starting communication */
        if (StartCom != 0)
        {
          /* Configure slave address, end mode and start condition */
          I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 255, I2C_Reload_Mode, I2C_Generate_Start_Read);
        }
        else
        {
          /* Configure slave address, end mode */
          I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 255, I2C_Reload_Mode, I2C_No_StartStop);          
        } 
      }
      
      /* Update local variable */
      StartCom = 0;      
      DataNum = 0;
      
      /* Wait until all data are received */
      while (DataNum != 255)
      {        
        /* Wait until RXNE flag is set */
        EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_RXNE) == RESET)
        {
          if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
        }
        
        /* Read data from RXDR */
        pBuffer[DataNum]= I2C_ReceiveData(EEPROM_CFG_I2C);
        
        /* Update number of received data */
        DataNum++;
      }      
      /* Update Pointer of received buffer */ 
      pBuffer += DataNum;  
      
      /* update number of reload cycle */
      Count--;
    }
    
    /* If number of single data is not equal to 0 */
    if (NumbOfSingle != 0)
    {            
      /* Wait until TCR flag is set */
      EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;   
      while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TCR) == RESET)
      {
        if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
      }
      
      /* Update CR2 : set Nbytes and end mode */
      I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, (uint8)(NumbOfSingle), I2C_AutoEnd_Mode, I2C_No_StartStop);
      
      /* Reset local variable */
      DataNum = 0;
      
      /* Wait until all data are received */
      while (DataNum != NumbOfSingle)
      {        
        /* Wait until RXNE flag is set */
        EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_RXNE) == RESET)
        {
          if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
        }
        
        /* Read data from RXDR */
        pBuffer[DataNum]= I2C_ReceiveData(EEPROM_CFG_I2C);
        
        /* Update number of received data */
        DataNum++;
      } 
    }
  }
  else
  {
    /* Update CR2 : set Slave Address , set read request, generate Start and set end mode */
    I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, (uint32)(NumbOfSingle), I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
    
    /* Reset local variable */
    DataNum = 0;
    
    /* Wait until all data are received */
    while (DataNum != NumbOfSingle)
    {
      /* Wait until RXNE flag is set */
      EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT; 
      while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_RXNE) == RESET)
      {
        if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
      }
      
      /* Read data from RXDR */
      pBuffer[DataNum]= I2C_ReceiveData(EEPROM_CFG_I2C);
      
      /* Update number of received data */
      DataNum++;
    }    
  }  
  
  /* Wait until STOPF flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_STOPF) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }
  
  /* Clear STOPF flag */
  I2C_ClearFlag(EEPROM_CFG_I2C, I2C_ICR_STOPCF);
  
  /* If all operations OK, return EEPROM_CONF_OK (0) */
  return EEPROM_CONF_OK;
}

/** *****************************************************************************
 * @brief  Writes more than one byte to the EEPROM with a single WRITE cycle.
 *
 * @note   The number of bytes (combined to write start address) must not 
 *         cross the EEPROM page boundary. This function can only write into
 *         the boundaries of an EEPROM page.
 *         This function doesn't check on boundaries condition (in this driver 
 *         the function EEPROM_WriteBuffer() which calls EEPROM_WritePage() is 
 *         responsible of checking on Page boundaries).
 *
 * \param[in]     pBuffer : pointer to the buffer containing the data to be written to 
 *                          the EEPROM.
 *                WriteAddr : EEPROM's internal address to write to.
 *                NumByteToWrite : pointer to the variable holding number of bytes to 
 *                                 be written into the EEPROM.
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        EEPROM_CONF_OK (0) if operation is correctly performed, else return value 
 *                different from EEPROM_CONF_OK (0) or the timeout user callback.
 *
 ***************************************************************************** */
uint32 EEPROM_u32WritePage(const uint8* pBuffer, uint16 WriteAddr, uint8 NumByteToWrite)
{   
  uint32 DataNum = 0;
  
#ifdef EEPROM_M24C08
  
  /* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;  
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }
  
  /* Send memory address */
  I2C_SendData(EEPROM_CFG_I2C, (uint8)WriteAddr);
  
#elif defined(EEPROM_M24M01) || defined(EEPROM_M24C64_32) || defined (EEPROM_M24LR64) || defined(EEPROM_M24C512)
  
  /* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 2, I2C_Reload_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }
  
  /* Send MSB of memory address */
  I2C_SendData(EEPROM_CFG_I2C, (uint8)((WriteAddr & 0xFF00) >> 8));  
  
  /* Wait until TXIS flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TXIS) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }
  
  /* Send LSB of memory address  */
  I2C_SendData(EEPROM_CFG_I2C, (uint8)(WriteAddr & 0x00FF));
  
#endif /*!< EEPROM_M24C08 */
  
  /* Wait until TCR flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TCR) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }
  
  /* Update CR2 : set Slave Address , set write request, generate Start and set end mode */
  I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, (uint8)NumByteToWrite, I2C_AutoEnd_Mode, I2C_No_StartStop);
  
  while (DataNum != NumByteToWrite)
  {      
    /* Wait until TXIS flag is set */
    EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_TXIS) == RESET)
    {
      if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
    }  
    
    /* Write data to TXDR */
    I2C_SendData(EEPROM_CFG_I2C, (uint8)(pBuffer[DataNum]));
    
    /* Update number of transmitted data */
    DataNum++;   
  }  
  
  /* Wait until STOPF flag is set */
  EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_STOPF) == RESET)
  {
    if((EEPROMTimeout--) == 0) return mg_u32TimeoutUserCallback();
  }   
  
  /* Clear STOPF flag */
  I2C_ClearFlag(EEPROM_CFG_I2C, I2C_ICR_STOPCF);
  
  /* If all operations OK, return EEPROM_CONF_OK (0) */
  return EEPROM_CONF_OK;
}

/** *****************************************************************************
 * \brief         Writes buffer of data to the I2C EEPROM.
 *
 * \param[in]     pBuffer : pointer to the buffer  containing the data to be written 
 *                          to the EEPROM.
 *                WriteAddr : EEPROM's internal address to write to.
 *                NumByteToWrite : number of bytes to write to the EEPROM.
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint32 EEPROM_u32WriteBuffer(const uint8* pBuffer, uint16 WriteAddr, uint16 NumByteToWrite)
{
  uint16 NumOfPage = 0, NumOfSingle = 0, count = 0;
  uint16 Addr = 0;
  
  Addr = WriteAddr % EEPROM_CONF_PAGESIZE;
  count = EEPROM_CONF_PAGESIZE - Addr;
  NumOfPage =  NumByteToWrite / EEPROM_CONF_PAGESIZE;
  NumOfSingle = NumByteToWrite % EEPROM_CONF_PAGESIZE;
  
  /*!< If WriteAddr is EEPROM_CONF_PAGESIZE aligned  */
  if(Addr == 0) 
  {
    /*!< If NumByteToWrite < EEPROM_CONF_PAGESIZE */
    if(NumOfPage == 0) 
    {
      /* Store the number of data to be written */
      EEPROMDataNum = NumOfSingle;
      /* Start writing data */
      if(EEPROM_CONF_OK != EEPROM_u32WritePage(pBuffer, WriteAddr, (uint8)EEPROMDataNum))
			{
				return mg_u32TimeoutUserCallback();
			}
      if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
			{
				return mg_u32TimeoutUserCallback();
			}
    }
    /*!< If NumByteToWrite > EEPROM_CONF_PAGESIZE */
    else  
    {
      while(NumOfPage--)
      {
        /* Store the number of data to be written */
        EEPROMDataNum = EEPROM_CONF_PAGESIZE;        
        if(EEPROM_CONF_OK != EEPROM_u32WritePage(pBuffer, WriteAddr, (uint8)EEPROMDataNum)) 
				{
					return mg_u32TimeoutUserCallback();
				}
        if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
				{
					return mg_u32TimeoutUserCallback();
				}
        WriteAddr +=  EEPROM_CONF_PAGESIZE;
        pBuffer += EEPROM_CONF_PAGESIZE;
      }
      
      if(NumOfSingle!=0)
      {
        /* Store the number of data to be written */
        EEPROMDataNum = NumOfSingle;          
        if(EEPROM_CONF_OK != EEPROM_u32WritePage(pBuffer, WriteAddr, (uint8)EEPROMDataNum))
				{
					return mg_u32TimeoutUserCallback();
				}
        if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
				{
					return mg_u32TimeoutUserCallback();
				}
      }
    }
  }
  /*!< If WriteAddr is not EEPROM_CONF_PAGESIZE aligned  */
  else 
  {
    /*!< If NumByteToWrite < EEPROM_CONF_PAGESIZE */
    if(NumOfPage== 0) 
    {
      /*!< If the number of data to be written is more than the remaining space 
      in the current page: */
      if (NumByteToWrite > count)
      {
        /* Store the number of data to be written */
        EEPROMDataNum = count;        
        /*!< Write the data contained in same page */
        if(EEPROM_CONF_OK != EEPROM_u32WritePage(pBuffer, WriteAddr, (uint8)EEPROMDataNum))
				{
					return mg_u32TimeoutUserCallback();
				}
        if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
				{
					return mg_u32TimeoutUserCallback();
				}					
        
        /* Store the number of data to be written */
        EEPROMDataNum = (NumByteToWrite - count);          
        /*!< Write the remaining data in the following page */
        if(EEPROM_CONF_OK != EEPROM_u32WritePage((uint8*)(pBuffer + count), (WriteAddr + count), (uint8)EEPROMDataNum))
				{
					return mg_u32TimeoutUserCallback();
				}
        if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
				{
					return mg_u32TimeoutUserCallback();
				}					
      }      
      else      
      {
        /* Store the number of data to be written */
        EEPROMDataNum = NumOfSingle;         
        if(EEPROM_CONF_OK != EEPROM_u32WritePage(pBuffer, WriteAddr, (uint8)EEPROMDataNum))
				{
					return mg_u32TimeoutUserCallback();
				}
        if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
				{
					return mg_u32TimeoutUserCallback();
				}					
      }     
    }
    /*!< If NumByteToWrite > EEPROM_CONF_PAGESIZE */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / EEPROM_CONF_PAGESIZE;
      NumOfSingle = NumByteToWrite % EEPROM_CONF_PAGESIZE;
      
      if(count != 0)
      {  
        /* Store the number of data to be written */
        EEPROMDataNum = count;         
        if(EEPROM_CONF_OK != EEPROM_u32WritePage(pBuffer, WriteAddr, (uint8)EEPROMDataNum))
				{
					return mg_u32TimeoutUserCallback();
				}
        if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
				{
					return mg_u32TimeoutUserCallback();
				}
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
        /* Store the number of data to be written */
        EEPROMDataNum = EEPROM_CONF_PAGESIZE;          
        if(EEPROM_CONF_OK != EEPROM_u32WritePage(pBuffer, WriteAddr, (uint8)EEPROMDataNum))
				{
					return mg_u32TimeoutUserCallback();
				}
        EEPROMTimeout = EEPROM_CONF_LONG_TIMEOUT;
        if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
				{
					return mg_u32TimeoutUserCallback();
				}
        WriteAddr +=  EEPROM_CONF_PAGESIZE;
        pBuffer += EEPROM_CONF_PAGESIZE;  
      }
      if(NumOfSingle != 0)
      {
        /* Store the number of data to be written */
        EEPROMDataNum = NumOfSingle;           
        if(EEPROM_CONF_OK != EEPROM_u32WritePage(pBuffer, WriteAddr, (uint8)EEPROMDataNum))
				{
					return mg_u32TimeoutUserCallback();
				}
        if(EEPROM_CONF_OK != EEPROM_u32WaitEepromStandbyState())
				{
					return mg_u32TimeoutUserCallback();
				}
      }
    }
  } 
  
  /* If all operations OK, return EEPROM_CONF_OK (0) */
  return EEPROM_CONF_OK;	
}

/** *****************************************************************************
 * \brief         Wait for EEPROM Standby state.
 * 
 * @note  This function allows to wait and check that EEPROM has finished the 
 *        last operation. It is mostly used after Write operation: after receiving
 *        the buffer to be written, the EEPROM may need additional time to actually
 *        perform the write operation. During this time, it doesn't answer to
 *        I2C packets addressed to it. Once the write operation is complete
 *        the EEPROM responds to its address.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        EEPROM_CONF_OK (0) if operation is correctly performed, else return value 
 *                different from EEPROM_CONF_OK (0) or the timeout user callback.
 *
 ***************************************************************************** */
uint32 EEPROM_u32WaitEepromStandbyState(void)      
{
  __IO uint32 EEPROMTrials = 0;
  
  /* Keep looping till the slave acknowledge his address or maximum number 
  of trials is reached (this number is defined by EEPROM_MAX_TRIALS_NUMBER define
  in stm32303c_eval_i2c_ee.h file) */
  
  /* Configure CR2 register : set Slave Address and end mode */
  I2C_TransferHandling(EEPROM_CFG_I2C, EEPROMAddress, 0, I2C_AutoEnd_Mode, I2C_No_StartStop);  
  
  do
  { 
    /* Initialize EEPROMTimeout */
    EEPROMTimeout = EEPROM_CONF_FLAG_TIMEOUT;
    
    /* Clear NACKF */
    I2C_ClearFlag(EEPROM_CFG_I2C, I2C_ICR_NACKCF | I2C_ICR_STOPCF);
    
    /* Generate start */
    I2C_GenerateSTART(EEPROM_CFG_I2C, ENABLE);
    
    /* Wait until timeout elapsed */
    while (EEPROMTimeout-- != 0)
		{
		}			
    
    /* Check if the maximum allowed numbe of trials has bee reached */
    if (EEPROMTrials++ == EEPROM_MAX_TRIALS_NUMBER)
    {
      /* If the maximum number of trials has been reached, exit the function */
      return mg_u32TimeoutUserCallback();
    }
  }
  while(I2C_GetFlagStatus(EEPROM_CFG_I2C, I2C_ISR_NACKF) != RESET);
  
  /* Clear STOPF */
  I2C_ClearFlag(EEPROM_CFG_I2C, I2C_ICR_STOPCF);
  
  /* Return EEPROM_CONF_OK if device is ready */
  return EEPROM_CONF_OK;
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
static uint32 mg_u32TimeoutUserCallback(void)
{
 return EEPROM_CONF_FAIL;
}

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

