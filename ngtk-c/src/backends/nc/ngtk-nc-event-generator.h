#ifndef __NGtk_nc_event_generator__
#define __NGtk_nc_event_generator__

#include "../../widgets/ngtk-widgets.h"
#include "../basic/ngtk-basic.h"

NGtkInterface*     ngtk_nc_event_generator_create_interface ();

#define  ngtk_nc_event_generator_add_mouse_listener     ngtk_basic_event_generator_add_mouse_listener
#define  ngtk_nc_event_generator_send_click             ngtk_basic_event_generator_send_click
#define  ngtk_nc_event_generator_clear_mouse_listeners  ngtk_basic_event_generator_clear_mouse_listeners

void     ngtk_nc_event_generator_grab_keyboard_focus    (NGtkEventGenerator *self);

#endif