#include <stdint.h>


#ifndef HW_01_BMP_H
#define HW_01_BMP_H

#pragma pack(push, 1)
typedef struct bmp_header {
    uint16_t name;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t image_data_offset;
} bmp_header;

typedef struct image_header {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPixPerMeter;
    uint32_t biYPixPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} image_header;

typedef struct pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel;

typedef struct image_data {
    uint32_t width;
    uint32_t height;
    pixel **image_pixels;
} image_data;
#pragma pack(pop)

typedef struct bmp_image {
    bmp_header *header;
    image_header *info;
    image_data image;
} bmp_image;

typedef enum ANSWER {
    SUCCESS,
    FAIL_HEIGHT,
    FAIL_WIDTH
} ANSWER;

static uint32_t get_addition_bytes_quantity(uint32_t number);
bmp_image read_bmp_image(const char *input_filename);
void write_bmp_image(const char *output_filename, const bmp_image *image);
ANSWER check_sizes(int all_width, int all_height, int start_x, int start_y, int rect_width, int rect_height);
bmp_image turn_image_right(const bmp_image *old_image, uint32_t start_x, uint32_t start_y, uint32_t rect_width, uint32_t rect_height);
void free_bmp_image(bmp_image image);

#endif //HW_01_BMP_H
