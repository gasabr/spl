#include "image.h"


read_result image_read_bmp(FILE* in, image* dest) {
	bmp_header* bmp = malloc(sizeof(bmp_header));
	read_result err = bmp_header_read(in, bmp);
	printf("height=%d\n", bmp->biHeight);
	dest->header = bmp;
	size_t read_pixels = 0;

	if (err != READ_OK) {
		return err;
	}

	dest->width = dest->header->biWidth;
	dest->height = dest->header->biHeight;
	dest->data = malloc(sizeof(pixel*) * dest->header->biHeight);

	int stride = (dest->header->biWidth * (dest->header->biBitCount / 8) + 3) & ~3;
	printf("stride=%d\n", stride);

	for (int i = 0; i < dest->header->biHeight; ++i) {
		dest->data[i] = malloc(sizeof(pixel) * dest->width);
		read_pixels = fread(dest->data[i], sizeof(pixel), dest->width, in);
		if (read_pixels < dest->width) {
			printf("Break on height: %d\n", i);
			return READ_INVALID_BITS;
		}
	}

	return READ_OK;
}


write_result image_write_bmp(FILE* out, image* source) {
	size_t written = 0;
	written = fwrite(source->header, sizeof(bmp_header), 1, out);
	if (written < 1) {
		return WRITE_ERROR;
	}
	written = fwrite(source->data, source->header->biSize - sizeof(bmp_header), 1, out);
	if (written < 1) {
		return WRITE_ERROR;
	}
	
	return WRITE_OK;
}


void image_print_info(const image* img) {
	printf("Image {\n");
	printf("\twidth=%llu,\n", img->width);
	printf("\theight=%llu,\n", img->height);
	printf("}\n");
}
