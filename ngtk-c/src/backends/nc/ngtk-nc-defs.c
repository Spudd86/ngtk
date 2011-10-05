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
#include "ngtk-nc.h"

void ngtk_nc_backend_init (NGtkNcBackend *self)
{
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

	/* Mark the finish of the initialization */
	ngtk_basic_backend_call_after_init (self);
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

	ngtk_interface_send_signal (ngtk_object_cast (comp, NGTK_COMPONENT_TYPE), "event::mouse", &evnt, TRUE);
}

static void component_keyed (NGtkComponent* comp, int ch)
{
//	NGtkKeyboardEvent event;
}

void ngtk_nc_backend_start_main_loop (NGtkNcBackend *self)
{
	while (! ngtk_basic_backend_should_quit (self))
	{
		int ch = getch ();

		if (ch == KEY_MOUSE)
		{
			MEVENT         mouse_event;
			const NGtkRectangle *comp_rect;
			NGtkListNode  *iter;
			NGtkContainer *inner_most_comp = ngtk_backend_get_root_window (self);

			if (getmouse (&mouse_event) == OK)
			{
				do {
					ngtk_list_foreach (iter, ngtk_container_get_children (inner_most_comp))
					{
						NGtkComponent *comp = (NGtkComponent*) iter->data;
						comp_rect = ngtk_nc_component_get_abs_rect (comp);
						if (ngtk_rect_contains (comp_rect, mouse_event.x, mouse_event.y))
						{
							inner_most_comp = comp;
							break;
						}
					}
				} while (ngtk_object_is_a (inner_most_comp, NGTK_CONTAINER_TYPE));

				component_moused (inner_most_comp, mouse_event.bstate);
			}
		}
		else if (ch == KEY_RESIZE)
		{
			ngtk_container_pack (ngtk_backend_get_root_window (self));
		}
		else
		{
			component_keyed (ngtk_backend_get_focus_holder (self), ch);
		}
	}
}

void ngtk_nc_backend_quit (NGtkNcBackend *self)
{
	NGtkContainer *root_window = ngtk_basic_backend_get_root_window (self);

	/* Free the root window */
	if (root_window)
	{
		ngtk_object_free (root_window);
	}

	/* Leave curses mode */
	endwin ();
}
