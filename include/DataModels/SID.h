#ifndef UDS_SERVICE_IDENTIFIER_H_
#define UDS_SERVICE_IDENTIFIER_H_

    /** @brief All possible Request Commands defined by the ISO 14229-1 UDS Standard.
     * The first byte of the UDS Message always declares what function the server should execute on this request.
     * Some can only be used in a extended Session. The Server will respond with an error message on false usage.
     */
    typedef enum SID_t_public {
        /** This command is responsible for switching Sessions on the Server. */
        SID_DiagnosticSessionControl = 0x10,
        /** Reset the ECU */
        SID_ECUReset = 0x11,
        /** Clear the non-volatile error memory */
        SID_ClearDiagnosticInformation = 0x14,
        /** Read the Diagnostic Information */
        SID_ReadDTCInformation = 0x19,
        /** Read diagnostic data defined by the DataIdentifier */
        SID_ReadDataByIdentifier = 0x22,
        /** Read some piece of memory of the server at a specific address. */
        SID_ReadMemoryByAdress = 0x23,
        /** Read Scaling Data defined by a DataIdentifier.
         * @note Very complicated. See ISO 14229-1 Chp. 10.4
         */
        SID_ReadScalingDataByIdentifier = 0x24,
        /** Request Security Access to switch to extended Security Session */
        SID_SecurityAccess = 0x27,
        /** Control the Communication on the Server */
        SID_CommunicationControl = 0x28,
        /** Authenticate Client on Server */
        SID_Authentication = 0x29,
        /** Read a DataIdentifier periodically, resulting in asynchronous Responses from the Server */
        SID_ReadDataByPeriodicIdentifier = 0x2A,
        /** Dynamically define a Data Identifier eitherby Memory Address or combining other Data Identifier */
        SID_DynamicallyDefineDataIdentifier = 0x2C,
        /** Write Data to an Data Identifier */
        SID_WriteDataByIdentifier = 0x2E,
        /** Simulate different States on specific I/O-Ports of the Server */
        SID_InputOutputControlByIdentifier = 0x2F,
        /** Start a Routine on the Server. */
        SID_RoutineControl = 0x31,
        /** Request a Data Download, Client to Server */
        SID_RequestDownload = 0x34,
        /** Request a Data Upload, Server to Client */
        SID_RequestUpload = 0x35,
        /** Cyclic Request to Send or Receive Data from a previous Up- or Download Request. */
        SID_TransferData = 0x36,
        /** Signal that the Transfer has been completed. */
        SID_RequestTransferExit = 0x37,
        /** Request an Upload of a File, Server to Client */
        SID_RequestFileTransfer = 0x38,
        /** Write Data to a specified Memory Address. */
        SID_WriteMemoryByAdress = 0x3D,
        /** Signals the Server that the Client is still present and wants to remain in the active non-default Session */
        SID_TesterPresent = 0x3E,
        /** Signal of the Server to the Client, that the previous request was unsuccessful */
        SID_NEGATIVE_RESPONSE = 0x7F,
        /** Get or Set the Session Timeout Parameters P2 and P2* */
        SID_AccessTimingParameter = 0x83,
        /** Signal the Server that everything after this Byte is encrypted. */
        SID_SecuredDataTransmission = 0x84,
        /** Control the Diagnostic Status Services. */
        SID_ControlDTCSettings = 0x85,
        /** Signals the Server to send a Response after a specified Event happened. */
        SID_ResponseOnEvent = 0x86,
        /** Control the Communication Speed between Server and Client */
        SID_LinkControl = 0x87,
    } SID_t;

    // TODO: Add all Negative Error Codes to provide a better Error Handling.
    /** Server Error Codes. */
    typedef enum NRC_t_public {
        /** A Positive Response */
        NRC_PositiveResponse = 0x00,
        /** Rejected for general reasons. */
        NRC_generalReject = 0x10,
        /** Signal that the Request was successfully received, but the response takes longer than p2 specifies */
        NRC_responsePending = 0x78,
    } NRC_t;

#endif // UDS_SERVICE_IDENTIFIER_H_