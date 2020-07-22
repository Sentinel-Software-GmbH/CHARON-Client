/****************************************************
 *  SessionAndTransportManager.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class SessionAndTransportManager       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_3711EF7D_AB63_4670_87A0_AD943D576A54__INCLUDED_)
#define EA_3711EF7D_AB63_4670_87A0_AD943D576A54__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include "DataModels/Session.h"
#include "Interfaces/ComInterface.h"
#include "Interfaces/TimerInterface.h"
#include "DataModels/ErrorCode.h"

bool STM_Init(ComInterface *com, TimerInterface *timer, uint8_t * const rxBuffer, uint32_t rxLength);

bool STM_Deploy(uint8_t *data, uint32_t length, void(*callback)(uint8_t* buffer, uint32_t length), bool suppressPositiveResponse);

UDS_Client_Error_t STM_cyclic(void);

void STM_LinkControl();

bool STM_SetSession(UDS_SessionType_t session_type, uint16_t p2_timeout, uint16_t p2_star_timeout);

void STM_SetSessionTimeout(uint32_t timeout);

#ifdef TEST
    ComInterface* STM_getComInterface(void);
    TimerInterface* STM_getTimerInterface(void);
    uint8_t STM_getCurrentSID(void);
    UDS_Session_t STM_getCurrentSession(void);
    void STM_setCurrentSID(uint8_t sid);
#endif

#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_3711EF7D_AB63_4670_87A0_AD943D576A54__INCLUDED_)*/
 