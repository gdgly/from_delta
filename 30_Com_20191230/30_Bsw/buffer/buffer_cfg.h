/** ****************************************************************************
 * \file    buffer_cfg.h
 * \brief   BUFFER module implementation configuration
 *
 * \section AUTHOR
 *  J. Boyd
 *
 * \section SVN
 *  $Date: 2019-05-08 09:09:27 +0800 (Wed, 08 May 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 179 $
 *
 * \section LICENSE
 *  Copyright (c) 2016 Delta Energy Systems (Germany) GmbH.
 *  All rights reserved.
 **************************************************************************** */

#ifndef BUFFER_CFG_H
#define BUFFER_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

#define BUFFER_CFG_1MS_SIZE    (64u) /* Number of values to average over */
#define BUFFER_CFG_10MS_SIZE  (1024u) /* Number of values to average over */
 
/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
 
 /* TODO extend this to be configurable so the value buffered can be a float32 or an uint32, and mean of each works. */
    
typedef enum BUFFER_CFG_E_INDEX_
{
  BUFFER_CFG_E_ExtVsb = 0,
  BUFFER_CFG_E_IntVsb,
  BUFFER_CFG_E_Isb,
  BUFFER_CFG_E_Vin,
  BUFFER_CFG_E_Iin,
  BUFFER_CFG_E_Pin,
  BUFFER_CFG_E_V1,
  BUFFER_CFG_E_I1,
  BUFFER_CFG_E_P1,
  BUFFER_CFG_E_INDEX_COUNT /* Must be last row!*/
} BUFFER_CFG_E_INDEX;

#ifdef __cplusplus
}
#endif

#endif

/*
 * End of file
 */

