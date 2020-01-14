/** *****************************************************************************
 * \file    global.h
 * \brief   Common definitions
 *
 * \section AUTHOR
 *    1. HDC Software Team
 *    2. BDC Software Team
 *
 * \section SVN
 *  $Date$
 *  $Author$
 *  $Revision$
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

#ifndef GLOBAL_H
#define GLOBAL_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/* Logic state definition */
#ifndef FALSE
  #define FALSE                  0
#endif

#ifndef TRUE
  #define TRUE                   (!FALSE)
#endif

#ifndef LOW
  #define LOW                    0
#endif

#ifndef HIGH
  #define HIGH                   (!LOW)
#endif

#ifndef OFF
  #define OFF                    0
#endif

#ifndef ON
  #define ON                     (!OFF)
#endif

#ifndef DOWN
  #define DOWN                   0
#endif

#ifndef UP
  #define UP                     (!DOWN)
#endif

#ifndef NO
  #define NO                     0
#endif

#ifndef YES
  #define YES                    (!NO)
#endif

#ifndef RESET_
  #define RESET_                 0
#endif

#ifndef SET_
  #define SET_                   (!RESET_)
#endif

#ifndef NEG
  #define NEG                    0
#endif

#ifndef POS
  #define POS                    (!NEG)
#endif

#ifndef DE_ERROR
  #define DE_ERROR               1
#endif

#ifndef NO_ERROR
  #define NO_ERROR               (!DE_ERROR)
#endif

#ifndef LOW_EN
  #define LOW_EN                 0
#endif

#ifndef LOW_DIS
  #define LOW_DIS                (!LOW_DIS)
#endif

#ifndef HIGH_EN
  #define HIGH_EN                0
#endif

#ifndef HIGH_DIS
  #define HIGH_DIS               (!HIGH_EN)
#endif

/* Define CRC initial value*/
#define CRC_INIT_02              0x02

/* Definition for index */
#define NO_0                     ((uint8)0U)
#define NO_1                     ((uint8)1U)
#define NO_2                     ((uint8)2U)
#define NO_3                     ((uint8)3U)
#define NO_4                     ((uint8)4U)
#define NO_5                     ((uint8)5U)
#define NO_6                     ((uint8)6U)
#define NO_7                     ((uint8)7U)
#define NO_8                     ((uint8)8U)
#define NO_9                     ((uint8)9U)
#define NO_10                    ((uint8)10U)
#define NO_11                    ((uint8)11U)
#define NO_12                    ((uint8)12U)
#define NO_13                    ((uint8)13U)
#define NO_14                    ((uint8)14U)
#define NO_15                    ((uint8)15U)

/* Bit declaration for 16bits */
#define BIT0                     0x0001
#define BIT1                     0x0002
#define BIT2                     0x0004
#define BIT3                     0x0008
#define BIT4                     0x0010
#define BIT5                     0x0020
#define BIT6                     0x0040
#define BIT7                     0x0080
#define BIT8                     0x0100
#define BIT9                     0x0200
#define BIT10                    0x0400
#define BIT11                    0x0800
#define BIT12                    0x1000
#define BIT13                    0x2000
#define BIT14                    0x4000
#define BIT15                    0x8000

/* Datatype Converting */
#define HIGH_BYTE                0xFF00U
#define LOW_BYTE                 0x00FFU
#define HIGH_INT                 0xFFFF0000U
#define LOW_INT                  0x0000FFFFU
#define LOW_BYTE_OF_HIGH_INT     0x00FF0000U
#define HIGH_BYTE_OF_HIGH_INT    0xFF000000U

/* SI prefixes */
#define F64_TERRA                ((float64)1e12)  /* Can be converted to uint64 */
#define F64_GIGA                 ((float64)1e9)   /* Can be converted to uint32 */
#define F64_MEGA                 ((float64)1e6)   /* Can be converted to uint32 */
#define F64_KILO                 ((float64)1e3)   /* Can be converted to uint16 */
#define F64_MILLI                ((float64)1e-3)
#define F64_MICRO                ((float64)1e-6)
#define F64_NANO                 ((float64)1e-9)
#define F64_PICO                 ((float64)1e-12)

#define F64_ONE_BY_TERRA         (float64)(1.0F / U32_TERRA)
#define F64_ONE_BY_GIGA          (float64)(1.0F / U32_GIGA)
#define F64_ONE_BY_MEGA          (float64)(1.0F / U32_MEGA)
#define F64_ONE_BY_KILO          (float64)(1.0F / U16_KILO)
#define F64_ONE_BY_MILLI         (float64)(1.0F / F64_MILLI)  /* Can be converted to uint16 */
#define F64_ONE_BY_MICRO         (float64)(1.0F / F64_MICRO)  /* Can be converted to uint32 */
#define F64_ONE_BY_NANO          (float64)(1.0F / F64_NANO)   /* Can be converted to uint32 */
#define F64_ONE_BY_PICO          (float64)(1.0F / F64_PICO)   /* Can be converted to uint64 */

/***************************************
 * Scaling factors
 **************************************/
#define F32_1_NANO               (F64_ONE_BY_NANO / 1)
#define F32_10_NANO              (F64_ONE_BY_NANO / 10)
#define F32_100_NANO             (F64_ONE_BY_NANO / 100)
#define F32_1_MICRO              (F64_ONE_BY_MICRO / 1)
#define F32_10_MICRO             (F64_ONE_BY_MICRO / 10)
#define F32_100_MICRO            (F64_ONE_BY_MICRO / 100)
#define F32_1_MILLI              (F64_ONE_BY_MILLI / 1)
#define F32_10_MILLI             (F64_ONE_BY_MILLI / 10)
#define F32_100_MILLI            (F64_ONE_BY_MILLI / 100)

#define F32_SQRT2                1.41421356F   /* Square root of 2 */
#define F32_RMS_AMPL_FACT           1.11068F   /* RMS scaling factor (1/SQRT2*pi/2) = 1.11068 */
#define F32_AMPL_RMS_FACT           0.70709F   /* 1/SQRT2 = 0.70709 */

/* Defines for division by Right shift @ Value >> dividor_factor */
#define DIV_SHIFT_1              1   /* Value will divided by     2 */
#define DIV_SHIFT_2              2   /* Value will divided by     4 */
#define DIV_SHIFT_3              3   /* Value will divided by     8 */
#define DIV_SHIFT_4              4   /* Value will divided by    16 */
#define DIV_SHIFT_5              5   /* Value will divided by    32 */
#define DIV_SHIFT_6              6   /* Value will divided by    64 */
#define DIV_SHIFT_7              7   /* Value will divided by   128 */
#define DIV_SHIFT_8              8   /* Value will divided by   256 */
#define DIV_SHIFT_9              9   /* Value will divided by   512 */
#define DIV_SHIFT_10             10  /* Value will divided by  1024 */
#define DIV_SHIFT_11             11  /* Value will divided by  2048 */
#define DIV_SHIFT_12             12  /* Value will divided by  4096 */
#define DIV_SHIFT_13             13  /* Value will divided by  8192 */
#define DIV_SHIFT_14             14  /* Value will divided by 16384 */
#define DIV_SHIFT_15             15  /* Value will divided by 32768 */
#define DIV_SHIFT_16             16  /* Value will divided by 65536 */

/* multiplication by left shift @  Value << multiply_factor */
#define MUL_SHIFT_1              1   /* Value will multiply by     2 */
#define MUL_SHIFT_2              2   /* Value will multiply by     4 */
#define MUL_SHIFT_3              3   /* Value will multiply by     8 */
#define MUL_SHIFT_4              4   /* Value will multiply by    16 */
#define MUL_SHIFT_5              5   /* Value will multiply by    32 */
#define MUL_SHIFT_6              6   /* Value will multiply by    64 */
#define MUL_SHIFT_7              7   /* Value will multiply by   128 */
#define MUL_SHIFT_8              8   /* Value will multiply by   256 */
#define MUL_SHIFT_9              9   /* Value will multiply by   512 */
#define MUL_SHIFT_10             10  /* Value will multiply by  1024 */
#define MUL_SHIFT_11             11  /* Value will multiply by  2048 */
#define MUL_SHIFT_12             12  /* Value will multiply by  4096 */
#define MUL_SHIFT_13             13  /* Value will multiply by  8192 */
#define MUL_SHIFT_14             14  /* Value will multiply by 16384 */
#define MUL_SHIFT_15             15  /* Value will multiply by 32768 */
#define MUL_SHIFT_16             16  /* Value will multiply by 65536 */

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/* Definitions for 16-bit and 32-Bit signed/unsigned integers */
#ifndef DATA_TYPES
#define DATA_TYPES
  typedef unsigned char          boolean;
  typedef   signed char          sint8;
  typedef unsigned char          uint8;
  typedef   signed short int     sint16;  /* Add for 32bit MCU */
  typedef unsigned short int     uint16;  /* Add for 32bit MCU */
  typedef   signed long          sint32;
  typedef unsigned long          uint32;
  typedef   signed long long     sint64;
  typedef unsigned long long     uint64;
  typedef          float         float32;
  typedef          long double   float64;
#endif

typedef union GLOBAL_BYTE_VAL_
{
  uint8 u8Val;
  struct
  {
    uint8 Bits0_3:4;
    uint8 Bits4_7:4;
  } Bits4;
} GLOBAL_BYTE_VAL;

typedef union GLOBAL_WORD_VAL_
{
  uint16 u16Val;
  sint16 s16Val;
  struct
  {
    uint16 Bits0_3:4;
    uint16 Bits4_7:4;
    uint16 Bits8_B:4;
    uint16 BitsC_F:4;
  } Bits4;
  struct 
  {
    uint16 LB:8;
    uint16 HB:8;
  } Bytes;
} GLOBAL_WORD_VAL;

typedef union GLOBAL_DWORD_VAL_
{
  uint32 u32Val;
  struct
  {
    uint32 Bits0_3:4;
    uint32 Bits4_7:4;
    uint32 Bits8_B:4;
    uint32 BitsC_F:4;
    uint32 Bits10_13:4;
    uint32 Bits14_17:4;
    uint32 Bits18_1B:4;
    uint32 Bits1C_1F:4;
  } Bits4;
  struct 
  {
    uint32 LW:16;
    uint32 HW:16;
  } Words;
  struct
  {
    uint32 LB:8;
    uint32 HB:8;
    uint32 UB:8;
    uint32 MB:8;
  } Bytes;
} GLOBAL_DWORD_VAL;

typedef union GLOBAL_U_U8BIT_
{
  uint8 ALL;
  struct
  {
    uint8 Bits0_3:4;
    uint8 Bits4_7:4;
  } Bits4;
  struct
  {
    uint8 f0:1;
    uint8 f1:1;
    uint8 f2:1;
    uint8 f3:1;
    uint8 f4:1;
    uint8 f5:1;
    uint8 f6:1;
    uint8 f7:1;
  } Bits;
} GLOBAL_U_U8BIT;

typedef union GLOBAL_U_U16BIT_
{
  uint16 ALL;
  struct
  {
    uint16 Bits0_3:4;
    uint16 Bits4_7:4;
    uint16 Bits8_B:4;
    uint16 BitsC_F:4;
  } Bits4;
  struct
  {
    uint16 LB:8;
    uint16 HB:8;
  } Bytes;
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
  } Bits;
} GLOBAL_U_U16BIT;

typedef union GLOBAL_U_REG32_
{
  uint32 u32Val;
  sint32 s32Val;
  uint16 u16Val[2];
  sint16 s16Val[2];
  uint8  u8Val[4];
  sint8  s8Val[4];
} GLOBAL_U_REG32;

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/* Q format definition for fix to fix point */
#define Q6(X)                    ((X < 0.0) ? (sint16)(64 * (X) - 0.5) : (sint16)(64 * (X) + 0.5))
#define Q8(X)                    ((X < 0.0) ? (sint16)(256 * (X) - 0.5) : (sint16)(256 * (X) + 0.5))
#define Q10(X)                   ((X < 0.0) ? (sint16)(1024 * (X) - 0.5) : (sint16)(1023 * (X) + 0.5))
#define Q11(X)                   ((X < 0.0) ? (sint16)(2048 * (X) - 0.5) : (sint16)(2047 * (X) + 0.5))
#define Q12(X)                   ((X < 0.0) ? (sint16)(4096 * (X) - 0.5) : (sint16)(4095 * (X) + 0.5))
#define Q13(X)                   ((X < 0.0) ? (sint16)(8192 * (X) - 0.5) : (sint16)(8191 * (X) + 0.5))
#define Q14(X)                   ((X < 0.0) ? (sint16)(16384 * (X) - 0.5) : (sint16)(16383 * (X) + 0.5))
#define Q15(X)                   ((X < 0.0) ? (sint16)(32768 * (X) - 0.5) : (sint16)(32767 * (X) + 0.5))
#define Q16(X)                   ((X < 0.0) ? (sint32)(65536 * (X) - 0.5) : (sint32)(65536 * (X) + 0.5))
#define Q20(X)                   ((X < 0.0) ? (sint32)(1048576 * (X) - 0.5) : (sint32)(1048576 * (X) + 0.5))
#define Q23(X)                   ((X < 0.0) ? (sint32)(8388608 * (X) - 0.5) : (sint32)(8388608 * (X) + 0.5))
#define Q24(X)                   ((X < 0.0) ? (sint32)(16777216 * (X) - 0.5) : (sint32)(16777216 * (X) + 0.5))
#define Q25(X)                   ((X < 0.0) ? (sint32)(33554432 * (X) - 0.5) : (sint32)(33554432 * (X) + 0.5))
#define Q26(X)                   ((X < 0.0) ? (sint32)(67108864 * (X) - 0.5) : (sint32)(67108864 * (X) + 0.5))
#define Q27(X)                   ((X < 0.0) ? (sint32)(134217728 * (X) - 0.5) : (sint32)(134217728 * (X) + 0.5))

/* Q format definition for floating point to fix point conversion */
/* floating to signed int */
#define S32Q8(X)                 ((sint32)((X < 0.0F) ? (256.0F * (X) - 0.5F) : (256.0F * (X) + 0.5F)))
#define S32Q9(X)                 ((sint32)((X < 0.0F) ? (512.0F * (X) - 0.5F) : (512.0F * (X) + 0.5F)))
#define S32Q10(X)                ((sint32)((X < 0.0F) ? (1024.0F * (X) - 0.5F) : (1024.0F * (X) + 0.5F)))
#define S32Q11(X)                ((sint32)((X < 0.0F) ? (2048.0F * (X) - 0.5F) : (2048.0F  * (X) + 0.5F)))
#define S32Q12(X)                ((sint32)((X < 0.0F) ? (4096.0F * (X) - 0.5F) : (4096.0F * (X) + 0.5F)))
#define S32Q13(X)                ((sint32)((X < 0.0F) ? (8192.0F * (X) - 0.5F) : (8192.0F * (X) + 0.5F)))
#define S32Q14(X)                ((sint32)((X < 0.0F) ? (16384.0F * (X) - 0.5F) : (16384.0F * (X) + 0.5F)))
#define S32Q15(X)                ((sint32)((X < 0.0F) ? (32768.0F * (X) - 0.5F) : (32768.0F * (X) + 0.5F)))
#define S32Q16(X)                ((sint32)((X < 0.0F) ? (65536.0F * (X) - 0.5F) : (65536.0F * (X) + 0.5F)))
#define S32Q17(X)                ((sint32)((X < 0.0F) ? (131072.0F * (X) - 0.5F) : (131072.0F * (X) + 0.5F)))
#define S32Q18(X)                ((sint32)((X < 0.0F) ? (262144.0F * (X) - 0.5F) : (262144.0F * (X) + 0.5F)))
#define S32Q19(X)                ((sint32)((X < 0.0F) ? (524288.0F * (X) - 0.5F) : (524288.0F  * (X) + 0.5F)))
#define S32Q20(X)                ((sint32)((X < 0.0F) ? (1048576.0F * (X) - 0.5F) : (1048576.0F * (X) + 0.5F)))
#define S32Q21(X)                ((sint32)((X < 0.0F) ? (2097152.0F * (X) - 0.5F) : (2097152.0F * (X) + 0.5F)))
#define S32Q22(X)                ((sint32)((X < 0.0F) ? (4194304.0F * (X) - 0.5F) : (4194304.0F * (X) + 0.5F)))
#define S32Q23(X)                ((sint32)((X < 0.0F) ? (8388608.0F * (X) - 0.5F) : (8388608.0F * (X) + 0.5F)))
#define S32Q24(X)                ((sint32)((X < 0.0F) ? (16777216.0F * (X) - 0.5F) : (16777216.0F * (X) + 0.5F)))
#define S32Q25(X)                ((sint32)((X < 0.0F) ? (33554432.0F * (X) - 0.5F) : (33554432.0F * (X) + 0.5F)))
#define S32Q26(X)                ((sint32)((X < 0.0F) ? (67108864.0F * (X) - 0.5F) : (67108864.0F * (X) + 0.5F)))
#define S32Q27(X)                ((sint32)((X < 0.0F) ? (134217728.0F * (X) - 0.5F) : (134217728.0F * (X) + 0.5F)))
#define S32Q28(X)                ((sint32)((X < 0.0F) ? (268435456.0F * (X) - 0.5F) : (268435456.0F * (X) + 0.5F)))
#define S32Q29(X)                ((sint32)((X < 0.0F) ? (536870912.0F * (X) - 0.5F) : (536870912.0F * (X) + 0.5F)))
#define S32Q30(X)                ((sint32)((X < 0.0F) ? (1073741824.0F * (X) - 0.5F) : (1073741824.0F * (X) + 0.5F)))
#define S32Q31(X)                ((sint32)((X < 0.0F) ? (2147483648.0F * (X) - 0.5F) : (2147483648.0F * (X) + 0.5F)))

/* Floating to unsigned int - result of floating to int type casting is int32 */
#define U32Q8(X)                 ((uint32)(256.0F * (X) + 0.5F))
#define U32Q9(X)                 ((uint32)(512.0F * (X) + 0.5F))
#define U32Q10(X)                ((uint32)(1024.0F * (X) + 0.5F))
#define U32Q11(X)                ((uint32)(2048.0F * (X) + 0.5F))
#define U32Q12(X)                ((uint32)(4096.0F * (X) + 0.5F))
#define U32Q13(X)                ((uint32)(8192.0F * (X) + 0.5F))
#define U32Q14(X)                ((uint32)(16384.0F * (X) + 0.5F))
#define U32Q15(X)                ((uint32)(32768.0F * (X) + 0.5F))
#define U32Q16(X)                ((uint32)(65536.0F * (X) + 0.5F))
#define U32Q17(X)                ((uint32)(131072.0F * (X) + 0.5F))
#define U32Q18(X)                ((uint32)(262144.0F * (X) + 0.5F))
#define U32Q19(X)                ((uint32)(524288.0F * (X) + 0.5F))
#define U32Q20(X)                ((uint32)(1048576.0F * (X) + 0.5F))
#define U32Q21(X)                ((uint32)(2097152.0F * (X) + 0.5F))
#define U32Q22(X)                ((uint32)(4194304.0F * (X) + 0.5F))
#define U32Q23(X)                ((uint32)(8388608.0F * (X) + 0.5F))
#define U32Q24(X)                ((uint32)(16777216.0F * (X) + 0.5F))
#define U32Q25(X)                ((uint32)(33554432.0F * (X) + 0.5F))
#define U32Q26(X)                ((uint32)(67108864.0F * (X) + 0.5F))
#define U32Q27(X)                ((uint32)(134217728.0F * (X) + 0.5F))
#define U32Q28(X)                ((uint32)(268435456.0F * (X) + 0.5F))
#define U32Q29(X)                ((uint32)(536870912.0f * (X) + 0.5F))
#define U32Q30(X)                ((uint32)(1073741824.0F * (X) + 0.5F))
#define U32Q31(X)                ((uint32)(2147483648.0F * (X) + 0.5F))

/* Bit operations, for 8bit register, i/o ports etc. */
#define SETBIT(ADDRESS, BIT)     (ADDRESS |= ((uint16)1 << BIT))
#define CLRBIT(ADDRESS, BIT)     (ADDRESS &= ~((uint16)1 << BIT))
#define TOGBIT(ADDRESS, BIT)     (ADDRESS ^= ((uint16)1 << BIT))
#define TESTBIT(ADDRESS, BIT)    (ADDRESS & ((uint16)1 << BIT))
#define CLRFLAG(ADDRESS, BIT)    (ADDRESS = ((uint16)1 << BIT))

#define SETBIT16(ADDRESS, BIT)   (ADDRESS |= (1U << (uint8_t)BIT))
#define SETBIT32(ADDRESS, BIT)   (ADDRESS |= (1U << (uint8_t)BIT))

#define HIBYTE(DATA)             ((uint8)((DATA >> DIV_SHIFT_8) & LOW_BYTE))
#define LOBYTE(DATA)             ((uint8)(DATA & LOW_BYTE))
#define GET_WORD(HB,LB)          (((uint16)HB << 8) + LB)

#define SETBITPORT(PORT, BIT)    (PORT |= (1U << (uint8)BIT))   /* set bit in port */
#define CLRBITPORT(PORT, BIT)    (PORT &= ~(1U <<(uint8)BIT))   /* clear bit in port */

#define DIM(X)                   (sizeof(X)/sizeof(X[0]))

/* Comparison */
#define MIN(A, B)                ((A) < (B) ? (A) : (B))
#define MAX(A, B)                ((A) > (B) ? (A) : (B))

/* Limitation */
#define SAT_H(A, B)              (((A) > (B)) ? (B) : (A))
#define SAT_L(A, B)              ((A < B) ? (B) : (A))
#define LIMIT(A, B, C)           ((A < B) ? (B) : (A > C) ? (C) : (A))

/* Counter resets */
#define RESET_CTR_EQU(A, B)      (A = ((A == B) ? (0) : (A)))
#define RESET_CTR_OVR(A, B)      (A = ((A > B) ? (0) : (A)))
#define RESET_CTR_EQU_OVR(A, B)  (A = ((A >= B) ? (0) : (A)))
#define EQU_ZERO_TO_ONE(A)       (A = ((A == 0) ? (1) : (A)))


#ifdef __cplusplus
  }
#endif
#endif  /* GLOBAL_H */


/*
 * End of file
 */
