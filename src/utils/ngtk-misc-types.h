/*
 * ngtk-misc-types.h - Part of the NGtk library
 *
 * Copyright (c) 2011, Barak Itkin <lightningismyname at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NGtk nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __NGtk_misc_types_h__
#define __NGtk_misc_types_h__

#include "ngtk-macros.h"

/** A Rectangle defined by a corener point (x,y) and dimensions wxh */
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

/* Idea: Two segments on one axis intersect if the starting point
 *       of one of them is inside the other. We apply this to both
 *       X and Y, and if both intersect then the rectangles intersect
 */
#define ngtk_rect_interesects(rect1,rect2) \
	(  (  NGTK_IN_RANGE ((rect1)->x, (rect2)->x, (rect2)->x + (rect2)->w - 1)  \
	   || NGTK_IN_RANGE ((rect2)->x, (rect1)->x, (rect1)->x + (rect1)->w - 1)) \
	&& (  NGTK_IN_RANGE ((rect1)->y, (rect2)->y, (rect2)->y + (rect2)->h - 1)  \
	   || NGTK_IN_RANGE ((rect2)->y, (rect1)->y, (rect1)->y + (rect1)->h - 1)) \
    )

/** A type for functions that free memory */
typedef void (*NGtkFreeFunc) (void *data);
/**
 * A type for functions that free memory and receive an additional
 * pointer that may be needed for freeing the data.
 * */
typedef void (*NGtkDFreeFunc) (void *data, void *extra_data);
#endif
