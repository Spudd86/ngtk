/*
 * ngtk-win-backend.c
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

#include "ngtk-win.h"

static void win_backend_destructor (NGtkObject *obj);

NGtkBackendI* ngtk_win_backend_create_interface (NGtkObject *obj)
{
	NGtkBackendI *in = ngtk_basic_backend_create_interface (obj);

	NGTK_BACKEND_I2F (in) -> init = ngtk_win_backend_init;
	NGTK_BACKEND_I2F (in) -> start_main_loop = ngtk_win_backend_start_main_loop;
	NGTK_BACKEND_I2F (in) -> quit_main_loop = ngtk_win_backend_quit_main_loop;
	NGTK_BACKEND_I2F (in) -> quit = ngtk_win_backend_quit;

	NGTK_BACKEND_I2F (in) -> create_root_window = ngtk_win_backend_create_root_window;
	NGTK_BACKEND_I2F (in) -> create_button = ngtk_win_backend_create_button;
	NGTK_BACKEND_I2F (in) -> create_label = ngtk_win_backend_create_label;
	NGTK_BACKEND_I2F (in) -> create_text_entry = ngtk_win_backend_create_text_entry;

	NGTK_BACKEND_I2F (in) -> get_focus_holder = ngtk_win_backend_get_focus_holder;
	NGTK_BACKEND_I2F (in) -> set_focus_holder = ngtk_win_backend_set_focus_holder;
	NGTK_BACKEND_I2F (in) -> focus_to_next = ngtk_win_backend_focus_to_next;

	NGTK_BACKEND_I2F (in) -> get_root_window = ngtk_win_backend_get_root_window;
	NGTK_BACKEND_I2F (in) -> get_all_components = ngtk_win_backend_get_all_components;

	NGTK_BACKEND_I2F (in) -> print = ngtk_win_backend_print;
	NGTK_BACKEND_I2F (in) -> debug = ngtk_win_backend_debug;
	NGTK_BACKEND_I2F (in) -> error = ngtk_win_backend_error;

	ngtk_object_push_destructor (obj, win_backend_destructor);

	return in;
}

static void win_backend_destructor (NGtkObject *obj)
{

}

void ngtk_win_backend_init (NGtkBasicBackend *self)
{
	ngtk_win_init (self);
	ngtk_basic_backend_call_after_init (self);
}

void ngtk_win_backend_start_main_loop (NGtkBasicBackend *self)
{
	ngtk_basic_backend_call_before_start_main_loop (self);
	ngtk_win_start_main_loop (self);
}

void ngtk_win_backend_quit (NGtkBasicBackend *self)
{
	ngtk_win_quit (self);
}

NGtkContainer* ngtk_win_backend_create_root_window (NGtkBasicBackend *self, const char *title)
{
	NGtkContainer *wnd = ngtk_win_create_window_imp (self, title, FALSE);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_basic_backend_root_window_register (wnd);
	ngtk_object_push_destructor (wnd, ngtk_basic_backend_root_window_unregister);

	ngtk_interface_send_signal (in, "backend::create-wnd",  wnd, TRUE);
	return wnd;
}

NGtkComponent* ngtk_win_backend_create_button (NGtkBasicBackend *self, NGtkContainer* parent, const char *text)
{
	NGtkComponent *but = ngtk_win_create_button_imp (self, text, FALSE, parent);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-but",  but, TRUE);

	return but;
}

NGtkComponent* ngtk_win_backend_create_label (NGtkBasicBackend *self, NGtkContainer* parent, const char *text)
{
	NGtkComponent *lab = ngtk_win_create_label_imp (self, text, FALSE, parent);;
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-lab",  lab, TRUE);

	return lab;
}

NGtkComponent* ngtk_win_backend_create_text_entry (NGtkBasicBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len)
{
	NGtkObject* te = ngtk_win_create_text_entry_imp (self, parent, initial_text, FALSE, max_text_len);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-te",  te, TRUE);

	return te;
}


int ngtk_win_backend_set_focus_holder (NGtkWinBackend *self, NGtkComponent* eg)
{
	if (ngtk_basic_backend_can_focus_on (self, eg))
	{
		SetFocus (ngtk_win_component_get_hwnd (eg));
	}
	return ngtk_basic_backend_set_focus_holder (self, eg);
}


NGtkComponent* ngtk_win_backend_get_for_window (NGtkWinBackend *self, HWND wnd)
{
	NGtkListNode *iter;
	ngtk_list_foreach (iter, ngtk_backend_get_all_components (self))
	{
		if (ngtk_win_component_get_hwnd ((NGtkComponent*) iter->data) == wnd)
			return (NGtkComponent*) iter->data;
	}
	return NULL;
}

NGtkWinBackend* ngtk_win_backend_new ()
{
	NGtkObject *obj = ngtk_object_new ();
	ngtk_assert (obj);
	ngtk_win_backend_create_interface (obj);
	return obj;
}
