                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET_RAM, DATA, READONLY
                EXPORT  __Vectors_RAM
                EXPORT  __Vectors_RAM_End
                EXPORT  __Vectors_RAM_Size

__Vectors_RAM   DCD     0                          ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                   ; Window WatchDog
                DCD     PVD_IRQHandler                    ; PVD through EXTI Line detection
                DCD     TAMPER_STAMP_IRQHandler           ; Tamper and TimeStamps through the EXTI line
                DCD     RTC_WKUP_IRQHandler               ; RTC Wakeup through the EXTI line
                DCD     FLASH_IRQHandler                  ; FLASH
                DCD     RCC_IRQHandler                    ; RCC
                DCD     EXTI0_IRQHandler                  ; EXTI Line0
                DCD     EXTI1_IRQHandler                  ; EXTI Line1
                DCD     EXTI2_TS_IRQHandler               ; EXTI Line2 and Touch Sense
                DCD     EXTI3_IRQHandler                  ; EXTI Line3
                DCD     EXTI4_IRQHandler                  ; EXTI Line4
                DCD     DMA1_Channel1_IRQHandler          ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler          ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler          ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler          ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler          ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler          ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler          ; DMA1 Channel 7
                DCD     ADC1_2_IRQHandler                 ; ADC1 and ADC2
                DCD     CAN1_TX_IRQHandler                ; CAN1 TX
                DCD     CAN1_RX0_IRQHandler               ; CAN1 RX0
                DCD     CAN1_RX1_IRQHandler               ; CAN1 RX1
                DCD     CAN1_SCE_IRQHandler               ; CAN1 SCE
                DCD     EXTI9_5_IRQHandler                ; External Line[9:5]s
                DCD     TIM1_BRK_TIM15_IRQHandler         ; TIM1 Break and TIM15
                DCD     TIM1_UP_TIM16_IRQHandler          ; TIM1 Update and TIM16
                DCD     TIM1_TRG_COM_TIM17_IRQHandler     ; TIM1 Trigger and Commutation and TIM17
                DCD     TIM1_CC_IRQHandler                ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler                   ; TIM2
                DCD     TIM3_IRQHandler                   ; TIM3
                DCD     0                                 ; Reserved
                DCD     I2C1_EV_IRQHandler         ; I2C1 Event and EXTI Line 23
                DCD     I2C1_ER_IRQHandler                ; I2C1 Error
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     SPI1_IRQHandler                   ; SPI1
                DCD     0                                 ; Reserved
                DCD     USART1_IRQHandler          ; USART1 and EXTI Line 25
                DCD     USART2_IRQHandler          ; USART2 and EXTI Line 26
                DCD     USART3_IRQHandler          ; USART3 and EXTI Line 28
                DCD     EXTI15_10_IRQHandler              ; External Line[15:10]s
                DCD     RTC_Alarm_IRQHandler              ; RTC Alarm (A and B) through EXTI Line
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     TIM6_DAC1_IRQHandler              ; TIM6 and DAC1 underrun errors
                DCD     TIM7_DAC2_IRQHandler              ; TIM7 and DAC2 underrun errors
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     COMP2_IRQHandler                  ; COMP2
                DCD     COMP4_6_IRQHandler                ; COMP4, COMP6
                DCD     0                                 ; Reserved
                DCD     HRTIM1_Master_IRQHandler          ; HRTIM1 master timer
                DCD     HRTIM1_TIMA_IRQHandler            ; Reserved
                DCD     HRTIM1_TIMB_IRQHandler            ; Reserved
                DCD     HRTIM1_TIMC_IRQHandler            ; Reserved
                DCD     HRTIM1_TIMD_IRQHandler            ; Reserved
                DCD     HRTIM1_TIME_IRQHandler            ; Reserved
                DCD     HRTIM1_FLT_IRQHandler             ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     FPU_IRQHandler                    ; FPU

__Vectors_RAM_End

__Vectors_RAM_Size  EQU  __Vectors_RAM_End - __Vectors_RAM

                AREA    |.text|, CODE, READONLY

                IMPORT  Reset_Handler
                IMPORT  NMI_Handler                ; NMI Handler
                IMPORT  HardFault_Handler          ; Hard Fault Handler
                IMPORT  MemManage_Handler          ; MPU Fault Handler
                IMPORT  BusFault_Handler           ; Bus Fault Handler
                IMPORT  UsageFault_Handler         ; Usage Fault Handler
                IMPORT  SVC_Handler                ; SVCall Handler
                IMPORT  DebugMon_Handler           ; Debug Monitor Handler
                IMPORT  PendSV_Handler             ; PendSV Handler
                IMPORT  SysTick_Handler            ; SysTick Handler

                IMPORT  WWDG_IRQHandler                   [WEAK]
                IMPORT  PVD_IRQHandler                    [WEAK]
                IMPORT  TAMPER_STAMP_IRQHandler           [WEAK]
                IMPORT  RTC_WKUP_IRQHandler               [WEAK]
                IMPORT  FLASH_IRQHandler                  [WEAK]
                IMPORT  RCC_IRQHandler                    [WEAK]
                IMPORT  EXTI0_IRQHandler                  [WEAK]
                IMPORT  EXTI1_IRQHandler                  [WEAK]
                IMPORT  EXTI2_TS_IRQHandler               [WEAK]
                IMPORT  EXTI3_IRQHandler                  [WEAK]
                IMPORT  EXTI4_IRQHandler                  [WEAK]
                IMPORT  DMA1_Channel1_IRQHandler          [WEAK]
                IMPORT  DMA1_Channel2_IRQHandler          [WEAK]
                IMPORT  DMA1_Channel3_IRQHandler          [WEAK]
                IMPORT  DMA1_Channel4_IRQHandler          [WEAK]
                IMPORT  DMA1_Channel5_IRQHandler          [WEAK]
                IMPORT  DMA1_Channel6_IRQHandler          [WEAK]
                IMPORT  DMA1_Channel7_IRQHandler          [WEAK]
                IMPORT  ADC1_2_IRQHandler                 [WEAK]
                IMPORT  CAN1_TX_IRQHandler                [WEAK]
                IMPORT  CAN1_RX0_IRQHandler               [WEAK]
                IMPORT  CAN1_RX1_IRQHandler               [WEAK]
                IMPORT  CAN1_SCE_IRQHandler               [WEAK]
                IMPORT  EXTI9_5_IRQHandler                [WEAK]
                IMPORT  TIM1_BRK_TIM15_IRQHandler         [WEAK]
                IMPORT  TIM1_UP_TIM16_IRQHandler          [WEAK]
                IMPORT  TIM1_TRG_COM_TIM17_IRQHandler     [WEAK]
                IMPORT  TIM1_CC_IRQHandler                [WEAK]
                IMPORT  TIM2_IRQHandler                   [WEAK]
                IMPORT  TIM3_IRQHandler                   [WEAK]
                IMPORT  I2C1_EV_IRQHandler         		  [WEAK]
                IMPORT  I2C1_ER_IRQHandler                [WEAK]
                IMPORT  SPI1_IRQHandler                   [WEAK]
                IMPORT  USART1_IRQHandler          		  [WEAK]
                IMPORT  USART2_IRQHandler          		  [WEAK]
                IMPORT  USART3_IRQHandler          		  [WEAK]
                IMPORT  EXTI15_10_IRQHandler              [WEAK]
                IMPORT  RTC_Alarm_IRQHandler              [WEAK]
                IMPORT  TIM6_DAC1_IRQHandler              [WEAK]
                IMPORT  TIM7_DAC2_IRQHandler              [WEAK]
                IMPORT  COMP2_IRQHandler              	  [WEAK]
                IMPORT  COMP4_6_IRQHandler                [WEAK]
                IMPORT  HRTIM1_Master_IRQHandler          [WEAK]
                IMPORT  HRTIM1_TIMA_IRQHandler            [WEAK]
                IMPORT  HRTIM1_TIMB_IRQHandler            [WEAK]
                IMPORT  HRTIM1_TIMC_IRQHandler            [WEAK]
                IMPORT  HRTIM1_TIMD_IRQHandler            [WEAK]
                IMPORT  HRTIM1_TIME_IRQHandler            [WEAK]
                IMPORT  HRTIM1_FLT_IRQHandler             [WEAK]
                IMPORT  FPU_IRQHandler                    [WEAK]
                
                END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
