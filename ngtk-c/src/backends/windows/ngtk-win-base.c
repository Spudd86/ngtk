#include <Windows.h>
#include "ngtk-win-base.h"

NGtkWinBaseI* ngtk_win_base_create_interface ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_WINBASE_TYPE);
	NGtkWinBaseD *wbd;

	in->d[0] = wbd = ngtk_new (NGtkWinBaseD);
	wbd->hwnd = NULL;
	wbd->base_wndproc = NULL;
	in->d_free[0] = ngtk_win_base_d_free;

	in->f = NULL;
	in->f = NULL;

	return in;
}

void ngtk_win_base_d_free (void *d)
{
	NGtkWinBaseD *dReal = (NGtkWinBaseD*) d;
	if (dReal->hwnd != NULL)
		DestroyWindow (dReal->hwnd);
	ngtk_free (d);
}