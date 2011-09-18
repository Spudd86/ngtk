#include "ngtk-basic-event-generator.h"

NGtkInterface* ngtk_basic_event_generator_create_interface ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_EVENT_GENERATOR_TYPE);
	NGtkBasicEventGeneratorD *begd;

	in->d[0] = begd = ngtk_new (NGtkBasicEventGeneratorD);

	begd->mouse_native_listener    = NULL;
	begd->mouse_listener_infos     = ngtk_list_new ();

	begd->keyboard_native_listener = NULL;
	begd->keyboard_listener_infos  = ngtk_list_new ();
	
	in->d_free[0] = ngtk_basic_event_generator_d_free;

	in->f = ngtk_new (NGtkContainerF);
	NGTK_EVENT_GENERATOR_I2F (in) -> add_mouse_listener       = ngtk_basic_event_generator_add_mouse_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_mouse_listeners    = ngtk_basic_event_generator_clear_mouse_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> fire_mouse_event         = ngtk_basic_event_generator_fire_mouse_event;
	
	NGTK_EVENT_GENERATOR_I2F (in) -> add_keyboard_listener    = ngtk_basic_event_generator_add_keyboard_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_keyboard_listeners = ngtk_basic_event_generator_clear_keyboard_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> fire_keyboard_event      = ngtk_basic_event_generator_fire_keyboard_event;
	
	NGTK_EVENT_GENERATOR_I2F (in) -> grab_keyboard_focus      = ngtk_basic_event_generator_grab_keyboard_focus;
	in->f_free = ngtk_free;

	return in;
}

static void basic_event_generator_clear_mouse_listeners (NGtkList *listeners)
{
	NGtkListNode *iter;

	ngtk_list_foreach (iter, listeners)
	{
		NGtkBasicMouseListenerInfo *bli = (NGtkBasicMouseListenerInfo *) iter->data;
		if (bli->data != NULL && bli->free_func != NULL)
			bli->free_func (bli->data);
		ngtk_free (bli);
	}
}

static void basic_event_generator_clear_keyboard_listeners (NGtkList *listeners)
{
	NGtkListNode *iter;

	ngtk_list_foreach (iter, listeners)
	{
		NGtkBasicKeyboardListenerInfo *bli = (NGtkBasicKeyboardListenerInfo *) iter->data;
		if (bli->data != NULL && bli->free_func != NULL)
			bli->free_func (bli->data);
		ngtk_free (bli);
	}
}

void ngtk_basic_event_generator_d_free (void *d)
{
	NGtkBasicEventGeneratorD *dReal = (NGtkBasicEventGeneratorD*) d;

	basic_event_generator_clear_mouse_listeners (dReal->mouse_listener_infos);
	ngtk_list_free (dReal->mouse_listener_infos);
	
	basic_event_generator_clear_keyboard_listeners (dReal->keyboard_listener_infos);
	ngtk_list_free (dReal->keyboard_listener_infos);
	
	ngtk_free (d);
}

void ngtk_basic_event_generator_add_mouse_listener (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc)
{
	NGtkBasicMouseListenerInfo *bli = ngtk_new (NGtkBasicMouseListenerInfo);
	bli->data = Data;
	bli->free_func = FreeFunc;
	bli->listener = ListenFunc;
	ngtk_list_append (NGTK_BASIC_EVENT_GENERATOR_O2D (self)->mouse_listener_infos, bli);
}

void ngtk_basic_event_generator_fire_mouse_event (NGtkEventGenerator *self, NGtkMouseEvent *evnt)
{
	NGtkListNode *iter;

	if (NGTK_BASIC_EVENT_GENERATOR_O2D (self) -> mouse_native_listener)
		NGTK_BASIC_EVENT_GENERATOR_O2D (self) -> mouse_native_listener (self, evnt, NULL);

	ngtk_list_foreach (iter, NGTK_BASIC_EVENT_GENERATOR_O2D (self)->mouse_listener_infos)
	{
		NGtkBasicMouseListenerInfo *bli = (NGtkBasicMouseListenerInfo *) iter->data;
		bli->listener (self, evnt, bli->data);
	}
}

void ngtk_basic_event_generator_clear_mouse_listeners (NGtkEventGenerator *self)
{
	basic_event_generator_clear_mouse_listeners (NGTK_BASIC_EVENT_GENERATOR_O2D (self)->mouse_listener_infos);
}

void ngtk_basic_event_generator_add_keyboard_listener (NGtkEventGenerator *self, NGtkKeyboardListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc)
{
	NGtkBasicKeyboardListenerInfo *bli = ngtk_new (NGtkBasicKeyboardListenerInfo);
	bli->data = Data;
	bli->free_func = FreeFunc;
	bli->listener = ListenFunc;
	ngtk_list_append (NGTK_BASIC_EVENT_GENERATOR_O2D (self)->keyboard_listener_infos, bli);
}

void ngtk_basic_event_generator_fire_keyboard_event (NGtkEventGenerator *self, NGtkKeyboardEvent *evnt)
{
	NGtkListNode *iter;

	if (NGTK_BASIC_EVENT_GENERATOR_O2D (self) -> keyboard_native_listener)
		NGTK_BASIC_EVENT_GENERATOR_O2D (self) -> keyboard_native_listener (self, evnt, NULL);

	ngtk_list_foreach (iter, NGTK_BASIC_EVENT_GENERATOR_O2D (self)->keyboard_listener_infos)
	{
		NGtkBasicKeyboardListenerInfo *bli = (NGtkBasicKeyboardListenerInfo *) iter->data;
		bli->listener (self, evnt, bli->data);
	}
}

void ngtk_basic_event_generator_clear_keyboard_listeners (NGtkEventGenerator *self)
{
	basic_event_generator_clear_keyboard_listeners (NGTK_BASIC_EVENT_GENERATOR_O2D (self)->keyboard_listener_infos);
}

void ngtk_basic_event_generator_grab_keyboard_focus (NGtkEventGenerator *self)
{
}
