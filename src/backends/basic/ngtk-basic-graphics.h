/*
 * ngtk-basic-graphics.h - Part of the NGtk library
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

#ifndef __NGtk_basic_graphics_h__
#define __NGtk_basic_graphics_h__

#include "ngtk-basic-types.h"
#include "../../utils/ngtk-utils.h"

typedef struct _NGtkGraphicsF {
	void (*clear)      (NGtkGraphics *self);

	int  (*calc_text_width)  (NGtkGraphics *self, const char *text, int start, int length);
	int  (*calc_text_height) (NGtkGraphics *self);
	void (*draw_text)        (NGtkGraphics *self, const char *text, int start, int length, int x, int y);

	int  (*calc_text_cursor_end_width) (NGtkGraphics *self);
	void (*draw_text_cursor)           (NGtkGraphics *self, int x, int y);

	void (*draw_frame)      (NGtkGraphics *self, const NGtkRectangle *rect, int is_focus_frame);
} NGtkGraphicsF;

#define NGTK_GRAPHICS_O2F(comp) NGTK_O2F_CAST(comp,NGTK_GRAPHICS_TYPE,NGtkGraphicsF)
#define NGTK_GRAPHICS_I2F(comp) NGTK_I2F_CAST(comp,NGTK_GRAPHICS_TYPE,NGtkGraphicsF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkGraphicsF object */

void ngtk_graphics_clear (NGtkGraphics *self);

int  ngtk_graphics_calc_text_width  (NGtkGraphics *self, const char *text, int start, int length);
int  ngtk_graphics_calc_text_height (NGtkGraphics *self);
void ngtk_graphics_draw_text        (NGtkGraphics *self, const char *text, int start, int length, int x, int y);

int  ngtk_graphics_calc_text_cursor_end_width (NGtkGraphics *self);
void ngtk_graphics_draw_text_cursor           (NGtkGraphics *self, int x, int y);

void ngtk_graphics_draw_frame (NGtkGraphics *self, const NGtkRectangle *rect, int is_focus_frame);


/* The following functions are utility functions which can draw advanced
 * stuff using the NGtkGraphics interface */

void ngtk_basic_graphics_draw_aligned_text (NGtkGraphics *self,
	const NGtkRectangle *rect, int ignoreXY,
	float halign, int hpad,
	float valign, int vpad,
	const char* text);

/**
 * In short, this function allows simulating a text entry widget by
 * drawing text aligned with it's cursor, so that the cursor is always
 * visible.
 *
 * And now a bit more detailed:
 * Draw text with it's cursor so that the cursor is always visible. In
 * case where the text is too wide to fit in the rectangle, it will
 * focus on the area with cursor. This means that if enough text is on
 * each side of the cursor, the cursor will be displayed in the center
 * with the matching text aroud it. Otherwise, the cursor will be as
 * close as it can to the center withuot leaving margins near the end of
 * the text */
void ngtk_basic_graphics_draw_text_with_cursor (NGtkGraphics *self,
	const NGtkRectangle *rect, int ignoreXY,
	float halign, int hpad,
	float valign, int vpad,
	const char* text, int cursor_position);

#endif
