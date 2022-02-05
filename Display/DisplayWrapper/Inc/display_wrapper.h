#ifndef DISPLAY_WRAPPER_H
#define DISPLAY_WRAPPER_H

// Wrapper for e-Paper display drivers

#include "EPD_2in7.h"
#include "GUI_Paint.h"
#include "CANBus.h"
#include "stm32f4xx.h"

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

/* Font size selection */
#define FONT8 &Font8
#define FONT12 &Font12
#define FONT16 &Font16
#define FONT20 &Font20
#define FONT24 &Font24

/** Display Init
 * @brief 
 * Initializes the display signals and display buffer
 */
void Display_Init();


/** Display Update
 * @brief 
 * Update the display with the contents of the display buffer
 */
void Display_Update();


/** Display Clear
 * @brief 
 * Clear the image on the actual display
 */
void Display_Clear();


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
                        UWORD xcoord, UWORD ycoord);


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
                        UWORD xcoord, UWORD ycoord);


/** Draw CAN Message
 * @brief 
 * Draw a formatted CAN message
 * 
 * @param canmessage pointer to single CAN message or array of CAN messages
 *                   if data spans multiple messages
 * @param xcoord x-coordinate of bottom left of message
 * @param ycoord y-coordinate of bottom left of message
 */
HAL_StatusTypeDef Display_DrawCANMessage(CANMSG_t *canmessage, sFONT* fontsize,
                        UWORD xcoord, UWORD ycoord);
#endif /* DISPLAY_WRAPPER_H */