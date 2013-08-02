/*
 * ngtk-nc-backend.h - Part of the NGtk library
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

void           ngtk_nc_backend_print              (NGtkBasicBackend *self, const char *format, va_list args);
void           ngtk_nc_backend_debug              (NGtkBasicBackend *self, const char *format, va_list args);
void           ngtk_nc_backend_error              (NGtkBasicBackend *self, const char *format, va_list args);

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
