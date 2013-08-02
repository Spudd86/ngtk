/*
 * ngtk-win-defs.h
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

#ifndef __NGtk_win_defs__
#define __NGtk_win_defs__

#include "ngtk-win-widget-types.h"

#include "ngtk-win-backend.h"
#include "ngtk-win-component.h"
#include "ngtk-win-container.h"

// #include "ngtk-widget-window.h"

#define NGtk_Win_hInstance     (GetModuleHandle (NULL))
typedef NGtkObject* NGtk_Win_ExtraDataType;

void  ngtk_win_call_after_compononet_creation (NGtkComponent *obj);
void  ngtk_win_init                           (NGtkBackend *backend);
void  ngtk_win_start_main_loop                (NGtkBackend *backend);
void  ngtk_win_quit_main_loop                 (NGtkBackend *backend);
void  ngtk_win_quit                           (NGtkBackend *backend);

LRESULT CALLBACK ngtk_win_general_WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LPCSTR ngtk_win_get_root_window_class_name    (NGtkBackend *backend);

#endif