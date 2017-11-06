#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdlib.h>

#include "bmp.h"
#include "pixel.h"
#include "results.h"


typedef pixel** pixels;

typedef struct Image {
	uint64_t width, height;
	pixels data;
} image;


read_result  from_bmp(FILE* in, image* const dest);
write_result to_bmp(FILE* out, image* const source);

void print_image_info(const image* img);

#endif
