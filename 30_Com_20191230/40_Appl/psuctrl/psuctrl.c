/******************************************************************************
 * \file    psuctrl.c
 * \brief   State machine control of PSU
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-09-04 09:45:45 +0800 (Wed, 04 Sep 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 228 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

/* Module header */
#define PSUCTRL_EXPORT_H
#include "psuctrl_api.h"
#include "psuctrl_cfg.h"
#include "psuctrl_conf.h"
#include "psuctrl_scb.h"
#include "psuctrl_scfg.h"
#include "psuctrl_rte.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

#define MG_VSB_PWR_UP_DLY          (60u)     /* 60 * 1ms = 60ms */
#define MG_VSB_PWR_OK_DLY          (60u)     /* 60 * 1ms = 60ms */
#define MG_VSB_PWR_DOWN_DLY        (1000u)   /* 1000 * 1ms = 1000ms */
#define MG_VSB_REGU_LOW            (0)        /* todo */
#define MB_V1_OFF_4_VSB_OFF_DLY    (1u)       /* 2* 1ms = 2ms*/

#define MG_V1_PWR_UP_DLY           (200u)    /* 200 * 1ms = 200ms  */

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

typedef enum
{
	MG_E_POWER_INIT = 0,
	MG_E_POWER_ON,
	MG_E_POWER_CHECK_PROTECT
} MG_E_POWER_STATE;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static MG_E_POWER_STATE        mg_VsbState;
static MG_E_POWER_STATE        mg_V1State;

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
 * Function:        PSUCTRL_Init
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Initial function
 *
 ******************************************************************************/
void PSUCTRL_vInit(void)
{
	mg_VsbState          = MG_E_POWER_INIT;
	mg_V1State           = MG_E_POWER_INIT;
}

/*******************************************************************************
 * Function:        PSUCTRL_DeInit
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Initial function
 *
 ******************************************************************************/
void PSUCTRL_vDeInit(void)
{
}

/*******************************************************************************
 * Function:        PSUCTRL_vVsbOut()
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Handle PSU power up , monitor and power down.
 *                  Execute every 1ms
 *
 ******************************************************************************/
void PSUCTRL_vVsbOut(void)
{
	static uint16 u16DelayTurnOn   = 300u;
	static boolean bIsClearFault   = 0;
	static uint16 u16DelaySetVsbOK = 0;

	static uint16 u16CheckFailCount = 0;
	static uint16 u16DelayVinNoOk   = 0;
	static uint16 u16DelayBulkCheck = 0;

	switch (mg_VsbState)
	{
		case MG_E_POWER_INIT:
		{
			PSUCTRL_SCFG_vVsbSetOn(FALSE);
			u16CheckFailCount = 0;
			PSUCTRL_Rte_Write_B_P_STA_VSB_ON(FALSE);

			//Nokia has no ps_kill,only ps_on
			if (FALSE != PSUCTRL_RTE_Read_B_R_PSON_ACTIVE())
			{
				bIsClearFault = TRUE;
			}
			else
			{
				/* Do nothing */
			}

			PSUCTRL_Rte_Write_B_P_VSB_MONI_EN(FALSE);

			/* Delay 300ms to turn on Vsb */
			if (0 != u16DelayTurnOn)
			{
				u16DelayTurnOn--;
			}

			if (
			  (0 == u16DelayTurnOn)                       &&
			  (FALSE == PSUCTRL_RTE_Read_B_R_VSB_LATCH()) &&  /* VSB is not Latched off  */
			  (FALSE == PSUCTRL_RTE_Read_B_R_AUX_MODE())      /* Not in Aux mode */
			)
			{
				mg_VsbState = MG_E_POWER_ON;
			}

			break;
		}

		case MG_E_POWER_ON:
		{
			/* AC and Bulk must be OK */
			if (
			  (FALSE != PSUCTRL_RTE_Read_B_R_RELAY_ON()) &&
			  //        (FALSE != PSUCTRL_RTE_Read_B_R_BULK_OK()) &&
			  (FALSE != PSUCTRL_RTE_Read_B_R_VIN_OK())
			)
			{
				if (FALSE != bIsClearFault)
				{
					PSUCTRL_SCFG_vClearAllFault();
					bIsClearFault = FALSE;
				}

				mg_VsbState = MG_E_POWER_CHECK_PROTECT;
				PSUCTRL_SCFG_vVsbSetOn(TRUE);
				u16DelaySetVsbOK  = 0;
				u16DelayVinNoOk   = 0;
				u16DelayBulkCheck = 1000u;
			}
			else
			{
				/* do nothing */
			}

			break;
		}

		case MG_E_POWER_CHECK_PROTECT:
		{
			/* Delay Check protection */
			if (u16DelaySetVsbOK > 1000u)
			{
				PSUCTRL_Rte_Write_B_P_STA_VSB_ON(TRUE);
			}
			else
			{
				u16DelaySetVsbOK++;
			}

			if (u16CheckFailCount < 500u)
			{
				u16CheckFailCount++;
			}
			else
			{
				PSUCTRL_Rte_Write_B_P_VSB_MONI_EN(TRUE);
			}

			if (0 != u16DelayBulkCheck)
			{
				u16DelayBulkCheck--;
			}

			if (
			  (FALSE != PSUCTRL_RTE_Read_B_R_VSB_OCP())    ||
			  (FALSE != PSUCTRL_RTE_Read_B_R_VSB_LATCH())  ||
			  (FALSE == PSUCTRL_RTE_Read_B_R_VIN_OK())     ||
			  (FALSE != PSUCTRL_RTE_Read_B_R_AUX_MODE())   ||
			  ((0 == u16DelayBulkCheck) && (FALSE != PSUCTRL_RTE_Read_B_R_V1_FAULT_ACTIVE()))
			)
			{
				if ((FALSE == PSUCTRL_RTE_Read_B_R_VIN_OK()) ||
				    ((0 == u16DelayBulkCheck) && (FALSE != PSUCTRL_RTE_Read_B_R_V1_FAULT_ACTIVE()))
				   )
				{
					if (u16DelayVinNoOk < 20u)
					{
						u16DelayVinNoOk++;
					}
					else
					{
						mg_VsbState = MG_E_POWER_INIT;
						u16DelayTurnOn = 300u;
					}
				}
				else
				{
					mg_VsbState = MG_E_POWER_INIT;

					if (FALSE != PSUCTRL_RTE_Read_B_R_VSB_OCP())
					{
						u16DelayTurnOn = 1100u;
					}
					else
					{
						u16DelayTurnOn = 300u;
					}
				}
			}

			break;
		}

		default:
		{
			mg_VsbState = MG_E_POWER_INIT;
			u16DelayTurnOn = 300u;
			break;
		}
	}
} /* PSUCTRL_vVsbOut() */

/*******************************************************************************
 * Function:        PSUCTRL_vV1Out()
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     Handle v1 power up , monitor and power down.
 *                  Execute every 1ms
 *
 ******************************************************************************/
void PSUCTRL_vV1Out(void)
{
	static uint16 u16DelaySetVmainOK  = 0;
	static uint8  u8DelayTurnoffVmain = 0;
	static uint8  u8IsPowerOkSet;

	switch (mg_V1State)
	{
		case MG_E_POWER_INIT:
		{
			PSUCTRL_Rte_Write_B_P_STA_V1_ON(FALSE);
			PSUCTRL_Rte_Write_B_P_TURN_ON_MAIN(FALSE);
			PSUCTRL_Rte_Write_B_P_V1_MONI_EN(FALSE);
			PSUCTRL_Rte_Write_B_P_OUTPUT_OK(FALSE);

			if (
			  (FALSE == PSUCTRL_RTE_Read_B_R_VIN_OK())      ||   /* Vin is not OK */
			  (FALSE != PSUCTRL_RTE_Read_B_R_KILL_ACTIVE()) ||   /* Ps Kill active */
			  (FALSE != PSUCTRL_RTE_Read_B_R_AUX_MODE())         /* In Aux mode */
			)
			{
				/* don't turn on the main output */
			}
			else
			{
				if (
				  (FALSE == PSUCTRL_RTE_Read_B_R_PFC_OVP())    &&    /* PFC OVP */
				  (FALSE == PSUCTRL_RTE_Read_B_R_V1_LATCHED()) &&
				  (FALSE != PSUCTRL_RTE_Read_B_R_REMOTE_ON())  &&
				  (FALSE == PSUCTRL_Rte_Read_B_R_TEMP_ANY_OTP()) &&
#ifndef HALT_TEST_MODE
				  (FALSE != PSUCTRL_RTE_Read_B_R_STA_VSB_ON())   &&
#endif
				  (FALSE != PSUCTRL_RTE_Read_B_R_VIN_OK())
				)
				{
					PSUCTRL_Rte_Write_B_P_TURN_ON_MAIN(TRUE);
					PSUCTRL_Rte_Write_B_P_STA_V1_ON(TRUE);
					u16DelaySetVmainOK = 0;
					mg_V1State = MG_E_POWER_CHECK_PROTECT;
					u8IsPowerOkSet = FALSE;
					u8DelayTurnoffVmain = 0;
					PSUCTRL_CFG_vBlaboxClearFault();
				}
			}

			break;
		}

		case MG_E_POWER_CHECK_PROTECT:
		{
			if ((u16DelaySetVmainOK > 350u) && (FALSE == u8IsPowerOkSet))
			{
				PSUCTRL_Rte_Write_B_P_V1_MONI_EN(TRUE);
				PSUCTRL_Rte_Write_B_P_OUTPUT_OK(TRUE);
				PSUCTRL_SCFG_vClearPowerOffFault();
				u8IsPowerOkSet = TRUE;
			}
			else
			{
				u16DelaySetVmainOK++;
			}

			if (
			  (FALSE != PSUCTRL_RTE_Read_B_R_V1_FAULT_ACTIVE())   ||    /* BULK is not OK */
			  (FALSE != PSUCTRL_RTE_Read_B_R_PFC_OVP())           ||    /* PFC OVP */
			  (FALSE != PSUCTRL_RTE_Read_B_R_V1_OVP())            ||    /* V1 OVP*/
			  (FALSE != PSUCTRL_RTE_Read_B_R_V1_OCP())            ||    /* V1 OCP*/
			  (FALSE != PSUCTRL_RTE_Read_B_R_V1_UVP())            ||    /* V1 UVP*/
			  (FALSE == PSUCTRL_RTE_Read_B_R_VIN_OK())            ||    /* Vin is not OK */
			  (FALSE != PSUCTRL_Rte_Read_B_R_TEMP_ANY_OTP())      ||    /* Any OTP  */
#ifndef HALT_TEST_MODE
			  (FALSE == PSUCTRL_RTE_Read_B_R_STA_VSB_ON())        ||    /* Vsb is off */
#endif
			  (FALSE == PSUCTRL_RTE_Read_B_R_REMOTE_ON())         ||    /* PMBus Operation Off/ PSON inactive / PSKILL active */
			  (FALSE != PSUCTRL_RTE_Read_B_R_AUX_MODE())          ||    /* Aux mode */
			  (FALSE != PSUCTRL_RTE_Read_B_R_BOOT_RESET_FLAG())         /* Not in bootloader mode */
			)
			{
				PSUCTRL_Rte_Write_B_P_OUTPUT_OK(FALSE);

				if (
				  (FALSE != PSUCTRL_RTE_Read_B_R_V1_OVP())           ||    /* V1 OVP*/
				  (FALSE != PSUCTRL_RTE_Read_B_R_V1_OCP())           ||    /* V1 OCP*/
				  (FALSE != PSUCTRL_RTE_Read_B_R_V1_UVP())                /* V1 UVP*/
				)
				{
					PSUCTRL_Rte_Write_B_P_V1_LATCHED(TRUE);
				}

				if (FALSE != PSUCTRL_RTE_Read_B_R_V1_OVP())
				{
					PSUCTRL_Rte_Write_B_P_V1_OVP_TEST(FALSE);
				}

				if (u8DelayTurnoffVmain > 4u)
				{
					mg_V1State = MG_E_POWER_INIT;
				}
				else
				{
					u8DelayTurnoffVmain++;
				}
			}
			else
			{
				u8DelayTurnoffVmain = 0;
			}

			break;
		}

		default:
		{
			mg_V1State = MG_E_POWER_INIT;
			break;
		}
	}
}

/*******************************************************************************
 * \brief         Adjust 5V/54V voltage
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PSUCTRL_vTrim(void)
{
	uint16 u16TrimVsbGain;
	uint16 u16TrimV1Gain;
	uint16 u16TrimVsbGainAct;
	uint16 u16TrimV1GainAct;
	static 	uint16 u16TrimVsbOvpGainAct;

	/* Vsb trim and Ovp test */
	if (FALSE != PSUCTRL_RTE_Read_B_R_VSB_OVP_TEST())
	{
		if (FALSE == PSUCTRL_RTE_Read_B_R_VSB_UVP())
		{
			PSUCTRL_Rte_Read_R_u16TrimVsbGainOvp(&u16TrimVsbGain);

			if (u16TrimVsbGain > 1000u) /* Limitation */
			{
				u16TrimVsbGain = 1000u;
				PSUCTRL_Rte_Write_P_u16TrimVsbGainOvp(1000u);
			}

			PSUCTRL_SCFG_vSetVsbOvpPwmOut(TRUE);

			if (u16TrimVsbGain > u16TrimVsbOvpGainAct)
			{
				if ((u16TrimVsbOvpGainAct + 10u) > u16TrimVsbGain)
				{
					u16TrimVsbOvpGainAct = u16TrimVsbGain;
				}
				else
				{
					u16TrimVsbOvpGainAct += 10u;
				}

				PSUCTRL_SCFG_vVsbOvpDuty(u16TrimVsbOvpGainAct);
			}
		}
		else
		{
			if (u16TrimVsbOvpGainAct > 10u)
			{
				u16TrimVsbOvpGainAct -= 10u;
				PSUCTRL_SCFG_vVsbOvpDuty(u16TrimVsbOvpGainAct);
			}
			else
			{
				PSUCTRL_SCFG_vSetVsbOvpPwmOut(FALSE);
			}
		}
	}
	else
	{
		PSUCTRL_Rte_Read_R_u16TrimVsbGain(&u16TrimVsbGain);
		PSUCTRL_Rte_Read_R_u16TrimVsbGainAct(&u16TrimVsbGainAct);

		if (u16TrimVsbGain != u16TrimVsbGainAct)
		{
			if (u16TrimVsbGain > 1000u) /* Limitation */
			{
				u16TrimVsbGain = 1000u;
				PSUCTRL_Rte_Write_P_u16TrimVsbGain(1000u);
			}

			if (u16TrimVsbGain > u16TrimVsbGainAct)
			{
				if (u16TrimVsbGain > (u16TrimVsbGainAct + 10u))
				{
					u16TrimVsbGainAct += 10u;
				}
				else
				{
					u16TrimVsbGainAct = u16TrimVsbGain;
				}
			}
			else
			{
				if (u16TrimVsbGainAct > (u16TrimVsbGain + 10u))
				{
					u16TrimVsbGainAct -= 10u;
				}
				else
				{
					u16TrimVsbGainAct = u16TrimVsbGain;
				}
			}

			PSUCTRL_Rte_Write_P_u16TrimVsbGainAct(u16TrimVsbGainAct);
			PSUCTRL_SCFG_vVsbTrimDuty(u16TrimVsbGainAct);
		}

		if (u16TrimVsbOvpGainAct > 10u)
		{
			u16TrimVsbOvpGainAct -= 10u;
			PSUCTRL_SCFG_vVsbOvpDuty(u16TrimVsbOvpGainAct);
		}
		else
		{
			PSUCTRL_SCFG_vSetVsbOvpPwmOut(FALSE);
		}
	}

	/* V1 trim and Ovp test */
	if (FALSE != PSUCTRL_RTE_Read_B_R_V1_OVP_TEST())
	{
		PSUCTRL_Rte_Read_R_u16TrimV1GainOvp(&u16TrimV1Gain);

		if (u16TrimV1Gain >= Q12(1.2f)) /* Limitation */
		{
			u16TrimV1Gain = Q12(1.2f);
			PSUCTRL_Rte_Write_P_u16TrimV1GainOvp(u16TrimV1Gain);
		}
		else if (u16TrimV1Gain <= Q12(0.8f))
		{
			u16TrimV1Gain = Q12(0.8f);
			PSUCTRL_Rte_Write_P_u16TrimV1GainOvp(u16TrimV1Gain);
		}

		PSUCTRL_Rte_Write_P_u16TrimV1GainAct(u16TrimV1Gain);
	}
	else
	{
		PSUCTRL_Rte_Read_R_u16TrimV1Gain(&u16TrimV1Gain);
		PSUCTRL_Rte_Read_R_u16TrimV1GainAct(&u16TrimV1GainAct);

		if (u16TrimV1Gain != u16TrimV1GainAct)
		{
			if (u16TrimV1Gain >= Q12(1.2f)) /* Limitation */
			{
				u16TrimV1Gain = Q12(1.2f);
				PSUCTRL_Rte_Write_P_u16TrimV1Gain(u16TrimV1Gain);
			}
			else if (u16TrimV1Gain <= Q12(0.8f))
			{
				u16TrimV1Gain = Q12(0.8f);
				PSUCTRL_Rte_Write_P_u16TrimV1Gain(u16TrimV1Gain);
			}

			PSUCTRL_Rte_Write_P_u16TrimV1GainAct(u16TrimV1Gain);
		}
	}
}/* PSUCTRL_vTrim */

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/


/*
 * End of file
 */
