/*******************************************************************************
 * \file    fanctrl_rte.h
 * \brief   RTE interface for fanctrl.c
 *
 * \section AUTHOR
 *    1. Fred Ji
 *
 * \section SVN
 *  $Date: 2018-11-09 11:10:05 +0800 (Fri, 09 Nov 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 115 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef FANCTRL_RTE_H
#define FANCTRL_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif
		
#include "rte.h"
#include "tempctrl_cfg.h"

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
#define MG_RTE_MODULE               1U
/***********************************************
 * Input  
**********************************************/
/* Flags */
#define MG_B_FAN_CTRL_SYS_UNLOCK    1      /* 1 = Fan ctrl is unlock from system and can be set any speed */           

/* Variables */
#define MG_U16Q12_VIN_AVG           ((uint16)U32Q12(200.0F / RTE_F32_VIN_MAX))

#define FANCTRL_RTE_S16_TEMP1             FANCTRL_SCFG_s16ReadAmbTemp()
#define FANCTRL_RTE_S16_TEMP2             FANCTRL_SCFG_s16ReadPriPfc()
#define FANCTRL_RTE_S16_TEMP3             FANCTRL_SCFG_s16ReadPriLlc()
#define FANCTRL_RTE_S16_TEMP4             FANCTRL_SCFG_s16ReadSecRecdiode()
#define FANCTRL_RTE_S16_TEMP5							FANCTRL_SCFG_s16ReadOutTemp()

#define FANCTRL_RTE_S16_TEMP1_OFFSET      ((sint16)30)
#define FANCTRL_RTE_S16_TEMP2_OFFSET      ((sint16)70+5)
#define FANCTRL_RTE_S16_TEMP3_OFFSET      ((sint16)80+5)
#define FANCTRL_RTE_S16_TEMP4_OFFSET      ((sint16)80+5)
#define FANCTRL_RTE_S16_TEMP5_OFFSET      ((sint16)30)

#define FANCTRL_RTE_S16_TEMP1_DIFF        (FANCTRL_RTE_S16_TEMP1 - FANCTRL_RTE_S16_TEMP1_OFFSET)
#define FANCTRL_RTE_S16_TEMP2_DIFF        (FANCTRL_RTE_S16_TEMP2 - FANCTRL_RTE_S16_TEMP2_OFFSET)
#define FANCTRL_RTE_S16_TEMP3_DIFF        (FANCTRL_RTE_S16_TEMP3 - FANCTRL_RTE_S16_TEMP3_OFFSET)
#define FANCTRL_RTE_S16_TEMP4_DIFF        (FANCTRL_RTE_S16_TEMP4 - FANCTRL_RTE_S16_TEMP4_OFFSET)
#define FANCTRL_RTE_S16_TEMP5_DIFF        (FANCTRL_RTE_S16_TEMP5 - FANCTRL_RTE_S16_TEMP5_OFFSET)

#define FANCTRL_RTE_S16_TEMP_DIFF_MAX     MAX((MAX(MAX(MAX(FANCTRL_RTE_S16_TEMP1_DIFF,FANCTRL_RTE_S16_TEMP2_DIFF),FANCTRL_RTE_S16_TEMP3_DIFF),FANCTRL_RTE_S16_TEMP4_DIFF)),FANCTRL_RTE_S16_TEMP5_DIFF)

#define RTE_Read_B_R_BULK_OK             (RTE_B_PRI_BULK_OK)
#define RTE_Read_B_R_VIN_OK              (RTE_B_PRI_VIN_OK)
#define RTE_Read_B_R_DIO_INPUT_OK        (RTE_B_DIO_VIN_OK_ACTIVE) 

#define RTE_Read_B_R_BOOT_MODE           (PMBUS_uSysStatu1.Bits.BOOT_RESET_FLAG)
#define RTE_Read_B_R_INPUT_OFF           (RTE_B_COM_NO_VIN)
#define RTE_Read_B_R_SYS_UNLOCK          (PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)

#define Rte_Read_R_u32PoutV1Mul128(var)       ((**var) = PMBUS_tData.u32Pout_V1_Mul_128.u32Val)
#define Rte_Read_R_s32AmbTemp(var)            ((**var) = TEMPCTRL_mg_sTmp[MG_U16_NTC_NBR_COM_INLET].s16Temperature) 
#define Rte_Read_R_s32TempDiff(var)           ((**var) = (sint32)FANCTRL_RTE_S16_TEMP_DIFF_MAX)
/***********************************************
 * Output
 **********************************************/
/* Flags */
/* Registers */
#define Rte_Write_P_uFanDuty(index,var)         (RTE_uFanDuty[index].s16Val = (var))
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
SINLINE uint8 FANCTRL_RTE_Read_B_R_BULK_OK(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_BULK_OK;
	#endif
}

SINLINE uint8 FANCTRL_RTE_Read_B_R_VIN_OK(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_VIN_OK;
	#endif
}

SINLINE uint8 FANCTRL_RTE_Read_B_R_DIO_INPUT_OK(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_DIO_INPUT_OK;
	#endif
}

SINLINE uint8 FANCTRL_RTE_Read_B_R_BOOT_MODE(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_BOOT_MODE;
	#endif
}

SINLINE uint8 FANCTRL_RTE_Read_B_R_INPUT_OFF(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_INPUT_OFF;
	#endif
}

SINLINE uint8 FANCTRL_RTE_Read_B_R_SYS_UNLOCK(void)
{
  #if MG_RTE_MODULE
	return RTE_Read_B_R_SYS_UNLOCK;
	#endif
}


SINLINE void FANCTRL_Rte_Read_R_u32PoutV1Mul128(uint32 *var)
{
  #if MG_RTE_MODULE
	Rte_Read_R_u32PoutV1Mul128(&var);
	#endif
}

SINLINE void FANCTRL_Rte_Read_R_s32TempDiff(sint32 *var)
{
  #if MG_RTE_MODULE
	Rte_Read_R_s32TempDiff(&var);
	#endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* FANCTRL_RTE_H */


/*
 * End of file
 */
