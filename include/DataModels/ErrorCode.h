/**
 * Error Codes used as return values.
 */
#ifndef ERROR_CODE_H_
#define ERROR_CODE_H_

#define FOREACH_CODE(CODE) \
        CODE(E_OK) \
        CODE(E_NotResponding) \
        CODE(E_NegativeResponse) \
        CODE(E_Pending) \
        CODE(E_Busy) \
        CODE(E_NotSupported) \
        CODE(E_ComSpeedNotAdjusted) \
        CODE(E_Unexpected) \
        CODE(ErrorCode_Amount)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum ErrorCode_public {
    FOREACH_CODE(GENERATE_ENUM)
} UDS_Client_Error_t;

static const char *ErrorCode_STRING[] = {
    FOREACH_CODE(GENERATE_STRING)
};

#endif // ERROR_CODE_H_