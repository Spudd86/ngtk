/*
 * ngtk-xlib-defs.c
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
//	if (display_name == NULL) display_name = ":0";

	/* Open a connection to the X server */
	xbd->display = XOpenDisplay (display_name);

	if (xbd->display == NULL)
		ngtk_error (self, "Can not connect to the X server at %s\n", display_name);

	ngtk_debug (self, "Made a connection with the display %p", xbd->display);

	/* Find the default screen on which we should operate */
	xbd->screen = DefaultScreen (xbd->display);
	ngtk_debug (self, "The screen we'll use is %d", xbd->screen);

	/* Each screen has a root window - a window that covers the entire
	 * screen. We need it in order to create the children windows */
	xbd->root_window = RootWindow (xbd->display, xbd->screen);
	ngtk_debug (self, "The screen root window is %lu", xbd->root_window);

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

//		ngtk_debug (self, "Allocating color #%02x%02x%02x\n",col->red, col->green, col->blue);
		ngtk_assert (XAllocColor (xbd->display, xbd->colormap, col));
//		ngtk_debug (self, "Result is %lu\n", col->pixel);
	}

	/* Initialize a connection property with the window manager,
	 * associated with a window close event */
	xbd->window_close_atom = XInternAtom (xbd->display, "WM_DELETE_WINDOW", FALSE);
	ngtk_debug (self, "Finished initializing with display %p",ngtk_xlib_backend_get_X_display (self));
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

//		/* A clicked object should receive the keyboard focus, iff it's
//		 * an event-generator.
//		 * TODO: Fix focus handling in the Xlib backend. Specifically,
//		 * do we need to manually keep track of focus for widgets inside
//		 * a window? */
//		if (widget != NULL && ngtk_object_is_a (widget, NGTK_EVENT_GENERATOR_TYPE))
//			ngtk_event_generator_grab_keyboard_focus (widget);
	}
	else /* if (type == ButtonRelease) */
	{
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
	Atom              xlib_window_close_atom = xbd->window_close_atom;

	while (! ngtk_xlib_backend_should_quit (self))
	{
		XEvent event;
		XNextEvent (xbd->display, &event);

		ngtk_debug (self, "%d\n", event.type);
		/* See NGTK_XLIB_EVENT_MASK in ngtk-xlib-defs.h */
		switch (event.type)
		{
		/* Friendly reminder: We need curly braces to define variables
		 * inside case statements */

		case Expose: /* This is the case were we need to redraw */
		{
			ngtk_debug (self, "Expose Received");

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
			ngtk_debug (self, "ButtonPress or ButtonRelease Received");
		{
			handle_mouse_button_event (self, event.xbutton);
			break;
		}

		case MotionNotify:
			ngtk_debug (self, "MotionNotify Received");
		{

			 /* TODO: handle the event here */

			break;
		}

		case KeyPress:
			ngtk_debug (self, "KeyPress Received");
		{
//			Window wnd = event.xbutton.window;
			KeySym keysym;
			int has_keysym;
			char key_ascii;
			int has_ascii;

			/* XLookupString will translate a key event into an ascii
			 * symbol, after interpreting the Shift and other modifiers
			 * along with actual key pressed. It will return the number
			 * of characters in the generated string (0 if it's not
			 * translatable to an ascii string), and keysym will hold a
			 * symbolic value for that key (for things like the return
			 * key) */
			has_ascii = XLookupString (&event.xkey, &key_ascii, 1, &keysym, NULL);
			has_keysym = keysym != NoSymbol;

			if (has_ascii && key_ascii == '\t')
				ngtk_backend_focus_to_next (self);
			else if (has_ascii)
			{
			}
			else if (has_keysym)
			{
			}
			else
			{
			}

			 /* TODO: handle the event here */

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
			ngtk_debug (self, "ConfigureNotify Received");
		{
			/* The only component who has the bit on to signal it should
			 * accept resize requests is the root window */
			NGtkComponent *widget = ngtk_xlib_backend_get_for_window (self, event.xconfigure.window);
			const NGtkRectangle *rect = ngtk_xlib_component_get_rect (widget);

			if (ngtk_object_is_a (widget, NGTK_CONTAINER_TYPE) && (rect->w != event.xconfigure.width || rect->h != event.xconfigure.height))
				ngtk_container_pack (widget);
			break;
		}

		case DestroyNotify:
			ngtk_debug (self, "DestroyNotify Received");
		{
			Window wnd = event.xdestroywindow.window;
			NGtkComponent *xb = ngtk_xlib_backend_get_for_window (self, wnd);

			ngtk_xlib_component_call_on_window_destroyed (xb);

			if (xb == ngtk_xlib_root_window)
			{
				ngtk_backend_quit_main_loop (self);
				ngtk_debug (self, "Quit main loop!\n");
			}
			break;
		}

		case ClientMessage:
			ngtk_debug (self, "ClientMessage Received");
			if (event.xclient.data.l[0] == xbd->window_close_atom
				&& event.xclient.window == ngtk_xlib_component_get_window (ngtk_xlib_root_window))
			{
				ngtk_debug (self, "Received destroy message from WM!\n");
				ngtk_object_send_signal (ngtk_xlib_root_window, "event::close", NULL);
				XDestroyWindow (xlib_display, ngtk_xlib_component_get_window (ngtk_xlib_root_window));
			}
			else
			{
				ngtk_debug (self, "Client data is %ld ", event.xclient.data.l[0]);
				ngtk_debug (self, "while our atom is %ld\n", (unsigned long) xlib_window_close_atom);
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

#if FALSE
NGtkContainer* ngtk_xlib_create_root_window (const char* title)
{
	if (ngtk_xlib_root_window == NULL)
		ngtk_xlib_root_window = ngtk_xlib_create_window_imp (title, FALSE);

	XSetWMProtocols (xlib_display, ngtk_xlib_base_get_window (ngtk_xlib_root_window), &xlib_window_close_atom, 1);
	return ngtk_xlib_root_window;
}

NGtkComponent* ngtk_xlib_create_button (NGtkContainer* parent, const char* text)
{
	return ngtk_xlib_create_button_imp (text, FALSE, parent);
}

NGtkComponent* ngtk_xlib_create_label (NGtkContainer* parent, const char* text)
{
	return ngtk_xlib_create_label_imp (text, FALSE, parent);
}

NGtkComponent* ngtk_xlib_create_text_entry (NGtkContainer* parent, const char* text)
{
	return NULL;
}
#endif
