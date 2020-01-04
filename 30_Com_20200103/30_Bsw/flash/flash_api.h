/** *****************************************************************************
 * \file    flash_api.h
 * \brief   Service function request file for flash.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-09-13 20:02:04 +0800 (Thu, 13 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 30 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef FLASH_API_H
#define FLASH_API_H
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
void FLASH_vInit(void);

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
void FLASH_vDeInit(void);

/** *****************************************************************************
 * \brief         Read flash address of boot loader existing flag
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 FLASH_u8ReadBlExistFlg(void);

/** *****************************************************************************
 * \brief         Memory write routine for application data
 *                RTE_FLG_MOD_OK if operation is successeful, else RTE_FLG_MOD_FAIL
 * \param[in]     Buffer data to write, length of data to write
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        MOD ok/fail flag
 *
 ***************************************************************************** */
uint8 FLASH_u8AppWr32(uint8* Buff, uint32 size);

/** *****************************************************************************
 * \brief         Memory write routine for application data
 *                RTE_FLG_MOD_OK if operation is successeful, else RTE_FLG_MOD_FAIL
 * \param[in]     Buffer data to write, length of data to write
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        MOD ok/fail flag
 *
 ***************************************************************************** */
uint8 FLASH_u8AppWr(uint32 u32phyAddr, uint8* Buff, uint32 size);

/** *****************************************************************************
 * \brief         Read half word (16bit) from memory address
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        16bit value from address
 *
 ***************************************************************************** */
uint16 FLASH_u16ReadHalfWordFlash(uint32 u32Addr);

/** *****************************************************************************
 * \brief         Read word (32bit) from memory address
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        32bit value from address
 *
 ***************************************************************************** */
uint32 FLASH_u32ReadWordFlash(uint32 u32Addr);

/** *****************************************************************************
 * \brief         Memory write of 16bit data to address
 *
 * \param[in]     Address, Data
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        MOD ok/fail flag
 *
 ***************************************************************************** */
uint8 FLASH_u8WriteHalfWordFlash(uint32 u32Addr, uint16 u16Data);

/** *****************************************************************************
 * \brief         Memory write routine for boot flag
 *                RTE_FLG_MOD_OK if operation is successeful, else RTE_FLG_MOD_FAIL
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        MOD ok/fail flag
 *
 ***************************************************************************** */
uint8 FLASH_u8WriteWordFlash(uint32 u32Addr, uint32 u32Data);

/** *****************************************************************************
 * \brief         Erase one page of the memory
 *                The address has to be the start address of the page (multiples of 2048byte)
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        MOD ok/fail flag
 *
 ***************************************************************************** */
uint8 FLASH_u8ErasePageFlash(uint32 u32Addr);

/** *****************************************************************************
 * \brief         Read flash address of boot loader firmware version
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint32 FLASH_u32BootloaderFwVer(void);

void FLASH_vRemapVectorTable(void);


#ifdef __cplusplus
  }
#endif
#endif  /* FLASH_API_H */

  
/*
 * End of file
 */
