/*******************************************************************************
 * \file    tempctrl_rte.h
 * \brief   RTE interface for tempctrl.c
 *
 * \section AUTHOR
 *    1. Fred Ji
 *
 * \section SVN
 *  $Date: 2019-03-01 14:35:06 +0800 (Fri, 01 Mar 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 145 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef TEMPCTRL_RTE_H
#define TEMPCTRL_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif

#include "rte.h"
/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
static uint16 mg_u16Ret;

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/
 #define MG_RTE_MODULE           1
/***********************************************
 * Input
 **********************************************/
/* Flags */
#define Rte_Read_B_R_DISABLE_OT                (RTE_uFunctionCtrl.Bits.f0)

/* Registers */

#define Rte_Read_R_u161mVPfcNtc(var)           ((*var) = RTE_Pri.u16PfcNtcAdcAvg.u16Val)	
#define Rte_Read_R_u161mVSrNtc(var)            ((*var) = RTE_Sec.u161mVSrNtcAvg.u16Val)
#define Rte_Read_R_u161mVOringNtc(var)         ((*var) = RTE_Sec.u161mVOringNtcAvg.u16Val)
#define Rte_Read_R_u161mVLlcNtc(var)           ((*var) = RTE_Pri.u16LlcNtcAdcAvg.u16Val)	

#define Rte_Read_R_u8TempTestIndex(var)        ((**var) = RTE_u8TempTestIndex)	
#define Rte_Read_R_s16TempTestValue(var,index) ((**var) = RTE_s16TempTest[index])	
#define Rte_Read_R_s16OtWarning(var)           ((**var) = RTE_s16OtWarning)

#define RTE_au16q12AdcResult                    RTE_au16q12AdcResult

/***********************************************
 * Output
 **********************************************/

/* Flags */


/* Variables */
#define RTE_TempOtwStatus          RTE_TempOtwStatus
#define RTE_TempOtpStatus          RTE_TempOtpStatus

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
SINLINE uint8 TEMPCTRL_Rte_Read_B_R_DISABLE_OT(void)
{
  #if MG_RTE_MODULE
	return Rte_Read_B_R_DISABLE_OT;
  #endif
}
SINLINE uint16 TEMPCTRL_Rte_Read_R_u161mVSrNtc(void)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u161mVSrNtc(&mg_u16Ret);
  #endif
  return mg_u16Ret;
}
SINLINE uint16 TEMPCTRL_Rte_Read_R_u161mVOringNtc(void)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u161mVOringNtc(&mg_u16Ret);
  #endif
  return mg_u16Ret;
}
SINLINE uint16 TEMPCTRL_Rte_Read_R_u161mVPfcNtc(void)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u161mVPfcNtc(&mg_u16Ret);
  #endif
  return mg_u16Ret;
}
SINLINE uint16 TEMPCTRL_Rte_Read_R_u161mVLlcNtc(void)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u161mVLlcNtc(&mg_u16Ret);
  #endif
  return mg_u16Ret;
}
SINLINE void TEMPCTRL_Rte_Read_R_u8TempTestIndex(uint8 *u8data)
{
  #if MG_RTE_MODULE
  Rte_Read_R_u8TempTestIndex(&u8data);
  #endif
}
SINLINE void TEMPCTRL_Rte_Read_R_s16TempTestValue(sint16 *s16Data,uint8 u8data)
{
  #if MG_RTE_MODULE
  Rte_Read_R_s16TempTestValue(&s16Data,u8data);
  #endif
}
SINLINE void TEMPCTRL_Rte_Read_R_u16OtWarning(sint16 *var)
{
  #if MG_RTE_MODULE
  Rte_Read_R_s16OtWarning(&var);
  #endif
}

#ifdef __cplusplus
  }
#endif
#endif  /* TEMPCTRL_RTE_H */

  
/*
 * End of file
 */
