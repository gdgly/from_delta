/** *****************************************************************************
 * \file    tempctrl.c
 * \brief   Temperature related routines
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date$
 *  $Author$
 *  $Revision$
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "debug_llc.h"

/* Module header */
#define TEMPCTRL_EXPORT_H
  #include "tempctrl_api.h"
  #include "tempctrl_scb.h"
  #include "tempctrl_cfg.h"
  #include "tempctrl_scfg.h"
  #include "tempctrl_rte.h"
  #include "tempctrl_conf.h"

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/
 
typedef struct
{
  uint16 u161OhmResRaw;
  uint16 u161OhmResAvg;
  uint32 u321OhmResSum;
} TEMPCTRL_sNtc;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
#if MG_NTC_NBR
static TEMPCTRL_sNtc  TEMPCTRL_mg_sNtc[MG_NTC_NBR];
#endif
#if MG_NTC_OTP_MONITORING
static GLOBAL_U_U8BIT TEMPCTRL_mg_uTempStatus;
#endif

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

#if MG_NTC_OTP_MONITORING
#if MG_NTC_NBR > 0
static void TEMPCTRL_vNtc1ResMonitor(void);
#endif
#if MG_NTC_NBR > 1
static void TEMPCTRL_vNtc2ResMonitor(void);
#endif
#if MG_NTC_NBR > 2
static void TEMPCTRL_vNtc3ResMonitor(void);
#endif
#if MG_NTC_NBR > 3
static void TEMPCTRL_vNtc4ResMonitor(void);
#endif
#endif

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TEMPCTRL_vInit(void)
{
  #if MG_NTC_OTP_MONITORING
  /* Init temp status */
  TEMPCTRL_mg_uTempStatus.ALL = 0U;
  #endif
  #if MG_NTC_NBR
  uint8 ui8Index;
  /* Set initial data for NTC's */
  for (ui8Index = 0U; ui8Index < MG_NTC_NBR; ui8Index++)
  {
    TEMPCTRL_mg_sNtc[ui8Index].u161OhmResRaw = 0U;
    TEMPCTRL_mg_sNtc[ui8Index].u321OhmResSum = 0U;
    TEMPCTRL_mg_sNtc[ui8Index].u161OhmResAvg = 890U;
  }
  #endif
}

/** *****************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TEMPCTRL_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         NTC voltage calculation and filter
 *                Repetition time: 1ms
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TEMPCTRL_vNtcVoltAverage(void)
{
  static uint8 u8RmsCtr = 0U;

  #if MG_NTC_NBR > 0
    /* Read data from RTE */
    TEMPCTRL_Rte_Read_R_1Ohm_ResNtc1(&TEMPCTRL_mg_sNtc[0].u161OhmResRaw);
    /* Integrate NTC voltage values */
    TEMPCTRL_mg_sNtc[0].u321OhmResSum += TEMPCTRL_mg_sNtc[0].u161OhmResRaw;
  #endif
  #if MG_NTC_NBR > 1
    /* Read data from RTE */
    TEMPCTRL_Rte_Read_R_1Ohm_ResNtc2(&TEMPCTRL_mg_sNtc[1].u161OhmResRaw);
    /* Integrate NTC voltage values */
    TEMPCTRL_mg_sNtc[1].u321OhmResSum += TEMPCTRL_mg_sNtc[1].u161OhmResRaw;
  #endif
  #if MG_NTC_NBR > 2
    /* Read data from RTE */
    TEMPCTRL_Rte_Read_R_1Ohm_ResNtc3(&TEMPCTRL_mg_sNtc[2].u161OhmResRaw);
    /* Integrate NTC voltage values */
    TEMPCTRL_mg_sNtc[2].u321OhmResSum += TEMPCTRL_mg_sNtc[2].u161OhmResRaw;
  #endif
  #if MG_NTC_NBR > 3
    /* Read data from RTE */
    TEMPCTRL_Rte_Read_R_1Ohm_ResNtc4(&TEMPCTRL_mg_sNtc[3].u161OhmResRaw);
    /* Integrate NTC voltage values */
    TEMPCTRL_mg_sNtc[3].u321OhmResSum += TEMPCTRL_mg_sNtc[3].u161OhmResRaw;
  #endif

  /*******************************************************************************
   * Average NTC voltage
   *******************************************************************************/
  /* Count up RMS average counter */
  u8RmsCtr++;
  /* Wait until RMS average counter reaches the defined limit */
  if (MG_U8_AVG_CTR <= u8RmsCtr)
  {
    #if MG_NTC_NBR > 0
    /* Temperature averaging */
    TEMPCTRL_mg_sNtc[0].u161OhmResAvg = (TEMPCTRL_mg_sNtc[0].u321OhmResSum) / u8RmsCtr;
    TEMPCTRL_mg_sNtc[0].u321OhmResSum = 0U;
    /* Write data to RTE */
    TEMPCTRL_Rte_Write_P_1Ohm_ResNtc1Avg(TEMPCTRL_mg_sNtc[0].u161OhmResAvg);
    #endif
    #if MG_NTC_NBR > 1
    /* Temperature averaging */
    TEMPCTRL_mg_sNtc[1].u161OhmResAvg = (TEMPCTRL_mg_sNtc[1].u321OhmResSum) / u8RmsCtr;
    TEMPCTRL_mg_sNtc[1].u321OhmResSum = 0U;
    /* Write data to RTE */
    TEMPCTRL_Rte_Write_P_1Ohm_ResNtc2Avg(TEMPCTRL_mg_sNtc[1].u161OhmResAvg);
    #endif
    #if MG_NTC_NBR > 2
    /* Temperature averaging */
    TEMPCTRL_mg_sNtc[2].u161OhmResAvg = (TEMPCTRL_mg_sNtc[2].u321OhmResSum) / u8RmsCtr;
    TEMPCTRL_mg_sNtc[2].u321OhmResSum = 0U;
    /* Write data to RTE */
    TEMPCTRL_Rte_Write_P_1Ohm_ResNtc3Avg(TEMPCTRL_mg_sNtc[2].u161OhmResAvg);
    #endif
    #if MG_NTC_NBR > 3
    /* Temperature averaging */
    TEMPCTRL_mg_sNtc[3].u161OhmResAvg = (TEMPCTRL_mg_sNtc[3].u321OhmResSum) / u8RmsCtr;
    TEMPCTRL_mg_sNtc[3].u321OhmResSum = 0U;
    /* Write data to RTE */
    TEMPCTRL_Rte_Write_P_1Ohm_ResNtc4Avg(TEMPCTRL_mg_sNtc[3].u161OhmResAvg);
    #endif
    /* Reset counter */
    u8RmsCtr = 0U;
  }
}

/** *****************************************************************************
 * \brief         NTC OTP monitor
 *                Repetition time: 100ms
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TEMPCTRL_vNtcOtMonitor(void)
{
#if MG_NTC_OTP_MONITORING
  #if MG_NTC_NBR > 0
    TEMPCTRL_vNtc1ResMonitor();
  #endif
  #if MG_NTC_NBR > 1
    TEMPCTRL_vNtc2ResMonitor();
  #endif
  #if MG_NTC_NBR > 2
    TEMPCTRL_vNtc3ResMonitor();
  #endif
  #if MG_NTC_NBR > 3
    TEMPCTRL_vNtc4ResMonitor();
  #endif

  #if (!DEBUG_SECTION_OTP_DISABLE)
  /* If OT not disabled */
  if (!Rte_Read_R_B_OT_DISABLED)
  {
    if ((MG_B_NTC_1_OT) || (MG_B_NTC_2_OT) || (MG_B_NTC_3_OT) || (MG_B_NTC_4_OT))
    {
      /* Set OT flag */
      TEMPCTRL_Rte_Write_P_B_PSU_OT(TRUE);
    }
    else
    {
      /* Reset OT flag */
      TEMPCTRL_Rte_Write_P_B_PSU_OT(FALSE);
    }
  }
  else
  {
    /* Reset OT flag */
    TEMPCTRL_Rte_Write_P_B_PSU_OT(FALSE);
  }
  #endif
#endif
}

#if MG_NTC_OTP_MONITORING
/** *****************************************************************************
 * \brief         NTC 1 monitor
 *                Repetition time: 100ms
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
#if MG_NTC_NBR > 0
void TEMPCTRL_vNtc1ResMonitor(void)
{
  static uint16 u16OtDlyCnt = 0U;
  static uint16 u16OtwDlyCnt = 0U;

  /* If NTC average voltage lower than OTP voltage (OT) */
  if (MG_U16_1Ohm_NTC_1_OT_SETPOINT > TEMPCTRL_mg_sNtc[0].u161OhmResAvg)
  {
    /* OTP delay */
    if (MG_U16_100ms_NTC_1_OTP_DLY < u16OtDlyCnt)
    {
      /* Set OTP flag */
      MG_B_NTC_1_OT = TRUE;
    }
    else
    {
      /* Count up delay counter */
      u16OtDlyCnt++;
    }
  }
  /* If NTC average voltage higher than OTP recover voltage (no OT) */
  else if (MG_U16_1Ohm_NTC_1_OT_RESETPOINT < TEMPCTRL_mg_sNtc[0].u161OhmResAvg)
  {
    /* OTP reset delay  */
    if(0U < u16OtDlyCnt)
    {
      /* Count down delay counter */
      u16OtDlyCnt--;
    }
    else
    {
      /* Reset OT flag */
      MG_B_NTC_1_OT = FALSE;
    }
  }

  /* If NTC average voltage lower than OTW voltage (OTW) */
  if (MG_U16_1Ohm_NTC_1_OTW_SETPOINT > TEMPCTRL_mg_sNtc[0].u161OhmResAvg)
  {
    /* OTW delay */
    if (MG_U16_100ms_NTC_1_OTW_DLY < u16OtwDlyCnt)
    {
      /* Set OTW flag */
      MG_B_NTC_1_OTW = TRUE;
    }
    else
    {
      /* Count up delay counter */
      u16OtwDlyCnt++;
    }
  }
  /* If NTC average voltage higher than OTW recover voltage (no OTW) */
  else if (MG_U16_1Ohm_NTC_1_OTW_RESETPOINT < TEMPCTRL_mg_sNtc[0].u161OhmResAvg)
  {
    /* OTP reset delay  */
    if(0U < u16OtwDlyCnt)
    {
      /* Count down delay counter */
      u16OtwDlyCnt--;
    }
    else
    {
      /* Reset OTW flags */
      MG_B_NTC_1_OTW = FALSE;
    }
  }

  /* Write data to RTE */
  TEMPCTRL_Rte_Write_P_B_NTC_1_OTW(MG_B_NTC_1_OTW);
  TEMPCTRL_Rte_Write_P_B_NTC_1_OT(MG_B_NTC_1_OT);
}
#endif

/** *****************************************************************************
 * \brief         NTC 2 monitor
 *                Repetition time: 100ms
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
#if MG_NTC_NBR > 1
void TEMPCTRL_vNtc2ResMonitor(void)
{
  static uint16 u16OtDlyCnt = 0U;
  static uint16 u16OtwDlyCnt = 0U;

  /* If NTC average voltage lower than OTP voltage (OT) */
  if (MG_U16_1Ohm_NTC_2_OT_SETPOINT > TEMPCTRL_mg_sNtc[1].u161OhmResAvg)
  {
    /* OTP delay */
    if (MG_U16_100ms_NTC_2_OTP_DLY < u16OtDlyCnt)
    {
      /* Set OTP flag */
      MG_B_NTC_2_OT = TRUE;
    }
    else
    {
      /* Count up delay counter */
      u16OtDlyCnt++;
    }
  }
  /* If NTC average voltage higher than OTP recover voltage (no OT) */
  else if (MG_U16_1Ohm_NTC_2_OT_RESETPOINT < TEMPCTRL_mg_sNtc[1].u161OhmResAvg)
  {
    /* OTP reset delay  */
    if(0U < u16OtDlyCnt)
    {
      /* Count down delay counter */
      u16OtDlyCnt--;
    }
    else
    {
      /* Reset OT flag */
      MG_B_NTC_2_OT = FALSE;
    }
  }

  /* If NTC average voltage lower than OTW voltage (OTW) */
  if (MG_U16_1Ohm_NTC_2_OTW_SETPOINT > TEMPCTRL_mg_sNtc[1].u161OhmResAvg)
  {
    /* OTW delay */
    if (MG_U16_100ms_NTC_2_OTW_DLY < u16OtwDlyCnt)
    {
      /* Set OTW flag */
      MG_B_NTC_2_OTW = TRUE;
    }
    else
    {
      /* Count up delay counter */
      u16OtwDlyCnt++;
    }
  }
  /* If NTC average voltage higher than OTW recover voltage (no OTW) */
  else if (MG_U16_1Ohm_NTC_2_OTW_RESETPOINT < TEMPCTRL_mg_sNtc[1].u161OhmResAvg)
  {
    /* OTP reset delay  */
    if(0U < u16OtwDlyCnt)
    {
      /* Count down delay counter */
      u16OtwDlyCnt--;
    }
    else
    {
      /* Reset OTW flags */
      MG_B_NTC_2_OTW = FALSE;
    }
  }

  /* Write data to RTE */
  TEMPCTRL_Rte_Write_P_B_NTC_2_OTW(MG_B_NTC_2_OTW);
  TEMPCTRL_Rte_Write_P_B_NTC_2_OT(MG_B_NTC_2_OT);
}
#endif

/** *****************************************************************************
 * \brief         NTC 3 monitor
 *                Repetition time: 100ms
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
#if MG_NTC_NBR > 2
void TEMPCTRL_vNtc3ResMonitor(void)
{
  static uint16 u16OtDlyCnt = 0U;
  static uint16 u16OtwDlyCnt = 0U;

  /* If NTC average voltage lower than OTP voltage (OT) */
  if (MG_U16_1Ohm_NTC_3_OT_SETPOINT > TEMPCTRL_mg_sNtc[2].u161OhmResAvg)
  {
    /* OTP delay */
    if (MG_U16_100ms_NTC_3_OTP_DLY < u16OtDlyCnt)
    {
      /* Set OTP flag */
      MG_B_NTC_3_OT = TRUE;
    }
    else
    {
      /* Count up delay counter */
      u16OtDlyCnt++;
    }
  }
  /* If NTC average voltage higher than OTP recover voltage (no OT) */
  else if (MG_U16_1Ohm_NTC_3_OT_RESETPOINT < TEMPCTRL_mg_sNtc[2].u161OhmResAvg)
  {
    /* OTP reset delay  */
    if(0U < u16OtDlyCnt)
    {
      /* Count down delay counter */
      u16OtDlyCnt--;
    }
    else
    {
      /* Reset OT flag */
      MG_B_NTC_3_OT = FALSE;
    }
  }

  /* If NTC average voltage lower than OTW voltage (OTW) */
  if (MG_U16_1Ohm_NTC_3_OTW_SETPOINT > TEMPCTRL_mg_sNtc[2].u161OhmResAvg)
  {
    /* OTW delay */
    if (MG_U16_100ms_NTC_3_OTW_DLY < u16OtwDlyCnt)
    {
      /* Set OTW flag */
      MG_B_NTC_3_OTW = TRUE;
    }
    else
    {
      /* Count up delay counter */
      u16OtwDlyCnt++;
    }
  }
  /* If NTC average voltage higher than OTW recover voltage (no OTW) */
  else if (MG_U16_1Ohm_NTC_3_OTW_RESETPOINT < TEMPCTRL_mg_sNtc[2].u161OhmResAvg)
  {
    /* OTP reset delay  */
    if(0U < u16OtwDlyCnt)
    {
      /* Count down delay counter */
      u16OtwDlyCnt--;
    }
    else
    {
      /* Reset OTW flags */
      MG_B_NTC_3_OTW = FALSE;
    }
  }

  /* Write data to RTE */
  TEMPCTRL_Rte_Write_P_B_NTC_3_OTW(MG_B_NTC_3_OTW);
  TEMPCTRL_Rte_Write_P_B_NTC_3_OT(MG_B_NTC_3_OT);
}
#endif

/** *****************************************************************************
 * \brief         NTC 4 monitor
 *                Repetition time: 100ms
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
#if MG_NTC_NBR > 3
void TEMPCTRL_vNtc4ResMonitor(void)
{
  static uint16 u16OtDlyCnt = 0U;
  static uint16 u16OtwDlyCnt = 0U;

  /* If NTC average voltage lower than OTP voltage (OT) */
  if (MG_U16_1Ohm_NTC_4_OT_SETPOINT > TEMPCTRL_mg_sNtc[3].u161OhmResAvg)
  {
    /* OTP delay */
    if (MG_U16_100ms_NTC_4_OTP_DLY < u16OtDlyCnt)
    {
      /* Set OTP flag */
      MG_B_NTC_4_OT = TRUE;
    }
    else
    {
      /* Count up delay counter */
      u16OtDlyCnt++;
    }
  }
  /* If NTC average voltage higher than OTP recover voltage (no OT) */
  else if (MG_U16_1Ohm_NTC_4_OT_RESETPOINT < TEMPCTRL_mg_sNtc[3].u161OhmResAvg)
  {
    /* OTP reset delay  */
    if(0U < u16OtDlyCnt)
    {
      /* Count down delay counter */
      u16OtDlyCnt--;
    }
    else
    {
      /* Reset OT flag */
      MG_B_NTC_4_OT = FALSE;
    }
  }

  /* If NTC average voltage lower than OTW voltage (OTW) */
  if (MG_U16_1Ohm_NTC_4_OTW_SETPOINT > TEMPCTRL_mg_sNtc[3].u161OhmResAvg)
  {
    /* OTW delay */
    if (MG_U16_100ms_NTC_4_OTW_DLY < u16OtwDlyCnt)
    {
      /* Set OTW flag */
      MG_B_NTC_4_OTW = TRUE;
    }
    else
    {
      /* Count up delay counter */
      u16OtwDlyCnt++;
    }
  }
  /* If NTC average voltage higher than OTW recover voltage (no OTW) */
  else if (MG_U16_1Ohm_NTC_4_OTW_RESETPOINT < TEMPCTRL_mg_sNtc[3].u161OhmResAvg)
  {
    /* OTP reset delay  */
    if(0U < u16OtwDlyCnt)
    {
      /* Count down delay counter */
      u16OtwDlyCnt--;
    }
    else
    {
      /* Reset OTW flags */
      MG_B_NTC_4_OTW = FALSE;
    }
  }

  /* Write data to RTE */
  TEMPCTRL_Rte_Write_P_B_NTC_4_OTW(MG_B_NTC_4_OTW);
  TEMPCTRL_Rte_Write_P_B_NTC_4_OT(MG_B_NTC_4_OT);
}
#endif
#endif


/*
 * End of file
 */
