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
 * @file MemoryDefinition.h
 * Includes the representation of all ISO specified UDS Sessions and a formal description of a session with its timeouts.
 * 
 * Check ISO 14229-1 Chapter 9.2 Table 25
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_SESSION_H_
#define UDS_SESSION_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @brief Representation of every possible ISO specified Session on the Server. */
typedef enum SessionType_public
{
    UDS_Session_Reserved_00 = 0x00,     /**< ISO Reserved */
    UDS_Session_Default,                /**< Default Session. */
    UDS_Session_Programming,            /**< Session to enable the Programming Logic on the Server */
    UDS_Session_Extended,               /**< Session with extended rights. */
    UDS_Session_SafetySystem,           /**< Enables all diagnostic services required to support safety system related functions (e.g., airbag deployment). */
} UDS_SessionType_t;

/** @brief Formal Description of a Session and its relevant Timings */
typedef struct Session_public
{
    UDS_SessionType_t session;          /**< Session Type as described in @ref @c UDS_SessionType_t */
    uint16_t p2;                        /**< Timeout for the initial answer. 1ms Resolution. */
    uint16_t p2_star;                   /**< Timeout for the extended answer. 10ms Resolution. */
} UDS_Session_t;


#ifdef __cplusplus
}
#endif


#endif /* UDS_SESSION_H_ */
 