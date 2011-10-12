/*
 * ngtk-grid-layout.h
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

#ifndef __NGtk_grid_layout_h__
#define __NGtk_grid_layout_h__

#include "../widgets/ngtk-widgets.h"

typedef struct _ngtk_grid_layout {
	NGtkContainer *cont;
	int            xSize, ySize;
	NGtkList       comps;
	NGtkList       areas;
} NGtkGridLayoutD;

typedef NGtkLayout NGtkGridLayout;

#define NGTK_GRID_LAYOUT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_LAYOUT_TYPE,NGtkGridLayoutD,0)
#define NGTK_GRID_LAYOUT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_LAYOUT_TYPE,NGtkGridLayoutD,0)

NGTK_EXPORT NGtkLayout* ngtk_grid_layout_new  (NGtkContainer *cont, int xSize, int ySize);
NGTK_EXPORT int         ngtk_grid_layout_add  (NGtkLayout *self, NGtkComponent *comp, const NGtkRectangle *area);
NGTK_EXPORT void        ngtk_grid_layout_pack (NGtkLayout *self, NGtkContainer *cont, int width, int height);

#endif
