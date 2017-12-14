#ifndef IMAGE_H
#define IMAGE_H

#define __STDC_FORMAT_MACROS

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h> // to printf uint32_t
#include <pthread.h>

#include "bmp.h"
#include "pixel.h"
#include "results.h"


typedef pixel** pixels;

typedef struct Image {
	uint64_t width, height;
	pixels data;
} image;


typedef enum ActionEnum {
	ROTATE_LEFT = 0,
	ROTATE_RIGHT,
	BLUR,
	SEPIA,
	SEPIA_ASM,
	SEPIA_THREADED,
	SEPIA_THREADED_V2,
	NOT_KNOWN_ACTION
} action_e;

typedef struct ImagesPair {
	image* src;
	image* dest;
} images_pair_t;


typedef struct ThreadInfo {
	image* src;
	image* dest;
	size_t start_line;
	size_t step;
} thread_info_t;

typedef int (*sepia_channel_filter)(float[4], float[4], float[4], float[4]);


read_result  image_read_bmp(FILE* in, image* dest);
write_result image_write_bmp(FILE* out, image* source);
free_result  image_free(image* img);

image image_rotate(image* original, action_e rd, float angle);
image image_blur(image* img);
image image_sepia(image* img);
image image_sepia_asm(image* img);
image image_sepia_threaded(image* img);
image image_sepia_threaded_v2(image* img, int n_threads);
void* image_sepia_asm_lines(void* arg);
image image_sepia_c_threaded(image* img, size_t n_threads);
void* image_sepia_c_lines(void* arg);

void* _sepia_blue(void* images);
void* _sepia_green(void* images);
void* _sepia_red(void* images);

void sepia_blue(float[4], float[4], float[4], float[12]);
void sepia_red(float[4], float[4], float[4], float[12]);
void sepia_green(float[4], float[4], float[4], float[12]);

void image_print_info(const image* img);

#endif
