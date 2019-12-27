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
