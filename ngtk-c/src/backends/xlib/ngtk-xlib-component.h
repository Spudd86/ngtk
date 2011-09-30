/*
 * ngtk-xlib-component.h
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

#ifndef __NGtk_xlib_component__
#define __NGtk_xlib_component__

#include <ncurses.h>
#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

NGtkInterface* ngtk_xlib_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible, int focusable);

#define  ngtk_xlib_component_get_parent   ngtk_basic_component_get_parent

#define  ngtk_xlib_component_get_enabled  ngtk_basic_component_get_enabled
void     ngtk_xlib_component_set_enabled  (NGtkComponent *self, int enabled);

#define  ngtk_xlib_component_get_visible  ngtk_basic_component_get_visible
void     ngtk_xlib_component_set_visible  (NGtkComponent *self, int visible);

#define  ngtk_xlib_component_get_text     ngtk_basic_component_get_text
void     ngtk_xlib_component_set_text     (NGtkComponent *self, const char *text);

#define  ngtk_xlib_component_redraw       ngtk_basic_component_redraw

#endif
