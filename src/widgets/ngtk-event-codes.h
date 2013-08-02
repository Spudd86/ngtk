/*
 * ngtk-event-codes.h
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
