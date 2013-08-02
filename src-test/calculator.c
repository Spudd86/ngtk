/*
 * calculator.c
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
