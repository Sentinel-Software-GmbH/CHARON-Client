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
#include "DataModels/SID.h"
#include "Interfaces/CallbackInterface.h"
#include "DataModels/ResetTypes.h"
#include "DataModels/ComparisonLogic.h"
#include "DataModels/TimerRates.h"
#include "DataModels/BaudRates.h"
#include "DataModels/CommunicationControl.h"
#include <stdbool.h>

/**
 * 
 */
bool UDS_DCM_DiagnosticSessionControl(UDS_SessionType_t session, UDS_callback callback);
bool UDS_DCM_ECUReset(UDS_Reset_t resetType, UDS_callback callback);
bool UDS_DCM_SecurityAccess(uint8_t function, uint8_t *securityParameter, uint8_t parameterLength, UDS_callback callback);
bool UDS_DCM_CommunicationControl(UDS_CommunicationControlSubfunction_t comCtrl, UDS_CommunicationType_t communicationType, uint8_t subnet, uint16_t nodeIdentificationNumber, UDS_callback callback);
bool UDS_DCM_AccessTimingParameter(uint16_t P2, uint16_t P2_star, UDS_callback callback);
bool UDS_DCM_SecuredDataTransmission(uint8_t *data, uint32_t length, UDS_callback callback);
bool UDS_DCM_ControlDTCSetting(uint8_t subfunction, uint8_t *data, uint32_t length, UDS_callback callback);
bool UDS_DCM_ResponseOnCustomEvent(uint8_t event, bool isPersistent, uint8_t eventWindowTime, uint8_t* eventTypeRecord, uint8_t eventTypeRecordLength, uint8_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);
bool UDS_DCM_ResponseOnDTCStatusChange(bool isPersistent, uint8_t eventWindowTime, uint8_t DTC_Status_Mask, SID_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);
bool UDS_DCM_ResponseOnTimerInterrupt(bool isPersistent, uint8_t eventWindowTime, UDS_TimerRates_t timerRate, SID_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);
bool UDS_DCM_ResponseOnChangeOfDataIdentifier(bool isPersistent, uint8_t eventWindowTime, uint16_t dataIdentifier, SID_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);
bool UDS_DCM_ResponseOnComparisonOfValues(bool isPersistent, uint8_t eventWindowTime, uint16_t dataIdentifier, ComparisonLogic_t logic, uint32_t reference, uint8_t hysteresis, bool comparisonWithSign, uint8_t lengthOfDID, uint16_t DIDoffset, uint8_t serviceToRespondTo, uint16_t comparedDID, UDS_callback callback, UDS_callback response_callback);
bool UDS_DCM_StartResponseOnEvents(UDS_callback callback);
bool UDS_DCM_StopResponseOnEvents(UDS_callback callback);
bool UDS_DCM_ClearResponseOnEvents(UDS_callback callback);
bool UDS_DCM_GetActiveResponseEvents(UDS_callback callback);
bool UDS_DCM_LinkControl_verifyWithFixedParameter(UDS_Baudrate_t linkControlMode, UDS_callback callback);
bool UDS_DCM_LinkControl_verifyWithSpecificParameter(uint32_t modeParameter, UDS_callback callback);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_D8733EBF_401F_4e54_98DB_F39301A5207A__INCLUDED_)*/
 