/** *****************************************************************************
 * \file    tmctrl.c
 * \brief   LLC timing control
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
#define TMCTRL_EXPORT_H
  #include "tmctrl_api.h"
  #include "tmctrl_scb.h"
  #include "tmctrl_cfg.h"
  #include "tmctrl_scfg.h"
  #include "tmctrl_rte.h"
  #include "tmctrl_conf.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static uint8 mg_u8LlcCtrlState;
static GLOBAL_U_U8BIT TMCTRL_mg_uTmStatus;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

void TMCTRL_vGpioStateHandle(void);

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
void TMCTRL_vInit(void)
{
  mg_u8LlcCtrlState = MG_LLC_INIT;
  TMCTRL_mg_uTmStatus.ALL = 0;
  /* PWM disable by hardware */
  TMCTRL_Write_P_B_PORT_PWM_ON_rte(FALSE);
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
void TMCTRL_vDeInit(void)
{
  /* PWM disable by hardware */
  TMCTRL_Write_P_B_PORT_PWM_ON_rte(FALSE);
}

/** *****************************************************************************
 * \brief         LLC control on/off timing
 *                INIT: Init variables and wait for delay passed
 *                LLC_IDLE: Check turn on conditions
 *                LLC_ON: LLC on, check operation conditions
 *                LLC_OFF: LLC off
 *                Repetition time: 200us
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TMCTRL_vLlcCtrl(void)
{
  /* Initialize variables */
  static uint16 u16LlcStartDlyCtr = MG_U16_LLC_RESTART_DLY - MG_U16_LLC_START_DLY;
  static uint16 u16LlcStartUpCtr = 0U;
  #if MG_SYNC_START_UP
  static sint16 u16LlcSyncCtr = 0U;
  static sint16 u16LlcSyncMasterCtr = 0U;
  #endif

  /* Judge the GPIO states for the timing control */
  TMCTRL_vGpioStateHandle();

  /*******************************************************************************
   * State machine
   *******************************************************************************/
  switch (mg_u8LlcCtrlState) 
  {
    /*******************************************************************************
     * Init
     * Description: Keep LLC off; wait for start up delay passed
     *******************************************************************************/
    case MG_LLC_INIT:
    {
      /* PWM disable by hardware */
      TMCTRL_Write_P_B_PORT_PWM_ON_rte(FALSE);
      /* Ishare disabled */
      TMCTRL_Write_P_B_PORT_ISHARE_ON_rte(FALSE);
      /* ORING disabled */
      TMCTRL_Write_P_PORT_ORING_EN_rte(FALSE);
      /* LLC not in stand-by */
      MG_B_LLC_STANDBY = FALSE;
      /* LLC is not enabled */
      MG_B_LLC_EN = FALSE;

      /* Wait for start up delay passed */
      if (MG_U16_LLC_RESTART_DLY < u16LlcStartDlyCtr) 
      {
        /* Go to LLC IDLE state */
        mg_u8LlcCtrlState = MG_LLC_IDLE;
        /* Reset start-up counter */
        u16LlcStartDlyCtr = 0U;
      }
      else 
      {
        /* Count up start delay */
        u16LlcStartDlyCtr++;
      }
      break;
    }

    /*******************************************************************************
     * LLC_IDLE
     * Description: Check for LLC turn on
     *******************************************************************************/
    case MG_LLC_IDLE:
    {
      /* If fault reset or Vin lost */
      if (Rte_Read_R_B_LLC_FAULT_CLR || Rte_Read_R_B_PRIM_VIN_LOST) 
      {
        /* Set GPIO OVP clear */
        TMCTRL_Write_P_B_PORT_OVP_CLR_rte(TRUE);
        /* Reset all latched faults */
        TMCTRL_Write_P_B_LLC_OV_LATCH_CLR_rte(TRUE);
        TMCTRL_Write_P_B_LLC_UV_LATCH_CLR_rte(TRUE);
        TMCTRL_Write_P_B_LLC_OC_LATCH_CLR_rte(TRUE);
        TMCTRL_Write_P_B_LLC_OPP_LATCH_CLR_rte(TRUE);
        /* Reset LLC start up counter */
        u16LlcStartUpCtr = 0U;
      }

      /* Check the restart counter and the restart conditions */
      if ((MG_U16_LLC_RESTART_CTR > (sint16)u16LlcStartUpCtr) && (Rte_Read_R_B_LLC_OCP || Rte_Read_R_B_LLC_UVP))
      {
        /* Reset flags */
        TMCTRL_Write_P_B_LLC_UV_LATCH_CLR_rte(TRUE);
        TMCTRL_Write_P_B_LLC_OC_LATCH_CLR_rte(TRUE);
        /* Increase start-up counter */
        u16LlcStartUpCtr++;
      }

      /* Check LLC enable conditions */
      if (
           (FALSE == MG_B_LLC_HALT)
        && (TRUE == MG_B_PRIM_BULK_OK)
        && (FALSE == Rte_Read_R_B_LLC_OCP)
        && (FALSE == Rte_Read_R_B_LLC_OPP)
        && (FALSE == Rte_Read_R_B_LLC_UVP)
        && (FALSE == Rte_Read_R_B_LLC_OVP)

//        && (FALSE == Rte_Read_R_B_PRIM_VIN_LOST)
//        && (TRUE == MG_B_LLC_SWITCH_EN)
//        && (FALSE == Rte_Read_R_B_LLC_FAN_FAIL_1)
//        && (FALSE == Rte_Read_R_B_LLC_FAN_FAIL_2)
//        && (FALSE == Rte_Read_R_B_LLC_OT) 
         )
      {
        /* Go to LLC ON state */
        mg_u8LlcCtrlState = MG_LLC_ON;
        /* Reset latch clears to IDLE */
        TMCTRL_Write_P_B_PORT_OVP_CLR_rte(FALSE);
        TMCTRL_Write_P_B_LLC_OV_LATCH_CLR_rte(FALSE);
        TMCTRL_Write_P_B_LLC_UV_LATCH_CLR_rte(FALSE);
        TMCTRL_Write_P_B_LLC_OC_LATCH_CLR_rte(FALSE);
        TMCTRL_Write_P_B_LLC_OPP_LATCH_CLR_rte(FALSE);
      }
      break;
    }

    /*******************************************************************************
     * LLC_ON
     * Description: Turn on LLC control
     *******************************************************************************/
    case MG_LLC_ON:
    {
      /* Check LLC okay conditions */
      if (
           (FALSE == MG_B_LLC_HALT)
        && (TRUE == MG_B_PRIM_BULK_OK)
        && (FALSE == Rte_Read_R_B_LLC_OCP)
        && (FALSE == Rte_Read_R_B_LLC_UVP)
        && (FALSE == Rte_Read_R_B_LLC_OPP)
        && (FALSE == Rte_Read_R_B_LLC_OVP)
//        && (TRUE == MG_B_LLC_SWITCH_EN)
//        && (FALSE == Rte_Read_R_B_LLC_FAN_FAIL_1)
//        && (FALSE == Rte_Read_R_B_LLC_FAN_FAIL_2)
//        && (FALSE == Rte_Read_R_B_LLC_OT)
         )
      {
        #if (!LLC_ALWAYS_OFF)
        /* PWM enable by hardware */
        TMCTRL_Write_P_B_PORT_PWM_ON_rte(TRUE);
        #endif
        /* Ishare enabled */
        TMCTRL_Write_P_B_PORT_ISHARE_ON_rte(TRUE);
        /* ORING enabled */
        TMCTRL_Write_P_PORT_ORING_EN_rte(TRUE);
        /* LLC in stand-by */
        MG_B_LLC_STANDBY = TRUE;
        /* Check synced start-up flag */
        if (TRUE == Rte_Read_R_B_LLC_SYNC_START_UP)
        {
          /* LLC is enabled */
          MG_B_LLC_EN = TRUE;
        }
      }
      /* Any fault case, shut down LLC */
      else 
      {
        /* PWM disable by hardware */
        TMCTRL_Write_P_B_PORT_PWM_ON_rte(FALSE);
        /* Ishare disabled */
        TMCTRL_Write_P_B_PORT_ISHARE_ON_rte(FALSE);
        /* ORING disabled */
        TMCTRL_Write_P_PORT_ORING_EN_rte(FALSE);
        /* LLC not in stand-by */
        MG_B_LLC_STANDBY = FALSE;
        /* Disable LLC */
        MG_B_LLC_EN = FALSE;
        /* Go to LLC OFF state */
        mg_u8LlcCtrlState = MG_LLC_OFF;
      }
      break;
    }

    /*******************************************************************************
     * LLC_OFF
     * Description: Shutdown LLC
     *******************************************************************************/
    case MG_LLC_OFF:
    {
      /* PWM disable by hardware */
      TMCTRL_Write_P_B_PORT_PWM_ON_rte(FALSE);
      /* Ishare disabled */
      TMCTRL_Write_P_B_PORT_ISHARE_ON_rte(FALSE);
      /* ORING disabled */
      TMCTRL_Write_P_PORT_ORING_EN_rte(FALSE);
      /* LLC is not enabled */
      MG_B_LLC_EN = FALSE;
      /* Go back to LLC INIT state */
      mg_u8LlcCtrlState = MG_LLC_INIT;
      break;
    }

    /*******************************************************************************
     * Default case
     * Description: Default go to INIT state
     *******************************************************************************/
    default:
    {
      /* Go back to LLC INIT state */
      mg_u8LlcCtrlState = MG_LLC_INIT;
      break;
    }
  }

  /* Write RTE variables */
  TMCTRL_Write_P_B_LLC_EN_rte(MG_B_LLC_EN);
  TMCTRL_Write_P_B_LLC_STANDBY_rte(MG_B_LLC_STANDBY);  
}

/*******************************************************************************
 * Local functions (privat for module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         GPIO state judgement
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TMCTRL_vGpioStateHandle(void)
{
  static sint16 u16LlcEnableCtr = 0U;
  static sint16 u16LlcDisableCtr = 0U;
  static sint16 u16LlcEnableOutCtr = 0U;
  static sint16 u16LlcDisableOutCtr = 0U;
  static sint16 u16LlcBulkOkCtr = 0U;
  static sint16 u16LlcBulkFailCtr = 0U;

  /*******************************************************************************
   * PSU HALT signal
   *******************************************************************************/
  /* LLC disabled at HIGH */
  if (Rte_Read_R_B_PORT_LLC_HALT || Rte_Read_R_B_LLC_COM_HALT)
  {
    /* Reset enable counter */
    u16LlcEnableCtr = 0U;
    /* Check if disable delay passed */
    if (MG_U16_LLC_HALT_DLY < u16LlcDisableCtr) 
    {
      /* PSU OFF */
      MG_B_LLC_HALT = TRUE;
    }
    else
    {
      u16LlcDisableCtr++; 
    }
  }
  /* LLC enabled at LOW */
  else
  {
    /* Reset disable counter */
    u16LlcDisableCtr = 0U;
    /* Check if enable delay passed */
    if (MG_U16_LLC_ENABLE_DLY < u16LlcEnableCtr) 
    {
      /* PSU ON */
      MG_B_LLC_HALT = FALSE;
    }
    else 
    {
      u16LlcEnableCtr++; 
    }
  }

  /*******************************************************************************
   * PSU switch disable/enable
   *******************************************************************************/
  /* LLC disabled at LOW */
  if (!Rte_Read_R_B_PORT_LLC_SWITCH_EN)
  {
    /* Reset enable counter */
    u16LlcEnableOutCtr = 0U;
    /* Check if disable delay passed */
    if (MG_U16_LLC_SWITCH_DIS_DLY < u16LlcDisableOutCtr) 
    {
      /* PSU OFF */
      MG_B_LLC_SWITCH_EN = FALSE;
    }
    else 
    {
      u16LlcDisableOutCtr++; 
    }
  }
  /* LLC output enabled at HIGH */
  else
  {
    /* Reset disable counter */
    u16LlcDisableOutCtr = 0U;
    /* Check if enable delay passed */
    if (MG_U16_LLC_SWITCH_EN_DLY < u16LlcEnableOutCtr) 
    { 
      /* PSU ON */
      MG_B_LLC_SWITCH_EN = TRUE;
    }
    else 
    { 
      u16LlcEnableOutCtr++; 
    }
  }

  /*******************************************************************************
   * Bulk voltage okay signal
   *******************************************************************************/
  /* If bulk okay signal = high */
  if (Rte_Read_R_B_PORT_BULK_OK) 
  {
    /* Reset bulk fail counter */
    u16LlcBulkFailCtr = 0U;
    /* If bulk okay counter higher than ok delay */
    if (MG_U16_LLC_BULK_OK_DLY < u16LlcBulkOkCtr) 
    {
      /* Set bulk okay flag */
      MG_B_PRIM_BULK_OK = TRUE;
    }
    else 
    {
      /* Count up bulk okay counter */
      u16LlcBulkOkCtr++; 
    }
  }
  /* Else bulk okay singal = low */
  else 
  {
    /* Reset bulk ok counter */
    u16LlcBulkOkCtr = 0U;
    /* If bulk fail counter higher than fail delay */
    if (MG_U16_LLC_BULK_FAIL_DLY < u16LlcBulkFailCtr)
    {
      /* Reset bulk okay flag */
      MG_B_PRIM_BULK_OK = FALSE;      
    } 
    else 
    {
      /* Count up bulk fail counter */
      u16LlcBulkFailCtr++; 
    }
  }
}

/** *****************************************************************************
 * \brief         Upgrade flag and MCU reset
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void TMCTRL_vWriteUpgradeFlgAndReset(void)
{
  /* Write FW upgrade flag to Flash and reset MCU */
  if ((FALSE != Rte_Read_R_B_BL_MODE) &&
      (FALSE == MG_B_LLC_EN))
  {
    TMCTRL_scfg_vFlashWriteUpgradeFlg();
    TMCTRL_scfg_vWdgSysReset();
  }
}


/*
 * End of file
 */
