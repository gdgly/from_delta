/** *****************************************************************************
 * \file    flash_conf.h
 * \brief   Configurations file for flash.c
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

#ifndef FLASH_CONF_H
#define FLASH_CONF_H
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

#define FLG_MOD_OK                    0 
#define FLG_MOD_FAIL                  1
    
/***************************************
 * Flash memory configuration
 **************************************/
/* (Note: edit file "Project.sct" accordingly) */
#define MG_FLASH_32KB                0
#define MG_FLASH_64KB                1u

#if (MG_FLASH_32KB)
  /* Flash size 32KBytes */
  #define MG_FLASH_SIZE              0x8000
  /* Flash page size 2KBytes (2048Bytes) */
  #define MG_PAGE_SIZE               0x0800
  /*
  * Memory map (Note: edit file "Project.sct" accordingly):
   * 0x0800 0000    Boot loader code (8kB)
   * 0x0800 1FF0    Boot loader CRC16 (16bit)
   * 0x0800 1FF8    Boot loader FW revision (32bit)
   * 0x0800 1FFC    Boot loader existing key (32bit)
   * 0x0800 2000    Application code (22kB)
   * 0x0800 7800    Reserved page (2kB)
   * 0x0800 7802    Application CRC16 (16bit)
   * 0x0800 7800    Upgrade flag (16bit)
   */
  /* Address boot loader start */
  #define MG_BL_START_ADDR           0x08000000
  /* Address boot loader end */
  #define MG_BL_END_ADDR             0x08001FEF
  /* Address for boot loader CRC16 (16bit) */
  #define MG_BL_CRC16_ADDR           0x08001FF0
  /* Address for boot loader FW revision (32bit) */
  #define MG_BL_FW_REV_ADDR          0x08001FF8
  /* Address for boot loader existing key (32bit) */
  #define MG_BL_EXISTING_ADDR        0x08001FFC

  /* Address applications start */
  #define MG_APP_START_ADDR          0x08002000
  /* Address application end */
  #define MG_APP_END_ADDR            0x080077FF

  /* Reserved page for flags, CRC, FW identifier */
  #define MG_RESERVED_PAGE_ADDR      0x08007800
  /* Address for application code CRC (32bit) */
  #define MG_CRC16_ADDR              0x08007802
  /* Address for firmware upgrade flag key (16bit) */
  #define MG_FW_UPGRADE_FLG_ADDR     0x08007800
#endif

#if (MG_FLASH_64KB)
  /* Flash size 64KBytes */
  #define MG_FLASH_SIZE              0x10000
  /* Flash page size 2KBytes (2048Bytes) */
  #define MG_PAGE_SIZE               0x0800
  /*
  * Memory map (Note: edit file "Project.sct" accordingly):
   * 0x0800 0000    Boot loader code (8kB)
   * 0x0800 2FF0    Boot loader CRC16 (16bit)
   * 0x0800 2FF8    Boot loader FW revision (32bit)
   * 0x0800 2FFC    Boot loader existing key (32bit)
   * 0x0800 3000    Application code (54kB)
   * 0x0800 B000    Reserved page (2kB)
   * 0x0800 B002    Application CRC16 (16bit)
   * 0x0800 B000    Upgrade flag (16bit)
   */
  /* Address boot loader start */
  #define MG_BL_START_ADDR           0x08000000
  /* Address boot loader end */
  #define MG_BL_END_ADDR             0x08002FEF
  /* Address for boot loader CRC16 (16bit) */
  #define MG_BL_CRC16_ADDR           0x08002FF0
  /* Address for boot loader FW revision (32bit) */
  #define MG_BL_FW_REV_ADDR          0x08002FF8
  /* Address for boot loader existing key (32bit) */
  #define MG_BL_EXISTING_ADDR        0x08002FFC

  /* Address applications start */
  #define MG_APP_START_ADDR          0x08003000
  /* Address application end */
  #define MG_APP_END_ADDR            0x080AFFF

  /* Reserved page for flags, CRC, FW identifier */
  #define MG_RESERVED_PAGE_ADDR      0x0800B000
  /* Address for application code CRC (32bit) */
  #define MG_CRC16_ADDR              0x0800B002
  /* Address for firmware upgrade flag key (32bit) */
  #define MG_FW_UPGRADE_FLG_ADDR     0x0800B000
#endif

/***************************************
 * Flash memory flags and keys
 **************************************/
/* 16bit firmware upgrade flag (use zero to allow writing without flash erase) */
#define MG_FW_UPGRADE_FLG            0x55AA
/* 32bit boot loader existing flag key */
#define MG_BL_EXISTING_FLG           0xA1B2C3D4


#ifdef __cplusplus
  }
#endif
#endif  /* FLASH_CONF_H */

  
/*
 * End of file
 */
