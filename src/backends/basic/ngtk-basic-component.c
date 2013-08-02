/*
 * ngtk-basic-component.c - Part of the NGtk library
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

#include "ngtk-basic-component.h"
#include <string.h>

static void simple_destroy_component_interface (NGtkObject *obj);

NGtkInterface* ngtk_basic_component_create_interface (NGtkObject *obj, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible)
{
	NGtkInterface *in = ngtk_interface_new (obj, NGTK_COMPONENT_TYPE);
	NGtkBasicComponentD *bcd;

	in->imp_data[0] = bcd = ngtk_new (NGtkBasicComponentD);
	bcd->enabled = enabled;
	bcd->parent = parent;
	bcd->text = text;
	bcd->focusable = focusable;
	bcd->visible = visible;
	in->imp_data_free[0] = ngtk_free;

	in->functions = ngtk_new (NGtkComponentF);
	NGTK_COMPONENT_I2F (in) -> get_enabled   = ngtk_basic_component_get_enabled;
	NGTK_COMPONENT_I2F (in) -> get_focusable = ngtk_basic_component_get_focusable;
	NGTK_COMPONENT_I2F (in) -> get_parent    = ngtk_basic_component_get_parent;
	NGTK_COMPONENT_I2F (in) -> get_text      = ngtk_basic_component_get_text;
	NGTK_COMPONENT_I2F (in) -> get_visible   = ngtk_basic_component_get_visible;
	NGTK_COMPONENT_I2F (in) -> redraw        = ngtk_basic_component_redraw;
	NGTK_COMPONENT_I2F (in) -> set_enabled   = ngtk_basic_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text      = ngtk_basic_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible   = ngtk_basic_component_set_visible;
	in->functions_free = ngtk_free;

	if (parent != NULL)
	{
		ngtk_container_add_child (parent, obj);
	}

	ngtk_object_push_destructor (obj, simple_destroy_component_interface);

	return in;
}

static void simple_destroy_component_interface (NGtkObject *obj)
{
	NGtkContainer *parent = ngtk_component_get_parent (obj);

	if (parent != NULL)
	{
		ngtk_container_remove_child (parent, obj);
	}

	ngtk_interface_detach_and_free (ngtk_object_cast (obj, NGTK_COMPONENT_TYPE));
}

NGtkContainer* ngtk_basic_component_get_parent  (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> parent;
}

int ngtk_basic_component_get_enabled (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> enabled;
}

void ngtk_basic_component_set_enabled (NGtkComponent *self, int enabled)
{
	NGTK_BASIC_COMPONENT_O2D (self) -> enabled = enabled;
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_COMPONENT_TYPE), "component::enable", &enabled, TRUE);
}

int ngtk_basic_component_get_visible (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> visible;
}

void ngtk_basic_component_set_visible (NGtkComponent *self, int visible)
{
	NGTK_BASIC_COMPONENT_O2D (self) -> visible = visible;
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_COMPONENT_TYPE), "component::visible", &visible, TRUE);
}

int ngtk_basic_component_get_focusable (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> focusable;
}

const char* ngtk_basic_component_get_text (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> text;
}

void ngtk_basic_component_set_text (NGtkComponent *self, const char *text)
{
	char *str = ngtk_new_array (char, strlen (text) + 1);
	strcpy (str, text);
	NGTK_BASIC_COMPONENT_O2D (self) -> text = text;
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_COMPONENT_TYPE), "component::text", str, TRUE);
	ngtk_free (str);
}

void ngtk_basic_component_redraw (NGtkComponent *self)
{
	/* Let's break some abstraction */
	if (ngtk_object_is_a (self, NGTK_CONTAINER_TYPE))
	{
		NGtkListNode *iter;
		ngtk_list_foreach (iter, ngtk_container_get_children (self))
		{
			ngtk_component_redraw ((NGtkComponent*) iter->data);
		}
	}
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_COMPONENT_TYPE), "component::redraw", NULL, TRUE);
}
