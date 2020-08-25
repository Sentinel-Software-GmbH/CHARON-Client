/*
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
 *  Created on: Mon Aug 17 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup TestModules
 * @{
 * @addtogroup Support
 * @{
 * @file
 * Callback mockup.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef TEST_CALLBACK_H_
#define TEST_CALLBACK_H_

/* Includes ******************************************************************/

#include "Interfaces/CallbackInterface.h"

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Interfaces ****************************************************************/

void testCallback(UDS_Client_Error_t error, uint8_t* data, uint32_t length);

#endif /* TEST_CALLBACK_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
