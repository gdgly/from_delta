  if (MEM_RTE_Read_B_R_VSB_TRIM() != FALSE )
  {
		MEM_RTE_Read_R_uTrimVsbGain(&uTrimGain.u16Val);
    au8EepromWriteBuf[0] = uTrimGain.Bytes.LB;
    au8EepromWriteBuf[1] = uTrimGain.Bytes.HB;
    u8Crc = MEM_CFG_CRC_INIT;
    u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.LB);      /* calculat CRC */
    au8EepromWriteBuf[2] = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.HB);    /*get CRC*/
		if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
		{
			 MEM_Rte_Write_B_R_VSB_TRIM(FALSE);
       MEM_SCFG_vWriteMem(EEP_ADR_VSB_TRIM_LSB, au8EepromWriteBuf, 3u);
		}
  }
	
	if (RTE_B_PSUCTRL_VSB_TRIM_LOW != FALSE)
	{
		uTrimGain.u16Val = RTE_u16TrimVsbGain_LowLoad.u16Val;
    au8EepromWriteBuf[0] = uTrimGain.Bytes.LB;
    au8EepromWriteBuf[1] = uTrimGain.Bytes.HB;
    u8Crc = MEM_CFG_CRC_INIT;
    u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.LB);      /* calculat CRC */
    au8EepromWriteBuf[2] = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.HB);    /*get CRC*/
		if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
		{
			 MEM_Rte_Write_B_R_VSB_TRIM(FALSE);
       MEM_SCFG_vWriteMem(EEP_ADR_VSB_TRIM1_LSB, au8EepromWriteBuf, 3u);
		}	
	}
	
	if (RTE_B_PSUCTRL_VSB_TRIM_HIGH != FALSE)
	{
		uTrimGain.u16Val = RTE_u16TrimVsbGain_HighLoad.u16Val;
    au8EepromWriteBuf[0] = uTrimGain.Bytes.LB;
    au8EepromWriteBuf[1] = uTrimGain.Bytes.HB;
    u8Crc = MEM_CFG_CRC_INIT;
    u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.LB);      /* calculat CRC */
    au8EepromWriteBuf[2] = MEM_SCFG_u8GetCrc8(u8Crc, uTrimGain.Bytes.HB);    /*get CRC*/
		if(MEM_SCFG_u8IsEepromStandbyState() == TRUE)
		{
			 MEM_Rte_Write_B_R_VSB_TRIM(FALSE);
       MEM_SCFG_vWriteMem(EEP_ADR_VSB_TRIM2_LSB, au8EepromWriteBuf, 3u);
		}	
	}


  MEM_SCFG_vReadMem(mg_u8DataBuf,EEP_ADR_VSB_TRIM_LSB, 3u);
  u32EepReadTmp.Bytes.LB = mg_u8DataBuf[0];
  u32EepReadTmp.Bytes.HB = mg_u8DataBuf[1];

  u8Crc = MEM_CFG_CRC_INIT;
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepReadTmp.Bytes.LB);
  u8Crc = MEM_SCFG_u8GetCrc8(u8Crc, u32EepReadTmp.Bytes.HB);
  if (u8Crc != mg_u8DataBuf[2])
  {
    MONCTRL_Rte_Write_P_u16TrimVsbGain(EEP_VSB_TRIM_DEFAULT);
  }
  else
  {
    MONCTRL_Rte_Write_P_u16TrimVsbGain(u32EepReadTmp.Words.LW);
  }


  RTE_u16TrimVsbGain_HighLoad.u16Val = 500;