#include "image.h"


read_result from_bmp(FILE* in, image* dest) {
	bmp_header* bmp = malloc(sizeof(bmp_header));
	read_result err = bmp_header_read(in, bmp);

	if (err != READ_OK) {
		return err;
	}

	dest->width = bmp->biWidth;
	dest->height = bmp->biHeight;

	return READ_OK;
}
