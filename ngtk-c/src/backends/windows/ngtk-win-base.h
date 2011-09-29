/*
 * ngtk-win-base.h
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

#ifndef __NGtk_win_base_h__
#define __NGtk_win_base_h__

#include <Windows.h>
#include "../../utils/ngtk-utils.h"
#include "ngtk-win-widget-types.h"

//typedef struct _ngtk_winbase_f {
//	HWND (*get_hwnd)      (NGtkWinBase *self);
//	void (*set_hwnd)      (NGtkWinBase *self, HWND hwnd);
//	void (*destroy_hwnd)  (NGtkWinBase *self, HWND hwnd);
//} NGtkWinBaseF;
//
//#define NGTK_WINBASE_O2F(comp) NGTK_O2F_CAST(comp,NGTK_WINBASE_TYPE,NGtkWinBaseF)
//#define NGTK_WINBASE_I2F(comp) NGTK_I2F_CAST(comp,NGTK_WINBASE_TYPE,NGtkWinBaseF)
//

typedef struct _ngtk_win_base_d {
	HWND    hwnd;
	WNDPROC base_wndproc;
} NGtkWinBaseD;

#define NGTK_WINBASE_O2D(comp) NGTK_O2D_CAST(comp,NGTK_WINBASE_TYPE,NGtkWinBaseD,0)
#define NGTK_WINBASE_I2D(comp) NGTK_I2D_CAST(comp,NGTK_WINBASE_TYPE,NGtkWinBaseD,0)

NGtkWinBaseI*  ngtk_win_base_create_interface  ();
void           ngtk_win_base_d_free            (void *d);

///* The following functions only wrap calls instead of doing them
// * directly from the NGtkContainerF object */
//
//HWND   ngtk_winbase_get_hwnd      (NGtkWinBase *self)
//HWND   ngtk_winbase_set_hwnd      (NGtkWinBase *self, HWND hwnd);
//HWND   ngtk_winbase_destroy_hwnd  (NGtkWinBase *self, HWND hwnd);
//
//HWND   ngtk_winbase_get_hwnd_imp  (NGtkWinBase *self)
//HWND   ngtk_winbase_set_hwnd_imp  (NGtkWinBase *self, HWND hwnd);
//HWND   ngtk_winbase_destroy_hwnd  (NGtkWinBase *self, HWND hwnd);

#endif
