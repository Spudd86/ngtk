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
#include "ngtk-xlib-backend.h"

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

	ngtk_xlib_backend_register_window (backend, xlib_wnd, in);

	return in;
}


void ngtk_xlib_base_d_free (void *d)
{
	NGtkXlibBaseD *dReal = (NGtkXlibBaseD*) d;

	if (dReal->_wnd != BadWindow)
	{
		ngtk_xlib_backend_unregister_window (dReal->backend, dReal->_wnd);
		XDestroyWindow (ngtk_xlib_backend_get_display (dReal->backend), dReal->_wnd);
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
	NGtkBackend   *xbd  = ngtk_xlib_base_get_backend (self);

	rect->x = area->x;
	rect->y = area->y;
	rect->w = area->w;
	rect->h = area->h;

	if (! already_put)
	{
		XMoveWindow (ngtk_xlib_backend_get_display (xbd), wnd, area->x, area->y);
		ngtk_debug (xbd, "XMoveWindow (%p, %lu, %d, %d)", ngtk_xlib_backend_get_display (xbd), wnd, area->x, area->y);
		XResizeWindow (ngtk_xlib_backend_get_display (xbd), wnd, area->w, area->h);
		ngtk_debug (xbd, "XResizeWindow (%p, %lu, %lu, %lu)", ngtk_xlib_backend_get_display (xbd), wnd, area->w, area->h);
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

NGtkXlibBackend* ngtk_xlib_base_get_backend2 (NGtkXlibBaseI *self)
{
	return NGTK_XLIBBASE_I2D (self) -> backend;
}


NGtkXlibBase* ngtk_xlib_base_call_on_window_destroyed (NGtkXlibBackend *backend, Window xlib_wnd)
{
	NGtkXlibBaseI *xb = ngtk_xlib_backend_unregister_window (backend, xlib_wnd);
	NGTK_XLIBBASE_I2D (xb) -> _wnd = BadWindow;
	return ngtk_interface_get_object (xb);
}
