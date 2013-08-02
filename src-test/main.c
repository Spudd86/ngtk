/*
 * main.c - Part of the NGtk library
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

#include "../src/ngtk.h"
#include "../src/layouts/ngtk-grid-layout.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "calculator.h"
#define MAX_STR 4096

NGtkComponent *number, *op;

void UpdateGUI ()
{
	ngtk_component_set_text (number, GetNumberToDisplay ());
	ngtk_component_set_text (op, GetOpToDisplay ());
}

void NumberClick (void *src, const char* signame, void *sigdata, void *lisdata)
{
	NGtkComponent *comp = (NGtkComponent*) src;
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		DigitPressed (ngtk_component_get_text (comp) [0]);
		UpdateGUI ();
	}
}

void DotClick (void *src, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		DotPressed ();
		UpdateGUI ();
	}
}

void OpClick (void *src, const char* signame, void *sigdata, void *lisdata)
{
	NGtkComponent *comp = (NGtkComponent*) src;
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		OpPressed (ngtk_component_get_text (comp) [0]);
		UpdateGUI ();
	}
}

void EraseClick (void *src, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		ErasePressed ();
		UpdateGUI ();
	}
}

void ComputeClick (void *src, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
		ComputePressed ();
	UpdateGUI ();
}

void ClearClick (void *src, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
		ClearPressed ();
	UpdateGUI ();
}

void ToggleClick (void *src, const char* signame, void *sigdata, void *lisdata)
{
	if (((NGtkMouseEvent*) sigdata)->type == NGTK_MET_CLICK)
	{
		ToggleMinus ();
		UpdateGUI ();
	}
}

void CommonKeyboardHandler (void *src, const char* signame, void *sigdata, void *lisdata)
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
	else if (key == 'Q' || key == 'q')
		ngtk_backend_quit_main_loop (ngtk_base_get_backend ((NGtkComponent*) src));
	else
		someUpdate = FALSE;

	if (someUpdate)
		UpdateGUI ();
}

void QuitClick (void *src, const char* signame, void *sigdata, void *lisdata)
{
	NGtkComponent *comp = (NGtkComponent*) src;
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
 * | 0 |+/-| . | / |   |
 * +---+---+---+---+---+
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
		ngtk_component_set_visible (lab, TRUE);

		if (gui[i].mouse_handler != NULL)
			ngtk_object_connect_to (lab, "event::mouse", gui[i].mouse_handler, NULL);
		if (gui[i].keyboard_handler != NULL)
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
	ngtk_object_free (gl);

	return EXIT_SUCCESS;
}
