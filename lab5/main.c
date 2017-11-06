#include "main.h"


int main() {
	char* filename = "/Users/gasabr/itmo/debts/lsp/src/lab5/images/collision.bmp";

	FILE* img_file = fopen(filename, "rb");
	if (!img_file) {
		printf("Can not open file!\n");
	}

	image* img = malloc(sizeof(image));
	read_result err = from_bmp(img_file, img);
	if (err != READ_OK) {
		printf("RETARD ALLERT.\n");
	}

	print_image_info(img);
}
