/****************************************************
 *  DiagnosticCommunicationManager.c                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class DiagnosticCommunicationManager       
 *  Original author: Steven Inacio                     
 ****************************************************/

#include "DiagnosticCommunicationManager.h"

struct SecurityInterface SecurityModule;



uint8_t DiagnosticSessionControl(uint8_t session, uint16_t P2_server_max, uint16_t P2_star_server_max)
{
	return  NULL;
}

uint8_t ECUReset(uint8_t resetType)
{
	return  NULL;
}

uint8_t SecurityAccess(uint8_t function, byte[] securityParameter, uint8_t parameterLength)
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

uint8_t SecuredDataTransmission(byte* data)
{
	return  NULL;
}

uint8_t ControlDTCSetting(uint8_t subfunction, byte[] data)
{
	return  NULL;
}

uint8_t ResponseOnEvent(uint8_t event, boolean storeEvent, uint8_t eventWindowTime, uint8_t[10] eventTypeRecord, uint8_t serviceToRespondTo, uint8_t* serviceParameter)
{
	return  NULL;
}

void LinkControl()
{
	
}

boolean Init(struct ComInterface Com, struct SecurityInterface Security)
{
	return  NULL;
} 

