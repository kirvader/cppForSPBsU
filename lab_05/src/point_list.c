
#include <stdlib.h>
#include <stdio.h>
#include "point_list.h"

/// CONSTANTS

const int ONE_BYTE = 8;
const int MAX_VALUE = 5000000;
const int BYTES_IN_NUMBER = 3;


///WORKING WITH LIST POINTS

point *get_point(intrusive_node *node) {
    return container_of(node, point, node);
}

void add_point(intrusive_list *user_list, int x, int y) {
    point *point_to_add = malloc(sizeof(point));
    if (!point_to_add) {
        printf("ERROR: memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    point_to_add->x = x;
    point_to_add->y = y;
    add_node(user_list, &point_to_add->node);
}

void remove_point(intrusive_list *user_list, int x, int y) { // removes all (x, y) pairs
    intrusive_node *current_node = user_list->head;
    while (current_node != NULL) {
        point *data = get_point(current_node);
        intrusive_node *next_node = current_node->next;
        if ((data->x == x) && (data->y == y)) {
            remove_node(user_list, current_node);
            free(data);
        }
        current_node = next_node;
    }
}

void show_all_points(intrusive_list *user_list) {
    intrusive_node *current_node = user_list->head;
    while (current_node != NULL) {
        point *data = get_point(current_node);
        if (current_node != NULL)
            printf("(%d %d) ", data->x, data->y);
        else
            printf("(%d %d)", data->x, data->y);
        current_node = current_node->next;
    }
    printf("\n");
}

void remove_all_points(intrusive_list *user_list) {
    while (user_list->head != NULL) {
        point *data = get_point(user_list->head);
        remove_node(user_list, user_list->head);
        free(data);
    }
}


/// PRINTING

static void print_point_to_file(intrusive_node *node, FILE *file, char *format) {
    point *data = get_point(node);
    fprintf(file, format, data->x, data->y);
}

static void print_point_to_txt(intrusive_node *node, void *file) {
    print_point_to_file(node, (FILE *)file, "%d %d\n");
}

static void print_point_stdout(intrusive_node *node, void *format) {
    print_point_to_file(node, stdout, ((char *)format));
}

void print_points_by_format(intrusive_list *list, char *format) {
    apply(list, print_point_stdout, format);
    putchar('\n');
}

static void print_number_to_bin(int number, FILE *file) {
    if (number < 0)
        number = (((1 << (BYTES_IN_NUMBER * ONE_BYTE)) - 1) ^ (number * (-1))) + 1;
    unsigned char *number_bytes = (unsigned char *)&number;
    fwrite(number_bytes, sizeof(char), BYTES_IN_NUMBER, file);
}

static void print_point_to_bin(intrusive_node *node, void *file) {
    point *data = get_point(node);
    print_number_to_bin(data->x, (FILE *)file);
    print_number_to_bin(data->y, (FILE *)file);
}

/// READING

static int read_next_int_from_bin(FILE *file) {
    int number = 0;

    if (fread(&number, BYTES_IN_NUMBER, 1, file) != 1) return MAX_VALUE + 1;

    // обработка отрицательного
    if (number > MAX_VALUE) {
        number = ((1 << (BYTES_IN_NUMBER * ONE_BYTE)) - 1) ^ (number - 1);
        number *= -1;
    }

    return number;
}

void read_list_from_txt(intrusive_list *list, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("can't open file %s", filename);
        exit(EXIT_FAILURE);
    }
    int x, y;
    while (fscanf(file, "%d %d", &x, &y) != EOF) {
        add_point(list, x, y);
    }
    reverse_intrusive_list(list);
    fclose(file);
}

void read_list_from_bin(intrusive_list *list, char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("can't open file %s", filename);
        exit(EXIT_FAILURE);
    }
    int x, y;
    while ((x = read_next_int_from_bin(file)) != MAX_VALUE + 1) { // value from text
        y = read_next_int_from_bin(file);
        add_point(list, x, y);
    }
    reverse_intrusive_list(list);
    fclose(file);
}

/// SAVING

void save_list_to_txt(intrusive_list *list, char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("can't open file %s", filename);
        exit(EXIT_FAILURE);
    }
    apply(list, print_point_to_txt, file);
    fclose(file);
}

void save_list_to_bin(intrusive_list *list, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("can't open file %s", filename);
        exit(EXIT_FAILURE);
    }
    apply(list, print_point_to_bin, file);
    fclose(file);
}

/// LENGTH COUNTING

void length_count_iteration(intrusive_node *node, void *count) {
    ++(*(int *)count);
}

int count(intrusive_list *list) {
    int count = 0;
    apply(list, length_count_iteration, &count);
    return count;
}
