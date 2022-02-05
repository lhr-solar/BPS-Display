// Display Wrapper

#include "display_wrapper.h"

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




