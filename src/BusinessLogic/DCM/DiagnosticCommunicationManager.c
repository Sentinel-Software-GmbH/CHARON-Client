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
 * @addtogroup UDSClient
 * @{
 * @addtogroup ComLogic
 * @{
 * @file DiagnosticCommunicationManager.c
 * Implementation of the Diagnostic and Communication Management Functional Unit.
 * The detailed specifications can be found in @b ISO @b 14229-1 Chapter 9.
 * 
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

/* Includes ******************************************************************/

#include "DiagnosticCommunicationManager.h"
#include "SessionAndTransportManager.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/** Specific Message structure of the Diagnostic Control Service.
 * It contains a mask for the structure of the message and access to a bytestream representing the message.
 */

/* Variables *****************************************************************/

static SecurityInterface_t *SecurityModule;

static UDS_callback DSC_user_callback;

/* Private Function Definitions **********************************************/

void DSC_callback(UDS_Client_Error_t error, uint8_t* data, uint32_t length);

/* Interfaces  ***************************************************************/

bool DiagnosticSessionControl(UDS_SessionType_t session, uint16_t P2_server_max, uint16_t P2_star_server_max, UDS_callback callback)
{
	// No struct or whatever because compiler could pad some bytes in between.
	// attribute__((packed))__ is compiler dependent, and a Macro definition is impossible.
	uint8_t message[] = {SID_DiagnosticSessionControl, session, (uint8_t)(P2_server_max >> 8), (uint8_t)(P2_server_max & 0xFF), (uint8_t)(P2_star_server_max >> 8), (uint8_t)(P2_star_server_max & 0xFF)}; 
	DSC_user_callback = callback;
	return STM_Deploy(&message, 6, DSC_callback, false);
}

bool ECUReset(uint8_t resetType)
{
	return  NULL;
}

bool SecurityAccess(uint8_t function, uint8_t *securityParameter, uint8_t parameterLength)
{
	return  NULL;
}

/**
 * Do we have to implement this?
 * Or is it part of the Specific Com Unit?
 */
void CommunicationControl()
{
	
}

uint8_t TesterPresent()
{
	return  NULL;
}

/**
 * Might be required
 */
void AccessTimingParameter()
{
	
}

uint8_t SecuredDataTransmission(uint8_t* data, uint32_t length)
{
	return  NULL;
}

uint8_t ControlDTCSetting(uint8_t subfunction, uint8_t* data, uint32_t length)
{
	return  NULL;
}

uint8_t ResponseOnEvent(uint8_t event, bool storeEvent, uint8_t eventWindowTime, uint8_t eventTypeRecord[10], uint8_t serviceToRespondTo, uint8_t* serviceParameter)
{
	return  NULL;
}

void LinkControl()
{
	
}

bool DCM_Init(SecurityInterface_t *security)
{
	SecurityModule = security;
	return true;
}

/* Private Function **********************************************************/

void DSC_callback(UDS_Client_Error_t error, uint8_t* data, uint32_t length) {
	if(error == E_OK) {
		uint16_t p2 = data[2] << 8 + data[3];
		uint16_t p2_star = data[4] << 8 + data[5];
		STM_AccessTimingParameter(p2, p2_star);
	}
	DSC_user_callback(error, data, length);
	DSC_user_callback = NULL;
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
