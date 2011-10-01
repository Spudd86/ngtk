/*
 * ngtk-misc-types.h
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

#ifndef __NGtk_misc_types_h__
#define __NGtk_misc_types_h__

#include "ngtk-macros.h"

typedef struct _ngtk_rectangle {
	int x, y;
	int w, h;
} NGtkRectangle;

typedef struct _ngtk_point {
	int x, y;
} NGtkPoint;

#define ngtk_rect_contains(prect,x0,y0) \
	(  NGTK_IN_RANGE (x0, (prect)->x, (prect)->x + (prect)->w - 1) \
	&& NGTK_IN_RANGE (y0, (prect)->y, (prect)->y + (prect)->h - 1) )

typedef void (*NGtkFreeFunc) (void *data);
typedef void (*NGtkDFreeFunc) (void *data, void *extra_data);
#endif
