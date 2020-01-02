/** ****************************************************************************
 * \file    buffer_api.h
 * \brief   BUFFER module interface header
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

#ifndef BUFFER_API_H
#define BUFFER_API_H

#include "buffer_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Global constants and macros
 ******************************************************************************/

/*******************************************************************************
 * Global data types (typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Global data
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/

/** ****************************************************************************
 * \brief   This function return the mean value
 *
 **************************************************************************** */
uint16 BUFFER_u16GetMean1ms(const BUFFER_CFG_E_INDEX eIndex);
uint16 BUFFER_u16GetMean10ms(const BUFFER_CFG_E_INDEX eIndex);

#ifdef __cplusplus
}
#endif

#endif

/*
 * End of file
 */

