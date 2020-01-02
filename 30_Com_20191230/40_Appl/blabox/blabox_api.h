/** ****************************************************************************
 * \file    blabox_api.h
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
#ifndef BLABOX_API_H
#define BLABOX_API_H
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
extern boolean BLABOX_bWriteEEPROMProcessing;
/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/

/*******************************************************************************
 * Function:        BLABOX_vMFR_BLABOX
 * Parameters:      -
 * Returned value:  -
 * Description:     PMBus function cmd (0xDC) get All BlackBox
 *
 ******************************************************************************/
extern boolean BLABOX_vMFR_BLABOX(uint8* pu8Buffer);
/*******************************************************************************
 * Function:        BLABOX_vSetRealTimeClockDataSystemBlackbox
 * Parameters:      -
 * Returned value:  -
 * Description:     PMBus function cmd (0xDD) Write
 *
 ******************************************************************************/
extern void BLABOX_vSetRealTimeClockDataSystemBlackbox(uint32 u32ReadTime);
/*******************************************************************************
 * Function:        BLABOX_vGetRealTimeClockDataSystemBlackbox
 * Parameters:      -
 * Returned value:  -
 * Description:     PMBus function cmd (0xDD) Read
 *
 ******************************************************************************/
extern uint32 BLABOX_vGetRealTimeClockDataSystemBlackbox(void);
/*******************************************************************************
 * Function:        BLABOX_vMFR_SystemBlackBox
 * Parameters:      -
 * Returned value:  -
 * Description:     PMBus function cmd (0xDE) get Name Serial system (ascii-code)
 *
 ******************************************************************************/
extern void BLABOX_vMFR_SystemBlackBox(uint8* pu8Buffer,uint8 IsWrite);
/*******************************************************************************
 * Function:        BLABOX_vSetEnableBlackbox
 * Parameters:      -
 * Returned value:  -
 * Description:     PMBus function cmd (0xDF) Write
 *
 ******************************************************************************/
extern void BLABOX_vSetEnableBlackbox(uint8 u8Tmp);
/*******************************************************************************
 * Function:        BLABOX_vGetEnableBlackbox
 * Parameters:      -
 * Returned value:  -
 * Description:     PMBus function cmd (0xDF) Read
 *
 ******************************************************************************/
extern uint8 BLABOX_vGetEnableBlackbox(void);
/*******************************************************************************
 * Function:        BLABOX_vMFR_ClearBlackBox
 * Parameters:      -
 * Returned value:  -
 * Description:     PMBus function cmd (0xE0) 
 *
 ******************************************************************************/
extern void BLABOX_vMFR_ClearBlackBox(void);

#ifdef __cplusplus
  }
#endif
#endif  /* BLABOX_API_H */

  
/*
 * End of file
 */
 
