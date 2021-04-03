#include "stddef.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

#ifndef LAB_04_CLIST_H
#define LAB_04_CLIST_H

struct intrusive_node {
	struct intrusive_node *next;
	struct intrusive_node *prev;
} intrusive_node;

struct intrusive_list {
    struct intrusive_node *head;
};

void init_list(struct intrusive_list *user_list);
void add_node(struct intrusive_list *user_list, struct intrusive_node *node_to_add);
void remove_node(struct intrusive_list *user_list, struct intrusive_node *node_to_remove);

int get_length(struct intrusive_list *user_list);

#endif
