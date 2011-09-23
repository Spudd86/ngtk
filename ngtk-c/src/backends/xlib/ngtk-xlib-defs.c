#include <X11/Xlib.h>
#include <stdlib.h>

#include "ngtk-xlib-defs.h"
#include "ngtk-xlib-base.h"

#include "ngtk-xlib-window.h"

static int                 ngtk_xlib_should_quit  = FALSE;
static NGtkContainer*      ngtk_xlib_root_window  = NULL;
static int                 ngtk_xlib_initialized  = FALSE;
static NGtkEventGenerator* ngtk_xlib_focus_holder = NULL;

static Display*            xlib_display           = NULL;
static int                 xlib_screen;
static Window              xlib_root_window;

/* Colors used by this backend */
enum {
	NGTK_XLIB_WHITE = 0,
	NGTK_XLIB_BLACK = 1,
	NGTK_XLIB_GRAY  = 2,

	NGTK_XLIB_COLOR_MAX = 3
};

static Colormap      xlib_colormap;
static unsigned char xlib_color_vals[NGTK_XLIB_COLOR_MAX][3] = { {255, 255, 255}, {0, 0, 0}, {167, 157, 120} };
static XColor        xlib_colors[NGTK_XLIB_COLOR_MAX];

void ngtk_xlib_init ()
{
	const char* display_name;
	int i;

	/* Prevent double initialization */
	ngtk_assert (! ngtk_xlib_initialized);

	display_name = getenv ("DISPLAY");
	if (display_name == NULL) display_name = ":0";
	
	/* Open a connection to the X server */
	ngtk_xlib_display = XOpenDisplay (display_name);

	if (ngtk_xlib_display == NULL)
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
		XColor *col = xlib_colors[i];
		col->red = xlib_color_vals[i][0];
		col->green = xlib_color_vals[i][1];
		col->blue = xlib_color_vals[i][2];
		/* TODO: the following line is used in some guides and in some
		 * not. Check way and maybe remove */
		col->flags = DoRed | DoGreen | DoBlue;
		
		ngtk_assert (XAllocColor (xlib_display, xlib_colormap, col));
	}
	
	/* Finally, marked as initialized */
	ngtk_xlib_initialized = TRUE;
}

static void component_moused (NGtkComponent* comp, mmask_t bstate)
{
}

static void component_keyed (NGtkComponent* comp, int ch)
{
}

void ngtk_xlib_start_main_loop ()
{
	/* Assert initialization */
	ngtk_assert (ngtk_xlib_initialized);

	while (! ngtk_xlib_should_quit)
	{
		XEvent event;
		XNextEvent (xlib_display, &event);

		/* See NGTK_XLIB_EVENT_MASK in ngtk-xlib-defs.h */
		switch (event.type)
		{
		/* Friendly reminder: We need curly braces to define variables
		 * inside case statements */
		 
		case Expose: /* This is the case were we need to redraw */
		{
			/* The window that was exposed */
			Window wnd = event.xexpose.window;
			/* If we have several pending expose events, to avoid
			 * flickering we will handle just the last one. */
			if (event.xexpose.count > 0) break;

			/* TODO: handle the event here */
			
			break;
		}

		case ButtonPress:
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			ngtk_xlib_quit_main_loop ();
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
			/* TODO: remove me!!!!!!!!!!!!!!!! */
		case ButtonRelease:
		case MotionNotify:
		{
			Window wnd = event.xbutton.window;
			unsigned long state = event.xbutton.state;
			/* Valid masks are:
			 * Button1Mask, Button1MotionMask
			 * Button2Mask, Button2MotionMask
			 * Button3Mask, Button3MotionMask
			 *
			 * distinguish the event type by checking event.type
			 */
			 
			 /* TODO: handle the event here */
			 
			break;
		}

		case KeyPress:
		{
			Window wnd = event.xbutton.window;
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
			has_ascii = XLookupString (event.xkey, &key_ascii, 1, &keysym, NULL);
			has_keysym = keysym != NoSymbol;
			
			 /* TODO: handle the event here */
			 
			break;
		}

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
		XFreeColors (xlib_display, &xlib_colors[i].pixel, 1, 0);
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

	return ngtk_xlib_root_window;
}

NGtkComponent* ngtk_xlib_create_button (const char* text)
{
	return NULL;
}

NGtkComponent* ngtk_xlib_create_label (const char* text)
{
	NGtkObject *lab = ngtk_xlib_create_label_imp (text, FALSE);
	return lab;
}

NGtkComponent* ngtk_xlib_create_text_entry (const char* text)
{
	return NULL;
}

void ngtk_xlib_set_focus_holder (NGtkEventGenerator* eg)
{
	ngtk_xlib_focus_holder = eg;
}

NGtkEventGenerator* ngtk_xlib_get_focus_holder ()
{
	return ngtk_xlib_focus_holder;
}
