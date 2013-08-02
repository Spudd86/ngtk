/*
 * ngtk-backend.c - Part of the NGtk library
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

NGtkComponent* ngtk_backend_get_focus_holder (NGtkBackend *self)
{
	return NGTK_BACKEND_O2F(self) -> get_focus_holder (self);
}

int ngtk_backend_set_focus_holder (NGtkBackend *self, NGtkComponent* new_focus)
{
	return NGTK_BACKEND_O2F(self) -> set_focus_holder (self, new_focus);
}

NGtkComponent* ngtk_backend_focus_to_next (NGtkBackend *self)
{
	return NGTK_BACKEND_O2F(self) -> focus_to_next (self);
}

NGtkContainer* ngtk_backend_get_root_window (NGtkBackend *self)
{
	return NGTK_BACKEND_O2F(self) -> get_root_window (self);
}

const NGtkList* ngtk_backend_get_all_components (NGtkBackend *self)
{
	return NGTK_BACKEND_O2F(self) -> get_all_components (self);
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
