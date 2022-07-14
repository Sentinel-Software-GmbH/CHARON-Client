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
 * @addtogroup wincom.c
 * @{
 * @file
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
HANDLE pipeHandle;
LPCSTR pipeName = "\\\\.\\pipe\\charonserver";

/* Private Function Definitions **********************************************/

/* Interfaces  ***************************************************************/

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

/* Private Function **********************************************************/




/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
