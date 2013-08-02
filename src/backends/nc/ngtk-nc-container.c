/*
 * ngtk-nc-container.c - Part of the NGtk library
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

#include "ngtk-nc.h"

NGtkInterface* ngtk_nc_container_create_interface (NGtkObject *obj)
{
	NGtkInterface *in = ngtk_basic_container_create_interface (obj);

	NGTK_CONTAINER_I2F (in) -> add_child    = ngtk_nc_container_add_child;
	NGTK_CONTAINER_I2F (in) -> get_children = ngtk_nc_container_get_children;
	NGTK_CONTAINER_I2F (in) -> place_child  = ngtk_nc_container_place_child;
	NGTK_CONTAINER_I2F (in) -> remove_child = ngtk_nc_container_remove_child;

	return in;
}

void ngtk_nc_container_add_child (NGtkContainer *self, NGtkComponent* child)
{
	ngtk_basic_container_add_child (self, child);
}

void ngtk_nc_container_remove_child (NGtkContainer *self, NGtkComponent* child)
{
	ngtk_nc_component_set_visible (child, FALSE);
	ngtk_nc_component_unmap_window (child);
	ngtk_basic_container_remove_child (self, child);
}

void ngtk_nc_container_place_child (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect)
{
	/* TODO: since we allow only one window in the NCurses backend */
	ngtk_nc_component_map_to (child, rect);
	ngtk_basic_container_place_child (self, child, rect);
}
