/*
 * ngtk-basic-graphics.c
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

#include <string.h>
#include "ngtk-basic-graphics.h"

void ngtk_graphics_clear (NGtkGraphics *self)
{
	NGTK_GRAPHICS_O2F (self) -> clear (self);
}

int ngtk_graphics_calc_text_width (NGtkGraphics *self, const char *text, int start, int length)
{
	return NGTK_GRAPHICS_O2F (self) -> calc_text_width (self, text, start, length);
}

int ngtk_graphics_calc_text_height (NGtkGraphics *self)
{
	return NGTK_GRAPHICS_O2F (self) -> calc_text_height (self);
}

void ngtk_graphics_draw_text (NGtkGraphics *self, const char *text, int start, int length, int x, int y)
{
	NGTK_GRAPHICS_O2F (self) -> draw_text (self, text, start, length, x, y);
}

int ngtk_graphics_calc_text_cursor_end_width (NGtkGraphics *self)
{
	return NGTK_GRAPHICS_O2F (self) -> calc_text_cursor_end_width (self);
}

void ngtk_graphics_draw_text_cursor (NGtkGraphics *self, int x, int y)
{
	return NGTK_GRAPHICS_O2F (self) -> draw_text_cursor (self, x, y);
}

void ngtk_graphics_draw_frame (NGtkGraphics *self, const NGtkRectangle *rect, int is_focus_frame)
{
	NGTK_GRAPHICS_O2F (self) -> draw_frame (self, rect, is_focus_frame);
}

void ngtk_basic_graphics_draw_aligned_text (NGtkGraphics *self,
	const NGtkRectangle *rect, int ignoreXY,
	float halign, int hpad,
	float valign, int vpad,
	const char* text)
{
	int str_w, str_h, len = strlen (text);
	int xoff, yoff;

	str_w = ngtk_graphics_calc_text_width (self, text, 0, len);
	str_h = ngtk_graphics_calc_text_height (self);

	xoff = (int) (hpad + (rect->w - 2 * hpad - str_w) * halign);
	yoff = (int) (vpad + (rect->h - 2 * vpad - str_h) * valign);

	if (! ignoreXY)
	{
		xoff += rect->x;
		yoff += rect->y;
	}

	ngtk_graphics_draw_text (self, text, 0, len, xoff, yoff);
}

void ngtk_basic_graphics_draw_text_with_cursor (NGtkGraphics *self,
	const NGtkRectangle *rect, int ignoreXY,
	float halign, int hpad,
	float valign, int vpad,
	const char* text, int cursor_position)
{
	int str_w_before, str_w_after, ce_w, str_w, str_h, len = strlen (text);
	int xoff, yoff, cursor_x;
	int real_h, real_w;

	ce_w         = ngtk_graphics_calc_text_cursor_end_width (self);
	str_w_before = ngtk_graphics_calc_text_width (self, text, 0, cursor_position);
	str_w        = ngtk_graphics_calc_text_width (self, text, 0, len) + ce_w;
	str_w_after  = str_w - str_w_before;
	str_h = ngtk_graphics_calc_text_height (self);

	real_w = rect->w - 2 * hpad;
	real_h = rect->h - 2 * vpad;

	yoff = (int) (vpad + (real_h - str_h) * valign);

	/* Check for the easy case - does the text fit inside the rect? */
	if (str_w <= real_w)
	{
		xoff = (int) (hpad + (real_w - str_w) * halign);
		cursor_x = xoff + str_w_before;
	}
	/* If we reached this part, we encountered text which is too wide...
	 * So, let's work on displaying the part with the cursor! */
	else
	{
		float space_before, space_after;
		float cursor_x_f = hpad + real_w / 2.0f;

		/* Avoid missing one space unit due to integer division. Work
		 * with floats and avoid bad stuff */
		space_before = real_w / 2.0f - str_w_before;
		space_after = real_w / 2.0f - str_w_after;

		if (space_before > 0)
			cursor_x_f -= space_before;
		else if (space_after > 0)
			cursor_x_f += space_after;

		cursor_x = (int) cursor_x_f;
		xoff = cursor_x - str_w_before;
	}

	if (! ignoreXY)
	{
		xoff     += rect->x;
		yoff     += rect->y;
		cursor_x += rect->x;
	}

	ngtk_graphics_draw_text (self, text, 0, len, xoff, yoff);
	ngtk_graphics_draw_text_cursor (self, cursor_x, yoff);
}
