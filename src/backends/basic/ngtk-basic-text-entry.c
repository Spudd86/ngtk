/*
 * ngtk-basic-text-entry.c - Part of the NGtk library
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

#include <string.h>
#include <ctype.h>

#include "ngtk-basic.h"

static void basic_text_entry_destructor (NGtkTextEntry *self);
static void simulate_text_entry (void *src, const char* signame, void *sigdata, void *lisdata);

int ngtk_text_entry_get_cursor_position    (NGtkTextEntry *self)
{
	return NGTK_TEXT_ENTRY_O2F (self) -> get_cursor_position (self);
}
char* ngtk_text_entry_get_text_buf_ptr       (NGtkTextEntry *self)
{
	return NGTK_TEXT_ENTRY_O2F (self) -> get_text_buf_ptr (self);
}
int   ngtk_text_entry_get_max_text_len       (NGtkTextEntry *self)
{
	return NGTK_TEXT_ENTRY_O2F (self) -> get_max_text_len (self);
}

/* And the implementation */
NGtkTextEntryI* ngtk_basic_text_entry_create_interface (NGtkObject *obj, const char *initial_text, int max_text_len)
{
	NGtkInterface *in = ngtk_interface_new (obj, NGTK_TEXT_ENTRY_TYPE);
	NGtkBasicTextEntryD *btd = ngtk_new (NGtkBasicTextEntryD);

	in->imp_data[0] = btd;
	btd->cur_pos = 0;
	btd->text = ngtk_new_array (char, max_text_len + 1);
	strcpy (btd->text, initial_text);
	btd->max_text_len = max_text_len;
	in->imp_data_free[0] = ngtk_free;

	in->functions = ngtk_new (NGtkTextEntryF);
	NGTK_TEXT_ENTRY_I2F (in) -> get_cursor_position = ngtk_basic_text_entry_get_cursor_position;
	NGTK_TEXT_ENTRY_I2F (in) -> get_text_buf_ptr = ngtk_basic_text_entry_get_text_buf_ptr;
	NGTK_TEXT_ENTRY_I2F (in) -> get_max_text_len = ngtk_basic_text_entry_get_max_text_len;
	in->functions_free = ngtk_free;

	ngtk_object_push_destructor (obj, basic_text_entry_destructor);

	ngtk_object_connect_to (obj, "event::keyboard", simulate_text_entry, btd);

	return in;
}

static void basic_text_entry_destructor (NGtkTextEntry *self)
{
	NGtkBasicTextEntryD *bted = NGTK_BASIC_TEXT_ENTRY_O2D (self);
	ngtk_free (bted->text);
	ngtk_interface_detach_and_free (ngtk_object_cast (self, NGTK_TEXT_ENTRY_TYPE));
}

static void simulate_text_entry (void *src, const char* signame, void *sigdata, void *lisdata)
{
	NGtkBasicTextEntryD *ted = (NGtkBasicTextEntryD*) lisdata;
	NGtkComponent       *comp = (NGtkComponent*) src;

	char *textbuf = ted->text;
	int curlen = strlen (textbuf);
	int i;

	NGtkKeyboardEvent *kevent = (NGtkKeyboardEvent*) sigdata;
	NGtkKeyboardEventKey key = kevent->key;

	if (key == NGTK_KKEY_ARROW_LEFT && ted->cur_pos > 0)
		ted->cur_pos--;
	else if (key == NGTK_KKEY_ARROW_RIGHT && ted->cur_pos < curlen)
		ted->cur_pos++;
	if (curlen > 0 && key == NGTK_KKEY_BACKSPACE && ted->cur_pos > 0)
	{
		for (i = ted->cur_pos - 1; i < curlen; i++)
			textbuf[i] = textbuf [i + 1];
		ted->cur_pos--;
	}
	else if (curlen + 1 < ted->max_text_len)
	{
		char toAdd = '\0';
		if (key == NGTK_KKEY_SPACE)
			toAdd = ' ';
		else if (NGTK_KKEY_MIN_CHAR < key && key < NGTK_KKEY_MAX_CHAR && isprint (key))
			toAdd = key;

		if (toAdd != '\0')
		{
			for (i = curlen + 1; i > ted->cur_pos + 1; i--)
				textbuf[i] = textbuf [i - 1];

			textbuf[ted->cur_pos++] = toAdd;
		}
	}

	ngtk_component_set_text (comp, textbuf);
}

int   ngtk_basic_text_entry_get_cursor_position    (NGtkTextEntry *self)
{
	return NGTK_BASIC_TEXT_ENTRY_O2D (self) -> cur_pos;
}

char* ngtk_basic_text_entry_get_text_buf_ptr       (NGtkTextEntry *self)
{
	return NGTK_BASIC_TEXT_ENTRY_O2D (self) -> text;
}

int   ngtk_basic_text_entry_get_max_text_len       (NGtkTextEntry *self)
{
	return NGTK_BASIC_TEXT_ENTRY_O2D (self) -> max_text_len;
}
