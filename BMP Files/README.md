## BMP Files
BMP file format is a common way to store images
There are several versions of BMP headers, but we will focus on the most common ones
Each BMP file contains:
* a 14-bytes long file header:
* * 2-byte type (must be equal to BM encoded in ASCII)
* * 4-byte file size
* * 2x 2-byte reserved fields (not used)
* * 4-byte offset to the main data (pixel values)
* a variable size (but with modern system, at least 40-bytes lone) info header:
* * 4-byte real size of the header
* * 4-byte width
* * 4-byte height
* * 2-byte number of planes (not used)
* * 2-byte number of bits used to store pixels
* * 4-byte compression type
* * 4-byte image size
* * 4-byte horizontal DPI
* * 4-byte vertical DPI
* * 4-byte number of colors in the palette
* * 4-byte number of important colors (not used)

* an array of pixel data
# Project
* The program should accept one command line parameter in the format:
```
$ ./program PATH-TO-BMP-FILE
```
For example:
```
$ ./program test.bmp
```
* Program must print out the parsed values from BITMAPFILEHEADER e.g.:
```
BITMAPFILEHEADER:
  bfType:          0x4D42 (BM)
  bfSize:          369738
  bfReserved1:     0x0
  bfReserved2:     0x0
  bfOffBits:       138
```

* Additionally, program must print out parsed values from BITMAPINFOHEADER e.g.:
```
BITMAPINFOHEADER:
  biSize:          124
  biWidth:         280
  biHeight:        330
  biPlanes:        1
  biBitCount:      32
  biCompression:   3
  biSizeImage:     369600
  biXPelsPerMeter: 3779
  biYPelsPerMeter: 3779
  biClrUsed:       0
  biClrImportant:  0
```

* Additionally, program must print out a histogram of RGB colors. For this part, focus only on uncompressed bitmaps with 24-bits (1-byte per red, green and blue channels), but remember that the pixel array has padding in each row if width is not divisible by 4. For example, 123 pixels wide image will contain 123 * 3 = 369123∗3=369 bytes which is not a number divisible by 4. Therefore, after every 369 bytes in the pixel array, there will be 4 - (369 mod 4) = 34−(369mod4)=3 padding bytes (with any value such as zero). For bitmaps with biCompression != 0 or biBitCount != 24, you can just emit a message that histogram calculation is unsupported (but parsing of headers is still required). The expected outcome for an uncompressed 24-bit BMP file:
```
Red:
  0-15: 21.80%
  16-31: 3.02%
  32-47: 2.24%
  48-63: 0.46%
  64-79: 0.40%
  80-95: 0.26%
  96-111: 0.21%
  112-127: 0.17%
  128-143: 0.22%
  144-159: 0.18%
  160-175: 0.21%
  176-191: 0.50%
  192-207: 0.50%
  208-223: 0.57%
  224-239: 0.84%
  240-255: 68.42%
Green:
  0-15: 13.21%
  16-31: 0.54%
  32-47: 0.43%
  48-63: 0.51%
  64-79: 0.52%
  80-95: 0.60%
  96-111: 0.76%
  112-127: 0.84%
  128-143: 1.13%
  144-159: 1.38%
  160-175: 1.42%
  176-191: 6.27%
  192-207: 1.92%
  208-223: 1.12%
  224-239: 0.76%
  240-255: 68.59%
Blue:
  0-15: 13.20%
  16-31: 0.54%
  32-47: 0.42%
  48-63: 0.33%
  64-79: 0.35%
  80-95: 0.40%
  96-111: 0.35%
  112-127: 0.36%
  128-143: 0.50%
  144-159: 0.62%
  160-175: 0.72%
  176-191: 1.13%
  192-207: 1.38%
  208-223: 1.87%
  224-239: 2.89%
  240-255: 74.92%
```

* Program must also handle case when it is started with two command line parameters:
```
$ ./program PATH-TO-INPUT-BMP-FILE PATH-TO-OUTPUT-BMP-FILE
```

* The output BMP file should have all the headers with exactly the same values, but the pixel array should be modified to make the image grayscale using the simplest formula computed for each pixel: gray =(red + green + blue)/3. The value gray should be copied to red, green and blue fields for the pixel. For example, a pixel has red=100, green=60, blue=200, therefore gray = 360/3 = 120 and you should modify the pixel array to have red = green = blue = 120. For this task, you can also assume to support only uncompressed 24-bit BMP files and emit a message for others.
