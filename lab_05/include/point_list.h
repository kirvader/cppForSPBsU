#include "clist.h"
#ifndef LAB_05_POINTLIST_H
#define LAB_05_POINTLIST_H


typedef struct point {
    int x, y;
    struct intrusive_node node;
} point;

point *get_point(intrusive_node *node);

void add_point(intrusive_list *user_list, int x, int y);

void remove_point(intrusive_list *user_list, int x, int y);

void show_all_points(intrusive_list *user_list);

void remove_all_points(intrusive_list *user_list);

static void print_point_to_file(intrusive_node *node, FILE *file, char *format);

static void print_point_to_txt(intrusive_node *node, void *file);

static void print_point_stdout(intrusive_node *node, void *format);

void print_points_by_format(intrusive_list *list, char *format);

static void print_number_to_bin(int number, FILE *file);

static void print_point_to_bin(intrusive_node *node, void *file);

static int read_next_int_from_bin(FILE *file);

void save_list_to_txt(intrusive_list *list, char *filename);

void read_list_from_txt(intrusive_list *list, char *filename);

void save_list_to_bin(intrusive_list *list, char *filename);

void read_list_from_bin(intrusive_list *list, char *filename);

static void length_count_iteration(intrusive_node *node, void *count);

int count(intrusive_list *list);


#endif