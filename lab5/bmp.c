#include "bmp.h"


read_result bmp_header_read(FILE* in, bmp_header* dest) {
	size_t read_headers = fread(dest, sizeof(bmp_header), 1, in);

	if (read_headers < 1) {
		return READ_INVALID_SIGNATURE;
	}

	return READ_OK;
}


void bmp_header_print(bmp_header* const header) {
	printf("BMPHeader {\n");
	printf("\tbfType=%u,\n", header->bfType);
	printf("\tbfileSize=%u,\n", header->bfileSize);
	printf("\tbiWidth=%u,\n", header->biWidth);
	printf("\tbiHeight=%u,\n", header->biHeight);
	printf("\tbiSizeImage=%u,\n", header->biSizeImage);
	printf("}");
}
