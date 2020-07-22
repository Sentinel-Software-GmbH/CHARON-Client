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

#include "Interfaces/SecurityInterface.h"
#include "DataModels/Session.h"
#include "DataModels/ErrorCode.h"
#include "DataModels/ResponseCode.h"
#include "DataModels/SID.h"
#include "Interfaces/CallbackInterface.h"
#include <stdbool.h>

bool DiagnosticSessionControl(UDS_SessionType_t session, uint16_t P2_server_max, uint16_t P2_star_server_max, UDS_callback callback);
bool ECUReset(uint8_t resetType, uint8_t *tx, uint8_t *rx);
bool SecurityAccess(uint8_t function, uint8_t *securityParameter, uint8_t parameterLength, uint8_t *tx, uint8_t *rx);
/**
 * Do we have to implement this?
 * Or is it part of the Specific Com Unit?
 */
void CommunicationControl();
/**
 * Might be required
 */
void AccessTimingParameter();
uint8_t SecuredDataTransmission(uint8_t *data);
uint8_t ControlDTCSetting(uint8_t subfunction, uint8_t *data);
uint8_t ResponseOnEvent(uint8_t event, bool storeEvent, uint8_t eventWindowTime, uint8_t eventTypeRecord[10], uint8_t serviceToRespondTo, uint8_t* serviceParameter);
void LinkControl();
bool DCM_Init(SecurityInterface_t *security);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_D8733EBF_401F_4e54_98DB_F39301A5207A__INCLUDED_)*/
 