/*
 * ngtk-widget-types.h - Part of the NGtk library
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

#ifndef __NGtk_widget_types_h__
#define __NGtk_widget_types_h__

#include "../object-system/ngtk-object.h"

enum {
	NGTK_NONE_TYPE            = 0,
	NGTK_COMPONENT_TYPE       = 1,
	NGTK_CONTAINER_TYPE       = 2,
	NGTK_LAYOUT_TYPE          = 3,
	NGTK_BACKEND_TYPE         = 4,
	NGTK_BASE_TYPE            = 5,

	NGTK_BACKEND_BASE_TYPE    = (NGTK_MAX_INTERFACES / 2)
};

typedef  NGtkInterface  NGtkComponentI;
typedef  NGtkObject     NGtkComponent;

typedef  NGtkInterface  NGtkContainerI;
typedef  NGtkObject     NGtkContainer;

typedef  NGtkInterface  NGtkLayoutI;
typedef  NGtkObject     NGtkLayout;

typedef  NGtkInterface  NGtkBackendI;
typedef  NGtkObject     NGtkBackend;

typedef  NGtkInterface  NGtkBaseI;
typedef  NGtkObject     NGtkBase;

#endif
