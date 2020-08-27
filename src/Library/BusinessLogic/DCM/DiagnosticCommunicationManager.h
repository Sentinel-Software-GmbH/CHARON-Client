/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 Steven Inácio
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup BusinessLogic
 * @{
 * @file
 * Implementation of the Diagnostic and Communication Management Functional
 * Unit. The detailed specifications can be found in @b ISO @b 14229-1
 * Chapter 9.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_DIAGNOSTIC_COMMUNICATION_MANAGER_H_
#define UDS_DIAGNOSTIC_COMMUNICATION_MANAGER_H_


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

/** @brief Switches Diagnostic Sessions on the server.
 * @param session Session to change to.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 */
bool UDS_DCM_DiagnosticSessionControl(UDS_SessionType_t session, UDS_callback callback);

/** @brief Forces server to perform a reset.
 * @param resetType What kind of reset should be used.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_ECUReset(UDS_Reset_t resetType, UDS_callback callback);

/** @brief Request security seed or send security answer.
 * @param function Uneven functions are used to request a seed, even functions are used to send the Key.
 * @param securityParameter Provides additional information to the server, or the security key to unlock the server.
 * @param parameterLength Size of the securityParameter in bytes.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_SecurityAccess(uint8_t function, uint8_t *securityParameter, uint8_t parameterLength, UDS_callback callback);

/** @brief Control the communication on the server.
 * @param comCtrl How to control the communication on the server.
 * @param communicationType What communication will be controlled.<br>@b NOTE: communicationType and subnet build one byte of bit-encoded data.
 * @param subnet The subnet to be controlled.<br>@b NOTE: communicationType and subnet build one byte of bit-encoded data.<br><table><tr><th>Value</th><th>Function</th></tr><tr><td>0x0</td><td>Disables the complete communicationType</td></tr><tr><td>0x1-0xE</td><td>Specific Subnets.</td></tr><tr><td>0xF</td><td>disables the subnet where the request was received on</td></tr></table>
 * @param nodeIdentificationNumber This is used to identify a node on a sub-network somewhere in the vehicle.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_CommunicationControl(UDS_CommunicationControlSubfunction_t comCtrl, UDS_CommunicationType_t communicationType, uint8_t subnet, uint16_t nodeIdentificationNumber, UDS_callback callback);

/* TODO: Access Timing Parameter Service */
bool UDS_DCM_AccessTimingParameter(uint16_t P2, uint16_t P2_star, UDS_callback callback);

/** @brief Stop or resume the updating of DTC status bits.
 * @param subfunction The DTC Control Type you want to use.
 * @param data List of DTCs or additional parameter for a vendor specific service.
 * @param length Size of the data parameter.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_ControlDTCSetting(uint8_t subfunction, uint8_t *data, uint32_t length, UDS_callback callback);

/** @brief Setup a response on a custom vendor specific event.
 * @param event Event identifier of the custom event.
 * @param isPersistent Indicates if a requested event logic shall be
 * stored persistently till the event logic is explicitly cleared (via clearResponseOnEvent) or the event logic is overwritten.
 * @param eventWindowTime 0x00-0x01 are ISO reserved, 0x02 is Infinite and 0x03-0x7F is manufacturer specific.
 * @param eventTypeRecord Additional parameter and information for the event.
 * @param eventTypeRecordLength Size in bytes of eventTypeRecord.
 * @param serviceToRespondTo Service the server will execute whenever the specified event occured.
 * @param serviceParameter Additional parameter for the service that gets executed.
 * @param serviceParameterLength Size in bytes of the serviceParameter.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @param response_callback The function that gets executed whenever an Event has occured and the client has received the server resonse.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_ResponseOnCustomEvent(uint8_t event, bool isPersistent, uint8_t eventWindowTime, uint8_t* eventTypeRecord, uint8_t eventTypeRecordLength, uint8_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);

/** @brief Setup a response on a DTC status change.
 * @param isPersistent Indicates if a requested event logic shall be
 * stored persistently till the event logic is explicitly cleared (via clearResponseOnEvent) or the event logic is overwritten.
 * @param eventWindowTime 0x00-0x01 are ISO reserved, 0x02 is Infinite and 0x03-0x7F is manufacturer specific.
 * @param DTC_Status_Mask 
 * @param serviceToRespondTo Service the server will execute whenever the specified event occured.
 * @param serviceParameter Additional parameter for the service that gets executed.
 * @param serviceParameterLength Size in bytes of the serviceParameter.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @param response_callback The function that gets executed whenever an Event has occured and the client has received the server resonse.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_ResponseOnDTCStatusChange(bool isPersistent, uint8_t eventWindowTime, uint8_t DTC_Status_Mask, SID_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);

/** @brief Setup a response on a Timer Interrupt.
 * @param isPersistent Indicates if a requested event logic shall be
 * stored persistently till the event logic is explicitly cleared (via clearResponseOnEvent) or the event logic is overwritten.
 * @param eventWindowTime 0x00-0x01 are ISO reserved, 0x02 is Infinite and 0x03-0x7F is manufacturer specific.
 * @param timerRate Time between the events. 
 * @param serviceToRespondTo Service the server will execute whenever the specified event occured.
 * @param serviceParameter Additional parameter for the service that gets executed.
 * @param serviceParameterLength Size in bytes of the serviceParameter.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @param response_callback The function that gets executed whenever an Event has occured and the client has received the server resonse.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_ResponseOnTimerInterrupt(bool isPersistent, uint8_t eventWindowTime, UDS_TimerRates_t timerRate, SID_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);

/** @brief Setup a response on a Timer Interrupt.
 * @param isPersistent Indicates if a requested event logic shall be
 * stored persistently till the event logic is explicitly cleared (via clearResponseOnEvent) or the event logic is overwritten.
 * @param eventWindowTime 0x00-0x01 are ISO reserved, 0x02 is Infinite and 0x03-0x7F is manufacturer specific.
 * @param dataIdentifier Identifier of the data. 
 * @param serviceToRespondTo Service the server will execute whenever the specified event occured.
 * @param serviceParameter Additional parameter for the service that gets executed.
 * @param serviceParameterLength Size in bytes of the serviceParameter.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @param response_callback The function that gets executed whenever an Event has occured and the client has received the server resonse.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_ResponseOnChangeOfDataIdentifier(bool isPersistent, uint8_t eventWindowTime, uint16_t dataIdentifier, SID_t serviceToRespondTo, uint8_t* serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback);

/** @brief Setup a response on a Timer Interrupt.
 * @param isPersistent Indicates if a requested event logic shall be
 * stored persistently till the event logic is explicitly cleared (via clearResponseOnEvent) or the event logic is overwritten.
 * @param eventWindowTime 0x00-0x01 are ISO reserved, 0x02 is Infinite and 0x03-0x7F is manufacturer specific.
 * @param dataIdentifier Identifier of the data to be compared.
 * @param logic Comparison operator to be used.
 * @param reference Reference Value the data identifier will be compared to.
 * @param hysteresis Range of allowed inaccuracy.
 * @param comparisonWithSign Indicator if the values are supposed to be treated as signed values.
 * @param lengthOfDID Size of the DID value in bytes.
 * @param DIDoffset Offset inside the DID.
 * @param serviceToRespondTo Service the server will execute whenever the specified event occured.
 * @param comparedDID DID to be read and compared.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @param response_callback The function that gets executed whenever an Event has occured and the client has received the server resonse.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_ResponseOnComparisonOfValues(bool isPersistent, uint8_t eventWindowTime, uint16_t dataIdentifier, ComparisonLogic_t logic, uint32_t reference, uint8_t hysteresis, bool comparisonWithSign, uint8_t lengthOfDID, uint16_t DIDoffset, uint8_t serviceToRespondTo, uint16_t comparedDID, UDS_callback callback, UDS_callback response_callback);
/** @brief Start the Execution of the set Response on Event Services.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 */
bool UDS_DCM_StartResponseOnEvents(UDS_callback callback);
/** @brief Stop the Execution of the set Response on Event Services.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 */
bool UDS_DCM_StopResponseOnEvents(UDS_callback callback);
/** @brief Clear all set Response on Event Services.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 */
bool UDS_DCM_ClearResponseOnEvents(UDS_callback callback);
/** @brief Receive a list of all set Response on Event Services.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 */
bool UDS_DCM_GetActiveResponseEvents(UDS_callback callback);

/** @brief Control the Communication Link Speed with ISO specified values.
 * @param linkControlMode Specified Baudrate to be set up.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_LinkControl_withFixedParameter(UDS_Baudrate_t linkControlMode, UDS_callback callback);

/** @brief Control the Communication Link Speed with user specified values.
 * @param modeParameter User specified connection speed.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_DCM_LinkControl_WithSpecificParameter(uint32_t modeParameter, UDS_callback callback);


#ifdef __cplusplus
}
#endif


#endif /* UDS_DIAGNOSTIC_COMMUNICATION_MANAGER_H_ */
 