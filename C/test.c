#define RTE_B_DIO_HIGH_LINE_ENA RTE_uDioOutStatus.Bits.fa
#define RTE_B_PRI_VIN_LINE_LOW RTE_Pri.u16PriStatus00.Bits.f3 /* 1 = low line */

#define RTE_Read_B_R_VIN_LINE_LOW (RTE_B_PRI_VIN_LINE_LOW)
#define RTE_Read_B_R_VIN_LINE (RTE_B_PRI_VIN_LINE_LOW)
#define RTE_Read_B_R_PRI_VIN_LINE (RTE_B_PRI_VIN_LINE_LOW)

#define RTE_Write_B_P_VIN_LINE_LOW (RTE_B_TO_SEC_STA_VIN_LINE_LOW)

CALI_RTE_W_sData.sVoutV1[u8CaliLine].s16Amp = MG_V_V1_AMP_DEFAULT;
CALI_RTE_R_sData.sVoutV1[0] RTE_CALI_sData
    RTE_CALI_sData

        SINLINE void
        MONCTRL_Rte_Read_R_u16VsbLinearExt(uint16 *var)
{
  Rte_Read_R_u16VsbLinearExt(&var);
}
#define Rte_Read_R_u16VsbLinearExt(var) ((**var) = RTE_u16VoutExtVsbFast)

SINLINE uint16 MONCTRL_SCFG_u16GetVsbExtVolt10mVAvg(void)
{
  return BUFFER_u16GetMean1ms(BUFFER_CFG_E_ExtVsb);
}

PSUCTRL_SCFG_vVsbOvpDuty(u16TrimVsbOvpGainAct);
PSUCTRL_SCFG_vSetVsbOvpPwmOut(TRUE);

RTE_u16TrimVsbGainOvp.u16Val
    RTE_u16TrimVsbGainOvp.u16Val

    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_0, .Mode_Type = GPIO_Mode_AN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource0, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},    /* Inlet NTC */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_1, .Mode_Type = GPIO_Mode_AN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource1, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},    /* Outlet NTC */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_2, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource2, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE},    /* TX of UART2 */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_3, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource3, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE},    /* RX of UART2 */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_4, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource4, .u8GpioAF = GPIO_AF_4, .u8OutState = FALSE},    /* Adjust the VSB voltage */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_5, .Mode_Type = GPIO_Mode_AN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource5, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE},    /* voltage of VSB */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_6, .Mode_Type = GPIO_Mode_AN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource6, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE},    /* current of VSB */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_7, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource7, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE},    /* Reserve */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_8, .Mode_Type = GPIO_Mode_OUT, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource8, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},   /* PSON/L signal to PSU */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_9, .Mode_Type = GPIO_Mode_OUT, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource9, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},   /* LED Green */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_10, .Mode_Type = GPIO_Mode_OUT, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource10, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE}, /* LED Amber */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_11, .Mode_Type = GPIO_Mode_OUT, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource11, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE}, /* Power OK signal to system */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_12, .Mode_Type = GPIO_Mode_OUT, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource12, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE}, /* SMBAlert signal */
    {.u32Perip = RCC_AHBPeriph_GPIOA, .GPIOx = GPIOA, .u16Pin = GPIO_Pin_15, .Mode_Type = GPIO_Mode_OUT, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource15, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE}, /* EEPROM Write Protect */

    /* Port B */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_0, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource0, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},       /* Fault flag of 56V */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_1, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource1, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},       /* Reserve */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_2, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_OD, .GPIO_PuPd = GPIO_PuPd_NOPULL, .u16PinSource = GPIO_PinSource2, .u8GpioAF = GPIO_AF_0, .u8OutState = TRUE},    /* Turn on or off VSB*/
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_3, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource3, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},       /* Vin line */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_4, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource4, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},       /* I2c Address pin1 */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_5, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource5, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},       /* I2c Address pin0 */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_6, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource6, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},       /* TX of UART1*/
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_7, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource7, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},       /* RX of UART1 */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_8, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_OD, .GPIO_PuPd = GPIO_PuPd_NOPULL, .u16PinSource = GPIO_PinSource8, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE},   /* SCL */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_9, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_OD, .GPIO_PuPd = GPIO_PuPd_NOPULL, .u16PinSource = GPIO_PinSource9, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE},   /* SDA */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_10, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_OD, .GPIO_PuPd = GPIO_PuPd_NOPULL, .u16PinSource = GPIO_PinSource10, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE}, /* SCL*/
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_11, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_OD, .GPIO_PuPd = GPIO_PuPd_NOPULL, .u16PinSource = GPIO_PinSource11, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE}, /* SDA */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_12, .Mode_Type = GPIO_Mode_OUT, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource12, .u8GpioAF = GPIO_AF_0, .u8OutState = TRUE},     /* Internal synchronize with second side */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_13, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource13, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},     /* Output VIN OK signal to system */
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_14, .Mode_Type = GPIO_Mode_OUT, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource14, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE},    /* AC OK signal from PFC*/
    {.u32Perip = RCC_AHBPeriph_GPIOB, .GPIOx = GPIOB, .u16Pin = GPIO_Pin_15, .Mode_Type = GPIO_Mode_AF, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource15, .u8GpioAF = GPIO_AF_1, .u8OutState = FALSE},     /* PWM debug */
    /* Port C */
    {.u32Perip = RCC_AHBPeriph_GPIOC, .GPIOx = GPIOC, .u16Pin = GPIO_Pin_13, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource13, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE}, /* RESERVE */
    {.u32Perip = RCC_AHBPeriph_GPIOC, .GPIOx = GPIOC, .u16Pin = GPIO_Pin_14, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource14, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE}, /* RESERVE */
    {.u32Perip = RCC_AHBPeriph_GPIOC, .GPIOx = GPIOC, .u16Pin = GPIO_Pin_15, .Mode_Type = GPIO_Mode_IN, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_UP, .u16PinSource = GPIO_PinSource15, .u8GpioAF = GPIO_AF_0, .u8OutState = FALSE}, /* RESERVE */

    TEMPCTRL_SCFG_u16ReadOutletNtc();

typedef enum BUFFER_CFG_E_INDEX_
{
  BUFFER_CFG_E_ExtVsb = 0,
  BUFFER_CFG_E_IntVsb,
  BUFFER_CFG_E_Isb,
  BUFFER_CFG_E_Vin,
  BUFFER_CFG_E_Iin,
  BUFFER_CFG_E_Pin,
  BUFFER_CFG_E_V1,
  BUFFER_CFG_E_I1,
  BUFFER_CFG_E_P1,
  BUFFER_CFG_E_INDEX_COUNT /* Must be last row!*/
} BUFFER_CFG_E_INDEX;



  mg_vConfigGpioPin(PORT_A, PIN_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC VOLT_OUT_EXT_BUF */
  mg_vConfigGpioPin(PORT_A, PIN_1, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* ADC VOLT_OUT_INT_BUF */
  mg_vConfigGpioPin(PORT_A, PIN_2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /*  */
  mg_vConfigGpioPin(PORT_A, PIN_3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /*  */
  mg_vConfigGpioPin(PORT_A, PIN_4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /*  */
  mg_vConfigGpioPin(PORT_A, PIN_5, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* DAC DAC1_OUT2 */
  mg_vConfigGpioPin(PORT_A, PIN_6, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /*  */
  mg_vConfigGpioPin(PORT_A, PIN_7, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                 /* COMP2 CT current limitation */
  mg_vConfigGpioPin(PORT_A, PIN_8, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_HRTIMER_PWM);    /* PWM AD */
  mg_vConfigGpioPin(PORT_A, PIN_9, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_HRTIMER_PWM);    /* PWM BC */
  mg_vConfigGpioPin(PORT_A, PIN_10, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_HRTIMER_PWM);   /* PWM SR A */
  mg_vConfigGpioPin(PORT_A, PIN_11, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_HRTIMER_PWM);   /*  */
  mg_vConfigGpioPin(PORT_A, PIN_12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                /*  */
  #if (FALSE == DEBUG_MODE)
  mg_vConfigGpioPin(PORT_A, PIN_13, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_SWDIO_SWCLK);   /* SWDIO */
  mg_vConfigGpioPin(PORT_A, PIN_14, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, MG_SWDIO_SWCLK);   /* SWCLK */
  #endif
  mg_vConfigGpioPin(PORT_A, PIN_15, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL, 0);                /*  */




    if (u8BroadcastFlg) 
    {
      /* Read data from buffer */
      uCom2Pri00.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uCom2Pri00.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      uDebugData0Addr.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uDebugData0Addr.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      u1mACurrInOffset.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      u1mACurrInOffset.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      uVoltInCaliAmp.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uVoltInCaliAmp.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      uVoltInCaliOfs.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uVoltInCaliOfs.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      /* Write data to RTE */
      INTCOM_Rte_Write_P_uComStatus00(uCom2Pri00);
      INTCOM_Rte_Write_P_u16DebugData0(*((uint16 *)(uDebugData0Addr.ALL + 0x08000000)));
      INTCOM_Rte_Write_P_1mA_CurrInOffset(u1mACurrInOffset.ALL);
      INTCOM_Rte_Write_P_s16VoltInAmpIntcom(uVoltInCaliAmp.s16Val);
      INTCOM_Rte_Write_P_s16VoltInOfsIntcom(uVoltInCaliOfs.s16Val);
    }
    else
    {
      /* Read data from buffer */
      uCom2Pri00.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uCom2Pri00.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      uDebugData0Addr.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uDebugData0Addr.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      u1mACurrInOffset.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      u1mACurrInOffset.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      uVoltInCaliAmp.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uVoltInCaliAmp.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      uVoltInCaliOfs.Bytes.LB = pau8RxBuf[u16RxBufCnt++];
      uVoltInCaliOfs.Bytes.HB = pau8RxBuf[u16RxBufCnt++];
      /* Write data to RTE */
      INTCOM_Rte_Write_P_uComStatus00(uCom2Pri00);
      INTCOM_Rte_Write_P_u16DebugData0(*((uint16 *)(uDebugData0Addr.ALL + 0x08000000)));
      INTCOM_Rte_Write_P_1mA_CurrInOffset(u1mACurrInOffset.ALL);
      INTCOM_Rte_Write_P_s16VoltInAmpIntcom(uVoltInCaliAmp.s16Val);
      INTCOM_Rte_Write_P_s16VoltInOfsIntcom(uVoltInCaliOfs.s16Val);

RTE_Write_B_P_PRI_RX_PKG = 0
RTE_Write_B_P_PRI_NO_RX_PKG = 1


u32FanSpeedAdj += ((uint32)((sint32)MG_U32_FAN_SCALING_FACT_2 * ((sint32)s32LoadDiff))) >> 7u;


#define MG_FAN_CTRL_BASE_VIN_EN                       1
#define MG_FAN_CTRL_BASE_LOAD1_EN                      1           /* fan ctrl base load enable */
#define MG_FAN_CTRL_BASE_LOAD2_EN                      1           /* fan ctrl base load enable */

  /* 12V Load radio */
#define MG_U16_FAN_CTRL_VIN_MAX_SPEED1              ((sint16)3500)
#define MG_U16_FAN_CTRL_VIN_MIN_SPEED1              ((sint16)0)
#define MG_U16Q12_FAN_CTRL_MAX_VIN                  ((uint16)U32Q12(215.0F / RTE_VIN_MAX))
#define MG_U16Q12_FAN_CTRL_MIN_VIN                  ((uint16)U32Q12(190.0F / RTE_VIN_MAX))
/* Note: the below variable may overflow */
#define MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT1         (sint16)(S32Q8(MG_U16_FAN_CTRL_VIN_MAX_SPEED1 - MG_U16_FAN_CTRL_VIN_MIN_SPEED1) \
                                                      / (MG_U16Q12_FAN_CTRL_MAX_VIN - MG_U16Q12_FAN_CTRL_MIN_VIN))

#define MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT1      (sint16)(S32Q16(1.0F) / (MG_U16_FAN_PSU_FULL_LOAD1))

/* 54V Load radio */
#define MG_U16_FAN_CTRL_VIN_MAX_SPEED2              ((sint16)1100)
#define MG_U16_FAN_CTRL_VIN_MIN_SPEED2              ((sint16)0)
#define MG_U16Q12_FAN_CTRL_MAX_VIN                  ((uint16)U32Q12(215.0F / RTE_VIN_MAX))
#define MG_U16Q12_FAN_CTRL_MIN_VIN                  ((uint16)U32Q12(190.0F / RTE_VIN_MAX))
/* Note: the below variable may overflow */
#define MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT2         (sint16)(S32Q8(MG_U16_FAN_CTRL_VIN_MAX_SPEED2 - MG_U16_FAN_CTRL_VIN_MIN_SPEED2) \
                                                      / (MG_U16Q12_FAN_CTRL_MAX_VIN - MG_U16Q12_FAN_CTRL_MIN_VIN))

#define MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT2      (sint16)(S32Q8(1.0F) / (MG_U16_FAN_PSU_FULL_LOAD2))


PMB_8B_READ_VOUT
PMB_8C_READ_IOUT
PMB_96_READ_POUT
PMB_8D_READ_TEMPERATURE_1
PMB_8E_READ_TEMPERATURE_2
PMB_8F_READ_TEMPERATURE_3


PMB_C3_TRIM_VOUT
PMB_C4_OVP_TEST_VOUT
PMB_C5_CURR_SHARE
PMB_C9_CALIBRATION
PMB_CA_ISHARE_CALIBRATION
PMB_CB_READ_TEST_REVISION
PMB_CF_ORING_TEST
PMB_E2_READ_APP_FW_REVISION
PMB_EB_READ_APP_FW_DUG_REV
PMB_F0_UNLOCK_FW_UPGRADE_MODE
PMB_F1_SET_BOOT_FLAG
PMB_F5_DEBUG_REG
PMB_F6_UNLOCK_DEBUG



typedef union PMBUS_U_BOOT_STATUS_
{
  uint8 ALL;
  struct
  {
    uint8 CHECKSUM_SUCCESS : 1; /* bit0 */
    uint8 MEM_BOUN_ERR : 1;     /* bit1 */
    uint8 ALIGN_ERR : 1;        /* bit2 */
    uint8 KEY_ERR : 1;          /* bit3 */
    uint8 START_ERR : 1;        /* bit4 */
    uint8 RESERVED : 1;         /* bit5 */
    uint8 BOOT_MODE : 1;        /* bit6 */
    uint8 PROGRAM_BUSY : 1;     /* bit7 */
    
  } Bits;
  
} PMBUS_U_BOOT_STATUS;


typedef union PMBUS_U_BOOT_STATUS_
{
  uint8 ALL;
  struct
  { 
    uint8 UC_SELECT_BIT_0     : 1;  /* bit0 */
    uint8 UC_SELECT_BIT_1     : 1;  /* bit1 */
    uint8 BOOT_FLAG           : 1;  /* bit2 */
    uint8 UNLOCK_FW_UPGRADE   : 1;  /* bit3 */
    uint8 BUSY                : 1;  /* bit4 */
    uint8 TRANSMISSIION_ERR   : 1;  /* bit5 */
    uint8 APP_CRC16_ERR       : 1;  /* bit6 */
    uint8 FW_ID_ERR           : 1;  /* bit7 */
  } Bits;
} PMBUS_U_BOOT_STATUS;


switch (u8Cmd)
{
  case PMB_F0_UNLOCK:
  {
    ...
    u8Cmd = PMB_F2_RAM_DATA;
    break;
  }
  case PMB_F1_PSMODE:
  {
    PMBUS_sSysCmd.Cmd = PMB_F1_PSMODE;
    ...
    break;
  }  
  case PMB_F2_RAM_DATA:
  {
    PMBUS_sSysCmd.Cmd = PMB_F2_RAM_DATA;
    ...
    EEP_u8ReadMemory(u32EepAddr, (uint8 *)&PMBUS_sCodeBlock.Buf[0], 16);
    ...
    if (32 == u8BlockNum) //last block
    {
      u8BlockNum = 0;
      u8Cmd = PMB_F3_FLASH_WRITE;
    }
    break;
  }    
  case PMB_F3_FLASH_WRITE:
  {
    PMBUS_sSysCmd.Cmd = PMB_F3_FLASH_WRITE;
    ...
    if (60 == u8PageNum) //last page
    {
      u8Cmd = PMB_F4_CRC16;
    } 
    else
    {
      u8Cmd = PMB_F2_RAM_DATA;
    }      
    break;
  }      
  case PMB_F4_CRC16:
  {
    PMBUS_sSysCmd.Cmd = PMB_F4_CRC16;
    ...        
    u8Cmd = PMB_F1_PSMODE;
    break;
  }
  default:
  {
    u8Cmd = PMB_F0_UNLOCK;
    break;
  }




switch (PMBUS_sSysCmd.Cmd)
{
  case PMB_F0_UNLOCK:
  {
    ...
    break;
  }
  case PMB_F1_PSMODE:
  {
    ...
    break;
  }
  case PMB_F2_RAM_DATA:
  {
    ...
    for (u8ByteCnt = 0; u8ByteCnt < 16; u8ByteCnt++)
    {
      RTE_au8Uart1TxBuf[RTE_u16Uart1TxDataNbr++] = PMBUS_sCodeBlock.Buf[u8ByteCnt];
    }
    break;
  }
  case PMB_F3_FLASH_WRITE:
  {
    ...
    break;
  }
  case PMB_F4_CRC16:
  {
    ...
    break;
  }
  default:
  {
    break;
  }
}




void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != FALSE)
  {
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		(*mg_Uart1RxIsrCallback)(0);
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != FALSE)
  {
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		(*mg_Uart2RxIsrCallback)(1u);
	}
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != FALSE)
  {
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		(*mg_Uart1RxIsrCallback)(1u);
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != FALSE)
  {
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		(*mg_Uart2RxIsrCallback)(0);
	}
}



		/* Vsb trim */
		PSUCTRL_Rte_Read_R_u16TrimVsbGain(&u16TrimVsbGain);
		PSUCTRL_Rte_Read_R_u16TrimVsbGainAct(&u16TrimVsbGainAct);

		if (u16TrimVsbGain != u16TrimVsbGainAct)
		{
			if (u16TrimVsbGain > 1000u) /* Limitation */
			{
				u16TrimVsbGain = 1000u;
				PSUCTRL_Rte_Write_P_u16TrimVsbGain(1000u);
			}

			if (u16TrimVsbGain > u16TrimVsbGainAct)
			{
				if (u16TrimVsbGain > (u16TrimVsbGainAct + 10u))
				{
					u16TrimVsbGainAct += 10u;
				}
				else
				{
					u16TrimVsbGainAct = u16TrimVsbGain;
				}
			}
			else
			{
				if (u16TrimVsbGainAct > (u16TrimVsbGain + 10u))
				{
					u16TrimVsbGainAct -= 10u;
				}
				else
				{
					u16TrimVsbGainAct = u16TrimVsbGain;
				}
			}

			PSUCTRL_Rte_Write_P_u16TrimVsbGainAct(u16TrimVsbGainAct);
			PSUCTRL_SCFG_vVsbTrimDuty(u16TrimVsbGainAct);
		}

		if (u16TrimVsbOvpGainAct > 10u)
		{
			u16TrimVsbOvpGainAct -= 10u;
			PSUCTRL_SCFG_vVsbOvpDuty(u16TrimVsbOvpGainAct);
		}
		/* Vsb PWM duty cover the OVP by severin */
		#if 0
		else
		{
			PSUCTRL_SCFG_vSetVsbOvpPwmOut(FALSE);
		}
		#endif







