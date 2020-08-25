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
 *  Created on: Wed Jul 29 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @defgroup DataModels
 * @{
 * @file SID.h
 * Includes the representation of all Service IDs and Negative Responses.
 * 
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_SERVICE_IDENTIFIER_H_
#define UDS_SERVICE_IDENTIFIER_H_

// TODO: Do they need to be public?

    /** @brief All possible Request Commands defined by the ISO 14229-1 UDS Standard.
     * The first byte of the UDS Message always declares what function the server should execute on this request.
     * Some can only be used in a extended Session. The Server will respond with an error message on false usage.
     * 
     * <a href="https://en.wikipedia.org/wiki/Unified_Diagnostic_Services#Services">Wikipedia Overview over all Services</a>
     */
    typedef enum SID_t_public {
        /** @brief This command is responsible for switching Sessions on the Server. */
        SID_DiagnosticSessionControl = 0x10,
        /** @brief Reset the ECU */
        SID_ECUReset = 0x11,
        /** @brief Clear the non-volatile error memory */
        SID_ClearDiagnosticInformation = 0x14,
        /** @brief Read the Diagnostic Information */
        SID_ReadDTCInformation = 0x19,
        /** @brief Read diagnostic data defined by the DataIdentifier */
        SID_ReadDataByIdentifier = 0x22,
        /** @brief Read some piece of memory of the server at a specific address. */
        SID_ReadMemoryByAddress = 0x23,
        /** @brief Read Scaling Data defined by a DataIdentifier.
         * @note Very complicated. See ISO 14229-1 Chp. 10.4
         */
        SID_ReadScalingDataByIdentifier = 0x24,
        /** @brief Request Security Access to switch to extended Security Session */
        SID_SecurityAccess = 0x27,
        /** @brief Control the Communication on the Server */
        SID_CommunicationControl = 0x28,
        /** @brief Authenticate Client on Server */
        SID_Authentication = 0x29,
        /** @brief Read a DataIdentifier periodically, resulting in asynchronous Responses from the Server */
        SID_ReadDataByPeriodicIdentifier = 0x2A,
        /** @brief Dynamically define a Data Identifier eitherby Memory Address or combining other Data Identifier */
        SID_DynamicallyDefineDataIdentifier = 0x2C,
        /** @brief Write Data to an Data Identifier */
        SID_WriteDataByIdentifier = 0x2E,
        /** @brief Simulate different States on specific I/O-Ports of the Server */
        SID_InputOutputControlByIdentifier = 0x2F,
        /** @brief Start a Routine on the Server. */
        SID_RoutineControl = 0x31,
        /** @brief Request a Data Download, Client to Server */
        SID_RequestDownload = 0x34,
        /** @brief Request a Data Upload, Server to Client */
        SID_RequestUpload = 0x35,
        /** @brief Cyclic Request to Send or Receive Data from a previous Up- or Download Request. */
        SID_TransferData = 0x36,
        /** @brief Signal that the Transfer has been completed. */
        SID_RequestTransferExit = 0x37,
        /** @brief Request an Upload of a File, Server to Client */
        SID_RequestFileTransfer = 0x38,
        /** @brief Write Data to a specified Memory Address. */
        SID_WriteMemoryByAdress = 0x3D,
        /** @brief Signals the Server that the Client is still present and wants to remain in the active non-default Session */
        SID_TesterPresent = 0x3E,
        /** @brief Signal of the Server to the Client, that the previous request was unsuccessful */
        SID_NEGATIVE_RESPONSE = 0x7F,
        /** @brief Get or Set the Session Timeout Parameters P2 and P2* */
        SID_AccessTimingParameter = 0x83,
        /** @brief Signal the Server that everything after this Byte is encrypted. */
        SID_SecuredDataTransmission = 0x84,
        /** @brief Control the Diagnostic Status Services. */
        SID_ControlDTCSettings = 0x85,
        /** @brief Signals the Server to send a Response after a specified Event happened. */
        SID_ResponseOnEvent = 0x86,
        /** @brief Control the Communication Speed between Server and Client */
        SID_LinkControl = 0x87,
    } SID_t;

    // TODO: Add all Negative Error Codes to provide a better Error Handling.
    /** @brief Server Error Codes.
     * @note ISO 14229-1 Table A.1
    */
    typedef enum NRC_t_public {
        /** @brief A Positive Response */
        NRC_PositiveResponse = 0x00,
        /** @brief Rejected for general reasons. */
        NRC_generalReject = 0x10,
        /** @brief Signal that the Request was successfully received, but the response takes longer than p2 specifies */
        NRC_responsePending = 0x78,
    } NRC_t;

#endif // UDS_SERVICE_IDENTIFIER_H_