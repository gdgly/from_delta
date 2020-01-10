/** *****************************************************************************
 * \file    eeprom_api.h
 * \brief   Service function request file for eeprom.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-10 18:40:44 +0800 (Fri, 10 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 12 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef EEPROM_API_H
#define EEPROM_API_H
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
uint32 EEPROM_u32ReadBuffer(uint8* pBuffer, uint16 ReadAddr, uint16 NumByteToRead);

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
uint32 EEPROM_u32WritePage(const uint8* pBuffer, uint16 WriteAddr, uint8 NumByteToWrite);

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
uint32 EEPROM_u32WriteBuffer(const uint8* pBuffer, uint16 WriteAddr, uint16 NumByteToWrite);

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
uint32 EEPROM_u32WaitEepromStandbyState(void);

#ifdef __cplusplus
  }
#endif
#endif  /* UART_API_H */

  
/*
 * End of file
 */
