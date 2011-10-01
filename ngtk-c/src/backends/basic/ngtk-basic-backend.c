/*
 * ngtk-basic-backend.c
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
#include <stdio.h>
#include "ngtk-basic-backend.h"

static void on_root_window_creation (NGtkBackendI *self, const char* signame, NGtkValue *val);
static void on_label_creation       (NGtkBackendI *self, const char* signame, NGtkValue *val);
static void on_button_creation      (NGtkBackendI *self, const char* signame, NGtkValue *val);
static void on_text_entry_creation  (NGtkBackendI *self, const char* signame, NGtkValue *val);

NGtkBackendI* ngtk_basic_backend_create_interface ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_BACKEND_TYPE);
	NGtkBasicBackendD *bbd;

	bbd = ngtk_new (NGtkBasicBackendD);
	bbd->root_window = NULL;
	bbd->focus_holder = NULL;
	bbd->should_quit = FALSE;
	bbd->initialized = FALSE;
	ngtk_list_init (&bbd->all_components);

	in->d[0] = bbd;
	in->d_free[0] = ngtk_basic_backend_d_free;
	
	in->f = ngtk_new (NGtkBackendF);
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
	
	NGTK_BACKEND_I2F (in) -> print = ngtk_basic_backend_print;
	NGTK_BACKEND_I2F (in) -> debug = ngtk_basic_backend_debug;
	NGTK_BACKEND_I2F (in) -> error = ngtk_basic_backend_error;

	in->f_free = ngtk_free;

	ngtk_interface_connect_to (in, "backend::create-but", (NGtkListener) on_button_creation);
	ngtk_interface_connect_to (in, "backend::create-lab", (NGtkListener) on_label_creation);
	ngtk_interface_connect_to (in, "backend::create-te",  (NGtkListener) on_text_entry_creation);
	ngtk_interface_connect_to (in, "backend::create-wnd", (NGtkListener) on_root_window_creation);

	return in;
}

void ngtk_basic_backend_d_free (void *d)
{
	NGtkBasicBackendD *d_real = (NGtkBasicBackendD*) d;
	ngtk_list_clear_with_free_func (&d_real->all_components, (NGtkFreeFunc) ngtk_object_unref);
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

static void on_root_window_creation (NGtkBackendI *self, const char* signame, NGtkValue *val)
{
	NGTK_BASIC_BACKEND_I2D (self) -> root_window = (NGtkContainer*) val->val.v_pvoid;
}

static void on_label_creation (NGtkBackendI *self, const char* signame, NGtkValue *val)
{
	ngtk_list_append (& NGTK_BASIC_BACKEND_I2D (self) -> all_components, val->val.v_pvoid);
}

static void on_button_creation (NGtkBackendI *self, const char* signame, NGtkValue *val)
{
	ngtk_list_append (& NGTK_BASIC_BACKEND_I2D (self) -> all_components, val->val.v_pvoid);
}

static void on_text_entry_creation (NGtkBackendI *self, const char* signame, NGtkValue *val)
{
	ngtk_list_append (& NGTK_BASIC_BACKEND_I2D (self) -> all_components, val->val.v_pvoid);
}

NGtkEventGenerator* ngtk_basic_backend_get_focus_holder (NGtkBasicBackend *self)
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
NGtkEventGenerator* ngtk_basic_backend_focus_to_next (NGtkBasicBackend *self)
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