#include "ngtk-nc-base.h"

NGtkNcBaseI*   ngtk_nc_base_create_interface  ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_NCBASE_TYPE);
	NGtkNcBaseD   *nbd;
	
	in->d[0] = nbd = ngtk_new (NGtkNcBaseD);
	nbd->area.x = 0;
	nbd->area.y = 0;
	nbd->area.w = 0;
	nbd->area.h = 0;
	nbd->wnd = NULL;
	in->d_free[0] = ngtk_nc_base_d_free;

	return in;
}

void ngtk_nc_base_d_free (void *d)
{
	NGtkNcBaseD   *dReal = (NGtkNcBaseD*) d;

	if (dReal->wnd != NULL)
		delwin (dReal->wnd);

	ngtk_free (dReal);
}


WINDOW* ngtk_nc_base_get_window (NGtkNcBase *self)
{
	return NGTK_NCBASE_O2D (self) -> wnd;
}

void ngtk_nc_base_unmap_window (NGtkNcBase *self)
{
	WINDOW** wnd = &(NGTK_NCBASE_O2D (self) -> wnd);
	if (*wnd != NULL)
	{
		delwin (*wnd);
		*wnd = NULL;
	}
}

void ngtk_nc_base_map_to (NGtkNcBase *self, const NGtkRectangle *area)
{
	NGtkRectangle *rect = &(NGTK_NCBASE_O2D (self) -> area);
	WINDOW       **wnd  = &(NGTK_NCBASE_O2D (self) -> wnd);

	rect->x = area->x;
	rect->y = area->y;
	rect->w = area->w;
	rect->h = area->h;

#if TRUE
	ngtk_nc_base_unmap_window (self);
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

const NGtkRectangle*  ngtk_nc_base_get_abs_rect (NGtkNcBase *self)
{
	return &(NGTK_NCBASE_O2D (self) -> area);
}

void ngtk_nc_base_clear_window_area (NGtkNcBase *self)
{
	wclear (NGTK_NCBASE_O2D (self) -> wnd);
	ngtk_nc_base_publish_window (self);
}
/** Publish the window content to the screen */
void ngtk_nc_base_publish_window (NGtkNcBase *self)
{
	overwrite (NGTK_NCBASE_O2D (self) -> wnd, stdscr);
	refresh ();
}
