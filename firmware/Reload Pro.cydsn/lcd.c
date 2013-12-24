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

char display_buffer[4][13];

void vTaskLCD(void *pvParameters) {
	while(1) {
		display_buffer[0][0]++;
	}
}

/* [] END OF FILE */
