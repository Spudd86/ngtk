/*
 * ngtk-container.c
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

#include "ngtk-container.h"

NGtkComponentList* ngtk_container_get_children (NGtkContainer *self)
{
	return NGTK_CONTAINER_O2F (self)->get_children (self);
}

void ngtk_container_add_child (NGtkContainer *self, NGtkComponent* child)
{
	NGTK_CONTAINER_O2F (self)->add_child (self, child);
}

void ngtk_container_remove_child (NGtkContainer *self, NGtkComponent* child)
{
	NGTK_CONTAINER_O2F (self)->remove_child (self, child);
}

void ngtk_container_place_child (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect)
{
	NGTK_CONTAINER_O2F (self)->place_child (self, child, rect);
}

void ngtk_container_set_layout (NGtkContainer *self, NGtkLayout *layout)
{
	NGTK_CONTAINER_O2F (self)->set_layout (self, layout);
}

void ngtk_container_pack (NGtkContainer *self)
{
	NGTK_CONTAINER_O2F (self)->pack (self);
}
