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

void HideOnClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	NGtkMouseEvent *evnt = (NGtkMouseEvent*) sigdata;
	if (evnt->type == NGTK_MET_CLICK)
		ngtk_component_set_visible (comp, ! ngtk_component_get_visible (comp));
}

void QuitOnPress (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	ngtk_debug (ngtk_base_get_backend (comp), "Received mouse event signal!");
	NGtkMouseEvent *evnt = (NGtkMouseEvent*) sigdata;
	if (evnt->type == NGTK_MET_CLICK)
		ngtk_backend_quit_main_loop (ngtk_base_get_backend (comp));
}

int main (int argc, char **argv)
{
	NGtkBackend *X = ngtk_xlib_backend_new ();

	NGtkContainer *wnd;
	NGtkComponent *lab, *lab2;
	NGtkRectangle  rect;

	ngtk_backend_init (X);

	wnd = ngtk_backend_create_root_window (X, "oh yeah!");
	ngtk_object_connect_to (wnd, "event::mouse", QuitOnPress, NULL);
	ngtk_component_set_visible (wnd, TRUE);

	ngtk_backend_start_main_loop (X);

	ngtk_backend_quit (X);

	ngtk_object_free (X);

	return EXIT_SUCCESS;
}
