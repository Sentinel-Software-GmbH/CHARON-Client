#ifndef CALLBACK_INTERFACE_H_
#define CALLBACK_INTERFACE_H_
    #include <stdint.h>
    #include "DataModels/ErrorCode.h"

    typedef void(*UDS_callback)(UDS_Client_Error_t errorCode, uint8_t* buffer, uint32_t length);
#endif // CALLBACK_INTERFACE_H