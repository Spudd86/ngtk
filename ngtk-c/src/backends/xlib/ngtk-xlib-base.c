#include "ngtk-xlib-base.h"

NGtkXlibBaseI* ngtk_xlib_base_create_interface  ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_XLIBBASE_TYPE);
	NGtkXlibBaseD  xbd;
	
	in->d[0] = xbd = ngtk_new (NGtkXlibBaseD);
	xbd->area.x = 0;
	xbd->area.y = 0;
	xbd->area.w = 0;
	xbd->area.h = 0;
	xbd->wnd = NULL;
	in->d_free[0] = ngtk_xlib_base_d_free;

	return in;
}

void ngtk_xlib_base_d_free (void *d)
{
	NGtkXlibBaseD *dReal = (NGtkXlibBaseD*) d;

	if (dReal->wnd != NULL)
		XDestroyWindow ()

	ngtk_free (dReal);
}


WINDOW* ngtk_xlib_base_get_window (NGtkXlibBase *self)
{
	return NGTK_NCBASE_O2D (self) -> wnd;
}

void ngtk_xlib_base_unmap_window (NGtkXlibBase *self)
{
	WINDOW** wnd = &(NGTK_NCBASE_O2D (self) -> wnd);
	if (*wnd != NULL)
	{
		delwin (*wnd);
		*wnd = NULL;
	}
}

void ngtk_xlib_base_map_to (NGtkXlibBase *self, const NGtkRectangle *area)
{
	NGtkRectangle *rect = &(NGTK_NCBASE_O2D (self) -> area);
	WINDOW       **wnd  = &(NGTK_NCBASE_O2D (self) -> wnd);

	rect->x = area->x;
	rect->y = area->y;
	rect->w = area->w;
	rect->h = area->h;

#if FALSE
	ngtk_xlib_base_unmap_window (self);
	*wnd = newwin (area->h, area->w, area->y, area->x);
#else
	if (*wnd == NULL)
		*wnd = newwin (area->h, area->w, area->y, area->x);
	else
	{
		wresize (*wnd, area->h, area->w);
		wmove (*wnd, area->x, area->y);
	}
#endif
}

const NGtkRectangle*  ngtk_xlib_base_get_abs_rect (NGtkXlibBase *self)
{
	return &(NGTK_NCBASE_O2D (self) -> area);
}

void ngtk_xlib_base_clear_window_area (NGtkXlibBase *self)
{
	wclear (NGTK_NCBASE_O2D (self) -> wnd);
	ngtk_xlib_base_publish_window (self);
}
/** Publish the window content to the screen */
void ngtk_xlib_base_publish_window (NGtkXlibBase *self)
{
	overwrite (NGTK_NCBASE_O2D (self) -> wnd, stdscr);
	refresh ();
}
