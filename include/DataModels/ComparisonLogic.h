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
 * @defgroup DataModels
 * @{
 * @file ComparisonLogic.h
 * Provides a user friendly representation of the comparation logic parameter used in Response on Comparison of DIDs Event.
 * 
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef COMPARISON_LOGIC_H_
#define COMPARISON_LOGIC_H_

/* Includes ******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/** @brief Comparison Logic used in Response On Events Requests. */
typedef enum ComparisonLogic_public {
    CompLogic_LessThan = 0x01,              /**< @c < */
    CompLogic_GreaterThan = 0x02,           /**< @c > */
    CompLogic_Equal = 0x03,                 /**< @c == */
    CompLogic_NotEqual = 0x04               /**< @c != */
} ComparisonLogic_t;

/* Interfaces ****************************************************************/

#endif /* COMPARISON_LOGIC_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
