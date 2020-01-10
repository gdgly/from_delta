/** *****************************************************************************
 * \file    flash_conf.h
 * \brief   Configurations file for flash.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-11-02 18:17:25 +0800 (Fri, 02 Nov 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 100 $
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

#define FLG_MOD_OK                    0u 
#define FLG_MOD_FAIL                  1u
    
/***************************************
 * Flash memory configuration
 **************************************/
/* (Note: edit file "Project.sct" accordingly) */
#define MG_FLASH_32KB                0u
#define MG_FLASH_64KB                1u

#if (MG_FLASH_32KB)
  /* Flash size 32KBytes */
  #define MG_FLASH_SIZE              0x8000u
  /* Flash page size 2KBytes (2048Bytes) */
  #define MG_PAGE_SIZE               0x0800u
  /*
  * Memory map (Note: edit file "Project.sct" accordingly):
   * 0x0800 0000    Boot loader code (8kB)
   * 0x0800 3FF8    Boot loader CRC16 (16bit)
   * 0x0800 3FFA    Boot loader FW revision (16bit)
   * 0x0800 3FFC    Boot loader existing key (32bit)
   * 0x0800 4000    Application code (22kB)
   * 0x0800 F800    Reserved page (2kB)
   * 0x0800 FFF8    Application CRC16 (16bit)
   * 0x0800 FFFC    Upgrade flag (32bit)
   */
  #define MG_BL_START_ADDR           0x08000000u
  /* Address boot loader end */
  #define MG_BL_END_ADDR             0x08003FEFu
  /* Address for boot loader CRC16 (16bit) */
  #define MG_BL_CRC16_ADDR           0x08003FF0u
  /* Address for boot loader FW revision (16bit) */
  #define MG_BL_FW_REV_ADDR          0x08003FF8u
  /* Address for boot loader existing key (32bit) */
  #define MG_BL_EXISTING_ADDR        0x08003FFCu

  /* Address applications start */
  #define MG_APP_START_ADDR          0x08004000u
  /* Address application end */
  #define MG_APP_END_ADDR            0x080077FFu

  /* Reserved page for flags, CRC, FW identifier */
  #define MG_RESERVED_PAGE_ADDR      0x08007800u
  /* Address for application code CRC (32bit) */
  #define MG_CRC16_ADDR              0x08007FF8u
  /* Address for firmware upgrade flag key (32bit) */
  #define MG_FW_UPGRADE_FLG_ADDR     0x08007FFCu
#endif

#if (MG_FLASH_64KB)
  /* Flash size 64KBytes */
  #define MG_FLASH_SIZE              0x10000u
  /* Flash page size 2KBytes (2048Bytes) */
  #define MG_PAGE_SIZE               0x0800u
  /*
  * Memory map (Note: edit file "Project.sct" accordingly):
   * 0x0800 0000    Boot loader code (8kB)
   * 0x0800 3FF0    Boot loader CRC16 (16bit)
   * 0x0800 3FF8    Boot loader FW revision (16bit)
   * 0x0800 3FFC    Boot loader existing key (32bit)
   * 0x0800 2000    Application code (54kB)
   * 0x0800 F800    Reserved page (2kB)
   * 0x0800 FFF8    Application CRC16 (16bit)
   * 0x0800 FFFC    Upgrade flag (32bit)
   */
  /* Address boot loader start */
  #define MG_BL_START_ADDR           0x08000000u
  /* Address boot loader end */
  #define MG_BL_END_ADDR             0x08003FEFu
  /* Address for boot loader CRC16 (16bit) */
  #define MG_BL_CRC16_ADDR           0x08003FF0u
  /* Address for boot loader FW revision (16bit) */
  #define MG_BL_FW_REV_ADDR          0x08003FF8u
  /* Address for boot loader existing key (32bit) */
  #define MG_BL_EXISTING_ADDR        0x08003FFCu

  /* Address applications start */
  #define MG_APP_START_ADDR          0x08004000u
  /* Address application end */
  #define MG_APP_END_ADDR            0x0800F7FFu

  /* Reserved page for flags, CRC, FW identifier */
  #define MG_RESERVED_PAGE_ADDR      0x0800F800u
  /* Address for application code CRC (32bit) */
  #define MG_CRC16_ADDR              0x0800FFF8u
  /* Address for firmware upgrade flag key (32bit) */
  #define MG_FW_UPGRADE_FLG_ADDR     0x0800FFFCu
#endif

/***************************************
 * Flash memory flags and keys
 **************************************/
/* 32bit firmware upgrade flag (use zero to allow writing without flash erase) */
#define MG_FW_UPGRADE_FLG            0x00000000
/* 32bit boot loader existing flag key */
#define MG_BL_EXISTING_FLG           0xA1B2C3D4


#ifdef __cplusplus
  }
#endif
#endif  /* FLASH_CONF_H */

  
/*
 * End of file
 */
