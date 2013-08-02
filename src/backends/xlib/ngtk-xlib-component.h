/*
 * ngtk-xlib-component.h
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
