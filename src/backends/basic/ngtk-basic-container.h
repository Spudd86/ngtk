/*
 * ngtk-basic-container.h
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

#ifndef __NGtk_basic_container__
#define __NGtk_basic_container__

#include "../../widgets/ngtk-widgets.h"

typedef struct _ngtk_basic_container_d {
	NGtkComponentList  children;
	NGtkLayout*        layout;
} NGtkBasicContainerD;

#define NGTK_BASIC_CONTAINER_O2D(comp) NGTK_O2D_CAST(comp,NGTK_CONTAINER_TYPE,NGtkBasicContainerD,0)
#define NGTK_BASIC_CONTAINER_I2D(comp) NGTK_I2D_CAST(comp,NGTK_CONTAINER_TYPE,NGtkBasicContainerD,0)

NGtkInterface*     ngtk_basic_container_create_interface (NGtkObject *obj);

NGtkComponentList* ngtk_basic_container_get_children     (NGtkContainer *self);

void               ngtk_basic_container_add_child        (NGtkContainer *self, NGtkComponent* child);
void               ngtk_basic_container_remove_child     (NGtkContainer *self, NGtkComponent* child);

void               ngtk_basic_container_place_child      (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);

void               ngtk_basic_container_set_layout       (NGtkContainer *self, NGtkLayout *layout);
void               ngtk_basic_container_pack             (NGtkContainer *self);

/* Non interface functions */
NGtkLayout*        ngtk_basic_container_get_layout       (NGtkContainer *self);

#endif
