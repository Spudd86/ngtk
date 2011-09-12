#ifndef __NGtk_basic_event_generator__
#define __NGtk_basic_event_generator__

#include "../../widgets/ngtk-widgets.h"

typedef struct _ngtk_basic_listener_info {
	NGtkMouseListener  listener;
	void              *data;
	NGtkFreeFunc       free_func;
} NGtkBasicListenerInfo;

typedef struct _ngtk_basic_event_generator_d {
	NGtkList* listener_infos;
} NGtkBasicEventGeneratorD;

#define NGTK_BASIC_EVENT_GENERATOR_O2D(comp) NGTK_O2D_CAST(comp,NGTK_EVENT_GENERATOR_TYPE,NGtkBasicEventGeneratorD,0)
#define NGTK_BASIC_EVENT_GENERATOR_I2D(comp) NGTK_I2D_CAST(comp,NGTK_EVENT_GENERATOR_TYPE,NGtkBasicEventGeneratorD,0)

NGtkInterface* ngtk_basic_event_generator_create_interface ();
void           ngtk_basic_event_generator_d_free           (void *d);

void ngtk_basic_event_generator_add_mouse_listener    (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
void ngtk_basic_event_generator_send_click            (NGtkEventGenerator *self, NGtkMouseEvent *evnt);
void ngtk_basic_event_generator_clear_mouse_listeners (NGtkEventGenerator *self);
void ngtk_basic_event_generator_grab_keyboard_focus   (NGtkEventGenerator *self);


#endif