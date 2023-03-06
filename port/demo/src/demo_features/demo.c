/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2023 Rene Mutscheller
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
 * @file demo.c
 * Handles the User preview.
 * 
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

/* Includes ******************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "demo.h"
#include "UDSClientLib.h"
#include "config.h"
#include "DiagnosticCommunicationManager.h"
#include "StoredDataTransmitter.h"
#include "DataTransmitter.h"
#include "ErrorCode.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/** @brief Get the size of an input array. */
#define SIZE_OF_ARRAY(a) sizeof(a) / sizeof(a[0])
/** @brief Can be used as printf to print in the terminal center.   !!! does not support "\n" !!! */
#define PRINT_CENTERED(string)  demo_printCentered(string,SIZE_OF_ARRAY(string))


/* Types *********************************************************************/


/* Variables *****************************************************************/

/** @brief Holds the current terminal size. */
static struct currentTerminalSize_t
{
    uint32_t columns;    /**< Amount of current terminal columns.*/
    uint32_t rows;       /**< Amount of current terminal rows.*/
} currentTerminalSize;   /**< Name of the struct, holds current terminal size.*/

/** @brief Holds server response for easy collection. */
static uint8_t  serverResponse[1024];
/** @brief Holds server response length for easy collection. */
static uint32_t serverResponseLength = 0;
/** @brief Holds error response for easy collection. */
static uint32_t serverError = 0;


/* Private Function Definitions **********************************************/

// Helper functions 
//_____________________________________________________________________________
/**
 * @brief Calculate the current terminal size, but not on real time.
 */
static void demo_getCurrentTerminalSize (void);

/**
 * @brief Print the wanted input centered in the terminal.
 * 
 * @param input         wanted output string
 * @param lengthRaw     string length
 */
static void demo_printCentered (char * input, uint32_t lengthRaw);

/**
 * @brief Prints a full line based on current terminal size.
 */
static void demo_printUnderscoreLine_noFlush (void);

/**
 * @brief Prints small or big Charon logo depending on current terminal size.
 */
static void demo_printCharonDemoLogo (void);

/**
 * @brief Based on flag uses "cls" or "clear".
 */
static void demo_clearTerminal (void);

/**
 * @brief Programming dummy and currently not implemented functionalities.
 */
static void demo_currentlyNotSupported (void);

/**
 * @brief Wrong or not supported input.
 */
static void demo_defaultInputFailed (void);

/**
 * @brief For functions like the OBD related topic which are not supported by Sentinel Software.
 */
static void demo_subfunctionBySentinelNotSupported (void);

/** 
 * @brief This function is used to print error messages received via server response or user callback function.
 * 
 * @param error Error       response received from server @ref UDS_Client_Error_t
 * @param receive Buffer    containing received message from callback function
 * @param receive_length    Size of buffer contend in bytes
 */
static void printDemoMessage(UDS_Client_Error_t error, uint8_t* receive, uint32_t receive_length);

/** 
 * @brief This function is used to to check if UDS_Client_Task is still pending and raise an timeout Error if needed. 
 */
static void uds_demoWait (void);

/**
 * @brief Handles server return.
 * 
 * @param wait:             True = will wait for ENTER input, False will continue.
 */
static void demo_DTCResponseToDelete_return (bool wait);

/**
 * @brief Handles positive server return value.
 * 
 * @param wait:             True = will wait for ENTER input, False will continue.
 */
static void demo_DTCResponseToDelete_positive (bool wait);

/**
 * @brief Handles negative server return value.
 * 
 * @param wait:             True = will wait for ENTER input, False will continue.
 */
static void demo_DTCResponseToDelete_negative (bool wait);

/**
 * @brief Take a hex string and convert it to a 64bit number (max 16 hex digits).
 * 
 * @param str:              The string must only contain digits and valid hex characters.
 */
static uint32_t demo_xToUint_32(uint8_t *str);

/**
 * @brief Takes DTC input and retuns the calculated int.
 * 
 * @return uint32_t:        calculated INT out of HEX input.
 */
static uint32_t demo_DTCNumberInputAndHexCheck (void);

/**
 * @brief Takes DID input and retuns the calculated int.
 * 
 * @return uint32_t         calculated INT out of HEX input.
 */
static uint32_t demo_DIDNumberInputAndHexCheck (void);

/**
 * @brief Asks for 8bit user input, checks for valid hex input. 
 * 
 * @return uint32_t:        gives inputted hex in int back.
 */
static uint32_t demo_get8bitHex (void);


// main functions.
//_____________________________________________________________________________
/**
 * @brief Ask user to set his wanted terminal size.
 */
static void demo_terminalSizeQuestion (void);

/**
 * @brief Welcome and menu function with output based on size.
 */
static void demo_welcomeMenu (void);

// DTC functions.
//_____________________________________________________________________________
/**
 * @brief The main part of the DTC demo.
 */
static void demo_DTC (void);

/**
 * @brief Handles SID 0x14: ClearDiagnosticInformation for the DTC demo.
 */
static void demo_SID_0X14_DTC (void);

/**
 * @brief Handles preparation for Group DTC deletion.
 */
static void demo_SID_0X14_groupDTCSelection (void);

/**
 * @brief Handles preparation for single DTC deletion.
 */
static void demo_SID_0X14_singleDTCSelection (void);

/**
 * @brief Handles SID 0x19: ReadDTCInformation for the DTC demo.
 */
static void demo_SID_0X19_DTC (void);

/**
 * @brief Based on ISO 14229-1 Table 271 response handler.
 */
static void demo_SID_0X19_DTC_subfunctionResponseTable271 (void);

/**
 * @brief Based on ISO 14229-1 Table 272 response handler.
 */
static void demo_SID_0X19_DTC_subfunctionResponseTable272 (void);

/**
 * @brief Based on ISO 14229-1 Table 273 response handler.
 */
static void demo_SID_0X19_DTC_subfunctionResponseTable273 (void);

/**
 * @brief Based on ISO 14229-1 Table 274 response handler.
 */
static void demo_SID_0X19_DTC_subfunctionResponseTable274 (void);

/**
 * @brief Based on ISO 14229-1 Table 275 response handler.
 */
static void demo_SID_0X19_DTC_subfunctionResponseTable275 (void);

/**
 * @brief Based on ISO 14229-1 Table 276 response handler.
 */
static void demo_SID_0X19_DTC_subfunctionResponseTable276 (void);

/**
 * @brief Based on ISO 14229-1 Table 277 response handler.
 */
static void demo_SID_0X19_DTC_subfunctionResponseTable277 (void);

/**
 * @brief Based on ISO 14229-1 Table 279 response handler.
 */
static void demo_SID_0X19_DTC_subfunctionResponseTable279 (void);

// DID functions.
//_____________________________________________________________________________
/**
 * @brief The main part of the DID demo.
 */
static void demo_DID (void);

/**
 * @brief Handles SID 0X22: ReadDataByIdentifier for the DID demo.
 */
static void demo_SID_0X22_ReadDataByIdentifier (void);

/**
 * @brief Handles SID 0X23: ReadMemoryByAddress for the DID demo.
 */
static void demo_SID_0X23_ReadMemoryByAddress (void);

/**
 * @brief Handles SID 0X24: ReadScalingDataByIdentifier for the DID demo.
 */
static void demo_SID_0X24_ReadScalingDataByIdentifier (void);

/**
 * @brief Handles SID 0X2A: ReadDataByPeriodicIdentifier for the DID demo.
 */
static void demo_SID_0X2A_ReadDataByPeriodicIdentifier (void);

/**
 * @brief Handles SID 0X2C: DynamicallyDefineDataIdentifier for the DID demo.
 */
static void demo_SID_0X2C_DynamicallyDefineDataIdentifier (void);

/**
 * @brief Handles SID 0X2C: Subfunction 0X01 DefineByIdentifier.
 */
static void demo_SID_0X2C_SUB_0X01_DefineByIdentifier (void);

/**
 * @brief Handles SID 0X2C: Subfunction 0X02 DefineByMemoryAddress.
 */
static void demo_SID_0X2C_SUB_0X02_DefineByMemoryAddress (void);

/**
 * @brief Handles SID 0X2C: Subfunction 0X03 ClearDynamicalDefinedDID.
 */
static void demo_SID_0X2C_SUB_0X03_ClearDynamicalDefinedDID (void);

/**
 * @brief Handles SID 0X2E: WriteDataByIdentifier for the DID demo.
 */
static void demo_SID_0X2E_WriteDataByIdentifier (void);

/**
 * @brief Handles SID 0X3D: WriteMemoryByAddress for the DID demo.
 */
static void demo_SID_0X3D_WriteMemoryByAddress (void);

// Diagnostic functions.
//_____________________________________________________________________________
/**
 * @brief Handles SID 0x85: ControlDTCSetting for the DTC demo.
 */
static void demo_SID_0X85_DTC (void);

/**
 * @brief DO NOT USE WITHOUT demo_SID_0X85_DTC CALLING IT! Handles DTC number input.
 */
static void demo_SID_0x85_DTC_controlling (uint8_t ONorOFF);


/* Interfaces  ***************************************************************/

//  "main"
void demo_charonDemo (bool exit)
{
    // Ask user to set his wanted terminal size now.
    demo_getCurrentTerminalSize();
    demo_terminalSizeQuestion();

    // When Terminal size is set get the current size to print centered.
    demo_clearTerminal();
    demo_welcomeMenu();
}


/* Private Function **********************************************************/

// Helper functions.
//_____________________________________________________________________________
static void demo_getCurrentTerminalSize (void)
{
    // https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows       first answer

    // wincon.h given struct to get the current terminal data.
    CONSOLE_SCREEN_BUFFER_INFO terminal;

    // srWindow "contains the console screen buffer coordinates of the upper-left and lower-right corners of the display window"
    // will result in the current size. (+1 bc there is always 1 missing to true size)
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &terminal);
    currentTerminalSize.columns = terminal.srWindow.Right - terminal.srWindow.Left + 1;
    currentTerminalSize.rows = terminal.srWindow.Bottom - terminal.srWindow.Top + 1;
}


static void demo_printCentered (char * input, uint32_t lengthRaw)
{
    // Discount the terminal '\0'.
    uint32_t length = (lengthRaw - 0x01);

    // Calculates the needed padding from left to start of the string.
    uint32_t pad = (length >= currentTerminalSize.columns) ? 0 : (currentTerminalSize.columns - length) / 2;

    // Will print text in the current middle of the terminal.
    printf("%*s%s\n", pad, " ", input);
}


static void demo_printUnderscoreLine_noFlush (void)
{
    // Based on current width
    for (uint32_t i = 0; i < currentTerminalSize.columns; i++)
    {
        putchar('_');
    }
    printf("\n");
}


static void demo_printCharonDemoLogo (void)
{
    if (currentTerminalSize.columns <= 60)
    {
        PRINT_CENTERED("___________");
        PRINT_CENTERED("/CHARON DEMO\\");
    }
    else
    {
        PRINT_CENTERED("  _______ _____   ___  ____  _  __    ___  ______  _______ ");
        PRINT_CENTERED(" / ___/ // / _ | / _ \\/ __ \\/ |/ /   / _ \\/ __/  |/  / __ \\");
        PRINT_CENTERED("/ /__/ _  / __ |/ , _/ /_/ /    /   / // / _// /|_/ / /_/ /");
        PRINT_CENTERED("\\___/_//_/_/ |_/_/|_|\\____/_/|_/   /____/___/_/  /_/\\____/ ");
    }
    printf("\n\n");
}


static void demo_clearTerminal (void)
{
    // could be used in future for OS based demo
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}


static void demo_currentlyNotSupported (void)
{
    PRINT_CENTERED(" / ! \\");
    printf("\n");
    PRINT_CENTERED("DEMO AT THE MOMENT NOT SUPPORTED TRY AGAIN, PRESS ENTER TO CONTINUE.");
    fflush(stdout);

    fflush(stdin);
    getchar();
}


static void demo_defaultInputFailed (void)
{
    PRINT_CENTERED(" / ! \\");
    printf("\n");
    PRINT_CENTERED("REQUEST NOT SUPPORTED TRY AGAIN, PRESS ENTER TO CONTINUE.");
    fflush(stdout);

    fflush(stdin);
    getchar();
    demo_clearTerminal();
}


static void demo_subfunctionBySentinelNotSupported (void)
{
    PRINT_CENTERED(" / ! \\");
    printf("\n");
    PRINT_CENTERED("OBD GROUP IS NOT SUPPORTED BY SENTINEL SOFTWARE ATM.");

    printf("\n    press ENTER to return to subfunction selection.");
    fflush(stdout);


    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
}


static void printDemoMessage(UDS_Client_Error_t error, uint8_t* receive, uint32_t receive_length) 
{
    // clear old data 
    serverError = 0x00;
    for (uint32_t i = 0; i < serverResponseLength; i++)
    {
        serverResponse[i] = 0x00;
    }
    serverResponseLength = 0x00;


    // Duplicates response information into the static cache.
    serverError = error;
    serverResponseLength = receive_length;
    for (uint32_t i = 0; i < receive_length; i++)
    {
        serverResponse[i] = receive[i];
    }
    

    if(error != E_OK) 
    {
        UDS_LOG_WARNING("Got Error response %s (0x%02x)", ErrorCode_getString(error), error);
    }
    if(receive != NULL) 
    {
        printf("[UDS Server --> UDS Client] received: 0x");
        for (int i = 0; i < receive_length; i++) 
        {
            printf("%02x", receive[i]);
        }
        printf("\n"); 
    }
    return;
}


static void uds_demoWait (void)
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


static void demo_DTCResponseToDelete_return (bool wait)
{
    if (serverResponse[0] == 84)
    {
        demo_DTCResponseToDelete_positive(wait);
    }
    else
    {
        demo_DTCResponseToDelete_negative(wait);
    }
}

static void demo_DTCResponseToDelete_positive (bool wait)
{
    printf("\n");
    PRINT_CENTERED("DTC is now cleared and SERVER send a Positive response (0x54) to the CLIENT.");
    printf("\n");
    if (wait)
    {
        fflush(stdin);
        getchar();
    }
}

static void demo_DTCResponseToDelete_negative (bool wait)
{
    printf("\n");
    PRINT_CENTERED("Something went wrong and SERVER send a Negative response to the CLIENT.");
    printf("\n");
    if (wait)
    {
        fflush(stdin);
        getchar();
    }
}


static uint32_t demo_xToUint_32(uint8_t *str)
{
    uint32_t returnValue = 0;
    char c;

    // Number and shifting magic found in the webs but it may be forgotten about its existence.
    while ((c = *str++)) 
    {
        char v = ((c & 0xF) + (c >> 6)) | ((c >> 3) & 0x8);
        returnValue = (returnValue << 4) | (uint32_t) v;
    }
    return returnValue;
} 


static uint32_t demo_DTCNumberInputAndHexCheck (void)
{
    bool whileBreaker = true;
    uint8_t buffer[7] = {0};
    uint8_t directInputBuffer[3] = {0};


    for (uint8_t i = 0; i < 3; i++)
    {
        while (whileBreaker == true)
        {
            if (i == 0)
            {
                printf("\n    Type the high byte of the 24 bit DTC number digit:\n\n    0x");
                fflush(stdout);
            }
            if (i == 1)
            {
                printf("\n    Type the middle byte of the 24 bit DTC number digit:\n\n    0x");
                fflush(stdout);
            }
            if (i == 2)
            {
                printf("\n    Type the low byte of the 24 bit DTC number digit:\n\n    0x");
                fflush(stdout);
            }

            // Take user input.
            fflush(stdin);
            scanf("%3s",directInputBuffer); // <-- Will bug out sometimes if only a 2 slot array is used, so 3 will be kept.
                    
            // Check for size valid input.
            if (directInputBuffer[1] == 0)
            {
                printf("\n");
                PRINT_CENTERED("Wrong input! Double digit needed.");
                printf("\n\n");
                fflush(stdout);
            }

            // Check for HEX valid input.
            if ((directInputBuffer[0] >= 'A' && directInputBuffer[0] <= 'F') || (directInputBuffer[0] >= 'a' && directInputBuffer[0] <= 'f') || (directInputBuffer[0] >= '0' && directInputBuffer[0] <= '9'))
            {
                if ((directInputBuffer[1] >= 'A' && directInputBuffer[1] <= 'F') || (directInputBuffer[1] >= 'a' && directInputBuffer[1] <= 'f') || (directInputBuffer[1] >= '0' && directInputBuffer[1] <= '9'))
                {
                    whileBreaker = false;
                }   
            }
        }
        whileBreaker = true;

        // Filling temporary buffer.
        buffer[(i * 2)] = directInputBuffer[0];
        buffer[((i * 2) + 1)] = directInputBuffer[1];

        // Resetting buffer for next round.
        directInputBuffer[1] = 0;
        directInputBuffer[2] = 0;
    }

    // Give user input back.
    printf("\n    Your requested DTC is : %6s", buffer);
    fflush(stdout);
    printf("\n\n");
    PRINT_CENTERED("Request will be send to server now.");
    fflush(stdout);
    // Will turn user input into hex.
    return demo_xToUint_32(buffer);
}


static uint32_t demo_DIDNumberInputAndHexCheck (void)
{
    bool whileBreaker = true;
    uint8_t directInputBuffer[6] = {0};
    uint8_t safetyInputBuffer[4] = {0};

    while (whileBreaker)
    {
        // Take user input. params will only scan the first 4 chars AND will only scan HEX valid inputs 
        fflush(stdin);
        scanf("%5[a-fA-F0-9]",directInputBuffer);       /* Dunno what cpp wants from me here  \`[-|-] /  */

        for (uint8_t i = 0; i < 4; i++)
        {
            safetyInputBuffer[i] = directInputBuffer[i]; // scanf can be a bit faulty and gets a bigger buffer for that reason.
        }
        
        // Check for size of valid input.
        if (safetyInputBuffer[3] == 0)
        {
            printf("\n");
            PRINT_CENTERED("Wrong input! Full valid HEX, DID number needed. Try again.");
            printf("\n\n");
            fflush(stdout);
        } 
        else
        {
            whileBreaker = false; 
            // Give user input back.
            printf("\n    Your requested DID is : %.4s", safetyInputBuffer);
            fflush(stdout);
            printf("\n\n"); 
        }
    }
    // Will turn user input into hex.
    return demo_xToUint_32(safetyInputBuffer);
}


static uint32_t demo_get8bitHex (void)
{
    bool whileBreaker = true;
    uint8_t userInput[] = {0,0,0};
    uint8_t buffer[3] = {0};

    // Get user input.
    while (whileBreaker == true)
    {
        fflush(stdin);
        scanf("%3s",userInput);
        // Filter only for valid input.
        if (userInput[1] == 0)
        {
            printf("\n");
            PRINT_CENTERED("Wrong input! Double digit needed. Try again.");
            printf("\n\n");
            fflush(stdout);
        }


        if ((userInput[0] >= 'A' && userInput[0] <= 'F') || (userInput[0] >= 'a' && userInput[0] <= 'f') || (userInput[0] >= '0' && userInput[0] <= '9'))
        {
            if ((userInput[1] >= 'A' && userInput[1] <= 'F') || (userInput[1] >= 'a' && userInput[1] <= 'f') || (userInput[1] >= '0' && userInput[1] <= '9'))
            {
                buffer[0] = userInput[0];
                buffer[1] = userInput[1];
                whileBreaker = false;
            }   
        }
    }
    

    // Gives user input back
    printf("    Your input is : 0x%2s\n", buffer);
    fflush(stdout);
    // will turn user input into hex
    return demo_xToUint_32(buffer);
}


//#############################################################################
//#     Main functions
//#############################################################################
static void demo_terminalSizeQuestion (void)
{
    // Start up screen.
    demo_printUnderscoreLine_noFlush();
    PRINT_CENTERED("Press ENTER when your wanted terminal size is set.");
    demo_printUnderscoreLine_noFlush();
    fflush(stdout);
    getchar();
}


static void demo_welcomeMenu (void)
{
    uint8_t input;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("Welcome to our CHARON, Please TYPE which demo you want to run.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");

    printf("           [1]  =  DTC handling\n\n\n");


    printf("           [2]  =  DID handling\n\n\n");


    printf("           [3]  =  Diagnostic and communication management\n\n\n");


    printf("           [E]  =  EXIT the demo\n\n\n\n\n\n");
    fflush(stdout);

    fflush(stdin);
    input = getchar();
    switch (input)
    {
    case '1':
        // DTC demo.
        demo_DTC();
        break;
    

    case '2':
        // DID demo.
        demo_DID();
        break;


    case '3':
        // Diagnostic and communication management demo.
        demo_currentlyNotSupported();
        demo_clearTerminal();
        demo_welcomeMenu();
        break;


    case 'E':
    case 'e':
        // EXIT the demo.
        demo_clearTerminal();
        exit(0);
        break;


    default:
        // Input not valid try again.
        demo_defaultInputFailed();
        demo_welcomeMenu();
        break;
    }
}


//#############################################################################
//#     DTC area
//#############################################################################
static void demo_DTC (void)
{
    uint8_t input;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("Welcome to DTC demo, TYPE your wanted SID.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");

    printf("    SID 0x1[4]  =  ClearDiagnosticInformation\n\n\n");


    printf("    SID 0x1[9]  =  ReadDTCInformation\n\n\n");


    printf("    SID 0x8[5]  =  ControlDTCSetting\n\n\n");


    printf("           [B]  =  Back to demo selection\n\n\n\n");
    fflush(stdout);


    fflush(stdin);
    input = getchar();
    switch (input)
    {
    case '4':
        // SID 0x14
        demo_SID_0X14_DTC();
        break;
    

    case '9':
        // SID 0x19
        demo_SID_0X19_DTC();
        break;


    case '5':
        // SID 0x85
        demo_SID_0X85_DTC();
        break;


    case 'B':
        // Back to menu.
        demo_clearTerminal();
        demo_welcomeMenu();
        break;
    case 'b':
        // Back to menu.
        demo_clearTerminal();
        demo_welcomeMenu();
        break;


    default:
        // Input not valid try again.
        demo_defaultInputFailed();
        demo_DTC();
        break;
    }
}


static void demo_SID_0X14_DTC (void)
{
    uint8_t input;
     
    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0x14: ClearDiagnosticInformation, TYPE your wanted input to the server.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");

    printf("    Use one of the suggestions OR choose your own input but it might not delete a DTC, needs a perfect fit.\n\n\n");


    printf("           [1]  =  Groups of DTC                 \n\n\n");


    printf("           [2]  =  Single DTC                    \n\n\n");


    printf("           [B]  =  Back to demo selection \n\n");

    fflush(stdout);

    // get input
    fflush(stdin);
    input = getchar();

    switch (input)
    {
    case '1':
        demo_SID_0X14_groupDTCSelection();
        break;


    case '2':
        demo_SID_0X14_singleDTCSelection();
        break;


    case 'B':
    case 'b':
        demo_clearTerminal();
        demo_DTC();
        break;


    default:
        // Input not valid try again.
        demo_defaultInputFailed();
        demo_SID_0X14_DTC();
        break;
    }
}

static void demo_SID_0X14_groupDTCSelection (void)
{
    uint8_t input;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("DTC group deletion.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");


    if (currentTerminalSize.columns <= 120)
    {
        printf("    TYPE your wanted group.\n\n\n");

        printf("           [1]  =   VOBD_SYSTEM_GROUP                                _______________________________________________ \n");
        printf("           [2]  =   SAFETY_SYSTEM_GROUP                             |                                               |\n");
        printf("           [3]  =   EMISSION_SYSTEM_GROUP                           |    0xFFFFFE  =  VOBD_SYSTEM_GROUP             |\n");
        printf("           [4]  =   DEL_ALL_DTC                                     |    0xFFFFD0  =  SAFETY_SYSTEM_GROUP           |\n");
        printf("                                                                    |    0xFFFF33  =  EMISSION_SYSTEM_GROUP         |\n");
        printf("           [5]  =   powertrain group                                |    0xFFFFFF  =  DEL_ALL_DTC                   |\n");
        printf("           [6]  =   chassis group                                   |                                               |\n");
        printf("           [7]  =   body group                                      |    0x000100  =  powertrain_group              |\n");
        printf("           [8]  =   network_communication group                     |    0xB00000  =  chassis_group                 |\n");
        printf("                                                                    |    0xD00000  =  body_group                    |\n");
        printf("           [B]  =  Back to SID 0x14 selection                       |    0xF00000  =  network_communication_group   |\n\n");
    } 
    else
    {
        printf("    TYPE your wanted group.\n\n\n");

        printf("           [1]  =   VOBD_SYSTEM_GROUP                                                                                           _______________________________________________ \n");
        printf("           [2]  =   SAFETY_SYSTEM_GROUP                                                                                        |                                               |\n");
        printf("           [3]  =   EMISSION_SYSTEM_GROUP                                                                                      |    0xFFFFFE  =  VOBD_SYSTEM_GROUP             |\n");
        printf("           [4]  =   DEL_ALL_DTC                                                                                                |    0xFFFFD0  =  SAFETY_SYSTEM_GROUP           |\n");
        printf("                                                                                                                               |    0xFFFF33  =  EMISSION_SYSTEM_GROUP         |\n");
        printf("           [5]  =   powertrain group                                                                                           |    0xFFFFFF  =  DEL_ALL_DTC                   |\n");
        printf("           [6]  =   chassis group                                                                                              |                                               |\n");
        printf("           [7]  =   body group                                                                                                 |    0x000100  =  powertrain_group              |\n");
        printf("           [8]  =   network_communication group                                                                                |    0xB00000  =  chassis_group                 |\n");
        printf("                                                                                                                               |    0xD00000  =  body_group                    |\n");
        printf("           [B]  =  Back to SID 0x14 selection                                                                                  |    0xF00000  =  network_communication_group   |\n\n");
    }
    fflush(stdout);

    // get input
    fflush(stdin);
    input = getchar();
    switch (input)
    {
    case '1':
        printf("    VOBD_SYSTEM_GROUP requested.\n\n");
        UDS_DTC_ClearDiagnosticInformation(0xFFFFFE,printDemoMessage);
        uds_demoWait();

        demo_DTCResponseToDelete_return(true);
        demo_SID_0X14_groupDTCSelection();
        break;


    case '2':
        printf("    SAFETY_SYSTEM_GROUP requested.\n\n");
        UDS_DTC_ClearDiagnosticInformation(0xFFFFD0,printDemoMessage);
        uds_demoWait();

        demo_DTCResponseToDelete_return(true);
        demo_SID_0X14_groupDTCSelection();
        break;


    case '3':
        printf("    EMISSION_SYSTEM_GROUP requested.\n\n");
        UDS_DTC_ClearDiagnosticInformation(0xFFFF33,printDemoMessage);
        uds_demoWait();

        demo_DTCResponseToDelete_return(true);
        demo_SID_0X14_groupDTCSelection();
        break;


    case '4':
        printf("    DEL_ALL_DTC requested.\n\n");
        UDS_DTC_ClearDiagnosticInformation(0xFFFFFF,printDemoMessage);
        uds_demoWait();

        demo_DTCResponseToDelete_return(true);
        demo_SID_0X14_groupDTCSelection();
        break;


    case '5':
        printf("    powertrain group requested.\n\n");
        UDS_DTC_ClearDiagnosticInformation(0x000100,printDemoMessage);
        uds_demoWait();

        demo_DTCResponseToDelete_return(true);
        demo_SID_0X14_groupDTCSelection();
        break;


    case '6':
        printf("    chassis group requested.\n\n");
        UDS_DTC_ClearDiagnosticInformation(0xB00000,printDemoMessage);
        uds_demoWait();

        demo_DTCResponseToDelete_return(true);
        demo_SID_0X14_groupDTCSelection();
        break;    


    case '7':
        printf("    body group requested.\n\n");
        UDS_DTC_ClearDiagnosticInformation(0xD00000,printDemoMessage);
        uds_demoWait();

        demo_DTCResponseToDelete_return(true);
        demo_SID_0X14_groupDTCSelection();
        break;


    case '8':
        printf("    network_communication group requested.\n\n");
        UDS_DTC_ClearDiagnosticInformation(0xF00000,printDemoMessage);
        uds_demoWait();

        demo_DTCResponseToDelete_return(true);
        demo_SID_0X14_groupDTCSelection();
        break;


    case 'B':
    case 'b':
        demo_SID_0X14_DTC();
        break;


    default:
        // Input not valid try again.
        demo_defaultInputFailed();
        demo_SID_0X14_groupDTCSelection();
        break;
    }
}

static void demo_SID_0X14_singleDTCSelection (void)
{
    uint8_t input[2] = {0,0};

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("DTC single deletion.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");


    printf("    TYPE how many DTC you want to delete. (1-99) \n\n\n");


    printf("           [B]  =  Back to SID 0x14 selection\n\n\n");

    fflush(stdout);


    fflush(stdin);
    scanf("%2s",input);
    if (((input[0] != '0') && (input[1] != '0'))  ||  ((input[0] > '0') && (input[1] != '0')))
    {
        if (input[0] == 'b' || input[0] == 'B')
        {
            demo_SID_0X14_DTC();
        }
        if ((input[0] >= 48 && input[0] <= 57) || (input[1] >= 48 && input[1] <= 57))
        {
            uint16_t amount;
            // input[1] is only 0 by single digit requests
            if (input[1] == 0)
            {
                // Null on single digit input must be eliminated.
                amount = (input[0] - '0');
            } else
            {
                amount = (input[1] - '0');
                if ((input[0] != '0') && (input[0] != 0x00))
                {
                    amount += ((input[0] - '0') * 10);
                }
            }


            // Takes user input for requested amount of DTC.
            for (uint8_t i = 0; i < amount; i++)
            {
                uint32_t userInput = 0;

                userInput = demo_DTCNumberInputAndHexCheck();

                UDS_DTC_ClearDiagnosticInformation(userInput,printDemoMessage);
                uds_demoWait();
                demo_DTCResponseToDelete_return(false);
                if (serverError == 2)
                {
                    printf("\n\n");
                    PRINT_CENTERED("Requested DTC is not supported by ISO 14229-1 or User.");
                    printf("\n\n");
                }
            }
            // Done, return to menu
            printf("\n\n\n\n");
            PRINT_CENTERED("----------------------------------------------------------------------------------------------");
            PRINT_CENTERED("Requested amount to delete DTC are now fulfilled. Press ENTER to return to SID 0x14 selection.");
            PRINT_CENTERED("----------------------------------------------------------------------------------------------");
            printf("\n\n");
            fflush(stdout);
            fflush(stdin);
            getchar();
            demo_SID_0X14_DTC();
        }
    }
    else
    {
        // Input not valid try again.
        demo_defaultInputFailed();
        demo_SID_0X14_singleDTCSelection();
    }
}
  

static void demo_SID_0X19_DTC (void)
{
    uint32_t DTCnumber = 0;
    uint16_t DTCStatusMask = 333;
    uint16_t DTCSeverityMask = 0;
    uint8_t input[2];

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // ReadDTCInformation
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0x19: ReadDTCInformation.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");

    PRINT_CENTERED("By SentinelSW supported subfunctions:");
    printf("\n");
    printf("      Sub 0x01  =  NumberOfDTCByStatusMask\n");
    printf("      Sub 0x02  =  DTCByStatusMask\n");
    printf("      Sub 0x03  =  DTCSnapshotIdentification\n");
    printf("      Sub 0x04  =  DTCSnapshotRecordByDTCNumber\n");
    printf("      Sub 0x05  =  DTCStoredDataByRecordNumber\n");
    printf("      Sub 0x06  =  DTCExtDataRecordByDTCNumber\n");
    printf("      Sub 0x07  =  NumberOfDTCBySeverityMaskRecord\n");
    printf("      Sub 0x08  =  DTCBySeverityMaskRecord\n");
    printf("      Sub 0x09  =  SeverityInformationOfDTC\n");
    printf("      Sub 0x0A  =  SupportedDTC\n");
    printf("      Sub 0x0B  =  FirstTestFailedDTC\n");
    printf("      Sub 0x0C  =  FirstConfirmedDTC\n");
    printf("      Sub 0x0D  =  MostRecentTestFailedDTC\n");
    printf("      Sub 0x0E  =  MostRecentConfirmedDTC\n");
    printf("      Sub 0x0F  =  MirrorMemoryDTCByStatusMask\n");
    printf("      Sub 0x10  =  MirrorMemoryDTCExtDataRecordByDTCNumber\n");
    printf("      Sub 0x11  =  NumberOfMirrorMemoryDTCByStatusMask\n");
    printf("      Sub 0x12  =  NumberOfEmissionsOBDDTCByStatusMask\n");
    printf("      Sub 0x13  =  EmissionsOBDDTCByStatusMask\n");
    printf("      Sub 0x14  =  DTCFaultDetectionCounter\n");
    printf("      Sub 0x15  =  DTCWithPermanentStatus\n");
    printf("      Sub 0x16  =  DTCExtDataRecordByRecordNumber\n");
    printf("      Sub 0x17  =  UserDefMemoryDTCByStatusMask\n");
    printf("      Sub 0x18  =  UserDefMemoryDTCSnapshotRecordByDTCNumber\n");
    printf("      Sub 0x19  =  UserDefMemoryDTCExtDataRecordByDTCNumber\n\n");

    printf("           [B]  =  Back to demo selection\n");
    printf("0x");
    fflush(stdout);

    fflush(stdin);
    scanf("%2s",input);

    // Single digit input is only valid for back request
    if (((input[0] == 'b') || (input[0] == 'B')) && (input[1] == 0))
    {
        demo_clearTerminal();
        demo_DTC();
    }

    if ((input[0] == '0') && (input[1] == '1'))
    {
        PRINT_CENTERED("Requested subfunction: 0x01.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function takes input and will AND 16 to 16 bit mask, counts up when even 1 bit is a hit.");
        printf("\n\n");
        
        while (DTCStatusMask >= 256)
        {
            PRINT_CENTERED("TYPE your wanted StatusMask. (0x00 - 0xFF)");
            printf("0x");
            fflush(stdout);
            DTCStatusMask = demo_get8bitHex();
        }

        UDS_DTC_ReportNumberOfDTCByStatusMask(DTCStatusMask,printDemoMessage);
        uds_demoWait();

        demo_SID_0X19_DTC_subfunctionResponseTable271();
    }

    if ((input[0] == '0') && (input[1] == '2'))
    {
        PRINT_CENTERED("Requested subfunction: 0x02.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function takes input and will AND 16 to 16 bit mask, when even 1 bit is a hit it will return this DTC.");
        printf("\n\n");


        while (DTCStatusMask >= 256)
        {
            PRINT_CENTERED("TYPE your wanted StatusMask. (0x00 - 0xFF)");
            PRINT_CENTERED("(Request for only one bit works best for an overview, 0x04 for example.)");
            printf("0x");
            fflush(stdout);
            DTCStatusMask = demo_get8bitHex();
        }

        UDS_DTC_ReportDTCByStatusMask(DTCStatusMask,printDemoMessage);
        uds_demoWait();

        demo_SID_0X19_DTC_subfunctionResponseTable272();
    }

    if ((input[0] == '0') && (input[1] == '3'))
    {
        PRINT_CENTERED("Requested subfunction: 0x03.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function will return all DTC with a snapshot saved to them + the Snapshot identification number.");
        printf("\n\n");


        UDS_DTC_ReportDTCSnapshotIdentification(printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable273();
    }

    if ((input[0] == '0') && (input[1] == '4'))
    {
        PRINT_CENTERED("Requested subfunction: 0x04.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function will return DTC with requested Snapshot number.");
        PRINT_CENTERED("(its advised to load subfunction 0x03 first to see DTC + Snapshot number)");
        printf("\n\n");


        DTCnumber = demo_DTCNumberInputAndHexCheck();

        PRINT_CENTERED("_________________________________");
        PRINT_CENTERED("TYPE the fitting Snapshot number.");
        printf("0x");
        uint8_t snapshotNumber = demo_get8bitHex();
        
        UDS_DTC_ReportDTCSnapshotRecordByDTCNumber(DTCnumber,snapshotNumber,printDemoMessage);
        uds_demoWait();

        demo_SID_0X19_DTC_subfunctionResponseTable274();
    }

    if ((input[0] == '0') && (input[1] == '5'))
    {
        PRINT_CENTERED("Requested subfunction: 0x05.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function will return DTC with matching StoredDataRecordNumber.");
        printf("\n\n");


        printf("TYPE your wanted Stored Data Record Number:\n");
        printf("0x");
        uint8_t dataRecordNumber = demo_get8bitHex();


        UDS_DTC_ReportDTCStoredDataByRecordNumber(dataRecordNumber,printDemoMessage);
        uds_demoWait();

        demo_SID_0X19_DTC_subfunctionResponseTable275();
    }

    if ((input[0] == '0') && (input[1] == '6'))
    {
        PRINT_CENTERED("Requested subfunction: 0x06.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function will return the first OR all (request 0xFF) saved ExtDataRecord.");
        printf("\n\n");


        DTCnumber = demo_DTCNumberInputAndHexCheck();

        PRINT_CENTERED("______________________________________");
        PRINT_CENTERED("TYPE your input, any number or 0xFF for all saved.");
        printf("0x");
        fflush(stdout);
        uint8_t extDataRecordNumber = demo_get8bitHex();

        UDS_DTC_ReportDTCExtDataRecordByDTCNumber(DTCnumber, extDataRecordNumber, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable276();
    }

    if ((input[0] == '0') && (input[1] == '7'))
    {
        PRINT_CENTERED("Requested subfunction: 0x07.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function takes input and will AND 16 to 16 bit mask, counts up when even 1 bit is a hit.");
        printf("\n\n");
        

        PRINT_CENTERED("TYPE your wanted SeverityMask. (0x00 - 0xFF)");
        printf("0x");
        fflush(stdout);
        DTCSeverityMask = demo_get8bitHex();

        PRINT_CENTERED("TYPE your wanted StatusMask. (0x00 - 0xFF)");
        printf("0x");
        fflush(stdout);
        DTCStatusMask = demo_get8bitHex();


        UDS_DTC_ReportNumberOfDTCBySeverityMaskRecord(DTCSeverityMask, DTCStatusMask, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable271();
    }

    if ((input[0] == '0') && (input[1] == '8'))
    {
        PRINT_CENTERED("Requested subfunction: 0x08.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function takes input and will AND 16 to 16 bit mask, returns all DTC matching your request.");
        printf("\n\n");
        

        PRINT_CENTERED("TYPE your wanted SeverityMask. (0x00 - 0xFF)");
        printf("0x");
        fflush(stdout);
        DTCSeverityMask = demo_get8bitHex();

        PRINT_CENTERED("TYPE your wanted StatusMask. (0x00 - 0xFF)");
        printf("0x");
        fflush(stdout);
        DTCStatusMask = demo_get8bitHex();


        UDS_DTC_ReportDTCBySeverityMaskRecord(DTCSeverityMask, DTCStatusMask, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable277();
    }

    if ((input[0] == '0') && (input[1] == '9'))
    {
        PRINT_CENTERED("Requested subfunction: 0x09.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Returns requested DTC and severity information.");
        printf("\n\n");

        
        DTCnumber = demo_DTCNumberInputAndHexCheck();


        UDS_DTC_ReportSeverityInformationOfDTC(DTCnumber, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable277();
    }

    if (((input[1] == 'a') || (input[1] == 'A')) && (input[0] == '0'))
    {
        PRINT_CENTERED("Requested subfunction: 0x0A.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Returns all supported DTC.");
        printf("\n\n");


        UDS_DTC_ReportSupportedDTC(printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable272();
    }

    if (((input[1] == 'b') || (input[1] == 'B')) && (input[0] == '0'))
    {
        PRINT_CENTERED("Requested subfunction: 0x0B.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Returns first failed DTC.");
        printf("\n\n");


        UDS_DTC_ReportFirstTestFailedDTC(printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable272();
    }

    if (((input[1] == 'c') || (input[1] == 'C')) && (input[0] == '0'))
    {
        PRINT_CENTERED("Requested subfunction: 0x0C.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Returns first confirmed DTC.");
        printf("\n\n");


        UDS_DTC_ReportFirstConfirmedDTC(printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable272();
    }

    if (((input[1] == 'd') || (input[1] == 'D')) && (input[0] == '0'))
    {
        PRINT_CENTERED("Requested subfunction: 0x0D.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Returns most recent failed DTC.");
        printf("\n\n");


        UDS_DTC_ReportMostRecentTestFailedDTC(printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable272();
    }

    if (((input[1] == 'e') || (input[1] == 'E')) && (input[0] == '0'))
    {
        PRINT_CENTERED("Requested subfunction: 0x0E.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Returns most recent confirmed DTC.");
        printf("\n\n");


        UDS_DTC_ReportMostRecentConfirmedDTC(printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable272();
    }

    if (((input[1] == 'f') || (input[1] == 'F')) && (input[0] == '0'))
    {
        PRINT_CENTERED("Requested subfunction: 0x0F.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function takes input and will AND 16 to 16 bit mask, when even 1 bit is a hit it will return this DTC.");
        PRINT_CENTERED("(Works like sub 0x02 but will get its information out of the MIRROR MEMORY.)");
        printf("\n\n");


        while (DTCStatusMask >= 256)
        {
            PRINT_CENTERED("TYPE your wanted StatusMask. (0x00 - 0xFF)");
            PRINT_CENTERED("(Request for only one bit works best for an overview, 0x04 for example.)");
            printf("0x");
            fflush(stdout);
            DTCStatusMask = demo_get8bitHex();
        }

        UDS_DTC_ReportMirrorMemoryDTCByStatusMask(DTCStatusMask, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable272();
    }

    if ((input[0] == '1') && (input[1] == '0'))
    {
        PRINT_CENTERED("Requested subfunction: 0x10.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function will return requested ExtDataRecord.");
        PRINT_CENTERED("(Works like sub 0x06 but will get its information out of the MIRROR MEMORY.)");
        printf("\n\n");


        DTCnumber = demo_DTCNumberInputAndHexCheck();

        PRINT_CENTERED("______________________________________");
        PRINT_CENTERED("TYPE the fitting ExtDataRecord number.");
        printf("0x");
        fflush(stdout);
        uint8_t extDataRecordNumber = demo_get8bitHex();

        UDS_DTC_ReportDTCExtDataRecordByDTCNumber(DTCnumber, extDataRecordNumber, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable276();
    }

    if ((input[0] == '1') && (input[1] == '1'))
    {
        PRINT_CENTERED("Requested subfunction: 0x11.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function takes input and will AND 16 to 16 bit mask, counts up when even 1 bit is a hit.");
        PRINT_CENTERED("(Works like sub 0x01 but will get its information out of the MIRROR MEMORY.)");
        printf("\n\n");
        

        while (DTCStatusMask >= 256)
        {
            PRINT_CENTERED("TYPE your wanted StatusMask. (0x00 - 0xFF)");
            printf("0x");
            fflush(stdout);
            DTCStatusMask = demo_get8bitHex();
        }

        UDS_DTC_ReportNumberOfMirrorMemoryDTCByStatusMask(DTCStatusMask, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable271();
    }

    if ((input[0] == '1') && (input[1] == '2'))
    {
        PRINT_CENTERED("Requested subfunction: 0x12.");
        demo_printUnderscoreLine_noFlush();
        printf("\n\n");


        demo_subfunctionBySentinelNotSupported();
    }

    if ((input[0] == '1') && (input[1] == '3'))
    {
        PRINT_CENTERED("Requested subfunction: 0x13.");
        demo_printUnderscoreLine_noFlush();
        printf("\n\n");


        demo_subfunctionBySentinelNotSupported();
    }

    if ((input[0] == '1') && (input[1] == '4'))
    {
        PRINT_CENTERED("Requested subfunction: 0x14.");
        demo_printUnderscoreLine_noFlush();
        printf("\n\n");


        demo_subfunctionBySentinelNotSupported();
    }

    if ((input[0] == '1') && (input[1] == '5'))
    {
        PRINT_CENTERED("Requested subfunction: 0x15.");
        demo_printUnderscoreLine_noFlush();
        printf("\n\n");


        demo_subfunctionBySentinelNotSupported();
    }

    if ((input[0] == '1') && (input[1] == '6'))
    {
        PRINT_CENTERED("Requested subfunction: 0x16.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Takes DTCExtDataRecordNumber and searches memory for DTC with matching number.");
        printf("\n\n");


        PRINT_CENTERED("TYPE your wanted DTCExtDataRecordNumber. (0x00 - 0xFF)");
        printf("0x");
        fflush(stdout);
        DTCStatusMask = demo_get8bitHex();


        UDS_DTC_ReportDTCExtDataRecordByRecordNumber(DTCStatusMask,printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable279();
    }

    if ((input[0] == '1') && (input[1] == '7'))
    {
        PRINT_CENTERED("Requested subfunction: 0x17.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function takes input and will AND 16 to 16 bit mask, counts up when even 1 bit is a hit.");
        PRINT_CENTERED("(Works like sub 0x01 but will get its information out of the USER DEFINED MEMORY.)");
        printf("\n\n");
        

        while (DTCStatusMask >= 256)
        {
            PRINT_CENTERED("TYPE your wanted StatusMask. (0x00 - 0xFF)");
            printf("0x");
            fflush(stdout);
            DTCStatusMask = demo_get8bitHex();
        }

        UDS_DTC_ReportUserDefMemoryDTCByStatusMask(DTCStatusMask, 1, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable271();
    }

    if ((input[0] == '1') && (input[1] == '8'))
    {
        PRINT_CENTERED("Requested subfunction: 0x18.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function will return DTC with requested Snapshot number.");
        PRINT_CENTERED("(its advised to load subfunction 0x03 first to see DTC + Snapshot number)");
        PRINT_CENTERED("(Works like sub 0x04 but will get its information out of the USER DEFINED MEMORY.)");
        printf("\n\n");


        DTCnumber = demo_DTCNumberInputAndHexCheck();

        PRINT_CENTERED("_________________________________");
        PRINT_CENTERED("TYPE the fitting Snapshot number.");
        printf("0x");
        uint8_t snapshotNumber = demo_get8bitHex();
        
        UDS_DTC_ReportUserDefMemoryDTCSnapshotRecordByDTCNumber(DTCnumber,snapshotNumber,1,printDemoMessage);
        uds_demoWait();

        demo_SID_0X19_DTC_subfunctionResponseTable274();
    }

    if ((input[0] == '1') && (input[1] == '9'))
    {
        PRINT_CENTERED("Requested subfunction: 0x19.");
        demo_printUnderscoreLine_noFlush();
        printf("\n");
        PRINT_CENTERED("Function will return requested ExtDataRecord.");
        PRINT_CENTERED("(Works like sub 0x06 but will get its information out of the USER DEFINED MEMORY.)");

        printf("\n\n");


        DTCnumber = demo_DTCNumberInputAndHexCheck();

        PRINT_CENTERED("______________________________________");
        PRINT_CENTERED("TYPE the fitting ExtDataRecord number.");
        printf("0x");
        fflush(stdout);
        uint8_t extDataRecordNumber = demo_get8bitHex();

        UDS_DTC_ReportUserDefMemoryDTCExtDataRecordByDTCNumber(DTCnumber, extDataRecordNumber,1, printDemoMessage);
        uds_demoWait();


        demo_SID_0X19_DTC_subfunctionResponseTable276();
    }
    else
    {
        // Input not valid try again.
        demo_defaultInputFailed();
        demo_SID_0X19_DTC();
    }
}

static void demo_SID_0X19_DTC_subfunctionResponseTable271 (void)
{
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 89)
    {
        printf("0x59 = Positive response\n");
        printf("0x%02x = Requested subfunction\n", serverResponse[1]);
        printf("0x%02x = From server current supported bit mask\n", serverResponse[2]);
        printf("0x%02x = DTC format: 0x01 for ISO_14229-1\n", serverResponse[3]);

        printf("0x%02x = DTC count high byte\n", serverResponse[4]);
        printf("0x%02x = DTC count low byte\n\n\n", serverResponse[5]);

        uint16_t temp = ((serverResponse[4] << 8) | serverResponse[5]);
        printf("---------------------------------------------------\n");
        printf("There are currently %4i DTCs matching your request.\n",temp);
        printf("---------------------------------------------------\n\n");

        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_SID_0X19_DTC();
        
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
    }
}

static void demo_SID_0X19_DTC_subfunctionResponseTable272 (void)
{
    uint32_t count = ((serverResponseLength - 3) / 4);

    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 89)
    {
        printf("0x59 = Positive response\n");
        printf("0x%02x = Requested subfunction\n", serverResponse[1]);
        printf("0x%02x = From server current supported bit mask\n\n", serverResponse[2]);

        printf(".--------------------------------------------------------------.\n");
        printf("|  Unique DTC identification number       Status of DTC        |\n");
        printf("'--------------------------------------------------------------'\n");
        for (uint32_t i = 0; i < count; i++)
        {
            printf("|  0x%02x%02x%02x                               0x%02x                 |\n", serverResponse[(i * 4) + 3],serverResponse[(i * 4) + 4],serverResponse[(i * 4) + 5], serverResponse[(i * 4) + 6]);
            printf("|..............................................................|\n");
        }
        printf("'--------------------------------------------------------------'\n\n\n");


        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_SID_0X19_DTC();
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
    }
}

static void demo_SID_0X19_DTC_subfunctionResponseTable273 (void)
{
    uint32_t count = ((serverResponseLength - 2) / 4);

    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 89)
    {
        printf("0x59 = Positive response\n");
        printf("0x%02x = Requested subfunction\n\n", serverResponse[1]);

        printf(".--------------------------------------------------------------.\n");
        printf("|  Unique DTC identification number       Snapshot number      |\n");
        printf("'--------------------------------------------------------------'\n");
        for (uint32_t i = 0; i < count; i++)
        {
            printf("|  0x%02x%02x%02x                               0x%02x                 |\n", serverResponse[(i * 4) + 2],serverResponse[(i * 4) + 3],serverResponse[(i * 4) + 4], serverResponse[(i * 4) + 5]);
            printf("|..............................................................|\n");
        }
        printf("'--------------------------------------------------------------'\n\n\n");


        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_SID_0X19_DTC();
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
    }
}

static void demo_SID_0X19_DTC_subfunctionResponseTable274 (void)
{
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 89)
    {
        printf("0x59 = Positive response\n");
        printf("0x%02x = Requested subfunction\n", serverResponse[1]);
        printf("0x%02x%02x%02x = Echo of: DTC identification number\n", serverResponse[2],serverResponse[3],serverResponse[4]);
        printf("0x%02x = Current DTC status\n", serverResponse[5]);
        printf("0x%02x = Snapshot number\n", serverResponse[6]);
        printf("0x%02x = Number of identifiers for the Snapshot\n", serverResponse[7]);

        printf("Snapshot payload:\n");
        printf("0x");
        for (uint32_t i = 8; i < serverResponseLength; i++)
        {
            printf("%02x", serverResponse[i]);
        }
        printf("\n\n");


        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_SID_0X19_DTC();
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
    }
}

static void demo_SID_0X19_DTC_subfunctionResponseTable275 (void)
{
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 89)
    {
        printf("0x59 = Positive response\n");
        printf("0x%02x = Requested subfunction\n", serverResponse[1]);
        printf("0x%02x = Data Record number\n", serverResponse[2]);
        printf("0x%02x%02x%02x = Echo of: DTCStoredDataRecordNumber\n", serverResponse[3],serverResponse[4],serverResponse[5]);
        printf("0x%02x = Current DTC status\n", serverResponse[6]);
        
        printf("0x%02x = Number of identifiers for the Data Record\n", serverResponse[7]);

        printf("Data Record payload:\n");
        printf("0x");
        for (uint32_t i = 8; i < serverResponseLength; i++)
        {
            printf("%02x", serverResponse[i]);
        }
        printf("\n\n");


        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_SID_0X19_DTC();
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
    }
}

static void demo_SID_0X19_DTC_subfunctionResponseTable276 (void)
{
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 89)
    {
        if (serverResponseLength == 0x06)
        {
            printf("0x59 = Positive response\n");
            printf("0x%02x = Requested subfunction\n", serverResponse[1]);
            printf("0x%02x%02x%02x = Echo of: DTC identification number\n", serverResponse[2],serverResponse[3],serverResponse[4]);
            printf("0x%02x = Current DTC status\n", serverResponse[5]);
            printf("    Server found no match so send beck an eco of the request.\n");


            PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
            fflush(stdout);
            fflush(stdin);
            getchar();
            demo_SID_0X19_DTC();
        }
        else 
        {
            printf("0x59 = Positive response\n");
            printf("0x%02x = Requested subfunction\n", serverResponse[1]);
            printf("0x%02x%02x%02x = Echo of: DTC identification number\n", serverResponse[2],serverResponse[3],serverResponse[4]);
            printf("0x%02x = Current DTC status\n", serverResponse[5]);
            printf("0x%02x = ExtDataRecord number\n", serverResponse[6]);

            printf("ExtDataRecord payload:\n");
            printf("0x");
            for (uint32_t i = 7; i < serverResponseLength; i++)
            {
                printf("%02x", serverResponse[i]);
            }
            printf("\n\n");


            PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
            fflush(stdout);
            fflush(stdin);
            getchar();
            demo_SID_0X19_DTC();
        }
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
    }
}

static void demo_SID_0X19_DTC_subfunctionResponseTable277 (void)
{
    uint32_t count = ((serverResponseLength - 3) / 6);

    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 89)
    {
        printf("0x59 = Positive response\n");
        printf("0x%02x = Requested subfunction\n", serverResponse[1]);
        printf("0x%02x = From server current supported bit mask\n\n", serverResponse[2]);

        printf(".----------------------------------------------------------------------------------------------.\n");
        printf("|  DTCSeverity mask  |  DTCFunctionalUnit  |  Unique DTC identification number  |  DTC status  |\n");
        printf("'----------------------------------------------------------------------------------------------'\n");
        for (uint32_t i = 0; i < count; i++)
        {
            printf("|  0x%02x              |  0x%02x               |  0x%02x%02x%02x                          |  0x%02x        |\n", serverResponse[(i * 6) + 3],serverResponse[(i * 6) + 4],serverResponse[(i * 6) + 5], serverResponse[(i * 6) + 6], serverResponse[(i * 6) + 7], serverResponse[(i * 6) + 8]);
            printf("|..............................................................................................|\n");
        }
        printf("'----------------------------------------------------------------------------------------------'\n\n\n");


        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_SID_0X19_DTC();
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
    }
}

static void demo_SID_0X19_DTC_subfunctionResponseTable279 (void)
{
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 89)
    {
        printf("0x59 = Positive response\n");
        printf("0x%02x = Requested subfunction\n", serverResponse[1]);
        printf("0x%02x = Extended Data Record number\n", serverResponse[2]);
        printf("0x%02x%02x%02x = DTC identification number\n", serverResponse[3],serverResponse[4],serverResponse[5]);
        printf("0x%02x = Current DTC status\n", serverResponse[6]);
    
        printf("Extended Data Record payload:\n");
        printf("0x");
        for (uint32_t i = 7; i < serverResponseLength; i++)
        {
            printf("%02x", serverResponse[i]);
        }
        printf("\n\n");


        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_SID_0X19_DTC();
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X19_DTC();
    }
}


//#############################################################################
//#     DID area
//#############################################################################
static void demo_DID (void)
{
    uint8_t input;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("Welcome to DID demo, TYPE your wanted SID.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");

    printf("    SID 0x2[2]  =  ReadDataByIdentifier\n\n\n");


    printf("    SID 0x2[3]  =  ReadMemoryByAddress\n\n\n");


    printf("    SID 0x2[4]  =  ReadScalingDataByIdentifier\n\n\n");


    printf("    SID 0x2[A]  =  ReadDataByPeriodicIdentifier\n\n\n");


    printf("    SID 0x2[C]  =  DynamicallyDefineDataIdentifier\n\n\n");


    printf("    SID 0x2[E]  =  WriteDataByIdentifier\n\n\n");


    printf("    SID 0x3[D]  =  WriteMemoryByAddress\n\n\n");


    printf("           [B]  =  Back to demo selection\n\n");
    fflush(stdout);


    fflush(stdin);
    input = getchar();
    switch (input)
    {
    case '2':
        // SID 0x22
        demo_SID_0X22_ReadDataByIdentifier();
        break;
    

    case '3':
        // SID 0x23
        demo_SID_0X23_ReadMemoryByAddress();
        break;


    case '4':
        // SID 0x24
        demo_SID_0X24_ReadScalingDataByIdentifier();
        break;


    case 'A':
    case 'a':
        // SID 0x2A
        demo_SID_0X2A_ReadDataByPeriodicIdentifier();
        break;


    case 'C':
    case 'c':
        // SID 0x2C
        demo_SID_0X2C_DynamicallyDefineDataIdentifier();
        break;


    case 'E':
    case 'e':
        // SID 0x2E
        demo_SID_0X2E_WriteDataByIdentifier();
        break;


    case 'D':
    case 'd':
        // SID 0x3D
        demo_SID_0X3D_WriteMemoryByAddress();
        break;


    case 'B':
    case 'b':
        // Back to menu.
        demo_clearTerminal();
        demo_welcomeMenu();
        break;


    default:
        // Input not valid try again.
        demo_defaultInputFailed();
        demo_DID();
        break;
    } 
}


static void demo_SID_0X22_ReadDataByIdentifier (void)
{
    uint16_t DIDnumber[1];
    uint8_t length = 3u;
    uint8_t input = 0;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // ReadDataByIdentifier.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0x22: ReadDataByIdentifier.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");


    printf("\n    TYPE your requested DID id.    (0x4269 for example)\n\n    0x");
    fflush(stdout);
    // Get requested DID number.
    DIDnumber[0] = (uint16_t)demo_DIDNumberInputAndHexCheck();
    // Send data to server.
    UDS_DT_readDataByIdentifier(DIDnumber,length,printDemoMessage);
    uds_demoWait();

    // Communicate with user based on response
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 0x62)
    {
        printf("0x62 = Positive response\n");
        printf("0x%02x = Requested dataIdentifier high byte (DID Number)\n", serverResponse[1]);
        printf("0x%02x = Requested dataIdentifier low byte  (DID Number)\n", serverResponse[2]);

        printf("DID payload:\n");
        for (uint32_t i = 3; i < serverResponseLength; i++)
        {
            printf("0x%02x ", serverResponse[i]);
        }
        printf("\n\n");

        PRINT_CENTERED("Press ENTER to Try another DID   ///   [B] return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        input = getchar();
        if (input == 'b' || input == 'B')
        {
            demo_DID();
        }
        else
        {
            demo_SID_0X22_ReadDataByIdentifier();
        }
    }
    else
    {
        printf("\n\n");
        PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
        PRINT_CENTERED("Press ENTER to Try another DID   ///   [B] to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        input = getchar();
        if (input == 'b' || input == 'B')
        {
            demo_DID();
            
        }
        else
        {
            demo_SID_0X22_ReadDataByIdentifier();
        }
    }
}

static void demo_SID_0X23_ReadMemoryByAddress (void)
{
    MemoryDefinition memDef;
    uint8_t address[3] = {0x10,0x00,0x00};

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // ReadMemoryByAddress.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0x23: ReadMemoryByAddress.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");
    printf("      Due to complexity of this request,    (user needs to know exact size and other perimeter)\n");
    printf("      subfunction will be pre defined and runs automatic. \n\n\n");

    memcpy(memDef.Address,address,3);
    printf("      memoryAddress =  0x10 0x00 0x00\n\n");
    *(memDef.Size) = 0x0A;
    printf("      memorySize    =  0x0A\n\n");
    memDef.AddressLength = 0x03; // 3 Byte
    printf("      addressAndLengthFormatIdentifier    =  0x03\n");
    printf("      Low nibble of the identifier\n\n");
    memDef.SizeLength = 0x01; // 1 Byte
    printf("      addressAndLengthFormatIdentifier    =  0x10\n");
    printf("      High nibble of the identifier\n\n");

    // Send data to server.
    UDS_DT_readMemoryByAddress(memDef,printDemoMessage);
    uds_demoWait();

    // Communicate with user based on response
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 0x63)
    {
        printf("0x63 = Positive response\n");

        printf("DID payload:\n");
        for (uint32_t i = 1; i < serverResponseLength; i++)
        {
            printf("0x%02x ", serverResponse[i]);
        }
        printf("\n\n");

        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_DID();
    }
    else
    {
        printf("\n\n");
        PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
        PRINT_CENTERED("Press ENTER to return to the DID selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_DID();
    }
}

static void demo_SID_0X24_ReadScalingDataByIdentifier (void)
{
    uint16_t DIDnumber;
    uint8_t input = 0;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // ReadScalingDataByIdentifier.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0x24: ReadScalingDataByIdentifier.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");


    printf("\n    TYPE your requested DID id.    (0x4269 for example)\n\n    0x");
    fflush(stdout);
    // Get requested DID number.
    DIDnumber = (uint16_t)demo_DIDNumberInputAndHexCheck();
    // Send data to server.
    UDS_DT_readScalingDataByIdentifier(DIDnumber,printDemoMessage);
    uds_demoWait();

    // Communicate with user based on response
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 0x64)
    {
        printf("0x64 = Positive response\n");
        printf("0x%02x = Requested dataIdentifier high byte (DID Number)\n", serverResponse[1]);
        printf("0x%02x = Requested dataIdentifier low byte  (DID Number)\n", serverResponse[2]);
        printf("0x%02x = scalingByte\n", serverResponse[3]);

        printf("DID scalingByteExtensionParameter:\n");
        for (uint32_t i = 4; i < serverResponseLength; i++)
        {
            printf("0x%02x ", serverResponse[i]);
        }
        printf("\n\n");

        PRINT_CENTERED("Press ENTER to Try another DID   ///   [B] return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        input = getchar();
        if (input == 'b' || input == 'B')
        {
            demo_DID();
        }
        else
        {
            demo_SID_0X24_ReadScalingDataByIdentifier();
        }
    }
    else
    {
        printf("\n\n");
        PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
        PRINT_CENTERED("Press ENTER to Try another DID   ///   [B] to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        input = getchar();
        if (input == 'b' || input == 'B')
        {
            demo_DID();
        }
        else
        {
            demo_SID_0X24_ReadScalingDataByIdentifier();
        }
    }
}

static void demo_SID_0X2A_ReadDataByPeriodicIdentifier (void)
{
    uint8_t transmissionMode = 0x00;
    uint8_t periodicDataIdentifiers[1] = {0x00};
    uint8_t input = 0x00;
    uint8_t length = 0x01;
    bool whileBreaker = true;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // ReadDataByPeriodicIdentifier.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0x2A: ReadDataByPeriodicIdentifier.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");


    while (whileBreaker)
    {
        printf("    Choose your wanted sending rate. \n\n");

        printf("    [1]    =   sendSlowRate\n\n");

        printf("    [2]    =   sendMediumRate\n\n");

        printf("    [3]    =   sendFastRate\n\n");

        fflush(stdout);

        // Get input.
        fflush(stdin);
        input = getchar();

        switch (input)
        {
        case '1':
            transmissionMode = 0x01;
            whileBreaker = false;
            printf("You choose 0x01\n\n");
            fflush(stdout);
            break;

        case '2':
            transmissionMode = 0x02;
            whileBreaker = false;
            printf("You choose 0x02\n\n");
            fflush(stdout);
            break;

        case '3':
            transmissionMode = 0x03;
            whileBreaker = false;
            printf("You choose 0x03\n\n");
            fflush(stdout);
            break;
        
        default:
            demo_defaultInputFailed();
            break;
        }
    }
    whileBreaker = true;

    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("Next the periodicDataIdentifier a range of 0xF200 - 0xF2FF is reserved for this purpose. 0xF202 - 0xF204 are prepared ");
    PRINT_CENTERED("0xF201 - 0xF203 are prepared for this demo.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");


    while (whileBreaker)
    {
        printf("    Choose your wanted periodicDataIdentifier. \n\n");

        printf("    [1]    =   0xF269\n\n");

        printf("    [2]    =   0xF242\n\n");

        printf("    [3]    =   0xF203\n\n");

        fflush(stdout);

        // Get input.
        fflush(stdin);
        input = getchar();

        switch (input)
        {
        case '1':
            periodicDataIdentifiers[0] = 0x69;
            whileBreaker = false;
            printf("You choose 0xF269\n\n");
            fflush(stdout);
            break;

        case '2':
            periodicDataIdentifiers[0] = 0x42;
            whileBreaker = false;
            printf("You choose 0xF242\n\n");
            fflush(stdout);
            break;

        case '3':
            periodicDataIdentifiers[0] = 0x03;
            whileBreaker = false;
            printf("You choose 0xF203\n\n");
            fflush(stdout);
            break;
        
        default:
            demo_defaultInputFailed();
            break;
        }
    }

    // Quick session change.
    UDS_DCM_DiagnosticSessionControl(UDS_Session_Extended, printDemoMessage);
    uds_demoWait();
    PRINT_CENTERED("^--- Server needs to be in SESSION_EXTENDED or SESSION_SECURED, this ist automated in the demo.");
    printf("\n");

    // Send data to server.
    UDS_DT_ReadDataByPeriodicIdentifier(transmissionMode,periodicDataIdentifiers,length,printDemoMessage,printDemoMessage);
    uds_demoWait();

    bool oneWayTicket = true;
    uint16_t counter = 0x00;
    for (uint32_t u = 0; counter < 1; u++)
    {
        if (oneWayTicket)
        {
            // Communicate with user based on response
            printf("\n\n");
            PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
            if (serverResponse[0] == 0x6A)
            {
                printf("0x6A = Positive response\n");

                printf("Server will now send periodically requested data until revoked.)\n");
                printf("for demo purpose this will be automatically cancelled after the first cycle.)\n");

                fflush(stdout);
                printDemoMessage(0,0,0);
                uds_demoWait();
                oneWayTicket = false;
            }
            else
            {
                printf("\n\n");
                PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
                PRINT_CENTERED("Press ENTER to return to the DID selection.");
                fflush(stdout);
                fflush(stdin);
                getchar();
                demo_DID();
            }
        }
        
        if (serverResponse[0] == periodicDataIdentifiers[0])
        {
            // Communicate with user based on response
            printf("\n\n");
            PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
            printf("0x%2x = requested periodicDataIdentifier\n",periodicDataIdentifiers[0]);

            printf("DID payload:\n");
            for (uint32_t i = 1; i < serverResponseLength; i++)
            {
                printf("0x%02x ", serverResponse[i]);
            }
            printf("\n\n");
            
            fflush(stdout);
            counter++;
        }
    }

    UDS_DT_stopDataByPeriodicIdentifier(periodicDataIdentifiers,length,printDemoMessage);
    uds_demoWait();
    PRINT_CENTERED("Data is now send and periodic sending will be terminated");
    printf("\n\n");
    PRINT_CENTERED("Press ENTER to Try another DID   ///   [B] return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    input = getchar();
    if (input == 'b' || input == 'B')
    {
        demo_DID();
    }
    else
    {
        demo_SID_0X2A_ReadDataByPeriodicIdentifier();
    }

}

static void demo_SID_0X2C_DynamicallyDefineDataIdentifier (void)
{
    uint8_t input = 0;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // DynamicallyDefineDataIdentifier.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0X2C: DynamicallyDefineDataIdentifier.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");

    printf("    Choose your wanted subfunction. \n\n\n");


    printf("    [1]    =   DefineByIdentifier\n\n\n");


    printf("    [2]    =   DefineByMemoryAddress\n\n\n");


    printf("    [3]    =   ClearDynamicalDefinedDID\n\n\n");


    printf("    [B]    =   Return to DID demo\n\n\n");


    fflush(stdout);


    // Get input.
    fflush(stdin);
    input = getchar();
    
    switch (input)
    {
    case '1':
        printf("    You choose: 0x01 DefineByIdentifier");
        fflush(stdout);
        demo_SID_0X2C_SUB_0X01_DefineByIdentifier();
        break;
    
    case '2':
        printf("    You choose: 0x02 DefineByMemoryAddress");
        fflush(stdout);
        demo_SID_0X2C_SUB_0X02_DefineByMemoryAddress();
        break;

    case '3':
        printf("    You choose: 0x03 ClearDynamicalDefinedDID");
        fflush(stdout);
        demo_SID_0X2C_SUB_0X03_ClearDynamicalDefinedDID();
        break;

    case 'B':
    case 'b':
        demo_DID();
        break;

    default:
        demo_defaultInputFailed();
        demo_SID_0X2C_DynamicallyDefineDataIdentifier();
        break;
    }
}

static void demo_SID_0X2C_SUB_0X01_DefineByIdentifier (void)
{
    uint8_t input = 0x00;
    uint8_t highByteDefiner = 0x00;
    uint8_t lowByteDefiner = 0x00;
    uint16_t newDID = 0x00;
    DataDefinition dataDef[3];
    uint8_t amountOfDID = 0x00;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // DefineByIdentifier.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0X2C - SUB 0X01: DefineByIdentifier.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");

    printf("    Whit this function its possible to define a new DID, it takes some understanding of this matter. \n");
    printf("    It is possible to build a DID chain to get pre defined data packages.\n\n");
    
    printf("    First how many DID do you want to pack into one call?\n");
    printf("    (For demo purpose only: max 3 are allowed, normally 20 Byte are currently reserved.)\n\n\n");
    fflush(stdout);

    printf("    [1]  =  1 source DID into new defined DID.\n\n\n");


    printf("    [2]  =  2 source DID into new defined DID.\n\n\n");


    printf("    [3]  =  3 source DID into new defined DID.\n\n\n");


    printf("    [B]  =  Back to SID 0x2C selection\n\n\n");


    // Get high byte for new DID.
    fflush(stdin);
    input = getchar();
    switch (input)
    {
    case '1':
        printf("   You choose: 1 source DID\n\n\n\n");
        amountOfDID = 0x01;
        fflush(stdout);
        break;

    case '2':
        printf("   You choose: 2 source DID\n\n\n\n");
        amountOfDID = 0x02;
        fflush(stdout);
        break;

    case '3':
        printf("   You choose: 3 source DID\n\n\n\n");
        amountOfDID = 0x03;
        fflush(stdout);
        break;

    case 'B':
    case 'b':
        demo_SID_0X2C_DynamicallyDefineDataIdentifier();
        break;

    default:
        demo_defaultInputFailed();
        demo_SID_0X2C_SUB_0X01_DefineByIdentifier();
        break;
    }
    input = 0x00; // rest data

    printf("    Choose your high byte identifier for your new DID. \n\n\n");

    printf("    [1]    =   0xF2  -  Default for periodic Data Identifier but can be used for dynamically as well.\n\n\n");

    printf("    [2]    =   0xF3  -  Default for Dynamically Defined Data Identifier. \n\n\n");

    printf("    [B]    =   Back to SID 0x2C selection\n\n\n");
    fflush(stdout);


    // Get high byte for new DID.
    fflush(stdin);
    input = getchar();
    switch (input)
    {
    case '1':
        printf("   You choose: 0xF2 as High Byte identifier\n\n\n\n");
        highByteDefiner = 0xF2;
        fflush(stdout);
        break;

    case '2':
        printf("    You choose: 0xF3 as High Byte identifier\n\n\n\n");
        highByteDefiner = 0xF3;
        fflush(stdout);
        break;

    case 'B':
    case 'b':
        demo_SID_0X2C_DynamicallyDefineDataIdentifier();
        break;

    default:
        demo_defaultInputFailed();
        demo_SID_0X2C_SUB_0X01_DefineByIdentifier();
        break;
    }

    // Get low byte for new DID.
    printf("    Choose your low byte identifier for your new DID.    (0x00 - 0xFF) \n\n");
    printf("0x");
    fflush(stdout);

    lowByteDefiner = demo_get8bitHex();
    newDID = (highByteDefiner << 8 | lowByteDefiner);   // first argument of function call.


    for (uint8_t i = 0; i < amountOfDID; i++)
    {
        // Get source DID for new DID.
        printf("\n\n    Now define the source data DID.  (currently used: 0x4269, 0x6942, 0xF269, 0xF242, 0xF301)\n");
        printf("    It is possible to not hit a pre defined DID and the function will not work.\n\n");
        fflush(stdout);

        dataDef[i].DID = (uint16_t)demo_DIDNumberInputAndHexCheck();

        switch ((uint16_t)dataDef[i].DID)
        {
        case 0x4269:
            dataDef[i].firstBytePosition = 0x01;
            dataDef[i].memorySize = 0x04;
            break;
        
        case 0x6942:
            dataDef[i].firstBytePosition = 0x02;
            dataDef[i].memorySize = 0x04;
            break;

        case 0xF269:
            dataDef[i].firstBytePosition = 0x03;
            dataDef[i].memorySize = 0x04;
            break;

        case 0xF242:
            dataDef[i].firstBytePosition = 0x04;
            dataDef[i].memorySize = 0x04;
            break;

        case 0xF301:
            dataDef[i].firstBytePosition = 0x05;
            dataDef[i].memorySize = 0x04;
            break;        

        default:
            PRINT_CENTERED("DID not found, try again.");
            i--;
            break;
        }
    }
    
    PRINT_CENTERED("Data will be send to server now");
    UDS_DT_dynamicallyDefineDataIdentifierByDID(newDID,dataDef,amountOfDID,printDemoMessage);
    uds_demoWait();

    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 0x6C)
    {
        printf("0x6C = Positive response\n");
        printf("0x%02x = New defined DID high byte.\n", serverResponse[1]);
        printf("0x%02x = New defined DID low byte.\n\n", serverResponse[2]);

        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_SID_0X2C_DynamicallyDefineDataIdentifier();
    }
    else
    {
    PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
    PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
    fflush(stdout);
    fflush(stdin);
    getchar();
    demo_SID_0X2C_DynamicallyDefineDataIdentifier();
    }
}

static void demo_SID_0X2C_SUB_0X02_DefineByMemoryAddress (void)
{
    demo_currentlyNotSupported();
    demo_DID();

    /* not done ... @todo demo needs to be finished
    uint8_t input = 0;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // DefineByMemoryAddress.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0X2C - SUB 0X02: DefineByMemoryAddress.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");






    fflush(stdout);


    // Get input.
    fflush(stdin);
    input = getchar();

    //UDS_DT_dynamicallyDefineDataIdentifierByMemoryDefinition();
    */
}

static void demo_SID_0X2C_SUB_0X03_ClearDynamicalDefinedDID (void)
{
    demo_currentlyNotSupported();
    demo_DID();

    /* not done ... @todo demo needs to be finished



    uint8_t input = 0;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // ClearDynamicalDefinedDID.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0X2C - SUB 0X03: ClearDynamicalDefinedDID.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");





    fflush(stdout);


    // Get input.
    fflush(stdin);
    input = getchar();

    //UDS_DT_clearDynamicallyDefineDataIdentifier();
 */
}

static void demo_SID_0X2E_WriteDataByIdentifier (void)
{
    demo_currentlyNotSupported();
    demo_DID();
}

static void demo_SID_0X3D_WriteMemoryByAddress (void)
{
    MemoryDefinition memDef;
    uint8_t address[3] = {0x10,0x00,0x00};

    demo_clearTerminal();
    demo_getCurrentTerminalSize();

    // WriteMemoryByAddress.
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0x3D: WriteMemoryByAddress.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");
    printf("      Due to complexity of this request,    (user needs to know exact size and other perimeter)\n");
    printf("      subfunction will be pre defined and runs automatic. \n\n\n");

    memcpy(memDef.Address,address,3);
    printf("      memoryAddress =  0x10 0x00 0x00\n\n");
    *(memDef.Size) = 0x0A;
    printf("      memorySize    =  0x0A\n\n");
    memDef.AddressLength = 0x03; // 3 Byte
    printf("      addressAndLengthFormatIdentifier    =  0x03\n");
    printf("      Low nibble of the identifier\n\n");
    memDef.SizeLength = 0x01; // 1 Byte
    printf("      addressAndLengthFormatIdentifier    =  0x10\n");
    printf("      High nibble of the identifier\n\n");

    // Send data to server.
    UDS_DT_readMemoryByAddress(memDef,printDemoMessage);
    uds_demoWait();

    // Communicate with user based on response
    printf("\n\n");
    PRINT_CENTERED("Charon SERVER send a response to the CLIENT:");
    if (serverResponse[0] == 0x63)
    {
        printf("0x63 = Positive response\n");

        printf("DID payload:\n");
        for (uint32_t i = 1; i < serverResponseLength; i++)
        {
            printf("0x%02x ", serverResponse[i]);
        }
        printf("\n\n");

        PRINT_CENTERED("Press ENTER to return to the subfunction selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_DID();
    }
    else
    {
        printf("\n\n");
        PRINT_CENTERED("!!! Charon SERVER send a error try again !!!");
        PRINT_CENTERED("Press ENTER to return to the DID selection.");
        fflush(stdout);
        fflush(stdin);
        getchar();
        demo_DID();
    }
}


//#############################################################################
//#     Diagnostic area
//#############################################################################
static void demo_SID_0X85_DTC (void)
{
    uint8_t input;

    demo_clearTerminal();
    demo_getCurrentTerminalSize();
    
    demo_printCharonDemoLogo();
    demo_printUnderscoreLine_noFlush();
    printf("\n");
    PRINT_CENTERED("SID 0x85: ControlDTCSetting.");
    demo_printUnderscoreLine_noFlush();
    printf("\n\n");

    printf("    Turn DTC update function ON or OFF for a single requested DTC\n\n\n");


    printf("        0x0[2]  =  ON \n\n\n");


    printf("        0x0[3]  =  OFF \n\n\n");


    printf("           [B]  =  Back to demo selection \n\n\n");
    fflush(stdout);


    // get input
    fflush(stdin);
    input = getchar();
    switch (input)
    {
    case '2':
        printf("\n");
        PRINT_CENTERED("Your input: 0x02 turn ON update.");
        printf("\n\n");
        PRINT_CENTERED("Next TYPE your requested DTC to change. (0x004400 is currently the first saved as suggestion)");
        printf("\n\n");
        demo_SID_0x85_DTC_controlling(2);
        break;


    case '3':
        printf("\n");
        PRINT_CENTERED("Your input: 0x03 turn OFF update.");
        printf("\n\n");
        PRINT_CENTERED("Next TYPE your requested DTC to change. (0x004400 is currently the first saved as suggestion)");
        printf("\n\n");
        demo_SID_0x85_DTC_controlling(3);
        break;


    case 'B':
        demo_clearTerminal();
        demo_DTC();
        break;
    case 'b':
        demo_clearTerminal();
        demo_DTC();
        break;


    default:
        // Input not valid try again.
        demo_defaultInputFailed();
        demo_SID_0X85_DTC();
        break;
    }  
}

static void demo_SID_0x85_DTC_controlling (uint8_t ONorOFF)
{
    uint32_t DTCNumberFromUserInput = demo_DTCNumberInputAndHexCheck();
    uint8_t highByte = 0;
    uint8_t midByte = 0;
    uint8_t lowByte = 0;

    highByte = (DTCNumberFromUserInput >> 16);
    midByte = (DTCNumberFromUserInput >> 8);
    lowByte = (DTCNumberFromUserInput >> 0);



    // Quick session change.
    UDS_DCM_DiagnosticSessionControl(UDS_Session_Extended, printDemoMessage);
    uds_demoWait();
    PRINT_CENTERED("^--- Server needs to be in SESSION_EXTENDED or SESSION_SECURED, this ist automated in the demo.");
    printf("\n");

    // First uin8_t in array is for on/ff  0x01 = ON / 0x02 = OFF
    UDS_DCM_ControlDTCSetting(ONorOFF, (uint8_t[]){highByte, midByte, lowByte}, 3, printDemoMessage);
    uds_demoWait();

    if (serverResponseLength == 2)
    {
        PRINT_CENTERED("^--- DTC setting is now changed and SERVER send a Positive response (0xc5) to the CLIENT");
        PRINT_CENTERED("+ an echo of the requested change.");
        printf("\n\n");
    } 
    else
    {
        PRINT_CENTERED("Change failed try again...");
        printf("\n\n");
    }
    

    PRINT_CENTERED("------------------------");
    PRINT_CENTERED("press ENTER to return.");
    PRINT_CENTERED("------------------------");
    fflush(stdout);


    fflush(stdin);
    getchar();
    demo_clearTerminal();
    demo_SID_0X85_DTC();
}



// backup
/*
  _______ _____   ___  ____  _  __    ___  ______  _______ 
 / ___/ // / _ | / _ \/ __ \/ |/ /   / _ \/ __/  |/  / __ \
/ /__/ _  / __ |/ , _/ /_/ /    /   / // / _// /|_/ / /_/ /
\___/_//_/_/ |_/_/|_|\____/_/|_/   /____/___/_/  /_/\____/ 
*/

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
