/*
 * ngtk-xlib-component.c
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

	ngtk_debug (backend, "XSelectInput (%p, %lu, %lu)", disp, xcd->wnd, NGTK_XLIB_EVENT_MASK);
	XSelectInput (disp, xcd->wnd, NGTK_XLIB_EVENT_MASK);

	ngtk_basic_backend_component_register (obj);
	ngtk_assert (ngtk_xlib_backend_get_for_window (backend, xcd->wnd) == obj);
	ngtk_object_push_destructor (obj, ngtk_basic_backend_component_unregister);

	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_xlib_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_xlib_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_xlib_component_set_visible;

	return in;
}

void ngtk_xlib_component_set_enabled (NGtkComponent *self, int enabled)
{
	ngtk_basic_component_set_enabled (self, enabled);
	ngtk_xlib_component_redraw (self);
}

void ngtk_xlib_component_set_visible (NGtkComponent *self, int visible)
{
	int old_val = ngtk_component_get_visible (self);

	if (old_val != visible)
	{
		Window           wnd  = ngtk_xlib_component_get_window (self);
		NGtkXlibBackend *xb   = ngtk_base_get_backend (self);
		Display         *disp = ngtk_xlib_backend_get_X_display (xb);

		if (visible)
		{
			ngtk_debug (xb, "XMapWindow (%p, %lu)", disp, wnd);
			XMapWindow (disp, wnd);
		}
		else
		{
			ngtk_debug (xb, "XUnmapWindow (%p, %lu)", disp, wnd);
			XUnmapWindow (disp, wnd);
		}
	}
	ngtk_basic_component_set_visible (self, visible);
}

void ngtk_xlib_component_set_text (NGtkComponent *self, const char *text)
{
	ngtk_basic_component_set_text (self, text);
	ngtk_component_redraw (self);
}


void ngtk_xlib_component_put_to (NGtkComponent *self, const NGtkRectangle *new_area, int already_there)
{
	NGtkXlibComponentD *xcd = NGTK_XLIB_COMPONENT_O2D (self);
	NGtkXlibBackend    *xb  = ngtk_base_get_backend (self);

	xcd->area.x = new_area->x;
	xcd->area.y = new_area->y;
	xcd->area.w = new_area->w;
	xcd->area.h = new_area->h;

	if (! already_there)
		XMoveResizeWindow (ngtk_xlib_backend_get_X_display (xb), xcd->wnd, new_area->x, new_area->y, new_area->w, new_area->h);
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
