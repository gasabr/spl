#include "main.h"


int main() {
	char* filename = "/Users/gasabr/itmo/debts/lsp/src/lab5/images/spiral.bmp";

	FILE* img_file = fopen(filename, "rb");
	if (!img_file) {
		printf("Can not open file!\n");
	}
	/* image* img = malloc(sizeof(image)); */
	bmp_header* bmp = malloc(sizeof(bmp_header));
	read_result err = bmp_header_read(img_file, bmp);
	if (err != READ_OK) {
		printf("RETARD ALLERT.\n");
	}

	bmp_header_print(bmp);
}
