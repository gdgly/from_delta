/** *****************************************************************************
 * \file    comp.c
 * \brief   MCU comparator configurations
 *
 * \section AUTHOR
 *    1. Fred.Ji
 *
 * \section SVN
 *  $Date: 2018-08-03 11:21:52 +0800 (Fri, 03 Aug 2018) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 8 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center)
 * All rights reserved.
 ***************************************************************************** */

/*******************************************************************************
 * Included header
 ******************************************************************************/
 
#include <stdio.h>
#include <StdPeriphDriver.h>
#include "global.h"
#include "rte.h"

/* Module header */
#define COMP_EXPORT_H
  #include "comp.h"
  
/*******************************************************************************
 * Local constants and macros (private to module)
 ******************************************************************************/

#define MG_F32_IIN_OC_CMP_CURR      30.0F
#define MG_U16Q12_IIN_OC_CMP_SET    U16Q12(MG_F32_IIN_OC_CMP_CURR / RTE_F32_IREF_CMP_MAX)

#if RTE_EXTENDER_ON_BOARD
#define MG_F32_IEXT_OC_CMP_CURR     25.0F
#define MG_U16Q12_IEXT_OC_CMP_SET   U16Q12(MG_F32_IEXT_OC_CMP_CURR / RTE_F32_IEXT_CMP_MAX)
#endif

/*******************************************************************************
 * Local data types (private typedefs / structs / enums)
 ******************************************************************************/

/*******************************************************************************
 * Local data (private to module)
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes (private to module)
 ******************************************************************************/
 
void mg_vDacInit(void);

/*******************************************************************************
 * Global functions (public to other modules)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initialize and configure MCU comparators (current limitation)
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void COMP_vCompHwInit(void)
{

}

/*******************************************************************************
 * Local functions (private to module)
 ******************************************************************************/

/** *****************************************************************************
 * \brief         Initializes the DAC registers
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ***************************************************************************** */
void mg_vDacInit(void)
{

}

/*
 * End of file
 */
