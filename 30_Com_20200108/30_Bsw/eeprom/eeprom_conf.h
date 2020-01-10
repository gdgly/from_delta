/** *****************************************************************************
 * \file    eeprom_conf.h
 * \brief   Configurations file for eeprom.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-29 08:42:30 +0800 (Wed, 29 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 15 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef EEPROM_CONF_H
#define EEPROM_CONF_H
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

#define EEPROM_M24C512
/* #define EEPROM_M24C64_32 */
/* #define EEPROM_M24M01 */ 
   
/* #define USE_DEFAULT_TIMEOUT_CALLBACK */
   
#if !defined (EEPROM_M24C08) && !defined (EEPROM_M24C64_32) && !defined (EEPROM_M24LR64) && !defined (EEPROM_M24M01) && !defined(EEPROM_M24C512)
/* Use the defines below the choose the EEPROM type */
#define EEPROM_M24M01  /* Support the device: M24M01. */
/* #define EEPROM_M24C08*/  /* Support the device: M24C08. */
/* note: Could support: M24C01, M24C02, M24C04 and M24C16 if the blocks and 
   HW address are correctly defined*/
/*#define EEPROM_M24C64_32*/  /* Support the devices: M24C32 and M24C64 */
/*#define EEPROM_M24LR64*/ /*Support the devices: M24LR64 */
#endif

#ifdef EEPROM_M24C64_32
/* For M24C32 and M24C64 devices, E0,E1 and E2 pins are all used for device 
  address selection (ne need for additional address lines). According to the 
  Hardware connection on the board. */

 #define EEPROM_CONF_HW_ADDRESS         0xAEu   /* E0 = E1 = E2 = 0 */ 

#elif defined (EEPROM_M24C08)
/* The M24C08W contains 4 blocks (128byte each) with the addresses below: E2 = 0 
   EEPROM Addresses defines */
#define EEPROM_CONF_HW_ADDRESS          0xA0   /* E2 = 0 */ 

#elif defined (EEPROM_M24LR64)
#define EEPROM_CONF_HW_ADDRESS         0xA0

#elif defined (EEPROM_M24M01)
/* The EEPROM_M24M01 contains 2 blocks (64Kbytes each) with the adresses below 
   EEPROM Addresses defines */
#define EEPROM_CONF_HW_ADDRESS        0xA4    /* Block 1 : E1= 1; E2 = 0; A16 = 0 */
/*#define EEPROM_CONF_HW_ADDRESS     0xA6*/  /* Block 2 : E1= 1; E2 = 0; A16 = 1 */

#elif defined (EEPROM_M24C512)

#define EEPROM_CONF_HW_ADDRESS      0xA0

#endif /* EEPROM_M24C64_32 */
   

#if defined (EEPROM_M24C08)
 #define EEPROM_CONF_PAGESIZE           16
#elif defined (EEPROM_M24C64_32)
 #define EEPROM_CONF_PAGESIZE           32
#elif defined (EEPROM_M24LR64)
 #define EEPROM_CONF_PAGESIZE           4
#elif defined (EEPROM_M24M01)
 #define EEPROM_CONF_PAGESIZE           128 
#elif defined (EEPROM_M24C512) 
 #define EEPROM_CONF_PAGESIZE           128 
#endif
   
/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define EEPROM_CONF_FLAG_TIMEOUT         ((uint32)0x1000)
#define EEPROM_CONF_LONG_TIMEOUT         ((uint32)(10 * EEPROM_CONF_FLAG_TIMEOUT))

/* Maximum number of trials for EEPROM_WaitEepromStandbyState() function */
#define EEPROM_MAX_TRIALS_NUMBER          300u
      
#define EEPROM_CONF_OK                    0u
#define EEPROM_CONF_FAIL                  1u   



#ifdef __cplusplus
  }
#endif
#endif  /* EEPROM_CONF_H */


/*
 * End of file
 */
