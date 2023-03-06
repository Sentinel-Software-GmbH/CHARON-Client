/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2023 Rene Mutscheller
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
 * @addtogroup WindowsPort Windows Port
 * @{
 * @file communication_test.h
 * Functions for testing communication and debugging.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_CLIENT_COMMUNICATION_TEST_H_
#define UDS_CLIENT_COMMUNICATION_TEST_H_

/* Includes ******************************************************************/

/* Constants *****************************************************************/

/* Types *********************************************************************/

/* Interfaces ****************************************************************/

/** @brief This function is used to prepare and setup environment for trouble free client usage.*/
void Setup();

/** @brief This Function calls all implemented and integrated Diagnostic Communication Manager functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void DCM();

/** @brief This Function calls alls implemented and integrated Diagnostic Trouble Code functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void DTC();

/** @brief This Function calls alls implemented and integrated Input and Output Controller functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void IOControl();

/** @brief This Function calls alls implemented and integrated Upload and Download functional Unit functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void UploadDownload();

/** @brief This Function calls alls implemented and integrated Routine control functional Unit functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void Routine();

/** @brief This Function calls alls implemented and integrated Service and Session Control Module functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void DataTransmit();


#endif /* UDS_CLIENT_COMMUNICATION_TEST_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
