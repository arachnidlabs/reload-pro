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
#include <project.h>

void CyBtldrCommStart(void) {
	UART_Start();
}

void CyBtldrCommStop (void) {
	UART_Stop();
}

void CyBtldrCommReset(void) {
	UART_SpiUartClearRxBuffer();
	UART_SpiUartClearTxBuffer();
}

cystatus CyBtldrCommWrite(uint8* buffer, uint16 size, uint16* count, uint8 timeOut) {
	for(*count = 0; *count < size; (*count)++) {
		UART_UartPutChar(buffer[*count]);
	}
	
	return CYRET_SUCCESS;
}

cystatus CyBtldrCommRead (uint8* buffer, uint16 size, uint16* count, uint8 timeOut) {
	int timeoutUs = timeOut * 10000;
	cystatus status = CYRET_TIMEOUT;
	
	*count = 0;
	while(*count < size && timeoutUs >= 0) {
		if(UART_SpiUartGetRxBufferSize() > 0) {
			buffer[(*count)++] = UART_UartGetByte();
			// Switch to byte-to-byte timeout and mark as success
			timeoutUs = 10000; //10mS
			status = CYRET_SUCCESS;
		} else {
			CyDelayUs(10);
			timeoutUs -= 10;
		}
	}
	
	return status;
}

void main()
{
	int i;
	
	if(Bootloader_GET_RUN_TYPE == Bootloader_START_BTLDR)
		Bootloader_Start();
	
    for(i = 0; i < 2000; i++) {
        uint8 status = Button_Read();
        if(status)
            break;
        CyDelay(1);
    }
    
    if(i == 2000) {
        // Time expired, start bootloader
		Bootloader_SET_RUN_TYPE(Bootloader_START_BTLDR);
    } else {
        // Button released, reset
		Bootloader_SET_RUN_TYPE(Bootloader_START_APP);
    }
    Bootloader_Start();
}

/* [] END OF FILE */
