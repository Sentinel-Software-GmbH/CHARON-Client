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
 * @defgroup DataModels
 * @{
 * @file DataDefinition.h
 * Includes a Data Struct to gather all relevant data for an DID Access.
 * 
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef EA_887CA2F3_18C0_457b_9C74_AABCA202DABE__INCLUDED_
#define EA_887CA2F3_18C0_457b_9C74_AABCA202DABE__INCLUDED_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    /** @brief Data Structure of all the Information the Server needs to access a Data Identifier */
    typedef struct DataDefinition_public
    {
        /** @brief Data Identifier. This is Server/Vendor/Manufacturer specific.
         * Can also be a dynamically defined Identifier.
         */
        uint16_t DID;
        /** @brief Offset in Data Identifier.
         * @warning 0x01 for the first byte. First Byte is NOT 0x00.
         */
        uint8_t firstBytePosition;
        /** @brief Size of underlying Data. */
        uint8_t memorySize;
    } DataDefinition;

#ifdef __cplusplus
}
#endif

#endif /*!defined(EA_887CA2F3_18C0_457b_9C74_AABCA202DABE__INCLUDED_)*/
