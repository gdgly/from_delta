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
#define VOUT_FRC_RESULUTION 256
#define VOUT_FRC_NUM 8
#define IOUT_FRC_RESULUTION 64
#define IOUT_FRC_NUM 6
#define POUT_FRC_RESULUTION 2
#define POUT_FRC_NUM 1
#define VIN_FRC_RESULUTION 32
#define VIN_FRC_NUM 5
#define IIN_FRC_RESULUTION 64
#define IIN_FRC_NUM 6
#define PIN_FRC_RESULUTION 4
#define PIN_FRC_NUM 2
#define FAN_SPEED_FRC_RESULUTION 1
#define FAN_SPEED_FRC_NUM 0
#define TEMPERATURE_FRC_RESULUTION 64
#define TEMPERATURE_FRC_NUM 6

static uint16 u16Ones(uint8 x)
{
  uint16 u16Res;
  u16Res = 0;
  while (x--)
  {
    u16Res += 1 << x;
  }
  return u16Res;
}

static uint16 psmi_DataFormat(sint32 s32DataIn, uint16 u16FrcRes)
{
  uint16 u16Result = 0;
  //X = Y/m;
  u16Result = s32DataIn * u16FrcRes >>7;


  return u16Result;
}

static uint16 mg_u16TxLinearDatFormatDiv128_PSMI(sint32 s32DataIn, uint8 u16FrcNum, uint16 u16FrcRes)
{
  uint16 u16Result = 0;
  uint16 u16Int = 0;
  uint16 u16Fra = 0;
  uint16 u16tmp1, u16tmp2;

  u16tmp1 = u16Ones(16 - u16FrcNum);
  u16tmp2 = u16Ones(u16FrcNum);

  if (s32DataIn >= 0)
  {
    u16Int = (s32DataIn >> 7) & u16tmp1;
    u16Fra = ((s32DataIn - u16Int * 128) * u16FrcRes >> 7) & u16tmp2;
  }
  else
  {
    s32DataIn = (~s32DataIn) + 1;
    u16Int = (s32DataIn >> 7) & u16tmp1; // 2^(16-1-6)-1
    u16Fra = ((s32DataIn - u16Int * 128) * u16FrcRes >> 7) & u16tmp2;
    u16Int = (~u16Int) + 1;
  }

  u16Result += ((u16Int & u16tmp1) << u16FrcNum) + u16Fra;

  return u16Result;
}

static uint16 mg_u16TxLinearDatFormatDiv128_PSMI_TEMP(sint16 s16DataIn)
{
  uint16 u16Result = 0;
  uint16 u16Int = 0;
  uint16 u16Fra = 0;

  if (s16DataIn >= 0)
  {
    u16Int = (s16DataIn >> 7) & 0x03FF; // 2^(16-1-6)-1
    u16Fra = ((s16DataIn - u16Int * 128) * TEMPERATURE_FRC_RESULUTION >> 7) & 0x3F;
  }
  else
  {
    s16DataIn = (~s16DataIn) + 1;
    u16Int = (s16DataIn >> 7) & 0x03FF; // 2^(16-1-6)-1
    u16Fra = ((s16DataIn - u16Int * 128) * TEMPERATURE_FRC_RESULUTION >> 7) & 0x3F;
    u16Int = (~u16Int) + 1;
  }

  u16Result += ((u16Int & 0x03FF) << TEMPERATURE_FRC_NUM) + u16Fra;
  return u16Result;
}

/* GUI运行，可以执行float */
static float PsmiData_to_float(uint16 u16data, uint8 u16FrcNum, uint16 u16FrcRes)
{
  float FInt, FFra, FRes;
  uint16 u16Int, u16Fra;

  u16Int = (u16data >> u16FrcNum) & (u16Ones(16 - u16FrcNum));
  u16Fra = (u16data & (u16Ones(u16FrcNum)));
  FFra = (float)u16Fra / u16FrcRes;

  if (u16data & 0x8000)
  {
    //neg
    u16Int = ((~u16Int) + 1) & (u16Ones(16 - u16FrcNum));
    FInt = ((float)u16Int) * (-1);
    FFra = FFra * (-1);
  }
  else
  {
    //pos
    FInt = u16Int;
  }
  FRes = FInt + FFra;
  return FRes;
}

static float Psmi_to_float(uint16 u16data, uint16 u16FrcRes)
{
  float f_res;
  if(u16data & 0x8000)
  {
    //f_res = sint16(u16data)
  }
  else
  {
    f_res = (float)u16data /u16FrcRes;
  }
  return f_res;
}

int main(void)
{
  uint16 a, b, c;
  float ff, f2 ,f3;
  uint16 vout, iout, pout, vin, iin, pin, fanspeed;
  ff = -3.3 * 128;

  c = mg_u16TxLinearDatFormatDiv128_PSMI_TEMP((sint16)ff);
  f2 = Psmi_to_float(c,TEMPERATURE_FRC_RESULUTION);

  printf("%x,%f\n", c, f2);
  // c = mg_u16TxLinearDatFormatDiv128_PSMI(3.4*128, VOUT_FRC_NUM, VOUT_FRC_RESULUTION);
  // f2 = PsmiData_to_float(c,VOUT_FRC_NUM,VOUT_FRC_RESULUTION);

  // c = mg_u16TxLinearDatFormatDiv128_PSMI(-230*128, VIN_FRC_NUM, VIN_FRC_RESULUTION);
  // f2 = PsmiData_to_float(c,VIN_FRC_NUM,VIN_FRC_RESULUTION);

  // c = mg_u16TxLinearDatFormatDiv128_PSMI(-3.3*128, IOUT_FRC_NUM, IOUT_FRC_RESULUTION);
  // f2 = PsmiData_to_float(c,IOUT_FRC_NUM,IOUT_FRC_RESULUTION);

  // c = mg_u16TxLinearDatFormatDiv128_PSMI(-3.3*128, IIN_FRC_NUM, IIN_FRC_RESULUTION);
  // f2 = PsmiData_to_float(c,IIN_FRC_NUM,IIN_FRC_RESULUTION);

  // c = mg_u16TxLinearDatFormatDiv128_PSMI(-3.6*128, POUT_FRC_NUM, POUT_FRC_RESULUTION);
  // f2 = PsmiData_to_float(c,POUT_FRC_NUM,POUT_FRC_RESULUTION);

  // c = mg_u16TxLinearDatFormatDiv128_PSMI(-3.3*128, PIN_FRC_NUM, PIN_FRC_RESULUTION);
  // f2 = PsmiData_to_float(c,PIN_FRC_NUM,PIN_FRC_RESULUTION);

  // c = mg_u16TxLinearDatFormatDiv128_PSMI(6500*128, FAN_SPEED_FRC_NUM, FAN_SPEED_FRC_RESULUTION);
  // f2 = PsmiData_to_float(c,FAN_SPEED_FRC_NUM,FAN_SPEED_FRC_RESULUTION);

  return 0;
}