#include <stdio.h>
#include "string.h"
#include "math.h"

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
//  FANCTRL_CFG_E_INDEX_FAN1 = 0,
  FANCTRL_CFG_E_INDEX_FAN2 = 5,
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
    uint16 temp:1;
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

#if 0
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
#else
	#define BOOT_BL_PAGE_NUM_START      ((uint16)0)    /* 64 per page */
  #define BOOT_BL_PAGE_NUM_SIZE       ((uint16)192u)
  #define BOOT_BL_PAGE_NUM_END        (BOOT_BL_PAGE_NUM_START + BOOT_BL_PAGE_NUM_SIZE - 1u)   /* 64per page */

  #define BOOT_APP_PAGE_NUM_START     (BOOT_BL_PAGE_NUM_END + 1u)   /* 64 per page */
  #define BOOT_APP_PAGE_NUM_SIZE      ((uint16)512u)
  #define BOOT_APP_PAGE_NUM_END       (BOOT_APP_PAGE_NUM_START + BOOT_APP_PAGE_NUM_SIZE - 1u)  /* 64 per page */
  
  #define BOOT_CRC_BF_PAGE_NUM_START  (BOOT_APP_PAGE_NUM_END + 1u)   /* 64 per page */
  #define BOOT_CRC_BF_PAGE_NUM_SIZE   ((uint16)32u)
  #define BOOT_CRC_BF_PAGE_NUM_END    (BOOT_CRC_BF_PAGE_NUM_START + BOOT_CRC_BF_PAGE_NUM_SIZE - 1u)   /* 64 per page */

  #define BOOT_FLASH_BASE_ADDR        ((uint32)0x08000000u)
  #define BOOT_ADDR_NUM_PER_PAGE      ((uint32)64u)
  #define BOOT_CRC_BF_ADDR_START      (BOOT_FLASH_BASE_ADDR+BOOT_ADDR_NUM_PER_PAGE*BOOT_CRC_BF_PAGE_NUM_START)
  #define BOOT_APP_START_ADDR         (BOOT_FLASH_BASE_ADDR+BOOT_ADDR_NUM_PER_PAGE*BOOT_APP_PAGE_NUM_START)
  #define BOOT_APP_END_ADDR           ((BOOT_FLASH_BASE_ADDR+(uint32)BOOT_ADDR_NUM_PER_PAGE*(BOOT_APP_PAGE_NUM_END+1u))-1u)

  #define BOOT_APP_END_SAVE_ADDR      (BOOT_CRC_BF_ADDR_START +4)
	
  #define BOOT_JUMP_APP_START_ADDR    (BOOT_APP_START_ADDR + (uint32)0x10u)
#endif

uint16 CRC_u16GetCrc16(uint16 u16InCrc, uint8 u8InData)
{
  uint16 u16Crc;

  u16Crc = u16InCrc;
  u16Crc = CRC_mg_au16crc16tab[((u16Crc) ^ (u8InData)) & 0xffu] ^ ((u16Crc) >> 8u);
  return u16Crc;
}


#define S32Q19(X)                ((sint32)((X < 0.0F) ? (524288.0F * (X) - 0.5F) : (524288.0F  * (X) + 0.5F)))
#define MG_S16_FAN_CTRL_LOAD_MAX_LL                 ((sint16)1250)

#define MG_U16_FAN_CTRL_VIN_MAX_SPEED2                 ((sint16)3500)
#define MG_U16_FAN_CTRL_VIN_MIN_SPEED2                 ((sint16)0)
#define MG_U16_FAN_CTRL_MAX_VIN_LL                     ((uint16)(110.0F ))
#define MG_U16_FAN_CTRL_MIN_VIN_LL                     ((uint16)(90.0F ))
#define MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT2            (sint16)((MG_U16_FAN_CTRL_VIN_MAX_SPEED2 - MG_U16_FAN_CTRL_VIN_MIN_SPEED2) \
                                                        / (MG_U16_FAN_CTRL_MAX_VIN_LL - MG_U16_FAN_CTRL_MIN_VIN_LL))

#define MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT2         (sint16)(S32Q19(1.0F) / (MG_S16_FAN_CTRL_LOAD_MAX_LL))
#define LIMIT(A, B, C)           ((A < B) ? (B) : (A > C) ? (C) : (A))

static uint16 mg_u16LinearCalc(sint16 s16X,  sint16 s16K, uint8 u8KQformat, \
sint16 s16B, sint16 s16MinX, sint16 s16MaxX, uint16 u16MinY, uint16 u16MaxY)
{
  sint16 s16Temp = 0;
  if(s16MinX > s16X)
  {
    return(u16MinY);
  }
  else if(s16MaxX < s16X)
  {
    return(u16MaxY);
  }
  else
  {
    s16Temp = ((((sint32)(s16X - s16MinX) * s16K) >> u8KQformat) + s16B);
    s16Temp = LIMIT(s16Temp, u16MinY, u16MaxY);
    return(s16Temp);
  }
} /* mg_u16LinearCalc() */

#define TRUE     1

void Test_Return(uint8* pBuffer, uint32 ReadAddr, uint16 Num)
{
  uint8 i,j=0;
  uint8 RTE[100];
  for(i=0;i<100;i++)
  {
    RTE[i] = i;
  }
  for(i = ReadAddr;i<Num;i++)
  {
    pBuffer[j] = RTE[i];
    j++;
  }
  

}
#define   MG_VSB_MUL_128(X)             ((uint16)(X * 128.0F))

#define MG_F32_PWM_CTRL_KP               2.0000F  /* KP parameter */
#define S32Q8(X)                 ((sint32)((X < 0.0F) ? (256.0F * (X) - 0.5F) : (256.0F * (X) + 0.5F)))
#define MG_S32Q8_PWM_CTRL_KP                ((sint32)S32Q8(MG_F32_PWM_CTRL_KP))
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
  // data.Bits.ff = 1;
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
  // printf("%.8x\n",BOOT_APP_START_ADDR);
  // printf("%.8x\n",BOOT_APP_END_ADDR);
  // printf("%.8x\n",BOOT_CRC_BF_ADDR_START);

//  uint32 u32ErasePageStartAddr;
//  	for(u32ErasePageStartAddr = BOOT_APP_START_ADDR; u32ErasePageStartAddr < BOOT_APP_END_ADDR; u32ErasePageStartAddr += 2048)
// 	{
// 	  printf("%.8x\n",u32ErasePageStartAddr);
// 	}

/****************************************/
/***************计算Hex校验和********************/
  // uint8 u8buf[]="1001C00002480169802211430161704700200240";
  // uint8 u8len,i;
  // uint8 u8sum=0;
  // uint8 u8tmp;
  
  // u8len = strlen(u8buf);
  // for(i=0;i<u8len;i++)
  // {
  //   if(u8buf[i]>0x39)
  //   {      u8buf[i] = u8buf[i] - 0x30 -0x07;    }
  //   else
  //   {      u8buf[i] = u8buf[i] - 0x30;    }
  // }
  // for(i=0;i<u8len;i += 2)
  // {
  //   u8tmp = (u8buf[i] << 4) + u8buf[i+1];
  //   u8sum += u8tmp;
  // }
  // printf("%.2X",0x0100 - u8sum);
/**************************************/
/****************************************************/
  // uint16 a,b,c,d,e;
  // uint16 a2,b2,c2,d2,e2;
  // a = ~0x003F;
  // b = ~0x003C;
  // c = ~0x0003;
  // d = ~0x0009;
  // e = 0x01F0;

  // a2= 0x0009;
  // b2= 0;
  // c2= 0;
  // d2= 0x0008;
  // e2= 0x0020;
  // printf("%.4x\n",a2&(~a));
  // printf("%.4x\n",b2&(~b));
  // printf("%.4x\n",c2&(~c));
  // printf("%.4x\n",d2&(~d));
  // printf("%.4x\n",e2&(~e));
/*********************************************************/
  // uint32 u32a,u32sum;
  // float fb = 1.05;
  // uint8 i,j;

  // u32sum = 0;
  // for(i=1;i<10;i++)
  // {
  //   if(i<10)
  //   {
  //     for(j=1;j<=i;j++)
  //     {
  //       u32sum += (pow(1.05,j) - 1) * 10000; 
  //     }
  //   }
  //   else if(i>=10)
  //   {
  //     for(j=i-10+1;j<=i;j++)
  //     {
  //       u32sum += (pow(1.05,j) - 1) * 10000; 
  //     }
  //   }

  //   printf("%d\n",u32sum);
  // }
/**********************************************/
//  uint16 a = 0x0008;
//  uint16 aa;
//  uint16 b = 0x0008;
//  if( 0 != (a & 0x0009))
//  {
//   aa = b ^ a;
//   b &= aa;

//   printf("%.4x",b);

//  }
/*********************************************/
  // uint8 i;
  // for(i=0;i<1;i++)
  // {
  //   printf("%d",i);
  // }
/********************************/
//   uint16 i;
//   uint32 j,p,q,s;
//   for(i=0;i<100;i++)
//   {
//     p = i;
//     p += BOOT_APP_PAGE_NUM_START;
//     if(p%32 == 0)
//     {
//       j =  BOOT_FLASH_BASE_ADDR + (((uint32)p/32u)<<11);
// //      printf("%d,0x%.8x\n",i,j);
//     }
//     q = BOOT_FLASH_BASE_ADDR+(p*BOOT_ADDR_NUM_PER_PAGE);
//     printf("0x%.8x\n",q);
//   }
//   s = BOOT_FLASH_BASE_ADDR+(p*BOOT_ADDR_NUM_PER_PAGE) + 0x3F;
//   printf("EndAddr = 0x%.8x\n",s);



  // MG_U_UARTPRT_STATUS abc;
  // abc.Bit.u8UartRegErr = 1;
  // printf("%x",abc.ALL);
/******************************/
  // uint8 mg_u8Buff[100] = {0};
  // uint8 i,j;
  // uint8 addr;
  
  // addr=0;
  // for(j=addr;j<addr+20;j+=5)
  // {
  //   Test_Return(&mg_u8Buff[j],0,5);
  // }
  
  
  // for(i=0;i<20;i++)
  // {
  //   printf("%d,",mg_u8Buff[i]);
  // }
  // Test_Return(&mg_u8Buff[5],0,5);
  // printf("\n");
  // for(i=0;i<100;i++)
  // {
  //   printf("%d,",mg_u8Buff[i]);
  // }

  /***********************************/\
  // uint16 y;
  // y = (550 - 500)*(MG_VSB_MUL_128(0.6)- MG_VSB_MUL_128(0.2))/(MG_VSB_MUL_128(0.9) - MG_VSB_MUL_128(0.2)) + 500;
  // printf("%d",y);
/******************************/
  // uint8 a,i;

  // for(i=0;i<30;i++)
  // {
  //   if(i>20)
  //   {
  //     printf("a = %d\n",i);
  //   }
  //   else if(i>11)
  //   {
  //     printf("b = %d\n",i);
  //   }
  //   else if(i<9)
  //   {
  //     printf("c = %d\n",i);
  //   }
  //   else
  //   {
  //     printf("d = %d\n",i);
  //   }
  // }

  // uint16 a,b,i;
  // for(i=0;i<900;i++)
  // {
  //   a =(513-517)*(i-200)/(900-200)+517;
  //   printf("%d, ",a);
  // }
  
  
  printf("%d",MG_S32Q8_PWM_CTRL_KP);

}