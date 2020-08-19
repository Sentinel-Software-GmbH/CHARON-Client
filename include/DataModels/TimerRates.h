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
 * @defgroup ComLogic
 * @{
 * @file $Filename$.h
 * Brief Description.
 * Detailed Description
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef TIMER_RATES_H_
#define TIMER_RATES_H_

/* Includes ******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/** Identification Codes for different Timer rates.
 * The exact time rates are vendor specific.
 */
typedef enum TimerRates_public {
    /** Represents a Slow Timer Rate e.g. 1 second */
    UDS_SlowTimer = 0x01,
    /** Represents a Medium Timer Rate e.g. 300 ms */
    UDS_MediumTimer = 0x02,
    /** Represents a Fast Timer Rate e.g. 25 ms */
    UDS_FastTimer = 0x03,
} UDS_TimerRates_t;

/* Interfaces ****************************************************************/

#endif /* TIMER_RATES_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
