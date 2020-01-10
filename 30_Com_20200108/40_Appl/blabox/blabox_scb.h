/** ****************************************************************************
 * \file    blabox_scb.h
 * \brief   COM module implementation configuration
 *
 * \section AUTHOR
 *  S. Ratchanon
 *
 * \section SVN
 *  $Date: 2016-06-10 16:01:06 +0200 (Fr, 10 Jun 2016) $
 *  $Author: dementm $
 *  $Revision: 1413 $
 *
 * \section LICENSE
 *  Copyright (c) 2014 Delta Energy Systems (Thailand) GmbH.
 *  All rights reserved.
 **************************************************************************** */

#ifndef BLABOX_SCB_H
#define BLABOX_SCB_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
/*******************************************************************************
 * Function:        BLABOX_vInit
 * Parameters:      -
 * Returned value:  -
 * Description:     Init function
 *
 ******************************************************************************/
 extern void BLABOX_vInit(void);
 
/*******************************************************************************
 * Function:        BLABOX_vProcessBlackbox
 * Parameters:      -
 * Returned value:  -
 * Description:     Task manage 10 ms
 *
 ******************************************************************************/
extern void BLABOX_vProcessBlackbox(void);

/*******************************************************************************
 * Function:        BLABOX_vMFR_CheckPSONBlackBox
 * Parameters:      -
 * Returned value:  -
 * Description:     Task manage 100 ms Count PSON
 *
 ******************************************************************************/
extern void BLABOX_vMFR_CheckPSONBlackBox(void);

/*******************************************************************************
 * Function:        BLABOX_vMFR_CheckACBlackBox
 * Parameters:      -
 * Returned value:  -
 * Description:     Task manage 100 ms Count AC 
 *
 ******************************************************************************/
extern void BLABOX_vMFR_CheckACBlackBox(void);

/*******************************************************************************
 * Function:        BLABOX_vMFR_TimePSONBlackBox
 * Parameters:      -
 * Returned value:  -
 * Description:     Task manage 100 ms Count Total Time
 *
 ******************************************************************************/
extern void BLABOX_vMFR_TimePSONBlackBox(void);

/*******************************************************************************
 * Function:        BLABOX_vCountRealTimeClockDataSystemBlackbox
 * Parameters:      -
 * Returned value:  -
 * Description:     Task manage 100 ms for Count RealTime standard IPMI
 *
 ******************************************************************************/
extern void BLABOX_vCountRealTimeClockDataSystemBlackbox(void);

/** ****************************************************************************
 * \brief  BLABOX_vClearWarning
 * \param[in]  -  -
 * \param[out] -  -
 * \comment -  Clear Event after PSU re-turnOn
 * \return  - Loop 100ms
 *
 **************************************************************************** */
extern void BLABOX_vClearWarning(void);

/*******************************************************************************
 * Function:        BLABOX_vClearFault
 * Parameters:      -
 * Returned value:  -
 * Description:     Clear Fault , at program re-TurnOn PSU (function control Vmain)
 *
 ******************************************************************************/
extern void BLABOX_vClearFault(void);
 
 #ifdef __cplusplus
  }
#endif
#endif  /* BLABOX_SCB_H */

  
/*
 * End of file
 */

