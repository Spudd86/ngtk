/*
 * ngtk-basic-backend.c - Part of the NGtk library
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
#include <stdio.h>
#include "ngtk-basic-backend.h"

static void simple_destroy_backend_interface (NGtkObject *obj);

NGtkBackendI* ngtk_basic_backend_create_interface (NGtkObject *obj)
{
	NGtkInterface *in = ngtk_interface_new (obj, NGTK_BACKEND_TYPE);
	NGtkBasicBackendD *bbd;

	in->imp_data[0] = bbd = ngtk_new (NGtkBasicBackendD);
	bbd->root_window = NULL;
	bbd->focus_holder = NULL;
	bbd->should_quit = FALSE;
	bbd->initialized = FALSE;
	ngtk_list_init (&bbd->all_components);
	in->imp_data_free[0] = ngtk_basic_backend_d_free;

	in->functions = ngtk_new (NGtkBackendF);
	NGTK_BACKEND_I2F (in) -> init = NULL;
	NGTK_BACKEND_I2F (in) -> start_main_loop = NULL;
	NGTK_BACKEND_I2F (in) -> quit_main_loop = ngtk_basic_backend_quit_main_loop;
	NGTK_BACKEND_I2F (in) -> quit = NULL;

	NGTK_BACKEND_I2F (in) -> create_root_window = NULL;
	NGTK_BACKEND_I2F (in) -> create_button = NULL;
	NGTK_BACKEND_I2F (in) -> create_label = NULL;
	NGTK_BACKEND_I2F (in) -> create_text_entry = NULL;

	NGTK_BACKEND_I2F (in) -> get_focus_holder = ngtk_basic_backend_get_focus_holder;
	NGTK_BACKEND_I2F (in) -> set_focus_holder = ngtk_basic_backend_set_focus_holder;
	NGTK_BACKEND_I2F (in) -> focus_to_next = ngtk_basic_backend_focus_to_next;

	NGTK_BACKEND_I2F (in) -> get_root_window = ngtk_basic_backend_get_root_window;

	NGTK_BACKEND_I2F (in) -> print = ngtk_basic_backend_print;
	NGTK_BACKEND_I2F (in) -> debug = ngtk_basic_backend_debug;
	NGTK_BACKEND_I2F (in) -> error = ngtk_basic_backend_error;

	in->functions_free = ngtk_free;

	ngtk_object_push_destructor (obj, simple_destroy_backend_interface);

	return in;
}

static void simple_destroy_backend_interface (NGtkObject *obj)
{
	ngtk_interface_detach_and_free (ngtk_object_cast (obj, NGTK_BACKEND_TYPE));
}

void ngtk_basic_backend_d_free (void *d)
{
	NGtkBasicBackendD *d_real = (NGtkBasicBackendD*) d;
//	ngtk_list_clear_with_free_func (&d_real->all_components, (NGtkFreeFunc) ngtk_object_unref);
	ngtk_free (d_real);
}

void ngtk_basic_backend_call_after_init (NGtkBasicBackend *self)
{
	ngtk_assert (! NGTK_BASIC_BACKEND_O2D (self) -> initialized);
	NGTK_BASIC_BACKEND_O2D (self) -> initialized = TRUE;
}

void ngtk_basic_backend_call_before_start_main_loop (NGtkBasicBackend *self)
{
	NGtkContainer *root_window;

	ngtk_assert (NGTK_BASIC_BACKEND_O2D (self) -> initialized);

	root_window = NGTK_BASIC_BACKEND_O2D (self) -> root_window;
	ngtk_component_set_visible (root_window, TRUE);
	ngtk_component_set_enabled (root_window, TRUE);

	if (ngtk_backend_get_focus_holder (self) == NULL)
		ngtk_backend_set_focus_holder (self, root_window);
}

int ngtk_basic_backend_should_quit (NGtkBasicBackend *self)
{
	ngtk_assert (NGTK_BASIC_BACKEND_O2D (self) -> initialized);
	return NGTK_BASIC_BACKEND_O2D (self) -> should_quit;
}

void ngtk_basic_backend_quit_main_loop (NGtkBasicBackend *self)
{
	ngtk_assert (NGTK_BASIC_BACKEND_O2D (self) -> initialized);
	NGTK_BASIC_BACKEND_O2D (self) -> should_quit = TRUE;
}


NGtkComponent* ngtk_basic_backend_get_focus_holder (NGtkBasicBackend *self)
{
	return NGTK_BASIC_BACKEND_O2D (self) -> focus_holder;
}

int ngtk_basic_backend_can_focus_on (NGtkBasicBackend *self, NGtkComponent *new_focus)
{
	ngtk_assert (ngtk_object_is_a (self, NGTK_BACKEND_TYPE));
	ngtk_assert (ngtk_object_is_a (new_focus, NGTK_COMPONENT_TYPE));
	return (   ngtk_component_get_visible (new_focus)
	        && ngtk_component_get_enabled (new_focus)
	        && ngtk_component_get_focusable (new_focus) )
	       || new_focus == NGTK_BASIC_BACKEND_O2D (self) -> root_window;
}

int ngtk_basic_backend_set_focus_holder (NGtkBasicBackend *self, NGtkComponent* new_focus)
{

	if (ngtk_basic_backend_can_focus_on (self, new_focus))
	{
		NGtkComponent *old_focus = NGTK_BASIC_BACKEND_O2D (self) -> focus_holder;
		NGTK_BASIC_BACKEND_O2D (self) -> focus_holder = new_focus;
		if (old_focus != NULL) ngtk_component_redraw (old_focus);
		ngtk_component_redraw (new_focus);
		return TRUE;
	}
	return FALSE;
}

static NGtkComponent* find_first_focus (NGtkBasicBackend *self, NGtkComponent *comp)
{
	if (ngtk_basic_backend_can_focus_on (self, comp))
		return comp;
	else if (ngtk_object_is_a (comp, NGTK_COMPONENT_TYPE))
	{
		NGtkList *children = ngtk_container_get_children (comp);
		NGtkListNode *iter;

		ngtk_list_foreach (iter, children)
		{
			NGtkComponent *child = (NGtkComponent *)iter->data;
			NGtkComponent *new_focus = find_first_focus (self, child);
			if (new_focus)
				return new_focus;
		}
	}

	return NULL;
}
NGtkComponent* ngtk_basic_backend_focus_to_next (NGtkBasicBackend *self)
{
	NGtkComponent *current_focus = NGTK_BASIC_BACKEND_O2D (self) -> focus_holder;
	NGtkComponent *focus_iter = current_focus;
	NGtkContainer *parent = ngtk_component_get_parent (current_focus);
	NGtkComponent *new_focus;

	/* Check the case in which the root window owns the focus */
	if (parent == NULL)
	{
		ngtk_assert (ngtk_object_is_a (current_focus, NGTK_CONTAINER_TYPE));
		new_focus = find_first_focus (self, (NGtkContainer*)current_focus);

		/* Did we find a focusable child? */
		if (new_focus != NULL)
		{
			ngtk_backend_set_focus_holder (self, new_focus);
			return new_focus;
		}
		/* If not, the focus can't change */
		return current_focus;
	}

	/* Otherwise someone else owns the focus */
	while (parent != NULL)
	{
		NGtkList *siblings = ngtk_container_get_children (parent);
		NGtkListNode *iter = ngtk_list_find (siblings, focus_iter);
		while (iter->next != NULL)
		{
			iter = iter->next;
			new_focus = find_first_focus (self, (NGtkComponent*) iter->data);
			if (new_focus != NULL)
			{
				ngtk_backend_set_focus_holder (self, new_focus);
				return new_focus;
			}
		}

		/* None of the siblings is a focus holder, so go up */
		focus_iter = parent;
		parent = ngtk_component_get_parent (parent);
	}

	/* If we reached here, then none of the children of the root window
	 * that come after the cuyrrent focus are focusable. So, restart the
	 * focus loop by focusing at the root window */
	ngtk_backend_set_focus_holder (self, NGTK_BASIC_BACKEND_O2D (self) -> root_window);
	return NGTK_BASIC_BACKEND_O2D (self) -> root_window;
}

NGtkContainer* ngtk_basic_backend_get_root_window (NGtkBackend *self)
{
	return NGTK_BASIC_BACKEND_O2D (self) -> root_window;
}

const NGtkList* ngtk_basic_backend_get_all_components (NGtkBasicBackend *self)
{
	return & NGTK_BASIC_BACKEND_O2D (self) -> all_components;
}

void ngtk_basic_backend_print (NGtkBasicBackend *self, const char *format, va_list args)
{
	vprintf (format, args);
}

void ngtk_basic_backend_debug (NGtkBasicBackend *self, const char *format, va_list args)
{
	fprintf (stderr, "== ngtk::backend::debug == ");
	vfprintf (stderr, format, args);
	fprintf (stderr, "\n");
}

void ngtk_basic_backend_error (NGtkBasicBackend *self, const char *format, va_list args)
{
	fprintf (stderr, "== ngtk::backend::error == ");
	vfprintf (stderr, format, args);
	fprintf (stderr, "\n");
	exit (EXIT_FAILURE);
}

void ngtk_basic_backend_component_register (NGtkComponent *comp)
{
	NGtkBackend *self  = ngtk_base_get_backend (comp);
	NGtkList    *comps = & NGTK_BASIC_BACKEND_O2D (self) -> all_components;

	ngtk_assert (ngtk_list_find (comps, comp) == NULL);

	ngtk_list_append (comps, comp);
}

void ngtk_basic_backend_component_unregister (NGtkComponent *comp)
{
	NGtkBackend  *self  = ngtk_base_get_backend (comp);
	NGtkList     *comps = & NGTK_BASIC_BACKEND_O2D (self) -> all_components;
	NGtkListNode *n     = ngtk_list_find (comps, comp);

	ngtk_assert (n != NULL);
	ngtk_list_remove_node (comps, n);
	ngtk_assert (ngtk_list_find (comps, comp) == NULL);
}

void ngtk_basic_backend_root_window_register (NGtkContainer *root_window)
{
	NGtkBackend *self  = ngtk_base_get_backend (root_window);

	ngtk_assert (NGTK_BASIC_BACKEND_O2D (self) -> root_window == NULL);

	NGTK_BASIC_BACKEND_O2D (self) -> root_window = root_window;
}

void ngtk_basic_backend_root_window_unregister (NGtkContainer *root_window)
{
	NGtkBackend *self  = ngtk_base_get_backend (root_window);

	ngtk_assert (NGTK_BASIC_BACKEND_O2D (self) -> root_window == root_window);

	NGTK_BASIC_BACKEND_O2D (self) -> root_window = NULL;
}
