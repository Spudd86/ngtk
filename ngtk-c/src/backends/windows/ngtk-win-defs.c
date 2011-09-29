/*
 * ngtk-win-defs.c
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

#include "windows.h"

void ngtk_win_start_main_loop ()
{
	MSG Msg;

	/* The Message Loop. Receive messages and continue as long as there is no
	 * error (the return code is non negative) and as long as the message isn't
	 * a QUIT message (return code 0).
	 *
	 * We don't want to limit to a specific window, so pass NULL as the HWND
	 *
	 * Finally, for now we don't limit to just specific events, so both min and
	 * max of the message range are 0
	 */
	while (GetMessage (&Msg, NULL, 0, 0) > 0)
	{
		/* Do some processing of the message. TODO: what exactly? */
		TranslateMessage (&Msg);
		/* Send the message forward. TODO: how does this work with TranslateMessage? */
		DispatchMessage (&Msg);
	}
}

void ngtk_win_quit_main_loop ()
{
	PostQuitMessage (0);
}

