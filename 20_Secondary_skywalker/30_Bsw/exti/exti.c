/** ****************************************************************************
 * \file    exti.c
 * \brief   MCU ext interrupt configurations
 *
 * \section AUTHOR
 *    1. Wayne Wen
 *
 * \section SVN
 *  $Date$
 *  $Author$
 *  $Revision$
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 **************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "debug_llc.h"

/* Module header */
#define EXTI_EXPORT_H
  #include "exti_api.h"
  #include "exti_scb.h"
  #include "exti_cfg.h"
  #include "exti_scfg.h"
  #include "exti_conf.h"

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void mg_vExtiHwInit(void);
  
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
void EXTI_vInit(void)
{
  mg_vExtiHwInit();
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
void EXTI_vDeInit(void)
{

}

/*******************************************************************************
 * Local functions (privat for module)
 ******************************************************************************/

/** ****************************************************************************
 * \brief         Initialize the exti module
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 **************************************************************************** */
static void mg_vExtiHwInit(void)
{
  /* Temporary typedefs */
  EXTI_InitTypeDef              EXTI_InitStructure;
  
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Connect EXTI2 Line to PB2 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2); 
  /* Configure EXTI2 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/*
 * End of file
 */
