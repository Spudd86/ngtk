/*
 * ngtk-xlib-component.h - Part of the NGtk library
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

#ifndef __NGtk_xlib_component__
#define __NGtk_xlib_component__

#include <X11/Xlib.h>
#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

typedef struct _ngtk_xlib_component_d {
	/** The area that this component covers, in pixels. The coordinates
	 *  are relative to the top-left corner of the parent component. */
	NGtkRectangle  area;
	/** The Xlib window which is used to draw/display/interact with this
	 * widget */
	Window         wnd;
	/** In Xlib, resizing a widget to a zero width/height would cause a
	 * fatal error. Therefore, whenever such a request is made, we will
	 * hide the widget to "fake" it as having zero size. This variable
	 * will hold a TRUE value iff the last resize request for this
	 * widget included a zero size in one (or more) of it's two
	 * dimensions. */
	int            zero_size_hide;
} NGtkXlibComponentD;

#define NGTK_XLIB_COMPONENT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkXlibComponentD,1)
#define NGTK_XLIB_COMPONENT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkXlibComponentD,1)

/**
 * Implement the \ref NGtkComponentF interface  inside the given object,
 * where the implementation is backed up by the Xlib backend.
 * @warning The object must implement the \NGtkBaseF interface and have
 *          an Xlib backend returned by the base, in order for this
 *          constructor to succeed
 */
NGtkInterface* ngtk_xlib_component_create_interface (NGtkObject *obj, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible);

#define  ngtk_xlib_component_get_parent   ngtk_basic_component_get_parent

#define  ngtk_xlib_component_get_enabled  ngtk_basic_component_get_enabled
void     ngtk_xlib_component_set_enabled  (NGtkComponent *self, int enabled);

#define  ngtk_xlib_component_get_visible  ngtk_basic_component_get_visible
void     ngtk_xlib_component_set_visible  (NGtkComponent *self, int visible);

#define  ngtk_xlib_component_get_text     ngtk_basic_component_get_text
void     ngtk_xlib_component_set_text     (NGtkComponent *self, const char *text);

#define  ngtk_xlib_component_redraw       ngtk_basic_component_redraw

/**
 * Set the area of the given component, in coordinates relative to the
 * parent container.
 * @param already_there In case the component was already moved to that
 *                      place, and this call is only made to update the,
 *                      NGtk data structures, this should be TRUE.
 */
void                 ngtk_xlib_component_put_to     (NGtkComponent *self, const NGtkRectangle *new_area, int already_there);
/** Return the Xlib window of this component */
Window               ngtk_xlib_component_get_window (NGtkComponent *self);
/** Return the area of this component */
const NGtkRectangle* ngtk_xlib_component_get_rect   (NGtkComponent *self);
/**
 * When the Xlib window is destroyed, this is the function that should
 * be called to make sure no further attempts to use that window are
 * made. */
void ngtk_xlib_component_call_on_window_destroyed   (NGtkComponent *self);

#endif
