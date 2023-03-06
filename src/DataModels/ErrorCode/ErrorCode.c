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
 * Created on: Mon Aug 24 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup DataModels Data Model Modules
 * @{
 * @file
 * Provides helper functions for UDS_Client_Error_t.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

/* Includes ******************************************************************/

#include "ErrorCode.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/** @brief A representation of all the Errors that the Client and Server could have. */
static const char *ErrorCode_STRING[ErrorCode_amount] = {
    "E_OK",                     /**< Everything was OK. */ 
    "E_NotResponding",          /**< The Server does not respond. */
    "E_NegativeResponse",       /**< The Server replied with a negative response. */
    "E_Pending",                /**< The Server signaled that it needs more time to handle this request. */
    "E_Busy",                   /**< The Communication Manager is currently waiting for an answer. */
    "E_NotSupported",           /**< This Request is not supported by the client. */
    "E_ComSpeedNotAdjusted",    /**< The Communication Link Speed could not be adjusted because of an error. */
    "E_Unexpected",             /**< Received an unexpected response from the server.  */
    "E_MessageTooLong",         /**< The message was too long for the Static TXBuffer */
};

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Private Function Definitions **********************************************/

/* Interfaces  ***************************************************************/

const char * ErrorCode_getString(UDS_Client_Error_t code) 
{
    if(code < 0 || code >= ErrorCode_amount) return "Unknown Error Code";
    return ErrorCode_STRING[code];
}

/* Private Function **********************************************************/




/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
