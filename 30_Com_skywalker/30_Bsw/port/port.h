/*******************************************************************************
 * \file    port.h
 * \brief   Global interface for port.c
 *
 * \section AUTHOR
 *    1. Hulk.Zhang
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/******************** digital input pin High/Low status ********************************/
#define PORT_12VSB_OVP                      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)    /* Read Pin status */
#define PORT_FAN_TACH_1_STATUS              GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)    /* Read Pin status */
#define PORT_FAN_TACH_2_STATUS              GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)    /* Read Pin status */		
#define PORT_PSON_L_STATUS                  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)   /* Read Pin status */
#define PORT_PSKILL_L_STATUS                GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)   /* Read Pin status */
		
#define PORT_ADDRESS_PA2                    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)   /* Read Pin status */
#define PORT_ADDRESS_PA1                    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)   /* Read Pin status */
#define PORT_ADDRESS_PA0                    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)   /* Read Pin status */
#define PORT_VIN_OK_STATUS                  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)   /* Read Pin status */
#define PORT_PS_54V_FAULTSTATUS             GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)   /* Read Pin status */

/******************  digital output pin High/Low status  *******************************/
#define PORT_VSB_CLEAR_LATCH_HIGH           GPIOB->BSRR = GPIO_Pin_1      /* Set GPIOB_1 */
#define PORT_VSB_CLEAR_LATCH_LOW            GPIOB->BRR = GPIO_Pin_1       /* Set GPIOB_1 */
#define PORT_VSB_ON_OFF_HIGH                GPIOB->BSRR = GPIO_Pin_2      /* Set GPIOB_2 */
#define PORT_VSB_ON_OFF_LOW                 GPIOB->BRR = GPIO_Pin_2       /* Reset GPIOB_2 */ 
#define PORT_VSB_OVP_TEST_HIGH              GPIOB->BSRR = GPIO_Pin_12     /* Set GPIOB_12 */
#define PORT_VSB_OVP_TEST_LOW               GPIOB->BRR = GPIO_Pin_12      /* Reset GPIOB_12 */ 
#define PORT_SYNC_INTERNAL_HIGH             GPIOB->BSRR = GPIO_Pin_15     /* Set GPIOB_15 */
#define PORT_SYNC_INTERNAL_LOW              GPIOB->BRR = GPIO_Pin_15      /* Reset GPIOB_15 */  
#define PORT_LED_OUT_OK_HIGH                GPIOC->BSRR = GPIO_Pin_13     /* Set GPIOC_13 */
#define PORT_LED_OUT_OK_LOW                 GPIOC->BRR = GPIO_Pin_13      /* Reset GPIOC_13 */ 
#define PORT_LED_FAULT_HIGH                 GPIOC->BSRR = GPIO_Pin_15     /* Set GPIOC_15 */
#define PORT_LED_FAULT_LOW                  GPIOC->BRR = GPIO_Pin_15      /* Reset GPIOC_15 */ 
#define PORT_LED_IN_OK_HIGH                 GPIOC->BSRR = GPIO_Pin_14     /* Set GPIOC_14 */
#define PORT_LED_IN_OK_LOW                  GPIOC->BRR = GPIO_Pin_14      /* Set GPIOC_14 */
#define PORT_PWOK_HIGH                      GPIOA->BSRR = GPIO_Pin_11     /* Set GPIOA_11 */
#define PORT_PWOK_LOW                       GPIOA->BRR = GPIO_Pin_11      /* Set GPIOA_11 */
#define PORT_SMBALERT_HIGH                  GPIOA->BSRR = GPIO_Pin_12     /* Set GPIOA_12 */
#define PORT_SMBALERT_LOW                   GPIOA->BRR = GPIO_Pin_12      /* Set GPIOA_12 */

/**************** set digital output pin High/Low status  ******************************/
#define PORT_VSB_CLEAR_LATCH_ON()          { PORT_VSB_CLEAR_LATCH_HIGH; \
                                             RTE_DIO_VSB_CLEAR_LATCH_ON = 1; }
#define PORT_VSB_CLEAR_LATCH_OFF()         { PORT_VSB_CLEAR_LATCH_LOW; \
                                             RTE_DIO_VSB_CLEAR_LATCH_ON = 0; }
#define PORT_VSB_ON_OFF_SET_ON()           { PORT_VSB_ON_OFF_HIGH; \
                                             RTE_DIO_VSB_ON = 1; }
#define PORT_VSB_ON_OFF_SET_OFF()          { PORT_VSB_ON_OFF_LOW; \
                                             RTE_DIO_VSB_ON = 0; }
#define PORT_VSB_OVP_TEST_SET_ACTIVE()     { PORT_VSB_OVP_TEST_HIGH; \
                                             RTE_DIO_VSB_OVPTEST_ACTIVE = 1; }
#define PORT_VSB_OVP_TEST_SET_INACTIVE()   { PORT_VSB_OVP_TEST_LOW; \
                                             RTE_DIO_VSB_OVPTEST_ACTIVE = 0; }
#define PORT_SYNC_INTERNAL_SET_ON()        { PORT_SYNC_INTERNAL_HIGH; \
                                             RTE_DIO_SYNC_INTERNAL_ON = 1; }
#define PORT_SYNC_INTERNAL_SET_OFF()       { PORT_SYNC_INTERNAL_LOW; \
                                             RTE_DIO_SYNC_INTERNAL_ON = 0; }
#define PORT_PWOK_SET_EN()                 { PORT_PWOK_HIGH; \
                                             RTE_DIO_PWOK_ENA = 1; }
#define PORT_PWOK_SET_DS()                 { PORT_PWOK_LOW; \
                                             RTE_DIO_PWOK_ENA = 0; }
#define PORT_SMBALERT_SET_EN()             { PORT_SMBALERT_LOW; \
                                             RTE_DIO_SMBALERT_ENA = 1; }
#define PORT_SMBALERT_SET_DS()             { PORT_SMBALERT_HIGH; \
                                             RTE_DIO_SMBALERT_ENA = 0; }
#define PORT_LED_IN_OK_ON()                { PORT_LED_IN_OK_HIGH; \
                                             RTE_DIO_INPUT_LED_OK_ON = 1; }
#define PORT_LED_IN_OK_OFF()               { PORT_LED_IN_OK_LOW; \
                                             RTE_DIO_INPUT_LED_OK_ON = 0; }
#define PORT_LED_OUT_OK_ON()               { PORT_LED_OUT_OK_HIGH; \
                                             RTE_DIO_OUTPUT_LED_OK_ON = 1; }
#define PORT_LED_OUT_OK_OFF()              { PORT_LED_OUT_OK_LOW; \
                                             RTE_DIO_OUTPUT_LED_OK_ON = 0; }
#define PORT_LED_FAIL_AMBER_ON()           { PORT_LED_FAULT_HIGH; \
                                             RTE_DIO_LED_FAULT_ON = 1; }
#define PORT_LED_FAIL_AMBER_OFF()          { PORT_LED_FAULT_LOW; \
                                             RTE_DIO_LED_FAULT_ON = 0; }


/**************** set digital input pin High/Low status  *******************************/

#define PORT_PS_ON_ENABLE                  ( PORT_PSON_L_STATUS   == FALSE )
#define PORT_PS_ON_DISABLE                 ( PORT_PSON_L_STATUS   == TRUE )
#define PORT_PS_KILL_ACTIVE                ( PORT_PSKILL_L_STATUS  == FALSE )
#define PORT_PS_KILL_INACTIVE              ( PORT_PSKILL_L_STATUS  == TRUE )
#define PORT_VSB_OVP_ACTIVE                ( PORT_12VSB_OVP  == TRUE )
#define PORT_VSB_OVP_INACTIVE              ( PORT_12VSB_OVP  == FALSE )
#define PORT_54V_FAULT_ACTIVE              ( PORT_PS_54V_FAULTSTATUS  == TRUE )
#define PORT_54V_FAULT_INACTIVE            ( PORT_PS_54V_FAULTSTATUS  == FALSE )																						 
#define PORT_VIN_OK_ACTIVE                 ( PORT_VIN_OK_STATUS  == TRUE )
#define PORT_VIN_OK_INACTIVE               ( PORT_VIN_OK_STATUS  == FALSE )
/**************** set I2C pin High/Low status  *******************************/
#define PORT_SCL_LOW                       ( !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) )
#define PORT_SDA_LOW                       ( !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) )

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/

/*******************************************************************************
 * \brief         Initialize and configure MCU ports
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
extern void PORT_vPortHwInit(void);

#ifdef __cplusplus
  }
#endif
#endif  /* PORT_H */

  
/*
 * End of file
 */
