/*
 * ngtk-nc-graphics.c
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

static void ngtk_nc_graphics_destroy (NGtkGraphics *self);

NGtkNcGraphics* ngtk_nc_graphics_create (NGtkComponent *comp)
{
	NGtkNcBackend *backend = ngtk_base_get_backend (comp);

	NGtkObject      *obj = ngtk_object_new ();
	NGtkGraphicsI   *inG;

	NGtkNcGraphicsD *ngd = NULL;

	ngtk_basic_base_create_interface (obj, backend);

	inG = ngtk_interface_new (obj, NGTK_GRAPHICS_TYPE);

	inG->imp_data[0] = ngd = ngtk_new (NGtkNcGraphicsD);
	ngd->wnd = ngtk_nc_component_get_window (comp);
	inG->imp_data_free[0] = ngtk_free;

	inG->functions = ngtk_new (NGtkGraphicsF);
	NGTK_GRAPHICS_I2F (inG) -> clear = ngtk_nc_graphics_clear;
	NGTK_GRAPHICS_I2F (inG) -> calc_text_width = ngtk_nc_graphics_calc_text_width;
	NGTK_GRAPHICS_I2F (inG) -> calc_text_height = ngtk_nc_graphics_calc_text_height;
	NGTK_GRAPHICS_I2F (inG) -> draw_text = ngtk_nc_graphics_draw_text;
	NGTK_GRAPHICS_I2F (inG) -> calc_text_cursor_end_width = ngtk_nc_graphics_calc_text_cursor_end_width;
	NGTK_GRAPHICS_I2F (inG) -> draw_text_cursor = ngtk_nc_graphics_draw_text_cursor;
	NGTK_GRAPHICS_I2F (inG) -> draw_frame = ngtk_nc_graphics_draw_frame;
	inG->functions_free = ngtk_free;

	ngtk_object_push_destructor (obj, ngtk_nc_graphics_destroy);

	ngtk_assert (ngtk_object_is_a (obj, NGTK_GRAPHICS_TYPE));

	return obj;
}

static void ngtk_nc_graphics_destroy (NGtkGraphics *self)
{
	ngtk_interface_detach_and_free (ngtk_object_cast (self, NGTK_GRAPHICS_TYPE));
}

void ngtk_nc_graphics_clear (NGtkGraphics *self)
{
	NGtkNcGraphicsD *dd = NGTK_NC_GRAPHICS_O2D (self);
	wclear (dd->wnd);
}

int  ngtk_nc_graphics_calc_text_width  (NGtkGraphics *self, const char *text, int start, int length)
{
	return length;
}

int ngtk_nc_graphics_calc_text_height (NGtkGraphics *self)
{
	return 1;
}

void ngtk_nc_graphics_draw_text (NGtkGraphics *self, const char *text, int start, int length, int x, int y)
{
	NGtkNcGraphicsD *dd = NGTK_NC_GRAPHICS_O2D (self);
	int i;
	int width, height;
	int begin_at, short_len;

	getmaxyx (dd->wnd, height, width);

	if (y >= height || y < 0)
		return;

	begin_at  = start - MIN (0, x);
	short_len = MIN(width, length - begin_at) - 1;

	for (i = begin_at; i <= begin_at + short_len; i++)
		mvwaddch (dd->wnd, y, x + i, text[i]);
}

int ngtk_nc_graphics_calc_text_cursor_end_width (NGtkGraphics *self)
{
	return 1;
}

void ngtk_nc_graphics_draw_text_cursor (NGtkGraphics *self, int x, int y)
{
	NGtkNcGraphicsD *dd = NGTK_NC_GRAPHICS_O2D (self);
	mvwchgat (dd->wnd, y, x, 1, A_REVERSE, 0, NULL);
}

void ngtk_nc_graphics_draw_frame (NGtkGraphics *self, const NGtkRectangle *rect, int is_focus_frame)
{
	NGtkNcGraphicsD *dd = NGTK_NC_GRAPHICS_O2D (self);

	if (is_focus_frame)
		wattron (dd->wnd, A_BOLD);
	box (dd->wnd, 0, 0);
	wattroff (dd->wnd, A_BOLD);
}
