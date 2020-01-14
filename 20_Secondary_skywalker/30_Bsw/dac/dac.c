/** *****************************************************************************
 * \file    dac.c
 * \brief   MCU DAC configurations
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
#define DAC_EXPORT_H
  #include "dac_api.h"
  #include "dac_scb.h"
  #include "dac_cfg.h"
  #include "dac_scfg.h"
  #include "dac_conf.h"

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/

static void mg_vDacHwInit(void);

/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/
uint32 mg_u32q12Dac1Ch1ScaleFact = 0U;
uint32 mg_u32q12Dac1Ch2ScaleFact = 0U;
uint32 mg_u32q12Dac2Ch1ScaleFact = 0U;

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
void DAC_vInit(void)
{
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
void DAC_vDeInit(void)
{

}

/** *****************************************************************************
 * \brief         Initialize the DAC scaling factors
 *
 * \param[in]     Reference scaling factor
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void DAC_vDac1Ch1Scale(uint32 u32ScaleFact)
{
  mg_u32q12Dac1Ch1ScaleFact = ((MG_DAC_RESOLUTION << 12) / u32ScaleFact);
}

void DAC_vDac1Ch2Scale(uint32 u32ScaleFact)
{
  mg_u32q12Dac1Ch2ScaleFact = ((MG_DAC_RESOLUTION << 12) / u32ScaleFact);
}

void DAC_vDac2Ch1Scale(uint32 u32ScaleFact)
{
  mg_u32q12Dac2Ch1ScaleFact = ((MG_DAC_RESOLUTION << 12) / u32ScaleFact);
}

/** *****************************************************************************
 * \brief         Write DAC value
 *
 * \param[in]     DacId: can be 1 or 2. DacCh: can be 1 or 2. DacVal: any value between 0 and 4096
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void DAC_vWriteDacValue(uint8 u8DacId, uint8 u8DacCh, uint16 u16q12DacVal)
{
  /* DAC1 */
  if (u8DacId == MG_DAC1)
  {
    /* Channel 1 */
    if (u8DacCh == MG_CH1)
    {
      MG_REG_DAC1_CHANNEL1_DATA = u16q12DacVal;
    }
    /* Channel 2 */
    if (u8DacCh == MG_CH2)
    {
      MG_REG_DAC1_CHANNEL2_DATA = u16q12DacVal;
    }
  }
  /* DAC2 */
  if (u8DacId == MG_DAC2)
  {
    /* Channel 1 */
    if (u8DacCh == MG_CH1)
    {
      MG_REG_DAC2_CHANNEL1_DATA = u16q12DacVal;
    }
  } 
}

/*******************************************************************************
 * Local functions (privat for module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initialize the DAC module
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
  /*
   * NOTE: Take care of DAC configuration for OCP in comp.c
   * DAC1CH1 has output buffer
   * DAC1CH2 and DAC2CH1 has output switch
   * Set DAC data: DAC_SetChannel2Data(DAC1, DAC_Align_12b_R, DATA_IN_12BIT);
   * Software trigger for DAC (required to apply new data to DAC output): DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG2;
   */

  /* Temporary typedefs */
  static DAC_InitTypeDef     DAC_InitConfig;

  /* DAC1 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);
  
  /* Configure trigger none */
  DAC_InitConfig.DAC_Trigger = DAC_Trigger_None;
  /* Wave generation none */
  DAC_InitConfig.DAC_WaveGeneration = DAC_WaveGeneration_None;
  /* Output buffer disable */
  DAC_InitConfig.DAC_Buffer_Switch = DAC_BufferSwitch_Enable;

  /* Use initialized structure for DAC1 channel 1 */
  DAC_Init(DAC1, DAC_Channel_1, &DAC_InitConfig);

  /* Configure trigger none */
  DAC_InitConfig.DAC_Trigger = DAC_Trigger_None;
  /* Wave generation none */
  DAC_InitConfig.DAC_WaveGeneration = DAC_WaveGeneration_None;
  /* Output buffer disable */
  DAC_InitConfig.DAC_Buffer_Switch = DAC_OutputSwitch_Enable;

  /* Use initialized structure for DAC1 channel 2 */
  DAC_Init(DAC1, DAC_Channel_2, &DAC_InitConfig);

  /* Enable DAC's */
  DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
  DAC_Cmd(DAC1, DAC_Channel_2, ENABLE);
}

/*
 * End of file
 */
