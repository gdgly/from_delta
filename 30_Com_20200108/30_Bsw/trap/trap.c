/** *****************************************************************************
 * \file    trap.c
 * \brief   MCU trap and fault handler
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <stdio.h>
#include <StdPeriphDriver.h>
#include "global.h"
#include "rte.h"
#include "port.h"
#include "pwm.h"

/* Module header */
#define TRAP_EXPORT_H
  #include "trap.h"
  #include "trap_rte.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void mg_vError(void);

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Cortex-M4 Processor Exceptions Handlers 
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
/* This function handles NMI exception */
void NMI_Handler(void)
{
  mg_vError();
}

/* This function handles Hard Fault exception */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
    mg_vError();
  }
}

/* This function handles SVCall exception */
void SVC_Handler(void)
{
  mg_vError();
}

/* This function handles PendSVC exception */
void PendSV_Handler(void)
{
  mg_vError();
}

/* This function handles Debug Monitor exception */
void DebugMon_Handler(void)
{
  mg_vError();
}

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{
  #if 0
  DEBUG_PIN_TOGGLE;
  #endif
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Error or fault processing
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vError(void)
{

}

/*
 * End of file
 */
