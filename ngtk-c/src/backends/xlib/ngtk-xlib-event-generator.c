#include "ngtk-xlib-base.h"
#include "ngtk-xlib-event-generator.h"
#include "ngtk-xlib-defs.h"

NGtkInterface* ngtk_xlib_event_generator_create_interface ()
{
	NGtkInterface *in = ngtk_basic_event_generator_create_interface ();

	NGTK_EVENT_GENERATOR_I2F (in) -> add_mouse_listener       = ngtk_xlib_event_generator_add_mouse_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_mouse_listeners    = ngtk_xlib_event_generator_clear_mouse_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> fire_mouse_event         = ngtk_xlib_event_generator_fire_mouse_event;
	
	NGTK_EVENT_GENERATOR_I2F (in) -> add_keyboard_listener    = ngtk_xlib_event_generator_add_keyboard_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_keyboard_listeners = ngtk_xlib_event_generator_clear_keyboard_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> fire_keyboard_event      = ngtk_xlib_event_generator_fire_keyboard_event;
	
	NGTK_EVENT_GENERATOR_I2F (in) -> grab_keyboard_focus      = ngtk_xlib_event_generator_grab_keyboard_focus;

	return in;
}

void ngtk_xlib_event_generator_grab_keyboard_focus (NGtkEventGenerator *self)
{
	ngtk_xlib_set_focus_holder (self);
	ngtk_basic_event_generator_grab_keyboard_focus (self);
}
