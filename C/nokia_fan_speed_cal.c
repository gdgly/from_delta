#include <stdio.h>
#include "string.h"

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short int sint16;   /* Add for 32bit MCU */
typedef unsigned short int uint16; /* Add for 32bit MCU */
typedef signed long sint32;
typedef unsigned long uint32;

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

int main(void)
{
  /* cal fan speed nokia sHUB 2kw */
sint32 s32VinDiff;
sint32 s32Dummy;
sint32 u32Vin;
sint32 u32PoutV1;
uint32 u32FanSpeedAdj;
uint8 u8VinLine;
sint32 s32LoadDiff;
sint32 s16FanCtrlLoadMax;

u32FanSpeedAdj = 5500;
u32Vin = 110;
u32PoutV1 = 56 * 20;

  u32FanSpeedAdj = 5500;
  u8VinLine = 1;
  s16FanCtrlLoadMax = 1250;
  /* Control the fan accoiding to the load */
  s32LoadDiff = (sint32)(u32PoutV1) - (sint32)s16FanCtrlLoadMax;
  if( TRUE == u8VinLine)
  {/* max min value need confirm */
      u32FanSpeedAdj += ((sint32)((sint32)((2200-0)*128/1250) * ((sint32)s32LoadDiff))) >> 7u;
  }
  else
  {
      u32FanSpeedAdj += ((sint32)((sint32)((2720-0)*128/2000)  * ((sint32)s32LoadDiff))) >> 7u;	
  }

  s32VinDiff = 110-u32Vin;
  if(0 < s32VinDiff)
  {
    s32Dummy = mg_u16LinearCalc(u32Vin, MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT2,\
                                0,0,MG_U16_FAN_CTRL_MIN_VIN_LL,MG_U16_FAN_CTRL_MAX_VIN_LL,\
                                  MG_U16_FAN_CTRL_VIN_MIN_SPEED2,MG_U16_FAN_CTRL_VIN_MAX_SPEED2);
    s32Dummy = MG_U16_FAN_CTRL_VIN_MAX_SPEED2 - s32Dummy;
    s32Dummy = (s32Dummy * u32PoutV1 * MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT2) >> 19;
    u32FanSpeedAdj += s32Dummy;
  }
  else
  {
    u32FanSpeedAdj += MG_U16_FAN_CTRL_VIN_MIN_SPEED2;
  }	
  printf("%d\n",u32FanSpeedAdj);

}