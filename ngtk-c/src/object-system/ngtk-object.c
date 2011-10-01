/*
 * ngtk-object.c
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

#include "../utils/ngtk-utils.h"
#include "ngtk-object.h"

#include <string.h>

static void append_listener (NGtkList *listeners, const char *signal, NGtkListener listener, void *user_data);
static void clear_listeners (NGtkList *listeners);
static void emit_signal     (void *src, NGtkList *listeners, const char *signal, void *sigdata);

static void attach (NGtkObject *obj, NGtkInterface *in);
static void detach (NGtkObject *obj, NGtkInterface *in);

static void object_free_real (NGtkObject *obj);

#define LOCKED   TRUE
#define UNLOCKED FALSE

NGtkObject* ngtk_object_new ()
{
	int i;
	NGtkObject *obj = ngtk_new (NGtkObject);
	ngtk_assert (obj);

	obj->interface_mask = 0;

	for (i = 0; i < NGTK_MAX_INTERFACES; i++)
		obj->interfaces[i] = NULL;

	obj->direct_ref_count = 1;    /* We will return one ref */

	ngtk_list_init (&obj->listeners);

	ngtk_list_init (&obj->destructors);

	obj->double_free_lock = UNLOCKED;

	return obj;
}

NGtkInterface* ngtk_interface_new (NGtkObject *obj, NGtkType type)
{
	int i;
	NGtkInterface *in = ngtk_new (NGtkInterface);

	in->type = type;

	for (i = 0; i < NGTK_MAX_INTERFACE_IMP_LEVELS; i++)
	{
		in->imp_data[i] = NULL;
		in->imp_data_free[i] = NULL;
		in->imp_destruct[i] = NULL;
	}

	in->functions = NULL;
	in->functions_free = NULL;

	ngtk_list_init (&in->listeners);

	/* The attach function wants to know the object is NULL. So if we
	 * don't want to depend on uninitialized memory, we must set the
	 * object first */
	in->object = NULL;
	attach (obj, in);

	return in;
}

static void attach (NGtkObject *obj, NGtkInterface *in)
{
	ngtk_assert (obj);
	ngtk_assert (in);

	ngtk_assert (! ngtk_object_is_a (obj, in->type));
	ngtk_assert (in->object == NULL);

	obj->interface_mask       |= NGTK_BIT_MASK (in->type);
	obj->interfaces[in->type]  = in;

	in->object                 = obj;
}

static void detach (NGtkObject *obj, NGtkInterface *in)
{
	ngtk_assert (obj);
	ngtk_assert (in);

	ngtk_assert (ngtk_object_cast (obj, in->type) == in);
	ngtk_assert (in->object == obj);

	obj->interface_mask       ^= NGTK_BIT_MASK (in->type);
	obj->interfaces[in->type]  = NULL;

	in->object                 = NULL;
}

/* To be used by external destructors of the objects. When a destructor
 * wants to finish a certain interface of an object, this is what he
 * should call */
void ngtk_interface_detach_and_free (NGtkInterface *in)
{
	int i;
	ngtk_assert (in != NULL);
	ngtk_assert (in->object != NULL);

	for (i = NGTK_MAX_INTERFACE_IMP_LEVELS - 1; i >= 0 ; i--)
	{
		if (in->imp_destruct[i] != NULL)
		{
			in->imp_destruct[i] (in->object);
			in->imp_destruct[i] = NULL;
		}
		if (in->imp_data[i] && in->imp_data_free[i])
		{
			in->imp_data_free[i] (in->imp_data[i]);
			in->imp_data_free[i] = NULL;
			in->imp_data[i] = NULL;
		}
	}

	if (in->functions && in->functions_free)
		in->functions_free (in->functions);

	clear_listeners (& in->listeners);

	detach (in->object, in);

	ngtk_free (in);
}

static void object_free_real (NGtkObject *obj)
{
	NGtkListNode *iter;
	int i;

	ngtk_assert (obj != NULL);

	ngtk_list_foreach (iter, &obj->destructors)
		((NGtkDestructor) iter->data) (obj);

	/* Now make sure the object was cleaned succesfully */
	for (i = 0; i < NGTK_MAX_INTERFACES; i++)
		ngtk_assert (obj->interfaces[i] == NULL);

	ngtk_assert (obj->interface_mask == 0);

	/* Now, clean the remaining stuff */
	clear_listeners (& obj->listeners);
	ngtk_list_clear (& obj->destructors);
	ngtk_free (obj);
}

void ngtk_object_free (NGtkObject *obj)
{
	if (obj->double_free_lock == UNLOCKED)
	{
		obj->double_free_lock = LOCKED;
		object_free_real (obj);
	}
}

int ngtk_object_is_a (NGtkObject* obj, NGtkType type)
{
	/* Sanity check */
	ngtk_assert (obj != NULL);
	return ((obj->interface_mask) & NGTK_BIT_MASK(type)) != 0;
}

int ngtk_interface_is_a (NGtkInterface* in, NGtkType type)
{
	ngtk_assert (in != NULL);
	if (in->type == type) return TRUE;

	/* Sanity check */
	ngtk_assert (in->object != NULL);
	return ngtk_object_is_a (in->object, type);
}

NGtkInterface* ngtk_object_cast (NGtkObject* obj, NGtkType type)
{
	ngtk_assert (ngtk_object_is_a (obj, type));
	return obj->interfaces[type];
}

NGtkInterface* ngtk_interface_cast (NGtkInterface* in, NGtkType type)
{
	ngtk_assert (in != NULL);
	if (in->type == type) return in;

	/* Sanity check */
	ngtk_assert (in->object!= NULL);
	return ngtk_object_cast (in->object, type);
}

NGtkObject* ngtk_interface_get_object (NGtkInterface *in)
{
	ngtk_assert (in);
	return in->object;
}

void ngtk_object_ref (NGtkObject* obj)
{
	++ obj->direct_ref_count;
}

void ngtk_object_unref (NGtkObject* obj)
{
	ngtk_assert (-- obj->direct_ref_count >= 0);
	if (obj->direct_ref_count == 0)
		ngtk_object_free (obj);
}

void ngtk_object_push_destructor (NGtkObject *obj, NGtkDestructor dest)
{
	ngtk_assert (obj != NULL);
	ngtk_assert (dest != NULL);

	ngtk_list_prepend (& obj->destructors, dest);
}

static void append_listener (NGtkList *listeners, const char *signal, NGtkListener listener, void *user_data)
{
	NGtkListenerInfo *i = ngtk_new (NGtkListenerInfo);
	i->signame = signal;
	i->func = listener;
	i->lisdata = user_data;
	ngtk_list_append (listeners, i);
}

static void clear_listeners (NGtkList *listeners)
{
	ngtk_list_clear_with_free_func (listeners, ngtk_free);
}

static void emit_signal (void *src, NGtkList *listeners, const char *signal, void *sigdata)
{
	NGtkListNode *iter;
	ngtk_list_foreach (iter, listeners)
	{
		NGtkListenerInfo *li = (NGtkListenerInfo*) iter->data;
		if (li->signame == NGTK_ALL_SIGNALS || strcmp (li->signame, signal) == 0)
			li->func (src, signal, sigdata, li->lisdata);
	}
}

void ngtk_object_connect_to (NGtkObject *obj, const char* signal, NGtkListener listener, void *user_data)
{
	append_listener (&obj->listeners, signal, listener, user_data);
}

void ngtk_object_send_signal (NGtkObject* obj, const char* signal, void *sigdata)
{
	emit_signal (obj, &obj->listeners, signal, sigdata);
}

void ngtk_interface_connect_to (NGtkInterface *in, const char* signal, NGtkListener listener, void *user_data)
{
	append_listener (&in->listeners, signal, listener, user_data);
}

void ngtk_interface_send_signal (NGtkInterface* in, const char* signal, void *sigdata, int also_object)
{
	emit_signal (in, &in->listeners, signal, sigdata);
	if (also_object && in->object)
		ngtk_object_send_signal (in->object, signal, sigdata);
}
