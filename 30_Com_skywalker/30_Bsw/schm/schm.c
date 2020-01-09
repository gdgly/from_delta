/*******************************************************************************
 * \file    schm.c
 * \brief   Scheme of task processing
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2019-10-14 17:07:42 +0800 (Mon, 14 Oct 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 234 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

/* Module header */
#define SCHM_EXPORT_H
	#include "schm_api.h"
  #include "schm_scb.h"
  #include "schm_cfg.h"
  #include "schm_scfg.h"
  #include "schm_rte.h"
  #include "schm_conf.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
 

  
/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

typedef struct
{
  uint8 u8CtrBase;
  uint8 u8Ctr1ms;
  uint8 u8Ctr10ms;
  uint8 u8Ctr100ms;
} MG_S_FLOW_CTRL;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static MG_S_FLOW_CTRL   SCHM_mg_sFlowCtrl;
uint16 ADC_Test=0;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
#if !MG_TIME_BASE_ISR
void SCHM_vSchmRoutine(void);
#endif
/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/
void SCHM_vInit(void)
{
  /* Disable IRQ Interrupts */
  SCHM_scfg_vDisableIrq();
	
  /***************************************
   * Initialize MCAL modules
   **************************************/
  SCHM_scfg_vClockInit();
  SCHM_scfg_vFlashInit();
  SCHM_scfg_vPortInit();
  SCHM_scfg_vTimerInit();
	SCHM_scfg_vPWMInit();
  SCHM_scfg_vAdcInit();
  SCHM_scfg_vUartInit();
  SCHM_scfg_vRtcInit();
  SCHM_scfg_vI2cInit();
  SCHM_scfg_vWdgInit();

  /***************************************
   * Initialize BSW modules
   **************************************/
  SCHM_cfg_vRteInit();
  SCHM_cfg_vHwioInit();
  SCHM_cfg_vUartPrtInit();
  SCHM_cfg_vCrcInit();
  SCHM_cfg_vBufferInit();
  SCHM_cfg_vEepromInit();
  SCHM_cfg_vI2cprtInit();
  SCHM_cfg_vCaliInit();
  SCHM_cfg_vMemInit();	
  
  /***************************************
   * Initialize CDD modules
   **************************************/

  /***************************************
   * Initialize APPL modules
   **************************************/
  SCHM_cfg_vIntComInit();
  SCHM_cfg_vMonCtrlInit();
  SCHM_cfg_vTempCtrlInit();
  SCHM_cfg_vPmbusInit();
  SCHM_cfg_vFanCtrlInit();
  SCHM_cfg_vLedCtrlInit();
  SCHM_cfg_vTimeCtrlInit();
  SCHM_cfg_vPsuCtrlInit();
  SCHM_cfg_vBlaboxInit();
  /***************************************
   * Advanced initializing
   **************************************/

  /* Check if boot loader existing flag is written to flash */
  SCHM_cfg_vHwioCheckBootLoaderExistFlg();

  /* Set the watch dog time out delay */
  SCHM_scfg_vWdgSetTimeOutDly(MG_WDG_TIME_OUT_DLY);
	
  /* Enable the watchdog */
  SCHM_scfg_vWdgEn();
 
  /* Enable IRQ Interrupts */
  SCHM_scfg_vEnableIrq();
}

/** *****************************************************************************
 * \brief         De-init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void SCHM_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         MCU IDLE loop
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void SCHM_vSchmIdleLoop(void)
{
  /* Feed the watchdog */
  SCHM_scfg_vWdgFeed();

  #if (!MG_TIME_BASE_ISR)
    /* Scheme routine */
    if (FALSE != SCHM_scfg_u8TimerGetUpdateItFlg())
    {
      SCHM_vSchmRoutine();
    }
  #endif
}

/** *****************************************************************************
 * \brief         Interrupt service routine for task processings
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
#if MG_TIME_BASE_ISR
void MG_VECT_TIME_BASE_ISR
#else
void SCHM_vSchmRoutine(void)
#endif
{
	
	SCHM_scfg_vTimerClearUpdateItFlg();

	SCHM_cfg_vUartPrtTxData();
	SCHM_scfg_vI2cTimeOutHandler();
	SCHM_cfg_vFanSpeedCnt();
	SCHM_cfg_vHwioReadGpioPin();
  SCHM_cfg_vHwioSetGpioPin();
  SCHM_cfg_vCalibrateIShare();
  SCHM_cfg_vCaliFast();
  SCHM_cfg_vMonCtrlCheckVsbOvp();

	/* Increase basic counter */
	SCHM_mg_sFlowCtrl.u8CtrBase++;
	/***********************************************
	* 1ms task repetition
	**********************************************/
	switch (SCHM_mg_sFlowCtrl.u8CtrBase)
	{
		case 1:
		{
			SCHM_cfg_vUartPrtTmOutMon();
			break;
		}
		case 2:
		{
			SCHM_cfg_vUartPrtHandleTxData();
			break;
		}
		case 3:
		{
			SCHM_cfg_vUartPrtHandleRxData();
			break;
		}
		case 4:
		{
                        SCHM_cfg_vMonCtrlVsbOutput();
			SCHM_cfg_vPsuCtrlVsbOut();
			break;
		}
		case 5:
		{
			SCHM_cfg_vPsuCtrlV1Out();
			break;
		}
		case 6:
		{
			SCHM_cfg_vTempCtrlNtcVoltAverage();
			break;
		}
		case 7:
		{
			SCHM_cfg_vI2cprtProcessRxData();
			SCHM_cfg_vPmbusCopyPecAndOringStatus();
			break;
		}
		case 8:
		{
			SCHM_cfg_vIntComTmOutMOn();
      SCHM_cfg_vBufferCalc1ms();
			break;
		}
		case 9:
		{
      SCHM_cfg_vMonCtrlVin();
			break;
		}
		case 10:
		{
			/* Reset basic counter */
			SCHM_mg_sFlowCtrl.u8CtrBase = 0U;
			/* Increase 1ms counter */
			SCHM_mg_sFlowCtrl.u8Ctr1ms++;
		
			/***********************************************
			 * 10ms task repetition
			 **********************************************/
			switch(SCHM_mg_sFlowCtrl.u8Ctr1ms)
			{
				case 1:
				{
					SCHM_cfg_vCaliHandler();
					break;
				}
				case 2:
				{
					SCHM_cfg_vPmbusCopySensorData();
					break;
				}
				case 3:
				{
					SCHM_cfg_vMonCtrlUpdateStatus();
					SCHM_cfg_vLedControl();
					break;
				}
				case 4:
				{
					SCHM_cfg_vPsuCtrlTrim();
          SCHM_cfg_vCalcCaliPara();
					break;
				}
				case 5:
				{
					SCHM_cfg_vFanSpeedCalc();
					break;
				}
				case 6:
				{
				  SCHM_cfg_vPmbusCheckBootMode();
          SCHM_cfg_vBufferCalc10ms();
					break;
				}
				case 7:
				{
					SCHM_cfg_vI2cprtUpdateI2cAddr();
					break;
				}
				case 8:
				{
					SCHM_cfg_vProcessBlackbox();
					break;
				}
				case 9:
				{
					SCHM_cfg_vMemSaveData();
					break;
				}
				case 10:
				{
					/* Reset 1ms counter */
					SCHM_mg_sFlowCtrl.u8Ctr1ms = 0U;
					/* Increase 10ms counter */
					SCHM_mg_sFlowCtrl.u8Ctr10ms++;
				
					/***********************************************
					 * 100ms task repetition
					 **********************************************/
					switch(SCHM_mg_sFlowCtrl.u8Ctr10ms)
					{
						case 1:
						{
							SCHM_cfg_vFanCtrl();
							SCHM_cfg_vCheckACBlackBox();
							break;
						}
						case 2:
						{
							SCHM_cfg_vMonCtrlCheckStatusReset();
							SCHM_cfg_vTimePSONBlackBox();
							break;
						}
						case 3:
						{
							SCHM_cfg_vPmbusCopyStatusData();
							SCHM_cfg_vCountRealTimeClockDataSystemBlackbox();
							break;
						}
						case 4:
						{
							SCHM_cfg_vTempCtrlLookUpNtcTemperature();
							SCHM_cfg_vClearWarning();
							break;
						}
						case 5:
						{
						  SCHM_cfg_vPmbusCopyDebugData();
							break;
						}
						case 6:
						{
              SCHM_cfg_vTempCtrlNtcVoltMonitor();
							break;
						}
						case 7:
						{
							SCHM_cfg_vMonCtrlAxuModeDetect();
							break;
						}
						case 8:
						{
							SCHM_cfg_vCheckPSONBlackBox();
							break;
						}
						case 9:
						{
							SCHM_cfg_vTimeCtrlSaveHoursUsed();
							break;
						}
						case 10:
						{
							/* Reset 10ms counter */
							SCHM_mg_sFlowCtrl.u8Ctr10ms = 0U;
							/* Increase 100ms counter */
							SCHM_mg_sFlowCtrl.u8Ctr100ms++;

							/***********************************************
							 * 500ms task repetition
							 **********************************************/
							switch(SCHM_mg_sFlowCtrl.u8Ctr100ms)
							{
								case 1:
								{
									break;
								}
								case 2:
								{
									break;
								}
								case 3:
								{
									break;
								}
								case 4:
								{
									break;
								}
								case 5:
								{
									SCHM_mg_sFlowCtrl.u8Ctr100ms = 0U;
									break;
								}
							}
							break;
						}
						default:
						{
							/* Reset 10ms counter */
							SCHM_mg_sFlowCtrl.u8Ctr10ms = 0U;
							break;
						}
					} /* switch(10ms) */
					break;
				}
				default:
				{
					/* Reset 1ms counter */
					SCHM_mg_sFlowCtrl.u8Ctr1ms = 0U;
					break;
				}
			} /* switch(1ms) */
			break;
		}
		default:
		{
			/* Reset basic counter */
			SCHM_mg_sFlowCtrl.u8CtrBase = 0U;
			break;
		}
	} /* switch(basic) */
}

/*
 * End of file
 */
