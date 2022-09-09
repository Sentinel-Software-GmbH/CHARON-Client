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
 *  Created on: Tue Jul 28 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup Config
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

/* Includes ******************************************************************/

#include <stdio.h>

/* Timings *******************************************************************/

#define P2_DEFAULT              100U
#define P2_STAR_DEFAULT         300U
#define NON_DEFAULT_SESSION_TIMEOUT 2000U

/* Constants *****************************************************************/

#define MAX_ASYNC_MESSAGES      5U
#define PROGRAMMING_BAUD_RATE   9600U

/* OS Plug Functions *********************************************************/

#define UDS_MUTEX_LOCK()
#define UDS_MUTEX_UNLOCK()

#define UDS_LOG_INFO(x, ...)         printf("[UDS Client] Info: " x "\n", ##__VA_ARGS__)
#define UDS_LOG_WARNING(x, ...)      printf("[UDS Client] Warning: " x "\n", ##__VA_ARGS__)
#define UDS_LOG_ERROR(x, ...)        printf("[UDS Client] Error: " x "\n", ##__VA_ARGS__)

/* Types *********************************************************************/

/* Interfaces ****************************************************************/

#define str(x) #x
#define xstr(x) str(x)

#endif /* UDS_CLIENT_CONFIG_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
