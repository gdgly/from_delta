/** *****************************************************************************
 * \file    monctrl_scb.h
 * \brief   Service function call back file for monctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-09-09 17:59:22 +0800 (Mon, 09 Sep 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 229 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef MONCATL_SCB_H
#define MONCATL_SCB_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
void MONCTRL_vInit(void);
void MONCTRL_vDeInit(void);		
void MONCTRL_vUpdateStatus(void);
/*******************************************************************************
 * Function:        MONI_AuxModeDetect
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     
 *
 ******************************************************************************/
void MONCTRL_vAxuModeDetect(void);
void MONCTRL_vCheckStatusReset(void);
/*******************************************************************************
 * Function:        MONCTRL_vCheckVsbOvp
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Exe Period:      0.1ms
 * Description:     Mornitor the vsb ovp
 *
 ******************************************************************************/
void MONCTRL_vCheckVsbOvp(void);
void MONCTRL_vVsbOutput(void);
/*******************************************************************************
 * Function:        MONCTRL_vVin
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Exe Period:      1ms
 * Description:     Mornitor the Input voltage 
 *
 ******************************************************************************/
void MONCTRL_vVin(void);

#ifdef __cplusplus
  }
#endif
#endif  /* MONCATL_SCB_H */

  
/*
 * End of file
 */
