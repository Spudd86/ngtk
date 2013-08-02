/*
 * ngtk-widget-window.c - Part of the NGtk library
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

#include <stdio.h>
#include "ngtk-win.h"

NGtkObject* ngtk_win_create_window_imp (NGtkBackend *self, const char* title, int visible)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp, *inCont;
	HWND hwnd;
	
	hwnd = CreateWindowExA (
		WS_EX_CLIENTEDGE, /* A sunken edge border. Pretty sure we can just use 0=WS_EX_LEFT default */
		ngtk_win_get_root_window_class_name (self),
		title,
		WS_OVERLAPPEDWINDOW, /* Default window style - border and title bar */
		CW_USEDEFAULT, CW_USEDEFAULT, /* Initial X and Y position of the window */
		CW_USEDEFAULT, CW_USEDEFAULT, /* Initial width and height of the window. Default is only valid for overlapped windows! */
		NULL, /* Parent window */
		NULL, /* Menu resource */
		NGtk_Win_hInstance,
		NULL /* The lParam value that will be passed to the window function on the WM_CREATE message */
		);

	obj    = ngtk_object_new ();
	inW    = ngtk_basic_base_create_interface (obj, self);
	inComp = ngtk_win_component_create_interface (obj, hwnd, NULL, TRUE, TRUE, title, visible);
	inCont = ngtk_win_container_create_interface (obj);

	ngtk_component_set_visible (obj, visible);

	return obj;
}

NGtkObject* ngtk_win_create_label_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp;
	
	HWND hwnd = CreateWindowExA (
		0, /* Default */
		"STATIC",
		text,
		WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, /* Regular push button */
		0, 0, /* X, Y */
		50, 50, /* Temporary untill someone will change it */
		ngtk_win_component_get_hwnd (parent), /* Parent window */
		NULL, /* Number ID */
		NGtk_Win_hInstance, /* Instance */
		NULL /* The lParam passed with WM_CREATE message */
		);

	obj    = ngtk_object_new ();
	inW    = ngtk_basic_base_create_interface (obj, self);
	inComp = ngtk_win_component_create_interface (obj, hwnd, NULL, TRUE, TRUE, text, visible);

	ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, visible);

	return obj;
}

NGtkObject* ngtk_win_create_button_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp;
	
	HWND hwnd = CreateWindowExA (
		0, /* Default */
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_TEXT, /* Regular push button */
		0, 0, /* X, Y */
		50, 50, /* Temporary untill someone will change it */
		ngtk_win_component_get_hwnd (parent), /* Parent window */
		NULL, /* Number ID */
		NGtk_Win_hInstance, /* Instance */
		NULL /* The lParam passed with WM_CREATE message */
		);

	obj    = ngtk_object_new ();
	inW    = ngtk_basic_base_create_interface (obj, self);
	inComp = ngtk_win_component_create_interface (obj, hwnd, NULL, TRUE, TRUE, text, visible);

	ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, visible);

	return obj;
}

NGtkObject* ngtk_win_create_text_entry_imp (NGtkBackend *self, NGtkContainer *parent, const char* initial_text, int visible, int max_text_len)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp;
	
	HWND hwnd = CreateWindowExA (
		0, /* Default */
		"EDIT",
		initial_text,
		/* Regular one-line text entry field. Note that text edit widgets are
		 * limited to a text matching the view size. Adding ES_AUTOHSCROOL*/
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 0, /* X, Y */
		150, 150, /* Temporary untill someone will change it */
		ngtk_win_component_get_hwnd (parent), /* Parent window */
		NULL, /* Number ID */
		NGtk_Win_hInstance, /* Instance */
		NULL /* The lParam passed with WM_CREATE message */
		);

	SendMessage (hwnd, EM_LIMITTEXT, max_text_len + 1, 0);
	obj    = ngtk_object_new ();
	inW    = ngtk_basic_base_create_interface (obj, self);
	inComp = ngtk_win_component_create_interface (obj, hwnd, NULL, TRUE, TRUE, initial_text, visible);

	ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, visible);

	return obj;
}
