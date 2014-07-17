/* ========================================
 *
 * Copyright Arachnid Labs, 2013
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#define FONT_GLYPH_PAGES 2
#define FONT_GLYPH_COLUMNS 12
#define FONT_GLYPH_COUNT 192
#define FONT_GLYPH_OFFSET 32
#define FONT_BIGDIGIT_OFFSET (96 + FONT_GLYPH_OFFSET)
#define FONT_BIGDIGIT_ROW_WIDTH 32

#define GLYPH_CHAR(x) (x[0])
#define FONT_GLYPH_BIGPERIOD "\xDE"
#define FONT_GLYPH_LARR "\x9E"
#define FONT_GLYPH_RARR "\x9F"
#define FONT_GLYPH_UARR "\xBE"
#define FONT_GLYPH_DARR "\xBF"
#define FONT_GLYPH_ENTER "\xDF"
#define FONT_GLYPH_OHM "\x7F"

extern char glyphs[192][FONT_GLYPH_PAGES][FONT_GLYPH_COLUMNS];

/* [] END OF FILE */
