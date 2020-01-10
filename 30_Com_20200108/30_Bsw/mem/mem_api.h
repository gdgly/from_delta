/** *****************************************************************************
 * \file    mem_api.h
 * \brief   Service function request file for mem.c
 *
 * \section AUTHOR
 *    1. Jeff Zhou
 *
 * \section SVN
 *  $Date: 2019-01-11 10:40:42 +0800 (Fri, 11 Jan 2019) $
 *  $Author: Jeff.Zhou $
 *  $Revision: 137 $
 *
 * \section LICENSE
 * Copyright (c) 2016 Delta Electronics (Hangzhou Design Center & Thailand)
 * All rights reserved.
 ***************************************************************************** */

#ifndef MEM_API_H
#define MEM_API_H
#ifdef __cplusplus
  extern "C"  {
#endif

/*******************************************************************************
 * Included header
 ******************************************************************************/

#include "global.h"

/*******************************************************************************
 * Global function prototypes (public to other modules)
 ******************************************************************************/
/*******************************************************************************
 * \brief         Read the black box data from eeprom
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void MEM_vReadBlackBoxData(uint8 u8Index, uint8 *pData);

/*******************************************************************************
 * \brief         Write the black box data from eeprom
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void MEM_vWriteBlackBoxData(uint8 u8Index, const uint8 *pData);

/*******************************************************************************
 * \brief         Read the black box page write distance from eeprom
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
uint8 MEM_vReadBlcBoxPageWrDis(void);

/*******************************************************************************
 * \brief         Write the black box page write distance to eeprom
 *
 * \param[in]     -
 * \param[in,out] -
 * \param[out]    -
 *
 * \return        -
 *
 ******************************************************************************/
void MEM_vWriteBlcBoxPageWrDis(uint8 u8Data);

/** ****************************************************************************
 * \brief  MEM_vWriteTomem
 * \param[in]  -  
 * \param[out] -
 *
 * \return  -Write to mem (Ram)
 *
 **************************************************************************** */
void MEM_vWriteToMem(uint32 u32WriteAddr,const uint8 *pu8Buffer,uint32 u32NumByteToWrite );

 /** ****************************************************************************
 * \brief  MEM_vReadFromMem
 * \param[in]  -  
 * \param[out] -
 *
 * \return  -Read from mem (Ram)
 *
 **************************************************************************** */
boolean MEM_vReadFromMem(uint32 u32ReadAddr,uint8 *pu8Buffer,uint32 u32NumByteToRead );

 /** ****************************************************************************
 * \brief  emem_u16Getlenght
 * \param[in]  -  
 * \param[out] -
 *
 * \return  - size array emem
 *
 **************************************************************************** */
uint16 MEM_u16Getlenght(uint8 index);
 /** ****************************************************************************
 * \brief  emem_u16GetOffset
 * \param[in]  -  
 * \param[out] -
 *
 * \return  - offset array emem
 *
 **************************************************************************** */
uint16 MEM_u16GetOffset(uint8 index);
 /** ****************************************************************************
 * \brief  emem_u16Getlenght
 * \param[in]  -  
 * \param[out] -
 *
 * \return  - 
 *
 **************************************************************************** */
void MEM_vWrite2EEPORM(uint16 u16Lenght , uint16 u16Offset);

 /** ****************************************************************************
 * \brief  emem_vRead2EEPORM
 * \param[in]  -  
 * \param[out] -
 *
 * \return  - Read from EEPROM To Emem(RAM)
 *
 **************************************************************************** */
void MEM_vRead2EEPORM(uint16 u16Lenght ,uint16 u16Offset);

#ifdef __cplusplus
  }
#endif
#endif  /* MEM_API_H */

  
/*
 * End of file
 */
