/*
 * ngtk-grid-layout.h - Part of the NGtk library
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
