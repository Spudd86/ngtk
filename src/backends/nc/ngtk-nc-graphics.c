/*
 * ngtk-nc-graphics.c - Part of the NGtk library
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
