/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 ${Author}
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
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup DemoPort Demo Port
 * @{
 * @file wincom.c
 * Brief Description.
 * Communication Interface for Windows.
 * Detailed Description.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

/* Includes ******************************************************************/

#include "ComInterface.h"
#include <windows.h>
#include <stddef.h>

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

/** @brief declare name of pipeHandle. */
HANDLE pipeHandle;
/** @brief declare name of pipe. */
LPCSTR pipeName = "\\\\.\\pipe\\charonserver";

/* Function Definitions ******************************************************/

/** @brief Function to initialize pipe for communication between Client and Server when boot entities launched on windows. */
void pipe_init(void);

/**
 * @brief Function sends data using pipe and windows std. libraries.
 * 
 * @param data Data buffer to send. 
 * @param size Size of data buffer in bytes.
 * @return Number of bytes transmitted.
 */
static int32_t uart_transmit (uint8_t* data, uint32_t size);

/**
 * @brief Function to receive data via pipe. 
 * 
 * @param data Date buffer with received data.
 * @param maxSize maximum size of data to receive in bytes.
 * @return Number of received bates.
 */
static int32_t uart_receive (uint8_t* data, uint32_t maxSize);
/* Private Function Definitions **********************************************/

/* Interfaces  ***************************************************************/

const ComInterface wincom1 = {
    uart_transmit,
    uart_receive,
    NULL,
    false
};

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

/* Private Function **********************************************************/




/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
