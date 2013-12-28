from PIL import Image
import lzf
import numpy


def main():
    img = Image.open("splashscreen.gif")

    # Convert to an array of gray values - data[row, column]
    data = numpy.asarray(img.convert('L'))

    # Flip
    data = data[::-1]

    # Invert
    data = numpy.subtract(255, data)

    # Split up into pages - pages[page, page_row:8, column]
    pages = numpy.array_split(data, range(8, img.size[1], 8), 0)

    # Reverse order of pages, too
    pages = pages[::-1]

    # Rearrange each page to be column-major - pages[page, column, page_row:8]
    pages = numpy.transpose(pages, (0, 2, 1))

    # Unpack into bits - pages[page, column, page_row:8, pixel_bit:8]
    pages = numpy.expand_dims(pages, 3)
    pages = numpy.unpackbits(pages, 3)

    # Truncate to 4bpp - pages[page, column, page_row:8, pixel_bit:4]
    pages = pages[:, :, :, :4]

    # Transpose into bit planes - pages[page, column, pixel_bit:4, page_row:8]
    pages = numpy.transpose(pages, (0, 1, 3, 2))

    # Collapse bit-planes - pages[page, column, pixel_bit:4, value:1]
    pages = numpy.packbits(pages, 3)

    # Flatten into pages - pages[page, byte]
    pages = numpy.reshape(pages, (pages.shape[0], -1))

    # Compress each page - pages[page]
    pages = [lzf.compress(page.tostring('C')) for page in pages]

    # Neatly format the image for output
    indexes = [0]
    for i in range(len(pages)):
        indexes.append(indexes[i] + len(pages[i]))

    out = open('splashscreen.c', 'w')
    out.write('#include "splashscreen.h"\n\n')
    out.write("const uint8 splashscreen_data[] = {\n")
    for i, page in enumerate(pages):
        out.write("    // %d-%d: Page %d\n" % (indexes[i], indexes[i + 1] - 1, i))
        for line in range(0, len(page), 10):
            value = ''.join('0x%02X, ' % ord(x) for x in page[line:line + 10]).strip()
            out.write("    %s\n" % (value,))
    out.write("};\n\n")

    out.write("const int16 splashscreen_indexes[] = {%s};\n" % (', '.join(str(x) for x in indexes)))
    out.close()

    print "Image output in %d bytes" % (sum(len(page) + 2 for page in pages) + 2,)

if __name__ == '__main__':
    main()
