/*
 * ngtk-basic-container.c - Part of the NGtk library
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
	NGTK_CONTAINER_I2F (in) -> set_layout   = ngtk_basic_container_set_layout;
	NGTK_CONTAINER_I2F (in) -> pack         = ngtk_basic_container_pack;
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
		NGtkComponent *child = (NGtkComponent*) children->first->data;
		ngtk_list_remove (children, child);
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

NGtkLayout* ngtk_basic_container_get_layout (NGtkContainer *self)
{
	return NGTK_BASIC_CONTAINER_O2D (self) -> layout;
}
