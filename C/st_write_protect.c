#include "bsp_data.h"
#include "stm32f0xx_flash.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
u8 protect_flag =0 ;
/* Private define ------------------------------------------------------------*/
#ifdef STM32F030
 #define FLASH_PAGE_SIZE                ((uint16_t)0x2000) 
 #define FLASH_PAGES_TO_BE_PROTECTED   (OB_WRP_Pages0to3   | OB_WRP_Pages4to7   | OB_WRP_Pages8to11  |\
                                        OB_WRP_Pages12to15 | OB_WRP_Pages16to19 | OB_WRP_Pages20to23 |\
                                        OB_WRP_Pages24to27 | OB_WRP_Pages28to31 | OB_WRP_Pages32to35 |\
                                        OB_WRP_Pages36to39 | OB_WRP_Pages40to43 | OB_WRP_Pages44to47 |\
                                        OB_WRP_Pages48to51 | OB_WRP_Pages52to55 | OB_WRP_Pages56to59 |\
                                        OB_WRP_Pages60to63) /*OB_WRP_AllPages*/
#else
 #define FLASH_PAGE_SIZE                ((uint16_t)0x2000)
 #define FLASH_PAGES_TO_BE_PROTECTED   (OB_WRP_Pages0to3   | OB_WRP_Pages4to7   | OB_WRP_Pages8to11  |\
                                        OB_WRP_Pages12to15 | OB_WRP_Pages16to19 | OB_WRP_Pages20to23 |\
                                        OB_WRP_Pages24to27 | OB_WRP_Pages28to31 | OB_WRP_Pages32to35 |\
                                        OB_WRP_Pages36to39 | OB_WRP_Pages40to43 | OB_WRP_Pages44to47 |\
                                        OB_WRP_Pages48to51 | OB_WRP_Pages52to55 | OB_WRP_Pages56to59 |\
                                        OB_WRP_Pages60to63) /*OB_WRP_AllPages*/
#endif /* STM32F030 */

#define BANK1_WRITE_START_ADDR         ((uint32_t)0x08006000)
#define BANK1_WRITE_END_ADDR           ((uint32_t)0x08010000)
 
/* Uncomment this line to program the Flash pages */
//#define FLASH_PAGE_PROGRAM

/* Uncomment this line to Enable Write Protection */
#define WRITE_PROTECTION_ENABLE
 
/* Uncomment this line to Disable Write Protection */
//#define WRITE_PROTECTION_DISABLE
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t EraseCounter = 0x0, Address = 0x0;
uint16_t Data = 0x1753;
uint32_t WRPR_Value = 0xFFFFFFFF, ProtectedPages = 0x0;
uint32_t NbrOfPage;
__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO TestStatus MemoryProgramStatus = PASSED;

/*****************main****************/
int main(void)
{  
All_Init();
/*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */ 
  
  /* Unlock the Flash Program Erase controller */  
  FLASH_Unlock();
  
  FLASH_OB_Unlock();
  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
    
  /* Get pages write protection status */
  WRPR_Value = FLASH_OB_GetWRP();

#ifdef WRITE_PROTECTION_DISABLE 
  /* Get pages already write protected */
  ProtectedPages = ~(WRPR_Value | FLASH_PAGES_TO_BE_PROTECTED);
  
  /* Check if desired pages are already write protected */
  if((WRPR_Value | (~FLASH_PAGES_TO_BE_PROTECTED)) != 0xFFFFFFFF )
  {
    /* Erase all the option Bytes */
    FLASHStatus = FLASH_OB_Erase();
    
    /* Check if there is write protected pages */
    if(ProtectedPages != 0x0)
    {
      /* Restore write protected pages */
      FLASHStatus = FLASH_OB_EnableWRP(ProtectedPages);
    }
    /* Generate System Reset to load the new option byte values */
    FLASH_OB_Launch();
  }

#elif defined WRITE_PROTECTION_ENABLE
  /* Get current write protected pages and the new pages to be protected */
  ProtectedPages =  (~WRPR_Value) | FLASH_PAGES_TO_BE_PROTECTED; 
  
  /* Check if desired pages are not yet write protected */
  if(((~WRPR_Value) & FLASH_PAGES_TO_BE_PROTECTED )!= FLASH_PAGES_TO_BE_PROTECTED)
  {
  
    /* Erase all the option Bytes because if a program operation is 
      performed on a protected page, the Flash memory returns a 
      protection error */
    FLASHStatus = FLASH_OB_Erase();

    /* Enable the pages write protection */
    FLASHStatus = FLASH_OB_EnableWRP(ProtectedPages);
  
    /* Generate System Reset to load the new option byte values */
    FLASH_OB_Launch();
  }  
#endif /* WRITE_PROTECTION_DISABLE */

#ifdef FLASH_PAGE_PROGRAM  
  /* Get the number of pages to be erased */
  NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;

  /* The selected pages are not write protected */
  if ( (WRPR_Value & FLASH_PAGES_TO_BE_PROTECTED) != 0x00)
  {
    /* Clear pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR |FLASH_FLAG_WRPERR);

    /* erase the FLASH pages */
    for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
    {
      FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
    }
  
    /* FLASH Half Word program of data 0x1753 at addresses defined by  BANK1_WRITE_START_ADDR and BANK1_WRITE_END_ADDR */
    Address = BANK1_WRITE_START_ADDR;

    while((Address < BANK1_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE))
    {
      FLASHStatus = FLASH_ProgramHalfWord(Address, Data);
      Address = Address + 2;
    }

    /* Check the correctness of written data */
    Address = BANK1_WRITE_START_ADDR;

    while((Address < BANK1_WRITE_END_ADDR) && (MemoryProgramStatus != FAILED))
    {
      if((*(__IO uint16_t*) Address) != Data)
      {
        MemoryProgramStatus = FAILED;
      }
      Address += 2;
    }
  }
  else
  { 
    /* Error to program the flash : The desired pages are write protected */ 
    MemoryProgramStatus = FAILED;
  }
#endif /* FLASH_PAGE_PROGRAM */
 
  while (1)
  {
    Whole_Process();
    if(protect_flag>3)
    {
    /* Get pages already write protected */
      ProtectedPages = ~(WRPR_Value | FLASH_PAGES_TO_BE_PROTECTED);
      
      /* Check if desired pages are already write protected */
      if((WRPR_Value | (~FLASH_PAGES_TO_BE_PROTECTED)) != 0xFFFFFFFF )
      {
        /* Erase all the option Bytes */
        FLASHStatus = FLASH_OB_Erase();
        
        /* Check if there is write protected pages */
        if(ProtectedPages != 0x0)
        {
          /* Restore write protected pages */
          FLASHStatus = FLASH_OB_EnableWRP(ProtectedPages);
        }
        /* Generate System Reset to load the new option byte values */
        FLASH_OB_Launch();
      }
    }
  }
}



