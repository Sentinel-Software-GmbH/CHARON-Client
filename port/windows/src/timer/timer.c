/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 ${Author}
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
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup WindowsPort Windows Port
 * @{
 * @file timer.c
 * Implementation of Timer functions for Windows.
 * Detailed Description.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

/* Includes ******************************************************************/

#include "TimerInterface.h"
#include <windows.h>

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Function Definitions ******************************************************/

/**
 * @brief A Function that should return a value that increases every Millisecond.
 * 
 * @return  An unsigned numeric value that increases every Millisecond. 
 */
uint32_t getTime();

/**
 * @brief A function to get the difference between two timestamps provided by the @ref getTimeFunc .
 * 
 * @param start Timestamp taken at start of measurement.
 * @param stop  Timestamp taken at end of measurement.
 * @return start > end should return a negative value. Equally start < end should return a positive value.
 */
int64_t diffTime(uint32_t start, uint32_t stop);

/* Private Function Definitions **********************************************/

/* Interfaces  ***************************************************************/

TimerInterface timer1 = 
{
    getTime,
    diffTime
};

uint32_t getTime() 
{
    return GetTickCount();
}

int64_t diffTime(uint32_t start, uint32_t stop) 
{
    int64_t diff = stop;
    diff = diff - start;
    return diff;
}
/* Private Function **********************************************************/




/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
