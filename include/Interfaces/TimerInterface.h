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

/**
 * @brief A Function that should return a value that increases every Millisecond.
 * This can be from a RTC or a simple System Timer.
 * @returns An unsigned numeric value that increases every Millisecond. 
 */
typedef uint32_t(*getTimeFunc)(void);
/** @brief A function to get the difference between two timestamps provided by the @ref @c getTimeFunc .
 * @warning Please take overflowing values into consideration.
 * @returns The difference between two provided timestamps.
 * start > end should return a negative value.
 * Equally start < end should return a positive value.
 */
typedef int64_t(*diffTimeFunc)(uint32_t start, uint32_t stop);


typedef struct TimerInterface_public {
    getTimeFunc getTime;
    diffTimeFunc diffTime;
} TimerInterface;


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_3000AB7D_0796_4ec4_A5F1_E152F29A2086__INCLUDED_)*/
 