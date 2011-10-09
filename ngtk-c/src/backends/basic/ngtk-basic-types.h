/*
 * ngtk-basic-types.h
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

#ifndef __NGtk_basic_types_h__
#define __NGtk_basic_types_h__

#include "../../object-system/ngtk-object.h"
#include "../../widgets/ngtk-widget-types.h" /* To define the graphics type */

typedef NGtkObject    NGtkGraphics;
typedef NGtkInterface NGtkGraphicsI;

typedef NGtkObject    NGtkTextEntry;
typedef NGtkInterface NGtkTextEntryI;

enum {
	NGTK_GRAPHICS_TYPE = NGTK_BACKEND_BASE_TYPE,
	NGTK_TEXT_ENTRY_TYPE,
	NGTK_SUB_BACKEND_BASE_TYPE
};

#endif
