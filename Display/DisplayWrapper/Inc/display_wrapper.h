#ifndef DISPLAY_WRAPPER_H
#define DISPLAY_WRAPPER_H

// Wrapper for e-Paper display drivers

#include "EPD_2in7.h"
#include "GUI_Paint.h"

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


#endif /* DISPLAY_WRAPPER_H */