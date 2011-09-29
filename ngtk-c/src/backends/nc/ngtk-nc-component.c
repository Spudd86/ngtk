/*
 * ngtk-nc-component.c
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

#include "ngtk-nc-base.h"
#include "ngtk-nc-component.h"
#include "../basic/ngtk-basic.h"

NGtkInterface* ngtk_nc_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (enabled, parent, text, visible);

	NGTK_COMPONENT_I2F (in) -> redraw      = ngtk_nc_component_redraw;
	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_nc_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_nc_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_nc_component_set_visible;

	return in;
}

void ngtk_nc_component_set_enabled (NGtkComponent *self, int enabled)
{
	ngtk_basic_component_set_enabled (self, enabled);
	ngtk_nc_component_redraw (self);
}

void ngtk_nc_component_set_visible (NGtkComponent *self, int visible)
{
	int old_val = ngtk_component_get_visible (self);
	ngtk_basic_component_set_visible (self, visible);
	ngtk_nc_component_redraw (self);

	/* Clear the widget if it wasn't visible */
	if (old_val && ! visible)
	{
		/* TODO: The behaviour is underfined for widgets that overlap one
		 * another. This is not a bug, but it should be documented. Since
		 * redrawing an invisible area clears the area below it, then
		 * redrawing an invisible widget will lead to unexpected results.
		 * maybe fix this by asking the parent to redraw... */
		ngtk_nc_base_clear_window_area (self);
	}
	else if (! old_val && visible)
	{
		ngtk_component_redraw (self);
	}
}

void ngtk_nc_component_set_text (NGtkComponent *self, const char *text)
{
	ngtk_basic_component_set_text (self, text);
	ngtk_nc_component_redraw (self);
}

void ngtk_nc_component_redraw (NGtkComponent *self)
{
	const NGtkBasicComponentD *dReal = NGTK_BASIC_COMPONENT_O2D (self);
	WINDOW *wnd = ngtk_nc_base_get_window (self);
	const NGtkRectangle *area = ngtk_nc_base_get_abs_rect (self);

	int max_x, max_y, min_x, min_y;

	if (wnd == NULL || ! dReal->visible)
		return;

	wclear (wnd);
	box (wnd, 0, 0);

	if (! dReal->enabled)
		wattron (wnd, A_DIM);

	/* Don't use the printw version, since then you need "%s" to avoid
	 * format string attacks, which is just an annoyance */
	mvwaddstr (wnd, 1, 1, dReal->text);

	getbegyx (wnd, min_y, min_x);
	getmaxyx (wnd, max_y, max_x);

	mvwprintw (wnd, area->h-1, 1, "W: (%d,%d) %dx%d, A: (%d,%d) %dx%d", min_x, min_y, max_x - min_x, max_y - min_y, area->x, area->y, area->w, area->h);

	if (! dReal->enabled)
		wattroff (wnd, A_DIM);

	ngtk_nc_base_publish_window (self);

	/* Base will redraw the children if needed */
	ngtk_basic_component_redraw (self);
}
