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
#include "../src/layouts/ngtk-grid-layout.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "calculator.h"
#define MAX_STR 4096

NGtkComponent *number, *op;

/* Calculator Logic in Pseudo Code:
 *
 * On "Op":
 * - If CurrentOp == NOP:
 * -     Current = Prev
 * -     Single Type
 * - Else:
 * - Compute 
 * On "Compute":
 * NUMBER:
 * : "Op":
 * : -> prev = current, current = 
 * : 
 * : "Digit"/"Erase" -> NUMBER1 (change number)
 * : "Compute"       -> NUMBER1 (do nothing)
 *
 * NUMBER2:
 * : "COMPUTE"
 *
 */

void UpdateGUI ()
{
	ngtk_component_set_text (number, GetNumberToDisplay ());
	ngtk_component_set_text (op, GetOpToDisplay ());
}

void NumberClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		DigitPressed (ngtk_component_get_text (comp) [0]);
		UpdateGUI ();
	}
}

void DotClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		DotPressed ();
		UpdateGUI ();
	}
}

void OpClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		OpPressed (ngtk_component_get_text (comp) [0]);
		UpdateGUI ();
	}
}

void EraseClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		ErasePressed ();
		UpdateGUI ();
	}
}

void ComputeClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
		ComputePressed ();
	UpdateGUI ();
}

void ClearClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
		ClearPressed ();
	UpdateGUI ();
}

void ToggleClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		ToggleMinus ();
		UpdateGUI ();
	}
}

void CommonKeyboardHandler (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	NGtkKeyboardEventKey key = ((NGtkKeyboardEvent*)sigdata)->key;
	int someUpdate = TRUE;
	if (key == '-' || key == '+' || key == '*' || key == '/')
		OpPressed ((char)key);
	else if (key == '.')
		DotPressed ();
	else if (key == 'c' || key == 'C')
		ClearPressed ();
	else if (key == 'i' || key == 'I')
		ToggleMinus ();
	else if (key >= NGTK_KKEY_MIN_CHAR && key <= NGTK_KKEY_MAX_CHAR && isdigit ((char)key))
		DigitPressed ((char)key);
	else if (key == NGTK_KKEY_BACKSPACE)
		ErasePressed ();
	else if (key == NGTK_KKEY_ENTER)
		ComputePressed ();
	else
		someUpdate = FALSE;

	if (someUpdate)
		UpdateGUI ();
}

void QuitClick (NGtkComponent *comp, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
		ngtk_backend_quit_main_loop (ngtk_base_get_backend (comp));
}

typedef enum {
	LABEL,
	BUTTON,
	TEXT_ENTRY
} WidgetType;

typedef struct {
	const char          *text;
	const NGtkRectangle  rect;
	WidgetType           wt;
	NGtkListener         mouse_handler;
	NGtkListener         keyboard_handler;
} WidgetSpecs;

/* We are going to create a calculator with the
 * following layout:
 *
 *   Op     Number
 * +---+---------------+
 * |   |               |
 * |---+---+---+---+---|
 * | 1 | 2 | 3 | + | < |
 * |---+---+---+---+---|
 * | 4 | 5 | 6 | - | C |
 * |---+---+---+---+---|
 * | 7 | 8 | 9 | * |   |
 * |---+---+---+---| = |
 * |   0   | . | / |   |
 * +-------+---+---+---+
 * |       Quit        |
 * +-------------------+
 *
 * This actually based on a grid which is 5x6 (width x height)
 */

const static int GridWidth = 5, GridHeight = 6;

const static WidgetSpecs gui[] = {
	{ "",  { 0, 0, 1, 1 }, LABEL, NULL, NULL },
	{ "",  { 1, 0, 4, 1 }, LABEL, NULL, NULL },

	{ "1",   { 0, 1, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "2",   { 1, 1, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "3",   { 2, 1, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "4",   { 0, 2, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "5",   { 1, 2, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "6",   { 2, 2, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "7",   { 0, 3, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "8",   { 1, 3, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "9",   { 2, 3, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "0",   { 0, 4, 1, 1 }, BUTTON, NumberClick, CommonKeyboardHandler },
	{ "+/-", { 1, 4, 1, 1 }, BUTTON, ToggleClick, CommonKeyboardHandler },
	{ ".",   { 2, 4, 1, 1 }, BUTTON, DotClick, CommonKeyboardHandler },

	{ "+", { 3, 1, 1, 1 }, BUTTON, OpClick, CommonKeyboardHandler },
	{ "-", { 3, 2, 1, 1 }, BUTTON, OpClick, CommonKeyboardHandler },
	{ "*", { 3, 3, 1, 1 }, BUTTON, OpClick, CommonKeyboardHandler },
	{ "/", { 3, 4, 1, 1 }, BUTTON, OpClick, CommonKeyboardHandler },

	{ "<", { 4, 1, 1, 1 }, BUTTON, EraseClick, CommonKeyboardHandler },
	{ "C", { 4, 2, 1, 1 }, BUTTON, ClearClick, CommonKeyboardHandler },
	{ "=", { 4, 3, 1, 2 }, BUTTON, ComputeClick, CommonKeyboardHandler },

	{ "Quit", { 0, 5, 5, 1 }, BUTTON, QuitClick, CommonKeyboardHandler },
};

int main (int argc, char **argv)
{
	char text[MAX_STR+1] = { '\0' };
	NGtkGridLayout *gl;

#ifdef NGTK_USE_NC
	NGtkBackend *X = ngtk_nc_backend_new ();
#elif defined (NGTK_USE_XLIB)
	NGtkBackend *X = ngtk_xlib_backend_new ();
#elif defined (NGTK_USE_WINDOWS)
	NGtkBackend *X = ngtk_win_backend_new ();
#else
#error "No backend selected!"
#endif

	NGtkContainer *wnd;
	NGtkComponent *lab;
	int            i;

	ngtk_backend_init (X);

	wnd = ngtk_backend_create_root_window (X, "oh yeah!");

	gl = ngtk_grid_layout_new (wnd, GridWidth, GridHeight);

	for (i = 0; i < NGTK_ELEMENT_COUNT (gui); i++)
	{
		switch (gui[i].wt)
		{
		case LABEL:
			lab = ngtk_backend_create_label (X, wnd, gui[i].text);
			break;
		case BUTTON:
			lab = ngtk_backend_create_button (X, wnd, gui[i].text);
			break;
		case TEXT_ENTRY:
			lab = ngtk_backend_create_text_entry (X, wnd, gui[i].text, MAX_NUMBER_LEN);
			break;
		default:
			ngtk_assert (FALSE);
		}
		
		ngtk_grid_layout_add (gl, lab, &gui[i].rect);
//		printf ("Adding \"%s\" at (%d,%d) %dx%d\n", gui[i].text, gui[i].rect.x, gui[i].rect.y, gui[i].rect.w, gui[i].rect.h);
		ngtk_component_set_visible (lab, TRUE);
		ngtk_object_connect_to (lab, "event::mouse", gui[i].mouse_handler, NULL);
		ngtk_object_connect_to (lab, "event::keyboard", gui[i].keyboard_handler, NULL);

		if (i == 0)
			op = lab;
		else if (i == 1)
			number = lab;
	}
	
	ClearPressed ();
	UpdateGUI ();

	ngtk_container_set_layout (wnd, gl);
	ngtk_component_set_visible (wnd, TRUE);
	ngtk_container_pack (wnd);

	ngtk_assert (ngtk_backend_set_focus_holder (X, lab));

//	ngtk_backend_set_focus_holder (X, lab);

	ngtk_backend_start_main_loop (X);

	ngtk_backend_quit (X);

	ngtk_object_free (X);

	return EXIT_SUCCESS;
}
