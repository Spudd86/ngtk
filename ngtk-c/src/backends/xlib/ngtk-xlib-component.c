#include "ngtk-xlib-defs.h"
#include "ngtk-xlib-base.h"
#include "ngtk-xlib-component.h"
#include "../basic/ngtk-basic.h"

NGtkInterface* ngtk_xlib_component_create_interface (int enabled, NGtkContainer *parent, const char* text, int visible)
{
	NGtkInterface *in = ngtk_basic_component_create_interface (enabled, parent, text, visible);

	NGTK_COMPONENT_I2F (in) -> redraw      = ngtk_xlib_component_redraw;
	NGTK_COMPONENT_I2F (in) -> set_enabled = ngtk_xlib_component_set_enabled;
	NGTK_COMPONENT_I2F (in) -> set_text    = ngtk_xlib_component_set_text;
	NGTK_COMPONENT_I2F (in) -> set_visible = ngtk_xlib_component_set_visible;

	return in;
}

void ngtk_xlib_component_set_enabled (NGtkComponent *self, int enabled)
{
	ngtk_basic_component_set_enabled (self, enabled);
	ngtk_xlib_component_redraw (self);
}

void ngtk_xlib_component_set_visible (NGtkComponent *self, int visible)
{
	int old_val = ngtk_component_get_visible (self);

	if (old_val != visible)
	{
		if (visible)
			XMapWindow (ngtk_xlib_get_display (), NGTK_XLIBBASE_O2D (self) -> wnd);
		else
			XUnmapWindow (ngtk_xlib_get_display (), NGTK_XLIBBASE_O2D (self) -> wnd);
	}
	ngtk_basic_component_set_visible (self, visible);
}

void ngtk_xlib_component_set_text (NGtkComponent *self, const char *text)
{
	ngtk_basic_component_set_text (self, text);
	ngtk_xlib_component_redraw (self);
}

void ngtk_xlib_component_redraw (NGtkComponent *self)
{
//	const NGtkBasicComponentD *dReal = NGTK_BASIC_COMPONENT_O2D (self);
//	WINDOW *wnd = ngtk_xlib_base_get_window (self);
//	const NGtkRectangle *area = ngtk_xlib_base_get_abs_rect (self);
//
//	int max_x, max_y, min_x, min_y;
//	
//	if (wnd == NULL || ! dReal->visible)
//		return;
//
//	/* TODO redraw */
//
//	ngtk_xlib_base_publish_window (self);
//	
//	/* Base will redraw the children if needed */
	ngtk_basic_component_redraw (self);
}
