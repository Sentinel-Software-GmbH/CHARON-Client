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
 * @file ComInterface.h
 * Includes the definition of a communication socket.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_COM_INTERFACE_H_
#define UDS_COM_INTERFACE_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/** @brief Takes a uds message starting at SID and send it to the server.
 * The user should implement the uds conform transport protocol (or if necessary the application protocol frame).
 * 
 * This will get called any time a request is send.
 * 
 * @note Implement the uds conform transport protocol here.
 * Refer to @b ISO @b 14229-3,-4,-5,-6,-7 @c UDSon... Standard Documents.
 * 
 * @param buffer The data to be sent. This is the inner message, this does not include the application layer protocol frames.
 * @param length Size of the data in bytes.
 * @return How many bytes have been sent. Returns a negative number when an error ocurred.
 */
typedef int32_t (*sendFunc)(uint8_t* data, uint32_t length);

/** @brief Should only receive the A_DATA part of the response message.
 * The user should implement the uds conform transport protocol (or if necessary the application protocol frame).
 * 
 * This will get called any time a request is send.
 * This should not be blocking, because we still need to meet certain timing requirements,
 * instead the function should return false, when no message is available.
 * 
 * @note Implement the uds conform transport protocol here. Only write the A_DATA part into the buffer.
 * Refer to @b ISO @b 14229-3,-4,-5,-6,-7 @c UDSon... Standard Documents.
 * 
 * @param buffer The buffer of the data to be received, only write the A_DATA into this buffer.
 * @param count Tries to read up to @c count bytes.
 * @return How many bytes have been read. If it's negative, there was an error.
 */
typedef int32_t (*recvFunc)(uint8_t* buffer, uint32_t count);

/** @brief Adjusts the Baudrate of the Connection.
 * 
 * After a LinkControl Request was successful, the baudrate of the connection
 * needs to be adjusted to the new connection Speed.
 * So the Interface must provide a function to adjust the baudrate.
 * 
 * @note Depending on the Server this might be optional.
 * 
 * @param speed Baudrate in B/s
 * @return True, if it succeeded.
 */
typedef bool (*setSpeedFunc)(uint32_t speed);

/** @brief Provides Functions to communicate through the user implemented connection driver.
 * @req S03 Interface for Communication Sockets
*/
typedef struct ComInterface_public {
    /** @brief Takes a uds message starting at SID and send it to the server.
     * The user should implement the uds conform transport protocol (or if necessary the application protocol frame).
     * 
     * This will get called any time a request is send.
     * 
     * @note Implement the uds conform transport protocol here.
     * Refer to @b ISO @b 14229-3,-4,-5,-6,-7 @c UDSon... Standard Documents.
     */
    sendFunc send;
    /**
     * @brief Should only receive the A_DATA part of the response message.
     * The user should implement the uds conform transport protocol (or if necessary the application protocol frame).
     * 
     * This will get called any time a request is send.
     * 
     * @warning This needs to be NON-BLOCKING.
     * @note Implement the uds conform transport protocol here. Only write the complete A_DATA part into the buffer.  
     * Refer to @b ISO @b 14229-3,-4,-5,-6,-7 @c UDSon... Standard Documents.
     */
    recvFunc receive;
    /** @brief Adjusts the Baudrate of the Connection.
     * 
     * After a LinkControl Request was successful, the baudrate of the connection
     * needs to be adjusted to the new connection Speed.
     * So the Interface must provide a function to adjust the baudrate.
     * 
     * @note Depending on the Server this might be optional.
     */
    setSpeedFunc setSpeed;
    /** @brief The Ability to adjust the Baudrate of the Interface.
     * 
     * If the Interface cannot change its Baudrate, there is no use to send a LinkControl request.
     * So the usage of LinkControl should not allowed.
     * 
     */
    bool speedIsAdjustable;
} ComInterface;


#ifdef __cplusplus
}
#endif


#endif /* UDS_COM_INTERFACE_H_ */
 