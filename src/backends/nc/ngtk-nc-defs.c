/*
 * ngtk-nc-defs.c - Part of the NGtk library
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
	NGtkKeyboardEvent event;

	switch (ch)
	{
	case KEY_ENTER:
	case '\n':
		event.key = NGTK_KKEY_ENTER;
		break;
	case KEY_BACKSPACE:
		event.key = NGTK_KKEY_BACKSPACE;
		break;
	case KEY_UP:
		event.key = NGTK_KKEY_ARROW_UP;
		break;
	case KEY_DOWN:
		event.key = NGTK_KKEY_ARROW_DOWN;
		break;
	case KEY_LEFT:
		event.key = NGTK_KKEY_ARROW_LEFT;
		break;
	case KEY_RIGHT:
		event.key = NGTK_KKEY_ARROW_RIGHT;
		break;
	case ' ':
		event.key = NGTK_KKEY_SPACE;
		break;
	default:
		if (NGTK_KKEY_MIN_CHAR <= ch && ch <= NGTK_KKEY_MAX_CHAR)
			event.key = ch;
		else
			event.key = NGTK_KKEY_OTHER;
	}

	ngtk_interface_send_signal (ngtk_object_cast (comp, NGTK_COMPONENT_TYPE), "event::keyboard", &event, TRUE);
}

void ngtk_nc_backend_start_main_loop (NGtkNcBackend *self)
{
	while (! ngtk_basic_backend_should_quit (self))
	{
//		ngtk_component_redraw (ngtk_backend_get_root_window (self));

		int ch = getch ();

		if (ch == KEY_MOUSE)
		{
			MEVENT         mouse_event;
			const NGtkRectangle *comp_rect;
			NGtkListNode  *iter;
			NGtkComponent *inner_most_comp = ngtk_backend_get_root_window (self);
			NGtkComponent *old_inner_most_comp;

			if (getmouse (&mouse_event) == OK)
			{
				do {
					old_inner_most_comp = inner_most_comp;
					ngtk_list_foreach (iter, ngtk_container_get_children (inner_most_comp))
					{
						NGtkComponent *comp = (NGtkComponent*) iter->data;
						comp_rect = ngtk_nc_component_get_abs_rect (comp);
						if (ngtk_component_get_visible (comp) &&
							ngtk_rect_contains (comp_rect, mouse_event.x, mouse_event.y))
						{
							inner_most_comp = comp;
							break;
						}
					}
				} while (ngtk_object_is_a (inner_most_comp, NGTK_CONTAINER_TYPE)
						&& inner_most_comp != old_inner_most_comp);

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
