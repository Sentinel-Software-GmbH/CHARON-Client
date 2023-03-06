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
 * @addtogroup WindowsPort Windows Port
 * @{
 * @file main.c
 * Main function for Windows Port can be used as showcase for Client->Server and Server<-Client communication. 
 * main.c
 * Detailed Description.
 * main
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

/* Includes ******************************************************************/

#include "UDSClientLib.h"
#include "config.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdarg.h>

#include "communication_test.h"

/* Imports *******************************************************************/
/** @brief Declare extern function prototype for windows communication interface. */
extern void pipe_init(void);

/* Constants *****************************************************************/

/* Function Definitions ******************************************************/
/** @brief Declare external member of @ref TimerInterface class to access system time functionality. */
extern TimerInterface timer1;
/** @brief Declare external member of @ref ComInterface class to access driver connection functionality.  */
extern const ComInterface wincom1;

/* Constants *****************************************************************/

/* Macros ********************************************************************/
/** @brief Macro for convenient configuration of rx buffer size.*/
#define RX_BUFFER_LENGTH 4096
/** @brief  */
uint8_t rxBuffer[RX_BUFFER_LENGTH];
/** @brief macro for convenient usage of logger functions. */
#define str(x) #x
/** @brief macro for convenient usage of logger functions. */
#define xstr(x) str(x)

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Private Function Definitions **********************************************/

/** @brief This function is used to print error messages received via server response or user callback function.
 * 
 * @param error Error response received from server @ref UDS_Client_Error_t.
 * @param receive Buffer containing received message from callback function.
 * @param receive_length Size of buffer contend in bytes.
 */
void printMessage(UDS_Client_Error_t error, uint8_t* receive, uint32_t receive_length);

/** @brief This function is used to to check if UDS_Client_Task is still pending and raise an timeout Error if needed. */
void uds_wait();


/* Interfaces  ***************************************************************/

/** @brief Simple main function to call all needed functions for using uds client. */
int main(void) 
{
    pipe_init();
    UDS_Client_Init(&wincom1, &timer1, NULL, rxBuffer, RX_BUFFER_LENGTH);
    // Add function calls and routines here.
    DTC();
    DCM();



    //########################
    exit(0);
}


/* Private Function **********************************************************/

void printMessage(UDS_Client_Error_t error, uint8_t* receive, uint32_t receive_length) 
{
    if(error != E_OK) 
    {
        UDS_LOG_WARNING("Got Error response %s (0x%02x)", ErrorCode_getString(error), error);
    }
    if(receive != NULL) 
    {
        printf("[UDS Client] CALLBACK: 0x");
        for (int i = 0; i < receive_length; i++) 
        {
            printf("%02x", receive[i]);
        }
        printf("\n"); 
    }
    return;
}

void uds_wait()
{
    int counter = 0;
    while(E_Pending == UDS_Client_Task()) 
    {
        if(counter == 100) 
        {
            UDS_LOG_ERROR("Timeout.");
            break;
        }
        Sleep(100);
        counter++;
    }
    return;
}


/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
