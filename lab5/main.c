#include "main.h"

#define PI 3.1416


int main() {
	char* filename = "/Users/gasabr/itmo/debts/lsp/src/lab5/images/ball.bmp";
	char* filename_out = "/Users/gasabr/itmo/debts/lsp/src/lab5/images/spiral_out.bmp";

	FILE* img_file = fopen(filename, "rb");
	if (!img_file) {
		printf("Can not open file!\n");
	}

	image* img = malloc(sizeof(image));
	read_result err = image_read_bmp(img_file, img);
	if (err != READ_OK) {
		printf("RETARD ALLERT #%d\n", err);
	}

	image_print_info(img);
	print_pixel_info(&img->data[259][100]);

	FILE* out_file = fopen(filename_out, "wb");
	if (!out_file) {
		printf("Can not open out file!\n");
	}

	image rotated = image_rotate(img, PI/2);
	write_result w_err = image_write_bmp(out_file, &rotated);
	if (w_err != WRITE_OK) {
		printf("Can not write to bmp file. Error %d\n", w_err);
	}
	fclose(out_file);

}
