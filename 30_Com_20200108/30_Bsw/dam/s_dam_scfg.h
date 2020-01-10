/** ****************************************************************************
 * \file    s_dam_scfg.h
 * \brief   S_DAM module server configuration header
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

#ifndef S_DAM_SCFG_H
#define S_DAM_SCFG_H

#include <global.h>

#include "mem_api.h"

//#include "devlog_cfg.h"
//#include "devlog_scb.h"
#include "crc_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/
#define MG_CRC_SEED    0x0000U
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
 * \brief   Call server module to enter an event in the developer log
 *
 **************************************************************************** */
SINLINE void S_DAM_SCFG_vOnErrorDetected(uint16 u16LineNumber,
    uint32 u32Value)
{
 // DEVLOG_SCB_vLogEvent(DEVLOG_E_MODULE_S_DAM, u16LineNumber, u32Value);
}

/* Check CRC */
SINLINE uint32 S_DAM_SCFG_u32Crc(const uint8* pu8Buffer, uint32 u32NumByteToCheckCRC)
{
	uint32 u32Loop,u32Ret;
	
	u32Ret = MG_CRC_SEED;
	for(u32Loop=0;u32Loop<u32NumByteToCheckCRC;u32Loop++)
	{
		u32Ret = CRC_u16GetCrc16((uint16)u32Ret, *(pu8Buffer+u32Loop));
	}
  return u32Ret;
}

/* Read area. */
SINLINE boolean S_DAM_SCFG_bRead(uint8* pu8Buffer, uint32 u32ReadAddr,
    uint32 u32NumByteToRead)
{
  boolean bToReturn = TRUE;
  MEM_vReadFromMem(u32ReadAddr ,pu8Buffer,u32NumByteToRead);
  return bToReturn;
}

/* Write a block to memory.*/
SINLINE boolean S_DAM_SCFG_bWrite(const uint8* pu8Buffer, uint32 u32WriteAddr,
    uint32 u32NumByteToWrite)
{
  boolean bToReturn = TRUE;
  MEM_vWriteToMem(u32WriteAddr, pu8Buffer, u32NumByteToWrite);
  return bToReturn;
}

#ifdef __cplusplus
}
#endif

#endif

/*
 * End of file
 */

