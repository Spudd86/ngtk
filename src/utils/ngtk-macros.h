/*
 * ngtk-macros.h - Part of the NGtk library
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

#ifndef __NGtk_macros_h__
#define __NGtk_macros_h__

#include <assert.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (! FALSE)
#endif

#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(a) (((a) < 0) ? -(a) : (a))
#endif

/** Check if a value is in the range between two given values
 * (including thos values) */
#define NGTK_IN_RANGE(val,min,max) ((min) <= (val) && (val) <= (max))
#define NGTK_BIT_MASK(bit) ( ((unsigned long long)1) << ((bit)-1))

#define NGTK_FIELD_OFFSET(field,type) ((int)(&(((type*)NULL)->field)))

#define NGTK_LONG_MACRO_BEGIN do {
#define NGTK_LONG_MACRO_END   } while (FALSE)

#define NGTK_MACRO_DO_NOTHING() NGTK_LONG_MACRO_BEGIN NGTK_LONG_MACRO_END

#ifndef NGTK_OPTIMIZE
#define ngtk_assert(expr) assert(expr)
#else
#define ngtk_assert(expr) NGTK_MACRO_DO_NOTHING ()
#endif

#ifdef _WIN32
#define NGTK_EXPORT __declspec(dllexport)
#else
#define NGTK_EXPORT
#endif

#define NGTK_ELEMENT_COUNT(ar) (sizeof(ar)/sizeof((ar)[0]))
#define ngtk_assert_not_reached() assert (FALSE)
#endif
