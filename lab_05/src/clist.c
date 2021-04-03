#include <stdlib.h>
#include <stdio.h>
#include "clist.h"

void init_list(intrusive_list *user_list) {
    user_list->head = NULL;
}

int get_length(intrusive_list *user_list) {
    intrusive_node *current_node = user_list->head;
    int size = 0;

    while (current_node != NULL) {
        current_node = current_node->next;
        size++;
    }

    return size;
}

void add_node(intrusive_list *user_list, intrusive_node *node_to_add) {
    intrusive_node *first_node = user_list->head;

    user_list->head = node_to_add;
    node_to_add->prev = NULL;
    node_to_add->next = first_node;

    if (first_node != NULL) {
        first_node->prev = node_to_add;
    }
}

void remove_node(intrusive_list *user_list, intrusive_node *node_to_remove) {
    intrusive_node *prev_node = node_to_remove->prev;
    intrusive_node *next_node = node_to_remove->next;

    if (next_node != NULL)
        next_node->prev = prev_node;

    if (prev_node != NULL)
        prev_node->next = next_node;
    else
        user_list->head = next_node;

    node_to_remove->prev = NULL;
    node_to_remove->next = NULL;

}

void apply(intrusive_list *user_list, void (*op)(intrusive_node *, void *), void *data) {
    intrusive_node *current_node = user_list->head;
    while (current_node != NULL) {
        op(current_node, data);
        current_node = current_node->next;
    }
}

static intrusive_node *get_last_node(intrusive_list *user_list) {
    intrusive_node *current_node = user_list->head;
    if (current_node == NULL) return NULL;

    while (current_node->next != NULL) current_node = current_node->next;
    return current_node;
}


void reverse_intrusive_list(intrusive_list *user_list) {
    intrusive_node *current_node = get_last_node(user_list);
    if (current_node == NULL) return;
    user_list->head = current_node;
    while (current_node != NULL) {
        intrusive_node *prev_node = current_node->prev;

        intrusive_node *swap_help = current_node->prev;
        current_node->prev = current_node->next;
        current_node->next = swap_help;

        current_node = prev_node;
    }
}
