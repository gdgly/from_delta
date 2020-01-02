/** ****************************************************************************
 * \file    s_dam.c
 * \brief   S_DAM module
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
/*lint --e{9018}
 * These messages are suppressed for the whole of this module.
 * Note: 9018 declaration of symbol  with union based type
 * [MISRA 2012 Rule 19.2, advisory]
 *
 * reason:
 * Allow the use of unions
 *
 */
/*******************************************************************************
 * Included headers
 ******************************************************************************/

#include <global.h>

/*******************************************************************************
 * Own module headers
 ******************************************************************************/
#define S_DAM_EXPORT_H
#include "s_dam_api.h"
#include "s_dam_cfg.h"
#include "s_dam_scb.h"
#include "s_dam_scfg.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
static uint32 S_DAM_mgU32HeaderIndex(E_S_DAM_CFG_SECTOR eLogSector);
/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

boolean S_DAM_bWrite(E_S_DAM_CFG_SECTOR eLogSector, const uint8* pu8Buffer)
{
  static T_U_S_DAM_SECTOR_INDEX uSector;
  boolean bToReturn = TRUE;
  uint32 u32IndexAddress;
  uint32 u32AddressToWrite = 0u;
  uint32 u32CrcCal = 0u;
  static uint16 u16Crc = 0u;

  u32IndexAddress = S_DAM_mgU32HeaderIndex(eLogSector);
  if (eLogSector >= S_DAM_CFG_SECTOR_SIZE)
  {
    bToReturn = FALSE;
  }
  else
  {
    if (FALSE
        == S_DAM_SCFG_bRead((uint8 *) uSector.au8Data, u32IndexAddress,
            sizeof(uSector)))
    {
      bToReturn = FALSE;
      S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
    }

    if (TRUE == bToReturn)
    {
      /* We need to separate the following into:
       *
       * Is it new?
       * Is it full?
       *  if full, is it overwritable?
       *  if full, and not overwritable, return error
       *  if full and overwritable, return to start of records.
       *
       * */
      if (S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord
          <= (uSector.Index.u16Current))
      {

        if (0xFFFFu == uSector.Index.u16Current)
        {
          /* New EEprom */
          uSector.Index.u16Current = 1u;
          uSector.Index.u8Override = FALSE;
        }
        else if (TRUE == S_S_DAM_CFG_CFG_SETUP[eLogSector].bOverwritable)
        {
          /* full so need to restart. */
          uSector.Index.u16Current = 1u;
          uSector.Index.u8Override = TRUE;
        }
        else
        {
          /* Overwrite protect don not add Devlog? */
          bToReturn = FALSE;
        }
      }
      else
      {
        uSector.Index.u16Current++;
      }

      if (TRUE == bToReturn)
      {
        u32AddressToWrite =
            (uint32) (S_S_DAM_CFG_CFG_SETUP[eLogSector].u32AreaStartAddress
                + S_DAM_CFG_FIRST_RECORD_OFFSET + (((uint32) uSector.Index.u16Current - 1u)
                    * (((uint32) S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize
                        + S_DAM_CFG_CRC_SIZE))));

        u32CrcCal = S_DAM_SCFG_u32Crc(pu8Buffer,
            S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize);

        u16Crc = (uint16) u32CrcCal;

        if (FALSE
            == S_DAM_SCFG_bWrite(pu8Buffer, u32AddressToWrite,
                (uint32) S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize))
        {
          bToReturn = FALSE;
          S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
        }
      }
      if (TRUE == bToReturn)
      {
        if (FALSE
            == S_DAM_SCFG_bWrite((uint8 *) &u16Crc,
                u32AddressToWrite
                    + S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize,
                S_DAM_CFG_CRC_SIZE))
        {
          bToReturn = FALSE;
          S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
        }
      }
      if (TRUE == bToReturn)
      {
        if (FALSE
            == S_DAM_SCFG_bWrite((uint8 *) uSector.au8Data, u32IndexAddress,
                sizeof(uSector)))
        {
          bToReturn = FALSE;
          S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
        }
      }
    }
  }
  return bToReturn;
}

boolean S_DAM_bWriteToRecord(E_S_DAM_CFG_SECTOR eLogSector, const uint8* pu8Buffer,
    uint16 u16RecordNumber)
{
  static T_U_S_DAM_SECTOR_INDEX uSector;
  boolean bToReturn = TRUE;
  uint32 u32IndexAddress;
  uint32 u32AddressToWrite = 0u;
  uint32 u32CrcCal = 0u;
  static uint16 u16Crc = 0u;

  u32IndexAddress = S_DAM_mgU32HeaderIndex(eLogSector);
  if (eLogSector >= S_DAM_CFG_SECTOR_SIZE)
  {
    bToReturn = FALSE;
  }
  else
  {
    if (FALSE
        == S_DAM_SCFG_bRead((uint8 *) uSector.au8Data, u32IndexAddress,
            sizeof(uSector)))
    {
      bToReturn = FALSE;
      S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
    }

    if (TRUE == bToReturn)
    {
      if (S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord < u16RecordNumber)
      {
        bToReturn = FALSE;
        S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
      }
      else
      {
        if (0xFFFFu == uSector.Index.u16Current)
        {
          /* New EEprom */
          uSector.Index.u16Current = u16RecordNumber;
          uSector.Index.u8Override = FALSE;
        }
        else if (uSector.Index.u16Current <= u16RecordNumber)
        {
          /* writing to same or higher record than index */
          uSector.Index.u16Current = u16RecordNumber;
          /* Override flag not modified */
        }
        else
        {
          /* writing to lower record than index,
           * possibly overwriting previous record,
           * number of records now assumed from CFG */
          uSector.Index.u16Current = u16RecordNumber;
          uSector.Index.u8Override = TRUE;
        }
      }

      if (TRUE == bToReturn)
      {
        u32AddressToWrite =
            (uint32) (S_S_DAM_CFG_CFG_SETUP[eLogSector].u32AreaStartAddress
                + S_DAM_CFG_FIRST_RECORD_OFFSET + (((uint32) u16RecordNumber - 1u)
                    * (((uint32) S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize
                        + S_DAM_CFG_CRC_SIZE))));

        u32CrcCal = S_DAM_SCFG_u32Crc(pu8Buffer,
            S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize);

        u16Crc = (uint16) u32CrcCal;

        if (FALSE
            == S_DAM_SCFG_bWrite(pu8Buffer, u32AddressToWrite,
                (uint32) S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize))
        {
          bToReturn = FALSE;
          S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
        }
      }
      if (TRUE == bToReturn)
      {
        if (FALSE
            == S_DAM_SCFG_bWrite((uint8 *) &u16Crc,
                u32AddressToWrite
                    + S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize,
                S_DAM_CFG_CRC_SIZE))
        {
          bToReturn = FALSE;
          S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
        }
      }
      if (TRUE == bToReturn)
      {
        if (FALSE
            == S_DAM_SCFG_bWrite((uint8 *) uSector.au8Data, u32IndexAddress,
                sizeof(uSector)))
        {
          bToReturn = FALSE;
          S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
        }
      }
    }
  }
  return bToReturn;
}

boolean S_DAM_bRead(E_S_DAM_CFG_SECTOR eLogSector, uint8* pu8Buffer,
    uint16 u16RecordNumber)
{
  boolean bToReturn = TRUE;
  T_U_S_DAM_SECTOR_INDEX uSector;
  uint32 u32IndexAddress = S_DAM_mgU32HeaderIndex(eLogSector);
  uint32 u32AddressToRead = 0UL;
  uint32 u32CrcCal = 0u;
  static uint32 u32CrcPackage = 0u;

  /*lint -save -e928 -e934
   * Note: 928 cast from pointer to pointer [MISRA 2004 Rule 11.4, advisory]
   * Note: 934 Taking address of near auto variable 'u16Index' (initialization) [MISRA 2004 Rule 1.2, required]
   * Reason:
   * Reading a u16 address from eeprom location, ok.
   */
  if (eLogSector >= S_DAM_CFG_SECTOR_SIZE)
  {
    bToReturn = FALSE;
    S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
  }
  else
  {
    if (FALSE
        == S_DAM_SCFG_bRead((uint8 *) uSector.au8Data, u32IndexAddress,
            sizeof(uSector)))
    /*lint -restore *//* 928 934 */
    {
      bToReturn = FALSE;
      S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
    }

    if (TRUE == bToReturn)
    {
      if (((uSector.Index.u16Current < u16RecordNumber)
          && ((FALSE == S_S_DAM_CFG_CFG_SETUP[eLogSector].bOverwritable)
              || (FALSE == uSector.Index.u8Override)))
          || (S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord
              < uSector.Index.u16Current) || (0u == u16RecordNumber))
      {
        bToReturn = FALSE;
        S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
      }
    }

    if (TRUE == bToReturn)
    {
      /* Read the record */
      u32AddressToRead = S_S_DAM_CFG_CFG_SETUP[eLogSector].u32AreaStartAddress
          + S_DAM_CFG_FIRST_RECORD_OFFSET + (((uint32) u16RecordNumber - 1u)
              * (((uint32) S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize
                  + S_DAM_CFG_CRC_SIZE)));
      /*  If fail to read, */
      if (FALSE
          == (S_DAM_SCFG_bRead(pu8Buffer, u32AddressToRead,
              (uint32) S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize)))
      {
        bToReturn = FALSE;
        S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
      }
    }

    if (TRUE == bToReturn)
    {
      /* Read the CRC */
      if (FALSE
          == S_DAM_SCFG_bRead((uint8 *) &u32CrcPackage,
              u32AddressToRead + S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize,
              S_DAM_CFG_CRC_SIZE))
      {
        bToReturn = FALSE;
        S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
      }
    }

    if (TRUE == bToReturn)
    {
      u32CrcCal = S_DAM_SCFG_u32Crc(pu8Buffer,
          S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize);
      u32CrcCal = (uint32) (u32CrcCal & (uint32) S_DAM_CFG_MOD_CRC);
      if (u32CrcPackage != u32CrcCal)
      {
        bToReturn = FALSE;
        S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, u32CrcPackage);
        S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, u32CrcCal);
      }
    }
  }
  return bToReturn;
}

void S_DAM_SCB_vInit(void)
{
  /* Crosscheck with assertion for (area Size >= number of records * record size) */
  /* Log problem to S_DAM_SCFG_vOnErrorDetected */
  uint32 u32TotalMemoryAllcate =
      (S_S_DAM_CFG_CFG_SETUP[(uint16) S_DAM_CFG_SECTOR_SIZE - 1u]).u32AreaStartAddress
          + S_S_DAM_CFG_CFG_SETUP[(uint16) S_DAM_CFG_SECTOR_SIZE - 1u].u16LogSize;
  if (u32TotalMemoryAllcate > S_DAM_CFG_MEMORY_SIZE)
  {
    S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, u32TotalMemoryAllcate);
  }
  S_DAM_CFG_vOnInit();
}

boolean S_DAM_vReset(E_S_DAM_CFG_SECTOR eLogSector)
{
  boolean bToReturn = TRUE;
  static T_U_S_DAM_SECTOR_INDEX uSector;
  uint32 u32IndexAddress;
  u32IndexAddress = S_DAM_mgU32HeaderIndex(eLogSector);
  uSector.Index.u16Current = 0xFFFFu;
  uSector.Index.u8Override = 0u;
  if (FALSE
      == S_DAM_SCFG_bWrite((uint8 *) uSector.au8Data, u32IndexAddress,
          sizeof(uSector)))
  {
    bToReturn = FALSE;
  }
  return bToReturn;
}

boolean S_DAM_bResetRecord(E_S_DAM_CFG_SECTOR eLogSector, uint16 u16RecordNumber)
{
  boolean bToReturn = TRUE;
  uint32 u32AddressToWrite;
  static uint16 u16Crc;

  if (S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord >= u16RecordNumber)
  {
    /* Address of record */
    u32AddressToWrite =
        (uint32) (S_S_DAM_CFG_CFG_SETUP[eLogSector].u32AreaStartAddress
            + S_DAM_CFG_FIRST_RECORD_OFFSET
            + (((uint32) u16RecordNumber - 1u)
                * (((uint32) S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize
                    + S_DAM_CFG_CRC_SIZE))));

    /* Erase CRC at the end of record */
    u16Crc = (uint16) 0xFFFFu;

    if (FALSE
        == S_DAM_SCFG_bWrite((uint8 *) &u16Crc,
            u32AddressToWrite + S_S_DAM_CFG_CFG_SETUP[eLogSector].u16RecordSize,
            S_DAM_CFG_CRC_SIZE))
    {
      bToReturn = FALSE;
      S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
    }
  }
  else
  {
    bToReturn = FALSE;
    S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, 0UL);
  }

  return bToReturn;
}

uint32 S_DAM_u32GetNumberOfRecords(E_S_DAM_CFG_SECTOR eLogSector)
{
  uint32 u32ToReturn = 0u;
  static T_U_S_DAM_SECTOR_INDEX uSector;
  uint32 u32IndexAddress = S_DAM_mgU32HeaderIndex(eLogSector);
  if (TRUE
      == S_DAM_SCFG_bRead((uint8 *) uSector.au8Data, u32IndexAddress,
          sizeof(uSector)))
  {
    if (S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord
        >= uSector.Index.u16Current)
    {
      if ((TRUE == uSector.Index.u8Override)
          && (TRUE == S_S_DAM_CFG_CFG_SETUP[eLogSector].bOverwritable))
      {
        u32ToReturn = S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord;
      }
      else
      {
        u32ToReturn = uSector.Index.u16Current;
      }
    }
  }
  return u32ToReturn;
}

uint32 S_DAM_u32GetFirstRecordId(E_S_DAM_CFG_SECTOR eLogSector)
{
  uint32 u32ToReturn = 0u;
  static T_U_S_DAM_SECTOR_INDEX uSector;
  uint8 *pu8Index;
  uint32 u32IndexAddress;
  pu8Index = uSector.au8Data;
  u32IndexAddress = S_DAM_mgU32HeaderIndex(eLogSector);
  if (TRUE == S_DAM_SCFG_bRead(pu8Index, u32IndexAddress, sizeof(uSector)))
  {
    if ((uSector.Index.u16Current > 0u) && (FALSE == uSector.Index.u8Override)
        && (uSector.Index.u16Current < 0xFFFFu))
    {
      u32ToReturn = 1u;
    }
    else
    {
      /* To check override for return current index */
      if ((TRUE == uSector.Index.u8Override)
          && (TRUE == S_S_DAM_CFG_CFG_SETUP[eLogSector].bOverwritable))
      {
        if (S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord
            > uSector.Index.u16Current)
        {

          u32ToReturn = (uint32) uSector.Index.u16Current + 1u;
        }
        else if (S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord
            == uSector.Index.u16Current)
        {

          u32ToReturn = 1u;
        }
        else
        {
          /* do nothing */;
        }
      }
      else
      {
        u32ToReturn = 0u;
      }
    }
  }
  return u32ToReturn;
}

uint32 S_DAM_u32GetLastRecordId(E_S_DAM_CFG_SECTOR eLogSector)
{
  uint32 u32ToReturn = 0u;
  static T_U_S_DAM_SECTOR_INDEX uSector;
  uint8 * pu8Index = (uint8 *) uSector.au8Data;
  uint32 u32IndexAddress;

  u32IndexAddress = S_DAM_mgU32HeaderIndex(eLogSector);

  if (TRUE == S_DAM_SCFG_bRead(pu8Index, u32IndexAddress, sizeof(uSector)))
  {
    if (uSector.Index.u16Current
        <= S_S_DAM_CFG_CFG_SETUP[eLogSector].u16NumberOfRecord)
    {
      u32ToReturn = uSector.Index.u16Current;
    }
    else
    {
      /* Invalid value has been written to sector index, because it's larger
       * than the number of records. */
      S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__,
          (((uint32) eLogSector) << 16) | ((uint32) uSector.Index.u16Current));
    }
  }
  else
  {
    /* Failed to read the index. */
    S_DAM_SCFG_vOnErrorDetected((uint16) __LINE__, (uint32) eLogSector);
  }
  return u32ToReturn;
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

static uint32 S_DAM_mgU32HeaderIndex(E_S_DAM_CFG_SECTOR eLogSector)
{
  uint32 headerIndex;

#if (S_DAM_CFG_INDEX_STORED_IN_SECTOR)
  headerIndex = S_S_DAM_CFG_CFG_SETUP[eLogSector].u32AreaStartAddress;
#else
  headerIndex = (uint32)eLogSector * (uint32)S_DAM_CFG_HEADER_SECTOR_SIZE;
#endif

  return headerIndex;
}
/*
 * End of file
 */

