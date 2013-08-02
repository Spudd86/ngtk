/*
 * ngtk-list.c - Part of the NGtk library
 *
 * Copyright (c) 2011, Barak Itkin <lightningismyname at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NGtk nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
	if (list->first == NULL)
	{
		ngtk_assert (list->last == NULL);
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
	if (list->first == NULL)
	{
		ngtk_assert (list->last == NULL);
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
