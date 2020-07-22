/****************************************************
 *  MemoryDefinition.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class MemoryDefinition       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_7EE78724_DD43_4f4e_ACD1_C384E0B642F2__INCLUDED_)
#define EA_7EE78724_DD43_4f4e_ACD1_C384E0B642F2__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * Data Class for a MemoryAddress.
 */
typedef struct MemoryDefinition_public {
    /** @brief The address of the wanted memory block.
     * 
     * This is an Array because it's server dependent how much memory can be accessed.
     * 
     * @warning Please make sure this number has it's MSB first.
     */
    uint8_t* Address;
    
    /** @brief The size of the wanted memory block.
     * 
     * This is an Array because the length of the memory size is dynamic.
     * You should always use the least required byte count for the memory size to keep the frame overhead small.
     * 
     * @warning Please make sure this number has it's MSB first.
     */ 
    uint8_t* Size;

    /** @brief Length in Bytes of the address. 
     * 
     * @warning This is actually just a nibble, so everything greater than 15 will be cut off after 4 bits.
     */ 
    uint8_t AddressLength;
    
    /** @brief Length in Bytes of the memory size. 
     * 
     * @warning This is actually just a nibble, so everything greater than 15 will be cut off after 4 bits.
     */ 
    uint8_t SizeLength;
} MemoryDefinition;

/**
 * Prepares the Address and Length Format Identifier by truncating the AddressLength and SizeLength
 * and writing the corresponding nibbles.
 * 
 * Takes the AddressLength and SizeLength of the @ref @c MemoryDefinition, masks them with @c 0x0F and saves it into one byte,
 * according to e.g. @b ISO @b 14229-1 @b Table @b 152 @c addressAndLengthFormatIdentifier.
 */
uint8_t MemoryDefinition_getAddressAndLengthFormatIdentifier(MemoryDefinition *memdef);

#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_7EE78724_DD43_4f4e_ACD1_C384E0B642F2__INCLUDED_)*/
 