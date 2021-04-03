#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bmp.h"

bool is_number(const char *string) {
    for (int index = 0; index < strlen(string); index++)
        if (!(string[index] >= '0' && string[index] <= '9'))
            return false;
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 8) {
        printf("Wrong quantity of args");
        return 0;
    }
    char *action_type = argv[1];
    char *input_filename = argv[2];
    char *output_filename = argv[3];
    if (strcmp(action_type, "crop-rotate") != 0) {
        return 0;
    }
    if (!is_number(argv[4])) {
        printf("start_x variable should be integer.");
        return 0;
    }
    int start_x = atoi(argv[4]);
    if (!is_number(argv[5])) {
        printf("start_y variable should be integer.");
        return 0;
    }
    int start_y = atoi(argv[5]);
    if (!is_number(argv[6])) {
        printf("width variable should be integer.");
        return 0;
    }
    int width = atoi(argv[6]);
    if (!is_number(argv[7])) {
        printf("height variable should be integer.");
        return 0;
    }
    int height = atoi(argv[7]);

    // image reading and checking for sizes
    bmp_image input_image = read_bmp_image(input_filename);

    ANSWER size_check = check_sizes(input_image.info->biWidth, input_image.info->biHeight, start_x, start_y, width, height);
    switch (size_check) {
        case (FAIL_WIDTH) :
            printf("Widths are wrong!");
            break;
        case (FAIL_HEIGHT) :
            printf("Heights are wrong!");
            break;
    }


    // cutting and turning a new image
    bmp_image new_image = turn_image_right(&input_image, start_x, start_y, width, height);

    // writing new image to another file
    write_bmp_image(output_filename, &new_image);


    // freedom for memory!
    free_bmp_image(input_image);
    free_bmp_image(new_image);

    return 0;
}