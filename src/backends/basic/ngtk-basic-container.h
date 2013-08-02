/*
 * ngtk-basic-container.h - Part of the NGtk library
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

#ifndef __NGtk_basic_container__
#define __NGtk_basic_container__

#include "../../widgets/ngtk-widgets.h"

typedef struct _ngtk_basic_container_d {
	NGtkComponentList  children;
	NGtkLayout*        layout;
} NGtkBasicContainerD;

#define NGTK_BASIC_CONTAINER_O2D(comp) NGTK_O2D_CAST(comp,NGTK_CONTAINER_TYPE,NGtkBasicContainerD,0)
#define NGTK_BASIC_CONTAINER_I2D(comp) NGTK_I2D_CAST(comp,NGTK_CONTAINER_TYPE,NGtkBasicContainerD,0)

NGtkInterface*     ngtk_basic_container_create_interface (NGtkObject *obj);

NGtkComponentList* ngtk_basic_container_get_children     (NGtkContainer *self);

void               ngtk_basic_container_add_child        (NGtkContainer *self, NGtkComponent* child);
void               ngtk_basic_container_remove_child     (NGtkContainer *self, NGtkComponent* child);

void               ngtk_basic_container_place_child      (NGtkContainer *self, NGtkComponent* child, NGtkRectangle *rect);

void               ngtk_basic_container_set_layout       (NGtkContainer *self, NGtkLayout *layout);
void               ngtk_basic_container_pack             (NGtkContainer *self);

/* Non interface functions */
NGtkLayout*        ngtk_basic_container_get_layout       (NGtkContainer *self);

#endif
