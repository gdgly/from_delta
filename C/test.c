1   (1 == PSUCTRL_RTE_Read_B_R_V1_FAULT_ACTIVE())   ||    /* BULK is not OK */
0   (1 == PSUCTRL_RTE_Read_B_R_PFC_OVP())           ||    /* PFC OVP */
0   (1 == PSUCTRL_RTE_Read_B_R_V1_OVP())            ||    /* V1 OVP*/
0   (1 == PSUCTRL_RTE_Read_B_R_V1_OCP())            ||    /* V1 OCP*/
0   (1 == PSUCTRL_RTE_Read_B_R_V1_SCP())            ||
0   (1 == PSUCTRL_RTE_Read_B_R_V1_UVP())            ||    /* V1 UVP*/
1   (0 == PSUCTRL_RTE_Read_B_R_VIN_OK())            ||    /* Vin is not OK */
0   (1 == PSUCTRL_Rte_Read_B_R_TEMP_ANY_OTP())      ||    /* Any OTP  */
1   (0 == PSUCTRL_RTE_Read_B_R_STA_VSB_ON())        ||    /* Vsb is off */
1   (0 == PSUCTRL_RTE_Read_B_R_REMOTE_ON())         ||    /* PMBus Operation Off/ PSON inactive / PSKILL active */
0   (1 == PSUCTRL_RTE_Read_B_R_AUX_MODE())          ||    /* Aux mode */
0   (1 == PSUCTRL_RTE_Read_B_R_BOOT_RESET_FLAG())   ||    /* Not in bootloader mode */
0   (1 == RTE_B_COM_FAN1_FAIL)                       ||
0   (1 == RTE_B_COM_FAN2_FAIL)

‭10 0000 1011 0000‬                

		    if(u8Test < 5)
				{
				  u8Test ++;
					RTE_u16ComDebug[0] = (PSUCTRL_RTE_Read_B_R_V1_FAULT_ACTIVE()<<13)+(PSUCTRL_RTE_Read_B_R_PFC_OVP()<<12)
					                     +(PSUCTRL_RTE_Read_B_R_V1_OVP()<<11)+(PSUCTRL_RTE_Read_B_R_V1_OCP()<<10)
															 +(PSUCTRL_RTE_Read_B_R_V1_SCP()<<9)+(PSUCTRL_RTE_Read_B_R_V1_UVP()<<8)
															 +(PSUCTRL_RTE_Read_B_R_VIN_OK()<<7)+(PSUCTRL_Rte_Read_B_R_TEMP_ANY_OTP()<<6)
					                     +(PSUCTRL_RTE_Read_B_R_STA_VSB_ON()<<5)+(PSUCTRL_RTE_Read_B_R_REMOTE_ON()<<4)
					                     +(PSUCTRL_RTE_Read_B_R_AUX_MODE()<<3)+(PSUCTRL_RTE_Read_B_R_BOOT_RESET_FLAG()<<2)
					                     +(RTE_B_COM_FAN1_FAIL<<1)+(RTE_B_COM_FAN2_FAIL);
					
				}

#define LIMIT(A, B, C)           ((A < B) ? (B) : (A > C) ? (C) : (A))

if(A < B)
{
  B //取大
}
else
{
  if(A > C)
  {
    C//
  }
  else
  {
    A
  }
  
}


else
{
  if(/* from PSON on to PWOK */
    (TRUE == RTE_Read_B_R_PSON_ACTIVE) &&
    (LEDCTRL_RTE_Read_B_R_VIN_OK() != FALSE) &&
    (LEDCTRL_RTE_Read_B_R_VSB_ON() != FALSE) &&
    (LEDCTRL_SCFG_u8ReadFanBitFail() == FALSE) &&
    (LEDCTRL_RTE_Read_B_R_TEMP_OTP() == FALSE)
  )
  { 
//			LEDCTRL_SCFG_vSetInGREOn();
    LEDCTRL_SCFG_vSetInREDOff();
  }
  else if (/* AC loss */
    (TRUE == RTE_B_COM_NO_VIN)&&(FALSE == RTE_B_PRI_BULK_OK) && (FALSE == RTE_B_PRI_VIN_OK)
  )
  {
    LEDCTRL_SCFG_vSetInGREOff();
    LEDCTRL_SCFG_vSetInREDOff();
  }
  else if(/* when starting VinOK, but Vsb not OK */
    ((LEDCTRL_RTE_Read_B_R_VIN_OK() != FALSE)  &&
    ((LEDCTRL_RTE_Read_B_R_VSB_ON() == FALSE))  &&
    (RTE_Read_B_R_VSB_OVP == FALSE)  &&
    (RTE_Read_B_R_VSB_UVP == FALSE)  &&
    (RTE_Read_B_R_VSB_OCP == FALSE)  &&
    (RTE_Read_B_R_VSB_SCP == FALSE)) ||
    /* when start, Vin OK and Vsb OK, V1 not OK */
    ((LEDCTRL_RTE_Read_R_VMAIN_OK() == FALSE) &&
    (FALSE == LEDCTRL_RTE_Read_B_R_V1_OVP()) &&
    (FALSE == LEDCTRL_RTE_Read_B_R_V1_OCP()) &&
    (FALSE == LEDCTRL_RTE_Read_B_R_V1_UVP()) &&
    (FALSE == LEDCTRL_RTE_Read_B_R_V1_SCP()) &&
    (FALSE == RTE_B_COM_V1_OCP_HICCUP_MODE))
  )
  {
    LEDCTRL_SCFG_vSetInGREOff();
    LEDCTRL_SCFG_vSetInREDOff();
  }
  else
  {
    LEDCTRL_SCFG_vSetInGREOff();
    LEDCTRL_SCFG_vSetInREDOn();
  }
}





