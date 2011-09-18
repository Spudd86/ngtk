#ifndef __NGtk_event_generator_h__
#define __NGtk_event_generator_h__

#include "../utils/ngtk-utils.h"
#include "ngtk-widget-types.h"
#include "ngtk-event-codes.h"

typedef void (*NGtkMouseListener)    (NGtkEventGenerator *comp, const NGtkMouseEvent    *evnt, void* data);
typedef void (*NGtkKeyboardListener) (NGtkEventGenerator *comp, const NGtkKeyboardEvent *evnt, void* data);

typedef struct _NGtkEventGeneratorF {
	void (*add_mouse_listener)       (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
	void (*fire_mouse_event)         (NGtkEventGenerator *self, NGtkMouseEvent *evnt);
	void (*clear_mouse_listeners)    (NGtkEventGenerator *self);

	void (*add_keyboard_listener)    (NGtkEventGenerator *self, NGtkKeyboardListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
	void (*fire_keyboard_event)      (NGtkEventGenerator *self, NGtkKeyboardEvent *evnt);
	void (*clear_keyboard_listeners) (NGtkEventGenerator *self);

	void (*grab_keyboard_focus)      (NGtkEventGenerator *self);
} NGtkEventGeneratorF;

#define NGTK_EVENT_GENERATOR_O2F(comp) \
	NGTK_O2F_CAST(comp,NGTK_EVENT_GENERATOR_TYPE,NGtkEventGeneratorF)

#define NGTK_EVENT_GENERATOR_I2F(comp) \
	NGTK_I2F_CAST(comp,NGTK_EVENT_GENERATOR_TYPE,NGtkEventGeneratorF)

/* The following functions only wrap calls instead of doing them
 * directly from the NGtkEventGeneratorF object */

void ngtk_event_generator_add_mouse_listener       (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
void ngtk_event_generator_fire_mouse_event         (NGtkEventGenerator *self, NGtkMouseEvent *evnt);
void ngtk_event_generator_clear_mouse_listeners    (NGtkEventGenerator *self);

void ngtk_event_generator_add_keyboard_listener    (NGtkEventGenerator *self, NGtkKeyboardListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc);
void ngtk_event_generator_fire_keyboard_event      (NGtkEventGenerator *self, NGtkKeyboardEvent *evnt);
void ngtk_event_generator_clear_keyboard_listeners (NGtkEventGenerator *self);

void ngtk_event_generator_grab_keyboard_focus      (NGtkEventGenerator *self);

#endif
