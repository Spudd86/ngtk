/*
 * ngtk-win-backend.h - Part of the NGtk library
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

#ifndef __NGtk_win_backend__
#define __NGtk_win_backend__

#include "../basic/ngtk-basic.h"
#include "ngtk-win-widget-types.h"
#include <windows.h>

NGtkBackendI*   ngtk_win_backend_create_interface   (NGtkObject *obj);
void            ngtk_win_backend_d_free             (void *d);

void            ngtk_win_backend_init               (NGtkWinBackend *self);
void            ngtk_win_backend_start_main_loop    (NGtkWinBackend *self);
void            ngtk_win_backend_quit_main_loop     (NGtkWinBackend *self);
void            ngtk_win_backend_quit               (NGtkWinBackend *self);

NGtkContainer*  ngtk_win_backend_create_root_window (NGtkWinBackend *self, const char *title);
NGtkComponent*  ngtk_win_backend_create_button      (NGtkWinBackend *self, NGtkContainer* parent, const char *text);
NGtkComponent*  ngtk_win_backend_create_label       (NGtkWinBackend *self, NGtkContainer* parent, const char *text);
NGtkComponent*  ngtk_win_backend_create_text_entry  (NGtkWinBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len);

#define         ngtk_win_backend_get_focus_holder   ngtk_basic_backend_get_focus_holder
int             ngtk_win_backend_set_focus_holder   (NGtkWinBackend *self, NGtkComponent* new_focus);
#define         ngtk_win_backend_focus_to_next      ngtk_basic_backend_focus_to_next
#define         ngtk_win_backend_get_root_window    ngtk_basic_backend_get_root_window
#define         ngtk_win_backend_get_all_components ngtk_basic_backend_get_all_components

#define         ngtk_win_backend_print              ngtk_basic_backend_print
#define         ngtk_win_backend_debug              ngtk_basic_backend_debug
#define         ngtk_win_backend_error              ngtk_basic_backend_error

#define         ngtk_win_backend_should_quit        ngtk_basic_backend_should_quit

/* Non interface functions */

void            ngtk_win_backend_register_window    (NGtkWinBackend *self, HWND wnd, NGtkComponent *comp);
NGtkComponent*  ngtk_win_backend_unregister_window  (NGtkWinBackend *self, HWND wnd);
NGtkComponent*  ngtk_win_backend_get_for_window     (NGtkWinBackend *self, HWND wnd);

NGTK_EXPORT NGtkWinBackend* ngtk_win_backend_new ();
#endif
