/** ****************************************************************************
 * \file    buffer.c
 * \brief   Buffer module
 *
 * \section AUTHOR
 *  J. Boyd
 *
 * \section SVN
 *  $Date: 2019-05-08 09:09:27 +0800 (Wed, 08 May 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 179 $
 *
 * \section LICENSE
 *  Copyright (c) 2016 Delta Energy Systems (Germany) GmbH.
 *  All rights reserved.
 **************************************************************************** */

/*******************************************************************************
 * Included headers
 ******************************************************************************/

#include <global.h>

/*******************************************************************************
 * Own module headers
 ******************************************************************************/
#define BUFFER_EXPORT_H
#include "buffer_api.h"
#include "buffer_cfg.h"
#include "buffer_conf.h"
#include "buffer_scb.h"
#include "buffer_scfg.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
static uint32 mg_u32Buffer1ms[(uint8)BUFFER_CFG_E_INDEX_COUNT] ={0u}; /* Buffer for sums */
static uint16 mg_u16Means1ms[(uint8)BUFFER_CFG_E_INDEX_COUNT] = {0u};
static uint32 mg_u32Buffer10ms[(uint8)BUFFER_CFG_E_INDEX_COUNT] ={0u}; /* Buffer for sums */
static uint16 mg_u16Means10ms[(uint8)BUFFER_CFG_E_INDEX_COUNT] = {0u};

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/
/** *****************************************************************************
 * \brief         Initialize the buffer module
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void BUFFER_SCB_vInit(void)
{
  uint8 u8Count;

#ifdef DEBUG
  UARTprintf("%s()\n", __FUNCTION__);
#endif

  for (u8Count = 0u; u8Count < (uint8)BUFFER_CFG_E_INDEX_COUNT; u8Count++)
  {
    mg_u32Buffer1ms[u8Count] = 0u;
    mg_u16Means1ms[u8Count] = 0u;
  }
  for (u8Count = 0u; u8Count < (uint8)BUFFER_CFG_E_INDEX_COUNT; u8Count++)
  {
    mg_u32Buffer10ms[u8Count] = 0u;
    mg_u16Means10ms[u8Count] = 0u;
  }
}

/** *****************************************************************************
 * \brief         De-Initialize the buffer module
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void BUFFER_SCB_vDeInit(void)
{
}
/** ****************************************************************************
 * \brief   This function must be called every 1ms to trigger calculate the mean
 *          value of the raw value
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 **************************************************************************** */
void BUFFER_SCB_vLoop1msTask(void)
{
  static uint16 u16SampleCounter = 0u;
  uint8 u8Count;
  static uint16 u16ReadValue = 0UL;

  for (u8Count = 0u; u8Count < (uint8)BUFFER_CFG_E_INDEX_COUNT; u8Count++)  
	{
    BUFFER_SCFG_vReadValue(u8Count, &u16ReadValue);
    mg_u32Buffer1ms[u8Count] =  mg_u32Buffer1ms[u8Count] + (uint32)u16ReadValue;
  }
  u16SampleCounter++;

  if (u16SampleCounter == BUFFER_CFG_1MS_SIZE)
  {
    for (u8Count = 0u; u8Count < ((uint8)BUFFER_CFG_E_INDEX_COUNT); u8Count++)
    {
      mg_u16Means1ms[u8Count] = (uint16)(mg_u32Buffer1ms[u8Count] / BUFFER_CFG_1MS_SIZE);
      mg_u32Buffer1ms[u8Count] = 0u;
    }
    u16SampleCounter = 0u;
  }
}

/** ****************************************************************************
 * \brief   This function must be called every 100ms to trigger calculate the mean
 *          value of the raw value
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 **************************************************************************** */
void BUFFER_SCB_vLoop10msTask(void)
{
  static uint16 u16SampleCounter = 0u;
  uint8 u8Count;
  static uint16 u16ReadValue = 0UL;

  for (u8Count = 0u; u8Count < (uint8)BUFFER_CFG_E_INDEX_COUNT; u8Count++)  
	{
    BUFFER_SCFG_vReadValue(u8Count, &u16ReadValue);
    mg_u32Buffer10ms[u8Count] =  mg_u32Buffer10ms[u8Count] + (uint32)u16ReadValue;
  }
  u16SampleCounter++;

  if (u16SampleCounter == BUFFER_CFG_10MS_SIZE)
  {
    for (u8Count = 0u; u8Count < ((uint8)BUFFER_CFG_E_INDEX_COUNT); u8Count++)
    {
      mg_u16Means10ms[u8Count] = (uint16)(mg_u32Buffer10ms[u8Count] / BUFFER_CFG_10MS_SIZE);
      mg_u32Buffer10ms[u8Count] = 0u;
    }
    u16SampleCounter = 0u;
  }
}

/** ****************************************************************************
 * \brief Read the mean value 
 *
 * \param[in] eAdcIndex     Index of the specified mean value
 * \param[out] -
 *
 * \return mean value
 *
 **************************************************************************** */
uint16 BUFFER_u16GetMean1ms(const BUFFER_CFG_E_INDEX eIndex)
{
  uint32 u32ToRet = 0u;
  if(((uint8)eIndex) < ((uint8)BUFFER_CFG_E_INDEX_COUNT))
  {
    u32ToRet = mg_u16Means1ms[eIndex];
  }
  else
  {
    BUFFER_SCFG_vOnErrorDetected((uint16)__LINE__,(uint32)0u);
  }

  return u32ToRet;
}

/** ****************************************************************************
 * \brief Read the mean value 
 *
 * \param[in] eAdcIndex     Index of the specified mean value
 * \param[out] -
 *
 * \return mean value
 *
 **************************************************************************** */
uint16 BUFFER_u16GetMean10ms(const BUFFER_CFG_E_INDEX eIndex)
{
  uint32 u32ToRet = 0u;
  if(((uint8)eIndex) < ((uint8)BUFFER_CFG_E_INDEX_COUNT))
  {
    u32ToRet = mg_u16Means10ms[eIndex];
  }
  else
  {
    BUFFER_SCFG_vOnErrorDetected((uint16)__LINE__,(uint32)0u);
  }

  return u32ToRet;
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/*
 * End of file
 */

