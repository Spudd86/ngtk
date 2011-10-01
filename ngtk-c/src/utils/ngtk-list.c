/*
 * ngtk-list.c
 * (C) Barak Itkin <lightningismyname at gmail dot com>, 2011
 *
 * This file is part of NGtk.
 *
 * NGtk is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * NGtk is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with NGtk.  If not, see <http://www.gnu.org/licenses/>.
 */

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

void ngtk_list_init (NGtkList* list)
{
	list->first = list->last = NULL;
}

NGtkList* ngtk_list_new ()
{
	NGtkList *list = ngtk_new (NGtkList);
	ngtk_list_init (list);
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

void ngtk_list_clear_with_free_func  (NGtkList *list, NGtkFreeFunc func)
{
	NGtkListNode *iter, *next = NULL;

	for (iter = list->first; iter != NULL; iter = next)
	{
		next = iter->next;
		func (iter->data);
		ngtk_list_node_free (iter);
	}
}

void ngtk_list_clear (NGtkList *list)
{
	NGtkListNode *iter, *next = NULL;

	for (iter = list->first; iter != NULL; iter = next)
	{
		next = iter->next;
		ngtk_list_node_free (iter);
	}
}

void ngtk_list_free (NGtkList *list)
{
	ngtk_list_clear (list);
	ngtk_free (list);
}

int ngtk_list_is_empty (const NGtkList *list)
{
	return list->first == NULL;
}

NGtkList* ngtk_list_duplicate (const NGtkList *list)
{
	NGtkListNode *iter;
	NGtkList     *copy = ngtk_list_new ();

	ngtk_list_foreach (iter, list)
		ngtk_list_append (copy, iter->data);

	return copy;
}
