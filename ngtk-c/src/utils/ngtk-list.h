/*
 * ngtk-list.h
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

#ifndef __NGtk_list_h__
#define __NGtk_list_h__

#include "ngtk-misc-types.h"

typedef struct _ngtk_list_node {
	void *data;
	struct _ngtk_list_node* prev;
	struct _ngtk_list_node* next;
} NGtkListNode;

typedef struct {
	NGtkListNode *first;
	NGtkListNode *last;
} NGtkList;

#define NGTK_EMPTY_LIST_CONST { NULL, NULL }

typedef void (*NGtkListApplyFunc) (void *data);
typedef void (*NGtkListDataApplyFunc) (void *data, void *extra_data);

NGtkListNode* ngtk_list_node_new              (void* data);

void          ngtk_list_node_free             (NGtkListNode *node);

void          ngtk_list_node_unlink_from_next (NGtkListNode *node);

void          ngtk_list_node_unlink_from_prev (NGtkListNode *node);

void          ngtk_list_node_link             (NGtkListNode *first, NGtkListNode *second);

NGtkList*     ngtk_list_new                   ();

void          ngtk_list_init                  (NGtkList* list);

NGtkListNode* ngtk_list_find                  (const NGtkList *list, void *data);

int           ngtk_list_contains              (const NGtkList *list, void *data);

int           ngtk_list_remove                (NGtkList *list, void *data);

int           ngtk_list_remove_node           (NGtkList *list, NGtkListNode *node);

void          ngtk_list_append                (NGtkList *list, void *data);

void          ngtk_list_prepend               (NGtkList *list, void *data);

void          ngtk_list_free                  (NGtkList *list);

void          ngtk_list_clear_with_free_func  (NGtkList *list, NGtkFreeFunc func);

void          ngtk_list_clear                 (NGtkList *list);

int           ngtk_list_is_empty              (NGtkList *list);

/**
 * A read-only iterator on the list. This means you may not modify the
 * list structure while the iteration is in process (you may however
 * modify the list data).
 */
#define       ngtk_list_foreach(iter,list)    for ((iter) = (list)->first; (iter) != NULL; (iter) = (iter)->next)

#endif
