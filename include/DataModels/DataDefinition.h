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

typedef struct DataDefinition_public {
    uint16_t DID;
    /**
     * 0x01 for the first byte. First Byte is NOT 0x00.
     */
    uint8_t firstBytePosition;
    uint8_t memorySize;
} DataDefinition;



#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_887CA2F3_18C0_457b_9C74_AABCA202DABE__INCLUDED_)*/
 