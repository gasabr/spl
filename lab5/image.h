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
	bmp_header* header;
} image;


read_result  image_read_bmp(FILE* in, image* dest);
write_result image_write_bmp(FILE* out, image* source);
free_result  image_free(image* img);

void image_print_info(const image* img);

#endif
