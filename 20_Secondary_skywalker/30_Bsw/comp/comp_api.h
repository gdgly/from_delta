/** *****************************************************************************
 * \file    comp_api.h
 * \brief   Service function request file for comp.c
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

#ifndef COMP_API_H
#define COMP_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"
#include "comp_conf.h"

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
void COMP_vInit(void);

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
void COMP_vDeInit(void);

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
void COMP_vComp2Scale(uint32 u32ScaleFact);
void COMP_vComp4Scale(uint32 u32ScaleFact);
void COMP_vComp6Scale(uint32 u32ScaleFact);

/** *****************************************************************************
 * \brief         Comparator reference setup
 *
 * \param[in]     CompRef: Comparator reference value
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline void COMP_vSetComp2Ref(uint32 u32CompRef)
{
  /* Scale reference value and set DAC */
  MG_REG_DAC2_CHANNEL1_DATA = ((mg_u32q12Comp2ScaleFact * u32CompRef) >> 12);
}
__attribute__((section ("ccram")))
extern inline void COMP_vSetComp4Ref(uint32 u32CompRef)
{
  /* Scale reference value and set DAC */
  MG_REG_DAC2_CHANNEL1_DATA = ((mg_u32q12Comp4ScaleFact * u32CompRef) >> 12);
}
__attribute__((section ("ccram")))
extern inline void COMP_vSetComp6Ref(uint32 u32CompRef)
{
  /* Scale reference value and set DAC */
  MG_REG_DAC2_CHANNEL1_DATA = ((mg_u32q12Comp6ScaleFact * u32CompRef) >> 12);
}

/** *****************************************************************************
 * \brief         Read comparator output level
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        Comparator output status
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline uint8 COMP_u8Comp2OutputStatus()
{
  return MG_REG_COMP2_OUT;
}
__attribute__((section ("ccram")))
extern inline uint8 COMP_u8Comp4OutputStatus()
{
  return MG_REG_COMP4_OUT;
}
__attribute__((section ("ccram")))
extern inline uint8 COMP_u8Comp6OutputStatus()
{
  return MG_REG_COMP6_OUT;
}


#ifdef __cplusplus
  }
#endif
#endif  /* COMP_API_H */

  
/*
 * End of file
 */
