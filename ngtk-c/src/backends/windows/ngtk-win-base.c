/*
 * ngtk-win-base.c
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

#include <Windows.h>
#include "ngtk-win-base.h"

NGtkWinBaseI* ngtk_win_base_create_interface ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_WINBASE_TYPE);
	NGtkWinBaseD *wbd;

	in->d[0] = wbd = ngtk_new (NGtkWinBaseD);
	wbd->hwnd = NULL;
	wbd->base_wndproc = NULL;
	in->d_free[0] = ngtk_win_base_d_free;

	in->f = NULL;
	in->f = NULL;

	return in;
}

void ngtk_win_base_d_free (void *d)
{
	NGtkWinBaseD *dReal = (NGtkWinBaseD*) d;
	if (dReal->hwnd != NULL)
		DestroyWindow (dReal->hwnd);
	ngtk_free (d);
}
