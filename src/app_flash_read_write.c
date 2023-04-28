/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_flash_read_write.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app_flash_read_write.h"
#include "config/default/definitions.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_FLASH_READ_WRITE_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_FLASH_READ_WRITE_DATA app_flash_read_writeData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************
// Define a constant array in Flash.
// It must be aligned to block boundary and size has to be in multiple of blocks
const uint8_t nvm_user_start_address[NVMCTRL_FLASH_BLOCKSIZE] __attribute__((aligned(NVMCTRL_FLASH_BLOCKSIZE),keep,externally_visible,space(prog)))= {0};

void populate_buffer(uint8_t* data)
{
    int i = 0;

    for (i = 0; i < (NVMCTRL_FLASH_PAGESIZE); i++)
    {
        *(data + i) = i;
    }
}
/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_FLASH_READ_WRITE_Initialize ( void )

  Remarks:
    See prototype in app_flash_read_write.h.
 */

void APP_FLASH_READ_WRITE_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_flash_read_writeData.state = APP_FLASH_READ_WRITE_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_FLASH_READ_WRITE_Tasks ( void )

  Remarks:
    See prototype in app_flash_read_write.h.
 */

void APP_FLASH_READ_WRITE_Tasks ( void )
{
    uint8_t data [NVMCTRL_FLASH_PAGESIZE] = {0};
    /* Check the application's current state. */
    switch ( app_flash_read_writeData.state )
    {
        /* Application's initial state. */
        case APP_FLASH_READ_WRITE_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {
                LED_OFF();
               /*Populate random data to programmed*/
               populate_buffer(data);

               while(NVMCTRL_IsBusy());

               /* Erase the block */
               NVMCTRL_BlockErase((uint32_t)nvm_user_start_address);

               while(NVMCTRL_IsBusy());

               /* Program 512 byte page */
               NVMCTRL_PageWrite((uint32_t *)data, (uint32_t)nvm_user_start_address);

               while(NVMCTRL_IsBusy());

               /* Verify the programmed content*/
               if (!memcmp(data, (void *)nvm_user_start_address, NVMCTRL_FLASH_PAGESIZE))
               {
                   LED_ON();
               }
                app_flash_read_writeData.state = APP_FLASH_READ_WRITE_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_FLASH_READ_WRITE_STATE_SERVICE_TASKS:
        {

            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
