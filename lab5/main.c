#include "main.h"


int main() {
	char* filename = "/Users/gasabr/itmo/debts/lsp/src/lab5/images/spiral_test.bmp";
	char* filename_out = "/Users/gasabr/itmo/debts/lsp/src/lab5/images/spiral_out.bmp";

	FILE* img_file = fopen(filename, "rb");
	if (!img_file) {
		printf("Can not open file!\n");
	}
	fclose(img_file);

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
	image_write_bmp(out_file, img);
	fclose(out_file);

}
