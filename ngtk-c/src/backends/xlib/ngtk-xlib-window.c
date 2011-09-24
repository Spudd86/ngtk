#include "ngtk-xlib.h"

#if FALSE
static void pack_main_window (NGtkContainer *self)
{
	NGtkRectangle new_area;
	NGtkListNode  *iter;
	
	new_area.x = new_area.y = 0;
	getmaxyx (stdscr, new_area.h, new_area.w);
	ngtk_xlib_base_map_to (self, &new_area);

	if (NGTK_BASIC_CONTAINER_O2D(self)->layout != NULL)
		ngtk_layout_pack (NGTK_BASIC_CONTAINER_O2D(self)->layout, self, COLS, LINES);

	ngtk_component_redraw (self);

	ngtk_list_foreach (iter, ngtk_container_get_children (self))
	{
		ngtk_component_redraw ((NGtkComponent*) iter->data);
	}
}

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

	ngtk_xlib_base_put_to (obj, &entire_screen);
//	NGTK_CONTAINER_O2F (obj)->pack = pack_main_window;

	XSelectInput (ngtk_xlib_get_display (), xlib_wnd, NGTK_XLIB_EVENT_MASK);


	return obj;
}
