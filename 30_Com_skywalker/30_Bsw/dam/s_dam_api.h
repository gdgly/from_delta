/** ****************************************************************************
 * \file    s_dam_api.h
 * \brief   S_DAM module interface header
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

#ifndef S_DAM_API_H
#define S_DAM_API_H

#include "s_dam_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/

/** ****************************************************************************
 * \brief Read a record
 * \param[in] eAreaIndex The area to read a record from
 * \param[in] pu8Buffer : pointer to the buffer containing the data that has been read.
 * \param[in] u32RecordNumber: the record number to be read.
 * \return Returns TRUE/FALSE based on CRC check passing/failing or index not being available
 **************************************************************************** */
extern boolean S_DAM_bRead(E_S_DAM_CFG_SECTOR eLogSector, uint8* pu8Buffer,
    uint16 u16RecordNumber);

/******************************************************************************
 * \brief Store a record in the allocated area, unless there is no space (and it's not overwritable) or there is a failure to write.
 * \param[in] eAreaIndex The area to add a record to.
 * \param[in] pu8Buffer : pointer to the buffer  containing the data to be written.
 * \return Returns TRUE/FALSE based on CRC check passing/failing or index not being available
 * **************************************************************************** */
extern boolean S_DAM_bWrite(E_S_DAM_CFG_SECTOR eLogSector, const uint8* pu8Buffer);

/** ****************************************************************************
 * \brief Write to a specific record
 * \param[in] eLogSector The area to write a record to
 * \param[in] pu8Buffer : pointer to the buffer containing the data to be written.
 * \param[in] u16RecordNumber: the record number to write to.
 * \return Returns TRUE/FALSE based on CRC check passing/failing or index not being available
 **************************************************************************** */
extern boolean S_DAM_bWriteToRecord(E_S_DAM_CFG_SECTOR eLogSector, const uint8* pu8Buffer,
    uint16 u16RecordNumber);

/** ****************************************************************************
 * \brief Read the area metadata
 * \param[in] eAreaIndex The area to read about
 * \return Returns information about the log
 **************************************************************************** */
extern uint32 S_DAM_u32GetNumberOfRecords(E_S_DAM_CFG_SECTOR eLogSector);
extern uint32 S_DAM_u32GetFirstRecordId(E_S_DAM_CFG_SECTOR eLogSector);
extern uint32 S_DAM_u32GetLastRecordId(E_S_DAM_CFG_SECTOR eLogSector);

/* MarkAsErasable - used to Erase a non-overwritable area so that it can be written to again if needed. */
extern boolean S_DAM_vReset(E_S_DAM_CFG_SECTOR eLogSector);
extern boolean S_DAM_bResetRecord(E_S_DAM_CFG_SECTOR eLogSector, uint16 u16RecordNumber);

#ifdef __cplusplus
}
#endif

#endif

/*
 * End of file
 */

