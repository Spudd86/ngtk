#include "ngtk-xlib.h"
#include <stdio.h>

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
	new_area.w = h;
	
	ngtk_xlib_base_put_to (self, &new_area, TRUE);

	if (NGTK_BASIC_CONTAINER_O2D(self)->layout != NULL)
		ngtk_layout_pack (NGTK_BASIC_CONTAINER_O2D(self)->layout, self, new_area.w, new_area.h);

	ngtk_component_redraw (self);

	ngtk_list_foreach (iter, ngtk_container_get_children (self))
	{
		ngtk_component_redraw ((NGtkComponent*) iter->data);
	}
}

#if FALSE
NGtkObject* ngtk_xlib_create_label_imp (const char* title, int visible)
{
	NGtkObject *obj = ngtk_object_new ();

	NGtkInterface *in_base = ngtk_xlib_base_create_interface ();
	NGtkInterface *in_comp = ngtk_xlib_component_create_interface (TRUE, NULL, title, visible);
	NGtkInterface *in_evgn = ngtk_xlib_event_generator_create_interface ();

	ngtk_object_implement (obj, in_base);
	ngtk_object_implement (obj, in_comp);
	ngtk_object_implement (obj, in_evgn);

	return obj;
}
#endif

void checkers_draw (NGtkXlibBase *xb)
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
NGtkObject* ngtk_xlib_create_window_imp (const char* title, int visible)
{
	Window xlib_wnd = XCreateSimpleWindow (
		ngtk_xlib_get_display (),     /* Connection to the X server */
		ngtk_xlib_get_root_window (), /* Parent window */
		50, 50,                       /* (X,Y) of Top Left Corner */
		200, 200,                     /* Width, Height of the window */
		0,                            /* Border width of the window */
		ngtk_xlib_get_color (NGTK_XLIB_BLACK), /* Border color */
		ngtk_xlib_get_color (NGTK_XLIB_WHITE) /* Background color */
		);
		
	NGtkRectangle entire_screen;
	NGtkObject *obj = ngtk_object_new ();

	NGtkInterface *in_base = ngtk_xlib_base_create_interface (xlib_wnd);
	NGtkInterface *in_comp = ngtk_xlib_component_create_interface (TRUE, NULL, title, visible);
	NGtkInterface *in_cont = ngtk_xlib_container_create_interface ();
	NGtkInterface *in_evgn = ngtk_xlib_event_generator_create_interface ();

	ngtk_object_implement (obj, in_base);
	ngtk_object_implement (obj, in_comp);
	ngtk_object_implement (obj, in_cont);
	ngtk_object_implement (obj, in_evgn);

	entire_screen.x = 50;
	entire_screen.y = 50;
	entire_screen.w = 200;
	entire_screen.h = 200;

	ngtk_xlib_base_put_to (obj, &entire_screen, FALSE);
	NGTK_CONTAINER_O2F (obj)->pack = pack_main_window;

	XSelectInput (ngtk_xlib_get_display (), xlib_wnd, NGTK_XLIB_EVENT_MASK | ResizeRedirectMask);

	NGTK_COMPONENT_O2F (obj) -> redraw = checkers_draw;
	
	return obj;
}
