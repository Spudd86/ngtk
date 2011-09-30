/*
 * ngtk-xlib-base.c
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

#include "ngtk-xlib-defs.h"
#include "ngtk-xlib-base.h"

#include <stdio.h>

NGtkXlibBaseI* ngtk_xlib_base_create_interface  (NGtkXlibBackend *backend, Window xlib_wnd)
{
	NGtkInterface *in = ngtk_interface_new (NGTK_XLIBBASE_TYPE);
	NGtkXlibBaseD *xbd;

	in->d[0] = xbd = ngtk_new (NGtkXlibBaseD);
	xbd->area.x = 0;
	xbd->area.y = 0;
	xbd->area.w = 0;
	xbd->area.h = 0;
	xbd->_wnd = xlib_wnd;
	xbd->backend = backend;
	in->d_free[0] = ngtk_xlib_base_d_free;

	ngtk_xlib_backend_register_window (backend, xlib_wnd);

	return in;
}

void ngtk_xlib_base_d_free (void *d)
{
	NGtkXlibBaseD *dReal = (NGtkXlibBaseD*) d;
	NGtkListNode  *wnb;

	if (dReal->_wnd != BadWindow)
	{
		wnb = find_window (dReal->_wnd);
		ngtk_assert (wnb != NULL);
		unregister_window_and_base (wnb);

		XDestroyWindow (ngtk_xlib_get_display (), dReal->_wnd);
	}

	ngtk_free (dReal);
}


Window ngtk_xlib_base_get_window (NGtkXlibBase *self)
{
	return NGTK_XLIBBASE_O2D (self) -> _wnd;
}

void ngtk_xlib_base_put_to (NGtkXlibBase *self, const NGtkRectangle *area, int already_put)
{
	NGtkRectangle *rect = &(NGTK_XLIBBASE_O2D (self) -> area);
	Window         wnd  = ngtk_xlib_base_get_window (self);

	rect->x = area->x;
	rect->y = area->y;
	rect->w = area->w;
	rect->h = area->h;

	if (! already_put)
	{
		XMoveWindow (ngtk_xlib_get_display (), wnd, area->x, area->y);
		XResizeWindow (ngtk_xlib_get_display (), wnd, area->w, area->h);
	}
}

const NGtkRectangle*  ngtk_xlib_base_get_relative_rect (NGtkXlibBase *self)
{
	return &(NGTK_XLIBBASE_O2D (self) -> area);
}

NGtkXlibBackend* ngtk_xlib_base_get_backend (NGtkXlibBase *self)
{
	return NGTK_XLIBBASE_O2D (self) -> backend;
}

NGtkXlibBase* ngtk_xlib_base_call_on_window_destroyed (Window xlib_wnd)
{
	NGtkXlibBaseI *xb = ngtk_xlib_backend_unregister_window (backend, xlib_wnd);
	return ngtk_interface_get_object (xb);
}
