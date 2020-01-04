/*******************************************************************************
 * \file    clock.c
 * \brief   MCU clock configuration
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2019-02-19 14:24:47 +0800 (Tue, 19 Feb 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 142 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>

/* Module header */
#define CLOCK_EXPORT_H
  #include "clock_api.h"
  #include "clock_scb.h"
  #include "clock_cfg.h"
  #include "clock_scfg.h"
  #include "clock_conf.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
 
/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

#ifdef EXTERNAL_OSCILLATOR
/* External oscillator prototype */
static void mg_vXtalOscSel(void);
#else
/* Internal oscillator prototype */
static void mg_vIntOscSel(void);
#endif

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static uint32 mg_u32SysCoreClk;
__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

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
void CLOCK_vInit(void)
{
  SystemInit();
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
void CLOCK_vDeInit(void)
{

}
/*******************************************************************************
 * \brief         Initialize the System and the MCU Clock
 *                Called by startup_xxx.s
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void SystemInit(void)   //Change the name from SystemInit() to SystemInit(), all the SystemInit() change to SystemInit() 
{
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FFB80C;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  RCC->CFGR &= (uint32_t)0xFFC0FFFF;

  /* Reset PREDIV1[3:0] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;

  /* Reset USARTSW[1:0], I2CSW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFEAC;

  /* Reset HSI14 bit */
  RCC->CR2 &= (uint32_t)0xFFFFFFFE;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;

  /* Configure the System clock frequency, AHB/APBx prescalers and Flash settings */
  #ifdef EXTERNAL_OSCILLATOR 
    /***********************************************
     * Function call: XtalOscSel()
     * Description: Select External CRYSTAL Oscillator as Clock Source
     **********************************************/
    mg_vXtalOscSel();
  #else
    /***********************************************
     * Function call: IntOscSel()
     * Description: Select Internal Oscillator as Clock Source
     **********************************************/
    mg_vIntOscSel();
  #endif
}

/*******************************************************************************
 * \brief         Update SystemCoreClock variable according to Clock Register Values
 *                 The SystemCoreClock variable contains the core clock (HCLK)
 *                Each time the core clock (HCLK) changes, this function must be called
 *                 to update SystemCoreClock variable value
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void CLOCK_vSysCoreClkUpdate(void)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      mg_u32SysCoreClk = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      mg_u32SysCoreClk = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        mg_u32SysCoreClk = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
        /* HSE oscillator clock selected as PREDIV1 clock entry */
        mg_u32SysCoreClk = (HSE_VALUE / prediv1factor) * pllmull; 
      }
      break;
    default: /* HSI used as system clock */
      mg_u32SysCoreClk = HSI_VALUE;
      break;
  }
  /* Compute HCLK clock frequency ----------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK clock frequency */
  mg_u32SysCoreClk >>= tmp;  
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

#ifdef EXTERNAL_OSCILLATOR
/*******************************************************************************
 * \brief         This function switches to External CRYSTAL oscillator
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vXtalOscSel(void)
{
	/*
   * System Clock source:   PLL (HSE)
   * SYSCLK(Hz):            48000000
   * HCLK(Hz):              48000000
   * AHB Prescaler:         1
   * APB2 Prescaler:        1
   * APB1 Prescaler:        2
   * HSE Frequency(Hz):     16000000
   * PLLMUL:                6
   * PREDIV:                2
   * USB Clock:             DISABLE
   * Flash Latency(WS):     2
   * Prefetch Buffer:       OFF
   */
 __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } 
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer and set Flash Latency */
    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
 
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE_DIV1;

    /* PLL configuration = HSE/2 * 6 = 48 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLXTPRE_PREDIV1_Div2 | RCC_CFGR_PLLMULL6);
            
    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
  }  
}

#else

/*******************************************************************************
 * \brief         This function switches to Internal Oscillator
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
static void mg_vIntOscSel(void)
{
  /* System Clock source: 	PLL (HSI)
   * SYSCLK(Hz): 					  48000000
   * HCLK(Hz):            	48000000
   * AHB Prescaler:       	1
   * APB2 Prescaler:      	1
   * APB1 Prescaler:      	2
   * HSI Frequency(Hz):   	8000000
   * PLLMUL:              	12
   * PREDIV:              	2
   * USB Clock:           	DISABLE
   * Flash Latency(WS):   	2
   * Prefetch Buffer:     	ON
   */
  /* At this stage the HSI is already enabled */

  /* Enable Prefetch Buffer and set Flash Latency */
  FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
 
  /* HCLK = SYSCLK */
  RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
  /* PCLK = HCLK */
  RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE_DIV1;

  /* PLL configuration = (HSI/2) * 12 = ~48 MHz */
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
  RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLMULL12);
            
  /* Enable PLL */
  RCC->CR |= RCC_CR_PLLON;

  /* Wait till PLL is ready */
  while((RCC->CR & RCC_CR_PLLRDY) == 0)
  {
  }

  /* Select PLL as system clock source */
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

  /* Wait till PLL is used as system clock source */
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
  {
  }
}
#endif

/*
 * End of file
 */
