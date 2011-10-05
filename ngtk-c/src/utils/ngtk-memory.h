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

/**
 * A malloc function which outputs to the terminal the type and adress
 * of the allocated memory. Can be useful for debugging pointer types.
 * This should not be used directly - it should be used by the
 * \ref ngtk_new macro when type debugging is enabled.
 */
void* ngtk_debug_malloc (int size, const char *type);
/**
 * A free function which outputs to the terminal the adress of the freed
 * memory. Together with \ref ngtk_debug_malloc it can be useful for
 * debugging memory allocations
 */
void ngtk_debug_free (void *where);

#ifdef NGTK_TYPE_DEBUG
#define ngtk_new(type)         ((type*) (ngtk_debug_malloc (sizeof (type), #type)))
#define ngtk_new_array(type,n) ((type*) (ngtk_debug_malloc ((n) * sizeof (type), #type "[" #n "]")))
#else
#define ngtk_new(type)         ((type*) (ngtk_malloc (sizeof (type))))
#define ngtk_new_array(type,n) ((type*) (ngtk_malloc ((n) * sizeof (type))))
#endif

/* May be useful to have all the code use our own malloc/free. Note
 * that these must be valid function pointers to be passed on, so if
 * something custom should be made, it must be wrapped in a real function
 */

#ifdef NGTK_TYPE_DEBUG
#define ngtk_malloc      malloc
#define ngtk_free        ngtk_debug_free
#else
#define ngtk_malloc      malloc
#define ngtk_free        free
#endif

#endif
