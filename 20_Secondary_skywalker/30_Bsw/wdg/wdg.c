/** *****************************************************************************
 * \file    wdg.c
 * \brief   Watchdog setup and control functions
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

#include "StdPeriphDriver.h"
#include "global.h"
#include "debug_llc.h"

/* Module header */
#define WDG_EXPORT_H
  #include "wdg_api.h"
  #include "wdg_scb.h"
  #include "wdg_cfg.h"
  #include "wdg_scfg.h"
  #include "wdg_conf.h"

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
void WDG_vInit(void)
{
  /* Allow write access */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /*
   * IWDG independent low speed clock = 41KHz (LSI)
   * 12-bit max counter value (4096)
   * 41kHz / 4 (prescaler) = 10250/s
   * 150ms / 1s * 10250 = 1537 = 0x0601
   * 2ms / 1s * 10250 = 20 = 0x0014
   * Set prescaler value for IWDG and wait until completion
   */
  IWDG_SetPrescaler(IWDG_Prescaler_4);
  while(!IWDG_GetFlagStatus(IWDG_FLAG_PVU));

  /* Permit write access to IWDG registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
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
void WDG_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         Set watch dog time out delay
 *
 * \param[in]     msTimeOutDly: Time out delay in ms
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void WDG_vWdgSetTimeOutDly(uint16 u16msTimeOutDly)
{
  /* Convert milli second to timer value */
  u16msTimeOutDly = (uint16)(MG_F32_MS_WDG_CONV_FACT * u16msTimeOutDly);
  
  /* Allow write access */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* 
   * Set watchdog reloud counter value and wait for completion
   * This value is loaded into the counter register after each reaload (feeding)
   */
  IWDG_SetReload(u16msTimeOutDly);
  while(!IWDG_GetFlagStatus(IWDG_FLAG_RVU));
  
  /* Load the reload counter value to the counter register */
  IWDG_ReloadCounter();
  
  /* Permit write access to IWDG registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
}

/** *****************************************************************************
 * \brief         Feed the watch dog (reset watch dog counter)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void WDG_vWatchDogFeed(void)
{
  /* Write the counter reload key to the key register */
  IWDG->KR = ((uint16_t)0xAAAA);
}

/** *****************************************************************************
 * \brief         Enable the Independent Watchdog Timer
 *                The IWDG uses its own clock and is independet from the main clock
 *                --> lower timing accuqracy, but higher safety level
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void WDG_vWatchDogEn(void)
{
  /* Allow write access */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* Enable the IWDG */
  IWDG_Enable();

  /* Permit write access to IWDG registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
}

/** *****************************************************************************
 * \brief         System/MCU reset
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void WDG_vSysReset(void)
{
  /* Write the reset key into reset register */
  SCB->AIRCR = (0x05FAU << SCB_AIRCR_VECTKEYSTAT_Pos) | (0x1U << SCB_AIRCR_SYSRESETREQ_Pos);
}

/*
 * End of file
 */
