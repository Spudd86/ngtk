#ifndef __NGtk_misc_types_h__
#define __NGtk_misc_types_h__

#include "ngtk-macros.h"

typedef struct _ngtk_rectangle {
	int x, y;
	int w, h;
} NGtkRectangle;

#define ngtk_rect_contains(prect,x0,y0) \
	(  NGTK_IN_RANGE (x0, (prect)->x, (prect)->x + (prect)->w - 1) \
	&& NGTK_IN_RANGE (y0, (prect)->y, (prect)->y + (prect)->h - 1) )
#endif
