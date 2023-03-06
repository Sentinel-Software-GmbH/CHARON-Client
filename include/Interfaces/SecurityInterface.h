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
 * @addtogroup Interfaces
 * @{
 * @file SecurityInterface.h
 * Includes the definition of an interface to the security layer.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_SECURITY_INTERFACE_H_
#define UDS_SECURITY_INTERFACE_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * Prototype of an encryption Function.
 * 
 * It's in the responsibility of the user to provide keys, or any other required data to encrypt the message, inside this function.
 * 
 * @param message The byte array to be encoded.
 * @param length length of the message in bytes.
 * @return An encrypted message.
 */
typedef uint8_t*(*encryptFunc)(uint8_t* message, uint32_t length);

/**
 * Prototype of an decryption Function.
 * 
 * It's in the responsibility of the user to provide keys, or any other required data to decrypt the message, inside this function.
 * @param message The encrypted message.
 * @param length length of the message in bytes.
 * @return A decrypted message.
 */
typedef uint8_t*(*decryptFunc)(uint8_t* message, uint32_t length);

/**
 * Provides Security functions to encrypt and decrypt byte arrays.
 * 
 * @req S05 Interface for Security Layer
 */
typedef struct SecurityInterface_public {
    
    /** @brief Encrypt the message.
     * 
     * This is manufacturer and vehicle dependent.
     * The user needs to implement the encryption routine if they want to use a secured connection.
     * This will be called everytime a secured data transmission is used.
     * 
     * @note The user should implement a fast encryption algorithm since this will be called synchronous.
     */
    encryptFunc encrypt;
    
    /** @brief Decrypt the message.
     * 
     * This is manufacturer and vehicle dependent.
     * The user needs to implement the encryption routine if they want to use a secured connection.
     * This will be called everytime a secured data transmission is used.
     * 
     * @note The user should implement a fast encryption algorithm since this will be called synchronous.
     */
    decryptFunc decrypt;
} SecurityInterface;

#ifdef __cplusplus
}
#endif


#endif /* UDS_SECURITY_INTERFACE_H_ */
 