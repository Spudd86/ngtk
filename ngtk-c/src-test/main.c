#include "../src/backends/windows/ngtk-win-defs.h"
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

	ngtk_win_start_main_loop ();
	
	/* TODO: free all the widgets that may still be open in this backend */
	ngtk_object_free (win);
}