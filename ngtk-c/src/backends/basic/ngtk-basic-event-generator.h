/*
 * ngtk-basic-event-generator.h
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

#ifndef __NGtk_basic_event_generator__
#define __NGtk_basic_event_generator__

#include "../../widgets/ngtk-widgets.h"

typedef struct _ngtk_basic_mouse_listener_info {
	NGtkMouseListener  listener;
	void              *data;
	NGtkFreeFunc       free_func;
} NGtkBasicMouseListenerInfo;

typedef struct _ngtk_basic_keyboard_listener_info {
	NGtkKeyboardListener  listener;
	void                 *data;
	NGtkFreeFunc          free_func;
} NGtkBasicKeyboardListenerInfo;

typedef struct _ngtk_basic_event_generator_d {
	NGtkMouseListener    mouse_native_listener;
	NGtkList*            mouse_listener_infos;

	NGtkKeyboardListener keyboard_native_listener;
	NGtkList*            keyboard_listener_infos;
} NGtkBasicEventGeneratorD;

#define NGTK_BASIC_EVENT_GENERATOR_O2D(comp) NGTK_O2D_CAST(comp,NGTK_EVENT_GENERATOR_TYPE,NGtkBasicEventGeneratorD,0)
#define NGTK_BASIC_EVENT_GENERATOR_I2D(comp) NGTK_I2D_CAST(comp,NGTK_EVENT_GENERATOR_TYPE,NGtkBasicEventGeneratorD,0)

NGtkInterface* ngtk_basic_event_generator_create_interface ();
void           ngtk_basic_event_generator_d_free           (void *d);

void ngtk_basic_event_generator_add_mouse_listener       (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
void ngtk_basic_event_generator_fire_mouse_event         (NGtkEventGenerator *self, NGtkMouseEvent *evnt);
void ngtk_basic_event_generator_clear_mouse_listeners    (NGtkEventGenerator *self);

void ngtk_basic_event_generator_add_keyboard_listener    (NGtkEventGenerator *self, NGtkKeyboardListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
void ngtk_basic_event_generator_fire_keyboard_event      (NGtkEventGenerator *self, NGtkKeyboardEvent *evnt);
void ngtk_basic_event_generator_clear_keyboard_listeners (NGtkEventGenerator *self);

void ngtk_basic_event_generator_grab_keyboard_focus      (NGtkEventGenerator *self);

#endif
