#include "bmp.h"


read_result bmp_header_read(FILE* in, bmp_header* dest) {
	size_t read_headers = fread(dest, sizeof(bmp_header), 1, in);
	// some 24bpp images have negotive height on my computer...
	/* dest->biHeight = abs(dest->biHeight); */

	if (read_headers < 1) {
		printf("Can not read header!");
		return READ_INVALID_SIGNATURE;
	}

	return READ_OK;
}


void bmp_header_print(const bmp_header* header) {
	printf("BMPHeader {\n");
	printf("\tbfType=%u,\n", header->bfType);
	printf("\tbfileSize=%u,\n", header->bfileSize);
	printf("\tbiWidth=%u,\n", header->biWidth);
	printf("\tbiHeight=%u,\n", header->biHeight);
	printf("\tbiSizeImage=%u,\n", header->biSizeImage);
	printf("}");
}
