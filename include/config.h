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
 *  Created on: Tue Jul 28 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @defgroup ComLogic
 * @{
 * @file $Filename$.h
 * Brief Description.
 * Detailed Description
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_CLIENT_CONFIG_H_
#define UDS_CLIENT_CONFIG_H_

/* Timings *******************************************************************/

/** The server has to answer the client within this timerange */
#define P2_DEFAULT              100U
/** Extended server response timeout. */
#define P2_STAR_DEFAULT         300U
/** Timeout of a non-default Session, where the Client needs to send a Tester Present Request. */
#define NON_DEFAULT_SESSION_TIMEOUT 2000U

/* Constants *****************************************************************/

/** Maximum amount of Asynchronous Messages in the receive buffer.
 * @note Memory Size of one Async Buffer Entry is 1 Byte + sizeof(FunctionPointer)
 */
#define MAX_ASYNC_MESSAGES      5U

/** Vendor specific Baudrate of the programming setup */
#define PROGRAMMING_BAUD_RATE   9600U

/* OS Plug Functions *********************************************************/

/** Optional implementation of a mutex lock function. */
#define UDS_MUTEX_LOCK()
/** Optional implementation of a mutex unlock function */
#define UDS_MUTEX_UNLOCK()

/** Optional implementation of a logging functions in a info context */
#define UDS_LOG_INFO(x, ...)
/** Optional implementation of a logging functions in a warning context */
#define UDS_LOG_WARNING(x, ...)
/** Optional implementation of a logging functions in a error context */
#define UDS_LOG_ERROR(x, ...)

/* Types *********************************************************************/

/* Interfaces ****************************************************************/

/** Utility functions to provide a string representation of an enumeration. */
#define str(x) #x
#define xstr(x) str(x)

#endif /* UDS_CLIENT_CONFIG_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
