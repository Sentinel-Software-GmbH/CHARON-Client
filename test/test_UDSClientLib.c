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
 *  Created on: Tue Jul 28 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup TestModules
 * @{
 * @file
 * UDS Client Module Tests.
 * 
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#include "unity.h"
#include "UDSClientLib.h"
#include "mock_SessionAndTransportManager.h"
#include "mock_DiagnosticCommunicationManager.h"

void setUp(void) {
}
void tearDown(void) {}

void test_Init_success(void) {
    STM_Init_ExpectAnyArgs();
    UDS_Client_Init(NULL, NULL, NULL, NULL, 0);
}