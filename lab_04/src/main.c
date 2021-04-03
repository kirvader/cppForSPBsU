#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "clist.h"

struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point(struct intrusive_list *user_list, int x, int y) {
    struct point *point_to_add = malloc(sizeof(struct point));
    if (!point_to_add) {
        printf("ERROR: memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    point_to_add->x = x;
    point_to_add->y = y;
    add_node(user_list, &point_to_add->node);
}

void remove_point(struct intrusive_list *user_list, int x, int y) { // removes all (x, y) pairs
    struct intrusive_node *current_node = user_list->head;
    while (current_node != NULL) {
        struct point *data = container_of(current_node, struct point, node);

        struct intrusive_node *next_node = current_node->next;

        if ((data->x == x) && (data->y == y)) {
            remove_node(user_list, current_node);
            free(data);
        }

        current_node = next_node;
    }
}

void show_all_points(struct intrusive_list *user_list) {
    struct intrusive_node *current_node = user_list->head;
    while (current_node != NULL) {
        struct point *data = container_of(current_node, struct point, node);

        if (current_node != NULL)
            printf("(%d %d) ", data->x, data->y);
        else
            printf("(%d %d)", data->x, data->y);

        current_node = current_node->next;
    }
    printf("\n");
}

void remove_all_points(struct intrusive_list *user_list) {
    while (user_list->head != NULL) {
        struct point *data = container_of(user_list->head, struct point, node);

        remove_node(user_list, user_list->head);

        free(data);
    }
}


int main() {
    struct intrusive_list *intrusiveList = malloc(sizeof(struct intrusive_list));
    if (!intrusiveList) {
        printf("ERROR: memory allocation failed!");
        return -1;
    }

	init_list(intrusiveList);

	while (true) {
	    char request_type[100];
	    scanf("%100s", request_type);
	    if (strcmp(request_type, "add") == 0) {
            int x, y;
            scanf("%d %d\n", &x, &y);
	        add_point(intrusiveList, x, y);
	    } else if (strcmp(request_type, "rm") == 0) {
            int x, y;
            scanf("%d %d\n", &x, &y);
            remove_point(intrusiveList, x, y);
	    } else if (strcmp(request_type, "print") == 0) {
            show_all_points(intrusiveList);
	    } else if (strcmp(request_type, "rma") == 0) {
            remove_all_points(intrusiveList);
	    } else if (strcmp(request_type, "len") == 0) {
	        printf("%d\n", get_length(intrusiveList));
	    } else if (strcmp(request_type, "exit") == 0) {
	        break;
	    } else {
	        printf("Unknown command\n");
	    }
	}
	// free all points from list except first
	remove_all_points(intrusiveList);

	// free list
	free(intrusiveList);
    return 0;
}
