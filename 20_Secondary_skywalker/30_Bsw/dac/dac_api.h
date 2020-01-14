/** *****************************************************************************
 * \file    dac_api.h
 * \brief   Service function request file for dac.c
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

#ifndef DAC_API_H
#define DAC_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "dac_conf.h"

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
void DAC_vInit(void);

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
void DAC_vDeInit(void);

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
void DAC_vDac1Ch1Scale(uint32 u32ScaleFact);
void DAC_vDac1Ch2Scale(uint32 u32ScaleFact);
void DAC_vDac2Ch1Scale(uint32 u32ScaleFact);

/** *****************************************************************************
 * \brief         Write value to DAC
 *
 * \param[in]     DacId: can be 1 or 2. DacCh: can be 1 or 2. DacVal: any value between 0 and 4096
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void DAC_vWriteDacValue(uint8 u8DacId, uint8 u8DacCh, uint16 u16q12DacVal);

/** *****************************************************************************
 * \brief         Write value to DAC (direct access)
 *
 * \param[in]     u16q12DacVal: DAC value
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void DAC_vSetDac1Ch1(uint16 u16q12DacVal)
{
  /* Set DAC1Ch1 */
  MG_REG_DAC1_CHANNEL1_DATA = u16q12DacVal;
}

__attribute__((section ("ccram")))
extern inline void DAC_vSetDac1Ch2(uint16 u16q12DacVal)
{
  /* Set DAC1Ch2 */
  MG_REG_DAC1_CHANNEL2_DATA = u16q12DacVal;
}

__attribute__((section ("ccram")))
extern inline void DAC_vSetDac2Ch1(uint16 u16q12DacVal)
{
  /* Set DAC2Ch1 */
  MG_REG_DAC2_CHANNEL1_DATA = u16q12DacVal;
}

/** *****************************************************************************
 * \brief         Write value to DAC (scaled)
 *
 * \param[in]     u16q12DacVal: DAC value
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
extern inline void DAC_vSetDac1Ch1Scaled(uint16 u16DacValueScaled)
{
  /* Scale reference value and set DAC */
  MG_REG_DAC1_CHANNEL1_DATA = ((mg_u32q12Dac1Ch1ScaleFact * u16DacValueScaled) >> 12);
}

extern inline void DAC_vSetDac1Ch2Scaled(uint16 u16DacValueScaled)
{
  /* Scale reference value and set DAC */
  MG_REG_DAC1_CHANNEL2_DATA = ((mg_u32q12Dac1Ch2ScaleFact * u16DacValueScaled) >> 12);
}

extern inline void DAC_vSetDac2Ch1Scaled(uint16 u16DacValueScaled)
{
  /* Scale reference value and set DAC */
  MG_REG_DAC2_CHANNEL1_DATA = ((mg_u32q12Dac2Ch1ScaleFact * u16DacValueScaled) >> 12);
}


#ifdef __cplusplus
  }
#endif
#endif  /* DAC_API_H */

  
/*
 * End of file
 */
