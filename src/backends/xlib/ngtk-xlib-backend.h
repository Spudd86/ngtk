/*
 * ngtk-xlib-backend.h - Part of the NGtk library
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
} NGtkXlibBackendD;

#define NGTK_XLIB_BACKEND_O2D(comp) NGTK_O2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkXlibBackendD,1)
#define NGTK_XLIB_BACKEND_I2D(comp) NGTK_I2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkXlibBackendD,1)

NGtkBackendI*       ngtk_xlib_backend_create_interface   (NGtkObject *obj);
void                ngtk_xlib_backend_d_free             (void *d);

void                ngtk_xlib_backend_init               (NGtkXlibBackend *self);
void                ngtk_xlib_backend_start_main_loop    (NGtkXlibBackend *self);
#define             ngtk_xlib_backend_quit_main_loop     ngtk_basic_backend_quit_main_loop
void                ngtk_xlib_backend_quit               (NGtkXlibBackend *self);

NGtkContainer*      ngtk_xlib_backend_create_root_window (NGtkXlibBackend *self, const char *title);
NGtkComponent*      ngtk_xlib_backend_create_button      (NGtkXlibBackend *self, NGtkContainer* parent, const char *text);
NGtkComponent*      ngtk_xlib_backend_create_label       (NGtkXlibBackend *self, NGtkContainer* parent, const char *text);
NGtkComponent*      ngtk_xlib_backend_create_text_entry  (NGtkXlibBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

#define             ngtk_xlib_backend_get_focus_holder   ngtk_basic_backend_get_focus_holder
int                 ngtk_xlib_backend_set_focus_holder   (NGtkXlibBackend *self, NGtkComponent* new_focus);
#define             ngtk_xlib_backend_focus_to_next      ngtk_basic_backend_focus_to_next
#define             ngtk_xlib_backend_get_root_window    ngtk_basic_backend_get_root_window
#define             ngtk_xlib_backend_get_all_components ngtk_basic_backend_get_all_components

#define             ngtk_xlib_backend_print              ngtk_basic_backend_print
#define             ngtk_xlib_backend_debug              ngtk_basic_backend_debug
#define             ngtk_xlib_backend_error              ngtk_basic_backend_error

#define             ngtk_xlib_backend_should_quit        ngtk_basic_backend_should_quit

/* Non interface functions */

Display*      ngtk_xlib_backend_get_X_display     (NGtkXlibBackend *self);
int           ngtk_xlib_backend_get_X_screen      (NGtkXlibBackend *self);
Window        ngtk_xlib_backend_get_X_root_window (NGtkXlibBackend *self);
unsigned long ngtk_xlib_backend_get_X_color       (NGtkXlibBackend *self, NGtkXlibColorName cn);

void            ngtk_xlib_backend_register_window    (NGtkXlibBackend *self, Window xlib_wnd, NGtkComponent *comp);
NGtkComponent*  ngtk_xlib_backend_unregister_window  (NGtkXlibBackend *self, Window xlib_wnd);
NGtkComponent*  ngtk_xlib_backend_get_for_window     (NGtkXlibBackend *self, Window xlib_wnd);

NGtkXlibBackend* ngtk_xlib_backend_new ();
#endif
