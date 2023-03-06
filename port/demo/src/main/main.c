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
 * @file main.c
 * Main function for Demo Port can be used as showcase for Client->Server and Server<-Client communication. 
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

#include "demo.h"

/* Imports *******************************************************************/

/** @brief Declare extern function prototype for windows communication interface. */
extern void pipe_init(void);


/* Constants *****************************************************************/


/* Macros ********************************************************************/

/** @brief Macro for convenient configuration of rx buffer size.*/
#define RX_BUFFER_LENGTH 4096
/** @brief  */
uint8_t rxBuffer[RX_BUFFER_LENGTH];


/* Types *********************************************************************/


/* Variables *****************************************************************/


/* Function Definitions ******************************************************/

/** @brief Declare external member of @ref TimerInterface class to access system time functionality. */
extern TimerInterface timer1;
/** @brief Declare external member of @ref ComInterface class to access driver connection functionality.  */
extern const ComInterface wincom1;


/* Private Function Definitions **********************************************/


/* Interfaces  ***************************************************************/

/** @brief Simple main function to call all needed functions for using uds client. */
int main(void) 
{
    pipe_init();
    UDS_Client_Init(&wincom1, &timer1, NULL, rxBuffer, RX_BUFFER_LENGTH);

    demo_charonDemo(false);

    exit(0);
}


/* Private Function **********************************************************/


/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
