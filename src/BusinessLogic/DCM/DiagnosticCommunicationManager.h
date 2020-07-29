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
#include "DataModels/ResetTypes.h"
#include "DataModels/ComparisonLogic.h"
#include "DataModels/TimerRates.h"
#include "DataModels/BaudRates.h"
#include "DataModels/CommunicationControl.h"
#include <stdbool.h>

bool DiagnosticSessionControl(UDS_SessionType_t session, UDS_callback callback);
bool ECUReset(UDS_Reset_t resetType, UDS_callback callback);
bool SecurityAccess(uint8_t function, uint8_t *securityParameter, uint8_t parameterLength, UDS_callback callback);
bool CommunicationControl(CommunicationControlSubfunction_t comCtrl, Com_t communicationType, uint8_t subnet, uint16_t nodeIdentificationNumber, UDS_callback callback);
bool AccessTimingParameter(uint16_t P2, uint16_t P2_star, UDS_callback callback);
bool SecuredDataTransmission(uint8_t *data, uint32_t length, UDS_callback callback);
bool ControlDTCSetting(uint8_t subfunction, uint8_t *data, uint32_t length, UDS_callback callback);
bool ResponseOnCustomEvent(uint8_t event, bool storeEvent, uint8_t eventWindowTime, uint8_t* eventTypeRecord, uint8_t eventTypeRecordLength, uint8_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);
bool ResponseOnDTCStatusChange(bool IsPersistent, uint8_t eventWindowTime, uint8_t DTC_Status_Mask, SID_t service_to_respond_to, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);
bool ResponseOnTimerInterrupt(bool IsPersistent, uint8_t eventWindowTime, TimerRates_t timer_rate, SID_t service_to_respond_to, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);
bool ResponseOnChangeOfDataIdentifier(bool IsPersistent, uint8_t eventWindowTime, uint16_t DataIdentifier, SID_t service_to_respond_to, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);
bool ResponseOnComparisonOfValues(bool IsPersistent, uint8_t eventWindowTime, uint16_t DataIdentifier, ComparisonLogic_t logic, uint32_t reference, uint8_t hysteresis, bool comparisonWithSign, uint8_t lengthOfDID, uint16_t DIDoffset, uint8_t serviceToRespondTo, uint16_t comparedDID, UDS_callback callback, UDS_callback response_callback);
bool StartResponseOnEvents(UDS_callback callback);
bool StopResponseOnEvents(UDS_callback callback);
bool ClearResponseOnEvents(UDS_callback callback);
bool GetActiveResponseEvents(UDS_callback callback);
bool LinkControl_verifyWithFixedParameter(UDS_Baudrate_t linkControlMode, UDS_callback callback);
bool LinkControl_verifyWithSpecificParameter(uint32_t modeParameter, UDS_callback callback);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_D8733EBF_401F_4e54_98DB_F39301A5207A__INCLUDED_)*/
 