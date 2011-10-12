/*
 * ngtk-widget-window.c
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

	SendMessage (hwnd, EM_LIMITTEXT, max_text_len + 1, NULL);
	obj    = ngtk_object_new ();
	inW    = ngtk_basic_base_create_interface (obj, self);
	inComp = ngtk_win_component_create_interface (obj, hwnd, NULL, TRUE, TRUE, initial_text, visible);

	ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, visible);

	return obj;
}
