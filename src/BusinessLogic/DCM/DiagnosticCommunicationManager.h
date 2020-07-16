/****************************************************
 *  DiagnosticCommunicationManager.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class DiagnosticCommunicationManager       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_D8733EBF_401F_4e54_98DB_F39301A5207A__INCLUDED_)
#define EA_D8733EBF_401F_4e54_98DB_F39301A5207A__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include "SecurityInterface.h"

SecurityInterface *m_SecurityInterface;


uint8_t DiagnosticSessionControl(uint8_t session, uint16_t P2_server_max, uint16_t P2_star_server_max);
uint8_t ECUReset(uint8_t resetType);
uint8_t SecurityAccess(uint8_t function, byte[] securityParameter, uint8_t parameterLength);
/**
 * Do we have to implement this?
 * Or is it part of the Specific Com Unit?
 */
void CommunicationControl();
uint8_t TesterPresent();
/**
 * Might be required
 */
void AccessTimingParameter();
uint8_t SecuredDataTransmission(byte* data);
uint8_t ControlDTCSetting(uint8_t subfunction, byte[] data);
uint8_t ResponseOnEvent(uint8_t event, boolean storeEvent, uint8_t eventWindowTime, uint8_t[10] eventTypeRecord, uint8_t serviceToRespondTo, uint8_t* serviceParameter);
void LinkControl();
boolean Init(struct ComInterface Com, struct SecurityInterface Security);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_D8733EBF_401F_4e54_98DB_F39301A5207A__INCLUDED_)*/
 