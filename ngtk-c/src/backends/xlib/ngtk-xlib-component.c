/*
 * ngtk-xlib-component.c
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

#include "ngtk-xlib-component.h"
#include "ngtk-xlib.h"
//#include "ngtk-xlib-base.h"
//#include "../basic/ngtk-basic.h"

NGtkInterface* ngtk_xlib_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible, int focusable)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (enabled, parent, text, visible, focusable);

	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_xlib_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_xlib_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_xlib_component_set_visible;

	return in;
}

void ngtk_xlib_component_set_enabled (NGtkComponent *self, int enabled)
{
	ngtk_basic_component_set_enabled (self, enabled);
	ngtk_xlib_component_redraw (self);
}

void ngtk_xlib_component_set_visible (NGtkComponent *self, int visible)
{
	int old_val = ngtk_component_get_visible (self);

	if (old_val != visible)
	{
		Window wnd = ngtk_xlib_base_get_window (self);
		if (visible)
			XMapWindow (ngtk_xlib_base_get_display (self), wnd);
		else
			XUnmapWindow (ngtk_xlib_base_get_display (self), wnd);
	}
	ngtk_basic_component_set_visible (self, visible);
}

void ngtk_xlib_component_set_text (NGtkComponent *self, const char *text)
{
	ngtk_basic_component_set_text (self, text);
	ngtk_component_redraw (self);
}
