/** *****************************************************************************
 * \file    schm.c
 * \brief   Scheme of task processing
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

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"
#include "debug_llc.h"

/* Module header */
#define SCHM_EXPORT_H
  #include "schm_api.h"
  #include "schm_scb.h"
  #include "schm_cfg.h"
  #include "schm_scfg.h"
  #include "schm_rte.h"
  #include "schm_conf.h"

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

typedef struct
{
  uint8 u8CtrBase;
  uint8 u8Ctr1ms;
  uint8 u8Ctr10ms;
} MG_S_FLOW_CTRL;

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static MG_S_FLOW_CTRL   SCHM_mg_sFlowCtrl;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
#if !MG_TIME_BASE_ISR
void SCHM_vSchmRoutine(void);
#endif

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Init function
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void SCHM_vInit(void)
{
  /***************************************
   * Initialize MCAL modules
   **************************************/
  SCHM_scfg_vClockInit();
  SCHM_scfg_vFlashInit();
  SCHM_scfg_vPortInit();
  SCHM_scfg_vExtiInit();
  SCHM_scfg_vTimerInit();
  SCHM_scfg_vHrTimerInit();
  SCHM_scfg_vAdcInit();
  SCHM_scfg_vDacInit();
  SCHM_scfg_vCompInit();
  SCHM_scfg_vUartInit();
  SCHM_scfg_vWdgInit();

  /***************************************
   * Initialize BSW modules
   **************************************/
  SCHM_cfg_vRteInit();
  SCHM_cfg_vHwioInit();
  SCHM_cfg_vUartPrtInit();
  SCHM_cfg_vCrcInit();
  
  /***************************************
   * Initialize CDD modules
   **************************************/

  /***************************************
   * Initialize APPL modules
   **************************************/
  SCHM_cfg_vLlcCtrlInit();
  SCHM_cfg_vAcsctrlInit();
  SCHM_cfg_vIntComInit();
  SCHM_cfg_vMonCtrlInit();
  SCHM_cfg_vTmCtrlInit();
  SCHM_cfg_vTempCtrlInit();
  SCHM_cfg_vMeterInit();

  /***************************************
   * Advanced initializing
   **************************************/
  /* Config NVIC vectors */
  SCHM_scfg_vAdcDmaNvicCfg(MG_DMA1CH1, MG_ADC_DMA1_CH1_ISR_PRE_PRIO, MG_ADC_DMA1_CH1_ISR_SUB_PRIO);
  SCHM_scfg_vUartNvicCfg(MG_UART2, MG_USART2_RX_ISR_PRE_PRIO, MG_USART2_RX_ISR_SUB_PRIO);
  #if (MG_TIME_BASE_ISR)
  SCHM_scfg_vTimerNvicCfg(MG_TIM17, MG_TIM17_ISR_PRE_PRIO, MG_TIM17_ISR_SUB_PRIO);
  #endif

  /* Init Timer17 period */
  SCHM_scfg_vTimerSetPeriod(MG_TIM17, MG_TIME_BASE_PERIOD_US);
  /* Init Timer15 period */
  //SCHM_scfg_vTimerSetPeriod(MG_TIM15, MG_U32_US_TIM15_ISR_PERIOD);    
  SCHM_scfg_vTimerSetFrequency(MG_TIM15, MG_TIM15_ISR_FREQ);
  
  /* Start high resolution timers syncronized */
  SCHM_scfg_vSyncStartHrTimer();

  /* Check if boot loader existing flag is written to flash */
  SCHM_cfg_vHwioCheckBootLoaderExistFlg();
  
  /* Read boot loader firmware version from flash */
  SCHM_cfg_vHwioReadBootLoaderFwVer();
  
  /* Set the watch dog time out delay */
  SCHM_scfg_vWdgSetTimeOutDly(MG_WDG_TIME_OUT_DLY);
  /* Enable the watchdog */
  SCHM_scfg_vWdgEn();
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
  DEBUG_SECTION_PIN_DEBUG_RESET;
  /* Feed the watchdog */
  SCHM_scfg_vWdgFeed();
  
  SCHM_cfg_vTmCtrlWriteUpgradeFlgAndReset();

  #if (!MG_TIME_BASE_ISR)
    /* Scheme routine */
    if (SCHM_scfg_u16TimerReadIrFlg(MG_TIM17))
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
  
  DEBUG_SECTION_PIN_DEBUG_SET;
  /* Clear interrupt flag */
  SCHM_scfg_vTimerClrIrFlg(MG_TIM17);
  /* Handle IIR filter for output */
  SCHM_cfg_vLlcctrlIirRippleFlt();
  /* LLC status update to avoid union issue */
  SCHM_cfg_vLlcctrlStatusUpdate();
  /* Read ADC buffer */
  SCHM_cfg_vHwioReadAdcUnits();
  /* Read ports */
  SCHM_cfg_vHwioReadGpioPin();

  /* Process 200uS tasks */
  SCHM_cfg_vTmCtrlLlcCtrl();
  SCHM_cfg_vMonCtrlOutFaultMon();
  SCHM_cfg_vAcsctrlSyncCtrl();
  SCHM_cfg_vLlcctrlLlHlAdjust();
  SCHM_cfg_vMeterAvg();
  SCHM_cfg_vUartPrtTxData();

  /* Set ports */
  SCHM_cfg_vHwioSetGpioPin();

  /* Increase basic counter */
  SCHM_mg_sFlowCtrl.u8CtrBase++;

  /***********************************************
   * 1ms task repetition
   **********************************************/
  switch (SCHM_mg_sFlowCtrl.u8CtrBase)
  {
    case 1:
    {
      SCHM_cfg_vUartPrtHandleTxData();
      break;
    }
    case 2:
    {
      SCHM_cfg_vTempCtrlNtcVoltAverage();
      break;
    }
    case 3:
    {
      SCHM_cfg_vUartPrtHandleRxData();
      break;
    }
    case 4:
    {
      SCHM_cfg_vUartPrtTmOutMon();
      break;
    }
    case 5:
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
          break;
        }
        case 6:
        {
          break;
        }
        case 7:
        {
          break;
        }
        case 8:
        {
          break;
        }
        case 9:
        {
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
              break;
            }
            case 2:
            {
              break;
            }
            case 3:
            {
              SCHM_cfg_vTempCtrlNtcOtMonitor();
              break;
            }
            case 4:
            {
              break;
            }
            case 5:
            {
              break;
            }
            case 6:
            {
              break;
            }
            case 7:
            {
              break;
            }
            case 8:
            {
              break;
            }
            case 9:
            {
              break;
            }
            case 10:
            {
              /* Reset 10ms counter */
              SCHM_mg_sFlowCtrl.u8Ctr10ms = 0U;
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
  }
}

/** *****************************************************************************
 * \brief         LLC control ISR
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
 /*
  * NOTE: Put the ccram attribute directly in front of the function (DMA1_Channel1_IRQHandler)
  * Add in memory map dissambly file:
  *       RW_IRAM2 0x10000000 0x00001000
  *       {
  *         *.o (RESET_RAM, +First) ;in case of vector table relocated in CCRAM
  *         .ANY (ccram)
  *       }
  */
__attribute__((section ("ccram")))  /* Load ISR into CCRAM for max processing speed */
void MG_VECT_LLC_CTRL_ISR
{
  /* Timing measurement by debug pin */
  DEBUG_SECTION_PIN_DEBUG_SET;

  /* Clear this Interrupt FLAG to avoid re-entry of this ISR */
  SCHM_scfg_vAdcDma1Ch1IsrFlgReset();

  /* Call the active current share routine */
  SCHM_cfg_vAcsctrlActiveCurrShare();

  /* Call the interrupt A routine */
  SCHM_cfg_vLlcCtrlIsr();
}

/** *****************************************************************************
 * \brief         RX data by UART ISR
 *
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
 /*
  * NOTE: Put the ccram attribute directly in front of the function (DMA1_Channel1_IRQHandler)
  * Add in memory map dissambly file:
  *       RW_IRAM2 0x10000000 0x00001000
  *       {
  *         *.o (RESET_RAM, +First) ;in case of vector table relocated in CCRAM
  *         .ANY (ccram)
  *       }
  */
__attribute__((section ("ccram")))  /* Load ISR into CCRAM for max processing speed */
void MG_VECT_USART2_ISR
{
  /* Rx data processing */
  SCHM_cfg_vUsart2IrqHandler();
}

/** *****************************************************************************
 * \brief         Error or fault processing
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void mg_vError(void)
{
  /* Deinit PWM's */
  SCHM_scfg_vHrTimerDeInit();
  /* Deinit ports */
  SCHM_scfg_vPortDeInit();
  /* Deinit control bits */
  SCHM_cfg_vRteDeInit();
}

/** *****************************************************************************
 * \brief         Cortex-M4 Processor Exceptions Handlers 
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
/* This function handles NMI exception */
void NMI_Handler(void)
{
  mg_vError();
}

/* This function handles Hard Fault exception */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
    mg_vError();
  }
}

/* This function handles Memory Manage exception */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
    mg_vError();
  }
}

/* This function handles Bus Fault exception */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
    mg_vError();
  }
}

/* This function handles Usage Fault exception */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
    mg_vError();
  }
}

/* This function handles SVCall exception */
void SVC_Handler(void)
{
  mg_vError();
}

/* This function handles Debug Monitor exception */
void DebugMon_Handler(void)
{
  mg_vError();
}

/* This function handles PendSVC exception */
void PendSV_Handler(void)
{
  mg_vError();
}

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{

}


/*
 * End of file
 */
