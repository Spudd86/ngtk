/*
 * ngtk-xlib-window.h
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

#include "ngtk-xlib-container.h"

NGtkObject* ngtk_xlib_create_button_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent);
NGtkObject* ngtk_xlib_create_label_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent);
NGtkObject* ngtk_xlib_create_window_imp (NGtkBackend *self, const char* title, int visible);
NGtkObject* ngtk_xlib_create_text_entry_imp (NGtkBackend *self, NGtkContainer *parent, const char* initial_text, int visible, int max_text_len);
