#include <stdio.h>
#include "string.h"
#include "math.h"

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short int sint16;   /* Add for 32bit MCU */
typedef unsigned short int uint16; /* Add for 32bit MCU */
typedef signed long sint32;
typedef unsigned long uint32;

int main(void)
{
/***************计算Hex校验和********************/
  uint8 u8buf[]="10F7EC00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
  uint8 u8len,i;
  uint8 u8sum=0;
  uint8 u8tmp;
  
  u8len = strlen(u8buf);
  for(i=0;i<u8len;i++)
  {
    if(u8buf[i]>0x39)
    {      u8buf[i] = u8buf[i] - 0x30 -0x07;    }
    else
    {      u8buf[i] = u8buf[i] - 0x30;    }
  }
  for(i=0;i<u8len;i += 2)
  {
    u8tmp = (u8buf[i] << 4) + u8buf[i+1];
    u8sum += u8tmp;
  }
  printf("%.2X",0x0100 - u8sum);
}



