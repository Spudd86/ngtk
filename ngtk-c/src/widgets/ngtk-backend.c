/*
 * ngtk-backend.c
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

#include "ngtk-backend.h"

void ngtk_backend_init (NGtkBackend *self)
{
	NGTK_BACKEND_O2F (self) -> init (self);
}

void ngtk_backend_start_main_loop (NGtkBackend *self)
{
	NGTK_BACKEND_O2F (self) -> start_main_loop (self);
}

void ngtk_backend_quit_main_loop (NGtkBackend *self)
{
	NGTK_BACKEND_O2F (self) -> quit_main_loop (self);
}

void ngtk_backend_quit (NGtkBackend *self)
{
	NGTK_BACKEND_O2F (self) -> quit (self);
}

NGtkContainer* ngtk_backend_create_root_window (NGtkBackend *self, const char *title)
{
	return NGTK_BACKEND_O2F(self) -> create_root_window (self, title);
}

NGtkComponent* ngtk_backend_create_button (NGtkBackend *self, NGtkContainer* parent, const char *text)
{
	return NGTK_BACKEND_O2F(self) -> create_button (self, parent, text);
}

NGtkComponent* ngtk_backend_create_label (NGtkBackend *self, NGtkContainer* parent, const char *text)
{
	return NGTK_BACKEND_O2F(self) -> create_label (self, parent, text);
}

NGtkComponent* ngtk_backend_create_text_entry (NGtkBackend *self, NGtkContainer* parent, const char *initial_text, int max_text_len)
{
	return NGTK_BACKEND_O2F(self) -> create_text_entry (self, parent, initial_text, max_text_len);
}

NGtkEventGenerator* ngtk_backend_get_focus_holder (NGtkBackend *self)
{
	return NGTK_BACKEND_O2F(self) -> get_focus_holder (self);
}

int ngtk_backend_set_focus_holder (NGtkBackend *self, NGtkComponent* new_focus)
{
	return NGTK_BACKEND_O2F(self) -> set_focus_holder (self, new_focus);
}

NGtkEventGenerator* ngtk_backend_focus_to_next (NGtkBackend *self)
{
	return NGTK_BACKEND_O2F(self) -> focus_to_next (self);
}

void ngtk_backend_print (NGtkBackend *self, const char *format, ...)
{
	va_list args;
	va_start (args, format);
	NGTK_BACKEND_O2F (self) -> print (self, format, args);
	va_end (args);
}

void ngtk_backend_debug (NGtkBackend *self, const char *format, ...)
{
	va_list args;
	va_start (args, format);
	NGTK_BACKEND_O2F (self) -> debug (self, format, args);
	va_end (args);
}

void ngtk_backend_error (NGtkBackend *self, const char *format, ...)
{
	va_list args;
	va_start (args, format);
	NGTK_BACKEND_O2F (self) -> error (self, format, args);
	va_end (args);
}
