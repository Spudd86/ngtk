/*
 * ngtk-win-defs.h
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

#ifndef __NGtk_win_defs__
#define __NGtk_win_defs__

#include "ngtk-win-widget-types.h"

#include "ngtk-win-base.h"
#include "ngtk-win-component.h"
#include "ngtk-win-container.h"
#include "ngtk-win-event-generator.h"

#include "ngtk-widget-window.h"

void     ngtk_win_start_main_loop      ();
void     ngtk_win_quit_main_loop       ();

#endif
