/*
 * ngtk-nc-component.h
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

#ifndef __NGtk_nc_component__
#define __NGtk_nc_component__

#include <ncurses.h>
#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

typedef struct _NGtkNcComponentD {
	NGtkRectangle  area;
	WINDOW        *wnd;
	int            wnd_resized;
} NGtkNcComponentD;

#define NGTK_NC_COMPONENT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkNcComponentD,1)
#define NGTK_NC_COMPONENT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkNcComponentD,1)

NGtkInterface* ngtk_nc_component_create_interface (NGtkObject *obj, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible);

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
