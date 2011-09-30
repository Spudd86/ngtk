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

static void remove_children (void *src_interface, const char *signame, NGtkValue *temp);

NGtkInterface* ngtk_basic_container_create_interface ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_CONTAINER_TYPE);
	NGtkBasicContainerD *bcd;

	in->d[0] = bcd = ngtk_new (NGtkBasicContainerD);
	ngtk_list_init (&bcd->children);
	bcd->layout    = NULL;
	in->d_free[0]  = ngtk_basic_container_free_d;

	in->f = ngtk_new (NGtkContainerF);
	NGTK_CONTAINER_I2F (in) -> get_children = ngtk_basic_container_get_children;
	NGTK_CONTAINER_I2F (in) -> add_child    = ngtk_basic_container_add_child;
	NGTK_CONTAINER_I2F (in) -> remove_child = ngtk_basic_container_remove_child;
	NGTK_CONTAINER_I2F (in) -> place_child  = ngtk_basic_container_place_child;
	in->f_free = ngtk_free;

	/* We need to destroy some stuff while the object is still whole,
	 * see function documentation below */
	ngtk_interface_connect_to (in, "object::detach", remove_children);

	return in;
}

/* When coming here to destroy the last part of the interface, we
 * can't count on having a connection to a fully working object.
 * Therefore, we can't link from a child to ourselves, and so we
 * don't have a pinter to the container object to pass to the
 * remove_child function to generate the signal.
 * So, we will remove the children while the object is still whole */
static void remove_children (void *src_interface, const char *signame, NGtkValue *temp)
{
	NGtkListNode *iter;
	NGtkContainer *real = ngtk_interface_get_object ((NGtkContainerI*)src_interface);
	
	ngtk_list_foreach (iter, ngtk_container_get_children (real))
	{
		NGtkComponent *child = (NGtkComponent*)iter->data;
		ngtk_container_remove_child (real, child);
		ngtk_object_free (child);
	}
}

void ngtk_basic_container_free_d (void *d)
{
	ngtk_list_clear (& ((NGtkBasicContainerD*)d)->children);
	ngtk_free (d);
}

NGtkComponentList* ngtk_basic_container_get_children (NGtkContainer *self)
{
	return & NGTK_BASIC_CONTAINER_O2D (self) -> children;
}

void ngtk_basic_container_add_child (NGtkContainer *self, NGtkComponent* child)
{
	NGtkValue temp;
	ngtk_list_append (& NGTK_BASIC_CONTAINER_O2D (self) -> children, child);
	temp.type = NGTK_VALUE_P_VOID;
	temp.val.v_pvoid = child;
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_CONTAINER_TYPE), "structure::child-add", &temp, TRUE);
}

void ngtk_basic_container_remove_child (NGtkContainer *self, NGtkComponent* child)
{
	NGtkValue temp;
	ngtk_list_remove (& NGTK_BASIC_CONTAINER_O2D (self) -> children, child);
	temp.type = NGTK_VALUE_P_VOID;
	temp.val.v_pvoid = child;
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_CONTAINER_TYPE), "structure::child-rem", &temp, TRUE);
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
