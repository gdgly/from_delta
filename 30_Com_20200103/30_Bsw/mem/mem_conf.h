/** *****************************************************************************
 * \file    mem_conf.h
 * \brief   Configurations file for mem.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-01-16 18:46:21 +0800 (Wed, 16 Jan 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 139 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef MEM_CONF_H
#define MEM_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"


/* Pri FW REV */
#define EEP_REVI_PRI_APP_MAJOR                    0x0000
#define EEP_REVI_PRI_APP_MINOR                    0x0001
#define EEP_REVI_PRI_APP_DEBUG                    0x0002
#define EEP_REVI_PRI_APP_CRC                      0x0003

/* Pri Boot FW REV */
#define EEP_REVI_PRI_BOOT_MAJOR                    0x0004
#define EEP_REVI_PRI_BOOT_MINOR                    0x0005
#define EEP_REVI_PRI_BOOT_DEBUG                    0x0006
#define EEP_REVI_PRI_BOOT_CRC                      0x0007

/* Sec FW REV */
#define EEP_REVI_SEC_APP_MAJOR                    0x0008
#define EEP_REVI_SEC_APP_MINOR                    0x0009
#define EEP_REVI_SEC_APP_DEBUG                    0x000A
#define EEP_REVI_SEC_APP_CRC                      0x000B

/* Sec FW REV */
#define EEP_REVI_SEC_BOOT_MAJOR                    0x000C
#define EEP_REVI_SEC_BOOT_MINOR                    0x000D
#define EEP_REVI_SEC_BOOT_DEBUG                    0x000E
#define EEP_REVI_SEC_BOOT_CRC                      0x000F
/* Hours/Minutes Used Data */
#define EEP_USED_MINUTES_LB                     0x0070
#define EEP_USED_MINUTES_HB                     0x0071
#define EEP_USED_MINUTES_UB                     0x0072
#define EEP_USED_MINUTES_MB                     0x0073
#define EEP_USED_MINUTES_CRC                    0x0074

#define EEP_USED_MINUTES_1_LB                   0x0075
#define EEP_USED_MINUTES_1_HB                   0x0076
#define EEP_USED_MINUTES_1_UB                   0x0077
#define EEP_USED_MINUTES_1_MB                   0x0078
#define EEP_USED_MINUTES_1_CRC                  0x0079

/* Trim */
#define EEP_ADR_VSB_TRIM_LSB    								0x007A
#define EEP_ADR_VSB_TRIM_MSB    								0x007B
#define EEP_ADR_VSB_TRIM_CRC	    							0x007C

#define EEP_ADR_V1_1_TRIM_LSB    								0x007D
#define EEP_ADR_V1_1_TRIM_MSB    								0x007E
#define EEP_ADR_V1_1_TRIM_CRC	    							0x007F

#define EEP_ADR_V1_2_TRIM_LSB    								0x0080
#define EEP_ADR_V1_2_TRIM_MSB    								0x0081
#define EEP_ADR_V1_2_TRIM_CRC	    							0x0082

#define EEP_ADR_AC_CURR_OFFSET_LSB    					0x0083
#define EEP_ADR_AC_CURR_OFFSET_MSB    				  0x0084
#define EEP_ADR_BULK_ADC_CRC	    							0x0085

#define EEP_ADR_EXIT_SLEEP_LS_STR	    		  		0x0090
#define EEP_ADR_EXIT_SLEEP_LS_END	    		  		0x0094

/* EEPROM address for black box  */
#define EEP_ADR_BLACK_BOX_STR           0x0300
#define EEP_ADR_BLACK_BOX_SIZE          384u   
    
#define EEP_ADR_BLACK_BOX_PAGE_W_DIS    (EEP_ADR_BLACK_BOX_STR + EEP_ADR_BLACK_BOX_SIZE)
#define EEP_ADR_BLACK_BOX_END           (EEP_ADR_BLACK_BOX_PAGE_W_DIS + EEP_ADR_BLACK_BOX_SIZE - 1)  
/******* EEPROM address for MFR infomation ********/
#define MG_EE_ADR_MFR_INFO_STR            (RTE_EEPROM_ADDR_MFR_INF_STR)
#define MG_EE_ADR_MFR_INFO_SIZE           (RTE_MFR_DATA_RAW * RTE_MFR_DATA_COL + 1u)
#define MG_EE_ADR_MFR_INFO_END            (MG_EE_ADR_MFR_INFO_STR + MG_EE_ADR_MFR_INFO_SIZE - 1u)  


#define EEP_VSB_TRIM_DEFAULT                    500
#define EEP_V1_CHA_TRIM_DEFAULT                 4095
#define EEP_V1_CHB_TRIM_DEFAULT                 4095


#ifdef __cplusplus
  }
#endif
#endif  /* MEM_CONF_H */


/*
 * End of file
 */
