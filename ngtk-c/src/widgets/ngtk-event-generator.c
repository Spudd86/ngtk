/*
 * ngtk-event-generator.c
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

#include "ngtk-event-generator.h"

void ngtk_event_generator_add_mouse_listener (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc)
{
	NGTK_EVENT_GENERATOR_O2F (self)->add_mouse_listener (self, ListenFunc, Data, FreeFunc);
}
void ngtk_event_generator_fire_mouse_event (NGtkEventGenerator *self, NGtkMouseEvent *evnt)
{
	NGTK_EVENT_GENERATOR_O2F (self)->fire_mouse_event (self, evnt);
}
void ngtk_event_generator_clear_mouse_listeners (NGtkEventGenerator *self)
{
	NGTK_EVENT_GENERATOR_O2F (self)->clear_mouse_listeners (self);
}

void ngtk_event_generator_add_keyboard_listener (NGtkEventGenerator *self, NGtkKeyboardListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc)
{
	NGTK_EVENT_GENERATOR_O2F (self)->add_keyboard_listener (self, ListenFunc, Data, FreeFunc);
}
void ngtk_event_generator_fire_keyboard_event (NGtkEventGenerator *self, NGtkKeyboardEvent *evnt)
{
	NGTK_EVENT_GENERATOR_O2F (self)->fire_keyboard_event (self, evnt);
}
void ngtk_event_generator_clear_keyboard_listeners (NGtkEventGenerator *self)
{
	NGTK_EVENT_GENERATOR_O2F (self)->clear_keyboard_listeners (self);
}

void ngtk_event_generator_grab_keyboard_focus (NGtkEventGenerator *self)
{
	NGTK_EVENT_GENERATOR_O2F (self)->grab_keyboard_focus (self);
}
