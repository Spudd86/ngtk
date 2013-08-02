/*
 * ngtk-xlib.h
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

#ifndef __NGtk_win_h__
#define __NGtk_win_h__

#include <windows.h>
#include "ngtk-win-widget-types.h"

#include "ngtk-win-backend.h"
#include "ngtk-win-component.h"
#include "ngtk-win-container.h"
#include "ngtk-win-defs.h"

#include "ngtk-win-window.h"

#define ngtk_win_base_has_focus(self) (ngtk_backend_get_focus_holder (ngtk_base_get_backend (self)) == (self))

#define ngtk_init                ngtk_win_init
#define ngtk_start_main_loop     ngtk_win_start_main_loop
#define ngtk_quit_main_loop      ngtk_win_quit_main_loop
#define ngtk_quit                ngtk_win_quit

#define ngtk_create_root_window  ngtk_win_create_root_window
#define ngtk_create_button       ngtk_win_create_button
#define ngtk_create_label        ngtk_win_create_label
#define ngtk_create_text_entry   ngtk_win_create_text_entry

#endif
