/****************************************************
 *  Routine.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class Routine       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_8000A827_0A91_45b2_AE8E_2116EEC82217__INCLUDED_)
#define EA_8000A827_0A91_45b2_AE8E_2116EEC82217__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

void routineControl(uint8_t routineCommand, uint16_t routineIdentifier, uint8_t* routineControlOptionRecord, uint8_t routineControlOptionsLength);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_8000A827_0A91_45b2_AE8E_2116EEC82217__INCLUDED_)*/
 