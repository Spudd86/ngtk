/*
 * ngtk-nc-defs.c
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

#include <ncurses.h>
#include "ngtk-nc-defs.h"
#include "ngtk-nc-base.h"

#include "ngtk-nc-window.h"

static int                 ngtk_nc_should_quit  = FALSE;
static NGtkComponentList*  ngtk_nc_components   = NULL;
static NGtkContainer*      ngtk_nc_root_window  = NULL;
static int                 ngtk_nc_initialized  = FALSE;
static NGtkEventGenerator* ngtk_nc_focus_holder = NULL;

void ngtk_nc_init ()
{
	/* Prevent double initialization */
	ngtk_assert (! ngtk_nc_initialized);

	/* Start CURSES mode */
	initscr ();

	/* Initialize the use of color pairs */
	start_color ();

	/* Disable line bufferring, and interpretation of other characters
	 * as signals */
	cbreak ();

	/* Do not show typed characters */
	noecho ();

	/* In order to receive some of the mouse and keyboard events, we
	 * must enable them. We will be accepting all the events via the
	 * standard screen, and we'll pass them on to relevant subwindows */
	keypad (stdscr, TRUE);

	/* Finaly, we want every known kind of mouse event. The main loop
	 * will filter out those which are not yet supported */
	mousemask (ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

	/* A list of all the components that were created during runtime.
	 * This will allow us to do easy garbage collection later */
	ngtk_nc_components = ngtk_list_new ();

	/* Finally, marked as initialized */
	ngtk_nc_initialized = TRUE;
}

static void component_moused (NGtkComponent* comp, mmask_t bstate)
{
#define ngtk_set_mouse_event(evnt,typ,but) \
NGTK_LONG_MACRO_BEGIN                 \
	evnt.type = typ;                  \
	evnt.button = but;                \
NGTK_LONG_MACRO_END

	NGtkMouseEvent evnt;
	if (! ngtk_component_get_enabled (comp)) return;

	if (bstate & BUTTON1_PRESSED)
		ngtk_set_mouse_event (evnt, NGTK_MET_DOWN, NGTK_MBUT_L);
	else if  (bstate & BUTTON1_RELEASED)
		ngtk_set_mouse_event (evnt, NGTK_MET_UP, NGTK_MBUT_L);
	else if  (bstate & BUTTON1_CLICKED)
		ngtk_set_mouse_event (evnt, NGTK_MET_CLICK, NGTK_MBUT_L);

	else if  (bstate & BUTTON2_PRESSED)
		ngtk_set_mouse_event (evnt, NGTK_MET_DOWN, NGTK_MBUT_R);
	else if  (bstate & BUTTON2_PRESSED)
		ngtk_set_mouse_event (evnt, NGTK_MET_UP, NGTK_MBUT_R);
	else if  (bstate & BUTTON1_CLICKED)
		ngtk_set_mouse_event (evnt, NGTK_MET_CLICK, NGTK_MBUT_R);

	else if  (bstate & BUTTON3_PRESSED)
		ngtk_set_mouse_event (evnt, NGTK_MET_DOWN, NGTK_MBUT_M);
	else if  (bstate & BUTTON3_PRESSED)
		ngtk_set_mouse_event (evnt, NGTK_MET_UP, NGTK_MBUT_M);
	else if  (bstate & BUTTON1_CLICKED)
		ngtk_set_mouse_event (evnt, NGTK_MET_CLICK, NGTK_MBUT_M);

	else if (bstate & REPORT_MOUSE_POSITION)
		ngtk_set_mouse_event (evnt, NGTK_MET_MOVE, NGTK_MBUT_NONE);

	else
		/* It's a non supported button, don't report this */
		return;

	ngtk_event_generator_fire_mouse_event (comp, &evnt);
}

static void component_keyed (NGtkComponent* comp, int ch)
{
//	NGtkKeyboardEvent event;
}

void ngtk_nc_start_main_loop ()
{
	/* Assert initialization */
	ngtk_assert (ngtk_nc_initialized);

	while (! ngtk_nc_should_quit)
	{
		int ch = getch ();

		if (ch == KEY_MOUSE)
		{
			MEVENT         mouse_event;
			const NGtkRectangle *comp_rect;
			NGtkListNode  *iter;

			if (getmouse (&mouse_event) == OK)
			ngtk_list_foreach (iter, ngtk_container_get_children (ngtk_nc_root_window))
			{
				NGtkComponent *comp = (NGtkComponent*) iter->data;
				comp_rect = ngtk_nc_base_get_abs_rect (comp);
				if (ngtk_rect_contains (comp_rect, mouse_event.x, mouse_event.y))
					component_moused (comp, mouse_event.bstate);
			}
		}
		else if (ch == KEY_RESIZE)
		{
//			WINDOW *prev = ngtk_nc_base_get_window (ngtk_nc_root_window);

//			wclear (prev);
//			wrefresh (prev);

			ngtk_container_pack (ngtk_nc_root_window);
		}
		else
		{
			component_keyed (ngtk_nc_focus_holder, ch);
		}
	}
}

void ngtk_nc_quit_main_loop ()
{
	/* Assert initialization */
	ngtk_assert (ngtk_nc_initialized);

	ngtk_nc_should_quit = TRUE;
}

void ngtk_nc_quit ()
{
	NGtkListNode *iter;

	/* Assert initialization */
	ngtk_assert (ngtk_nc_initialized);

	/* Release the allocated components */
	if (ngtk_nc_components)
	{
		/* If there are any components that were still not freed, free them
		 * before we quit, to make sure we don't leak memory */
		ngtk_list_foreach (iter, ngtk_nc_components)
		{
			NGtkComponent *comp = (NGtkComponent*) iter->data;
			ngtk_object_free (comp);
		}

		/* Now free the component list */
		ngtk_list_free (ngtk_nc_components);

		ngtk_nc_components = NULL;
	}

	/* Free the root window */
	if (ngtk_nc_root_window)
	{
		ngtk_object_free (ngtk_nc_root_window);
		ngtk_nc_root_window = NULL;
	}

	/* Leave curses mode */
	endwin ();
}

NGtkContainer* ngtk_nc_create_root_window (const char* title)
{
	if (ngtk_nc_root_window == NULL)
		ngtk_nc_root_window = ngtk_nc_create_window_imp (title, FALSE);

	return ngtk_nc_root_window;
	/* if (! ngtk_nc_focus_holder) ngtk_nc_focus_holder = ... */
}

NGtkComponent* ngtk_nc_create_button (const char* text)
{
	/* if (! ngtk_nc_focus_holder) ngtk_nc_focus_holder = ... */
	return NULL;
}

NGtkComponent* ngtk_nc_create_label (const char* text)
{
	/* if (! ngtk_nc_focus_holder) ngtk_nc_focus_holder = ... */
	NGtkObject *lab = ngtk_nc_create_label_imp (text, FALSE);
	ngtk_list_append (ngtk_nc_components, lab);
	return lab;
}

NGtkComponent* ngtk_nc_create_text_entry (const char* text)
{
	return NULL;
}

void ngtk_nc_set_focus_holder (NGtkEventGenerator* eg)
{
	ngtk_nc_focus_holder = eg;
}

NGtkEventGenerator* ngtk_nc_get_focus_holder ()
{
	return ngtk_nc_focus_holder;
}
