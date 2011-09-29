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

typedef enum {
	NGTK_VALUE_P_VOID,
	NGTK_VALUE_CHAR,
	NGTK_VALUE_UCHAR,
	NGTK_VALUE_SHORT,
	NGTK_VALUE_USHORT,
	NGTK_VALUE_INT,
	NGTK_VALUE_UINT,
	NGTK_VALUE_LONG,
	NGTK_VALUE_ULONG,
	NGTK_VALUE_DOUBLE,
	NGTK_VALUE_FLOAT,
	NGTK_VALUE_CONST_STR,
	NGTK_VALUE_STR,
	NGTK_VALUE_RECT,
	NGTK_VALUE_P_CONST_RECT
} NGtkValueType;

typedef struct {
	NGtkValueType  type;
	union {
		void                *v_pvoid;

		char                 v_char;
		unsigned char        v_uchar;
		
		short                v_short;
		unsigned short       v_ushort;
		
		int                  v_int;
		unsigned int         v_uint;
		
		long                 v_long;
		unsigned long        v_ulong;
		
		double               v_double;
		float                v_float;

		const char          *v_cstr;
		char                *v_str;
		
		NGtkRectangle        v_rect;
		const NGtkRectangle *v_cprect;
	} val;
} NGtkValue;

#define ngtk_rect_contains(prect,x0,y0) \
	(  NGTK_IN_RANGE (x0, (prect)->x, (prect)->x + (prect)->w - 1) \
	&& NGTK_IN_RANGE (y0, (prect)->y, (prect)->y + (prect)->h - 1) )
#endif
