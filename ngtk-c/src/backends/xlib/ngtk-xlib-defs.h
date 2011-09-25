#ifndef __NGtk_xlib_defs__
#define __NGtk_xlib_defs__

#include <X11/Xlib.h>
#include "../../widgets/ngtk-widgets.h"

void            ngtk_xlib_init                ();
void            ngtk_xlib_start_main_loop     ();
void            ngtk_xlib_quit_main_loop      ();
void            ngtk_xlib_quit                ();

NGtkContainer*  ngtk_xlib_create_root_window  (const char* title);
NGtkComponent*  ngtk_xlib_create_button       (NGtkContainer* parent, const char* text);
NGtkComponent*  ngtk_xlib_create_label        (NGtkContainer* parent, const char* text);
NGtkComponent*  ngtk_xlib_create_text_entry   (NGtkContainer* parent, const char* text);

#define NGTK_XLIB_EVENT_MASK (                                         \
	/* A part of a component became visible after it was hidden, so we \
	 * need to redraw it. This will generate an event of type Expose */\
	ExposureMask |                                                     \
	/* Any of the mouse buttons was pressed down. This will generate   \
	 * an event of type ButtonPress */                                 \
	ButtonPressMask |                                                  \
	/* Any of the mouse buttons was released. This will generate an    \
	 * event of type ButtonRelease */                                  \
	ButtonReleaseMask |                                                \
	/* Any of the keyboard keys was pressed down. This will generate   \
	 * an event of type KeyPress */                                    \
	KeyPressMask |                                                     \
	/* The mouse was moved while none of it's buttons was pressed.     \
	 * This will generate an event of type MotionNotify */             \
	PointerMotionMask |                                                \
	/* The mouse was moved while one or more of it's buttons was       \
	 * pressed. This will generate an event of type MotionNotify */    \
	ButtonMotionMask |                                                 \
	/* The window structure was modified. We will use this to be       \
	 * notified when the window was closed. This will generate an      \
	 * event of several types, we will catch just DestroyNotify */     \
	StructureNotifyMask                                                \
	)

/* Colors used by this backend */
typedef enum {
	NGTK_XLIB_WHITE = 0,
	NGTK_XLIB_BLACK = 1,
	NGTK_XLIB_GRAY  = 2,

	NGTK_XLIB_COLOR_MAX = 3
} NGtkXlibColorName;


/* Utility functions of this backend */
void                ngtk_xlib_set_focus_holder (NGtkEventGenerator* eg);
NGtkEventGenerator* ngtk_xlib_get_focus_holder ();

Display*            ngtk_xlib_get_display ();
Window              ngtk_xlib_get_root_window ();
unsigned long       ngtk_xlib_get_color (NGtkXlibColorName cn);
#endif
