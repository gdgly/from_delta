/*******************************************************************************
 * \file    rtc.c
 * \brief   Calculate USED_HOURS
 *
 * \section AUTHOR
 *    1. Hulk.Zhang
 *
 * \section SVN
 *  $Date: 2018-10-31 13:45:45 +0800 (Wed, 31 Oct 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 95 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/
 
/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>
#include "global.h"

/* Module header */
#define RTC_EXPORT_H
  #include "rtc_api.h"
  #include "rtc_scb.h"
  #include "rtc_cfg.h"
  #include "rtc_scfg.h"
  #include "rtc_conf.h"

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/


/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

uint32_t mg_u32AsynchPrediv = 0, mg_u32SynchPrediv = 0;

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/


/********************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void RTC_vDeInit(void)
{
	
}

/********************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void RTC_vInit(void)
{
  uint16 u16DelayCnt = 0;
  RTC_InitTypeDef RTC_InitStructure;
  
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
  
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div32);  //RCC_RTCCLKSource_LSI
  
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  /* ck_spre(1Hz) = RTCCLK(LSI) /(mg_u32AsynchPrediv + 1)*(mg_u32SynchPrediv + 1)*/
  mg_u32AsynchPrediv = 99u;
  mg_u32SynchPrediv  = 4999u;

   /* Configure the RTC data register and RTC prescaler */
  RTC_InitStructure.RTC_AsynchPrediv = mg_u32AsynchPrediv; /*This parameter must be set to a value lower than 0x7F */
  RTC_InitStructure.RTC_SynchPrediv = mg_u32SynchPrediv;  /*This parameter must be set to a value lower than 0x1FFF */
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;

  /* Check on RTC init */
  while((RTC_Init(&RTC_InitStructure) == ERROR) && (u16DelayCnt < 200))
  {
    u16DelayCnt ++;
  }
  
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
}


