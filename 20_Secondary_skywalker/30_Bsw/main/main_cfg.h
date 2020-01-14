/** *****************************************************************************
 * \file    main_cfg.h
 * \brief   Server call back service file for main.c
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

#ifndef MAIN_CFG_H
#define MAIN_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_SCHM_MODULE            1

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

#if MG_SCHM_MODULE
#include "schm_scb.h"
#endif

/*******************************************************************************
 * Module interface
 ******************************************************************************/
/* Schedule manager module section */
inline void MAIN_cfg_vSchmInit(void)
{
  #if MG_SCHM_MODULE
  SCHM_vInit();
  #endif
}

inline void MAIN_cfg_vSchmDeInit(void)
{
  #if MG_SCHM_MODULE
  SCHM_vDeInit();
  #endif
}

inline void MAIN_cfg_vSchmIdleLoop(void)
{
  #if MG_SCHM_MODULE
  SCHM_vSchmIdleLoop();
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* MAIN_CFG_H */

  
/*
 * End of file
 */
