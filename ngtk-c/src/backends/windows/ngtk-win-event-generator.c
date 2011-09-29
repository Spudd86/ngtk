/*
 * ngtk-win-event-generator.c
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

#include <Windows.h>
#include "ngtk-win-base.h"
#include "ngtk-win-event-generator.h"

NGtkInterface* ngtk_win_event_generator_create_interface ()
{
	NGtkInterface *in = ngtk_basic_event_generator_create_interface ();

	NGTK_EVENT_GENERATOR_I2F (in) -> add_mouse_listener    = ngtk_win_event_generator_add_mouse_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_mouse_listeners = ngtk_win_event_generator_clear_mouse_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> grab_keyboard_focus   = ngtk_win_event_generator_grab_keyboard_focus;
	NGTK_EVENT_GENERATOR_I2F (in) -> send_click            = ngtk_win_event_generator_send_click;
}

void ngtk_win_event_generator_grab_keyboard_focus (NGtkEventGenerator *self)
{
	SetFocus (NGTK_WINBASE_O2D (self)->hwnd);
	ngtk_basic_event_generator_grab_keyboard_focus (self);
}
