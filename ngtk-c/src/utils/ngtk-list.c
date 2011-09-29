#include <stdlib.h>

#include "ngtk-utils.h"

NGtkListNode* ngtk_list_node_new (void* data)
{
	NGtkListNode *node = ngtk_new (NGtkListNode);
	node->data = data;
	node->prev = node->next = NULL;
	return node;
}

void ngtk_list_node_free (NGtkListNode *node)
{
	ngtk_free (node);
}

void ngtk_list_node_unlink_from_next (NGtkListNode *node)
{
	if (node->next == NULL)
		return;

	ngtk_assert (node->next->prev == node);
	node->next->prev = NULL;
	node->next = NULL;
}

void ngtk_list_node_unlink_from_prev (NGtkListNode *node)
{
	if (node->prev == NULL)
		return;

	ngtk_assert (node->prev->next == node);
	node->prev->next = NULL;
	node->prev = NULL;
}

void ngtk_list_node_link (NGtkListNode *first, NGtkListNode *second)
{
	ngtk_assert (! first  ||  first->next == NULL);
	ngtk_assert (! second || second->prev == NULL);

	if (first != NULL) first->next = second;
	if (second != NULL) second->prev = first;
}

NGtkList* ngtk_list_new ()
{
	NGtkList *list = ngtk_new (NGtkList);
	list->first = list->last = NULL;
	return list;
}

NGtkListNode* ngtk_list_find (const NGtkList *list, void *data)
{
	NGtkListNode *iter;

	ngtk_list_foreach(iter, list)
		if (iter->data == data)
			return iter;

	return NULL;
}

int ngtk_list_contains (const NGtkList *list, void *data)
{
	return ngtk_list_find (list, data) != NULL;
}

int ngtk_list_remove (NGtkList *list, void *data)
{
	return ngtk_list_remove_node (list, ngtk_list_find (list, data));
}

int ngtk_list_remove_node (NGtkList *list, NGtkListNode *node)
{
	NGtkListNode *prev, *next;

	if (node == NULL) return FALSE;

	prev = node->prev;
	next = node->next;

	ngtk_list_node_unlink_from_next (node);
	ngtk_list_node_unlink_from_prev (node);
	ngtk_list_node_link (prev, next);

	if (list->first == node)
		list->first = next;

	if (list->last == node)
		list->last = prev;

	ngtk_list_node_free (node);

	return TRUE;
}

void ngtk_list_append (NGtkList *list, void *data)
{
	NGtkListNode *nn = ngtk_list_node_new (data);
	if (list->first == NULL /* && list->last == NULL */)
	{
		list->first = list->last = nn;
	}
	else
	{
		ngtk_list_node_link (list->last, nn);
		list->last = nn;
	}
}

void ngtk_list_prepend (NGtkList *list, void *data)
{
	NGtkListNode *nn = ngtk_list_node_new (data);
	if (list->first == NULL /* && list->last == NULL */)
	{
		list->first = list->last = nn;
	}
	else
	{
		ngtk_list_node_link (nn, list->first);
		list->first = nn;
	}
}

void ngtk_list_free (NGtkList *list)
{
	NGtkListNode *iter, *next = NULL;

	for (iter = list->first; iter != NULL; iter = next)
	{
		next = iter->next;
		ngtk_list_node_free (iter);
	}
	
	ngtk_free (list);
}

int ngtk_list_is_empty (NGtkList *list)
{
	return list->first == NULL;
}
