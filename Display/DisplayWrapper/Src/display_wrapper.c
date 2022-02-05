// Display Wrapper

#include "display_wrapper.h"
#include "config.h"

/**
 * This display wrapper makes the initialization and some
 * draw functions easier to use.
 * 
 * Other draw functionality can be found in GUI_Paint.h/GUI_Paint.c
 */

/** Display Coordinates : (x,y)
 * ┌────────────────────────────────────────┐
 * │(0,0)                            (264,0)│
 * │                                        │
 * │                                        │
 * │                                        │
 * │                                        │
 * │                                        │
 * │                                        │
 * │(0,176)                        (264,176)│
 * └────────────────────────────────────────┘
 */

/**
 * The display has a buffer storing the value of every pixel.
 * Draw functions change this buffer and Display_Update() puts
 * the buffer on the screen.
 */
UBYTE image_buffer[EPD_2IN7_WIDTH * EPD_2IN7_HEIGHT / 8];

char out_string_buffer[EPD_2IN7_WIDTH / 5]; // 5 is width of narrowest font

/** Display Init
 * @brief 
 * Initializes the display signals and display buffer
 */
void Display_Init() {
    /* initialize the display module */
    DEV_Module_Init();
    EPD_2IN7_Init();
    EPD_2IN7_Clear();
    DEV_Delay_ms(500);

    /* initialize the buffer to blank */
    Paint_NewImage(image_buffer, EPD_2IN7_WIDTH, EPD_2IN7_HEIGHT, 270, WHITE);
    Paint_SelectImage(image_buffer);
    Paint_Clear(WHITE);
}


/** Display Update
 * @brief 
 * Update the display with the contents of the display buffer
 */
void Display_Update() {
    EPD_2IN7_Display(image_buffer);
}


/** Display Clear
 * @brief 
 * Clear the image in the buffer and on the actual display
 */
void Display_Clear() {
    Paint_Clear(WHITE);
    EPD_2IN7_Clear();
}


/** Draw String
 * @brief 
 * Draw a string on the image buffer
 * (Does not update the display)
 * 
 * If nothing is drawing, the start coordinates are out of bounds
 * If the string is too long to display, extra characters will wrap around
 * 
 * @param text The string to display
 * @param fontsize Size of text
 * @param xcoord x-coordinate of bottom left of text
 * @param ycoord y-coordinate of bottom left of text
 */
void Display_DrawString(const char* text, sFONT* fontsize, 
                        UWORD xcoord, UWORD ycoord) {
    Paint_DrawString_EN(xcoord, ycoord, text, fontsize, WHITE, BLACK);
}

/** Draw Decimal
 * @brief 
 * Draw a decimal number on the image buffer
 * 
 * @param num The number to display
 * @param fontsize Size of text
 * @param xcoord x-coordinate of bottom left of number
 * @param ycoord y-coordinate of bottom left of number
 */
void Display_DrawDec(int32_t num, sFONT* fontsize,
                        UWORD xcoord, UWORD ycoord) {
    Paint_DrawNum(xcoord, ycoord, num, fontsize, WHITE, BLACK);
}

/** Draw CAN Message
 * @brief 
 * Draw a formatted CAN message
 * 
 * @param canmessage Pointer to single CAN message or array of CAN messages
 *                   if data spans multiple messages.
 *                   Array of CAN messages must be ordered by the payload idx
 * @param xcoord x-coordinate of bottom left of message
 * @param ycoord y-coordinate of bottom left of message
 */
HAL_StatusTypeDef Display_DrawCANMessage(CANMSG_t *canmessage, sFONT* fontsize,
                        UWORD xcoord, UWORD ycoord) {
    uint8_t array_size = 0;
    switch (canmessage->id) {
        // Handle messages with one byte of data
        case TRIP:
        case ALL_CLEAR:
        case CONTACTOR_STATE:
        case WDOG_TRIGGERED:
        case CAN_ERROR:
        case CHARGE_ENABLE: ;
            uint8_t data_byte = canmessage->payload.data.b;
            Display_DrawDec(data_byte, fontsize, xcoord, ycoord);
            break;

        // Handle messages with 4 byte data
        case CURRENT_DATA:
        case SOC_DATA: ;
            uint32_t data_word = canmessage->payload.data.w;
            Display_DrawDec(data_word, fontsize, xcoord, ycoord);
            break;

        // Handle messages with idx + 4 byte data
        case VOLT_DATA:
            array_size = NUM_BATTERY_MODULES;
        case TEMP_DATA:
            // set to temperature sensors only if it hasn't been set above
            if (array_size == 0) {
                array_size = NUM_TEMPERATURE_SENSORS;
            }

            // find max and min of data
            uint32_t max = 0;
            uint32_t min = UINT32_MAX;
            for (uint8_t i = 0; i < array_size; i++) {
                if (i != canmessage[i].payload.idx) {
                    return HAL_ERROR;
                }
                uint32_t data = canmessage[i].payload.data.w;
                if (data > max) {
                    max = data;
                }
                if (data < min) {
                    min = data;
                }
            }

            // print out messages
            sprintf(out_string_buffer, "MIN: %lu", min);
            Display_DrawString(out_string_buffer, fontsize, xcoord, ycoord);
            sprintf(out_string_buffer, "MAX: %lu", max);
            Display_DrawString(out_string_buffer, fontsize,
                    xcoord, ycoord + fontsize->Height);

            break;
        default :
            return HAL_ERROR;
    }

    return HAL_OK;
}


