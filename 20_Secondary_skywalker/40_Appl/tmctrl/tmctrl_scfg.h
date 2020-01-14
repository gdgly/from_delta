/** *****************************************************************************
 * \file    tmctrl_scfg.h
 * \brief   Server request service file for tmctrl.c
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

#ifndef TMCTRL_SCFG_H
#define TMCTRL_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/
#define MG_HWIO_MODULE             1

/*******************************************************************************
 * Included header
 ******************************************************************************/
#include "global.h"
    
#if MG_HWIO_MODULE
#include "hwio_api.h"
#endif

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Module interface
 ******************************************************************************/

/* Flash module section */
inline void TMCTRL_scfg_vFlashWriteUpgradeFlg(void)
{
  #if MG_HWIO_MODULE
  HWIO_vSetFwUpgradeFlg();
  #endif
}    

/* Watch dog module section */
inline void TMCTRL_scfg_vWdgSysReset(void)
{
  #if MG_HWIO_MODULE
  HWIO_vWdgSysReset();
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* TMCTRL_SCFG_H */

  
/*
 * End of file
 */
