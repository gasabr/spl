#include "image.h"


read_result from_bmp(FILE* in, image* dest) {
	bmp_header* bmp = malloc(sizeof(bmp_header));
	read_result err = bmp_header_read(in, bmp);
	size_t read_pixels = 0;

	if (err != READ_OK) {
		return err;
	}

	dest->width = bmp->biWidth;
	dest->height = bmp->biHeight;
	dest->data = malloc(sizeof(pixel*) * bmp->biHeight);

	int stride = (bmp->biWidth * (bmp->biBitCount / 8) + 3) & ~3;
	printf("stride=%d\n", stride);

	for (int i = 0; i < bmp->biHeight; ++i) {
		dest->data[i] = malloc(sizeof(pixel) * dest->width);
		read_pixels = fread(dest->data[i], sizeof(pixel), dest->width, in);
		if (read_pixels < dest->width) {
			printf("Break on height: %d\n", i);
			return READ_INVALID_BITS;
		}
	}

	return READ_OK;
}


void print_image_info(const image* img) {
	printf("Image {\n");
	printf("\twidth=%llu,\n", img->width);
	printf("\theight=%llu,\n", img->height);
	printf("}\n");
}
