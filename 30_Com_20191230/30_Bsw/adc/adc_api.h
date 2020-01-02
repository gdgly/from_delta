/** *****************************************************************************
 * \file    adc_api.h
 * \brief   Service function request file for adc.c
 *
 * \section AUTHOR
 *    1. Dominik Beinlich
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
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
#include "adc_cfg.h"

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

/** ****************************************************************************
 * \brief Read the specified value 
 *
 * \param[in] eAdcIndex     Index of the specified adc channel
 * \param[out] pu16AdcVal   Raw value of the adc
 *
 * \return -
 *
 **************************************************************************** */
void ADC_vReadRaw(ADC_CFG_E_INDEX eAdcIndex,uint16 *pu16AdcVal);

#ifdef __cplusplus
  }
#endif
#endif  /* ADC_API_H */

  
/*
 * End of file
 */
