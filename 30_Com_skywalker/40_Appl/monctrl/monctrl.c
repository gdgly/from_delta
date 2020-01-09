/******************************************************************************
 * \file    monctrl.c
 * \brief   output monitor control
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2019-11-22 11:01:57 +0800 (Fri, 22 Nov 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 239 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 *******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

/* Module header */
#define MONCTRL_EXPORT_H
  #include "monctrl_api.h"
  #include "monctrl_cfg.h"
  #include "monctrl_conf.h"
  #include "monctrl_scb.h"
  #include "monctrl_scfg.h"
	#include "monctrl_rte.h"
  

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
typedef struct MONCTRL_sVsbMonitor_
{
  uint16 u16MoniDly;
  uint16 u16OcpDly;
  uint16 u16OcwDly;
  uint16 u16ScpDly;
  uint16 u16UvpDly;
  uint16 u16ExtUvpDly;
  uint16 u16UvwDly;
  uint16 u16OvpDly;
  uint16 u16OvwDly;
  uint16 u16OcpOffDly;
  uint16 u16ScpOffDly;
  uint16 u16UvpOffDly;
  uint16 u16PwOkDly;
} MONCTRL_sVsbMonitor;

typedef struct MONCTRL_sV1Monitor_
{
  uint16 u16MoniDly;
  uint16 u16OcpDly;
  uint16 u16OcwDly;
  uint16 u16ScpDly;
  uint16 u16UvpDly;
  uint16 u16UvwDly;
  uint16 u16OvpDly;
  uint16 u16OvwDly;
  uint16 u16OcpOffDly;
  uint16 u16ScpOffDly;
  uint16 u16UvpOffDly;
  uint16 u16PwOkDly;
} MONCTRL_sV1Monitor;

MONCTRL_sVsbMonitor mg_sVsbMonitor;
MONCTRL_sV1Monitor  mg_sV1Monitor;

typedef enum
{
	MG_PSON_INIT,
	MG_PSON_MODE_OFF,
	MG_PSON_MODE_ON,
} MG_E_PSON;

/*******************************************************************************
 * Local functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Function:        MONCTRL_vUpdateStatus
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Update all secondary status informations. This function is
 *                  called every 10ms.
 *
 ******************************************************************************/
void MONCTRL_vUpdateStatus(void)
{

  static uint16 u16NtcFault = 0;
  static uint8 u8RemoteOnDlyCnt = 13u;
	
	uint8  u8PmbusOperation;
	
  /* Ntc short or open fault */
  if ((FALSE == PMBUS_uSysStatu0.Bits.AUX_MODE) && 
		  (FALSE != MONCTRL_RTE_Read_B_R_RELAY_ON()))
  {
    if (FALSE != MONCTRL_RTE_Read_B_R_NTC_FAULT())
    {
      if (u16NtcFault < 50u) 
      {
        u16NtcFault++;
      }
      else
      {
        MONCTRL_RTE_Write_B_P_ANY_NTC_FAULT(TRUE);
      }
    }
    else
    {
      u16NtcFault = 0;
      MONCTRL_RTE_Write_B_P_ANY_NTC_FAULT(FALSE);
    }
  }
  else
  {
    u16NtcFault = 0;
    MONCTRL_RTE_Write_B_P_ANY_NTC_FAULT(FALSE);
  }
	
	/* Check remote on/off */
	MONCTRL_RTE_Read_R_u8PmbusOperation(&u8PmbusOperation);
	if((0 == u8PmbusOperation )                      || 
		 (FALSE == MONCTRL_RTE_Read_B_R_PSON_ACTIVE()) ||
	   (FALSE != MONCTRL_RTE_Read_B_R_PS_KILL_ACTIVE()))
	{
		MONCTRL_RTE_Write_B_P_REMOTE_ON(FALSE);
		if((FALSE != MONCTRL_RTE_Read_B_P_VSB_ON()) &&
			 (FALSE == MONCTRL_RTE_Read_B_R_VIN_UV()) && 
		   (FALSE == MONCTRL_RTE_Read_B_R_VIN_OV()) 
		  )
		{
			MONCTRL_Rte_Write_B_P_STB_MODE(TRUE);
		}
		else
		{
			MONCTRL_Rte_Write_B_P_STB_MODE(FALSE);
		}
    if(FALSE != MONCTRL_RTE_Read_B_R_PS_KILL_ACTIVE())
    {
      u8RemoteOnDlyCnt = 0u; /* delay 0ms */
    }
    else
    {
      u8RemoteOnDlyCnt = 8u;    /* delay 80ms*/
    }
	}
	else
	{
    if(
       (FALSE != MONCTRL_RTE_Read_B_R_NO_VIN()) &&
       (FALSE == MONCTRL_RTE_Read_B_R_V1_ON())  &&
       (FALSE == MONCTRL_RTE_Read_B_R_V1_OVP()) &&
       (FALSE == MONCTRL_RTE_Read_B_R_V1_UVP()) &&
       (FALSE == MONCTRL_RTE_Read_B_R_V1_OCP()) 
      )
    {
		  MONCTRL_Rte_Write_B_P_STB_MODE(TRUE);
    }
    else
    {
		  MONCTRL_Rte_Write_B_P_STB_MODE(FALSE);
    }
    
    if(0 == u8RemoteOnDlyCnt)
    {
		  MONCTRL_RTE_Write_B_P_REMOTE_ON(TRUE);
    }
    else
    {
      u8RemoteOnDlyCnt--;
    }
	}
	
} /* MONCTRL_vUpdateStatus() */



/*******************************************************************************
 * Function:        MONCTRL_vInit
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Initial protection points and delay time.
 *                
 *
 ******************************************************************************/
void MONCTRL_vInit(void)
{
  mg_sVsbMonitor.u16MoniDly = 0;
  mg_sVsbMonitor.u16OcpDly = 0;
  mg_sVsbMonitor.u16OcpOffDly = 0;
  mg_sVsbMonitor.u16ScpDly = 0;
  mg_sVsbMonitor.u16ScpOffDly = 0;
  mg_sVsbMonitor.u16OvpDly = 0;
  mg_sVsbMonitor.u16OvwDly = 0;
  mg_sVsbMonitor.u16UvpDly = 0;
  mg_sVsbMonitor.u16UvwDly = 0;
  mg_sVsbMonitor.u16UvpOffDly = 0;
  mg_sVsbMonitor.u16PwOkDly = 0;
}

/*******************************************************************************
 * Function:        MONCTRL_vDeInit
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Initial protection points and delay time.
 *                
 *
 ******************************************************************************/
void MONCTRL_vDeInit(void)
{
}

/*******************************************************************************
 * Function:        MONCTRL_vClearFault
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     
 *
 ******************************************************************************/
void MONCTRL_vClearFault(void)
{
//  MONCTRL_RTE_Write_P_TrimVsbGain(0);
//  MONCTRL_RTE_Write_P_TrimV1GainOvpA(0);
}

/*******************************************************************************
 * Function:        MONCTRL_vVin
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Exe Period:      1ms
 * Description:     Mornitor the Input voltage 
 *
 ******************************************************************************/
void MONCTRL_vVin(void)
{
  uint16 u16VinVoltage;
  
  static uint16 u16VinUvThrHigh  = AC_VIN_UV_HIGH;
  static uint16 u16VinUvThrLow   = AC_VIN_UV_LOW;
  static uint16 u16VinOvThrHigh  = AC_VIN_OV_HIGH;
  static uint16 u16VinOvThrLow   = AC_VIN_OV_LOW;
  static uint16 u16VinDropOutHigh = AC_DROPOUT_VIN_HIGH;
  static uint16 u16VinDropOutLow  = AC_DROPOUT_VIN_LOW;
  static uint16 u16VinUvwThr      = AC_VIN_UVW_VOLT;

  static uint16 u16VinUvCnt     = 0;
  static uint16 u16VinOvCnt     = 0;
  static uint16 u16VinUvwCnt    = 0;
  static uint16 u16VinTypeAOld  = 0;
  
  static uint8 u8IsAcOn2Off = FALSE;
  static uint8 u8IsVinUvDataSave = FALSE;
  static uint8 u8IsVinOvDataSave = FALSE;
  
  if(FALSE != MONCTRL_RTE_Read_B_R_PRI1_RX_PKG())
  {
    MONCTRL_RTE_Read_R_vVinLinear(&u16VinVoltage);

    /* swtich Vin threshold for HVAC and HVDC input */
    if (FALSE == MONCTRL_RTE_Read_B_R_VDC_IN()) /* HVAC input */
    {
      if (u16VinTypeAOld != MONCTRL_RTE_Read_B_R_VDC_IN())
      {
        u16VinTypeAOld   = MONCTRL_RTE_Read_B_R_VDC_IN();
        u16VinUvThrHigh = AC_VIN_UV_HIGH;
        u16VinUvThrLow  = AC_VIN_UV_LOW;
        u16VinOvThrHigh = AC_VIN_OV_HIGH;
        u16VinOvThrLow  = AC_VIN_OV_LOW;
        u16VinDropOutHigh = AC_DROPOUT_VIN_HIGH;
        u16VinDropOutLow  = AC_DROPOUT_VIN_LOW;
        u16VinUvwThr      = AC_VIN_UVW_VOLT;
      }
    }
    else /* HVDC input */
    {
      if (u16VinTypeAOld != MONCTRL_RTE_Read_B_R_VDC_IN())
      {
        u16VinTypeAOld   = MONCTRL_RTE_Read_B_R_VDC_IN();
        u16VinUvThrHigh = DC_VIN_UV_HIGH;
        u16VinUvThrLow  = DC_VIN_UV_LOW;
        u16VinOvThrHigh = DC_VIN_OV_HIGH;
        u16VinOvThrLow  = DC_VIN_OV_LOW;
        u16VinDropOutHigh = DC_DROPOUT_VIN_HIGH;
        u16VinDropOutLow  = DC_DROPOUT_VIN_LOW;
        u16VinUvwThr      = DC_VIN_UVW_VOLT;
      }
    }
    
    /************************************************************
     * UNDER VOLTAGE detection
     ************************************************************/

    if((u16VinVoltage < u16VinUvThrLow) && (FALSE == INTCOM_RTE_Read_B_R_VIN_OK_PRI()))
    { 
      if (u16VinUvCnt < MG_U16_VIN_UVP_DLY)
      {
        u16VinUvCnt++;
      }
      else
      {
        u16VinUvCnt = 0;
        MONCTRL_RTE_Write_B_P_VIN_UV(TRUE);
        MONCTRL_RTE_Write_B_P_VIN_UVW(TRUE);
        if(FALSE == u8IsVinUvDataSave)
        {        
          MONCTRL_cfg_vBlackBoxVinSaveData2Buff();
          u8IsVinUvDataSave = TRUE;
        }
      }
    }
    else if(u16VinVoltage < u16VinUvwThr)
    {
      if (u16VinUvwCnt < MG_U16_VIN_UVW_DLY)
      {
        u16VinUvwCnt++;
      }
      else
      {
        u16VinUvwCnt = 0;
        MONCTRL_RTE_Write_B_P_VIN_UVW(TRUE);
      }
    }
    else if (u16VinVoltage >= u16VinUvThrHigh)
    {
      u16VinUvCnt = 0;
      MONCTRL_RTE_Write_B_P_VIN_UV(FALSE);
      MONCTRL_RTE_Write_B_P_VIN_UVW(FALSE);
      u8IsVinUvDataSave = FALSE;
    }
    else
    {
      /* do nothing */
    }

    /************************************************************
     * OVER VOLTAGE detection
     ************************************************************/
    if (u16VinVoltage > u16VinOvThrHigh)
    { 
      if (u16VinOvCnt < MG_U16_VIN_OVP_DLY)
      {
        u16VinOvCnt++;
      }
      else
      {
        u16VinOvCnt = 0;
#ifndef HALT_TEST_MODE
        MONCTRL_RTE_Write_B_P_VIN_OV(TRUE);
#endif        
        if(FALSE == u8IsVinOvDataSave)
        {
#ifndef HALT_TEST_MODE          
          MONCTRL_cfg_vBlackBoxVinSaveData2Buff();
#endif
          u8IsVinOvDataSave = TRUE;
        }

      }
    }
    else if (u16VinVoltage <= u16VinOvThrLow)
    {
      u16VinOvCnt = 0;
      MONCTRL_RTE_Write_B_P_VIN_OV(FALSE);
      u8IsVinOvDataSave = FALSE;
    }
    else
    {
      /* do nothing */
    }
    
    if((u16VinVoltage < u16VinDropOutLow) && (FALSE == INTCOM_RTE_Read_B_R_VIN_OK_PRI()))
    {
      MONCTRL_RTE_Write_B_P_NO_VIN(TRUE);
      if(FALSE == u8IsAcOn2Off)
      {
        MONCTRL_RTE_Write_B_P_INPUT_OFF(TRUE);
        u8IsAcOn2Off = TRUE;
      }
    }
    else if(u16VinVoltage > u16VinDropOutHigh)
    {
      MONCTRL_RTE_Write_B_P_NO_VIN(FALSE);
      u8IsAcOn2Off = FALSE;
    }

    /* Detect Vin is OK or not */
    if(
       (FALSE != MONCTRL_RTE_Read_B_R_VIN_DROPOUT()) ||
       (FALSE != MONCTRL_RTE_Read_B_R_VIN_UV())      ||
       (FALSE != MONCTRL_RTE_Read_B_R_VIN_OV())      ||
       ((FALSE == INTCOM_RTE_Read_B_R_VIN_OK_PRI()) && (RTE_B_PRI_VIN_ALERT)))
    {

      MONCTRL_RTE_Write_B_P_VIN_OK(FALSE);
    }
    else
    {
      MONCTRL_RTE_Write_B_P_VIN_OK(TRUE);
    }
    
    /* Check input AC line status */
    if(FALSE != MONCTRL_RTE_Read_B_R_NO_VIN())
    {
      MONCTRL_RTE_Write_P_u8AcLineStatus(MG_NO_AC_INPUT);
    }
    else if(FALSE != MONCTRL_RTE_Read_B_R_VDC_IN())
    {
      MONCTRL_RTE_Write_P_u8AcLineStatus(MG_HVDC_INPUT);
    }
    else
    {
      uint16 u16DataTmp;
      
      MONCTRL_Rte_Read_R_u16100mHzVoltInFreq(&u16DataTmp);
      
      if(FALSE != MONCTRL_Rte_Read_B_R_VIN_LINE_LOW())
      {
        if((u16DataTmp >= 475u) && (u16DataTmp <= 525u)) /* 50Hz */
        {
          MONCTRL_RTE_Write_P_u8AcLineStatus(MG_LOW_LINE_50HZ);
        }
        else if((u16DataTmp >= 570u) && (u16DataTmp <= 630u)) /* 60Hz */
        {
          MONCTRL_RTE_Write_P_u8AcLineStatus(MG_LOW_LINE_60HZ);
        }
        else
        {
          MONCTRL_RTE_Write_P_u8AcLineStatus(MG_RESERVED);
        }
      }
      else
      {
        if((u16DataTmp >= 475u) && (u16DataTmp <= 525u)) /* 50Hz */
        {
          MONCTRL_RTE_Write_P_u8AcLineStatus(MG_HIGH_LINE_50HZ);
        }
        else if((u16DataTmp >= 570u) && (u16DataTmp <= 630u))  /* 60Hz */
        {
          MONCTRL_RTE_Write_P_u8AcLineStatus( MG_HIGH_LINE_60HZ);
        }
        else
        {
          MONCTRL_RTE_Write_P_u8AcLineStatus(MG_RESERVED);
        }
      }
    }
  }
}

/*******************************************************************************
 * Function:        MONCTRL_vVsbOutput
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Exe Period:      0.1ms
 * Description:     Mornitor the output voltage and current 
 *
 ******************************************************************************/
void MONCTRL_vCheckVsbOvp(void)
{
  uint16 u16VsbInt;
  
  MONCTRL_RTE_Read_R_vVsbLinear(&u16VsbInt);
  
  if (FALSE != MONCTRL_RTE_Read_B_R_VSB_MONI_EN())
  {
		/* OVP detect */
		if((u16VsbInt > MG_VSB_OVP_HIGH))
		{
			if (mg_sVsbMonitor.u16OvpDly >= MG_VSB_OVP_DLY)
			{
#ifndef HALT_TEST_MODE
				MONCTRL_RTE_Write_B_P_VSB_LATCH(TRUE);
				MONCTRL_RTE_Write_B_P_VSB_OVP(TRUE);
				MONCTRL_RTE_Write_B_P_VSB_OVW(TRUE);
#endif
			}
			else
			{
				mg_sVsbMonitor.u16OvpDly++;
			}
		}
		else
		{
			if(mg_sVsbMonitor.u16OvpDly > 0)
			{
				mg_sVsbMonitor.u16OvpDly--;
			}
		}
  }
  else
  {
    mg_sVsbMonitor.u16OvpDly = 0;
  }
  
}
/*******************************************************************************
 * Function:        MONCTRL_vVsbOutput
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Exe Period:      1ms
 * Description:     Mornitor the output voltage and current 
 *
 ******************************************************************************/
void MONCTRL_vVsbOutput(void)
{ 
	uint16 u16VsbVoltInt;
  uint16 u16VsbVoltExt;
	uint16 u16VsbCurrent;
  uint16 u16VsbExtVolt10mV;
  static uint8 u8VsbPreState = FALSE;
  static uint16 u8VsbStartCnt = 0;
  boolean bIsVsbOcpTest;
	
	MONCTRL_RTE_Read_R_vVsbLinear(&u16VsbVoltInt);
  MONCTRL_RTE_Read_R_vIoutVsbLinear(&u16VsbCurrent);
  MONCTRL_Rte_Read_R_u16VsbLinearExt(&u16VsbVoltExt);
  
  if((FALSE != MONCTRL_RTE_Read_B_R_VSB_ON_DIO()) && 
      (FALSE == u8VsbPreState)
     )
  {
    u8VsbStartCnt = 65;
  }
  else
  {
  }
  u8VsbPreState =  MONCTRL_RTE_Read_B_R_VSB_ON_DIO();
	
  /* Check Vsb OCP/SCP/OVP after soft start */
  if (FALSE != MONCTRL_RTE_Read_B_R_VSB_MONI_EN())
  {
		/* OVW detect */
		if(u16VsbVoltInt > MG_VSB_OVW_HIGH)
		{
			if (mg_sVsbMonitor.u16OvwDly < MG_VSB_OVW_DLY)
			{
				mg_sVsbMonitor.u16OvwDly++;
			}
			else
			{
				MONCTRL_RTE_Write_B_P_VSB_OVW(TRUE);
			}
		}
		/* OVW recover */
		else if(u16VsbVoltInt < MG_VSB_OVW_LOW)
		{
			if (mg_sVsbMonitor.u16OvwDly > 0)
			{
				mg_sVsbMonitor.u16OvwDly--;
			}
			else
			{
				MONCTRL_RTE_Write_B_P_VSB_OVW(FALSE);
			}
		}
		
    /* Check UVP only when current is less than OCP point */
    if(u16VsbCurrent < MG_VSB_OCP_HIGH)
    {
      /* UVP detect */
      if (u16VsbVoltInt < MG_VSB_UVP_LOW)
      {
        if (mg_sVsbMonitor.u16UvpDly >= MG_VSB_UVP_DLY)
        {
#ifndef HALT_TEST_MODE
          MONCTRL_RTE_Write_B_P_VSB_LATCH(TRUE);
          MONCTRL_RTE_Write_B_P_VSB_UVP(TRUE);
#endif
          MONCTRL_RTE_Write_B_P_VSB_UVW(TRUE);
        }
        else
        {
          mg_sVsbMonitor.u16UvpDly++;
        }
      }
      else
      {
        if(mg_sVsbMonitor.u16UvpDly > 0)
        {
          mg_sVsbMonitor.u16UvpDly--;
        }
      }
      
      u16VsbExtVolt10mV = MONCTRL_SCFG_u16GetVsbExtVolt10mVAvg();
      
      if (u16VsbExtVolt10mV < MG_VSB_EXT_UVP_LOW)
      {
        if (mg_sVsbMonitor.u16ExtUvpDly >= MG_VSB_UVP_DLY)
        {
#ifndef HALT_TEST_MODE
          MONCTRL_RTE_Write_B_P_VSB_LATCH(TRUE);
          MONCTRL_RTE_Write_B_P_VSB_UVP(TRUE);
#endif
          MONCTRL_RTE_Write_B_P_VSB_UVW(TRUE);
        }
        else
        {
          mg_sVsbMonitor.u16ExtUvpDly++;
        }
      }
      else
      {
        if(mg_sVsbMonitor.u16ExtUvpDly > 0)
        {
          mg_sVsbMonitor.u16ExtUvpDly--;
        }
      }
      
      /* UVW  detect */		
      if(u16VsbVoltInt < MG_VSB_UVW_LOW) 
      {
        if (mg_sVsbMonitor.u16UvwDly >= MG_VSB_UVW_DLY)
        {
          MONCTRL_RTE_Write_B_P_VSB_UVW(TRUE);
        }
        else
        {
          mg_sVsbMonitor.u16UvwDly++;
        }
      }
      else if(u16VsbVoltInt > MG_VSB_UVW_HIGH) 
      {
        /* UVW recover */
        if (mg_sVsbMonitor.u16UvwDly > 0)
        {
          mg_sVsbMonitor.u16UvwDly--;
        }
        else
        {
          MONCTRL_RTE_Write_B_P_VSB_UVW(FALSE);
        }
      }
    }
    
    MONCTRL_Rte_Read_R_bIsVsbOcpTest(&bIsVsbOcpTest);
    
    if(FALSE != bIsVsbOcpTest)
    {
      MONCTRL_RTE_Write_B_P_VSB_OCP(TRUE);
      mg_sVsbMonitor.u16OcpOffDly = 0;
    }
  }
	/* VSB soft start */
  else
  {
		mg_sVsbMonitor.u16UvpDly  = 0;
		mg_sVsbMonitor.u16OvwDly  = 0;
		mg_sVsbMonitor.u16UvwDly  = 0;
  }
  
  /* During soft start */
  if(u8VsbStartCnt != 0)
  {
    u8VsbStartCnt--;
    
    /* SCP detect */
    if((u16VsbVoltExt < MG_VSB_SCP_VOLT_ST) && (u16VsbCurrent > MG_VSB_OCP_HIGH))
    {
      if(mg_sVsbMonitor.u16ScpDly < MG_VSB_SCP_ST_DLY)
      {
        mg_sVsbMonitor.u16ScpDly++; 
      }
      else
      {
        MONCTRL_RTE_Write_B_P_VSB_OCP(TRUE);
        MONCTRL_RTE_Write_B_P_VSB_OCW(TRUE);
      }
      mg_sVsbMonitor.u16OcpOffDly = 0;
    }
    else
    {
      mg_sVsbMonitor.u16ScpDly = 0; 
    }
    
    /* OCP detect  */
    if(u16VsbCurrent > MG_VSB_OCP_HIGH)
    {
      if(mg_sVsbMonitor.u16OcpDly < MG_VSB_OCP_ST_DLY)
      {
        mg_sVsbMonitor.u16OcpDly++;
      }
      else
      {
        MONCTRL_RTE_Write_B_P_VSB_OCP(TRUE);
        MONCTRL_RTE_Write_B_P_VSB_OCW(TRUE);
        
        mg_sVsbMonitor.u16OcpOffDly = 0;
      }
    }
    else
    {
      mg_sVsbMonitor.u16OcpDly = 0;
    }
  }
  else /* After soft start */
  {
    /* SCP detect */
    if(((u16VsbVoltExt < MG_VSB_SCP_VOLT_H) && (u16VsbCurrent > MG_VSB_OCP_HIGH)) ||
       (u16VsbVoltExt < MG_VSB_SCP_VOLT_L))
    {
      if(mg_sVsbMonitor.u16ScpDly < MG_VSB_SCP_DLY)
      {
        mg_sVsbMonitor.u16ScpDly++; 
      }
      else
      {
        MONCTRL_RTE_Write_B_P_VSB_OCP(TRUE);
        MONCTRL_RTE_Write_B_P_VSB_OCW(TRUE);
        
        mg_sVsbMonitor.u16OcpOffDly = 0;
      }
    }
    else
    {
      mg_sVsbMonitor.u16ScpDly = 0;
    }
    
     /* OCP detect  */
    if(u16VsbCurrent > MG_VSB_OCP_HIGH)
    {
      if(mg_sVsbMonitor.u16OcpDly < MG_VSB_OCP_DLY)
      {
        mg_sVsbMonitor.u16OcpDly++;
      }
      else
      {
        MONCTRL_RTE_Write_B_P_VSB_OCP(TRUE);
        MONCTRL_RTE_Write_B_P_VSB_OCW(TRUE);
        
        mg_sVsbMonitor.u16OcpOffDly = 0;
      }
    }
    else
    {
      mg_sVsbMonitor.u16OcpDly = 0;
    }		

    /* OCW detect */
    if(u16VsbCurrent > MG_VSB_OCW_HIGH)
    {
      if(mg_sVsbMonitor.u16OcwDly < MG_VSB_OCW_DLY)
      {
        mg_sVsbMonitor.u16OcwDly++;
      }
      else
      {
        MONCTRL_RTE_Write_B_P_VSB_OCW(TRUE);
      }
    }
    /* OCW recover */
    else if(u16VsbCurrent < MG_VSB_OCW_LOW)
    {
      if(mg_sVsbMonitor.u16OcwDly > 0U)
      {
        mg_sVsbMonitor.u16OcwDly--;
      }
      else
      {
        MONCTRL_RTE_Write_B_P_VSB_OCW(FALSE);
      }
    }
  }
  
  /* Vsb OCP hiccup restart */
  if(u16VsbCurrent < MG_VSB_OCP_LOW)
  {
    if(mg_sVsbMonitor.u16OcpOffDly < MG_VSB_OCP_OFF_DLY)
    {
      mg_sVsbMonitor.u16OcpOffDly++;
    }
    else
    {
      MONCTRL_RTE_Write_B_P_VSB_OCP(FALSE);
      MONCTRL_RTE_Write_B_P_VSB_OCW(FALSE);
    }
    mg_sVsbMonitor.u16OcpDly=0;
    mg_sVsbMonitor.u16ScpDly=0;
    mg_sVsbMonitor.u16OcwDly= 0;
  }	
  
} /* MONCTRL_vVsbOutput() */

/*******************************************************************************
 * Function:        MONI_AuxModeDetect 100ms cycle
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     
 *
 ******************************************************************************/
void MONCTRL_vAxuModeDetect(void)
{
  static uint16 u16AuxModeCnt = 0;

  if ((FALSE != MONCTRL_RTE_Read_B_R_PRI1_NO_RX_PKG()) &&
      (FALSE != MONCTRL_RTE_Read_B_R_SEC1_NO_RX_PKG())) /* add hardware pin status */
  {
    if (u16AuxModeCnt < VSB_AUX_MODE_DETECT_DLY)
    {
      u16AuxModeCnt++;
    }
    else
    {
      u16AuxModeCnt = 0;

      RTE_PMB_Write_bit_Aux_Mode(TRUE);
      MONCTRL_RTE_Write_P_u8AcLineStatus(MG_NO_AC_INPUT);
    }
  }
  else
  {
    u16AuxModeCnt = 0;
    RTE_PMB_Write_bit_Aux_Mode(FALSE);
  }
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/
/*******************************************************************************
 * Function:        MONCTRL_vCheckStatusReset
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     This function to check status reset or not.
 *
 ******************************************************************************/
 void MONCTRL_vCheckStatusReset(void)
{
	static uint16 u16DelayCheckReCycle = 10;
	static MG_E_PSON  ePsonState = MG_PSON_INIT;
	static MG_E_PSON  ePsCycle   = MG_PSON_INIT;
	boolean bIsClearFault = FALSE;
	
	if(FALSE == MONCTRL_RTE_Read_B_R_REMOTE_ON())
	{
		ePsonState = MG_PSON_MODE_OFF;
	}
	
	if(MG_PSON_MODE_OFF == ePsonState)
	{
		if(FALSE != MONCTRL_RTE_Read_B_R_REMOTE_ON())
		{
			ePsonState = MG_PSON_INIT;
			bIsClearFault = TRUE;
		}
	}
	
	if(FALSE != MONCTRL_RTE_Read_B_R_NO_VIN())
	{
		ePsCycle = MG_PSON_MODE_OFF;
		if(0 != u16DelayCheckReCycle)
		{
			u16DelayCheckReCycle--;
		}
	}
	else if((FALSE == MONCTRL_RTE_Read_B_R_NO_VIN()) &&
		      (0 == u16DelayCheckReCycle)              &&
	        (MG_PSON_MODE_OFF == ePsCycle))
	{
		ePsCycle = MG_PSON_INIT;
		u16DelayCheckReCycle = 10u;
		bIsClearFault = TRUE;
	}
	
	if(FALSE != bIsClearFault)
	{
		MONCTRL_RTE_Write_P_uComStatus01(0);
		MONCTRL_SCFG_vClearAllFault();
		MONCTRL_RTE_Write_B_P_VSB_LATCH(FALSE);
		MONCTRL_RTE_Write_B_P_VSB_OVP(FALSE);
		MONCTRL_RTE_Write_B_P_VSB_UVP(FALSE);
		MONCTRL_RTE_Write_B_P_VSB_OCP(FALSE);
		MONCTRL_RTE_Write_B_P_VIN_UV(FALSE);
		MONCTRL_RTE_Write_B_P_VIN_OV(FALSE);	
    MONCTRL_Rte_Write_B_P_V1_OVP(FALSE);
    MONCTRL_Rte_Write_B_P_V1_UVP(FALSE);
    MONCTRL_Rte_Write_B_P_V1_OCP(FALSE);
    MONCTRL_Rte_Write_B_P_V1_OCW(FALSE);
		MONCTRL_RTE_Write_B_P_CLEAR_LATCH_FAULT(TRUE);
    MONCTRL_RTE_Write_P_TrimVsbGainOvp(100u);
    MONCTRL_SCFG_vSetVsbOvpPwmOut(FALSE);
    MONCTRL_SCFG_vVsbOvpDuty(10u);
    MONCTRL_Rte_Write_B_P_V1_OVP_TEST(FALSE);
    MONCTRL_Rte_Write_B_P_VSB_OVP_TEST(FALSE);
    MONCTRL_Rte_Write_B_P_V1_LATCHED(FALSE);
    bIsClearFault = FALSE;
	}
 
	
	/* When Sec side had clear fault, reset the clear latched fault flag */
	if(FALSE != MONCTRL_RTE_Read_B_R_SEC_FAULT_CLR())
	{
		MONCTRL_RTE_Write_B_P_CLEAR_LATCH_FAULT(FALSE);
	}

}


/*
 * End of file
 */
