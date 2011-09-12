#ifndef __NGtk_event_generator_h__
#define __NGtk_event_generator_h__

#include "../utils/ngtk-utils.h"
#include "ngtk-widget-types.h"

typedef enum {
	NGTK_MOUSE_LCLICK,
	NGTK_MOUSE_RCLICK,
	NGTK_MOUSE_MCLICK,
	NGTK_MOUSE_SCROLL_UP,
	NGTK_MOUSE_SCROLL_DOWN
} NGtkMouseEventType;

typedef struct _ngtk_mouse_event {
	NGtkMouseEventType met;
} NGtkMouseEvent;

typedef void (*NGtkMouseListener) (NGtkEventGenerator *comp, const NGtkMouseEvent *evnt, void* data);

typedef struct _NGtkEventGeneratorF {
	void (*add_mouse_listener)    (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
	void (*send_click)            (NGtkEventGenerator *self, NGtkMouseEvent *evnt);
	void (*clear_mouse_listeners) (NGtkEventGenerator *self);
	void (*grab_keyboard_focus)   (NGtkEventGenerator *self);
} NGtkEventGeneratorF;

#define NGTK_EVENT_GENERATOR_O2F(comp) \
	NGTK_O2F_CAST(comp,NGTK_EVENT_GENERATOR_TYPE,NGtkEventGeneratorF)

#define NGTK_EVENT_GENERATOR_I2F(comp) \
	NGTK_I2F_CAST(comp,NGTK_EVENT_GENERATOR_TYPE,NGtkEventGeneratorF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkEventGeneratorF object */

void ngtk_event_generator_add_mouse_listener    (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
void ngtk_event_generator_send_click            (NGtkEventGenerator *self, NGtkMouseEvent *evnt);
void ngtk_event_generator_clear_mouse_listeners (NGtkEventGenerator *self);
void ngtk_event_generator_grab_keyboard_focus   (NGtkEventGenerator *self);

#endif