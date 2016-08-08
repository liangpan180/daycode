/*
 * Vlist.c
 * void* list operation, can translate to any other type
 *
 */
#include "Vlist.h"

void list_insert_head(LIST_HEAD *head, list_node_t* node)
{
	if (!node)
		return;

	if (!*head) {
		*head = node;
		(*head)->prev = node;
		(*head)->next = NULL;
		return;
	}

	node->next = *head;
	node->prev = (*head)->prev;
	(*head)->prev = node;
	*head = node;
}

void list_insert_tail(LIST_HEAD *head, list_node_t* node)
{
	list_node_t* tmp;

	if (!node)
		return;

	if (!*head) {
		*head = node;
		(*head)->prev = node;
		(*head)->next = NULL;
		return;
	}

	node->prev = (*head)->prev;
	tmp = (*head)->prev;
	tmp->next = node;
	(*head)->prev = node;
}

void list_append_tail(LIST_HEAD *dst, LIST_HEAD src)
{
	list_node_t* tmp;

	if (!*dst) {
		*dst = src;
		return;
	}

	tmp = (*dst)->prev;
	tmp->next = src;
	(*dst)->prev = src->prev;
	src->prev = tmp;
}

void list_append_head(LIST_HEAD *dst, LIST_HEAD src)
{
	list_node_t* tmp;

	if (!*dst) {
		*dst = src;
		return;
	}

	tmp = src->prev;
	tmp->next = *dst;
	src->prev = (*dst)->prev;
	(*dst)->prev = tmp;

	*dst = src;
}
