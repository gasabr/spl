#include "main.h"

action_e parse_action(char* action_str) {
	if (strcmp(action_str, "rotate_left") == 0) {
		return ROTATE_LEFT;
	} else if (strcmp(action_str, "rotate_right") == 0) {
		return ROTATE_RIGHT; 
	} else if (strcmp(action_str, "blur") == 0) {
		return BLUR;
	} else if (strcmp(action_str, "sepia") == 0) {
		return SEPIA;
	} else if (strcmp(action_str, "sepia_asm") == 0) {
		return SEPIA_ASM;
	} else if (strcmp(action_str, "sepia_threaded") == 0) {
		return SEPIA_THREADED;
	} else {
		return NOT_KNOWN_ACTION;
	}
}


int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Usage ./bmp_transform <input file name> <output file name>" 
				"<left|right>\n");
	}

	char* filename_in = argv[1];
	char* filename_out = argv[2];
	char* action_str = argv[3];
	action_e action = parse_action(action_str);

	clock_t start, finish;
	double time_spent;

	if (action == NOT_KNOWN_ACTION) {
		printf("Invalid action, choose one of the: rotate_left,"
				"rotate_right, blur, sepia, sepia_asm, sepia_threaded.\n");
		exit(1);
	}

	FILE* img_file = fopen(filename_in, "rb");
	if (img_file == NULL) {
		perror("Error opening input file");
		exit(1);
	}

	image* img = malloc(sizeof(image));
	read_result err = image_read_bmp(img_file, img);
	if (err != READ_OK) {
		printf("Can not read bmp file. Error %d\n", err);
		exit(1);
	}

	start = clock();
	// perform action
	image result_image;
	if (action == ROTATE_LEFT || action == ROTATE_RIGHT) {
		result_image = image_rotate(img, action, PI_2);
	} else if (action == SEPIA) {
		result_image = image_sepia(img);
	} else if (action == SEPIA_ASM) {
		result_image = image_sepia_asm(img);
	} else if (action == SEPIA_THREADED) {
		result_image = image_sepia_threaded(img);
	} else {
		result_image = image_blur(img);
	}
	finish = clock();
	time_spent = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("%10s time: %f\n", action_str, time_spent);

	FILE* out_file = fopen(filename_out, "wb");
	if (!out_file) {
		perror("Error opening output file");
		exit(1);
	}
	write_result w_err = image_write_bmp(out_file, &result_image);
	if (w_err != WRITE_OK) {
		printf("Can not write to bmp file. Error %d\n", w_err);
		exit(1);
	}

	fclose(out_file);
	return 0;
}
