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

	uint16 u16TrimVsbGain;
	uint16 u16TrimV1Gain;
	uint16 u16TrimVsbGainAct;
	uint16 u16TrimV1GainAct;
	static uint16 u16TrimVsbOvpGainAct;
  uint16 tmp = 800;

  while(1)
  {
    u16TrimVsbGainAct = tmp;
    u16TrimVsbGain = 0;
		if (u16TrimVsbGain != u16TrimVsbGainAct)
		{

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
    tmp = u16TrimVsbGainAct;
    printf("%d\n",u16TrimVsbGainAct);
  }}



  return 0;
}





















