/*
 * ngtk-nc-graphics.h - Part of the NGtk library
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
