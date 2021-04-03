#include "stddef.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

#ifndef LAB_05_CLIST_H
#define LAB_05_CLIST_H

typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
} intrusive_node;

typedef struct intrusive_list {
    intrusive_node *head;
} intrusive_list;

void init_list(intrusive_list *user_list);
void add_node(intrusive_list *user_list, intrusive_node *node_to_add);
void remove_node(intrusive_list *user_list, intrusive_node *node_to_remove);


int get_length(intrusive_list *user_list);
void reverse_intrusive_list(intrusive_list *user_list);

void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data);


#endif