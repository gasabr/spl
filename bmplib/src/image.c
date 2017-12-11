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
    printf("\twidth=%" PRIu64 "\n", img->width);
    printf("\theight=%" PRIu64 ",\n", img->height);
    printf("}\n");
}


image image_rotate(image* original, action_e rd, float angle) {
	// angle is always >0
	int i=0, j=0, new_i=0, new_j=0;
	double rotation_matrix[2][2];
	float rotation_angle = angle;

	if (rd == ROTATE_LEFT) {
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

			if (rd == ROTATE_RIGHT) new_i += (int)rotated.height - 1;
			else new_j += (int)rotated.width - 1;

			rotated.data[new_i][new_j] = original->data[i][j];
		}
	}

	return rotated;
}

image image_blur(image* img) {
	int i=0, j=0;
	int	k=0, l=0;
	int blue_ch_sum=0, green_ch_sum=0, red_ch_sum=0, n_neighbour_pixs=0;

	// create the new image
	image blurred;
	blurred.width = img->width;
	blurred.height = img->height;
	blurred.data = malloc(sizeof(pixel*) * img->height);
	for (i = 0; i < blurred.height; i++) {
		blurred.data[i] = malloc(sizeof(pixel) * blurred.width);
	}

	// for all the pixels in the new image
	for (i=0; i < blurred.height; i++) {
		for (j = 0; j < blurred.width; j++) {
			if (i == 0 || j == 0 || i == blurred.height-1 || j == blurred.width-1) {
				blurred.data[i][j] = img->data[i][j];
				continue;
			}

			blue_ch_sum = 0;
			green_ch_sum = 0;
			red_ch_sum = 0;
			n_neighbour_pixs = 0;

			// count sum of channels around the pixel
			for (k = i-1; k <= i+1; k++) {
				for (l = j-1; l <= j+1; l++) {
					blue_ch_sum = blue_ch_sum + img->data[k][l].b;
					green_ch_sum += img->data[k][l].g;
					red_ch_sum += img->data[k][l].r;
					n_neighbour_pixs += 1;
				}
			}
			blurred.data[i][j].b = (uint32_t)(blue_ch_sum / n_neighbour_pixs);
			blurred.data[i][j].g = (uint32_t)(green_ch_sum / n_neighbour_pixs);
			blurred.data[i][j].r = (uint32_t)(red_ch_sum / n_neighbour_pixs);
		}
	}
	return blurred;
}


image image_sepia(image* img) {
	int i=0, j=0;

	// TODO: move copying image to the function
	image filtered;
	filtered.height = img->height;
	filtered.width = img->width;

	filtered.data = malloc(sizeof(pixel*) * img->height);
	for (i = 0; i < filtered.height; i++) {
		filtered.data[i] = malloc(sizeof(pixel) * filtered.width);
	}

	for (i=0; i < img->height; i++) {
		for (j = 0; j < img->width; j++) {
			filtered.data[i][j] = pixel_sepia(img->data[i][j]);
		}
	}

	return filtered;
}


image image_sepia_asm(image* img) {
	int i=0, j=0, k=0;

	image filtered;
	filtered.height = img->height;
	filtered.width = img->width;

	filtered.data = malloc(sizeof(pixel*) * img->height);
	for (i = 0; i < filtered.height; i++) {
		filtered.data[i] = malloc(sizeof(pixel) * filtered.width);
	}

	for (i = 0; i < img->height; i++) {
		// for all the pixels in the row except last 3, if width % 4 != 0
		for (j = 0; j < img->width; j += 4) {
			float b[4], new_b[4];
			float g[4], new_g[4];
			float r[4], new_r[4];

			if (j >= img->width - 3) {
				break;
			}
			for (k = 0; k < 4; k++) {
				b[k] = img->data[i][j + k].b;
				g[k] = img->data[i][j + k].g;
				r[k] = img->data[i][j + k].r;
			}

			sepia_blue(b, g, r, new_b);
			sepia_green(b, g, r, new_g);
			sepia_red(b, g, r, new_r);

			// printf("%f -> %f\n", b[0], new_b[0]);

			for (k = 0; k < 4; k++) {
				filtered.data[i][j+k].b = new_b[k];
				filtered.data[i][j+k].g = new_g[k];
				filtered.data[i][j+k].r = new_r[k];
			}

		}
	}

	return filtered;
}
