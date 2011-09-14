#include "windows.h"

void ngtk_win_start_main_loop ()
{
	MSG Msg;

	/* The Message Loop. Receive messages and continue as long as there is no
	 * error (the return code is non negative) and as long as the message isn't
	 * a QUIT message (return code 0).
	 *
	 * We don't want to limit to a specific window, so pass NULL as the HWND
	 *
	 * Finally, for now we don't limit to just specific events, so both min and
	 * max of the message range are 0
	 */
	while (GetMessage (&Msg, NULL, 0, 0) > 0)
	{
		/* Do some processing of the message. TODO: what exactly? */
		TranslateMessage (&Msg);
		/* Send the message forward. TODO: how does this work with TranslateMessage? */
		DispatchMessage (&Msg);
	}
}

void ngtk_win_quit_main_loop ()
{
	PostQuitMessage (0);
}

