/*
 * ngtk-macros.h
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

#ifndef __NGtk_macros_h__
#define __NGtk_macros_h__

#include <assert.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (! FALSE)
#endif

#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(a) (((a) < 0) ? -(a) : (a))
#endif


#define NGTK_IN_RANGE(val,min,max) ((min) <= (val) && (val) <= (max))
#define NGTK_BIT_MASK(bit) ( ((unsigned long long)1) << ((bit)-1))

#define NGTK_FIELD_OFFSET(field,type) ((int)(&(((type*)NULL)->field)))

#define NGTK_LONG_MACRO_BEGIN do {
#define NGTK_LONG_MACRO_END   } while (FALSE)

#define NGTK_MACRO_DO_NOTHING() NGTK_LONG_MACRO_BEGIN NGTK_LONG_MACRO_END

#ifndef NGTK_OPTIMIZE
#define ngtk_assert(expr) assert(expr)
#else
#define ngtk_assert(expr) NGTK_MACRO_DO_NOTHING ()
#endif

#ifdef _WIN32
#define NGTK_EXPORT __declspec(dllexport)
#else
#define NGTK_EXPORT
#endif

#define NGTK_ELEMENT_COUNT(ar) (sizeof(ar)/sizeof((ar)[0]))
#define ngtk_assert_not_reached() assert (FALSE)
#endif
