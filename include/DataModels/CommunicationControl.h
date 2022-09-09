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
 *  Created on: Wed Jul 29 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup DataModels
 * @{
 * @file CommunicationControl.h
 * Includes a user friendly representation of the Communication Controls and Network Types.
 * 
 * Check ISO 14229-1 Chapter 9.5 Table 54
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef _UDS_COMMUNICATION_CONTROL_H_
#define _UDS_COMMUNICATION_CONTROL_H_

/* Includes ******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/** @brief How the Server should modify the <tt>Communication Type</tt>
 * @note ISO 14229-1 Chapter 9.5
 */
typedef enum CommunicationControlSubfunction_public {
    UDS_ComCtrl_enableRxAndTx = 0x00,                                       /**< Enable RX and TX Channels on the Server */ 
    UDS_ComCtrl_enableRxAndDisableTx = 0x01,                                /**< Enable RX and Disable TX Channels on the Server*/
    UDS_ComCtrl_disableRxAndEnableTx = 0x02,                                /**< Disable RX and Enable TX Channels on the Server */
    UDS_ComCtrl_disableRxAndTx = 0x03,                                      /**< Disable RX and TX Channels on the Server */
    UDS_ComCtrl_enableRxAndDisableTxWithEnhancedAddressInformation = 0x04,  /**< Enable RX and Disable TX Channels while using vendor-specific Enhanced Address Information on the Server */
    UDS_ComCtrl_enableRxAndTxWithEnhancedAddressInformation = 0x05          /**< Enable RX and TX Channels while using vendor-specific Enhanced Address Information on the Server */
} UDS_CommunicationControlSubfunction_t;

/** @brief Communication Type of the Server that should be modified
 * @note ISO 14229-1 Chapter 9.5
 */
typedef enum Com_public {
    UDS_Com_normalCommunicationMessages = 0x01,                                             /**< This value references all application-related communication (interapplication signal exchange between multiple in-vehicle servers). @note ISO 14229-1 Pg. 333 */
    UDS_Com_networkManagementCommunicationMessages = 0x02,                                  /**< This value references all network management related communication. @note ISO 14229-1 Pg. 333 */
    UDS_Com_networkManagementCommunicationMessagesAndNormalCommunicationMessages = 0x03     /**< This value references all network management and application-related communication. @note ISO 14229-1 Pg. 333 */
} UDS_CommunicationType_t;

/* Types *********************************************************************/

/* Interfaces ****************************************************************/

#endif // _UDS_COMMUNICATION_CONTROL_H_
/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/