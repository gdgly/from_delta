/*******************************************************************************
 * \file    psuctrl.h
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

#ifndef PSUCTRL_H
#define PSUCTRL_H
#ifdef __cplusplus
  extern "C"  {
#endif
#include "global.h"
#define VSB_FIRST_POWER_UP_DELAY           1000 /* Power up delay = value * 1mS */
#define VSB_POWER_UP_DELAY                 1000  /* Power up delay = value * 1mS */
#define V1_FIRST_POWER_UP_DELAY            1000 /* Power up delay = value * 1mS */
#define V1_POWER_UP_DELAY                  500  /* Power up delay = value * 1mS */
#define VOUT_PWRDOWN_DELAY	           500  /* 500ms = value * 1mS */

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/
//extern uint16 u16TrimVsbGainAct;
//extern uint16 PSUCTRL_u16VsbPwrUpDly;
//extern uint16 PSUCTRL_u16V1RestartTimer; 
//extern uint8  mg_u8V1PowerUpCnt;
/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/
//

/*******************************************************************************
 * Global data
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
extern	void PSUCTRL_Init(void);
extern	void PSCTRL_vVsbOut(void);
extern	void PSCTRL_vV1Out(void);
extern  void vSecVsbPwrOn( void );
extern  void vSecVsbPwrOff( void );
/*******************************************************************************
 * \brief         Adjust 5V voltage
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
extern void PSCTRL_vTrim(void);
extern void PSCTRL_vTestOutputOring(void);
extern void PSCTRL_SleepModeCtrl(void);
extern void PSCTRL_vClearV1PwrUpCnt(void);
extern void PSCTRL_vSetV1RstTim(uint16 u16Value);
extern void PSCTRL_vV1OffDly4VsbOff(void);

#ifdef __cplusplus
  }
#endif
#endif /* psuctrl */



/*
 * End of file
 */

