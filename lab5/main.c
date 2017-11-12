#include "main.h"


int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Usage ./rotate <input file name> <output file name> <left|right>\n");
	}

	char* filename_in = argv[1];
	char* filename_out = argv[2];
	char* rotation_directon_str = argv[3];
	rotation_direction rd;

	if (strcmp(rotation_directon_str, "left") == 0) {
		rd = RD_LEFT;
	} else if (strcmp(rotation_directon_str, "right") == 0) {
		rd = RD_RIGHT;
	} else {
		printf("Invalid rotation direction.\n");
		exit(0);
	}

	FILE* img_file = fopen(filename_in, "rb");
	if (img_file == NULL) {
		printf("Can not open file!\n");
	}

	image* img = malloc(sizeof(image));
	read_result err = image_read_bmp(img_file, img);
	if (err != READ_OK) {
		printf("Can not read bmp file. Error %d\n", err);
		exit(1);
	}

	FILE* out_file = fopen(filename_out, "wb");
	if (!out_file) {
		printf("Can not open output file!\n");
		exit(1);
	}

	image rotated = image_rotate(img, rd, M_PI_2);
	write_result w_err = image_write_bmp(out_file, &rotated);
	if (w_err != WRITE_OK) {
		printf("Can not write to bmp file. Error %d\n", w_err);
		exit(1);
	}

	fclose(out_file);

}
