/*******************************************************************************
 * \file    main.c
 * \brief   Main routines
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2018-09-10 08:40:13 +0800 (Mon, 10 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 24 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/


#include "global.h"

/* Module header */
#define MAIN_EXPORT_H
  #include "main_api.h"
  #include "main_scb.h"
  #include "main_cfg.h"
  #include "main_scfg.h"
  #include "main_conf.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/


/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/


/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

volatile sint32 s32Debug = 0;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/
uint8 u8RdData[50]={0};
uint8 u8WrData[50]={0};
/*******************************************************************************
 * \brief         Initialize peripherals and data processing
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 * 
 ******************************************************************************/
int main(void)
{
  /********************it is for bootloader function*********************/
  MAIN_SCFG_vRemapVectorTable();
  /**********************************************************************/

  MAIN_cfg_vSchmInit();
	
  while (1)
  {
    /* Call scheme idle loop */
    MAIN_cfg_vSchmIdleLoop();
  } /* while (1) */
} /* main() */

/*
 * End of file
 */
