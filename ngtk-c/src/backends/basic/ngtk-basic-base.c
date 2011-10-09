/*
 * ngtk-basic-base.c
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
