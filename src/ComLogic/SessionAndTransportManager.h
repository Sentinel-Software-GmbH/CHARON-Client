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

bool Init(ComInterface com, TimerInterface timer);
void Send();
void Receive();
void KeepAlive();
void LinkControl();
void ComControl();
void AccessTimingParameter();


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_3711EF7D_AB63_4670_87A0_AD943D576A54__INCLUDED_)*/
 