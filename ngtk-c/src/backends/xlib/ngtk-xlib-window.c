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

static void pack_main_window (NGtkContainer *self)
{
	NGtkRectangle new_area;
	NGtkListNode  *iter;
	unsigned int w, h;

	Window root;
	unsigned int border_width, depth;

	new_area.x = new_area.y = 0;
	XGetGeometry (ngtk_xlib_get_display (), ngtk_xlib_base_get_window (self), &root,
		&new_area.x, &new_area.y, &w, &h, &border_width, &depth);
	new_area.w = w;
	new_area.h = h;

	ngtk_xlib_base_put_to (self, &new_area, TRUE);

	if (NGTK_BASIC_CONTAINER_O2D(self)->layout != NULL)
		ngtk_layout_pack (NGTK_BASIC_CONTAINER_O2D(self)->layout, self, new_area.w, new_area.h);

	ngtk_component_redraw (self);

	ngtk_list_foreach (iter, ngtk_container_get_children (self))
	{
		ngtk_component_redraw ((NGtkComponent*) iter->data);
	}
}

static void draw_aligned_text (Display *disp, Drawable d, GC gc,
	const NGtkRectangle *rect, int ignoreXY,
	float halign, int hpad,
	float valign, int vpad,
	const char* text)
{
	XFontStruct *font;
	int str_w, str_h, len = strlen (text);
	int xoff, yoff;

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

	font = XQueryFont (disp, XGContextFromGC (DefaultGC (disp, ngtk_xlib_get_screen ())));
	ngtk_assert (font != NULL);
	str_w = XTextWidth (font, text, len);
	/* The Glyphs (shapes) of a font are in coordinates relative to
	 * some imaginary line called baseline. The ascent is how much above
	 * the line does the highest glyph go, and the descent is the how
	 * much below the line do glyphs go. Therefor, their sum is the
	 * maximal height of the text */
	str_h = font->ascent + font->descent;

	xoff = (int) (hpad + (rect->w - 2 * hpad - str_w) * halign);
	yoff = (int) (vpad + (rect->h - 2 * vpad - str_h) * valign);
	if (! ignoreXY)
	{
		xoff += rect->x;
		yoff += rect->y;
	}

	/* Since the point we specify is the origin (the y is the baseline),
	 * we must add the ascent if we wish to specify the top side)
	 */
	XDrawString (disp, d, gc, xoff, yoff + font->ascent, text, len);
	XFreeFontInfo (NULL, font, 1);
}
#if FALSE
static void checkers_draw (NGtkXlibBase *xb)
{
	Window wnd = ngtk_xlib_base_get_window (xb);
	Display* disp = ngtk_xlib_get_display ();
	GC gc = XCreateGC (disp, wnd, 0, 0);

	int w = ngtk_xlib_base_get_relative_rect (xb)->w;
	int h = ngtk_xlib_base_get_relative_rect (xb)->h;

	int i, j;

	ngtk_assert (! (gc < 0));

	fprintf (stderr, "Printing checkers on indow %d %dx%d\n", (int)wnd, w, h);

	XSetFillStyle (disp, gc, FillSolid);

	XSetForeground (disp, gc, ngtk_xlib_get_color (NGTK_XLIB_BLACK));
	XFillRectangle (disp, wnd, gc, 0, 0, w, h);

	XSetForeground (disp, gc, ngtk_xlib_get_color (NGTK_XLIB_WHITE));
	for (i = 0; i * 20 < h; i++)
		for (j = 0; j * 20 < w; j++)
		{
			if ((i + j) % 2 == 0)
				XFillRectangle (disp, wnd, gc, j * 20, i * 20, 20, 20);
		}

	XFreeGC (disp, gc);
}
#endif
static void draw_window (NGtkComponent *window)
{
	Display* disp = ngtk_xlib_get_display ();
	Window wnd = ngtk_xlib_base_get_window (window);
	GC gc = XCreateGC (disp, wnd, 0, 0);

	const NGtkRectangle *rect = ngtk_xlib_base_get_relative_rect (window);

	XClearArea (disp, wnd, 0, 0, rect->w, rect->h, FALSE);

	XFreeGC (disp, gc);

	ngtk_basic_component_redraw (window);
}

static void draw_label (NGtkComponent *label)
{
	Display* disp = ngtk_xlib_get_display ();
	Window wnd = ngtk_xlib_base_get_window (label);
	GC gc = XCreateGC (disp, wnd, 0, 0);

	const NGtkRectangle *rect = ngtk_xlib_base_get_relative_rect (label);
	const char *text = ngtk_component_get_text (label);

	XClearArea (disp, wnd, 0, 0, rect->w, rect->h, FALSE);
	draw_aligned_text (disp, wnd, gc, rect, TRUE, 0, 2, 0.5f, 2, text);

	XFreeGC (disp, gc);
}

static void draw_button (NGtkComponent *but)
{
	Display* disp = ngtk_xlib_get_display ();
	Window wnd = ngtk_xlib_base_get_window (but);
	GC gc = XCreateGC (disp, wnd, 0, 0);

	const NGtkRectangle *rect = ngtk_xlib_base_get_relative_rect (but);
	const char *text = ngtk_component_get_text (but);

	XClearArea (disp, wnd, 0, 0, rect->w, rect->h, FALSE);
	draw_aligned_text (disp, wnd, gc, rect, TRUE, 0.5f, 2, 0.5f, 2, text);
	XDrawRectangle (disp, wnd, gc, 0, 0, rect->w - 1, rect->h - 1);

	XFreeGC (disp, gc);
}

static NGtkObject* create_basic_widget (int enabled, NGtkContainer *parent, const char* text, int visible, const NGtkRectangle *area)
{
	Window wnd = XCreateSimpleWindow (
		ngtk_xlib_get_display (),     /* Connection to the X server */
		parent == NULL ? ngtk_xlib_get_root_window () : ngtk_xlib_base_get_window (parent), /* Parent window */
		area->x, area->y,                       /* (X,Y) of Top Left Corner */
		area->w, area->h,                     /* Width, Height of the window */
		0,                            /* Border width of the window */
		ngtk_xlib_get_color (NGTK_XLIB_BLACK), /* Border color */
		ngtk_xlib_get_color (NGTK_XLIB_WHITE) /* Background color */
		);

	NGtkObject *obj = ngtk_object_new ();
	NGtkInterface *in_base, *in_comp, *in_evgn;

	in_base = ngtk_xlib_base_create_interface (wnd);
	ngtk_object_implement (obj, in_base);

	in_comp = ngtk_xlib_component_create_interface (enabled, parent, text, visible);
	ngtk_object_implement (obj, in_comp);

	in_evgn = ngtk_xlib_event_generator_create_interface ();
	ngtk_object_implement (obj, in_evgn);

	/* Now, do the parts of the construction that depend on the
	 * existance of a whole object and therefore couldn't be done while
	 * constructing the interface imps */
	if (parent != NULL)
		ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, visible);
	ngtk_xlib_base_put_to (obj, area, TRUE);

	XSelectInput (ngtk_xlib_get_display (), wnd, NGTK_XLIB_EVENT_MASK);

	return obj;
}

NGtkObject* ngtk_xlib_create_window_imp (const char* title, int visible)
{
	NGtkRectangle area = { 50, 50, 200, 200 };
	NGtkObject *obj = create_basic_widget (TRUE, NULL, title, visible, &area);

	NGtkInterface *in_cont = ngtk_xlib_container_create_interface ();
	ngtk_object_implement (obj, in_cont);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_window;
	NGTK_CONTAINER_O2F (obj) -> pack = pack_main_window;

	return obj;
}

NGtkObject* ngtk_xlib_create_label_imp (const char* text, int visible, NGtkContainer *parent)
{
	NGtkRectangle area = { 50, 50, 200, 200 };
	NGtkObject *obj = create_basic_widget (TRUE, parent, text, visible, &area);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_label;

	return obj;
}

NGtkObject* ngtk_xlib_create_button_imp (const char* text, int visible, NGtkContainer *parent)
{
	NGtkRectangle area = { 50, 50, 200, 200 };
	NGtkObject *obj = create_basic_widget (TRUE, parent, text, visible, &area);

	NGTK_COMPONENT_O2F (obj) -> redraw = draw_button;

	return obj;
}
