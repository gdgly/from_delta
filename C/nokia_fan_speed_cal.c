#include <stdio.h>
#include "string.h"

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short int sint16;   /* Add for 32bit MCU */
typedef unsigned short int uint16; /* Add for 32bit MCU */
typedef signed long sint32;
typedef unsigned long uint32;
typedef   signed long long     sint64;

#define LIMIT(A, B, C)           ((A < B) ? (B) : (A > C) ? (C) : (A))

#define S32Q19(X)                ((sint32)((X < 0.0F) ? (524288.0F * (X) - 0.5F) : (524288.0F  * (X) + 0.5F)))
#define MG_S16_FAN_CTRL_LOAD_MAX_LL                 ((sint16)1250)
#define MG_S16_FAN_CTRL_LOAD_MAX_HL                 ((sint16)2000)
#define MG_S16_FAN_CTRL_SPEED_MAX                   ((sint16)18000)
#define MG_S16_FAN_CTRL_STAG1_TEMP_MAX_SPEED_LL        ((sint16)MG_S16_FAN_CTRL_SPEED_MAX)
#define MG_S16_FAN_CTRL_STAG1_TEMP_MIN_SPEED_LL        ((sint16)9000)
#define MG_S16_FAN_CTRL_STAG1_TEMP_MAX_SPEED_HL        ((sint16)MG_S16_FAN_CTRL_SPEED_MAX)
#define MG_S16_FAN_CTRL_STAG1_TEMP_MIN_SPEED_HL        ((sint16)9000)
#define MG_S16_FAN_CTRL_STAG1_MAX_TEMP                 ((sint16)55)
#define MG_S16_FAN_CTRL_STAG1_MIN_TEMP                 ((sint16)(28))

#define MG_S16_FAN_CTRL_STAG2_TEMP_MAX_SPEED_LL        ((sint16)9000)
#define MG_S16_FAN_CTRL_STAG2_TEMP_MIN_SPEED_LL        ((sint16)6800)
#define MG_S16_FAN_CTRL_STAG2_TEMP_MAX_SPEED_HL        ((sint16)9000)
#define MG_S16_FAN_CTRL_STAG2_TEMP_MIN_SPEED_HL        ((sint16)6800)
#define MG_S16_FAN_CTRL_STAG2_MAX_TEMP                 ((sint16)25)
#define MG_S16_FAN_CTRL_STAG2_MIN_TEMP                 ((sint16)(18))

#define MG_S16_FAN_CTRL_STAG3_TEMP_MAX_SPEED_LL        ((sint16)6800)
#define MG_S16_FAN_CTRL_STAG3_TEMP_MIN_SPEED_LL        ((sint16)5600)
#define MG_S16_FAN_CTRL_STAG3_TEMP_MAX_SPEED_HL        ((sint16)6800)
#define MG_S16_FAN_CTRL_STAG3_TEMP_MIN_SPEED_HL        ((sint16)5600)
#define MG_S16_FAN_CTRL_STAG3_MAX_TEMP                 ((sint16)15)
#define MG_S16_FAN_CTRL_STAG3_MIN_TEMP                 ((sint16)(3))

#define MG_S16_FAN_CTRL_STAG4_TEMP_MAX_SPEED_LL        ((sint16)5600)
#define MG_S16_FAN_CTRL_STAG4_TEMP_MIN_SPEED_LL        ((sint16)3000)
#define MG_S16_FAN_CTRL_STAG4_TEMP_MAX_SPEED_HL        ((sint16)5600)
#define MG_S16_FAN_CTRL_STAG4_TEMP_MIN_SPEED_HL        ((sint16)3000)
#define MG_S16_FAN_CTRL_STAG4_MAX_TEMP                 ((sint16)-20)
#define MG_S16_FAN_CTRL_STAG4_MIN_TEMP                 ((sint16)(-33))

#define MG_U16_FAN_CTRL_VIN_MAX_SPEED2                 ((sint16)3750)
#define MG_U16_FAN_CTRL_VIN_MIN_SPEED2                 ((sint16)0)
#define MG_U16_FAN_CTRL_MAX_VIN_LL                     ((uint16)(105.0F ))
#define MG_U16_FAN_CTRL_MIN_VIN_LL                     ((uint16)(90.0F ))
#define MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT2            (sint16)((MG_U16_FAN_CTRL_VIN_MAX_SPEED2 - MG_U16_FAN_CTRL_VIN_MIN_SPEED2) \
                                                        / (MG_U16_FAN_CTRL_MAX_VIN_LL - MG_U16_FAN_CTRL_MIN_VIN_LL))
#define MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT2         (sint16)(S32Q19(1.0F) / (MG_S16_FAN_CTRL_LOAD_MAX_LL))

#define MG_U16_FAN_CTRL_VIN_MAX_SPEED1                 ((sint16)3750)
#define MG_U16_FAN_CTRL_VIN_MIN_SPEED1                 ((sint16)0)
#define MG_U16_FAN_CTRL_MAX_VIN_HL                     ((uint16)(205.0F ))
#define MG_U16_FAN_CTRL_MIN_VIN_HL                     ((uint16)(176.0F ))
#define MG_U16Q8_FAN_CTRL_VIN_SCALING_FACT1            (sint16)((MG_U16_FAN_CTRL_VIN_MAX_SPEED1 - MG_U16_FAN_CTRL_VIN_MIN_SPEED1) \
                                                        / (MG_U16_FAN_CTRL_MAX_VIN_HL - MG_U16_FAN_CTRL_MIN_VIN_HL))
#define MG_U16Q8_FAN_CTRL_VIN_LOAD_RADIO_FACT1          (sint16)(S32Q19(1.0F) / (MG_S16_FAN_CTRL_LOAD_MAX_HL))

#define TRUE      1
#define LOWLINE   1
#define HIGHLINE  0

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

	sint16 s16FanStag1TempFact;
	sint16 s16FanStag2TempFact;
	sint16 s16FanStag3TempFact;
	sint16 s16FanStag4TempFact;
	sint16 s16FanStag1SpeedMax;
	sint16 s16FanStag2SpeedMax;
	sint16 s16FanStag3SpeedMax;
	sint16 s16FanStag4SpeedMax;
	sint16 s16FanStag1SpeedMin;
	sint16 s16FanStag2SpeedMin;
	sint16 s16FanStag3SpeedMin;
	sint16 s16FanStag4SpeedMin;

  sint16 tempInlet;
  uint8 u8VinNormal;
	volatile sint32 s32Dummy;
	sint32 s32TempDiff;
	volatile sint16 MG_S16_FAN_CTRL_TEMP;

  u32Vin = 90;
  u32PoutV1 = 1250 * 1.3;
  tempInlet = 25;
  
  if(u32Vin > 150)
  {
    u8VinLine = HIGHLINE;
  }
  else
  {
    u8VinLine = LOWLINE;
  }  

	if (LOWLINE == u8VinLine)/* low line */
	{
		s16FanStag1SpeedMax = MG_S16_FAN_CTRL_STAG1_TEMP_MAX_SPEED_LL;
		s16FanStag2SpeedMax = MG_S16_FAN_CTRL_STAG2_TEMP_MAX_SPEED_LL;
		s16FanStag3SpeedMax = MG_S16_FAN_CTRL_STAG3_TEMP_MAX_SPEED_LL;
		s16FanStag4SpeedMax = MG_S16_FAN_CTRL_STAG4_TEMP_MAX_SPEED_LL;

		s16FanStag1SpeedMin = MG_S16_FAN_CTRL_STAG1_TEMP_MIN_SPEED_LL;
		s16FanStag2SpeedMin = MG_S16_FAN_CTRL_STAG2_TEMP_MIN_SPEED_LL;
		s16FanStag3SpeedMin = MG_S16_FAN_CTRL_STAG3_TEMP_MIN_SPEED_LL;
		s16FanStag4SpeedMin = MG_S16_FAN_CTRL_STAG4_TEMP_MIN_SPEED_LL;

		s16FanCtrlLoadMax = MG_S16_FAN_CTRL_LOAD_MAX_LL;
		u8VinNormal = 110 - 5;
	}
	else/* high line */
	{
		s16FanStag1SpeedMax = MG_S16_FAN_CTRL_STAG1_TEMP_MAX_SPEED_HL;
		s16FanStag2SpeedMax = MG_S16_FAN_CTRL_STAG2_TEMP_MAX_SPEED_HL;
		s16FanStag3SpeedMax = MG_S16_FAN_CTRL_STAG3_TEMP_MAX_SPEED_HL;
		s16FanStag4SpeedMax = MG_S16_FAN_CTRL_STAG4_TEMP_MAX_SPEED_HL;

		s16FanStag1SpeedMin = MG_S16_FAN_CTRL_STAG1_TEMP_MIN_SPEED_HL;
		s16FanStag2SpeedMin = MG_S16_FAN_CTRL_STAG2_TEMP_MIN_SPEED_HL;
		s16FanStag3SpeedMin = MG_S16_FAN_CTRL_STAG3_TEMP_MIN_SPEED_HL;
		s16FanStag4SpeedMin = MG_S16_FAN_CTRL_STAG4_TEMP_MIN_SPEED_HL;

		s16FanCtrlLoadMax = MG_S16_FAN_CTRL_LOAD_MAX_HL;
		u8VinNormal	= 220 - 5;
	}

	s16FanStag1TempFact = (sint16)((s16FanStag1SpeedMax - s16FanStag1SpeedMin) / (MG_S16_FAN_CTRL_STAG1_MAX_TEMP - MG_S16_FAN_CTRL_STAG1_MIN_TEMP));
	s16FanStag2TempFact = (sint16)((s16FanStag2SpeedMax - s16FanStag2SpeedMin) / (MG_S16_FAN_CTRL_STAG2_MAX_TEMP - MG_S16_FAN_CTRL_STAG2_MIN_TEMP));
	s16FanStag3TempFact = (sint16)((s16FanStag3SpeedMax - s16FanStag3SpeedMin) / (MG_S16_FAN_CTRL_STAG3_MAX_TEMP - MG_S16_FAN_CTRL_STAG3_MIN_TEMP));
	s16FanStag4TempFact = (sint16)((s16FanStag4SpeedMax - s16FanStag4SpeedMin) / (MG_S16_FAN_CTRL_STAG4_MAX_TEMP - MG_S16_FAN_CTRL_STAG4_MIN_TEMP));

  MG_S16_FAN_CTRL_TEMP = tempInlet-25;
  s32TempDiff = tempInlet-25;
	if (28 <= MG_S16_FAN_CTRL_TEMP)
	{
		/*Temp > 53,stag1*/
		s32Dummy = mg_u16LinearCalc(s32TempDiff, s16FanStag1TempFact, \
		                            0, s16FanStag1SpeedMin, MG_S16_FAN_CTRL_STAG1_MIN_TEMP, MG_S16_FAN_CTRL_STAG1_MAX_TEMP, \
		                            s16FanStag1SpeedMin, s16FanStag1SpeedMax);

		u32FanSpeedAdj += (uint16) s32Dummy;
	}
  else if((25 <= MG_S16_FAN_CTRL_TEMP)&&(28 > MG_S16_FAN_CTRL_TEMP))
  { /* 50 < Temp < 53*/
    u32FanSpeedAdj += 9000;
  }
	else if ((18 <= MG_S16_FAN_CTRL_TEMP) && (25 > MG_S16_FAN_CTRL_TEMP))
	{
		/* 43 < Temp < 50,,stag2*/
		s32Dummy = mg_u16LinearCalc(s32TempDiff, s16FanStag2TempFact, \
		                            0, s16FanStag2SpeedMin, MG_S16_FAN_CTRL_STAG2_MIN_TEMP, MG_S16_FAN_CTRL_STAG2_MAX_TEMP, \
		                            s16FanStag2SpeedMin, s16FanStag2SpeedMax);

		u32FanSpeedAdj += (uint16) s32Dummy;
	}
  else if((15 <= MG_S16_FAN_CTRL_TEMP)&&(18 > MG_S16_FAN_CTRL_TEMP))
  {/* 40 < Temp < 43*/
    u32FanSpeedAdj += 6800;
  }
	else if ((3 <= MG_S16_FAN_CTRL_TEMP) && (15 > MG_S16_FAN_CTRL_TEMP))
	{
		/*When 28 < Amb Temp <40°C,,stag3 */
		s32Dummy = mg_u16LinearCalc(s32TempDiff, s16FanStag3TempFact, \
		                            0, s16FanStag3SpeedMin, MG_S16_FAN_CTRL_STAG3_MIN_TEMP, MG_S16_FAN_CTRL_STAG3_MAX_TEMP, \
		                            s16FanStag3SpeedMin, s16FanStag3SpeedMax);

		u32FanSpeedAdj += (uint16) s32Dummy;
	}
  else if((0 <= MG_S16_FAN_CTRL_TEMP)&&(3 > MG_S16_FAN_CTRL_TEMP))
  {/* 25 < Temp < 28*/
    u32FanSpeedAdj += 5600;
  }
	else if ((-20 <= MG_S16_FAN_CTRL_TEMP) && (0 > MG_S16_FAN_CTRL_TEMP))
	{
		/*When 5 < Amb Temp <25°C */
		u32FanSpeedAdj += s16FanStag4SpeedMax;
	}
	else if ((-33 < MG_S16_FAN_CTRL_TEMP) && (-20 > MG_S16_FAN_CTRL_TEMP))
	{
		/* -8°C < When Amb Temp < 5°C ,stag4*/
		s32Dummy = mg_u16LinearCalc(s32TempDiff, s16FanStag4TempFact, \
		                            0, s16FanStag4SpeedMin, MG_S16_FAN_CTRL_STAG4_MIN_TEMP, MG_S16_FAN_CTRL_STAG4_MAX_TEMP, \
		                            s16FanStag4SpeedMin, s16FanStag4SpeedMax);

		u32FanSpeedAdj += (uint16) s32Dummy;
	}
	else if (-34 > MG_S16_FAN_CTRL_TEMP)
	{
		/* When Amb Temp < -8°C */
		u32FanSpeedAdj += s16FanStag4SpeedMin;
	}

 printf("%d\n",u32FanSpeedAdj);
  /* Control the fan accoiding to the load */
  uint8 u8LoadOffset;
  if(TRUE == u8VinLine)
  {
    u8LoadOffset = 34;
  }
  else
  {
    u8LoadOffset = 54;
  }
  
  s32LoadDiff = (sint32)(u32PoutV1) - (sint32)(s16FanCtrlLoadMax);
  s32VinDiff = (sint32)(u8VinNormal) - (sint32)(u32Vin);
  if( TRUE == u8VinLine)
  {		
    if(0 > s32VinDiff)/* Vin > normal */
		{
//			if(s32LoadDiff > 0)
      if(s32LoadDiff > 0.03*s16FanCtrlLoadMax)
      {
        s32LoadDiff -= u8LoadOffset;
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
      if(s32LoadDiff > 0.03*s16FanCtrlLoadMax)
      {
        s32LoadDiff -= u8LoadOffset;
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
      if(s32LoadDiff > 0.03*s16FanCtrlLoadMax)
      {
        s32LoadDiff -= u8LoadOffset;
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
      if(s32LoadDiff > 0.03*s16FanCtrlLoadMax)
      {
        s32LoadDiff -= u8LoadOffset;
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
 printf("%d\n",u32FanSpeedAdj);
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