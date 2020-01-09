/*******************************************************************************
 * \file    pmbus.c
 * \brief   pmbus communication with system
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
 *******************************************************************************/

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include <StdPeriphDriver.h>

/* Module header */
#define PMBUS_EXPORT_H
	#include "pmbus_api.h"
	#include "pmbus_cfg.h"
	#include "pmbus_conf.h"
	#include "pmbus_scb.h"
	#include "pmbus_scfg.h"
	#include "pmbus_rte.h"


/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

typedef enum MG_E_SENSOR_UPDATE_
{
  MG_E_UPD_FAN_NTC = 0,
  MG_E_UPD_OUTPUT,
  MG_E_UPD_INPUT,
} MG_E_SENSOR_UPDATE;

typedef union 
{
  uint32 Val;
  struct 
  {
    uint16 Reserved;
    uint16 CRC_Value;
  } Words;
  struct
  {
    uint8 LED_Status;
    uint8 BootFlag;
    uint8 CRC_LB;
    uint8 CRC_HB;
  } Bytes;
}MG_U_CRC_BF;

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/* Output Voltage */
#define MG_VOUT_V1                     ((uint8)0x10U)
#define MG_VOUT_VSB                    ((uint8)0x20U)

/* Page Number */
#define MG_PAGE_00                     ((uint8)0U)
#define MG_PAGE_01                     ((uint8)1U)
#define MG_PAGE_02                     ((uint8)2U)
#define MG_PAGE_03                     ((uint8)3U)
#define MG_PAGE_04                     ((uint8)4U)
#define MG_PAGE_FF                     ((uint8)0xFFU)
#define MG_PAGE_MAX                    MG_PAGE_04

/* Operation Value */
#define MG_OPERATION_ON_80             (0x80U)
#define MG_OPERATION_OFF_00            (0x00U)

/* Constant Data Definition */
#define MG_UNLOCK_DEBUG_KEY_UL         (0x4C55)
#define MG_LOCK_DEBUG_KEY_AAAA         (0xAAAA)
#define MG_TIME_CLEAR                  (0x0CEA)       /* Clear Time when shipment Sandra 20180212 */ 
#define MG_AC_OFFSET_CLEAR             (0x4C55)

/* Delay Setting */
#define MG_STA_PWR_UP_UPD_DLY          ((uint8)30U)     /* 30 * 0.1s , When power up, to delay 3 seconds    */
#define MG_STA_CLR_FLT_UPD_DLY         ((uint8)10U)     /* 10 * 0.1s , When clear fault, to delay 1 seconds */

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
/*
 * supported Write commands
 * i2c received byte cnt, including cmd code, not including PEC
 */
const uint8 PMB_mg_au8I2cRxNumber[256] = {
  /*
   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
   */
  2, 2, 0, 1, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $0x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, /* $1x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $2x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 3, 3, /* $3x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $4x */
  0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $5x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $6x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $7x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $8x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 13, 7, 16, 10, 15, 0, /* $9x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $Ax */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $Bx */
  0, 0, 0, 4, 4, 4, 3, 2, 0, 11, 0, 0, 0, 0, 3, 0, /* $Cx */
  0, 5, 2, 0, 17, 0, 0, 0, 0, 0, 0, 0, 3, 6, 42, 2, /* $Dx */
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, /* $Ex */
  14, 3, 0, 3, 4, 2, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, /* $Fx */
};

/*
 * supported Read Commands
 * i2c read : only data, not including PEC
 */
const uint8 PMB_mg_au8I2cTxNumber[] = 
{
  /*
   * Read only
  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
   */
  1, 1, 0, 1, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $0x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 0, /* $1x */
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $2x */
  5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, /* $3x */
  2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, /* $4x */
  0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, /* $5x */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $6x */
  0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 0, /* $7x */
  0, 0, 0, 0, 0, 0, 7, 7, 2, 2, 0, 2, 2, 2, 2, 2, /* $8x */
  0, 0, 0, 0, 0, 0, 2, 2, 1, 6, 12, 6, 9, 9, 12, 1, /* $9x */
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 14, 0, 0, 0, 0, /* $Ax */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $Bx */
  2, 2, 2, 2, 2, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, /* $Cx */
  1, 2, 1, 0, 0, 7, 1, 0, 1, 2, 1, 1, 2, 2, 2, 0, /* $Dx */       
  2, 2, 2, 0, 0, 4, 4, 0, 0, 0, 1, 2, 2, 2, 2, 0, /* $Ex */
  0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* $Fx */
};


const uint8 PMB_mg_au8ByteFormatP0[] = {
  /* 0    1     2     3     4     5     6     7     8     9     A     B     C     D     E     F     */
  0xF0, 0xFC, 0x00, 0xDC, 0x00, 0xDC, 0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $0x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0xBC, 0xFC, 0x00, 0x00, 0x00, 0x00, /* $1x */
  0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $2x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0xE0, 0xE0, 0xBC, 0xE0, 0xE0, /* $3x */
  0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xA0, /* $4x */
  0x00, 0xE0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $5x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $6x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, /* $7x */
  0xBC, 0xBC, 0xBC, 0x00, 0x00, 0x00, 0xAC, 0xAC, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, /* $8x */
  0xA0, 0xA0, 0xA0, 0xA0, 0x00, 0x00, 0xA0, 0xA0, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0x00, /* $9x */
  0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, /* $Ax */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $Bx */
  0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $Cx */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0x00, 0x00, 0x00, 0xBC, 0xFC, 0xFC, 0xFC, /* $Dx */     
  0xDC, 0xBC, 0xBC, 0xBC, 0x00, 0xBC, 0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $Ex */
  0xD8, 0xF8, 0xD8, 0xD8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00 /* $Fx */
};

const uint8 PMB_mg_au8ByteFormatP1[] = {
  /* 0    1     2     3     4     5     6     7     8     9     A     B     C     D     E     F     */
  0xF0, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $0x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, /* $1x */
  0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $2x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $3x */
  0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, /* $4x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $5x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $6x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0xBC, 0xBC, 0xBC, 0x00, 0x00, 0x00, 0x00, /* $7x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xA0, 0x00, 0x00, 0x00, /* $8x */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $9x */
  0x00, 0x00, 0x00, 0x00, 0xA0, 0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $Ax */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $Bx */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $Cx */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $Dx */     
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* $Ex */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 /* $Fx */
};

const uint8 PMB_mg_au8_BOOT_FW_ID[11] = {
  '7', '0', '1', '0', '2', '0', '6', '1', 'D', 'C', 'E', 
  /* use below just for test */
  //    '5', '0', '0', '0', '2', '0', '6', '5', 'D', 'C', 'E'
};

const uint8 PMB_mg_au8_PROJECT_ID[] = {14};

static PMBUS_U_BOOT_STATUS mg_uBootStatus;
static WORD_VAL mg_u16UnlockDebugKey;
static uint8 mg_u8Page;
static uint8 mg_u8UpdSensor = MG_E_UPD_FAN_NTC;
static uint16 mg_u16StatusUpdDly = MG_STA_PWR_UP_UPD_DLY;
static PMBUS_S_SMB_MASK mg_sP0SmbMask;
static PMBUS_S_SMB_MASK mg_sP1SmbMask;

static WORD_VAL mg_au8DebugRegBuf[RTE_I2C_DEB_BUF_SIZE];
static WORD_VAL mg_u16DebugRegIndex; 

uint8 mg_au8BlackBoxData[RTE_BLACK_BOX_DEEPNESS][RTE_BLACK_BOX_DATA_CNT_PER_FAULT];
uint8 mg_au8BBVinUVPData[RTE_BLACK_BOX_DEEPNESS_VIN_UVP][RTE_BLACK_BOX_DATA_CNT_PER_FAULT];
PMBUS_U_BLCBOX_PAGE_W_DIS mg_uBlcBoxPageWrDis;

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
static void mg_vSendQuerydata(void);
static void mg_vSendSmbMaskdata(void);
static uint16 mg_u16TxLinearDatFormatDiv128(uint32 u32DataIn);
static void mg_vClearPage00Fault(void);
static void mg_vClearPage01Fault(void);
static void mg_vClearPageAllFault(void);

//static uint32 mg_u32LinearDatFormatToNormal(uint16 u16DataIn);
static sint32 mg_s32LinearDatFormatToNormal(uint16 u16DataIn);
#if 0
static uint32 mg_u32LinearDatFormatToNormalMul128(uint16 u16DataIn);
#endif
/*******************************************************************************
 * Global data (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/
static uint8 mg_u8BootMcuId;

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize PMBus data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vInit(void)
{
	uint8 u8Cnt;
  /* System Control Status */
#if 1
  PMBUS_uOperation.ALL = MG_OPERATION_ON_80;
#else
  PMBUS_uOperation.ALL = MG_OPERATION_OFF_00;
#endif
  /* System Used Status */
  PMBUS_tStatus.u16StatusWordP0.ALL = 0;
  PMBUS_tStatus.u16StatusWordP1.ALL = 0;
  PMBUS_tStatus.u8StatusVoutP0.ALL = 0;
  PMBUS_tStatus.u8StatusVoutP1.ALL = 0;
  PMBUS_tStatus.u8StatusIoutP0.ALL = 0;
  PMBUS_tStatus.u8StatusIoutP1.ALL = 0;
  PMBUS_tStatus.u8StatusInputP0.ALL = 0;
  PMBUS_tStatus.u8StatusTempP0.ALL = 0;
  PMBUS_tStatus.u8StatusCmlP0.ALL = 0;

  PMBUS_tStatus.u8StatusOtherP0.ALL = 0;
  PMBUS_tStatus.u8StatusMfrP0.ALL = 0;
  PMBUS_tStatus.u8StatusFan12P0.ALL = 0;
  PMBUS_tStatus.u8StatusFan34P0.ALL = 0;

  PMBUS_tStatusOld.u16StatusWordP0.ALL = 0;
  PMBUS_tStatusOld.u16StatusWordP1.ALL = 0;
  PMBUS_tStatusOld.u8StatusVoutP0.ALL = 0;
  PMBUS_tStatusOld.u8StatusVoutP1.ALL = 0;
  PMBUS_tStatusOld.u8StatusIoutP0.ALL = 0;
  PMBUS_tStatusOld.u8StatusIoutP1.ALL = 0;
  PMBUS_tStatusOld.u8StatusInputP0.ALL = 0;
  PMBUS_tStatusOld.u8StatusTempP0.ALL = 0;
  PMBUS_tStatusOld.u8StatusCmlP0.ALL = 0;
  PMBUS_tStatusOld.u8StatusOtherP0.ALL = 0;
  PMBUS_tStatusOld.u8StatusMfrP0.ALL = 0;
  PMBUS_tStatusOld.u8StatusFan12P0.ALL = 0;
  PMBUS_tStatusOld.u8StatusFan34P0.ALL = 0;

  /* System Used Data */
  PMBUS_tData.u32DataCopy.u32Val = 0;
  PMBUS_tData.u16Vin_Linear.u16Val = 0;
  PMBUS_tData.u16Iin_Linear.u16Val = 0;
  PMBUS_tData.u16Pin_Linear.u16Val = 0;
  PMBUS_tData.u16Vout_V1_Linear.u16Val = 0;
  PMBUS_tData.u16Iout_V1_Linear.u16Val = 0;
  PMBUS_tData.u16Pout_V1_Linear.u16Val = 0;
  PMBUS_tData.u16Pout_VSB_Linear.u16Val = 0;
  PMBUS_tData.u16Temperatue_1_Linear.u16Val = 0;
  PMBUS_tData.u16Temperatue_2_Linear.u16Val = 0;
  PMBUS_tData.u16Temperatue_3_Linear.u16Val = 0;
  PMBUS_tData.u16FanSpeed_1_Linear.u16Val = 0;
  PMBUS_tData.u16FanSpeed_2_Linear.u16Val = 0;
  PMBUS_tData.u16FanSpeed_3_Linear.u16Val = 0;
  PMBUS_tData.u16FanSpeed_4_Linear.u16Val = 0;
  PMBUS_tData.u16FanCmd_1_Linear.u16Val = 0;
  PMBUS_tData.u16FanCmd_2_Linear.u16Val = 0;
  PMBUS_tData.u16FanCmd_3_Linear.u16Val = 0;
  PMBUS_tData.u16FanCmd_4_Linear.u16Val = 0;
  /* CR mode */
  PMBUS_tData.u8CrMode   = U8_CR_NORMAL_MODE;
  PMBUS_tData.u8PsuUnits = U8_CR_PSUUNITS_02;

  /* Internal Used Data */
  mg_u16UnlockDebugKey.u16Val = 0;
  PMBUS_uSysStatu0.ALL = 0;
  PMBUS_uSysStatu1.ALL = 0;
  PMBUS_uDataUpdStatus.ALL = 0;
  PMBUS_uDataUpdStatus1.ALL = 0;

  mg_sP0SmbMask.u8Pmb_7A = 0x6F;
  mg_sP0SmbMask.u8Pmb_7B = 0x5F;
  mg_sP0SmbMask.u8Pmb_7C = 0x67;
  mg_sP0SmbMask.u8Pmb_7D = 0x3F;
  mg_sP0SmbMask.u8Pmb_7E = 0x1D;
  mg_sP0SmbMask.u8Pmb_81 = 0x3F;

  mg_sP1SmbMask.u8Pmb_7A = 0x6F;
  mg_sP1SmbMask.u8Pmb_7B = 0x5F; 
  mg_sP1SmbMask.u8Pmb_7C = 0xDF; 
  mg_sP1SmbMask.u8Pmb_7D = 0xFF;
  mg_sP1SmbMask.u8Pmb_7E = 0xFF;
  mg_sP1SmbMask.u8Pmb_81 = 0xFF;

  /* Boot loader used data */
  mg_uBootStatus.ALL = 0;
  mg_u8BootMcuId = 0;
	
  for(u8Cnt = 0U; u8Cnt < RTE_I2C_DEB_BUF_SIZE; u8Cnt++)
  {
    mg_au8DebugRegBuf[u8Cnt].u16Val = 0;
  }
}/* PMBUS_vInit */

/*******************************************************************************
 * \brief         DeInitialize PMBus data
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vDeInit(void)
{
}

/*******************************************************************************
 * \brief          Clear fault or warning status
 *                  ucPage: page0, 1, FF
 *                  ucMode: 1: clear All, and can restart ( OPERATION )
 *                          2: clear All except STA_MFR, and can restart ( PS_ON, PS_KILL )
 *                          3: clear All, and can't restart ( CLEAR_FAULT, CLEAR_BITS )
 *                          4: clear All except STA_MFR, and can't restart
 *
 * \param[in]     -ucPage, ucMode
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vClearAllPageFault(void)
{
  mg_vClearPageAllFault();
}

/*******************************************************************************
 * \brief          Check boot mode
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
uint8 PMBUS_u8GetBootMcuId(void)
{
	return mg_u8BootMcuId;
}

/*******************************************************************************
 * \brief          Check boot mode
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCheckBootMode(void)
{
  static uint16 u16BootWait = 0;
  static uint8  u8BootFlag = 0;
	MG_U_CRC_BF Dword_CrcBootFlag;

  if (PMBUS_uSysStatu1.Bits.BOOT_MODE_JUMP)
  {
    /* Inform PFC go to BL after Sec go to BL mode */
    if ((mg_u8BootMcuId == PRI_uC_A) || (mg_u8BootMcuId == PRI_uC_ALL))
    {
      PMBUS_SCFG_vSetBootMode(0x00);
      PMBUS_uSysStatu1.Bits.BOOT_MODE_JUMP  = FALSE;
      PMBUS_uSysStatu1.Bits.BOOT_RESET_FLAG = TRUE;
    }
		else if ((mg_u8BootMcuId == SEC_uC_A) || (mg_u8BootMcuId == SEC_uC_ALL))
		{
      PMBUS_SCFG_vSetBootMode(0x01);
      PMBUS_uSysStatu1.Bits.BOOT_MODE_JUMP  = FALSE;
      PMBUS_uSysStatu1.Bits.BOOT_RESET_FLAG = TRUE;
		}
    else
    {
      PMBUS_uSysStatu1.Bits.BOOT_MODE_JUMP  = FALSE;
      PMBUS_uSysStatu1.Bits.BOOT_RESET_FLAG = TRUE;
    }
    u16BootWait = 20; /* wait 200ms to turn off output and UART */
		
		switch (mg_u8BootMcuId)
		{ 
			case PRI_uC_A: 
			{
				u8BootFlag = BOOT_FLAG_SET_PRI_A;      
				break;
			}
			case SEC_uC_A:
			{
				u8BootFlag = BOOT_FLAG_SET_SEC_A;                            
				break;
			}
			case COM_uC_S: 
			{
				u8BootFlag = BOOT_FLAG_SET_COM_S; 
				break;
			}
			default:
			{
				PMBUS_uSysStatu1.Bits.BOOT_RESET_FLAG = FALSE;
				break;
			}
		}
  }
  if (PMBUS_uSysStatu1.Bits.BOOT_RESET_FLAG)
  {
    if (u16BootWait)
    {
      u16BootWait--;
    }
    else
    {
      CLI();  /* disable interrupt */
      /* read INPUT_LED status (1 byte), bootflag (1 byte), CRC16 (2 bytes) */
      Dword_CrcBootFlag.Val = PMBUS_SCFG_u32ReadWordFlash(BOOT_CRC_BF_ADDR_START);
      
      /* update INPUT_LED status, bootflag */
      Dword_CrcBootFlag.Bytes.LED_Status = RTE_u8InputLedState; /* 0:OFF, 1:ON, 2:BLINK */
      Dword_CrcBootFlag.Bytes.BootFlag = u8BootFlag;
      
      /* erase this page */
      PMBUS_SCFG_vErasePageFlash(BOOT_CRC_BF_ADDR_START);
      
      /* write this page */
      PMBUS_SCFG_vWriteWordFlash(BOOT_CRC_BF_ADDR_START, Dword_CrcBootFlag.Val);
      PMBUS_SCFG_vWriteHalfWordFlash(BOOT_PEC_STATUS_ADDR_START, RTE_bPEC_Enable);
      
      /* reset */
      NVIC_SystemReset();
    }
  }
}

/*******************************************************************************
 * \brief         Copy sensor data to PMBus sensor registers
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCopySensorData(void)
{
  uint16 u16Dummy = 0;
  uint32 u32Dummy = 0;

  switch (mg_u8UpdSensor)
  {
    case MG_E_UPD_FAN_NTC:
    {
      /* Update Fan Speed 1 */
      RTE_PMB_Write_u32DataCopy(RTE_PMB_Read_u16FanSpeed1_Linear());
      u16Dummy = mg_u16TxLinearDatFormatDiv128(((uint32) PMBUS_SCFG_u16ReadFanSpeed(0)) << 7);
      RTE_PMB_Write_bit_Fan_Spd_1_Upd(TRUE);
      RTE_PMB_Write_u16FanSpeed1_Linear(u16Dummy);
      RTE_PMB_Write_bit_Fan_Spd_1_Upd(FALSE);
			
      /* Update Fan Speed 2 */			
      RTE_PMB_Write_u32DataCopy(RTE_PMB_Read_u16FanSpeed2_Linear());
      u16Dummy = mg_u16TxLinearDatFormatDiv128(((uint32) PMBUS_SCFG_u16ReadFanSpeed(1)) << 7);
      RTE_PMB_Write_bit_Fan_Spd_2_Upd(TRUE);
      RTE_PMB_Write_u16FanSpeed2_Linear(u16Dummy);
      RTE_PMB_Write_bit_Fan_Spd_2_Upd(FALSE);
			
      /* Update Temperatue_1: NTC_Inlet  */
      RTE_PMB_Write_u32DataCopy(RTE_PMB_Read_u16Temp1_Linear());
      u16Dummy = PMBUS_SCFG_s16ReadInletTemp() & 0x07FFu;
      RTE_PMB_Write_bit_Inlet_Upd(TRUE);
      RTE_PMB_Write_u16Temp1_Linear(u16Dummy);
      RTE_PMB_Write_bit_Inlet_Upd(FALSE);
			
      /* Update Temperatue_2: NTC_PFC */
      RTE_PMB_Write_u32DataCopy(RTE_PMB_Read_u16Temp2_Linear());
      u16Dummy = PMBUS_SCFG_s16ReadPriPfc() & 0x07FFu;
      RTE_PMB_Write_bit_Pfc_Upd(TRUE);
      RTE_PMB_Write_u16Temp2_Linear(u16Dummy);
      RTE_PMB_Write_bit_Pfc_Upd(FALSE);

      /* Update Temperatue_3: NTC_SR  */
      RTE_PMB_Write_u32DataCopy(RTE_PMB_Read_u16Temp3_Linear());
      u16Dummy = (PMBUS_SCFG_s16ReadSecSr()) & 0x07FFu;  
      RTE_PMB_Write_bit_SR_Upd(TRUE);
      RTE_PMB_Write_u16Temp3_Linear(u16Dummy);
      RTE_PMB_Write_bit_SR_Upd(FALSE);
      
      RTE_PMB_Write_u32DataCopy(RTE_PMB_Read_u32Hours_Used());
      RTE_PMB_Write_bit_Hours_Upd(TRUE);
      PMBUS_Rte_Read_R_u32PMBusCmd(&u32Dummy);
      RTE_PMB_Write_u32Hours_Used(u32Dummy);
      RTE_PMB_Write_bit_Hours_Upd(FALSE);

      mg_u8UpdSensor = MG_E_UPD_OUTPUT;

      break;
    }

    case MG_E_UPD_OUTPUT:
    {
      PMBUS_tData.u32DataCopy.Words.LW = RTE_PMB_Read_u16Vout_V1_Linear();
      u16Dummy = PMBUS_tData.u16Vout_V1_Mul_128.u16Val;
      RTE_PMB_Write_bit_Vout_V1_Upd(TRUE);
      RTE_PMB_Write_u16Vout_V1_Linear(u16Dummy);
      RTE_PMB_Write_bit_Vout_V1_Upd(FALSE);
			
      PMBUS_tData.u32DataCopy.Words.LW = RTE_PMB_Read_u16Iout_V1_Linear();
      u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Iout_V1_Mul_128.u16Val);
      RTE_PMB_Write_bit_Iout_V1_Upd(TRUE);
      RTE_PMB_Write_u16Iout_V1_Linear(u16Dummy);
      RTE_PMB_Write_bit_Iout_V1_Upd(FALSE);

      PMBUS_tData.u32DataCopy.Words.LW = RTE_PMB_Read_u16Vout_VSB_Linear();
      u16Dummy = PMBUS_tData.u16Vout_VSB_Mul_128.u16Val;
      RTE_PMB_Write_bit_Vout_VSB_Upd(TRUE);
      RTE_PMB_Write_u16Vout_VSB_Linear(u16Dummy);
      RTE_PMB_Write_bit_Vout_VSB_Upd(FALSE);

      PMBUS_tData.u32DataCopy.Words.LW = RTE_PMB_Read_u16Iout_VSB_Linear();
      u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Iout_VSB_Mul_128.u16Val);
      RTE_PMB_Write_bit_Iout_VSB_Upd(TRUE);
      RTE_PMB_Write_u16Iout_VSB_Linear(u16Dummy);
      RTE_PMB_Write_bit_Iout_VSB_Upd(FALSE);

      PMBUS_tData.u32DataCopy.Words.LW = RTE_PMB_Read_u16Pout_V1_Linear();
      u16Dummy = mg_u16TxLinearDatFormatDiv128((PMBUS_tData.u32Pout_V1_Mul_128.u32Val + PMBUS_tData.u32Pout_VSB_Mul_128.u32Val));
      RTE_PMB_Write_bit_Pout_V1_Upd(TRUE);
      RTE_PMB_Write_u16Pout_V1_Linear(u16Dummy);
      RTE_PMB_Write_bit_Pout_V1_Upd(FALSE);

      PMBUS_tData.u32DataCopy.Words.LW = RTE_PMB_Read_u16Pout_VSB_Linear();
      u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u32Pout_VSB_Mul_128.u32Val);
      RTE_PMB_Write_bit_Pout_VSB_Upd(TRUE);
      RTE_PMB_Write_u16Pout_VSB_Linear(u16Dummy);
      RTE_PMB_Write_bit_Pout_VSB_Upd(FALSE);
			
      PMBUS_tData.u32DataCopy.Words.LW = RTE_PMB_Read_u16Vout_V1Sense_Linear();
      u16Dummy = PMBUS_tData.u16Vout_V1Sense_Mul_128.u16Val;
      RTE_PMB_Write_bit_Vout_Sense_Upd(TRUE);
      RTE_PMB_Write_u16Vout_V1Sense_Linear(u16Dummy);
      RTE_PMB_Write_bit_Vout_Sense_Upd(FALSE);
			
      PMBUS_tData.u32DataCopy.Words.LW = RTE_PMB_Read_u16Vout_V1IShare_Mul_128();
      u16Dummy = PMBUS_tData.u16Vout_V1IShare_Mul_128.u16Val;
      RTE_PMB_Write_bit_Vout_IShare_Upd(TRUE);
      RTE_PMB_Write_u16Vout_V1IShare_Linear(u16Dummy);
      RTE_PMB_Write_bit_Vout_IShare_Upd(FALSE);

      PMBUS_tData.u32PoutEnergyCtr_Old.u32Val = PMBUS_tData.u32PoutEnergyCtr.u32Val;
      PMBUS_tData.u32PoutSampleCount_Old.u32Val = PMBUS_tData.u32PoutSampleCount.u32Val;
      PMBUS_tData.u8PoutRolloverCount_Old = PMBUS_tData.u8PoutRolloverCount;

      RTE_PMB_Write_bit_Eout_Upd(TRUE);

      PMBUS_tData.u32PoutSampleCount.u32Val++;
      if (PMBUS_tData.u32PoutSampleCount.u32Val > 0x00FFFFFFu)
      {
        PMBUS_tData.u32PoutSampleCount.u32Val = 1;
        PMBUS_tData.u8PoutRolloverCount = 0;
      }
      PMBUS_tData.u32PoutEnergyCtr.u32Val += ((PMBUS_tData.u32Pout_V1_Mul_128.u32Val + PMBUS_tData.u32Pout_VSB_Mul_128.u32Val) >> 7);

      if (PMBUS_tData.u32PoutEnergyCtr.u32Val > MAX_DIRECT_DATA_FORMAT_VAL)
      {
        PMBUS_tData.u32PoutEnergyCtr.u32Val -= MAX_DIRECT_DATA_FORMAT_VAL;
        if (PMBUS_tData.u8PoutRolloverCount < 0xFFu)
        {
          PMBUS_tData.u8PoutRolloverCount++; /* rollover */
        }
        else
        {
          PMBUS_tData.u8PoutRolloverCount = 0; /* rollover */
          PMBUS_tData.u32PoutSampleCount.u32Val = 1;
        }
      }
      RTE_PMB_Write_bit_Eout_Upd(FALSE);

      mg_u8UpdSensor = MG_E_UPD_INPUT;

      break;
    }

    case MG_E_UPD_INPUT:
    {
      /*
       * Update Vin :
       * Covert (Vin * 128) value to Y
       */
      PMBUS_tData.u32DataCopy.Words.LW = PMBUS_tData.u16Vin_Linear.u16Val;
      u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Vin_Mul_128.u16Val);
      RTE_PMB_Write_bit_Vin_Upd(TRUE);
      PMBUS_tData.u16Vin_Linear.u16Val = u16Dummy;
      RTE_PMB_Write_bit_Vin_Upd(FALSE);

      /*
       * Update Iin :
       * Covert (Iin * 128) value to Y
       */
      PMBUS_tData.u32DataCopy.Words.LW = PMBUS_tData.u16Iin_Linear.u16Val;
      u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Iin_Mul_128.u16Val);
      RTE_PMB_Write_bit_Iin_Upd(TRUE);
      PMBUS_tData.u16Iin_Linear.u16Val = u16Dummy;
      RTE_PMB_Write_bit_Iin_Upd(FALSE);
      /*
       * Update VBulk :
       * Covert (VBulk * 128) value to Y
       */
      PMBUS_tData.u32DataCopy.Words.LW = PMBUS_tData.u16Vcap_Linear.u16Val;
      u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Vcap_Mul_128.u16Val);
      RTE_PMB_Write_bit_VCAP_Upd(TRUE);
      PMBUS_tData.u16Vcap_Linear.u16Val = u16Dummy;
      RTE_PMB_Write_bit_VCAP_Upd(FALSE);

      /*
       * Update Pin :
       * Covert (Pin * 128) value to Y
       */
      PMBUS_tData.u32DataCopy.Words.LW = PMBUS_tData.u16Pin_Linear.u16Val;
      u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u32Pin_Mul_128.u32Val);
      RTE_PMB_Write_bit_Pin_Upd(TRUE);
      PMBUS_tData.u16Pin_Linear.u16Val = u16Dummy;
      RTE_PMB_Write_bit_Pin_Upd(FALSE);

      /*
       * Update Ein :
       * m = 1, b = 0, r = 0
       */
      PMBUS_tData.u32PinEnergyCtr_Old.u32Val = PMBUS_tData.u32PinEnergyCtr.u32Val;
      PMBUS_tData.u32PinSampleCount_Old.u32Val = PMBUS_tData.u32PinSampleCount.u32Val;
      PMBUS_tData.u8PinRolloverCount_Old = PMBUS_tData.u8PinRolloverCount;

      RTE_PMB_Write_bit_Ein_Upd(TRUE);
      PMBUS_tData.u32PinSampleCount.u32Val++;
      if (PMBUS_tData.u32PinSampleCount.u32Val > 0x00FFFFFFu)
      {
        PMBUS_tData.u8PinRolloverCount = 0;
        PMBUS_tData.u32PinSampleCount.u32Val = 1;
      }
      PMBUS_tData.u32PinEnergyCtr.u32Val += (PMBUS_tData.u32Pin_Mul_128.u32Val >> 7);

      if (PMBUS_tData.u32PinEnergyCtr.u32Val > MAX_DIRECT_DATA_FORMAT_VAL)
      {
        PMBUS_tData.u32PinEnergyCtr.u32Val -= MAX_DIRECT_DATA_FORMAT_VAL;
        if (PMBUS_tData.u8PinRolloverCount < 0xFFu)
        {
          PMBUS_tData.u8PinRolloverCount++; /* rollover */
        }
        else
        {
          PMBUS_tData.u8PinRolloverCount = 0;
          PMBUS_tData.u32PinSampleCount.u32Val = 1;
        }
      }
      RTE_PMB_Write_bit_Ein_Upd(FALSE);

      mg_u8UpdSensor = MG_E_UPD_FAN_NTC;

      break;
    }

    default:
    {
      mg_u8UpdSensor = MG_E_UPD_FAN_NTC;
      break;
    }
  }
}/* PMBUS_vCopySensorData */

/*******************************************************************************
 * \brief         Copy sensor data to PMBus sensor registers / 10ms
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCopyStatusData(void)
{
  /* First power up, need to delay 3s then to update status */
  if (0U < mg_u16StatusUpdDly)
  {
    mg_u16StatusUpdDly--;
  }
  else
  {

    /* 0x78  Status words */
    PMBUS_tStatusOld.u16StatusWordP0.ALL = PMBUS_tStatus.u16StatusWordP0.ALL;
    PMBUS_tStatusOld.u16StatusWordP1.ALL = PMBUS_tStatus.u16StatusWordP1.ALL;
    /* 0x7A Status Vout */
    PMBUS_tStatusOld.u8StatusVoutP0.ALL  = PMBUS_tStatus.u8StatusVoutP0.ALL;
    PMBUS_tStatusOld.u8StatusVoutP1.ALL  = PMBUS_tStatus.u8StatusVoutP1.ALL;
    /* 0x7B Status Iout */
    PMBUS_tStatusOld.u8StatusIoutP0.ALL  = PMBUS_tStatus.u8StatusIoutP0.ALL;
    PMBUS_tStatusOld.u8StatusIoutP1.ALL  = PMBUS_tStatus.u8StatusIoutP1.ALL;
		/* 0x7C Status Input */
    PMBUS_tStatusOld.u8StatusInputP0.ALL = PMBUS_tStatus.u8StatusInputP0.ALL;
    /* 0x7D Status Temperature */
    PMBUS_tStatusOld.u8StatusTempP0.ALL  = PMBUS_tStatus.u8StatusTempP0.ALL;
    /* 0x7E Status CML */
    PMBUS_tStatusOld.u8StatusCmlP0.ALL   = PMBUS_tStatus.u8StatusCmlP0.ALL;
    /* 0x7E Status Other */
    PMBUS_tStatusOld.u8StatusOtherP0.ALL = PMBUS_tStatus.u8StatusOtherP0.ALL;
    /* 0x80 Status MFR Specific */
    PMBUS_tStatusOld.u8StatusMfrP0.ALL   = PMBUS_tStatus.u8StatusMfrP0.ALL;
    /* 0x81 Status Fan_1_2 */
    PMBUS_tStatusOld.u8StatusFan12P0.ALL = PMBUS_tStatus.u8StatusFan12P0.ALL;
    /* 0x82 Status Fan_3_4 */
    PMBUS_tStatusOld.u8StatusFan34P0.ALL = PMBUS_tStatus.u8StatusFan34P0.ALL;

    RTE_PMB_Write_bit_Status_Upd(TRUE);
    /* Update Fault Status */
              
    /* if Work at Aux mode, then set it base status table */
    if (RTE_PMB_Read_bit_Aux_Mode())
    {
      PMBUS_tStatus.u16StatusWordP0.ALL |= 0x2848u;
      PMBUS_tStatus.u16StatusWordP1.ALL |= 0x0840u;

      PMBUS_tStatus.u8StatusInputP0.ALL |= 0x18u;
    }
    /* AC input applied, V1 turn off by Operation and control signals and Vsb present (STB Mode)*/
    else if (RTE_PMB_Read_bit_STB_MODE())
    {
      PMBUS_tStatus.u16StatusWordP0.ALL |= 0x0840u;
      PMBUS_tStatus.u16StatusWordP1.ALL |= 0x0800u;
    }
    else if ((RTE_B_PRI_UART_FAIL) || (RTE_B_SEC_UART_FAIL))
    {
      /* UART fail Mode */
      PMBUS_tStatus.u16StatusWordP0.ALL |= 0x0842u;
      PMBUS_tStatus.u16StatusWordP1.ALL |= 0x0840u;
      PMBUS_tStatus.u8StatusCmlP0.ALL   |= 0x02u;
    }
    else
    {
			/* if VSB Vout Fault */
			if ((TRUE == RTE_B_COM_VSB_OVP) || (TRUE == RTE_B_COM_VSB_UVP))
			{
				/*
				 * 0x7A Status Vout
				 * Bit7: VOUT_OV_FAULT
				 * Bit6:
				 * Bit5:
				 * Bit4: VOUT_UV_FAULT
				 * Bit3:
				 * Bit2:
				 * Bit1:
				 * Bit0:
				 */
				PMBUS_tStatus.u16StatusWordP1.Bits.VOUT_F_OR_W   = TRUE;
				if(TRUE == RTE_B_COM_VSB_OVP)
				{
					PMBUS_tStatus.u16StatusWordP1.Bits.VOUT_OV_FAULT = TRUE;
					PMBUS_tStatus.u8StatusVoutP1.Bits.VOUT_OV_FAULT  = TRUE;
				}
				if(TRUE == RTE_B_COM_VSB_UVP)
				{
				  PMBUS_tStatus.u8StatusVoutP1.Bits.VOUT_UV_FAULT  = RTE_B_COM_VSB_UVP;
				}
				/* Set Power Good and Output OFF Falg */
				PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N  = TRUE;
				PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF      = TRUE;
				PMBUS_tStatus.u16StatusWordP1.Bits.POWER_GOOD_N  = TRUE;
				PMBUS_tStatus.u16StatusWordP1.Bits.UINT_OFF      = TRUE;
			}
			/* if VSB Iout Fault */
			if (TRUE == RTE_B_COM_VSB_OCP)
			{
				/*
				 * 0x7B Status Vout
				 * Bit7: IOUT_OC_FAULT
				 * Bit6:
				 * Bit5: IOUT_OC_WARN
				 * Bit4:
				 * Bit3:
				 * Bit2:
				 * Bit1:
				 * Bit0:
				 */
				PMBUS_tStatus.u16StatusWordP1.Bits.IOUT_POUT_F_OR_W = TRUE;
				PMBUS_tStatus.u16StatusWordP1.Bits.IOUT_OC_FAULT    = TRUE;
				PMBUS_tStatus.u8StatusIoutP1.Bits.IOUT_OC_FAULT     = TRUE;
				PMBUS_tStatus.u8StatusIoutP1.Bits.IOUT_OC_WARN      = TRUE;
        
				/* Set Power Good and Output OFF Falg */
        if(TRUE == RTE_B_COM_VSB_ON)
        {
          PMBUS_tStatus.u16StatusWordP1.Bits.POWER_GOOD_N  = TRUE;
          PMBUS_tStatus.u16StatusWordP1.Bits.UINT_OFF      = TRUE;
        }
        else
        {
          PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N  = TRUE;
          PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF      = TRUE;
          PMBUS_tStatus.u16StatusWordP1.Bits.POWER_GOOD_N  = TRUE;
          PMBUS_tStatus.u16StatusWordP1.Bits.UINT_OFF      = TRUE;
        }
			}

      /* V1 Status report, if V1 ON */
      if ((FALSE != PMBUS_Rte_Read_B_R_V1_OVP()) || (FALSE != PMBUS_Rte_Read_B_R_V1_UVP()) || (FALSE != PMBUS_Rte_Read_B_R_V1_OCP()))
      {
        /* Set Power Good and Output OFF Falg */
        PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N = TRUE;
        PMBUS_tStatus.u16StatusWordP1.Bits.POWER_GOOD_N = TRUE;
        PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF     = TRUE;
				
				/*
         * 0x7A Status Vout
         * Bit7: VOUT_OV_FAULT
         * Bit6:
         * Bit5:
         * Bit4: VOUT_UV_FAULT
         * Bit3:
         * Bit2:
         * Bit1:
         * Bit0:
         */
				/* if V1 Vout Fault */
				if (TRUE == PMBUS_Rte_Read_B_R_V1_OVP())
				{
					PMBUS_tStatus.u16StatusWordP0.Bits.VOUT_F_OR_W = TRUE;
					PMBUS_tStatus.u16StatusWordP0.Bits.VOUT_OV_FAULT = TRUE;
					PMBUS_tStatus.u8StatusVoutP0.Bits.VOUT_OV_FAULT = TRUE;

				}
				if (TRUE == PMBUS_Rte_Read_B_R_V1_UVP())
				{
					PMBUS_tStatus.u16StatusWordP0.Bits.VOUT_F_OR_W  = TRUE;
					PMBUS_tStatus.u8StatusVoutP0.Bits.VOUT_UV_FAULT = TRUE;
				}
				
				/*
				 * 0x7B Status Iout
				 * Bit7: IOUT_OC_FAULT
				 * Bit6: IOUT_OC_LV_FAULT
				 * Bit5: IOUT_OC_WARN
				 * Bit4:
				 * Bit3:
				 * Bit2:
				 * Bit1:
				 * Bit0:
				 */
				/* if V1 Iout Fault */
				if (TRUE == PMBUS_Rte_Read_B_R_V1_OCP())
				{
					PMBUS_tStatus.u16StatusWordP0.Bits.IOUT_POUT_F_OR_W = TRUE;
					PMBUS_tStatus.u16StatusWordP0.Bits.IOUT_OC_FAULT = TRUE;
					PMBUS_tStatus.u8StatusIoutP0.Bits.IOUT_OC_FAULT = TRUE;
					PMBUS_tStatus.u8StatusIoutP0.Bits.IOUT_OC_WARN = TRUE;
				}	
      }
			
			/* if VSB Iout Warning */
			if ((TRUE == RTE_B_COM_VSB_OCW))
			{
				/*
				 * 0x7B Status Vout
				 * Bit7: 
				 * Bit6:
				 * Bit5: IOUT_OC_WARN
				 * Bit4:
				 * Bit3:
				 * Bit2:
				 * Bit1:
				 * Bit0:
				 */
				PMBUS_tStatus.u16StatusWordP1.Bits.IOUT_POUT_F_OR_W = TRUE;
				PMBUS_tStatus.u8StatusIoutP1.Bits.IOUT_OC_WARN      = TRUE;
			}
			
			/* if V1 Iout Warning */
			if (TRUE == RTE_B_COM_V1_OCW)
			{
				/*
				 * 0x7B Status Iout
				 * Bit7: 
				 * Bit6: 
				 * Bit5: IOUT_OC_WARN
				 * Bit4:
				 * Bit3:
				 * Bit2:
				 * Bit1:
				 * Bit0:
				 */
				PMBUS_tStatus.u16StatusWordP0.Bits.IOUT_POUT_F_OR_W = TRUE;
				PMBUS_tStatus.u8StatusIoutP0.Bits.IOUT_OC_WARN      = TRUE;
			}
      
      /* V1 output is OK */
      if(TRUE == PMBUS_Rte_Read_B_R_V1_OK())
      {
        /* Set Power Good and Output OFF Falg */
        PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N = FALSE;
        PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF     = FALSE;
      }

      /*
       * 0x7C Input judge, when UART fail, it will not run to here.
       * Bit7: VIN_OV_FAULT
       * Bit6: 
       * Bit5: VIN_UV_WARNING
       * Bit4: VIN_UV_FAULT
       * Bit3: VIN_LOW_OFF
       * Bit2:
       * Bit1:
       * Bit0:
       */
      if (FALSE == RTE_B_COM_VIN_OK)
      {
        PMBUS_tStatus.u16StatusWordP0.Bits.INPUT_F_OR_W     = TRUE;  
				PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N     = TRUE;
        PMBUS_tStatus.u16StatusWordP1.Bits.POWER_GOOD_N     = TRUE;
        PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF         = TRUE;
        PMBUS_tStatus.u16StatusWordP1.Bits.UINT_OFF         = TRUE;

        if (RTE_B_PRI_VIN_DROPOUT || RTE_B_COM_VIN_UV)
        {
					/* Word Status */
          PMBUS_tStatus.u16StatusWordP0.Bits.VIN_UV_FAULT    = TRUE;
					/* Input Status */
          PMBUS_tStatus.u8StatusInputP0.Bits.VIN_UV_FAULT    = TRUE;
          PMBUS_tStatus.u8StatusInputP0.Bits.VIN_UV_WARN     = TRUE;
          PMBUS_tStatus.u8StatusInputP0.Bits.OFF_FOR_VIN_LOW = TRUE;
        }
        if (RTE_B_COM_VIN_OV)
        {
          PMBUS_tStatus.u8StatusInputP0.Bits.VIN_OV_FAULT = TRUE;
        }      
      }
      
      /*
       * 0x7C Input judge, when UART fail, it will not run to here.
       * Bit7: 
       * Bit6: 
       * Bit5: VIN_UV_WARNING
       * Bit4: 
       * Bit3: 
       * Bit2:
       * Bit1:
       * Bit0:
       */
      if(FALSE != RTE_B_COM_VIN_UVW)
      {
        PMBUS_tStatus.u16StatusWordP0.Bits.INPUT_F_OR_W     = TRUE;  
        PMBUS_tStatus.u8StatusInputP0.Bits.VIN_UV_WARN      = TRUE;
      }

      /* Set/reset NONE_OF_THE_ABOVE bit. not used for Project Y */
      if (0x01 < PMBUS_tStatus.u16StatusWordP0.Bytes.LB)
      {
        PMBUS_tStatus.u16StatusWordP0.Bits.NONE_OF_THE_ABOVE = FALSE;
      }
      if (0x01 < PMBUS_tStatus.u16StatusWordP1.Bytes.LB)
      {
        PMBUS_tStatus.u16StatusWordP1.Bits.NONE_OF_THE_ABOVE = FALSE;
      }
			
      /*
       * 0x7D Status Temperature
       * Bit7: OT_FAULT
       * Bit6: OT_WARN
       * Bit5:
       * Bit4:
       * Bit3:
       * Bit2:
       * Bit1:
       * Bit0:
       */
      if (TRUE == RTE_B_TEMP_ANY_OTP)
      {
				/* 0x79 Word Status Page0 */
				PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N     = TRUE;
			  PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF         = TRUE;
        PMBUS_tStatus.u16StatusWordP0.Bits.TEMP_F_OR_W      = TRUE;
				/* 0x79 Word Status Page1 */
        PMBUS_tStatus.u16StatusWordP1.Bits.POWER_GOOD_N     = TRUE;
        /* 0x7D Temperature Status */
        PMBUS_tStatus.u8StatusTempP0.Bits.OT_FAULT          = TRUE;
        PMBUS_tStatus.u8StatusTempP0.Bits.OT_WARN           = TRUE;
      }
			
			if(TRUE ==  RTE_B_TEMP_ANY_OTW)
      {
				/* 0x79 Word Status Page0 */
        PMBUS_tStatus.u16StatusWordP0.Bits.TEMP_F_OR_W      = TRUE;
				/* 0x7D Temperature Status */
        PMBUS_tStatus.u8StatusTempP0.Bits.OT_WARN           = TRUE;
      }

      /*
       * 0x81 Status  STATUS_FANS_1_2
       * Bit7: FAN1_FAULT
       * Bit6: FAN2_FAULT
       * Bit5:
       * Bit4:
       * Bit3: FAN1_OVER_RIDE
       * Bit2: FAN2_OVER_RIDE
       * Bit1:
       * Bit0:
       */

      if (FALSE != PMBUS_SCFG_u8ReadFanBitFail(0))
      {
        PMBUS_tStatus.u8StatusFan12P0.Bits.FAN_1_FAULT = TRUE;
        PMBUS_tStatus.u16StatusWordP0.Bits.FANS_F_OR_W = TRUE;
      }
      if (FALSE != PMBUS_SCFG_u8ReadFanBitFail(1))
      {
        PMBUS_tStatus.u8StatusFan12P0.Bits.FAN_2_FAULT = TRUE;
        PMBUS_tStatus.u16StatusWordP0.Bits.FANS_F_OR_W = TRUE;
      }
      
      if (FALSE != PMBUS_SCFG_u8ReadFanBitOvrd(0))
      {
        PMBUS_tStatus.u8StatusFan12P0.Bits.FAN_1_SPD_OVERRIDE = TRUE;
				PMBUS_tStatus.u8StatusFan12P0.Bits.FAN_2_SPD_OVERRIDE = TRUE;
      }
      else
      {
        PMBUS_tStatus.u8StatusFan12P0.Bits.FAN_1_SPD_OVERRIDE = FALSE;
				PMBUS_tStatus.u8StatusFan12P0.Bits.FAN_2_SPD_OVERRIDE = FALSE;
      }
    }
    /*
     * 0x7E Status CML
     * Bit7: INVALID_CMD
     * Bit6: INVALID_DATAi
     * Bit4: 
     * Bit3:
     * Bit2:
     * Bit1: COMMS_FAULT
     * Bit0: 
     */
    if (PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA || 
			  PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD  ||
		    PMBUS_tStatus.u8StatusCmlP0.Bits.PEC_FAULT    ||
        PMBUS_tStatus.u8StatusCmlP0.Bits.COMMS_FAULT
		   )
    {
      PMBUS_tStatus.u16StatusWordP0.Bits.CML = TRUE;
    }

    RTE_PMB_Write_bit_Status_Upd(FALSE);
  }
  /* Judge SMBALERT base fault status */
  if (
       (PMBUS_tStatus.u8StatusVoutP0.ALL & (~mg_sP0SmbMask.u8Pmb_7A)) || /* 0x7A Page0 */
       (PMBUS_tStatus.u8StatusVoutP1.ALL & (~mg_sP1SmbMask.u8Pmb_7A)) || /* 0x7A Page1 */
       (PMBUS_tStatus.u8StatusIoutP0.ALL & (~mg_sP0SmbMask.u8Pmb_7B)) || /* 0x7B Page0 */
       (PMBUS_tStatus.u8StatusIoutP1.ALL & (~mg_sP1SmbMask.u8Pmb_7B)) || /* 0x7B Page1 */ 
       (PMBUS_tStatus.u8StatusInputP0.ALL & (~mg_sP0SmbMask.u8Pmb_7C))|| /* 0x7C */
       (PMBUS_tStatus.u8StatusTempP0.ALL & (~mg_sP0SmbMask.u8Pmb_7D)) || /* 0x7D */
       (PMBUS_tStatus.u8StatusCmlP0.ALL & (~mg_sP0SmbMask.u8Pmb_7E))  || /* 0x7E */
       (PMBUS_tStatus.u8StatusOtherP0.ALL & (~mg_sP0SmbMask.u8Pmb_7F))|| /* 0x7F */
       (PMBUS_tStatus.u8StatusMfrP0.ALL   & (~mg_sP0SmbMask.u8Pmb_80))|| /* 0x80 */
       ((PMBUS_tStatus.u8StatusFan12P0.ALL & 0xF0u) & (~mg_sP0SmbMask.u8Pmb_81)) ||  /* 0x81 */
       ((PMBUS_tStatus.u8StatusFan34P0.ALL & 0xF0u) & (~mg_sP0SmbMask.u8Pmb_82))     /* 0x82 */
    )
  {
    /* SMB asserted */
    RTE_B_COM_SMBALLERT_ST = TRUE;
  }
  else
  {
    /* SMB de-asserted */
    RTE_B_COM_SMBALLERT_ST = FALSE;
  }
}/* PMBUS_vCopyStatusData */

/*******************************************************************************
 * \brief         Update PEC Error and Oring Fault to E5 and E7
 *                which need to be updated fast
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCopyPecAndOringStatus(void)
{

} /* PMBUS_vCopyPecAndOringStatus */

/*******************************************************************************
 * \brief         Copy debug data to PMBus debug registers, every 10ms.
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCopyDebugData(void)
{
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_VIN_ADC].u16Val = RTE_Pri.u1610mVVinAvg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_IIN_ADC].u16Val = RTE_Pri.u161mAIinAvg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_PIN_ADC].u16Val = RTE_Pri.u16100mAPinAvg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_VBULK_ADC].u16Val = RTE_Pri.u16q12VbulkAdc.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_NTC_PFC_ADC].u16Val = RTE_Pri.u16PfcNtcAdcAvg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_STATUS_00].u16Val = RTE_Pri.u16PriStatus00.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_STATUS_01].u16Val = RTE_Pri.u16PriStatus01.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_DEBUG_0].u16Val = RTE_Pri.u16PriDebug0.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_DEBUG_1].u16Val = RTE_Pri.u16PriDebug1.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_DEBUG_2].u16Val = RTE_Pri.u16PriDebug2.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_VIN_FREQ].u16Val = RTE_Pri.u16100mHzVoltInFreq.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_PWR_FACT].u16Val = RTE_Pri.u16q16PwrFact.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_PRI_TEMP_STATUS].u16Val = RTE_Pri.uTempStatus00.ALL;

  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_V1_I_ADC].u16Val = RTE_Sec.u1610mAIoutAvg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_V1_INT_ADC].u16Val = RTE_Sec.u1610mVIntV1Avg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_V1_EXT_ADC].u16Val = RTE_Sec.u1610mVExtV1Avg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_V1_PWR_ADC].u16Val = RTE_Sec.u16100mWPwrOutAvg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_ISHARE_ADC].u16Val = RTE_Sec.u16VIShareAdcAvgAdc.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_ILOCAL_ADC].u16Val = RTE_Sec.u16VILocalAdcAvgAdc.u16Val;	
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_NTC_SR_ADC].u16Val = RTE_Sec.u161mVSrNtcAvg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_NTC_ORING_ADC].u16Val = RTE_Sec.u161mVOringNtcAvg.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_STATUS_00].u16Val = RTE_Sec.u16SecStatus00.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_STATUS_01].u16Val = RTE_Sec.u16SecStatus01.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_STATUS_02].u16Val = RTE_Sec.u16SecStatus02.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_DEBUG_0].u16Val = RTE_Sec.u16SecDebug0.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_DEBUG_1].u16Val = RTE_Sec.u16SecDebug1.u16Val;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_SEC_DEBUG_2].u16Val = RTE_Sec.u16SecDebug2.u16Val;

  mg_au8DebugRegBuf[RTE_DEBUG_ADR_TEMP_OTW_STATUS].u16Val = RTE_uTempOtwStatus.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_TEMP_OTP_STATUS].u16Val = RTE_uTempOtpStatus.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_DIO_IN_STATUS  ].u16Val = RTE_uDioInStatus.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_DIO_OUT_STATUS ].u16Val = RTE_uDioOutStatus.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_TO_PRI_STATUS].u16Val = RTE_uComToPriStatus.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_TO_SEC_STATUS].u16Val = RTE_uComToSecStatus.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_STATUS_00  ].u16Val = RTE_uComStatus00.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_STATUS_01  ].u16Val = RTE_uComStatus01.ALL;
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_STATUS_02  ].u16Val = RTE_uComStatus02.ALL;

  mg_au8DebugRegBuf[RTE_DEBUG_ADR_V_VSB_INT_AVG      ].u16Val = PMBUS_SCFG_u16GetVsbIntVoltAvg();
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_V_VSB_EXT_AVG      ].u16Val = PMBUS_SCFG_u16GetVsbExtVoltAvg();
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_I_VSB_AVG          ].u16Val = PMBUS_SCFG_u16GetVsbCurrAvg();
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_NTC_INLET_ADC_AVG  ].u16Val = PMBUS_SCFG_u16ReadAdcAvgInlet();
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_FAN_DUTY           ].u16Val = PMBUS_SCFG_u16ReadFanCtrlDuty(0);
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_FAN_SPEED_1        ].u16Val = PMBUS_SCFG_u16ReadFanSpeed(0);
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_FAN_SPEED_2        ].u16Val = PMBUS_SCFG_u16ReadFanSpeed(1);
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_DEBUG_0        ].u16Val = RTE_u16ComDebug[0];
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_DEBUG_1        ].u16Val = RTE_u16ComDebug[1];
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_DEBUG_2        ].u16Val = RTE_u16ComDebug[2];
  mg_au8DebugRegBuf[RTE_DEBUG_ADR_COM_DEBUG_3        ].u16Val = RTE_u16ComDebug[3];

}/* PMBUS_vCopyDebugData */

/*******************************************************************************
 * \brief         Prehandle the received bytes by command
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vCmdCheck(void)
{
	uint8 u8PmbusCommand;
	
  if (1U == RTE_u8I2cRxCnt)
  {
    PMBUS_uSysStatu0.Bits.PAGE_PLUS_WRITE  = 0;
    PMBUS_uSysStatu0.Bits.PAGE_PLUS_READ   = 0;
    PMBUS_uSysStatu0.Bits.PAGE_AND_WRITE   = 0;
    PMBUS_uSysStatu0.Bits.PAGE_AND_READ    = 0;
    PMBUS_uSysStatu0.Bits.INVALID_CMD      = 0;
    PMBUS_uSysStatu0.Bits.INVALID_DATA     = 0;
    PMBUS_uSysStatu0.Bits.QUERY_REQUEST    = 0;
    PMBUS_uSysStatu1.Bits.SMB_MASK_REQUEST = 0;    
    u8PmbusCommand                         = RTE_au8I2cRxBuf[0];
		PMBUS_Rte_Write_P_u8PMBusCmd(u8PmbusCommand);
    RTE_u8I2cExpRxCnt                      = PMB_mg_au8I2cRxNumber[u8PmbusCommand];
		RTE_u8I2cExpRxCnt                      += (RTE_bPEC_Enable == TRUE) ? 1u : 0;
    RTE_u8I2cExpTxCnt                      = PMB_mg_au8I2cTxNumber[u8PmbusCommand];
    RTE_I2C_CMD_DETECTED                   = TRUE;
  }

	PMBUS_Rte_Read_R_u8PMBusCmd(&u8PmbusCommand);
	
  switch (u8PmbusCommand)
  {
    case PMB_00_PAGE:
    case PMB_03_CLEAR_FAULTS: /* only effected here */
    {
      break;
    }
		
    case PMB_05_PAGE_PLUS_WRITE:
    {
      switch (RTE_u8I2cRxCnt)
      {
        case 1: /* cmd = PMB_05_PAGE_PLUS_WRITE */
        {
          PMBUS_SCFG_vSetBlockWrState();
          break;
        }
        case 2: /* Byte cnt */
        {
          break;
        }
        case 3: /* Page# */
        {
          break;
        }
        case 4: /* cmd code being queried */
        {
          if (RTE_au8I2cRxBuf[1] >= 2u)
          {
            if ((MG_PAGE_MAX >= RTE_au8I2cRxBuf[2]) || (MG_PAGE_FF == RTE_au8I2cRxBuf[2]))     /*change from RTE_au8I2cRxBuf[1] to RTE_au8I2cRxBuf[2]  joe20171221*/
            {
              RTE_PMB_Write_bit_Page_Plus_Write(TRUE);
              mg_u8Page = RTE_au8I2cRxBuf[2];
              u8PmbusCommand  = RTE_au8I2cRxBuf[3];
							PMBUS_Rte_Write_P_u8PMBusCmd(u8PmbusCommand);
              if (u8PmbusCommand == PMB_05_PAGE_PLUS_WRITE)
              {
                RTE_u8I2cRxCnt = 0x01u;
                PMBUS_SCFG_vSetBlockWrState();
              }
            }
            else
            {
              PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
            }
          }
          break;
        }
        default: /* err handle */
        {
          break;
        }
      }
      break;
    }

    case PMB_06_PAGE_PLUS_READ:
    {
      switch (RTE_u8I2cRxCnt)
      {
        case 1: /* cmd = PMB_05_PAGE_PLUS_WRITE */
        {
          /* Why add this, it is unused ?????????????????? */
          PMBUS_SCFG_vSetBlockWrState();
          break;
        }
        case 2: /* Byte cnt */
        {
          break;
        }
        case 3: /* Page# */
        {
          if ((MG_PAGE_MAX >= RTE_au8I2cRxBuf[2]) || (MG_PAGE_FF == RTE_au8I2cRxBuf[2]))  /*change from RTE_au8I2cRxBuf[1] to RTE_au8I2cRxBuf[2]  joe20171221*/
          {
            if (RTE_au8I2cRxBuf[1] >= 0x01u)
            {
              mg_u8Page = RTE_au8I2cRxBuf[2];
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
          }
          break;
        }
        case 4: /* cmd code to read */
        {
          if (RTE_au8I2cRxBuf[1] >= 0x01u)
          {
            RTE_PMB_Write_bit_Page_Plus_Read(TRUE);
            u8PmbusCommand = RTE_au8I2cRxBuf[3];
						PMBUS_Rte_Write_P_u8PMBusCmd(u8PmbusCommand);
            RTE_u8I2cExpTxCnt = PMB_mg_au8I2cTxNumber[u8PmbusCommand];
          }
          break;
        }
        default: /* err handle */
        {
          break;
        }
      }
      break;
    }

    case PMB_1A_QUERY:
    {
      switch (RTE_u8I2cRxCnt)
      {
        case 1: /* cmd */
        {
          PMBUS_SCFG_vSetBlockWrState();
          break;
        }
        case 2: /* Byte cnt */
        {
          break;
        }
        case 3: /* data */
        {
          if (RTE_au8I2cRxBuf[1] <= 0x01u)
          {
            RTE_PMB_Write_bit_Query_Request(TRUE);
          }
          break;
        }
        default: /* err handle */
        {
          break;
        }
      }
      break;
    }

    case PMB_1B_SMBALERT_MASK:
    {
      switch (RTE_u8I2cRxCnt)
      {
        case 1: /* cmd */
        {
          break;
        }
        case 2: /* Byte cnt */
        {
          break;
        }
        case 3: /* data */
        {
          if (0x01 == RTE_au8I2cRxBuf[1])
          {
            PMBUS_uSysStatu1.Bits.SMB_MASK_REQUEST = TRUE;
          }
          break;
        }
        default: /* err handle */
        {
          break;
        }
      }
      break;
    }

    case PMB_7E_STATUS_CML:
    {
      break;
    }

    case PMB_30_COEFFICIENTS:
    {
      switch (RTE_u8I2cRxCnt)
      {
        case 1: /* cmd */
        {
          /* this is not block write */
          PMBUS_uSysStatu0.Bits.CEFCT_READ_EIN_EOUT = FALSE;
          /* WHen write to MCU, it is not block write */
          PMBUS_SCFG_vSetBlockWrState();
          break;
        }
        case 2: /* Byte cnt */
        {
          break;
        }
        case 3: /* data */
        {
          if ((PMB_86_READ_EIN == RTE_au8I2cRxBuf[2]) ||
            (PMB_87_READ_EOUT == RTE_au8I2cRxBuf[2]))
          {
            if (0x01 == RTE_au8I2cRxBuf[3])
            {
              PMBUS_uSysStatu0.Bits.CEFCT_READ_EIN_EOUT = TRUE;
            }
          }
          break;
        }
        default: /* err handle */
        {
          break;
        }
      }
      break;
    }

    case PMB_C9_CALIBRATION: 
		{
      if (FALSE == PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
      {
        PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
        break;
      }

      switch (RTE_u8I2cRxCnt)
      {
        case 1:
        { /* cmd */
          break;
        }
        case 2:
        { /* byte count */
          break;
        }
        case 3:
        {
          /* cali done/def @ cnt = 1, else cali mode  */
          if (RTE_u8I2cPEC == 0)
          {
            CALI_uStatus.Bits.CALI_COMMAND = FALSE;
            CALI_uStatus.Bits.CALI_READ = FALSE;
          }
          else
          {
            CALI_sPara.u8DataBytes = RTE_au8I2cRxBuf[1];
            CALI_sPara.u8DataMode = RTE_au8I2cRxBuf[2];
          }
          break;
        }
        case 4:
        {
          /* cali line */
          CALI_sPara.u8DataLine = RTE_au8I2cRxBuf[3];
          if ((0U == RTE_u8I2cPEC) /* PEC */
            && (1U == CALI_sPara.u8DataBytes))
          { /* Cali done/default */
            CALI_uStatus.Bits.CALI_COMMAND = TRUE;
          }
          break;
        }
        case 5:
        {
          /* Amp Low */
          if ((RTE_u8I2cPEC == 0)
              && (CALI_sPara.u8DataBytes == 2))
          {
            CALI_uStatus.Bits.CALI_READ = TRUE;
            CALI_uStatus.Bits.CALI_COMMAND = TRUE;
          }
          break;
        }
        case 6:
        {
          break;
        }
        case 7:
        {
          break;
        }
        case 8:
        {
          break;
        }
        case 9:
        {
          break;
        }
        case 10:
        {
          break;
        }
        case 11:
        {
          if (RTE_u8I2cPEC == 0)
          {
            if ((RTE_au8I2cRxBuf[1] == 8u)
              && (!CALI_uStatus.Bits.CALI_NEW_DATA))
            {
              CALI_sPara.sUser.s16Amp = GET_WORD(RTE_au8I2cRxBuf[5], RTE_au8I2cRxBuf[4]);
              CALI_sPara.sUser.s16Ofs = GET_WORD(RTE_au8I2cRxBuf[7], RTE_au8I2cRxBuf[6]);
              CALI_sPara.sUser.s16Thr = GET_WORD(RTE_au8I2cRxBuf[9], RTE_au8I2cRxBuf[8]);
              CALI_uStatus.Bits.CALI_NEW_DATA = TRUE;
            }
            CALI_uStatus.Bits.CALI_COMMAND = TRUE;
          }
          break;
        }
        default:
        {
          /* err handle */
          break;
        }
      }
      break;
    }
		
		case PMB_01_OPERATION:
		case PMB_3B_FAN_COMMAND_1:
		case PMB_3C_FAN_COMMAND_2:
		case PMB_3E_FAN_COMMAND_3:
		case PMB_3F_FAN_COMMAND_4:
    case PMB_51_OT_WARN_LIMIT:
		case PMB_DD_MFR_REAL_TIME_BLACK_BOX:
		case PMB_DE_MFR_SYSTEM_BLCAKBOX:
		case PMB_DF_MFR_BLCAKBOX_CONFIG:
		case PMB_E0_MFR_CLEAR_BLACKBOX:
    case PMB_FA_MFR_FUNCTION_CTRL:
		{
			break;
		}
		
		case PMB_F6_UNLOCK_DEBUG:
		{
			break;
		}

    default:
    {
      /* Check if command is valid */
      if (RTE_u8I2cRxCnt == 1)
      {
        if (FALSE == PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
        {
          /* Access to Delta Internal used commands is not supported unless unlocked */
          if ((u8PmbusCommand >= PMB_CMD_DELTA_INT_STR)
               && (u8PmbusCommand <= PMB_CMD_DELTA_INT_END))
          {
            RTE_u8I2cExpRxCnt = 0;
            RTE_u8I2cExpTxCnt = 0;
          }
        }
        if ((RTE_u8I2cExpRxCnt == 0)
             && (RTE_u8I2cExpTxCnt == 0))
        {
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
        }
      }
      break;
    }
  }
} /* PMBUS_vCmdCheck */

/********************************************************************************
 * \brief         Prepare data for Query command
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vSendQuerydata(void)
{
  uint8 u8Query_CmdCode = RTE_au8I2cRxBuf[2];

  RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 1; /* one byte */
  switch (mg_u8Page)
  {
    case MG_PAGE_00: /* send back, which Registers are supported */
    {
      RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMB_mg_au8ByteFormatP0[u8Query_CmdCode];
      break;
    }
		case MG_PAGE_01:
		{
      RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMB_mg_au8ByteFormatP1[u8Query_CmdCode];
      break;
		}
		case MG_PAGE_02:
		case MG_PAGE_04:
		{
      if ((u8Query_CmdCode == PMB_00_PAGE)      ||
          (u8Query_CmdCode == PMB_1A_QUERY)     ||
          (u8Query_CmdCode == PMB_20_VOUT_MODE)	||	
          (u8Query_CmdCode == PMB_8B_READ_VOUT)			
			   )
      {
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMB_mg_au8ByteFormatP0[u8Query_CmdCode];
      }
      else
			{
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
			}
			break;
		}
    case MG_PAGE_03:
    {
      if ((u8Query_CmdCode == PMB_00_PAGE)
        || (u8Query_CmdCode == PMB_1A_QUERY))
      {
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMB_mg_au8ByteFormatP0[u8Query_CmdCode];
      }
			else
			{
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
			}
      break;
    }
    case MG_PAGE_FF: /* send back, which Registers are supported */
    {
      if ((u8Query_CmdCode == PMB_00_PAGE)
        || (u8Query_CmdCode == PMB_03_CLEAR_FAULTS)
        || (u8Query_CmdCode == PMB_1A_QUERY))
      {
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMB_mg_au8ByteFormatP0[u8Query_CmdCode];
      }
			else
			{
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
			}
      break;
    }

    default:
    {
      RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
      break;
    }
  }
} /* mg_vSendQuerydata() */

/********************************************************************************
 * \brief         Prepare data for SMB Alert MASK command
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vSendSmbMaskdata(void)
{
  uint8 u8SmbMask_CmdCode = RTE_au8I2cRxBuf[2];

  RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 1; /* one byte */
  switch (mg_u8Page)
  {
    case MG_PAGE_00: /* send back, which Registers are supported */
    {
      switch (u8SmbMask_CmdCode)
      {
        case PMB_7A_STATUS_VOUT:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_7A;
          break;
        }
        case PMB_7B_STATUS_IOUT:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_7B;
          break;
        }
        case PMB_7C_STATUS_INPUT:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_7C;
          break;
        }
        case PMB_7D_STATUS_TEMPERATURE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_7D;
          break;
        }
        case PMB_7E_STATUS_CML:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_7E;
          break;
        }
        case PMB_7F_STATUS_OTHER:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_7F;
          break;
        }
        case PMB_80_STATUS_MFR_SPECIFIC:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_80;
          break;
        }
        case PMB_81_STATUS_FANS_1_2:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_81;
          break;
        }
        case PMB_82_STATUS_FANS_3_4:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_82;
          break;
        }
        default:
        {
					PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
          break;
        }
      }
      break;
    }
    case MG_PAGE_01: /* send back, which Registers are supported */
    {
      switch (u8SmbMask_CmdCode)
      {
        case PMB_7A_STATUS_VOUT:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP0SmbMask.u8Pmb_7A;
          break;
        }
        case PMB_7B_STATUS_IOUT:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_sP1SmbMask.u8Pmb_7B;
          break;
        }
        default:
        {
					PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
          break;
        }
      }
    }

    default:
    {
      PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
      break;
    }
  } /* mg_vSendSmbMaskdata() */
}

/********************************************************************************
 * \brief         Prepare data for system reading
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vSendData(void)
{
  uint8 u8Cnt = 0;
  uint8 u8ByteNum = 0;
  WORD_VAL u16TempData;
	uint8 u8PmbusCommand;
  uint8 u8TmpData;
	
	PMBUS_Rte_Read_R_u8PMBusCmd(&u8PmbusCommand);

  if (PMBUS_uSysStatu0.Bits.QUERY_REQUEST == TRUE)
  {
    PMBUS_uSysStatu0.Bits.QUERY_REQUEST = FALSE;
    mg_vSendQuerydata();
  }
  else if (PMBUS_uSysStatu1.Bits.SMB_MASK_REQUEST == TRUE)
  {
    PMBUS_uSysStatu1.Bits.SMB_MASK_REQUEST = FALSE;
    mg_vSendSmbMaskdata();
  }
  else
  {
    RTE_u8I2cTxLen = 0;

    if (PMBUS_uSysStatu0.Bits.PAGE_PLUS_READ)
    {
      if (RTE_u8I2cExpTxCnt > 0)
      {
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u8I2cExpTxCnt;
      }
      PMBUS_uSysStatu0.Bits.PAGE_PLUS_READ = 0;
    }

    /*************************************************
     *   PAGE 00/01
     *************************************************/
    if (mg_u8Page == MG_PAGE_00)
    {
      switch (u8PmbusCommand)
      {
          /* Standard PMBus commands */
        case PMB_00_PAGE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_u8Page;
          break;
        }				
          /*
           * Turns on/off power supply. Command argument determines ON/OFF.
           * Data:
           * 0000 0000 ¡§C to turn off
           * 1000 0000 ¡§C to turn on.
           * The read back should return the last written value.
           */
        case PMB_01_OPERATION:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x00;
          }
          else
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_uOperation.ALL;
          }
          break;
        }
          /*
           * Bit  7=1    Packet Error Checking is supported
           * Bits 6:5=01 Maximum supported bus speed is 400 kHz
           * Bit  4=0    This device does not support the SMBus Alert Response protocol
           * Bits 3:1    Reserved
           * Bit  0=0    Code Redundancy can't support
           */
        case PMB_19_CAPABILITY:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = SUPPORT_PEC_400K_ALERT;
          break;
        }

          /*
           * Bits 7:5=010   Linear Mode Supported
           * Bit  4:0=00000 Don't Care
           */
        case PMB_20_VOUT_MODE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_VOUT_MODE_LINEAR; /* 0x19 */
          break;
        }

        case PMB_30_COEFFICIENTS: /* .sab0d30d02d86d01sab1rrrrrrlp */
        {
          if (PMBUS_uSysStatu0.Bits.CEFCT_READ_EIN_EOUT)
          {
            RTE_au8I2cTxBuf[0] = COEFF_BYTE_COUNT_5;
            RTE_au8I2cTxBuf[1] = COEFF_M_EIN_EOUT_LB;
            RTE_au8I2cTxBuf[2] = COEFF_M_EIN_EOUT_HB;
            RTE_au8I2cTxBuf[3] = COEFF_B_EIN_EOUT_LB;
            RTE_au8I2cTxBuf[4] = COEFF_B_EIN_EOUT_HB;
            RTE_au8I2cTxBuf[5] = COEFF_R_EIN_EOUT;
            RTE_u8I2cTxLen     = 6;
            PMBUS_uSysStatu0.Bits.CEFCT_READ_EIN_EOUT = FALSE;
          }
          break;
        }
          /* Read: 0x99 => FAN 1 and 2 installed and commanded in duty cycle, 2 pulse per revolution */
        case PMB_3A_FAN_CONFIG_1_2:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_PARA_3A_FAN_CFG_1_2;
          break;
        }
          /* Speed read in Duty-Cycle */
        case PMB_3B_FAN_COMMAND_1:
        {
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u16FanCmd_1_Linear.Bytes.LB;
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u16FanCmd_1_Linear.Bytes.HB;
          break;
        }
          /* Speed read in Duty-Cycle */
        case PMB_3C_FAN_COMMAND_2:
        {
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u16FanCmd_2_Linear.Bytes.LB;
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u16FanCmd_2_Linear.Bytes.HB;
          break;
        }
          /* Read: 0x99 => FAN 3 and 4 installed and commanded in duty cycle, 2 pulse per revolution */
        case PMB_3D_FAN_CONFIG_3_4:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_PARA_3D_FAN_CFG_3_4;
          break;
        }

        /* Speed read in Duty-Cycle */
        case PMB_3E_FAN_COMMAND_3:
        {
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u16FanCmd_3_Linear.Bytes.LB;
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u16FanCmd_3_Linear.Bytes.HB;
          break;
        }

          /* Speed read in Duty-Cycle */
        case PMB_3F_FAN_COMMAND_4:
        {
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u16FanCmd_4_Linear.Bytes.LB;
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u16FanCmd_4_Linear.Bytes.HB;
          break;
        }
				
        case PMB_40_VOUT_OV_FAULT_LIMIT:
        {
          u16TempData.u16Val = V1_VOUT_OV_FAULT_LIMIT;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
				
        case PMB_46_IOUT_OC_FAULT_LIMIT:
        {
          if (RTE_B_PRI_VIN_LINE_LOW) /* Low line input */
          {
            u16TempData.u16Val = V1_IOUT_OC_FAULT_LIMIT_LL;
          }
          else
          {
            u16TempData.u16Val = V1_IOUT_OC_FAULT_LIMIT_HL;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        case PMB_4A_IOUT_OC_WARN_LIMIT:
        {
          if (RTE_B_PRI_VIN_LINE_LOW) /* Low line input */
          {
            u16TempData.u16Val = V1_IOUT_OC_WARN_LIMIT_HL;
          }
          else
          {
            u16TempData.u16Val = V1_IOUT_OC_WARN_LIMIT_LL;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
				
        case PMB_4F_OT_FAULT_LIMIT:
        {
          u16TempData.u16Val = V1_IOUT_OT_FAULT_LIMIT;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        case PMB_51_OT_WARN_LIMIT:
        {
          PMBUS_Rte_Read_R_s16OtWarning(&u16TempData.s16Val);
          u16TempData.u16Val &= 0x07FFu;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        case PMB_55_VIN_OV_FAULT_LIMIT:
        {
          if (RTE_B_PRI_VDC_IN) /* DC input */
          {
            u16TempData.u16Val = VIN_OV_FAULT_LIMIT_DC;
          }
          else
          {
            u16TempData.u16Val = VIN_OV_FAULT_LIMIT_AC;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        case PMB_59_VIN_UV_FAULT_LIMIT:
        {
          if (RTE_B_PRI_VDC_IN) /* DC input */
          {
            u16TempData.u16Val = VIN_UV_FAULT_LIMIT_DC;
          }
          else
          {
            u16TempData.u16Val = VIN_UV_FAULT_LIMIT_AC;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
				
        case PMB_78_STATUS_BYTE:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u16StatusWordP0.Bytes.LB;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u16StatusWordP0.Bytes.LB;
					}
          break;
        }
   
        case PMB_79_STATUS_WORD:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u16StatusWordP0.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u16StatusWordP0.Bytes.HB;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u16StatusWordP0.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u16StatusWordP0.Bytes.HB;
					}
          break;
        }

        case PMB_7A_STATUS_VOUT:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusVoutP0.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusVoutP0.ALL;
					}
          break;
        }

        case PMB_7B_STATUS_IOUT:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusIoutP0.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusIoutP0.ALL;
					}
          break;
        }

        case PMB_7C_STATUS_INPUT:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusInputP0.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusInputP0.ALL;
					}
          break;
        }

        case PMB_7D_STATUS_TEMPERATURE:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusTempP0.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusTempP0.ALL;
					}
          break;
        }

        case PMB_7E_STATUS_CML:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusCmlP0.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusCmlP0.ALL;
					}
          break;
        }

        case PMB_7F_STATUS_OTHER:
        {
				  RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusOtherP0.ALL;
          break;
        }
				
        case PMB_80_STATUS_MFR_SPECIFIC:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusMfrP0.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusMfrP0.ALL;
					}
          break;
        }

        case PMB_81_STATUS_FANS_1_2:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusFan12P0.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusFan12P0.ALL;
					}
          break;
        }
        case PMB_82_STATUS_FANS_3_4:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusFan34P0.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusFan34P0.ALL;
					}
          break;
        }

        case PMB_86_READ_EIN:
        {
					if (PMBUS_uDataUpdStatus1.Bits.EIN_UPDTING)
					{
						u16TempData.u16Val = PMBUS_tData.u32PinEnergyCtr_Old.u32Val;
						RTE_au8I2cTxBuf[0] = 6u; /* Block Counter */
						RTE_au8I2cTxBuf[1] = u16TempData.Bytes.LB; /* Energy Counter Low Byte */
						RTE_au8I2cTxBuf[2] = u16TempData.Bytes.HB; /* Energy Counter High Byte */
						RTE_au8I2cTxBuf[3] = PMBUS_tData.u8PinRolloverCount_Old; /* Rollover Counter Byte */
						RTE_au8I2cTxBuf[4] = PMBUS_tData.u32PinSampleCount_Old.Bytes.LB; /* Sample Counter LOW Byte */
						RTE_au8I2cTxBuf[5] = PMBUS_tData.u32PinSampleCount_Old.Bytes.HB; /* Sample Counter MID Byte */
						RTE_au8I2cTxBuf[6] = PMBUS_tData.u32PinSampleCount_Old.Bytes.UB; /* Sample Counter HIGH Byte */
						RTE_u8I2cTxLen = 7;
					}
					else
					{
						u16TempData.u16Val = PMBUS_tData.u32PinEnergyCtr.u32Val;
						RTE_au8I2cTxBuf[0] = 6u; /* Block Counter */
						RTE_au8I2cTxBuf[1] = u16TempData.Bytes.LB; /* Energy Counter Low Byte */
						RTE_au8I2cTxBuf[2] = u16TempData.Bytes.HB; /* Energy Counter High Byte */
						RTE_au8I2cTxBuf[3] = PMBUS_tData.u8PinRolloverCount; /* Rollover Counter Byte */
						RTE_au8I2cTxBuf[4] = PMBUS_tData.u32PinSampleCount.Bytes.LB; /* Sample Counter LOW Byte */
						RTE_au8I2cTxBuf[5] = PMBUS_tData.u32PinSampleCount.Bytes.HB; /* Sample Counter MID Byte */
						RTE_au8I2cTxBuf[6] = PMBUS_tData.u32PinSampleCount.Bytes.UB; /* Sample Counter HIGH Byte */
						RTE_u8I2cTxLen = 7;
					}
          break;
        }
				
        case PMB_87_READ_EOUT:
        {
					if (PMBUS_uDataUpdStatus1.Bits.EOUT_UPDTING)
					{
						u16TempData.u16Val = PMBUS_tData.u32PoutEnergyCtr_Old.u32Val;
						RTE_au8I2cTxBuf[0] = 6u; /* Block Counter */
						RTE_au8I2cTxBuf[1] = u16TempData.Bytes.LB; /* Energy Counter Low Byte */
						RTE_au8I2cTxBuf[2] = u16TempData.Bytes.HB; /* Energy Counter High Byte */
						RTE_au8I2cTxBuf[3] = PMBUS_tData.u8PoutRolloverCount_Old; /* Rollover Counter Byte */
						RTE_au8I2cTxBuf[4] = PMBUS_tData.u32PoutSampleCount_Old.Bytes.LB; /* Sample Counter LOW Byte */
						RTE_au8I2cTxBuf[5] = PMBUS_tData.u32PoutSampleCount_Old.Bytes.HB; /* Sample Counter MID Byte */
						RTE_au8I2cTxBuf[6] = PMBUS_tData.u32PoutSampleCount_Old.Bytes.UB; /* Sample Counter HIGH Byte */
						RTE_u8I2cTxLen = 7;
					}
					else
					{
						u16TempData.u16Val = PMBUS_tData.u32PoutEnergyCtr.u32Val;
						RTE_au8I2cTxBuf[0] = 6u; /* Block Counter*/
						RTE_au8I2cTxBuf[1] = u16TempData.Bytes.LB; /* Energy Counter Low Byte */
						RTE_au8I2cTxBuf[2] = u16TempData.Bytes.HB; /* Energy Counter High Byte */
						RTE_au8I2cTxBuf[3] = PMBUS_tData.u8PoutRolloverCount; /* Rollover Counter Byte */
						RTE_au8I2cTxBuf[4] = PMBUS_tData.u32PoutSampleCount.Bytes.LB; /* Sample Counter LOW Byte */
						RTE_au8I2cTxBuf[5] = PMBUS_tData.u32PoutSampleCount.Bytes.HB; /* Sample Counter MID Byte */
						RTE_au8I2cTxBuf[6] = PMBUS_tData.u32PoutSampleCount.Bytes.UB; /* Sample Counter HIGH Byte */
						RTE_u8I2cTxLen = 7;
					}
          break;
        }

        case PMB_88_READ_VIN:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
					}
					else
					{
						if (RTE_PMB_Read_bit_Vin_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Vin_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
					}
          break;
        }

        case PMB_89_READ_IIN:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
					}
					else
					{
						if (RTE_PMB_Read_bit_Iin_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Iin_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
					}
          break;
        }
				
				case PMB_8A_READ_VCAP:
				{
					if (RTE_PMB_Read_bit_VCAP_Upd())
					{
						u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
					}
					else
					{
						u16TempData.u16Val = PMBUS_tData.u16Vcap_Linear.u16Val;
					}
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
					break;
				}
				
        case PMB_8B_READ_VOUT:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
          }
          else
          {
						if (RTE_PMB_Read_bit_Vout_V1_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Vout_V1_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
				  }
          break;
        }

        case PMB_8C_READ_IOUT:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
          }
          else
          {
						if (RTE_PMB_Read_bit_Iout_V1_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Iout_V1_Linear.u16Val;
						}
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          }
          break;
        }
				
        case PMB_8D_READ_TEMPERATURE_1:
        {
          if (RTE_PMB_Read_bit_Inlet_Upd())
          {
            u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
          }
          else
          {
            u16TempData.u16Val = PMBUS_tData.u16Temperatue_1_Linear.u16Val;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_8E_READ_TEMPERATURE_2:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
            if (RTE_PMB_Read_bit_Inlet_Upd())
            {
              u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
            }
            else
            {
              u16TempData.u16Val = PMBUS_tData.u16Temperatue_1_Linear.u16Val;
            }
					}
					else
					{
						if (RTE_PMB_Read_bit_Pfc_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Temperatue_2_Linear.u16Val;
						}
					}
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_8F_READ_TEMPERATURE_3:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
            if (RTE_PMB_Read_bit_Inlet_Upd())
            {
              u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
            }
            else
            {
              u16TempData.u16Val = PMBUS_tData.u16Temperatue_1_Linear.u16Val;
            }
					}
					else
					{
						if (RTE_PMB_Read_bit_SR_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Temperatue_3_Linear.u16Val;
						}
					}
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
          /* Read RPM Fan 1. 10 bit data. Linear data format */
        case PMB_90_READ_FAN_SPEED_1:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
					}
					else
					{
						if (RTE_PMB_Read_bit_Fan_Spd_1_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16FanSpeed_1_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
					}
          break;
        }
          /* Read RPM Fan 1. 10 bit data. Linear data format */
        case PMB_91_READ_FAN_SPEED_2:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
					}
					else
					{
						if (RTE_PMB_Read_bit_Fan_Spd_2_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16FanSpeed_2_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
				  }

          break;
        }

        case PMB_92_READ_FAN_SPEED_3:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
					}
					else
					{
						if (RTE_PMB_Read_bit_Fan_Spd_3_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16FanSpeed_3_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
					}
          break;
        }

        case PMB_93_READ_FAN_SPEED_4:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
					}
					else
					{
						if (RTE_PMB_Read_bit_Fan_Spd_4_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16FanSpeed_4_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
					}
          break;
        }

        case PMB_96_READ_POUT:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
          }
          else
          {
						if (RTE_PMB_Read_bit_Pout_V1_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Pout_V1_Linear.u16Val;
						}
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          }
          break;
        }

        case PMB_97_READ_PIN:
        {
					if (RTE_PMB_Read_bit_Aux_Mode())
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
					}
					else
					{
						if (RTE_PMB_Read_bit_Pin_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Pin_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
					}
          break;
        }

        case PMB_98_PMBUS_REVISION:
        {
				  RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_PARA_REVISION;
          break;
        }
				
        case PMB_99_MFR_ID:
        case PMB_9A_MFR_MODEL:
        case PMB_9B_MFR_REVISION:
        case PMB_9C_MFR_LOCATION:
        case PMB_9D_MFR_DATE:
        case PMB_9E_MFR_SERIAL:
        {
						//u16Addr = ((u8PmbusCommand - PMB_99_MFR_ID) << 4) + EEP_MFR_INFO_STR;
					u8ByteNum = RTE_au8MfrData[(u8PmbusCommand - PMB_99_MFR_ID)][0];
					if (u8ByteNum > 16u)
					{
						u8ByteNum = 16u;
					}
					for (u8Cnt = 0; u8Cnt <= u8ByteNum; u8Cnt++)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_au8MfrData[(u8PmbusCommand - PMB_99_MFR_ID)][u8Cnt];
					}
          break;
        }
				
        case PMB_A0_MFR_VIN_MIN:
        {
          if (RTE_B_PRI_VDC_IN)/* DC input */
          {
            u16TempData.u16Val = MFR_VIN_DC_MAX;
          }
          else
          {
            u16TempData.u16Val = MFR_VIN_AC_MIN;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A1_MFR_VIN_MAX:
        {
          if (RTE_B_PRI_VDC_IN)/* DC input */
          {
            u16TempData.u16Val = MFR_VIN_DC_MAX;
          }
          else
          {
            u16TempData.u16Val = MFR_VIN_AC_MAX;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A2_MFR_IIN_MAX:
        {
          u16TempData.u16Val = MFR_IIN_AC_MAX;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A3_MFR_PIN_MAX:
        {
          u16TempData.u16Val = MFR_PIN_HL_MAX; //MFR_PIN_LL_MAX
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A4_MFR_VOUT_MIN:
        {
          u16TempData.u16Val = MFR_V1OUT_MIN;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A5_MFR_VOUT_MAX:
        {
          u16TempData.u16Val = MFR_V1OUT_MAX;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A6_MFR_IOUT_MAX:
        {
          u16TempData.u16Val = MFR_I1OUT_HL_MAX;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A7_MFR_POUT_MAX:
        {
          u16TempData.u16Val = MFR_P1OUT_MAX;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
				
        case PMB_A8_MFR_TAMBIENT_MAX:
        {
          u16TempData.u16Val = MFR_TAMBIENT_MAX;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A9_MFR_TAMBIENT_MIN:
        {
          u16TempData.u16Val = MFR_TAMBIENT_MIN;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        
        case PMB_AA_EFFICIENCY_LL:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 14u;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_VIN_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_VIN_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_L_POWER_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_L_POWER_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_L_EFFICY_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_L_EFFICY_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_M_POWER_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_M_POWER_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_M_EFFICY_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_M_EFFICY_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_H_POWER_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_H_POWER_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_H_EFFICY_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_LL_H_EFFICY_HB;
          break;
        }
        
        case PMB_AB_EFFICIENCY_HL:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 14u;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_VIN_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_VIN_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_L_POWER_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_L_POWER_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_L_EFFICY_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_L_EFFICY_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_M_POWER_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_M_POWER_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_M_EFFICY_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_M_EFFICY_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_H_POWER_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_H_POWER_HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_H_EFFICY_LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = EFFICIENCY_HL_H_EFFICY_HB;
          break;
        }
        
        case PMB_C0_MFR_MAX_TEMP_1:
        {
          u16TempData.u16Val = MFR_MAX_TEMP_1;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        
        case PMB_C1_MFR_MAX_TEMP_2:
        {
          u16TempData.u16Val = MFR_MAX_TEMP_2;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        
        case PMB_C2_MFR_MAX_TEMP_3:
        {
          u16TempData.u16Val = MFR_MAX_TEMP_3;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        
        case PMB_D8_MFR_LINE_STATUS:
        {
          PMBUS_Rte_Read_R_u8AcLineStatus(&u8TmpData);
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u8TmpData;
          break;
        }

        case PMB_DC_MFR_BLACK_BOX:
        { 
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 252u;
          PMBUS_SCFG_vReadMfrBlackbox((uint8 *)&RTE_au8I2cTxBuf[RTE_u8I2cTxLen]);
          RTE_u8I2cTxLen += 252u;
          break;
        }

        case PMB_DD_MFR_REAL_TIME_BLACK_BOX:
        {
          DWORD_VAL dwTmp;

          dwTmp.u32Val = PMBUS_SCFG_u32GetRealTimeClockDataSystemBlackbox();
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x04u;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = dwTmp.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = dwTmp.Bytes.HB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = dwTmp.Bytes.UB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = dwTmp.Bytes.MB;

          break;
        }
        case PMB_DE_MFR_SYSTEM_BLCAKBOX:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 40u;
          PMBUS_SCFG_vReadSystemBlackBox((uint8 *)&RTE_au8I2cTxBuf[RTE_u8I2cTxLen]);
          RTE_u8I2cTxLen += 40u;
          break;
        }
        case PMB_DF_MFR_BLCAKBOX_CONFIG:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_SCFG_u8GetEnableBlackbox();
          break;
        }
				
        case PMB_E1_READ_BOOT_FW_REVISION: 
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x06u;
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusBootFwRevCom.Bytes.LB;       /* Logic A Major Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusBootFwRevCom.Bytes.HB;        /* Logic A Minor Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusBootFwRevSec1.Bytes.LB;       /* Sec A Boot Major Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusBootFwRevSec1.Bytes.HB;      /* Sec A Boot Minor Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusBootFwRevPri1.Bytes.LB;       /* Pri A Boot Major Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusBootFwRevPri1.Bytes.HB;      /* Pri A Boot Minor Rev */
          break;
        }

        case PMB_E2_READ_APP_FW_REVISION: 
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = 0x06u;
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevCom.Bytes.LB;      /* Logic A Major Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevCom.Bytes.HB;     /* Logic A Minor Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevSec1.Bytes.LB;     /* Sec A Major Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevSec1.Bytes.HB;    /* Sec A Minor Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevPri1.Bytes.LB;     /* Pri A Major Rev */
					RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevPri1.Bytes.HB;    /* Pri A Minor Rev */
					break;
        }

        case PMB_E3_READ_HOURS_USED: 
        {
				  if (RTE_PMB_Read_bit_Hours_Upd()) 
					{ 
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x03u;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.HB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.UB;
					}
					else 
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x03u;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32HoursUsed.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32HoursUsed.Bytes.HB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32HoursUsed.Bytes.UB;  
					}
          break;
        }
        
        case PMB_E5_MFR_POS_TOTAL:
        {
          if (RTE_PMB_Read_bit_POS_TOTAL_Upd())
          {
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x04u;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.HB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.UB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.MB;
          }
          else
          {
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x04u;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32PosTotal.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32PosTotal.Bytes.HB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32PosTotal.Bytes.UB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32PosTotal.Bytes.MB;
          }
          break;
        }
        
        case PMB_E6_MFR_POS_LAST:
        {
          if (RTE_PMB_Read_bit_POS_LAST_Upd())
          {
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x04u;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.HB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.UB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32DataCopy.Bytes.MB;
          }
          else
          {
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x04u;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32PosLast.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32PosLast.Bytes.HB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32PosLast.Bytes.UB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tData.u32PosLast.Bytes.MB;
          }
          break;
        }
        
        case PMB_FA_MFR_FUNCTION_CTRL:
        {
          PMBUS_Rte_Read_R_u16FunctionCtrl(&u16TempData.u16Val);
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
        

				/*******************************************************
				 *   Internal PMBus commands ( used by Delta only, need unlock )
				 *******************************************************/
				
				case PMB_C3_TRIM_VOUT:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            WORD_VAL uDataTmp;
            uDataTmp.u16Val = 4095u * 2u - RTE_u16TrimV1Gain.u16Val;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = uDataTmp.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = uDataTmp.Bytes.HB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u16TrimVsbGain.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u16TrimVsbGain.Bytes.HB;
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
				
				case PMB_C4_OVP_TEST_VOUT:
				{
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u16TrimV1GainOvp.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u16TrimV1GainOvp.Bytes.HB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u16TrimVsbGainOvp.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u16TrimVsbGainOvp.Bytes.HB;
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
				}
				
        case PMB_CA_ISHARE_CALIBRATION:
        {
					if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG) 
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_B_PSUCTRL_LS_CALI_MODE;
					}
					break;
        }
        
        case PMB_CF_ORING_TEST:
        {
					if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG) 
					{
						if (RTE_PMB_Read_bit_Vout_V1_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Vout_V1_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
					}
					break;
        }
				
        case PMB_C9_CALIBRATION:
        {
				  if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = LOBYTE(CALI_sPara.sUser.s16Amp);
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = HIBYTE(CALI_sPara.sUser.s16Amp);
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = LOBYTE(CALI_sPara.sUser.s16Ofs);
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = HIBYTE(CALI_sPara.sUser.s16Ofs);
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = LOBYTE(CALI_sPara.sUser.s16Thr);
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = HIBYTE(CALI_sPara.sUser.s16Thr);
						CALI_uStatus.Bits.CALI_READ = FALSE;
          }
					else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
				}
				
				case PMB_CB_READ_TEST_REVISION:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = COM_DEBUG_SW_VERSION; /* Com uC1 */
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u32PmbusFwRevSec1.Bytes.UB; /* Sec uC1 */
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u32PmbusFwRevPri1.Bytes.UB; /* Pri uC1 */
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
        
        case PMB_EB_READ_APP_FW_DUG_REV:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0x03u;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevCom.Bytes.UB;        /* Logic A debug Rev */
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevSec1.Bytes.UB;       /* Sec A Boot Major Rev */
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++]  = RTE_u32PmbusFwRevPri1.Bytes.UB;       /* Pri A Boot Major Rev */
            break;
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
				
				
				case PMB_F0_UNLOCK_FW_UPGRADE_MODE: /* Read to get ECD and Project ID */
        {
					uint8 u8Index;
					
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMB_mg_au8_PROJECT_ID[0];
            for (u8Index = 0; u8Index < 11; u8Index++)
            {
              RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMB_mg_au8_BOOT_FW_ID[u8Index];
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }

        /* Only the unlock and lock key are active,other data are not supported */
        case PMB_F6_UNLOCK_DEBUG:
        {
          if(
              (mg_u16UnlockDebugKey.u16Val == MG_UNLOCK_DEBUG_KEY_UL) ||  /* 'U' = 0x55, 'L' = 0x4C */
              (mg_u16UnlockDebugKey.u16Val == MG_LOCK_DEBUG_KEY_AAAA)     /* Lock */
             )
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_u16UnlockDebugKey.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_u16UnlockDebugKey.Bytes.HB;
          }
          else
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_CFG_I2C_DEFAULT_VAL;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_CFG_I2C_DEFAULT_VAL;
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }

        case PMB_F5_DEBUG_REG:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            if (mg_u16DebugRegIndex.u16Val < RTE_I2C_DEB_BUF_SIZE)
            {
              u16TempData.u16Val = mg_au8DebugRegBuf[mg_u16DebugRegIndex.u16Val].u16Val;
            }
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }

        case PMB_F1_SET_BOOT_FLAG:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_uBootStatus.ALL;
          break;
        }
        default:
        {
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          /* All other commands that not used */
          break;
        }
      }
    }
		else if (mg_u8Page == MG_PAGE_01)
		{
			switch(u8PmbusCommand)
			{
        case PMB_00_PAGE: 
				{
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_u8Page;
          break;
				}
				
        case PMB_20_VOUT_MODE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_VOUT_MODE_LINEAR; /* 0x19 */
          break;
        }
				
        case PMB_40_VOUT_OV_FAULT_LIMIT:
        {
          u16TempData.u16Val = VSB_VOUT_OV_FAULT_LIMIT;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_46_IOUT_OC_FAULT_LIMIT:
        {
          if (RTE_B_PRI_VIN_LINE_LOW) /* Low line input */
          {
            u16TempData.u16Val = VSB_IOUT_OC_FAULT_LIMIT_LL;
          }
          else
          {
            u16TempData.u16Val = VSB_IOUT_OC_FAULT_LIMIT_HL;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_4A_IOUT_OC_WARN_LIMIT:
        {
          if (RTE_B_PRI_VIN_LINE_LOW) /* Low line input */
          {
            u16TempData.u16Val = VSB_IOUT_OC_WARN_LIMIT_HL;
          }
          else
          {
            u16TempData.u16Val = VSB_IOUT_OC_WARN_LIMIT_LL;
          }
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_78_STATUS_BYTE:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u16StatusWordP1.Bytes.LB;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u16StatusWordP1.Bytes.LB;
					}
          break;
        }

        case PMB_79_STATUS_WORD:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u16StatusWordP1.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u16StatusWordP1.Bytes.HB;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u16StatusWordP1.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u16StatusWordP1.Bytes.HB;
					}
          break;
        }
				
        case PMB_7A_STATUS_VOUT:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusVoutP1.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusVoutP1.ALL;
					}
          break;
        }
				
        case PMB_7B_STATUS_IOUT:
        {
					if (PMBUS_uDataUpdStatus1.Bits.STATUS_78_82_UPDTING)
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatusOld.u8StatusIoutP1.ALL;
					}
					else
					{
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_tStatus.u8StatusIoutP1.ALL;
					}
          break;
        }				

        case PMB_8B_READ_VOUT:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
          }
          else
          {
						if (RTE_PMB_Read_bit_Vout_VSB_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Vout_VSB_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
				  }
          break;
        }

        case PMB_8C_READ_IOUT:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
          }
          else
          {
						if (RTE_PMB_Read_bit_Iout_VSB_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Iout_VSB_Linear.u16Val;
						}
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          }
          break;
        }
				
        case PMB_96_READ_POUT:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
          }
          else
          {
						if (RTE_PMB_Read_bit_Pout_VSB_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Pout_VSB_Linear.u16Val;
						}
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          }
          break;
        }

        case PMB_A4_MFR_VOUT_MIN:
        {
          u16TempData.u16Val = MFR_VOUT_VSB_MIN;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A5_MFR_VOUT_MAX:
        {
          u16TempData.u16Val = MFR_VOUT_VSB_MAX;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A6_MFR_IOUT_MAX:
        {
          u16TempData.u16Val = MFR_IOUT_VSB_MAX;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }

        case PMB_A7_MFR_POUT_MAX:
        {
          u16TempData.u16Val = MFR_POUT_VSB_MAX;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
          break;
        }
				default:
				{
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          /* All other commands that not used */
          break;
				}
			}
		}
    else if (mg_u8Page == MG_PAGE_02)
    {
      switch (u8PmbusCommand)
      {
          /* Standard PMBus commands */
        case PMB_00_PAGE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_u8Page;
          break;
        }
				
        case PMB_20_VOUT_MODE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_VOUT_MODE_LINEAR; /* 0x19 */
          break;
        }
				
        case PMB_8B_READ_VOUT:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
          }
          else
          {
						if (RTE_PMB_Read_bit_Vout_IShare_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Vout_V1IShare_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
				  }
          break;
        }
        default:
        {
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          /* All other commands that not used */
          break;
        }
      }
    }
		
    else if (mg_u8Page == MG_PAGE_03)
    {
      switch (u8PmbusCommand)
      {
          /* Standard PMBus commands */
        case PMB_00_PAGE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_u8Page;
          break;
        }
        default:
        {
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          /* All other commands that not used */
          break;
        }
      }
    }
    else if (mg_u8Page == MG_PAGE_04)
    {
      switch (u8PmbusCommand)
      {
          /* Standard PMBus commands */
        case PMB_00_PAGE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_u8Page;
          break;
        }
				
        case PMB_20_VOUT_MODE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = PMBUS_VOUT_MODE_LINEAR; /* 0x19 */
          break;
        }
				
        case PMB_8B_READ_VOUT:
        {
          if (RTE_PMB_Read_bit_Aux_Mode())
          {
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
            RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = 0;
          }
          else
          {
						if (RTE_PMB_Read_bit_Vout_Sense_Upd())
						{
							u16TempData.u16Val = PMBUS_tData.u32DataCopy.Words.LW;
						}
						else
						{
							u16TempData.u16Val = PMBUS_tData.u16Vout_V1Sense_Linear.u16Val;
						}
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.LB;
						RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = u16TempData.Bytes.HB;
				  }
          break;
        }
        default:
        {
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          /* All other commands that not used */
          break;
        }
      }
    }
		/*******************************************************
		 *    PAGE FF
		 *******************************************************/
    else if (mg_u8Page == MG_PAGE_FF)
    {
      switch (u8PmbusCommand)
      {
          /* Standard PMBus commands */
        case PMB_00_PAGE:
        {
          RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = mg_u8Page;
          break;
        }
        default:
        {
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          /* All other commands that not used */
          break;
        }
      }
    }
  } /* end switch */
}/* I2cGetData */

/*******************************************************************************
 * Function:        I2cSetData
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     GUI -> MCU
 *
 ******************************************************************************/
void vPMBus_HandleData(void)
{
  uint8 u8Data0 = 0;
  uint8 u8Data1 = 0;
  uint8 u8Data2 = 0;
  uint8 u8Cnt   = 0;
  uint8 u8RxBufOfst = 0;
  WORD_VAL u16TempData;

  static uint16 u16SysCmdDuty = 0;
	uint8 u8PmbusCommand;

  u8Data0 = RTE_au8I2cRxBuf[1 + u8RxBufOfst];
  u8Data1 = RTE_au8I2cRxBuf[2 + u8RxBufOfst];
  u8Data2 = RTE_au8I2cRxBuf[3 + u8RxBufOfst];

	PMBUS_Rte_Read_R_u8PMBusCmd(&u8PmbusCommand);
	
  if (u8PmbusCommand == PMB_00_PAGE) 
  {
    if ((MG_PAGE_MAX >= u8Data0) || (MG_PAGE_FF == u8Data0))
    {
      mg_u8Page = u8Data0;
    }
    else
    {
      PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;     
    }
  }
  else
  {
    /*************************************************
     *   PAGE 00
     *************************************************/
    if (mg_u8Page == MG_PAGE_00)
    {
      /* Command and byte data received */
      switch (u8PmbusCommand)
      {
				
				/*************************************************************
				 *   Standard PMBus commands
				 *************************************************************/
				/*
				 * Turns on/off power supply. Command argument determines ON/OFF.
				 * Data:
				 * 0000 0000 ? to turn off
				 * 1000 0000 ? to turn on.
				 * The read back should return the last written value.
				 */        
        case PMB_01_OPERATION:
        {
          if(
              (u8Data0 == 0x00u)  ||
              (u8Data0 == 0x80u)
            )
          {
            if (FALSE!= RTE_PMB_Read_bit_Aux_Mode())
            {
              /* Ignore write under VSB_STB_MODE */
            }
            else
            {         
              PMBUS_uOperation.ALL = u8Data0; 
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE; 
          }
          break;
        }
        case PMB_03_CLEAR_FAULTS: /* Register 0x03 (RW) */
        {
          mg_vClearPage00Fault(); /* Clear Faults on page0 */
          break;
        }
  
        case PMB_1B_SMBALERT_MASK:  /* Register 0x1B (RW) */
        {
          switch (u8Data0)
          {
            case PMB_7A_STATUS_VOUT:
            {
              mg_sP0SmbMask.u8Pmb_7A = u8Data1;
              break;
            }
            case PMB_7B_STATUS_IOUT:
            {
              mg_sP0SmbMask.u8Pmb_7B = u8Data1;
              break;
            }
            case PMB_7C_STATUS_INPUT:
            {
              mg_sP0SmbMask.u8Pmb_7C = u8Data1;
              break;
            }
            case PMB_7D_STATUS_TEMPERATURE:
            {
              mg_sP0SmbMask.u8Pmb_7D = u8Data1;
              break;
            }
            case PMB_7E_STATUS_CML:
            {
              mg_sP0SmbMask.u8Pmb_7E = u8Data1;
              break;
            }
            case PMB_7F_STATUS_OTHER:
            {
              mg_sP0SmbMask.u8Pmb_7F = u8Data1;
              break;
            }
						case PMB_80_STATUS_MFR_SPECIFIC:
						{
							mg_sP0SmbMask.u8Pmb_80 = u8Data1;
							break;
						}
            case PMB_81_STATUS_FANS_1_2:
            {
              mg_sP0SmbMask.u8Pmb_81 = u8Data1;
              break;
            }
						case PMB_82_STATUS_FANS_3_4:
						{
							mg_sP0SmbMask.u8Pmb_82 = u8Data1;
							break;
						}
            default:
            {
              PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
              break;
            }
          }
          break;
        }  
        case PMB_3B_FAN_COMMAND_1:
				case PMB_3C_FAN_COMMAND_2:
        {
          /* The power supply fan speed shall remain under PMBus control */
          u16TempData.Bytes.LB = RTE_au8I2cRxBuf[1];
          u16TempData.Bytes.HB = RTE_au8I2cRxBuf[2];
          u16SysCmdDuty = (uint16)mg_s32LinearDatFormatToNormal(u16TempData.u16Val);
          if (u16SysCmdDuty <= 100u)
          {
            PMBUS_tData.u16FanCmd_1_Linear.u16Val = u16TempData.u16Val;
						PMBUS_tData.u16FanCmd_2_Linear.u16Val = u16TempData.u16Val;
            PMBUS_SCFG_vSysSetFanCtrlDuty(0,u16SysCmdDuty);
            PMBUS_SCFG_vSysSetFanCtrlDuty(1u,u16SysCmdDuty); 
            if((u16SysCmdDuty==0)&&(FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG))
            {
              PMBUS_SCFG_vSetFanBlockTest(TRUE);
            }
          }
          break;
        } 
				case PMB_3E_FAN_COMMAND_3:
				case PMB_3F_FAN_COMMAND_4:
				{
					break;
				}	

        case PMB_51_OT_WARN_LIMIT:
        {
          u16TempData.Bytes.LB = RTE_au8I2cRxBuf[1];
          u16TempData.Bytes.HB = RTE_au8I2cRxBuf[2];
          u16TempData.s16Val = (sint16)mg_s32LinearDatFormatToNormal(u16TempData.u16Val);
          /* limit Length Temp */
          if(u16TempData.s16Val  < -10) 
          {
            u16TempData.s16Val  = -10;
          }
          else if(u16TempData.s16Val  > 150) 
          {
            u16TempData.s16Val  = 150;
          }
          PMBUS_Rte_Write_P_s16OtWarning(u16TempData.s16Val);
          PMBUS_SCFG_vSetOtWarnValue(u16TempData.s16Val);
          break;
        }          
				
        case PMB_99_MFR_ID:
        case PMB_9A_MFR_MODEL:
        case PMB_9B_MFR_REVISION:
        case PMB_9C_MFR_LOCATION:
        case PMB_9D_MFR_DATE:
        case PMB_9E_MFR_SERIAL:
        {
           /* save MFR data to eeprom */
					if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            if (16u >= u8Data0) /* check the data nbr limited */
            {
              /* check the data nbr is right */
							for (u8Cnt = 0; u8Cnt < (u8Data0+1); u8Cnt++)
							{
								RTE_au8MfrData[(u8PmbusCommand - PMB_99_MFR_ID)][u8Cnt] = RTE_au8I2cRxBuf[(u8Cnt + 1)];
							}
							RTE_au8MfrData[(u8PmbusCommand - PMB_99_MFR_ID)][16] = u8PmbusCommand;
							RTE_PMB_Write_bit_MFR_Update(TRUE);
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
        /***********************************************************
          *   Non-Standard PMBus commands
        ************************************************************/

				/*************************************************
				 *   Internal PMBus commands need unlock
				 *************************************************/
				/*
				* Write: Trim Data
				* 0x1X: Main output
				* 0x2X: Standby output
				*/
        case PMB_C3_TRIM_VOUT:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            u16TempData.Bytes.LB = u8Data1;
            u16TempData.Bytes.HB = u8Data2;
            if (MG_VOUT_V1 == u8Data0)
            {
              /* V1 trim voltage Gain must (0.8 ~ 1.2) * 4095  */
              if((u16TempData.u16Val <= 4915u) && (u16TempData.u16Val >= 3276u))
              {
                RTE_u16TrimV1Gain.u16Val  = 4095u * 2u - u16TempData.u16Val;
                RTE_B_PSUCTRL_V1_OVP_TEST = FALSE;
                PMBUS_Rte_Write_B_P_V1_TRIM(TRUE);
              }
              else
              {
                PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
              }
            }
            else if (MG_VOUT_VSB == u8Data0)
            {
              /* VSB trim duty must less than 100% */
              if (u16TempData.u16Val <= 1000u)
              {
                RTE_u16TrimVsbGain.u16Val  = u16TempData.u16Val;
                RTE_B_PSUCTRL_VSB_OVP_TEST = FALSE;
                PMBUS_Rte_Write_B_P_VSB_TRIM(TRUE);
              }
              else
              {
                PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
              }
            }
            else
            {
              PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
				/*
				 *  Write: OVP Test
				 */
        case PMB_C4_OVP_TEST_VOUT:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            u16TempData.Bytes.LB = u8Data1;
            u16TempData.Bytes.HB = u8Data2;
            if (MG_VOUT_V1 == u8Data0)
            {
              /* V1 trim voltage Gain must (0.8 ~ 1.2) * 4095  */
              if((u16TempData.u16Val <= 4915u) && (u16TempData.u16Val >= 3276u))
              {
                 RTE_u16TrimV1GainOvp.u16Val  = 4095u * 2u - u16TempData.u16Val;
                 RTE_B_PSUCTRL_V1_OVP_TEST    = TRUE;
              }
              else
              {
                PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
              }
            }
            else if (MG_VOUT_VSB == u8Data0)
            {
              /* VSB trim duty must less than 100% */
              if (u16TempData.u16Val <= 1000u)
              {
                RTE_u16TrimVsbGainOvp.u16Val  = u16TempData.u16Val;
                RTE_B_PSUCTRL_VSB_OVP_TEST    = TRUE;
              }
              else
              {
                PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
              }
            }
            else
            {
              PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
				
        /*
         * Write: Current Share
         * 0x01: xx% load
         * 0x02: xx% load
         * 0x03: xx% load
         * 0x04: xx% load
         */
        case PMB_C5_CURR_SHARE:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            u16TempData.Bytes.LB = u8Data1;
            u16TempData.Bytes.HB = u8Data2;
            if (u16TempData.u16Val < 0xFFFFu)
            {
              PMBUS_uSysStatu1.Bits.I_SHARE_CALI_DONE  = 0;
              PMBUS_uSysStatu1.Bits.I_SHARE_CALI_P1  = 0;
              PMBUS_uSysStatu1.Bits.I_SHARE_CALI_P2  = 0;
              PMBUS_uSysStatu1.Bits.I_SHARE_CALI_P3  = 0;
              PMBUS_uSysStatu1.Bits.I_SHARE_CALI_P4  = 0;
              switch (u8Data0)
              {
                case 0:
                {
                  PMBUS_uSysStatu1.Bits.I_SHARE_CALI_DONE = 1u;
                  break;
                }
                case 1:
                {
                  RTE_sAdjustData.s16V1CurrShareGainP1.s16Val = u16TempData.u16Val;
                  PMBUS_uSysStatu1.Bits.I_SHARE_CALI_P1 = 1u;
                  break;
                }
                case 2:
                {
                  RTE_sAdjustData.s16V1CurrShareGainP2.s16Val = u16TempData.u16Val;
                  PMBUS_uSysStatu1.Bits.I_SHARE_CALI_P2 = 1u;
                  break;
                }
                case 3:
                {
                  RTE_sAdjustData.s16V1CurrShareGainP3.s16Val = u16TempData.u16Val;
                  PMBUS_uSysStatu1.Bits.I_SHARE_CALI_P3 = 1u;
                  break;
                }
                case 4:
                {
                  RTE_sAdjustData.s16V1CurrShareGainP4.s16Val = u16TempData.u16Val;
                  PMBUS_uSysStatu1.Bits.I_SHARE_CALI_P4 = 1u;
                  break;
                }
                default:
                {
                  break;
                }
              }
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
        
        case PMB_C6_NTC_TEST:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
             sint16 s16Tmp;
             if(u8Data0 < RTE_TEMP_TOTAL_NUM )
             {
               s16Tmp = (sint16)u8Data1 - 40;
               PMBUS_Rte_Write_P_s16TempTestValue(s16Tmp,u8Data0);
               PMBUS_Rte_Write_P_u8TempTestIndex(u8Data0);
             }
             else if(u8Data0 == 0xFFu)
             {
               PMBUS_Rte_Write_P_u8TempTestIndex(u8Data0);
             }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
        }
        
        case PMB_C7_OCP_TEST:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
             if(u8Data0 == 0x10 )
             {
               Rte_Write_P_bIsV1OcpTest(TRUE);
             }
             if(u8Data0 == 0x20 )
             {
               Rte_Write_P_bIsVsbOcpTest(TRUE);
             }
             else if(u8Data0 == 0xFFu)
             {
               Rte_Write_P_bIsV1OcpTest(FALSE);
               Rte_Write_P_bIsVsbOcpTest(FALSE);
             }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
        }
				
        case PMB_CA_ISHARE_CALIBRATION:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            if((0 == u8Data0) || (1u == u8Data0))
            {
              RTE_B_PSUCTRL_LS_CALI_MODE = u8Data0;
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
				
        case PMB_CD_TIME_CLEAR:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            u16TempData.Bytes.LB = u8Data0;
            u16TempData.Bytes.HB = u8Data1;
            if(MG_TIME_CLEAR == u16TempData.u16Val)
            {
              RTE_PMBUS_Write_bit_Time_Clear_Enable(TRUE);
            }
            else
            {
              RTE_PMBUS_Write_bit_Time_Clear_Enable(FALSE); 
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
        
        case PMB_CE_AC_CURR_SAVE_FLG:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            u16TempData.Bytes.LB = u8Data0;
            u16TempData.Bytes.HB = u8Data1;
            if(MG_AC_OFFSET_CLEAR == u16TempData.u16Val)
            {
              PMBUS_Rte_Write_B_P_AC_OFFSET_SAVEED(FALSE);
              PMBUS_RTE_Write_B_P_SetAcOffsetValue(0);
            }
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }

        case PMB_DD_MFR_REAL_TIME_BLACK_BOX:
        {
          DWORD_VAL dwTmp;
          
          if(RTE_au8I2cRxBuf[1] == 0x04u)
          {
            dwTmp.Bytes.LB = RTE_au8I2cRxBuf[2];
            dwTmp.Bytes.HB = RTE_au8I2cRxBuf[3];
            dwTmp.Bytes.UB = RTE_au8I2cRxBuf[4];
            dwTmp.Bytes.MB = RTE_au8I2cRxBuf[5];
            PMBUS_SCFG_vSetRealTimeClockDataSystemBlackbox(dwTmp.u32Val);
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
          }
          break;
        }
        case PMB_DE_MFR_SYSTEM_BLCAKBOX:
        {
          if(RTE_au8I2cRxBuf[1] == 40u)
          {
            PMBUS_SCFG_vWriteSystemBlackBox((uint8 *)&RTE_au8I2cRxBuf[2]);
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_DATA = TRUE;
          }

          break;
        }
        case PMB_DF_MFR_BLCAKBOX_CONFIG:
        {
          PMBUS_SCFG_vSetEnableBlackbox(u8Data0);
          break;
        }
        case PMB_E0_MFR_CLEAR_BLACKBOX:
        {
          PMBUS_SCFG_vMFR_ClearBlackBox();
          break;
        }
        
        case PMB_FA_MFR_FUNCTION_CTRL:
        {
          u16TempData.Bytes.LB = u8Data0;
          u16TempData.Bytes.HB = u8Data1;
          PMBUS_Rte_Write_P_u16FunctionCtrl(u16TempData.u16Val);
          break;
        }

        case PMB_F6_UNLOCK_DEBUG:
        {
          mg_u16UnlockDebugKey.Bytes.LB = u8Data0;
          mg_u16UnlockDebugKey.Bytes.HB = u8Data1;
          if (MG_UNLOCK_DEBUG_KEY_UL == mg_u16UnlockDebugKey.u16Val) /* 'L' = 0x55, 'L' = 0x4C */
          {
            PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG = 1u;
          }
          else if (MG_LOCK_DEBUG_KEY_AAAA == mg_u16UnlockDebugKey.u16Val)
          {
            PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG = 0;
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }
          /* Get Debug Register Address. */
        case PMB_F5_DEBUG_REG:
        {
          if (FALSE != PMBUS_uSysStatu0.Bits.UNLOCK_DEBUG)
          {
            mg_u16DebugRegIndex.u16Val = u8Data0;
          }
          else
          {
            PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          }
          break;
        }

				/*********************************************************************
				 *   Bootloader PMBus commands
				 *********************************************************************/
				/* Delta Tiger Q method */

        case PMB_F0_UNLOCK_FW_UPGRADE_MODE: // Register 0xF0 (RW)
        {
					mg_u8BootMcuId = RTE_au8I2cRxBuf[2];
          if (RTE_au8I2cRxBuf[1] == 0x0Cu)// && (RTE_au8I2cRxBuf[14] == 0x01u))
          {
            for (u8Cnt = 0; u8Cnt < 11u; u8Cnt++)
            {
              if (RTE_au8I2cRxBuf[3u + u8Cnt] != PMB_mg_au8_BOOT_FW_ID[u8Cnt])
              {
                break;
              }  
            }
            if (u8Cnt == 11u) /* unlock success */
            {
              mg_uBootStatus.Bits.TRANSMISSIION_ERR = FALSE;
              mg_uBootStatus.Bits.FW_ID_ERR         = FALSE;
              mg_uBootStatus.Bits.UNLOCK_FW_UPGRADE = TRUE;
              PMBUS_uSysStatu1.Bits.CORRECT_BOOT_KEY      = TRUE;
							
							switch(mg_u8BootMcuId)
							{
								case PRI_uC_A:
								{
									mg_uBootStatus.Bits.UC_SELECT_BIT_1 = 0;
									mg_uBootStatus.Bits.UC_SELECT_BIT_0 = 0;
									break;
								}
								case SEC_uC_A:
								{
									mg_uBootStatus.Bits.UC_SELECT_BIT_1 = 0;
									mg_uBootStatus.Bits.UC_SELECT_BIT_0 = 1u;
									break;
								}
								case COM_uC_S:
								{
									mg_uBootStatus.Bits.UC_SELECT_BIT_1 = 1u;
									mg_uBootStatus.Bits.UC_SELECT_BIT_0 = 0;
									break;
								}
								default:
								{
									mg_uBootStatus.Bits.FW_ID_ERR          = TRUE;
									mg_uBootStatus.Bits.UNLOCK_FW_UPGRADE  = FALSE;
									PMBUS_uSysStatu1.Bits.CORRECT_BOOT_KEY = FALSE;
									
									mg_uBootStatus.Bits.UC_SELECT_BIT_1 = 1u;
									mg_uBootStatus.Bits.UC_SELECT_BIT_0 = 1u;
									break;
								}
							}
            }
            else
            {
              /* If unlock fail, set related flag */
              mg_uBootStatus.Bits.FW_ID_ERR          = TRUE;
              mg_uBootStatus.Bits.UNLOCK_FW_UPGRADE  = FALSE;
              PMBUS_uSysStatu1.Bits.CORRECT_BOOT_KEY = FALSE;
            }
          }
          break;
        }
        case PMB_F1_SET_BOOT_FLAG: // Register 0xF1 (RW)
        {
					if (mg_u8BootMcuId == RTE_au8I2cRxBuf[1]) 
					{ 
						/* Should meet two condition to set Jump */
						if (0x01u == (RTE_au8I2cRxBuf[2])
							&& (TRUE == mg_uBootStatus.Bits.UNLOCK_FW_UPGRADE))
						{
							mg_uBootStatus.Bits.TRANSMISSIION_ERR = FALSE;
							/* set busy here, and should not set Bits.BOOT_FLAG here */
							mg_uBootStatus.Bits.BUSY = TRUE;
							PMBUS_uSysStatu1.Bits.BOOT_MODE_JUMP = TRUE;
						}
						else
						{
							mg_uBootStatus.Bits.TRANSMISSIION_ERR = TRUE;
						}
				  }
					else
					{
					  mg_uBootStatus.Bits.TRANSMISSIION_ERR = TRUE;
					}
          break;
        }

        default:/* All commands that not used */
        {
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;;
          /* err: No write */
          break;
				}
			} /* end switch */
		} /* end if*/  
    /*************************************************
    *   PAGE 01
    *************************************************/ 
    else if (mg_u8Page == MG_PAGE_01)
    {
      switch(u8PmbusCommand)
      {    
        case PMB_03_CLEAR_FAULTS:  /* Register 0x03 (RW) */
        {
         mg_vClearPage01Fault();
         break;
        }
				
				case PMB_1B_SMBALERT_MASK: /* Register 0x1B (RW) */
				{
					switch(u8Data0)
					{
						case PMB_7A_STATUS_VOUT:
						{
							mg_sP1SmbMask.u8Pmb_7A = u8Data1;
							break;
						}

						case PMB_7B_STATUS_IOUT:
						{
							mg_sP1SmbMask.u8Pmb_7B = u8Data1;
							break;
						}
						default:
						{
							PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
							break;
						}
					}/* end switch */
					break;
				}/* end case PMB_1B_SMBALERT_MASK*/
        default:
        {
          PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
          break;
        }/* end default */
      }/* end switch */
    }/* end elseif*/

    /*************************************************
    *   PAGE FF
    *************************************************/ 
    else if (mg_u8Page == MG_PAGE_FF)
    {
			switch(u8PmbusCommand)
			{
				case PMB_03_CLEAR_FAULTS:
				{
					mg_vClearPage00Fault();
					mg_vClearPage01Fault();
					break;
				}
				default:
				{
					PMBUS_tStatus.u8StatusCmlP0.Bits.INVALID_CMD = TRUE;
					break;
				}
			}
		}
  }
}/* vPMBus_HandleData*/

void PMBUS_vClearAllFault(void)
{
	mg_vClearPage00Fault();
  mg_vClearPage01Fault();
  PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N  = FALSE;
  PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF      = FALSE;
  PMBUS_tStatus.u16StatusWordP1.Bits.POWER_GOOD_N  = FALSE;
  PMBUS_tStatus.u16StatusWordP1.Bits.UINT_OFF      = FALSE;
	PMBUS_tData.u16FanCmd_1_Linear.u16Val = 0;
	PMBUS_tData.u16FanCmd_2_Linear.u16Val = 0;
}

void PMBUS_vClearPowerOffFault(void)
{
  PMBUS_tStatus.u16StatusWordP0.Bits.POWER_GOOD_N  = FALSE;
  PMBUS_tStatus.u16StatusWordP0.Bits.UINT_OFF      = FALSE;
  PMBUS_tStatus.u16StatusWordP1.Bits.POWER_GOOD_N  = FALSE;
  PMBUS_tStatus.u16StatusWordP1.Bits.UINT_OFF      = FALSE;
}

/********************************************************************************
 * \brief         - PMBUS_BlackBoxSaveData to buffer 1ms cycle
 *
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
void PMBUS_vSaveBlackBoxData2Buff(void)
{
  uint16 u16Dummy = 0;
  PMBUS_SCFG_vCalibrateV1();

  PMBUS_tData.u16Vin_Linear_Box.u16Val = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Vin_Mul_128.u16Val);     
  PMBUS_tData.u16Iin_Linear_Box.u16Val = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Iin_Mul_128.u16Val);
  PMBUS_tData.u16Pin_Linear_Box.u16Val = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u32Pin_Mul_128.u32Val);

  RTE_PMB_Write_u16Vout_V1_Linear_Box(PMBUS_tData.u16Vout_V1_Mul_128_Box.u16Val);

  u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Iout_V1_Mul_128_Box.u16Val);
  RTE_PMB_Write_u16Iout_V1_Linear_Box(u16Dummy);  

  RTE_PMB_Write_u16Vout_VSB_Linear_Box(PMBUS_tData.u16Vout_VSB_Mul_128_Box.u16Val);

  u16Dummy = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Iout_VSB_Mul_128_Box.u16Val);
  RTE_PMB_Write_u16Iout_VSB_Linear_Box(u16Dummy);
}

void PMBUS_vSaveBlackBoxVinData2Buff(void)
{
  PMBUS_tData.u16Vin_Linear_Box.u16Val = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Vin_Mul_128.u16Val);     
  PMBUS_tData.u16Iin_Linear_Box.u16Val = mg_u16TxLinearDatFormatDiv128(PMBUS_tData.u16Iin_Mul_128.u16Val);
  
}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/********************************************************************************
 * \brief         Get linear data format value which devided by 128
 *
 * \param[in]     - u32DataIn
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        - linear data format value / 128
 *
 *******************************************************************************/
static uint16 mg_u16TxLinearDatFormatDiv128(uint32 u32DataIn)
{
  uint16 u16Result = 0;

  if (u32DataIn > N7_LIMIT)
  {
    if (u32DataIn > N11_LIMIT)
    {
      if (u32DataIn > N14_LIMIT) //2^15
      {
        u32DataIn = (u32DataIn + 16384u) >> 15;
        u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N8;
      }
      else if (u32DataIn > N13_LIMIT) //2^14
      {
        u32DataIn = (u32DataIn + 8192u) >> 14;
        u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N7;
      }
      else if (u32DataIn > N12_LIMIT) //2^13
      {
        u32DataIn = (u32DataIn + 4096u) >> 13;
        u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N6;
      }
      else if (u32DataIn > N11_LIMIT) //2^12
      {
        u32DataIn = (u32DataIn + 2048u) >> 12;
        u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N5;
      }
    }
    else if (u32DataIn > N10_LIMIT) //2^11
    {
      u32DataIn = (u32DataIn + 1024u) >> 11;
      u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N4;
    }
    else if (u32DataIn > N9_LIMIT) //2^10
    {
      u32DataIn = (u32DataIn + 512u) >> 10;
      u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N3;
    }
    else if (u32DataIn > N8_LIMIT) //2^9
    {
      u32DataIn = (u32DataIn + 256u) >> 9;
      u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N2;
    }
    else if (u32DataIn > N7_LIMIT) //2^8
    {
      u32DataIn = (u32DataIn + 128u) >> 8;
      u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N1;
    }
  }
  else if (u32DataIn > N3_LIMIT)
  {
    if (u32DataIn > N6_LIMIT) //2^7
    {
      u32DataIn = (u32DataIn + 64u) >> 7;
      u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_N0;
    }
    else if (u32DataIn > N5_LIMIT) //2^6
    {
      u32DataIn = (u32DataIn + 32u) >> 6;
      u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_MN1;
    }
    else if (u32DataIn > N4_LIMIT) //2^5
    {
      u32DataIn = (u32DataIn + 16u) >> 5;
      u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_MN2;
    }
    else if (u32DataIn > N3_LIMIT) //2^4
    {
      u32DataIn = (u32DataIn + 8u) >> 4;
      u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_MN3;
    }
  }
  else if (u32DataIn > N2_LIMIT) // 2^3
  {
    u32DataIn = (u32DataIn + 4u) >> 3;
    u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_MN4;
  }
  else if (u32DataIn > N1_LIMIT) // 2^2
  {
    u32DataIn = (u32DataIn + 2u) >> 2;
    u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_MN5;
  }
  else if (u32DataIn > N0_LIMIT) // 2^1
  {
    u32DataIn = (u32DataIn + 1u) >> 1;
    u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_MN6;
  }
  else // 2^0
  {
    u16Result = (uint16) (u32DataIn & 0x000003FF) + SCALE_MN7;
  }
  return (u16Result);
} /* uiTxLinearDatFormatDiv128() */

/*******************************************************************************
 * \brief          Clear fault or warning status
 *                  ucPage: page0, 1, FF
 *                  ucMode: 1: clear All, and can restart ( OPERATION )
 *                          2: clear All except STA_MFR, and can restart ( PS_ON, PS_KILL )
 *                          3: clear All, and can't restart ( CLEAR_FAULT, CLEAR_BITS )
 *                          4: clear All except STA_MFR, and can't restart
 *
 * \param[in]     -ucPage, ucMode
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vClearPage00Fault(void)
{
  PMBUS_tStatus.u16StatusWordP0.ALL &= 0x840;
  PMBUS_tStatus.u8StatusVoutP0.ALL = 0;
  PMBUS_tStatus.u8StatusIoutP0.ALL = 0;
  PMBUS_tStatus.u8StatusInputP0.ALL = 0;
  PMBUS_tStatus.u8StatusTempP0.ALL = 0;
  PMBUS_tStatus.u8StatusCmlP0.ALL = 0;
  PMBUS_tStatus.u8StatusFan12P0.ALL = 0;
	PMBUS_tStatus.u8StatusFan34P0.ALL = 0;

  PMBUS_tStatusOld.u16StatusWordP0.ALL &= 0x840;
  PMBUS_tStatusOld.u8StatusVoutP0.ALL  = 0;
  PMBUS_tStatusOld.u8StatusIoutP0.ALL  = 0;
  PMBUS_tStatusOld.u8StatusInputP0.ALL = 0;
  PMBUS_tStatusOld.u8StatusTempP0.ALL  = 0;
  PMBUS_tStatusOld.u8StatusCmlP0.ALL   = 0;
  PMBUS_tStatusOld.u8StatusFan12P0.ALL = 0;
	PMBUS_tStatusOld.u8StatusFan34P0.ALL = 0;
  
  PMBUS_Rte_Write_B_P_V1_OVP(FALSE);
  PMBUS_Rte_Write_B_P_V1_UVP(FALSE);
  PMBUS_Rte_Write_B_P_V1_OCP(FALSE);
  PMBUS_Rte_Write_B_P_V1_OCW(FALSE); 
}

/*******************************************************************************
 * \brief          Clear fault or warning status
 *                  ucPage: page0, 1, FF
 *                  ucMode: 1: clear All, and can restart ( OPERATION )
 *                          2: clear All except STA_MFR, and can restart ( PS_ON, PS_KILL )
 *                          3: clear All, and can't restart ( CLEAR_FAULT, CLEAR_BITS )
 *                          4: clear All except STA_MFR, and can't restart
 *
 * \param[in]     -ucPage, ucMode
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vClearPage01Fault(void)
{
  PMBUS_tStatus.u16StatusWordP1.ALL    &= 0x840;
  PMBUS_tStatus.u8StatusVoutP1.ALL     = 0;
  PMBUS_tStatus.u8StatusIoutP1.ALL     = 0;
  PMBUS_tStatusOld.u16StatusWordP1.ALL &= 0x840;
  PMBUS_tStatusOld.u8StatusVoutP1.ALL  = 0;
  PMBUS_tStatusOld.u8StatusIoutP1.ALL  = 0;
  
  PMBUS_Rte_Write_B_P_VSB_OVP(FALSE);
  PMBUS_Rte_Write_B_P_VSB_UVP(FALSE);
  PMBUS_Rte_Write_B_P_VSB_OCP(FALSE);
  PMBUS_Rte_Write_B_P_VSB_OCW(FALSE); 
}

/*******************************************************************************
 * \brief          Clear fault or warning status
 *                  ucPage: page0, 1, FF
 *                  ucMode: 1: clear All, and can restart ( OPERATION )
 *                          2: clear All except STA_MFR, and can restart ( PS_ON, PS_KILL )
 *                          3: clear All, and can't restart ( CLEAR_FAULT, CLEAR_BITS )
 *                          4: clear All except STA_MFR, and can't restart
 *
 * \param[in]     -ucPage, ucMode
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 *******************************************************************************/
static void mg_vClearPageAllFault()
{
  mg_vClearPage00Fault();
  mg_vClearPage01Fault();
}

#if 0
/********************************************************************************
 * \brief         Convert linear data format to normal value which multiply 128
 *
 * \param[in]     - u16DataIn
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        - linear data to normal data multiply 128
 *
 *******************************************************************************/
static uint32 mg_u32LinearDatFormatToNormalMul128(uint16 u16DataIn)
{
  uint8 u8DataN = 0;
  uint32 u32DataY = 0;
  uint32 u32Result = 0;

  u32DataY = u16DataIn & 0x07FFu;
  u32DataY = u32DataY << 7;
  u8DataN = (uint8) ((u16DataIn & 0xF800) >> 11);

  if (u8DataN & 0x10u)
  {
    u32Result = u32DataY >> (0x10u - (u8DataN & 0x0Fu));
  }
  else
  {
    u32Result = u32DataY << (u8DataN & 0x0Fu);
  }
  return (u32Result);
} /* mg_u32LinearDatFormatToNormalMul128() */
#endif

#if 0
/*******************************************************************************
 * Function:        ulLinearDatFormatToNormal
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     linear data to normal data
 *
 ******************************************************************************/
static uint32 mg_u32LinearDatFormatToNormal(uint16 u16DataIn)
{
  uint8 u8DataN = 0;
  uint32 u32DataY = 0;
  uint32 u32Result = 0;

  u32DataY = u16DataIn & 0x07FFu;
  u8DataN = (uint8) ((u16DataIn & 0xF800u) >> 11);

  if (u8DataN & 0x10u)
  {
    u32Result = u32DataY >> (0x10u - (u8DataN & 0x0Fu));
  }
  else
  {
    u32Result = u32DataY << (u8DataN & 0x0Fu);
  }
  return (u32Result);
} /* mg_u32LinearDatFormatToNormal() */
#endif
/*******************************************************************************
 * Function:        ulLinearDatFormatToNormal
 *
 * Parameters:      -
 * Returned value:  -
 *
 * Description:     linear data to normal data
 *
 ******************************************************************************/
static sint32 mg_s32LinearDatFormatToNormal(uint16 u16DataIn)
{
  uint8 u8DataN = 0;
  uint32 u32DataY = 0;
  sint32 s32Result = 0;

  u32DataY = u16DataIn & 0x07FFu;
  
  u8DataN = (uint8) ((u16DataIn & 0xF800u) >> 11);

  if (u8DataN & 0x10u)
  {
    if((u32DataY & 0x400u) == 0)
    {
      s32Result = u32DataY >> (0x10u - (u8DataN & 0x0Fu));
    }
    else
    {
      u32DataY = (0x800 - u32DataY)>> (0x10u - (u8DataN & 0x0Fu));
      s32Result = 0 - (sint32)u32DataY;
    }
  }
  else
  {
    if((u32DataY & 0x400u) == 0)
    {
      s32Result = u32DataY << (u8DataN & 0x0Fu);
    }
    else
    {
      u32DataY = (0x800 - u32DataY) << (u8DataN & 0x0Fu);
      s32Result = 0 - (sint32)u32DataY;
    }
  }
    
  return (s32Result);
} /* mg_u32LinearDatFormatToNormal() */


/*
 * End of file
 */


