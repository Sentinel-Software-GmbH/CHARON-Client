/****************************************************
 *  TimerInterface.h                                         
 *  Created on: 16-Jul-2020 13:50:31                      
 *  Implementation of the Interface TimerInterface       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_3000AB7D_0796_4ec4_A5F1_E152F29A2086__INCLUDED_)
#define EA_3000AB7D_0796_4ec4_A5F1_E152F29A2086__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint32_t(*getTimeFunc)(void);
typedef uint32_t(*diffTimeFunc)(uint32_t start, uint32_t stop);


typedef struct TimerInterface_public {
    getTimeFunc getTime;
    diffTimeFunc diffTime;
} TimerInterface;


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_3000AB7D_0796_4ec4_A5F1_E152F29A2086__INCLUDED_)*/
 