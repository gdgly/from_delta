/******************************************************************************
 * \file    timectrl.c
 * \brief   calculate psu operation time
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-02-19 14:24:47 +0800 (Tue, 19 Feb 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 142 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 *******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

/* Module header */
#define TIMECTRL_EXPORT_H
  #include "timectrl_api.h"
  #include "timectrl_cfg.h"
  #include "timectrl_conf.h"
  #include "timectrl_scb.h"
  #include "timectrl_scfg.h"
	#include "timectrl_rte.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

#define MG_MINUTE_IN_1S            ((uint8)59u)
#define MG_HALF_HOUR_IN_MIN        ((uint8)30u)

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

static uint16    mg_u16MinIn1SCnt = MG_MINUTE_IN_1S;
static uint8     mg_u8HalfHourInMinCnt = MG_HALF_HOUR_IN_MIN;
static uint8     mg_u8SaveMinutePos = 0;
static DWORD_VAL mg_u32MinutesUsed;
static DWORD_VAL mg_u32MinutesUsedOld;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Read operating minutes and calculate Hours used
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMECTRL_vInit(void)
{	
  uint8 u8Crc = 0;
  uint8 u8Crc1 = 0;
  uint8 u8Dummy1 = 0;
  uint8 u8Dummy2 = 0;
  DWORD_VAL u32HoursUsed;
  DWORD_VAL u32MinutesUsed_temp0;
  DWORD_VAL u32MinutesUsed_temp1;
	uint8 u8DataBuf[5]={0,0,0,0,0};

  /* read used minutes */
  mg_u32MinutesUsed.u32Val = 0;

  TIMECATL_SCFG_vReadMem(u8DataBuf);
  u32MinutesUsed_temp0.Bytes.MB = u8DataBuf[3];
  u32MinutesUsed_temp0.Bytes.UB = u8DataBuf[2];
  u32MinutesUsed_temp0.Bytes.HB = u8DataBuf[1];
  u32MinutesUsed_temp0.Bytes.LB = u8DataBuf[0];

  u8Crc = CRC_INIT_02;
  u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, u32MinutesUsed_temp0.Bytes.MB);
  u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, u32MinutesUsed_temp0.Bytes.UB);
  u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, u32MinutesUsed_temp0.Bytes.HB);
  u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, u32MinutesUsed_temp0.Bytes.LB);

  u8Crc1 = u8DataBuf[4];
    
  if (u8Crc == u8Crc1)
  {
    u8Dummy1 = 1u;
  } 
  else
  {
    u8Dummy1 = 0;
  }

  TIMECATL_SCFG_vReadMem_1(u8DataBuf);
  u32MinutesUsed_temp1.Bytes.MB = u8DataBuf[3];
  u32MinutesUsed_temp1.Bytes.UB = u8DataBuf[2];
  u32MinutesUsed_temp1.Bytes.HB = u8DataBuf[1];
  u32MinutesUsed_temp1.Bytes.LB = u8DataBuf[0];

  u8Crc = CRC_INIT_02;
  u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, u32MinutesUsed_temp1.Bytes.MB);
  u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, u32MinutesUsed_temp1.Bytes.UB);
  u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, u32MinutesUsed_temp1.Bytes.HB);
  u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, u32MinutesUsed_temp1.Bytes.LB);
  
  u8Crc1 = u8DataBuf[4];

  if (u8Crc == u8Crc1)
  {
    u8Dummy2 = 1u;
  } 
  else
  {
    u8Dummy2 = 0;
  }

  if (1u == u8Dummy1)
  {   
    if (1u == u8Dummy2) 
    { 
      /* u8Crc1 is correct, u8Crc2 is correct */ 
      if (u32MinutesUsed_temp0.u32Val > u32MinutesUsed_temp1.u32Val)
      {
				mg_u32MinutesUsed.u32Val = u32MinutesUsed_temp0.u32Val;
			}
			else
			{
				mg_u32MinutesUsed.u32Val = u32MinutesUsed_temp1.u32Val;
			}
    }
    else 
    { 
      /* u8Crc1 is correct , u8Crc 2 is wrong */             
	    mg_u32MinutesUsed.u32Val = u32MinutesUsed_temp0.u32Val;
    }    
  }
  else /* u8Crc 1 is wrong */
  {
    if (1u == u8Dummy2)/* if u8Crc 2 is correct, use crc2 */
    { 
  	  mg_u32MinutesUsed.u32Val = u32MinutesUsed_temp1.u32Val;  
    }
    else /* both CRC are wrong */
    {
      mg_u32MinutesUsed.u32Val = 0;
    }
  }

  mg_u32MinutesUsedOld.u32Val = mg_u32MinutesUsed.u32Val;
  u32HoursUsed.u32Val = mg_u32MinutesUsed.u32Val / 3600;

  TIMECTRL_RTE_Write_P_vWrHoursUsed(u32HoursUsed.u32Val);
  TIMECTRL_RTE_Write_P_u32PosTotal(mg_u32MinutesUsed.u32Val);
	
	

} /* TIMECTRL_vInit() */

/*******************************************************************************
 * \brief         Read operating minutes and calculate Hours used
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void TIMECTRL_vDeInit(void)
{
}

/*******************************************************************************
 * \brief         Calculate Hours Used and save operating minutes 
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/

void TIMECTRL_vSaveHoursUsed( void )
{
  static uint8 mg_RtcTrSecondUnit = 0;
  uint8 u8Crc = 0;
  DWORD_VAL u32HoursUsed;
	uint32 u32HoursUsedPre;
	uint32 RtcTrSecondUnit;
  static uint8 u8PowerOnRst = TRUE;
  static uint32 u32PosLast = 0;
  uint32 u32TmpData;
	
  uint8 au8EepromWriteBuf[5] = {0,0,0,0,0};
	RtcTrSecondUnit = TIMECTRL_CFG_RTC_TR_SECOND_UNIT;
  if(mg_RtcTrSecondUnit != RtcTrSecondUnit)
  {
    mg_RtcTrSecondUnit = RtcTrSecondUnit;
    
    if ( FALSE != TIMECTRL_RTE_Read_B_R_V1_ON())
    { 
      if(FALSE != u8PowerOnRst)
      {
        u32PosLast   = 0u;
        u8PowerOnRst = FALSE;
      }
      else
      {
        u32PosLast++;
      }
      mg_u32MinutesUsed.u32Val++;
      TIMECTRL_RTE_Read_R_PosTotal(&u32TmpData);
      TIMECTRL_RTE_Write_P_vDataCopy(u32TmpData);
      TIMECTRL_RTE_Write_B_P_PSO_TOTAL_UPDTING(TRUE);
      TIMECTRL_RTE_Write_P_u32PosTotal(mg_u32MinutesUsed.u32Val);
      TIMECTRL_RTE_Write_B_P_PSO_TOTAL_UPDTING(FALSE);
      
      TIMECTRL_RTE_Read_R_PosLast(&u32TmpData);
      TIMECTRL_RTE_Write_P_vDataCopy(u32TmpData);
      TIMECTRL_RTE_Write_B_P_PSO_LAST_UPDTING(TRUE);
      TIMECTRL_RTE_Write_P_u32PosLast(u32PosLast);
      TIMECTRL_RTE_Write_B_P_PSO_LAST_UPDTING(FALSE);

    }
    else
    {
      u8PowerOnRst = TRUE;
    }
      
    if (mg_u16MinIn1SCnt != 0)
    {
      mg_u16MinIn1SCnt--;
    }
    else
    {
      mg_u16MinIn1SCnt = MG_MINUTE_IN_1S;
      
      if (mg_u8HalfHourInMinCnt != 0)
      {
        mg_u8HalfHourInMinCnt--;
      }
    }
  }

  if ((FALSE != TIMECTRL_RTE_Read_B_R_INPUT_OFF()) || (0 == mg_u8HalfHourInMinCnt))
  {
    TIMECTRL_RTE_Write_B_P_INPUT_OFF(FALSE);
    if (0U == mg_u8HalfHourInMinCnt)
    {
      /* every 30 minutes to update HOURS_USED */
      mg_u8HalfHourInMinCnt = MG_HALF_HOUR_IN_MIN;
    }
    
    u32HoursUsed.u32Val = mg_u32MinutesUsed.u32Val / 3600u;
		TIMECTRL_RTE_Read_R_PmbusHoursUsed(&u32HoursUsedPre);
    TIMECTRL_RTE_Write_P_vDataCopy(u32HoursUsedPre);
    TIMECTRL_RTE_Write_P_vWrBitHoursUpd(TRUE );
    TIMECTRL_RTE_Write_P_vWrHoursUsed(u32HoursUsed.u32Val);
    TIMECTRL_RTE_Write_P_vWrBitHoursUpd(FALSE);
    
    if (mg_u32MinutesUsedOld.u32Val != mg_u32MinutesUsed.u32Val) 
    {
      mg_u32MinutesUsedOld.u32Val = mg_u32MinutesUsed.u32Val;
      u8Crc = CRC_INIT_02;
      u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, mg_u32MinutesUsed.Bytes.MB);
      u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, mg_u32MinutesUsed.Bytes.UB);
      u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, mg_u32MinutesUsed.Bytes.HB);
      u8Crc = TIMECATL_SCFG_u8GetCrc8(u8Crc, mg_u32MinutesUsed.Bytes.LB);
      au8EepromWriteBuf[0] = mg_u32MinutesUsed.Bytes.LB;
      au8EepromWriteBuf[1] = mg_u32MinutesUsed.Bytes.HB;
      au8EepromWriteBuf[2] = mg_u32MinutesUsed.Bytes.UB;
      au8EepromWriteBuf[3] = mg_u32MinutesUsed.Bytes.MB;
      au8EepromWriteBuf[4] = u8Crc;

      if (0 == mg_u8SaveMinutePos)
      {
				if(TIMECTRL_SCFG_u8IsEepromStandbyState() == TRUE)
				{
          TIMECATL_SCFG_vWriteMem(EEP_USED_MINUTES_LB, au8EepromWriteBuf, 5u);
				}
        mg_u8SaveMinutePos = 0x01u; 
      }
      else
      {
				if(TIMECTRL_SCFG_u8IsEepromStandbyState() == TRUE)
				{
          TIMECATL_SCFG_vWriteMem(EEP_USED_MINUTES_1_LB, au8EepromWriteBuf, 5u);
				}
        mg_u8SaveMinutePos = 0x00;
      }
    }
  } 
} /* TIME_vHoursUsed() */

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/*
 * End of file
 */
