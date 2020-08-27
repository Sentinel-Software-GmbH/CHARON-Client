/*
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
 *  Created on: Fri Aug 21 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup DataModels
 * @{
 * @file DataIdentifier.h
 * Adds a representation of all ISO specified Data Identifier.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_DATA_IDENTIFIER_H_
#define UDS_DATA_IDENTIFIER_H_

/* Includes ******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/


/* TODO: Insert all DIDs */
/** @brief All ISO 14229-1 specified DIDs.
 * @note Check ISO 14229-1 Table C.1
 * @warning Only the Starting Address is defined, the Range of the DID can be found as Length under the notes of the documentation of the DID.
 */
typedef enum DID_public {
    /** @brief Remote addresses of all trailer systems independent of their functionality.
     * @note Length of 0x0F
     */
    DID_networkConfigurationDataForTractorTrailerApplicationDataIdentifier = 0xF000,
    /** @brief Reference the vehicle manufacturer specific ECU boot software identification record.
     * @note Length of 0x01
     */
    DID_BootSoftwareIdentificationDataIdentifier = 0xF180,

} UDS_DataIdentifier_t

/* Interfaces ****************************************************************/

#endif /* CHARON_TEMPLATE_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
