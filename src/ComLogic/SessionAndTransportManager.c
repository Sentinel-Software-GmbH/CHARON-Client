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
}

bool Send(uint8_t *data, uint32_t length)
{
}

bool Receive(uint8_t *data, uint32_t length)
{
}

bool KeepAlive()
{
}

void LinkControl()
{
	
}

bool AccessTimingParameter(uint16_t p2_timeout, uint16_t p2_star_timeout)
{
	
} 

