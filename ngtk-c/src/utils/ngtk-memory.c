#include "ngtk-utils.h"
#include <stdio.h>

void* ngtk_debug_malloc (int size, const char *type)
{
	void* d = malloc (size);
	fprintf (stderr, "%p allocated for %s\n", d, type);
	return d;
}

void ngtk_debug_free (void *where)
{
	free (where);
	fprintf (stderr, "%p freed\n", where);
}
