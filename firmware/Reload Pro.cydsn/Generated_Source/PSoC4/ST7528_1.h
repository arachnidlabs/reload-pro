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

void ST7528_1_Start();
void ST7528_1_WritePixels(uint8 data[], uint8 len);
void ST7528_1_SetCursorPosition(uint8 page, uint8 col);
void ST7528_1_SetContrast(uint8 contrast_level);
void ST7528_1_DrawText(uint8 start_page, uint8 start_col, char *text);
void ST7528_1_DrawBigNumbers(uint8 start_page, uint8 start_col, char *nums);
void ST7528_1_ClearAll();
void ST7528_1_Clear(uint8 start_row, uint8 start_col, uint8 end_row, uint8 end_col);

/* [] END OF FILE */
