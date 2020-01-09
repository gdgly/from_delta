/** ****************************************************************************
 * \file    mean_scfg.h
 * \brief   BUFFER module server configuration header
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

#ifndef BUFFER_SCFG_H
#define BUFFER_SCFG_H

#include "adc_api.h"
#include "buffer_cfg.h"
#include "rte.h"

#ifdef __cplusplus
extern "C" {
#endif

  /*******************************************************************************
   * Global constants and macros
   ******************************************************************************/

  /*******************************************************************************
   * Global data types (typedefs / structs / enums)
   ******************************************************************************/

  /*******************************************************************************
   * Global data
   ******************************************************************************/

  /*******************************************************************************
   * Global function prototypes
   ******************************************************************************/
  /** ****************************************************************************
   * \brief   Call server module to enter an event in the developer log
   *
   * \return  result of service request
   *
   **************************************************************************** */
  SINLINE void BUFFER_SCFG_vOnErrorDetected(uint16 u16LineNumber, uint32 u32Value)
  {
//    DEVLOG_SCB_vLogEvent(DEVLOG_E_MODULE_H_BUFFER, u16LineNumber, u32Value);
  }

  /** ****************************************************************************
   * \brief   Call server module to read the value into the given buffer index
   *
   * \return  result of service request
   *
   **************************************************************************** */
SINLINE void BUFFER_SCFG_vReadValue(const uint8 u8BufferIndex, uint16 *pu16Value)
{
	switch(u8BufferIndex)
	{
		case BUFFER_CFG_E_ExtVsb:
		{
			ADC_vReadRaw(ADC_CFG_E_INDEX_PA5_AIN5_ExtVsb, pu16Value);
			*pu16Value = (uint16)(((uint32)*pu16Value * RTE_U16_10mV_V_VSB_EXT_SCALE_FACT)>>12);
			break;
		}
		case BUFFER_CFG_E_IntVsb:
		{
			ADC_vReadRaw(ADC_CFG_E_INDEX_PA1_AIN1_IntVsb, pu16Value);
			*pu16Value = (uint16)(((uint32)*pu16Value * RTE_U16_10mV_V_VSB_INT_SCALE_FACT)>>12);
			break;
		}
		case BUFFER_CFG_E_Isb:
		{
			ADC_vReadRaw(ADC_CFG_E_INDEX_PA6_AIN6_IVsb, pu16Value);
			*pu16Value = (uint16)(((uint32)*pu16Value * RTE_U16_1mA_I_VSB_SCALE_FACT)>>12);
			break;
		}
		case BUFFER_CFG_E_Vin:
		{
      *pu16Value = PMBUS_tData.u16Vin_Mul_128.u16Val;
			break;
		}
    case BUFFER_CFG_E_Iin:
		{
      *pu16Value = PMBUS_tData.u16Iin_Mul_128.u16Val;
			break;
		}
		case BUFFER_CFG_E_Pin:
		{
      *pu16Value = (uint16)(PMBUS_tData.u32Pin_Mul_128.u32Val >> 7u);
			break;
		}
		case BUFFER_CFG_E_V1:
		{
      *pu16Value = PMBUS_tData.u16Vout_V1_Mul_128.u16Val;
			break;
		}
		case BUFFER_CFG_E_I1:
		{
      *pu16Value = PMBUS_tData.u16Iout_V1_Mul_128.u16Val;
			break;
		}
    case BUFFER_CFG_E_P1:
    {
      *pu16Value = (uint16)(PMBUS_tData.u32Pout_V1_Mul_128.u32Val >> 7u);
      break;
    }
		default:
		{
      BUFFER_SCFG_vOnErrorDetected((uint16)__LINE__,(uint32)0u);
		}
	}
}

#ifdef __cplusplus
}
#endif

#endif

/*
 * End of file
 */

