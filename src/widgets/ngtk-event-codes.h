/*
 * ngtk-event-codes.h - Part of the NGtk library
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

#ifndef __NGtk_event_codes_h__
#define __NGtk_event_codes_h__

typedef enum {
	NGTK_MBUT_NONE = 0,
	NGTK_MBUT_L,
	NGTK_MBUT_R,
	NGTK_MBUT_M,
} NGtkMouseEventButton;

typedef enum {
	NGTK_MET_UP,
	NGTK_MET_DOWN,
	NGTK_MET_CLICK,
	NGTK_MET_MOVE
} NGtkMouseEventType;

typedef enum {
	NGTK_KKEY_MIN_CHAR     = 0x000,

	NGTK_KKEY_MAX_CHAR     = 0xff,

	NGTK_KKEY_ARROW_MIN    = 0x100,
	NGTK_KKEY_ARROW_LEFT,
	NGTK_KKEY_ARROW_RIGHT,
	NGTK_KKEY_ARROW_UP,
	NGTK_KKEY_ARROW_DOWN,
	NGTK_KKEY_ARROW_MAX    = 0x199,

	NGTK_KKEY_SPACERS_MIN  = 0x200,
	NGTK_KKEY_ENTER,
	NGTK_KKEY_SPACE,
	NGTK_KKEY_BACKSPACE,
	NGTK_KKEY_SPACERS_MAX  = 0x299,

	NGTK_KKEY_OTHER        = 0xffff
} NGtkKeyboardEventKey;

typedef struct _ngtk_mouse_event {
	NGtkMouseEventType   type;
	NGtkMouseEventButton button;
} NGtkMouseEvent;

typedef struct _ngtk_keyboard_event {
	NGtkKeyboardEventKey key;
} NGtkKeyboardEvent;

#endif
