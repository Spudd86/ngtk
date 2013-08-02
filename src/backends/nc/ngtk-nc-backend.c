/*
 * ngtk-nc-backend.c - Part of the NGtk library
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

#include "ngtk-nc.h"

static void ngtk_nc_backend_destructor (NGtkNcBackend *obj);

NGtkBackendI* ngtk_nc_backend_create_interface (NGtkObject *obj)
{
	NGtkBackendI *in = ngtk_basic_backend_create_interface (obj);
	NGtkNcBackendD *nbd;

	in->imp_data[1] = nbd = ngtk_new (NGtkNcBackendD);
	nbd -> freeze_count = 0;
	nbd -> has_waiting = FALSE;
	in->imp_data_free[1] = ngtk_free;


	NGTK_BACKEND_I2F (in) -> init            = ngtk_nc_backend_init;
	NGTK_BACKEND_I2F (in) -> start_main_loop = ngtk_nc_backend_start_main_loop;
	NGTK_BACKEND_I2F (in) -> quit_main_loop  = ngtk_nc_backend_quit_main_loop;
	NGTK_BACKEND_I2F (in) -> quit            = ngtk_nc_backend_quit;

	NGTK_BACKEND_I2F (in) -> create_root_window = ngtk_nc_backend_create_root_window;
	NGTK_BACKEND_I2F (in) -> create_button      = ngtk_nc_backend_create_button;
	NGTK_BACKEND_I2F (in) -> create_label       = ngtk_nc_backend_create_label;
	NGTK_BACKEND_I2F (in) -> create_text_entry  = ngtk_nc_backend_create_text_entry;

	ngtk_object_push_destructor (obj, ngtk_nc_backend_destructor);

	return in;
}

static void ngtk_nc_backend_destructor (NGtkNcBackend *obj)
{
	/* THe basic destructor is actually the one detaches the interface,
	 * so here we shuold only do misc stuff if any */
}

NGtkContainer* ngtk_nc_backend_create_root_window (NGtkBasicBackend *self, const char *title)
{
	NGtkContainer *wnd = ngtk_nc_create_window_imp (self, title, FALSE);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_basic_backend_root_window_register (wnd);
	ngtk_object_push_destructor (wnd, ngtk_basic_backend_root_window_unregister);

	ngtk_interface_send_signal (in, "backend::create-wnd",  wnd, TRUE);
	return wnd;
}

NGtkComponent* ngtk_nc_backend_create_button (NGtkBasicBackend *self, NGtkContainer* parent, const char *text)
{
	NGtkComponent *but = ngtk_nc_create_button_imp (self, text, FALSE, parent);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-but",  but, TRUE);

	return but;
}

NGtkComponent* ngtk_nc_backend_create_label (NGtkBasicBackend *self, NGtkContainer* parent, const char *text)
{
	NGtkComponent *lab = ngtk_nc_create_label_imp (self, text, FALSE, parent);;
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-lab",  lab, TRUE);

	return lab;
}

NGtkComponent* ngtk_nc_backend_create_text_entry (NGtkBasicBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len)
{
	NGtkObject* te = ngtk_nc_create_text_entry_imp (self, parent, initial_text, FALSE, max_text_len);
	NGtkInterface *in = ngtk_object_cast (self, NGTK_BACKEND_TYPE);

	ngtk_interface_send_signal (in, "backend::create-te",  te, TRUE);

	return te;
}

void ngtk_nc_backend_drawing_accumulate (NGtkNcBackend *self)
{
	/* Increase the counter of how many times we were asked to
	 * accumulate drawing requests (so that we release them together) by
	 * 1. No need to check any preconditions */
	NGTK_NC_BACKEND_O2D (self) -> freeze_count ++;
}

void ngtk_nc_backend_drawing_release (NGtkNcBackend *self)
{
	/* First, make sure someone actually asked to accumulate drawings,
	 * and his request wasn't cancelled already */
	ngtk_assert (NGTK_NC_BACKEND_O2D (self) -> freeze_count > 0);

	/* Release the accumulation request, and check if no other requests
	 * are waiting */
	if (-- NGTK_NC_BACKEND_O2D (self) -> freeze_count == 0
		/* Check if during the accumulation, some drawing requests were
		 * actually made */
		&& NGTK_NC_BACKEND_O2D (self) -> has_waiting)
	{
		/* If so, commit the drawings */
		wrefresh (stdscr);
		/* Now, mark that we don't have any pending drawing requests */
		NGTK_NC_BACKEND_O2D (self) -> has_waiting = FALSE;
	}

}

void ngtk_nc_backend_drawing_commit (NGtkNcBackend *self, NGtkComponent *comp)
{
	WINDOW *to_out = ngtk_nc_component_get_window (comp);

	/* When sending out a window to the terminal, only the parts that
	 * were modified are sent. This is not exactly convinient, because
	 * then if widgets overlap (should not happen! but still) we may get
	 * a partially drawn widget on top of another widget. This can also
	 * happen if for some reason the window would be moved into an area
	 * where another widget once was. In order to avoid this, and other
	 * potential problems, we mark all the areas of the window as
	 * "touched" (i.e. changed) */
	touchwin (to_out);

	/* Now, actually commit the "touched" window to the accumulation
	 * buffer */
	overwrite (to_out, stdscr);

	/* If we are not currently in accumulation mode, we should send
	 * graphical updates as soon as we get them. */
	if (NGTK_NC_BACKEND_O2D (self) -> freeze_count == 0)
		wrefresh (stdscr);
	/* Otherwise, we should mark that updates were made, so that when
	 * accumulation ends, our requests will be passed */
	else
		NGTK_NC_BACKEND_O2D (self) -> has_waiting = TRUE;
}

void ngtk_nc_backend_call_on_widget_hide (NGtkNcBackend *self, NGtkComponent *comp)
{
	WINDOW *to_clear = ngtk_nc_component_get_window (comp);

	/* Simply erase the area where the widget once was. Since widgets
	 * do not get overlayed, we should no worry about drawing the things
	 * that may have been below it */
	wclear (to_clear);

	/* Now, actually commit to the accumulation buffer */
	overwrite (to_clear, stdscr);

	/* If we are not currently in accumulation mode, we should send
	 * graphical updates as soon as we get them. */
	if (NGTK_NC_BACKEND_O2D (self) -> freeze_count == 0)
		wrefresh (stdscr);
	/* Otherwise, we should mark that updates were made, so that when
	 * accumulation ends, our requests will be passed */
	else
		NGTK_NC_BACKEND_O2D (self) -> has_waiting = TRUE;
}

NGtkNcBackend* ngtk_nc_backend_new ()
{
	NGtkObject *obj = ngtk_object_new ();
	ngtk_nc_backend_create_interface (obj);
	return obj;
}

void ngtk_nc_backend_print (NGtkBasicBackend *self, const char *format, va_list args)
{
}
void ngtk_nc_backend_debug (NGtkBasicBackend *self, const char *format, va_list args)
{
}
void ngtk_nc_backend_error (NGtkBasicBackend *self, const char *format, va_list args)
{
}
