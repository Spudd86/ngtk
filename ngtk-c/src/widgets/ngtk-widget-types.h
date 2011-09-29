/*
 * ngtk-widget-types.h
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

#ifndef __NGtk_widget_types_h__
#define __NGtk_widget_types_h__

#include "../object-system/ngtk-object.h"

enum {
	NGTK_NONE_TYPE            = 0,
	NGTK_COMPONENT_TYPE       = 1,
	NGTK_CONTAINER_TYPE       = 2,
	NGTK_EVENT_GENERATOR_TYPE = 3,
	NGTK_LAYOUT_TYPE          = 4,

	NGTK_BACKEND_BASE_TYPE    = (NGTK_MAX_INTERFACES / 2)
};

typedef  NGtkInterface  NGtkComponentI;
typedef  NGtkObject     NGtkComponent;

typedef  NGtkInterface  NGtkContainerI;
typedef  NGtkObject     NGtkContainer;

typedef  NGtkInterface  NGtkEventGeneratorI;
typedef  NGtkObject     NGtkEventGenerator;

typedef  NGtkInterface  NGtkLayoutI;
typedef  NGtkObject     NGtkLayout;

#endif
