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

static void simple_destroy_container_interface (NGtkObject *obj);

NGtkInterface* ngtk_basic_container_create_interface (NGtkObject *obj)
{
	NGtkInterface *in = ngtk_interface_new (obj, NGTK_CONTAINER_TYPE);
	NGtkBasicContainerD *bcd;

	in->imp_data[0] = bcd = ngtk_new (NGtkBasicContainerD);
	ngtk_list_init (&bcd->children);
	bcd->layout    = NULL;
	in->imp_data_free[0]  = ngtk_free;

	in->functions = ngtk_new (NGtkContainerF);
	NGTK_CONTAINER_I2F (in) -> get_children = ngtk_basic_container_get_children;
	NGTK_CONTAINER_I2F (in) -> add_child    = ngtk_basic_container_add_child;
	NGTK_CONTAINER_I2F (in) -> remove_child = ngtk_basic_container_remove_child;
	NGTK_CONTAINER_I2F (in) -> place_child  = ngtk_basic_container_place_child;
	in->functions_free = ngtk_free;

	ngtk_object_push_destructor (obj, simple_destroy_container_interface);

	return in;
}

static void simple_destroy_container_interface (NGtkObject *obj)
{
	/* The original child list of this container */
	NGtkList     *children = ngtk_container_get_children (obj);

	/* Warning! We can't iterate over the original children list while
	 * destroying children, because these children will remove
	 * themselves from the list upon their destruction. So, instead
	 * always free the first child */
	while (! ngtk_list_is_empty (children))
	{
		NGtkComponent *child = (NGtkComponent*) children->first;
		ngtk_object_free (child);
	}

	ngtk_interface_detach_and_free (ngtk_object_cast (obj, NGTK_CONTAINER_TYPE));
}

NGtkComponentList* ngtk_basic_container_get_children (NGtkContainer *self)
{
	return & NGTK_BASIC_CONTAINER_O2D (self) -> children;
}

void ngtk_basic_container_add_child (NGtkContainer *self, NGtkComponent* child)
{
	ngtk_list_append (& NGTK_BASIC_CONTAINER_O2D (self) -> children, child);
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_CONTAINER_TYPE), "structure::child-add", child, TRUE);
}

void ngtk_basic_container_remove_child (NGtkContainer *self, NGtkComponent* child)
{
	ngtk_list_remove (& NGTK_BASIC_CONTAINER_O2D (self) -> children, child);
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_CONTAINER_TYPE), "structure::child-rem", child, TRUE);
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
