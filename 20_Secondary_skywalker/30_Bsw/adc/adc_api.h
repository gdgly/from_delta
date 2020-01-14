/** *****************************************************************************
 * \file    adc_api.h
 * \brief   Service function request file for adc.c
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

#ifndef ADC_API_H
#define ADC_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "adc_conf.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
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
void ADC_vInit(void);

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
void ADC_vDeInit(void);

/** *****************************************************************************
 * \brief         ADC buffer transfer to HWIO for conversion to physical units
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void ADC_vAdcUnitConv(void);

/** *****************************************************************************
 * \brief         ADC DMA NVIC configuration
 *
 * \param[in]     DmaChId: can be 1 to 7. PrePriority: can be 1 to 7. SubPriority: can be 1 to 7
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void ADC_vAdcDmaNvicCfg(uint8 u8DmaChId, uint8 u8PrePriority, uint8 u8SubPriority);

/** *****************************************************************************
 * \brief         Reset DMA ISR flag
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void ADC_vAdcDma1Ch1IsrFlgReset(void)
{
  MG_REG_DMA_CLR_DMA1_TC1_FLG;
}

__attribute__((section ("ccram")))
extern inline void ADC_vAdcDma1Ch2IsrFlgReset(void)
{
  MG_REG_DMA_CLR_DMA1_TC2_FLG;
}

/** *****************************************************************************
 * \brief         Initialize the ADC scaling factors
 *
 * \param[in]     Reference scaling factor
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void ADC_vVoltOutExtScale(uint16 u16ScaleFact);
void ADC_vVoltOutIntScale(uint16 u16ScaleFact);
void ADC_vCurrOutScale(uint16 u16ScaleFact);
void ADC_vAcsBusScale(uint16 u16ScaleFact);
void ADC_vAcsLocalScale(uint16 u16ScaleFact);
void ADC_vVoltRef3V3Scale(uint16 u16ScaleFact);
void ADC_vAdcResNtcScale(uint16 u16ScaleFact);

/** *****************************************************************************
 * \brief         Convert ADC values and return units
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        Converted ADC value
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleVoltOutExt(void)
{
  return ((mg_u32q12AdcScaleFactVoltOutExt * MG_ADC_1_BUFFER_V_OUT_EXT) >> 12);
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleVoltOutInt(void)
{
  return ((mg_u32q12AdcScaleFactVoltOutInt * MG_ADC_1_BUFFER_V_OUT_INT) >> 12);
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleCurrOut(void)
{
  return ((mg_u32q12AdcScaleFactCurrOut * MG_ADC_1_BUFFER_I_OUT) >> 12);
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleAcsBus(void)
{
  return ((mg_u32q12AdcScaleFactAcsBus * MG_ADC_1_BUFFER_ACS_BUS) >> 12);
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleAcsLocal(void)
{
  return ((mg_u32q12AdcScaleFactAcsLocal * MG_ADC_1_BUFFER_ACS_LOCAL) >> 12);
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleVoltRef3V3(void)
{
  return ((mg_u32q12AdcScaleFactVoltRef3V3 * MG_ADC_1_BUFFER_2V5REF) >> 12);
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleNtcOring(void)
{
  return (SAT_H(((mg_u321OhmAdcScaleFactResNtc * MG_ADC_2_BUFFER_NTC_ORING) / (SAT_L((MG_ADC_RESOLUTION - MG_ADC_2_BUFFER_NTC_ORING), 1U))), 65535));
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleNtcSr(void)
{
  return (SAT_H(((mg_u321OhmAdcScaleFactResNtc * MG_ADC_2_BUFFER_NTC_SR) / (SAT_L((MG_ADC_RESOLUTION - MG_ADC_2_BUFFER_NTC_SR), 1U))), 65535));
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleNtcOringmV(void)
{
  return MG_ADC_2_BUFFER_NTC_ORING;;
}

__attribute__((section ("ccram")))
extern inline uint16 ADC_u16AdcSampleNtcSrmV(void)
{
  return MG_ADC_2_BUFFER_NTC_SR;
}


#ifdef __cplusplus
  }
#endif
#endif  /* ADC_API_H */

  
/*
 * End of file
 */
