/*
 * ngtk-win-defs.h - Part of the NGtk library
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

#ifndef __NGtk_win_defs__
#define __NGtk_win_defs__

#include "ngtk-win-widget-types.h"

#include "ngtk-win-backend.h"
#include "ngtk-win-component.h"
#include "ngtk-win-container.h"

// #include "ngtk-widget-window.h"

#define NGtk_Win_hInstance     (GetModuleHandle (NULL))
typedef NGtkObject* NGtk_Win_ExtraDataType;

void  ngtk_win_call_after_compononet_creation (NGtkComponent *obj);
void  ngtk_win_init                           (NGtkBackend *backend);
void  ngtk_win_start_main_loop                (NGtkBackend *backend);
void  ngtk_win_quit_main_loop                 (NGtkBackend *backend);
void  ngtk_win_quit                           (NGtkBackend *backend);

LRESULT CALLBACK ngtk_win_general_WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LPCSTR ngtk_win_get_root_window_class_name    (NGtkBackend *backend);

#endif
