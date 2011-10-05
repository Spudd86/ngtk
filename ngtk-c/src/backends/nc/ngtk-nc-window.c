/*
 * ngtk-nc-window.c
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

#include "ngtk-nc.h"

static void pack_main_window (NGtkContainer *self)
{
	NGtkRectangle new_area;
	NGtkListNode *iter;
	new_area.x = new_area.y = 0;
	getmaxyx (stdscr, new_area.h, new_area.w);
	ngtk_nc_component_map_to (self, &new_area);

	/* NCURSES has a bug that means that if any WINDOW became partially
	 * outside the screen, it will erdraaw uglylly. So we must refresh
	 * the windows when resizing to avoid this.
	 *
	 * The put_to function of the NGtkNcComponent class will delete
	 * the existing WINDOW and will crate a new one. We will do this for
	 * all the children that weren't resize during the packing done by
	 * the layout.
	 *
	 * TODO: for future versions, consider using pads instead of windows
	 */

	ngtk_list_foreach (iter, ngtk_container_get_children (self))
	{
		NGtkComponent *child = (NGtkComponent*) iter->data;
		ngtk_nc_component_reset_resize_bit (child);
	}

	if (NGTK_BASIC_CONTAINER_O2D(self)->layout != NULL)
		ngtk_layout_pack (NGTK_BASIC_CONTAINER_O2D(self)->layout, self, COLS, LINES);

	ngtk_list_foreach (iter, ngtk_container_get_children (self))
	{
		NGtkComponent *child = (NGtkComponent*) iter->data;
		if (! ngtk_nc_component_was_resized (child))
			ngtk_nc_component_map_to (child, ngtk_nc_component_get_abs_rect (child));
	}

	/* Note that the redraw method also redraws the children */
	ngtk_component_redraw (self);
}

static void draw_window (NGtkComponent *window)
{
	NGtkNcGraphics *g;

	g = ngtk_nc_graphics_create (window);
	ngtk_graphics_clear (g);
	ngtk_object_free (g);

	ngtk_basic_component_redraw (window);
}

static void draw_label (NGtkComponent *label)
{
	const NGtkRectangle *rect = ngtk_nc_component_get_abs_rect (label);
	NGtkNcGraphics      *g    = ngtk_nc_graphics_create (label);
	const char          *text = ngtk_component_get_text (label);

	ngtk_graphics_clear (g);
	ngtk_basic_graphics_draw_aligned_text (g, rect, TRUE, 0, 1, 0.5f, 1, text);

	ngtk_object_free (g);
	ngtk_basic_component_redraw (label);
}

static void draw_button (NGtkComponent *but)
{
	const NGtkRectangle *rect = ngtk_nc_component_get_abs_rect (but);
	NGtkNcGraphics      *g    = ngtk_nc_graphics_create (but);
	const char          *text = ngtk_component_get_text (but);

	ngtk_graphics_clear (g);
	ngtk_graphics_draw_frame (g, rect, ngtk_nc_component_has_focus (but));
	ngtk_basic_graphics_draw_aligned_text (g, rect, TRUE, 0.5f, 1, 0.5f, 1, text);

	ngtk_object_free (g);
	ngtk_basic_component_redraw (but);
}

static void draw_text_entry (NGtkComponent *te)
{
	const NGtkRectangle *rect = ngtk_nc_component_get_abs_rect (te);
	NGtkNcGraphics      *g    = ngtk_nc_graphics_create (te);
	const char          *text = ngtk_component_get_text (te);

	ngtk_graphics_clear (g);
	ngtk_graphics_draw_frame (g, rect, ngtk_nc_component_has_focus (te));
	ngtk_basic_graphics_draw_text_with_cursor (g, rect, TRUE, 0, 1, 0.5f, 1, text, ngtk_text_entry_get_cursor_position (te));

	ngtk_object_free (g);
	ngtk_basic_component_redraw (te);
}

static NGtkObject* create_basic_widget (NGtkBackend *self, int enabled, NGtkContainer *parent, const char* text, int visible, const NGtkRectangle *area, int focusable)
{
	NGtkObject *obj = ngtk_object_new ();

	ngtk_basic_base_create_interface (obj, self);
	ngtk_nc_component_create_interface (obj, parent, enabled, focusable, text, visible);

	/* Now, do the parts of the construction that depend on the
	 * existance of a whole object and therefore couldn't be done while
	 * constructing the interface imps */
	if (parent != NULL)
		ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, visible);
	ngtk_nc_component_map_to (obj, area);

	return obj;
}

NGtkObject* ngtk_nc_create_window_imp (NGtkBackend *self, const char* title, int visible)
{
	NGtkRectangle area = { 0, 0, COLS, LINES };
	NGtkObject *obj = create_basic_widget (self, TRUE, NULL, title, visible, &area, TRUE);

	ngtk_nc_container_create_interface (obj);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_window;
	NGTK_CONTAINER_O2F (obj) -> pack = pack_main_window;

	return obj;
}

NGtkObject* ngtk_nc_create_label_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent)
{
	NGtkRectangle area = { 0, 0, 100, 100 };
	NGtkObject *obj = create_basic_widget (self, TRUE, parent, text, visible, &area, FALSE);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_label;

	return obj;
}

NGtkObject* ngtk_nc_create_button_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent)
{
	NGtkRectangle area = { 0, 0, 100, 100 };
	NGtkObject *obj = create_basic_widget (self, TRUE, parent, text, visible, &area, TRUE);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_button;

	return obj;
}

NGtkObject* ngtk_nc_create_text_entry_imp (NGtkBackend *self, NGtkContainer *parent, const char* initial_text, int visible, int max_text_len)
{
	NGtkRectangle area = { 0, 0, 100, 100 };
	NGtkObject *obj = create_basic_widget (self, TRUE, parent, initial_text, visible, &area, TRUE);

	ngtk_basic_text_entry_create_interface (obj, initial_text, max_text_len);
	NGTK_COMPONENT_O2F (obj) -> redraw = draw_text_entry;

	return obj;
}
