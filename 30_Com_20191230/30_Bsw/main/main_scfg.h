/** *****************************************************************************
 * \file    main_scfg.h
 * \brief   Server request service file for main.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-09-20 11:15:53 +0800 (Thu, 20 Sep 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 41 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef MAIN_SCFG_H
#define MAIN_SCFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "flash_api.h"
		
SINLINE void MAIN_SCFG_vRemapVectorTable(void)
{
	FLASH_vRemapVectorTable();
}
		

#ifdef __cplusplus
  }
#endif
#endif  /* MAIN_SCFG_H */

  
/*
 * End of file
 */
