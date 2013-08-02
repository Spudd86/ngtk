/*
 * ngtk-xlib-graphics.c - Part of the NGtk library
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

#include "ngtk-xlib.h"

/* A class of wrappers around XLib graphics, to attach them to common
 * shared widget drawing logic. Unless you are interested in drawing
 * lines and stuff, skip this */

static void ngtk_xlib_graphics_data_init (NGtkXlibGraphicsD *dd, NGtkComponent *comp);
static void ngtk_xlib_graphics_destroy (NGtkGraphics *self);

NGtkXlibGraphics* ngtk_xlib_graphics_create (NGtkComponent *comp)
{
	NGtkXlibBackend *backend = ngtk_base_get_backend (comp);

	NGtkObject      *obj = ngtk_object_new ();
	NGtkGraphicsI   *inG;

	NGtkXlibGraphicsD *xgd = NULL;

	ngtk_basic_base_create_interface (obj, backend);

	inG = ngtk_interface_new (obj, NGTK_GRAPHICS_TYPE);

	xgd = ngtk_new (NGtkXlibGraphicsD);
	inG->imp_data[0] = xgd;
	ngtk_xlib_graphics_data_init (xgd, comp);
	inG->imp_data_free[0] = ngtk_free;

	inG->functions = ngtk_new (NGtkGraphicsF);
	NGTK_GRAPHICS_I2F (inG) -> clear = ngtk_xlib_graphics_clear;
	NGTK_GRAPHICS_I2F (inG) -> calc_text_width = ngtk_xlib_graphics_calc_text_width;
	NGTK_GRAPHICS_I2F (inG) -> calc_text_height = ngtk_xlib_graphics_calc_text_height;
	NGTK_GRAPHICS_I2F (inG) -> draw_text = ngtk_xlib_graphics_draw_text;
	NGTK_GRAPHICS_I2F (inG) -> calc_text_cursor_end_width = ngtk_xlib_graphics_calc_text_cursor_end_width;
	NGTK_GRAPHICS_I2F (inG) -> draw_text_cursor = ngtk_xlib_graphics_draw_text_cursor;
	NGTK_GRAPHICS_I2F (inG) -> draw_frame = ngtk_xlib_graphics_draw_frame;
	inG->functions_free = ngtk_free;

	ngtk_object_push_destructor (obj, ngtk_xlib_graphics_destroy);

	return obj;
}

static void ngtk_xlib_graphics_data_init (NGtkXlibGraphicsD *dd, NGtkComponent *comp)
{
	int enabled = ngtk_component_get_enabled (comp);
	int screen;
	GC  default_gc;
	NGtkXlibBackend *backend = ngtk_base_get_backend (comp);

	NGtkXlibColorName fg = enabled ? NGTK_XLIB_BLACK : NGTK_XLIB_GRAY;

	dd->display = ngtk_xlib_backend_get_X_display (backend);
	dd->window  = ngtk_xlib_component_get_window (comp);
	dd->gc      = XCreateGC (dd->display, dd->window, 0, 0);

	dd->rect    = ngtk_xlib_component_get_rect (comp);

	dd->fg      = ngtk_xlib_backend_get_X_color (backend, fg);

	screen      = ngtk_xlib_backend_get_X_screen (backend);
	default_gc  = DefaultGC (dd->display, screen);

	/* In theory, to get the default Font, pass the default GC to
	 * XQueryFont, instead of passing an actual font ID (as returned from
	 * XGetGCValues). Created GC's simply do not have a font set to them
	 * and only the default GC has.
	 *
	 * See (merge the link into one line):
	 *   http://books.google.co.il/books?id=d8tByjvMmIwC&lpg=PA146
	 *   &ots=mnQJfk48K5&dq=xlib%20get%20default%20font&hl=en&pg=PA146
	 *   #v=onepage&q=xlib%20get%20default%20font&f=false
	 */
	dd->font    = XQueryFont (dd->display, XGContextFromGC (default_gc));
	/* The Glyphs (shapes) of a font are in coordinates relative to
	 * some imaginary line called baseline. The ascent is how much above
	 * the line does the highest glyph go, and the descent is the how
	 * much below the line do glyphs go. Therefor, their sum is the
	 * maximal height of the text */
	dd->font_height = dd->font->ascent + dd->font->descent;

	XSetForeground (dd->display, dd->gc, dd->fg);
}

static void ngtk_xlib_graphics_destroy (NGtkGraphics *self)
{
	NGtkXlibGraphicsD *dd = NGTK_XLIB_GRAPHICS_O2D (self);

	XFreeFontInfo (NULL, dd->font, 1);
	XFreeGC (dd->display, dd->gc);

	ngtk_interface_detach_and_free (ngtk_object_cast (self, NGTK_GRAPHICS_TYPE));
}

void ngtk_xlib_graphics_clear (NGtkGraphics *self)
{
	NGtkXlibGraphicsD *dd = NGTK_XLIB_GRAPHICS_O2D (self);
	XClearWindow (dd->display, dd->window);
}

int  ngtk_xlib_graphics_calc_text_width  (NGtkGraphics *self, const char *text, int start, int length)
{
	NGtkXlibGraphicsD *dd = NGTK_XLIB_GRAPHICS_O2D (self);
	return XTextWidth (dd->font, &text[start], length);
}

int ngtk_xlib_graphics_calc_text_height (NGtkGraphics *self)
{
	NGtkXlibGraphicsD *dd = NGTK_XLIB_GRAPHICS_O2D (self);
	return dd->font_height;
}
void ngtk_xlib_graphics_draw_text (NGtkGraphics *self, const char *text, int start, int length, int x, int y)
{
	NGtkXlibGraphicsD *dd = NGTK_XLIB_GRAPHICS_O2D (self);
	/* Since the point we specify is the origin (the y is the baseline),
	 * we must add the ascent if we wish to specify the top side)
	 */
	XDrawString (dd->display, dd->window, dd->gc, x, y + dd->font->ascent, &text[start], length);
}

int ngtk_xlib_graphics_calc_text_cursor_end_width (NGtkGraphics *self)
{
	return 1;
}

void ngtk_xlib_graphics_draw_text_cursor (NGtkGraphics *self, int x, int y)
{
	NGtkXlibGraphicsD *dd = NGTK_XLIB_GRAPHICS_O2D (self);
	XGCValues oldfunc, newfunc;

	XGetGCValues (dd->display, dd->gc, GCFunction, &oldfunc);
	newfunc.function = GXinvert;
	XChangeGC (dd->display, dd->gc, GCFunction, &newfunc);

	XDrawLine (dd->display, dd->window, dd->gc, x, y, x, y + dd->font_height);

	XChangeGC (dd->display, dd->gc, GCFunction, &oldfunc);
}

void ngtk_xlib_graphics_draw_frame (NGtkGraphics *self, const NGtkRectangle *rect, int is_focus_frame)
{
	NGtkXlibGraphicsD *dd = NGTK_XLIB_GRAPHICS_O2D (self);
	XDrawRectangle (dd->display, dd->window, dd->gc, 0, 0, dd->rect->w - 1, dd->rect->h - 1);
	if (is_focus_frame)
		XDrawRectangle (dd->display, dd->window, dd->gc, 1, 1, dd->rect->w - 3, dd->rect->h - 3);
}
