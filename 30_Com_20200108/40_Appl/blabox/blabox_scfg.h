/** ****************************************************************************
 * \file    BLABOX_SCFG_H.h
 * \brief   COM module implementation configuration
 *
 * \section AUTHOR
 *  S. Ratchanon
 *
 * \section SVN
 *  $Date: 2016-06-10 16:01:06 +0200 (Fr, 10 Jun 2016) $
 *  $Author: dementm $
 *  $Revision: 1413 $
 *
 * \section LICENSE
 *  Copyright (c) 2014 Delta Energy Systems (Thailand) GmbH.
 *  All rights reserved.
 **************************************************************************** */
 
#ifndef BLABOX_SCFG_H
#define BLABOX_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

#include "mem_api.h"
#include "s_dam_api.h"
#include "fanctrl_api.h"

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
 
/*******************************************************************************
 * Function:        s_dam
 * Parameters:      -
 * Returned value:  -
 * Description:     -
 *
 ******************************************************************************/
SINLINE boolean BLABOX_SCFG_Write(uint8 eLogSector,const uint8* pu8Buffer) 
{	
	boolean bRet;
	switch (eLogSector)
	{
		case BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA:
		{
			bRet = S_DAM_bWrite(S_DAM_CFG_BLABOX_EVENTDATA_SECTOR,pu8Buffer);
			break;
		}
		case BLABOX_CFG_CONFIG_SECTOR_HEADER:
		{
			bRet = S_DAM_bWrite(S_DAM_CFG_BLABOX_HEADER_SECTOR,pu8Buffer);
			break;
		}
		case BLABOX_CFG_CONFIG_SECTOR_CONFIG:
		{
			bRet = S_DAM_bWrite(S_DAM_CFG_BLABOX_CONFIG_SECTOR,pu8Buffer);
			break;
		}
		default:
		{
			bRet = FALSE;
			break;
		}
	}
	return bRet;
}
   
SINLINE boolean BLABOX_SCFG_Read(uint8 eLogSector,uint8* pu8Buffer,uint16 u16RecordNumber) 
{	
	boolean bRet;
	switch (eLogSector)
	{
		case BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA:
		{
			bRet = S_DAM_bRead(S_DAM_CFG_BLABOX_EVENTDATA_SECTOR,pu8Buffer,u16RecordNumber);
			break;
		}
		case BLABOX_CFG_CONFIG_SECTOR_HEADER:
		{
			bRet = S_DAM_bRead(S_DAM_CFG_BLABOX_HEADER_SECTOR,pu8Buffer,u16RecordNumber);
			break;
		}
		case BLABOX_CFG_CONFIG_SECTOR_CONFIG:
		{
			bRet = S_DAM_bRead(S_DAM_CFG_BLABOX_CONFIG_SECTOR,pu8Buffer,u16RecordNumber);
			break;
		}
		default:
		{
			bRet = FALSE;
			break;
		}
	}
	return bRet;
}

SINLINE uint32 BLABOX_SCFG_u32GetNumberOfRecords()
{
	return S_DAM_u32GetNumberOfRecords(S_DAM_CFG_BLABOX_EVENTDATA_SECTOR);
}

SINLINE uint32 BLABOX_SCFG_u32GetLastRecordId() 
{
	return S_DAM_u32GetLastRecordId(S_DAM_CFG_BLABOX_EVENTDATA_SECTOR);
}
/*******************************************************************************
 * Function:        Emem
 * Parameters:      -
 * Returned value:  -
 * Description:     -
 *
 ******************************************************************************/
SINLINE void BLABOX_SCFG_vEEPROM2Emem(uint16 u16Lenght , uint16 u16Offset)
{
  MEM_vRead2EEPORM(u16Lenght,u16Offset);
}
SINLINE void BLABOX_SCFG_vEmem2EEPROM(uint16 u16Lenght  , uint16 u16Offset)
{
  MEM_vWrite2EEPORM(u16Lenght,u16Offset);
}
SINLINE uint16 BLABOX_SCFG_u16Getlenght(uint8 index)
{
   return MEM_u16Getlenght(index);
}

SINLINE uint8 BLABOX_SCFG_u8ReadFanBitFail(uint8 u8Index)
{
 return FANCTRL_u8ReadFanBitFail(u8Index);
}
SINLINE uint8 BLABOX_SCFG_u8ReadFanBitWarn(uint8 u8Index)
{
 return FANCTRL_u8ReadFanBitWarn(u8Index);
}



 
 #ifdef __cplusplus
  }
#endif
#endif  /* BLABOX_SCFG_H */

  
/*
 * End of file
 */
