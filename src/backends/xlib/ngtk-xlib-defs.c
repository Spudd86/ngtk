/*
 * ngtk-xlib-defs.c - Part of the NGtk library
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

#include <X11/Xlib.h>
#include <X11/Xutil.h> /* For XLookupString */

#include <stdlib.h>
#include <stdio.h>

#include "ngtk-xlib.h"

static float xlib_color_vals[NGTK_XLIB_COLOR_MAX][3] = {
	{1, 1, 1},          /* NGTK_XLIB_WHITE */
	{0, 0, 0},          /* NGTK_XLIB_BLACK */
	{0.6f, 0.5f, 0.4f}  /* NGTK_XLIB_GRAY  */
	};

void ngtk_xlib_init (NGtkXlibBackend *self)
{
	NGtkXlibBackendD *xbd = NGTK_XLIB_BACKEND_O2D (self);

	const char* display_name = NULL;
	int i = 0;

	display_name = getenv ("DISPLAY");
	if (display_name == NULL) display_name = ":0";

	/* Open a connection to the X server */
	xbd->display = XOpenDisplay (display_name);

	if (xbd->display == NULL)
		ngtk_error (self, "Can not connect to the X server at %s\n", display_name);

	/* Find the default screen on which we should operate */
	xbd->screen = DefaultScreen (xbd->display);

	/* Each screen has a root window - a window that covers the entire
	 * screen. We need it in order to create the children windows */
	xbd->root_window = RootWindow (xbd->display, xbd->screen);

	/* Each screen has a colormap - an object that given an RGB color
	 * will return an identifier of the closest displayable color to
	 * the given color */
	xbd->colormap = DefaultColormap (xbd->display, xbd->screen);

	for (i = 0; i < NGTK_XLIB_COLOR_MAX; i++)
	{
		XColor *col = &xbd->colors[i];
		col->red = (unsigned long) (xlib_color_vals[i][0] * 65535);
		col->green = (unsigned long) (xlib_color_vals[i][1] * 65535);
		col->blue = (unsigned long) (xlib_color_vals[i][2] * 65535);
		/* TODO: the following line is used in some guides and in some
		 * not. Check way and maybe remove */
		col->flags = DoRed | DoGreen | DoBlue;

		ngtk_assert (XAllocColor (xbd->display, xbd->colormap, col));
	}

	/* Initialize a connection property with the window manager,
	 * associated with a window close event */
	xbd->window_close_atom = XInternAtom (xbd->display, "WM_DELETE_WINDOW", FALSE);
}

/* You want to read the man page for XButtonEvent in order to understand
 * the following function. */
static void handle_mouse_button_event (NGtkXlibBackend *self, XButtonEvent evnt)
{
	/* In order to determine where a mouse press and release together
	 * from a click, we must check that the press and release of the
	 * button both happen on the same component */
	static Window last_but_press_here[4] = { 0, BadWindow, BadWindow, BadWindow };

	/* The Xlib Window where the event occured */
	Window wnd = evnt.window;

	/* A mask of pressed mouse buttons and keyboard modifiers just
	 * before the event occured */
	/* unsigned int state_before = evnt.state; */

	/* The mouse button that triggered the event */
	unsigned int event_button = evnt.button;

	/* The evnt.type is either ButtonPress or ButtonRelease */
	int is_release = (evnt.type == ButtonRelease);

	/* This is the NGtkMouseEvent that we will construct from this Xlib
	 * event, in order to send it to the component */
	NGtkMouseEvent nevent;

	/* An index between 1-3 of the mouse button that is clicked. */
	int mouse_but_index = 0;

	/* If this is a mouse button release event that also completes a
	 * click, then we should fire a click event after firing a release
	 * event. This variable is an indicator for that */
	int also_fire_click = FALSE;

	NGtkComponent *widget = ngtk_xlib_backend_get_for_window (self, wnd);

	/* An event should be ignored in any of the following cases:
	 *
	 * 1. The Widget matching the Xlib Window where the event happened
	 *    is not an event generator.
	 * 2. The Widget matching the Xlib Window where the event happened
	 *    is a component that has it's "enabled" state as FALSE.
	 * 3. No NGtk widget matches this Xlib window (should not happen!)
	 *
	 * However, since mouse events do require some handling which isn't
	 * specific to one widget (i.e. it has some global effects), then we
	 * will finish handling the event properly (instead of just
	 * returning from the function) and we'll just skip sending the
	 * event.
	 */
	int ignore_event = FALSE;

	switch (event_button)
	{
	case Button1:
		mouse_but_index = 1;
		nevent.button = NGTK_MBUT_L;
		break;
	case Button2:
		mouse_but_index = 2;
		nevent.button = NGTK_MBUT_R;
		break;
	case Button3:
		mouse_but_index = 3;
		nevent.button = NGTK_MBUT_M;
		break;
	default:
		/* Unknown mouse button. Therefore, don't handle the event */
		ignore_event = FALSE;
		break;
	}

	if (! is_release)
	{
		nevent.type = NGTK_MET_DOWN;
		last_but_press_here[mouse_but_index] = evnt.window;

		/* TODO: in the future, focus on this widget */
	}
	else /* if (type == ButtonRelease) */
	{
		/* If we have a mouse release, and it's on the same widget where
		 * the last press of this button occured, then we have a click
		 */
		if (last_but_press_here[mouse_but_index] == evnt.window)
			also_fire_click = TRUE;

		nevent.type = NGTK_MET_UP;
		last_but_press_here[mouse_but_index] = BadWindow;
	}

	if (! ignore_event)
	{
		NGtkComponentI *compi = ngtk_object_cast (widget, NGTK_COMPONENT_TYPE);
		ngtk_interface_send_signal (compi, "event::mouse", &nevent, TRUE);
		if (also_fire_click)
		{
			nevent.type = NGTK_MET_CLICK;
			ngtk_interface_send_signal (compi, "event::mouse", &nevent, TRUE);
		}
	}
}

void ngtk_xlib_start_main_loop (NGtkXlibBackend *self)
{
	NGtkXlibBackendD *xbd = NGTK_XLIB_BACKEND_O2D (self);
	NGtkBasicBackendD *bbd = NGTK_BASIC_BACKEND_O2D (self);

	NGtkContainer    *ngtk_xlib_root_window = bbd->root_window;
	Display          *xlib_display = xbd->display;

	while (! ngtk_xlib_backend_should_quit (self))
	{
		XEvent event;

		/* Retrieve the next event from the event Queue, or block untill
		 * such an event is received */
		XNextEvent (xbd->display, &event);

		/* See NGTK_XLIB_EVENT_MASK in ngtk-xlib-defs.h */
		switch (event.type)
		{
		/* Friendly reminder: We need curly braces to define variables
		 * inside case statements */

		case Expose: /* This is the case were we need to redraw */
		{
			/* The window that was exposed */
			Window wnd = event.xexpose.window;
			NGtkComponent *comp = ngtk_xlib_backend_get_for_window (self, wnd);

			/* If we have several pending expose events, to avoid
			 * flickering we will handle just the last one. */
			if (event.xexpose.count > 0) break;

			if (comp != NULL && ngtk_object_is_a (comp, NGTK_COMPONENT_TYPE))
				ngtk_component_redraw (comp);

			break;
		}

		case ButtonPress:
		case ButtonRelease:
		{
			handle_mouse_button_event (self, event.xbutton);
			break;
		}

		/* Support detection of mouse motion events. This is mostly
		 * experimental and was not in the requirements */
		case MotionNotify:
		{
			XMotionEvent mevent = event.xmotion;
			Window wnd = mevent.window;
			NGtkComponent *comp = ngtk_xlib_backend_get_for_window (self, wnd);
			NGtkMouseEvent nevent;

			if (mevent.state & Button1Mask)
				nevent.button = NGTK_MBUT_L;
			else if (mevent.state & Button2Mask)
				nevent.button = NGTK_MBUT_R;
			if (mevent.state & Button3Mask)
				nevent.button = NGTK_MBUT_M;
			else
				nevent.button = NGTK_MBUT_NONE;

			nevent.type = NGTK_MET_MOVE;

			ngtk_assert (comp != NULL);
			ngtk_assert (ngtk_object_is_a (comp, NGTK_COMPONENT_TYPE));
			ngtk_interface_send_signal (ngtk_object_cast (comp, NGTK_COMPONENT_TYPE), "event::mouse", &nevent, TRUE);

			break;
		}

		case KeyPress:
		{
			/* Due to a problem with Xlib, the window inside the event
			 * structure isn't what we mean to have as the focus holder.
			 * I had lots of trouble convincing Xlib to set the focus
			 * correctly, so I'm managing the focus myself inside the
			 * backend object, and whenever a keyboard key is typed,
			 * I send the event to my own focus holder.
			 * See http://stackoverflow.com/questions/7617630/xsetinputfocus-fails
			 */
			NGtkComponent *comp = ngtk_backend_get_focus_holder (self);
			KeySym keysym;
			int has_keysym;
			char key_ascii;
			int has_ascii;

			NGtkKeyboardEvent kevent;
			kevent.key = NGTK_KKEY_OTHER;

			if (comp == NULL) break;
			/* XLookupString will translate a key event into an ascii
			 * symbol, after interpreting the Shift and other modifiers
			 * along with actual key pressed. It will return the number
			 * of characters in the generated string (0 if it's not
			 * translatable to an ascii string), and keysym will hold a
			 * symbolic value for that key (for things like the return
			 * key) */
			has_ascii = XLookupString (&event.xkey, &key_ascii, 1, &keysym, NULL);
			has_keysym = keysym != NoSymbol;

			if ((has_ascii && key_ascii == '\t') || (has_keysym && keysym == XK_Tab))
			{
				ngtk_backend_focus_to_next (self);
				break;
			}

			if (has_ascii)
			{
				kevent.key = key_ascii;
			}
			/* No "else", since we have some collisions */
			if (has_keysym)
			{
				switch (keysym)
				{
				case XK_BackSpace:
					kevent.key = NGTK_KKEY_BACKSPACE;
					break;
				case XK_Return:
					kevent.key = NGTK_KKEY_ENTER;
					break;
				case XK_space:
					kevent.key = NGTK_KKEY_SPACE;
					break;
				case XK_Left:
					kevent.key = NGTK_KKEY_ARROW_LEFT;
					break;
				case XK_Up:
					kevent.key = NGTK_KKEY_ARROW_UP;
					break;
				case XK_Right:
					kevent.key = NGTK_KKEY_ARROW_RIGHT;
					break;
				case XK_Down:
					kevent.key = NGTK_KKEY_ARROW_DOWN;
					break;
				}
			}

			ngtk_interface_send_signal (ngtk_object_cast (comp, NGTK_COMPONENT_TYPE), "event::keyboard", &kevent, TRUE);
			break;
		}

		/* This event is sent when something happened to the window
		 * structure. We will use it to catch resize events. However,
		 * since it will be generated by all the components (because
		 * it's activated by the StructureNotify mask that we enabled to
		 * catch resize events), we must make sure we are handling the
		 * resize of the right component.
		 * Based on the example on http://www.lemoda.net/c/xlib-resize/ */
		case ConfigureNotify:
		{
			/* The only component who has the bit on to signal it should
			 * accept resize requests is the root window */
			NGtkComponent *widget = ngtk_xlib_backend_get_for_window (self, event.xconfigure.window);
			const NGtkRectangle *rect = ngtk_xlib_component_get_rect (widget);

			if (ngtk_object_is_a (widget, NGTK_CONTAINER_TYPE) && (rect->w != event.xconfigure.width || rect->h != event.xconfigure.height))
				ngtk_container_pack (widget);
			break;
		}

		/* Sent when a window was actually destroyed */
		case DestroyNotify:
		{
			Window wnd = event.xdestroywindow.window;
			NGtkComponent *xb = ngtk_xlib_backend_get_for_window (self, wnd);

			ngtk_xlib_component_call_on_window_destroyed (xb);

			/* Quit if this was the root window */
			if (xb == ngtk_xlib_root_window)
			{
				ngtk_backend_quit_main_loop (self);
			}
			break;
		}

		/* A message from the window manager. Earlier we registered for
		 * a message when the user tries to close the window */
		case ClientMessage:
			if (event.xclient.data.l[0] == xbd->window_close_atom
				&& event.xclient.window == ngtk_xlib_component_get_window (ngtk_xlib_root_window))
			{
				ngtk_object_send_signal (ngtk_xlib_root_window, "event::close", NULL);
				XDestroyWindow (xlib_display, ngtk_xlib_component_get_window (ngtk_xlib_root_window));
			}
			else
			{
			}
			break;

		default:
			break;
		}
	}
}

void ngtk_xlib_quit (NGtkXlibBackend *self)
{
	NGtkXlibBackendD *xbd = NGTK_XLIB_BACKEND_O2D (self);
	NGtkBasicBackendD *bbd = NGTK_BASIC_BACKEND_O2D (self);

	int i;

	/* Assert initialization */
	ngtk_assert (bbd->initialized);

	/* Free the root window */
	if (bbd->root_window)
	{
		/* Freeing the root window will free it's children */
		ngtk_object_free (bbd->root_window);
		bbd->root_window = NULL;
	}

	/* Free the colors we allocated */
	for (i = 0; i < NGTK_XLIB_COLOR_MAX; i++)
	{
		/* To free a color saved in a given XColor struct, we free the
		 * "pixel" field which is actually the identifier relative to
		 * the given colormap. We then specify that we are freeing 1
		 * color, and 0 planes. We don't deal with color planes in NGtk
		 */
		XFreeColors (xbd->display, xbd->colormap, &xbd->colors[i].pixel, 1, 0);
	}
	/* Free the colormap */
	XFreeColormap (xbd->display, xbd->colormap);

	/* Close the connection to the X server */
	XCloseDisplay (xbd->display);
}
