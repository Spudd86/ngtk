/*
 * ngtk-xlib-backend.c
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

#include "ngtk-xlib.h"

static void xlib_backend_destructor (NGtkObject *obj);

NGtkBackendI* ngtk_xlib_backend_create_interface (NGtkObject *obj)
{
	NGtkBackendI *in = ngtk_basic_backend_create_interface (obj);
	NGtkXlibBackendD *xbd;

	in->imp_data[1] = xbd = ngtk_new (NGtkXlibBackendD);
	xbd->display           = NULL;
	xbd->screen            = 0;
	xbd->root_window       = BadWindow;
	xbd->window_close_atom = BadAtom;
	xbd->colormap          = BadValue;
	in->imp_data_free[1] = ngtk_free;

	NGTK_BACKEND_I2F (in) -> init = ngtk_xlib_backend_init;
	NGTK_BACKEND_I2F (in) -> start_main_loop = ngtk_xlib_backend_start_main_loop;
	NGTK_BACKEND_I2F (in) -> quit_main_loop = ngtk_xlib_backend_quit_main_loop;
	NGTK_BACKEND_I2F (in) -> quit = ngtk_xlib_backend_quit;

	NGTK_BACKEND_I2F (in) -> create_root_window = ngtk_xlib_backend_create_root_window;
	NGTK_BACKEND_I2F (in) -> create_button = ngtk_xlib_backend_create_button;
	NGTK_BACKEND_I2F (in) -> create_label = ngtk_xlib_backend_create_label;
	NGTK_BACKEND_I2F (in) -> create_text_entry = ngtk_xlib_backend_create_text_entry;

	NGTK_BACKEND_I2F (in) -> get_focus_holder = ngtk_xlib_backend_get_focus_holder;
	NGTK_BACKEND_I2F (in) -> set_focus_holder = ngtk_xlib_backend_set_focus_holder;
	NGTK_BACKEND_I2F (in) -> focus_to_next = ngtk_xlib_backend_focus_to_next;

	NGTK_BACKEND_I2F (in) -> get_root_window = ngtk_xlib_backend_get_root_window;
	NGTK_BACKEND_I2F (in) -> get_all_components = ngtk_xlib_backend_get_all_components;

	NGTK_BACKEND_I2F (in) -> print = ngtk_xlib_backend_print;
	NGTK_BACKEND_I2F (in) -> debug = ngtk_xlib_backend_debug;
	NGTK_BACKEND_I2F (in) -> error = ngtk_xlib_backend_error;

	ngtk_object_push_destructor (obj, xlib_backend_destructor);

	return in;
}

static void xlib_backend_destructor (NGtkObject *obj)
{

}

void ngtk_xlib_backend_init (NGtkBasicBackend *self)
{
	ngtk_xlib_init (self);
	ngtk_basic_backend_call_after_init (self);
}

void ngtk_xlib_backend_start_main_loop (NGtkBasicBackend *self)
{
//	XEvent e;
//	int mark1 = FALSE;
//	int mark2 = FALSE;
//	while (TRUE) {
//		XNextEvent (ngtk_xlib_backend_get_display (self), &e);
//		if (! mark1 && e.type == ReparentNotify)
//			mark1 = TRUE;
//		else if (! mark2 && e.type == ConfigureNotify)
//			break;
//	}
//	ngtk_basic_backend_call_before_start_main_loop (self);
	ngtk_xlib_start_main_loop (self);
}

void ngtk_xlib_backend_quit (NGtkBasicBackend *self)
{
	ngtk_xlib_quit (self);
}

NGtkContainer* ngtk_xlib_backend_create_root_window (NGtkBasicBackend *self, const char *title)
{
	NGtkContainer *wnd = ngtk_xlib_create_window_imp (self, title, FALSE);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_basic_backend_root_window_register (wnd);
	ngtk_object_push_destructor (wnd, ngtk_basic_backend_root_window_unregister);

	ngtk_interface_send_signal (in, "backend::create-wnd",  wnd, TRUE);
	return wnd;
}

NGtkComponent* ngtk_xlib_backend_create_button (NGtkBasicBackend *self, NGtkContainer* parent, const char *text)
{
	NGtkComponent *but = ngtk_xlib_create_button_imp (self, text, FALSE, parent);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-but",  but, TRUE);

	return but;
}

NGtkComponent* ngtk_xlib_backend_create_label (NGtkBasicBackend *self, NGtkContainer* parent, const char *text)
{
	NGtkComponent *lab = ngtk_xlib_create_label_imp (self, text, FALSE, parent);;
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-lab",  lab, TRUE);

	return lab;
}

NGtkComponent* ngtk_xlib_backend_create_text_entry (NGtkBasicBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len)
{
	NGtkObject* te = ngtk_xlib_create_text_entry_imp (self, parent, initial_text, FALSE, max_text_len);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-te",  te, TRUE);

	return te;
}


int ngtk_xlib_backend_set_focus_holder (NGtkXlibBackend *self, NGtkComponent* eg)
{
#if FALSE
	if (ngtk_basic_backend_can_focus_on (self, eg))
	{
		int has_parent = ngtk_component_get_parent (eg) != NULL;
		int revert_to = has_parent ? RevertToParent : RevertToNone;
		ngtk_debug (self, "Setting focus2 to %p with Window %d", eg, ngtk_xlib_component_get_window (eg));
		/* In the case where a component that owns the focus becomes
		 * non focusable, we must deliver the focus onwards. For the
		 * root window, we can't deliver to the parent (so deliver to
		 * None, knowing this won't happen) and for others pass to the
		 * parent */
//		XFlush (ngtk_xlib_backend_get_display (self));
		XSetInputFocus (ngtk_xlib_backend_get_X_display (self), ngtk_xlib_component_get_window (eg), revert_to, CurrentTime);
	}
#endif
	return ngtk_basic_backend_set_focus_holder (self, eg);
}


Display* ngtk_xlib_backend_get_X_display (NGtkXlibBackend *self)
{
	return NGTK_XLIB_BACKEND_O2D (self) -> display;
}

int ngtk_xlib_backend_get_X_screen (NGtkXlibBackend *self)
{
	return NGTK_XLIB_BACKEND_O2D (self) -> screen;
}

Window ngtk_xlib_backend_get_X_root_window (NGtkXlibBackend *self)
{
	return NGTK_XLIB_BACKEND_O2D (self) -> root_window;
}

unsigned long ngtk_xlib_backend_get_X_color (NGtkXlibBackend *self, NGtkXlibColorName cn)
{
	ngtk_assert (0 <= cn && cn < NGTK_XLIB_COLOR_MAX);
	return NGTK_XLIB_BACKEND_O2D (self) -> colors[cn].pixel;
}


NGtkComponent* ngtk_xlib_backend_get_for_window (NGtkXlibBackend *self, Window xlib_wnd)
{
	NGtkListNode *iter;
	ngtk_list_foreach (iter, ngtk_backend_get_all_components (self))
	{
		if (ngtk_xlib_component_get_window ((NGtkComponent*) iter->data) == xlib_wnd)
			return (NGtkComponent*) iter->data;
	}
	return NULL;
}

NGtkXlibBackend* ngtk_xlib_backend_new ()
{
	NGtkObject *obj = ngtk_object_new ();
	ngtk_assert (obj);
	ngtk_xlib_backend_create_interface (obj);
	return obj;
}
