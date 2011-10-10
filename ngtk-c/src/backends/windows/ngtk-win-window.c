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

NGtkObject* ngtk_win_create_window (NGtkBackend *backend, const char* title, int visible)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp, *inCont;
	HWND hwnd;
	
	hwnd = CreateWindowExA (
		WS_EX_CLIENTEDGE, /* A sunken edge border. Pretty sure we can just use 0=WS_EX_LEFT default */
		ngtk_win_get_root_window_class_name (backend),
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
	inW    = ngtk_basic_base_create_interface (obj, backend);
	inComp = ngtk_win_component_create_interface (obj, hwnd, NULL, TRUE, TRUE, title, visible);
	inCont = ngtk_win_container_create_interface (obj);

	ngtk_component_set_visible (obj, visible);

	return obj;
}

NGtkObject* ngtk_win_create_button (const char* text, NGtkContainer *parent)
{
	NGtkObject *obj;
	NGtkInterface *inW, *inComp, *inEG;
	WNDPROC nativeButProc;

	obj    = ngtk_object_new ();
	inW    = ngtk_win_base_create_interface ();
	inComp = ngtk_win_component_create_interface (TRUE, NULL, text, TRUE);
	inEG   = ngtk_basic_event_generator_create_interface ();

	ngtk_object_implement (obj, inW);
	ngtk_object_implement (obj, inComp);
	ngtk_object_implement (obj, inEG);

	/* Creating the window will start generating messages that should be
	 * handled, so we must have the object ready before doing this */

	NGTK_WINBASE_I2D (inW)->hwnd = CreateWindowExA (
		0, /* Default */
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_TEXT, /* Regular push button */
		0, 0, /* X, Y */
		50, 50, /* Temporary untill someone will change it */
		NGTK_WINBASE_O2D (parent)->hwnd, /* Parent window */
		NULL, /* Number ID */
		NGtk_hInstance, /* Instance */
		NULL /* The lParam passed with WM_CREATE message */
		);

	nativeButProc = (WNDPROC) GetWindowLong (NGTK_WINBASE_I2D (inW)->hwnd, GWL_WNDPROC);
	NGTK_WINBASE_I2D (inW)->base_wndproc = nativeButProc;
	SetWindowLong (NGTK_WINBASE_I2D (inW)->hwnd, GWL_WNDPROC, (LONG)ngtk_win_window_WndProc);

	SetToHwnd (NGTK_WINBASE_I2D (inW)->hwnd, obj);

	ngtk_container_add_child (parent, obj);
	ngtk_component_set_visible (obj, TRUE);


	return obj;
}

NGtkObject* ngtk_win_create_window_imp (NGtkBackend *self, const char* title, int visible)
{
}

NGtkObject* ngtk_win_create_label_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent)
{
}

NGtkObject* ngtk_win_create_button_imp (NGtkBackend *self, const char* text, int visible, NGtkContainer *parent)
{
}

NGtkObject* ngtk_win_create_text_entry_imp (NGtkBackend *self, NGtkContainer *parent, const char* initial_text, int visible, int max_text_len)
{
}
