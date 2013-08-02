/*
 * ngtk-basic-base.c - Part of the NGtk library
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

#include "ngtk-basic-base.h"

static void simple_destroy_base_interface (NGtkObject *obj);

NGtkBaseI* ngtk_basic_base_create_interface (NGtkObject *obj, NGtkBackend *backend)
{
	NGtkInterface *in = ngtk_interface_new (obj, NGTK_BASE_TYPE);
	NGtkBasicBaseD *bbd;

	in->imp_data[0] = bbd = ngtk_new (NGtkBasicBaseD);
	bbd->backend = backend;
	in->imp_data_free[0] = ngtk_free;

	in->functions = ngtk_new (NGtkBaseF);
	NGTK_BASE_I2F (in) -> get_backend = ngtk_basic_base_get_backend;
	in->functions_free = ngtk_free;

	ngtk_object_push_destructor (obj, simple_destroy_base_interface);

	return in;
}

static void simple_destroy_base_interface (NGtkObject *obj)
{
	ngtk_interface_detach_and_free (ngtk_object_cast (obj, NGTK_BASE_TYPE));
}

NGtkBackend* ngtk_basic_base_get_backend (NGtkBase *self)
{
	return NGTK_BASIC_BASE_O2D (self) -> backend;
}
