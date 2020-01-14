/** *****************************************************************************
 * \file    monctrl.c
 * \brief   Monitor output voltage and output currrent and process related tasks
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
#define MONCTRL_EXPORT_H
  #include "monctrl_api.h"
  #include "monctrl_scb.h"
  #include "monctrl_cfg.h"
  #include "monctrl_scfg.h"
  #include "monctrl_rte.h"
  #include "monctrl_conf.h"

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static GLOBAL_U_U16BIT MONCTRL_mg_uMonStatus;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

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
void MONCTRL_vInit(void)
{
  MONCTRL_mg_uMonStatus.ALL = 0x00;
  RTE_u16DebugData1 = 0x00;
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
void MONCTRL_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         Output fault condition monitoring; OVP, UVP, OCP
 *                Repetition time: 200uS
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void MONCTRL_vOutFaultMon(void)
{
  static uint8 u8OvpCtr = 0U;
  static uint8 u8HovCtr = 0U;
  static uint16 u16OvwCtr = 0U;
  static uint16 u16UvpCtr = 0U;
  static uint16 u16Ocp1Ctr = 0U;
  static uint16 u16Ocp2Ctr = 0U;
  static uint16 u16Ocp3Ctr = 0U;
  static uint16 u16OcwCtr = 0U;
  static uint16 u16OppCtr = 0U;
  static uint16 u16CurrOutOcp1 = MG_U16_10mA_LLC_IOUT_OCP_1_HL;
  #if (MG_3_LEVEL_OCP)
  static uint16 u16CurrOutOcp2 = MG_U16_10mA_LLC_IOUT_OCP_2_HL;
  static uint16 u16CurrOutOcp3 = MG_U16_10mA_LLC_IOUT_OCP_3_HL;
  #endif
  static uint16 u16CurrOutOcw = MG_U16_10mA_LLC_IOUT_OCW_HL;
  static uint16 u16CurrModeOcp = MG_U16_10mA_LLC_CURRENT_MODE_OCP_HL;
  static uint16 u1610mVVoltOutExt = 0U;
  static uint16 u1610mVVoltOutInt = 0U;
  static uint16 u1610mACurrOut = 0U;
  static uint16 u1610mACurrOutCali = 0U;
  static uint16 u1610mACurrOutAvg = 0U;
  static uint16 u16100mWPwrOutAvg = 0U;

  /* Read data from RTE */
  MONCTRL_Read_R_10mV_VoltOutExt_rte(&u1610mVVoltOutExt);
  MONCTRL_Read_R_10mV_VoltOutInt_rte(&u1610mVVoltOutInt);
  MONCTRL_Read_R_10mA_CurrOut_rte(&u1610mACurrOut);
  MONCTRL_Read_R_10mA_CurrOutCali_rte(&u1610mACurrOutCali);
  MONCTRL_Read_R_10mA_CurrOutAvg_rte(&u1610mACurrOutAvg);
  MONCTRL_Read_R_100mW_PwrOutAvg_rte(&u16100mWPwrOutAvg);

  /* Process the fault monitoring only when LLC is turned on */
  if (Rte_Read_R_B_LLC_EN)
  {
    /*******************************************************************************
     * Over voltage protection
     *******************************************************************************/
    /* Read output voltage OVP pin; High = over voltage (HOV) */
    if (Rte_Read_R_B_PORT_OVP)
    {
      /* If HOV counter higher than HOV delay */
      if (1U < u8HovCtr)
      {
        /* Set flags */
        MG_B_LLC_OUT_OVW = TRUE;
        MG_B_LLC_OUT_OVP = TRUE;
        u8HovCtr = 0U;
      }
      /* Else count up HOV counter */
      else
      {
        u8HovCtr++;
      }
    }

    /* If internal output voltage higher than OVP point */
    if (MG_U16_10mV_LLC_VOLT_OUT_OVP < u1610mVVoltOutInt)
    {
      /* If OVP counter higher than OVP delay */
      if (MG_U16_LLC_VOUT_OVP_DLY <= u8OvpCtr)
      {
        /* Set OVP flags */
        MG_B_LLC_OUT_OVW = TRUE;
        MG_B_LLC_OUT_OVP = TRUE;
      }
      /* Else count up OVP counter */
      else
      {
        u8OvpCtr++;
      }
    }
    /* Else if internal output voltage higher than OVW point */
    else if(MG_U16_10mV_LLC_VOLT_OUT_OVW < u1610mVVoltOutInt)
    {
      /* Count down OVP counter */
      if (0U < u8OvpCtr)
      {
        u8OvpCtr--;
      }

      /* If OVW counter higher than OVW delay */
      if(MG_U16_LLC_VOUT_OVW_DLY < u16OvwCtr)
      {
        /* Set OVW flag */
        MG_B_LLC_OUT_OVW = TRUE;
      }
      /* Else count up OVW counter */
      else
      {
        u16OvwCtr++;
      }
    }
    /* Else reset OVW */
    else
    {
      /* Count down OVP counter */
      if (0U < u8OvpCtr)
      {
        u8OvpCtr--;
      }
      /* Reset OVW */
      u16OvwCtr = 0U;
      MG_B_LLC_OUT_OVW = FALSE;
    }

    /*******************************************************************************
     * Under voltage protection
     *******************************************************************************/

    /* If internal output voltage lower than UVP point AND no current limit mode active */
    if ((MG_U16_10mV_LLC_VOUT_UVP > u1610mVVoltOutInt) && (!Rte_Read_R_B_LLC_CURR_LIMIT))
    {
      /* If UVP counter higher than UVP delay */
      if (MG_U16_LLC_VOUT_UVP_DLY < u16UvpCtr)
      {
        #if HALT_TEST_MODE
        #else
        /* Set UVP flags */
        MG_B_LLC_OUT_UVP = TRUE;
        MG_B_LLC_OUT_UVW = TRUE;
        #endif
        u16UvpCtr = 0U;
      }
      /* Else count up UVP counter */
      else
      {
        u16UvpCtr++;
      }
    }
    /* Else reset UVP counter */
    else
    {
      /* Reset UVW */
      u16UvpCtr = 0U;
      MG_B_LLC_OUT_UVW = FALSE;
    }
    /*******************************************************************************
     * Over current protection
     *******************************************************************************/
    /* Vin high line */
    if(Rte_Read_R_B_VIN_LINE)
    {
      u16CurrOutOcp1 = MG_U16_10mA_LLC_IOUT_OCP_1_HL;
      #if (MG_3_LEVEL_OCP)
      u16CurrOutOcp2 = MG_U16_10mA_LLC_IOUT_OCP_2_HL;
      u16CurrOutOcp3 = MG_U16_10mA_LLC_IOUT_OCP_3_HL;
      #endif
      u16CurrModeOcp = MG_U16_10mA_LLC_CURRENT_MODE_OCP_HL;
      u16CurrOutOcw = MG_U16_10mA_LLC_IOUT_OCW_HL;
    }
    /* Vin low line */
    else
    {
      u16CurrOutOcp1 = MG_U16_10mA_LLC_IOUT_OCP_1_LL;
      #if (MG_3_LEVEL_OCP)
      u16CurrOutOcp2 = MG_U16_10mA_LLC_IOUT_OCP_2_LL;
      u16CurrOutOcp3 = MG_U16_10mA_LLC_IOUT_OCP_3_LL;
      #endif
      u16CurrModeOcp = MG_U16_10mA_LLC_CURRENT_MODE_OCP_LL;
      u16CurrOutOcw = MG_U16_10mA_LLC_IOUT_OCW_LL;
    }

    /* If output current higher than OCP point OR voltage to current fail */
    if ( (u16CurrOutOcp1 < u1610mACurrOutCali) ||
        ((MG_U16_10mV_LLC_VOUT_UVP > u1610mVVoltOutInt) && (u16CurrModeOcp < u1610mACurrOutCali)) )
    {
      #if HALT_TEST_MODE
      #else
      u16Ocp1Ctr++;
      /* If OCP counter higher than OCP delay */
      if (MG_U16_LLC_IOUT_OCP_1_DLY < u16Ocp1Ctr)
      {
        /* Set OCP flags */
        u16Ocp1Ctr = 0U;
        MG_B_LLC_OUT_OCP = TRUE;
        MG_B_LLC_OUT_OCW = TRUE;
      }
      #if (MG_3_LEVEL_OCP)
      if (u16CurrOutOcp2 < u1610mACurrOutCali)
      {
        u16Ocp2Ctr++;
      }
      if ((MG_U16_LLC_IOUT_OCP_2_DLY < u16Ocp2Ctr))
      {
        /* Set OCP flags */
        u16Ocp2Ctr = 0U;
        MG_B_LLC_OUT_OCP = TRUE;
        MG_B_LLC_OUT_OCW = TRUE;
      }
      if (u16CurrOutOcp3 < u1610mACurrOutCali)
      {
        u16Ocp3Ctr++;
      }
      if (MG_U16_LLC_IOUT_OCP_3_DLY < u16Ocp3Ctr)
      {
        /* Set OCP flags */
        u16Ocp3Ctr = 0U;
        MG_B_LLC_OUT_OCP = TRUE;
        MG_B_LLC_OUT_OCW = TRUE;
      }
      #endif
      #endif
    }
    /* else if output current higher than OCW point */
    else if(u16CurrOutOcw < u1610mACurrOutCali)
    {
      /* Count down OCP counter */
      if (0U < u16Ocp1Ctr)
      {
        u16Ocp1Ctr--;
      }
      if (0U < u16Ocp2Ctr)
      {
        u16Ocp2Ctr--;
      }
      if (0U < u16Ocp3Ctr)
      {
        u16Ocp3Ctr--;
      }
      /* If OCW counter higher than OCW delay */
      if(MG_U16_LLC_IOUT_OCW_DLY < u16OcwCtr)
      {
        /* Set OCW flag */
        MG_B_LLC_OUT_OCW = TRUE;
      }
      /* Else count up OCW counter */
      else
      {
        u16OcwCtr++;
      }
    }
    /* else reset OCP and OCW */
    else
    {
      /* Reset OCP counter */
      u16Ocp1Ctr = 0;
      u16Ocp2Ctr = 0;
      u16Ocp3Ctr = 0;
      /* Reset OCW */
      u16OcwCtr = 0U;
      MG_B_LLC_OUT_OCW = FALSE;
    }

    /*******************************************************************************
     * CT over current protection
     *******************************************************************************/
    if (TRUE == Rte_Read_R_B_LLC_OCP_CT)
    {
      /* Set OCP flags */
      MG_B_LLC_OUT_OCP = TRUE;
      MG_B_LLC_OUT_OCW = TRUE;
    }

    /*******************************************************************************
     * Over power protection
     *******************************************************************************/
    /* If output power is higher than over power protection threshold */
    if (MG_U16_100mW_LLC_POUT_OPP < u16100mWPwrOutAvg)
    {
      /* If OP counter higher than OP delay */
      if (MG_U16_LLC_POUT_OPP_DLY < u16OppCtr)
      {
        /* Set OP flag */
        #if HALT_TEST_MODE
        #else
        /* MG_B_LLC_OUT_OPP = TRUE; */
        u16OppCtr = 0U;
        #endif
      }
      /* Else count up OP counter */
      else
      {
        u16OppCtr++;
      }
    }
    /* Else reset OP counter */
    else
    {
      /* Count down OP counter */
      if (0U < u16OppCtr)
      {
        u16OppCtr--;
      }
    }
  }
  /* If LLC disabled clear all counters */
  else
  {
    u8HovCtr = 0U;
    u8OvpCtr = 0U;
    u16UvpCtr = 0U;
    u16Ocp1Ctr = 0U;
    u16Ocp2Ctr = 0U;
    u16Ocp3Ctr = 0U;
    u16OvwCtr = 0U;
    u16OcwCtr = 0U;
    u16OppCtr = 0U;
  }

  /* If OV clear or fault clear */
  if (Rte_Read_R_B_LLC_OV_LATCH_CLR)
  {
    MG_B_LLC_OUT_OVP = FALSE;
  }
  /* If UV clear or fault clear */
  if (Rte_Read_R_B_LLC_UV_LATCH_CLR)
  {
    MG_B_LLC_OUT_UVP = FALSE;
  }
  /* If OC clear or fault clear */
  if (Rte_Read_R_B_LLC_OC_LATCH_CLR)
  {
    MG_B_LLC_OUT_OCP = FALSE;
  }
  /* If OC clear or fault clear */
  if (Rte_Read_R_B_LLC_OPP_LATCH_CLR)
  {
    MG_B_LLC_OUT_OPP = FALSE;
  }

  /* Write RTE variables */
  MONCTRL_Write_P_B_LLC_OUT_OVP_rte(MG_B_LLC_OUT_OVP);
  MONCTRL_Write_P_B_LLC_OUT_OVW_rte(MG_B_LLC_OUT_OVW);
  MONCTRL_Write_P_B_LLC_OUT_UVP_rte(MG_B_LLC_OUT_UVP);
  MONCTRL_Write_P_B_LLC_OUT_UVW_rte(MG_B_LLC_OUT_UVW);
  MONCTRL_Write_P_B_LLC_OUT_OCP_rte(MG_B_LLC_OUT_OCP);
  MONCTRL_Write_P_B_LLC_OUT_OCW_rte(MG_B_LLC_OUT_OCW);
  MONCTRL_Write_P_B_LLC_OUT_OPP_rte(MG_B_LLC_OUT_OPP);
}


/*
 * End of file
 */
