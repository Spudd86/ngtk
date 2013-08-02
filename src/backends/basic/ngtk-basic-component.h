/*
 * ngtk-basic-component.h
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

#ifndef __NGtk_basic_component__
#define __NGtk_basic_component__

#include "../../widgets/ngtk-widgets.h"

typedef struct _ngtk_basic_component_d {
	NGtkContainer* parent;
	int            enabled;
	int            visible;
	int            focusable;
	const char*    text;
} NGtkBasicComponentD;

#define NGTK_BASIC_COMPONENT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkBasicComponentD,0)
#define NGTK_BASIC_COMPONENT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkBasicComponentD,0)

NGtkInterface* ngtk_basic_component_create_interface (NGtkObject *obj, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible);

NGtkContainer* ngtk_basic_component_get_parent       (NGtkComponent *self);

int            ngtk_basic_component_get_enabled      (NGtkComponent *self);
void           ngtk_basic_component_set_enabled      (NGtkComponent *self, int enabled);

int            ngtk_basic_component_get_visible      (NGtkComponent *self);
void           ngtk_basic_component_set_visible      (NGtkComponent *self, int visible);

int            ngtk_basic_component_get_focusable    (NGtkComponent *self);

const char*    ngtk_basic_component_get_text         (NGtkComponent *self);
void           ngtk_basic_component_set_text         (NGtkComponent *self, const char *text);

void           ngtk_basic_component_redraw           (NGtkComponent *self);

#endif
