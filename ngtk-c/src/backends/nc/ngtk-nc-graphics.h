/*
 * ngtk-nc-graphics.h
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

#ifndef __NGtk_xlib_grahpics__
#define __NGtk_xlib_graphics__

#include "../basic/ngtk-basic.h"
#include "ngtk-nc-widget-types.h"
#include <ncurses.h>

typedef struct {
	WINDOW            *wnd;
} NGtkNcGraphicsD;

#define NGTK_NC_GRAPHICS_O2D(comp) NGTK_O2D_CAST(comp,NGTK_GRAPHICS_TYPE,NGtkNcGraphicsD,0)
#define NGTK_NC_GRAPHICS_I2D(comp) NGTK_I2D_CAST(comp,NGTK_GRAPHICS_TYPE,NGtkNcGraphicsD,0)

NGtkGraphics* ngtk_nc_graphics_create (NGtkComponent *comp);

void ngtk_nc_graphics_clear (NGtkGraphics *self);

int  ngtk_nc_graphics_calc_text_width  (NGtkGraphics *self, const char *text, int start, int length);
int  ngtk_nc_graphics_calc_text_height (NGtkGraphics *self);
void ngtk_nc_graphics_draw_text        (NGtkGraphics *self, const char *text, int start, int length, int x, int y);

int  ngtk_nc_graphics_calc_text_cursor_end_width (NGtkGraphics *self);
void ngtk_nc_graphics_draw_text_cursor           (NGtkGraphics *self, int x, int y);

void ngtk_nc_graphics_draw_frame (NGtkGraphics *self, const NGtkRectangle *rect, int is_focus_frame);

#endif
