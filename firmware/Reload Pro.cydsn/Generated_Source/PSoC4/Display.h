/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <CyLib.h>

void Display_Start();
void Display_WritePixels(uint8 data[], int len);
void Display_SetCursorPosition(uint8 page, uint8 col);
void Display_SetContrast(uint8 contrast_level);
void Display_DrawText(uint8 start_page, uint8 start_col, const char *text, uint8 inverse);
void Display_DrawBigNumbers(uint8 start_page, uint8 start_col, const char *nums);
void Display_ClearAll();
void Display_Clear(uint8 start_row, uint8 start_col, uint8 end_row, uint8 end_col);

/* [] END OF FILE */
