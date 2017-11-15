#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"
#include "pixel.h"
#include "results.h"


typedef pixel** pixels;

typedef struct Image {
	uint64_t width, height;
	pixels data;
} image;


typedef enum RotationDirection {
	RD_LEFT = 0,
	RD_RIGHT
} rotation_direction;

read_result  image_read_bmp(FILE* in, image* dest);
write_result image_write_bmp(FILE* out, image* source);
free_result  image_free(image* img);

image image_rotate(image* original, rotation_direction rd, float angle);

void image_print_info(const image* img);
image image_blur(image* img);

#endif
