/*
 * ngtk-xlib-backend.h
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

#ifndef __NGtk_xlib_backend__
#define __NGtk_xlib_backend__

#include "../basic/ngtk-basic.h"
#include "ngtk-xlib-widget-types.h"
#include <X11/Xlib.h>

/* Colors used by this backend */
typedef enum {
	NGTK_XLIB_WHITE = 0,
	NGTK_XLIB_BLACK = 1,
	NGTK_XLIB_GRAY  = 2,

	NGTK_XLIB_COLOR_MAX = 3
} NGtkXlibColorName;

typedef struct _ngtk_xlib_backend_d {
	/* The current connection to the X server */
	Display*  display;
	
	/* The screen on which we operate */
	int       screen;
	
	/* The root window of the xlib screen. This is not to be confused
	 * with the root application window created by NGtk (see above). */
	Window    root_window;

	/* A property/event that we communicate with the window manager. We will
	 * use it to store the property of closing a window */
	Atom      window_close_atom;

	/* The colormap of the current screen */
	Colormap  colormap;
	
	/* Colors that are allocated for usage by widgets of this backend */
	XColor    colors[NGTK_XLIB_COLOR_MAX];

	/* A list that will contain a mapping between `Window` objects and
	 * the matching `NGtkObject` objects */
	NGtkList  window2base;
} NGtkXlibBackendD;

#define NGTK_XLIB_BACKEND_O2D(comp) NGTK_O2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkXlibBackendD,1)
#define NGTK_XLIB_BACKEND_I2D(comp) NGTK_I2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkXlibBackendD,1)

NGtkBackendI*       ngtk_xlib_backend_create_interface   ();
void                ngtk_xlib_backend_d_free             (void *d);

void                ngtk_xlib_backend_init               (NGtkXlibBackend *self);
void                ngtk_xlib_backend_start_main_loop    (NGtkXlibBackend *self);
void                ngtk_xlib_backend_quit_main_loop     (NGtkXlibBackend *self);
void                ngtk_xlib_backend_quit               (NGtkXlibBackend *self);

NGtkContainer*      ngtk_xlib_backend_create_root_window (NGtkXlibBackend *self, const char *title);
NGtkComponent*      ngtk_xlib_backend_create_button      (NGtkXlibBackend *self, NGtkContainer* parent, const char *text);
NGtkComponent*      ngtk_xlib_backend_create_label       (NGtkXlibBackend *self, NGtkContainer* parent, const char *text);
NGtkComponent*      ngtk_xlib_backend_create_text_entry  (NGtkXlibBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

#define             ngtk_xlib_backend_get_focus_holder   ngtk_basic_backend_get_focus_holder
int                 ngtk_xlib_backend_set_focus_holder   (NGtkXlibBackend *self, NGtkComponent* new_focus);
#define             ngtk_xlib_backend_focus_to_next      ngtk_basic_backend_focus_to_next

#define             ngtk_xlib_backend_print              ngtk_basic_backend_print
#define             ngtk_xlib_backend_debug              ngtk_basic_backend_debug
#define             ngtk_xlib_backend_error              ngtk_basic_backend_error

#define             ngtk_xlib_backend_should_quit        ngtk_basic_backend_should_quit

/* Non interface functions */

Display*      ngtk_xlib_backend_get_display     (NGtkXlibBackend *self);
int           ngtk_xlib_backend_get_screen      (NGtkXlibBackend *self);
Window        ngtk_xlib_backend_get_root_window (NGtkXlibBackend *self);
unsigned long ngtk_xlib_backend_get_color       (NGtkXlibBackend *self, NGtkXlibColorName cn);

void            ngtk_xlib_backend_register_window    (NGtkXlibBackend *self, Window xlib_wnd, NGtkXlibBaseI* base);
NGtkXlibBaseI*  ngtk_xlib_backend_unregister_window  (NGtkXlibBackend *self, Window xlib_wnd);
NGtkXlibBase*   ngtk_xlib_backend_unregister_window2 (NGtkXlibBackend *self, Window xlib_wnd);
NGtkXlibBaseI*  ngtk_xlib_backend_get_for_window     (NGtkXlibBackend *self, Window xlib_wnd);
NGtkXlibBase*   ngtk_xlib_backend_get_for_window2    (NGtkXlibBackend *self, Window xlib_wnd);
#endif
