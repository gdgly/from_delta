/*******************************************************************************
 * \file    fanctrl.c
 * \brief   Fan control
 *
 * \section AUTHOR
 *    1. Fred Ji
 *
 * \section SVN
 *  $Date: 2019-05-08 09:09:27 +0800 (Wed, 08 May 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 179 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

/* Module header */
#define FANCTRL_EXPORT_H
#include "fanctrl_api.h"
#include "fanctrl_cfg.h"
#include "fanctrl_conf.h"
#include "fanctrl_scb.h"
#include "fanctrl_scfg.h"
#include "fanctrl_rte.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/


/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
typedef struct MG_S_FAN_CTRL_
{
	uint16 u16Cnt;
	uint16 u16Speed;
	uint16 u16q12Duty;
	uint16 u16SysCmdSpeed;
	uint16 u16q12SysCmdDuty;
	sint16 s16debug;
	struct Bits_
	{
		uint8 f0Warn: 1;
		uint8 f1Fail: 1;
		uint8 f2Ovrd: 1;
		uint8 f3IoPin: 1;
		uint8 Reserve: 4;
	} Bits;
} MG_S_FAN_CTRL;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
static uint16 mg_u16FanDuty = FANCTRL_CONF_DUTY_INIT;
static MG_S_FAN_CTRL  mg_sFan[FANCTRL_CFG_E_INDEX_COUNT];
static uint8 mg_u8IsFanBlockTest = FALSE;
/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
static void mg_AdjSpeed(void);
/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Fan Data init
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vInit(void)
{
	uint8 u8Index;

	for (u8Index = 0; u8Index < FANCTRL_CFG_E_INDEX_COUNT; u8Index++)
	{
		mg_sFan[u8Index].u16Cnt = 0U;
		mg_sFan[u8Index].u16q12Duty = (MG_U16_FAN_DUTY_MAX >> DIV_SHIFT_3); /* initial speed */
		mg_sFan[u8Index].u16q12SysCmdDuty = 0U;
		mg_sFan[u8Index].u16Speed = (FANCTRL_CONF_U16_FAN_SPEED_MAX >> DIV_SHIFT_3);
		mg_sFan[u8Index].u16SysCmdSpeed = 0U;
		mg_sFan[u8Index].Bits.f0Warn = 0U;
		mg_sFan[u8Index].Bits.f1Fail = 0U;
		mg_sFan[u8Index].Bits.f2Ovrd = 0U;
		mg_sFan[u8Index].Bits.f3IoPin = 0U;
	}
}

/*******************************************************************************
 * \brief         Fan Data De-init
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vDeInit(void)
{
}

/** *****************************************************************************
 * \brief         Fan Speed control, every 100ms
 *                Ref Speed =  FAN_SPEED_MIN + LOAD_SPEED + TEMP_STAGE1_SPEED + TEMP_STAGE1_SPEED
 *                + VIN_SPEED
 *                regulate the fan speed by change the the PWM duty
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vFanCtrl(void)
{
	static uint16 u16count = 0;
	uint8 u8Index;

	/*set 1 sec*/
	if (++u16count >= 5)
	{
		u16count = 0;

		/* Module */
		mg_AdjSpeed();


		for (u8Index = 0U; u8Index < FANCTRL_CFG_E_INDEX_COUNT; u8Index++)
		{
			/*Bootlaoder Mode*/
			if (FANCTRL_RTE_Read_B_R_BOOT_MODE() != FALSE)
			{
				mg_u16FanDuty = FANCTRL_CONF_DUTY_BOOT_MODE;
			}

			/* power off control fanSpeed */
			if ((FANCTRL_RTE_Read_B_R_INPUT_OFF() != FALSE)      &&
			    (mg_sFan[u8Index].u16q12SysCmdDuty == 0)
			   )
			{
				mg_u16FanDuty = FANCTRL_CONF_DUTY_AC_OFF;
			}

			Rte_Write_P_uFanDuty(u8Index, mg_u16FanDuty);
			/* command set duty FAN*/
//			(FANCTRL_CFG_CONF[u8Index].vSetFanCtrlPwmDuty)(mg_u16FanDuty);
		}
	}
}

/** *****************************************************************************
 * \brief         Fan Speed calculate, every 10ms
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vFanSpeedCalc(void)
{
	uint8 u8Index;
	static uint8 au8FanFailCnt[FANCTRL_CFG_E_INDEX_COUNT];
	static uint8 au8FanWarnCnt[FANCTRL_CFG_E_INDEX_COUNT];
	static uint8 au8FanOKCnt[FANCTRL_CFG_E_INDEX_COUNT];
	static uint8 u8Cnt;

	u8Cnt++;

	if (49 == u8Cnt)
	{
		u8Cnt = 0;

		for (u8Index = 0U; u8Index < FANCTRL_CFG_E_INDEX_COUNT; u8Index++)
		{
			/* Calculate Real Fan Speed, every 500ms */
			#if 0
			mg_sFan[u8Index].u16Speed = mg_sFan[u8Index].u16Cnt * 30;
			#else /* FanCnt is from Pri */
			mg_sFan[u8Index].u16Speed = RTE_Pri.u16FanCnt[u8Index].u16Val * 30;
			#endif
			/* Reset Fan Speed Count */
			mg_sFan[u8Index].u16Cnt = 0U;

			/* if Input OK, then it will judge fan status, or it will not */
			if ((FALSE != FANCTRL_RTE_Read_B_R_VIN_OK()) && (FALSE != FANCTRL_RTE_Read_B_R_DIO_INPUT_OK()))
			{
				/* Judge the Fan warning */
				if (MG_U16_FAN_WARN_SPEED > mg_sFan[u8Index].u16Speed)
				{
					if (MG_U8_FAN_WARN_SET_DLY < au8FanWarnCnt[u8Index])
					{
						mg_sFan[u8Index].Bits.f0Warn = TRUE;
						au8FanOKCnt[u8Index] = 0U;
					}
					else
					{
						au8FanWarnCnt[u8Index]++;
					}
				}

				/* Judge the Fan fail */
				if (MG_U16_FAN_FAIL_SPEED > mg_sFan[u8Index].u16Speed)
				{
					if (MG_U8_FAN_FAIL_SET_DLY < au8FanFailCnt[u8Index])
					{
						mg_sFan[u8Index].Bits.f1Fail = TRUE;
						au8FanOKCnt[u8Index] = 0U;
					}
					else
					{
						au8FanFailCnt[u8Index]++;
					}
				}

				/* Judge the Fan OK */
				if (MG_U16_FAN_OK_SPEED < mg_sFan[u8Index].u16Speed)
				{
					if (MG_U8_FAN_OK_DLY < au8FanOKCnt[u8Index])
					{
						mg_sFan[u8Index].Bits.f0Warn = FALSE;
						mg_sFan[u8Index].Bits.f1Fail = FALSE;
						au8FanFailCnt[u8Index] = 0U;
						au8FanWarnCnt[u8Index] = 0U;
					}
					else
					{
						au8FanOKCnt[u8Index]++;
					}
				}
			}
		}
	}
}

#if 0 /* FanCnt get from Pri */
/** *****************************************************************************
 * \brief         Fan Speed counter, every 100us or every 200us
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vFanSpeedCnt(void)
{
	static uint16 au8FanSpeedStatus[FANCTRL_CFG_E_INDEX_COUNT];
	static uint16 au8TachoTimerAct[FANCTRL_CFG_E_INDEX_COUNT];
	uint8 u8Index;

	for (u8Index = 0; u8Index < FANCTRL_CFG_E_INDEX_COUNT; u8Index++)
	{
		mg_sFan[u8Index].Bits.f3IoPin = (FANCTRL_CFG_CONF[u8Index].u8ReadPinIoStatus)();

		if (mg_sFan[u8Index].Bits.f3IoPin != au8FanSpeedStatus[u8Index])
		{
			/* > 2 * 0.2 = 0.6 ms to suppress noise */
			if (au8TachoTimerAct[u8Index] >= 2U)
			{
				if (mg_sFan[u8Index].u16Cnt < 0xFFFFu)
				{
					mg_sFan[u8Index].u16Cnt++;
				}

				au8TachoTimerAct[u8Index] = 0;
				au8FanSpeedStatus[u8Index] = mg_sFan[u8Index].Bits.f3IoPin;
			}
			else
			{
				au8TachoTimerAct[u8Index]++;
			}
		}
		else
		{
			if (au8TachoTimerAct[u8Index] > 0)
			{
				au8TachoTimerAct[u8Index]--;
			}
		}
	}
}
#endif
/** *****************************************************************************
 * \brief         Read fan speed
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint16 FANCTRL_u16ReadFanSpeed(uint8 u8Index)
{
	if (u8Index < (uint8)FANCTRL_CFG_E_INDEX_COUNT)
	{
		return mg_sFan[u8Index].u16Speed;
	}
	else
	{
		return 0xFFFFu;
	}
}

/** *****************************************************************************
 * \brief         Read fan control duty
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint16 FANCTRL_u16ReadFanCtrlDuty(uint8 u8Index)
{
	if (u8Index < (uint8)FANCTRL_CFG_E_INDEX_COUNT)
	{
		return mg_sFan[u8Index].u16q12Duty;
	}
	else
	{
		return 0xFFFFu;
	}
}

/** *****************************************************************************
 * \brief         Set fan system control duty
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vSysSetFanCtrlDuty(uint8 u8Index, uint16 u16Duty)
{
	if (u8Index < (uint8)FANCTRL_CFG_E_INDEX_COUNT)
	{
		mg_sFan[u8Index].u16q12SysCmdDuty = u16Duty;
	}
	else
	{
		/* do nothing */
	}
}

/** *****************************************************************************
 * \brief         Read fan Fail bit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 FANCTRL_u8ReadFanBitFail(uint8 u8Index)
{
	if (u8Index < (uint8)FANCTRL_CFG_E_INDEX_COUNT)
	{
		return mg_sFan[u8Index].Bits.f1Fail;
	}
	else
	{
		return 0;
	}
}

void FANCTRL_u8WriteFanBitFail(uint8 u8Index, uint8 u8Value)
{
	if (u8Index < (uint8)FANCTRL_CFG_E_INDEX_COUNT)
	{
		mg_sFan[u8Index].Bits.f1Fail = u8Value;
	}
}
/** *****************************************************************************
 * \brief         Read fan warning bit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 FANCTRL_u8ReadFanBitWarn(uint8 u8Index)
{
	if (u8Index < (uint8)FANCTRL_CFG_E_INDEX_COUNT)
	{
		return mg_sFan[u8Index].Bits.f0Warn;
	}
	else
	{
		return 0;
	}
}

void FANCTRL_u8WriteFanBitWarn(uint8 u8Index, uint8 u8Value)
{
	if (u8Index < (uint8)FANCTRL_CFG_E_INDEX_COUNT)
	{
		mg_sFan[u8Index].Bits.f0Warn = u8Value;
	}
}

/** *****************************************************************************
 * \brief         Read fan Fail bit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 FANCTRL_u8ReadFanBitOvrd(uint8 u8Index)
{
	if (u8Index < (uint8)FANCTRL_CFG_E_INDEX_COUNT)
	{
		return mg_sFan[u8Index].Bits.f2Ovrd;
	}
	else
	{
		return 0;
	}
}

/** *****************************************************************************
 * \brief         Set Fan Block test flag
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void FANCTRL_vSetFanBlockTest(uint8 u8State)
{
	mg_u8IsFanBlockTest = u8State;
}



/** ****************************************************************************
 * \brief  S_Control_fan_speed
 * \param[in]  -
 * \param[out] -
 *
 * \return  -
 *
 **************************************************************************** */
static void mg_AdjSpeed(void)
{
	uint8  u8Index;
	sint32 s32TempDiff;
	sint32 s32AmbTemp;
	uint32 u32PoutV1;
	sint32 s32LoadDiff;
	uint32 u32FanSpeedAdj = 0;
	sint32 s32Dummy;
	static sint16 s16FanSpeedErr = 0u;
	uint16 u16MaxFanSpeed = 0u;
	uint16 u16MinFanDuty = MG_U16_FAN_DUTY_MIN;

	FANCTRL_Rte_Read_R_s32TempDiff(&s32TempDiff);
	FANCTRL_SCFG_vReadAmbTemp(&s32AmbTemp);

	/* control the fan speed according to the tempareture */
	if (s32TempDiff > 0)
	{
		u32FanSpeedAdj = (uint32)((((sint32)MG_U32_FAN_SCALING_FACT_1) * s32TempDiff) + (sint32)MG_S16_FAN_CTRL_SPEED_THR_1);
	}
	else
	{
		u32FanSpeedAdj = (uint32)MG_S16_FAN_CTRL_SPEED_THR_1;
	}

	/* Control the fan accoiding to the load */
	u32PoutV1 = FANCTRL_SCFG_u16ReadPoutV1Avg();
	s32LoadDiff = (sint32)(u32PoutV1) - (sint32)MG_S16_FAN_CTRL_LOAD_THR_0;

	if (s32LoadDiff > 0)
	{
		RTE_u16ComDebug[1] = s32LoadDiff;
		u32FanSpeedAdj += ((uint32)((sint32)MG_U32_FAN_SCALING_FACT_2 * ((sint32)s32LoadDiff))) >> 7u;
	}

	/* If Ambient tempareture less than 5°С and mor than -8°С
	   the fan speed is linear reduction	*/
	if ((s32AmbTemp < 5) && (s32AmbTemp >= -8))
	{
		s32Dummy = ((s32AmbTemp + 8) * 6) * ((sint32)u32FanSpeedAdj);
		s32Dummy += ((sint32)u32FanSpeedAdj) * 51;
		u32FanSpeedAdj = (uint32)s32Dummy;
		u32FanSpeedAdj = u32FanSpeedAdj >> 7;
	}
	/* If Ambient tempareture less than -8°С
	   the fan speed must be 40% above speed */
	else if (s32AmbTemp < -8)
	{
		u32FanSpeedAdj = u32FanSpeedAdj * 51u;
		u32FanSpeedAdj = u32FanSpeedAdj >> 7u;
	}

	/* Limit the MAX fan speed */
	if (u32FanSpeedAdj > MG_S16_FAN_CTRL_SPEED_MAX)
	{
		u32FanSpeedAdj = (uint32)MG_S16_FAN_CTRL_SPEED_MAX;
	}

	RTE_u16ComDebug[0] = u32FanSpeedAdj;

	RTE_u16ComDebug[1] = mg_sFan[0].u16q12SysCmdDuty;
	RTE_u16ComDebug[2] = mg_sFan[1].u16q12SysCmdDuty;

	for (u8Index = 0; u8Index < FANCTRL_CFG_E_INDEX_COUNT; u8Index++)
	{
		if ((FALSE == FANCTRL_RTE_Read_B_R_SYS_UNLOCK()) && (0 == mg_sFan[u8Index].u16q12SysCmdDuty))
		{
			mg_u8IsFanBlockTest = FALSE;
			u16MinFanDuty = MG_U16_FAN_DUTY_MIN;
		}

		/*Check Fan Override*/
		if ((uint32)mg_sFan[u8Index].u16q12SysCmdDuty * ((uint32)MG_S16_FAN_CTRL_SPEED_MAX) > u32FanSpeedAdj * 100u)
		{
			mg_sFan[u8Index].Bits.f2Ovrd = TRUE;
			u32FanSpeedAdj = ((uint32)mg_sFan[u8Index].u16q12SysCmdDuty * ((uint32)MG_S16_FAN_CTRL_SPEED_MAX)) / 100u;
			u16MinFanDuty = 0;
		}
		else
		{
			mg_sFan[u8Index].Bits.f2Ovrd = FALSE;

			if (FALSE != FANCTRL_RTE_Read_B_R_SYS_UNLOCK())
			{
				if (0 != mg_sFan[u8Index].u16q12SysCmdDuty)
				{
					u32FanSpeedAdj = ((uint32)mg_sFan[u8Index].u16q12SysCmdDuty * ((uint32)MG_S16_FAN_CTRL_SPEED_MAX)) / 100u;
					u16MinFanDuty = 0;
				}
			}
			else
			{
				mg_sFan[u8Index].u16q12SysCmdDuty = 0;
				mg_u8IsFanBlockTest = FALSE;
				u16MinFanDuty = MG_U16_FAN_DUTY_MIN;
			}
		}
	}

	/* Select the max Fan speed */
	for (u8Index = 0; u8Index < FANCTRL_CFG_E_INDEX_COUNT; u8Index++)
	{
		if (mg_sFan[u8Index].u16Speed > u16MaxFanSpeed)
		{
			u16MaxFanSpeed = mg_sFan[u8Index].u16Speed;
		}
	}

	/* Step 3: Control the Fan by PWM duty */
	s16FanSpeedErr = (sint16)u32FanSpeedAdj - (sint16)u16MaxFanSpeed;

	/* Fan error > 5000 */
	if (MG_S16_FAN_FAST_FAST_CTRL_VALUE < s16FanSpeedErr)
	{
		mg_u16FanDuty += MG_U8_FAN_REGULATE_FAST_FAST_STEP ;
	}
	/* Fan error > 2000 */
	else if (MG_S16_FAN_FAST_CTRL_VALUE < s16FanSpeedErr)
	{
		mg_u16FanDuty += MG_U8_FAN_REGULATE_FAST_STEP ;
	}
	/* 0 < Fan error < 2000 */
	else if (0 < s16FanSpeedErr)
	{
		mg_u16FanDuty += MG_U8_FAN_REGULATE_SLOW_STEP;
	}
	/* -2000 < Fan error < 0 */
	else if ((-MG_S16_FAN_FAST_CTRL_VALUE) < s16FanSpeedErr)
	{
		if (mg_u16FanDuty >  MG_U8_FAN_REGULATE_SLOW_STEP)
		{
			mg_u16FanDuty -= MG_U8_FAN_REGULATE_SLOW_STEP;
		}
		else
		{
			mg_u16FanDuty = 0;
		}
	}
	/* Fan error < -2000 */
	else
	{
		if (mg_u16FanDuty >  MG_U8_FAN_REGULATE_FAST_STEP)
		{
			mg_u16FanDuty -=  MG_U8_FAN_REGULATE_FAST_STEP;
		}
		else
		{
			mg_u16FanDuty = 0;
		}
	}

	if (FALSE != mg_u8IsFanBlockTest)
	{
		mg_u16FanDuty = 0;
		u16MinFanDuty = 0;
	}

	mg_u16FanDuty = LIMIT(mg_u16FanDuty, u16MinFanDuty, MG_U16_FAN_DUTY_MAX);
}


/*
 * End of file
 */
