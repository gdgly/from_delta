/** ****************************************************************************
 * \file    clock.c
 * \brief   MCU clock configuration
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
 **************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "debug_llc.h"

/* Module header */
#define CLOCK_EXPORT_H
  #include "clock_api.h"
  #include "clock_scb.h"
  #include "clock_cfg.h"
  #include "clock_scfg.h"
  #include "clock_conf.h"

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

#if MG_EXTERNAL_OSCILLATOR
/* External oscillator prototype */
static void mg_vXtalOscSel(void);
#else
/* Internal oscillator prototype */
static void mg_vIntOscSel(void);
#endif

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

static uint32 mg_u32SysCoreClk;

__I uint8 mg_au8AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

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

/** ****************************************************************************
 * \brief         Initialize the System and the MCU Clock
 *                Called by startup_xxx.s
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 **************************************************************************** */
void SystemInit(void)
{
  /* FPU settings */
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  /* set CP10 and CP11 Full Access */
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  
  #endif

  /* Reset the RCC clock configuration to the default reset state */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;
  /* Reset CFGR register */
  RCC->CFGR &= 0xF87FC00C;
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;
  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;
  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;
  /* Reset PREDIV1[3:0] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;
  /* Reset USARTSW[1:0], I2CSW and TIMs bits */
  RCC->CFGR3 &= (uint32_t)0xFF00FCCC;
  /* Disable all interrupts */
  RCC->CIR = 0x00000000;

  #if MG_EXTERNAL_OSCILLATOR
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

  #if MG_VECT_TAB_SRAM
    /* Vector Table Relocation in Internal SRAM */
    SCB->VTOR = SRAM_BASE | MG_VECT_TAB_OFFSET;
  #endif
  #if MG_VECT_TAB_CCMRAM
    /* Vector Table Relocation in Internal CCMRAM */
    SCB->VTOR = CCMDATARAM_BASE | MG_VECT_TAB_OFFSET;
  #endif
  #if MG_VECT_TAB_FLASH
    /* Vector Table Relocation in Internal FLASH */
    SCB->VTOR = FLASH_BASE | MG_VECT_TAB_OFFSET;
  #endif 
  
} /* SystemInit */

/** ****************************************************************************
 * \brief         Update SystemCoreClock variable according to Clock Register 
 *                Values
 *                 The SystemCoreClock variable contains the core clock (HCLK)
 *                Each time the core clock (HCLK) changes, this function must 
 *                be called to update SystemCoreClock variable value               
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 **************************************************************************** */
void CLOCK_vSysCoreClkUpdate(void)
{
  uint32_t u32tmp = 0;
  uint32_t u32pllmull = 0;
  uint32_t u32pllsource = 0;
  uint32_t u32prediv1factor = 0;

  /* Get SYSCLK source */
  u32tmp = RCC->CFGR & RCC_CFGR_SWS;

  switch (u32tmp)
  {
    case 0x00:  /* HSI used as system clock */
      mg_u32SysCoreClk = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      mg_u32SysCoreClk = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor */
      u32pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      u32pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      u32pllmull = (u32pllmull >> 18U) + 2U;

      if (u32pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        mg_u32SysCoreClk = (HSI_VALUE >> 1) * u32pllmull;
      }
      else
      {
        u32prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1U;
        /* HSE oscillator clock selected as PREDIV1 clock entry */
        mg_u32SysCoreClk = (HSE_VALUE / u32prediv1factor) * u32pllmull;
      }
      break;
    default: /* HSI used as system clock */
      mg_u32SysCoreClk = HSI_VALUE;
      break;
  }
  /* Compute HCLK clock frequency */
  /* Get HCLK prescaler */
  u32tmp = mg_au8AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK clock frequency */
  mg_u32SysCoreClk >>= u32tmp;
} /* CLOCK_vSysCoreClkUpdate */

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

#if MG_EXTERNAL_OSCILLATOR
/** ****************************************************************************
 * \brief         This function switches to External CRYSTAL oscillator
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 **************************************************************************** */
static void mg_vXtalOscSel(void)
{
  /*
   * System Clock source:   PLL (HSE)
   * SYSCLK(Hz):            72000000
   * HCLK(Hz):              72000000
   * AHB Prescaler:         1
   * APB2 Prescaler:        1
   * APB1 Prescaler:        2
   * HSE Frequency(Hz):     16000000
   * PLLMUL:                9
   * PREDIV:                2
   * USB Clock:             DISABLE
   * Flash Latency(WS):     2
   * Prefetch Buffer:       OFF
   */

  __IO uint32_t u32StartUpCtr = 0;
  __IO uint32_t u32HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
  /* Enable HSE */
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    u32HSEStatus = RCC->CR & RCC_CR_HSERDY;
    u32StartUpCtr++;
  } while((u32HSEStatus == 0) && (u32StartUpCtr != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    u32HSEStatus = (uint32_t)0x01;
  }
  else
  {
    u32HSEStatus = (uint32_t)0x00;
  }

  if (u32HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer and set Flash Latency */
    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_1;
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
    /* PLL configuration: PLLCLK = (HSE / 2) * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
    #if RTE_MCO_OUTPUT
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_PREDIV1 |
                            RCC_CFGR_PLLXTPRE_PREDIV1_Div2 | 
                            RCC_CFGR_MCO_PLL | 
                            RCC_CFGR_MCO_PRE_4 | 
                            RCC_CFGR_PLLMULL9);
    #else
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_PREDIV1 | 
                            RCC_CFGR_PLLXTPRE_PREDIV1_Div2 | 
                            RCC_CFGR_PLLMULL9);
    #endif
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
  {
    /* If HSE fails to start-up, the app will have wrong clock configuration */
    /* Add code here to deal with this error */
  }
} /* mg_vXtalOscSel */

#else

/** ****************************************************************************
 * \brief         This function switches to Internal Oscillator
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 **************************************************************************** */
static void mg_vIntOscSel(void)
{
  /* System Clock source:   PLL (HSI)
   * SYSCLK(Hz):             64000000
   * HCLK(Hz):              64000000
   * AHB Prescaler:         1
   * APB2 Prescaler:        1
   * APB1 Prescaler:        2
   * HSI Frequency(Hz):     8000000
   * PLLMUL:                16
   * PREDIV:                2
   * USB Clock:             DISABLE
   * Flash Latency(WS):     2
   * Prefetch Buffer:       ON
   */
  /* PLL (clocked by HSI) used as System clock source */
  /* At this stage the HSI is already enabled and used as System clock source */

  /* SYSCLK, HCLK, PCLK configuration */
  /* Enable Prefetch Buffer and set Flash Latency */
  FLASH->ACR = FLASH_ACR_PRFTBE | (uint32_t)FLASH_ACR_LATENCY_1;
  /* HCLK = SYSCLK / 1 */
  RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
  /* PCLK2 = HCLK / 1 */
  RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
  /* PCLK1 = HCLK / 2 */
  RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
  /*  PLL configuration: PLLCLK = (HSI / 2) * 16 = 64 MHz */
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | 
                                      RCC_CFGR_PLLXTPRE | 
                                      RCC_CFGR_PLLMULL));
  RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_Div2 | 
                          RCC_CFGR_PLLXTPRE_PREDIV1 | 
                          RCC_CFGR_PLLMULL16);
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
} /* mg_vIntOscSel */
#endif

/*
 * End of file
 */
