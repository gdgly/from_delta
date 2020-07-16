
#define FLASH_64KB
#ifdef FLASH_64KB /* 64kB, 16 sectors */
#define FLASH_PAGES_TO_BE_PROTECTED   (OB_WRP_Pages0to1   | OB_WRP_Pages2to3   | OB_WRP_Pages4to5  |\
																			OB_WRP_Pages6to7 | OB_WRP_Pages8to9 | OB_WRP_Pages10to11 |\
																			OB_WRP_Pages12to13 | OB_WRP_Pages14to15 |OB_WRP_Pages16to17|\
																			OB_WRP_Pages18to19|OB_WRP_Pages20to21|OB_WRP_Pages22to23\
																			|OB_WRP_Pages24to25|OB_WRP_Pages26to27|OB_WRP_Pages28to29\
																			|OB_WRP_Pages30to31) /*OB_WRP_AllPages*/
#endif

//#define DIS_WRP
#ifdef DIS_WRP
#define WRP_0     ((uint8_t)0xFF)
#define WRP_1     ((uint8_t)0xFF)
#define WRP_2     ((uint8_t)0xFF)
#define WRP_3     ((uint8_t)0xFF)
#else
#define WRP_0     (uint8_t)((~FLASH_PAGES_TO_BE_PROTECTED) & 0xFF)
#define WRP_1     (uint8_t)((~FLASH_PAGES_TO_BE_PROTECTED >> 8) & 0xFF)
#define WRP_2     (uint8_t)((~FLASH_PAGES_TO_BE_PROTECTED >> 16) & 0xFF)
#define WRP_3     (uint8_t)((~FLASH_PAGES_TO_BE_PROTECTED >> 24) & 0xFF)
#endif

#define LEVEL_0   OB_RDP_Level_0
#define LEVEL_1   OB_RDP_Level_1
#define READ_PROTECTION_LEVEL				LEVEL_1	


const uint8 u8ReadProtection[1] __attribute__((at(0x1FFFF800))) = { READ_PROTECTION_LEVEL};
const uint8 u8WriteProtection[8] __attribute__((at(0x1FFFF808))) = {WRP_0, (uint8_t)(~WRP_0), WRP_1, (uint8_t)(~WRP_1),\
																																		WRP_2, (uint8_t)(~WRP_2), WRP_3, (uint8_t)(~WRP_3)};