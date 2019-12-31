#include <stdio.h>

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short int sint16;   /* Add for 32bit MCU */
typedef unsigned short int uint16; /* Add for 32bit MCU */
typedef signed long sint32;
typedef unsigned long uint32;

/*
READ_TEMPERATURE_1
READ_TEMPERATURE_2

READ_FAN_SPEED_1
READ_FAN_SPEED_2

READ_VOUT
READ_IOUT
READ_POUT

READ_AC_VIN
READ_AC_IIN
READ_AC_PIN
*/
/*
PMBUS_SCFG_s16ReadInletTemp() & 0x07FFu
"PMBUS_SCFG_s16ReadInletTemp()"得到的值为实际值
(PMBUS_SCFG_s16ReadSecSr()) & 0x07FFu

((uint32) PMBUS_SCFG_u16ReadFanSpeed(0)) << 7
((uint32) PMBUS_SCFG_u16ReadFanSpeed(1)) << 7

PMBUS_tData.u16Vout_V1_Mul_128.u16Val
PMBUS_tData.u16Iout_V1_Mul_128.u16Val
PMBUS_tData.u32Pout_V1_Mul_128.u32Val

PMBUS_tData.u16Vin_Mul_128.u16Val
PMBUS_tData.u16Iin_Mul_128.u16Val
PMBUS_tData.u32Pin_Mul_128.u32Val
*/

#define SETBIT(ADDRESS, BIT) (ADDRESS |= ((uint16)1 << BIT))
#define CLRBIT(ADDRESS, BIT) (ADDRESS &= ~((uint16)1 << BIT))
#define VOUT_FRC_RESULUTION 					256
#define VOUT_FRC_NUM									8
#define IOUT_FRC_RESULUTION 					64
#define IOUT_FRC_NUM									6
#define POUT_FRC_RESULUTION 					2
#define POUT_FRC_NUM									1
#define VIN_FRC_RESULUTION 						32
#define VIN_FRC_NUM										5
#define IIN_FRC_RESULUTION 						64
#define IIN_FRC_NUM										6
#define PIN_FRC_RESULUTION 						4
#define PIN_FRC_NUM										2
#define FAN_SPEED_FRC_RESULUTION 			1
#define FAN_SPEED_FRC_NUM							0
#define TEMPERATURE_FRC_RESULUTION 		64
#define TEMPERATURE_FRC_NUM						6

/*
static uint16 mg_u16TxLinearDatFormatDiv128_VOUT(uint32 u32DataIn)
{
  uint16 u16Result = 0;
  CLRBIT(u16Result, 15); //SETBIT(u16Result,15);
  uint8 u8Int = 0;
  uint8 u8Fra = 0;

  u8Int = u32DataIn >> 7;
  u8Fra = (u32DataIn - u8Int * 128) * VOUT_FRC_RESULUTION >> 7;

  u16Result += (u8Int << VOUT_FRC_NUM) + u8Fra;
}
*/

static uint16 mg_u16TxLinearDatFormatDiv128_PSMI(uint32 u32DataIn, uint8 u16FrcNum, uint16 u16FrcRes)
{
  uint16 u16Result = 0;
  uint16 u16Int = 0;
  uint16 u16Fra = 0;

  CLRBIT(u16Result, 15);
  u16Int = (u32DataIn >> 7);
  u16Fra = ((u32DataIn - u16Int * 128) * u16FrcRes >> 7);
  u16Result += (u16Int << u16FrcNum) + u16Fra;

  return u16Result;
}

static uint16 mg_u16TxLinearDatFormatDiv128_PSMI_TEMP(sint16 s16DataIn)
{
	uint16 u16Result = 0;
	uint16 u16Int = 0;
	uint16 u16Fra = 0;

	if (s16DataIn >= 0)
	{
		CLRBIT(u16Result, 15);
	}
	else
	{
		SETBIT(u16Result, 15);
	}
	u16Int = (s16DataIn >> 7)& 0x01FF;// 2^(16-1-6)-1
	u16Fra = ((s16DataIn - u16Int * 128) * TEMPERATURE_FRC_RESULUTION >> 7) & 0x3F;
	u16Result += (u16Int << TEMPERATURE_FRC_NUM) + u16Fra;

	return u16Result;
}

static float PSMI_to_float_temp(uint16 u16data)
{
  float a;

  a = ((u16data & 0x003F) >> 6) + (u16data & 0x7FC0)>>6;
  return a;
}

#define AC_IIN_FORMAT(x)        mg_u16TxLinearDatFormatDiv128_PSMI(x,IIN_FRC_NUM,IIN_FRC_RESULUTION)

int main(void)
{
  uint16 a, b, c;
  float ff,f2;
  uint16 vout,iout,pout,vin,iin,pin,fanspeed;
  ff = 24;

  c = mg_u16TxLinearDatFormatDiv128_PSMI_TEMP(ff*128);
  f2 = PSMI_to_float_temp(0x2580);
  printf("%x,%f",c,f2);
  
  // vout = mg_u16TxLinearDatFormatDiv128_PSMI(12*128, VOUT_FRC_NUM, VOUT_FRC_RESULUTION);
  // iout = mg_u16TxLinearDatFormatDiv128_PSMI(1*128, IOUT_FRC_NUM, IOUT_FRC_RESULUTION);
  // pout = mg_u16TxLinearDatFormatDiv128_PSMI(ff*128, POUT_FRC_NUM, POUT_FRC_RESULUTION);
  // vin = mg_u16TxLinearDatFormatDiv128_PSMI(230*128, VIN_FRC_NUM, VIN_FRC_RESULUTION);
  // iin = mg_u16TxLinearDatFormatDiv128_PSMI(ff*128, IIN_FRC_NUM, IIN_FRC_RESULUTION);
  // pin = mg_u16TxLinearDatFormatDiv128_PSMI(ff*128, PIN_FRC_NUM, PIN_FRC_RESULUTION);
  // fanspeed = mg_u16TxLinearDatFormatDiv128_PSMI(6500*128, FAN_SPEED_FRC_NUM, FAN_SPEED_FRC_RESULUTION);
  // printf("vout=%04x,\niout=%04x,\npout=%04x,\nvin=%04x,\niin=%04x,\npin=%04x,\nfanspeed=%04x\n", vout,iout,pout,vin,iin,pin,fanspeed);

  // vin = mg_u16TxLinearDatFormatDiv128_PSMI(279*128,VIN_FRC_NUM, VIN_FRC_RESULUTION);
  // printf("%x",vin);


  return 0;
}