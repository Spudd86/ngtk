/*
 * ngtk-basic-component.c
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
	char *str = strdup (text);
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
