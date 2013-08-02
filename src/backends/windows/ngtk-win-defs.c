/*
 * ngtk-win-defs.c
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
#include <windows.h>
#include "ngtk-win-defs.h"

int window_class_registered = FALSE;

/* The following must be Static variables, since sometimes they are compared
 * by the windows functions using a pointer comparision instead of actual
 * content comparision*/

static LPCSTR NGtk_Win_WinClassNameA = "NGtk_WindowsWindowClassName";
static LPCSTR NGtk_Win_ObjPropNameA  = "NGtk_Windows_ObjectProp";

/* static LPCWSTR NGtk_Win_WinClassNameW = L"NGtk_WindowsWindowClassName"; */
/* static LPCWSTR NGtk_Win_ObjPropNameW  = L"NGtk_Windows_ObjectProp"; */

static NGtkObject* GetFromHwnd (HWND hwnd)
{
	return (NGtkObject*) GetPropA (hwnd, NGtk_Win_ObjPropNameA);
}

void ngtk_win_call_after_compononet_creation (NGtkComponent* wdgt)
{
	SetPropA (ngtk_win_component_get_hwnd (wdgt), NGtk_Win_ObjPropNameA, wdgt);
}

static NGtkComponent* RemoveFromHwnd (HWND hwnd)
{
	return (NGtkComponent*) RemovePropA (hwnd, NGtk_Win_ObjPropNameA);
}

static int CALLBACK ngtk_win_mouse_handle (NGtkComponent* wc, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND last_but_press_here[3] = { NULL, NULL, NULL };
	const static int different_buttons = sizeof (last_but_press_here) / sizeof (HWND);
	
	int i;
	
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		if (ngtk_component_get_enabled (wc))
		{
			int but_press_index;

			NGtkMouseEvent m;
			
			if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP)
			{
				but_press_index = 0;
				m.button = NGTK_MBUT_L;
			}
			else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP)
			{
				but_press_index = 1;
				m.button = NGTK_MBUT_R;
			}
			else /* if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) */
			{
				but_press_index = 2;
				m.button = NGTK_MBUT_M;
			}
			
			if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN)
				m.type = NGTK_MET_DOWN;
			else
				m.type = NGTK_MET_UP;

			ngtk_interface_send_signal (ngtk_object_cast (wc, NGTK_COMPONENT_TYPE), "event::mouse", &m, TRUE);
			
			if (m.type == NGTK_MET_DOWN)
				last_but_press_here[but_press_index] = hwnd;
			else if (m.type == NGTK_MET_UP)
			{
				if (last_but_press_here[but_press_index] == hwnd)
				{
					m.type = NGTK_MET_CLICK;
					ngtk_interface_send_signal (ngtk_object_cast (wc, NGTK_COMPONENT_TYPE), "event::mouse", &m, TRUE);
				}
			}
		}
		return 1;
		
	case WM_DESTROY: /* The window was destroyed */
		for (i = 0; i < different_buttons; i++)
			if (last_but_press_here[i] == hwnd)
				last_but_press_here[i] = NULL;
		return 0;

	default:
		return 0;
	}
}

static int CALLBACK ngtk_win_keyboard_handle (NGtkComponent* wc, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	NGtkKeyboardEvent evnt;

	if (msg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_LEFT:
			evnt.key = NGTK_KKEY_ARROW_LEFT; break;
		case VK_DOWN:
			evnt.key = NGTK_KKEY_ARROW_DOWN; break;
		case VK_RIGHT:
			evnt.key = NGTK_KKEY_ARROW_RIGHT; break;
		case VK_UP:
			evnt.key = NGTK_KKEY_ARROW_UP; break;
		default:
			return 0;
		}
	}
	else if (msg == WM_CHAR)
	{
		if (wParam == '\b')
			evnt.key = NGTK_KKEY_BACKSPACE;
		else if  (wParam == '\r')
			evnt.key = NGTK_KKEY_ENTER;
		else if  (wParam == ' ')
			evnt.key = NGTK_KKEY_SPACE;
		else if (wParam >= NGTK_KKEY_MIN_CHAR && wParam <= NGTK_KKEY_MAX_CHAR)
			evnt.key = wParam;
		else
			evnt.key = NGTK_KKEY_OTHER;
	}
	else
		return 0;

	ngtk_interface_send_signal (ngtk_object_cast (wc, NGTK_COMPONENT_TYPE), "event::keyboard", &evnt, TRUE);

	return 1;
}

static int CALLBACK ngtk_win_container_handle (NGtkContainer* wc, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	NGtkBackend *backend = ngtk_base_get_backend (wc);
	NGtkLayout  *layout;
	
	if (! ngtk_object_is_a (wc, NGTK_CONTAINER_TYPE))
		return 0;
	
	switch (msg)
	{
	case WM_CLOSE: /* Signals the X button / alt-F4 / etc. was pressed */
		DestroyWindow (hwnd);
		return 1;

	case WM_DESTROY: /* The window was destroyed */
	{
		if (wc == ngtk_backend_get_root_window (backend))
			ngtk_backend_quit_main_loop (backend);
		return 1;
	}

	case WM_SIZING:
		if ((layout = NGTK_BASIC_CONTAINER_O2D (wc)->layout) != NULL)
		{
			/* The lParam is now a pointer to the new screen size of the
			 * window. That is NOT the size of the area inside the window that we
			 * can actually use! To get that, use GetClientRect. But, GetClientRect
			 * will return the size before the new resizing...
			 * So, we will compute the difference between a Client Rect and the
			 * Screen Rect, and we will add that to the new Screen Rect.
			 */
			RECT rectC, rectW, *rectN, rect;

			GetClientRect (hwnd, &rectC); /* Coordinates relative to client area, i.e. from (0,0) */
			GetWindowRect (hwnd, &rectW); /* Absolute Screen Coordinates, i.e. where the window really is */
			rectN = (RECT*) lParam;

			rect.left   = rectN->left   + (rectC.left   - rectW.left);
			rect.right  = rectN->right  + (rectC.right  - rectW.right);
			rect.top    = rectN->top    + (rectC.top    - rectW.top);
			rect.bottom = rectN->bottom + (rectC.bottom - rectW.bottom);

			ngtk_layout_pack (layout, wc, rect.right - rect.left, rect.bottom - rect.top);
			return 1;
		}

	default:
		return 0;
	}
}

/**
 * A procedure to handle window messages, as defined in
 * http://msdn.microsoft.com/en-us/library/ms633573.aspx
 */
LRESULT CALLBACK ngtk_win_general_WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	NGtkComponent *ww = GetFromHwnd (hwnd);
	NGtkBackend   *backend;
	WNDPROC        base_proc = ngtk_win_component_get_base_wnd_proc (ww);

	backend = ngtk_base_get_backend (ww);

	ngtk_win_container_handle (ww, hwnd, msg, wParam, lParam);
	ngtk_win_mouse_handle (ww, hwnd, msg, wParam, lParam);
	ngtk_win_keyboard_handle (ww, hwnd, msg, wParam, lParam);
	
	switch (msg)
	{
	case WM_DESTROY: /* The window was destroyed */

		/* Remove any association of from the component to the HWND,
		 * and restore the original WndProc for finishing the destruction */
		ngtk_win_component_call_on_wnd_destroy (ww);

		/* Properties must be removed before the window is destroyed */
		RemoveFromHwnd (hwnd);

		break;

	default:
		break;
	}

	return CallWindowProc (base_proc, hwnd, msg, wParam, lParam);
}

static void register_root_window_class ()
{
	WNDCLASSEX wc;

	/* Initialize the size of the struct */
	wc.cbSize = sizeof (WNDCLASSEX);

	/* The style of the window. A bit-mask of several flags that
	* indicate stuff such as whether the window has a shadow, whether
	* it has a close button, etc. For nothing special, just set as 0.
	* More details at http://msdn.microsoft.com/en-us/library/ff729176.aspx
	*/
	wc.style = 0;

	/* A function that processes messages that are sent to the window,
	 * such as close messages. We register the default function, and we'll
	 * override it later */
	wc.lpfnWndProc = DefWindowProc;

	/* Amount of extra bytes to allocate for this class in memory. Can be used
	* in the case where someone wants to maintain some data common to all
	* the windows of that class. We don't want to do that, so set to 0 */
	wc.cbClsExtra = 0;

	/* Amount of extra bytes to allocate for each window instance in memory.
	* We will use that space to point to the WindowsWindow containing this HWND */
	wc.cbWndExtra = sizeof (NGtk_Win_ExtraDataType);

	/* hInstace is a parameter representing the instance of the current windows
	* program/dll/module. */
	wc.hInstance = NGtk_Win_hInstance;

	/* A pointer to a large icon for the window. I'll pass NULL for the default icon */
	wc.hIcon = NULL;
	
	/* A pointer to a small icon for the window. I'll pass NULL for the default icon */
	wc.hIconSm = NULL;

	/* The cursor used by the windows of this class. We choose the regular one */
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);

	/* The background color of the window. Can be a brush object, or a color
	* value from a list of standard colors (this is what we choose) */
	wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	/* If we want to have a menu, here we should give the name of it's resource */
	wc.lpszMenuName = NULL;

	/* The name for this class of windows */
	wc.lpszClassName = NGtk_Win_WinClassNameA;

	/* Attempt registering the class */
	if (!RegisterClassEx (&wc))
	{
		fprintf (stderr, "Couldn't register the window class %s", NGtk_Win_WinClassNameA);
		exit (EXIT_FAILURE);
	}
	else
		window_class_registered = TRUE;
}


void ngtk_win_init (NGtkBackend *backend)
{
	if (window_class_registered)
		return;
	else
		register_root_window_class ();
}

void ngtk_win_start_main_loop (NGtkBackend *backend)
{
	MSG Msg;

	/* The Message Loop. Receive messages and continue as long as there is no
	 * error (the return code is non negative) and as long as the message isn't
	 * a QUIT message (return code 0).
	 *
	 * We don't want to limit to a specific window, so pass NULL as the HWND
	 *
	 * Finally, for now we don't limit to just specific events, so both min and
	 * max of the message range are 0
	 */
	while (GetMessage (&Msg, NULL, 0, 0) > 0)
	{
		/* Do some processing of the message. TODO: what exactly? */
		TranslateMessage (&Msg);
		/* Send the message forward. TODO: how does this work with TranslateMessage? */
		DispatchMessage (&Msg);
	}
}

void ngtk_win_quit_main_loop (NGtkBackend *backend)
{
	PostQuitMessage (0);
}

void ngtk_win_quit (NGtkBackend *backend)
{
	NGtkList *all_comps = ngtk_backend_get_all_components (backend);

	while (! ngtk_list_is_empty (all_comps))
		ngtk_object_free ((NGtkObject*) all_comps->first->data);

	if (ngtk_backend_get_root_window (backend) != NULL)
		ngtk_free (ngtk_backend_get_root_window (backend));
}

LPCSTR ngtk_win_get_root_window_class_name (NGtkBackend *backend)
{
	return NGtk_Win_WinClassNameA;
}