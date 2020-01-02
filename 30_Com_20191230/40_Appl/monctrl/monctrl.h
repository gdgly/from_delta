/*******************************************************************************
 * \file    monctrl.h
 * \brief   
 *
 * \section AUTHOR
 *    1. Fred Ji
 *
 * \section SVN
 *  $Date: 2018-08-07 18:22:40 +0800 (Tue, 07 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 11 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef MONCTRL_H
#define MONCTRL_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/


/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
extern void MONI_vUpdateStatus(void);
extern void MONI_Init(void);
extern void MONI_ClearFault(void);
extern void MONI_vVsbOutput(void);
/*******************************************************************************
 * Function:        MONI_AuxModeDetect
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     
 *
 ******************************************************************************/
extern void MONI_AxuModeDetect(void);
extern void MONI_InputTypeDetect(void);
extern void MONI_Output_UV_monitor(void);

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data
 ******************************************************************************/

#ifdef __cplusplus
  }
#endif
#endif /* monctrl */


/*
 * End of file
 */

