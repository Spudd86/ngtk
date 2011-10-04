/*
 * ngtk-nc-defs.h
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

#ifndef __NGtk_nc_defs__
#define __NGtk_nc_defs__

#include "../../widgets/ngtk-widgets.h"

void            ngtk_nc_init                ();
void            ngtk_nc_start_main_loop     ();
void            ngtk_nc_quit_main_loop      ();
void            ngtk_nc_quit                ();

NGtkContainer*  ngtk_nc_create_root_window  (const char* title);
NGtkComponent*  ngtk_nc_create_button       (const char* text);
NGtkComponent*  ngtk_nc_create_label        (const char* text);
NGtkComponent*  ngtk_nc_create_text_entry   (const char* text);

/* Utility functions of this backend */
void           ngtk_nc_set_focus_holder (NGtkComponent* eg);
NGtkComponent* ngtk_nc_get_focus_holder ();

#endif
