#ifndef __NGtk_xlib_event_generator__
#define __NGtk_xlib_event_generator__

#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkEventGeneratorF object */
NGtkInterface* ngtk_xlib_event_generator_create_interface ();

#define ngtk_xlib_event_generator_add_mouse_listener       ngtk_basic_event_generator_add_mouse_listener
#define ngtk_xlib_event_generator_fire_mouse_event         ngtk_basic_event_generator_fire_mouse_event
#define ngtk_xlib_event_generator_clear_mouse_listeners    ngtk_basic_event_generator_clear_mouse_listeners

#define ngtk_xlib_event_generator_add_keyboard_listener    ngtk_basic_event_generator_add_keyboard_listener
#define ngtk_xlib_event_generator_fire_keyboard_event      ngtk_basic_event_generator_fire_keyboard_event
#define ngtk_xlib_event_generator_clear_keyboard_listeners ngtk_basic_event_generator_clear_keyboard_listeners

void    ngtk_xlib_event_generator_grab_keyboard_focus      (NGtkEventGenerator* self);

#endif
