#include <stdio.h>
#include "string.h"

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short int sint16;   /* Add for 32bit MCU */
typedef unsigned short int uint16; /* Add for 32bit MCU */
typedef signed long sint32;
typedef unsigned long uint32;
typedef   signed long long     sint64;

#define S32Q19(X)                ((sint32)((X < 0.0F) ? (524288.0F * (X) - 0.5F) : (524288.0F  * (X) + 0.5F)))
#define MG_S16_FAN_CTRL_LOAD_MAX_LL                 ((sint16)1250)
#define MG_S16_FAN_CTRL_LOAD_MAX_HL                 ((sint16)2000)

#define MG_U16_FAN_CTRL_VIN_MAX_SPEED2                 ((sint16)5400)
#define MG_U16_FAN_CTRL_VIN_MIN_SPEED2                 ((sint16)0)
#define MG_U16_FAN_CTRL_MAX_VIN_LL                     ((uint16)(108.0F ))
#define MG_U16_FAN_CTRL_MIN_VIN_LL                     ((uint16)(90.0F ))
#define MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT2            (sint16)((MG_U16_FAN_CTRL_VIN_MAX_SPEED2 - MG_U16_FAN_CTRL_VIN_MIN_SPEED2) \
                                                        / (MG_U16_FAN_CTRL_MAX_VIN_LL - MG_U16_FAN_CTRL_MIN_VIN_LL))
#define MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT2         (sint16)(S32Q19(1.0F) / (MG_S16_FAN_CTRL_LOAD_MAX_LL))

#define MG_U16_FAN_CTRL_VIN_MAX_SPEED1                 ((sint16)5400)
#define MG_U16_FAN_CTRL_VIN_MIN_SPEED1                 ((sint16)0)
#define MG_U16_FAN_CTRL_MAX_VIN_HL                     ((uint16)(208.0F ))
#define MG_U16_FAN_CTRL_MIN_VIN_HL                     ((uint16)(176.0F ))
#define MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT1            (sint16)((MG_U16_FAN_CTRL_VIN_MAX_SPEED1 - MG_U16_FAN_CTRL_VIN_MIN_SPEED1) \
                                                        / (MG_U16_FAN_CTRL_MAX_VIN_HL - MG_U16_FAN_CTRL_MIN_VIN_HL))
#define MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT1          (sint16)(S32Q19(1.0F) / (MG_S16_FAN_CTRL_LOAD_MAX_HL))


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
  sint64 s64Dummy;
  sint32 u32Vin;
  sint32 u32PoutV1;
  uint32 u32FanSpeedAdj;
  uint8 u8VinLine;
  sint32 s32LoadDiff;
  sint32 s16FanCtrlLoadMax;

  sint16 tempAAA;
  uint8 u8VinNormal;

  u32FanSpeedAdj = 5400;
  u32Vin = 220;
  u32PoutV1 = 2000 * 1.3;

  u8VinLine = 0;
  s16FanCtrlLoadMax = 2000;
  u8VinNormal = 218;

  /* Control the fan accoiding to the load */
  s32LoadDiff = (sint32)(u32PoutV1) - (sint32)s16FanCtrlLoadMax;
  s32VinDiff = (sint32)(u8VinNormal) - (sint32)(u32Vin);
  if( TRUE == u8VinLine)
  {		
    if(0 > s32VinDiff)/* Vin > normal */
		{
			if(s32LoadDiff > 0)
      {
        u32FanSpeedAdj += ((sint32)((sint32)((27000 - 0) * 128 / s16FanCtrlLoadMax) * ((sint32)s32LoadDiff))) >> 7u;
      }
      else if(s32LoadDiff >= (-s16FanCtrlLoadMax / 2))/* half load */
			{
				/* max min value need confirm */
				u32FanSpeedAdj += ((sint32)((sint32)((3000 - 0) * 128 / s16FanCtrlLoadMax) * ((sint32)s32LoadDiff))) >> 7u;
			}
			else
			{	
				u32FanSpeedAdj -= 3000 / 2; 
	//		  u32FanSpeedAdj += ((sint32)((sint32)((2200 - 0) * 128 / s16FanCtrlLoadMax) * (-625))) >> 7u;
			}
		}
		else/* Vin < normal */
		{
      if(s32LoadDiff > 0)
      {
        u32FanSpeedAdj += ((sint32)((sint32)((27000 - 0) * 128 / s16FanCtrlLoadMax) * ((sint32)s32LoadDiff))) >> 7u;
      }
      else if(s32LoadDiff >= (-s16FanCtrlLoadMax / 2))/* half load */
      {
        u32FanSpeedAdj += ((sint32)((sint32)((3000 - 0) * 128 / s16FanCtrlLoadMax) * ((sint32)s32LoadDiff))) >> 7u;
      }
      else
      {
        u32FanSpeedAdj -= 3000 / 2; 
      }
		}
  }
  else
  {
		if(0 > s32VinDiff)
		{
			if(s32LoadDiff > 0)
      {
        u32FanSpeedAdj += ((sint32)((sint32)((27000 - 0) * 128 / s16FanCtrlLoadMax) * ((sint32)s32LoadDiff))) >> 7u;
      }
      else if(s32LoadDiff >= (-s16FanCtrlLoadMax / 2))
			{
				u32FanSpeedAdj += ((sint32)((sint32)((3000 - 0) * 128 / s16FanCtrlLoadMax)  * ((sint32)s32LoadDiff))) >> 7u;
			}
			else
			{
				u32FanSpeedAdj -= 3000/2;
			}	
		}
		else
		{
			if(s32LoadDiff > 0)
      {
        u32FanSpeedAdj += ((sint32)((sint32)((27000 - 0) * 128 / s16FanCtrlLoadMax) * ((sint32)s32LoadDiff))) >> 7u;
      }
      else if(s32LoadDiff >= (-s16FanCtrlLoadMax / 2))/* half load */
			{
				u32FanSpeedAdj += ((sint32)((sint32)((3000 - 0) * 128 / s16FanCtrlLoadMax) * ((sint32)s32LoadDiff))) >> 7u;
			}
			else
			{
				u32FanSpeedAdj -= 3000 / 2; 
			}
		}

  }

  s32VinDiff = u8VinNormal-u32Vin;
	if (TRUE == u8VinLine)/* low line */
	{
		if (0 < s32VinDiff)
		{
			s64Dummy = mg_u16LinearCalc(u32Vin, MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT2, \
			                            0, 0, MG_U16_FAN_CTRL_MIN_VIN_LL, MG_U16_FAN_CTRL_MAX_VIN_LL, \
			                            MG_U16_FAN_CTRL_VIN_MIN_SPEED2, MG_U16_FAN_CTRL_VIN_MAX_SPEED2);
			s64Dummy = MG_U16_FAN_CTRL_VIN_MAX_SPEED2 - s64Dummy;
			s64Dummy = (s64Dummy * u32PoutV1 * MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT2) >> 19;
			u32FanSpeedAdj += s64Dummy;
		}
		else
		{
			u32FanSpeedAdj += MG_U16_FAN_CTRL_VIN_MIN_SPEED2;
		}
	}
	else /* high line */
	{
		if (0 < s32VinDiff)
		{
			s64Dummy = mg_u16LinearCalc(u32Vin, MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT1, \
			                            0, 0, MG_U16_FAN_CTRL_MIN_VIN_HL, MG_U16_FAN_CTRL_MAX_VIN_HL, \
			                            MG_U16_FAN_CTRL_VIN_MIN_SPEED1, MG_U16_FAN_CTRL_VIN_MAX_SPEED1);
			s64Dummy = MG_U16_FAN_CTRL_VIN_MAX_SPEED1 - s64Dummy ;
			s64Dummy = (s64Dummy * u32PoutV1 * MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT1) >> 19;
			u32FanSpeedAdj += s64Dummy;
		}
		else
		{
			u32FanSpeedAdj += MG_U16_FAN_CTRL_VIN_MIN_SPEED1;
		}
	}

	if (u32FanSpeedAdj > 18000)
	{
		u32FanSpeedAdj = 18000;
	}

  printf("%d\n",u32FanSpeedAdj);

}