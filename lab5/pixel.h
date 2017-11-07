#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <stdio.h>

typedef struct Pixel {
	uint8_t b, g, r;
} pixel;


void print_pixel_info(const pixel*);

#endif
