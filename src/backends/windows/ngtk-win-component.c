/*
 * ngtk-win-component.c - Part of the NGtk library
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


#include "ngtk-win.h"

static void ngtk_win_component_destructor (NGtkComponent *self);
NGtkInterface* ngtk_win_component_create_interface (NGtkObject *obj, HWND hwnd, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (obj, parent, enabled, focusable, text, visible);
	NGtkWinComponentD *wcd = ngtk_new (NGtkWinComponentD);

	in->imp_data[1]      = wcd;
	wcd->hwnd            = hwnd;
	wcd->base_wndproc    = (WNDPROC) GetWindowLongPtrA (hwnd, GWL_WNDPROC);
	in->imp_data_free[1] = ngtk_free;
	
	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_win_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_win_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_win_component_set_visible;

	SetParent ((parent != NULL) ? ngtk_win_component_get_hwnd (parent) : NULL, hwnd);

	ngtk_basic_backend_component_register (obj);
	ngtk_object_push_destructor (obj, ngtk_basic_backend_component_unregister);
	ngtk_object_push_destructor (obj, ngtk_win_component_destructor);

	/* Register the component in the HWND, so that we can get the component
	 * from the HWND object */
	ngtk_win_call_after_compononet_creation (obj);
	/* Only now when the above link was made, switch to our WndProc which
	 * relies on the object */
	SetWindowLongPtrA (hwnd, GWL_WNDPROC, (LONG) ngtk_win_general_WndProc);

	return in;
}

static void ngtk_win_component_destructor (NGtkComponent *self)
{
	if (NGTK_WIN_COMPONENT_O2D (self)->hwnd != NULL)
		DestroyWindow (NGTK_WIN_COMPONENT_O2D (self)->hwnd);
}

void ngtk_win_component_set_enabled (NGtkComponent *self, int enabled)
{
	EnableWindow (NGTK_WIN_COMPONENT_O2D (self)->hwnd, enabled);
	ngtk_basic_component_set_enabled (self, enabled);
}

void ngtk_win_component_set_visible (NGtkComponent *self, int visible)
{
	ShowWindow (NGTK_WIN_COMPONENT_O2D (self)->hwnd, visible ? SW_NORMAL : SW_HIDE);
	ngtk_basic_component_set_visible (self, visible);
}

void ngtk_win_component_set_text (NGtkComponent *self, const char *text)
{
	SetWindowTextA (NGTK_WIN_COMPONENT_O2D (self)->hwnd, text);
	ngtk_basic_component_set_text (self, text);
}

HWND ngtk_win_component_get_hwnd (NGtkComponent *self)
{
	return NGTK_WIN_COMPONENT_O2D (self)->hwnd;
}

WNDPROC ngtk_win_component_get_base_wnd_proc (NGtkComponent *self)
{
	return NGTK_WIN_COMPONENT_O2D (self)->base_wndproc;
}

void ngtk_win_component_call_on_wnd_destroy (NGtkComponent *self)
{
	NGtkWinComponentD *wcd = NGTK_WIN_COMPONENT_O2D (self);

	/* Since this is called on the WM_DESTROY signal, we should
	 * switch back to the original WndProc since we are done handling
	 * this window. Let the system handle the destruction.
	 * Also note that since we remove the HWND<->component association
	 * on the WM_DESTROY call, we can't use our own WndProc anymore!
	 */
	SetWindowLongPtrA (wcd->hwnd, GWL_WNDPROC, (LONG) wcd->base_wndproc);
	/* Mark that we are no longer associated with any HWND, so that we
	 * won't try in the destructor to destroy an already destroyed HWND */
	wcd->hwnd = NULL;
}
