#include <stdio.h>

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short int sint16;   /* Add for 32bit MCU */
typedef unsigned short int uint16; /* Add for 32bit MCU */
typedef signed long sint32;
typedef unsigned long uint32;

const uint16 CRC_mg_au16crc16tab[256] = 
{
   0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
   0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
   0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
   0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
   0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
   0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
   0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
   0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
   0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
   0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
   0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
   0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
   0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
   0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
   0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
   0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
   0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
   0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
   0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
   0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
   0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
   0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
   0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
   0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
   0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
   0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
   0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
   0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
   0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
   0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
   0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
   0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

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
#define BOOT_UPDATE_BF_ADDR_START  (BOOT_PEC_STATUS_ADDR_START + 2)

uint16 CRC_u16GetCrc16(uint16 u16InCrc, uint8 u8InData)
{
  uint16 u16Crc;

  u16Crc = u16InCrc;
  u16Crc = CRC_mg_au16crc16tab[((u16Crc) ^ (u8InData)) & 0xffu] ^ ((u16Crc) >> 8u);
  return u16Crc;
}

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


  // sint32 s32LoadDiff;
  // uint32 u32FanSpeedAdj = 0;
  // s32LoadDiff = (sint32)(3000) - (sint32)MG_S16_FAN_CTRL_LOAD_THR_0;
  // u32FanSpeedAdj += ((uint32)((sint32)MG_U32_FAN_SCALING_FACT_2 * ((sint32)s32LoadDiff))) >> 7u;

  // printf("%d",MG_U32_FAN_SCALING_FACT_2);


  // printf("0x%x",BOOT_APP_START_ADDR);

/*****************************************/
  // uint32 u32PageCnt;
  // uint32 u32Loop;
  // uint32 u32DstAddr;
  // uint32 u32ScrAddr;
  // static uint8 mg_u8Buff[2048];
  
  // for (u32PageCnt = 0; u32PageCnt < 32; u32PageCnt++)
  // {
  //   u32DstAddr = BOOT_FLASH_BASE_ADDR + u32PageCnt * 2048;
  //   u32ScrAddr = BOOT_COM_FW_STORED_ADDR;

  //   for (u32Loop = 0; u32Loop < 2048; u32Loop++)
  //   {
  //     mg_u8Buff[u32Loop] = *((uint8 *)u32ScrAddr + u32Loop);
  //   }
/*****************************************/
  // uint16 a,i;
  // uint8 u8Buff[16];
  // for(i=0;i<16;i++)
  // {
  //   u8Buff[i]=i;
  //   printf("%.2x ",u8Buff[i]);
  // }
  // for(i=0;i<16;i++)
  // {
  //   a= CRC_u16GetCrc16(a, u8Buff[i]);
  // }
  // printf("\n0x%x",a);
  // return 0;
/*****************************************/
  printf("%.8x\n",BOOT_CRC_BF_ADDR_START);
  printf("%.8x",BOOT_UPDATE_BF_ADDR_START);
}





















