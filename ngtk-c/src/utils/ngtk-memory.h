/*
 * ngtk-memory.h
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

#ifndef __NGtk_memory_h__
#define __NGtk_memory_h__

#include <stdlib.h>

#define ngtk_new(type)         ((type*) ngtk_malloc (sizeof (type)))
#define ngtk_new_array(type,n) ((type*) ngtk_malloc ((n) * sizeof (type)))

/* May be useful to have all the code use our own malloc/free. Note
 * that these must be valid function pointers to be passed on, so if
 * something custom should be made, it must be wrapped in a real function
 */
#define ngtk_malloc      malloc
#define ngtk_free        free

typedef void (*NGtkFreeFunc) (void *data);
#endif
