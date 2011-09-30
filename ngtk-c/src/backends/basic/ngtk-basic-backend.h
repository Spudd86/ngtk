/*
 * ngtk-basic-backend.h
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

#ifndef __NGtk_basic_backend__
#define __NGtk_basic_backend__

#include "../../widgets/ngtk-backend.h"

typedef NGtkBackend NGtkBasicBackend;

typedef struct _ngtk_basic_backend_d {
	NGtkContainer     *root_window;
	NGtkComponent     *focus_holder;
	NGtkComponentList  all_components;
	int                should_quit;
	int                initialized;
} NGtkBasicBackendD;

#define NGTK_BASIC_BACKEND_O2D(comp) NGTK_O2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkBasicBackendD,0)
#define NGTK_BASIC_BACKEND_I2D(comp) NGTK_I2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkBasicBackendD,0)

NGtkBackendI*       ngtk_basic_backend_create_interface   ();
void                ngtk_basic_backend_d_free             (void *d);

//void                ngtk_basic_backend_init               (NGtkBasicBackend *self);
//void                ngtk_basic_backend_start_main_loop    (NGtkBasicBackend *self);
void                ngtk_basic_backend_quit_main_loop     (NGtkBasicBackend *self);
//void                ngtk_basic_backend_quit               (NGtkBasicBackend *self);

//NGtkContainer*      ngtk_basic_backend_create_root_window (NGtkBasicBackend *self, const char *title);
//NGtkComponent*      ngtk_basic_backend_create_button      (NGtkBasicBackend *self, NGtkContainer* parent, const char *text);
//NGtkComponent*      ngtk_basic_backend_create_label       (NGtkBasicBackend *self, NGtkContainer* parent, const char *text);
//NGtkComponent*      ngtk_basic_backend_create_text_entry  (NGtkBasicBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

NGtkEventGenerator* ngtk_basic_backend_get_focus_holder   (NGtkBasicBackend *self);
int                 ngtk_basic_backend_set_focus_holder   (NGtkBasicBackend *self, NGtkComponent* new_focus);
NGtkEventGenerator* ngtk_basic_backend_focus_to_next      (NGtkBasicBackend *self);

void                ngtk_basic_backend_print              (NGtkBasicBackend *self, const char *format, va_list args);
void                ngtk_basic_backend_debug              (NGtkBasicBackend *self, const char *format, va_list args);
void                ngtk_basic_backend_error              (NGtkBasicBackend *self, const char *format, va_list args);


/* Specific function to this implementation: */
void    ngtk_basic_backend_call_after_init             (NGtkBasicBackend *self);
void    ngtk_basic_backend_call_before_start_main_loop (NGtkBasicBackend *self);
int     ngtk_basic_backend_can_focus_on                (NGtkBasicBackend *self, NGtkComponent *new_focus);

int     ngtk_basic_backend_should_quit                 (NGtkBasicBackend *self);

#endif
