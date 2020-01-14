/** *****************************************************************************
 * \file    port.c
 * \brief   MCU port configurations
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

#include "StdPeriphDriver.h"
#include "global.h"
#include "debug_llc.h"

/* Module header */
#define PORT_EXPORT_H
  #include "port_api.h"
  #include "port_scb.h"
  #include "port_cfg.h"
  #include "port_scfg.h"
  #include "port_conf.h"

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void mg_vPortAHwInit(void);
static void mg_vPortBHwInit(void);
static void mg_vPortCHwInit(void);
static void mg_vPortDHwInit(void);
static void mg_vSetGpioPin(uint8 u8Port, uint8 u8Pin, uint8 u8Status);
static uint8 mg_u8ReadGpioPin(uint8 u8Port, uint8 u8Pin);
static void mg_vConfigGpioPin(uint8 u8Port, uint16 u16Pin, uint16 u8Mode, uint8 u8OType, uint8 u8Speed, uint8 u8PuPd, uint8 u8ModeAf);

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
void PORT_vInit(void)
{
  /* Initialize GPIO pin outputs */
  mg_vSetGpioPin(MG_PORT_PWM_ON, MG_PIN_PWM_ON, SET);         /* Active low */
  mg_vSetGpioPin(MG_PORT_ACS_ON, MG_PIN_ACS_ON, SET);         /* Active low */
  mg_vSetGpioPin(MG_PORT_ORING_EN, MG_PIN_ORING_EN, RESET);   /* Active high */
  mg_vSetGpioPin(MG_PORT_OVP_CLR, MG_PIN_OVP_CLR, RESET);     /* Active high */
  mg_vSetGpioPin(MG_PORT_LLC_FAULT, MG_PIN_LLC_FAULT, RESET); /* Active high */

  /* Init ports */
  mg_vPortAHwInit();
  mg_vPortBHwInit();
  mg_vPortCHwInit();
  mg_vPortDHwInit();
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
void PORT_vDeInit(void)
{
  mg_vSetGpioPin(MG_PORT_PWM_ON, MG_PIN_PWM_ON, SET);         /* Active low */
  mg_vSetGpioPin(MG_PORT_ACS_ON, MG_PIN_ACS_ON, SET);         /* Active low */
  mg_vSetGpioPin(MG_PORT_ORING_EN, MG_PIN_ORING_EN, RESET);   /* Active high */
  mg_vSetGpioPin(MG_PORT_OVP_CLR, MG_PIN_OVP_CLR, RESET);     /* Active high */
  mg_vSetGpioPin(MG_PORT_LLC_FAULT, MG_PIN_LLC_FAULT, RESET); /* Active high */
}

/** *****************************************************************************
 * \brief         Set or reset GPIO pin
 *
 * \param[in]     Set or Reset
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void PORT_vSetGpioPinPwmOn(uint8 u8Status)
{
  mg_vSetGpioPin(MG_PORT_PWM_ON, MG_PIN_PWM_ON, u8Status);
}

void PORT_vSetGpioPinIshareOn(uint8 u8Status)
{
  mg_vSetGpioPin(MG_PORT_ACS_ON, MG_PIN_ACS_ON, u8Status);
}

void PORT_vSetGpioPinOvpClr(uint8 u8Status)
{
  mg_vSetGpioPin(MG_PORT_OVP_CLR, MG_PIN_OVP_CLR, u8Status);
}

void PORT_vInputGpioPinOvpClr(void)
{
  mg_vConfigGpioPin(MG_PORT_OVP_CLR, MG_PIN_OVP_CLR, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);
}

void PORT_vOutputGpioPinOvpClr(void)
{
  mg_vConfigGpioPin(MG_PORT_OVP_CLR, MG_PIN_OVP_CLR, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);
}

void PORT_vSetGpioPinOringEn(uint8 u8Status)
{
  mg_vSetGpioPin(MG_PORT_ORING_EN, MG_PIN_ORING_EN, u8Status);
}

void PORT_vSetGpioPinLlcFault(uint8 u8Status)
{
  mg_vSetGpioPin(MG_PORT_LLC_FAULT, MG_PIN_LLC_FAULT, u8Status);
}

/** *****************************************************************************
 * \brief         Read GPIO pin
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    Pin status
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 PORT_u8ReadGpioPinBulkOk(void)
{
  return mg_u8ReadGpioPin(MG_PORT_BULK_OK, MG_PIN_BULK_OK);
}

uint8 PORT_u8ReadGpioPinOvp(void)
{
  return mg_u8ReadGpioPin(MG_PORT_OVP, MG_PIN_OVP);
}

uint8 PORT_u8ReadGpioPinLlcSwitchEn(void)
{
//  return mg_u8ReadGpioPin(MG_PORT_LLC_SWITCH_EN, MG_PIN_LLC_SWITCH_EN);
  return 1;
}

uint8 PORT_u8ReadGpioPinLlcHalt(void)
{
  return mg_u8ReadGpioPin(MG_PORT_LLC_HALT, MG_PIN_LLC_HALT);
}

uint8 PORT_u8ReadGpioPinUartAddr(void)
{
//  return mg_u8ReadGpioPin(MG_PORT_UART_ADDR, MG_PIN_UART_ADDR);
  return 0;
}

/*******************************************************************************
 * Local functions (privat for module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initialize and configure MCU port A
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vPortAHwInit(void)
{
  /* Enable GPIOA peripheral clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /*
   * ADC channel mapping:
   * Configure ADC1 inputs: PA0 = ADC1_IN1 (fast channel)
   *                        PA1 = ADC1_IN2 (fast channel)
   *                        PA2 = ADC1_IN3 (fast channel)
   *                        PA3 = ADC1_IN4 (fast channel)
   *
   * Configure ADC2 inputs: PA4 = ADC2_IN1 (fast channel) / DAC1_OUT1
   *                        PA5 = ADC2_IN2 (fast channel) / DAC1_OUT2
   *                        PA6 = ADC2_IN3 (fast channel) / DAC2_OUT1
   *                        PA7 = ADC2_IN4 (fast channel)
   */
  mg_vConfigGpioPin(PORT_A, PIN_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC VOLT_OUT_EXT_BUF */
  mg_vConfigGpioPin(PORT_A, PIN_1, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC VOLT_OUT_INT_BUF */
  mg_vConfigGpioPin(PORT_A, PIN_2, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC CURRENT_OUT_BUF */
  mg_vConfigGpioPin(PORT_A, PIN_3, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC ACS_BUS_BUF */
  mg_vConfigGpioPin(PORT_A, PIN_4, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* DAC ACS_LOCAL */
  mg_vConfigGpioPin(PORT_A, PIN_5, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* DAC DAC1_OUT2 */
  mg_vConfigGpioPin(PORT_A, PIN_6, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC NTC ORING / DAC CT_PROTECTION */
  mg_vConfigGpioPin(PORT_A, PIN_7, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* COMP2 CT current limitation */
  mg_vConfigGpioPin(PORT_A, PIN_8, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_HRTIMER_PWM);    /* PWM AD */
  mg_vConfigGpioPin(PORT_A, PIN_9, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_HRTIMER_PWM);    /* PWM BC */
  mg_vConfigGpioPin(PORT_A, PIN_10, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_HRTIMER_PWM);   /* PWM SR A */
  mg_vConfigGpioPin(PORT_A, PIN_11, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_HRTIMER_PWM);   /* PWM SR B */
  mg_vConfigGpioPin(PORT_A, PIN_12, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);               /* OUT ACS_EN */
  #if (FALSE == DEBUG_MODE)
  mg_vConfigGpioPin(PORT_A, PIN_13, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_SWDIO_SWCLK);   /* SWDIO */
  mg_vConfigGpioPin(PORT_A, PIN_14, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_SWDIO_SWCLK);   /* SWCLK */
  #endif
  mg_vConfigGpioPin(PORT_A, PIN_15, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_I2C);           /* SCL */
}

/** *****************************************************************************
 * \brief         Initialize and configure MCU port B
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vPortBHwInit(void)
{
  /* Enable GPIOB peripheral clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /*
   * Configure ADC1 inputs: PB0  = ADC1_IN11 (slow channel)
   *                        PB1  = ADC1_IN12 (slow channel)
   *                        PB13 = ADC1_IN13 (slow channel)
   *
   * Configure ADC2 inputs: PB2  = ADC2_IN12 (slow channel)
   *                        PB12 = ADC2_IN13 (slow channel)
   *                        PB14 = ADC2_IN14 (slow channel)
   *                        PB15 = ADC2_IN15 (slow channel)
   *
   * Configure comparator:  PB0 = COMP4
   *                        PB11 = COMP6
   */
  mg_vConfigGpioPin(PORT_B, PIN_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC 2V5_REF_BUF */
  mg_vConfigGpioPin(PORT_B, PIN_1, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC ACS_LOCAL_BUF */
  mg_vConfigGpioPin(PORT_B, PIN_2, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC NTC_SR_BUF */             
  mg_vConfigGpioPin(PORT_B, PIN_3, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_UP, MG_UART);               /* UART TX */
  mg_vConfigGpioPin(PORT_B, PIN_4, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_UP, MG_UART);               /* UART RX */
  mg_vConfigGpioPin(PORT_B, PIN_5, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                /* OUT PORT_PWM_ON */
  mg_vConfigGpioPin(PORT_B, PIN_6, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 
  mg_vConfigGpioPin(PORT_B, PIN_7, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 
  mg_vConfigGpioPin(PORT_B, PIN_8, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                /* IN/OUT PORT_OVP_CLR */
  mg_vConfigGpioPin(PORT_B, PIN_9, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* IN PORT_OVP */
  mg_vConfigGpioPin(PORT_B, PIN_10, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);              
  mg_vConfigGpioPin(PORT_B, PIN_11, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                
  mg_vConfigGpioPin(PORT_B, PIN_12, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);               /* OUT LLC FAULT */
  mg_vConfigGpioPin(PORT_B, PIN_13, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                /* IN PORT_BULK_OK */
  mg_vConfigGpioPin(PORT_B, PIN_14, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);               /* Debug */
  mg_vConfigGpioPin(PORT_B, PIN_15, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                /* IN PORT_LLC_HALT */
}

/** *****************************************************************************
 * \brief         Initialize and configure MCU port C
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vPortCHwInit(void)
{
  /* Enable GPIOC peripheral clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  mg_vConfigGpioPin(PORT_C, PIN_0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_5, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_6, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_7, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_8, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_9, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_10, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_11, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_C, PIN_13, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_TIMER1_CH1_PWM); /* PWM ORING_PULSE */
  mg_vConfigGpioPin(PORT_C, PIN_14, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                /* OUT PORT_ORING_EN */
  mg_vConfigGpioPin(PORT_C, PIN_15, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);               
}

/** *****************************************************************************
 * \brief         Initialize and configure MCU port D
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vPortDHwInit(void)
{
  /* Enable GPIOD peripheral clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

  mg_vConfigGpioPin(PORT_D, PIN_0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_5, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_6, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_7, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_8, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_9, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_10, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_11, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_13, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_14, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
  mg_vConfigGpioPin(PORT_D, PIN_15, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL, 0);
}

/** *****************************************************************************
 * \brief         Set or reset GPIO pin at dedicated port
 *
 * \param[in]     Port: 1(A) - 4(D); Pin: any number between 0 - 15; Status: SET or RESET
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void mg_vSetGpioPin(uint8 u8Port, uint8 u8Pin, uint8 u8Status)
{
  /* PORT A */
  if (u8Port == 1)
  {
    /* If GPIO enabled set the output to high */
    if (u8Status == SET)
    {
      GPIOA->BSRR = (1 << u8Pin);
    }
    /* Else set output to low */
    else
    {
      GPIOA->BRR = (1 << u8Pin);
    }
  }
  /* PORT B */
  else if (u8Port == 2)
  {
    /* If GPIO enabled set the output to high */
    if (u8Status == SET)
    {
      GPIOB->BSRR = (1 << u8Pin);
    }
    /* Else set output to low */
    else
    {
      GPIOB->BRR = (1 << u8Pin);
    }
  }
  /* PORT C */
  else if (u8Port == 3)
  {
    /* If GPIO enabled set the output to high */
    if (u8Status == SET)
    {
      GPIOC->BSRR = (1 << u8Pin);
    }
    /* Else set output to low */
    else
    {
      GPIOC->BRR = (1 << u8Pin);
    }
  }
  /* PORT D */
  else if (u8Port == 4)
  {
    /* If GPIO enabled set the output to high */
    if (u8Status == SET)
    {
      GPIOD->BSRR = (1 << u8Pin);
    }
    /* Else set output to low */
    else
    {
      GPIOD->BRR = (1 << u8Pin);
    }
  }
}

/** *****************************************************************************
 * \brief         Read GPIO pin at dedicated port
 *
 * \param[in]     Port: 1(A) - 4(D); Pin: any number between 0 - 15
 * \param[in,out] -
 * \param[out]    Pin status
 *
 * \return        -
 *
 ***************************************************************************** */
uint8 mg_u8ReadGpioPin(uint8 u8Port, uint8 u8Pin)
{
  uint8 u8Status;
  
  /* PORT A */
  if (u8Port == 1)
  {
    if ((GPIOA->IDR & (1 << u8Pin)) != (uint32)RESET)
    {
      u8Status = SET;
    }
    else
    {
      u8Status = RESET;
    }
  }
  /* PORT B */
  else if (u8Port == 2)
  {
    if ((GPIOB->IDR & (1 << u8Pin)) != (uint32)RESET)
    {
      u8Status = SET;
    }
    else
    {
      u8Status = RESET;
    }
  }
  /* PORT C */
  else if (u8Port == 3)
  {
    if ((GPIOC->IDR & (1 << u8Pin)) != (uint32)RESET)
    {
      u8Status = SET;
    }
    else
    {
      u8Status = RESET;
    }
  }
  /* PORT D */
  else if (u8Port == 4)
  {
    if ((GPIOD->IDR & (1 << u8Pin)) != (uint32)RESET)
    {
      u8Status = SET;
    }
    else
    {
      u8Status = RESET;
    }
  }
  return u8Status;
}

/** *****************************************************************************
 * \brief         Set GPIO pin
 *
 * \param[in]     Port: A - D, Pin: 0 - 15, Mode: In, Out, Af, An, OType: Push pull, open drain, 
 *                Speed: 2-50Mhz, PuPd: Pull up/down/no pull, ModeAf: When use AF choose mode
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void mg_vConfigGpioPin(uint8 u8Port, uint16 u16Pin, uint16 u8Mode, uint8 u8OType, uint8 u8Speed, uint8 u8PuPd, uint8 u8ModeAf)
{
  uint32_t tmpreg = 0x00;

  switch (u8Port)
  {
    case PORT_A:
    {
      if ((u8Mode == GPIO_Mode_OUT) || (u8Mode == GPIO_Mode_AF))
      {
        /* Speed mode configuration */
        GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (u16Pin * 2));
        GPIOA->OSPEEDR |= ((uint32_t)(u8Speed) << (u16Pin * 2));

        /* Output mode configuration */
        GPIOA->OTYPER &= ~((GPIO_OTYPER_OT_0) << u16Pin);
        GPIOA->OTYPER |= (uint16_t)(((uint16_t)u8OType) << (u16Pin));
      }
      /* Mode configuration */
      GPIOA->MODER  &= ~(GPIO_MODER_MODER0 << (u16Pin * 2));
      GPIOA->MODER |= (((uint32_t)u8Mode) << (u16Pin * 2));

      /* 
       * Use temporary variable to update PUPDR register configuration, to avoid 
       * unexpected transition in the GPIO pin configuration. 
      */
      tmpreg = GPIOA->PUPDR;
      tmpreg &= ~(GPIO_PUPDR_PUPDR0 << (u16Pin * 2));
      tmpreg |= (((uint32_t)u8PuPd) << (u16Pin * 2));
      GPIOA->PUPDR = tmpreg;
      /* Setup AF */
      if (u8Mode == GPIO_Mode_AF)
      {
        GPIO_PinAFConfig(GPIOA, u16Pin, u8ModeAf);
      }
      break;
    }
    case PORT_B:
    {
      if ((u8Mode == GPIO_Mode_OUT) || (u8Mode == GPIO_Mode_AF))
      {
        /* Speed mode configuration */
        GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (u16Pin * 2));
        GPIOB->OSPEEDR |= ((uint32_t)(u8Speed) << (u16Pin * 2));

        /* Output mode configuration */
        GPIOB->OTYPER &= ~((GPIO_OTYPER_OT_0) << u16Pin);
        GPIOB->OTYPER |= (uint16_t)(((uint16_t)u8OType) << (u16Pin));
      }
      /* Mode configuration */
      GPIOB->MODER  &= ~(GPIO_MODER_MODER0 << (u16Pin * 2));
      GPIOB->MODER |= (((uint32_t)u8Mode) << (u16Pin * 2));

      /* 
       * Use temporary variable to update PUPDR register configuration, to avoid 
       * unexpected transition in the GPIO pin configuration. 
      */
      tmpreg = GPIOB->PUPDR;
      tmpreg &= ~(GPIO_PUPDR_PUPDR0 << (u16Pin * 2));
      tmpreg |= (((uint32_t)u8PuPd) << (u16Pin * 2));
      GPIOB->PUPDR = tmpreg;
      /* Setup AF */
      if (u8Mode == GPIO_Mode_AF)
      {
        GPIO_PinAFConfig(GPIOB, u16Pin, u8ModeAf);
      }
      break;
    }
    case PORT_C:
    {
      if ((u8Mode == GPIO_Mode_OUT) || (u8Mode == GPIO_Mode_AF))
      {
        /* Speed mode configuration */
        GPIOC->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (u16Pin * 2));
        GPIOC->OSPEEDR |= ((uint32_t)(u8Speed) << (u16Pin * 2));

        /* Output mode configuration */
        GPIOC->OTYPER &= ~((GPIO_OTYPER_OT_0) << u16Pin);
        GPIOC->OTYPER |= (uint16_t)(((uint16_t)u8OType) << (u16Pin));
      }
      /* Mode configuration */
      GPIOC->MODER  &= ~(GPIO_MODER_MODER0 << (u16Pin * 2));
      GPIOC->MODER |= (((uint32_t)u8Mode) << (u16Pin * 2));

      /* 
       * Use temporary variable to update PUPDR register configuration, to avoid 
       * unexpected transition in the GPIO pin configuration. 
      */
      tmpreg = GPIOC->PUPDR;
      tmpreg &= ~(GPIO_PUPDR_PUPDR0 << (u16Pin * 2));
      tmpreg |= (((uint32_t)u8PuPd) << (u16Pin * 2));
      GPIOC->PUPDR = tmpreg;
      /* Setup AF */
      if (u8Mode == GPIO_Mode_AF)
      {
        GPIO_PinAFConfig(GPIOC, u16Pin, u8ModeAf);
      }
      break;
    }
    case PORT_D:
    {
      if ((u8Mode == GPIO_Mode_OUT) || (u8Mode == GPIO_Mode_AF))
      {
        /* Speed mode configuration */
        GPIOD->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (u16Pin * 2));
        GPIOD->OSPEEDR |= ((uint32_t)(u8Speed) << (u16Pin * 2));

        /* Output mode configuration */
        GPIOD->OTYPER &= ~((GPIO_OTYPER_OT_0) << u16Pin);
        GPIOD->OTYPER |= (uint16_t)(((uint16_t)u8OType) << (u16Pin));
      }
      /* Mode configuration */
      GPIOD->MODER  &= ~(GPIO_MODER_MODER0 << (u16Pin * 2));
      GPIOD->MODER |= (((uint32_t)u8Mode) << (u16Pin * 2));

      /* 
       * Use temporary variable to update PUPDR register configuration, to avoid 
       * unexpected transition in the GPIO pin configuration. 
      */
      tmpreg = GPIOD->PUPDR;
      tmpreg &= ~(GPIO_PUPDR_PUPDR0 << (u16Pin * 2));
      tmpreg |= (((uint32_t)u8PuPd) << (u16Pin * 2));
      GPIOD->PUPDR = tmpreg;
      /* Setup AF */
      if (u8Mode == GPIO_Mode_AF)
      {
        GPIO_PinAFConfig(GPIOD, u16Pin, u8ModeAf);
      }
      break;
    }
  }
}


/*
 * End of file
 */
