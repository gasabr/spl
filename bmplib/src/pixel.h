#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <stdio.h>

typedef struct Pixel {
	uint8_t b, g, r;
} pixel;

unsigned char sat( uint64_t x);

void print_pixel_info(const pixel*);
pixel pixel_sepia(const pixel);

#endif
