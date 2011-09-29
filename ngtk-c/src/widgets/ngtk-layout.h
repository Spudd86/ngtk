/*
 * ngtk-layout.h
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

#ifndef __NGtk_layout_h__
#define __NGtk_layout_h__

#include "../utils/ngtk-utils.h"
#include "ngtk-widget-types.h"

typedef struct _NGtkLayoutF {
	void (*pack) (NGtkLayout *self, NGtkContainer *cont, int width, int height);
} NGtkLayoutF;

#define NGTK_LAYOUT_O2F(comp) NGTK_O2F_CAST(comp,NGTK_LAYOUT_TYPE,NGtkLayoutF)
#define NGTK_LAYOUT_I2F(comp) NGTK_I2F_CAST(comp,NGTK_LAYOUT_TYPE,NGtkLayoutF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkLayoutF object */

/**
 * Pack the specified container and positions it's children, according
 * to the given size limitations
 *
 * @param self The layout object
 * @param cont The container to pack
 * @param width The width to use
 * @param height The height to use
 *
 * @warning This method should not be called outside of NGtk! Also,
 *          since containers may add functionallity to their pack
 *          method, then this function should not be called from
 *          anywhere other than a container's pack.
 *
 * @since 0.9
 */
void ngtk_layout_pack (NGtkLayout *self, NGtkContainer *cont, int width, int height);

#endif
