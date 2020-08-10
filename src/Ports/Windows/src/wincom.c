/**
 * Communication Interface for Windows.
 * 
 * Created on: 22.07.20
 *     Author: Steven Inácio
 */

#include "Interfaces/ComInterface.h"
#include <windows.h>
#include <stddef.h>

HANDLE pipeHandle;
LPCSTR pipeName = "\\\\.\\pipe\\charonserver";

void pipe_init (void)
{
    pipeHandle = CreateFile(
            pipeName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_ALWAYS,
            0,
            NULL
            );
    DWORD mode = PIPE_READMODE_MESSAGE;
    SetNamedPipeHandleState(pipeHandle, &mode, NULL, NULL);
}

static int32_t uart_receive (uint8_t* data, uint32_t maxSize)
{
	DWORD numBytes = 0;
    DWORD bytesAvailable = 0;
    BOOL peek = PeekNamedPipe(pipeHandle, data, maxSize, &numBytes, &bytesAvailable, NULL);
    if(bytesAvailable != 0) {
        BOOL result = ReadFile(pipeHandle, data, maxSize, &numBytes, NULL);
        INT error = GetLastError();
        if (!result && error == 109) pipe_init();
        return (int32_t)numBytes;
    }
    else {
        INT error = GetLastError();
        if (!peek && error == 109) pipe_init();
        return 0;
    }
}

static int32_t uart_transmit (uint8_t* data, uint32_t size)
{
	DWORD numBytes;
    WriteFile(pipeHandle, data, size, &numBytes, NULL);
    return (int32_t)numBytes;
}

ComInterface wincom1 = {
    uart_transmit,
    uart_receive,
    NULL,
    false
};