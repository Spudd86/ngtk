/*
 * ngtk-nc-component.h - Part of the NGtk library
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

#ifndef __NGtk_nc_component__
#define __NGtk_nc_component__

#include <ncurses.h>
#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

typedef void (*NGtkNcDrawingFunc) (NGtkComponent *self);

typedef struct _NGtkNcComponentD {
	NGtkRectangle     area;
	WINDOW           *wnd;
	int               wnd_resized;
	NGtkNcDrawingFunc real_draw;
} NGtkNcComponentD;

#define NGTK_NC_COMPONENT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkNcComponentD,1)
#define NGTK_NC_COMPONENT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkNcComponentD,1)

NGtkInterface* ngtk_nc_component_create_interface (NGtkObject *obj, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible, NGtkNcDrawingFunc real_draw);

#define  ngtk_nc_component_get_parent   ngtk_basic_component_get_parent

#define  ngtk_nc_component_get_enabled  ngtk_basic_component_get_enabled
void     ngtk_nc_component_set_enabled  (NGtkComponent *self, int enabled);

#define  ngtk_nc_component_get_visible  ngtk_basic_component_get_visible
void     ngtk_nc_component_set_visible  (NGtkComponent *self, int visible);

#define  ngtk_nc_component_get_text     ngtk_basic_component_get_text
void     ngtk_nc_component_set_text     (NGtkComponent *self, const char *text);

void     ngtk_nc_component_redraw       (NGtkComponent *self);

/* Non interface functions */
WINDOW*  ngtk_nc_component_get_window   (NGtkComponent *self);
int      ngtk_nc_component_is_mapped    (NGtkComponent *self);

const NGtkRectangle*  ngtk_nc_component_get_abs_rect      (NGtkComponent *self);

void     ngtk_nc_component_map_to       (NGtkComponent *self, const NGtkRectangle *area);
void     ngtk_nc_component_unmap_window (NGtkComponent *self);

void     ngtk_nc_component_reset_resize_bit (NGtkComponent *self);
int      ngtk_nc_component_was_resized      (NGtkComponent *self);

#endif
