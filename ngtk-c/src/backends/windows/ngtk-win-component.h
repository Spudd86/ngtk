/*
 * ngtk-win-component.h
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

#ifndef __NGtk_win_component__
#define __NGtk_win_component__

#include <windows.h>
#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

typedef struct _ngtk_win_component_d {
	HWND    hwnd;
	WNDPROC base_wndproc;
} NGtkWinComponentD;

#define NGTK_WIN_COMPONENT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkWinComponentD,1)
#define NGTK_WIN_COMPONENT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkWinComponentD,1)

NGtkInterface* ngtk_win_component_create_interface (NGtkObject *obj, HWND hwnd, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible);

#define  ngtk_win_component_get_parent   ngtk_basic_component_get_parent

#define  ngtk_win_component_get_enabled  ngtk_basic_component_get_enabled
void     ngtk_win_component_set_enabled  (NGtkComponent *self, int enabled);

#define  ngtk_win_component_get_visible  ngtk_basic_component_get_visible
void     ngtk_win_component_set_visible  (NGtkComponent *self, int visible);

#define  ngtk_win_component_get_text     ngtk_basic_component_get_text
void     ngtk_win_component_set_text     (NGtkComponent *self, const char *text);

/* Non interface functions */
HWND     ngtk_win_component_get_hwnd            (NGtkComponent *self);
WNDPROC  ngtk_win_component_get_base_wnd_proc   (NGtkComponent *self);
void     ngtk_win_component_call_on_wnd_destroy (NGtkComponent *self);

#endif
