/*
 * ngtk-nc-base.h
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

#ifndef __NGtk_nc_base_h__
#define __NGtk_nc_base_h__

#include <ncurses.h>
#include "../../utils/ngtk-utils.h"
#include "ngtk-nc-widget-types.h"

/* The class in this file is an abstract class with final methods. This
 * means it should not be used directly as the only class of a
 * NGtkObject, and also that it's methods should not be overriden (and
 * therefore there is not function pointer struct).
 */

typedef struct _ngtk_win_base_d {
	NGtkRectangle  area;
	WINDOW        *wnd;
} NGtkNcBaseD;

#define NGTK_NCBASE_O2D(comp) NGTK_O2D_CAST(comp,NGTK_NCBASE_TYPE,NGtkNcBaseD,0)
#define NGTK_NCBASE_I2D(comp) NGTK_I2D_CAST(comp,NGTK_NCBASE_TYPE,NGtkNcBaseD,0)

NGtkNcBaseI*          ngtk_nc_base_create_interface  ();
void                  ngtk_nc_base_d_free            (void *d);

WINDOW*               ngtk_nc_base_get_window        (NGtkNcBase *self);
const NGtkRectangle*  ngtk_nc_base_get_abs_rect      (NGtkNcBase *self);

void                  ngtk_nc_base_map_to            (NGtkNcBase *self, const NGtkRectangle *area);
void                  ngtk_nc_base_unmap_window      (NGtkNcBase *self);

/** Fill the area of the window with spaces, and then show it to the screen */
void                  ngtk_nc_base_clear_window_area (NGtkNcBase *self);
/** Publish the window content to the screen */
void                  ngtk_nc_base_publish_window    (NGtkNcBase *self);

#endif
