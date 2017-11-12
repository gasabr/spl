#include "image.h"


read_result image_read_bmp(FILE* in, image* dest) {
	size_t offset=0;
	bmp_header* bmp = malloc(sizeof(bmp_header));
	read_result err = bmp_header_read(in, bmp);
	printf("height=%d\n", bmp->biHeight);
	dest->header = bmp;
	size_t read_pixels = 0;

	if (err != READ_OK) {
		return err;
	}

	dest->width = dest->header->biWidth;
	dest->height = dest->header->biHeight;
	dest->data = malloc(sizeof(pixel*) * dest->header->biHeight);

	/* int stride = (dest->header->biWidth * (dest->header->biBitCount / 8) + 3) & ~3; */
	offset = dest->width * sizeof(pixel) % 4;
	if(offset != 0) {
		offset = 4 - offset;
	}
	printf("offset=%zu\n", offset);

	fseek(in, bmp->bOffBits, SEEK_SET);
	for (int i = 0; i < dest->header->biHeight; ++i) {
		dest->data[i] = malloc(sizeof(pixel) * dest->width);
		read_pixels = fread(dest->data[i], sizeof(pixel), dest->width, in);
		if (read_pixels < dest->width) {
			printf("Break on height: %d with %lu pixels\n", i, read_pixels);
			return READ_INVALID_BITS;
		}
	}

	return READ_OK;
}


write_result image_write_bmp(FILE* out, image* source) {
	size_t written = 0;
	int	i = 0, j = 0;
	written = fwrite(source->header, sizeof(bmp_header), 1, out);
	if (written < 1) {
		return WRITE_ERROR;
	}
	for (i = 0; i < source->height; ++i) {
		for (j = 0; j < source->width; ++j) {
			/* print_pixel_info(&source->data[i][j]); */
			written = fwrite(&source->data[i][j], sizeof(pixel), 1, out);
			/* printf("written="%) */
			if (written < 1) {
				printf("Failed on the row: %d\n", i);
				return WRITE_ERROR;
			}
		}
	}
	
	return WRITE_OK;
}

void image_print_info(const image* img) {
    printf("Image {\n");
    printf("\twidth=%llu,\n", img->width);
    printf("\theight=%llu,\n", img->height);
    printf("}\n");
}


image image_rotate(image* original, float angle) {
	int i=0, j=0, new_i=0, new_j=0;
	double rotation_matrix[2][2];
	rotation_matrix[0][0] = round(cos(angle) * 1000) / 1000;
	rotation_matrix[0][1] = round(-sin(angle) * 1000) / 1000;
	rotation_matrix[1][0] = round(sin(angle) * 1000) / 1000;
	rotation_matrix[1][1] = round(-cos(angle) * 1000) / 1000;

	printf("%f %f %f %f", rotation_matrix[0][0], rotation_matrix[0][1],
		   	rotation_matrix[1][0], rotation_matrix[1][1]);

	image rotated;
	rotated.header = original->header;
	// if angle == 90 this should always work
	rotated.width = original->height;
	rotated.height = original->width;

	rotated.data = malloc(sizeof(pixel*) * rotated.height);
	for (i = 0; i < rotated.height; ++i) {
		rotated.data[i] = malloc(sizeof(pixel) * rotated.width);
	}

	image_print_info(&rotated);

	// there should be code to fill image with background color
	// for rotation on any angle

	for (i = 0; i < original->height; ++i) {
		for (j = 0; j < original->width; ++j) {
			new_i = rotation_matrix[0][0] * i + rotation_matrix[1][0] * j;
			/* printf("ni= %d * %f + %d, %f = %d\n", i, rotation_matrix[0][0],  */
			/*         j, rotation_matrix[0][1], new_i); */
			new_j = rotation_matrix[0][1] * i + rotation_matrix[1][1] * j;
			/* printf("i=%d, j=%d-> ni=%d, nj=%d\n", i, j, new_i, new_j); */
			rotated.data[new_i][new_j + rotated.height] = original->data[i][j];
		}
	}

	return rotated;
}
