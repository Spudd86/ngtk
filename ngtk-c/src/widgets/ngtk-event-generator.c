#include "ngtk-event-generator.h"

void ngtk_event_generator_add_mouse_listener (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc)
{
	NGTK_EVENT_GENERATOR_O2F (self)->add_mouse_listener (self, ListenFunc, Data, FreeFunc);
}
void ngtk_event_generator_fire_mouse_event (NGtkEventGenerator *self, NGtkMouseEvent *evnt)
{
	NGTK_EVENT_GENERATOR_O2F (self)->fire_mouse_event (self, evnt);
}
void ngtk_event_generator_clear_mouse_listeners (NGtkEventGenerator *self)
{
	NGTK_EVENT_GENERATOR_O2F (self)->clear_mouse_listeners (self);
}

void ngtk_event_generator_add_keyboard_listener (NGtkEventGenerator *self, NGtkKeyboardListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc)
{
	NGTK_EVENT_GENERATOR_O2F (self)->add_keyboard_listener (self, ListenFunc, Data, FreeFunc);
}
void ngtk_event_generator_fire_keyboard_event (NGtkEventGenerator *self, NGtkKeyboardEvent *evnt)
{
	NGTK_EVENT_GENERATOR_O2F (self)->fire_keyboard_event (self, evnt);
}
void ngtk_event_generator_clear_keyboard_listeners (NGtkEventGenerator *self)
{
	NGTK_EVENT_GENERATOR_O2F (self)->clear_keyboard_listeners (self);
}

void ngtk_event_generator_grab_keyboard_focus (NGtkEventGenerator *self)
{
	NGTK_EVENT_GENERATOR_O2F (self)->grab_keyboard_focus (self);
}
