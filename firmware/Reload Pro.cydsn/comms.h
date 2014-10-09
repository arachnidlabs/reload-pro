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
#ifndef COMMS_H
#define COMMS_H

#define MAX_RESPONSE_LENGTH 32

// Use this function for "printf" style debugging
// under the hood it uses vsnprintf to format output string
// You must add your own \r\n
// maximum length of string that can be output is MAX_RESPONSE_LENGTH
    
void uart_printf(char *fmt, ...);

#endif
/* [] END OF FILE */
