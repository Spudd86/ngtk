#ifndef __NGtk_list_h__
#define __NGtk_list_h__

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

NGtkListNode* ngtk_list_node_new              (void* data);

void          ngtk_list_node_free             (NGtkListNode *node);

void          ngtk_list_node_unlink_from_next (NGtkListNode *node);

void          ngtk_list_node_unlink_from_prev (NGtkListNode *node);

void          ngtk_list_node_link             (NGtkListNode *first, NGtkListNode *second);

NGtkList*     ngtk_list_new                   ();

NGtkListNode* ngtk_list_find                  (const NGtkList *list, void *data);

int           ngtk_list_contains              (const NGtkList *list, void *data);

int           ngtk_list_remove                (NGtkList *list, void *data);

int           ngtk_list_remove_node           (NGtkList *list, NGtkListNode *node);

void          ngtk_list_append                (NGtkList *list, void *data);

void          ngtk_list_prepend               (NGtkList *list, void *data);

void          ngtk_list_free                  (NGtkList *list);

int           ngtk_list_is_empty              (NGtkList *list);

/**
 * A read-only iterator on the list. This means you may not modify the
 * list structure while the iteration is in process (you may however
 * modify the list data).
 */
#define       ngtk_list_foreach(iter,list)    for ((iter) = (list)->first; (iter) != NULL; (iter) = (iter)->next)

#endif
