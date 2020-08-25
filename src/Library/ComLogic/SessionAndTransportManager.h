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

#include "Interfaces/ComInterface.h"
#include "Interfaces/TimerInterface.h"
#include "Interfaces/SecurityInterface.h"
#include "Interfaces/CallbackInterface.h"
#include "DataModels/Session.h"
#include "DataModels/ErrorCode.h"
#include "DataModels/SID.h"

struct PendingObject {
    uint8_t SID;
    UDS_callback callback;
};

void STM_Init(ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxLength);

bool STM_Deploy(uint8_t *data, uint32_t length, UDS_callback callback, bool suppressPositiveResponse);

bool STM_AsyncDeploy(SID_t sid, UDS_callback callback);

bool STM_RemoveAsync(SID_t sid);

UDS_Client_Error_t STM_cyclic(void);

bool STM_LinkControl(uint32_t speed);

bool STM_SpeedIsAdjustable(void);

void STM_SetSession(UDS_SessionType_t session_type, uint16_t p2_timeout, uint16_t p2_star_timeout);

void STM_SetSessionTimeout(uint32_t timeout);

#ifdef TEST
    ComInterface* STM_getComInterface(void);
    TimerInterface* STM_getTimerInterface(void);
    uint8_t STM_getCurrentSID(void);
    UDS_Session_t STM_getCurrentSession(void);
    void STM_setCurrentSID(uint8_t sid);
    void STM_setStartPeriodicService(bool val);
    void STM_setStopPeriodicService(bool val);
    void STM_setPeriodicServiceActive(bool val);
    bool STM_getStartPeriodicService();
    bool STM_getStopPeriodicService();
    bool STM_getPeriodicServiceActive();
#endif

#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_3711EF7D_AB63_4670_87A0_AD943D576A54__INCLUDED_)*/
 