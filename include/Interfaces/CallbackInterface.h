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
 * @defgroup Interfaces
 * @{
 * @file CallbackInterface.h
 * Includes a prototype of a Callback.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef CALLBACK_INTERFACE_H_
#define CALLBACK_INTERFACE_H_
    #include <stdint.h>
    #include "DataModels/ErrorCode.h"

    /** @brief Represents a callback function that this UDS Client can handle.
     * @req S06 Notify application.
    */
    typedef void(*UDS_callback)(UDS_Client_Error_t errorCode, uint8_t* buffer, uint32_t length);
#endif // CALLBACK_INTERFACE_H