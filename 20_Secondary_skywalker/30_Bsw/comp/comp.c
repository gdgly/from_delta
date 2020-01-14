/** *****************************************************************************
 * \file    comp.c
 * \brief   MCU comparator configurations
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
#define COMP_EXPORT_H
  #include "comp_api.h"
  #include "comp_scb.h"
  #include "comp_cfg.h"
  #include "comp_scfg.h"
  #include "comp_conf.h"

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void mg_vCompHwInit(void);
static void mg_vDacHwInit(void);

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
void COMP_vInit(void)
{
  /* Configure comparator */
  mg_vCompHwInit();
  /* Configure DAC's for comparator references */
  mg_vDacHwInit();
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
void COMP_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         Initialize the COMP scaling factors
 *
 * \param[in]     Reference scaling factor
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void COMP_vComp2Scale(uint32 u32ScaleFact)
{
  mg_u32q12Comp2ScaleFact = ((MG_DAC_RESOLUTION << 12) / u32ScaleFact);
}

void COMP_vComp4Scale(uint32 u32ScaleFact)
{
  mg_u32q12Comp4ScaleFact = ((MG_DAC_RESOLUTION << 12) / u32ScaleFact);
}

void COMP_vComp6Scale(uint32 u32ScaleFact)
{
  mg_u32q12Comp6ScaleFact = ((MG_DAC_RESOLUTION << 12) / u32ScaleFact);
}

/*******************************************************************************
 * Local functions (privat for module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initialize and configure MCU comparators (current limitation)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vCompHwInit(void)
{
  /* COMP Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  #if MG_COMP_2_ENA
  /* Config COMP 2 */
  COMP2->CSR = (COMP2_CSR_COMP2EN | COMP2_CSR_COMP2LOCK | MG_DAC2_CH1);  /* Connect DAC2_CH1; NOTE: has to match comp_api config */
  #endif

  #if MG_COMP_4_ENA
  /* Config COMP 4 */
  COMP4->CSR = (COMP4_CSR_COMP4EN | COMP4_CSR_COMP4LOCK | MG_DAC2_CH1);  /* Connect DAC2_CH1; NOTE: has to match comp_api config */
  #endif
  
  #if MG_COMP_6_ENA
  /* Config COMP 6 */
  COMP6->CSR = (COMP6_CSR_COMP6EN | COMP6_CSR_COMP6LOCK | MG_DAC2_CH1);  /* Connect DAC2_CH1; NOTE: has to match comp_api config */
  #endif
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initializes the DAC registers
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
static void mg_vDacHwInit(void)
{
  /* Temporary typedefs */
  DAC_InitTypeDef     DAC_InitConfig;

  /* DAC1 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);
  /* DAC2 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC2, ENABLE);

  DAC_InitConfig.DAC_Trigger = DAC_Trigger_None;
  DAC_InitConfig.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitConfig.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1;
  DAC_InitConfig.DAC_Buffer_Switch = DAC_OutputSwitch_Disable;

  /* Configure DAC1_OUT1 to generate extender current limitation reference voltage */
  //DAC_Init(DAC1, DAC_Channel_1, &DAC_InitConfig);
  /* Configure DAC2_OUT1 to generate current limitation reference voltage */
  DAC_Init(DAC2, DAC_Channel_1, &DAC_InitConfig);

  /* Enable DAC's */
  //DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
  DAC_Cmd(DAC2, DAC_Channel_1, ENABLE);
}


/*
 * End of file
 */
