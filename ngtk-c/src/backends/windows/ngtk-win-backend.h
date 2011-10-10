/*
 * ngtk-win-backend.h
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

NGtkWinBackend* ngtk_win_backend_new ();
#endif
