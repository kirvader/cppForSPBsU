#include <stdlib.h>
#include <stdio.h>
#include "clist.h"

void init_list(struct intrusive_list *user_list) {
    user_list->head = NULL;
}

int get_length(struct intrusive_list *user_list) {
    struct intrusive_node *current_node = user_list->head;
    int size = 0;

    while (current_node != NULL) {
        current_node = current_node->next;
        size++;
    }

    return size;
}

void add_node(struct intrusive_list *user_list, struct intrusive_node *node_to_add) {
    struct intrusive_node *first_node = user_list->head;

    user_list->head = node_to_add;
    node_to_add->prev = NULL;
    node_to_add->next = first_node;

    if (first_node != NULL) {
        first_node->prev = node_to_add;
    }
}

void remove_node(struct intrusive_list *user_list, struct intrusive_node *node_to_remove) {
    struct intrusive_node *prev_node = node_to_remove->prev;
    struct intrusive_node *next_node = node_to_remove->next;

    if (next_node != NULL)
        next_node->prev = prev_node;

    if (prev_node != NULL)
        prev_node->next = next_node;
    else
        user_list->head = next_node;

    node_to_remove->prev = NULL;
    node_to_remove->next = NULL;

}
