#include <stdio.h>

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short int sint16;   /* Add for 32bit MCU */
typedef unsigned short int uint16; /* Add for 32bit MCU */
typedef signed long sint32;
typedef unsigned long uint32;

typedef union PSMI_SHUTDOWN_EVENT
{
  uint16 ALL;

  struct
  {
    uint8 reserve : 1;
    uint8 FAILURE : 1; /* bit0 */
    uint8 OVER_CURRENT : 1; /* bit1 */
    uint8 OVER_TEMPERATURE : 1; /* bit2 */
    uint8 AC_LOSS : 1; /* bit3 */
    uint8 FAN1_FAIL : 2; /* bit4 */
//    uint8 FAN2_FAIL : 1; /* bit5 */
  } Bits;
} PSMI_SHUTDOWN_EVENT;

typedef enum FANCTRL_CFG_E_CONF_INDEX_
{
  FANCTRL_CFG_E_INDEX_FAN1 = 0,
  FANCTRL_CFG_E_INDEX_FAN2,
  FANCTRL_CFG_E_INDEX_COUNT
} FANCTRL_CFG_E_CONF_INDEX;

typedef union PMBUS_U_SYS_BIT_FLAG_
{
  uint16 ALL;
  struct
  {
    uint16 f0:1;
    uint16 f1:1;
    uint16 f2:1;
    uint16 f3:1;
    uint16 f4:1;
    uint16 f5:1;
    uint16 f6:1;
    uint16 f7:1;
    uint16 f8:1;
    uint16 f9:1;
    uint16 fa:1;
    uint16 fb:1;
    uint16 fc:1;
    uint16 fd:1;
    uint16 fe:1;
    uint16 ff:1;
  }Bits;
  struct
  {
    uint8 LB;
    uint8 HB;
  }Bytes;
  uint16 Word;
  } PMBUS_U_SYS_BIT_FLAG;

#define PSMI_lineformat(x,y,z)  (((uint16)x)<<y) + ((x - (uint16)x)*z)
#define AA 2

typedef union MG_U_UARTPRT_STATUS_
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
  uint8 ALL;
} MG_U_UARTPRT_STATUS;

typedef struct MG_S_UARTPRT_DATA_
{
  uint16 u16TxDataCnt;
  uint16 u16RxDataCnt;
  uint16 u16RxByteTmOutCnt;
	uint16 u16RxFrameTmOutCnt;
	uint16 u16TxTmOutCnt;
  uint16 u16TxDataNbr;
  uint16 u16RxDataNbr;
  uint16 u16RxCrc;
  uint8  u8SlaveAddr;
  MG_U_UARTPRT_STATUS uStatus;
} MG_S_UARTPRT_DATA;

static MG_S_UARTPRT_DATA mg_uUartPrtData[2];

#define MG_S16_FAN_CTRL_TEMP_THR_0                  ((sint16)-8)
#define MG_S16_FAN_CTRL_TEMP_THR_1                  ((sint16)5)
#define MG_S16_FAN_CTRL_TEMP_THR_2                  ((sint16)30)
#define MG_S16_FAN_CTRL_TEMP_THR_3                  ((sint16)40)
#define MG_S16_FAN_CTRL_SPEED_THR_1                 ((sint16)5900)
#define MG_S16_FAN_CTRL_SPEED_THR_0                 ((sint16)(0.4 * MG_S16_FAN_CTRL_SPEED_THR_1))
#define MG_S16_FAN_CTRL_SPEED_THR_2                 ((sint16)10000)
#define MG_S16_FAN_CTRL_SPEED_MAX                   ((sint16)23600)
#define MG_S16_FAN_CTRL_SPEED_MIN                   ((sint16)2100)

#define MG_S16_FAN_CTRL_LOAD_MAX                    ((sint16)4000)
#define MG_S16_FAN_CTRL_LOAD_THR_0                  ((sint16)MG_S16_FAN_CTRL_LOAD_MAX * 0.5 )

#define MG_U32_FAN_SCALING_FACT_1                   ((uint32)(MG_S16_FAN_CTRL_SPEED_THR_2 - MG_S16_FAN_CTRL_SPEED_THR_1) \
                                                              / (uint32)(MG_S16_FAN_CTRL_TEMP_THR_3 - MG_S16_FAN_CTRL_TEMP_THR_2))
#define MG_U32_FAN_SCALING_FACT_2                   (((uint32)23600 - (uint32)0.4*5900) << 7 / (uint32)(2000))
#define AAA               (sint16)(S32Q16(1.0F)  / (MG_U16_FAN_PSU_FULL_LOAD1))

int main(void)
{
  // PSMI_SHUTDOWN_EVENT A;
  // A.ALL = 0;
  // A.Bits.FAN1_FAIL = 0x01,
  // printf("0x%02x\n",A.ALL);

  // uint16 a;
  // a = PSMI_lineformat(280,5,32);
  // printf("%x",a);

  //printf("%d",FANCTRL_CFG_E_INDEX_COUNT);

  // PMBUS_U_SYS_BIT_FLAG data;
  // data.ALL = 0x12;
  // printf("%x",data.Word);



  // uint16 s;
  // uint8 t[]={25,40,50};
  // uint8 v[]={90,110};
  // uint8 i,j;

  // for(i=0;i<3;i++)
  // {
  //   for(j=0;j<2;j++)
  //   {
  //     s=((170*((t[i]-30)*(t[i]-30)))>>7)+80*(t[i]-30)+65*(110-v[j])+5867;
  //     printf("%d\n",s);
  //   }
  // }


  sint32 s32LoadDiff;
  uint32 u32FanSpeedAdj = 0;
  s32LoadDiff = (sint32)(3000) - (sint32)MG_S16_FAN_CTRL_LOAD_THR_0;
  u32FanSpeedAdj += ((uint32)((sint32)MG_U32_FAN_SCALING_FACT_2 * ((sint32)s32LoadDiff))) >> 7u;

  printf("%d",MG_U32_FAN_SCALING_FACT_2);

  return 0;
}





















