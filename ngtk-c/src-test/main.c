/*
 * main.c
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

#include "../src/ngtk.h"

#include <stdio.h>
#include <ncurses.h>

void MyFunc(NGtkEventGenerator *comp, const NGtkMouseEvent *evnt, void* data)
{
	if (evnt->type == NGTK_MET_CLICK || evnt->type == NGTK_MET_DOWN)
		ngtk_component_set_visible (comp, ! ngtk_component_get_visible (comp));
}

void MyFunc2(NGtkEventGenerator *comp, const NGtkMouseEvent *evnt, void* data)
{
	ngtk_quit_main_loop ();
}

#ifdef NGTK_USE_NC
int main (int argc, char **argv)
{
	NGtkContainer *wnd;
	NGtkComponent *lab, *lab2;
	NGtkRectangle  rect;

	ngtk_init ();

	wnd = ngtk_create_root_window ("oh yeah!");
    lab = ngtk_create_label ("Quit here!");
    lab2 = ngtk_create_label ("Hide me!");

    ngtk_container_add_child (wnd, lab);
    rect.x = rect.y = 2;
    rect.w = 13;
    rect.h = 6;
    ngtk_container_place_child (wnd, lab, &rect);

    ngtk_container_add_child (wnd, lab2);
    rect.x += rect.w;
    ngtk_container_place_child (wnd, lab2, &rect);

    ngtk_container_pack (wnd);

	ngtk_component_set_visible (lab, TRUE);
	ngtk_component_set_enabled (lab, TRUE);

	ngtk_component_set_visible (lab2, TRUE);
	ngtk_component_set_enabled (lab2, TRUE);

	ngtk_component_set_visible (wnd, TRUE);

	ngtk_event_generator_add_mouse_listener (lab, MyFunc2, NULL, NULL);
	ngtk_event_generator_add_mouse_listener (lab2, MyFunc, NULL, NULL);

	ngtk_start_main_loop ();

/*	ngtk_object_free (wnd); */

	ngtk_quit ();
}
#endif

#ifdef NGTK_USE_XLIB
int main (int argc, char **argv)
{
	NGtkContainer *wnd;
	NGtkComponent *lab, *lab2;
	NGtkRectangle  rect;

	ngtk_init ();

	wnd = ngtk_create_root_window ("oh yeah!");
	lab = ngtk_create_button (wnd, "yesl!");

	ngtk_component_set_visible (lab, TRUE);
	rect.x = rect.y = 5;
	rect.w = rect.h = 55;
	ngtk_container_place_child (wnd, lab, &rect);
	ngtk_event_generator_add_mouse_listener (lab, MyFunc2, NULL, NULL);
	ngtk_component_set_visible (wnd, TRUE);

	ngtk_start_main_loop ();

/*	ngtk_object_free (wnd); */

	ngtk_quit ();
}
#endif
