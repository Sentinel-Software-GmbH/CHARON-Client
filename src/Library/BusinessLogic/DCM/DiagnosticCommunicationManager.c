/**
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
 * @addtogroup ComLogic
 * @{
 * @file DiagnosticCommunicationManager.c
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

/* Includes ******************************************************************/

#include "DiagnosticCommunicationManager.h"

#include <stddef.h>
#include <string.h>

#include "SessionAndTransportManager.h"

/* Imports *******************************************************************/

#include "config.h"

/* Constants *****************************************************************/

/** Iso specified baudrate value to actual Bd value converter. */
static const uint32_t baudRateLookup[_UDS_Baudrate_amount] = {
	0U,					  // UDS_BAUDRATE_RESERVED = 0x00,
	9600U,				  // UDS_Baud_PC9600 = 0x01,
	19200U,				  // UDS_Baud_PC19200 = 0x02,
	38400U,				  // UDS_Baud_PC38400 = 0x03,
	57600U,				  // UDS_Baud_PC57600 = 0x04,
	115200U,			  // UDS_Baud_PC115200 = 0x05,
	0U,					  // Reserved = 0x06
	0U,					  // Reserved = 0x07
	0U,					  // Reserved = 0x08
	0U,					  // Reserved = 0x09
	0U,					  // Reserved = 0x0A
	0U,					  // Reserved = 0x0B
	0U,					  // Reserved = 0x0C
	0U,					  // Reserved = 0x0D
	0U,					  // Reserved = 0x0E
	0U,					  // Reserved = 0x0F
	125000U,			  // UDS_Baud_CAN125000 = 0x10,
	250000U,			  // UDS_Baud_CAN250000 = 0x11,
	500000U,			  // UDS_Baud_CAN500000 = 0x12,
	1000000U,			  // UDS_Baud_CAN1000000 = 0x13,
	0U,					  // Reserved = 0x14
	0U,					  // Reserved = 0x15
	0U,					  // Reserved = 0x16
	0U,					  // Reserved = 0x17
	0U,					  // Reserved = 0x18
	0U,					  // Reserved = 0x19
	0U,					  // Reserved = 0x1A
	0U,					  // Reserved = 0x1B
	0U,					  // Reserved = 0x1C
	0U,					  // Reserved = 0x1D
	0U,					  // Reserved = 0x1E
	0U,					  // Reserved = 0x1F
	PROGRAMMING_BAUD_RATE // UDS_Baud_ProgrammingSetup = 0x20,
};

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

/** Save location of the user callback to call later. */
static UDS_callback DSC_user_callback;

/** proposed speed of link control, to change after positive callback */
static uint32_t proposedSpeed;

/* Private Function Definitions **********************************************/

void DSC_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length);
void Reset_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length);
void LinkControl_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length);
void LinkTransition_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length);
void SecureData_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length);

/* Interfaces  ***************************************************************/

bool UDS_DCM_DiagnosticSessionControl(UDS_SessionType_t session, UDS_callback callback)
{
	// No struct or whatever because compiler could pad some bytes in between.
	// attribute__((packed))__ is compiler dependent, and a Macro definition is
	// impossible.
	bool retVal;
	uint8_t message[] = {SID_DiagnosticSessionControl, session};
	if((retVal = STM_Deploy(message, 2, DSC_callback, false)) != false)
		DSC_user_callback = callback;
	return retVal;
}

bool UDS_DCM_ECUReset(UDS_Reset_t resetType, UDS_callback callback)
{
	bool retVal;
	uint8_t message[] = {SID_ECUReset, resetType};
	if((retVal = STM_Deploy(message, 2, Reset_callback, false)) != false)
		DSC_user_callback = callback;
	return retVal;
}

bool UDS_DCM_SecurityAccess(uint8_t function,
					uint8_t *securityParameter,
					uint8_t parameterLength,
					UDS_callback callback)
{
	uint8_t message[2 + parameterLength];
	message[0] = (uint8_t)SID_SecurityAccess;
	message[1] = function;
	memcpy(&message[2], securityParameter, parameterLength);
	return STM_Deploy(message, 2 + parameterLength, callback, false);
}

bool UDS_DCM_CommunicationControl(UDS_CommunicationControlSubfunction_t comCtrl, UDS_CommunicationType_t communicationType, uint8_t subnet, uint16_t nodeIdentificationNumber, UDS_callback callback)
{
	uint8_t message[5];
	message[0] = SID_CommunicationControl;
	message[1] = comCtrl;
	message[2] = ((subnet & 0xF) << 4) | (communicationType & 0x3);
	message[3] = (nodeIdentificationNumber >> 8) & 0xFF;
	message[4] = nodeIdentificationNumber & 0xFF;
	return STM_Deploy(message, 5, callback, false);
}


bool UDS_DCM_ControlDTCSetting(uint8_t subfunction,
					   uint8_t *data,
					   uint32_t length,
					   UDS_callback callback)
{
	uint8_t message[2 + length];
	message[0] = SID_ControlDTCSettings;
	message[1] = subfunction;
	memcpy(&message[2], data, length);
	return STM_Deploy(message, length + 2, callback, false);
}

bool UDS_DCM_AccessTimingParameter(uint16_t P2, uint16_t P2_star, UDS_callback callback){
   	if(callback != NULL) {
		callback(E_NotSupported, NULL, 0);
	}
}

bool UDS_DCM_ResponseOnCustomEvent(uint8_t event,
								   bool isPersistent,
								   uint8_t eventWindowTime,
								   uint8_t *eventTypeRecord,
								   uint8_t eventTypeRecordLength,
								   uint8_t serviceToRespondTo,
								   uint8_t *serviceParameter,
								   uint8_t serviceParameterLength,
								   UDS_callback callback,
								   UDS_callback response_callback
								   )
{
	UDS_LOG_INFO("Sending Response on Custom Event [Event: 0x%02x, StoreEvent: %s, eventWindowTime: 0x%02x, eventTypeRecordLength: %d, serviceToRespondTo: %s, serviceParameterLength: 0x%02x",
				event, isPersistent ? "true": "false", eventWindowTime, eventTypeRecordLength, xstr(serviceToRespondTo), serviceParameterLength);
	uint32_t length = 3 + eventTypeRecordLength + 1 + serviceParameterLength;
	uint8_t message[length];
	uint16_t i = 0;
	message[i++] = SID_ResponseOnEvent;
	message[i++] = isPersistent ? 0x40 | (event & 0x3F) : (event & 0x3F);
	message[i++] = eventWindowTime;
	memcpy(&message[i], eventTypeRecord, eventTypeRecordLength);
	i += eventTypeRecordLength;
	message[i++] = serviceToRespondTo;
	memcpy(&message[i], serviceParameter, serviceParameterLength);
	bool retVal = STM_Deploy(message, length, callback, false);
	retVal &= STM_AsyncDeploy(serviceToRespondTo, response_callback);
	return retVal;
}

bool UDS_DCM_ResponseOnDTCStatusChange(bool isPersistent, uint8_t eventWindowTime, uint8_t DTCStatusMask, SID_t serviceToRespondTo, uint8_t *serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback)
{
	UDS_LOG_INFO("Sending Response on DTC Status Change [StoreEvent: %s, eventWindowTime: 0x%02x, DTC Status Mask: 0x%02x, serviceToRespondTo: %s, serviceParameterLength: 0x%02x",
				isPersistent ? "true": "false", eventWindowTime, DTCStatusMask, xstr(serviceToRespondTo), serviceParameterLength);
	uint32_t length = 5 + serviceParameterLength;
	uint8_t message[length];
	message[0] = SID_ResponseOnEvent;
	message[1] = isPersistent ? 0x01 | 0x40 : 0x01;
	message[2] = eventWindowTime;
	message[3] = DTCStatusMask;
	message[4] = serviceToRespondTo;
	memcpy(&message[5], serviceParameter, serviceParameterLength);
	bool retVal = STM_Deploy(message, length, callback, false);
	retVal &= STM_AsyncDeploy(serviceToRespondTo, response_callback);
	return retVal;
}

bool UDS_DCM_ResponseOnTimerInterrupt(bool isPersistent, uint8_t eventWindowTime, UDS_TimerRates_t timerRate, SID_t serviceToRespondTo, uint8_t *serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback)
{
	UDS_LOG_INFO("Sending Response on Timer Interrupt [StoreEvent: %s, eventWindowTime: 0x%02x, TimerRate: %s, serviceToRespondTo: %s, serviceParameterLength: 0x%02x",
				isPersistent ? "true": "false", eventWindowTime, xstr(timerRate), xstr(serviceToRespondTo), serviceParameterLength);
	uint32_t length = 5 + serviceParameterLength;
	uint8_t message[length];
	message[0] = SID_ResponseOnEvent;
	message[1] = isPersistent ? 0x02 | 0x40 : 0x02;
	message[2] = eventWindowTime;
	message[3] = timerRate;
	message[4] = serviceToRespondTo;
	memcpy(&message[5], serviceParameter, serviceParameterLength);
	bool retVal = STM_Deploy(message, length, callback, false);
	retVal &= STM_AsyncDeploy(serviceToRespondTo, response_callback);
	return retVal;
}

bool UDS_DCM_ResponseOnChangeOfDataIdentifier(bool isPersistent, uint8_t eventWindowTime, uint16_t dataIdentifier, SID_t serviceToRespondTo, uint8_t *serviceParameter, uint8_t serviceParameterLength, UDS_callback callback, UDS_callback response_callback)
{
	UDS_LOG_INFO("Sending Response on DID Change [StoreEvent: %s, eventWindowTime: 0x%02x, DataIdentifier: 0x%04x, serviceToRespondTo: %s, serviceParameterLength: 0x%02x",
				isPersistent ? "true": "false", eventWindowTime, dataIdentifier, xstr(serviceToRespondTo), serviceParameterLength);
	uint32_t length = 6 + serviceParameterLength;
	uint8_t message[length];
	message[0] = SID_ResponseOnEvent;
	message[1] = isPersistent ? 0x03 | 0x40 : 0x03;
	message[2] = eventWindowTime;
	message[3] = (dataIdentifier >> 8) & 0xFF;
	message[4] = 0xFF & dataIdentifier;
	message[5] = serviceToRespondTo;
	memcpy(&message[6], serviceParameter, serviceParameterLength);
	bool retVal = STM_Deploy(message, length, callback, false);
	retVal &= STM_AsyncDeploy(serviceToRespondTo, response_callback);
	return retVal;
}

bool UDS_DCM_ResponseOnComparisonOfValues(bool isPersistent, uint8_t eventWindowTime, uint16_t dataIdentifier, ComparisonLogic_t logic, uint32_t reference, uint8_t hysteresis, bool comparisonWithSign, uint8_t lengthOfDID, uint16_t DIDoffset, uint8_t serviceToRespondTo, uint16_t comparedDID, UDS_callback callback, UDS_callback response_callback)
{
	UDS_LOG_INFO("Sending Response on Comparison of Values [StoreEvent: %s, eventWindowTime: 0x%02x, DID: 0x%04x, Comparison Logic: %s, Reference Value: %d, Hysteresis: %d%%, Signed Comparison: %s, Length of DID: %d, DID Offset: %d, Service to Respond To: %s, Compared DID: 0x%04x]",
				isPersistent ? "true": "false", eventWindowTime, dataIdentifier, xstr(logic), reference, hysteresis, comparisonWithSign ? "true" : "false", lengthOfDID, DIDoffset, xstr(serviceToRespondTo), comparedDID);
	uint8_t message[16]; 
	message[0] = SID_ResponseOnEvent;
	message[1] = isPersistent ? 0x07 | 0x40 : 0x07;
	message[2] = eventWindowTime;
	message[3] = (0xFF00 & dataIdentifier) >> 8;
	message[4] = 0xFF & dataIdentifier;
	message[5] = logic;
	message[6] = (reference >> 24) & 0xFF;
	message[7] = (reference >> 16) & 0xFF;
	message[8] = (reference >> 8) & 0xFF;
	message[9] = reference & 0xFF;
	message[10] = hysteresis;
	// TODO: Design Choice: throw error on more than 32?
	if(lengthOfDID >= 32) lengthOfDID = 0x00;
	uint16_t localization = (comparisonWithSign ? 0x80 : 0x00) | ((lengthOfDID & 0x1F) << 10) | (DIDoffset & 0x3F);
	message[11] = (localization >> 8) & 0xFF;
	message[12] = localization & 0xFF;
	message[13] = serviceToRespondTo;
	message[14] = (comparedDID >> 8) & 0xFF;
	message[15] = comparedDID & 0xFF;
	bool retVal = STM_Deploy(message, 16, callback, false);
	retVal &= STM_AsyncDeploy(serviceToRespondTo, response_callback);
	return retVal;
}

bool UDS_DCM_StartResponseOnEvents(UDS_callback callback)
{
	uint8_t message[] = {SID_ResponseOnEvent, 0x05};
	return STM_Deploy(message, 2, callback, false);
}

bool UDS_DCM_StopResponseOnEvents(UDS_callback callback)
{
	uint8_t message[] = {SID_ResponseOnEvent, 0x00};
	return STM_Deploy(message, 2, callback, false);
}

// TODO: Clear Async Queue in STM
bool UDS_DCM_ClearResponseOnEvents(UDS_callback callback)
{
	uint8_t message[] = {SID_ResponseOnEvent, 0x06};
	return STM_Deploy(message, 2, callback, false);
}

bool UDS_DCM_GetActiveResponseEvents(UDS_callback callback)
{
	uint8_t message[] = {SID_ResponseOnEvent, 0x04};
	return STM_Deploy(message, 2, callback, false);
}

bool UDS_DCM_LinkControl_withFixedParameter(UDS_Baudrate_t linkControlMode, UDS_callback callback)
{
	if (!STM_SpeedIsAdjustable())
	{
		if(callback != NULL)
			callback(E_NotSupported, NULL, 0);
		return false;
	}
	proposedSpeed = baudRateLookup[linkControlMode];
	uint8_t message[3] = {SID_LinkControl, 0x01, linkControlMode};
	DSC_user_callback = callback;
	return STM_Deploy(message, 3, LinkControl_callback, false);
}

bool UDS_DCM_LinkControl_WithSpecificParameter(uint32_t modeParameter, UDS_callback callback)
{
	if (!STM_SpeedIsAdjustable())
	{
		if(callback != NULL)
			callback(E_NotSupported, NULL, 0);
		return false;
	}
	proposedSpeed = modeParameter;
	uint8_t message[5] = {SID_LinkControl, 0x01, (modeParameter >> 16) & 0xFF, (modeParameter >> 8) & 0xFF, modeParameter & 0xFF};
	DSC_user_callback = callback;
	return STM_Deploy(message, 5, LinkControl_callback, false);
}

// TODO: SecuredDataTransmission einstellen
bool activateSecuredDataTransmission() {
	
}

bool deactivateSecuredDataTransmission() {
	
}

/* Private Function **********************************************************/

void DSC_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length)
{
	if (error == E_OK)
	{
		uint16_t p2 = (data[2] << 8) + data[3];
		uint16_t p2_star = (data[4] << 8) + data[5];
			STM_SetSession(data[1], p2, p2_star);
	}
	if(DSC_user_callback != NULL)
		DSC_user_callback(error, data, length);
	DSC_user_callback = NULL;
}

void Reset_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length)
{
	if (error == E_OK)
	{
			STM_SetSession(UDS_Session_Default, P2_DEFAULT, P2_STAR_DEFAULT);
	}
	if (DSC_user_callback != NULL)
		DSC_user_callback(error, data, length);
	DSC_user_callback = NULL;
}

void LinkControl_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length)
{
	if (E_OK == error)
	{
			uint8_t message[2] = {SID_LinkControl, 0x03};
		STM_Deploy(message, 2, LinkTransition_callback, false);
	}
	else
	{
		if(DSC_user_callback != NULL)
			DSC_user_callback(error, data, length);
		DSC_user_callback = NULL;
	}
}

void LinkTransition_callback(UDS_Client_Error_t error, uint8_t *data, uint32_t length)
{
	if (E_OK == error)
	{
			if (!STM_LinkControl(proposedSpeed))
		{
			UDS_LOG_WARNING("Couldn't adjust LinkControl speed.");
			if(DSC_user_callback != NULL)
				DSC_user_callback(E_ComSpeedNotAdjusted, data, length);
			DSC_user_callback = NULL;
			return;
		}
	}
	if(DSC_user_callback != NULL)
		DSC_user_callback(error, data, length);
	DSC_user_callback = NULL;
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
