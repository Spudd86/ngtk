/*
 * ngtk-memory.h - Part of the NGtk library
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

#ifndef __NGtk_memory_h__
#define __NGtk_memory_h__

#include <stdlib.h>

/**
 * A malloc function which outputs to the terminal the type and adress
 * of the allocated memory. Can be useful for debugging pointer types.
 * This should not be used directly - it should be used by the
 * \ref ngtk_new macro when type debugging is enabled.
 */
NGTK_EXPORT void* ngtk_debug_malloc (int size, const char *type);
/**
 * A free function which outputs to the terminal the adress of the freed
 * memory. Together with \ref ngtk_debug_malloc it can be useful for
 * debugging memory allocations
 */
NGTK_EXPORT void ngtk_debug_free (void *where);

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
