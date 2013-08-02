/*
 * ngtk-xlib-window.c
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

#include <stdio.h>
#include <string.h>

/* This file contains the creation functions for all the widget types */

/** The pack method of the main window - this is responsible for
 * refreshing the window size structures, and then using the layout to
 * reposition all the children. */
static void pack_main_window (NGtkContainer *self)
{
	NGtkRectangle new_area;
	NGtkListNode  *iter;
	unsigned int w, h;

	Window root;
	unsigned int border_width, depth;
	Display *disp = ngtk_xlib_base_get_display (self);

	new_area.x = new_area.y = 0;
	XGetGeometry (disp, ngtk_xlib_component_get_window (self), &root,
		&new_area.x, &new_area.y, &w, &h, &border_width, &depth);
	new_area.w = w;
	new_area.h = h;

	ngtk_xlib_component_put_to (self, &new_area, TRUE);
	ngtk_object_send_signal (self, "event::resize", &new_area);

	if (NGTK_BASIC_CONTAINER_O2D(self)->layout != NULL)
		ngtk_layout_pack (NGTK_BASIC_CONTAINER_O2D(self)->layout, self, new_area.w, new_area.h);

	ngtk_component_redraw (self);

	ngtk_list_foreach (iter, ngtk_container_get_children (self))
	{
		ngtk_component_redraw ((NGtkComponent*) iter->data);
	}
}

static void draw_window (NGtkComponent *window)
{
	NGtkXlibGraphics *g;

	g = ngtk_xlib_graphics_create (window);
	ngtk_graphics_clear (g);
	ngtk_object_free (g);

	ngtk_basic_component_redraw (window);
}

static void draw_label (NGtkComponent *label)
{
	const NGtkRectangle *rect = ngtk_xlib_component_get_rect (label);
	NGtkXlibGraphics    *g    = ngtk_xlib_graphics_create (label);
	const char          *text = ngtk_component_get_text (label);

	ngtk_graphics_clear (g);
	ngtk_basic_graphics_draw_aligned_text (g, rect, TRUE, 0, 2, 0.5f, 2, text);

	ngtk_object_free (g);
	ngtk_basic_component_redraw (label);
}

static void draw_button (NGtkComponent *but)
{
	const NGtkRectangle *rect = ngtk_xlib_component_get_rect (but);
	NGtkXlibGraphics    *g    = ngtk_xlib_graphics_create (but);
	const char          *text = ngtk_component_get_text (but);

	ngtk_graphics_clear (g);
	ngtk_graphics_draw_frame (g, rect, ngtk_xlib_base_has_focus (but));
	ngtk_basic_graphics_draw_aligned_text (g, rect, TRUE, 0.5f, 2, 0.5f, 2, text);

	ngtk_object_free (g);
	ngtk_basic_component_redraw (but);
}

static void draw_text_entry (NGtkComponent *te)
{
	const NGtkRectangle *rect = ngtk_xlib_component_get_rect (te);
	NGtkXlibGraphics    *g    = ngtk_xlib_graphics_create (te);
	const char          *text = ngtk_component_get_text (te);

	ngtk_graphics_clear (g);
	ngtk_graphics_draw_frame (g, rect, ngtk_xlib_base_has_focus (te));
	ngtk_basic_graphics_draw_text_with_cursor (g, rect, TRUE, 0, 2, 0.5f, 2, text, ngtk_text_entry_get_cursor_position (te));

	ngtk_object_free (g);
	ngtk_basic_component_redraw (te);
}

static NGtkObject* create_basic_widget (NGtkBackend *self, int enabled, NGtkContainer *parent, const char* text, int visible, const NGtkRectangle *area, int focusable)
{
	NGtkObject *obj = ngtk_object_new ();

	ngtk_basic_base_create_interface (obj, self);
	ngtk_xlib_component_create_interface (obj, parent, enabled, focusable, text, visible);

	/* Now, do the parts of the construction that depend on the
	 * existance of a whole object and therefore couldn't be done while
	 * constructing the interface imps */
	if (parent != NULL)
		ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, visible);
	ngtk_xlib_component_put_to (obj, area, FALSE);

	return obj;
}

NGtkObject* ngtk_xlib_create_window_imp (NGtkBackend *self, const char* title, int visible)
{
	NGtkRectangle area = { 100, 100, 200, 200 };
	NGtkObject *obj = create_basic_widget (self, TRUE, NULL, title, visible, &area, TRUE);

	ngtk_xlib_container_create_interface (obj);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_window;
	NGTK_CONTAINER_O2F (obj) -> pack = pack_main_window;

	XSetWMProtocols (ngtk_xlib_backend_get_X_display (self), ngtk_xlib_component_get_window (obj), & NGTK_XLIB_BACKEND_O2D (self) -> window_close_atom, 1);

	return obj;
}

NGtkObject* ngtk_xlib_create_label_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent)
{
	NGtkRectangle area = { 0, 0, 100, 100 };
	NGtkObject *obj = create_basic_widget (self, TRUE, parent, text, visible, &area, FALSE);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_label;

	return obj;
}

NGtkObject* ngtk_xlib_create_button_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent)
{
	NGtkRectangle area = { 0, 0, 100, 100 };
	NGtkObject *obj = create_basic_widget (self, TRUE, parent, text, visible, &area, TRUE);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_button;

	return obj;
}

NGtkObject* ngtk_xlib_create_text_entry_imp (NGtkBackend *self, NGtkContainer *parent, const char* initial_text, int visible, int max_text_len)
{
	NGtkRectangle area = { 0, 0, 100, 100 };
	NGtkObject *obj = create_basic_widget (self, TRUE, parent, initial_text, visible, &area, TRUE);

	ngtk_basic_text_entry_create_interface (obj, initial_text, max_text_len);
	NGTK_COMPONENT_O2F (obj) -> redraw = draw_text_entry;

	return obj;
}
