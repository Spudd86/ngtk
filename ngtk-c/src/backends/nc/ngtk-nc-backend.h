/*
 * ngtk-nc-backend.h
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

#ifndef __NGtk_nc_backend__
#define __NGtk_nc_backend__

#include "../basic/ngtk-basic.h"
#include "ngtk-nc-widget-types.h"
#include <ncurses.h>

/* Colors used by this backend */
typedef enum {
	NGTK_NC_WHITE_ON_BLACK = 0,
	NGTK_NC_GRAY_ON_BLACK = 1,
	NGTK_NC_WHITE_ON_GRAY = 2,
	NGTK_NC_BLACK_ON_GRAY = 3,
	NGTK_NC_BLACK_ON_WHITE = 4,
	NGTK_NC_GRAY_ON_WHITE = 5,

	NGTK_NC_COLOR_MAX = 6
} NGtkNcColorName;

typedef struct _ngtk_nc_backend_d {
	unsigned int freeze_count;
	int          has_waiting;
} NGtkNcBackendD;

#define NGTK_NC_BACKEND_O2D(comp) NGTK_O2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkNcBackendD,1)
#define NGTK_NC_BACKEND_I2D(comp) NGTK_I2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkNcBackendD,1)

NGtkBackendI*  ngtk_nc_backend_create_interface   (NGtkObject *obj);

void           ngtk_nc_backend_init               (NGtkNcBackend *self);
void           ngtk_nc_backend_start_main_loop    (NGtkNcBackend *self);
#define        ngtk_nc_backend_quit_main_loop     ngtk_basic_backend_quit_main_loop
void           ngtk_nc_backend_quit               (NGtkNcBackend *self);

NGtkContainer* ngtk_nc_backend_create_root_window (NGtkNcBackend *self, const char *title);
NGtkComponent* ngtk_nc_backend_create_button      (NGtkNcBackend *self, NGtkContainer* parent, const char *text);
NGtkComponent* ngtk_nc_backend_create_label       (NGtkNcBackend *self, NGtkContainer* parent, const char *text);
NGtkComponent* ngtk_nc_backend_create_text_entry  (NGtkNcBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

#define        ngtk_nc_backend_get_focus_holder   ngtk_basic_backend_get_focus_holder
#define        ngtk_nc_backend_set_focus_holder   ngtk_basic_backend_set_focus_holder
#define        ngtk_nc_backend_focus_to_next      ngtk_basic_backend_focus_to_next
#define        ngtk_nc_backend_get_root_window    ngtk_basic_backend_get_root_window
#define        ngtk_nc_backend_get_all_components ngtk_basic_backend_get_all_components

#define        ngtk_nc_backend_print              ngtk_basic_backend_print
#define        ngtk_nc_backend_debug              ngtk_basic_backend_debug
#define        ngtk_nc_backend_error              ngtk_basic_backend_error

#define        ngtk_nc_backend_should_quit        ngtk_basic_backend_should_quit

/* Non interface functions */

void           ngtk_nc_backend_drawing_accumulate  (NGtkNcBackend *self);
void           ngtk_nc_backend_drawing_release     (NGtkNcBackend *self);
/** Publish the window content to the screen */
void           ngtk_nc_backend_drawing_commit      (NGtkNcBackend *self, NGtkComponent *comp);
/** Fill the area of the window with spaces, and then show it to the screen */
void           ngtk_nc_backend_call_on_widget_hide (NGtkNcBackend *self, NGtkComponent *comp);

NGtkNcBackend* ngtk_nc_backend_new ();
#endif
