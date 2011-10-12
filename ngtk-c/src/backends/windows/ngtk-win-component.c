/*
 * ngtk-win-component.c
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

#include "ngtk-win.h"

NGtkInterface* ngtk_win_component_create_interface (NGtkObject *obj, HWND hwnd, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (obj, parent, enabled, focusable, text, visible);
	NGtkWinComponentD *wcd = ngtk_new (NGtkWinComponentD);

	in->imp_data[1]      = wcd;
	wcd->hwnd            = hwnd;
	wcd->base_wndproc    = (WNDPROC) GetWindowLong (hwnd, GWL_WNDPROC);
	in->imp_data_free[1] = ngtk_free;
	
	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_win_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_win_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_win_component_set_visible;

	SetParent ((parent != NULL) ? ngtk_win_component_get_hwnd (parent) : NULL, hwnd);
	SetWindowLongA (hwnd, GWL_WNDPROC, (LONG) ngtk_win_general_WndProc);
	ngtk_win_call_after_compononet_creation (obj);

	return in;
}

void ngtk_win_component_set_enabled (NGtkComponent *self, int enabled)
{
	EnableWindow (NGTK_WIN_COMPONENT_O2D (self)->hwnd, enabled);
	ngtk_basic_component_set_enabled (self, enabled);
}

void ngtk_win_component_set_visible (NGtkComponent *self, int visible)
{
	ShowWindow (NGTK_WIN_COMPONENT_O2D (self)->hwnd, visible ? SW_NORMAL : SW_HIDE);
	ngtk_basic_component_set_visible (self, visible);
}

void ngtk_win_component_set_text (NGtkComponent *self, const char *text)
{
	SetWindowTextA (NGTK_WIN_COMPONENT_O2D (self)->hwnd, text);
	ngtk_basic_component_set_text (self, text);
}

HWND ngtk_win_component_get_hwnd (NGtkComponent *self)
{
	return NGTK_WIN_COMPONENT_O2D (self)->hwnd;
}

WNDPROC ngtk_win_component_get_base_wnd_proc (NGtkComponent *self)
{
	return NGTK_WIN_COMPONENT_O2D (self)->base_wndproc;
}

void ngtk_win_component_call_on_wnd_destroy (NGtkComponent *self)
{
	NGTK_WIN_COMPONENT_O2D (self)->hwnd = NULL;
}
