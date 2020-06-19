/* Incremental PID */

#include <stdio.h>
//#include "graphics.h"

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short int sint16;   /* Add for 32bit MCU */
typedef unsigned short int uint16; /* Add for 32bit MCU */
typedef signed long sint32;
typedef unsigned long uint32;

#define MG_F32_PWM_CTRL_KP               0.5000F  /* KP parameter */
#define MG_F32_PWM_CTRL_KI               0.1000F  /* KP parameter */
#define S32Q8(X)                         ((sint32)((X < 0.0F) ? (256.0F * (X) - 0.5F) : (256.0F * (X) + 0.5F)))
#define MG_S32Q8_PWM_CTRL_KP             ((sint32)S32Q8(MG_F32_PWM_CTRL_KP))
#define MG_S32Q8_PWM_CTRL_KI             ((sint32)S32Q8(MG_F32_PWM_CTRL_KI))

typedef struct PID_Para_
{ 
  uint16 u16Prop;
  uint16 u16Integ;
  uint16 u16Deri;
  uint16 u16limit;
}PID_Para;

typedef struct Error_
{
  sint16 u16CurrError;//当前误差
  sint16 u16LastError;//上一次误差
  sint16 u16PreError;//上上次误差
}Error;
 
/**********************************************
 *  @brief      增量式PID
 *  @since      v1.0
 *  *sptr ：误差参数
 *  *pid:  PID参数
 *  NowPlace：实际值
 *  Point：   期望值
 ****************************************/
sint32 PID_Increase(Error *sptr, PID_Para *pid, uint16 u16NowPlace, uint16 u16Point)
{
	sint32 s32CurrError, s32Increase;

	s32CurrError = u16Point - u16NowPlace;	// 计算当前误差
	s32Increase = (pid->u16Prop * (s32CurrError - sptr->u16LastError) //P
			       + pid->u16Integ * s32CurrError) >>8;//I
#if 0 /* no need for "D" */
			       + pid->D * (iError - 2 * sptr->Last_Error + sptr->Previous_Error);  //D
#endif
	sptr->u16PreError = sptr->u16LastError;	// 更新前次误差
	sptr->u16LastError = s32CurrError;	// 更新上次误差
	
	return s32Increase;
}

void P_Increase(uint16 *u16NowPlace, uint16 u16Point)
{
	sint32 s32CurrError;

	s32CurrError = u16Point - *u16NowPlace;	// 计算当前误差
	if(s32CurrError > 0 )
  {
    *u16NowPlace += 1;
  }
  else
  {
    *u16NowPlace -= 1;
  }
}


int main(void)
{
  PID_Para Test_PID;
  Error Test_Error;
  sint32 a,c;
  uint16 b;
  uint8 i;
  
  Test_Error.u16CurrError = 0;
  Test_Error.u16LastError = 0;
  Test_Error.u16PreError = 0;
  Test_PID.u16Prop = MG_S32Q8_PWM_CTRL_KP;
  Test_PID.u16Integ = MG_S32Q8_PWM_CTRL_KI;

  b = 300;
  c = 0;
  for(i=0;i<100;i++)
  {
    a = PID_Increase(&Test_Error, &Test_PID, b,330);
    c = c+a;
    b = b+c;

//    P_Increase(&b,330);

    printf("%d,",b);
  }


}