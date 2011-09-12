#include "../src/backends/windows/ngtk-widget-window.h"
#include <stdio.h>

void MyFunc(NGtkEventGenerator *comp, const NGtkMouseEvent *evnt, void* data)
{
	printf ("You clicked the window!\n");
}

void MyFunc2(NGtkEventGenerator *comp, const NGtkMouseEvent *evnt, void* data)
{
	printf ("You clicked the button!\n");
}

int main (int argc, char **argv)
{
	NGtkObject* win = ngtk_win_create_window ("Oh yeah!", FALSE);
	NGtkObject* but = ngtk_win_create_button ("Oh blah!", win);
	NGtkRectangle rect;
	MSG Msg;

	ngtk_event_generator_add_mouse_listener (win, MyFunc, NULL, NULL);
	ngtk_event_generator_add_mouse_listener (but, MyFunc2, NULL, NULL);

	ngtk_component_set_visible (but, TRUE);
	rect.x = 0;
	rect.y = 0;
	rect.w = 50;
	rect.h = 50;
	ngtk_container_place_child (win, but, &rect);

	ngtk_component_set_visible (win, TRUE);

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
	/* TODO: free all the widgets that may still be open in this backend */
	ngtk_object_free (win);
}