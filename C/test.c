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



#define MG_S16_FAN_CTRL_STAG1_TEMP_MAX_SPEED_LL        ((sint16)20000)//((sint16)24000)//((sint16)16000)
#define MG_S16_FAN_CTRL_STAG1_TEMP_MIN_SPEED_LL        ((sint16)8000)
#define MG_S16_FAN_CTRL_STAG1_TEMP_MAX_SPEED_HL        ((sint16)20000)
#define MG_S16_FAN_CTRL_STAG1_TEMP_MIN_SPEED_HL        ((sint16)10000)
#define MG_S16_FAN_CTRL_STAG1_MAX_TEMP                 ((sint16)60) //((sint16)40)
#define MG_S16_FAN_CTRL_STAG1_MIN_TEMP                 ((sint16)(24))

#define MG_S16_FAN_CTRL_STAG2_TEMP_MAX_SPEED_LL        ((sint16)8000)
#define MG_S16_FAN_CTRL_STAG2_TEMP_MIN_SPEED_LL        ((sint16)6800)
#define MG_S16_FAN_CTRL_STAG2_TEMP_MAX_SPEED_HL        ((sint16)10000)
#define MG_S16_FAN_CTRL_STAG2_TEMP_MIN_SPEED_HL        ((sint16)8900)
#define MG_S16_FAN_CTRL_STAG2_MAX_TEMP                 ((sint16)14)
#define MG_S16_FAN_CTRL_STAG2_MIN_TEMP                 ((sint16)(-1))

#define MG_S16_FAN_CTRL_STAG3_TEMP_MAX_SPEED_LL        ((sint16)6800)
#define MG_S16_FAN_CTRL_STAG3_TEMP_MIN_SPEED_LL        ((sint16)5500)
#define MG_S16_FAN_CTRL_STAG3_TEMP_MAX_SPEED_HL        ((sint16)8900)
#define MG_S16_FAN_CTRL_STAG3_TEMP_MIN_SPEED_HL        ((sint16)6800)
#define MG_S16_FAN_CTRL_STAG3_MAX_TEMP                 ((sint16)-1)
#define MG_S16_FAN_CTRL_STAG3_MIN_TEMP                 ((sint16)(-21))

#define MG_S16_FAN_CTRL_STAG4_TEMP_MAX_SPEED_LL        ((sint16)5500)
#define MG_S16_FAN_CTRL_STAG4_TEMP_MIN_SPEED_LL        ((sint16)2200)
#define MG_S16_FAN_CTRL_STAG4_TEMP_MAX_SPEED_HL        ((sint16)6800)
#define MG_S16_FAN_CTRL_STAG4_TEMP_MIN_SPEED_HL        ((sint16)2720)
#define MG_S16_FAN_CTRL_STAG4_MAX_TEMP                 ((sint16)-21)
#define MG_S16_FAN_CTRL_STAG4_MIN_TEMP                 ((sint16)(-34))







































