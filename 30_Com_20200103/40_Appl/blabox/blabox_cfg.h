/** ****************************************************************************
 * \file    blabox_cfg.h
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
#ifndef BLABOX_CFG_H
#define BLABOX_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

#include "global.h"
#include "pmbus_scb.h"
/*******************************************************************************
 * Global constants and macros
******************************************************************************/
#define BLABOX_TIMESTART   2u /* x second*/

#define BLABOX_MFR_BLACKBOX_HEADER 					48
#define BLABOX_MFR_BLACKBOX_EVENT_MAX 			5
#define BLABOX_MFR_BLACKBOX_EVENT_LENGHT 		41
#define BLABOX_MFR_MAX_EVENT_HEADER         (BLABOX_MFR_BLACKBOX_EVENT_LENGHT>BLABOX_MFR_BLACKBOX_HEADER)?BLABOX_MFR_BLACKBOX_EVENT_LENGHT:BLABOX_MFR_BLACKBOX_HEADER /* 48 */

 
/* Event Fault BlackBox */
//#define BLABOX_CFG_OverVoltFault  			(PMBCTRL_mg_uStatusVoutVmain.bits.bVoutOvFault && tDcdc.tStatus.Bits.bOvp && PMBCTRL_mg_uStatusWordVmain.bits.bOff)
//#define BLABOX_CFG_UnderVoltFault       (PMBCTRL_mg_uStatusVoutVmain.bits.bVoutUvFault && ((PMBCTRL_mg_uStatusIoutVmain.bits.bIoutOcFault)?0:(tDcdc.tStatus.Bits.bUvp)) && PMBCTRL_mg_uStatusWordVmain.bits.bOff )
//#define BLABOX_CFG_OverCurrentWarning  	(PMBCTRL_mg_uStatusIoutVmain.bits.bIoutOcWarning && tDcdc.tStatus.Bits.bOcw && PMBCTRL_mg_uStatusWordVmain.bits.bIoutPout && PMBCTRL_mg_uStatusWordVmain.bits.bPowerGood)
//#define BLABOX_CFG_OverCurrentFault  		(PMBCTRL_mg_uStatusIoutVmain.bits.bIoutOcFault && tDcdc.tStatus.Bits.bOcp && PMBCTRL_mg_uStatusWordVmain.bits.bOff)
//#define BLABOX_CFG_OverInputVoltFault  	(tAnaVinOvp.Status && PMBCTRL_mg_uStatusInput.bits.bVInOvFault && PMBCTRL_mg_uStatusWordVmain.bits.bOff) 
//#define BLABOX_CFG_UnderInputVoltFault  (tAnaVinUvp.Status && PMBCTRL_mg_uStatusInput.bits.bVInUvFault && PMBCTRL_mg_uStatusWordVmain.bits.bOff) 
//#define BLABOX_CFG_LossInput  		    	(tAnaVinUvp.Status && !BLABOX_CFG_AuxMode)
//#define BLABOX_CFG_FanFault  						(PMBCTRL_mg_uStatusFan12.bits.bFan1Fault && tAnaFanFail.Status)
//#define BLABOX_CFG_OverTempWarning 			( (PMBCTRL_mg_uStatusTemp.bits.bOtWarning) && MG_B_TEMP_WARN() && PMBCTRL_mg_uStatusWordVmain.bits.bTemperature && !MG_B_TEMP_OVER())
//#define BLABOX_CFG_OverTempFault  			( (PMBCTRL_mg_uStatusTemp.bits.bOtFault) && MG_B_TEMP_OVER() && PMBCTRL_mg_uStatusWordVmain.bits.bTemperature && PMBCTRL_mg_uStatusTemp.bits.bOtWarning && PMBCTRL_mg_uStatusTemp.bits.bOtFault)
//#define BLABOX_CFG_GeneralFault    			( ((true == UartprocLLC.FlagCheck_COMFail || true == UartprocPFC.FlagCheck_COMFail) && (true == PMBCTRL_mg_uStatusCML.bits.bOtherCommunicationFault) && (true == PMBCTRL_mg_uStatusWordVmain.bits.bOff)) \
//																				|| (tComControl.bVsbLatch && (PMBCTRL_mg_uStatusVoutVsb.u8data || PMBCTRL_mg_uStatusIoutVsb.u8data) && PMBCTRL_mg_uStatusWordVsb.bits.bOff) )
																				
/* Event Clear  Warning BlackBox */						
//#define BLABOX_CFG_EventOCmainClearFlagWarning    (tDcdc.tStatus.Bits.bOcw) /* Vmain OCW*/
#define BLABOX_CFG_TimeOCmainClearFlagWarning     (10u) /* x * 100ms*/    
//#define BLABOX_CFG_EventFanClearFlagWarning     	(tAnaFanFail.Status)      /* Fan Fault(warning) */
#define BLABOX_CFG_TimeFanClearFlagWarning     		(10u) /* x * 100ms*/
//#define BLABOX_CFG_EventTempClearFlagWarning     	(MG_B_TEMP_WARN())        /* Temp Warning */
#define BLABOX_CFG_TimeTempClearFlagWarning     	(10u) /* x * 100ms*/ 

/* Signal BlackBox */
//#define BLABOX_CFG_PSONFault            (false == tInputPsOn.Status)
//#define BLABOX_CFG_ACPowerFault         (true == tAnaVinUvp.Status)
//#define BLABOX_CFG_AuxMode              (true == tVAuxMode.IsVauxMode)


/* Status & Raw Value Volt,Current,Temp,RMF */
//#define BLABOX_CFG_REAL_STATUS_WORD           (PMBCTRL_mg_uStatusWordVmain.u16Word)
//#define BLABOX_CFG_REAL_STATUS_IOUT           (PMBCTRL_mg_uStatusIoutVmain.u8data)
//#define BLABOX_CFG_REAL_STATUS_INPUT          (PMBCTRL_mg_uStatusInput.u8data)
//#define BLABOX_CFG_REAL_STATUS_TEMP           (PMBCTRL_mg_uStatusTemp.u8data)
//#define BLABOX_CFG_REAL_STATUS_FAN1_2         (PMBCTRL_mg_uStatusFan12.u8data)
//#define BLABOX_CFG_REAL_STATUS_FAN3_4         (0u)
//#define BLABOX_CFG_REAL_READ_VIN           		(RTE_u16PMBVin)
//#define BLABOX_CFG_REAL_READ_IIN           		(RTE_u16PMBIin)
//#define BLABOX_CFG_REAL_READ_IOUT           	(RTE_u16PMBIoutMain)
//#define BLABOX_CFG_REAL_READ_TEMP1           	(RTE_u16PMBTemp1)
//#define BLABOX_CFG_REAL_READ_TEMP2           	(RTE_u16PMBTemp2)
//#define BLABOX_CFG_REAL_READ_TEMP3           	(RTE_u16PMBTemp3)
//#define BLABOX_CFG_REAL_FAN_SPEED_1           (RTE_u16PMBFanSpeed1)
//#define BLABOX_CFG_REAL_FAN_SPEED_2           (0u)
//#define BLABOX_CFG_REAL_FAN_SPEED_3           (0u)
//#define BLABOX_CFG_REAL_FAN_SPEED_4           (0u)
//#define BLABOX_CFG_REAL_READ_PIN           		(RTE_u16PMBPin)
//#define BLABOX_CFG_REAL_READ_VOUT           	(RTE_u16PMBVoutMain)

#define BLABOX_LENGTH_SERIAL_SYSTEM    			40

/* Sector name of s_dam */
#define BLABOX_CFG_CONFIG_SECTOR_EVENT_DATA  	0
#define BLABOX_CFG_CONFIG_SECTOR_HEADER  			1
#define BLABOX_CFG_CONFIG_SECTOR_CONFIG  			2

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
 SINLINE void BLABOX_cfg_vPmbusSaveBlackBoxData2Buff(void)
{
  PMBUS_vSaveBlackBoxData2Buff();
}
#ifdef __cplusplus
  }
#endif
#endif
