/*
 * ngtk-basic-text-entry.h
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

#ifndef __NGtk_basic_text_entry_h__
#define __NGtk_basic_text_entry_h__

#include "ngtk-basic-types.h"
#include "../../utils/ngtk-utils.h"

typedef struct _NGtkTextEntryF {
	int   (*get_cursor_position) (NGtkTextEntry *self);
	char* (*get_text_buf_ptr)    (NGtkTextEntry *self);
	int   (*get_max_text_len)    (NGtkTextEntry *self);
} NGtkTextEntryF;

typedef struct _NGtkBasicTextEntryD {
	int   cur_pos;
	int   max_text_len; /* Not including the '\0' */
	char *text;
} NGtkBasicTextEntryD;

#define NGTK_TEXT_ENTRY_O2F(comp) NGTK_O2F_CAST(comp,NGTK_TEXT_ENTRY_TYPE,NGtkTextEntryF)
#define NGTK_TEXT_ENTRY_I2F(comp) NGTK_I2F_CAST(comp,NGTK_TEXT_ENTRY_TYPE,NGtkTextEntryF)

#define NGTK_BASIC_TEXT_ENTRY_O2D(comp) NGTK_O2D_CAST(comp,NGTK_TEXT_ENTRY_TYPE,NGtkBasicTextEntryD,0)
#define NGTK_BASIC_TEXT_ENTRY_I2D(comp) NGTK_I2D_CAST(comp,NGTK_TEXT_ENTRY_TYPE,NGtkBasicTextEntryD,0)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkTextEntryF object */

int   ngtk_text_entry_get_cursor_position    (NGtkTextEntry *self);
char* ngtk_text_entry_get_text_buf_ptr       (NGtkTextEntry *self);
int   ngtk_text_entry_get_max_text_len       (NGtkTextEntry *self);

/* And the implementation */
NGtkTextEntryI*  ngtk_basic_text_entry_create_interface (NGtkObject *obj, const char *initial_text, int max_text_len);
int   ngtk_basic_text_entry_get_cursor_position    (NGtkTextEntry *self);
char* ngtk_basic_text_entry_get_text_buf_ptr       (NGtkTextEntry *self);
int   ngtk_basic_text_entry_get_max_text_len       (NGtkTextEntry *self);

#endif
