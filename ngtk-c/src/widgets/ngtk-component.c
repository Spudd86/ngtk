#include "ngtk-component.h"

NGtkContainer* ngtk_component_get_parent  (NGtkComponent *self)
{
	return NGTK_COMPONENT_O2F (self)->get_parent (self);
}

int ngtk_component_get_enabled (NGtkComponent *self)
{
	return NGTK_COMPONENT_O2F (self)->get_enabled (self);
}

void ngtk_component_set_enabled (NGtkComponent *self, int enabled)
{
	NGTK_COMPONENT_O2F (self)->set_enabled (self, enabled);
}

int ngtk_component_get_visible (NGtkComponent *self)
{
	return NGTK_COMPONENT_O2F (self)->get_visible (self);
}

void ngtk_component_set_visible (NGtkComponent *self, int visible)
{
	NGTK_COMPONENT_O2F (self)->set_visible (self, visible);
}

const char* ngtk_component_get_text (NGtkComponent *self)
{
	return NGTK_COMPONENT_O2F (self)->get_text (self);
}

void ngtk_component_set_text (NGtkComponent *self, const char *text)
{
	NGTK_COMPONENT_O2F (self)->set_text (self, text);
}

void ngtk_component_redraw (NGtkComponent *self)
{
	NGTK_COMPONENT_O2F (self)->redraw (self);
}
