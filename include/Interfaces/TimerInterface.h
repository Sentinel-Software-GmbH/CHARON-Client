/**
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 Steven Inácio
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 *  Created on: Tue Jul 28 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup Interfaces
 * @{
 * @file TimerInterface.h
 * Includes the definition of the needed timer functions.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_TIMER_INTERFACE_H_
#define UDS_TIMER_INTERFACE_H_


#ifdef __cplusplus
extern "C" {
#endif
/* Includes ******************************************************************/

#include <stdint.h>

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Interfaces ****************************************************************/

/**
 * @brief A Function that should return a value that increases every Millisecond.
 * This can be from a RTC or a simple System Timer.
 * @returns An unsigned numeric value that increases every Millisecond. 
 */
typedef uint32_t(*getTimeFunc)(void);

/** @brief A function to get the difference between two timestamps provided by the @ref getTimeFunc .
 * @warning Please take overflowing values into consideration.
 * @returns The difference between two provided timestamps.
 * start > end should return a negative value.
 * Equally start < end should return a positive value.
 */
typedef int64_t(*diffTimeFunc)(uint32_t start, uint32_t stop);


/** @brief A Class that represents the implementation of a System Timer.
 * @req S04 Define a Timer Interface
 */
typedef struct TimerInterface_public 
{
    getTimeFunc getTime;        /**< member of class TimerInterface function pointer @ref getTimeFunc */
    diffTimeFunc diffTime;      /**< member of class TimerInterface function pointer @ref diffTimeFunc*/
} TimerInterface;


#ifdef __cplusplus
}
#endif


#endif /* UDS_TIMER_INTERFACE_H_*/
 /*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
 