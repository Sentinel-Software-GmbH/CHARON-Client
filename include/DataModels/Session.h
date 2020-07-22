/****************************************************
 *  session.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Enumeration session       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_C65E1C79_42D9_49a7_A8D8_44B6C0BD7973__INCLUDED_)
#define EA_C65E1C79_42D9_49a7_A8D8_44B6C0BD7973__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum SessionType_public
{
    UDS_Session_Reserved_00 = 0x00,
    UDS_Session_Default,
    UDS_Session_Programming,
    UDS_Session_Extended,
    UDS_Session_Safety,
} UDS_SessionType_t;

typedef struct Session_public
{
    UDS_SessionType_t session;
    uint16_t p2;
    uint16_t p2_star;
} UDS_Session_t;


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_C65E1C79_42D9_49a7_A8D8_44B6C0BD7973__INCLUDED_)*/
 