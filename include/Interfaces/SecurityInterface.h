/****************************************************
 *  SecurityInterface.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Interface SecurityInterface       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_4EDD4C82_621C_486a_B2ED_71902C3D2463__INCLUDED_)
#define EA_4EDD4C82_621C_486a_B2ED_71902C3D2463__INCLUDED_


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
 * 
 * @return An encrypted message.
 */
typedef uint8_t*(*encryptFunc)(uint8_t* message, uint32_t length);

/**
 * Prototype of an decryption Function.
 * 
 * It's in the responsibility of the user to provide keys, or any other required data to decrypt the message, inside this function.
 * @param message The encrypted message.
 * 
 * @return A decrypted message.
 */
typedef uint8_t*(*decryptFunc)(uint8_t* message, uint32_t length);

/**
 * Provides Security functions to encrypt and decrypt byte arrays.
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


#endif /*!defined(EA_4EDD4C82_621C_486a_B2ED_71902C3D2463__INCLUDED_)*/
 