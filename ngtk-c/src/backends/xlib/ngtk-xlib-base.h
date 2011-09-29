/*
 * ngtk-xlib-base.h
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

#ifndef __NGtk_xlib_base_h__
#define __NGtk_xlib_base_h__

#include <X11/Xlib.h>
#include "../../utils/ngtk-utils.h"
#include "ngtk-xlib-widget-types.h"

/* The class in this file is an abstract class with final methods. This
 * means it should not be used directly as the only class of a
 * NGtkObject, and also that it's methods should not be overriden (and
 * therefore there is not function pointer struct).
 */

typedef struct _ngtk_xlib_base_d {
	NGtkRectangle  area;
	Window        _wnd; /* This field must not be accessed directly! It
	                     * must be a constant field so that the mapping
	                     * we will maintain from Window->NGtkListBaseI
	                     * will remain valid */
} NGtkXlibBaseD;

#define NGTK_XLIBBASE_O2D(comp) NGTK_O2D_CAST(comp,NGTK_XLIBBASE_TYPE,NGtkXlibBaseD,0)
#define NGTK_XLIBBASE_I2D(comp) NGTK_I2D_CAST(comp,NGTK_XLIBBASE_TYPE,NGtkXlibBaseD,0)

NGtkXlibBaseI*        ngtk_xlib_base_create_interface  (Window xlib_wnd);
void                  ngtk_xlib_base_d_free            (void *d);

Window                ngtk_xlib_base_get_window        (NGtkXlibBase *self);
const NGtkRectangle*  ngtk_xlib_base_get_relative_rect (NGtkXlibBase *self);

void                  ngtk_xlib_base_put_to            (NGtkXlibBase *self, const NGtkRectangle *area, int already_put);

NGtkXlibBase*         ngtk_xlib_base_get_for_window    (Window xlib_wnd);
NGtkXlibBase*         ngtk_xlib_base_call_on_window_destroyed (Window xlib_wnd);
#endif
