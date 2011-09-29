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

#include "ngtk-xlib-defs.h"
#include "ngtk-xlib-base.h"

#include "ngtk-xlib-window.h"

static int                 ngtk_xlib_should_quit  = FALSE;
/* The root window that NGtk created. Not to be confused with the root
 * window of the given sreen (in XLib, see below). */
static NGtkContainer*      ngtk_xlib_root_window  = NULL;
static int                 ngtk_xlib_initialized  = FALSE;
static NGtkEventGenerator* ngtk_xlib_focus_holder = NULL;

/* The current connection to the X server */
static Display*            xlib_display           = NULL;
/* The screen on which we operate */
static int                 xlib_screen;
/* The root window of the xlib screen. This is not to be confused with
 * the root application window created by NGtk (see above). */
static Window              xlib_root_window;

/* A property/event that we communicate with the window manager. We will
 * use it to store the property of closing a window */
static Atom                xlib_window_close_atom;

static Colormap      xlib_colormap;
static float xlib_color_vals[NGTK_XLIB_COLOR_MAX][3] = {
	{1, 1, 1},          /* NGTK_XLIB_WHITE */
	{0, 0, 0},          /* NGTK_XLIB_BLACK */
	{0.6f, 0.5f, 0.4f}  /* NGTK_XLIB_GRAY  */
	};
static XColor        xlib_colors[NGTK_XLIB_COLOR_MAX];

void ngtk_xlib_init ()
{
	const char* display_name;
	int i;

	/* Prevent double initialization */
	ngtk_assert (! ngtk_xlib_initialized);

	display_name = getenv ("DISPLAY");
//	if (display_name == NULL) display_name = ":0";

	/* Open a connection to the X server */
	xlib_display = XOpenDisplay (display_name);

	if (xlib_display == NULL)
	{
		fprintf (stderr, "Can not connect to the X server at %s\n", display_name);
		exit (EXIT_FAILURE);
	}

	/* Find the default screen on which we should operate */
	xlib_screen = DefaultScreen (xlib_display);
	/* Each screen has a root window - a window that covers the entire
	 * screen. We need it in order to create the children windows */
	xlib_root_window = RootWindow (xlib_display, xlib_screen);
	/* Each screen has a colormap - an object that given an RGB color
	 * will return an identifier of the closest displayable color to
	 * the given color */
	xlib_colormap = DefaultColormap (xlib_display, xlib_screen);

	for (i = 0; i < NGTK_XLIB_COLOR_MAX; i++)
	{
		XColor *col = &xlib_colors[i];
		col->red = (unsigned long) (xlib_color_vals[i][0] * 65535);
		col->green = (unsigned long) (xlib_color_vals[i][1] * 65535);
		col->blue = (unsigned long) (xlib_color_vals[i][2] * 65535);
		/* TODO: the following line is used in some guides and in some
		 * not. Check way and maybe remove */
		col->flags = DoRed | DoGreen | DoBlue;

		fprintf (stderr, "Allocating color #%02x%02x%02x\n",col->red, col->green, col->blue);
		ngtk_assert (XAllocColor (xlib_display, xlib_colormap, col));
		fprintf (stderr, "Result is %lu\n", col->pixel);
	}

	/* Initialize a connection property with the window manager,
	 * associated with a window close event */
	xlib_window_close_atom = XInternAtom (xlib_display, "WM_DELETE_WINDOW", FALSE);

	/* Finally, marked as initialized */
	ngtk_xlib_initialized = TRUE;
}

/* You want to read the man page for XButtonEvent in order to understand
 * the following function. */
static void handle_mouse_button_event (XButtonEvent evnt)
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

	NGtkXlibBase *widget = ngtk_xlib_base_get_for_window (wnd);

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

		/* A clicked object should receive the keyboard focus, iff it's
		 * an event-generator.
		 * TODO: Fix focus handling in the Xlib backend. Specifically,
		 * do we need to manually keep track of focus for widgets inside
		 * a window? */
		if (widget != NULL && ngtk_object_is_a (widget, NGTK_EVENT_GENERATOR_TYPE))
			ngtk_event_generator_grab_keyboard_focus (widget);
	}
	else /* if (type == ButtonRelease) */
	{
		if (last_but_press_here[mouse_but_index] == evnt.window)
			also_fire_click = TRUE;

		nevent.type = NGTK_MET_UP;
		last_but_press_here[mouse_but_index] = BadWindow;
	}

	/* Now, if th ecomponent is an event generator, fire the mouse
	 * event(s). */
	if (! ignore_event && ngtk_object_is_a (widget, NGTK_EVENT_GENERATOR_TYPE))
	{
		ngtk_event_generator_fire_mouse_event (widget, &nevent);
		if (also_fire_click)
		{
			nevent.type = NGTK_MET_CLICK;
			ngtk_event_generator_fire_mouse_event (widget, &nevent);
		}
	}
}

#if FALSE
static void component_keyed (NGtkComponent* comp, XKeyEvent evnt)
{
}
#endif

void ngtk_xlib_start_main_loop ()
{
	/* Assert initialization */
	ngtk_assert (ngtk_xlib_initialized);

	printf ("Resize Request event is %d\n", ResizeRequest);
	while (! ngtk_xlib_should_quit)
	{
		XEvent event;
		XNextEvent (xlib_display, &event);

		printf ("%d\n", event.type);
		/* See NGTK_XLIB_EVENT_MASK in ngtk-xlib-defs.h */
		switch (event.type)
		{
		/* Friendly reminder: We need curly braces to define variables
		 * inside case statements */

		case Expose: /* This is the case were we need to redraw */
		{
			/* The window that was exposed */
			Window wnd = event.xexpose.window;
			NGtkXlibBase *base = ngtk_xlib_base_get_for_window (wnd);

			/* If we have several pending expose events, to avoid
			 * flickering we will handle just the last one. */
			if (event.xexpose.count > 0) break;

			if (base != NULL && ngtk_object_is_a (base, NGTK_COMPONENT_TYPE))
				ngtk_component_redraw (base);

			break;
		}

		case ButtonPress:
		case ButtonRelease:
		{
			handle_mouse_button_event (event.xbutton);
			break;
		}

		case MotionNotify:
		{

			 /* TODO: handle the event here */

			break;
		}

		case KeyPress:
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

			if (has_ascii)
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
		{
			/* The only component who has the bit on to signal it should
			 * accept resize requests is the root window */
			NGtkXlibBase *widget = ngtk_xlib_base_get_for_window (event.xconfigure.window);
			const NGtkRectangle *rect = ngtk_xlib_base_get_relative_rect (widget);

			if (ngtk_object_is_a (widget, NGTK_CONTAINER_TYPE) && (rect->w != event.xconfigure.width || rect->h != event.xconfigure.height))
				ngtk_container_pack (widget);
			break;
		}

		case DestroyNotify:
		{
			printf ("Received destroy notification!\n");
			Window wnd = event.xdestroywindow.window;
			NGtkXlibBase *xb = ngtk_xlib_base_call_on_window_destroyed (wnd);
			if (xb == ngtk_xlib_root_window)
			{
				ngtk_xlib_quit_main_loop ();
				printf ("Quit main loop!\n");
			}
			break;
		}

		case ClientMessage:
			if (event.xclient.data.l[0] == xlib_window_close_atom
				&& event.xclient.window == ngtk_xlib_base_get_window (ngtk_xlib_root_window))
			{
				printf ("Received destroy message from WM!\n");
				XDestroyWindow (xlib_display, ngtk_xlib_base_get_window (ngtk_xlib_root_window));
			}
			else
			{
				printf ("Client data is %ld ", event.xclient.data.l[0]);
				printf ("while our atom is %ld\n", (unsigned long) xlib_window_close_atom);
			}
			break;

		default:
			break;
		}
	}
}

void ngtk_xlib_quit_main_loop ()
{
	/* Assert initialization */
	ngtk_assert (ngtk_xlib_initialized);

	ngtk_xlib_should_quit = TRUE;
}

void ngtk_xlib_quit ()
{
	int i;

	/* Assert initialization */
	ngtk_assert (ngtk_xlib_initialized);

	/* Free the root window */
	if (ngtk_xlib_root_window)
	{
		ngtk_object_free (ngtk_xlib_root_window);
		ngtk_xlib_root_window = NULL;
	}

	/* Free the colors we allocated */
	for (i = 0; i < NGTK_XLIB_COLOR_MAX; i++)
	{
		/* To free a color saved in a given XColor struct, we free the
		 * "pixel" field which is actually the identifier relative to
		 * the given colormap. We then specify that we are freeing 1
		 * color, and 0 planes. We don't deal with color planes in NGtk
		 */
		XFreeColors (xlib_display, xlib_colormap, &xlib_colors[i].pixel, 1, 0);
	}
	/* Free the colormap */
	XFreeColormap (xlib_display, xlib_colormap);

	/* Close the connection to the X server */
	XCloseDisplay (xlib_display);
}

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

void ngtk_xlib_set_focus_holder (NGtkEventGenerator* eg)
{
	XSetInputFocus (xlib_display, ngtk_xlib_base_get_window (eg), RevertToParent, CurrentTime);
	ngtk_xlib_focus_holder = eg;
}

NGtkEventGenerator* ngtk_xlib_get_focus_holder ()
{
	return ngtk_xlib_focus_holder;
}

Display* ngtk_xlib_get_display ()
{
	return xlib_display;
}

int ngtk_xlib_get_screen ()
{
	return xlib_screen;
}

Window ngtk_xlib_get_root_window ()
{
	return xlib_root_window;
}

unsigned long ngtk_xlib_get_color (NGtkXlibColorName cn)
{
	ngtk_assert (0 <= cn && cn < NGTK_XLIB_COLOR_MAX);
	return xlib_colors[cn].pixel;
}
