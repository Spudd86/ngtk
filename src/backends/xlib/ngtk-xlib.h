/*
 * ngtk-xlib.h - Part of the NGtk library
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

#ifndef __NGtk_xlib_h__
#define __NGtk_xlib_h__

#include "ngtk-xlib-defs.h"

#include "ngtk-xlib-widget-types.h"

#include "ngtk-xlib-backend.h"
#include "ngtk-xlib-component.h"
#include "ngtk-xlib-container.h"

#include "ngtk-xlib-window.h"
#include "ngtk-xlib-graphics.h"

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
