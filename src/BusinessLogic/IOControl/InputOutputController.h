/****************************************************
 *  InputOutputController.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class InputOutputController       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_70138783_FAD5_499d_A07C_7FC49B646276__INCLUDED_)
#define EA_70138783_FAD5_499d_A07C_7FC49B646276__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

void InputOutputControlByIdentifier(uint16_t dataIdentifier, uint8_t inputOutputControlParameter, uint8_t* controlStates, uint8_t controlStatesLength, uint8_t* controlMasks, uint8_t controlMasksLength);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_70138783_FAD5_499d_A07C_7FC49B646276__INCLUDED_)*/
 