from PIL import Image


GLYPH_WIDTH = 12  # Pixels
GLYPH_ROWS = 2  # Bytes


def build_column(img, x, y):
    ret = 0
    for i in range(8):
        ret = (ret << 1) | (0 if img.getpixel((x, y + (7 - i))) else 1)
    return ret


def main():
    img = Image.open("reload font.png")
    width, height = img.size
    x_glyphs = width / GLYPH_WIDTH
    y_glyphs = height / (GLYPH_ROWS * 8)

    out = open('font.c', 'w')
    out.write("const char glyphs[%d][%d][%d] = {\n" % (x_glyphs * y_glyphs, GLYPH_ROWS, GLYPH_WIDTH))

    for y in range(y_glyphs):
        for x in range(x_glyphs):
            out.write("    {\n")
            for row in range(GLYPH_ROWS):
                columns = [build_column(img, x * GLYPH_WIDTH + i, (y * GLYPH_ROWS + row) * 8) for i in range(GLYPH_WIDTH)]
                out.write("        {%s},\n" % (", ".join("0x%X" % column for column in columns)))
            out.write("    },\n")

    out.write("};\n")


if __name__ == '__main__':
    main()
