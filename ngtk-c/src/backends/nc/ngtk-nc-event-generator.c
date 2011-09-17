#include <Ncdows.h>
#include "ngtk-nc-base.h"
#include "ngtk-nc-event-generator.h"

NGtkInterface* ngtk_nc_event_generator_create_interface ()
{
	NGtkInterface *in = ngtk_basic_event_generator_create_interface ();

	NGTK_EVENT_GENERATOR_I2F (in) -> add_mouse_listener    = ngtk_nc_event_generator_add_mouse_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_mouse_listeners = ngtk_nc_event_generator_clear_mouse_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> grab_keyboard_focus   = ngtk_nc_event_generator_grab_keyboard_focus;
	NGTK_EVENT_GENERATOR_I2F (in) -> send_click            = ngtk_nc_event_generator_send_click;
}

void ngtk_nc_event_generator_grab_keyboard_focus (NGtkEventGenerator *self)
{
	SetFocus (NGTK_NCBASE_O2D (self)->hwnd);
	ngtk_basic_event_generator_grab_keyboard_focus (self);
}