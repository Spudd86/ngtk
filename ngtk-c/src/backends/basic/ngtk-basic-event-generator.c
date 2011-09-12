#include "ngtk-basic-event-generator.h"

NGtkInterface* ngtk_basic_event_generator_create_interface ()
{
	NGtkInterface *in = ngtk_interface_new (NGTK_EVENT_GENERATOR_TYPE);
	NGtkBasicEventGeneratorD *begd;

	in->d[0] = begd = ngtk_new (NGtkBasicEventGeneratorD);
	begd->listener_infos  = ngtk_list_new ();
	in->d_free[0] = ngtk_basic_event_generator_d_free;

	in->f = ngtk_new (NGtkContainerF);
	NGTK_EVENT_GENERATOR_I2F (in) -> add_mouse_listener    = ngtk_basic_event_generator_add_mouse_listener;
	NGTK_EVENT_GENERATOR_I2F (in) -> clear_mouse_listeners = ngtk_basic_event_generator_clear_mouse_listeners;
	NGTK_EVENT_GENERATOR_I2F (in) -> grab_keyboard_focus   = ngtk_basic_event_generator_grab_keyboard_focus;
	NGTK_EVENT_GENERATOR_I2F (in) -> send_click            = ngtk_basic_event_generator_send_click;
	in->f_free = ngtk_free;

	return in;
}

static void basic_event_generator_clear_mouse_listeners (NGtkList *listeners)
{
	NGtkListNode *iter;

	ngtk_list_foreach (iter, listeners)
	{
		NGtkBasicListenerInfo *bli = (NGtkBasicListenerInfo *) iter->data;
		if (bli->data != NULL && bli->free_func != NULL)
			bli->free_func (bli->data);
		ngtk_free (bli);
	}
}

void ngtk_basic_event_generator_d_free (void *d)
{
	NGtkBasicEventGeneratorD *dReal = (NGtkBasicEventGeneratorD*) d;

	basic_event_generator_clear_mouse_listeners (dReal->listener_infos);

	ngtk_list_free (dReal->listener_infos);
	ngtk_free (d);
}

void ngtk_basic_event_generator_add_mouse_listener (NGtkEventGenerator *self, NGtkMouseListener ListenFunc, void *Data, NGtkFreeFunc FreeFunc)
{
	NGtkBasicListenerInfo *bli = ngtk_new (NGtkBasicListenerInfo);
	bli->data = Data;
	bli->free_func = FreeFunc;
	bli->listener = ListenFunc;
	ngtk_list_append (NGTK_BASIC_EVENT_GENERATOR_O2D (self)->listener_infos, bli);
}

void ngtk_basic_event_generator_send_click (NGtkEventGenerator *self, NGtkMouseEvent *evnt)
{
	NGtkListNode *iter;

	ngtk_list_foreach (iter, NGTK_BASIC_EVENT_GENERATOR_O2D (self)->listener_infos)
	{
		NGtkBasicListenerInfo *bli = (NGtkBasicListenerInfo *) iter->data;
		bli->listener (self, evnt, bli->data);
	}
}

void ngtk_basic_event_generator_clear_mouse_listeners (NGtkEventGenerator *self)
{
	basic_event_generator_clear_mouse_listeners (NGTK_BASIC_EVENT_GENERATOR_O2D (self)->listener_infos);
}

void ngtk_basic_event_generator_grab_keyboard_focus (NGtkEventGenerator *self)
{
}