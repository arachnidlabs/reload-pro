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
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_font.h"
#include "`$INSTANCE_NAME`_SPI.h"
#include "`$INSTANCE_NAME`_SS_Reg.h"
#include <stdbool.h>
#include <CyLib.h>

#define COMMAND_SET_MODE			0x38
#define COMMAND_WRITE_DATA 			0xE8
#define COMMAND_SET_PAGE 			0xB0
#define COMMAND_SET_COLUMN_MSB		0x10
#define COMMAND_SET_COLUMN_LSB		0x00
#define COMMAND_DISPLAY_ON			0xAE
#define COMMAND_POWER_CONTROL		0x28
#define COMMAND_SELECT_STEPUP		0x64
#define COMMAND_SELECT_REGULATOR	0x20
#define COMMAND_SET_CONTRAST		0x81
#define COMMAND_SET_BIAS			0x50
#define COMMAND_OSCILLATOR_ON		0xAB
#define COMMAND_SET_PARTIAL_DISPLAY 0x48
#define COMMAND_SET_COM0			0x44
#define COMMAND_SELECT_ADC_NORMAL	0xA0
#define COMMAND_SET_COM_SCAN_DIR_REVERSE 0xC8
#define COMMAND_EXT_SET_GRAY_LEVEL	0x80

#define MODE_NORMAL					0x64
#define MODE_EXT					0x65

#define DEFAULT_STEPUP				0x2
#define DEFAULT_LCD_BIAS			0x4
#define DEFAULT_REGULATOR_RESISTOR	0x6
#define DEFAULT_CONTRAST_LEVEL		0x0B
#define DEFAULT_COM0				0x12

static void begin_transaction() {
	`$INSTANCE_NAME``[SS_Reg]`Write(0);
}

static void end_transaction() {
	`$INSTANCE_NAME``[SS_Reg]`Write(1);
}
static void send_commands(uint8 commands[], int len) {
	begin_transaction();
	`$INSTANCE_NAME``[SPI]`PutArray(commands, len);
	end_transaction();
}

static void configure_grays() {
	send_commands((uint8[]) {
		COMMAND_SET_MODE, MODE_EXT,
	}, 2);
	for(int i = 0; i < 64; i += 4) {
		uint8 gray = (i * 0x2D) / 60;
		send_commands((uint8[]) {
			COMMAND_EXT_SET_GRAY_LEVEL | i,
			gray,
			COMMAND_EXT_SET_GRAY_LEVEL | (i + 1),
			gray,
			COMMAND_EXT_SET_GRAY_LEVEL | (i + 2),
			gray,
			COMMAND_EXT_SET_GRAY_LEVEL | (i + 3),
			gray
		}, 8);
	}
	send_commands((uint8[]) {
		COMMAND_SET_MODE, MODE_NORMAL
	}, 2);
}

static void display_setup() {
	send_commands((uint8[]) {
		COMMAND_SET_MODE, MODE_NORMAL, // 68Hz frequency, booster efficiency 2, standard commands
		COMMAND_OSCILLATOR_ON,
		COMMAND_SET_COM0, DEFAULT_COM0,
		COMMAND_SELECT_ADC_NORMAL,
		COMMAND_SET_COM_SCAN_DIR_REVERSE,
		COMMAND_SELECT_STEPUP | DEFAULT_STEPUP, // 5 x boost
		COMMAND_SET_BIAS | DEFAULT_LCD_BIAS, // 1/9 bias
		COMMAND_SET_PARTIAL_DISPLAY, 64, // Only use the first 64 lines
		COMMAND_SELECT_REGULATOR | DEFAULT_REGULATOR_RESISTOR,
		COMMAND_POWER_CONTROL | 0xC, // VC on
	}, 13);

	`$INSTANCE_NAME`_SetContrast(DEFAULT_CONTRAST_LEVEL);
	
	configure_grays();

	CyDelay(200);
	send_commands((uint8[]) {
		COMMAND_POWER_CONTROL | 0xE, // VC, VR on
	}, 1);
	
	CyDelay(200);
	send_commands((uint8[]) {
		COMMAND_POWER_CONTROL | 0xF, // VC, VR, VF on
		COMMAND_DISPLAY_ON | 1, // Display on
	}, 2);
}

void `$INSTANCE_NAME`_Start() {
	`$INSTANCE_NAME``[SPI]`Start();
	display_setup();
}

void write_pixels_begin(uint8 len) {
	begin_transaction();
	`$INSTANCE_NAME``[SPI]`PutArray((uint8[]){COMMAND_WRITE_DATA, len - 1}, 2);
}

void write_pixels_end() {
	end_transaction();
}

void `$INSTANCE_NAME`_WritePixels(uint8 data[], int len) {
	for(int i = 0; i < len; i += 255) {
		int write_size = len - i;
		if(write_size > 255)
			write_size = 255;
		write_pixels_begin((uint8)write_size);
		`$INSTANCE_NAME``[SPI]`PutArray(data + i, (uint8)write_size);
		write_pixels_end();
	}
}

void `$INSTANCE_NAME`_SetCursorPosition(uint8 page, uint8 col) {
	send_commands((uint8[]) {
		COMMAND_SET_PAGE | (page & 0xF),
		COMMAND_SET_COLUMN_MSB | ((col >> 4) & 0xF),
		COMMAND_SET_COLUMN_LSB | (col & 0xF)
	}, 3);
}

void `$INSTANCE_NAME`_SetContrast(uint8 contrast_level) {
	send_commands((uint8[]) {
		COMMAND_SET_CONTRAST, contrast_level & 0x3F
	}, 2);
}

static void draw_text_slice(char c, uint8 row, uint8 inverse) {
	write_pixels_begin(FONT_GLYPH_COLUMNS * 4);
	for(int8 i = 0; i < FONT_GLYPH_COLUMNS; i++) {
		char col = glyphs[c - FONT_GLYPH_OFFSET][row][i];
		if(inverse)
			col = ~col;
		uint8 pixels[4] = {col, col, col, col};
		`$INSTANCE_NAME``[SPI]`PutArray(pixels, 4);
	}
	write_pixels_end();
}

void `$INSTANCE_NAME`_Clear(uint8 start_row, uint8 start_col, uint8 end_row, uint8 end_col) {
	for(uint8 row = start_row; row < end_row; row++) {
		`$INSTANCE_NAME`_SetCursorPosition(row, start_col);
		for(uint8 col = start_col; col < end_col; col++) {
			`$INSTANCE_NAME`_WritePixels((uint8[]){0, 0, 0, 0}, 4);
		}
	}
}

void `$INSTANCE_NAME`_ClearAll() {
	`$INSTANCE_NAME`_Clear(0, 0, 8, 160);
}

void `$INSTANCE_NAME`_DrawText(uint8 start_page, uint8 start_col, char *text, uint8 inverse) {
	for(uint8 row = 0; row < 2; row++) {
		`$INSTANCE_NAME`_SetCursorPosition(start_page + row, start_col);
		for(char *c = text; *c != '\0'; c++) {
			draw_text_slice(*c, row, inverse);
		}
	}
}

void `$INSTANCE_NAME`_DrawBigNumbers(uint8 start_page, uint8 start_col, char *nums) {
	// Big numbers are 3 glyphs tall
	for(uint8 vglyph = 0; vglyph < 3; vglyph++) {
		for(uint8 row = 0; row < 2; row++) {
			`$INSTANCE_NAME`_SetCursorPosition(start_page + vglyph * 2 + row, start_col);
			// Big numbers are 3 glyphs wide
			for(char *c = nums; *c != '\0'; c++) {
				for(uint8 hglyph = 0; hglyph < 3; hglyph++) {
					if(*c >= '0' && *c <= '9') {
						// Determine glyph based on provided number, which glyph we're drawing vertically,
						// and which glyph we're drawing horizontally
						uint8 glyphnum = FONT_BIGDIGIT_OFFSET
										 + (*c - '0') * 3
										 + FONT_BIGDIGIT_ROW_WIDTH * vglyph
										 + hglyph;
						draw_text_slice(glyphnum, row, 0);
					} else  {
						hglyph = 2; // Other glyphs are only 1 glyph wide
						if(vglyph == 2) {
							draw_text_slice((*c == '.')?GLYPH_CHAR(FONT_GLYPH_BIGPERIOD):*c, row, 0);
						} else {
							draw_text_slice(' ', row, 0);
						}
					}
				}
			}
		}
	}
}

/* [] END OF FILE */
