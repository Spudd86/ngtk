/*
 * calculator.c - Part of the NGtk library
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

#include "calculator.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../src/ngtk.h" /* For TRUE and FALSE, Assertions, etc. */

static double previous_number = 0;

static int has_math_error = FALSE;

static char display_text_buf[MAX_NUMBER_LEN+2] = { '\0' };
static char text_buf[MAX_NUMBER_LEN+1] = { '\0' };
static int  has_minus = FALSE;
static int  current_number_has_dot = 0;
static int  text_buf_pos = 0;

static MathOp current_op = NOP;

void HandleIfError ()
{
	if (has_math_error)
		ClearPressed ();
}

const char* GetNumberToDisplay ()
{
	if (has_math_error)
		return "42 is definetly not the answer!";
	else if (text_buf_pos == 0)
		sprintf (display_text_buf, " 0");
	else
		sprintf (display_text_buf, "%c%s", (has_minus ? '-' : '+'), text_buf);
	return display_text_buf;
}

void Optimize ()
{
	int i = 0, j;

	if (has_math_error) return;

	while (text_buf[i] == '0' && i < MAX_NUMBER_LEN)
		i++;

	if (current_number_has_dot)
		i--; /* We need one zero before the dot */

	if (i > 0)
	{
		for (j = 0; j < text_buf_pos - i; j++)
			text_buf[j] = text_buf[j+i];
		text_buf[text_buf_pos = j] = '\0';
	}
}

/* Like Optimize, but also remove un-necessary information after the
 * decimal point */
void OptimizeResult ()
{
	if (has_math_error) return;

	Optimize ();
	if (current_number_has_dot)
	{
		while (text_buf[text_buf_pos-1] == '0')
			text_buf[--text_buf_pos] = '\0';
		if (text_buf[text_buf_pos-1] == '.')
		{
			text_buf[--text_buf_pos] = '\0';
			current_number_has_dot = FALSE;
		}
	}
}

/* Remove trailing zeros, or zeros after decimal dot */
/* Simulate a digit that was pressed */
void DigitPressed (char c)
{
	HandleIfError ();
	if (text_buf_pos < MAX_NUMBER_LEN && isdigit (c))
	{
		text_buf[text_buf_pos++] = c;
		text_buf[text_buf_pos] = '\0';
	}

	Optimize ();
}

void DotPressed ()
{
	HandleIfError ();
	if (current_number_has_dot)
		return;

	if (text_buf_pos == 0) /* If we have nothing currently */
		text_buf[text_buf_pos++] = '0';

	text_buf[text_buf_pos++] = '.';

	text_buf[text_buf_pos] = '\0';
	current_number_has_dot = TRUE;

	Optimize ();
}

void ErasePressed ()
{
	HandleIfError ();
	if (text_buf_pos > 0)
	{
		if (text_buf[--text_buf_pos])
			current_number_has_dot = FALSE;
		text_buf[text_buf_pos] = '\0';
	}

	Optimize ();
}

const char* GetOpToDisplay ()
{
	if (has_math_error)
		return ":D ";

	switch (current_op)
	{
	case NOP:
		return "";
	case ADD:
		return "+";
	case MUL:
		return "*";
	case SUB:
		return "-";
	case DIV:
		return "/";
	default:
		ngtk_assert (FALSE);
		return NULL; /* Shut up compiler warnings */
	}
}

double GetCurrentNumber ()
{
	return atof (text_buf) * (has_minus ? -1 : 1);
}

void ComputePressed ()
{
	double result;
	double current;
	int i;

	if (has_math_error) return;

	current = GetCurrentNumber ();

	switch (current_op)
	{
	case NOP:
		return;
	case ADD:
		result = previous_number + current; break;
	case SUB:
		result = previous_number - current; break;
	case MUL:
		result = previous_number * current; break;
	case DIV:
		if (current == 0)
		{
			has_math_error = TRUE;
			return;
		}
		result = previous_number / current; break;
	default:
		ngtk_assert (FALSE);
		return; /* Shut up compiler warnings */
	}

	text_buf_pos = sprintf (text_buf, "%f", ABS (result));
	current_number_has_dot = FALSE;
	for (i = 0; i < text_buf_pos; i++)
		if ((current_number_has_dot = (text_buf[i] == '.')))
			break;
	has_minus = result < 0;

	current_op = NOP;

	OptimizeResult ();
}

void OpPressed (char op)
{
	if (has_math_error) return;
	ngtk_assert (op == '+' || op == '-' || op == '*' || op == '/');
	if (current_op == NOP)
	{
		previous_number = GetCurrentNumber ();
		text_buf[text_buf_pos = 0] = '\0';
		has_minus = FALSE;
		current_number_has_dot = 0;
	}
	current_op = (MathOp) op;
}

void ToggleMinus ()
{
	if (has_math_error) return;
	has_minus = ! has_minus;
}

void ClearPressed ()
{
	has_math_error = FALSE;
	current_op = NOP;
	text_buf[text_buf_pos = 0] = '\0';
	has_minus = FALSE;
	current_number_has_dot = 0;
}
