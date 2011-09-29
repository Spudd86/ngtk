/*
 * ngtk-xlib-event-generator.h
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

#ifndef __NGtk_xlib_event_generator__
#define __NGtk_xlib_event_generator__

#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkEventGeneratorF object */
NGtkInterface* ngtk_xlib_event_generator_create_interface ();

#define ngtk_xlib_event_generator_add_mouse_listener       ngtk_basic_event_generator_add_mouse_listener
#define ngtk_xlib_event_generator_fire_mouse_event         ngtk_basic_event_generator_fire_mouse_event
#define ngtk_xlib_event_generator_clear_mouse_listeners    ngtk_basic_event_generator_clear_mouse_listeners

#define ngtk_xlib_event_generator_add_keyboard_listener    ngtk_basic_event_generator_add_keyboard_listener
#define ngtk_xlib_event_generator_fire_keyboard_event      ngtk_basic_event_generator_fire_keyboard_event
#define ngtk_xlib_event_generator_clear_keyboard_listeners ngtk_basic_event_generator_clear_keyboard_listeners

void    ngtk_xlib_event_generator_grab_keyboard_focus      (NGtkEventGenerator* self);

#endif
