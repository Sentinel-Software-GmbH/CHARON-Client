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
 * @file ErrorCode.h
 * Includes a representation for different error codes that can come up.
 * 
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/
#ifndef ERROR_CODE_H_
#define ERROR_CODE_H_

/* Includes ******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/** @brief A representation of all the Errors that the Client and Server could have. */
typedef enum ErrorCode_public {
    /** @brief Everything was OK. */
    E_OK,
    /** @brief The Server does not respond. */
    E_NotResponding,
    /** @brief The Server replied with a negative response. */
    E_NegativeResponse,
    /** @brief The Server signaled that it needs more time to handle this request. */
    E_Pending,
    /** @brief The Communication Manager is currently waiting for an answer. */
    E_Busy,
    /** @brief This Request is not supported by the client. */
    E_NotSupported,
    /** @brief The Communication Link Speed could not be adjusted because of an error. */
    E_ComSpeedNotAdjusted,
    /** @brief Received an unexpected response from the server. */
    E_Unexpected,
    /** @brief The message was too long for the Static TXBuffer */
    E_MessageTooLong,
#ifndef DOXY_SKIP
    /** @brief Amount of all possible Errorcodes. */
    ErrorCode_amount
#endif
} UDS_Client_Error_t;

/**
 * @brief Function that returns Errorcodes as a Sting.
 * 
 * @param code possible Errorcodes @ref UDS_Client_Error_t.
 * @return const char* Errorcode a a string.
 */
const char * ErrorCode_getString(UDS_Client_Error_t code);
/* Interfaces ****************************************************************/


#endif // ERROR_CODE_H_
/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
