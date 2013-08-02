/*
 * ngtk-backends.h
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

#ifndef __NGtk_backends_h__
#define __NGtk_backends_h__

#include "../widgets/ngtk-widgets.h"

#ifdef     NGTK_USE_NC
#  include "nc/ngtk-nc.h"
#elif defined NGTK_USE_WINDOWS
#  include "windows/ngtk-win.h"
#elif defined NGTK_USE_XLIB
#  include "xlib/ngtk-xlib.h"
#else
#  error   "No backend selected for NGtk!"
#endif

#endif