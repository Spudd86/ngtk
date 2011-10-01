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

#ifndef __NGtk_xlib_h__
#define __NGtk_xlib_h__

#include "ngtk-xlib-defs.h"

#include "ngtk-xlib-widget-types.h"

#include "ngtk-xlib-backend.h"
#include "ngtk-xlib-component.h"
#include "ngtk-xlib-container.h"

#include "ngtk-xlib-window.h"

#define ngtk_xlib_base_get_display(self) (ngtk_xlib_backend_get_X_display (ngtk_base_get_backend (self)))
#define ngtk_xlib_base_get_screen(self) (ngtk_xlib_backend_get_X_screen (ngtk_base_get_backend (self)))
#define ngtk_xlib_base_get_color(self,col) (ngtk_xlib_backend_get_X_color (ngtk_base_get_backend (self), (col)))
#define ngtk_xlib_base_has_focus(self) (ngtk_backend_get_focus_holder (ngtk_base_get_backend (self)) == (self))

#define ngtk_init                ngtk_xlib_init
#define ngtk_start_main_loop     ngtk_xlib_start_main_loop
#define ngtk_quit_main_loop      ngtk_xlib_quit_main_loop
#define ngtk_quit                ngtk_xlib_quit

#define ngtk_create_root_window  ngtk_xlib_create_root_window
#define ngtk_create_button       ngtk_xlib_create_button
#define ngtk_create_label        ngtk_xlib_create_label
#define ngtk_create_text_entry   ngtk_xlib_create_text_entry

#endif
