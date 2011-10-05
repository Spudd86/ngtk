/*
 * ngtk-nc.h
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

#ifndef __NGtk_nc_h__
#define __NGtk_nc_h__

#include "ngtk-nc-widget-types.h"

#include "ngtk-nc-backend.h"
#include "ngtk-nc-component.h"
#include "ngtk-nc-container.h"
#include "ngtk-nc-graphics.h"

#include "ngtk-nc-window.h"

#define ngtk_nc_component_has_focus(comp) (ngtk_backend_get_focus_holder (ngtk_base_get_backend (comp)) == (comp))

#define ngtk_init                ngtk_nc_init
#define ngtk_start_main_loop     ngtk_nc_start_main_loop
#define ngtk_quit_main_loop      ngtk_nc_quit_main_loop
#define ngtk_quit                ngtk_nc_quit

#define ngtk_create_root_window  ngtk_nc_create_root_window
#define ngtk_create_button       ngtk_nc_create_button
#define ngtk_create_label        ngtk_nc_create_label
#define ngtk_create_text_entry   ngtk_nc_create_text_entry

#endif
