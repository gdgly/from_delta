/** *****************************************************************************
 * \file    psuctrl_scb.h
 * \brief   Service function call back file for psuctrl.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2018-08-23 15:34:14 +0800 (Thu, 23 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 14 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef PSUCTRL_SCB_H
#define PSUCTRL_SCB_H
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
void PSUCTRL_vInit(void);
void PSUCTRL_vDeInit(void);
void PSUCTRL_vVsbOut(void);
void PSUCTRL_vV1Out(void);
void PSUCTRL_vTrim(void);
//void PSUCTRL_vTestOutputOring(void);
void PSUCTRL_vV1OffDly4VsbOff(void);

#ifdef __cplusplus
  }
#endif
#endif  /* PSUCTRL_SCB_H */

  
/*
 * End of file
 */
