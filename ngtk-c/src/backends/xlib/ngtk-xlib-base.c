#include "ngtk-xlib-defs.h"
#include "ngtk-xlib-base.h"

NGtkXlibBaseI* ngtk_xlib_base_create_interface  (Window xlib_wnd)
{
	NGtkInterface *in = ngtk_interface_new (NGTK_XLIBBASE_TYPE);
	NGtkXlibBaseD *xbd;
	
	in->d[0] = xbd = ngtk_new (NGtkXlibBaseD);
	xbd->area.x = 0;
	xbd->area.y = 0;
	xbd->area.w = 0;
	xbd->area.h = 0;
	xbd->wnd = xlib_wnd;
	in->d_free[0] = ngtk_xlib_base_d_free;

	return in;
}

void ngtk_xlib_base_d_free (void *d)
{
	NGtkXlibBaseD *dReal = (NGtkXlibBaseD*) d;

	if (dReal->wnd != BadWindow)
		XDestroyWindow (ngtk_xlib_get_display (), dReal->wnd);

	ngtk_free (dReal);
}


Window ngtk_xlib_base_get_window (NGtkXlibBase *self)
{
	return NGTK_XLIBBASE_O2D (self) -> wnd;
}

void ngtk_xlib_base_put_to (NGtkXlibBase *self, const NGtkRectangle *area)
{
	NGtkRectangle *rect = &(NGTK_XLIBBASE_O2D (self) -> area);
	Window         wnd  = NGTK_XLIBBASE_O2D (self) -> wnd;

	rect->x = area->x;
	rect->y = area->y;
	rect->w = area->w;
	rect->h = area->h;

	XMoveWindow (ngtk_xlib_get_display (), wnd, area->x, area->y);
	XResizeWindow (ngtk_xlib_get_display (), wnd, area->w, area->h);
}

const NGtkRectangle*  ngtk_xlib_base_get_relative_rect (NGtkXlibBase *self)
{
	return &(NGTK_XLIBBASE_O2D (self) -> area);
}
