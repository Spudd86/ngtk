/*
 * ngtk-xlib-defs.h - Part of the NGtk library
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

#ifndef __NGtk_xlib_defs__
#define __NGtk_xlib_defs__

#include <X11/Xlib.h>
#include "../../widgets/ngtk-widgets.h"
#include "ngtk-xlib-widget-types.h"

void            ngtk_xlib_init                (NGtkXlibBackend *self);
void            ngtk_xlib_start_main_loop     (NGtkXlibBackend *self);
void            ngtk_xlib_quit_main_loop      (NGtkXlibBackend *self);
void            ngtk_xlib_quit                (NGtkXlibBackend *self);

NGtkContainer*  ngtk_xlib_create_root_window  (const char* title);
NGtkComponent*  ngtk_xlib_create_button       (NGtkContainer* parent, const char* text);
NGtkComponent*  ngtk_xlib_create_label        (NGtkContainer* parent, const char* text);
NGtkComponent*  ngtk_xlib_create_text_entry   (NGtkContainer* parent, const char* text);

#define NGTK_XLIB_EVENT_MASK (                                         \
	/* A part of a component became visible after it was hidden, so we \
	 * need to redraw it. This will generate an event of type Expose */\
	ExposureMask |                                                     \
	/* Any of the mouse buttons was pressed down. This will generate   \
	 * an event of type ButtonPress */                                 \
	ButtonPressMask |                                                  \
	/* Any of the mouse buttons was released. This will generate an    \
	 * event of type ButtonRelease */                                  \
	ButtonReleaseMask |                                                \
	/* Any of the keyboard keys was pressed down. This will generate   \
	 * an event of type KeyPress */                                    \
	KeyPressMask |                                                     \
	/* The mouse was moved while none of it's buttons was pressed.     \
	 * This will generate an event of type MotionNotify */             \
	PointerMotionMask |                                                \
	/* The mouse was moved while one or more of it's buttons was       \
	 * pressed. This will generate an event of type MotionNotify */    \
	ButtonMotionMask |                                                 \
	/* The window structure was modified. We will use this to be       \
	 * notified when the window was closed. This will generate an      \
	 * event of several types, we will catch just DestroyNotify */     \
	StructureNotifyMask                                                \
	)

#endif
