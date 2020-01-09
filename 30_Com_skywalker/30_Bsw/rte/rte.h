/*******************************************************************************
 * \file    rte.h
 * \brief   RTE interface for main.c
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *    2.
 *    3. 
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

#ifndef RTE_H
#define RTE_H
#ifdef __cplusplus
  extern "C"  {
#endif
#include "global.h"

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/
/* pmbus debug register */
#define SW_HW_COMPATIBLITY	         0x01
#define PMB_F0_BLOCK_BYTES_COUNTER   0x0D
#define PMB_9A_BLOCK_BYTES_COUNTER   0x0B

#define RTE_UPDATE_NO_DLY           ((uint8)0U)
#define RTE_UPDATE_WITH_DLY         ((uint8)1U)

#define MAX_DROOP_LINE              ((uint8)2U)
#define DROOP_LINE_1                ((uint8)0U)
#define DROOP_LINE_2                ((uint8)1U)

#define METER_IC_DATA_NBR           ((uint8)16U)           

#define RTE_NTC_NUM                 ((uint8)1U)
#define RTE_CCP7_CCP6_CHANGE        0  /* 1 = use CCP7 for synchronise Fred.Ji 27Apr2016 */
#define RTE_USE_TX1_CLOSE_LLC       1  /* 1 = use TX1 to close LLC when detect mosfet is damaged Fred.Ji 27Apr2016 */
#define RTE_START_WITHOUT_EN        0  /* 1 = Start without Board en signal */


/* Define if internal or external oscillator is used */
#ifdef EXTERNAL_OSCILLATOR
  #define RTE_U32_CPU_CLK_FREQ      ((uint32)48000000U) /* Value in Hz */
#else
  #define RTE_U32_CPU_CLK_FREQ      ((uint32)48000000U) /* Value in Hz */
#endif


/* Default application revision */
#ifdef HALT_TEST_MODE
#define  SPECIAL_SW_VERSION                0x80u
#else
#define  SPECIAL_SW_VERSION                0x00u
#endif

#define COM_MAJOR_SW_VERSION    (2u + SPECIAL_SW_VERSION)
#define COM_MINOR_SW_VERSION    2
#define COM_DEBUG_SW_VERSION   'a'

#define SEC_MAJOR_SW_VERSION    0
#define SEC_MINOR_SW_VERSION    0
#define SEC_DEBUG_SW_VERSION   '0'

#define PRI_MAJOR_SW_VERSION    0
#define PRI_MINOR_SW_VERSION    0
#define PRI_DEBUG_SW_VERSION   '0'

/* Default bootloader revision */
#define SEC_MAJOR_BL_VERSION    0
#define SEC_MINOR_BL_VERSION    0
#define SEC_DEBUG_BL_VERSION   '0'

#define PRI_MAJOR_BL_VERSION    0
#define PRI_MINOR_BL_VERSION    0
#define PRI_DEBUG_BL_VERSION   '0'

/* Default boot loader revision */
#define COM_MAJOR_BL_VERSION    1
#define COM_MINOR_BL_VERSION    0
#define COM_DEBUG_BL_VERSION   'a'

/***********************************************
 * scale fact of voltage and current
 **********************************************/
#define RTE_F32_VSB_EXT_MAX            16.151F    /* (V) Maximum detectable external Vsb */
#define RTE_F32_VSB_INT_MAX            16.151F    /* (V) Maximum detectable internal Vsb */
#define RTE_F32_ISB_MAX                4.519F     /* (A) Maximum detectable Vsb current*/
#define RTE_F32_I_OUT_MAX              150.446F   /* (A) Maximum detectable output current */
                  
#define RTE_U16_10mV_V_VSB_INT_SCALE_FACT        ((uint16)(RTE_F32_VSB_INT_MAX * F32_10_MILLI))
#define RTE_U16_10mV_V_VSB_EXT_SCALE_FACT        ((uint16)(RTE_F32_VSB_EXT_MAX * F32_10_MILLI))
#define RTE_U16_1mA_I_VSB_SCALE_FACT             ((uint16)(RTE_F32_ISB_MAX * F32_1_MILLI))
#define RTE_U16_10mA_I_OUT_SCALE_FACT            ((uint16)(RTE_F32_I_OUT_MAX * F32_10_MILLI)) 
#define RTE_U16_10mA_I_LOCAL_SCALE_FACT          ((uint16)(RTE_F32_I_OUT_MAX * F32_10_MILLI)) 
#define RTE_U16_10mA_I_SHARE_SCALE_FACT          ((uint16)(RTE_F32_I_OUT_MAX * F32_10_MILLI)) 

/***********************************************
 * Uart
 **********************************************/

/* Define UART architecture */
#define RTE_UART_CHANNEL_USED             2U             /* UART1:PRI, UART2:SEC */

/* 0: only TX to PRI1, 1: TX to PRI1 and PRI2, 2: TX to PRI1 and PRI2 and broadcast*/
#define RTE_UART1_TX_PRI_SEQUENCE         0U

#define RTE_UART1_TX_PRI_1                0U
#define RTE_UART1_TX_PRI_2                1U
#define RTE_UART1_TX_PRI_ALL              2U

#if (2U == RTE_UART_CHANNEL_USED)
/* 0: only TX to SEC1, 1: TX to SEC1 and SEC2, 2: TX to SEC1 and SEC2 and broadcast*/
  #define RTE_UART2_TX_SEC_SEQUENCE       0U

  #define RTE_UART2_TX_SEC_1              0U
  #define RTE_UART2_TX_SEC_2              1U
  #define RTE_UART2_TX_SEC_ALL            2U
#endif

/* true: calculate crc for one byte once,  false: calculate crc for all data once */
#define RTE_UART_CAL_CRC_DISTRIBUTED      TRUE

#define RTE_UART1_TX_BUF_SIZE             ((uint16)128U)  /* COM TX to PRI */
#define RTE_UART1_RX_BUF_SIZE             ((uint16)128U)  /* COM RX from PRI */
#if (2U == RTE_UART_CHANNEL_USED)
  #define RTE_UART2_TX_BUF_SIZE           ((uint16)128U)  /* COM TX to SEC */
  #define RTE_UART2_RX_BUF_SIZE           ((uint16)128U)  /* COM RX from SEC */
#endif
#define RTE_UART_MIN_FRAME_LEN	          ((uint16)5U)   /* STX,ADDR,LEN,DATA0,CRC8 */
#define RTE_UART_FRAME_AUX_LEN			      ((uint16)4U)   /* STX,ADDR,LEN,CRC8 */	

/* Define frame format */
#define RTE_UART_FRAME_STX                0xAA           /* Start of a UART frame */
#define RTE_UART_ADDR_PRI_1               0x10           /* MCU address */
#define RTE_UART_ADDR_PRI_2               0x11                 
#define RTE_UART_ADDR_PRI_ALL             0x1F                
#define RTE_UART_ADDR_SEC_1               0x20                 
#define RTE_UART_ADDR_SEC_2               0x21                 
#define RTE_UART_ADDR_SEC_ALL             0x2F                  
#define RTE_UART_ADDR_COM                 0x30  

/* Define supported baudrate */
#define RTE_UART_BAUDRATE_4800            4800U          /* 1ms   RX polling */ 
#define RTE_UART_BAUDRATE_9600            9600U          /* 500us RX polling */
#define RTE_UART_BAUDRATE_19200           19200U         /* 200us RX polling */
#define RTE_UART_BAUDRATE_38400           38400U         /* 100us RX polling */
#define RTE_UART_BAUDRATE_57600           57600U         /* 100us RX polling */
#define RTE_UART_BAUDRATE_115200          115200UL       /* 50us  RX polling */

#define RTE_UART1_BAUDRATE                RTE_UART_BAUDRATE_38400   /* set baudrate */ 
#define RTE_UART2_BAUDRATE                RTE_UART_BAUDRATE_38400  /* set baudrate */

#define RTE_UART_RX_BYTE_TIMEOUT_4800     5U             /* Value * 1ms = time */ 
#define RTE_UART_RX_BYTE_TIMEOUT_9600     3U             /* Value * 1ms = time */ 
#define RTE_UART_RX_BYTE_TIMEOUT_19200    2U             /* Value * 1ms = time */
#define RTE_UART_RX_BYTE_TIMEOUT_38400    1U             /* Value * 1ms = time */
#define RTE_UART_RX_BYTE_TIMEOUT_57600    1U             /* Value * 1ms = time */
#define RTE_UART_RX_BYTE_TIMEOUT_115200   1U             /* Value * 1ms = time */

#define RTE_UART_RX_FRAME_TIMEOUT_4800    8U             /* Value * 1ms = time */
#define RTE_UART_RX_FRAME_TIMEOUT_9600    6U             /* Value * 1ms = time */
#define RTE_UART_RX_FRAME_TIMEOUT_19200   5U             /* Value * 1ms = time */
#define RTE_UART_RX_FRAME_TIMEOUT_38400   4U             /* Value * 1ms = time */
#define RTE_UART_RX_FRAME_TIMEOUT_57600   4U             /* Value * 1ms = time */
#define RTE_UART_RX_FRAME_TIMEOUT_115200  4U             /* Value * 1ms = time */

#define RTE_UART_TX_TIMEOUT_4800          7U             /* Value * 1ms = time */
#define RTE_UART_TX_TIMEOUT_9600          5U             /* Value * 1ms = time */
#define RTE_UART_TX_TIMEOUT_19200         4U             /* Value * 1ms = time */
#define RTE_UART_TX_TIMEOUT_38400         3U             /* Value * 1ms = time */
#define RTE_UART_TX_TIMEOUT_57600         3U             /* Value * 1ms = time */
#define RTE_UART_TX_TIMEOUT_115200        3U             /* Value * 1ms = time */

/* UART1 timeout config*/
#if (RTE_UART_BAUDRATE_4800 == RTE_UART1_BAUDRATE)
  #define RTE_UART1_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_4800
  #define RTE_UART1_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_4800
  #define RTE_UART1_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_4800
#endif
#if (RTE_UART_BAUDRATE_9600 == RTE_UART1_BAUDRATE)
  #define RTE_UART1_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_9600
  #define RTE_UART1_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_9600
  #define RTE_UART1_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_9600
#endif
#if (RTE_UART_BAUDRATE_19200 == RTE_UART1_BAUDRATE)
  #define RTE_UART1_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_19200
  #define RTE_UART1_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_19200
  #define RTE_UART1_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_19200
#endif
#if (RTE_UART_BAUDRATE_38400 == RTE_UART1_BAUDRATE)
  #define RTE_UART1_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_38400
  #define RTE_UART1_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_38400
  #define RTE_UART1_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_38400
#endif
#if (RTE_UART_BAUDRATE_57600 == RTE_UART1_BAUDRATE)
  #define RTE_UART1_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_57600
  #define RTE_UART1_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_57600
  #define RTE_UART1_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_57600
#endif
#if (RTE_UART_BAUDRATE_115200 == RTE_UART1_BAUDRATE)
  #define RTE_UART1_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_115200
  #define RTE_UART1_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_115200
  #define RTE_UART1_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_115200
#endif

/* UART2 timeout config*/
#if (2U == RTE_UART_CHANNEL_USED)
  #if (RTE_UART_BAUDRATE_4800 == RTE_UART2_BAUDRATE)
    #define RTE_UART2_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_4800
    #define RTE_UART2_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_4800
    #define RTE_UART2_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_4800
  #endif
  #if (RTE_UART_BAUDRATE_9600 == RTE_UART2_BAUDRATE)
    #define RTE_UART2_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_9600
    #define RTE_UART2_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_9600
    #define RTE_UART2_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_9600
  #endif
  #if (RTE_UART_BAUDRATE_19200 == RTE_UART2_BAUDRATE)
    #define RTE_UART2_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_19200
    #define RTE_UART2_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_19200
    #define RTE_UART2_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_19200
  #endif
  #if (RTE_UART_BAUDRATE_38400 == RTE_UART2_BAUDRATE)
    #define RTE_UART2_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_38400
    #define RTE_UART2_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_38400
    #define RTE_UART2_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_38400
  #endif
  #if (RTE_UART_BAUDRATE_57600 == RTE_UART2_BAUDRATE)
    #define RTE_UART2_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_57600
    #define RTE_UART2_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_57600
    #define RTE_UART2_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_57600
  #endif
  #if (RTE_UART_BAUDRATE_115200 == RTE_UART2_BAUDRATE)
    #define RTE_UART2_RX_BYTE_TIMEOUT         RTE_UART_RX_BYTE_TIMEOUT_115200
    #define RTE_UART2_RX_FRAME_TIMEOUT        RTE_UART_RX_FRAME_TIMEOUT_115200
    #define RTE_UART2_TX_TIMEOUT              RTE_UART_TX_TIMEOUT_115200
  #endif
#endif

#define RTE_UART1_FAIL_CNT                ((uint16)800U)   /* Total 2s for each CH, Value * 1ms = time */
#define RTE_UART2_FAIL_CNT                ((uint16)800U)   /* Total 2s for each CH, Value * 1ms = time */       
 
#define RTE_SYS_CLK_FREQ                  ((uint32)48000000UL)    /* 48MHz */  

/***********************************************
 * Fan control duty
**********************************************/        
#define RTE_FAN_MAX_DUTY                 100    
/***********************************************
 * Fan control number
 **********************************************/
#define RTE_FAN_CTRL_NBR                  2
#define RTE_FAN1                          0
#define RTE_FAN2                          1
#define RTE_FAN3                          2
#define RTE_FAN4                          3   


typedef union FANCTRL_U_STATUS_12_
{
  uint8 ALL;
  struct
  { 
    uint8 AIR_FLOW_12_WARNING : 1;  /* bit0 */
    uint8 AIR_FLOW_12_FAULT   : 1;  /* bit1 */
    uint8 FAN_2_SPEED_OVRD    : 1;  /* bit2 */
    uint8 FAN_1_SPEED_OVRD    : 1;  /* bit3 */
    uint8 FAN_2_WARNING       : 1;  /* bit4 */
    uint8 FAN_1_WARNING       : 1;  /* bit5 */
    uint8 FAN_2_FAULT         : 1;  /* bit6 */
    uint8 FAN_1_FAULT         : 1;  /* bit7 */
  } Bits;
} FANCTRL_U_STATUS_12;

typedef union FANCTRL_U_STATUS_34_
{
  uint8 ALL;
  struct
  { 
    uint8 AIR_FLOW_34_WARNING : 1;  /* bit0 */
    uint8 AIR_FLOW_34_FAULT   : 1;  /* bit1 */
    uint8 FAN_4_SPEED_OVRD    : 1;  /* bit2 */
    uint8 FAN_3_SPEED_OVRD    : 1;  /* bit3 */
    uint8 FAN_4_WARNING       : 1;  /* bit4 */
    uint8 FAN_3_WARNING       : 1;  /* bit5 */
    uint8 FAN_4_FAULT         : 1;  /* bit6 */
    uint8 FAN_3_FAULT         : 1;  /* bit7 */
  } Bits;
} FANCTRL_U_STATUS_34;

/***********************************************
 * PMBus
 **********************************************/
#define RTE_I2C_DEB_BUF_SIZE             ((uint16)0x80)

/***********************************************
 * Temperature control (tempctrl module )
 **********************************************/
#define RTE_TEMP_TOTAL_NUM              5u
 /*********************************
	* temperature status bit
	********************************/
#define RTE_B_TEMP_OUTLET_OTW    RTE_uTempOtwStatus.Bits.f0
#define RTE_B_TEMP_ORING_OTW     RTE_uTempOtwStatus.Bits.f1
#define RTE_B_TEMP_PFC_OTW       RTE_uTempOtwStatus.Bits.f2
#define RTE_B_TEMP_SR_OTW        RTE_uTempOtwStatus.Bits.f3
#define RTE_B_TEMP_ANY_OTW       RTE_uTempOtwStatus.Bits.ff

#define RTE_B_TEMP_OUTLET_OTP    RTE_uTempOtpStatus.Bits.f0  
#define RTE_B_TEMP_ORING_OTP     RTE_uTempOtpStatus.Bits.f1
#define RTE_B_TEMP_PFC_OTP       RTE_uTempOtpStatus.Bits.f2
#define RTE_B_TEMP_SR_OTP        RTE_uTempOtpStatus.Bits.f3
#define RTE_B_TEMP_ANY_OTP       RTE_uTempOtpStatus.Bits.ff

#define RTE_TEMP_NTC_FAULT       RTE_uTempStatus.Bits.f0

/***********************************************
 * DIO status bit
 **********************************************/
/* Input */
#define RTE_B_DIO_PS_KILL_ACTIVE         RTE_uDioInStatus.Bits.f0
#define RTE_B_DIO_PSON_ACTIVE            RTE_uDioInStatus.Bits.f1
#define RTE_B_DIO_VSB_OVP_ACTIVE         RTE_uDioInStatus.Bits.f2
#define RTE_B_DIO_54V_FAULT_ACTIVE       RTE_uDioInStatus.Bits.f3
#define RTE_B_DIO_VIN_OK_ACTIVE          RTE_uDioInStatus.Bits.f4
#define RTE_B_DIO_I2C_ADDRESS0           RTE_uDioInStatus.Bits.f5
#define RTE_B_DIO_I2C_ADDRESS1           RTE_uDioInStatus.Bits.f6
#define RTE_B_DIO_I2C_ADDRESS2           RTE_uDioInStatus.Bits.f7

/* Output */
#define RTE_B_DIO_PWOK_ENA               RTE_uDioOutStatus.Bits.f0
#define RTE_B_DIO_SMBALERT_ENA           RTE_uDioOutStatus.Bits.f1
#define RTE_B_DIO_SYNC_INTERNAL_ON       RTE_uDioOutStatus.Bits.f2
#define RTE_B_DIO_VSB_CLEAR_LATCH_ON     RTE_uDioOutStatus.Bits.f3
#define RTE_B_DIO_VSB_OVPTEST_ACTIVE     RTE_uDioOutStatus.Bits.f4
#define RTE_B_DIO_VSB_ON                 RTE_uDioOutStatus.Bits.f5
#define RTE_B_DIO_INPUT_LED_OK_ON        RTE_uDioOutStatus.Bits.f6
#define RTE_B_DIO_OUTPUT_LED_OK_ON       RTE_uDioOutStatus.Bits.f7
#define RTE_B_DIO_LED_FAULT_ON           RTE_uDioOutStatus.Bits.f8
#define RTE_B_DIO_VINOK_ENA              RTE_uDioOutStatus.Bits.f9


/***********************************************
 * Trim status bit
 **********************************************/
#define RTE_B_PSUCTRL_V1_TRIM              RTE_uPsuCtrlStatus.Bits.f0
#define RTE_B_PSUCTRL_VSB_TRIM             RTE_uPsuCtrlStatus.Bits.f1
#define RTE_B_PSUCTRL_V1_OVP_TEST          RTE_uPsuCtrlStatus.Bits.f2
#define RTE_B_PSUCTRL_VSB_OVP_TEST         RTE_uPsuCtrlStatus.Bits.f3
#define RTE_B_PSUCTRL_ORING_TEST_FAIL      RTE_uPsuCtrlStatus.Bits.f4
#define RTE_B_PSUCTRL_ORING_TEST_DONE      RTE_uPsuCtrlStatus.Bits.f5
#define RTE_B_PSUCTRL_LS_CALI_MODE         RTE_uPsuCtrlStatus.Bits.f6


/***********************************************
 * Intcom1 status bit (Primary side)
 **********************************************/
#define RTE_B_PRI_VDC_IN             RTE_Pri.u16PriStatus00.Bits.f0  /* 1 = input valtage is DC */
#define RTE_B_PRI_VIN_OK             RTE_Pri.u16PriStatus00.Bits.f1  /* 1 = input voltage is OK */
#define RTE_B_PRI_BULK_OK            RTE_Pri.u16PriStatus00.Bits.f2  /* 1 = bulk voltage is OK */
#define RTE_B_PRI_VIN_LINE_LOW       RTE_Pri.u16PriStatus00.Bits.f3  /* 1 = low line */
#define RTE_B_PRI_VIN_ALERT          RTE_Pri.u16PriStatus00.Bits.f4  /* 1 = input voltage alert to inform sec. */
#define RTE_B_PRI_BULK_OV            RTE_Pri.u16PriStatus00.Bits.f5  /* 1 = bulk is over voltage */
#define RTE_B_PRI_PFC_OT             RTE_Pri.u16PriStatus00.Bits.f6  /* 1 = PSU is over temperature */
/* Control bits */
#define RTE_B_PRI_PFC_HALT           RTE_Pri.u16PriStatus00.Bits.f7  /* 1 = PFC GO */
#define RTE_B_PRI_RELAY_ON           RTE_Pri.u16PriStatus00.Bits.f8  /* 1 = relat is closed */
#define RTE_B_PRI_PFC_EN             RTE_Pri.u16PriStatus00.Bits.f9  /* 1 = PFC is turn on */
#define RTE_B_PRI_EXT_EN             RTE_Pri.u16PriStatus00.Bits.fa  /* 1 = extender is turn on */
#define RTE_B_PRI_PFC_OT_DIS         RTE_Pri.u16PriStatus00.Bits.fb  /* 1 = PSU disable OT judgement */
#define RTE_B_PRI_BL_MODE            RTE_Pri.u16PriStatus00.Bits.fc  /* 1 = Boot loader mode */
#define RTE_B_PRI_BL_EXIST           RTE_Pri.u16PriStatus00.Bits.fd  /* 1 = Boot loader is existing */
#define RTE_B_PRI_PFC_OPP            RTE_Pri.u16PriStatus00.Bits.fe  /* 1 = PFC stage over power */
#define RTE_B_PRI_VIN_DROPOUT        RTE_Pri.u16PriStatus00.Bits.ff  /* 1 = Input voltage is dropout */
/* Primary Control bits */
#define RTE_B_PRI_PFC_OVP            RTE_Pri.u16PriStatus01.Bits.f0   /* 1 = PFC over voltage */
#define RTE_B_IIN_OFFSET_CALIB       RTE_Pri.u16PriStatus01.Bits.fe   /* 1 = New offset calibration value available for EEPROM */
#define RTE_B_BULK_EXT_UV            RTE_Pri.u16PriStatus01.Bits.ff   /* 1 = Extender bulk is UV */

#define RTE_B_PRI_UART_FAIL          RTE_uIntcom1Status.Bits.f0 
#define RTE_B_PRI_REV_UPDATE         RTE_uIntcom1Status.Bits.f1 
#define RTE_B_PRI_NO_RX_PKG          RTE_uIntcom1Status.Bits.f2 
#define RTE_B_PRI_METER_IC_CALI      RTE_uIntcom1Status.Bits.f3
#define RTE_B_PRI_SLEEP_MODE         RTE_uIntcom1Status.Bits.f4
#define RTE_B_PRI_ORING_TEST         RTE_uIntcom1Status.Bits.f5
#define RTE_B_PRI_CPU_RESET          RTE_uIntcom1Status.Bits.f6
#define RTE_B_PRI_CPU_RESET_FLG      RTE_uIntcom1Status.Bits.f7
#define RTE_B_PRI_RX_PKG             RTE_uIntcom1Status.Bits.f8

/***********************************************
 * Intcom2 status bit (Secondary side)
 **********************************************/
/* Status bits */
#define RTE_B_SEC_COM_HALT            RTE_Sec.u16SecStatus00.Bits.f0    /* 1 = LLC controlled by com */
#define RTE_B_SEC_LLC_EN              RTE_Sec.u16SecStatus00.Bits.f1    /* 1 = LLC enabled */
#define RTE_B_SEC_LLC_CURR_LIMIT      RTE_Sec.u16SecStatus00.Bits.f2    /* 1 = Current limit mode active */
#define RTE_B_SEC_LLC_SOFT_START      RTE_Sec.u16SecStatus00.Bits.f3    /* 1 = Soft start active */
#define RTE_B_SEC_ISHARE_EN           RTE_Sec.u16SecStatus00.Bits.f4    /* 1 = Active current share enabled */
#define RTE_B_SEC_PRIM_VIN_LOST       RTE_Sec.u16SecStatus00.Bits.f6    /* 1 = Primary side input voltage lost */
#define RTE_B_SEC_PRIM_VIN_LINE       RTE_Sec.u16SecStatus00.Bits.f7    /* 1 = Primary side input voltage line: 1 = Vin high line; 0 = Vin low line */
#define RTE_B_SEC_OT_DISABLED         RTE_Sec.u16SecStatus00.Bits.fc    /* 1 = Disabled OT judgement */
#define RTE_B_SEC_OVP_TEST            RTE_Sec.u16SecStatus00.Bits.fd    /* 1 = Over voltage protection test */
#define RTE_B_SEC_BL_MODE             RTE_Sec.u16SecStatus00.Bits.fe    /* 1 = Boot loader mode */
#define RTE_B_SEC_BL_EXIST            RTE_Sec.u16SecStatus00.Bits.ff    /* 1 = Boot loader is existing */
/* Fault status bits */
#define RTE_B_SEC_OVP                 RTE_Sec.u16SecStatus01.Bits.f0    /* 1 = LLC over voltage */
#define RTE_B_SEC_OVW                 RTE_Sec.u16SecStatus01.Bits.f1    /* 1 = LLC over voltage warning */
#define RTE_B_SEC_UVP                 RTE_Sec.u16SecStatus01.Bits.f2    /* 1 = LLC under voltage */
#define RTE_B_SEC_UVW                 RTE_Sec.u16SecStatus01.Bits.f3    /* 1 = LLC under voltage warning */
#define RTE_B_SEC_OCP                 RTE_Sec.u16SecStatus01.Bits.f4    /* 1 = LLC over current */
#define RTE_B_SEC_OCW                 RTE_Sec.u16SecStatus01.Bits.f5    /* 1 = LLC over current warning */
#define RTE_B_SEC_OCP_CT              RTE_Sec.u16SecStatus01.Bits.f8    /* 1 = LLC CT over current */
#define RTE_B_SEC_OPP                 RTE_Sec.u16SecStatus01.Bits.f9    /* 1 = LLC stage over power */
#define RTE_B_SEC_FAN_FAIL_1          RTE_Sec.u16SecStatus01.Bits.fa    /* 1 = Fan 1 fail */
#define RTE_B_SEC_FAN_FAIL_2          RTE_Sec.u16SecStatus01.Bits.fb    /* 1 = Fan 2 fail */
#define RTE_B_SEC_FAN_SPD_LOW_1       RTE_Sec.u16SecStatus01.Bits.fc    /* 1 = Fan 1 low speed */
#define RTE_B_SEC_FAN_SPD_LOW_2       RTE_Sec.u16SecStatus01.Bits.fd    /* 1 = Fan 2 low speed */
#define RTE_B_SEC_PSU_OT              RTE_Sec.u16SecStatus01.Bits.fe    /* 1 = LLC over temperature */
/* Fault status clear bits */
#define RTE_B_SEC_FAULT_CLR           RTE_Sec.u16SecStatus02.Bits.f0    /* 1 = LLC fault clear */
#define RTE_B_SEC_OV_LATCH_CLR        RTE_Sec.u16SecStatus02.Bits.f1    /* 1 = LLC OVP latch clear */
#define RTE_B_SEC_UV_LATCH_CLR        RTE_Sec.u16SecStatus02.Bits.f2    /* 1 = LLC UVP latch clear */
#define RTE_B_SEC_OC_LATCH_CLR        RTE_Sec.u16SecStatus02.Bits.f3    /* 1 = LLC OCP latch clear */

#define RTE_B_SEC_UART_FAIL             RTE_uIntcom2Status.Bits.f0 
#define RTE_B_SEC_REV_UPDATE            RTE_uIntcom2Status.Bits.f1 
#define RTE_B_SEC_NO_RX_PKG             RTE_uIntcom2Status.Bits.f2 
#define RTE_B_SEC_SLEEP_MODE            RTE_uIntcom2Status.Bits.f3
#define RTE_B_SEC_ORING_TEST            RTE_uIntcom2Status.Bits.f4 
#define RTE_B_SEC_CPU_RESET             RTE_uIntcom2Status.Bits.f5
#define RTE_B_SEC_CPU_RESET_FLG         RTE_uIntcom2Status.Bits.f6
#define RTE_B_SEC_RX_PKG                RTE_uIntcom2Status.Bits.f7 
/***********************************************
 * Com to Sec/Pri status bit
 **********************************************/
#define RTE_B_TO_PRI_STA_METER_IC_CALI      RTE_uComToPriStatus.Bits.f0 
#define RTE_B_TO_PRI_STA_SLEEP_MODE         RTE_uComToPriStatus.Bits.f1
#define RTE_B_TO_PRI_STA_ORING_TEST         RTE_uComToPriStatus.Bits.f2
#define RTE_B_TO_PRI_STA_CPU_RESET          RTE_uComToPriStatus.Bits.f3

#define RTE_B_TO_SEC_STA_TURN_ON_MAIN       RTE_uComToSecStatus.Bits.f0 
#define RTE_B_TO_SEC_STA_OVP_TEST           RTE_uComToSecStatus.Bits.f1 
#define RTE_B_TO_SEC_STA_AC_LOST            RTE_uComToSecStatus.Bits.f2 
#define RTE_B_TO_SEC_STA_REMOTE_ON          RTE_uComToSecStatus.Bits.f3 
#define RTE_B_TO_SEC_STA_VIN_LINE_LOW       RTE_uComToSecStatus.Bits.f4
#define RTE_B_TO_SEC_STA_CLEAR_LATCH_FAULT  RTE_uComToSecStatus.Bits.f5
#define RTE_B_TO_SEC_STA_DISABLE_VSHARE     RTE_uComToSecStatus.Bits.f6


/* Com MCU status define */
/* COM_Status_00 */
#define RTE_B_COM_VSB_PWOK                    RTE_uComStatus00.Bits.f0
#define RTE_B_COM_VSB_ON                      RTE_uComStatus00.Bits.f1
#define RTE_B_COM_VSB_MONI_EN                 RTE_uComStatus00.Bits.f2
#define RTE_B_COM_VIN_OK                      RTE_uComStatus00.Bits.f3
#define RTE_B_COM_NO_VIN                      RTE_uComStatus00.Bits.f4
#define RTE_B_COM_V1_MONI_EN                  RTE_uComStatus00.Bits.f5
#define RTE_B_COM_INPUT_OFF                   RTE_uComStatus00.Bits.f6
#define RTE_B_COM_OUTPUT_OK                   RTE_uComStatus00.Bits.f7
#define RTE_B_COM_V1_ON                       RTE_uComStatus00.Bits.f8
#define RTE_B_COM_SMBALLERT_ST                RTE_uComStatus00.Bits.f9

/* COM_Status_01 */
#define RTE_B_COM_VSB_LATCH                   RTE_uComStatus01.Bits.f0
#define RTE_B_COM_VSB_OVP                     RTE_uComStatus01.Bits.f1
#define RTE_B_COM_VSB_OVW                     RTE_uComStatus01.Bits.f2
#define RTE_B_COM_VSB_UVP                     RTE_uComStatus01.Bits.f3
#define RTE_B_COM_VSB_UVW                     RTE_uComStatus01.Bits.f4
#define RTE_B_COM_VSB_OCP                     RTE_uComStatus01.Bits.f5
#define RTE_B_COM_VSB_OCW                     RTE_uComStatus01.Bits.f6
#define RTE_B_COM_V1_LATCH                    RTE_uComStatus01.Bits.f7
#define RTE_B_COM_VIN_UV                      RTE_uComStatus01.Bits.f8
#define RTE_B_COM_VIN_OV                      RTE_uComStatus01.Bits.f9
#define RTE_B_COM_VIN_UVW                     RTE_uComStatus01.Bits.fa
#define RTE_B_COM_ANY_NTC_FAULT               RTE_uComStatus01.Bits.fb
#define RTE_B_COM_AC_OFFSET_SAVEED            RTE_uComStatus01.Bits.fc
#define RTE_B_COM_AC_OFFSET_NEED_SAVE         RTE_uComStatus01.Bits.fd

#define RTE_B_COM_CLEAR_BLACK_BOX             RTE_uComStatus02.Bits.f0
#define RTE_B_COM_CLEAR_BLACK_BOX_OTHER_FAIL  RTE_uComStatus02.Bits.f1
#define RTE_B_COM_CLEAR_BLACK_BOX_VINUVP_FAIL RTE_uComStatus02.Bits.f2
#define RTE_B_COM_READ_BLACK_BOX_OTHER_FAIL   RTE_uComStatus02.Bits.f3
#define RTE_B_COM_READ_BLACK_BOX_VINUVP_FAIL  RTE_uComStatus02.Bits.f4
#define RTE_B_COM_V1_OVP                      RTE_uComStatus02.Bits.f5
#define RTE_B_COM_V1_UVP                      RTE_uComStatus02.Bits.f6
#define RTE_B_COM_V1_OCP                      RTE_uComStatus02.Bits.f7
#define RTE_B_COM_V1_OCW                      RTE_uComStatus02.Bits.f8
#define RTE_B_COM_V1_LATCHED                  RTE_uComStatus02.Bits.f9

/***********************************************
 * Com RTC bit
 **********************************************/
#define RTE_COM_RTC_TR_SECOND_UNIT            RTC_TR_SECOND_UNIT_BIT0

/*******************************************************************************
 * Included header
 ******************************************************************************/

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

#define PMB_VM_Y_VSB_VOUT(X)            ( (uint16)( (X) * 512UL))
#define PMB_LF_Y_VSB_IOUT(X)            ( (uint16)((uint16)((X) * 128UL) + SCALE_MN7))


/***********************************************
 * Calibrate
 **********************************************/
typedef union CALI_U_STATUS_
{
  uint8 ALL;

  struct
  {
    uint8 CALI_COMMAND : 1; /* bit0 */
    uint8 CALI_SAVE_NEED : 1; /* bit1 */
    uint8 CALI_DEFAULT : 1; /* bit2 */
    uint8 CALI_CRC_FAULT : 1; /* bit3 */
    uint8 CALI_DONE : 1; /* bit4 */
    uint8 CALI_READ : 1; /* bit5 */
    uint8 CALI_READ_OK : 1; /* bit6 */
    uint8 CALI_NEW_DATA : 1; /* bit7 */
  } Bits;
} CALI_U_STATUS;

typedef struct CALI_S_Common_
{
  sint16 s16Amp;
  sint16 s16Ofs;
  uint16 s16Thr;
  uint8 u8Crc8;
} CALI_S_COMMON;

typedef struct CALI_S_PARAMETER_
{
  uint8 u8DataBytes;
  uint8 u8DataMode;
  uint8 u8DataLine;
  uint16 u16SaveAddr;

  CALI_S_COMMON sUser;
} CALI_S_PARAMETER;

typedef enum MG_E_DO_CALI_SENOSR_
{
  MG_E_DO_CALI_VIN = 0,
  MG_E_DO_CALI_IIN,
  MG_E_DO_CALI_PIN,
  MG_E_DO_CALI_V1,
  MG_E_DO_CALI_VSB,
	MG_E_DO_CALI_V1SENSE,
	MG_E_DO_CALI_V1ISHARE,
	MG_E_DO_CALI_VCAP
} MG_E_DO_CALI_SENOSR;

typedef struct CALI_S_TEMP_
{
  sint16 s16Amp;
  sint16 s16Ofs;
  sint16 s16Thr;
  uint8  u8Crc8;
} CALI_S_TEMP;


#define CALI_VIN_AC_LINE_NUM        ((uint8)1U)
#define CALI_IIN_AC_LINE_NUM        ((uint8)2U)
#define CALI_PIN_AC_LINE_NUM        ((uint8)2U)

#define CALI_V_V1_LINE_NUM          ((uint8)1U)
#define CALI_I_V1_LINE_NUM          ((uint8)3U)
#define CALI_V_VSB_LINE_NUM         ((uint8)1U)
#define CALI_I_VSB_LINE_NUM         ((uint8)3U)

#define CALI_V1_ISHARE_LINE_NUM     ((uint8)3U)

typedef struct CALI_S_DATA_
{
  CALI_S_COMMON sVinAc[CALI_VIN_AC_LINE_NUM];
  CALI_S_COMMON sIinAc[CALI_IIN_AC_LINE_NUM];
  CALI_S_COMMON sPinAc[CALI_PIN_AC_LINE_NUM];
  CALI_S_COMMON sVoutV1[CALI_V_V1_LINE_NUM];
  CALI_S_COMMON sIoutV1[CALI_I_V1_LINE_NUM];
  CALI_S_COMMON sVoutVsb[CALI_V_VSB_LINE_NUM];
  CALI_S_COMMON sIoutVsb[CALI_I_VSB_LINE_NUM];
  CALI_S_COMMON sV1IShare[CALI_V1_ISHARE_LINE_NUM];
} CALI_S_DATA;

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/***********************************************
 * bootloader
 **********************************************/
#define BOOT_BL_PAGE_NUM_START      0    /* 256 per page */
#define BOOT_BL_PAGE_NUM_SIZE       64u
#define BOOT_BL_PAGE_NUM_END        (BOOT_BL_PAGE_NUM_START + BOOT_BL_PAGE_NUM_SIZE - 1)   /* 256 per page */

#define BOOT_APP_PAGE_NUM_START     (BOOT_BL_PAGE_NUM_END + 1)   /* 256 per page */
#define BOOT_APP_PAGE_NUM_SIZE      184u
#define BOOT_APP_PAGE_NUM_END       (BOOT_APP_PAGE_NUM_START + BOOT_APP_PAGE_NUM_SIZE - 1)  /* 256 per page */

#define BOOT_CRC_BF_PAGE_NUM_START  (BOOT_APP_PAGE_NUM_END + 1)   /* 256 per page */
#define BOOT_CRC_BF_PAGE_NUM_SIZE   8u
#define BOOT_CRC_BF_PAGE_NUM_END    (BOOT_CRC_BF_PAGE_NUM_START + BOOT_CRC_BF_PAGE_NUM_SIZE - 1)   /* 256 per page */

#define BOOT_FLASH_BASE_ADDR     ((uint32)0x08000000u)
#define BOOT_ADDR_NUM_PER_PAGE   ((uint32)256u)
#define BOOT_CRC_BF_ADDR_START   BOOT_FLASH_BASE_ADDR+BOOT_ADDR_NUM_PER_PAGE*BOOT_CRC_BF_PAGE_NUM_START
#define BOOT_APP_START_ADDR      BOOT_FLASH_BASE_ADDR+BOOT_ADDR_NUM_PER_PAGE*BOOT_APP_PAGE_NUM_START
#define BOOT_APP_END_ADDR        ((BOOT_FLASH_BASE_ADDR+(uint32)BOOT_ADDR_NUM_PER_PAGE*(BOOT_APP_PAGE_NUM_END+1))-1)

#define BOOT_PEC_STATUS_ADDR_START (BOOT_CRC_BF_ADDR_START + 4)
#define APP_VECTOR_TABLR_ADDR    (BOOT_APP_START_ADDR + 0x10U)

#define BOOT_FLAG_SET_COM_S    0x55
#define BOOT_FLAG_SET_PRI_A    0x66
#define BOOT_FLAG_SET_SEC_A    0x77
#define BOOT_FLAG_SET_PRI_B    0x88
#define BOOT_FLAG_SET_SEC_B    0x99
#define BOOT_FLAG_SET_PRI_ALL  0xAA
#define BOOT_FLAG_SET_SEC_ALL  0xBB
#define BOOT_FLAG_CLR          0xFF

#define	PRI_uC_A		          (0x10U)
#define	PRI_uC_B			        (0x11U)
#define	SEC_uC_A			        (0x20U)
#define	SEC_uC_B              (0x21U)
#define	COM_uC_S              (0x30U)
#define	PRI_uC_ALL            (0x1FU)
#define	SEC_uC_ALL            (0x2FU)

#define REV_FLASH_SAVE_ADDR     ((uint32)0x08003000)
/***********************************************
 * I2C
 **********************************************/
#define I2C_RX_BUF_SIZE            255u
#define I2C_TX_BUF_SIZE            255u

#define RTE_COM_A0_FLG           RTE_u16I2cStatus0.Bits.f0  
#define RTE_COM_A1_FLG           RTE_u16I2cStatus0.Bits.f1 
#define RTE_COM_A2_FLG           RTE_u16I2cStatus0.Bits.f2 
#define RTE_I2C_MUX_RESET        RTE_u16I2cStatus0.Bits.f3 
#define RTE_I2C_MUX_RESET_OLD    RTE_u16I2cStatus0.Bits.f4
#define RTE_I2C_RESET_FLG        RTE_u16I2cStatus0.Bits.f5
#define RTE_I2C_SCL_IO_FLG       RTE_u16I2cStatus0.Bits.f6 
#define RTE_I2C_SDA_IO_FLG       RTE_u16I2cStatus0.Bits.f7 
#define RTE_I2C_CMD_WAIT_FLG     RTE_u16I2cStatus0.Bits.f8
#define RTE_I2C_PEC_ERR_FLG      RTE_u16I2cStatus0.Bits.f9
#define RTE_I2C_PEC_CHANGE_FLG   RTE_u16I2cStatus0.Bits.fa
#define RTE_I2C_CMD_DETECTED     RTE_u16I2cStatus0.Bits.fb

/***********************************************
 * UART
 **********************************************/
typedef union RTE_U_UARTSTATUS_
{
  struct
  {
    uint8 u8BootMode   : 1;   /* bit0 */
    uint8 u8CrcErr     : 1;   /* bit1 */
    uint8 u8McuAddrErr : 1;   /* bit2 */
    uint8 u8LenErr     : 1;   /* bit3 */
    uint8 u8ByteTmout  : 1;   /* bit4 */
    uint8 u8FrameTmout : 1;   /* bit5 */
    uint8 u8InvalidData: 1;   /* bit6 */
    uint8 u8UartRegErr : 1;   /* bit7 */
  } Bit;
  uint8 Byte;
} RTE_U_UARTSTATUS;

typedef struct RTE_S_UART_DATA_
{
  uint16 u16TxDataCnt;
  uint16 u16RxDataCnt;
  uint16 u16RxByteTmOutEna;
  uint16 u16RxByteTmOutCnt;
  uint16 u16RxFrameTmOutEna;
  uint16 u16RxFrameTmOutCnt;
  uint16 u16TxTmOutEna;
  uint16 u16TxTmOutCnt;
} RTE_S_UART_DATA;

typedef struct RTE_S_INTCOM1_DATA_
{
  GLOBAL_U_U16BIT u16PriStatus00;
  GLOBAL_U_U16BIT u16PriStatus01;
	WORD_VAL u16PriDebug0;
  WORD_VAL u16PriDebug1;
  WORD_VAL u16PriDebug2;
  WORD_VAL u1610mVVinAvg;
  WORD_VAL u161mAIinAvg;
  WORD_VAL u16100mAPinAvg;
	WORD_VAL u16100mHzVoltInFreq;
	WORD_VAL u16q16PwrFact;
  WORD_VAL u16MeterIcVin;
  WORD_VAL u16MeterIcIin;
  WORD_VAL u16MeterIcPin;
	WORD_VAL u16PfcNtcAdcAvg;
	WORD_VAL u16q12VbulkAdc;
  WORD_VAL u16AcOffset;
	GLOBAL_U_U8BIT uTempStatus00;
	GLOBAL_U_U8BIT uComStatus;
} RTE_S_INTCOM1_DATA;

typedef struct RTE_S_INTCOM2_DATA_
{
	GLOBAL_U_U16BIT u16SecStatus00;
  GLOBAL_U_U16BIT u16SecStatus01;
	GLOBAL_U_U16BIT u16SecStatus02;
  WORD_VAL u16SecDebug0;
  WORD_VAL u16SecDebug1;
  WORD_VAL u16SecDebug2;
  WORD_VAL u1610mVIntV1Avg;
  WORD_VAL u1610mVExtV1Avg;
  WORD_VAL u1610mAIoutAvg;
	WORD_VAL u16100mWPwrOutAvg;
  WORD_VAL u16VIShareAdcAvgAdc;
  WORD_VAL u16VILocalAdcAvgAdc;
  WORD_VAL u161mVSrNtcAvg;
	WORD_VAL u161mVOringNtcAvg;
	GLOBAL_U_U8BIT uTempStatus00;
	GLOBAL_U_U8BIT uComStatus;
} RTE_S_INTCOM2_DATA;

typedef union RTE_U_PMBUS_OPERATION_
{
  struct
  {
    uint8 Spare        : 7;   /* bit0 ~ bit 6 */
    uint8 OPERATION_ON : 1;   /* bit1 */
  } Bit;
  uint8 ALL;
} RTE_U_PMBUS_OPERATION;

/***********************************************
 * Fan control
 **********************************************/

/***********************************************
 * ADC
 **********************************************/

/***********************************************
 * ADC Channel number
 **********************************************/
#define RTE_ADC_CH_NBR                    (0x5u)       /* Total NTC number */

typedef enum RTE_ADC_E_INDEX_ 
{
  RTE_ADC_E_INDEX_OUTLET_AMB = 0,
  RTE_ADC_E_INDEX_INT_VSB_VOLT,
  RTE_ADC_E_INDEX_EXT_VSB_VOLT,
  RTE_ADC_E_INDEX_VSB_CURRENT,
  RTE_ADC_E_INDEX_INLET_AMB,
  RTE_ADC_E_INDEX_COUNT
} RTE_ADC_E_INDEX;

typedef enum RTE_ADC_E_FILTER_INDEX_
{
  RTE_ADC_E_FILTER_INDEX_VSB_INT = 0,
  RTE_ADC_E_FILTER_INDEX_VSB_EXT,
  RTE_ADC_E_FILTER_INDEX_VSB_CURRENT,
	RTE_ADC_E_FILTER_INDEX_COUNT
} RTE_ADC_E_FILTER_INDEX;

typedef struct RTE_S_ADC_ANALOG_
{
  uint16 u16q12Max;
  uint16 u16q12Min;
  uint16 u16q12Avg;
  uint32 u32Sum;
} RTE_S_ADC_ANALOG;

/***********************************************
 * Temperature
 **********************************************/
#define RTE_AMB_OT_WARN_LIMIT            (65)
/***********************************************
 * Vsb Monitor
 **********************************************/

/***********************************************
 * Vsb Trim
 **********************************************/
#define RTE_VSB_TRIM_DUTY_FULL            1000u
#define RTE_VSB_TRIM_DUTY_INIT            (RTE_VSB_TRIM_DUTY_FULL - 200u)
/***********************************************
 * V1 Monitor
 **********************************************/

/***********************************************
 * EEPROM map
 **********************************************/

#define RTE_EEPROM_ADDR_CONFIG_STR            (0x0000u)      /* For configure information */
#define RTE_EEPROM_ADDR_CONFIG_END            (0x007Fu)

#define RTE_EEPROM_ADDR_TRIM_STR              (0x0080u)      /* For tirm parameter */
#define RTE_EEPROM_ADDR_TRIM_END              (0x00FFu)

#define RTE_EEPROM_ADDR_CALIB_STR             (0x0100u)      /* For configure calibration */
#define RTE_EEPROM_ADDR_CALIB_END             (0x02FFu)

#define RTE_EEPROM_ADDR_BLACKBOX_STR          (0x0300u)      /* For configure balck box */
#define RTE_EEPROM_ADDR_BLACKBOX_END          (0x087Fu)

#define RTE_EEPROM_ADDR_MFR_INF_STR           (0x0880u)      /* For configure MFR information */
#define RTE_EEPROM_ADDR_MFR_INF_END           (0x08FFu)


#define RTE_MFR_DATA_RAW                      (6u)
#define RTE_MFR_DATA_COL                      (17u)

/***********************************************
 * Black box
 **********************************************/

#define RTE_BLACK_BOX_DEEPNESS              ((uint8)5)
#define RTE_BLACK_BOX_DATA_CNT_PER_FAULT    ((uint16)47)
#define RTE_BLACK_BOX_DATA_COUNT            ((uint16)RTE_BLACK_BOX_DEEPNESS * RTE_BLACK_BOX_DATA_CNT_PER_FAULT)
#define RTE_BLACK_BOX_DEEPNESS_VIN_UVP      ((uint8)5)

/***********************************************
 * PMBUS
 **********************************************/
typedef union PMBUS_U_OPERATION_
{
  uint8 ALL;

  struct
  {
    uint8 Spare : 7; /* bit0 ~ bit 6 */
    uint8 OPERATION_ON : 1; /* bit7 */
  } Bits;
} PMBUS_U_OPERATION;

typedef union PMBUS_U_BLCBOX_PAGE_W_DIS_
{
  uint8 ALL;
  struct
  {
    uint8 u8BlackBoxPage : 4; /* bit0~3 */
    uint8 u8BBPageVinUVP : 4;/* bit4~7 */
  }Bits;
}PMBUS_U_BLCBOX_PAGE_W_DIS;

typedef union PMBUS_U_LED_CTRL_
{
  uint8 ALL;

  struct
  {
    uint8 INPUT_LED_ON : 1; /* bit0 */
    uint8 INPUT_LED_OVERRIDE : 1; /* bit1 */
    uint8 OUTPUT_LED_ON : 1; /* bit2 */
    uint8 OUTPUT_LED_OVERRIDE : 1; /* bit3 */
    uint8 FAULT_LED_ON : 1; /* bit4 */
    uint8 FAULT_LED_OVERRIDE : 1; /* bit5 */
    uint8 ID_LED_TEST : 1; /* bit6 */
    uint8 ID_LED_OVERRIDE : 1; /* bit7 */
  } Bits;
} PMBUS_U_LED_CTRL;

typedef union PMBUS_U_STATUS_WORD_
{
  uint16 ALL;

  struct
  {
    uint8 LB : 8;
    uint8 HB : 8;
  } Bytes;

  struct
  {
    uint16 NONE_OF_THE_ABOVE : 1; /* bit0 */
    uint16 CML : 1; /* bit1 */
    uint16 TEMP_F_OR_W : 1; /* bit2 */
    uint16 VIN_UV_FAULT : 1; /* bit3 */
    uint16 IOUT_OC_FAULT : 1; /* bit4 */
    uint16 VOUT_OV_FAULT : 1; /* bit5 */
    uint16 UINT_OFF : 1; /* bit6 */
    uint16 UINT_BUSY : 1; /* bit7 */
    uint16 UNKNOWN_F_OR_W : 1; /* bit8 */
    uint16 OTHER : 1; /* bit9 */
    uint16 FANS_F_OR_W : 1; /* bitA */
    uint16 POWER_GOOD_N : 1; /* bitB */
    uint16 MFR_SPEC : 1; /* bitC */
    uint16 INPUT_F_OR_W : 1; /* bitD */
    uint16 IOUT_POUT_F_OR_W : 1; /* bitE */
    uint16 VOUT_F_OR_W : 1; /* bitF */
  } Bits;
} PMBUS_U_STATUS_WORD;

typedef union PMBUS_U_STATUS_VOUT_
{
  uint8 ALL;

  struct
  {
    uint8 VOUT_TRACK_ERROR : 1; /* bit0 */
    uint8 TOFF_MAX_WARN : 1; /* bit1 */
    uint8 TON_MAX_FAULT : 1; /* bit2 */
    uint8 VOUT_MAX_WARN : 1; /* bit3 */
    uint8 VOUT_UV_FAULT : 1; /* bit4 */
    uint8 VOUT_UV_WARN : 1; /* bit5 */
    uint8 VOUT_OV_WARN : 1; /* bit6 */
    uint8 VOUT_OV_FAULT : 1; /* bit7 */
  } Bits;
} PMBUS_U_STATUS_VOUT;

typedef union PMBUS_U_STATUS_IOUT_
{
  uint8 ALL;

  struct
  {
    uint8 POUT_OP_WARN : 1; /* bit0 */
    uint8 POUT_OP_FAULT : 1; /* bit1 */
    uint8 POWER_LIMIT_MODE : 1; /* bit2 */
    uint8 CURR_SHARE_FAULT : 1; /* bit3 */
    uint8 IOUT_UC_FAULT : 1; /* bit4 */
    uint8 IOUT_OC_WARN : 1; /* bit5 */
    uint8 IOUT_OC_LV_FAULT : 1; /* bit6 */
    uint8 IOUT_OC_FAULT : 1; /* bit7 */
  } Bits;
} PMBUS_U_STATUS_IOUT;

typedef union PMBUS_U_STATUS_INPUT_
{
  uint8 ALL;

  struct
  {
    uint8 PIN_OP_WARN : 1; /* bit0 */
    uint8 IIN_OC_WARN : 1; /* bit1 */
    uint8 IIN_OC_FAULT : 1; /* bit2 */
    uint8 OFF_FOR_VIN_LOW : 1; /* bit3 */
    uint8 VIN_UV_FAULT : 1; /* bit4 */
    uint8 VIN_UV_WARN : 1; /* bit5 */
    uint8 VIN_OV_WARN : 1; /* bit6 */
    uint8 VIN_OV_FAULT : 1; /* bit7 */
  } Bits;
} PMBUS_U_STATUS_INPUT;

typedef union PMBUS_U_STATUS_TEMP_
{
  uint8 ALL;

  struct
  {
    uint8 RESERVED_B0 : 1; /* bit0 */
    uint8 RESERVED_B1 : 1; /* bit1 */
    uint8 RESERVED_B2 : 1; /* bit2 */
    uint8 RESERVED_B3 : 1; /* bit3 */
    uint8 UT_FAULT : 1; /* bit4 */
    uint8 UT_WARN : 1; /* bit5 */
    uint8 OT_WARN : 1; /* bit6 */
    uint8 OT_FAULT : 1; /* bit7 */
  } Bits;
} PMBUS_U_STATUS_TEMP;

typedef union PMBUS_U_STATUS_CML_
{
  uint8 ALL;

  struct
  {
    uint8 MEM_LOGIC_FAULT : 1; /* bit0 */
    uint8 COMMS_FAULT : 1; /* bit1 */
    uint8 RESERVED_B2 : 1; /* bit2 */
    uint8 CPU_FAULT : 1; /* bit3 */
    uint8 MEM_FAULT : 1; /* bit4 */
    uint8 PEC_FAULT : 1; /* bit5 */
    uint8 INVALID_DATA : 1; /* bit6 */
    uint8 INVALID_CMD : 1; /* bit7 */
  } Bits;
} PMBUS_U_STATUS_CML;

typedef union PMBUS_U_STATUS_OTHER_
{
  uint8 ALL;

  struct
  {
    uint8 RESERVED_B0 : 1; /* bit0 */
    uint8 OUT_OR_FAULT : 1; /* bit1 */
    uint8 INB_OR_FAULT : 1; /* bit2 */
    uint8 INA_OR_FAULT : 1; /* bit3 */
    uint8 INB_BRK_FAULT : 1; /* bit4 */
    uint8 INA_BRK_FAULT : 1; /* bit5 */
    uint8 RESERVED_B6 : 1; /* bit6 */
    uint8 RESERVED_B7 : 1; /* bit7 */
  } Bits;
} PMBUS_U_STATUS_OTHER;

typedef union PMBUS_U_STATUS_MFR_
{
  uint8 ALL;

  struct
  {
    uint8 HIGH_LINE : 1; /* bit0 */
    uint8 Spare : 7; /* bit1 ~ bit 7 */
  } Bits;
} PMBUS_U_STATUS_MFR;

typedef union PMBUS_U_STATUS_FAN_12_
{
  uint8 ALL;

  struct
  {
    uint8 AIR_FLOW_WARNING : 1; /* bit0 */
    uint8 AIR_FLOW_FAULT : 1; /* bit1 */
    uint8 FAN_2_SPD_OVERRIDE : 1; /* bit2 */
    uint8 FAN_1_SPD_OVERRIDE : 1; /* bit3 */
    uint8 FAN_2_WARNING : 1; /* bit4 */
    uint8 FAN_1_WARNING : 1; /* bit5 */
    uint8 FAN_2_FAULT : 1; /* bit6 */
    uint8 FAN_1_FAULT : 1; /* bit7 */
  } Bits;
} PMBUS_U_STATUS_FAN_12;

typedef union PMBUS_U_STATUS_FAN_34_
{
  uint8 ALL;

  struct
  {
    uint8 AIR_FLOW_WARNING : 1; /* bit0 */
    uint8 AIR_FLOW_FAULT : 1; /* bit1 */
    uint8 FAN_4_SPD_OVERRIDE : 1; /* bit2 */
    uint8 FAN_3_SPD_OVERRIDE : 1; /* bit3 */
    uint8 FAN_4_WARNING : 1; /* bit4 */
    uint8 FAN_3_WARNING : 1; /* bit5 */
    uint8 FAN_4_FAULT : 1; /* bit6 */
    uint8 FAN_3_FAULT : 1; /* bit7 */
  } Bits;
} PMBUS_U_STATUS_FAN_34;

typedef union PMBUS_U_UPD_STATUS0_
{
  uint16 ALL;

  struct
  {
    uint16 VIN_UPDTING : 1; /* bit0 */
    uint16 IIN_UPDTING : 1; /* bit1 */
    uint16 PIN_UPDTING : 1; /* bit2 */
    uint16 VOUT_V1_UPDTING : 1; /* bit3 */
    uint16 IOUT_V1_UPDTING : 1; /* bit4 */
    uint16 VOUT_VSB_UPDTING : 1; /* bit5 */
    uint16 IOUT_VSB_UPDTING : 1; /* bit6 */
    uint16 POUT_V1_UPDTING : 1; /* bit7 */
    uint16 TEMP_INLET_UPDTING : 1; /* bit8 */
    uint16 TEMP_PFC_UPDTING : 1; /* bit9 */
    uint16 TEMP_SR_UPDTING : 1; /* bitA */
		uint16 HOURS_USED_UPDTING : 1; /* bitB */
    uint16 FAN_SPD_1_UPDTING : 1; /* bitC */
    uint16 FAN_SPD_2_UPDTING : 1; /* bitD */
    uint16 FAN_SPD_3_UPDTING : 1; /* bitE */
    uint16 FAN_SPD_4_UPDTING : 1; /* bitF */
  } Bits;
} PMBUS_U_UPD_STATUS0;

typedef union PMBUS_U_UPD_STATUS1_
{
  uint16 ALL;

  struct
  {
    uint16 EIN_UPDTING : 1;           /* bit0 */
    uint16 EOUT_UPDTING : 1;          /* bit1 */
    uint16 STATUS_78_82_UPDTING : 1;  /* bit2 */
    uint16 POUT_VSB_UPDTING : 1;      /* bit3 */
    uint16 FALT_UPDT_V1_VI_OUT : 1;   /* bit4 */
    uint16 FALT_UPDT_VSB_VI_OUT : 1;  /* bit5 */
		uint16 VOUT_V1_ISHARE_UPDTING :1; /* bit6 */
		uint16 VOUT_V1_SENSE_UPDTING :1;  /* bit7 */
		uint16 VCAP_UPDTING :1;      /* bit8 */
    uint16 MFR_POS_TOTAL:1;      /* bit9 */
    uint16 MFR_POS_LAST:1;       /* bitA */
    uint16 RESERVED : 5;         /* bitB~F */
  } Bits;
} PMBUS_U_UPD_STATUS1;

typedef union PMBUS_U_SYS_STATUS0_
{
  uint16 ALL;

  struct
  {
    uint16 MFR_INFO_UPDATE : 1;      /* bit0 */
    uint16 QUERY_REQUEST : 1;        /* bit1 */
    uint16 PAGE_PLUS_WRITE : 1;      /* bit2 */
    uint16 PAGE_PLUS_READ : 1;       /* bit3 */
    uint16 PAGE_AND_WRITE : 1;       /* bit4 */
    uint16 PAGE_AND_READ : 1;        /* bit5 */
    uint16 CEFCT_READ_EIN_EOUT : 1;  /* bit6 */
    uint16 INVALID_CMD : 1;          /* bit7 */
    uint16 INVALID_DATA : 1;         /* bit8 */
    uint16 UNLOCK_DEBUG : 1;         /* bit9 */
    uint16 AUX_MODE : 1;             /* bitA */
    uint16 OUT_ORING_TEST_ON : 1;    /* bitB */
    uint16 FAN_1_OVERRIDE : 1;       /* bitC */
    uint16 FAN_2_OVERRIDE : 1;       /* bitD */
    uint16 FAN_3_OVERRIDE : 1;       /* bitE */
    uint16 FAN_4_OVERRIDE : 1;       /* bitF */
  } Bits;
} PMBUS_U_SYS_STATUS0;

typedef union PMBUS_U_SYS_STATUS1_
{
  uint16 ALL;

  struct
  {
    uint16 EEPROM_ENABLE : 1; /* bit0 */
    uint16 CORRECT_BOOT_KEY : 1; /* bit1 */
    uint16 BOOT_MODE_JUMP : 1; /* bit2 */
    uint16 BOOT_RESET_FLAG : 1; /* bit3 */
    uint16 I_SHARE_CALI_DONE : 1; /* bit4 */
    uint16 I_SHARE_CALI_P1 : 1; /* bit5 */
    uint16 I_SHARE_CALI_P2 : 1; /* bit6 */
    uint16 I_SHARE_CALI_P3 : 1; /* bit7 */
    uint16 I_SHARE_CALI_P4 : 1; /* bit8 */
    uint16 SMB_MASK_REQUEST : 1; /* bit9 */
    uint16 STB_MODE:1;           /* bit 10*/
		uint16 TIME_CLEAR_ENABLE:1;/* bit a*/  
    uint16 RESERVED : 4; /* bitb ~ f */
  } Bits;

  struct
  {
    uint16 LB : 8;
    uint16 HB : 8;
  } Bytes;
} PMBUS_U_SYS_STATUS1;

typedef union PMBUS_U_BOOT_STATUS_
{
  uint8 ALL;

  struct
  {
#if 0
    uint8 CHECKSUM_SUCCESS : 1; /* bit0 */
    uint8 MEM_BOUN_ERR : 1; /* bit1 */
    uint8 ALIGN_ERR : 1; /* bit2 */
    uint8 KEY_ERR : 1; /* bit3 */
    uint8 START_ERR : 1; /* bit4 */
    uint8 RESERVED : 1; /* bit5 */
    uint8 BOOT_MODE : 1; /* bit6 */
    uint8 PROGRAM_BUSY : 1; /* bit7 */
#else
    uint8 UC_SELECT_BIT_0 : 1; /* bit0 */
    uint8 UC_SELECT_BIT_1 : 1; /* bit1 */
    uint8 BOOT_FLAG : 1; /* bit2 */
    uint8 UNLOCK_FW_UPGRADE : 1; /* bit3 */
    uint8 BUSY : 1; /* bit4 */
    uint8 TRANSMISSIION_ERR : 1; /* bit5 */
    uint8 APP_CRC16_ERR : 1; /* bit6 */
    uint8 FW_ID_ERR : 1; /* bit7 */
#endif

  } Bits;
} PMBUS_U_BOOT_STATUS;

typedef struct PMBUS_S_DATA_
{
  WORD_VAL u16Vin_Mul_128;
  WORD_VAL u16Iin_Mul_128;
  DWORD_VAL u32Pin_Mul_128;
  WORD_VAL u16Vout_V1_Mul_128;
  WORD_VAL u16Vout_VSB_Mul_128;
  WORD_VAL u16Vout_V1IShare_Mul_128;
  WORD_VAL u16Vout_V1Sense_Mul_128;
  WORD_VAL u16Iout_V1_Mul_128;
  WORD_VAL u16Iout_VSB_Mul_128;
  DWORD_VAL u32Pout_V1_Mul_128;
  DWORD_VAL u32Pout_VSB_Mul_128;
	
  WORD_VAL u16Vin_Mul_128_Box;
  WORD_VAL u16Iin_Mul_128_Box;
  DWORD_VAL u32Pin_Mul_128_Box;
	WORD_VAL u16Vout_V1_Mul_128_Box;
  WORD_VAL u16Vout_VSB_Mul_128_Box;
  WORD_VAL u16Iout_V1_Mul_128_Box;
  WORD_VAL u16Iout_VSB_Mul_128_Box;
	
  WORD_VAL u16Vin_Linear;
  WORD_VAL u16Iin_Linear;
  WORD_VAL u16Pin_Linear;
  WORD_VAL u16Vout_V1_Linear;
  WORD_VAL u16Vout_VSB_Linear;
  WORD_VAL u16Iout_V1_Linear;
  WORD_VAL u16Iout_VSB_Linear;
  WORD_VAL u16Pout_V1_Linear;
  WORD_VAL u16Pout_VSB_Linear;
	WORD_VAL u16Vout_V1IShare_Linear;
  WORD_VAL u16Vout_V1Sense_Linear;
	WORD_VAL u16Vcap_Linear;
  WORD_VAL u16Vcap_Mul_128;
	
  WORD_VAL u16Vin_Linear_Box;
  WORD_VAL u16Iin_Linear_Box;
	WORD_VAL u16Pin_Linear_Box;
	WORD_VAL u16Vout_V1_Linear_Box;
  WORD_VAL u16Vout_VSB_Linear_Box;
  WORD_VAL u16Iout_V1_Linear_Box;
  WORD_VAL u16Iout_VSB_Linear_Box;
	
  WORD_VAL u16Temperatue_1_Linear;
  WORD_VAL u16Temperatue_2_Linear;
  WORD_VAL u16Temperatue_3_Linear;
  WORD_VAL u16Temperatue_4_Linear;
  WORD_VAL u16FanSpeed_1_Linear;
  WORD_VAL u16FanSpeed_2_Linear;
  WORD_VAL u16FanSpeed_3_Linear;
  WORD_VAL u16FanSpeed_4_Linear;
  WORD_VAL u16FanCmd_1_Linear;
  WORD_VAL u16FanCmd_2_Linear;
  WORD_VAL u16FanCmd_3_Linear;
  WORD_VAL u16FanCmd_4_Linear;
  DWORD_VAL u32HoursUsed;
  DWORD_VAL u32DataCopy;

  DWORD_VAL u32PinEnergyCtr;
  DWORD_VAL u32PinSampleCount;
  uint8 u8PinRolloverCount;

  DWORD_VAL u32PinEnergyCtr_Old;
  DWORD_VAL u32PinSampleCount_Old;
  uint8 u8PinRolloverCount_Old;

  DWORD_VAL u32PoutEnergyCtr;
  DWORD_VAL u32PoutSampleCount;
  uint8 u8PoutRolloverCount;

  DWORD_VAL u32PoutEnergyCtr_Old;
  DWORD_VAL u32PoutSampleCount_Old;
  uint8 u8PoutRolloverCount_Old;

  uint8 u8CrMode;

  struct
  {
    uint8 u8WakeCurrAA;
    uint8 u8SlpCurrBB;
    uint8 u8WakeCurrCC;
    uint8 u8SlpCurrDD;
    uint8 u8WakeCurrEE;
    uint8 u8SlpCurrFF;
  } VONOFF;
  uint8 u8PsuUnits;
  DWORD_VAL u32PosTotal;
  DWORD_VAL u32PosLast;
} PMBUS_S_DATA;

typedef struct PMBUS_S_STATUS_
{
  PMBUS_U_STATUS_WORD    u16StatusWordP0;
  PMBUS_U_STATUS_VOUT    u8StatusVoutP0;
  PMBUS_U_STATUS_IOUT    u8StatusIoutP0;
  PMBUS_U_STATUS_WORD    u16StatusWordP1;
  PMBUS_U_STATUS_VOUT    u8StatusVoutP1;
  PMBUS_U_STATUS_IOUT    u8StatusIoutP1;

  PMBUS_U_STATUS_INPUT   u8StatusInputP0;
  PMBUS_U_STATUS_TEMP    u8StatusTempP0;
  PMBUS_U_STATUS_CML     u8StatusCmlP0;
  PMBUS_U_STATUS_OTHER   u8StatusOtherP0;
  PMBUS_U_STATUS_MFR     u8StatusMfrP0;
  PMBUS_U_STATUS_FAN_12  u8StatusFan12P0;
  PMBUS_U_STATUS_FAN_34  u8StatusFan34P0;
} PMBUS_S_STATUS;

 typedef struct PMBUS_S_BLACK_BOX_
{
  WORD_VAL u16SaveVin;
  WORD_VAL u16SaveIin;
  WORD_VAL u16SaveV1Vout;
  WORD_VAL u16SaveV1Iout;
  WORD_VAL u16SaveVsbVout;
  WORD_VAL u16SaveVsbIout;
  DWORD_VAL u16SavePriAppRev;
  DWORD_VAL u32SaveTimePresent;
  WORD_VAL  u16SaveFanSpeed1;  
  WORD_VAL  u16SaveFanSpeed2;  	
} PMBUS_S_BLACK_BOX; 

typedef struct PMBUS_S_SMB_MASK_
{
  uint8 u8PmbCrrentReg;
  uint8 u8Pmb_7A;
  uint8 u8Pmb_7B;
  uint8 u8Pmb_7C;
  uint8 u8Pmb_7D;
  uint8 u8Pmb_7E;
  uint8 u8Pmb_7F;
  uint8 u8Pmb_80;
  uint8 u8Pmb_81;
  uint8 u8Pmb_82;
} PMBUS_S_SMB_MASK;
/***********************************************
 * Uart
 **********************************************/
extern uint8  RTE_au8Uart1TxBuf[RTE_UART1_TX_BUF_SIZE];
extern uint8  RTE_au8Uart1RxBuf[RTE_UART1_RX_BUF_SIZE];
extern uint16 RTE_u16Uart1TxDataNbr;
extern uint16 RTE_u16Uart1RxDataNbr;
extern uint8  RTE_u8Uart1TxBufUpdated;
extern uint8  RTE_u8Uart1RxNewFrame;
extern uint8  RTE_u8Uart1FrameTmoutFlg;
extern uint8  RTE_u8Uart1ByteTmoutFlg;
extern uint8  RTE_u8Uart1TxTmoutFlg;
extern uint8  RTE_u8Uart1BroadcastFlg;
extern uint8  RTE_u8Uart1RxCrc;
extern RTE_U_UARTSTATUS RTE_uUart1Status;
extern GLOBAL_U_U16BIT  RTE_uUart1Pri1VinAD;
extern GLOBAL_U_U16BIT  RTE_uUart1Pri2VinAD;
extern RTE_U_PMBUS_OPERATION RTE_uPmbusOperation;
extern boolean RTE_bPEC_Enable;

#if (2U == RTE_UART_CHANNEL_USED)
  extern uint8  RTE_au8Uart2TxBuf[RTE_UART2_TX_BUF_SIZE];
  extern uint8  RTE_au8Uart2RxBuf[RTE_UART2_RX_BUF_SIZE];
  extern uint16 RTE_u16Uart2TxDataNbr;
  extern uint16 RTE_u16Uart2RxDataNbr;
  extern uint8  RTE_u8Uart2TxBufUpdated;
  extern uint8  RTE_u8Uart2RxNewFrame;
  extern uint8  RTE_u8Uart2FrameTmoutFlg;
  extern uint8  RTE_u8Uart2ByteTmoutFlg;
  extern uint8  RTE_u8Uart2TxTmoutFlg;
  extern uint8  RTE_u8Uart2BroadcastFlg;
  extern uint8  RTE_u8Uart2RxCrc;
  extern RTE_U_UARTSTATUS RTE_uUart2Status;
#endif

extern uint16  RTE_u16ComDebug[4];

typedef struct RTE_S_ADJ_DATA_
{
  uint16   u16V1VoltGainAdj;
  uint16   u16VsbVoltGainAdj;
  WORD_VAL s16V1CurrShareGainP1;
  WORD_VAL s16V1CurrShareGainP2;
  WORD_VAL s16V1CurrShareGainP3;
  WORD_VAL s16V1CurrShareGainP4;
} RTE_S_ADJ_Data;

extern RTE_S_INTCOM1_DATA RTE_Pri;
extern RTE_S_INTCOM2_DATA RTE_Sec;
extern GLOBAL_U_U16BIT RTE_uComToSecStatus;
extern GLOBAL_U_U16BIT RTE_uComToPriStatus;
extern GLOBAL_U_U16BIT RTE_uComStatus00;
extern GLOBAL_U_U16BIT RTE_uComStatus01;
extern GLOBAL_U_U16BIT RTE_uComStatus02;

extern GLOBAL_U_U16BIT RTE_uTempOtwStatus;
extern GLOBAL_U_U16BIT RTE_uTempOtpStatus;
extern GLOBAL_U_U16BIT RTE_uSensorFaultStatus;
extern GLOBAL_U_U16BIT RTE_uTempStatus;
extern GLOBAL_U_U16BIT RTE_uDioInStatus;
extern GLOBAL_U_U16BIT RTE_uDioOutStatus;
extern GLOBAL_U_U16BIT RTE_uPsuCtrlStatus;
extern GLOBAL_U_U16BIT RTE_uIntcom1Status;
extern GLOBAL_U_U16BIT RTE_uIntcom2Status;

extern volatile GLOBAL_U_U16BIT RTE_sV1FaultFlag00, RTE_sVsbFaultFlag00;
extern volatile GLOBAL_U_U16BIT RTE_sVoutStateFlag, RTE_sSysStateFlag00;

extern WORD_VAL RTE_u16TrimV1Gain;
extern WORD_VAL RTE_u16TrimV1GainOvp;
extern WORD_VAL RTE_u16TrimV1GainAct;
extern WORD_VAL RTE_u16TrimVsbGain;
extern WORD_VAL RTE_u16TrimVsbGainOvp;
extern WORD_VAL RTE_u16TrimVsbGainAct;

extern WORD_VAL RTE_u16V1CurrentGain;
extern WORD_VAL RTE_u16IShareGain;
extern WORD_VAL RTE_u16IShareOfs;


extern GLOBAL_U_U16BIT RTE_u16MonCtrlInputType;

extern DWORD_VAL RTE_u32PmbusFwRevPri1;
extern DWORD_VAL RTE_u32PmbusBootFwRevPri1;
extern DWORD_VAL RTE_u32PmbusFwRevSec1;
extern DWORD_VAL RTE_u32PmbusBootFwRevSec1;
extern DWORD_VAL RTE_u32PmbusFwRevPri1Old;
extern DWORD_VAL RTE_u32PmbusBootFwRevPri1Old;
extern DWORD_VAL RTE_u32PmbusFwRevSec1Old;
extern DWORD_VAL RTE_u32PmbusBootFwRevSec1Old;
extern DWORD_VAL RTE_u32PmbusFwRevCom;
extern DWORD_VAL RTE_u32PmbusBootFwRevCom;

extern  WORD_VAL  RTE_u16ComToPriDebug;
extern  WORD_VAL  RTE_u16ComToSecDebug;

extern WORD_VAL RTE_u16ComToSecDebug1;
extern WORD_VAL RTE_u16ComToSecDebug2;

extern uint16 RTE_u161mAIinAvgAvgPri;
extern uint16 RTE_u16100mAPinAvgAvgPri;
extern uint16 RTE_u1610mVIntV1AvgAvgSec;
extern uint16 RTE_u1610mVExtV1AvgAvgSec;
extern uint16 RTE_u1610mAIoutAvgAvgSec;
extern CALI_S_DATA      RTE_CALI_sData;
extern RTE_S_ADJ_Data   RTE_sAdjustData;

extern uint8 RTE_ModelNumber[11];

extern uint16 RTE_u16CaliIout;
extern uint8  RTE_au8MfrData[6][17];

extern volatile uint8 RTE_au8I2cTxBuf[I2C_TX_BUF_SIZE+1];
extern volatile uint8 RTE_au8I2cRxBuf[I2C_RX_BUF_SIZE+1];
extern volatile uint8 RTE_u8I2cPEC;
extern volatile uint8 RTE_u8I2cExpTxCnt;
extern volatile uint8 RTE_u8I2cExpRxCnt;
extern volatile uint8 RTE_u8I2cRxCnt;
extern volatile uint8 RTE_u8I2cTxLen;
extern volatile uint8 RTE_u8I2cPECErrCmd;
extern uint16 RTE_u16VoutIntVsbFast;
extern uint16 RTE_u16VoutExtVsbFast;
extern uint16 RTE_u16IoutVsbFast;

extern uint8 RTE_u8InputLedState;
extern volatile GLOBAL_U_U16BIT  RTE_u16I2cStatus0;

extern CALI_U_STATUS CALI_uStatus;
extern CALI_S_PARAMETER CALI_sPara;

extern FANCTRL_U_STATUS_12 FANCTRL_uFanStatus12;
extern FANCTRL_U_STATUS_12 FANCTRL_uFanStatus34;

extern WORD_VAL RTE_uCaliV1Amp;
extern WORD_VAL RTE_uCaliV1Ofs;
extern WORD_VAL RTE_uCaliI1Amp;
extern WORD_VAL RTE_uCaliI1Ofs;

/***********************************************
 * I2C
 **********************************************/

extern volatile GLOBAL_U_U16BIT  RTE_u16I2cStatus0;
/***********************************************
 * PMBus
 **********************************************/
extern uint8 RTE_u8PmbusCommand;
extern PMBUS_U_OPERATION PMBUS_uOperation;
extern PMBUS_U_SYS_STATUS0 PMBUS_uSysStatu0;
extern PMBUS_U_SYS_STATUS1 PMBUS_uSysStatu1;
extern PMBUS_U_UPD_STATUS0 PMBUS_uDataUpdStatus;
extern PMBUS_U_UPD_STATUS1 PMBUS_uDataUpdStatus1;
extern PMBUS_S_DATA   PMBUS_tData;
extern PMBUS_S_STATUS PMBUS_tStatus;
extern PMBUS_S_STATUS PMBUS_tStatusOld;
extern uint8 RTE_u8AcLineStatus;

/***********************************************
 * Temperature control
 **********************************************/
extern sint16 RTE_s16TempTest[RTE_TEMP_TOTAL_NUM];
extern uint8  RTE_u8TempTestIndex;
extern boolean  RTE_bIsV1OcpTest;
extern boolean  RTE_bIsVsbOcpTest;
extern GLOBAL_U_U16BIT RTE_uFunctionCtrl;
extern sint16 RTE_s16OtWarning;
/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/******************************************************************************
 * \brief     RTE_vRteDataInit
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *****************************************************************************/
void RTE_vInit(void);
void RTE_vDeInit(void);

#ifdef __cplusplus
  }
#endif
#endif  /* _RTE_H */

  
/*
 * End of file
 */
