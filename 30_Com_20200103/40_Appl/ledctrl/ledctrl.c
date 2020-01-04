/******************************************************************************
 * \file    ledctrl.c
 * \brief   update led status 
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-03-18 10:51:05 +0800 (Mon, 18 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 150 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 *******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <global.h>

/* Module header */
#define LEDCTRL_EXPORT_H
  #include "ledctrl_api.h"
  #include "ledctrl_cfg.h"
  #include "ledctrl_conf.h"
  #include "ledctrl_scb.h"
  #include "ledctrl_scfg.h"
	#include "ledctrl_rte.h"


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

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/********************************************************************************
 * \brief         Initialize LED data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void LEDCTRL_vInit(void)
{

}

/********************************************************************************
 * \brief         De-Initialize LED data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void LEDCTRL_vDeInit(void)
{

}

/********************************************************************************
 * \brief         Control LED on off according to LED state. 500ms routine 
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void LEDCTRL_vLedControl(void)
{
	static uint8 mg_u8Count = 0;
	static uint8 mg_u8mg_u8Toggleboot = 0;
	
	/*Bootloader Mode*/
	if(LEDCTRL_RTE_Read_B_R_BOOT_MODE() != FALSE ) 
	{
		LEDCTRL_SCFG_vSetInOKOff();
		LEDCTRL_SCFG_vSetFailAmberOff();
		if(mg_u8mg_u8Toggleboot++ >= 25u)
		{
			mg_u8mg_u8Toggleboot = 0;			
			LEDCTRL_SCFG_vSetOutOKToggle();
		}		
	}
	else
	/*Application Mode*/
	{
		if(++mg_u8Count >= 50)
		{
			mg_u8Count = 0;
			
      /************************* Input LED state **********************/
			if(LEDCTRL_RTE_Read_B_R_VIN_OK() != FALSE)
			{
				LEDCTRL_SCFG_vSetInOKOn();
			}
			else
			{
				LEDCTRL_SCFG_vSetInOKOff();
			}
			
			if( /* V1 is ON and OK */
				 (FALSE == LEDCTRL_RTE_Read_B_R_V1_OVP())&&
				 (FALSE == LEDCTRL_RTE_Read_B_R_V1_OCP())&&
				 (FALSE == LEDCTRL_RTE_Read_B_R_V1_UVP())&&
				 (FALSE != LEDCTRL_RTE_Read_B_R_V1_ON()) &&     
			   /* Vsb is ON */
			   (LEDCTRL_RTE_Read_B_R_VSB_ON() != FALSE) && 
			   /* Vin is OK */
			   (LEDCTRL_RTE_Read_B_R_VIN_OK() != FALSE) &&
			   /* Not in Aux Mode */
				 (LEDCTRL_RTE_Read_B_R_Aux_Mode() == FALSE))
			{
				if((LEDCTRL_RTE_Read_B_R_TEMP_OTW() != FALSE) || 
	
				   (LEDCTRL_RTE_Read_B_R_VSB_OCW()  != FALSE) || 
           (LEDCTRL_RTE_Read_B_R_VIN_UVW() != FALSE) ||
					 (LEDCTRL_RTE_Read_B_R_V1_OCW() != FALSE))
          {
            LEDCTRL_SCFG_vSetOutOKOff();
            LEDCTRL_SCFG_vSetFailAmberToggle();
          }
          else if((LEDCTRL_SCFG_u8ReadFanBitFail() != FALSE) || 
                   LEDCTRL_RTE_Read_B_R_CML() != FALSE)
          {
						LEDCTRL_SCFG_vSetOutOKOff();
						LEDCTRL_SCFG_vSetFailAmberOn();
          }
          else
          {
            LEDCTRL_SCFG_vSetOutOKOn();
            LEDCTRL_SCFG_vSetFailAmberOff();
          }
			}
			else
			{
				if(FALSE == LEDCTRL_RTE_Read_B_R_Aux_Mode()) 
				{
          /* V1 and Vsb out of range and OTP */
          if(
             (FALSE != LEDCTRL_RTE_Read_B_R_V1_OVP()) ||
             (FALSE != LEDCTRL_RTE_Read_B_R_V1_OCP()) ||
             (FALSE != LEDCTRL_RTE_Read_B_R_V1_UVP()) ||
             (FALSE != LEDCTRL_RTE_Read_B_R_VSB_OVP()) ||
             (FALSE != LEDCTRL_RTE_Read_B_R_VSB_OCP()) ||
             (FALSE != LEDCTRL_RTE_Read_B_R_VSB_UVP()) || 
             (FALSE != LEDCTRL_RTE_Read_B_R_TEMP_OTP())          
            )
          {
						LEDCTRL_SCFG_vSetOutOKOff();
						LEDCTRL_SCFG_vSetFailAmberOn();
          }
					else if(FALSE == LEDCTRL_RTE_Read_B_R_VIN_OK())
					{
						LEDCTRL_SCFG_vSetOutOKOff();
						LEDCTRL_SCFG_vSetFailAmberOff();
					}
          else if((LEDCTRL_RTE_Read_B_R_PSKILL() != FALSE)          || 
						      (LEDCTRL_RTE_Read_R_u8PmBusOperation() == 0x00u)  || 
					        (LEDCTRL_RTE_Read_B_R_PSON() == FALSE)
                 )
					{
            LEDCTRL_SCFG_vSetOutOKToggle();
						LEDCTRL_SCFG_vSetFailAmberOff();
					}
          else
          {
          }
				}
				else
				{
					LEDCTRL_SCFG_vSetOutOKOff();
					LEDCTRL_SCFG_vSetFailAmberOn();
				}
			}
		}
	}
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/


/*
 * End of file
 */
