/*******************************************************************************
 * \file    pmbus_rte.h
 * \brief   RTE interface for pmbus.c
 *
 * \section AUTHOR
 *    1. Gary.Weng
 *
 * \section SVN
 *  $Date: 2019-11-22 11:01:57 +0800 (Fri, 22 Nov 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 239 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef PMBUS_RTE_H
#define PMBUS_RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif
		
#include "rte.h"

/*******************************************************************************
 * Global constants and macros (public to other modules)
 ******************************************************************************/
 
    
/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/
		
/***********************************************
 * Input
 **********************************************/ 
		
#define Rte_Read_R_u8PMBusCmd(var)               ((**var) = RTE_u8PmbusCommand)

#define RTE_PMB_Read_bit_Aux_Mode()               (PMBUS_uSysStatu0.Bits.AUX_MODE)
#define RTE_PMB_Write_bit_Aux_Mode(u8Val)         (PMBUS_uSysStatu0.Bits.AUX_MODE = (u8Val))
		
#define RTE_PMB_Read_bit_STB_MODE()               (PMBUS_uSysStatu1.Bits.STB_MODE)
#define RTE_PMB_Write_bit_STB_Mode(u8Val)         (PMBUS_uSysStatu1.Bits.STB_MODE = (u8Val))

#define RTE_PMB_Read_bit_Eeprom_Enable()          (PMBUS_uSysStatu1.Bits.EEPROM_ENABLE)
#define RTE_PMB_Write_bit_Eeprom_Enable(u8Val)    (PMBUS_uSysStatu1.Bits.EEPROM_ENABLE = (u8Val))
#if 0
#define RTE_PMB_Read_bit_RealTime_PecErr()        (PMBUS_tStatus.u8RealTimeStatusByte2.Bits.PEC_ERROR)
#define RTE_PMB_Write_bit_RealTime_PecErr(u8Val)  (PMBUS_tStatus.u8RealTimeStatusByte2.Bits.PEC_ERROR = (u8Val))

#define RTE_PMB_Read_bit_Latched_PecErr()         (PMBUS_tStatus.u8LatchedStatusByte2.Bits.PEC_ERROR)
#define RTE_PMB_Write_bit_Latched_PecErr(u8Val)   (PMBUS_tStatus.u8LatchedStatusByte2.Bits.PEC_ERROR = (u8Val))

#define RTE_PMB_Read_bit_Interrupt_Assert()       (PMBUS_uSysStatu0.Bits.INTERRUPT_ASSERT)
#define RTE_PMB_Write_bit_Interrupt_Assert(u8Val) (PMBUS_uSysStatu0.Bits.INTERRUPT_ASSERT = (u8Val))

#define RTE_PMB_Read_bit_PsFault_Assert()         (PMBUS_uSysStatu0.Bits.PS_FAULT_ASSERT)
#define RTE_PMB_Write_bit_PsFault_Assert(u8Val)   (PMBUS_uSysStatu0.Bits.PS_FAULT_ASSERT = (u8Val))
#endif
#define RTE_PMB_Read_bit_MFR_Update()             (PMBUS_uSysStatu0.Bits.MFR_INFO_UPDATE)
#define RTE_PMB_Write_bit_MFR_Update(u8Val)       (PMBUS_uSysStatu0.Bits.MFR_INFO_UPDATE = (u8Val))

//#define RTE_PMB_Read_bit_Invalid_Cmd()            (PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD)
//#define RTE_PMB_Write_bit_Invalid_Cmd(u8Val)      (PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = (u8Val))

//#define RTE_PMB_Read_bit_Invalid_Data()           (PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA)
//#define RTE_PMB_Write_bit_Invalid_Data(u8Val)     (PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = (u8Val))

#define RTE_PMB_Read_bit_Query_Request()          (PMBUS_uSysStatu0.Bits.QUERY_REQUEST)
#define RTE_PMB_Write_bit_Query_Request(u8Val)    (PMBUS_uSysStatu0.Bits.QUERY_REQUEST = (u8Val))

#define RTE_PMB_Read_bit_Page_Plus_Write()        (PMBUS_uSysStatu0.Bits.PAGE_PLUS_WRITE)
#define RTE_PMB_Write_bit_Page_Plus_Write(u8Val)  (PMBUS_uSysStatu0.Bits.PAGE_PLUS_WRITE = (u8Val))

#define RTE_PMB_Read_bit_Page_Plus_Read()         (PMBUS_uSysStatu0.Bits.PAGE_PLUS_READ)
#define RTE_PMB_Write_bit_Page_Plus_Read(u8Val)   (PMBUS_uSysStatu0.Bits.PAGE_PLUS_READ = (u8Val))

#define RTE_PMB_Read_bit_Get_Boot_Crc_Data()       (PMBUS_uSysStatu1.Bits.GET_BOOT_CRC_DATA)
#define RTE_PMB_Write_bit_Get_Boot_Crc_Data(u8Val) (PMBUS_uSysStatu1.Bits.GET_BOOT_CRC_DATA = (u8Val))

#define RTE_PMB_Read_bit_Ishare_Done()            (PMBUS_uSysStatu1.Bits.I_SHARE_CALI_DONE)
#define RTE_PMB_Write_bit_Ishare_Done(u8Val)      (PMBUS_uSysStatu1.Bits.I_SHARE_CALI_DONE = (u8Val))

#define RTE_PMB_Read_bit_EEP_Enable()             (PMBUS_uEepromEnable.Bits.ENABLE)
#define RTE_PMB_Write_bit_EEP_Enable(u8Val)       (PMBUS_uEepromEnable.Bits.ENABLE = (u8Val))

#define RTE_PMB_Read_Led_Ctrl_Register()          (PMBUS_uLedControl.ALL)
#define RTE_PMB_Write_Led_Ctrl_Register(u8Val)    (PMBUS_uLedControl.ALL = (u8Val))

#define RTE_PMB_Read_bit_Input_Led_On()           (PMBUS_uLedControl.Bits.INPUT_LED_ON)
#define RTE_PMB_Write_bit_Input_Led_On(u8Val)     (PMBUS_uLedControl.Bits.INPUT_LED_ON = (u8Val))

#define RTE_PMB_Read_bit_Input_Led_Ovrd()         (PMBUS_uLedControl.Bits.INPUT_LED_OVERRIDE)
#define RTE_PMB_Write_bit_Input_Led_Ovrd(u8Val)   (PMBUS_uLedControl.Bits.INPUT_LED_OVERRIDE = (u8Val))

#define RTE_PMB_Read_bit_Output_Led_On()          (PMBUS_uLedControl.Bits.OUTPUT_LED_ON)
#define RTE_PMB_Write_bit_Output_Led_On(u8Val)    (PMBUS_uLedControl.Bits.OUTPUT_LED_ON = (u8Val))

#define RTE_PMB_Read_bit_Output_Led_Ovrd()        (PMBUS_uLedControl.Bits.OUTPUT_LED_OVERRIDE)
#define RTE_PMB_Write_bit_Output_Led_Ovrd(u8Val)  (PMBUS_uLedControl.Bits.OUTPUT_LED_OVERRIDE = (u8Val))

#define RTE_PMB_Read_bit_Fault_Led_On()           (PMBUS_uLedControl.Bits.FAULT_LED_ON)
#define RTE_PMB_Write_bit_Fault_Led_On(u8Val)     (PMBUS_uLedControl.Bits.FAULT_LED_ON = (u8Val))

#define RTE_PMB_Read_bit_Fault_Led_Ovrd()         (PMBUS_uLedControl.Bits.FAULT_LED_OVERRIDE)
#define RTE_PMB_Write_bit_Fault_Led_Ovrd(u8Val)   (PMBUS_uLedControl.Bits.FAULT_LED_OVERRIDE = (u8Val))

#define RTE_PMB_Read_bit_ID_Led_On()              (PMBUS_uLedControl.Bits.ID_LED_ON)
#define RTE_PMB_Write_bit_ID_Led_On(u8Val)        (PMBUS_uLedControl.Bits.ID_LED_ON = (u8Val))

#define RTE_PMB_Read_bit_ID_Led_Ovrd()            (PMBUS_uLedControl.Bits.ID_LED_OVERRIDE)
#define RTE_PMB_Write_bit_ID_Led_Ovrd(u8Val)      (PMBUS_uLedControl.Bits.ID_LED_OVERRIDE = (u8Val))

#define RTE_PMB_Read_bit_ID_Led_Test()            (PMBUS_uLedControl.Bits.ID_LED_TEST)
#define RTE_PMB_Write_bit_ID_Led_Test(u8Val)      (PMBUS_uLedControl.Bits.ID_LED_TEST = (u8Val))

#define RTE_PMB_Read_bit_Fault_Sim_En()           (PMBUS_uEepromEnable.ENABLE)
#define RTE_PMB_Write_bit_Fault_Sim_En(u8Val)     (PMBUS_uEepromEnable.ENABLE = (u8Val))

#define RTE_PMB_Read_bit_Vin_Upd()                (PMBUS_uDataUpdStatus.Bits.VIN_UPDTING)
#define RTE_PMB_Write_bit_Vin_Upd(u8Val)          (PMBUS_uDataUpdStatus.Bits.VIN_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Iin_Upd()                (PMBUS_uDataUpdStatus.Bits.IIN_UPDTING)
#define RTE_PMB_Write_bit_Iin_Upd(u8Val)          (PMBUS_uDataUpdStatus.Bits.IIN_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Pin_Upd()                (PMBUS_uDataUpdStatus.Bits.PIN_UPDTING)
#define RTE_PMB_Write_bit_Pin_Upd(u8Val)          (PMBUS_uDataUpdStatus.Bits.PIN_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Vout_V1_Upd()            (PMBUS_uDataUpdStatus.Bits.VOUT_V1_UPDTING)
#define RTE_PMB_Write_bit_Vout_V1_Upd(u8Val)      (PMBUS_uDataUpdStatus.Bits.VOUT_V1_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Vout_IShare_Upd()            (PMBUS_uDataUpdStatus1.Bits.VOUT_V1_ISHARE_UPDTING)
#define RTE_PMB_Write_bit_Vout_IShare_Upd(u8Val)      (PMBUS_uDataUpdStatus1.Bits.VOUT_V1_ISHARE_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Vout_Sense_Upd()            (PMBUS_uDataUpdStatus1.Bits.VOUT_V1_SENSE_UPDTING)
#define RTE_PMB_Write_bit_Vout_Sense_Upd(u8Val)      (PMBUS_uDataUpdStatus1.Bits.VOUT_V1_SENSE_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Iout_V1_Upd()            (PMBUS_uDataUpdStatus.Bits.IOUT_V1_UPDTING)
#define RTE_PMB_Write_bit_Iout_V1_Upd(u8Val)      (PMBUS_uDataUpdStatus.Bits.IOUT_V1_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Pout_V1_Upd()            (PMBUS_uDataUpdStatus.Bits.POUT_V1_UPDTING)
#define RTE_PMB_Write_bit_Pout_V1_Upd(u8Val)      (PMBUS_uDataUpdStatus.Bits.POUT_V1_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Inlet_Upd()              (PMBUS_uDataUpdStatus.Bits.TEMP_INLET_UPDTING)
#define RTE_PMB_Write_bit_Inlet_Upd(u8Val)        (PMBUS_uDataUpdStatus.Bits.TEMP_INLET_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_SR_Upd()                 (PMBUS_uDataUpdStatus.Bits.TEMP_SR_UPDTING)
#define RTE_PMB_Write_bit_SR_Upd(u8Val)           (PMBUS_uDataUpdStatus.Bits.TEMP_SR_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Pfc_Upd()                (PMBUS_uDataUpdStatus.Bits.TEMP_PFC_UPDTING)
#define RTE_PMB_Write_bit_Pfc_Upd(u8Val)          (PMBUS_uDataUpdStatus.Bits.TEMP_PFC_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Hours_Upd()              (PMBUS_uDataUpdStatus.Bits.HOURS_USED_UPDTING)
#define RTE_PMB_Write_bit_Hours_Upd(u8Val)        (PMBUS_uDataUpdStatus.Bits.HOURS_USED_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Fan_Spd_1_Upd()          (PMBUS_uDataUpdStatus.Bits.FAN_SPD_1_UPDTING)
#define RTE_PMB_Write_bit_Fan_Spd_1_Upd(u8Val)    (PMBUS_uDataUpdStatus.Bits.FAN_SPD_1_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Fan_Spd_2_Upd()          (PMBUS_uDataUpdStatus.Bits.FAN_SPD_2_UPDTING)
#define RTE_PMB_Write_bit_Fan_Spd_2_Upd(u8Val)    (PMBUS_uDataUpdStatus.Bits.FAN_SPD_2_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Fan_Spd_3_Upd()          (PMBUS_uDataUpdStatus.Bits.FAN_SPD_3_UPDTING)
#define RTE_PMB_Write_bit_Fan_Spd_3_Upd(u8Val)    (PMBUS_uDataUpdStatus.Bits.FAN_SPD_3_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Fan_Spd_4_Upd()          (PMBUS_uDataUpdStatus.Bits.FAN_SPD_4_UPDTING)
#define RTE_PMB_Write_bit_Fan_Spd_4_Upd(u8Val)    (PMBUS_uDataUpdStatus.Bits.FAN_SPD_4_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Vout_VSB_Upd()           (PMBUS_uDataUpdStatus.Bits.VOUT_VSB_UPDTING)
#define RTE_PMB_Write_bit_Vout_VSB_Upd(u8Val)     (PMBUS_uDataUpdStatus.Bits.VOUT_VSB_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Iout_VSB_Upd()           (PMBUS_uDataUpdStatus.Bits.IOUT_VSB_UPDTING)
#define RTE_PMB_Write_bit_Iout_VSB_Upd(u8Val)     (PMBUS_uDataUpdStatus.Bits.IOUT_VSB_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Pout_VSB_Upd()           (PMBUS_uDataUpdStatus1.Bits.POUT_VSB_UPDTING)
#define RTE_PMB_Write_bit_Pout_VSB_Upd(u8Val)     (PMBUS_uDataUpdStatus1.Bits.POUT_VSB_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Ein_Upd()                (PMBUS_uDataUpdStatus1.Bits.EIN_UPDTING)
#define RTE_PMB_Write_bit_Ein_Upd(u8Val)          (PMBUS_uDataUpdStatus1.Bits.EIN_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Eout_Upd()               (PMBUS_uDataUpdStatus1.Bits.EOUT_UPDTING)
#define RTE_PMB_Write_bit_Eout_Upd(u8Val)         (PMBUS_uDataUpdStatus1.Bits.EOUT_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_Status_Upd()             (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
#define RTE_PMB_Write_bit_Status_Upd(u8Val)       (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING = (u8Val))

//#define RTE_PMB_Read_bit_V1_VI_OUT_Upd()          (PMBUS_uDataUpdStatus1.Bits.FALT_UPDT_V1_VI_OUT)
//#define RTE_PMB_Write_bit_V1_VI_OUT_Upd(u8Val)    (PMBUS_uDataUpdStatus1.Bits.FALT_UPDT_V1_VI_OUT = (u8Val))

#define RTE_PMB_Read_bit_VCAP_Upd()               (PMBUS_uDataUpdStatus1.Bits.VCAP_UPDTING)
#define RTE_PMB_Write_bit_VCAP_Upd(u8Val)         (PMBUS_uDataUpdStatus1.Bits.VCAP_UPDTING = (u8Val))

#define RTE_PMB_Read_bit_POS_TOTAL_Upd()          (PMBUS_uDataUpdStatus1.Bits.MFR_POS_TOTAL)
#define RTE_PMB_Write_bit_POS_TOTAL_Upd(u8Val)    (PMBUS_uDataUpdStatus1.Bits.MFR_POS_TOTAL = (u8Val))

#define RTE_PMB_Read_bit_POS_LAST_Upd()           (PMBUS_uDataUpdStatus1.Bits.MFR_POS_LAST)
#define RTE_PMB_Write_bit_POS_LAST_Upd(u8Val)     (PMBUS_uDataUpdStatus1.Bits.MFR_POS_LAST = (u8Val))


#define RTE_PMBUS_Read_bit_Time_Clear_Enable()           (PMBUS_uSysStatu1.Bits.TIME_CLEAR_ENABLE) 
#define RTE_PMBUS_Write_bit_Time_Clear_Enable(u8Data)    (PMBUS_uSysStatu1.Bits.TIME_CLEAR_ENABLE = (u8Data))


#define RTE_PMB_Read_u16Vin_Linear()              (PMBUS_tData.u16Vin_Linear.u16Val)
#define RTE_PMB_Write_u16Vin_Linear(u16Data)      (PMBUS_tData.u16Vin_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vin_Mul_128()             (PMBUS_tData.u16Vin_Mul_128.u16Val)
#define RTE_PMB_Write_u16Vin_Mul_128(u16Data)     (PMBUS_tData.u16Vin_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vin_Linear_Box()          (PMBUS_tData.u16Vin_Linear_Box.u16Val)
#define RTE_PMB_Write_u16Vin_Linear_Box(u16Data)  (PMBUS_tData.u16Vin_Linear_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vin_Mul_128_Box()         (PMBUS_tData.u16Vin_Mul_128_Box.u16Val)
#define RTE_PMB_Write_u16Vin_Mul_128_Box(u16Data) (PMBUS_tData.u16Vin_Mul_128_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iin_Linear()              (PMBUS_tData.u16Iin_Linear.u16Val)
#define RTE_PMB_Write_u16Iin_Linear(u16Data)      (PMBUS_tData.u16Iin_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iin_Mul_128()             (PMBUS_tData.u16Iin_Mul_128.u16Val)
#define RTE_PMB_Write_u16Iin_Mul_128(u16Data)     (PMBUS_tData.u16Iin_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iin_Linear_Box()          (PMBUS_tData.u16Iin_Linear_Box.u16Val)
#define RTE_PMB_Write_u16Iin_Linear_Box(u16Data)  (PMBUS_tData.u16Iin_Linear_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iin_Mul_128_Box()         (PMBUS_tData.u16Iin_Mul_128_Box.u16Val)
#define RTE_PMB_Write_u16Iin_Mul_128_Box(u16Data) (PMBUS_tData.u16Iin_Mul_128_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Pin_Linear()              (PMBUS_tData.u16Pin_Linear.u16Val)
#define RTE_PMB_Write_u16Pin_Linear(u16Data)      (PMBUS_tData.u16Pin_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u32Pin_Mul_128()             (PMBUS_tData.u32Pin_Mul_128.u32Val)
#define RTE_PMB_Write_u32Pin_Mul_128(u32Data)     (PMBUS_tData.u32Pin_Mul_128.u32Val = (u32Data))

#define RTE_PMB_Read_u32Pin_Mul_128_Box()         (PMBUS_tData.u32Pin_Mul_128_Box.u32Val)
#define RTE_PMB_Write_u32Pin_Mul_128_Box(u32Data) (PMBUS_tData.u32Pin_Mul_128_Box.u32Val = (u32Data))

#define RTE_PMB_Read_u16Vout_V1_Linear()          (PMBUS_tData.u16Vout_V1_Linear.u16Val)
#define RTE_PMB_Write_u16Vout_V1_Linear(u16Data)  (PMBUS_tData.u16Vout_V1_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_V1_Mul_512()         (PMBUS_tData.u16Vout_V1_Mul_128.u16Val)
#define RTE_PMB_Write_u16Vout_V1_Mul_512(u16Data) (PMBUS_tData.u16Vout_V1_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iout_V1_Linear()          (PMBUS_tData.u16Iout_V1_Linear.u16Val)
#define RTE_PMB_Write_u16Iout_V1_Linear(u16Data)  (PMBUS_tData.u16Iout_V1_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iout_V1_Mul_128()         (PMBUS_tData.u16Iout_V1_Mul_128.u16Val)
#define RTE_PMB_Write_u16Iout_V1_Mul_128(u16Data) (PMBUS_tData.u16Iout_V1_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Pout_V1_Linear()          (PMBUS_tData.u16Pout_V1_Linear.u16Val)
#define RTE_PMB_Write_u16Pout_V1_Linear(u16Data)  (PMBUS_tData.u16Pout_V1_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u32Pout_V1_Mul_128()         (PMBUS_tData.u32Pout_V1_Mul_128.u32Val)
#define RTE_PMB_Write_u32Pout_V1_Mul_128(u16Data) (PMBUS_tData.u32Pout_V1_Mul_128.u32Val = (u16Data))

#define RTE_PMB_Read_u16Pout_VSB_Linear()         (PMBUS_tData.u16Pout_VSB_Linear.u16Val)
#define RTE_PMB_Write_u16Pout_VSB_Linear(u16Data) (PMBUS_tData.u16Pout_VSB_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u32Pout_VSB_Mul_128()        (PMBUS_tData.u32Pout_VSB_Mul_128.u32Val)
#define RTE_PMB_Write_u32Pout_VSB_Mul_128(u32Data)(PMBUS_tData.u32Pout_VSB_Mul_128.u32Val = (u32Data))

#define RTE_PMB_Read_u16Vout_VSB_Linear()         (PMBUS_tData.u16Vout_VSB_Linear.u16Val)
#define RTE_PMB_Write_u16Vout_VSB_Linear(u32Data) (PMBUS_tData.u16Vout_VSB_Linear.u16Val = (u32Data))

#define RTE_PMB_Read_u16Vout_VSB_Mul_512()        (PMBUS_tData.u16Vout_VSB_Mul_128.u16Val)
#define RTE_PMB_Write_u16Vout_VSB_Mul_512(u16Data)(PMBUS_tData.u16Vout_VSB_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iout_VSB_Linear()         (PMBUS_tData.u16Iout_VSB_Linear.u16Val)
#define RTE_PMB_Write_u16Iout_VSB_Linear(u16Data) (PMBUS_tData.u16Iout_VSB_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iout_VSB_Mul_128()        (PMBUS_tData.u16Iout_VSB_Mul_128.u16Val)
#define RTE_PMB_Write_u16Iout_VSB_Mul_128(u16Data)(PMBUS_tData.u16Iout_VSB_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Temp1_Linear()            (PMBUS_tData.u16Temperatue_1_Linear.u16Val)
#define RTE_PMB_Write_u16Temp1_Linear(u16Data)    (PMBUS_tData.u16Temperatue_1_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Temp2_Linear()            (PMBUS_tData.u16Temperatue_2_Linear.u16Val)
#define RTE_PMB_Write_u16Temp2_Linear(u16Data)    (PMBUS_tData.u16Temperatue_2_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Temp3_Linear()            (PMBUS_tData.u16Temperatue_3_Linear.u16Val)
#define RTE_PMB_Write_u16Temp3_Linear(u16Data)    (PMBUS_tData.u16Temperatue_3_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Temp4_Linear()            (PMBUS_tData.u16Temperatue_4_Linear.u16Val)
#define RTE_PMB_Write_u16Temp4_Linear(u16Data)    (PMBUS_tData.u16Temperatue_4_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16FanSpeed1_Linear()        (PMBUS_tData.u16FanSpeed_1_Linear.u16Val)
#define RTE_PMB_Write_u16FanSpeed1_Linear(u16Data)(PMBUS_tData.u16FanSpeed_1_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16FanSpeed2_Linear()        (PMBUS_tData.u16FanSpeed_2_Linear.u16Val)
#define RTE_PMB_Write_u16FanSpeed2_Linear(u16Data)(PMBUS_tData.u16FanSpeed_2_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u32Hours_Used()              (PMBUS_tData.u32HoursUsed.u32Val)
#define RTE_PMB_Write_u32Hours_Used(u32Data)      (PMBUS_tData.u32HoursUsed.u32Val = (u32Data))

#define RTE_PMB_Read_u32DataCopy()                (PMBUS_tData.u32DataCopy.u32Val)
#define RTE_PMB_Write_u32DataCopy(u32Data)        (PMBUS_tData.u32DataCopy.u32Val = (u32Data))

#define RTE_PMB_Read_u16Vcap_Linear()             (PMBUS_tData.u16Vcap_Linear.u16Val)
#define RTE_PMB_Write_u16Vcap_Linear(u16Data)     (PMBUS_tData.u16Vcap_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vcap_Mul_128()            (PMBUS_tData.u16Vcap_Mul_128.u16Val)
#define RTE_PMB_Write_u16Vcap_Mul_128(u16Data)    (PMBUS_tData.u16Vcap_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_V1Sense_Mul_128()         (PMBUS_tData.u16Vout_V1Sense_Mul_128.u16Val)
#define RTE_PMB_Write_u16Vout_V1Sense_Mul_128(u16Data) (PMBUS_tData.u16Vout_V1Sense_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_V1Sense_Linear()          (PMBUS_tData.u16Vout_V1Sense_Linear.u16Val)
#define RTE_PMB_Write_u16Vout_V1Sense_Linear(u16Data)  (PMBUS_tData.u16Vout_V1Sense_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_V1IShare_Mul_128()         (PMBUS_tData.u16Vout_V1IShare_Mul_128.u16Val)
#define RTE_PMB_Write_u16Vout_V1IShare_Mul_128(u16Data) (PMBUS_tData.u16Vout_V1IShare_Mul_128.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_V1IShare_Linear()          (PMBUS_tData.u16Vout_V1IShare_Linear.u16Val)
#define RTE_PMB_Write_u16Vout_V1IShare_Linear(u16Data)  (PMBUS_tData.u16Vout_V1IShare_Linear.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_V1_Linear_Box()          (PMBUS_tData.u16Vout_V1_Linear_Box.u16Val)
#define RTE_PMB_Write_u16Vout_V1_Linear_Box(u16Data)  (PMBUS_tData.u16Vout_V1_Linear_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_V1_Mul_512_Box()         (PMBUS_tData.u16Vout_V1_Mul_128_Box.u16Val)
#define RTE_PMB_Write_u16Vout_V1_Mul_512_Box(u16Data) (PMBUS_tData.u16Vout_V1_Mul_128_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iout_V1_Linear_Box()          (PMBUS_tData.u16Iout_V1_Linear_Box.u16Val)
#define RTE_PMB_Write_u16Iout_V1_Linear_Box(u16Data)  (PMBUS_tData.u16Iout_V1_Linear_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iout_V1_Mul_128_Box()         (PMBUS_tData.u16Iout_V1_Mul_128_Box.u16Val)
#define RTE_PMB_Write_u16Iout_V1_Mul_128_Box(u16Data) (PMBUS_tData.u16Iout_V1_Mul_128_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_VSB_Linear_Box()          (PMBUS_tData.u16Vout_VSB_Linear_Box.u16Val)
#define RTE_PMB_Write_u16Vout_VSB_Linear_Box(u16Data)  (PMBUS_tData.u16Vout_VSB_Linear_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Vout_VSB_Mul_512_Box()         (PMBUS_tData.u16Vout_VSB_Mul_128_Box.u16Val)
#define RTE_PMB_Write_u16Vout_VSB_Mul_512_Box(u16Data) (PMBUS_tData.u16Vout_VSB_Mul_128_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iout_VSB_Linear_Box()          (PMBUS_tData.u16Iout_VSB_Linear_Box.u16Val)
#define RTE_PMB_Write_u16Iout_VSB_Linear_Box(u16Data)  (PMBUS_tData.u16Iout_VSB_Linear_Box.u16Val = (u16Data))

#define RTE_PMB_Read_u16Iout_VSB_Mul_128_Box()         (PMBUS_tData.u16Iout_VSB_Mul_128_Box.u16Val)
#define RTE_PMB_Write_u16Iout_VSB_Mul_128_Box(u16Data) (PMBUS_tData.u16Iout_VSB_Mul_128_Box.u16Val = (u16Data))


#define Rte_Read_B_P_ReadBlackBoxOtherFail            (RTE_B_COM_READ_BLACK_BOX_OTHER_FAIL)
#define Rte_Read_B_P_ReadBlackBoxVinUvpFail           (RTE_B_COM_READ_BLACK_BOX_VINUVP_FAIL)
#define Rte_Read_B_P_ClearBlackBoxAll                 (RTE_B_COM_CLEAR_BLACK_BOX)
#define Rte_Read_B_P_ClearBlackBoxOtherFail           (RTE_B_COM_CLEAR_BLACK_BOX_OTHER_FAIL)
#define Rte_Read_B_P_ClearBlackBoxVinUvpFail          (RTE_B_COM_CLEAR_BLACK_BOX_VINUVP_FAIL)

#define Rte_Read_R_u32PMBusCmd(var)                   ((**var) = PMBUS_tData.u32HoursUsed.u32Val)
#define Rte_Read_R_u8AcLineStatus(var)                ((**var) = RTE_u8AcLineStatus)
#define Rte_Read_R_u16FunctionCtrl(var)               ((**var) = RTE_uFunctionCtrl.ALL)
#define Rte_Read_R_s16OtWarning(var)                  ((**var) = RTE_s16OtWarning)


#define RTE_Read_B_R_V1_OVP                          (RTE_B_COM_V1_OVP)
#define RTE_Read_B_R_V1_UVP                          (RTE_B_COM_V1_UVP)
#define RTE_Read_B_R_V1_OCP                          (RTE_B_COM_V1_OCP)
#define RTE_Read_B_R_V1_OCW                          (RTE_B_COM_V1_OCW)
#define RTE_Read_B_R_V1_OK                           (RTE_B_COM_OUTPUT_OK)
/***********************************************
 * Output
 **********************************************/ 
#define Rte_Write_P_u8PMBusCmd                         (RTE_u8PmbusCommand)
#define Rte_Write_P_u8TempTestIndex(var)               (RTE_u8TempTestIndex = var)	
#define Rte_Write_P_bIsV1OcpTest(var)                  (RTE_bIsV1OcpTest = var)	
#define Rte_Write_P_bIsVsbOcpTest(var)                 (RTE_bIsVsbOcpTest = var)	

#define Rte_Write_P_s16TempTestValue(var,index)        (RTE_s16TempTest[index] = var)	
#define Rte_Write_P_u16FunctionCtrl(var)               (RTE_uFunctionCtrl.ALL = var)
#define Rte_Write_P_s16OtWarning(var)                  (RTE_s16OtWarning = var)

#define RTE_Write_B_P_ClearBlackBoxAll                 (RTE_B_COM_CLEAR_BLACK_BOX)
#define RTE_Write_B_P_ClearBlackBoxOtherFail           (RTE_B_COM_CLEAR_BLACK_BOX_OTHER_FAIL)
#define RTE_Write_B_P_ClearBlackBoxVinUvpFail          (RTE_B_COM_CLEAR_BLACK_BOX_VINUVP_FAIL)
#define RTE_Write_B_P_ReadBlackBoxOtherFail            (RTE_B_COM_READ_BLACK_BOX_OTHER_FAIL)
#define RTE_Write_B_P_ReadBlackBoxVinUvpFail           (RTE_B_COM_READ_BLACK_BOX_VINUVP_FAIL)
#define RTE_Write_B_P_SetAcOffsetValue                 (RTE_Pri.u16AcOffset.u16Val)

#define RTE_Write_B_P_AC_OFFSET_SAVEED           (RTE_B_COM_AC_OFFSET_SAVEED)  
#define RTE_Write_B_P_V1_OVP                     (RTE_B_COM_V1_OVP)
#define RTE_Write_B_P_V1_UVP                     (RTE_B_COM_V1_UVP)
#define RTE_Write_B_P_V1_OCP                     (RTE_B_COM_V1_OCP)
#define RTE_Write_B_P_V1_OCW                     (RTE_B_COM_V1_OCW)
#define Rte_Write_B_P_VSB_OVP                     (RTE_B_COM_VSB_OVP)
#define Rte_Write_B_P_VSB_UVP                     (RTE_B_COM_VSB_UVP)
#define Rte_Write_B_P_VSB_OCP                     (RTE_B_COM_VSB_OCP)
#define Rte_Write_B_P_VSB_OCW                     (RTE_B_COM_VSB_OCW)
#define RTE_Write_B_P_VSB_TRIM                   (RTE_B_PSUCTRL_VSB_TRIM)
#define RTE_Write_B_P_V1_TRIM                    (RTE_B_PSUCTRL_V1_TRIM)
 
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
SINLINE uint8 PMBUS_Rte_Read_B_R_V1_OVP(void)
{
	return RTE_Read_B_R_V1_OVP;
}
SINLINE uint8 PMBUS_Rte_Read_B_R_V1_UVP(void)
{
	return RTE_Read_B_R_V1_UVP;
}
SINLINE uint8 PMBUS_Rte_Read_B_R_V1_OCP(void)
{
	return RTE_Read_B_R_V1_OCP;
}
SINLINE uint8 PMBUS_Rte_Read_B_R_V1_OCW(void)
{
	return RTE_Read_B_R_V1_OCW;
}
SINLINE uint8 PMBUS_Rte_Read_B_R_V1_OK(void)
{
	return RTE_Read_B_R_V1_OK;
}
SINLINE uint8 PMBUS_Rte_Read_B_P_ReadBlackBoxOtherFail(void)
{
	return Rte_Read_B_P_ReadBlackBoxOtherFail;
}
SINLINE uint8 PMBUS_Rte_Read_B_P_ReadBlackBoxVinUvpFail(void)
{
	return Rte_Read_B_P_ReadBlackBoxVinUvpFail;
}
SINLINE uint8 PMBUS_Rte_Read_B_P_ClearBlackBoxAll(void)
{
	return Rte_Read_B_P_ClearBlackBoxAll;
}
SINLINE uint8 PMBUS_Rte_Read_B_P_ClearBlackBoxOtherFail(void)
{
	return Rte_Read_B_P_ClearBlackBoxOtherFail;
}
SINLINE uint8 PMBUS_Rte_Read_B_P_ClearBlackBoxVinUvpFail(void)
{
	return Rte_Read_B_P_ClearBlackBoxVinUvpFail;
}

SINLINE void PMBUS_Rte_Read_R_u8PMBusCmd(uint8 *var)
{
  Rte_Read_R_u8PMBusCmd(&var);
}
SINLINE void PMBUS_Rte_Read_R_u8AcLineStatus(uint8 *var)
{
  Rte_Read_R_u8AcLineStatus(&var);
}
SINLINE void PMBUS_Rte_Read_R_u16FunctionCtrl(uint16 *var)
{
  Rte_Read_R_u16FunctionCtrl(&var);
}
SINLINE void PMBUS_Rte_Read_R_s16OtWarning(sint16 *var)
{
  Rte_Read_R_s16OtWarning(&var);
}
SINLINE void PMBUS_Rte_Read_R_u32PMBusCmd(uint32 *var)
{
  Rte_Read_R_u32PMBusCmd(&var);
}


/* Write */
SINLINE void PMBUS_Rte_Write_P_u8PMBusCmd(uint8 u8Data)
{
  Rte_Write_P_u8PMBusCmd = u8Data;
}

SINLINE void PMBUS_Rte_Write_P_s16TempTestValue(sint16 var,uint8 index)
{
  Rte_Write_P_s16TempTestValue(var,index);
}

SINLINE void PMBUS_Rte_Write_P_u16FunctionCtrl(uint16 var)
{
  Rte_Write_P_u16FunctionCtrl(var);
}

SINLINE void PMBUS_Rte_Write_P_s16OtWarning(sint16 var)
{
  Rte_Write_P_s16OtWarning(var);
}

SINLINE void PMBUS_Rte_Write_P_u8TempTestIndex(uint8 var)
{
 Rte_Write_P_u8TempTestIndex(var);
}

SINLINE void PMBUS_RTE_Write_B_P_ClearBlackBoxAll(uint8 u8Data)
{
  RTE_Write_B_P_ClearBlackBoxAll = u8Data;
}

SINLINE void PMBUS_RTE_Write_B_P_ClearBlackBoxOtherFail(uint8 u8Data)
{
  RTE_Write_B_P_ClearBlackBoxOtherFail = u8Data;
}

SINLINE void PMBUS_RTE_Write_B_P_ClearBlackBoxVinUvpFail(uint8 u8Data)
{
  RTE_Write_B_P_ClearBlackBoxVinUvpFail = u8Data;
}

SINLINE void PMBUS_RTE_Write_B_P_ReadBlackBoxOtherFail(uint8 u8Data)
{
  RTE_Write_B_P_ReadBlackBoxOtherFail = u8Data;
}

SINLINE void PMBUS_RTE_Write_B_P_ReadBlackBoxVinUvpFail(uint8 u8Data)
{
  RTE_Write_B_P_ReadBlackBoxVinUvpFail = u8Data;
}

SINLINE void PMBUS_RTE_Write_B_P_SetAcOffsetValue(uint16 u16Data)
{
  RTE_Write_B_P_SetAcOffsetValue = u16Data;
}

SINLINE void PMBUS_Rte_Write_B_P_AC_OFFSET_SAVEED(uint8 u8Status)
{
  RTE_Write_B_P_AC_OFFSET_SAVEED =  u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_V1_OVP(uint8 u8Status)
{
	RTE_Write_B_P_V1_OVP = u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_V1_UVP(uint8 u8Status)
{
	RTE_Write_B_P_V1_UVP = u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_V1_OCP(uint8 u8Status)
{
	RTE_Write_B_P_V1_OCP = u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_V1_OCW(uint8 u8Status)
{
	RTE_Write_B_P_V1_OCW = u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_VSB_OVP(uint8 u8Status)
{
	Rte_Write_B_P_VSB_OVP = u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_VSB_UVP(uint8 u8Status)
{
	Rte_Write_B_P_VSB_UVP = u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_VSB_OCP(uint8 u8Status)
{
	Rte_Write_B_P_VSB_OCP = u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_VSB_OCW(uint8 u8Status)
{
	Rte_Write_B_P_VSB_OCW = u8Status;
}

SINLINE void PMBUS_Rte_Write_B_P_VSB_TRIM(uint8 u8Status)
{
	RTE_Write_B_P_VSB_TRIM = u8Status;
}
SINLINE void PMBUS_Rte_Write_B_P_V1_TRIM(uint8 u8Status)
{
	RTE_Write_B_P_V1_TRIM = u8Status;
}


#ifdef __cplusplus
  }
#endif
#endif  /* PMBUS_RTE_H */

  
/*
 * End of file
 */
