#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "results.h"

typedef struct __attribute__((packed))
    bmpHeader {
        uint16_t bfType;
		uint32_t bfileSize;
		uint32_t bfReserved;
		uint32_t bOffBits;
		uint32_t biSize;

		uint32_t biWidth;
		uint32_t biHeight;
		uint16_t biPlanes;
		uint16_t biBitCount;
		uint32_t biCompression;
		uint32_t biSizeImage;
		uint32_t biXPelsPerMeter;
		uint32_t biYPelsPerMeter;
		uint32_t biClrUsed;
		uint32_t biClrImportant;
} bmp_header;


read_result bmp_header_read(FILE* in, bmp_header* const dest);
void bmp_header_print(const bmp_header* header);

#endif
