/*
 * ngtk-basic-backend.h - Part of the NGtk library
 *
 * Copyright (c) 2011, Barak Itkin <lightningismyname at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NGtk nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __NGtk_basic_backend__
#define __NGtk_basic_backend__

#include "../../widgets/ngtk-backend.h"

typedef NGtkBackend NGtkBasicBackend;

/** A struct containing the data which is typically used by common
 * backend implementations */
typedef struct _ngtk_basic_backend_d {
	NGtkContainer     *root_window;
	NGtkComponent     *focus_holder;
	NGtkComponentList  all_components;
	int                should_quit;
	int                initialized;
} NGtkBasicBackendD;

#define NGTK_BASIC_BACKEND_O2D(comp) NGTK_O2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkBasicBackendD,0)
#define NGTK_BASIC_BACKEND_I2D(comp) NGTK_I2D_CAST(comp,NGTK_BACKEND_TYPE,NGtkBasicBackendD,0)

NGtkBackendI*       ngtk_basic_backend_create_interface   (NGtkObject *obj);
void                ngtk_basic_backend_d_free             (void *d);

//void                ngtk_basic_backend_init               (NGtkBasicBackend *self);
//void                ngtk_basic_backend_start_main_loop    (NGtkBasicBackend *self);
void                ngtk_basic_backend_quit_main_loop     (NGtkBasicBackend *self);
//void                ngtk_basic_backend_quit               (NGtkBasicBackend *self);

//NGtkContainer*      ngtk_basic_backend_create_root_window (NGtkBasicBackend *self, const char *title);
//NGtkComponent*      ngtk_basic_backend_create_button      (NGtkBasicBackend *self, NGtkContainer* parent, const char *text);
//NGtkComponent*      ngtk_basic_backend_create_label       (NGtkBasicBackend *self, NGtkContainer* parent, const char *text);
//NGtkComponent*      ngtk_basic_backend_create_text_entry  (NGtkBasicBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

NGtkComponent*  ngtk_basic_backend_get_focus_holder   (NGtkBasicBackend *self);
int             ngtk_basic_backend_set_focus_holder   (NGtkBasicBackend *self, NGtkComponent* new_focus);
NGtkComponent*  ngtk_basic_backend_focus_to_next      (NGtkBasicBackend *self);

NGtkContainer*  ngtk_basic_backend_get_root_window    (NGtkBasicBackend *self);
const NGtkList* ngtk_basic_backend_get_all_components (NGtkBasicBackend *self);

void                ngtk_basic_backend_print              (NGtkBasicBackend *self, const char *format, va_list args);
void                ngtk_basic_backend_debug              (NGtkBasicBackend *self, const char *format, va_list args);
void                ngtk_basic_backend_error              (NGtkBasicBackend *self, const char *format, va_list args);


/* Specific function to this implementation: */
void    ngtk_basic_backend_call_after_init             (NGtkBasicBackend *self);
void    ngtk_basic_backend_call_before_start_main_loop (NGtkBasicBackend *self);
int     ngtk_basic_backend_can_focus_on                (NGtkBasicBackend *self, NGtkComponent *new_focus);

void ngtk_basic_backend_component_register   (NGtkComponent *comp);
void ngtk_basic_backend_component_unregister (NGtkComponent *comp);

void ngtk_basic_backend_root_window_register   (NGtkContainer *root_window);
void ngtk_basic_backend_root_window_unregister (NGtkContainer *root_window);

int     ngtk_basic_backend_should_quit                 (NGtkBasicBackend *self);

#endif
