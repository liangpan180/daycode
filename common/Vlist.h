/*
 * Vlist.h
 * void* list operation, can translate to any other type
 *
 */
#include <stdio.h>

typedef void* node_t;

typedef struct list_node {
	node_t data;
	node_t prev;
	node_t next;
} list_node_t;

#define LIST_HEAD list_node_t*

void list_insert_head(LIST_HEAD *head, list_node_t* node);
void list_insert_tail(LIST_HEAD *head, list_node_t* node);
void list_append_head(LIST_HEAD *dst, LIST_HEAD src);
void list_append_tail(LIST_HEAD *dst, LIST_HEAD src);
