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
 * @defgroup Interfaces
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
 