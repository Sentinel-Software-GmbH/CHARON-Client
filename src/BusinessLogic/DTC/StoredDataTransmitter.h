/****************************************************
 *  StoredDataTransmitter.h                                         
 *  Created on: 16-Jul-2020 09:30:00                      
 *  Implementation of the Class StoredDataTransmitter       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_440C155A_D2E9_4389_BC1B_65E57D4858B4__INCLUDED_)
#define EA_440C155A_D2E9_4389_BC1B_65E57D4858B4__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

void clearDiagnosticInformation(uint32_t groupOfDTC);
/**
 * Divide by MANY subfunctions
 */
void readDTCInformation();


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_440C155A_D2E9_4389_BC1B_65E57D4858B4__INCLUDED_)*/
 