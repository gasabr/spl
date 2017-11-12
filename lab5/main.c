#include "main.h"

#define PI 3.1416


int main() {
	char* filename_in = "images/ball.bmp";
	char* filename_out = "images/ball_out.bmp";

	FILE* img_file = fopen(filename_in, "rb");
	if (!img_file) {
		printf("Can not open file!\n");
	}

	image* img = malloc(sizeof(image));
	read_result err = image_read_bmp(img_file, img);
	if (err != READ_OK) {
		printf("Can not read bmp file. Error %d\n", err);
	}

	FILE* out_file = fopen(filename_out, "wb");
	if (!out_file) {
		printf("Can not open output file!\n");
	}

	image rotated = image_rotate(img, PI/2);
	write_result w_err = image_write_bmp(out_file, &rotated);
	if (w_err != WRITE_OK) {
		printf("Can not write to bmp file. Error %d\n", w_err);
	}
	fclose(out_file);

}
