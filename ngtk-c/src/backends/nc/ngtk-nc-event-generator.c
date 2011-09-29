/*
 * ngtk-nc-event-generator.c
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

#include "ngtk-nc-base.h"
#include "ngtk-nc-event-generator.h"
#include "ngtk-nc-defs.h"

NGtkInterface* ngtk_nc_event_generator_create_interface ()
{
	NGtkInterface *in = ngtk_basic_event_generator_create_interface ();

	NGTK_EVENT_GENERATOR_I2F (in) -> add_mouse_listener       = ngtk_nc_event_generator_add_mouse_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_mouse_listeners    = ngtk_nc_event_generator_clear_mouse_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> fire_mouse_event         = ngtk_nc_event_generator_fire_mouse_event;

	NGTK_EVENT_GENERATOR_I2F (in) -> add_keyboard_listener    = ngtk_nc_event_generator_add_keyboard_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_keyboard_listeners = ngtk_nc_event_generator_clear_keyboard_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> fire_keyboard_event      = ngtk_nc_event_generator_fire_keyboard_event;

	NGTK_EVENT_GENERATOR_I2F (in) -> grab_keyboard_focus      = ngtk_nc_event_generator_grab_keyboard_focus;

	return in;
}

void ngtk_nc_event_generator_grab_keyboard_focus (NGtkEventGenerator *self)
{
	ngtk_nc_set_focus_holder (self);
	ngtk_basic_event_generator_grab_keyboard_focus (self);
}
