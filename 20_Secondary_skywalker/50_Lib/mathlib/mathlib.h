/** *****************************************************************************
 * \file    mathlib.h
 * \brief   Mathematical function library header
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

#ifndef MATHLIB_H
#define MATHLIB_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "StdPeriphDriver.h"
#include "global.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/***********************************************
 * Configuration
 **********************************************/
#define MG_FPU            1   /* 1 = Math accelerator present */

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         This function calculates the square root from u32Value
 *
 * \param[in]     u32Value - value to be square rooted
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        u16ResultSquareRoot (Square rot from from u32Value)
 *
 ***************************************************************************** */
__attribute__((section ("ccram")))
extern inline uint16 MATHLIB_u16CalcSqrt(uint32 u32Value)
{
  #if MG_FPU
  /* Use accelerated SQRT calculation */
  return ((uint16)__sqrtf((float32)((uint32)u32Value)));
  #else
  /* Calculate SQRT manually */
  uint8 u8BitPos;
  uint16 u16PrevResult;
  uint16 u16ResultSqrt = 0U;
  uint32 u32ResultSqrt;

  /* If u32Value is not zero then perform SQRT calculation */
  if (0U != u32Value)
  {
    for (u8BitPos = 16U; u8BitPos >= 1U; u8BitPos--)
    {
      u16PrevResult = u16ResultSqrt;
      u16ResultSqrt |= (0x0001 << (u8BitPos - 1U));
      u32ResultSqrt = (u16ResultSqrt * u16ResultSqrt);
      if (u32Value < u32ResultSqrt)
      {
        u16ResultSqrt = u16PrevResult;
      }
    }
  }
  return (u16ResultSqrt);
  #endif
}


#ifdef __cplusplus
  }
#endif
#endif  /* MATHLIB_H */


/*
 * End of file
 */
