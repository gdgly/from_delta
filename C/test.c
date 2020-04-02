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







