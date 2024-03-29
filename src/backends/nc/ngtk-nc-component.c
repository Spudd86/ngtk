/*
 * ngtk-nc-component.c - Part of the NGtk library
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

static const NGtkRectangle default_position = { 0, 0, 4, 4 };

static void ngtk_nc_component_destructor (NGtkComponent *comp);

NGtkInterface* ngtk_nc_component_create_interface (NGtkObject *obj, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible, NGtkNcDrawingFunc real_draw)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (obj, parent, enabled, focusable, text, visible);
	NGtkNcComponentD *ncd;

	in->imp_data[1] = ncd = ngtk_new (NGtkNcComponentD);
	ncd->area.x = default_position.x;
	ncd->area.y = default_position.y;
	ncd->area.w = default_position.w;
	ncd->area.h = default_position.h;
	ncd->wnd = NULL;
	ncd->wnd_resized = FALSE;
	ncd->real_draw = real_draw;
	in->imp_data_free[1] = ngtk_free;

	NGTK_COMPONENT_I2F (in) -> redraw      = ngtk_nc_component_redraw;
	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_nc_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_nc_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_nc_component_set_visible;

	ngtk_object_push_destructor (obj, ngtk_nc_component_destructor);

	return in;
}

static void ngtk_nc_component_destructor (NGtkComponent *comp)
{
	if (ngtk_nc_component_is_mapped (comp))
	{
		/* Hide the component if needed - clear the screen area it
		 * occupied */
		if (ngtk_component_get_visible (comp))
			ngtk_nc_backend_call_on_widget_hide (ngtk_base_get_backend (comp), comp);
		/* Now free the window */
		ngtk_nc_component_unmap_window (comp);
	}
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

	/* Clear the widget if it wasn't visible */
	if (old_val && ! visible)
	{
		ngtk_nc_backend_call_on_widget_hide (ngtk_base_get_backend (self), self);
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
	if (! ngtk_nc_component_is_mapped (self) || ! ngtk_component_get_visible (self))
		return;

	NGTK_NC_COMPONENT_O2D (self) -> real_draw (self);

	ngtk_nc_backend_drawing_commit (ngtk_base_get_backend (self), self);

	/* Base will redraw the children if needed */
	ngtk_basic_component_redraw (self);
}

WINDOW* ngtk_nc_component_get_window (NGtkComponent *self)
{
	return NGTK_NC_COMPONENT_O2D (self) -> wnd;
}

int ngtk_nc_component_is_mapped (NGtkComponent *self)
{
	return ngtk_nc_component_get_window (self) != NULL;
}

void ngtk_nc_component_unmap_window (NGtkComponent *self)
{
	WINDOW** wnd = &(NGTK_NC_COMPONENT_O2D (self) -> wnd);
	if (*wnd != NULL)
	{
		delwin (*wnd);
		*wnd = NULL;
	}
}

void ngtk_nc_component_map_to (NGtkComponent *self, const NGtkRectangle *area)
{
	NGtkRectangle *rect = &(NGTK_NC_COMPONENT_O2D (self) -> area);
	WINDOW       **wnd  = &(NGTK_NC_COMPONENT_O2D (self) -> wnd);

	/**
	 * @warning Always resize the WINDOW field, even if the new size
	 * is the current size! This is necessary due to a bug in NCURSES,
	 * which is detailed in ngtk-nc-window.c inside the pack method, and
	 * also here below.
	 */

	rect->x = area->x;
	rect->y = area->y;
	rect->w = area->w;
	rect->h = area->h;

	/* Remove and free the existing window (See below why) */
	ngtk_nc_component_unmap_window (self);

	/* When we create a child window, one may expect that we'll use the
	 * subwin/derwin functions. We are not going to do that...
	 *
	 * The reason is that once you have subwindows, you can not delete
	 * the window before deleting all the children. Since we do delete
	 * windows and in the pack method (see the comment in
	 * ngtk-nc-window.c), it would be unwise to enter this trouble. */
	if (area->h > 0 && area->w > 0)
	{
		*wnd = newwin (area->h, area->w, area->y, area->x);
		NGTK_NC_COMPONENT_O2D (self)-> wnd_resized = TRUE;
	}
}

const NGtkRectangle* ngtk_nc_component_get_abs_rect (NGtkComponent *self)
{
	return &(NGTK_NC_COMPONENT_O2D (self) -> area);
}

void ngtk_nc_component_reset_resize_bit (NGtkComponent *self)
{
	NGTK_NC_COMPONENT_O2D (self)-> wnd_resized = FALSE;
}

int ngtk_nc_component_was_resized (NGtkComponent *self)
{
	return NGTK_NC_COMPONENT_O2D (self)-> wnd_resized;
}
