/*
 * ngtk-xlib-container.h
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

#ifndef __NGtk_xlib_container__
#define __NGtk_xlib_container__

#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

NGtkInterface* ngtk_xlib_container_create_interface ();

void     ngtk_xlib_container_add_child     (NGtkContainer *self, NGtkComponent* child);
#define  ngtk_xlib_container_get_children  ngtk_basic_container_get_children
void     ngtk_xlib_container_remove_child  (NGtkContainer *self, NGtkComponent* child);
void     ngtk_xlib_container_place_child   (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);

#endif
