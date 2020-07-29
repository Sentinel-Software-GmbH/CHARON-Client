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

#ifndef COMPARISON_LOGIC_H_
#define COMPARISON_LOGIC_H_

/* Includes ******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

typedef enum ComparisonLogic_public {
    LessThan = 0x01,
    GreaterThan = 0x02,
    Equal = 0x03,
    NotEqual = 0x04
} ComparisonLogic_t;

/* Interfaces ****************************************************************/

#endif /* COMPARISON_LOGIC_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
