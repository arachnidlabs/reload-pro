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

void `$INSTANCE_NAME`_Start();
void `$INSTANCE_NAME`_WritePixels(uint8 data[], int len);
void `$INSTANCE_NAME`_SetCursorPosition(uint8 page, uint8 col);
void `$INSTANCE_NAME`_SetContrast(uint8 contrast_level);
void `$INSTANCE_NAME`_DrawText(uint8 start_page, uint8 start_col, const char *text, uint8 inverse);
void `$INSTANCE_NAME`_DrawBigNumbers(uint8 start_page, uint8 start_col, const char *nums);
void `$INSTANCE_NAME`_ClearAll();
void `$INSTANCE_NAME`_Clear(uint8 start_row, uint8 start_col, uint8 end_row, uint8 end_col);

/* [] END OF FILE */
