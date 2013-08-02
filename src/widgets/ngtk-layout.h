/*
 * ngtk-layout.h - Part of the NGtk library
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
NGTK_EXPORT void ngtk_layout_pack (NGtkLayout *self, NGtkContainer *cont, int width, int height);

#endif
