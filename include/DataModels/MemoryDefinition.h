/**
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 Steven Inácio
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 *  Created on: Wed Jul 29 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup DataModels
 * @{
 * @file
 * Includes a Data Struct to gather all relevant data for a direct memory access.
 * 
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_MEMORY_DEFINITION_H_
#define UDS_MEMORY_DEFINITION_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ******************************************************************/

#include <stdint.h>

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/**
 * Data Class for a MemoryAddress.
 */
typedef struct MemoryDefinition_public {
    /** @brief The address of the wanted memory block.
     * 
     * This is an Array because it's server dependent how much memory can be accessed.
     * 
     * @warning Please make sure this number has its MSB first.
     */
    uint8_t Address[15];
    
    /** @brief The size of the wanted memory block.
     * 
     * This is an Array because the length of the memory size is dynamic.
     * You should always use the least required byte count for the memory size to keep the frame overhead small.
     * 
     * @warning Please make sure this number has its MSB first.
     */ 
    uint8_t Size[15];

    /** @brief Length in Bytes of the address. 
     * 
     * @warning This is actually just a nibble, so anything greater than 15 will be cut off after 4 bits.
     */ 
    uint8_t AddressLength;
    
    /** @brief Length in Bytes of the memory size. 
     * 
     * @warning This is actually just a nibble, so anything greater than 15 will be cut off after 4 bits.
     */ 
    uint8_t SizeLength;
} MemoryDefinition;

/* Interfaces ****************************************************************/
/**
 * Prepares the Address and Length Format Identifier by truncating the AddressLength and SizeLength
 * and writing the corresponding nibbles.
 * 
 * Takes the AddressLength and SizeLength of the @ref MemoryDefinition, masks them with @c 0x0F and saves it into one byte,
 * according to e.g. @b ISO @b 14229-1 @b Table @b 152 @c addressAndLengthFormatIdentifier.
 * 
 * @param memdef The memory definition where address and memory size should be compiled into the addressAndLengthFormatIdentifier
 * 
 * @returns The valid addressAndLengthFormatIdentifier to use in a Memory Access Request.
 */
uint8_t MemoryDefinition_getAddressAndLengthFormatIdentifier(MemoryDefinition *memdef);

#ifdef __cplusplus
}
#endif


#endif /* UDS_MEMORY_DEFINITION_H_ */
/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
