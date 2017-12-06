#include "pixel.h"


void print_pixel_info(const pixel* px) {
	printf("Pixel {\n");
	printf("\tr=%u\n", px->r);
	printf("\tg=%u\n", px->g);
	printf("\tb=%u\n", px->b);
	printf("}\n");
}


unsigned char sat( uint64_t x) {
    if (x < 256) 
		return x; 
	return 255;
}


pixel pixel_sepia(const pixel px) {
	static const float c[3][3] =  {
		{ .393f, .769f, .189f },
		{ .349f, .686f, .168f },
		{ .272f, .543f, .131f } };	

	pixel filtered;
	filtered.r = sat(px.r * c[0][0] + px.g * c[0][1] + px.b * c[0][2]);
	filtered.g = sat(px.r * c[1][0] + px.g * c[1][1] + px.b * c[1][2]);
	filtered.b = sat(px.r * c[2][0] + px.g * c[2][1] + px.b * c[2][2]);

	return filtered;
}
