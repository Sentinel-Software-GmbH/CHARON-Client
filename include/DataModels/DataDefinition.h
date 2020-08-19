/****************************************************
 *  DataDefinition.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class DataDefinition       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_887CA2F3_18C0_457b_9C74_AABCA202DABE__INCLUDED_)
#define EA_887CA2F3_18C0_457b_9C74_AABCA202DABE__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @brief Data Structure of all the Information the Server needs to access a Data Identifier */
typedef struct DataDefinition_public {
    /** Data Identifier. This is Server/Vendor/Manufacturer specific.
     * Can also be a dynamically defined Identifier. */
    uint16_t DID;
    /** @brief Offset in Data Identifier.
     * @warning 0x01 for the first byte. First Byte is NOT 0x00.
     */
    uint8_t firstBytePosition;
    /** Size of underlying Data */
    uint8_t memorySize;
} DataDefinition;



#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_887CA2F3_18C0_457b_9C74_AABCA202DABE__INCLUDED_)*/
 