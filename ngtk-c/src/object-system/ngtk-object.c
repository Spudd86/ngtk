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

/* Gluing together an interface and an object is a one way operation,
 * which is not reversible for now to make things a bit more sane */
static void ngtk_object_detach (NGtkObject *obj, NGtkInterface *in);

static void append_listener (NGtkList *listeners, const char *signal, NGtkListener listener);
static void clear_listeners (NGtkList *listeners);
static void emit_signal     (void *src, NGtkList *listeners, const char *signal, NGtkValue *value);

NGtkObject* ngtk_object_new ()
{
	int i;
	NGtkObject *obj = ngtk_new (NGtkObject);

	obj->iBits = NGTK_TYPE_NONE;

	for (i = 0; i < NGTK_MAX_INTERFACES; i++)
		obj->iImps[i] = NULL;

	obj->d = NULL;
	obj->d_free = NULL;

	obj->direct_ref_count = 1; /* We will return one ref */
	obj->interfaces_ref_count = 0; /* No interfaces, so no references to
	                                * them */
	ngtk_list_init (&obj->listeners);
	
	return obj;
}

NGtkInterface* ngtk_interface_new (NGtkType iType)
{
	int i;
	NGtkInterface *in = ngtk_new (NGtkInterface);

	in->obj = NULL;

	in->iType = iType;

	for (i = 0; i < NGTK_MAX_INTERFACE_IMP_LEVELS; i++)
	{
		in->d[i] = NULL;
		in->d_free[i] = NULL;
	}

	in->f = NULL;
	in->f_free = NULL;

	in->ref_count = 0;
	ngtk_list_init (&in->listeners);
	
	return in;
}

int ngtk_object_is_a (NGtkObject* obj, NGtkType iType)
{
	/* Sanity check */
	ngtk_assert (obj != NULL);
	return ((obj->iBits) & NGTK_BIT_MASK(iType)) != 0;
}

int ngtk_interface_is_a (NGtkInterface* in, NGtkType iType)
{
	if (in->iType == iType) return TRUE;
	/* Sanity check */
	ngtk_assert (in->obj != NULL);
	return ngtk_object_is_a (in->obj, iType);
}

NGtkInterface* ngtk_object_cast (NGtkObject* obj, NGtkType iType)
{
	ngtk_assert (ngtk_object_is_a (obj, iType));
	return obj->iImps[iType];
}

NGtkInterface* ngtk_interface_cast (NGtkInterface* in, NGtkType iType)
{
	if (in->iType == iType) return in;
	/* Sanity check */
	ngtk_assert (in->obj != NULL);
	return ngtk_object_cast (in->obj, iType);
}

void ngtk_interface_free (NGtkInterface *in)
{
	NGtkValue value;
	int i;
	ngtk_assert (in != NULL);

	value.type = NGTK_VALUE_P_VOID;
	value.val.v_pvoid = in;
	ngtk_interface_send_signal (in, "object::destroy", &value, TRUE);
	
	clear_listeners (& in->listeners);

	if (in->obj != NULL)
	{
		ngtk_object_detach (in->obj, in);
	}

	for (i = 0; i < NGTK_MAX_INTERFACE_IMP_LEVELS; i++)
	{
		if (in->d[i] && in->d_free[i])
			in->d_free[i] (in->d[i]);
	}

	if (in->f && in->f_free)
		in->f_free (in->f);

	ngtk_free (in);
}

void ngtk_object_free (NGtkObject* obj)
{
	NGtkValue value;
	int i;

	ngtk_assert (obj != NULL);

	value.type = NGTK_VALUE_P_VOID;
	value.val.v_pvoid = obj;
	ngtk_object_send_signal (obj, "object::destroy", &value);
	
	if (obj->d && obj->d_free)
		obj->d_free (obj->d);

	for (i = 0; i < NGTK_MAX_INTERFACES; i++)
		if (obj->iImps[i])
			ngtk_object_detach (obj, obj->iImps[i]);

	/* The interfaces may bug the listeners a bit, so free only when
	 * done with them */
	clear_listeners (& obj->listeners);

	ngtk_free (obj);
}

NGtkObject* ngtk_interface_get_object (NGtkInterface *in)
{
	ngtk_assert (in);
	return in->obj;
}

void ngtk_object_implement (NGtkObject *obj, NGtkInterface *in)
{
	NGtkValue temp;
	ngtk_assert (obj);
	ngtk_assert (in);
	ngtk_assert (in->iType != NGTK_TYPE_NONE);
	ngtk_assert (in->obj == NULL);

	obj->iBits                |= NGTK_BIT_MASK (in->iType);
	obj->iImps[in->iType]      = in;
	obj->interfaces_ref_count += in->ref_count;
	in->obj                    = obj;

	ngtk_interface_ref (in);

	temp.type = NGTK_VALUE_P_VOID;
	temp.val.v_pvoid = in;
	ngtk_object_send_signal (obj, "object::implement", &temp);
	temp.val.v_pvoid = obj;
	ngtk_interface_send_signal (in, "object::implement", &temp, FALSE);
}

/* For now, detaching interfaces is only an internal operation that
 * happens when freeing an interface. Nevertheless, write code which is
 * prepared for the day where this can happen externally */
void ngtk_object_detach (NGtkObject *obj, NGtkInterface *in)
{
	NGtkValue value;
	ngtk_assert (obj);
	ngtk_assert (in);
	ngtk_assert (in->iType != NGTK_TYPE_NONE);
	ngtk_assert (in->obj == obj);
	ngtk_assert (ngtk_object_is_a (obj, in->iType));
	ngtk_assert (ngtk_object_cast (obj, in->iType) == in);

	value.type = NGTK_VALUE_P_VOID;
	value.val.v_pvoid = in;
	ngtk_object_send_signal (obj, "object::detach", &value);
	value.val.v_pvoid = obj;
	ngtk_interface_send_signal (in, "object::detach", &value, FALSE);

	/* To flip a bit, XOR with it's bit mask */
	obj->iBits                ^= NGTK_BIT_MASK (in->iType);
	obj->iImps[in->iType]      = NULL;
	obj->interfaces_ref_count -= in->ref_count;
	in->obj                    = NULL;
	
	ngtk_interface_unref (in);
}

void ngtk_object_ref (NGtkObject* obj)
{
	++ obj->direct_ref_count;
}

void ngtk_object_unref (NGtkObject* obj)
{
	ngtk_assert (-- obj->direct_ref_count >= 0);
	if (obj->direct_ref_count == 0 && obj->interfaces_ref_count == 0)
		ngtk_object_free (obj);
}

void ngtk_interface_ref (NGtkInterface* in)
{
	++ in->ref_count;
	if (in->obj != NULL)
		++ in->obj->interfaces_ref_count;
}

void ngtk_interface_unref (NGtkInterface* in)
{
	ngtk_assert (-- in->ref_count >= 0);

	if (in->obj != NULL)
		-- in->obj->interfaces_ref_count;
	
	/* If no reference, not from an object and not externally then free
	 * the interface implementation */
	if (in->ref_count == 0)
	{
		ngtk_assert (in->obj == NULL); /* The ref count should include
		                                * the object ref */
		ngtk_interface_free (in);
	}
}

static void append_listener (NGtkList *listeners, const char *signal, NGtkListener listener)
{
	NGtkListenerInfo *i = ngtk_new (NGtkListenerInfo);
	i->signame = signal;
	i->func = listener;
	ngtk_list_append (listeners, i);
}

static void clear_listeners (NGtkList *listeners)
{
	ngtk_list_clear_with_free_func (listeners, ngtk_free);
}

static void emit_signal (void *src, NGtkList *listeners, const char *signal, NGtkValue *value)
{
	NGtkListNode *iter;
	ngtk_list_foreach (iter, listeners)
	{
		NGtkListenerInfo *li = (NGtkListenerInfo*) iter->data;
		if (li->signame == NGTK_ALL_SIGNALS || strcmp (li->signame, signal) == 0)
			li->func (src, signal, value);
	}
}

void ngtk_object_connect_to (NGtkObject *obj, const char* signal, NGtkListener listener)
{
	append_listener (&obj->listeners, signal, listener);
}

void ngtk_object_send_signal (NGtkObject* obj, const char* signal, NGtkValue *data)
{
	emit_signal (obj, &obj->listeners, signal, data);
}

void ngtk_interface_connect_to (NGtkInterface *in, const char* signal, NGtkListener listener)
{
	append_listener (&in->listeners, signal, listener);
}

void ngtk_interface_send_signal (NGtkInterface* in, const char* signal, NGtkValue *data, int also_object)
{
	emit_signal (in, &in->listeners, signal, data);
	if (also_object && in->obj)
		ngtk_object_send_signal (in->obj, signal, data);
}
