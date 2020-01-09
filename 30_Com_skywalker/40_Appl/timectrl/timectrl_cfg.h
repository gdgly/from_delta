/** *****************************************************************************
 * \file    timectrl_cfg.h
 * \brief   Server call back service file for timectrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef TIMECATL_CFG_H
#define TIMECATL_CFG_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Module includes
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>
#include <global.h>

/*******************************************************************************
 * Module interface
 ******************************************************************************/
	
#define TIMECTRL_CFG_RTC_TR_SECOND_UNIT		(RTC->TR & 0x00000001)

#ifdef __cplusplus
  }
#endif
#endif  /* TIMECATL_CFG_H */

  
/*
 * End of file
 */
