/*
 * ngtk-basic-base.h
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

#ifndef __NGtk_basic_base__
#define __NGtk_basic_base__

#include "../../widgets/ngtk-base.h"

typedef NGtkBase NGtkBasicBase;

typedef struct _ngtk_basic_base_d {
	NGtkBackend *backend;
} NGtkBasicBaseD;

#define NGTK_BASIC_BASE_O2D(comp) NGTK_O2D_CAST(comp,NGTK_BASE_TYPE,NGtkBasicBaseD,0)
#define NGTK_BASIC_BASE_I2D(comp) NGTK_I2D_CAST(comp,NGTK_BASE_TYPE,NGtkBasicBaseD,0)

NGtkBaseI*    ngtk_basic_base_create_interface  (NGtkObject *obj, NGtkBackend *backend);
NGtkBackend*  ngtk_basic_base_get_backend       (NGtkBase *self);

#endif
