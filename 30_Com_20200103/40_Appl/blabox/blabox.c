/** ****************************************************************************
 * \file    BLABOX.h
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
 
/*******************************************************************************
 * Included header
 ******************************************************************************/

/* Module header */
#define FANCTRL_EXPORT_H
  #include "blabox_api.h"
  #include "blabox_cfg.h"
	#include "blabox_scb.h"
  #include "blabox_scfg.h"
  #include "blabox_conf.h"
	#include "blabox_rte.h"
/*******************************************************************************
 * Global constants and macros
 *****************************************************************************/

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/
 typedef enum
{
	BLABOX_INIT,
	BLABOX_MODE_OFF,
	BLABOX_MODE_ON,
} MG_BLABOX_E_STATE;

 typedef enum
{
	BLABOX_VinUnder_shutdown,
	BLABOX_Thermal_shutdown,
	BLABOX_OverCurr_shutdown,
	BLABOX_GenerFail_shutdown,
	BLABOX_FanFail_shutdown,
	BLABOX_OverVolt_shutodwn,
	BLABOX_InputFail_warning,
	BLABOX_Thermal_warning,
	BLABOX_OverCurr_warning,
	BLABOX_FanFail_warning,
  BLABOX_OverVsb_shutdown,
  BLABOX_OverIsb_shutdown,
  BLABOX_UnderVsb_shutdown,
  BLABOX_OverBulk_shutdown,
  BLABOX_VinOver_shutdown
} MG_BLABOX_E_EventCount;

typedef enum
{
	BLABOX_LOW,
	BLABOX_HIGH
} MG_BLABOX_E_SIDEBYTE;
/*******************************************************************************
 * Local data
 ******************************************************************************/
static boolean mg_OverVoutFaultWriteEnable = TRUE;
static boolean mg_UnderVoutFaultWriteEnable = TRUE;
static boolean mg_IoutFaultWriteEnable = TRUE;
static boolean mg_IoutWarningWriteEnable = TRUE;
static boolean mg_OverInputFaultWriteEnable = TRUE;
static boolean mg_UnderInputFaultWriteEnable = TRUE;
static boolean mg_InputLossWriteEnable = TRUE;
static boolean mg_FanFaultWriteEnable = TRUE;
static boolean mg_TempFaultWriteEnable = TRUE;
static boolean mg_TempWarningWriteEnable = TRUE;
static boolean mg_GeneralFaultWriteEnable = TRUE;
static boolean mg_OverVsbFaultWriteEnable = TRUE;
static boolean mg_OverIsbFaultWriteEnable = TRUE;
static boolean mg_UnderVsbFaultWriteEnable = TRUE;
static boolean mg_OverBulkFaultWriteEnable = TRUE;

/* Event Blackbox */
static uint8 mg_au8BuffWriteToEmem[BLABOX_MFR_MAX_EVENT_HEADER];
/* Config Enable */
static uint8 mg_bEnableBlackbox = TRUE;
/* Real Time Base IPMI 2.0 (UNIX-based)*/
static uint32 mg_u32RealTimeBaseIPMI = 0;

static uint8 mg_u8Tmp;
static WORD_VAL mg_wTmp;

/*******************************************************************************
 * Global data
 ******************************************************************************/
boolean BLABOX_bWriteEEPROMProcessing = FALSE;
/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
static void mg_vSetCountEventFaultAndWarning(MG_BLABOX_E_EventCount eTmp,MG_BLABOX_E_SIDEBYTE eSideByte);
static uint8 mg_u8IsMaxCountEventFaultAndWarning(MG_BLABOX_E_EventCount eTmp,MG_BLABOX_E_SIDEBYTE eSideByte);
static void mg_vPushEventFaultBlackBox(void);
static void mg_vMfrGetPSONCntBlackBox(uint8* pu8Buffer);
static void mg_vMfrGetACCntBlackBox(uint8* pu8Buffer);
static void mg_vMfrGetTimePSONBlackBox(uint8* pu8Buffer);
static void mg_vMfrSetPSONCntBlackBox(void);
static void mg_vMfrSetACCntBlackBox(void);


boolean BLABOX_vReadMFR_BLABOX_EVENT(uint8* pu8Buffer,uint8 Event);
static boolean mg_vReadMfrBlaboxHeader(uint8* pu8Buffer);
/** ****************************************************************************
 * \brief  BLABOX_vInit
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Init set value & Read in EEPROM
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vInit(void)
{

	/* Enable Flag Fault write */
	mg_OverVoutFaultWriteEnable = TRUE;
	mg_UnderVoutFaultWriteEnable = TRUE;
	mg_IoutFaultWriteEnable = TRUE;
	mg_IoutWarningWriteEnable = TRUE;
	mg_OverInputFaultWriteEnable = TRUE;
  mg_UnderInputFaultWriteEnable = TRUE;
	mg_InputLossWriteEnable = TRUE;
	mg_FanFaultWriteEnable = TRUE;
	mg_TempFaultWriteEnable = TRUE;
	mg_TempWarningWriteEnable = TRUE;
	mg_GeneralFaultWriteEnable = TRUE;
  mg_OverVsbFaultWriteEnable = TRUE;
  mg_OverIsbFaultWriteEnable = TRUE;
  mg_UnderVsbFaultWriteEnable = TRUE;
  mg_OverBulkFaultWriteEnable = TRUE;
	
	BLABOX_bWriteEEPROMProcessing = TRUE;
	/*============== Read from EEPROM ============================*/	
	BLABOX_SCFG_vEEPROM2Emem(BLABOX_SCFG_u16Getlenght(0),0);
	
	BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_CONFIG,&mg_bEnableBlackbox,1);
}
/** ****************************************************************************
 * \brief  BLABOX_vProcessBlackbox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Main process black box (Loop time 10 ms)
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vProcessBlackbox(void)
{
	static uint16 u16CntStartEnable = 0;
	static uint16 u16CntWriteEEPROMProcess = 0;
	
	/* Delay Init function 5 second */
	if(++u16CntStartEnable < (BLABOX_TIMESTART * 100u)) {				
		return;
	}else{ 
		u16CntStartEnable = (BLABOX_TIMESTART * 100u);
	}
	
	/* Check Enable function */
	if( (1 == (mg_bEnableBlackbox & 0x01)) && (FALSE == BLABOX_Rte_Read_B_R_AUX_MODE())) {
		
		/* Over Volt fault */
		if(  FALSE != BLABOX_Rte_Read_B_R_VOUT_OV_FAULT() && TRUE == mg_OverVoutFaultWriteEnable)
		{
			/* Clear Flag Event */
			mg_OverVoutFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
											
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_OverVolt_shutodwn,BLABOX_HIGH)) {
				
				mg_vPushEventFaultBlackBox();				
				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_OverVolt_shutodwn,BLABOX_HIGH);
							
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}
									
		}
		/* Under Volt Fault (General Fault) */
		else if(  FALSE != BLABOX_Rte_Read_B_R_VOUT_UV_FAULT() && TRUE == mg_UnderVoutFaultWriteEnable)
		{
			/* Clear Flag Event */
			mg_UnderVoutFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
							
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_GenerFail_shutdown,BLABOX_HIGH)) {			
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_GenerFail_shutdown,BLABOX_HIGH);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}
									
		}
		/* Over Current Fault */
		else if(  FALSE != BLABOX_Rte_Read_B_R_IOUT_OC_FAULT() && TRUE == mg_IoutFaultWriteEnable)
		{
			/* Clear Flag Event */
			mg_IoutFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_OverCurr_shutdown,BLABOX_LOW)) {					
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_OverCurr_shutdown,BLABOX_LOW);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}						
		}
		/* Over Current Warning */
		else if(  FALSE != BLABOX_Rte_Read_B_R_IOUT_OC_WARN() && TRUE == mg_IoutWarningWriteEnable && FALSE == BLABOX_Rte_Read_B_R_IOUT_OC_FAULT())
		{  
			/* Clear Flag Event */
			mg_IoutWarningWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_OverCurr_warning,BLABOX_LOW)) {					
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_OverCurr_warning,BLABOX_LOW);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}
		}
		/* Under Input Fault */
		else if(  FALSE != BLABOX_Rte_Read_B_R_VIN_UV_FAULT() && TRUE == mg_UnderInputFaultWriteEnable)
		{  
						
			/* Clear Flag Event */
			mg_UnderInputFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_VinUnder_shutdown,BLABOX_LOW)) {					
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_VinUnder_shutdown,BLABOX_LOW);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);		
			}
		}
		/* Over Input Fault  */
		else if(  FALSE != BLABOX_Rte_Read_B_R_VIN_OV_FAULT() && TRUE == mg_OverInputFaultWriteEnable)
		{  
			/* Clear Flag Event */
			mg_OverInputFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_VinOver_shutdown,BLABOX_LOW)) {					
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_VinOver_shutdown,BLABOX_LOW);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);		
			}
		}
		/* Fan Fail */
		else if(  FALSE != BLABOX_Rte_Read_B_R_FAN_FAULT() && TRUE == mg_FanFaultWriteEnable)
		{  
			/* Clear Flag Event */
			mg_FanFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_FanFail_shutdown,BLABOX_LOW)) {					
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_FanFail_shutdown,BLABOX_LOW);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}
		}
		/* Temp Fault */
 		else if(  FALSE != BLABOX_Rte_Read_B_R_OT_FAULT() && TRUE == mg_TempFaultWriteEnable)
		{  
			
			/* Clear Flag Event */
			mg_TempFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_Thermal_shutdown,BLABOX_HIGH)) {					
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_Thermal_shutdown,BLABOX_HIGH);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}
		}
		/* Temp Warning */
		else if(  FALSE != BLABOX_Rte_Read_B_R_OT_WARN() && TRUE == mg_TempWarningWriteEnable && FALSE == BLABOX_Rte_Read_B_R_OT_FAULT())
		{  
			/* Clear Flag Event */
			mg_TempWarningWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_Thermal_warning,BLABOX_HIGH)) {					
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_Thermal_warning,BLABOX_HIGH);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}
		}
		/* General Fault */
		else if(  FALSE != BLABOX_Rte_Read_B_R_GENERAL_FAULT() && TRUE == mg_GeneralFaultWriteEnable && FALSE == BLABOX_Rte_Read_B_R_LOSS_INPUT())
		{  
			/* Clear Flag Event */
			mg_GeneralFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_GenerFail_shutdown,BLABOX_HIGH)) {					
				mg_vPushEventFaultBlackBox();

				/* Event Couter */		
				mg_vSetCountEventFaultAndWarning(BLABOX_GenerFail_shutdown,BLABOX_HIGH);
						
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}
		}
		/* Over Vsb Volt fault */
		else if(  FALSE != BLABOX_Rte_Read_B_R_VSB_OV_FAULT() && TRUE == mg_OverVsbFaultWriteEnable)
		{
			/* Clear Flag Event */
			mg_OverVsbFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
											
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_OverVsb_shutdown,BLABOX_LOW)) {
				
				mg_vPushEventFaultBlackBox();				
				/* Event Couter */		           
				mg_vSetCountEventFaultAndWarning(BLABOX_OverVsb_shutdown,BLABOX_LOW);
							
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}	
    }
		/* Over Vsb current fault */
		else if(  FALSE != BLABOX_Rte_Read_B_R_ISB_OC_FAULT() && TRUE == mg_OverIsbFaultWriteEnable)
		{
			/* Clear Flag Event */
			mg_OverIsbFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
											
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_OverIsb_shutdown,BLABOX_HIGH)) {
				
				mg_vPushEventFaultBlackBox();				
				/* Event Couter */		           
				mg_vSetCountEventFaultAndWarning(BLABOX_OverIsb_shutdown,BLABOX_HIGH);
							
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}	      
		}
		/* under Vsb volt fault */
		else if(  FALSE != BLABOX_Rte_Read_B_R_VSB_UV_FAULT() && TRUE == mg_UnderVsbFaultWriteEnable)
		{
			/* Clear Flag Event */
			mg_UnderVsbFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
											
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_UnderVsb_shutdown,BLABOX_LOW)) {
				
				mg_vPushEventFaultBlackBox();				
				/* Event Couter */		           
				mg_vSetCountEventFaultAndWarning(BLABOX_UnderVsb_shutdown,BLABOX_LOW);
							
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}	      
		}
		/* Over Bulk volt fault */
		else if(  FALSE != BLABOX_Rte_Read_B_R_BULK_OV_FAULT() && TRUE == mg_OverBulkFaultWriteEnable)
		{
			/* Clear Flag Event */
			mg_OverBulkFaultWriteEnable = FALSE;
			
			/* Optimize Event Buff write */			
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,BLABOX_SCFG_u32GetLastRecordId());
											
			/* Check Max Event Count not full */
			if(FALSE == mg_u8IsMaxCountEventFaultAndWarning(BLABOX_OverBulk_shutdown,BLABOX_HIGH)) {
				
				mg_vPushEventFaultBlackBox();				
				/* Event Couter */		           
				mg_vSetCountEventFaultAndWarning(BLABOX_UnderVsb_shutdown,BLABOX_HIGH);
							
				/* Write Event to s_dam */		
				BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
			}	      
		}
	}/* End Enable BlackBox */
	
	/* SAVE TO EEPROM */
	/* Loss Input */
	if(FALSE != BLABOX_Rte_Read_B_R_LOSS_INPUT() && TRUE == mg_InputLossWriteEnable)
	{
		/* set protect cml error */
		if(FALSE == BLABOX_bWriteEEPROMProcessing) {
			BLABOX_bWriteEEPROMProcessing = TRUE;
			u16CntWriteEEPROMProcess = 0;
		}
		
		/* update another process for get alert for ready write EEPROm */
		if(u16CntWriteEEPROMProcess >= 10)
		{
			mg_InputLossWriteEnable = FALSE;	
			BLABOX_SCFG_vEmem2EEPROM(BLABOX_SCFG_u16Getlenght(0),0);
		} 
	}
	
	/* Clear EEPROm Read/Write process */
	if(++u16CntWriteEEPROMProcess > 500) /* cnt * 10 ms count */
	{
		BLABOX_bWriteEEPROMProcessing = FALSE;
		u16CntWriteEEPROMProcess = 0;
	}
	
}
/** ****************************************************************************
 * \brief  mg_vSetCountEventFaultAndWarning
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  process separate detect Event
 * \return  -
 *
 **************************************************************************** */
static void mg_vSetCountEventFaultAndWarning(MG_BLABOX_E_EventCount eTmp,MG_BLABOX_E_SIDEBYTE eSideByte)
{
	uint8 u8Addr = 0;	
	
	if(eTmp == BLABOX_VinUnder_shutdown || eTmp == BLABOX_Thermal_shutdown) u8Addr = 33;					
	else if(eTmp == BLABOX_OverCurr_shutdown || eTmp == BLABOX_GenerFail_shutdown) u8Addr = 34;					
	else if(eTmp == BLABOX_OverVolt_shutodwn || eTmp == BLABOX_FanFail_shutdown) u8Addr = 35;					
	else if(eTmp == BLABOX_InputFail_warning || eTmp == BLABOX_Thermal_warning) u8Addr = 36;					
	else if(eTmp == BLABOX_OverCurr_warning || eTmp == BLABOX_FanFail_warning) u8Addr = 37;		
		
	
	if(BLABOX_LOW == eSideByte) 
	{
		if((mg_au8BuffWriteToEmem[u8Addr] & 0x0F) < 0x0F) {
			mg_au8BuffWriteToEmem[u8Addr] = ((mg_au8BuffWriteToEmem[u8Addr] & 0x0F) + 1)  + (mg_au8BuffWriteToEmem[u8Addr] & 0xF0 );
		}
	}
	else if(BLABOX_HIGH == eSideByte) 
	{
		if((mg_au8BuffWriteToEmem[u8Addr] & 0xF0) < 0xF0) {
			mg_au8BuffWriteToEmem[u8Addr] = ((mg_au8BuffWriteToEmem[u8Addr] & 0xF0) + (1 << 4) ) + (mg_au8BuffWriteToEmem[u8Addr] & 0x0F );		
		}
	}
}
/** ****************************************************************************
 * \brief  mg_vSetCountEventFaultAndWarning
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  process separate detect Event
 * \return  -
 *
 **************************************************************************** */
static uint8 mg_u8IsMaxCountEventFaultAndWarning(MG_BLABOX_E_EventCount eTmp,MG_BLABOX_E_SIDEBYTE eSideByte)
{
	uint8 u8Addr = 0;	
	uint8 u8Return = 0;
	if(eTmp == BLABOX_VinUnder_shutdown || eTmp == BLABOX_Thermal_shutdown) u8Addr = 33;					
	else if(eTmp == BLABOX_OverCurr_shutdown || eTmp == BLABOX_GenerFail_shutdown) u8Addr = 34;					
	else if(eTmp == BLABOX_OverVolt_shutodwn || eTmp == BLABOX_FanFail_shutdown) u8Addr = 35;					
	else if(eTmp == BLABOX_InputFail_warning || eTmp == BLABOX_Thermal_warning) u8Addr = 36;					
	else if(eTmp == BLABOX_OverCurr_warning || eTmp == BLABOX_FanFail_warning) u8Addr = 37;		
		
	
	if(BLABOX_LOW == eSideByte) 
	{
		if((mg_au8BuffWriteToEmem[u8Addr] & 0x0F) < 0x0F) {
			u8Return = FALSE;
		}else{
			u8Return = FALSE;
		}
	}
	else if(BLABOX_HIGH == eSideByte) 
	{
		if((mg_au8BuffWriteToEmem[u8Addr] & 0xF0) < 0xF0) {
			u8Return = FALSE;
		}else u8Return = FALSE;
	}
	return u8Return;
}

/** ****************************************************************************
 * \brief  BLABOX_vReadMFR_BLABOX
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Command 0xDC (hex) in PMBus for Read BlackBox 
 * \return  -
 *
 **************************************************************************** */
boolean BLABOX_vMFR_BLABOX(uint8* pu8Buffer)
{
	uint8 u8Cnt = 0;
	uint8 u8CntEvent = 0;
	uint8 u8CntAllEvent = 0;
	uint8 u8IndexAllEvent = 0;
	uint8 u8LastRecode = 0;
	uint8 u8NumOfRecodes = 0;
	/* Get Header (Read All Header from S_dam)*/	
	u8IndexAllEvent = 0;  
	BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_HEADER,mg_au8BuffWriteToEmem,1);
	/* send to PMbus */
	for( u8CntEvent = 0; u8CntEvent < BLABOX_MFR_BLACKBOX_HEADER ; u8CntEvent++) 
	{		
		pu8Buffer[u8IndexAllEvent++] = mg_au8BuffWriteToEmem[u8CntEvent];
	}
	
	/* Clear Header mg_au8BuffWriteToEmem */
	for(u8Cnt = 0;u8Cnt < BLABOX_MFR_BLACKBOX_HEADER; u8Cnt++) {
		mg_au8BuffWriteToEmem[u8Cnt] = 0;
	}
	
	u8NumOfRecodes = BLABOX_SCFG_u32GetNumberOfRecords();	
	u8LastRecode = BLABOX_SCFG_u32GetLastRecordId();					
	/* Read All Event from s_dam */	
		for( u8CntEvent = u8LastRecode; u8CntEvent > 0 ; u8CntEvent--) 
		{
			/* Get each Event */
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,u8CntEvent);
			
			/* send to PMbus */
			for(u8CntAllEvent = 0;u8CntAllEvent < BLABOX_MFR_BLACKBOX_EVENT_LENGHT; u8CntAllEvent++) {
				pu8Buffer[u8IndexAllEvent++] = mg_au8BuffWriteToEmem[u8CntAllEvent];
			}
			
			/* Clear mg_au8BuffWriteToEmem */
			for(u8Cnt = 0;u8Cnt < BLABOX_MFR_BLACKBOX_EVENT_LENGHT; u8Cnt++) {
				mg_au8BuffWriteToEmem[u8Cnt] = 0;
			}
		}
		for( u8CntEvent = u8NumOfRecodes; u8CntEvent > u8LastRecode ; u8CntEvent--) 
		{
			/* Get each Event */
			BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,u8CntEvent);
			
			/* send to PMbus */
			for(u8CntAllEvent = 0;u8CntAllEvent < BLABOX_MFR_BLACKBOX_EVENT_LENGHT; u8CntAllEvent++) {
				pu8Buffer[u8IndexAllEvent++] = mg_au8BuffWriteToEmem[u8CntAllEvent];
			}
			
			/* Clear mg_au8BuffWriteToEmem */
			for(u8Cnt = 0;u8Cnt < BLABOX_MFR_BLACKBOX_EVENT_LENGHT; u8Cnt++) {
				mg_au8BuffWriteToEmem[u8Cnt] = 0;
			}
		}
	return TRUE;
}
/** ****************************************************************************
 * \brief  BLABOX_vWR_SystemBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Command 0xDE (hex) in PMBus for Write/Read Serial System 
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vMFR_SystemBlackBox(uint8* pu8Buffer,uint8 IsWrite)
{
	uint8 u8Cnt = 0;
	/* Read packet */
	if(FALSE == IsWrite) {
		/* Optimize Header Buff */
		mg_vReadMfrBlaboxHeader(mg_au8BuffWriteToEmem);		
			
		for(u8Cnt = 0; u8Cnt < BLABOX_LENGTH_SERIAL_SYSTEM; u8Cnt++) {
			pu8Buffer[u8Cnt] = mg_au8BuffWriteToEmem[u8Cnt];
		}		
	}else { /* Write packet */
		
		/* Optimize Header Buff */
		mg_vReadMfrBlaboxHeader(mg_au8BuffWriteToEmem);					
		for(u8Cnt = 0; u8Cnt < BLABOX_LENGTH_SERIAL_SYSTEM; u8Cnt++) {
			mg_au8BuffWriteToEmem[u8Cnt] = pu8Buffer[u8Cnt];
		}				
		/* Write Header to s_dam */
		BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_HEADER,mg_au8BuffWriteToEmem);
		
		
	}
}
/** ****************************************************************************
 * \brief  BLABOX_vMFR_ClearBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Command 0xE0 (hex) in PMBus for Write Clear 
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vMFR_ClearBlackBox(void)
{
	uint8 u8Cnt = 0;
	uint8 u8CntEvent = 0;
	/* Optimize Header Buff write */
	mg_vReadMfrBlaboxHeader(mg_au8BuffWriteToEmem);		
	/* Clear Header Blackbox */
	for(u8Cnt = 0; u8Cnt < BLABOX_MFR_BLACKBOX_HEADER; u8Cnt++) {
		mg_au8BuffWriteToEmem[u8Cnt] = 0;
	}			
	/* Write Header to s_dam */
	BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_HEADER,mg_au8BuffWriteToEmem);
	
  for(u8CntEvent = 1; u8CntEvent <= BLABOX_MFR_BLACKBOX_EVENT_MAX; u8CntEvent++ ) {							
		/* Optimize Event Buff write */			
		BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem,u8CntEvent);
		/* Clear Event */
		for(u8Cnt = 0; u8Cnt < BLABOX_MFR_BLACKBOX_EVENT_LENGHT; u8Cnt++) {			
			mg_au8BuffWriteToEmem[u8Cnt] = 0;
		}	
		/* Write Event to s_dam */		
		BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA,mg_au8BuffWriteToEmem);
		
	}
}
/** ****************************************************************************
 * \brief  BLABOX_vMFR_CheckPSONBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Check Present number of PSON power cycles
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vMFR_CheckPSONBlackBox(void)
{
	static MG_BLABOX_E_STATE BLABOX_ePson = BLABOX_INIT;
	
	/* Check Enable function */
	if( (0 == (mg_bEnableBlackbox & 0x01)) || (FALSE != BLABOX_Rte_Read_B_R_AUX_MODE()) ) return;
	
	if(FALSE != BLABOX_Rte_Read_B_R_PSON_FAULT()) {
		BLABOX_ePson = BLABOX_MODE_OFF;
	}
	
	if(BLABOX_ePson == BLABOX_MODE_OFF) {
		
		if(FALSE == BLABOX_Rte_Read_B_R_PSON_FAULT()) {			
			
			mg_vMfrSetPSONCntBlackBox();
			BLABOX_ePson = BLABOX_INIT;		
		}
	}
}
/** ****************************************************************************
 * \brief  mg_vPushEventFaultBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  coming soon 
 * \return  -
 *
 **************************************************************************** */
static void mg_vPushEventFaultBlackBox(void)
{
  mg_vMfrGetTimePSONBlackBox(&mg_au8BuffWriteToEmem[0]);

  /* Real Time */
  mg_au8BuffWriteToEmem[3] = (uint8)(mg_u32RealTimeBaseIPMI & 0xFF);
  mg_au8BuffWriteToEmem[4] = (uint8)((mg_u32RealTimeBaseIPMI >> 8) & 0xFF);
  mg_au8BuffWriteToEmem[5] = (uint8)((mg_u32RealTimeBaseIPMI >> 16) & 0xFF);
  mg_au8BuffWriteToEmem[6] = (uint8)((mg_u32RealTimeBaseIPMI >> 24) & 0xFF);

  mg_vMfrGetACCntBlackBox(&mg_au8BuffWriteToEmem[7]);
  mg_vMfrGetPSONCntBlackBox(&mg_au8BuffWriteToEmem[9]);

  BLABOX_cfg_vPmbusSaveBlackBoxData2Buff();

  /* Get Read Status & Raw value */
  BLABOX_Rte_Read_R_StatusWord(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[11] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[12] = mg_wTmp.Bytes.HB;
  BLABOX_Rte_Read_R_StatusIout(&mg_u8Tmp);
  mg_au8BuffWriteToEmem[13] = mg_u8Tmp;
  BLABOX_Rte_Read_R_StatusInput(&mg_u8Tmp);
  mg_au8BuffWriteToEmem[14] = mg_u8Tmp;
  BLABOX_Rte_Read_R_StatusTemp(&mg_u8Tmp);
  mg_au8BuffWriteToEmem[15] = mg_u8Tmp;
  BLABOX_Rte_Read_R_StatusFan12(&mg_u8Tmp);
  mg_au8BuffWriteToEmem[16] = mg_u8Tmp;
  BLABOX_Rte_Read_R_ReadVin(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[17] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[18] = mg_wTmp.Bytes.HB;
  BLABOX_Rte_Read_R_ReadIin(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[19] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[20] = mg_wTmp.Bytes.HB;
  BLABOX_Rte_Read_R_ReadIout(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[21] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[22] = mg_wTmp.Bytes.HB;
  BLABOX_Rte_Read_R_ReadTemp1(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[23] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[24] = mg_wTmp.Bytes.HB;
  BLABOX_Rte_Read_R_ReadTemp2(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[25] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[26] = mg_wTmp.Bytes.HB;
  BLABOX_Rte_Read_R_ReadFan1(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[27] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[28] = mg_wTmp.Bytes.HB;	
  BLABOX_Rte_Read_R_ReadPin(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[29] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[30] = mg_wTmp.Bytes.HB;	
  BLABOX_Rte_Read_R_ReadVout(&mg_wTmp.u16Val);
  mg_au8BuffWriteToEmem[31] = mg_wTmp.Bytes.LB;
  mg_au8BuffWriteToEmem[32] = mg_wTmp.Bytes.HB;	
}

/** ****************************************************************************
 * \brief  mg_vMfrSetPSONCntBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Set Present number of PSON power cycles
 * \return  -
 *
 **************************************************************************** */
static void mg_vMfrSetPSONCntBlackBox()
{
	uint16 u8TmpPSON = 0;
	/* Optimize Header Buff */
	mg_vReadMfrBlaboxHeader(mg_au8BuffWriteToEmem);					
	u8TmpPSON = ((mg_au8BuffWriteToEmem[46 + 1] << 8) + mg_au8BuffWriteToEmem[45 + 1]);
	
	/* Check Size Over flow */
	if(u8TmpPSON < 0xFFFF) {
		/* Only AC power is present */
		if(0 == BLABOX_Rte_Read_B_R_LOSS_INPUT()) {
			/* Up counter */
			u8TmpPSON++;
		}
		
		/* Set PSON */
		mg_au8BuffWriteToEmem[45 + 1] = (u8TmpPSON & 0xff);
		mg_au8BuffWriteToEmem[46 + 1] = ( (u8TmpPSON >> 8) & 0xff);
		
		/* Write Header to s_dam */
		BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_HEADER,mg_au8BuffWriteToEmem);	
	}
}
/** ****************************************************************************
 * \brief  mg_vMfrGetPSONCntBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Get Present number of PSON power cycles
 * \return  -
 *
 **************************************************************************** */
static void mg_vMfrGetPSONCntBlackBox(uint8* pu8Buffer)
{
	uint8 APP_BLACKBOX_au8Tmp[BLABOX_MFR_MAX_EVENT_HEADER];
	/* Optimize Header Buff */
	mg_vReadMfrBlaboxHeader(APP_BLACKBOX_au8Tmp);		
	
	pu8Buffer[0] = APP_BLACKBOX_au8Tmp[45 + 1]; 
	pu8Buffer[1] = APP_BLACKBOX_au8Tmp[46 + 1]; 	
}

/** ****************************************************************************
 * \brief  BLABOX_vMFR_CheckACBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Check Present number of AC power cycles
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vMFR_CheckACBlackBox(void)
{	 
	static MG_BLABOX_E_STATE BLABOX_eACpower = BLABOX_INIT;
	
	/* Check Enable function */
	if( (0 == (mg_bEnableBlackbox & 0x01)) || (FALSE != BLABOX_Rte_Read_B_R_AUX_MODE()) ) return;
	
	if(FALSE != BLABOX_Rte_Read_B_R_AC_POWER_FAULT()) 
	{
		BLABOX_eACpower = BLABOX_MODE_OFF;
	}
	
	if(BLABOX_eACpower == BLABOX_MODE_OFF) 
	{
		if(FALSE == BLABOX_Rte_Read_B_R_AC_POWER_FAULT()) 
		{			
			mg_vMfrSetACCntBlackBox();
			BLABOX_eACpower = BLABOX_INIT;		
		}
	}
}
/** ****************************************************************************
 * \brief  mg_vMfrSetACCntBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Set Present number of AC power cycles
 * \return  -
 *
 **************************************************************************** */
static void mg_vMfrSetACCntBlackBox()
{
	uint16 u8TmpAC = 0;
	/* Optimize Header Buff */
	mg_vReadMfrBlaboxHeader(mg_au8BuffWriteToEmem);					
	u8TmpAC = ((mg_au8BuffWriteToEmem[44 + 1] << 8) + mg_au8BuffWriteToEmem[43 + 1]);
	
	/* Check Size Over flow */
	if(u8TmpAC < 0xFFFF)  {
	
		/* Only PSON is present */
		if(FALSE == BLABOX_Rte_Read_B_R_PSON_FAULT()) {		
			/* Up counter */			
			u8TmpAC++;
		}
		
		/* Set PSON */
		mg_au8BuffWriteToEmem[43 + 1] = (u8TmpAC & 0xff);
		mg_au8BuffWriteToEmem[44 + 1] = ( (u8TmpAC >> 8) & 0xff);
		
		/* Write Header to s_dam */
		BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_HEADER,mg_au8BuffWriteToEmem);	
		
	}
}
/** ****************************************************************************
 * \brief  mg_vMfrGetACCntBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Get Present number of AC power cycles
 * \return  -
 *
 **************************************************************************** */
static void mg_vMfrGetACCntBlackBox(uint8* pu8Buffer)
{
	uint8 APP_BLACKBOX_au8Tmp[BLABOX_MFR_MAX_EVENT_HEADER];
	/* Optimize Header Buff */
	mg_vReadMfrBlaboxHeader(APP_BLACKBOX_au8Tmp);		
	
	pu8Buffer[0] = APP_BLACKBOX_au8Tmp[43 + 1]; 
	pu8Buffer[1] = APP_BLACKBOX_au8Tmp[44 + 1]; 	
}

/** ****************************************************************************
 * \brief  BLABOX_vMFR_TimePSONBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Count Total time of PSON (Loop every 100 ms)
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vMFR_TimePSONBlackBox(void)
{
	static uint16 u16Cnt100msecode = 0;
	uint32 u32TmpCntMinute = 0;
	
	/* Check Enable function */
	if( (0 == (mg_bEnableBlackbox & 0x01)) || (FALSE != BLABOX_Rte_Read_B_R_AUX_MODE()) ) return;
	
	if(FALSE == BLABOX_Rte_Read_B_R_PSON_FAULT()) {
		/* check Loop 100ms every 1 S */
		if( ++u16Cnt100msecode >= 600) 
		{ 		
			u16Cnt100msecode = 0;
			/* Optimize Header Buff */
			mg_vReadMfrBlaboxHeader(mg_au8BuffWriteToEmem);			
			
			u32TmpCntMinute = (uint32)(mg_au8BuffWriteToEmem[42 + 1] << 16) + (uint32)(mg_au8BuffWriteToEmem[41 + 1] << 8) + (uint32)mg_au8BuffWriteToEmem[40 + 1 ];
			u32TmpCntMinute += 1;
			
			mg_au8BuffWriteToEmem[40 + 1] = (u32TmpCntMinute & 0xff);
			mg_au8BuffWriteToEmem[41 + 1] = ((u32TmpCntMinute << 8) & 0xff);
			mg_au8BuffWriteToEmem[42 + 1] = ((u32TmpCntMinute << 16 ) & 0xff);
			
			/* Write Header to s_dam */
			BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_HEADER,mg_au8BuffWriteToEmem);	
		}
	}
}
/** ****************************************************************************
 * \brief  mg_vMfrGetTimePSONBlackBox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Get Total time of PSON 
 * \return  -
 *
 **************************************************************************** */
static void mg_vMfrGetTimePSONBlackBox(uint8* pu8Buffer)
{	
	uint8 APP_BLACKBOX_au8Tmp[BLABOX_MFR_MAX_EVENT_HEADER];
	/* Optimize Header Buff */
	mg_vReadMfrBlaboxHeader(APP_BLACKBOX_au8Tmp);			
	
	pu8Buffer[0] = APP_BLACKBOX_au8Tmp[40 + 1];
	pu8Buffer[1] = APP_BLACKBOX_au8Tmp[41 + 1];
	pu8Buffer[2] = APP_BLACKBOX_au8Tmp[42 + 1];
}



/** ****************************************************************************
 * \brief  mg_vReadMfrBlaboxHeader
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Get Header from S_dam
 * \return  -
 *
 **************************************************************************** */
static boolean mg_vReadMfrBlaboxHeader(uint8* pu8Buffer)
{
	uint8 APP_BLACKBOX_au8Tmp[BLABOX_MFR_MAX_EVENT_HEADER];
	uint8 u8CntEvent = 0;
	uint8 u8IndexAllEvent = 0;
	
	/* Get Header */	
	u8IndexAllEvent = 0;
  
	/* Read All Header emem */	
	BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_HEADER,APP_BLACKBOX_au8Tmp,1);
	for( u8CntEvent = 0; u8CntEvent < BLABOX_MFR_BLACKBOX_HEADER ; u8CntEvent++) 
	{		
		pu8Buffer[u8IndexAllEvent++] = APP_BLACKBOX_au8Tmp[u8CntEvent];
	}
	
	return TRUE;
}
/** ****************************************************************************
 * \brief  BLABOX_vSetEnableBlackbox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Set Enable function 
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vSetEnableBlackbox(uint8 u8Tmp)
{
	if(u8Tmp == 0x00 || u8Tmp == 0x01)
		mg_bEnableBlackbox = u8Tmp;	
	BLABOX_SCFG_Write(BLABOX_CFG_CONFIG_SECTOR_CONFIG,&mg_bEnableBlackbox);
}
/** ****************************************************************************
 * \brief  BLABOX_vGetEnableBlackbox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Get Enable function 
 * \return  -
 *
 **************************************************************************** */
uint8 BLABOX_vGetEnableBlackbox(void)
{	
	BLABOX_SCFG_Read(BLABOX_CFG_CONFIG_SECTOR_CONFIG,&mg_bEnableBlackbox,1);
	return mg_bEnableBlackbox;
}
/** ****************************************************************************
 * \brief  BLABOX_vCountRealTimeClockDataSystemBlackbox
 * \param[in]  -  -
 * \param[out] -  -
* \comment -  Count Real Time Base on IPMI 2.0 (Loop time : 100ms)
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vCountRealTimeClockDataSystemBlackbox(void)
{	
	static uint8 u8CntTime = 0;
	
	if(++u8CntTime >= 10) 
	{
		/* Loop time : 1 second */		
		u8CntTime = 0;
		mg_u32RealTimeBaseIPMI++;
	}
}
/** ****************************************************************************
 * \brief  BLABOX_vSetRealTimeClockDataSystemBlackbox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Set Real Time Base on IPMI 2.0
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vSetRealTimeClockDataSystemBlackbox(uint32 u32ReadTime)
{	
	mg_u32RealTimeBaseIPMI = u32ReadTime;
}
/** ****************************************************************************
 * \brief  BLABOX_vSetRealTimeClockDataSystemBlackbox
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Set Real Time Base on IPMI 2.0
 * \return  -
 *
 **************************************************************************** */
uint32 BLABOX_vGetRealTimeClockDataSystemBlackbox(void)
{	
	return mg_u32RealTimeBaseIPMI;
}

/** ****************************************************************************
 * \brief  BLABOX_vClearFault
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Clear Event after PSU re-turnOn
 * \return  -
 *
 **************************************************************************** */
void BLABOX_vClearFault(void)
{
	/* Enable Flag Fault write */	
	mg_OverVoutFaultWriteEnable = TRUE;
	mg_UnderVoutFaultWriteEnable = TRUE;
	mg_IoutFaultWriteEnable = TRUE;
	mg_IoutWarningWriteEnable = TRUE;
	mg_OverInputFaultWriteEnable = TRUE;
  mg_UnderInputFaultWriteEnable = TRUE;
	mg_InputLossWriteEnable = TRUE;
	mg_FanFaultWriteEnable = TRUE;
	mg_TempFaultWriteEnable = TRUE;
	mg_TempWarningWriteEnable = TRUE;
	mg_GeneralFaultWriteEnable = TRUE;
}


/** ****************************************************************************
 * \brief  BLABOX_vClearWarning
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Clear Event after PSU re-turnOn
 * \return  - Loop 100ms
 *
 **************************************************************************** */
void BLABOX_vClearWarning(void)
{
	static uint8 u8IndexFlagOCmainWarning = 0;
	static uint16 u16CntFlagOCmainWarning = 0;
	
	static uint8 u8IndexFlagFanWarning = 0;
	static uint16 u16CntFlagFanWarning = 0;
	
	static uint8 u8IndexFlagTempWarning = 0;
	static uint16 u16CntFlagTempWarning = 0;

	/* Enable OCmain Flag warning write */			
	if(TRUE == BLABOX_Rte_Read_B_R_IOUT_WARN()) u8IndexFlagOCmainWarning = 1;
	if(FALSE == BLABOX_Rte_Read_B_R_IOUT_WARN() && 1 == u8IndexFlagOCmainWarning) {
		if(u16CntFlagFanWarning < u16CntFlagOCmainWarning) u16CntFlagOCmainWarning++;
		else{
			u8IndexFlagOCmainWarning = 0;
			mg_IoutWarningWriteEnable = TRUE;	
		}
	}
	
	/* Enable Fan Flag warning write */			
	if(TRUE == BLABOX_Rte_Read_B_R_FAN_WARN()) u8IndexFlagFanWarning = 1;
	if(FALSE == BLABOX_Rte_Read_B_R_FAN_WARN() && 1 == u8IndexFlagFanWarning) {
		if(u16CntFlagFanWarning < BLABOX_CFG_TimeFanClearFlagWarning) u16CntFlagFanWarning++;
		else{
			u8IndexFlagFanWarning = 0;
			mg_FanFaultWriteEnable = TRUE;	
		}
	}
	
	
	/* Enable Temp Flag warning write */			
	if(TRUE == BLABOX_Rte_Read_B_R_TEMP_WARN()) u8IndexFlagTempWarning = 1;
	if(FALSE == BLABOX_Rte_Read_B_R_TEMP_WARN() && 1 == u8IndexFlagTempWarning) {
		if(u16CntFlagTempWarning < BLABOX_CFG_TimeTempClearFlagWarning) u16CntFlagTempWarning++;
		else{
			u8IndexFlagFanWarning = 0;
			mg_TempWarningWriteEnable = TRUE;	
		}
	}
	
	
}

