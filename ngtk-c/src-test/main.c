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
#include <string.h>

#define MAX_STR 4096
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

void SimulateLabel (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	char *textbuf = (char *) lisdata;
	int curlen = strlen (textbuf);

	NGtkKeyboardEvent *kevent = (NGtkKeyboardEvent*) sigdata;
	NGtkKeyboardEventKey key = kevent->key;

//	printf ("SimulateLabel\n");
	if (curlen > 0 && key == NGTK_KKEY_BACKSPACE)
		textbuf[curlen - 1] = '\0';
	else if (curlen < MAX_STR)
	{
		char toAdd = '\0';
		if (key == NGTK_KKEY_SPACE)
			toAdd = ' ';
		else if (NGTK_KKEY_MIN_CHAR < key && key < NGTK_KKEY_MAX_CHAR)
			toAdd = key;

		textbuf[curlen] = toAdd;
		textbuf[curlen+1] = '\0';
	}

	ngtk_component_set_text (comp, textbuf);
}

int main (int argc, char **argv)
{
	char text[MAX_STR+1] = { '\0' };

#ifdef NGTK_USE_NC
	NGtkBackend *X = ngtk_nc_backend_new ();
#elif defined (NGTK_USE_XLIB)
	NGtkBackend *X = ngtk_xlib_backend_new ();
#else
#error "No backend selected!"
#endif

	NGtkContainer *wnd;
	NGtkComponent *lab;
	NGtkRectangle  rect;

	ngtk_backend_init (X);

	wnd = ngtk_backend_create_root_window (X, "oh yeah!");
	ngtk_object_connect_to (wnd, "event::mouse", QuitOnPress, NULL);

	lab = ngtk_backend_create_text_entry (X, wnd, "oh no!", 4096);
	ngtk_object_connect_to (lab, "event::mouse", HideOnClick, text);

	ngtk_component_set_visible (lab, TRUE);
	ngtk_component_set_visible (wnd, TRUE);

	ngtk_assert (ngtk_backend_set_focus_holder (X, lab));

	ngtk_backend_start_main_loop (X);

	ngtk_backend_quit (X);

	ngtk_object_free (X);

	return EXIT_SUCCESS;
}
