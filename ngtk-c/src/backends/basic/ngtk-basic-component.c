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

NGtkInterface* ngtk_basic_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible, int focusable)
{
	NGtkInterface *in = ngtk_interface_new (NGTK_COMPONENT_TYPE);
	NGtkBasicComponentD *bcd;

	bcd = ngtk_new (NGtkBasicComponentD);
	bcd->enabled = enabled;
	bcd->parent = parent;
	bcd->text = text;
	bcd->focusable = focusable;
	bcd->visible = visible;

	in->d[0] = bcd;
	in->d_free[0] = ngtk_basic_component_d_free;

	in->f = ngtk_new (NGtkComponentF);
	NGTK_COMPONENT_I2F (in) -> get_enabled   = ngtk_basic_component_get_enabled;
	NGTK_COMPONENT_I2F (in) -> get_focusable = ngtk_basic_component_get_focusable;
	NGTK_COMPONENT_I2F (in) -> get_parent    = ngtk_basic_component_get_parent;
	NGTK_COMPONENT_I2F (in) -> get_text      = ngtk_basic_component_get_text;
	NGTK_COMPONENT_I2F (in) -> get_visible   = ngtk_basic_component_get_visible;
	NGTK_COMPONENT_I2F (in) -> redraw        = ngtk_basic_component_redraw;
	NGTK_COMPONENT_I2F (in) -> set_enabled   = ngtk_basic_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text      = ngtk_basic_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible   = ngtk_basic_component_set_visible;
	in->f_free = ngtk_free;

	return in;
}

void ngtk_basic_component_d_free (void *d)
{
	NGtkBasicComponentD *d_real = (NGtkBasicComponentD*) d;
	ngtk_free (d_real);
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
	NGtkValue temp;
	NGTK_BASIC_COMPONENT_O2D (self) -> enabled = enabled;
	temp.type = NGTK_VALUE_INT;
	temp.val.v_int = enabled;
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_COMPONENT_TYPE), "component::enable", &temp, TRUE);
}

int ngtk_basic_component_get_visible (NGtkComponent *self)
{
	return NGTK_BASIC_COMPONENT_O2D (self) -> visible;
}

void ngtk_basic_component_set_visible (NGtkComponent *self, int visible)
{
	NGtkValue temp;
	NGTK_BASIC_COMPONENT_O2D (self) -> visible = visible;
	temp.type = NGTK_VALUE_INT;
	temp.val.v_int = visible;
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_COMPONENT_TYPE), "component::visible", &temp, TRUE);
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
	NGtkValue temp;
	NGTK_BASIC_COMPONENT_O2D (self) -> text = text;
	temp.type = NGTK_VALUE_CONST_STR;
	temp.val.v_cstr = text;
	ngtk_interface_send_signal (ngtk_object_cast (self, NGTK_COMPONENT_TYPE), "component::text", &temp, TRUE);
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
