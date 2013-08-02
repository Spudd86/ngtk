/*
 * ngtk-basic-component.h - Part of the NGtk library
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

#ifndef __NGtk_basic_component__
#define __NGtk_basic_component__

#include "../../widgets/ngtk-widgets.h"

typedef struct _ngtk_basic_component_d {
	NGtkContainer* parent;
	int            enabled;
	int            visible;
	int            focusable;
	const char*    text;
} NGtkBasicComponentD;

#define NGTK_BASIC_COMPONENT_O2D(comp) NGTK_O2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkBasicComponentD,0)
#define NGTK_BASIC_COMPONENT_I2D(comp) NGTK_I2D_CAST(comp,NGTK_COMPONENT_TYPE,NGtkBasicComponentD,0)

NGtkInterface* ngtk_basic_component_create_interface (NGtkObject *obj, NGtkContainer *parent, int enabled, int focusable, const char* text, int visible);

NGtkContainer* ngtk_basic_component_get_parent       (NGtkComponent *self);

int            ngtk_basic_component_get_enabled      (NGtkComponent *self);
void           ngtk_basic_component_set_enabled      (NGtkComponent *self, int enabled);

int            ngtk_basic_component_get_visible      (NGtkComponent *self);
void           ngtk_basic_component_set_visible      (NGtkComponent *self, int visible);

int            ngtk_basic_component_get_focusable    (NGtkComponent *self);

const char*    ngtk_basic_component_get_text         (NGtkComponent *self);
void           ngtk_basic_component_set_text         (NGtkComponent *self, const char *text);

void           ngtk_basic_component_redraw           (NGtkComponent *self);

#endif
