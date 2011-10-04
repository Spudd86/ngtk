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
	ngtk_nc_base_map_to (self, &new_area);

	if (NGTK_BASIC_CONTAINER_O2D(self)->layout != NULL)
		ngtk_layout_pack (NGTK_BASIC_CONTAINER_O2D(self)->layout, self, COLS, LINES);

	/* NCURSES has a bug that means that if any WINDOW became partially
	 * outside the screen, it will erdraaw uglylly. So we must refresh
	 * the windows when resizing to avoid this.
	 *
	 * The put_to function of the ncbase class will delete the existing
	 * WINDOW and will crate a new one. We will do this for all the
	 * children since we have no (easy) way to know which one was
	 * resized by the packing and which one wasn't.
	 *
	 * TODO: for future versions, consider using pads instead of windows
	 */
	ngtk_list_foreach (iter, ngtk_container_get_children (self))
	{
		NGtkComponent *child = (NGtkComponent*) iter->data;
		ngtk_nc_base_map_to (child, ngtk_nc_base_get_abs_rect (child));
	}

	/* Note that the redraw method also redraws the children */
	ngtk_component_redraw (self);
}

NGtkObject* ngtk_nc_create_label_imp (const char* title, int visible)
{
	NGtkObject *obj = ngtk_object_new ();

	NGtkInterface *in_base = ngtk_nc_base_create_interface ();
	NGtkInterface *in_comp = ngtk_nc_component_create_interface (TRUE, NULL, title, visible);
	NGtkInterface *in_evgn = ngtk_nc_event_generator_create_interface ();

	ngtk_object_implement (obj, in_base);
	ngtk_object_implement (obj, in_comp);
	ngtk_object_implement (obj, in_evgn);

	return obj;
}

NGtkObject* ngtk_nc_create_window_imp (const char* title, int visible)
{
	NGtkRectangle entire_screen;

	NGtkObject *obj = ngtk_object_new ();

	NGtkInterface *in_base = ngtk_nc_base_create_interface ();
	NGtkInterface *in_comp = ngtk_nc_component_create_interface (TRUE, NULL, title, visible);
	NGtkInterface *in_cont = ngtk_nc_container_create_interface ();
	NGtkInterface *in_evgn = ngtk_nc_event_generator_create_interface ();

	ngtk_object_implement (obj, in_base);
	ngtk_object_implement (obj, in_comp);
	ngtk_object_implement (obj, in_cont);
	ngtk_object_implement (obj, in_evgn);

	entire_screen.x = 0;
	entire_screen.y = 0;
	entire_screen.w = COLS;
	entire_screen.h = LINES;

	ngtk_nc_base_map_to (obj, &entire_screen);
	NGTK_CONTAINER_O2F (obj)->pack = pack_main_window;

	return obj;
}
