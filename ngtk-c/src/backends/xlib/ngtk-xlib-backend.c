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

#include "ngtk-xlib-backend.h"
#include "ngtk-xlib-base.h"

static float xlib_color_vals[NGTK_XLIB_COLOR_MAX][3] = {
	{1, 1, 1},          /* NGTK_XLIB_WHITE */
	{0, 0, 0},          /* NGTK_XLIB_BLACK */
	{0.6f, 0.5f, 0.4f}  /* NGTK_XLIB_GRAY  */
	};

typedef struct {
	Window         wnd;
	NGtkXlibBaseI *baseI;
} WindowAndBase;

NGtkBackendI* ngtk_xlib_backend_create_interface ()
{
	NGtkBackendI *in = ngtk_basic_backend_create_interface ();
	NGtkXlibBackendD *xbd;

	xbd = ngtk_new (NGtkXlibBackendD);
	xbd->display           = NULL;
	xbd->screent           = 0;
	xbd->root_window       = BadWindow;
	xbd->window_close_atom = BadAtom;
	xbd->colormap          = BadValue;
	ngtk_list_init (&xbd->window2base);

	in->d[0] = xbd;
	in->d_free[0] = ngtk_xlib_backend_d_free;
	
	in->f = ngtk_new (NGtkBackendF);
	NGTK_BACKEND_I2F (in) -> init = ngtk_xlib_init;
	NGTK_BACKEND_I2F (in) -> start_main_loop = ngtk_xlib_start_main_loop;
	NGTK_BACKEND_I2F (in) -> quit_main_loop = ngtk_xlib_backend_quit_main_loop;
	NGTK_BACKEND_I2F (in) -> quit = ngtk_xlib_quit;

	NGTK_BACKEND_I2F (in) -> create_root_window = ngtk_xlib_create_root_window;
	NGTK_BACKEND_I2F (in) -> create_button = ngtk_xlib_create_button;
	NGTK_BACKEND_I2F (in) -> create_label = ntk_xlib_create_label;
	NGTK_BACKEND_I2F (in) -> create_text_entry = ngtk_xlib_create_text_entry;
	
	NGTK_BACKEND_I2F (in) -> get_focus_holder = ngtk_xlib_backend_get_focus_holder;
	NGTK_BACKEND_I2F (in) -> set_focus_holder = ngtk_xlib_backend_set_focus_holder;
	NGTK_BACKEND_I2F (in) -> focus_to_next = ngtk_xlib_backend_focus_to_next;

	NGTK_BACKEND_I2F (in) -> print = ngtk_xlib_backend_print;
	NGTK_BACKEND_I2F (in) -> debug = ngtk_xlib_backend_debug;
	NGTK_BACKEND_I2F (in) -> error = ngtk_xlib_backend_error;
	
	in->f_free = ngtk_free;

	return in;
}

void ngtk_xlib_backend_d_free (void *d)
{
	NGtkXlibBackendD *d_real = (NGtkXlibBackendD*) d;
	ngtk_list_clear_with_free_func (d_real->window2base, ngtk_free);
	ngtk_free (d_real);
}

void ngtk_xlib_backend_init (NGtkBasicBackend *self)
{
	ngtk_basic_backend_call_after_init (self);
}

void ngtk_xlib_backend_start_main_loop (NGtkBasicBackend *self)
{
	ngtk_basic_backend_call_before_start_main_loop (self);
}

void ngtk_xlib_backend_quit (NGtkBasicBackend *self)
{
}

NGtkContainer* ngtk_xlib_backend_create_root_window (NGtkBasicBackend *self, const char *title)
{
	NGtkContainer *wnd = NULL;
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);
	NGtkValue      val;
	
	register_window (self, title);
	val.type = NGTK_VALUE_P_VOID;
	val.value.v_pvoid = wnd;
	ngtk_interface_send_signal (in, "backend::create-wnd",  &val, TRUE);
	return wnd;
}

NGtkComponent* ngtk_xlib_backend_create_button (NGtkBasicBackend *self, NGtkContainer* parent, const char *text)
{
	NGtkContainer *but = NULL;
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);
	NGtkValue      val;
	
	val.type = NGTK_VALUE_P_VOID;
	val.value.v_pvoid = but;
	ngtk_interface_send_signal (in, "backend::create-but",  &val, TRUE);
	
	return but;
}

NGtkComponent* ngtk_xlib_backend_create_label (NGtkBasicBackend *self, NGtkContainer* parent, const char *text)
{
	NGtkContainer *lab = NULL;
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);
	NGtkValue      val;
	
	val.type = NGTK_VALUE_P_VOID;
	val.value.v_pvoid = lab;
	ngtk_interface_send_signal (in, "backend::create-lab",  &val, TRUE);
	
	return lab;
}

NGtkComponent* ngtk_xlib_backend_create_text_entry (NGtkBasicBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len)
{
	NGtkContainer *te = NULL;
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);
	NGtkValue      val;
	
	val.type = NGTK_VALUE_P_VOID;
	val.value.v_pvoid = te;
	ngtk_interface_send_signal (in, "backend::create-te",  &val, TRUE);
	
	return te;
}




static NGtkListNode* find_window (NGtkXlibBackend *self, Window xlib_wnd)
{
	NGtkListNode *iter;
	ngtk_list_foreach (iter, & NGTK_XLIB_BACKEND_O2D (self) -> window2base)
	{
		if (((WindowAndBase*)iter->data)->wnd == xlib_wnd)
			return iter;
	}
	return NULL;
}

void ngtk_xlib_backend_register_window (NGtkXlibBackend *self, Window xlib_wnd, NGtkXlibBaseI* baseI)
{
	NGtkXlibBackend *xb = ngtk_xlib_base_get_backend (base);
	WindowAndBase   *wb = ngtk_new (WindowAndBase);

	wb->wnd  = xlib_wnd;
	wb->baseI = baseI;

	ngtk_list_append (& NGTK_XLIB_BACKEND_O2D (self) -> window2base, wb);
}

NGtkXlibBaseI* ngtk_xlib_backend_unregister_window (NGtkXlibBackend *self, Window xlib_wnd)
{
	NGtkListNode *n = find_window (self, xlib_wnd);
	NGtkXlibBaseI *bi = ((WindowAndBase*) n->data) -> baseI;
	
	ngtk_free ((WindowAndBase*) n->data);
	ngtk_list_remove_node (& NGTK_XLIB_BACKEND_O2D (self) -> window2base, n);
}

NGtkXlibBaseI* ngtk_xlib_backend_get_for_window (NGtkXlibBackend *self, Window xlib_wnd)
{
	NGtkXlibBase *base = ((WindowAndBase*) find_window (self, xlib_wnd) -> data) -> base;
	if (baseI == NULL)
		return NULL;
	else
		return ngtk_interface_get_object (base);
}
