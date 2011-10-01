/*
 * ngtk-base.h
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

#ifndef __NGtk_base__
#define __NGtk_base__

#include "ngtk-widgets.h"
#include <stdarg.h>

typedef struct _ngtk_base_f {
	NGtkBackend* (*get_backend) (NGtkBase *self);
} NGtkBaseF;

#define NGTK_BASE_O2F(comp) NGTK_O2F_CAST(comp,NGTK_BASE_TYPE,NGtkBaseF)
#define NGTK_BASE_I2F(comp) NGTK_I2F_CAST(comp,NGTK_BASE_TYPE,NGtkBaseF)

/**
 * Get the backend associated with this object
 * 
 * @param self The object whose backend should be returned
 * @return The backend
 *
 * @since 0.9
 */
NGtkBackend* ngtk_base_get_backend (NGtkBase *self);

#endif
