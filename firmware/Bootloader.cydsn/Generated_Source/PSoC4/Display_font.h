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
#define FONT_BIGDIGIT_PERIOD (190 + FONT_GLYPH_OFFSET)

#define FONT_GLYPH_LARR (127 + FONT_GLYPH_OFFSET)
#define FONT_GLYPH_RARR (128 + FONT_GLYPH_OFFSET)
#define FONT_GLYPH_UARR (158 + FONT_GLYPH_OFFSET)
#define FONT_GLYPH_DARR (159 + FONT_GLYPH_OFFSET)
#define FONT_GLYPH_ENTER (191 + FONT_GLYPH_OFFSET)

extern char glyphs[192][FONT_GLYPH_PAGES][FONT_GLYPH_COLUMNS];

/* [] END OF FILE */
