#include "pixel.h"


void print_pixel_info(const pixel* px) {
	printf("Pixel {\n");
	printf("\tr=%u\n", px->r);
	printf("\tg=%u\n", px->g);
	printf("\tb=%u\n", px->b);
	printf("}\n");
}
