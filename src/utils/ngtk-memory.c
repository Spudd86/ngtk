#include "ngtk-utils.h"
#include <stdio.h>

static int malloc_count = 0;
void* ngtk_debug_malloc (int size, const char *type)
{
	void* d = malloc (size);
	fprintf (stderr, "%p allocated for %s\n", d, type);
	malloc_count++;
	return d;
}

void ngtk_debug_free (void *where)
{
	ngtk_assert (--malloc_count >= 0);
	free (where);
	fprintf (stderr, "%p freed (%d allocation remaining)\n", where, malloc_count);
}
