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

    switch (u8PmbusCommand)
    {
      /* Standard PMBus commands */
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
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = COM_DEBUG_SW_VERSION;           /* Com uC1 */
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
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u32PmbusFwRevCom.Bytes.UB;  /* Logic A debug Rev */
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u32PmbusFwRevSec1.Bytes.UB; /* Sec A Boot Major Rev */
        RTE_au8I2cTxBuf[RTE_u8I2cTxLen++] = RTE_u32PmbusFwRevPri1.Bytes.UB; /* Pri A Boot Major Rev */
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
      if (
          (mg_u16UnlockDebugKey.u16Val == MG_UNLOCK_DEBUG_KEY_UL) || /* 'U' = 0x55, 'L' = 0x4C */
          (mg_u16UnlockDebugKey.u16Val == MG_LOCK_DEBUG_KEY_AAAA)    /* Lock */
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
  } /* end switch */
} /* I2cGetData */