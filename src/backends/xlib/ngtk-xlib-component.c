/*
 * ngtk-xlib-component.c - Part of the NGtk library
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

#include "ngtk-xlib-component.h"
#include "ngtk-xlib.h"
//#include "ngtk-xlib-base.h"
//#include "../basic/ngtk-basic.h"

static const NGtkRectangle default_position = { 0, 0, 200, 200 };

NGtkInterface* ngtk_xlib_component_create_interface (NGtkObject *obj, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (obj, parent, enabled, focusable, text, visible);
	NGtkXlibComponentD *xcd = NULL;
	NGtkXlibBackend *backend = ngtk_base_get_backend (obj);
	Window parent_window = BadWindow;
	Display *disp = ngtk_xlib_backend_get_X_display (backend);

	/* Every X screen has a root_window - this is a window that covers
	 * the entire screen. If we want  to create a "Top-Level" window,
	 * then it's direct parent should be the root_window of the matching
	 * X screen */
	if (parent == NULL)
		parent_window = ngtk_xlib_backend_get_X_root_window (backend);
	else
		parent_window = NGTK_XLIB_COMPONENT_O2D (parent) -> wnd;

	xcd = ngtk_new (NGtkXlibComponentD);
	in->imp_data[1] = xcd;
	xcd->area.x = default_position.x;
	xcd->area.y = default_position.y;
	xcd->area.w = default_position.w;
	xcd->area.h = default_position.h;
	xcd->zero_size_hide = xcd->area.w == 0 || xcd->area.h == 0;

	xcd->wnd = XCreateSimpleWindow (
		/* Connection to X server */
		disp,
		/* Parent window */
		parent_window,
		/* (X,Y) Coordinates of top left corner, in coordinates
		 * relative to the parent window */
		default_position.x, default_position.y,
		/* Width and height of the window */
		default_position.w, default_position.h,
		/* Border width and color */
		0, ngtk_xlib_backend_get_X_color (backend, NGTK_XLIB_BLACK),
		/* Background color */
		ngtk_xlib_backend_get_X_color (backend, NGTK_XLIB_WHITE)
		);
	in->imp_data_free[1] = ngtk_free;

	/* Set the mask of events that we would like to be notified about */
	XSelectInput (disp, xcd->wnd, NGTK_XLIB_EVENT_MASK);

	/* Call to add this component to the general component list, and to
	 * emit the signal saying that a component was craeted on the
	 * backend */
	ngtk_basic_backend_component_register (obj);
	/* Assert that this component was registered succesfully */
	ngtk_assert (ngtk_xlib_backend_get_for_window (backend, xcd->wnd) == obj);
	/* When the component is destroyed, don't forget to unregister
	 * it from the backend! */
	ngtk_object_push_destructor (obj, ngtk_basic_backend_component_unregister);

	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_xlib_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_xlib_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_xlib_component_set_visible;

	return in;
}

void ngtk_xlib_component_set_enabled (NGtkComponent *self, int enabled)
{
	ngtk_basic_component_set_enabled (self, enabled);
	/* The enabled property has a visual feedback that should be
	 * updated */
	ngtk_xlib_component_redraw (self);
}

void ngtk_xlib_component_set_visible (NGtkComponent *self, int visible)
{
	int old_val = ngtk_component_get_visible (self);

	/* If we are indeed changing the visibility status, and if we are
	 * not locked in hidden mode due to a zero size, then there is a
	 * reason to consider doing something */
	if (old_val != visible && ! NGTK_XLIB_COMPONENT_O2D (self) -> zero_size_hide)
	{
		Window           wnd  = ngtk_xlib_component_get_window (self);
		NGtkXlibBackend *xb   = ngtk_base_get_backend (self);
		Display         *disp = ngtk_xlib_backend_get_X_display (xb);

		if (visible)
		{
			XMapWindow (disp, wnd);
		}
		else
		{
			XUnmapWindow (disp, wnd);
		}
	}
	ngtk_basic_component_set_visible (self, visible);
}

void ngtk_xlib_component_set_text (NGtkComponent *self, const char *text)
{
	ngtk_basic_component_set_text (self, text);
	/* The text property has a visual feedback that should be
	 * updated */
	ngtk_component_redraw (self);
}


void ngtk_xlib_component_put_to (NGtkComponent *self, const NGtkRectangle *new_area, int already_there)
{
	NGtkXlibComponentD *xcd = NGTK_XLIB_COMPONENT_O2D (self);
	NGtkXlibBackend    *xb  = ngtk_base_get_backend (self);

	int new_zero_size_hide = new_area->h == 0 || new_area->w == 0;
	int old_zero_size_hide = xcd->zero_size_hide;
	int visible = ngtk_component_get_visible (self);

	xcd->area.x = new_area->x;
	xcd->area.y = new_area->y;
	xcd->area.w = new_area->w;
	xcd->area.h = new_area->h;

	/* Do we really need to do something? */
	if (! already_there)
	{
		/* If the widget wasn't hidden previously (not because of zero
		 * size and not because of the visible property), then if it
		 * now gets a zero size, it should be hidden */
		if (new_zero_size_hide && visible && ! old_zero_size_hide)
			XUnmapWindow (ngtk_xlib_backend_get_X_display (xb), xcd->wnd);
		/* Otherwise, if the new size is valid, we should resize */
		else if (! new_zero_size_hide)
			XMoveResizeWindow (ngtk_xlib_backend_get_X_display (xb), xcd->wnd, new_area->x, new_area->y, new_area->w, new_area->h);

		/* If previously we were hidden only because of a zero size, and
		 * now the new size is legitimate, then map the window */
		if (! new_zero_size_hide && old_zero_size_hide && visible)
			XMapWindow (ngtk_xlib_backend_get_X_display (xb), xcd->wnd);

		xcd->zero_size_hide = new_zero_size_hide;
	}
}

Window ngtk_xlib_component_get_window (NGtkComponent *self)
{
	return NGTK_XLIB_COMPONENT_O2D (self) -> wnd;
}

const NGtkRectangle* ngtk_xlib_component_get_rect (NGtkComponent *self)
{
	return & NGTK_XLIB_COMPONENT_O2D (self) -> area;
}

void ngtk_xlib_component_call_on_window_destroyed (NGtkComponent *self)
{
	NGTK_XLIB_COMPONENT_O2D (self) -> wnd = BadWindow;
}
