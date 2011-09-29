/*
 * ngtk-basic-container.c
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

#include "ngtk-basic-container.h"

NGtkInterface* ngtk_basic_container_create_interface ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_CONTAINER_TYPE);
	NGtkBasicContainerD *bcd;

	in->d[0] = bcd = ngtk_new (NGtkBasicContainerD);
	bcd->children  = ngtk_list_new ();
	bcd->layout    = NULL;
	in->d_free[0]  = ngtk_basic_container_free_d;

	in->f = ngtk_new (NGtkContainerF);
	NGTK_CONTAINER_I2F (in) -> get_children = ngtk_basic_container_get_children;
	NGTK_CONTAINER_I2F (in) -> add_child    = ngtk_basic_container_add_child;
	NGTK_CONTAINER_I2F (in) -> remove_child = ngtk_basic_container_remove_child;
	NGTK_CONTAINER_I2F (in) -> place_child  = ngtk_basic_container_place_child;
	in->f_free = ngtk_free;

	return in;
}

void ngtk_basic_container_free_d (void *d)
{
	NGtkBasicContainerD *d_real = (NGtkBasicContainerD*)d;
	ngtk_list_free (d_real->children);
	ngtk_free (d);
}
NGtkComponentList* ngtk_basic_container_get_children (NGtkContainer *self)
{
	return NGTK_BASIC_CONTAINER_O2D (self) -> children;
}

void ngtk_basic_container_add_child (NGtkContainer *self, NGtkComponent* child)
{
	ngtk_list_append (NGTK_BASIC_CONTAINER_O2D (self) -> children, child);
}

void ngtk_basic_container_remove_child (NGtkContainer *self, NGtkComponent* child)
{
	ngtk_list_remove (NGTK_BASIC_CONTAINER_O2D (self) -> children, child);
}

void ngtk_basic_container_place_child (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect)
{
}

void ngtk_basic_container_set_layout (NGtkContainer *self, NGtkLayout *layout)
{
	NGTK_BASIC_CONTAINER_O2D (self) -> layout = layout;
}

void ngtk_basic_container_pack (NGtkContainer *self)
{
}
