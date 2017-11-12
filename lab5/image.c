#include "image.h"


read_result image_read_bmp(FILE* in, image* dest) {
	size_t offset=0, read_pixels = 0;

	bmp_header* bmp = malloc(sizeof(bmp_header));
	read_result err = bmp_header_read(in, bmp);

	if (err != READ_OK) {
		return err;
	}

	dest->width = bmp->biWidth;
	dest->height = bmp->biHeight;
	dest->data = malloc(sizeof(pixel*) * bmp->biHeight);

	offset = dest->width * sizeof(pixel) % 4;
	if(offset != 0) {
		offset = 4 - offset;
	}

	fseek(in, bmp->bOffBits, SEEK_SET);
	for (int i = 0; i < bmp->biHeight; ++i) {
		dest->data[i] = malloc(sizeof(pixel) * dest->width);
		read_pixels = fread(dest->data[i], sizeof(pixel), dest->width, in);
		if (read_pixels < dest->width) {
			return READ_INVALID_BITS;
		}
	}

	return READ_OK;
}


write_result image_write_bmp(FILE* out, image* source) {
	// amount of written to file pixels
	size_t written = 0, offset = 0;
	int	i = 0, j = 0;

	bmp_header header = get_bmp_header(source->width, source->height);

	written = fwrite(&header, sizeof(bmp_header), 1, out);
	if (written < 1) {
		return WRITE_ERROR;
	}
	
	offset = source->width * sizeof(pixel) % 4;
	if(offset != 0) {
		offset = 4 - offset;
	}

	for (i = 0; i < source->height; ++i) {
		for (j = 0; j < source->width; ++j) {
			written = fwrite(&source->data[i][j], sizeof(pixel), 1, out);
			if (written < 1) {
				return WRITE_ERROR;
			}
		}
		fseek(out, offset, SEEK_CUR);
	}
	
	return WRITE_OK;
}

void image_print_info(const image* img) {
    printf("Image {\n");
    printf("\twidth=%llu,\n", img->width);
    printf("\theight=%llu,\n", img->height);
    printf("}\n");
}


image image_rotate(image* original, rotation_direction rd, float angle) {
	// angle is always >0
	int i=0, j=0, new_i=0, new_j=0;
	double rotation_matrix[2][2];
	float rotation_angle = angle;

	if (rd == RD_LEFT) {
		rotation_angle = -rotation_angle;
	}

	rotation_matrix[0][0] = round(cos(rotation_angle) * 1000) / 1000;
	rotation_matrix[0][1] = round(-sin(rotation_angle) * 1000) / 1000;
	rotation_matrix[1][0] = round(sin(rotation_angle) * 1000) / 1000;
	rotation_matrix[1][1] = round(-cos(rotation_angle) * 1000) / 1000;
	
	image rotated;
	// if angle == 90 this should always work
	rotated.width = original->height;
	rotated.height = original->width;

	rotated.data = malloc(sizeof(pixel*) * rotated.height);
	for (i = 0; i < rotated.height; ++i) {
		rotated.data[i] = malloc(sizeof(pixel) * rotated.width);
	}

	// for each pixel of original image
	for (i = 0; i < original->height; i++) {
		for (j = 0; j < original->width; j++) {
			// find its [pixel] new position (new_i; new_j)
			new_i = rotation_matrix[0][0] * i + rotation_matrix[0][1] * j;
			new_j = rotation_matrix[1][0] * i + rotation_matrix[1][1] * j;

			if (rd == RD_RIGHT) new_i += (int)rotated.height - 1;
			else new_j += (int)rotated.width - 1;

			rotated.data[new_i][new_j] = original->data[i][j];
		}
	}

	return rotated;
}
