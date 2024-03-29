/*
 * ngtk-list.h - Part of the NGtk library
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

#ifndef __NGtk_list_h__
#define __NGtk_list_h__

#include "ngtk-misc-types.h"

/**
  * @defgroup NGtkListGroup Doubly Linked Lists
  * A two-sided doubly linked list of pointers
  * @{
  */

 /**
  * A node of the doubly linked list
  */
typedef struct _ngtk_list_node {
	void *data;                   /** < The data of the list node */
	struct _ngtk_list_node* prev; /** < The previous list node */
	struct _ngtk_list_node* next; /** < The next list node */
} NGtkListNode;

/**
 * The list struct itself
 */
typedef struct {
	NGtkListNode *first; /** < The first node of the list */
	NGtkListNode *last; /** < The last node of the list */
} NGtkList;


/**
 * The value to intialize NGtkList structs with
 */
#define NGTK_EMPTY_LIST_CONST { NULL, NULL }

/**
 * A function to apply on the data stored in each NGtkListNode
 */
typedef void (*NGtkListApplyFunc) (void *data);

/**
 * A function to apply on the data stored in each NGtkListNode, which
 * also accepts some additional data specified by the programmer
 */
typedef void (*NGtkListDataApplyFunc) (void *data, void *extra_data);

/**
 * Allocate a new NGtkListNode which is not connected to any other node,
 * and contains the given data pointer
 */
NGTK_EXPORT NGtkListNode* ngtk_list_node_new              (void* data);

NGTK_EXPORT void          ngtk_list_node_free             (NGtkListNode *node);

NGTK_EXPORT void          ngtk_list_node_unlink_from_next (NGtkListNode *node);

NGTK_EXPORT void          ngtk_list_node_unlink_from_prev (NGtkListNode *node);

NGTK_EXPORT void          ngtk_list_node_link             (NGtkListNode *first, NGtkListNode *second);

NGTK_EXPORT NGtkList*     ngtk_list_new                   ();

NGTK_EXPORT void          ngtk_list_init                  (NGtkList* list);

NGtkListNode* ngtk_list_find                  (const NGtkList *list, void *data);

NGTK_EXPORT int           ngtk_list_contains              (const NGtkList *list, void *data);

NGTK_EXPORT int           ngtk_list_remove                (NGtkList *list, void *data);

NGTK_EXPORT int           ngtk_list_remove_node           (NGtkList *list, NGtkListNode *node);

NGTK_EXPORT void          ngtk_list_append                (NGtkList *list, void *data);

NGTK_EXPORT void          ngtk_list_prepend               (NGtkList *list, void *data);

/**
 * Free all the memory associated with a given list. If the list is not
 * empty (i.e. it contains one or more list nodes) then it's contents
 * (the nodes) will also be freed. This function does NOT free the data
 * that was inserted to the list!
 *
 * For lists that were allocated statically (by declaring a variables of
 * type \ref NGtkList and not by ngtk_list_new), use \ref
 * ngtk_list_clear to free all the memory associated with the list
 */
NGTK_EXPORT void          ngtk_list_free                  (NGtkList *list);

/**
 * Similar to \ref ngtk_list_clear, but also calls the given
 * \ref NGtkFreeFunc on each element of the list before removing it from
 * the list. This can be used to free the data inserted to the list.
 */
NGTK_EXPORT void          ngtk_list_clear_with_free_func  (NGtkList *list, NGtkFreeFunc func);

/**
 * Empty a given list from all of it's contents. This will remoe all the
 * elements from the list, and free all of the memory used by the
 * \ref NGtkListNode structs that made it.
 *
 * This function does NOT free the data that was inserted to the list!
 */
NGTK_EXPORT void          ngtk_list_clear                 (NGtkList *list);

NGTK_EXPORT int           ngtk_list_is_empty              (const NGtkList *list);

NGTK_EXPORT NGtkList*     ngtk_list_duplicate             (const NGtkList *list);

/**
 * A read-only iterator on the list. This means you may not modify the
 * list structure while the iteration is in process (you may however
 * modify the list data).
 */
#define       ngtk_list_foreach(iter,list)    for ((iter) = (list)->first; (iter) != NULL; (iter) = (iter)->next)

/**
 * ATwo synchronized read-only iterators on two lists. This means you
 * may not modify the list structure while the iteration is in process
 * (you may however modify the list data).
 */

#define       ngtk_list_2foreach(iter1,list1,iter2,list2)    \
    for ((iter1) = (list1)->first, (iter2) = (list2)->first; \
	     (iter1) != NULL && (iter2 != NULL);                 \
         (iter1) = (iter1)->next, (iter2) = (iter2)->next)

/**
 * @}
 */
#endif
