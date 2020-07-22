#ifndef UDS_SERVICE_IDENTIFIER_H_
#define UDS_SERVICE_IDENTIFIER_H_

    typedef enum SID_t_public {
        SID_DiagnosticSessionControl = 0x10,
        SID_ECUReset = 0x11,
        SID_ClearDiagnosticInformation = 0x14,
        SID_ReadDTCInformation = 0x19,
        SID_ReadDataByIdentifier = 0x22,
        SID_ReadMemoryByAdress = 0x23,
        SID_ReadScalingDataByIdentifier = 0x24,
        SID_SecurityAccess = 0x27,
        SID_CommunicationControl = 0x28,
        SID_Authentication = 0x29,
        SID_ReadDataByPeriodicIdentifier = 0x2A,
        SID_DynamicallyDefineDataIdentifier = 0x2C,
        SID_WriteDataByIdentifier = 0x2E,
        SID_InputOutputControlByIdentifier = 0x2F,
        SID_RoutineControl = 0x31,
        SID_RequestDownload = 0x34,
        SID_RequestUpload = 0x35,
        SID_TransferData = 0x36,
        SID_RequestTransferExit = 0x37,
        SID_RequestFileTransfer = 0x38,
        SID_WriteMemoryByAdress = 0x3D,
        SID_TesterPresent = 0x3E,
        SID_NEGATIVE_RESPONSE = 0x7F,
        SID_AccessTimingParameter = 0x83,
        SID_SecuredDataTransmission = 0x84,
        SID_ControlDTCSettings = 0x85,
        SID_ResponseOnEvent = 0x86,
        SID_LinkControl = 0x87,
    } SID_t;

    typedef enum NRC_t_public {
        NRC_PositiveResponse = 0x00,
        NRC_generalReject = 0x010,
        NRC_responsePending = 0x78,
    } NRC_t;

#endif // UDS_SERVICE_IDENTIFIER_H_