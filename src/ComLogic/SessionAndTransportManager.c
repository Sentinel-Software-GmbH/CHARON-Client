/****************************************************
 *  SessionAndTransportManager.c                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class SessionAndTransportManager       
 *  Original author: Steven Inacio                     
 ****************************************************/

#include "SessionAndTransportManager.h"
#include "session.h"

static ComInterface s_com;
static Session s_currentSession;
static TimerInterface s_timer;

static uint16_t s_p2_timeout;
static uint16_t s_p2_star_timeout;

static uint8_t s_currentSID;
static uint32_t s_timeout;

static bool s_supressPosResponse;

bool Init(ComInterface com, TimerInterface timer) {
    s_com = com;
    if (com.init != NULL) {
        com.init();
    }
    s_timer = timer;
}

bool Send(uint8_t *data, uint32_t length)
{
    if (length < 2) {
        return false;
    }
    s_currentSID = data[0];
    s_supressPosResponse = (data[1] & 0x80) == 0x80;
    s_timeout = s_timer.getTime() + s_p2_timeout;
	s_com.send(data, length);
}

bool Receive(uint8_t *data, uint32_t length)
{
    uint32_t timeout = s_p2_timeout;
    if(!s_com.receive(data, length)) {
        return false;
    } else if (data[0] != s_currentSID + 0x40) {
        switch data[0] {
            // TODO: NRC handling.
        }
    }
    return true;
}

bool KeepAlive()
{
	uint8_t message[2] = { 0x3E, 0x80 };
    s_com.send(message, 2);
}

void LinkControl()
{
	
}

bool AccessTimingParameter(uint16_t p2_timeout, uint16_t p2_star_timeout)
{
	
} 

