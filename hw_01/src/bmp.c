#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

const int BITS_IN_BYTE = 8;
const int ONE_BYTE = 1;

uint32_t ceil_to_fourth(uint32_t number) {
    return ((number + 3) / 4) * 4;
}

bmp_image read_bmp_image(const char *input_filename) {
    FILE *input = fopen(input_filename, "rb");
    bmp_image input_image;

    // bmp_header reading
    input_image.header = (bmp_header *)malloc(sizeof(bmp_header));
    if (!input_image.header) {
        printf("ERROR: memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    fread(input_image.header, ONE_BYTE, sizeof(bmp_header), input);

    // image_header reading
    input_image.info = (image_header *)malloc(sizeof(image_header));
    if (!input_image.info) {
        printf("ERROR: memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    fread(input_image.info, ONE_BYTE, sizeof(image_header), input);

    // positioning on pixels data
    fseek(input, input_image.header->image_data_offset, SEEK_SET);
    input_image.image.height = input_image.info->biHeight;
    input_image.image.width = input_image.info->biWidth;

    uint32_t actual_width_in_bytes_to_read = ceil_to_fourth(input_image.image.width * sizeof(pixel));
    uint32_t padding_size = actual_width_in_bytes_to_read - input_image.image.width * sizeof(pixel); // bytes which added in alignment

    char padding_zeros[] = {0, 0, 0};

    input_image.image.image_pixels = (pixel **)malloc(input_image.image.height * sizeof(pixel *));
    if (!input_image.image.image_pixels) {
        printf("ERROR: memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    input_image.image.image_pixels[0] = (pixel *)malloc(input_image.image.height * input_image.image.width * sizeof(pixel *));
    if (!input_image.image.image_pixels[0]) {
        printf("ERROR: memory allocation failed!");
        exit(EXIT_FAILURE);
    }

    for (int height_index = 0; height_index < input_image.image.height; height_index++) {
        if (height_index != 0) {
            input_image.image.image_pixels[height_index] =
                    input_image.image.image_pixels[height_index - 1] + input_image.image.width;
        }

        for (int width_index = 0; width_index < input_image.image.width; width_index++) {
            fread(&input_image.image.image_pixels[height_index][width_index], ONE_BYTE, sizeof(pixel), input);
        }
        fread(padding_zeros, ONE_BYTE, padding_size, input);
    }
    fclose(input);
    return input_image;
}


void write_bmp_image(const char *output_filename, const bmp_image *image) {
    FILE* imageFile = fopen(output_filename, "wb");

    uint32_t width_in_bytes = image->info->biWidth * sizeof(pixel);

    unsigned char padding[] = {0, 0, 0};
    uint32_t padding_size = ceil_to_fourth(width_in_bytes) - width_in_bytes;


    fwrite(image->header, ONE_BYTE, sizeof(bmp_header), imageFile);

    fwrite(image->info, ONE_BYTE, sizeof(image_header), imageFile);

    for (int height_index = 0; height_index < image->info->biHeight; height_index++) {
        fwrite(image->image.image_pixels[height_index], sizeof(pixel), image->info->biWidth, imageFile);
        fwrite(padding, ONE_BYTE, padding_size, imageFile);
    }

    fclose(imageFile);
}

ANSWER check_sizes(int all_width, int all_height, int start_x, int start_y, int rect_width, int rect_height) {
    if (all_width < start_x + rect_width) {
        return FAIL_WIDTH;
    }
    if (all_height < start_y + rect_height) {
        return FAIL_HEIGHT;
    }
    return SUCCESS;
}

bmp_image turn_image_right(const bmp_image *old_image, uint32_t start_x, uint32_t start_y, uint32_t rect_width, uint32_t rect_height) {

    bmp_image new_image;

    uint32_t x_0 = start_x;
    uint32_t y_0 = old_image->info->biHeight - start_y - rect_height; // cause pixels are upside down

    // bmp_header_data change
    new_image.header = (bmp_header *)malloc(sizeof(bmp_header));
    if (!new_image.header) {
        printf("ERROR: memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    memcpy(new_image.header, old_image->header, sizeof(bmp_header));
    uint32_t actual_width_in_bytes = ceil_to_fourth(rect_height * sizeof(pixel));
    new_image.header->size = new_image.header->image_data_offset + rect_width * actual_width_in_bytes;

    // image info change
    new_image.info = (image_header *)malloc(sizeof(image_header));
    if (!new_image.info) {
        printf("ERROR: memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    memcpy(new_image.info, old_image->info, sizeof(image_header));
    new_image.info->biHeight = rect_width;
    new_image.info->biWidth = rect_height;
    new_image.info->biSizeImage = new_image.header->size - new_image.header->image_data_offset;

    // image data change
    new_image.image.width = new_image.info->biWidth;
    new_image.image.height = new_image.info->biHeight;

    new_image.image.image_pixels = (pixel **)malloc(new_image.image.height * sizeof(pixel *));
    if (!new_image.image.image_pixels) {
        printf("ERROR: memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    new_image.image.image_pixels[0] = (pixel *)malloc(new_image.image.height * new_image.image.width * sizeof(pixel));
    if (!new_image.image.image_pixels[0]) {
        printf("ERROR: memory allocation failed!");

        exit(EXIT_FAILURE);
    }
    for (uint32_t row_in_new = 0; row_in_new < new_image.image.height; row_in_new++) {
        if (row_in_new != 0) new_image.image.image_pixels[row_in_new] =
                new_image.image.image_pixels[row_in_new - 1] + new_image.image.width;

        for (uint32_t column_in_new = 0; column_in_new < new_image.image.width; column_in_new++) {
            new_image.image.image_pixels[row_in_new][column_in_new] =
                    old_image->image.image_pixels[y_0 + column_in_new][x_0 + rect_width - 1 - row_in_new];
        }
    }
    return new_image;
}

void free_bmp_image(bmp_image image) {
    free(image.image.image_pixels[0]);

    free(image.image.image_pixels);

    free(image.header);
    free(image.info);
}