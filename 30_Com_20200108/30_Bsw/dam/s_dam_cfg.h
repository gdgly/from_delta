/** ****************************************************************************
 * \file    s_dam_cfg.h
 * \brief   S_DAM module implementation configuration
 *
 * \section AUTHOR
 *  Phairot.C
 *
 * \section SVN
 *  $Date: $
 *  $Author: $
 *  $Revision: $
 *
 * \section LICENSE
 *  Copyright (c) 2017 Delta Energy Systems (Germany) GmbH.
 *  All rights reserved.
 **************************************************************************** */

#ifndef S_DAM_CFG_H
#define S_DAM_CFG_H
#define S_DAM_EXPORT_H

#ifdef __cplusplus
extern "C" {
#endif

  /*******************************************************************************
   * Global constants and macros
   ******************************************************************************/
  /*lint -e{129}
    * Error: 129 declaration expected, identifier '__packed' ignored
    * reason: Suppression of lint message for packing directive not being
    * recognised */
#pragma pack(push,1) /* set packing to one byte */
  typedef union
  {
      uint8 au8Data[4];
      struct
      {
          uint16 u16Current;
          uint8 u8Override;
          uint8 u8Reserved; /*  Added as byte packing/alignment issues meant this all took 4 bytes, so making this obvious */
      } Index;
  } T_U_S_DAM_SECTOR_INDEX;
  /*lint -e{129}
    * Error: 129 declaration expected, identifier '__packed' ignored
    * reason: Suppression of lint message for packing directive not being
    * recognised */
#pragma pack(pop) /* restore packing */

  typedef enum
  {
    S_DAM_CFG_BLABOX_EVENTDATA_SECTOR = 0,
    S_DAM_CFG_BLABOX_HEADER_SECTOR,
    S_DAM_CFG_BLABOX_CONFIG_SECTOR,
    S_DAM_CFG_SECTOR_SIZE
  } E_S_DAM_CFG_SECTOR;

#define S_DAM_CFG_CRC_SIZE 2u

#if (S_DAM_CFG_CRC_SIZE == 1u)
#define S_DAM_CFG_MOD_CRC 0xFFu
#elif (S_DAM_CFG_CRC_SIZE == 2u)
#define S_DAM_CFG_MOD_CRC 0xFFFFu
#elif (S_DAM_CFG_CRC_SIZE == 3u)
#define S_DAM_CFG_MOD_CRC 0xFFFFFFu
#elif (S_DAM_CFG_CRC_SIZE == 4u)
#define S_DAM_CFG_MOD_CRC 0xFFFFFFFFu
#else
#error Cannot set CRC size more than 4 bytes.
#endif

  /*lint -save -e835
   * Info: 835 A zero has been given as right argument to operator '+'
   * Reason:
   * CRC size is permitted to be 0.
   */
  /* CRC size can be det not exist 4 bytes*/

#define S_DAM_CFG_MEMORY_SIZE (0xFFFFu)

#define S_DAM_CFG_HEADER_SECTOR_SIZE 4UL

/* This constant sets the location of the sector index records
 * 1 - The index record for each sector is stored at the start address of the sector.
 *        (Size calculation must include S_DAM_CFG_HEADER_SECTOR_SIZE)
 * 0 - The index records for all sectors are stored at address 0 as per previous versions of S_DAM.
 *        (First sector offset must be at least (S_DAM_CFG_HEADER_SECTOR_SIZE * S_DAM_CFG_SECTOR_SIZE)
 */
#define S_DAM_CFG_INDEX_STORED_IN_SECTOR   (1)

#if (S_DAM_CFG_INDEX_STORED_IN_SECTOR)
#define S_DAM_CFG_FIRST_SECTOR_OFFSET (0u)
#define S_DAM_CFG_FIRST_RECORD_OFFSET (S_DAM_CFG_HEADER_SECTOR_SIZE)
#else
#define S_DAM_CFG_FIRST_SECTOR_OFFSET (S_DAM_CFG_HEADER_SECTOR_SIZE * S_DAM_CFG_SECTOR_SIZE)
#define S_DAM_CFG_FIRST_RECORD_OFFSET (0u)
#endif

  /*S_DAM_CFG_BLABOX_EVENTDATA_SECTOR*/
#define S_DAM_CFG_BLABOX_EVENTDATA_OFFSET (S_DAM_CFG_FIRST_SECTOR_OFFSET)
#define S_DAM_CFG_BLABOX_EVENTDATA_LEN (41u)
#define S_DAM_CFG_BLABOX_EVENTDATA_NUM_RECORD (5u)
#define S_DAM_CFG_EVENTDATA_SIZE ((uint16)(S_DAM_CFG_FIRST_RECORD_OFFSET + (S_DAM_CFG_BLABOX_EVENTDATA_NUM_RECORD * (S_DAM_CFG_BLABOX_EVENTDATA_LEN + S_DAM_CFG_CRC_SIZE))))
/* S_DAM_CFG_BLABOX_CONFIG_OFFSET (0) + S_DAM_CFG_BLABOX_CONFIG_SIZE (16) = 0x10 */

  /*S_DAM_CFG_BLABOX_HEADER_SECTOR*/
#define S_DAM_CFG_BLABOX_HEADER_OFFSET  (S_DAM_CFG_BLABOX_EVENTDATA_OFFSET + S_DAM_CFG_EVENTDATA_SIZE)
#define S_DAM_CFG_BLABOX_HEADER_LEN (48u)
#define S_DAM_CFG_BLABOX_HEADER_NUM_RECORD (1u)
#define S_DAM_CFG_BLABOX_HEADER_SIZE ((uint16)(S_DAM_CFG_FIRST_RECORD_OFFSET + (S_DAM_CFG_BLABOX_HEADER_NUM_RECORD * (S_DAM_CFG_BLABOX_HEADER_LEN + S_DAM_CFG_CRC_SIZE))))
/* S_DAM_CFG_CALIB_OFFSET (0x10) + S_DAM_CFG_CALIB_SIZE (30) = 0x2E */

/*S_DAM_CFG_BLABOX_CONFIG_SECTOR*/
#define S_DAM_CFG_BLABOX_CONFIG_OFFSET  (S_DAM_CFG_BLABOX_HEADER_OFFSET + S_DAM_CFG_BLABOX_HEADER_SIZE)
#define S_DAM_CFG_BLABOX_CONFIG_LEN (1U)
#define S_DAM_CFG_BLABOX_CONFIG_NUM_RECORD (1u)
#define S_DAM_CFG_BLABOX_CONFIG_SIZE ((uint16)(S_DAM_CFG_FIRST_RECORD_OFFSET + (S_DAM_CFG_BLABOX_CONFIG_NUM_RECORD * (S_DAM_CFG_BLABOX_CONFIG_LEN + S_DAM_CFG_CRC_SIZE))))
/* S_DAM_CFG_PROFILE_OFFSET (0x2E) + S_DAM_CFG_PROFILE_SIZE (15214) = 0x3B9C */


#if 0
	#if (S_DAM_CFG_BLABOX_CONFIG_OFFSET + S_DAM_CFG_BLABOX_CONFIG_SIZE) > S_DAM_CFG_MEMORY_SIZE)
	#error "Partitioning of Eeprom by S_DAM, including metadata and CRC, is larger than the configured size of EEPROM."
	#endif
#endif

  /*******************************************************************************
   * Global data types (typedefs / structs / enums)
   ******************************************************************************/

  typedef struct
  {
      uint32 u32AreaStartAddress; /* Start address in memory */
      uint16 u16LogSize; /* Size of the area allocated to this log */
      uint16 u16RecordSize; /* size of each record */
      uint16 u16NumberOfRecord; /* Number of records to be stores in the area */
      boolean bOverwritable; /* Overwrite when index of record is full */
  } T_S_S_DAM_CFG_SETUP;

  /*******************************************************************************
   * Global data
   ******************************************************************************/
#ifdef S_DAM_EXPORT_H
  static const T_S_S_DAM_CFG_SETUP S_S_DAM_CFG_CFG_SETUP[S_DAM_CFG_SECTOR_SIZE] =
  { /*Define the areas to be initialised */
    { /*  S_DAM_CFG_DEV_LOG_SECTOR*/
      S_DAM_CFG_BLABOX_EVENTDATA_OFFSET,
      S_DAM_CFG_BLABOX_EVENTDATA_OFFSET,
      S_DAM_CFG_BLABOX_EVENTDATA_LEN,
      S_DAM_CFG_BLABOX_EVENTDATA_NUM_RECORD, TRUE
    },
    {
      S_DAM_CFG_BLABOX_HEADER_OFFSET,
      S_DAM_CFG_BLABOX_HEADER_SIZE,
      S_DAM_CFG_BLABOX_HEADER_LEN,
      S_DAM_CFG_BLABOX_HEADER_NUM_RECORD, TRUE
    },
    {
      S_DAM_CFG_BLABOX_CONFIG_OFFSET,
      S_DAM_CFG_BLABOX_CONFIG_SIZE,
      S_DAM_CFG_BLABOX_CONFIG_LEN,
      S_DAM_CFG_BLABOX_CONFIG_NUM_RECORD, TRUE
    }//,
//    {
//      S_DAM_CFG_PMBUS_MFR_OFFSET,
//      S_DAM_CFG_PMBUS_MFR_SIZE,
//      S_DAM_CFG_PMBUS_MFR_LEN,
//      S_DAM_CFG_PMBUS_MFR_NUM_RECORD, TRUE
//    }
  };
#endif

/*lint -restore *//* 835 This needs turned off after usage, not turned off at the define where the rule is violated. */
/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
SINLINE void S_DAM_CFG_vOnInit (void)
{

}

#ifdef __cplusplus
}
#endif

#endif

/*
 * End of file
 */

