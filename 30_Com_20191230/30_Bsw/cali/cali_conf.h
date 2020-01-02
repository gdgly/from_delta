/** *****************************************************************************
 * \file    cali_conf.h
 * \brief   Configurations file for cali.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-06-21 15:59:54 +0800 (Fri, 21 Jun 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 192 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef CALI_CONF_H
#define CALI_CONF_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/
#define MG_SEVEN_BYTES                 (0x07u)

#define MG_SENSOR_THR_DEFAULT          (65535)

#define MG_VIN_AC_AMP_DEFAULT          (uint16)(655.36 * 16 + 0.5)
#define MG_VIN_AC_OFS_DEFAULT          (0)

#define MG_IIN_AC_AMP_DEFAULT          (uint16)(65.536 * 16 + 0.5)
#define MG_IIN_AC_OFS_DEFAULT          (0)
		
#define MG_PIN_AC_AMP_DEFAULT          (uint16)(655.36 * 16 + 0.5)
#define MG_PIN_AC_OFS_DEFAULT          (0)

#define MG_V_V1_AMP_DEFAULT            (uint16)(655.36 * 16 + 0.5)
#define MG_V_V1_OFS_DEFAULT            (0)

#define MG_I_V1_AMP_DEFAULT            (uint16)(655.36 * 16 + 0.5)
#define MG_I_V1_OFS_DEFAULT            (0)

#define MG_V_VSB_AMP_DEFAULT           (uint16)(655.36  * 16 + 0.5)
#define MG_V_VSB_OFS_DEFAULT           (0)

#define MG_I_VSB_AMP_DEFAULT           (uint16)(65.536 * 16 + 0.5)
#define MG_I_VSB_OFS_DEFAULT           (0)

#define MG_V1_SENSE_AMP_DEFAULT       ((uint16)(655.36 * 16 + 0.5))
#define MG_V1_SENSE_OFS_DEFAULT       (0)

#define MG_ISHARE_AMP_DEFAULT         ((uint16)(655.36 * 16 + 0.5))
#define MG_ISHARE_OFS_DEFAULT         (0)

#define MG_V1_ISHARE_AMP_DEFAULT       (4095u)
#define MG_V1_ISHARE_OFS_DEFAULT       (0)


#define MG_U16Q7_IIN_DCIN_COMP        ((uint16)(0.053F * 128.0))   /* 115% load 73 */

#define MG_U16Q7_VSB_OCP_THR_HI       ((uint16)(2.85F * 128.0))   /* 115% load*/
#define MG_U16Q7_V1_OCP_THR_HI        ((uint16)(200.0F * 128.0))   /* 115% load*/


/***********************************************
 * I2C peripheral register relative definition
 **********************************************/



#ifdef __cplusplus
  }
#endif
#endif  /* CALI_CONF_H */


/*
 * End of file
 */
