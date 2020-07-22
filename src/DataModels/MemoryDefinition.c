/****************************************************
 *  MemoryDefinition.c                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class MemoryDefinition       
 *  Original author: Steven Inacio                     
 ****************************************************/

#include "MemoryDefinition.h"
#include <stdint.h>

uint8_t MemoryDefinition_getAddressAndLengthFormatIdentifier(MemoryDefinition * memdef) {
    return ((memdef->SizeLength & 0x0F) << 4) | (memdef->AddressLength & 0x0F);
}

