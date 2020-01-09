/*******************************************************************************
 * \file    mem.c
 * \brief   System memory management
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2019-02-19 14:24:47 +0800 (Tue, 19 Feb 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 142 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "rte.h"

/* Module header */
#define EEPROM_EXPORT_H
  #include "mem_api.h"
  #include "mem_scb.h"
  #include "mem_cfg.h"
  #include "mem_scfg.h"
  #include "mem_conf.h"
  #include "mem_rte.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
static uint8 mg_u8DataBuf[5];
static uint8 mg_au8DataBase[MEM_CFG_LENGHT_EMEM];
/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void mg_vSaveTrimData(void);
static void mg_vReadTrimData(void);
static void mg_vReadFwRevData(void);
static void mg_vSaveFwRevData(void);
static void mg_vReadAcOffset(void);
static void mg_vSaveAcOffset(void);
static void mg_vReadMfrInfoData(void);
static void mg_vSaveMfrInfoData(void);

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief     Read init data from EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void MEM_vInit(void)
{
  mg_vReadFwRevData();
  mg_vReadTrimData();
  mg_vReadAcOffset();
  mg_vReadMfrInfoData();
}

/*******************************************************************************
 * \brief         De-init data from EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void MEM_vDeInit(void)
{
}

/** ****************************************************************************
 * \brief  MEM_vWriteTomem
 * \param[in]  -  
 * \param[out] -
 *
 * \return  -Write to mem (Ram)
 *
 **************************************************************************** */
void MEM_vWriteToMem(uint32 u32WriteAddr,const uint8 *pu8Buffer,uint32 u32NumByteToWrite )
{
	uint32 u32CntLoop = 0;
	for(u32CntLoop = 0; u32CntLoop < u32NumByteToWrite ; u32CntLoop++ )
	{
		mg_au8DataBase[u32WriteAddr + u32CntLoop] = pu8Buffer[u32CntLoop];
	}
}
 
 /** ****************************************************************************
 * \brief  MEM_vReadFromMem
 * \param[in]  -  
 * \param[out] -
 *
 * \return  -Read from mem (Ram)
 *
 **************************************************************************** */
boolean MEM_vReadFromMem(uint32 u32ReadAddr,uint8 *pu8Buffer,uint32 u32NumByteToRead )
{	
	uint8 statusRead = TRUE;
	uint32 u32CntLoop = 0;
	for(u32CntLoop = 0; u32CntLoop < u32NumByteToRead ; u32CntLoop++ )
	{
		pu8Buffer[u32CntLoop] = mg_au8DataBase[u32ReadAddr + u32CntLoop];
	}	
	return statusRead;
}

 /** ****************************************************************************
 * \brief  emem_u16Getlenght
 * \param[in]  -  
 * \param[out] -
 *
 * \return  - size array emem
 *
 **************************************************************************** */
uint16 MEM_u16Getlenght(uint8 index)
{		
	return MEM_CFG_SETUP[index].u16Length;
} 
 /** ****************************************************************************
 * \brief  emem_u16GetOffset
 * \param[in]  -  
 * \param[out] -
 *
 * \return  - offset array emem
 *
 **************************************************************************** */
uint16 MEM_u16GetOffset(uint8 index)
{		
	return MEM_CFG_SETUP[index].u16Offset;
} 
 /** ****************************************************************************
 * \brief  emem_u16Getlenght
 * \param[in]  -  
 * \param[out] -
 *
 * \return  - 
 *
 **************************************************************************** */
void MEM_vWrite2EEPORM(uint16 u16Lenght , uint16 u16Offset)
{		
	uint16 u16TmpAddrEEP;
	uint16 u16TmpAddrEmem;
	uint8 u8Buff[MEM_CFG_BIFFER_MAX_LEN];

	/*=========== Write to EEPROM =====================================================*/
	u16TmpAddrEEP = MEM_CFG_EEPROM_ADDRESS_START + u16Offset;
	u16TmpAddrEmem = u16Offset;
	MEM_vReadFromMem(u16TmpAddrEmem ,u8Buff,u16Lenght);
	MEM_SCFG_vWriteMem(u16TmpAddrEEP,u8Buff,u16Lenght);
} 

 /** ****************************************************************************
 * \brief  emem_vRead2EEPORM
 * \param[in]  -  
 * \param[out] -
 *
 * \return  - Read from EEPROM To Emem(RAM)
 *
 **************************************************************************** */
void MEM_vRead2EEPORM(uint16 u16Lenght ,uint16 u16Offset)
{		
	uint16 u16TmpAddrEEP;
	uint16 u16TmpAddrEmem;
	uint8 u8Buff[MEM_CFG_BIFFER_MAX_LEN];
	
	/*============== Read from EEPROM To Emem ============================*/	
	u16TmpAddrEEP = MEM_CFG_EEPROM_ADDRESS_START + u16Offset;
	u16TmpAddrEmem = u16Offset;

		MEM_SCFG_vReadMem(u8Buff,u16TmpAddrEEP,u16Lenght);		
		MEM_vWriteToMem(u16TmpAddrEmem,u8Buff,u16Lenght);
} 

/*******************************************************************************
 * \brief     Save data to EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void MEM_vSaveData(void)
{
  static uint8 u8State = 0;
  switch(u8State)
  {
   case 0:
   {
     mg_vSaveTrimData();
     u8State =1u;
     break;
   }
   case 1:
   {
     mg_vSaveFwRevData();
     u8State =2u;
     break;
   }
   case 2:
   {
     mg_vSaveAcOffset();
     u8State =3;
     break;
   }
   case 3:
   {
     mg_vSaveMfrInfoData();
     u8State =0;
     break;
   }
   default:
   {
     u8State = 0;
     break;
   }
  }
}

/*******************************************************************************
 * \brief         Read the black box page write distance from eeprom
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
uint8 MEM_vReadBlcBoxPageWrDis(void)
{
	uint8 u8Data;
	
	MEM_SCFG_vReadMem(&u8Data,EEP_ADR_BLACK_BOX_PAGE_W_DIS,1u);
	
	return u8Data;
}

/*******************************************************************************
 * \brief         Write the black box page write distance to eeprom
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void MEM_vWriteBlcBoxPageWrDis(uint8 u8Data)
{
	MEM_SCFG_vWriteMem(EEP_ADR_BLACK_BOX_PAGE_W_DIS,&u8Data,1u);
}
/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/*******************************************************************************
 * \brief     Read init data from EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vReadTrimData(void)
{
  uint8 u8Crc = 0,u8DelayCnt = 0;
  DWORD_VAL u32EepReadTmp;
	
  /* SEC V1 Trim */
  MEM_SCFG_vReadMem(mg_u8DataBuf,EEP_ADR_V1_1_TRIM_LSB, 3u);
  u32EepReadTmp.Bytes.LB = mg_u8DataBuf[0];
  u32EepReadTmp.Bytes.HB = mg_u8DataBuf[1];

  u8Crc = MEM_CFG_CRC_INIT;
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepReadTmp.Bytes.LB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepReadTmp.Bytes.HB);
  if (u8Crc != mg_u8DataBuf[2])
  {
    MONCTRL_Rte_Write_P_u16TrimV1Gain(EEP_V1_CHA_TRIM_DEFAULT);
    MONCTRL_Rte_Write_P_u16TrimV1GainAct(EEP_V1_CHA_TRIM_DEFAULT);
  }
  else
  {
    MONCTRL_Rte_Write_P_u16TrimV1Gain(u32EepReadTmp.Words.LW);
    MONCTRL_Rte_Write_P_u16TrimV1GainAct(u32EepReadTmp.Words.LW);
  }

  /* delay Between command */
  for(u8DelayCnt = 0; u8DelayCnt < 150u; u8DelayCnt ++)
  {
    __nop();
  }
  
  /* COM VSB Trim */
  MEM_SCFG_vReadMem(mg_u8DataBuf,EEP_ADR_VSB_TRIM_LSB, 3u);
  u32EepReadTmp.Bytes.LB = mg_u8DataBuf[0];
  u32EepReadTmp.Bytes.HB = mg_u8DataBuf[1];

  u8Crc = MEM_CFG_CRC_INIT;
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepReadTmp.Bytes.LB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepReadTmp.Bytes.HB);
  if (u8Crc != mg_u8DataBuf[2])
  {
    MONCTRL_Rte_Write_P_u16TrimVsbGain(EEP_VSB_TRIM_DEFAULT);
  }
  else
  {
    MONCTRL_Rte_Write_P_u16TrimVsbGain(u32EepReadTmp.Words.LW);
  }

  /* delay Between command */
  for(u8DelayCnt = 0; u8DelayCnt < 150u; u8DelayCnt ++)
  {
    __nop();
  }
} /* EEP_mg_vReadTrimData */

/*******************************************************************************
 * \brief         Save trim data to EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vSaveTrimData(void)
{
  uint8 u8Crc = 0;
  uint8 au8EepromWriteBuf[10] = {0,0,0,0,0,0,0,0,0,0};
	WORD_VAL uTrimGain;

  /* VSB trim data save*/
  if (MEM_RTE_Read_B_R_VSB_TRIM() != FALSE )
  {
		MEM_RTE_Read_R_uTrimVsbGain(&uTrimGain.u16Val);
    au8EepromWriteBuf[0] = uTrimGain.Bytes.LB;
    au8EepromWriteBuf[1] = uTrimGain.Bytes.HB;
    u8Crc = MEM_CFG_CRC_INIT;
    u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.LB);      /* calculat CRC */
    au8EepromWriteBuf[2] = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.HB);    /*get CRC*/
		if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
		{
			 MEM_Rte_Write_B_R_VSB_TRIM(FALSE);
       MEM_SCFG_vWriteMem(EEP_ADR_VSB_TRIM_LSB, au8EepromWriteBuf, 3u);
		}
  }

  /* V1 trim data save */
  if (MEM_RTE_Read_B_R_V1_TRIM() != FALSE)
  {
		MEM_RTE_Read_R_uTrimV1Gain(&uTrimGain.u16Val);
    au8EepromWriteBuf[0] = uTrimGain.Bytes.LB;
    au8EepromWriteBuf[1] = uTrimGain.Bytes.HB;
    u8Crc = MEM_CFG_CRC_INIT;
    u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.LB);      /* calculat CRC */
    au8EepromWriteBuf[2] = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.HB);    /*get CRC*/
		if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
		{
			MEM_Rte_Write_B_R_V1_TRIM(FALSE);
			MEM_SCFG_vWriteMem(EEP_ADR_V1_1_TRIM_LSB, au8EepromWriteBuf, 3u);
		}
  }
} /* mg_vSaveTrimData */ 

/*******************************************************************************
 * \brief         Read Firmware revision from EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vReadFwRevData(void)
{
  uint8 u8Crc, u8DelayCnt;
  DWORD_VAL u32EepFwRev;

  /* Pri FW REV */
  MEM_SCFG_vReadMem(mg_u8DataBuf,EEP_REVI_PRI_APP_MAJOR, 4u);
  u32EepFwRev.Bytes.LB = mg_u8DataBuf[0];
  u32EepFwRev.Bytes.HB = mg_u8DataBuf[1];
  u32EepFwRev.Bytes.UB = mg_u8DataBuf[2];
  u32EepFwRev.Bytes.MB = 0;

  u8Crc = MEM_CFG_CRC_INIT;
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.LB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.HB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.UB);
  if (u8Crc != mg_u8DataBuf[3])
  {
    u32EepFwRev.Bytes.LB = PRI_MAJOR_SW_VERSION;
    u32EepFwRev.Bytes.HB = PRI_MINOR_SW_VERSION;
    u32EepFwRev.Bytes.UB = PRI_DEBUG_SW_VERSION;
  }

	MONCTRL_Rte_Write_R_u32PmbusFwRevPri(u32EepFwRev.u32Val);

  /* delay Between command */
  for(u8DelayCnt = 0; u8DelayCnt < 150u; u8DelayCnt ++)
  {
    __nop();
  }
  
	/* Pri Boot FW REV */
  MEM_SCFG_vReadMem(mg_u8DataBuf,EEP_REVI_PRI_BOOT_MAJOR, 4u);
  u32EepFwRev.Bytes.LB = mg_u8DataBuf[0];
  u32EepFwRev.Bytes.HB = mg_u8DataBuf[1];
  u32EepFwRev.Bytes.UB = mg_u8DataBuf[2];
  u32EepFwRev.Bytes.MB = 0;

  u8Crc = MEM_CFG_CRC_INIT;
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.LB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.HB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.UB);
  if (u8Crc != mg_u8DataBuf[3])
  {
    u32EepFwRev.Bytes.LB = PRI_MAJOR_BL_VERSION;
    u32EepFwRev.Bytes.HB = PRI_MINOR_BL_VERSION;
    u32EepFwRev.Bytes.UB = PRI_DEBUG_BL_VERSION;
  }

	MONCTRL_Rte_Write_R_u32PmbusBlRevPri(u32EepFwRev.u32Val);

  /* delay Between command */
  for(u8DelayCnt = 0; u8DelayCnt < 150u; u8DelayCnt ++)
  {
    __nop();
  }
	
  /* Sec FW REV */
  MEM_SCFG_vReadMem(mg_u8DataBuf,EEP_REVI_SEC_APP_MAJOR, 4u);
  u32EepFwRev.Bytes.LB = mg_u8DataBuf[0];
  u32EepFwRev.Bytes.HB = mg_u8DataBuf[1];
  u32EepFwRev.Bytes.UB = mg_u8DataBuf[2];
  u32EepFwRev.Bytes.MB = 0;

  u8Crc = MEM_CFG_CRC_INIT;
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.LB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.HB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.UB);
  if (u8Crc != mg_u8DataBuf[3])
  {
    u32EepFwRev.Bytes.LB = SEC_MAJOR_SW_VERSION;
    u32EepFwRev.Bytes.HB = SEC_MINOR_SW_VERSION;
    u32EepFwRev.Bytes.UB = SEC_DEBUG_SW_VERSION;
  }

	MONCTRL_Rte_Write_R_u32PmbusFwRevSec(u32EepFwRev.u32Val);

  /* delay Between command */
  for(u8DelayCnt = 0; u8DelayCnt < 150u; u8DelayCnt ++)
  {
    __nop();
  }
  
  /* Sec Boot FW REV */
  MEM_SCFG_vReadMem(mg_u8DataBuf,EEP_REVI_SEC_BOOT_MAJOR, 4u);
  u32EepFwRev.Bytes.LB = mg_u8DataBuf[0];
  u32EepFwRev.Bytes.HB = mg_u8DataBuf[1];
  u32EepFwRev.Bytes.UB = mg_u8DataBuf[2];
  u32EepFwRev.Bytes.MB = 0;

  u8Crc = MEM_CFG_CRC_INIT;
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.LB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.HB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.UB);
  if (u8Crc != mg_u8DataBuf[3])
  {
    u32EepFwRev.Bytes.LB = SEC_MAJOR_BL_VERSION;
    u32EepFwRev.Bytes.HB = SEC_MINOR_BL_VERSION;
    u32EepFwRev.Bytes.UB = SEC_DEBUG_BL_VERSION;
  }

	MONCTRL_Rte_Write_R_u32PmbusBlRevSec(u32EepFwRev.u32Val);

  /* delay Between command */
  for(u8DelayCnt = 0; u8DelayCnt < 150u; u8DelayCnt ++)
  {
    __nop();
  }
	
  /* Sec Boot FW REV */
  u32EepFwRev.u32Val = MEM_SCFG_u32ReadBootloaderFwVer();
	MONCTRL_Rte_Write_R_u32PmbusBlRevCom(u32EepFwRev.u32Val);
	
	/* Com FW REV*/
	u32EepFwRev.Bytes.LB = COM_MAJOR_SW_VERSION;
	u32EepFwRev.Bytes.HB = COM_MINOR_SW_VERSION;
	u32EepFwRev.Bytes.UB = COM_DEBUG_SW_VERSION;
	
	MONCTRL_Rte_Write_R_u32PmbusFwRevCom(u32EepFwRev.u32Val);
  
} /* REV_vReadFwRevData */

/*******************************************************************************
 * \brief         Save Firmware revision to EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vSaveFwRevData(void)
{
  uint8 u8Crc = 0;
  uint8 au8EepromWriteBuf[5] = {0,0,0,0,0};
	DWORD_VAL u32EepFwRev;
	static uint8 u8SavePriState = 0;
	static uint8 u8SaveSecState = 0;
	
  /* pri rev */
  if (MEM_RTE_Read_B_R_PRI_REV_UPDATE() != FALSE)
  {
		switch(u8SavePriState)
		{
			case 0:
			{
				MEM_RTE_Read_R_uPmbusFwRevPri(&u32EepFwRev.u32Val);
				au8EepromWriteBuf[0] = u32EepFwRev.Bytes.LB;
				au8EepromWriteBuf[1] = u32EepFwRev.Bytes.HB;
				au8EepromWriteBuf[2] = u32EepFwRev.Bytes.UB;
				
				u8Crc = MEM_CFG_CRC_INIT;
				u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.LB);
				u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.HB);
				au8EepromWriteBuf[3] = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.UB);
				if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
				{
					MEM_SCFG_vWriteMem(EEP_REVI_PRI_APP_MAJOR, au8EepromWriteBuf, 4u);
					u8SavePriState = 1;
				}
				break;
			}
			case 1:
			{
				MEM_RTE_Read_R_uPmbusBlRevPri(&u32EepFwRev.u32Val);
				au8EepromWriteBuf[0] = u32EepFwRev.Bytes.LB;
				au8EepromWriteBuf[1] = u32EepFwRev.Bytes.HB;
				au8EepromWriteBuf[2] = u32EepFwRev.Bytes.UB;
				
				u8Crc = MEM_CFG_CRC_INIT;
				u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.LB);
				u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.HB);
				au8EepromWriteBuf[3] = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.UB);
				if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
				{
					MEM_Rte_Write_B_R_PRI_REV_UPDATE(FALSE);
					MEM_SCFG_vWriteMem(EEP_REVI_PRI_BOOT_MAJOR, au8EepromWriteBuf, 4u);
					u8SavePriState = 0;
				}
				break;
			}
			default:
			{
				u8SavePriState = 0;
				break;
			}
		}
  }

  /* sec rev */
  if (MEM_RTE_Read_B_R_SEC_REV_UPDATE() != FALSE )
  {
		switch(u8SaveSecState)
		{
			case 0:
			{
				MEM_RTE_Read_R_uPmbusFwRevSec(&u32EepFwRev.u32Val);
				au8EepromWriteBuf[0] = u32EepFwRev.Bytes.LB;
				au8EepromWriteBuf[1] = u32EepFwRev.Bytes.HB;
				au8EepromWriteBuf[2] = u32EepFwRev.Bytes.UB;
				
				u8Crc = MEM_CFG_CRC_INIT;
				u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.LB);
				u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.HB);
				au8EepromWriteBuf[3] = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.UB);
				if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
				{
					MEM_SCFG_vWriteMem(EEP_REVI_SEC_APP_MAJOR, au8EepromWriteBuf, 4u);
					u8SaveSecState = 1;
				}
				break;
			}
			case 1:
			{
				MEM_RTE_Read_R_uPmbusBlRevSec(&u32EepFwRev.u32Val);
				au8EepromWriteBuf[0] = u32EepFwRev.Bytes.LB;
				au8EepromWriteBuf[1] = u32EepFwRev.Bytes.HB;
				au8EepromWriteBuf[2] = u32EepFwRev.Bytes.UB;
				
				u8Crc = MEM_CFG_CRC_INIT;
				u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.LB);
				u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.HB);
				au8EepromWriteBuf[3] = MEM_SCFG_u8GetCrc8(u8Crc, u32EepFwRev.Bytes.UB);
				if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
				{
					MEM_Rte_Write_B_R_SEC_REV_UPDATE(FALSE);
					MEM_SCFG_vWriteMem(EEP_REVI_SEC_BOOT_MAJOR, au8EepromWriteBuf, 4u);
					u8SaveSecState = 0;
				}
				break;
			}
			default:
			{
				u8SaveSecState = 0;
				break;
			}
		}
  }
} /* REV_vSaveFwRevData */

/*******************************************************************************
 * \brief         Read MFR information from EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/

static void mg_vReadMfrInfoData(void)
{
  uint8 u8Crc;
  uint8 u8Loop;
  uint8 u8ReadDataBuf[MG_EE_ADR_MFR_INFO_SIZE];
	
  MEM_SCFG_vReadMem(u8ReadDataBuf,MG_EE_ADR_MFR_INFO_STR, MG_EE_ADR_MFR_INFO_SIZE);
  
  u8Crc = MEM_CFG_CRC_INIT;
  for(u8Loop=0;u8Loop<MG_EE_ADR_MFR_INFO_SIZE;u8Loop++)	
  {
    u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u8ReadDataBuf[u8Loop]);
  }
  
  if(0 != u8Crc)
  {
    for(u8Loop=0;u8Loop<(MG_EE_ADR_MFR_INFO_SIZE-1u);u8Loop++)	
    {
      u8ReadDataBuf[u8Loop] = 0;
    }
  }
  
  for(u8Loop=0;u8Loop<(MG_EE_ADR_MFR_INFO_SIZE-1u);u8Loop++)	
  {
    MONCTRL_Rte_Write_P_u8MfrInfo(u8ReadDataBuf[u8Loop],u8Loop);
  }
} /* REV_vSaveMfrInfoData */

/*******************************************************************************
 * \brief         Save MFR information to EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vSaveMfrInfoData(void)
{
  uint8 u8Crc = 0;
  uint8 au8EepromWriteBuf[MG_EE_ADR_MFR_INFO_SIZE];
  uint8 u8Loop;
	
  if (MEM_Rte_Read_B_R_MFR_INFO_UPDATE() != FALSE)
  {
    MEM_Rte_Read_R_au8MfrInfo(au8EepromWriteBuf);
    u8Crc = MEM_CFG_CRC_INIT;
		for(u8Loop=0;u8Loop<(MG_EE_ADR_MFR_INFO_SIZE -1u);u8Loop++)	
    {
      u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, au8EepromWriteBuf[u8Loop]);
    }
    au8EepromWriteBuf[MG_EE_ADR_MFR_INFO_SIZE-1u] = u8Crc;

    if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
    {
      MEM_SCFG_vWriteMem(MG_EE_ADR_MFR_INFO_STR, au8EepromWriteBuf, MG_EE_ADR_MFR_INFO_SIZE);
    }
    
    MONCTRL_Rte_Write_B_P_MFR_INFO_UPDATE(FALSE);
  }
} /* REV_vSaveMfrInfoData */


/*******************************************************************************
 * \brief         Read AC Offset to EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vReadAcOffset(void)
{
  uint8 u8Crc;
  WORD_VAL uAcOffset;

  /* Pri FW REV */
  MEM_SCFG_vReadMem(mg_u8DataBuf,EEP_ADR_AC_CURR_OFFSET_LSB, 3u);
  uAcOffset.Bytes.LB = mg_u8DataBuf[0];
  uAcOffset.Bytes.HB = mg_u8DataBuf[1];

  u8Crc = MEM_CFG_CRC_INIT;
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, uAcOffset.Bytes.LB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, uAcOffset.Bytes.HB);
  if (u8Crc != mg_u8DataBuf[2])
  {
    uAcOffset.s16Val = 0;
    MONCTRL_Rte_Write_B_P_AC_OFFSET_SAVEED(FALSE);
  }
  else
  {
    MONCTRL_Rte_Write_B_P_AC_OFFSET_SAVEED(TRUE);
  }

  MONCTRL_Rte_Write_R_s16AcOffset(uAcOffset.s16Val);
}

/*******************************************************************************
 * \brief         Save AC Offset to EEPROM
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vSaveAcOffset(void)
{
  uint8 u8Crc = 0;
  uint8 au8EepromWriteBuf[3] = {0,0,0};
	WORD_VAL uAcOffset;
  if(FALSE != MEM_RTE_Read_B_R_AC_OFFSET_NEED_SAVE())
  {
    MEM_Rte_Read_R_uAcOffset(&uAcOffset);
    au8EepromWriteBuf[0] = uAcOffset.Bytes.LB;
    au8EepromWriteBuf[1] = uAcOffset.Bytes.HB;
    
    u8Crc = MEM_CFG_CRC_INIT;
    u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, uAcOffset.Bytes.LB);
    au8EepromWriteBuf[2] = MEM_SCFG_u8GetCrc8(u8Crc, uAcOffset.Bytes.HB);
    if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
    {
      MEM_SCFG_vWriteMem(EEP_ADR_AC_CURR_OFFSET_LSB, au8EepromWriteBuf, 3u);
    }
    
    MONCTRL_Rte_Write_B_P_AC_OFFSET_NEED_SAVE(FALSE);
    MONCTRL_Rte_Write_B_P_AC_OFFSET_SAVEED(TRUE);
  }
}
/*
 * End of file
 */
