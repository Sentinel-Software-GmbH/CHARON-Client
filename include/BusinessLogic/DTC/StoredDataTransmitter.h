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
 *  Created on: 16.07.2018
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @defgroup BusinessLogic
 * @{
 * @file
 * Implementation of the Stored Data Transmitter Functional Unit.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */

#ifndef UDS_STORED_DATA_TRANSMITTER_H_
#define UDS_STORED_DATA_TRANSMITTER_H_


#ifdef __cplusplus
extern "C" {
#endif
/* Includes ******************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "CallbackInterface.h"
#include "compiler.h"

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Interfaces ****************************************************************/

/** @brief Clear the DTCs of a given Group of DTCs
 * @req R18 Clear diagnostic information from server.
 * @param groupOfDTC 3-byte value indicating the group of DTCs to be cleared.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ClearDiagnosticInformation(uint32_t groupOfDTC, UDS_callback callback);

/** @brief Retrieve the number of DTCs matching a client defined DTC status mask.
 * @param DTCStatusMask StatusMask to be matched.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportNumberOfDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback);

/** @brief Retrieve the list of all DTCs matching a client defined DTC status mask.
 * @param DTCStatusMask status mask to be matched.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback);

/** @brief Retrieve all captured DTCSnapshot data records.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCSnapshotIdentification(UDS_callback callback);

/** @brief Retrieve captured DTCSnapshot record data for a client defined DTCMaskRecord in conjunction with a DRCSnapshot.
 * @param DTCMaskRecord The server will search though it's supported DTCs for an exact match.
 * @param DTCSnapshotRecordNumber Specifies a particular occurrence of the specified DTC.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCSnapshotRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCSnapshotRecordNumber, UDS_callback callback);

/** @brief Retrieve captured DTCStoreData record data for a DTCStoredDataRecordNumber.
 * @param DTCStoredDataRecordNumber Data record number to be searched for.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCStoredDataByRecordNumber(uint8_t DTCStoredDataRecordNumber, UDS_callback callback);

/** @brief Request a DTC Extended Data Record with matching DTCNumber.
 * @param DTCMaskRecord The server will search though it's supported DTCs for an exact match.
 * @param DTCExtDataRecordNumber Specify a particular DTCExtendedData record of the specified DTC for which DTCExtendedData is being requested.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCExtDataRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCExtDataRecordNumber, UDS_callback callback);

/** @brief Check ISO 14229-1 Chapter 11.3.1.8
 * @param DTCSeverityMask Will be AND-ed with the DTCStatusMask. Every DTC Match will increase the counter.
 * @param DTCStatusMask Will be AND-ed with the DTCSeverityMask. Every DTC Match will increase the counter.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */ 
public bool UDS_DTC_ReportNumberOfDTCBySeverityMaskRecord(uint8_t DTCSeverityMask, uint8_t DTCStatusMask, UDS_callback callback);

/** @brief Request a list of DTCs that fulfill the function DTC == (DTCSeverityMask & DTCStatusMask)
 * @param DTCSeverityMask Will be AND-ed with the DTCStatusMask.
 * @param DTCStatusMask Will be AND-ed with the DTCSeverityMask.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCBySeverityMaskRecord(uint8_t DTCSeverityMask, uint8_t DTCStatusMask, UDS_callback callback);

/** @brief Request the severity and functional unit information for an exact match with the DTCMaskRecord.
 * @param DTCMaskRecord The server will search though it's supported DTCs for an exact match.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportSeverityInformationOfDTC(uint32_t DTCMaskRecord, UDS_callback callback);

/** @brief A client requests the status of all DTCs supported by the server. 
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportSupportedDTC(UDS_callback callback);

/** @brief Request the first failed DTC from the server. 
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportFirstTestFailedDTC(UDS_callback callback);

/** @brief Request the first confirmed DTC from the server. 
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportFirstConfirmedDTC(UDS_callback callback);

/** @brief Request the most recent failed DTC from the server.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportMostRecentTestFailedDTC(UDS_callback callback);

/** @brief Request the most recent confirmed DTC from the server.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportMostRecentConfirmedDTC(UDS_callback callback);

/** @brief Request a list of DTCs out of the DTC mirror memory.
 * @param DTCStatusMask Filters DTCs by this Status Mask.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportMirrorMemoryDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback);

/** @brief Request DTCExtendedData records out of the DTC mirror memory.
 * @param DTCMaskRecord Filter records by this DTC Number.
 * @param DTCExtDataRecord Select records by this record number. 0xFF for all records, 0xFE for all OBD records.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportMirrorMemoryDTCExtDataRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCExtDataRecordNumber, UDS_callback callback);

/** @brief Request the number of DTCs out of mirror memory.
 * @param DTCStatusMask Filter the DTCs by this Status Mask.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportNumberOfMirrorMemoryDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback);

/** @brief Request the number of emissions-related OBD DTCs.
 * @param DTCStatusMask Filter the DTCs by this Status Mask.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportNumberOfEmissionsOBDDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback);

/** @brief Request the emissions-related OBD DTCs and their status.
 * @param DTCStatusMask Filter the DTCs by this Status Mask.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportEmissionsOBDDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback);

/** @brief Request the list of current "prefailed" DTCs, which have not yet been detected as "pending" or "confirmed".
 * s. ISO 14229-1:2013 Pg. 196 Table 269
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCFaultDetectionCounter(UDS_callback callback);

/** @brief Request the list of DTCs with "permanent DTC" status.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCWithPermanentStatus(UDS_callback callback);

/** @brief Request the DTCExtendedData records.
 * @param DTCExtDataRecord Request the DTCExtendedData record with this record number. 
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportDTCExtDataRecordByRecordNumber(uint8_t DTCExtDataRecordNumber, UDS_callback callback);

/** @brief Request the list of DTCs out of the user defined DTC memory and their corresponding status.
 * @param DTCStatusMask Select DTCs by this Status Mask.
 * @param MemorySelection Select from this specified Memory.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportUserDefMemoryDTCByStatusMask(uint8_t DTCStatusMask, uint8_t MemorySelection, UDS_callback callback);
/** @brief Request the DTCSnapshot record(s) out of the user defined DTC Memory associated with a client defined DTC number and DTCSnapshot record number.
 * @param DTCMaskRecord Select the DTC number.
 * @param DTCSnapshotRecordNumber Select the DTCSnapshot record number (0xFF for all records.)
 * @param MemorySelection Select the Memory by ID.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportUserDefMemoryDTCSnapshotRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCSnapshotRecordNumber, uint8_t MemorySelection, UDS_callback callback);

/** @brief Request the DTCSnapshot record(s) out of the user defined DTC Memory associated with a client defined DTC number and DTCSnapshot record number.
 * @param DTCMaskRecord Select the DTC number.
 * @param DTCExtDataRecordNumber Select the DTCExtendedData record number (0xFF for all records.)
 * @param MemorySelection Select the Memory by ID.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportUserDefMemoryDTCExtDataRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCExtDataRecordNumber, uint8_t MemorySelection, UDS_callback callback);
/** @brief Request a list of WWH OBD DTCs and their corresponding status and severity information.
 * @param FunctionalGroupIdentifier Select the wanted functional group of DTCs.
 * @param DTCStatusMask Select the DTCs by this status mask.
 * @param DTCSeverityMask Select the DTCs by this severity mask.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportWWHOBDDTCByMaskRecord(uint8_t FunctionalGroupIdentifier, uint8_t DTCStatusMask, uint8_t DTCSeverityMask, UDS_callback callback);

/** @brief Request a list of WWH OBD DTCs with "permanent DTC" status.
 * @param FunctionalGroupIdentifier Select the wanted functional group of DTCs.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occurred.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_DTC_ReportWWHOBDDTCWithPermanentStatus(uint8_t FunctionalGroupIdentifier, UDS_callback callback);

#ifdef __cplusplus
}
#endif


#endif /* UDS_STORED_DATA_TRANSMITTER_H_*/
/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/