/**
 * Error Codes used as return values.
 */
#ifndef ERROR_CODE_H_
#define ERROR_CODE_H_

/** A representation of all the Errors that the Client could have. */
typedef enum ErrorCode_public {
    /** Everything was OK. */
    E_OK,
    /** The Server does not respond. */
    E_NotResponding,
    /** The Server replied with a negative response. */
    E_NegativeResponse,
    /** The Server signaled that it needs more time to handle this request. */
    E_Pending,
    /** The Communication Manager is currently waiting for an answer. */
    E_Busy,
    /** This Request is not supported by the client. */
    E_NotSupported,
    /** The Communication Link Speed could not be adjusted because of an error. */
    E_ComSpeedNotAdjusted,
#ifndef DOXY_SKIP
    ErrorCode_amount
#endif
} UDS_Client_Error_t;

static const char *ErrorCode_STRING[] = {
    "E_OK",
    "E_NotResponding",
    "E_NegativeResponse",
    "E_Pending",
    "E_Busy",
    "E_NotSupported",
    "E_ComSpeedNotAdjusted",
};

#endif // ERROR_CODE_H_