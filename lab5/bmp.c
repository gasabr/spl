#include "bmp.h"


read_result bmp_header_read(FILE* in, bmp_header* dest) {
	size_t read_headers = fread(dest, sizeof(bmp_header), 1, in);

	if (read_headers < 1) {
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


bmp_header get_bmp_header(uint32_t width, uint32_t height) {
	bmp_header header;

	header.bfType = 0x4d42;
	header.bfileSize = sizeof(bmp_header) + width*3 * height;
	header.bfReserved = 0;
	header.bOffBits = 54;
	header.biSize = 40;
	header.biWidth = width;
	header.biHeight = height;
	header.biPlanes = 1;
	header.biBitCount = 24;
	header.biCompression = 0;
	header.biSizeImage = 0;
	header.biXPelsPerMeter = 0xb13;
	header.biYPelsPerMeter = 0xb13;
	header.biClrUsed = 0;
	header.biClrImportant = 0;

	return header;
}
