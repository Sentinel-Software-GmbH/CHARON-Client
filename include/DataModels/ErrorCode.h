/**
 * Error Codes used as return values.
 */
#ifndef ERROR_CODE_H_
#define ERROR_CODE_H_

    typedef enum ErrorCodes_public {
        E_OK = 0x00,
        E_NotResponding,
        E_NegativeResponse,
        E_Pending,
        E_Busy,
        E_NotSupported,
        E_ComSpeedNotAdjusted,
        ErrorCode_amount
    } UDS_Client_Error_t;

#endif // ERROR_CODE_H_