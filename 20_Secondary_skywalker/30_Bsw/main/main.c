/** *****************************************************************************
 * \file    main.c
 * \brief   Main routines
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
#define MAIN_EXPORT_H
  #include "main_api.h"
  #include "main_scb.h"
  #include "main_cfg.h"
  #include "main_scfg.h"
  #include "main_conf.h"

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initialize peripherals and data processing
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
int main(void)
{
  /* Initialize the MCU before entering the main while loop */
  MAIN_cfg_vSchmInit();

  while (1)
  {
    /* Call scheme idle loop */
    MAIN_cfg_vSchmIdleLoop();
  }
}

/*
 * End of file
 */
