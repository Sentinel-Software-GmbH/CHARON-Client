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

/** @brief Enumeration Codes for every possible ISO specified Session on the Server. */
typedef enum SessionType_public
{
    UDS_Session_Reserved_00 = 0x00,     /**< ISO Reserved */
    UDS_Session_Default,                /**< Default Session. */
    UDS_Session_Programming,            /**< Session to enable the Programming Logic on the Server */
    UDS_Session_Extended,               /**< Session with extended rights. */
    UDS_Session_Safety,                 /**< Session with unlocked Security Access */
} UDS_SessionType_t;

/** @brief Formal Description of a Session and its relevant Timings */
typedef struct Session_public
{
    UDS_SessionType_t session;          /**< Session Type as described in @ref @c UDS_SessionType_t */
    uint16_t p2;                        /**< Timeout for the initial answer. 1ms Resolution. */
    uint16_t p2_star;                   /**< Timeout for the extended answer. 10ms Resolution. */
} UDS_Session_t;


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_C65E1C79_42D9_49a7_A8D8_44B6C0BD7973__INCLUDED_)*/
 