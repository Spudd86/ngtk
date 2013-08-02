/*
 * ngtk-nc.h - Part of the NGtk library
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
