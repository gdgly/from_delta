/** *****************************************************************************
 * \file    mem_cfg.h
 * \brief   Server call back service file for mem.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-01-11 10:40:42 +0800 (Fri, 11 Jan 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 137 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef MEM_CFG_H
#define MEM_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "s_dam_cfg.h"

/*******************************************************************************
 * Module interface
 ******************************************************************************/

#define MEM_CFG_CRC_INIT                CRC_INIT_02
/* EEPROM Size */
#define MEM_CFG_EEPROM_PAGE_SIZE     		128u
#define MEM_CFG_EEPROM_ADDRESS_START   	EEP_ADR_BLACK_BOX_STR /* start address for keep data in EEPROM , recommeneded to set EEPROM 32x6 (page32) = 192 for can divide page have no decimal */

/* Emem BlackBox Size */
#define MEM_CFG_BLABOX_LENGHT_EMEM 			(S_DAM_CFG_BLABOX_CONFIG_OFFSET + S_DAM_CFG_BLABOX_CONFIG_SIZE) /* (page EEP size)128 * 2 = 256 */
#define MEM_CFG_BLABOX_OFFSET_EMEM 			0 
/* Emem MFR Pmbus Size */
#define MEM_CFG_MFRPMBUS_LENGHT_EMEM 		0u 
#define MEM_CFG_MFRPMBUS_OFFSET_EMEM 		(MEM_CFG_BLABOX_LENGHT_EMEM)
/* Emem FWrev Size */
#define MEM_CFG_FWREV_LENGHT_EMEM 			0u
#define MEM_CFG_FWREV_OFFSET_EMEM 			(MEM_CFG_MFRPMBUS_LENGHT_EMEM + MEM_CFG_BLABOX_LENGHT_EMEM)
/* Emem Total Size */
#define MEM_CFG_LENGHT_EMEM 						(MEM_CFG_BLABOX_LENGHT_EMEM + MEM_CFG_MFRPMBUS_LENGHT_EMEM + MEM_CFG_FWREV_LENGHT_EMEM)

#define MEM_CFG_BIFFER_MAX_LEN_1        (MEM_CFG_BLABOX_LENGHT_EMEM >  MEM_CFG_MFRPMBUS_LENGHT_EMEM ? MEM_CFG_BLABOX_LENGHT_EMEM : MEM_CFG_MFRPMBUS_LENGHT_EMEM)
#define MEM_CFG_BIFFER_MAX_LEN          (MEM_CFG_BIFFER_MAX_LEN_1 >  MEM_CFG_FWREV_LENGHT_EMEM ? MEM_CFG_BIFFER_MAX_LEN_1 : MEM_CFG_FWREV_LENGHT_EMEM)

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/
typedef enum
{
  MEM_CFG_BLABOX_SECTOR = 0,
  MEM_CFG_MFRPMUBS_SECTOR,
  MEM_CFG_FWREV_SECTOR,
  MEM_CFG_SECTOR_SIZE
} MEM_CFG_SECTOR;

typedef struct
{		
  uint16 u16Length; /* Size of the area allocated to this log */
  uint16 u16Offset; /* size of each record */		
} T_MEM_CFG_SETUP;
/*******************************************************************************
 * Global data
 ******************************************************************************/
static const T_MEM_CFG_SETUP MEM_CFG_SETUP[MEM_CFG_SECTOR_SIZE] =
{ /*Define the areas to be initialised */
  { 
    MEM_CFG_BLABOX_LENGHT_EMEM,
    MEM_CFG_BLABOX_OFFSET_EMEM,      
  },
  {
    MEM_CFG_MFRPMBUS_LENGHT_EMEM,
    MEM_CFG_MFRPMBUS_OFFSET_EMEM,     
  },
  {
    MEM_CFG_FWREV_LENGHT_EMEM,
    MEM_CFG_FWREV_OFFSET_EMEM,     
  }
};
	
#ifdef __cplusplus
  }
#endif
#endif  /* MEM_CFG_H */

  
/*
 * End of file
 */
